#include <format>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "taskmanager.hpp"

class Game {
   public:
    void Init() {
        // Registering a callback for an event (for example, a handleMouseEvent with inputManager)
        InputManager_.RegisterCallback(
            name::InputManager::EventType::MOUSE,
            std::bind(&Game::HandleMouseEvent, this, std::placeholders::_1));
    }

    void Run() {
        InputManager_.DispatchMessage(name::InputManager::EventType::MOUSE, "Mouse moved");
        Running_ = true;
        TaskManager_.Start();
        while (Running_) {
            Command command1{0};
            std::cout << "Enter a number of command, to exit enter -1: ";
            std::cin >> command1;

            switch (command1) {
                case -1: {
                    Running_ = false;
                    break;
                }
                 case -100: {
                std::cout << "Restarting TaskManager" << std::endl;
                TaskManager_.Stop();
                TaskManager_.Start();
                break;
        }
                default: {
                    TaskManager_.QueueCommand(command1);
                    break;
                }
            }
        }

        std::cout << "Game Loop stopped" << std::endl;
    }

    void HandleMouseEvent(std::string data) {
        std::cout << std::format("Game clasds Mouse event handled with data: {}", data)
                  << std::endl;
    }

    name::InputManager& GetInputManager() { return InputManager_; }

   private:
    name::InputManager InputManager_{};
    TaskManager TaskManager_{};

    bool Running_{false};
};

void HandleMouseEvent(const std::string& data) {
    std::cout << std::format("Mouse event handled with data: {}", data) << std::endl;
}

int main(int argc, char* argv[]) {
    Game game;
    game.Init();

    game.Run();

    return 0;
}