#ifndef GALAGA_H
#define GALAGA_H

#include "GraphicsObject.h"
#include "GameContext.h"
#include "Enemy.h"
#include "Player.h"

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
    void MapKeydown(CMPUT350::GameContext* context, int key, std::string notification);
    void MapKeyup(CMPUT350::GameContext* context, int key, std::string notification);
    int state = 0;
    // States:
    // 0 - Main menu
    // 2 - Initialize game
    // 3 - Playing
    // 4 - 

    int score = 0;
    int lives = 0;
    int coins = 0;
    int time = 0;
    int level = 1;
    int wave = 0;
    int waveTime = 0;
    int waveLen = 0;
    bool waveFinish = false;
    bool isAlive;

    std::weak_ptr<Player> shipCache;
    std::vector<std::weak_ptr<Enemy>> enemyCache;
};

#endif