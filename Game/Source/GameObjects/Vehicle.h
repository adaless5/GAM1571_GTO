#pragma once

#include "GameObject.h"

class Mesh;
class PlayerController;
class Tilemap;

class Vehicle : public GameObject
{
	const float PLAYER_SPEED_FORWARD = 60.0f; // Units per second
	const float PLAYER_SPEED_REVERSE = 30.0f;  // Units per second
	const float PLAYER_TURNING_SPEED = 180.0f; // Degrees per second

protected: 
    Tilemap* m_pTilemap;
    PlayerController* m_pController;
    int m_PlayerNumber;
	float m_Speed; 
	float m_TurningSpeed; 
    bool m_IsActive = false; 
	Mesh* m_pMesh = nullptr;

public:
    Vehicle(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController);
    ~Vehicle(); 

    virtual void Update(float deltaTime) override; 
    bool FitsOnTilemap(vec2 newPos);
    fw::vec2 GetPosition();
	float GetAngle() { return m_Angle;  }
    bool GetIsActive(); 
    void SetIsActive(bool active);
	//fw::vec2 GetPosition() {return m_Position;}

	void SetSpeed(float speed) { m_Speed = speed; }
	void SetTurningSpeed(float speed) { m_TurningSpeed = speed; }
};