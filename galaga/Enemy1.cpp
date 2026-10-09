#include "Enemy.h"
#include "Enemy1.h"
#include "Bullet.h"
#include "Bezier.h"

Enemy1::Enemy1(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path)
    : Enemy(loc, path), bullets(4), score(100) {
    health = 2;
}

/* void Enemy1::Initialize(CMPUT350::GameContext* context) {
    pathCurve.reset(new CMPUT350::Bezier(path));
    center = pathCurve->GetPoint(curveProgress);
    topLeft = CMPUT350::Point2D(0 - (width / 2), 0 - (height / 2));
    body = CMPUT350::Rect(topLeft, width, height);
    selfShapes.push_back(body);
} */

/* void Enemy1::LateUpdate(CMPUT350::GameContext* context) {
    if (health == 0) {
        Kill();
    }
    if (context->currentFrame - lastFiredFrame >= 60) {
        trackingBullet.clear();
    }
    if (curveProgress < 1) {
        center = pathCurve->GetPoint(curveProgress);
        //rotation = std::atan(pathCurve->GetSlope(curveProgress).y /
        //                     pathCurve->GetSlope(curveProgress).x);
        curveProgress += 0.01f;
    }
} */

bool Enemy1::Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) { 
    if (trackingBullet.size() < bullets && curveProgress >= 1) {
        auto bullet = std::make_shared<Bullet>(
            center, CMPUT350::Point2D(target.x - center.x, target.y - center.y), false);
        context->mEngineView->AddGameObject(bullet);
        std::weak_ptr<Bullet> t_bullet = bullet;
        trackingBullet.push_back(bullet);
        lastFiredFrame = context->currentFrame;
        return true; 
    } else {
        return false;
    }
}

void Enemy1::RenderBackground(CMPUT350::GameContext* context) {
    context->ScreenContext->FrameRect(bounds, 5, CMPUT350::Colors::blue);
    if (health == 2) {
        context->ScreenContext->DrawRect({topLeft, this->width, this->height},
                                         CMPUT350::Colors::green);
    } else {
        context->ScreenContext->DrawRect({topLeft, this->width, this->height},
                                         CMPUT350::Colors::magenta);
    }
}

void Enemy1::RenderForeground(CMPUT350::GameContext* context) { 
    context->ScreenContext->DrawCircle(
        {topLeft.x + (width / 2) + (width / 4), topLeft.y + (height / 2) + (height / 4)}, 3,
        CMPUT350::Colors::black);
    context->ScreenContext->DrawCircle(
        {topLeft.x + (width / 2) - (width / 4), topLeft.y + (height / 2) + (height / 4)}, 3,
        CMPUT350::Colors::black);
}

static int GetScore() { return score; }

/* const CMPUT350::Rect& Enemy1::GetBounds() {
    this->bounds = CMPUT350::Rect({0, 0}, 0, 0);
    this->bounds |= this->body;
    return this->bounds;
} */

/* void Enemy1::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) {
    std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(obj);
    if (bullet != nullptr) {
        if (bullet->IsPlayerBullet()) {
            health -= 1;
        }
    } 
} */

// CMPUT350::Point2D Enemy1::GetLocation() const { return center; }

/* float Enemy1::GetRotation() const {
    return rotation;
} */

