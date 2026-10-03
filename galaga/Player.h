#ifndef PLAYER_H
#define PLAYER_H

#include "CollisionObject.h"
#include "Bullet.h"

class Player : public CMPUT350::CollisionObject, std::enable_shared_from_this<Player> {
public:
    Player(CMPUT350::Point2D loc);

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool HandleKeyEvent(CMPUT350::GameContext* context, char key) override; // nuke later
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

private:
    CMPUT350::Point2D center;
    CMPUT350::Point2D topLeft;
    CMPUT350::Rect body;
    CMPUT350::Rect topRect;
    CMPUT350::Rect leftRect;
    CMPUT350::Rect rightRect;
    CMPUT350::Rect bounds;
    int width = 40;
    int height = 40;
    int speed;

    std::vector<std::weak_ptr<Bullet>> trackingBullet;
    int bullets;
    bool flag_shoot = false;

    bool isAlive;
    std::vector<CMPUT350::Shape> selfShapes;
    float rotation = 0;
};

#endif
