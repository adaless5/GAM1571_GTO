#ifndef __Camera_H__
#define __Camera_H__

#include "GameObject.h"

class Game;
class Player; 

class Camera : public GameObject
{
protected:
    fw::vec2 m_ProjectionScale;
    Player* m_pPlayer; 

public:
    Camera(Game* pGame, Player* pPlayer, fw::vec2 position, fw::vec2 projectionScale);
    ~Camera();

    virtual void Update(float deltaTime) override;

    fw::vec2 GetProjectionScale() { return m_ProjectionScale; }
};

#endif //__Camera_H__
