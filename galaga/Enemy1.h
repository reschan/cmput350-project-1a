#include "Enemy.h"
#include "Bullet.h"
#include "Bezier.h"

class Enemy1 : public Enemy {
public:
    Enemy1(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path);
    // Enemy1(CMPUT350::Point2D loc) : Enemy(loc) { this->center = loc; }
    void Initialize(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) override;
    void RenderForeground(CMPUT350::GameContext* context) override;
    void RenderBackground(CMPUT350::GameContext* context) override;
    const CMPUT350::Rect& GetBounds() override;
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj);
    CMPUT350::Point2D GetLocation() const override;
    float GetRotation() const override;

private: 
    CMPUT350::Point2D center;
    CMPUT350::Rect bounds;
    CMPUT350::Point2D topLeft;
    int width;
    int height;
    bool isAlive;
    CMPUT350::Rect body;
    std::vector<CMPUT350::Shape> selfShapes;
    int health;
    std::vector<std::weak_ptr<Bullet>> trackingBullet;
    int bullets;
    int lastFiredFrame;
    std::vector<CMPUT350::Point2D> path;
    float curveProgress = 0;
    float rotation = 0;
    std::unique_ptr<CMPUT350::Bezier> pathCurve;
};
