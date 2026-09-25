#include "Bullet.h"
#include "Enemy.h"
#include <iostream>

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player) : location(location), heading(heading), player(player), length(20.0f), velocity(25.0f), width(3.0f) {}

bool Bullet::IsPlayerBullet()
{
    // TODO: Update
    return this->player;
}

void Bullet::Initialize(CMPUT350::GameContext* context)
{
}

void Bullet::Update(CMPUT350::GameContext* context) {
    GetBounds();
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
    //context->ScreenContext->FrameRect(this->bounds, 5, CMPUT350::Colors::blue);
    CMPUT350::Point2D to(location);
    // std::cout << to << std::endl;
    to.y -= length;
    context->ScreenContext->DrawLine(location, to, width, CMPUT350::Colors::grey); //move to render background so it looks like its coming out of ship
}

void Bullet::RenderForeground(CMPUT350::GameContext* context) {
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) {
    auto enemy = std::dynamic_pointer_cast<Enemy>(obj);
    if (enemy != nullptr) {
        CMPUT350::Rect intersection = bounds;
        intersection &= enemy->GetBounds();
        if (!(intersection.width <= 0 || intersection.height <= 0)) {
            enemy->Kill();
        }
    }
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
    this->bounds = CMPUT350::Rect({0, 0}, 0, 0);
    this->bounds |= location;
    this->bounds |= CMPUT350::Point2D(location.x - width/2, location.y - length);
    this->bounds.width = width;
    this->bounds.height = length;
    // std::cout << this->bounds << std::endl;
    return this->bounds;
}
