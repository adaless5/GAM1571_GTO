#ifndef __Mesh_H__
#define __Mesh_H__

#include "VertexFormat.h"

class fw::ShaderProgram;
class Camera;

class Mesh
{
protected:
    GLuint m_VBO;
    unsigned int m_NumVerts;
    GLenum m_PrimitiveType;
    fw::AABB m_BoundingBox;

public:
    Mesh();
    ~Mesh();

    void Init(VertexFormat* pVerts, unsigned int numVerts, GLenum primitiveType);
    void Draw(Camera* pCamera, fw::ShaderProgram* pShader, fw::vec2 pos, float angle, GLuint textureID);

    void GenerateTriangle();
    void GenerateCircle();
    void GenerateSquare(float size);
    void GenerateBuilding(float size);
    void GenerateVehicle(float width, float length);

    fw::AABB GetBoundingBox() { return m_BoundingBox; }
};

#endif //__Mesh_H__
