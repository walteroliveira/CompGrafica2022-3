#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>//Mac OS use _4_1_Core
#include <QTimer>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);

signals:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
private:
    QTimer timer;
    bool blinkFlag{false};
public slots:
    void toggleDarkMode(bool);
};

#endif // OPENGLWIDGET_H
