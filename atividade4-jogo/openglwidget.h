#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QVector4D>
#include <vector>
#include <QFile>
#include <QApplication>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <array>
#include <cmath>
#include <QRandomGenerator>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    GLuint vboVertices{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};

    std::vector<QVector4D> vertices;
    std::vector<QVector4D> colors;
    std::vector<GLuint> indices;

    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void changeDiagonal();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    float playerPosYOffset{0};
    float playerPosY{0};

    float targetPosYOffset{2.0f};
    float targetPosY{0};

    QTimer timer;
    QTimer timerHit;
    QTimer timerEnemy;

    QElapsedTimer elapsedTime;


    bool shootingZ{false};
    bool shootingX{false};
    bool upShot{true};
    bool enemyActive{false};
    bool shootingEnemy{false};
    bool shieldEnemy{false};
    bool hit{false};
    std::array<float,2> projectilePos;
    std::array<float,2> enemyProjectilePos;
    int numHits{0};

protected:
    void initializeGL() ;
    void resizeGL(int w, int h);
    void paintGL();
    void bgHit();
    void enemy();

signals:
    void updateHitsLabel(QString);
public slots:
    void animate();
};
#endif // OPENGLWIDGET_H
