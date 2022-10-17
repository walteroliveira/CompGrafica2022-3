#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

OpenGLWidget::~OpenGLWidget()
{
    destroyVBOs();
    destroyShaders();
}


void OpenGLWidget::createShaders()
{
    makeCurrent();
    destroyShaders();
    QFile vs(":/shaders/vshader1.glsl");
    QFile fs(":/shaders/fshader1.glsl");
    if(!vs.open(QFile::ReadOnly | QFile::Text)) return;//inserir mensagem de erro
    if(!fs.open(QFile::ReadOnly | QFile::Text)) return;//inserir mensagem de erro

    auto byteArrayVs{vs.readAll()};
    auto byteArrayFs{fs.readAll()};
    const char *c_strVs{byteArrayVs};
    const char *c_strFs{byteArrayFs};

    vs.close();
    fs.close();
    GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &c_strVs,0);
    glCompileShader(vertexShader);
    GLint isCompiled{0};
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE)
    {
        GLint maxLength{0};
        glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        return;
    }

    GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader,1,&c_strFs,0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&isCompiled);

    if(isCompiled == GL_FALSE)
    {
        GLint maxLength{0};
        glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    GLint isLinked{0};
    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE)
    {
        GLint maxLength{0};
        glGetProgramiv(shaderProgram,GL_INFO_LOG_LENGTH,&maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram,maxLength,&maxLength, &infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderProgram,vertexShader);
    glDetachShader(shaderProgram,fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void OpenGLWidget::destroyShaders()
{
    makeCurrent();
    glDeleteProgram(shaderProgram);
}

void OpenGLWidget::createVAOHouse()
{
    verticesHouse.resize(7);
    colorsHouse.resize(7);
    indicesHouse.resize(9); //2*3
    verticesHouse[0] = QVector4D(-0.8, -0.8 , 0, 1);
    verticesHouse[1] = QVector4D( -0.2, -0.8 , 0, 1);
    verticesHouse[2] = QVector4D( -0.2, -0.2 , 0, 1);
    verticesHouse[3] = QVector4D(-0.8, -0.2 , 0, 1);

    verticesHouse[4] = QVector4D(-0.9, -0.2 , 0, 1);
    verticesHouse[5] = QVector4D(-0.5, 0.1 , 0.2, 1);
    verticesHouse[6] = QVector4D(-0.1, -0.2 , 0, 1);

    // Create colors for the vertices
    colorsHouse[0] = QVector4D(1, 0, 0, 1); // Red
    colorsHouse[1] = QVector4D(0, 1, 0, 1); // Green
    colorsHouse[2] = QVector4D(0, 0, 1, 1); // Blue
    colorsHouse[3] = QVector4D(1, 1, 0, 1); // Yellow
    colorsHouse[4] = QVector4D(1, 1, 0, 1); // Yellow
    colorsHouse[5] = QVector4D(1, 1, 0, 1); // Yellow
    colorsHouse[6] = QVector4D(1, 1, 0, 1); // Yellow

    // Topology of the mesh ( square )
    indicesHouse[0] = 0; indicesHouse[1] = 1; indicesHouse[2] = 2;
    indicesHouse[3] = 2; indicesHouse[4] = 3; indicesHouse[5] = 0;
    indicesHouse[6] = 4; indicesHouse[7] = 5; indicesHouse[8] = 6;

    glGenVertexArrays(1,&vaoHouse);
    glBindVertexArray(vaoHouse);
    glGenBuffers(1,&vboVerticesHouse);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticesHouse);
    glBufferData(GL_ARRAY_BUFFER, verticesHouse.size()*sizeof(QVector4D),verticesHouse.data(),
    GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);
    glGenBuffers (1, &vboColorsHouse);
    glBindBuffer (GL_ARRAY_BUFFER,vboColorsHouse);
    glBufferData (GL_ARRAY_BUFFER,colorsHouse.size()*sizeof(QVector4D),colorsHouse.data(),
    GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);
    glGenBuffers (1, &eboIndicesHouse);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesHouse);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesHouse.size() * sizeof (GLuint), indicesHouse.data() ,
    GL_STATIC_DRAW);
}

