#ifndef GALAGA_H
#define GALAGA_H

#include "GraphicsObject.h"
#include "GameContext.h"

class Galaga : public CMPUT350::GraphicsObject
{
public:
    Galaga();

    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    void RenderUI(CMPUT350::GameContext* context);
    bool IsAlive() const override;
    void Kill() override;
    void ReceiveNotification(const std::string& key) override;

    void RenderBackground(CMPUT350::GameContext* context) override;
    void RenderForeground(CMPUT350::GameContext* context) override;
    CMPUT350::Point2D GetLocation() const override;
    float GetRotation() const override;

private:
    bool isAlive;
};

#endif