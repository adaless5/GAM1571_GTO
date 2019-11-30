#include "GamePCH.h"

#include "Vehicle.h"
#include "Tilemap/Tilemap.h"
#include "PlayerController.h"

Vehicle::Vehicle(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController)
    : GameObject(pGame, pMesh, pShader, textureID, position)
    , m_PlayerNumber(playerNum)
    , m_pTilemap(pTilemap)
    , m_pController(pController)
{

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

    if (m_IsActive)
    {
        float speed = 100;
        if (m_pTilemap->IsTileSwimmable(m_Position) == true)
        {
            speed = 10;
        }

        vec2 dir(0, 0);

        if (m_pController->m_Up)
            dir.y = 1;
        if (m_pController->m_Down)
            dir.y = -1;
        if (m_pController->m_Left)
            dir.x = -1;
        if (m_pController->m_Right)
            dir.x = 1;

        // X check.
        vec2 newPosition = m_Position + vec2(dir.x, 0) * speed * deltaTime;
        if (FitsOnTilemap(newPosition))
            m_Position = newPosition;

        // Y check.
        newPosition = m_Position + vec2(0, dir.y) * speed * deltaTime;
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
