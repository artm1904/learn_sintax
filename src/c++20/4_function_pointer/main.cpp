
#include <format>
#include <functional>
#include <iostream>
#include <string>

import inputManager;

// #define test1
// #define test2
#define test3

class Game {
   public:
    void Init() {
#if defined(test2)
        // Registering a callback for an event (for example, a handleMouseEvent with inputManager)
        InputManager_.RegisterCallback(
            name::InputManager::EventType::MOUSE,
            std::bind(&Game::HandleMouseEvent, this, std::placeholders::_1));

#endif

#if defined(test3)
        // using a lambda function as a callback
        InputManager_.RegisterCallback(
            name::InputManager::EventType::MOUSE,
            [this](const std::string& data) -> void { return HandleMouseEvent(data); });

#endif
    }

    void HandleMouseEvent(std::string data) {
        std::cout << std::format("Game clasds Mouse event handled with data: {}", data)
                  << std::endl;
    }

    name::InputManager& GetInputManager() { return InputManager_; }


   private:
    name::InputManager InputManager_;
};

void HandleMouseEvent(const std::string& data) {
    std::cout << std::format("Mouse event handled with data: {}", data) << std::endl;
}

int main(int argc, char* argv[]) {
    // name::printHello();

#if defined(test1)
    name::InputManager inputManager{};
    inputManager.RegisterCallback(name::InputManager::EventType::MOUSE, &HandleMouseEvent);
    inputManager.DispatchMessage(name::InputManager::EventType::MOUSE, "Mouse moved to (100, 200)");
    return 0;
#endif

#if defined(test2)
    name::InputManager inputManager{};
    inputManager.RegisterCallback(name::InputManager::EventType::MOUSE, &HandleMouseEvent);
    inputManager.DispatchMessage(name::InputManager::EventType::MOUSE, "Mouse moved to (100, 200)");

    Game game;
    game.Init();
    game.GetInputManager().DispatchMessage(name::InputManager::EventType::MOUSE,
                                           "Mouse moved to (150, 250)");

#endif

#if defined(test3)

    Game game;
    game.Init();
    game.GetInputManager().DispatchMessage(name::InputManager::EventType::MOUSE,
                                           "LAMBDA Mouse moved to (150, 250)");

#endif

    return 0;
}