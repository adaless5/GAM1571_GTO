#ifndef __GameObject_H__
#define __GameObject_H__

class Game;
class Mesh;
class Camera; 

class GameObject
{
protected:
    Game* m_pGame;
    Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    GLuint m_TextureID;
    fw::vec2 m_Position;
    float m_Radius;

public:
    GameObject(Game* pGame, Mesh* pMesh, fw::ShaderProgram* pShader, GLuint textureID, fw::vec2 position);
    ~GameObject();

    fw::vec2 GetPosition() { return m_Position; }
    float GetRadius() { return m_Radius; }
    fw::AABB GetWorldAABB();

    void SetPosition(fw::vec2 pos) { m_Position = pos; }

    virtual void Update(float deltaTime);
    virtual void Draw(Camera* pCamera);

    virtual bool IsColliding(GameObject* pOtherGameObject);
    virtual void OnCollision(GameObject* pOtherGameObject);
};

#endif //__GameObject_H__
