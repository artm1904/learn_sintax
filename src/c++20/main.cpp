#include <iostream>

import math; // Импортируем наш собственный модуль

int main()
{
    std::cout << "Hello, Modules!" << std::endl;
    std::cout << "2 + 3 = " << math::add(2, 3) << std::endl; //math::  это именно namespace, а не модуль
    return 0;
}