#include "GamePCH.h"

#include "Game.h"
#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Tilemap/Tilemap.h"
#include "GameObjects/Vehicle.h"

using namespace fw;

Player::Player(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position, int playerNum, Tilemap* pTilemap, PlayerController* pController, Vehicle* pVehicle)
: GameObject( pGame, pMesh, pShader, textureID, position )
, m_PlayerNumber( playerNum )
, m_pTilemap( pTilemap )
, m_pController( pController )
{
    m_pVehicle = pVehicle; 
}
    
Player::~Player()
{

}

void Player::Update(float deltaTime)
{
    //GameObject::Update( deltaTime, pFramework );
    m_CarActivationDistance = sqrtf((m_pVehicle->GetPosition().x - m_Position.x) * (m_pVehicle->GetPosition().x - m_Position.x) + (m_pVehicle->GetPosition().y - m_Position.y) * (m_pVehicle->GetPosition().y - m_Position.y));

    if (m_CarActivationDistance < 10.0f)
    {
        if (m_pController->m_Interact)
        {
            m_pVehicle->SetIsActive(true); 
            m_Position = m_pVehicle->GetPosition();
            m_InCar = true; 
        }
        if (!m_pController->m_Interact)
        {
            m_pVehicle->SetIsActive(false);
            m_InCar = false; 
        }
    }
    else
    {
        m_pController->m_Interact = false; 
        m_InCar = false; 
    }

    

    float speed = 30;
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

bool Player::FitsOnTilemap(vec2 newPos)
{
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x-2.0f, newPos.y-4.0f ) ) == false ) return false;
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x-2.0f, newPos.y+4.0f ) ) == false ) return false;
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x+2.0f, newPos.y+4.0f ) ) == false ) return false;
    if( m_pTilemap->IsTileWalkable( vec2( newPos.x+2.0f, newPos.y-4.0f ) ) == false ) return false;
    return true;
}

fw::vec2 Player::GetPosition()
{
    return m_Position;
}

bool Player::IsInCar()
{
    return m_InCar;
}
