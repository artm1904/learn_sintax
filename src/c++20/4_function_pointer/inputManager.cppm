module;

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

export module inputManager;

export namespace name {
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

void printHello();

}  // namespace name