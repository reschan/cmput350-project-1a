#ifndef PLAYER_H
#define PLAYER_H

#include "CollisionObject.h"

class Player : public CMPUT350::CollisionObject
{
public:
    Player(CMPUT350::Point2D loc);

    // GameObject Functions
    void Initialize(CMPUT350::GameContext* context) override;
    void Update(CMPUT350::GameContext* context) override;
    void LateUpdate(CMPUT350::GameContext* context) override;
    bool HandleKeyEvent(CMPUT350::GameContext* context, char key) override;
    bool IsAlive() const override;
    void Kill() override;

    // Graphics Object Functions
    void RenderBackground(CMPUT350::GameContext* context) override;
    void RenderForeground(CMPUT350::GameContext* context) override;


    // Collision Object Functions
    void CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) override;
    const CMPUT350::Rect& GetBounds() override;

private:
    CMPUT350::Point2D center;
    int width = 40;
    int height = 40;
    int side_rect_width;
    int side_rect_height;
    int top_rect_width;
    int top_rect_height;
    int body_width;
    int body_height;
    int side_rect_x_offset;
    int side_rect_y_offset;
    int top_rect_offset;
};

#endif
