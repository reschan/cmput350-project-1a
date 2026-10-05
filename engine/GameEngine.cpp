#include "GameEngine.h"
#include "GameContext.h"
#include "GraphicsObject.h"
#include "CollisionObject.h"
#include <iostream> // debug
#include <cmath>
#include "MathUtil.h"
/// @brief
namespace CMPUT350 {
#include "FontData.h"

GameEngine::GameEngine(unsigned int width, unsigned int height, const std::string& name) {    
    // load window
    mWindow.reset(new sf::RenderWindow(sf::VideoMode({width, height}), name));
    mWindow->setFramerateLimit(30);

    // initialize object vectors
    mObjectPending.reset(new std::vector<std::shared_ptr<GameObject>>);
    mObjects.reset(new std::vector<std::shared_ptr<GameObject>>);
    mKeydown.reset(new std::unordered_map<int, std::string>);
    mKeyup.reset(new std::unordered_map<int, std::string>);

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
    context->GUIContext = new DrawContext(mWindow, mFont);
    context->mNotificationManager = new NotificationManager();
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

void GameEngine::InstallKeyDownNotification(int key, const std::string& notification) {
    mKeydown->insert(std::pair<int, std::string>(key, notification));
}

void GameEngine::InstallKeyUpNotification(int key, const std::string& notification) {
    mKeyup->insert(std::pair<int, std::string>(key, notification));
}

GameEngine::const_iterator GameEngine::cbegin() const { return mObjects->cbegin(); }

GameEngine::const_iterator GameEngine::cend() const { return mObjects->cend(); }

GameEngine::const_iterator GameEngine::begin() const { return mObjects->begin(); }

GameEngine::const_iterator GameEngine::end() const { return mObjects->end(); }

bool GameEngine::ComputeCollision(const Rect a, const Rect b, Point2D* crossPt) {
    if (a.topLeft.x + a.width <= b.topLeft.x) {
        return false;
    } 
    if (b.topLeft.x + b.width <= a.topLeft.x) {
        return false;
    }
    if (a.topLeft.y + a.height <= b.topLeft.y) {
        return false;
    }
    if (b.topLeft.y + b.height <= a.topLeft.y) {
        return false;
    }
    return true;
}

bool GameEngine::ComputeCollision(const Rect a, const Circle b, Point2D* crossPt) { 
    
    return true; 
}

bool GameEngine::ComputeCollision(const Rect a, const Line b, Point2D* crossPt) { 
    Point2D rectCenter(a.topLeft.x + (a.width / 2), a.topLeft.y + (a.height / 2));
    bool res = a.IsInside(b.ClosestPoint(rectCenter));
    if (res) {
        *crossPt = b.ClosestPoint(rectCenter);
    }
    return res; 
}

bool GameEngine::ComputeCollision(const Circle a, const Circle b, Point2D* crossPt) { 
    return std::pow(b.center.x - a.center.x, 2) + std::pow(b.center.y - a.center.y, 2) <= std::pow(a.radius + b.radius, 2);
}

bool GameEngine::ComputeCollision(const Circle a, const Line b, Point2D* crossPt) { 
    Point2D closestPt = b.ClosestPoint(a.center);
    *crossPt = closestPt;

    return closestPt.Distance(a.center) <= a.radius; 
}

bool GameEngine::ComputeCollision(const Line a, const Line b, Point2D* crossPt) { 
    return a.Crosses(b, *crossPt); 
}

bool GameEngine::ComputeCollision(const Circle a, const Rect b, Point2D* crossPt) {
    return ComputeCollision(b, a, crossPt);
}
bool GameEngine::ComputeCollision(const Line a, const Rect b, Point2D* crossPt) {
    return ComputeCollision(b, a, crossPt);
}
bool GameEngine::ComputeCollision(const Line a, const Circle b, Point2D* crossPt) {
    return ComputeCollision(b, a, crossPt);
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
            context->CurrObject = mObjectPending->at(i);
            mObjectPending->at(i)->Initialize(context.get()); // calls initialize
            mObjects->push_back(mObjectPending->at(i)); // add to live objects
            mObjectPending->erase(mObjectPending->begin() + i); // remove from pending
        }

        // 2. Process events
        while (const std::optional event = mWindow->pollEvent()) {
            // (1b) Send keys to notification manager
            // keydown
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (mKeydown->contains((int)keyPressed->code)) {
                    context->mNotificationManager->Notify(mKeydown->at((int)keyPressed->code));
                }
            }

            // keyup
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                if (mKeyup->contains((int) keyReleased->code)) {
                    context->mNotificationManager->Notify(mKeyup->at((int)keyReleased->code));
                }
            }

            // window closing behavior
            if (event->is<sf::Event::Closed>()) mWindow->close();
        }

        // 3. Update game objects
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->Update(context.get());  // invoke update every objects
        }

        // 4. Process collision events
        // (1b) Compute collisions?
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            std::shared_ptr<CollisionObject> obj1 = std::dynamic_pointer_cast<CollisionObject>(i);
            if (obj1 == nullptr) { continue; }
            
            for (const std::shared_ptr<GameObject>& j : *mObjects) {
                std::shared_ptr<CollisionObject> obj2 = std::dynamic_pointer_cast<CollisionObject>(j);
                if (obj2 == nullptr || obj1 == obj2) { continue; } // check if its not itself

                

                // determine collisions
                if (ComputeCollision(obj1->GetBounds(), obj2->GetBounds())) {
                    obj1->CollisionEnter(obj2);
                }
            }
        }

        // 5. Late updates
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            i->LateUpdate(context.get());  // invoke late update every objects
        }

        // Clear window
        mWindow->clear(sf::Color::Black);

        // (1b) Get offsets and rotations from objects and pass them to DrawContext

        // 6. Render background
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            std::shared_ptr<GraphicsObject> obj = std::dynamic_pointer_cast<GraphicsObject>(i);
            if (obj == nullptr) { continue; }

            context->ScreenContext->SetContextRotation(obj->GetRotation());
            context->ScreenContext->SetContextOffset(obj->GetLocation());
            obj->RenderBackground(context.get());
        }

        // 7. Render foreground
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            std::shared_ptr<GraphicsObject> obj = std::dynamic_pointer_cast<GraphicsObject>(i);
            if (obj == nullptr) { continue; }

            context->ScreenContext->SetContextRotation(obj->GetRotation());
            context->ScreenContext->SetContextOffset(obj->GetLocation());
            obj->RenderForeground(context.get());
        }

        // (1b) Render GUI
        for (const std::shared_ptr<GameObject>& i : *mObjects) {
            std::shared_ptr<GraphicsObject> obj = std::dynamic_pointer_cast<GraphicsObject>(i);
            if (obj == nullptr) {
                continue;
            }

            obj->RenderUI(context.get());
        }

        // Actually render to window
        mWindow->display();

        context->currentFrame += 1;
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
