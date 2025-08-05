module;

#include <cmath>
#include <compare>
#include <iostream>

export module vector3;

export namespace vector3 {

struct Vector3 {
    float x{0};
    float y{0};
    float z{0};

    // Конструктор
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    float magnitude() const { return std::sqrt(x * x + y * y + z * z); }

    // Оператор сложения с присваиванием (изменяет текущий объект)
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Оператор сложения
    Vector3 operator+(const Vector3& other) const { return Vector3(*this) += other; }

    // Оператор вычитания
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Оператор умножения на скаляр
    Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }

    // Оператор сравнения <=> (spaceship operator)
    // 1) вариант когда сравниваются объекты типа Vector3, удобно делать через std::tie
    // std::partial_ordering operator<=>(const Vector3& rhs) const {
    //     return (std::tie(x, y, z) <=> std::tie(rhs.x, rhs.y, rhs.z));
    // }

    // 2) вариант когда сравниваются объекты типа float, например магнитуды векторов
    std::partial_ordering operator<=>(const Vector3& rhs) const {
        return (magnitude() <=> rhs.magnitude());
    }

    // Оператор сравнения ==
    bool operator==(const Vector3& rhs) const {
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    }
};

// Т.к. для оператора << lhd это будет std::ostream, то нужно будет перегрузить его ВНЕ класса
// Vector3
std::ostream& operator<<(std::ostream& os, const vector3::Vector3& vec) {
    os << "Vector3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
}  // namespace vector3