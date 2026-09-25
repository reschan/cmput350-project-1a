
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

namespace CMPUT350 {
class GameEngine;
}

#include "EngineView.h"
#include "GameObject.h"
#include "MathUtil.h"
#include <SFML/Graphics.hpp>

namespace CMPUT350 {

class DrawContext;

class GameEngine : public EngineView {
public:
    GameEngine(unsigned int width, unsigned int height, const std::string& name);
    ~GameEngine();

    GameEngine(const GameEngine&) = delete;             // Prevent copy-construction
    GameEngine(GameEngine&&) = delete;                  // Prevent move-construction
    GameEngine& operator=(const GameEngine&) = delete;  // Prevent assignment
    GameEngine& operator=(GameEngine&&) = delete;       // Prevent move-assignment

    void AddGameObject(std::shared_ptr<GameObject> gameObject) override;

    void Run();

private:
    std::shared_ptr<sf::RenderWindow> mWindow; // pointer to main window
    std::shared_ptr<sf::Font> mFont; // pointer to font resource 

    // game object lists
    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> mObjectPending; // pointer to pending game objects
    std::unique_ptr<std::vector<std::shared_ptr<GameObject>>> mObjects;  // pointer to game objects

    std::unique_ptr<GameContext> context; // keeps track of game contexts
};

}  // namespace CMPUT350

#endif  // GAMEENGINE_H
