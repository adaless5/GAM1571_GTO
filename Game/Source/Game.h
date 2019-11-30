#ifndef __Game_H__
#define __Game_H__

class Ball;
class Camera;
class GameObject;
class ImGuiManager;
class Mesh;
class Player;
class Vehicle; 
class PlayerController;
class Tilemap;

class Game : public fw::GameCore
{
protected:
    fw::ImGuiManager* m_pImGuiManager;

    fw::ShaderProgram* m_pShaderColor;
    fw::ShaderProgram* m_pShaderTexture;
    Mesh* m_pMeshTriangle;
    Mesh* m_pMeshCircle;
    Mesh* m_pMeshVehicle; 
    GLuint m_TextureBall;
    GLuint m_TextureCar;

    Tilemap* m_pTilemap;

    Player* m_pPlayer;
    Vehicle* m_pVehicle; 
    Camera* m_pCamera;
    Ball* m_pBall;

    PlayerController* m_pController;

public:
    Game(fw::Framework* pFramework);
    virtual ~Game();

    virtual void Init() override;
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void CheckForCollisions();
};

#endif //__Game_H__
