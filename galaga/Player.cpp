#include <cassert>
#include <iostream>
#include "Player.h"
#include "Bullet.h"

Player::Player(CMPUT350::Point2D loc)
{
    this->center = loc;
}

void Player::Initialize(CMPUT350::GameContext* context)
{ 
    this->side_rect_width = width / 4; 
    this->side_rect_height = height / 10;
    this->top_rect_width = width / 5;  
    this->top_rect_height = (height / 2 + (height / 5)) / 2; 
    
    this->body_width = width / 2.5; //2.6
    this->body_height = height; //1.3

    // location calcs
    this->side_rect_x_offset = (this->body_width / 2) + (this->side_rect_width / 2);
    this->side_rect_y_offset = (height/2) - (3.5*this->side_rect_height);
    this->top_rect_offset = 1.5*((this->body_width / 2) + (this->body_height * 0.005));
}

void Player::Update(CMPUT350::GameContext* context)
{
}

void Player::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return true; }

void Player::RenderBackground(CMPUT350::GameContext* context) {
    context->ScreenContext->DrawRect({center, width/2, height/2}, CMPUT350::Colors::white);
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawRect({{center.x, center.y - top_rect_offset}, top_rect_width, top_rect_height}, CMPUT350::Colors::red);
    context->ScreenContext->DrawRect({{center.x - side_rect_x_offset, center.y + side_rect_y_offset}, side_rect_width, side_rect_height}, CMPUT350::Colors::red);
    context->ScreenContext->DrawRect({{center.x + side_rect_x_offset, center.y + side_rect_y_offset}, side_rect_width, side_rect_height}, CMPUT350::Colors::red);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
}

void Player::Kill()
{
}

bool Player::IsAlive() const
{
    // TODO: Update code
    return true;
}

const CMPUT350::Rect& Player::GetBounds()
{
    // TODO: Update code
    static CMPUT350::Rect sBounds(0, 0, 0, 0);
    return sBounds;
}
