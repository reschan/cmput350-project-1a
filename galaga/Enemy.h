#ifndef ENEMY_H
#define ENEMY_H

#include "CollisionObject.h"
#include "GameContext.h"
#include "Bezier.h"
#include "Bullet.h"

class Enemy : public CMPUT350::CollisionObject
{
public:
    Enemy(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path);

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    // bool HandleKeyEvent(CMPUT350::GameContext* context, char key) override;
    bool IsAlive() const override;
    void Kill() override;
    void ReceiveNotification(const std::string& key) override;

    // Graphics Object Functions
    void RenderBackground(CMPUT350::GameContext* context) override;
    void RenderForeground(CMPUT350::GameContext* context) override;
    CMPUT350::Point2D GetLocation() const override;
    float GetRotation() const override;

    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;
    const std::vector<CMPUT350::Shape>& GetShapes() override;

    virtual bool Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) = 0;

protected:
    std::vector<std::weak_ptr<Bullet>> trackingBullet;
    CMPUT350::Point2D center;
    int lastFiredFrame;
    int health;
    CMPUT350::Point2D topLeft;
    int width;
    int height;
    float curveProgress = 0;
    CMPUT350::Rect bounds;

private: 
    bool isAlive;
    CMPUT350::Rect body;
    std::vector<CMPUT350::Shape> selfShapes;
    std::vector<CMPUT350::Point2D> path;
    std::unique_ptr<CMPUT350::Bezier> pathCurve;
    float rotation = 0;
};


#endif

