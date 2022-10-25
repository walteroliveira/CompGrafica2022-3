#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QTimer>
#include <QVector4D>
#include <QFile>
#include <QKeyEvent>
#include <QApplication>
#include <QFileDialog>
#include <memory>

#include <model.h>

class OpenGLWidget : public QOpenGLWidget, protected
QOpenGLFunctions_4_0_Core
{
Q_OBJECT
public:
explicit OpenGLWidget(QWidget *parent = nullptr);
~OpenGLWidget();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);

    std::shared_ptr<Model> model;

    void createVBOs(std::shared_ptr<Model>);
    void createShaders(std::shared_ptr<Model>);
    void destroyVBOs(std::shared_ptr<Model>);
    void destroyShaders(std::shared_ptr<Model>);

    signals:
        void statusBarMessage(QString);

    public slots:
        void toggleDarkMode(bool);
        void showFileOpenDialog();
    };
#endif // OPENGLWIDGET_H

