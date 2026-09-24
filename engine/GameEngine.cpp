#include "GameEngine.h"
#include "GameContext.h"
#include "GraphicsObject.h"
#include "CollisionObject.h"
#include <iostream> // debug
/// @brief
namespace CMPUT350 {
#include "FontData.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name) {
    // Sample font loading code
    //	if (!mFont->openFromMemory(&_font, _font_len))
    //	{
    //		fprintf(stderr, "WARNING: Font did not load.\n");
    //	}
    
    // load window
    mWindow.reset(new sf::RenderWindow(sf::VideoMode({width, height}), name));
    mWindow->setFramerateLimit(30);

    // initialize object vectors
    mObjectPending.reset(new std::vector<std::shared_ptr<GameObject>>);
    mObjects.reset(new std::vector<std::shared_ptr<GameObject>>);

    // TODO: load resources
    mFont.reset(new sf::Font);
    if (!mFont->openFromMemory(&_font, _font_len))
    {
    	fprintf(stderr, "WARNING: Font did not load.\n");
    }

    // create context
    context.reset(new GameContext());
    context->mEngineView = this;
    context->ScreenContext = new DrawContext(mWindow, mFont);
}

GameEngine::~GameEngine() {
    // TODO: Cleanup resources
    delete context->ScreenContext;

    for (int i = 0; i < mObjects->size(); i++) {
        mObjects->erase(mObjects->begin() + i);
    }
    
    for (int i = 0; i < mObjectPending->size(); i++) {
        mObjectPending->erase(mObjectPending->begin() + i);
    }
    
    mWindow->close();
}

void GameEngine::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    mObjectPending->push_back(gameObject); // add to pending array to be initialized next frame
}

/**
 * @method Run
 * @arguments None
 * @description Gives control to the game engine. Will not return until the game window is closed or
 * all objects have been destroyed.
 */
void GameEngine::Run() {

    while (mWindow->isOpen())  // window is open
    {
        // 0. Remove any objects that are now dead
        for (int i = 0; i < mObjects->size(); i++) {
            if (!mObjects->at(i)->IsAlive()) { mObjects->erase(mObjects->begin() + i); }
        }

        // 1. Activate and initialize any objects added during the last frame
        for (int i = 0; i < mObjectPending->size(); i++) {
            mObjectPending->at(i)->Initialize(context.get()); // calls initialize
            mObjects->push_back(mObjectPending->at(i)); // add to live objects
            mObjectPending->erase(mObjectPending->begin() + i); // remove from pending
        }

        // 2. Process events
        while (const std::optional event = mWindow->pollEvent()) {
            if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
                if (keyPressed->unicode < 128) {
                    for (const std::shared_ptr<GameObject>& i : *mObjects) {
                        i->HandleKeyEvent(context.get(), static_cast<char>(keyPressed->unicode));  // invoke event update every objects
                    }
                }
            }
            if (event->is<sf::Event::Closed>()) mWindow->close();
        }

        // 3. Update game objects
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->Update(context.get());  // invoke update every objects
        }

        // 4. Process collision events
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            std::shared_ptr<CollisionObject> obj1 = std::dynamic_pointer_cast<CollisionObject>(i);
            if (obj1 == nullptr) { continue; }
            
            for (const std::shared_ptr<GameObject>& j : *mObjects) {
                std::shared_ptr<CollisionObject> obj2 = std::dynamic_pointer_cast<CollisionObject>(j);
                if (obj2 == nullptr || obj1 == obj2) { continue; }

                obj1->CollisionEnter(obj2);
            }
        }

        // 5. Late updates
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->LateUpdate(context.get());  // invoke late update every objects
        }

        // Clear window
        mWindow->clear(sf::Color::Black);

        // 6. Render background
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            std::shared_ptr<GraphicsObject> obj = std::dynamic_pointer_cast<GraphicsObject>(i);
            if (obj == nullptr) { continue; }

            obj->RenderBackground(context.get());
        }

        // 7. Render foreground
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            std::shared_ptr<GraphicsObject> obj = std::dynamic_pointer_cast<GraphicsObject>(i);
            if (obj == nullptr) {
                continue;
            }
            //printf("drawing foreground\n");
            obj->RenderForeground(context.get());
        }

        // Actually render to window
        mWindow->display();
        //std::cout << mObjects->size() << std::endl;
    }
}

// Sample code for processing events

// bool GameEngine::ProcessEvents(GameContext *context)
//{
//	while (const std::optional event = mWindow->pollEvent())
//	{
//		if (event->is<sf::Event::Closed>())
//		{
//		}
//		else if (event->is<sf::Event::Resized>())
//		{
//		}
//		else if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>())
//		{
//			// use keyPressed->unicode to get character
//		}
//	}
// }

}  // namespace CMPUT350
