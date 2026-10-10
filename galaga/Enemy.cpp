#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

Enemy::Enemy(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path)
    : width(40), height(25), isAlive(true), path(path), movementRange(30) {}

void Enemy::Initialize(CMPUT350::GameContext* context) {
    pathCurve.reset(new CMPUT350::Bezier(path));
    center = pathCurve->GetPoint(curveProgress);
    topLeft = CMPUT350::Point2D(0 - (width / 2), 0 - (height / 2));
    body = CMPUT350::Rect(topLeft, width, height);
    selfShapes.push_back(body);
}

void Enemy::Update(CMPUT350::GameContext* context) { 
    GetBounds(); 
    if (curveProgress >= 1 && formation) {
        if (!hoverStarted) {
            originalCenter = center;
            hoverStarted = true;
        }
        center.x = originalCenter.x + std::sin(context->currentFrame * 0.05) * movementRange * hoverProgress;
        if (hoverProgress < 1) {
            hoverProgress += 0.02f;
        }
    }
}

// bool Enemy::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return false; } //enemy shouldn't need to respond to keyevent

void Enemy::RenderBackground(CMPUT350::GameContext* context) {
    // context->ScreenContext->FrameRect(bounds, 5, CMPUT350::Colors::blue);
}

void Enemy::RenderForeground(CMPUT350::GameContext* context)
{ context->ScreenContext->DrawRect({this->topLeft, this->width, this->height}, CMPUT350::Colors::magenta);  // enemy magenta for now? 
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet != nullptr) {
        if (bullet->IsPlayerBullet()) {
            health -= 1;
            return;
        }
    }
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(obj);
    if (player != nullptr) {
        health -= 1;
        return;
    }
}

void Enemy::Kill()
{ isAlive = false; }

bool Enemy::IsAlive() const
{
    return isAlive;
}

void Enemy::ReceiveNotification(const std::string& key) {
}

CMPUT350::Point2D Enemy::GetLocation() const { return center; }

float Enemy::GetRotation() const { return rotation; }

const CMPUT350::Rect& Enemy::GetBounds()
{
    bounds = CMPUT350::Rect({0, 0}, 0, 0);
    bounds |= body;
    return bounds;
}

const std::vector<CMPUT350::Shape>& Enemy::GetShapes() { return selfShapes; }