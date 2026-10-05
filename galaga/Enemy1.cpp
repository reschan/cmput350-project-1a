#include "Enemy.h"
#include "Enemy1.h"
#include "Bullet.h"

void Enemy1::Initialize(CMPUT350::GameContext* context) {
    width = 40;
    height = 25;
    topLeft = CMPUT350::Point2D(this->center.x - (width / 2), this->center.y - (height / 2));
    isAlive = true;
    body = CMPUT350::Rect(this->topLeft, this->width, this->height);
    selfShapes.push_back(body);
    health = 2;
    
}

void Enemy1::LateUpdate(CMPUT350::GameContext* context) {
    if (health == 0) {
        Kill();
    }
}

bool Enemy1::Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) { return true; }

void Enemy1::RenderBackground(CMPUT350::GameContext* context) {
    //context->ScreenContext->FrameRect(bounds, 5, CMPUT350::Colors::blue);
}

void Enemy1::RenderForeground(CMPUT350::GameContext* context) {
    if (health == 2) {
        context->ScreenContext->DrawRect({this->topLeft, this->width, this->height},
                                         CMPUT350::Colors::green);
    } else {
        context->ScreenContext->DrawRect({this->topLeft, this->width, this->height},
                                         CMPUT350::Colors::magenta);
    }
    
}

const CMPUT350::Rect& Enemy1::GetBounds() {
    this->bounds = CMPUT350::Rect({0, 0}, 0, 0);
    this->bounds |= this->body;
    return this->bounds;
}

void Enemy1::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) {
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet != nullptr) {
        if (bullet->IsPlayerBullet()) {
            health -= 1;
        }
    } 
}

