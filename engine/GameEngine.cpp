#include "GameEngine.h"
#include "GameContext.h"
#include "GraphicsObject.h"

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
    if (!mFont->openFromMemory(&_font, _font_len))
    {
    	fprintf(stderr, "WARNING: Font did not load.\n");
    }

    // create context
    context = new GameContext();
    context->mEngineView = this;
    context->ScreenContext = new DrawContext(mWindow, mFont);
}

GameEngine::~GameEngine() {
    // TODO: Cleanup resources
    
    
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
            mObjectPending->at(i)->Initialize(context); // calls initialize
            mObjects->push_back(mObjectPending->at(i)); // add to live objects
            mObjectPending->erase(mObjectPending->begin() + i); // remove from pending
        }

        // 2. Process events
        while (const std::optional event = mWindow->pollEvent()) {
            if (const auto* keyPressed = event->getIf<sf::Event::TextEntered>()) {
                if (keyPressed->unicode < 128) {
                    for (const std::shared_ptr<GameObject>& i : *mObjects) {
                        i->HandleKeyEvent(context, static_cast<char>(keyPressed->unicode));  // invoke event update every objects
                    }
                }
            }
        }

        // 3. Update game objects
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->Update(context); // invoke update every objects
        }

        // 4. Process collision events

        // 5. Late updates
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->LateUpdate(context);  // invoke late update every objects
        }

        // Clear window
        mWindow->clear();

        // 6. Render background
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->RenderBackground(context);
        }

        // 7. Render foreground
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->RenderForeground(context);
        }

        // Actually render to window
        mWindow->display();
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
