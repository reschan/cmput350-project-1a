#include "Enemy.h"

class Enemy2 : public Enemy {
public:
    Enemy2(CMPUT350::Point2D loc, const std::vector<CMPUT350::Point2D>& path);
    bool Attack(CMPUT350::GameContext* context, const CMPUT350::Point2D& target) override;
    void RenderForeground(CMPUT350::GameContext* context) override;
    void RenderBackground(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;

private: 
    int bullets;
};
