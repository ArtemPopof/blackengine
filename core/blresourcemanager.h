#ifndef BLRESOURCEMANAGER_H
#define BLRESOURCEMANAGER_H

#include "blresource.h"

#include <map>
#include <string>
#include <memory>

#include "blconstants.h"

namespace black {

/**
 * @brief The ResourceManager class
 *  Handles all ingame resources such as
 * textures, meshes, models, sounds and so on.
 *
 * Relies on the Service Manager pattern because of
 * private constructor.
 *
 * Stores resources by its relative to the resource
 * directory path called guid.
 *
 * @author george popoff <popoff96@live.com>
 *
 * @version 1.0 12.03.2017
 *  Working version
 * @version 1.1 19.03.2017
 *  Full support of smart pointers.
 *  Support of full pathes as well as relative.
 *
 */
class ResourceManager
{
public:
    using guid_t = std::string;

public:
    static ResourceManager& getInstance() {
        //TODO: change this hardcoded constant to normal
        // constant from Constants::
        static ResourceManager instance(Constants::RES_PATH);
        return instance;
    }

    /**
     * @brief Loads resource with given file path.
     *
     * @param path resource file path
     */
    template<class T> string load(std::string path, bool relative = true);

    /**
     * @brief Returns a resource with given file path.
     *  If resource hadn't been loaded yet - loads it.
     *
     * @param guid resource guid to get
     */
    template<class T> std::shared_ptr<T> get(guid_t guid, bool relative = true);

    /**
     * @brief Unloading resource by given guid.
     *
     * @param guid resource guid to unload
     */
    void unload(guid_t guid);

    //TODO: friend class ServiceManager;

    // Constructor can be accessed by ServiceManager only
private:
    ResourceManager(std::string resPath);
    ~ResourceManager();

private:
    std::map< guid_t, std::shared_ptr<Resource> > m_resources;

    std::string m_resourcesPath;
};


// TEMPLATE FUNCTIONS

template<class T>
string ResourceManager::load(std::string path, bool relative)
{
    auto res = std::make_shared<T>();

    guid_t guid = path;

    // Allow relative and non-relative path
    // cause when loading nested resources there are
    // problems with relative path
    if ( relative ) {
        guid = path;
        path = m_resourcesPath + path;
    }

    res->load(path);

    m_resources[path] = res;

    return guid;
}

template<class T>
std::shared_ptr<T> ResourceManager::get(guid_t guid, bool relative)
{
    // If relative - guid += resource path
    if ( relative ) {
        guid = m_resourcesPath + guid;
    }

    try {
        m_resources.at(guid);
    } catch (std::out_of_range e) {
        load<T>(guid, false); // Full path already
    }

    return std::dynamic_pointer_cast<T>(m_resources[guid]);
}

}
#endif // BLRESOURCEMANAGER_H