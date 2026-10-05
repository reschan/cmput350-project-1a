#include "Bullet.h"
#include "Enemy.h"
#include <iostream>
#include <math.h>

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player) : isAlive(true), globalLocation(location), heading(heading), player(player), length(20.0f), velocity(25.0f), width(3.0f), location(0, 0) {}

bool Bullet::IsPlayerBullet()
{
    // TODO: Update
    return player;
}

void Bullet::Initialize(CMPUT350::GameContext* context) {
    if (heading.x == 0 && heading.y == 0) {
        heading = CMPUT350::Point2D(0, -1);
    }
    heading.Normalize();
    bulletBody.p1 = location;
    bulletBody.p2 = location + (heading * length);
}

void Bullet::Update(CMPUT350::GameContext* context) {
    GetBounds();
    CMPUT350::Point2D movementVector = heading * velocity;
    //bulletBody.p1 += movementVector;
    //bulletBody.p2 += movementVector;
    globalLocation += movementVector;
    if (globalLocation.x < 0 || globalLocation.x > context->ScreenContext->GetWindowWidth() ||
        globalLocation.y < 0 || globalLocation.y > context->ScreenContext->GetWindowHeight()) {
        this->Kill();
        // std::cout << "kil\n";
    }
}

void Bullet::LateUpdate(CMPUT350::GameContext* context)
{
}

// bool Bullet::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return false; } //bullet shouldn't need to respond to keyevent

void Bullet::RenderBackground(CMPUT350::GameContext* context) 
{
    context->ScreenContext->FrameRect(this->bounds, 5, CMPUT350::Colors::blue);
    context->ScreenContext->DrawLine(bulletBody.p1, bulletBody.p2, width, CMPUT350::Colors::grey); //move to render background so it looks like its coming out of ship
    selfShapes.push_back(bulletBody);
}

void Bullet::RenderForeground(CMPUT350::GameContext* context) {
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) {
    auto enemy = std::dynamic_pointer_cast<Enemy>(obj);
    if (enemy != nullptr) {
<<<<<<< HEAD
        enemy->Kill();
=======
        CMPUT350::Rect intersection = this->bounds;
        intersection &= enemy->GetBounds();
        //std::cout << intersection << std::endl;
        if (!(intersection.width <= 0 || intersection.height <= 0)) {
            enemy->Kill();
        }
>>>>>>> c45e4ea22cf8125a74c04c4d3e3dbf66e8816f8b
    }
}

void Bullet::Kill()
{ isAlive = false; }

bool Bullet::IsAlive() const
{
    // TODO: Update code
    return isAlive;
}

void Bullet::ReceiveNotification(const std::string& key) {
    // TODO: write uwu
}

CMPUT350::Point2D Bullet::GetLocation() const {
    return globalLocation;
}

float Bullet::GetRotation() const {
    return 0; //rotation done in bulletBody.p2's calculation
}

const CMPUT350::Rect& Bullet::GetBounds()
{
    // TODO: Update code
    this->bounds = CMPUT350::Rect({0, 0}, 0, 0);
    this->bounds |= bulletBody.p1 + globalLocation;
    this->bounds |= bulletBody.p2 + globalLocation;
    this->bounds.width = width;
    this->bounds.height = length;
    bounds.topLeft.x = bounds.topLeft.x - (width / 2);
    // std::cout << this->bounds << std::endl;
    return this->bounds;
}

const std::vector<CMPUT350::Shape>& Bullet::GetShapes() { return selfShapes; }
