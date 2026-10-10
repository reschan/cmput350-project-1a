#include "Enemy.h"
#include "Enemy2.h"
#include "Bullet.h"
#include "Bezier.h"

Enemy2::Enemy2(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path)
    : Enemy(loc, path), bullets(2) {
    health = 1;
}

bool Enemy2::Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) { 
    // formation = false;
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

void Enemy2::RenderBackground(CMPUT350::GameContext* context) {
    //context->ScreenContext->FrameRect(bounds, 5, CMPUT350::Colors::blue);
    context->ScreenContext->DrawRect({topLeft, this->width, this->height}, CMPUT350::Colors::cyan);
}

void Enemy2::RenderForeground(CMPUT350::GameContext* context) { 
    context->ScreenContext->DrawCircle(
        {topLeft.x + (width / 2) + (width / 4), topLeft.y + (height / 2) + (height / 4)}, 3,
        CMPUT350::Colors::black);
    context->ScreenContext->DrawCircle(
        {topLeft.x + (width / 2) - (width / 4), topLeft.y + (height / 2) + (height / 4)}, 3,
        CMPUT350::Colors::black);
}

void Enemy2::LateUpdate(CMPUT350::GameContext* context) {
    if (health == 0) {
        context->mNotificationManager->Notify("Enemy2Killed");
        for (const auto& bullet : trackingBullet) {
            auto ptr = bullet.lock();
            if (ptr != nullptr) {
                ptr->Kill();
            }
        }
        Kill();
    }
    if (context->currentFrame - lastFiredFrame >= 30) {
        shootReady = true;
    }
    if (curveProgress < 1) {
        center = pathCurve->GetPoint(curveProgress);
        curveProgress += 0.01f;
    }
}

