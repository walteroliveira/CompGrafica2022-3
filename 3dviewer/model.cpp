#include "model.h"

Model::Model()
{
    shaderProgram.resize(fragmentShaderFile.size());
}

void Model::readOFFFile(const QString &fileName)
{
    QFile data(fileName);
    if(!data.open(QFile::ReadOnly)) {
        qWarning("Cannot open file");
        return;
    }

    QTextStream stream(&data);
    QString notUsed;
    stream >> notUsed; //OFF
    stream >> numVertices >> numFaces >> notUsed;
    vertices.resize(numVertices);
    indices.resize(numFaces*3);

    float x,y,z;

    //vertices
    for(size_t i{0}; i < numVertices;++i){
        stream >> x >> y >> z;
        vertices[i] = QVector4D(x,y,z,1);
    }
    //faces
    for(size_t i{0}; i < numFaces; ++i){
        stream >> notUsed >> indices[i*3 + 0] >> indices[i*3 +
        1] >> indices[i*3 + 2];
    }

    //rescaleModel();//testar sem este comando
    data.close();
}
