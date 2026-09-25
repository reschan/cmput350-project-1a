#include "Enemy.h"
#include "Bullet.h"

Enemy::Enemy(CMPUT350::Point2D loc) { 
    this->center = loc; 
}

void Enemy::Initialize(CMPUT350::GameContext* context) {
    this->width = 40;
    this->height = 40;
    this->topLeft = CMPUT350::Point2D(this->center.x - (width / 2), this->center.y - (height / 2));
    this->isAlive = true;
    this->body = CMPUT350::Rect(this->topLeft, this->width, this->height);
}

void Enemy::Update(CMPUT350::GameContext* context)
{ GetBounds(); }

void Enemy::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Enemy::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return false; } //enemy shouldn't need to respond to keyevent

void Enemy::RenderBackground(CMPUT350::GameContext* context) {
    //context->ScreenContext->FrameRect(this->bounds, 5, CMPUT350::Colors::blue);
}

void Enemy::RenderForeground(CMPUT350::GameContext* context)
{ context->ScreenContext->DrawRect({this->topLeft, this->width, this->height}, CMPUT350::Colors::magenta);  // enemy magenta for now? 
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    // handling enemy bullet collision only? 
    if (bullet != nullptr) {
        if (bullet->IsPlayerBullet()) {
            CMPUT350::Rect intersection = bounds;
            intersection &= bullet->GetBounds();
            //std::cout << intersection << std::endl;
            if (!(intersection.width <= 0 || intersection.height <= 0)) {
                //std::cout << "triggered" << std::endl;
                bullet->Kill();
            }
        }
    }
}

void Enemy::Kill()
{ isAlive = false; }

bool Enemy::IsAlive() const
{
    // TODO: Update code
    return isAlive;
}

const CMPUT350::Rect& Enemy::GetBounds()
{
    // TODO: Update code
    this->bounds = CMPUT350::Rect({0, 0}, 0, 0);
    this->bounds |= this->body;
    return this->bounds;
}
