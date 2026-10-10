#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <math.h>
#include <numbers>

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player) : isAlive(true), globalLocation(location), heading(heading), player(player), length(20.0f), width(3.0f), location(0, 0) {}

bool Bullet::IsPlayerBullet() const
{
    return player;
}

void Bullet::Initialize(CMPUT350::GameContext* context) {
    if (IsPlayerBullet()) {
        velocity = 25.0f;
    } else {
        velocity = 20.0f;
    }
    if (heading.x == 0 && heading.y == 0) {
        heading = CMPUT350::Point2D(0, -1);
    }
    heading.Normalize();
    rotation = std::atan2(heading.y, heading.x) + std::numbers::pi / 2.0f;
    bulletBody.p1 = location;
    bulletBody.p2 = CMPUT350::Point2D(location.x, -length);
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
    //context->ScreenContext->FrameRect(this->bounds, 5, CMPUT350::Colors::blue);
    if (IsPlayerBullet()) {
        context->ScreenContext->DrawLine(bulletBody.p1, bulletBody.p2, width, CMPUT350::Colors::grey);  
    } else {
        context->ScreenContext->DrawLine(bulletBody.p1, bulletBody.p2, width, CMPUT350::Colors::red);
    }
    selfShapes.push_back(bulletBody);
}

void Bullet::RenderForeground(CMPUT350::GameContext* context) {
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) {
    auto enemy = std::dynamic_pointer_cast<Enemy>(obj);
    if (enemy != nullptr && player) { //enemy collision from player bullet
        //std::cout << "globalLocation: " << globalLocation << std::endl;
        //std::cout << "bulletBody.p1: " << bulletBody.p1 << std::endl;
        //std::cout << "bulletBody.p2: " << bulletBody.p2 << std::endl;
        Kill();
    }
    auto player = std::dynamic_pointer_cast<Player>(obj);
    if (player != nullptr && !(this->player)) { // player collision from enemy bullet
        //std::cout << "globalLocation: " << globalLocation << std::endl;
        //std::cout << "bulletBody.p1: " << bulletBody.p1 << std::endl;
        //std::cout << "bulletBody.p2: " << bulletBody.p2 << std::endl;
        Kill();
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

float Bullet::GetRotation() const { return rotation; }

const CMPUT350::Rect& Bullet::GetBounds()
{
    bounds = CMPUT350::Rect({0, 0}, 0, 0);
    bounds |= bulletBody.p1;
    bounds |= bulletBody.p2;
    bounds.width = width;
    bounds.height = length;
    bounds.topLeft.x = bounds.topLeft.x - (width / 2);
    return bounds;
}

const std::vector<CMPUT350::Shape>& Bullet::GetShapes() { return selfShapes; }
