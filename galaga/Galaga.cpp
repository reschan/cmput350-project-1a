#include "Galaga.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy1.h"
#include "Stars.h"
#include "Keyboard.h"

Galaga::Galaga() : isAlive(true) {

}

void Galaga::Initialize(CMPUT350::GameContext* context) {
    context->mEngineView->AddGameObject(
        std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));
    MapKeydown(context, (int) sf::Keyboard::Key::A, "MoveLeftStart");
    MapKeyup(context, (int)sf::Keyboard::Key::A, "MoveLeftEnd");
    MapKeydown(context, (int) sf::Keyboard::Key::D, "MoveRightStart");
    MapKeyup(context, (int)sf::Keyboard::Key::D, "MoveRightEnd");
    MapKeydown(context, (int) sf::Keyboard::Key::Space, "Shoot");
    MapKeydown(context, (int)sf::Keyboard::Key::Num5, "Coin");
    MapKeydown(context, (int)sf::Keyboard::Key::Num1, "Start");
    MapKeydown(context, (int)sf::Keyboard::Key::Num3, "Reset");
    context->mNotificationManager->Register(context->CurrObject, "Coin");
    context->mNotificationManager->Register(context->CurrObject, "Start");
    context->mNotificationManager->Register(context->CurrObject, "Reset");
}

void Galaga::MapKeydown(CMPUT350::GameContext* context, int key, std::string notification) {
    context->mEngineView->InstallKeyDownNotification(key, notification);
}

void Galaga::MapKeyup(CMPUT350::GameContext* context, int key, std::string notification) {
    context->mEngineView->InstallKeyUpNotification(key, notification);
}

void Galaga::Update(CMPUT350::GameContext* context) {
    if (state == 0) { // menu screen
        time = context->currentFrame;
    }
    if (state == 1) { // info screen

        if (context->currentFrame > time) {
            state = 2;
        }
    }
    if (state == 2) {
        if (shipCache.expired()) {
            auto player = std::make_shared<Player>(CMPUT350::Point2D(768 / 2, 900));
            context->mEngineView->AddGameObject(player);
            shipCache = player;
        }
        
        for (int y = 0; y < 1; y++) {
            for (int x = 0; x < 1; x++) {
                std::vector<CMPUT350::Point2D> path;
                path.push_back(CMPUT350::Point2D(127, 767));
                path.push_back(CMPUT350::Point2D(599, 779));
                path.push_back(CMPUT350::Point2D(659, 603));
                path.push_back(CMPUT350::Point2D(100, 50));
                auto enemy =
                    std::make_shared<Enemy1>(CMPUT350::Point2D(100 + x * 200, 100 + 50 * y), path);
                
                enemyCache.push_back(enemy);
                context->mEngineView->AddGameObject(enemy);
            }
        }
        state = 3;
    }
    if (state == 3) {
        // all enemies died TODO: add condition to check on wave 5
        if (wave == 5) { // advance level
            time = context->currentFrame + 30;
            state = 1;
            level += 1;
            shipCache.lock()->Kill();
        }
        if (shipCache.expired()) {
            lives -= 1;
            state = 1;
        }
        if (!enemyCache.size() && wave < 5) {
            time = context->currentFrame + 30;
            state = 1;
            level += 1;
        }
        for (auto& enemy : enemyCache) {
            if (!enemy.expired()) {
                std::shared_ptr<Enemy> enemyPtr = enemy.lock();
                enemyPtr->Attack(context, shipCache.lock()->GetLocation());
            }
        }
    }
}

void Galaga::LateUpdate(CMPUT350::GameContext* context) {
    // clear enemy and object cache
    for (int i = 0; i < enemyCache.size(); i++) {
        if (enemyCache[i].expired()) {
            enemyCache.erase(enemyCache.begin() + i);
            std::cout << "erased enemy\n";
        }
    }
}

void Galaga::RenderUI(CMPUT350::GameContext* context) {
    if (state == 0) {
        context->GUIContext->DrawCenteredText(
            "Galaga", 25,
            CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2,
                              context->GUIContext->GetWindowHeight() / 2),
            CMPUT350::Colors::white);
        context->GUIContext->DrawText(
            "COINS: " + std::to_string(coins), 25,
            CMPUT350::Point2D(5, context->GUIContext->GetWindowHeight() - 5 - 25),
            CMPUT350::Colors::white);
    }

    if (state == 1) {
        context->GUIContext->DrawCenteredText(
            std::to_string(lives) + " LIVES LEFT", 25,
            CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2,
                              context->GUIContext->GetWindowHeight() / 2),
            CMPUT350::Colors::white);
        context->GUIContext->DrawCenteredText(
            "LEVEL " + std::to_string(level), 25,
            CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2,
                              context->GUIContext->GetWindowHeight() / 2 - 30),
            CMPUT350::Colors::white);
    }

    context->GUIContext->DrawCenteredText(
        "SCORE", 25,
        CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2, 5),
        CMPUT350::Colors::white);
    context->GUIContext->DrawCenteredText(
        std::to_string(score), 25, CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2, 35),
        CMPUT350::Colors::white);
    if (state > 0) {
        context->GUIContext->DrawText(
            "LIVES: " + std::to_string(lives), 25,
            CMPUT350::Point2D(5, context->GUIContext->GetWindowHeight() - 5 - 25),
            CMPUT350::Colors::white);    
    }
}

bool Galaga::IsAlive() const { return isAlive; }

void Galaga::Kill() { isAlive = false; }

void Galaga::ReceiveNotification(const std::string& key) {
    if (key == "Coin") {
        coins++;
    }
    else if (key == "Start" && state == 0 && coins > 0) {
        state = 1;
        coins--;
        lives = 3;
        time += 30;
    }

}

void Galaga::RenderBackground(CMPUT350::GameContext* context) {

}

void Galaga::RenderForeground(CMPUT350::GameContext* context) {
    
}

CMPUT350::Point2D Galaga::GetLocation() const { return {0, 0}; }

float Galaga::GetRotation() const { return 0; }
