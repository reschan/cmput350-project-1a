#include "Galaga.h"
#include "Player.h"
#include "Enemy.h"
#include "Stars.h"

Galaga::Galaga() : isAlive(true) {

}

void Galaga::Initialize(CMPUT350::GameContext* context) {
    auto player = std::make_shared<Player>(CMPUT350::Point2D(768 / 2, 900));
    context->mEngineView->AddGameObject(player);
    context->mEngineView->AddGameObject(
        std::make_shared<Stars>(250, CMPUT350::Rect(0, 0, 768, 1024)));
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 4; x++) {
            auto enemy = std::make_shared<Enemy>(CMPUT350::Point2D(100 + x * 200, 100 + 50 * y));
            context->mEngineView->AddGameObject(enemy);
        }
    }
    context->mEngineView->InstallKeyDownNotification((int)sf::Keyboard::Key::A, "MoveLeft");
    context->mEngineView->InstallKeyDownNotification((int)sf::Keyboard::Key::D, "MoveRight");
    context->mNotificationManager->Register(player, "MoveLeft");
    context->mNotificationManager->Register(player, "MoveRight");
}

void Galaga::Update(CMPUT350::GameContext* context) {

}

void Galaga::LateUpdate(CMPUT350::GameContext* context) {

}

void Galaga::RenderUI(CMPUT350::GameContext* context) {

}

bool Galaga::IsAlive() const { return isAlive; }

void Galaga::Kill() { isAlive = false; }

void Galaga::ReceiveNotification(const std::string& key) {

}

void Galaga::RenderBackground(CMPUT350::GameContext* context) {

}

void Galaga::RenderForeground(CMPUT350::GameContext* context) {

}

CMPUT350::Point2D Galaga::GetLocation() const { return {0, 0}; }

float Galaga::GetRotation() const { return 0; }
