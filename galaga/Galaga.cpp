#include "Galaga.h"

Galaga::Galaga() : isAlive(true) {

}

void Galaga::Initialize(CMPUT350::GameContext* context) {

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

CMPUT350::Point2D Galaga::GetLocation() const {

}

float Galaga::GetRotation() const {

}
