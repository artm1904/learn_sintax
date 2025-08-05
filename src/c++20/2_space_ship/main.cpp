#include <compare>
#include <format>
#include <iostream>

/*
- Тут хорошо объяснено про <=> https://ru.stackoverflow.com/questions/1364882/О-работе-ракеты

Смысл оператора <=> (spaceship operator) в C++20 заключается в том, что он позволяет
автоматически генерировать операторы сравнения. Достаточно определить один оператор <=>,
и компилятор сам сгенерирует остальные операторы сравнения, такие как <, >, == и т.д.
Если тип не тривиальный, то нужно будет явно определить оператор <=>, а так же оператор ==.

- Если перегрузить <=> руками, то будут работать только 4: <, <=, >, >=. Перегрузить == нужно
отдельно, и тогда != начнет работать автоматически (это работает независимо от <=>).

1) Для типа int в C++20 был добавлен новый оператор сравнения <=>, который позволяет сравнивать
объекты и возвращать результат в виде std::strong_ordering. std::strong_ordering::less,
std::strong_ordering::equal и std::strong_ordering::greater представляют собой три возможных
результата сравнения, а так же позволяют использовать операторы <, >, == и т.д. для сравнения.

2) При работе с float и double будет тип std::partial_ordering, который также имеет три возможных
результата: std::partial_ordering::less, std::partial_ordering::equivalent и
std::partial_ordering::greater, а также std::partial_ordering::unordered, который
используется для обозначения случая, когда значения не могут быть упорядочены (например, NaN).
Это позволяет корректно обрабатывать случаи, когда значения не могут быть сравнимы
(например, NaN в случае с float и double).


3) Для строк и других типов, которые могут быть равны, но по сути это разные объекты,
используется std::weak_ordering. Он также имеет три возможных результата: std::weak_ordering::less,
std::weak_ordering::equivalent и std::weak_ordering::greater. Этот тип используется для
сравнения объектов, которые могут быть равны, но не идентичны, например, строки,
где сравнение может быть выполнено без учета регистра или других факторов.
*/

void print_int_compare1(std::strong_ordering ord) {
    if (ord == 0)
        std::cout << "equal\n";
    else if (ord < 0)
        std::cout << "less\n";
    else
        std::cout << "greater\n";
}

void print_int_compare2(std::strong_ordering ord) {
    if (ord == std::strong_ordering::equal)
        std::cout << "equal\n";
    else if (ord == std::strong_ordering::less)
        std::cout << "less\n";
    else
        std::cout << "greater\n";
}

int main() {
    int a = 5;
    int b = 10;

    std::cout << "Comparing " << a << " and " << b << ":\n";

    // Используем <=> для сравнения
    auto ord = a <=> b;

    // Печатаем результат сравнения
    print_int_compare2(ord);

    // Пример форматирования строки с использованием std::format
    std::string formatted =
        std::format("Formatted output: {} is {} than {}", a, (ord < 0 ? "less" : "greater"), b);
    std::cout << formatted << std::endl;

    return 0;
}