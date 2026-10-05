
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

namespace CMPUT350 {
class GameEngine;
}

#include "EngineView.h"
#include "GameObject.h"
#include "MathUtil.h"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace CMPUT350 {

class DrawContext;

class GameEngine : public EngineView {
    using const_iterator = tGameObject::const_iterator;
public:
    GameEngine(unsigned int width, unsigned int height, const std::string& name);
    ~GameEngine();

    GameEngine(const GameEngine&) = delete;             // Prevent copy-construction
    GameEngine(GameEngine&&) = delete;                  // Prevent move-construction
    GameEngine& operator=(const GameEngine&) = delete;  // Prevent assignment
    GameEngine& operator=(GameEngine&&) = delete;       // Prevent move-assignment

    void AddGameObject(std::shared_ptr<GameObject> gameObject) override;
    void InstallKeyDownNotification(int, const std::string& notification) override;
    void InstallKeyUpNotification(int, const std::string& notification) override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;
    const_iterator begin() const override;
    const_iterator end() const override;

    bool ComputeCollision(const Rect a, const Rect b, Point2D* crossPt = nullptr);
    bool ComputeCollision(const Rect a, const Circle b, Point2D* crossPt = nullptr);
    bool ComputeCollision(const Rect a, const Line b, Point2D *crossPt = nullptr);
    bool ComputeCollision(const Circle a, const Rect b, Point2D* crossPt = nullptr);
    bool ComputeCollision(const Circle a, const Circle b, Point2D* crossPt = nullptr);
    bool ComputeCollision(const Circle a, const Line b, Point2D* crossPt = nullptr);
    bool ComputeCollision(const Line a, const Rect b, Point2D* crossPt = nullptr);
    bool ComputeCollision(const Line a, const Circle b, Point2D* crossPt = nullptr);
    bool ComputeCollision(const Line a, const Line b, Point2D* crossPt = nullptr);

    void Run();

private:
    std::shared_ptr<sf::RenderWindow> mWindow; // pointer to main window
    std::shared_ptr<sf::Font> mFont; // pointer to font resource 

    // game object lists
    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> mObjectPending; // pointer to pending game objects
    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> mObjects;  // pointer to game objects

    std::unique_ptr<GameContext> context; // keeps track of game contexts

    // key mapping
    std::unique_ptr<std::unordered_map<int, std::string>> mKeydown;
    std::unique_ptr<std::unordered_map<int, std::string>> mKeyup;
};

}  // namespace CMPUT350

#endif  // GAMEENGINE_H
