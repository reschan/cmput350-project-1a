#include "Enemy.h"
#include "Enemy1.h"
#include "Bullet.h"
#include "Bezier.h"

Enemy1::Enemy1(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path)
    : Enemy(loc, path), bullets(1) {
    health = 2;
}

bool Enemy1::Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) { 
    //formation = false;
    if (shootReady && curveProgress >= 1) {
        auto bullet = std::make_shared<Bullet>(
            center, CMPUT350::Point2D(target.x - center.x, target.y - center.y), false);
        context->mEngineView->AddGameObject(bullet);
        std::weak_ptr<Bullet> t_bullet = bullet;
        trackingBullet.push_back(t_bullet);
        lastFiredFrame = context->currentFrame;
        if (trackingBullet.size() >= bullets) {
            shootReady = false;
        }
        return true; 
    } else {
        return false;
    }
}

void Enemy1::RenderBackground(CMPUT350::GameContext* context) {
    //context->ScreenContext->FrameRect(bounds, 5, CMPUT350::Colors::blue);
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

void Enemy1::LateUpdate(CMPUT350::GameContext* context) {
    if (health == 0) {
        context->mNotificationManager->Notify("Enemy1Killed");
        for (const auto& bullet : trackingBullet) {
            auto ptr = bullet.lock();
            if (ptr != nullptr) {
                ptr->Kill();
            }
        }
        Kill();
    }
    if (context->currentFrame - lastFiredFrame >= 60) {
        shootReady = true;
    }
    if (curveProgress < 1) {
        center = pathCurve->GetPoint(curveProgress);
        curveProgress += 0.01f;
    }
}
