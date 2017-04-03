#ifndef MESH_H
#define MESH_H

#include "blresource.h"
#include "blresourcemanager.h"

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include <vector>
#include <string>

namespace black {

/**
 * @brief The Mesh class
 * Vertices data. Represents actualy VBO and
 * all vbo's.
 */
class Mesh : public Resource, protected QOpenGLFunctions //TODO: REMOVE THIS WHEN GLOBAL CLASSES WILL BE HERE
{
    friend class ResourceManager;
public:
    /**
     * @brief Creates a empty vao object
     *
     * @version 0.4 15.03.2017
     *  Texture support. Shader was removed from dependencies.
     *  Now class inherit QOpenGLFunctions, probably temporary solution.
     *
     * @version 0.2 07.03.2017
     * First working version
     *
     * @date 07.03.2017
     * @author george popoff <popoff96@live.com>
     */
    Mesh();

    /**
     * @brief Creates vao object and
     *  fills it with given position data.
     *
     * @param position Array of vertex elements
     * @param program A pointer to program. Need to
     *  set attribute array properly.
     *
     * @throw NoSupportedException
     * @date 07.03.2017
     * @author george popoff <popoff96@live.com>
     */
    Mesh(const std::vector<GLfloat> &position,
         const std::vector<GLclampf> &textureCoords);

    void setPositionData(const std::vector<GLfloat> &position);

    void setIndexData(const std::vector<GLuint> &index);

    void setColorData(const std::vector<GLclampf> &color);

    void setTextureCoords(const std::vector<GLclampf> &coords);

    void setNormalData(const std::vector<float> &normals);

    /**
     * @brief bind Binds vertex array buffer
     *  to the current context to be used as
     *  current VAO. You can use it to set up
     *  vertexAttribPointers or so.
     */
    void bind();
    void release();


    ~Mesh();

    GLuint vertexCount() const { return m_vertexCount; }
    bool isIndexed() const { return m_isIndexProvided; }

    // Resource interface
private:
    void load(string file) override;

private:
    bool   m_isDataProvided  = false;
    bool   m_isIndexProvided = false;
    GLuint m_vertexCount;

    QOpenGLVertexArrayObject m_vao;

    QOpenGLBuffer m_positionVBO;
    QOpenGLBuffer m_indexVBO;
    QOpenGLBuffer m_textureVBO;
    QOpenGLBuffer m_normalVBO;

    QOpenGLBuffer m_colorVBO;

    QOpenGLShaderProgram *m_program;
};


/** ========================================================== **/
/*
 *                       Exceptions
 ** ========================================================== **/
class NotSupportedException : public std::exception
{

public:
    /**
     * @brief NotSupportedException
     *  Constructs exception by providing a name
     *  of feature that hasn't been created.
     *
     * @param feature NotSupported feature name
     */
    NotSupportedException(const std::string &feature)
        : m_feature(feature)
    {

    }

    // exception interface
public:
    const char *what() const throw()
    {
        std::string msg = m_feature + " not supported!"
            " Check your OpenGL support for this feature.";

        return msg.c_str();
    }

private:
    std::string m_feature;

};
class NoDataProvidedException : public std::exception {

    // exception interface
public:
    const char *what() const throw()
    {
        return "Cannot render empty buffer!";
    }

private:
};
}
#endif // MESH_H