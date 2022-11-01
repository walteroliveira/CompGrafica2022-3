#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <QVector4D>
#include <QVector3D>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMatrix4x4>

class Model
{
public:
    Model();
    ~Model() = default;

    QMatrix4x4 modelMatrix;

    std::vector<QVector4D> vertices;
    std::vector<unsigned int> indices;

    unsigned numVertices{0};
    unsigned numFaces{0};
    unsigned vao{0};
    unsigned vboVertices{0};
    unsigned eboIndices{0};

    void readOFFFile(const QString &);

    void computeBBox();
    void rescaleModelMatrix();
    QVector3D centroidBB, minBB, maxBB;
    float diagonalBB{0};//poderia ter uma classe BBox,separadamente

    int currentShader{0};

    std::vector<QString> vertexShaderFile =
    {":/shaders/vzdepth.glsl"};
    std::vector<QString> fragmentShaderFile =
    {":/shaders/fzdepth.glsl"};
    std::vector<unsigned> shaderProgram;
};
#endif // MODEL_H
