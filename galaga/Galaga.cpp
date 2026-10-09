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
    context->mNotificationManager->Register(context->CurrObject, "Enemy1Killed");
    context->mNotificationManager->Register(context->CurrObject, "Enemy2Killed");
    context->mNotificationManager->Register(context->CurrObject, "Enemy3Killed");
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
            time = context->currentFrame + 60;
        }
    }
    if (state == 2) { // initialize
        if (shipCache.expired()) {
            auto player = std::make_shared<Player>(CMPUT350::Point2D(768 / 2, 900));
            context->mEngineView->AddGameObject(player);
            shipCache = player;
        }

        
        state = 3;
    }
    if (state == 3) { // main game loop
        // all enemies died TODO: add condition to check on wave 5
        if (wave == 5 && !enemyCache.size()) { // advance level
            time = context->currentFrame + 60;
            state = 1;
            level += 1;
            wave = 0;
            waveFinish = false;
            waveLen = 0;
            waveTime = 0;
        }
        if (shipCache.expired() && lives != -1) {
            lives -= 1;
            state = 1;
            time = context->currentFrame + 30;
        }
        if (lives == -1) {
            for (auto& enemy : enemyCache) {
                if (!enemy.expired()) {
                    enemy.lock()->Kill();
                }
            }
            time = context->currentFrame + 60;
            state = 4;
        }
        if (!enemyCache.size() && waveFinish) {
            wave += 1; // use this to script for 5 wave
            //spawn next wave
            // random waves?
            waveTime = 0;
            waveLen = 0;
        }
        if (!waveFinish && context->currentFrame > waveTime + 60) {
            if (waveLen == 5) {
                waveFinish = true;
            } else {
                for (int i = 0; i < 8; i++) {  // straight waves
                    // spawn 8 enemies
                    std::vector<CMPUT350::Point2D> path;
                    path.push_back(CMPUT350::Point2D(127, 767));
                    path.push_back(CMPUT350::Point2D(599, 779));
                    path.push_back(CMPUT350::Point2D(659, 603));
                    path.push_back(CMPUT350::Point2D(96 * i + 30, 50 * waveLen + 30));
                    auto enemy = std::make_shared<Enemy1>(CMPUT350::Point2D(0, 0), path);
                    std::shared_ptr<Enemy> baseEnemyVersionPtr = enemy;
                    enemyCache.push_back(baseEnemyVersionPtr);
                    context->mEngineView->AddGameObject(baseEnemyVersionPtr);
                }
                waveLen++;
                waveTime = context->currentFrame;
            }
        }
        if (waveFinish && context->currentFrame > waveTime + 120) {
            for (auto& enemy : enemyCache) {  // enemy scripting
                if (!enemy.expired() && !shipCache.expired() && context->currentFrame > time) {
                    std::shared_ptr<Enemy> enemyPtr = enemy.lock();
                    enemyPtr->Attack(context, shipCache.lock()->GetLocation());
                }
            }
        }
    }
    if (state == 4) { // cleanup and restart
        if (context->currentFrame > time) {
            level = 1;
            wave = 0;
            waveFinish = false;
            waveLen = 0;
            waveTime = 0;
            state = 0;
            score = 0;
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

    if (state == 4) {
        context->GUIContext->DrawCenteredText(
            "GAME OVER", 25,
            CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2,
                              context->GUIContext->GetWindowHeight() / 2),
            CMPUT350::Colors::white);
    }

    context->GUIContext->DrawCenteredText(
        "SCORE", 25,
        CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2, 5),
        CMPUT350::Colors::white);
    context->GUIContext->DrawCenteredText(
        std::to_string(score), 25, CMPUT350::Point2D(context->GUIContext->GetWindowWidth() / 2, 35),
        CMPUT350::Colors::white);
    if (state > 0 && state < 4) {
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
    if (key == "Start" && state == 0 && coins > 0) {
        state = 1;
        coins--;
        lives = 3;
        time += 30;
    }
    if (key == "Enemy1Killed") {
        score += 1000;
    }
    if (key == "Enemy2Killed") {
        score += 2000;
    }
    if (key == "Enemy3Killed") {
        score += 4000;
    }
}

void Galaga::RenderBackground(CMPUT350::GameContext* context) {

}

void Galaga::RenderForeground(CMPUT350::GameContext* context) {
    
}

CMPUT350::Point2D Galaga::GetLocation() const { return {0, 0}; }

float Galaga::GetRotation() const { return 0; }
