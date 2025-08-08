#include "taskmanager.hpp"

#include <iostream>

TaskManager::~TaskManager() { Stop(); }

void TaskManager::Start() {
    std::unique_lock lock(CommandMutex_);
    if (Running_) {
        std::cout << "Command thread is already running" << std::endl;
        return;
    }
    lock.unlock();
 
    if (CommandThread_.joinable()) {
        CommandThread_.join();
    }

    lock.lock();
    CommandQueue_.clear();
    Running_ = true;
    CommandThread_ = std::thread(&TaskManager::Run, this);
    std::cout << "TaskManager started" << std::endl;
}

void TaskManager::Stop() {
    {
        std::unique_lock lock(CommandMutex_);
        if (!Running_) {
            // If not "running" but thread is there, it might have stopped itself.
            // We still need to join it.
            if (CommandThread_.joinable()) {
                lock.unlock();
                CommandThread_.join();
            }
            return;
        }
        Running_ = false;
    }
    CommandCondition_.notify_one();
    if (CommandThread_.joinable()) {
        CommandThread_.join();
    }
}

void TaskManager::QueueCommand(Command command) {
    {
        std::unique_lock lock(CommandMutex_);
        if (!Running_) {
            std::cout << "TaskManager is not running" << std::endl;
            return;
        }

        std::cout << std::format("Command {} queued", command) << std::endl;
        CommandQueue_.push_back(command);
    }
    CommandCondition_.notify_one();
}

void TaskManager::Run() {
    std::cout << "TaskManager running" << std::endl;
    while (true) {
        Command command;
        {
            std::unique_lock lock(CommandMutex_);
            // Поток "засыпает" здесь, пока очередь не станет непустой ИЛИ пока Running_ не станет false
            CommandCondition_.wait(lock, [this] { return !CommandQueue_.empty() || !Running_; });

            // Условие выхода из цикла: поток больше не работает и все команды обработаны
            if (!Running_ && CommandQueue_.empty()) {
                break;
            }

            command = CommandQueue_.front();
            CommandQueue_.pop_front();
        }
        ExcecuteCommand(command);
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
            std::cout << std::format("Executing unknown command {}, stopping TaskManager", command)
                      << std::endl;
            // Безопасно изменяем флаг, чтобы цикл Run() завершился
            std::unique_lock lock(CommandMutex_);
            Running_ = false;
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
