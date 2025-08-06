module;

#include <iostream>

module inputManager;

void name::InputManager::RegisterCallback(name::InputManager::EventType type,
                                          name::InputManager::EventCallback callback) {
    Callbacks_[type].push_back(callback);
}

void name::InputManager::DispatchMessage(name::InputManager::EventType type,
                                         const std::string& data) {
    auto it = Callbacks_.find(type);
    if (it != Callbacks_.end()) {
        for (const auto& callback : it->second) {
            callback(data);
        }
    }
}

void name::printHello() { std::cout << "Hello from InputManager module!" << std::endl; }