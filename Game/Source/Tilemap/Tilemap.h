#pragma once

class Mesh;
class Camera;

enum class TileType
{
    Road4,     // 0
    Road2UD,   // 1
    Road2LR,   // 2
    Building,  // 3
    Water,     // 4
    NumTypes,  // 5
};

struct TileProperties
{
    Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    GLuint m_TextureID;
    bool m_IsWalkable;
    bool m_IsSwimmable; 
};

class Tilemap
{
protected:
    ivec2 m_MapSize;
    vec2 m_TileSize;

    Mesh* m_pMesh;
    Mesh* m_pBuildingMesh;
    fw::ShaderProgram* m_pShader;
    fw::ShaderProgram* m_pBuildingShader;

    TileType* m_Layout;
    TileProperties* m_Props;

public:
    Tilemap(char* filename);
    virtual ~Tilemap();

    void Draw(Camera* pCamera);
    bool IsTileWalkable(vec2 worldPos);
    bool IsTileSwimmable(vec2 worldPos); 
};