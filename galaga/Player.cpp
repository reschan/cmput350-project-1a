#include <cassert>
#include <iostream>
#include "Player.h"
#include "Bullet.h"

Player::Player(CMPUT350::Point2D loc) : center(loc) {
    this->topLeft = CMPUT350::Point2D(loc.x - (width / 2), loc.y - (height/2));

}

void Player::Initialize(CMPUT350::GameContext* context) {
    int side_rect_width = width / 4;
    int side_rect_height = height / 5;
    int top_rect_width = width / 5;
    int top_rect_height = (height / 2 + (height / 5)) / 2;
    
    int body_width = width / 2;
    std::cout << side_rect_width << std::endl;
    int body_height = height / 2; 

    // location calcs
    float side_rect_x_offset = (body_width / 2) + (side_rect_width / 2) - (side_rect_width / 5);
    float tl_center_adjustment = (side_rect_width) + (side_rect_width / 2);
    float side_rect_y_offset = (height/2) - (2*side_rect_height) + (side_rect_height / 2) + (side_rect_height / 4);
    float top_rect_x_offset = (body_width - top_rect_width)/2 + (top_rect_width) + (top_rect_width / 4) ;
    float top_rect_y_offset = 1.5*((body_width / 2) + (body_height * 0.005)) - (top_rect_height/4);
    float body_x_offset = body_width / 2;

    this->body = CMPUT350::Rect({this->topLeft.x + body_x_offset, this->topLeft.y}, body_width, body_height);
    this->top_rect = CMPUT350::Rect({this->topLeft.x + top_rect_x_offset, this->topLeft.y - top_rect_y_offset}, top_rect_width, top_rect_height);
    this->left_rect = CMPUT350::Rect({this->topLeft.x - side_rect_x_offset + tl_center_adjustment, this->topLeft.y + side_rect_y_offset}, side_rect_width, side_rect_height);
    this->right_rect = CMPUT350::Rect({this->topLeft.x + side_rect_x_offset + tl_center_adjustment, this->topLeft.y + side_rect_y_offset}, side_rect_width, side_rect_height);
}

void Player::Update(CMPUT350::GameContext* context) { GetBounds(); }

void Player::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key) { 
    if (key == 'a') {
        this->body.topLeft.x -= 1;
        this->right_rect.topLeft.x -= 1;
        this->left_rect.topLeft.x -= 1;
        this->top_rect.topLeft.x -= 1;
        this->center.x -= 1;
        return true;
    } else if (key == 'd') {
        this->body.topLeft.x += 1;
        this->right_rect.topLeft.x += 1;
        this->left_rect.topLeft.x += 1;
        this->top_rect.topLeft.x += 1;
        this->center.x += 1;
        return true;
    } else if (key == ' ') {
        if (tracking_bullet1.expired() || tracking_bullet2.expired()) {
            auto bullet = std::make_shared<Bullet>(center, center, true);
            context->mEngineView->AddGameObject(bullet);
            if (tracking_bullet1.expired()) {
                tracking_bullet1 = bullet;
            } else {
                tracking_bullet2 = bullet;
            }
            return true;
        }
    }
    return false; 
}

void Player::RenderBackground(CMPUT350::GameContext* context) {
    context->ScreenContext->FrameRect(this->bounds, 5, CMPUT350::Colors::blue);
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
    this->bounds = CMPUT350::Rect({0, 0}, 0, 0);
    this->bounds |= this->body;
    this->bounds |= this->top_rect;
    this->bounds |= this->left_rect;
    this->bounds |= this->right_rect;
    // std::cout << this->bounds << std::endl;
    return this->bounds; // saving in class in case needed for drawing 
}
