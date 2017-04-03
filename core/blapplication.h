#ifndef BLAPPLICATION_H
#define BLAPPLICATION_H

#include <memory>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <bllight.h>


#include "core/blmesh.h"
#include "core/blcamera.h"

#include "utils/blcubemesh.h"
#include "utils/bltimer.h"

#include "bltexture.h"
#include "blconstants.h"
#include "blmodel.h"

using std::unique_ptr;
using std::shared_ptr;

class BLApplication : public QOpenGLWidget, public QOpenGLFunctions {

public:
    BLApplication(QWidget *parent = nullptr);

    virtual ~BLApplication();

    unique_ptr<black::Camera> m_camera;

protected:
    // QOpenGLWidget interface
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    // QWidget interface
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *);
private:
    void initModels();
    void loadResources();
    void prepareToRender();

private:
    unique_ptr<QOpenGLShaderProgram> m_program;
    unique_ptr<QOpenGLShader> m_vShader;
    unique_ptr<QOpenGLShader> m_fShader;

    unique_ptr<black::CubeMesh> m_cubeMesh;
    unique_ptr<black::Mesh> m_axisMesh;

    bool m_initialized = false;

    unique_ptr<black::Timer> m_timer;

    // Handled by rm
    std::shared_ptr<black::Model> m_stallMesh;
    std::shared_ptr<black::Model> m_bodyMesh;
    std::shared_ptr<black::Model> m_monkeyMesh;
    std::shared_ptr<black::Model> m_houseModel;

    std::shared_ptr<black::Texture> m_brickTexture;

    unique_ptr<black::Light> m_lightSource;

    // QWindow interface
protected:
    void wheelEvent(QWheelEvent *) override;
};

#endif // BLAPPLICATION_H