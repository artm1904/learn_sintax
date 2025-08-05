#include <iostream>

import vector3;

int main() {
    vector3::Vector3 v1(1.0f, 2.0f, 3.0f);
    vector3::Vector3 v2(4.0f, 5.0f, 6.0f);

    

    auto v3 = v1 + v2;    // Сложение векторов
    auto v4 = v1 - v2;    // Вычитание векторов
    auto v5 = v1 * 2.0f;  // Умножение вектора на скаляр

    std::cout << v1 << ")\n";
    std::cout << v2 << ")\n";
    std::cout << v3 << ")\n";
    std::cout << v4 << ")\n";
    std::cout << v5 << ")\n";

    // Сравнение векторов
    if (v1 < v2) {
        std::cout << "v1 is less than v2 based on magnitude.\n";
    } else if (v1 > v2) {
        std::cout << "v1 is greater than v2 based on magnitude.\n";
    } else {
        std::cout << "v1 is equal to v2 based on magnitude.\n";
    }

    return 0;
}
