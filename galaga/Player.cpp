#include <cassert>
#include <iostream>
#include "Player.h"
#include "Bullet.h"

Player::Player(CMPUT350::Point2D loc) : isAlive(true), center(loc), bullets(2), speed(5) {
    this->topLeft = CMPUT350::Point2D(loc.x - (width / 2), loc.y - (height/2));

}

void Player::Initialize(CMPUT350::GameContext* context) {    
    int side_rect_width = width / 4;
    int side_rect_height = height / 5;
    int top_rect_width = width / 5;
    int top_rect_height = (height / 2 + (height / 5)) / 2;
    
    int body_width = width / 2;
    //std::cout << side_rect_width << std::endl;
    int body_height = height / 2; 

    // location calcs
    float side_rect_x_offset = (body_width / 2) + (side_rect_width / 2) - (side_rect_width / 5);
    float tl_center_adjustment = (side_rect_width) + (side_rect_width / 2);
    float side_rect_y_offset = (height/2) - (2*side_rect_height) + (side_rect_height / 2) + (side_rect_height / 4);
    float top_rect_x_offset = (body_width - top_rect_width)/2 + (top_rect_width) + (top_rect_width / 4) ;
    float top_rect_y_offset = 1.5*((body_width / 2) + (body_height * 0.005)) - (top_rect_height/4);
    float body_x_offset = body_width / 2;

    body = CMPUT350::Rect({this->topLeft.x + body_x_offset, this->topLeft.y}, body_width, body_height);
    selfShapes.push_back(body);
    topRect = CMPUT350::Rect({this->topLeft.x + top_rect_x_offset, this->topLeft.y - top_rect_y_offset}, top_rect_width, top_rect_height);
    selfShapes.push_back(body);
    leftRect = CMPUT350::Rect({this->topLeft.x - side_rect_x_offset + tl_center_adjustment, this->topLeft.y + side_rect_y_offset}, side_rect_width, side_rect_height);
    selfShapes.push_back(leftRect);
    rightRect = CMPUT350::Rect({this->topLeft.x + side_rect_x_offset + tl_center_adjustment, this->topLeft.y + side_rect_y_offset}, side_rect_width, side_rect_height);
    selfShapes.push_back(rightRect);
}

void Player::Update(CMPUT350::GameContext* context) { 
    GetBounds();
    for (int i = 0; i < trackingBullet.size(); i++) {
        if (trackingBullet[i].expired()) {
            trackingBullet.erase(trackingBullet.begin() + i);
        }
    }
}

void Player::LateUpdate(CMPUT350::GameContext* context)
{
}

bool Player::HandleKeyEvent(CMPUT350::GameContext* context, char key) { // nuke later
    if (key == 'a') {
        this->body.topLeft.x -= speed;
        this->rightRect.topLeft.x -= speed;
        this->leftRect.topLeft.x -= speed;
        this->topRect.topLeft.x -= speed;
        this->center.x -= speed;
        return true;
    } else if (key == 'd') {
        this->body.topLeft.x += speed;
        this->rightRect.topLeft.x += speed;
        this->leftRect.topLeft.x += speed;
        this->topRect.topLeft.x += speed;
        this->center.x += speed;
        return true;
    } else if (key == ' ') {
        if (trackingBullet.size() < bullets) {
            auto bullet = std::make_shared<Bullet>(center, center, true);
            context->mEngineView->AddGameObject(bullet);
            std::weak_ptr<Bullet> t_bullet = bullet;
            trackingBullet.push_back(bullet);
            return true;
        }
    }
    return false; 
}

void Player::RenderBackground(CMPUT350::GameContext* context) {
    //context->ScreenContext->FrameRect(this->bounds, 5, CMPUT350::Colors::blue);
    context->ScreenContext->DrawRect(this->body, CMPUT350::Colors::white);
}

void Player::RenderForeground(CMPUT350::GameContext* context)
{
    context->ScreenContext->DrawRect(this->topRect, CMPUT350::Colors::red);
    context->ScreenContext->DrawRect(this->leftRect, CMPUT350::Colors::red);
    context->ScreenContext->DrawRect(this->rightRect, CMPUT350::Colors::red);
}

void Player::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj)
{
}

void Player::Kill() { this->isAlive = false; }

bool Player::IsAlive() const
{
    return isAlive;
}

void Player::ReceiveNotification(const std::string& key) {
    // TODO: write uwu
    std::cout << "Player: notification received: " << key;
    if (key == "MoveLeft") {
        std::cout << "Player: MoveLeft\n";
        this->body.topLeft.x -= speed;
        this->rightRect.topLeft.x -= speed;
        this->leftRect.topLeft.x -= speed;
        this->topRect.topLeft.x -= speed;
        this->center.x -= speed;
    } else if (key == "MoveRight") {
        std::cout << "Player: MoveRight\n";
        this->body.topLeft.x += speed;
        this->rightRect.topLeft.x += speed;
        this->leftRect.topLeft.x += speed;
        this->topRect.topLeft.x += speed;
        this->center.x += speed;
    }// else if (key == "Shoot") {
     //   if (trackingBullet.size() < bullets) {
     //       auto bullet = std::make_shared<Bullet>(center, center, true);
     //       context->mEngineView->AddGameObject(bullet);
     //       std::weak_ptr<Bullet> t_bullet = bullet;
     //       trackingBullet.push_back(bullet);
     //       return true;
     //   }
    //}
}

CMPUT350::Point2D Player::GetLocation() const {
    // TODO: write uwu
    return {0, 0};
}

float Player::GetRotation() const {
    // TODO: write uwu
    return 0;
}

const CMPUT350::Rect& Player::GetBounds()
{
    this->bounds = CMPUT350::Rect({0, 0}, 0, 0);
    this->bounds |= this->body;
    this->bounds |= this->topRect;
    this->bounds |= this->leftRect;
    this->bounds |= this->rightRect;
    // std::cout << this->bounds << std::endl;
    return this->bounds; // saving in class in case needed for drawing 
}

const std::vector<CMPUT350::Shape>& Player::GetShapes() { return selfShapes; }
