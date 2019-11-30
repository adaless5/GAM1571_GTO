#ifndef __Player_H__
#define __Player_H__

#include "GameObject.h"

class Mesh;
class PlayerController;
class Tilemap;
class Vehicle; 

class Player : public GameObject
{
protected:
    Tilemap* m_pTilemap;
    PlayerController* m_pController;
    int m_PlayerNumber;
    Vehicle* m_pVehicle; 
    bool m_InCar = false;
    float m_CarActivationDistance = 0.0f; 

public:
    Player(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController, Vehicle* pVehicle);
    ~Player();

    virtual void Update(float deltaTime) override;
    bool FitsOnTilemap(vec2 newPos);
    fw::vec2 GetPosition(); 
    bool IsInCar(); 
};

#endif //__Player_H__
