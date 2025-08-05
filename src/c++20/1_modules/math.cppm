
export module math;  // объявляем, что данный файл определяет интерфейс модуля с именем math

namespace math {


export int add(int a, int b)  // export делает функцию add видимой для других файлов, которые будут
                              // импортировать модуль math.
{
    return a + b;
}

}  // namespace math

/*
Компиляция кода с модулями отличается от обычной. Это двухэтапный процесс: сначала нужно
скомпилировать интерфейс модуля, а затем уже основную программу, связав ее с модулем.


Вот как это сделать с помощью GCC (g++) (версии 11+):

bash
# Шаг 1: Скомпилировать интерфейс модуля 'math'.
# Эта команда создаст math.o и файл с информацией о модуле (например, gcm.cache/math.gcm)
g++ -std=c++20 -fmodules-ts -c src/c++20/math.cppm

# Шаг 2: Скомпилировать основную программу и слинковать ее с объектным файлом модуля.
# Компилятор сам найдет нужный gcm-файл.
g++ -std=c++20 -fmodules-ts src/c++20/main.cppm math.o -o my_program



А вот так с помощью Clang (clang++) (версии 12+):

bash
# Шаг 1: Предварительно скомпилировать интерфейс модуля 'math' в файл .pcm (pre-compiled module)
clang++ -std=c++20 --precompile -x c++-module src/c++20/math.cppm -o math.pcm

# Шаг 2: Скомпилировать основную программу, указав путь к .pcm файлу
clang++ -std=c++20 -fprebuilt-module-path=. src/c++20/main.cppm math.pcm -o my_program
*/
