#include "taskmanager.hpp"

#include <iostream>

TaskManager::~TaskManager() {
    if (CommandThread_.joinable()) {
        Running_ = false;
        CommandThread_.join();
    }
}

void TaskManager::Start() {
    std::cout << "TaskManager started" << std::endl;

    if (CommandThread_.joinable()) {
        if (!Running_) {
            CommandThread_.join();
            std::cout << "Thread finished, but wasn't joined" << std::endl;
        } else {
            std::cout << "Command thread is already running" << std::endl;
            return;
        }
    }

    CommandQueue_.clear();
    CommandThread_ = std::thread(&TaskManager::Run, this);
}

void TaskManager::QueueCommand(Command command) {
    if (!Running_) {
        std::cout << "TaskManager is not running" << std::endl;
        return;
    }

    std::cout << std::format("Command {} queued", command) << std::endl;

    CommandQueue_.push_back(command);
}

void TaskManager::Run() {
    std::cout << "TaskManager running" << std::endl;
    Running_ = true;
    while (Running_) {
        if (CommandQueue_.empty()) {
            continue;
        }

        ExcecuteCommand(CommandQueue_.front());

        CommandQueue_.pop_front();
    }
    std::cout << "TaskManager stopped" << std::endl;
}

void TaskManager::ExcecuteCommand(Command command) {
    switch (command) {
        case 0: {
            std::cout << "Executing command 0" << std::endl;
            break;
        }
        case 1: {
            std::cout << "Executing command 1" << std::endl;
            break;
        }
       
        default: {
            std::cout << std::format("Executing unknown command {}", command) << std::endl;
            Running_ = false;
            std::cout << "Stopping TaskManager" << std::endl;
            break;
        }
    }
}

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
