#include <cassert>
#include <iostream>
#include "Player.h"
#include "Bullet.h"

Player::Player(CMPUT350::Point2D loc)
{
    this->center = loc;
}

void Player::Initialize(CMPUT350::GameContext* context) {
    int side_rect_width = width / 4;
    int side_rect_height = height / 5;
    int top_rect_width = width / 5;
    int top_rect_height = (height / 2 + (height / 5)) / 2;
    
    int body_width = width / 2.5;
    int body_height = height; 

    // location calcs
    float side_rect_x_offset = (body_width / 2) + (side_rect_width / 2);
    float side_rect_y_offset = (height/2) - (2*side_rect_height);
    float top_rect_offset = 1.5*((body_width / 2) + (body_height * 0.005));

    this->body = CMPUT350::Rect(center, width / 2, height / 2);
    this->top_rect = CMPUT350::Rect({center.x, center.y - top_rect_offset}, top_rect_width, top_rect_height);
    this->left_rect = CMPUT350::Rect({center.x - side_rect_x_offset, center.y + side_rect_y_offset}, side_rect_width, side_rect_height);
    this->right_rect = CMPUT350::Rect({center.x + side_rect_x_offset, center.y + side_rect_y_offset}, side_rect_width, side_rect_height);
}

void Player::Update(CMPUT350::GameContext* context)
{
}

void Player::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key) { 
    if (key == 'a') {
        this->body.topLeft.x -= 1;
        this->right_rect.topLeft.x -= 1;
        this->left_rect.topLeft.x -= 1;
        this->top_rect.topLeft.x -= 1;
        return true;
    } else if (key == 'd') {
        this->body.topLeft.x += 1;
        this->right_rect.topLeft.x += 1;
        this->left_rect.topLeft.x += 1;
        this->top_rect.topLeft.x += 1;
        return true;
    } else if (key == ' ') {
        std::cout << "bullet shot placeholder" << std::endl;
        return true;
    }
    return false; 
}

void Player::RenderBackground(CMPUT350::GameContext* context) {
    context->ScreenContext->DrawRect(this->body, CMPUT350::Colors::white);
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawRect(this->top_rect, CMPUT350::Colors::red);
    context->ScreenContext->DrawRect(this->left_rect, CMPUT350::Colors::red);
    context->ScreenContext->DrawRect(this->right_rect, CMPUT350::Colors::red);
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
    //static CMPUT350::Rect sBounds(0, 0, 0, 0);
    CMPUT350::Rect sBounds = this->body |= this->top_rect;
    sBounds |= this->left_rect;
    sBounds |= this->right_rect;
    return sBounds;
}
