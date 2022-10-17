#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QVector4D>
#include <vector>
#include <QFile>
#include <QApplication>
#include <QKeyEvent>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    GLuint vboVerticesHouse{0};
    GLuint vboColorsHouse{0};
    GLuint eboIndicesHouse{0};
    GLuint vaoHouse{0};

    GLuint vboVerticesTree{0};
    GLuint vboColorsTree{0};
    GLuint eboIndicesTree{0};
    GLuint vaoTree{0};

    GLuint vboVerticesSun{0};
    GLuint vboColorsSun{0};
    GLuint eboIndicesSun{0};
    GLuint vaoSun{0};

    std::vector<QVector4D> verticesHouse;
    std::vector<QVector4D> colorsHouse;
    std::vector<GLuint> indicesHouse;

    std::vector<QVector4D> verticesTree;
    std::vector<QVector4D> colorsTree;
    std::vector<GLuint> indicesTree;

    std::vector<QVector4D> verticesSun;
    std::vector<QVector4D> colorsSun;
    std::vector<GLuint> indicesSun;

    GLuint shaderProgram{0};

    void createVBOs();
    void createVAOHouse();
    void createVAOTree();
    void createVAOSun();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void changeDiagonal();
    void keyPressEvent(QKeyEvent *event);

protected:
    void initializeGL() ;
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void toggleDarkMode(bool);
};
#endif // OPENGLWIDGET_H
