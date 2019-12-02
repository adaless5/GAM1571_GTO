#include "GamePCH.h"

#include "Vehicle.h"
#include "Tilemap/Tilemap.h"
#include "PlayerController.h"
#include "Base/Mesh.h"
#include "Camera.h"

Vehicle::Vehicle(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController)
    : GameObject(pGame, pMesh, pShader, textureID, position)
    , m_PlayerNumber(playerNum)
    , m_pTilemap(pTilemap)
    , m_pController(pController)
{
	m_pMesh = pMesh; 
}

Vehicle::~Vehicle()
{

}

void Vehicle::Update(float deltaTime)
{
   /* if (m_pController->m_Interact)
    {
        m_IsActive = true; 
    }
    else if (!m_pController->m_Interact)
    {
        m_IsActive = false;
    }*/
	SetSpeed(0);
	SetTurningSpeed(0);

	if (m_pTilemap->IsTileSwimmable(m_Position) == true)
	{
		SetSpeed(0);
		SetTurningSpeed(0);
		m_IsActive = false; 
	}


    if (m_IsActive)
    {
        //float speed = 100;
		

        
        //vec2 dir(0, 0);

        if (m_pController->m_Up)
            //dir.y = 1;
			SetSpeed(PLAYER_SPEED_FORWARD);
        if (m_pController->m_Down)
            //dir.y = -1;
			SetSpeed(-PLAYER_SPEED_REVERSE);
		if (m_pController->m_Left)
			//dir.x = -1;
			SetTurningSpeed(PLAYER_TURNING_SPEED);
		if (m_pController->m_Right)
			//dir.x = 1;
			SetTurningSpeed(-PLAYER_TURNING_SPEED); 

		m_Angle += m_TurningSpeed * deltaTime;
		float angleradian = (m_Angle + 90.0f) * M_PI / 180.0f; 
		vec2 dir(cosf(angleradian), sinf(angleradian));
		
		//m_Position += dir * m_Speed * deltaTime;

        // X check.
        vec2 newPosition = m_Position + vec2(dir.x, 0) * m_Speed * deltaTime;
        if (FitsOnTilemap(newPosition))
            m_Position = newPosition;

        // Y check.
        newPosition = m_Position + vec2(0, dir.y) * m_Speed * deltaTime;
        if (FitsOnTilemap(newPosition))
            m_Position = newPosition;

		
		

        ImGui::Begin("Player Stuff");
        ImGui::Text("Hello");
        ImGui::Text("Position (%f, %f)", m_Position.x, m_Position.y);
        ImGui::DragFloat("X", &m_Position.x);
        ImGui::DragFloat("Y", &m_Position.y);
        ImGui::End();
    }
}

bool Vehicle::FitsOnTilemap(vec2 newPos)
{
    if (m_pTilemap->IsTileWalkable(vec2(newPos.x - 2.0f, newPos.y - 4.0f)) == false) return false;
    if (m_pTilemap->IsTileWalkable(vec2(newPos.x - 2.0f, newPos.y + 4.0f)) == false) return false;
    if (m_pTilemap->IsTileWalkable(vec2(newPos.x + 2.0f, newPos.y + 4.0f)) == false) return false;
    if (m_pTilemap->IsTileWalkable(vec2(newPos.x + 2.0f, newPos.y - 4.0f)) == false) return false;
    return true;
}

fw::vec2 Vehicle::GetPosition()
{
    return m_Position;
}

bool Vehicle::GetIsActive()
{
    return m_IsActive;
}

void Vehicle::SetIsActive(bool active)
{
    m_IsActive = active; 
}
