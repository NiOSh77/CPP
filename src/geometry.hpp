#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <typename ElementType, size_t Dimension>
class Point
{
private:
public:
    std::array<ElementType, Dimension> values;

    Point()
    {
    }

    template <typename... Args>
    Point(ElementType type, Args &&...args)
        : values{type, static_cast<ElementType>(std::forward<Args>(args))...}
    {
        static_assert(Dimension - 1 == sizeof...(args));
    }

    Point &operator+=(const Point &other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), [](ElementType x1, ElementType x2) { return x1 + x2; });
        return *this;
    }

    Point &operator*=(const Point &other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), [](ElementType x1, ElementType x2) { return x1 * x2; });
        return *this;
    }

    Point &operator*=(const ElementType scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(), [scalar](ElementType x) { return x * scalar; });
        return *this;
    }

    Point &operator-=(const Point &other)
    {
        std::transform(values.begin(), values.end(), other.values.begin(), values.begin(), [](ElementType x1, ElementType x2) { return x1 - x2; });
        return *this;
    }

    Point operator-() const
    {
        Point result = *this;
        std::transform(values.begin(), values.end(), result.values.begin(), [](ElementType type) { return type = -type; });
        return result;
    }

    Point operator+(const Point &other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator*(const Point &other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator-(const Point &other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const ElementType scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    ElementType &x()
    {
        static_assert(Dimension >= 1);
        return values[0];
    }

    ElementType &y()
    {
        static_assert(Dimension >= 2);
        return values[1];
    }

    ElementType &z()
    {
        static_assert(Dimension >= 3);
        return values[2];
    }

    ElementType x() const
    {
        static_assert(Dimension >= 1);
        return values[0];
    }

    ElementType y() const
    {
        static_assert(Dimension >= 2);
        return values[1];
    }

    ElementType z() const
    {
        static_assert(Dimension >= 3);
        return values[2];
    }

    float length() const
    {
        return std::sqrt(std::reduce(values.begin(), values.end(), 0.f, [](ElementType a, ElementType b) {
            return b * b + a;
        }));
    }

    float distance_to(const Point &other) const { return (*this - other).length(); }

    Point &normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point &cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    template <typename T, size_t U>
    friend std::ostream &operator<<(std::ostream &os, const Point<T, U> &values);
};

template <typename T, size_t U>
std::ostream &operator<<(std::ostream &os, const Point<T, U> &values)
{
    os << "[";
    auto separator = "";
    for (const auto &current : values.values)
    {
        os << separator << current;
        separator = ", ";
    }
    return os << "]";
}

using Point2D = Point<float, 2>;
using Point3D = Point<float, 3>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D &p)
{
    return {.5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z()};
}