void OpenGLWidget::createVAOTree()
{
    verticesTree.resize(9);
    colorsTree.resize(9);
    indicesTree.resize(12); //2*3

    verticesTree[0] = QVector4D(0.5, -0.8 , 0, 1);
    verticesTree[1] = QVector4D(0.6, -0.8 , 0, 1);
    verticesTree[2] = QVector4D(0.6, -0.2 , 0, 1);
    verticesTree[3] = QVector4D(0.5, -0.2 , 0, 1);

    verticesTree[4] = QVector4D(0.45, -0.25,0, 1);
    verticesTree[5] = QVector4D(0.65, -0.25,0, 1);
    verticesTree[6] = QVector4D(0.65, 0.15, 0, 1);
    verticesTree[7] = QVector4D(0.45, 0.15, 0, 1);
    verticesTree[8] = QVector4D(0, 0,0, 1);

    // https://www.tug.org/pracjourn/2007-4/walden/color.pdf
    // Create colors for the vertices
    colorsTree[0] = QVector4D(0.538, 0.294, 0, 1); // Brown
    colorsTree[1] = QVector4D(0.538, 0.294, 0, 1); // Brown
    colorsTree[2] = QVector4D(0.538, 0.294, 0, 1); // Brown
    colorsTree[3] = QVector4D(0.538, 0.294, 0, 1); // Brown
    colorsTree[4] = QVector4D(0, 0.8, 0, 0.4); // Yellow
    colorsTree[5] = QVector4D(0, 0.8, 0, 0.4); // Yellow
    colorsTree[6] = QVector4D(0, 0.8, 0, 0.4); // Yellow
    colorsTree[7] = QVector4D(0, 0.8, 0, 0.4); // Yellow
    colorsTree[8] = QVector4D(0, 0.8, 0, 0.4); // Yellow


    // Topology of the mesh ( square )
    indicesTree[0] = 0; indicesTree[1] = 1; indicesTree[2] = 2;
    indicesTree[3] = 2; indicesTree[4] = 3; indicesTree[5] = 0;

    indicesTree[6] = 4; indicesTree[7] = 5; indicesTree[8] = 6;
    indicesTree[9] = 4; indicesTree[10] =6; indicesTree[11] = 7;
//    indicesTree[12] = 7; indicesTree[13] = 8;

    glGenVertexArrays(1,&vaoTree);
    glBindVertexArray(vaoTree);

    glGenBuffers(1,&vboVerticesTree);
    glBindBuffer(GL_ARRAY_BUFFER,vboVerticesTree);
    glBufferData(GL_ARRAY_BUFFER, verticesTree.size()*sizeof(QVector4D),verticesTree.data(),
    GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboColorsTree);
    glBindBuffer (GL_ARRAY_BUFFER,vboColorsTree);
    glBufferData (GL_ARRAY_BUFFER,colorsTree.size()*sizeof(QVector4D),colorsTree.data(),
    GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndicesTree);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesTree);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesTree.size() * sizeof (GLuint), indicesTree.data() ,
    GL_STATIC_DRAW);
}
void OpenGLWidget::createVBOs()
{
    makeCurrent();
    destroyVBOs();
    createVAOHouse();
    createVAOTree();
}

void OpenGLWidget::destroyVBOs()
{
    makeCurrent ();
    glDeleteBuffers(1, &vboVerticesHouse);
    glDeleteBuffers (1, &vboColorsHouse);
    glDeleteBuffers (1, &eboIndicesHouse);
    glDeleteBuffers(1, &vboVerticesTree);
    glDeleteBuffers (1, &vboColorsTree);
    glDeleteBuffers (1, &eboIndicesTree);
    glDeleteVertexArrays (1, &vaoHouse);
    glDeleteVertexArrays (1, &vaoTree);
    vboVerticesHouse=0;
    eboIndicesHouse=0;
    vboColorsHouse=0;
    vaoHouse=0;
    vboVerticesTree=0;
    eboIndicesTree=0;
    vboColorsTree=0;
    vaoTree=0;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);

    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));

    createShaders();
    createVBOs();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vaoHouse);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
    glBindVertexArray(vaoTree);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void OpenGLWidget::toggleDarkMode(bool changeToDarkMode)
{
    makeCurrent();
    if(changeToDarkMode)
        glClearColor(0,0,0,1);
    else
        glClearColor(1,1,1,1);
    update();
}

void OpenGLWidget::resizeGL(int w, int h)
{

}

void OpenGLWidget::changeDiagonal()
{
    makeCurrent();
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndicesHouse);
    // glMappBuffer-> mac
    auto idx{static_cast<GLuint*>(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER , 0,
    indicesHouse.size()*sizeof(GL_UNSIGNED_INT),GL_MAP_WRITE_BIT))};
    idx[0] = 0; idx[1] = 1; idx[2] = 3;
    idx[3] = 1; idx[4] = 2; idx[5] = 3;
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) ;
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent
*event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            QApplication::quit();
        break;//desnecessario
    }
}
