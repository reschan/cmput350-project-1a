#include "Bullet.h"
#include <iostream>

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player) : location(location), heading(heading), player(player), length(5.0f), velocity(5.0f) {}

bool Bullet::IsPlayerBullet()
{
    // TODO: Update
    return this->player;
}

void Bullet::Initialize(CMPUT350::GameContext* context)
{
}

void Bullet::Update(CMPUT350::GameContext* context) {
    if (this->player) {
        this->location.y -= this->velocity;
        if (location.x < 0 || location.x > context->ScreenContext->GetWindowWidth() ||
            location.y < 0 || location.y > context->ScreenContext->GetWindowHeight()) {
            this->Kill();
            std::cout << "kil\n"; 
        }
    }
}

void Bullet::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Bullet::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return false; } //bullet shouldn't need to respond to keyevent

void Bullet::RenderBackground(CMPUT350::GameContext* context)
{
}

void Bullet::RenderForeground(CMPUT350::GameContext* context) {
    CMPUT350::Point2D to(location);
    to.y -= length;
    context->ScreenContext->DrawLine(location, to, 3.0f, CMPUT350::Colors::white);
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
}

void Bullet::Kill()
{ isAlive = false; }

bool Bullet::IsAlive() const
{
    // TODO: Update code
    return isAlive;
}

const CMPUT350::Rect& Bullet::GetBounds()
{
    // TODO: Update code
    static CMPUT350::Rect sBounds(0, 0, 0, 0);
    return sBounds;
}
