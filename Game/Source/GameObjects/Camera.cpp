#include "GamePCH.h"

#include "Base/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Player.h"
#include "Vehicle.h"
#include "Game.h"

using namespace fw;

Camera::Camera(Game* pGame, Player* pPlayer, Vehicle* pVehicle, fw::vec2 position, fw::vec2 projectionScale)
: GameObject( pGame, nullptr, nullptr, 0, position )
, m_ProjectionScale( projectionScale )
{
    m_pPlayer = pPlayer; 
	m_pVehicle = pVehicle;
}

Camera::~Camera()
{

}

void Camera::Update(float deltaTime)
{
    ImGui::Begin( "Camera Stuff" );
    ImGui::Text( "Position (%f, %f)", m_Position.x, m_Position.y );
    ImGui::DragFloat2( "Pos", &m_Position.x );
    ImGui::End();

    m_Position = m_pPlayer->GetPosition();

	float angle = (m_pVehicle->GetAngle() + 90) * M_PI / 180; 

    if (m_pPlayer->IsInCar() == true)
    {
		m_Position = m_pVehicle->GetPosition() + fw::vec2(10 * cos(angle), 10 * sin(angle));
        m_ProjectionScale = fw::vec2(1 / 50.0f, 1 / 50.0f); 
    }
    else if (m_pPlayer->IsInCar() == false)
    {
        m_ProjectionScale = fw::vec2(1 / 30.0f, 1 / 30.0f);
    }
}
