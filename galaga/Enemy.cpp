#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(CMPUT350::Point2D loc) { 
    this->center = loc; 
}

void Enemy::Initialize(CMPUT350::GameContext* context) {
    this->width = 40;
    this->height = 40;
    this->isAlive = true;
}

void Enemy::Update(CMPUT350::GameContext* context)
{

}

void Enemy::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Enemy::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return false; } //enemy shouldn't need to respond to keyevent

// leaving empty because enemies won't ever need to be in the background?
void Enemy::RenderBackground(CMPUT350::GameContext* context) {}

void Enemy::RenderForeground(CMPUT350::GameContext* context)
{ context->ScreenContext->DrawRect({this->center, this->width, this->height}, CMPUT350::Colors::magenta);  // enemy magenta for now? 
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    // handling enemy bullet collision only? 
    if (bullet != nullptr) {
        if (bullet->IsPlayerBullet()) {
            
        }
    }
}

void Enemy::Kill()
{
}

bool Enemy::IsAlive() const
{
    // TODO: Update code
    return isAlive;
}

const CMPUT350::Rect& Enemy::GetBounds()
{
    // TODO: Update code
    static CMPUT350::Rect sBounds(0, 0, 0, 0);
    return sBounds;
}
