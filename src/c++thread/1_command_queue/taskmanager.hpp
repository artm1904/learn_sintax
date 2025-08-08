#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using Command = int;

class TaskManager {
   public:
    TaskManager() = default;
    ~TaskManager();

    void Start();
    void Stop();

    void QueueCommand(Command);

   protected:
    void Run();
    void ExcecuteCommand(Command command);

   private:
    bool Running_{false};
    std::deque<Command> CommandQueue_;
    std::thread CommandThread_;
    std::mutex CommandMutex_;
    std::condition_variable CommandCondition_;
};












namespace name {
class InputManager {
   public:
    enum class EventType { MOUSE, KEYBOARD, GAMEPAD };

    // 1) пример создания логики callback через указатель на функцию
    //  using EventCallback = void (*)(const std::string&);

    // 2) пример создания логики callback через std::function, где  <void - возвращаемый тип (const
    // std::string&) - аргумент функции>
    using EventCallback = std::function<void(const std::string&)>;

    // Register the callback for the specified event
    void RegisterCallback(EventType event, EventCallback callback);

    // Call all registered callbacks for the event type
    void DispatchMessage(EventType type, const std::string& data);

   private:
    std::unordered_map<EventType, std::vector<EventCallback>> Callbacks_{};
};

;

}  // namespace name