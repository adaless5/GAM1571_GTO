#pragma once

#include "GameObject.h"

class Mesh;
class PlayerController;
class Tilemap;

class Vehicle : public GameObject
{
protected: 
    Tilemap* m_pTilemap;
    PlayerController* m_pController;
    int m_PlayerNumber;

    bool m_IsActive = false; 

public:
    Vehicle(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController);
    ~Vehicle(); 

    virtual void Update(float deltaTime) override;
    bool FitsOnTilemap(vec2 newPos);
    fw::vec2 GetPosition();
    bool GetIsActive(); 
    void SetIsActive(bool active);
};