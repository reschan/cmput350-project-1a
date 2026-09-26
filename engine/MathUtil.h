#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <cmath>
#include <iostream>
#include <algorithm>

namespace CMPUT350 {

struct Point2D {
    float x, y;
    Point2D(float x = 0, float y = 0) : x(x), y(y) {}
    /**
    * @brief Calculates distance between points
    * 
    * @param other The other point
    * @return Distance
    */
    double Distance(const Point2D &other) const {
        return std::sqrt((((other.x - x) * (other.x - x)) + ((other.y - y) * (other.y - y))));
    }
    /**
     * @brief Adds the two points' coordinates
     *
     * @param other The other point
     */
    Point2D operator+(const Point2D &other) const {
        return Point2D(this->x + other.x, this->y + other.y);
    }
    /**
     * @brief Adds a float to the point
     *
     * @param other Float to add to the point
     */
    Point2D operator+(const float &other) const {
        return Point2D(this->x + other, this->y + other);
    }
    /**
     * @brief Minus another point from self. 
     *
     * @param other The other point
     */
    Point2D operator-(const Point2D &other) const {
        return Point2D(this->x - other.x, this->y - other.y);
    }
    /**
     * @brief Minus a float from the point
     *
     * @param other Float to minus from the point
     */
    Point2D operator-(const float &other) const {
        return Point2D(this->x - other, this->y - other);
    }
    /**
     * @brief Multiplies a scalar with self
     *
     * @param scalar Scalar to multiply with the point
     */
    Point2D operator*(const float &scalar) const {
        return Point2D(this->x * scalar, this->y * scalar);
    }
    /**
     * @brief Adds a float to the point
     *
     * @param scalar Float to add with the point
     */
    Point2D &operator+=(const float &scalar) {
        this->x += scalar;
        this->y += scalar;
        return *this;
    }
    /**
     * @brief Adds another point to the point
     *
     * @param other Other point to add to the point
     */
    Point2D &operator+=(const Point2D &other) {
        if (*this != other) {
            this->x += other.x;
            this->y += other.y;
        }
        return *this;
    }
    /**
     * @brief Minus another point from self.
     *
     * @param other The other point
     */
    Point2D &operator-=(const Point2D &other) {
        if (*this != other) {
            this->x -= other.x;
            this->y -= other.y;
        }
        return *this;
    }
    /**
     * @brief Check if another point is equal to self
     *
     * @param other The other point
     * @return True/false depending if other point is equal to self
     */
    bool operator==(const Point2D &other) const {
        if (this->x == other.x && this->y == other.y) {
            return true;
        } else {
            return false;
        }
    }
    /**
     * @brief Multiplies a scalar with self
     *
     * @param scalar Scalar to multiply with the point
     */
    Point2D &operator*=(const int &scalar) {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }
    /**
     * @brief Divides a scalar with self
     *
     * @param scalar Scalar to divide with the point
     */
    Point2D &operator/=(const int &scalar) {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }
    // Below are unused functions
    float operator*(const Point2D& other) const {
        // TODO: write this code
        return 0;
    }
    float Dot(Point2D b) const {
        return (this->x * b.x)+(this->y * b.y);
    }
    static float Dot(Point2D a, Point2D b) {
        return (a.x*b.x)+(a.y*b.y);
    }
    static float Cross(Point2D a, Point2D b) {
        // https://allenchou.net/2013/07/cross-product-of-2d-vectors/
        return (a.x*b.y)-(a.y*b.x);
    }
    void Normalize() {
        // TODO: write this code
        float length = std::sqrt((this->x * this->x) + (this->y * this->y));
        *this /= length;
    }
};

/**
 * @brief Prints info about a point
 *
 * @param os Stream to print to 
 * @param p Point to print
 * @return Reference to printing stream
 */
static std::ostream &operator<<(std::ostream &os, const Point2D &p) {
    os << "Point: x: ";
    os << p.x;
    os << " y: ";
    os << p.y;
    return os;
}

// Unused function, assumed to be multiplying a Point2D and a float? 
static Point2D operator*(float number, const Point2D &rhs) {
    // TODO: write this code
    return rhs * number;
}

struct Line {
    Point2D p1, p2;

    Line(Point2D p1 = {0, 0}, Point2D p2 = {0, 0}) : p1(p1), p2(p2) {}
    Line(float x1, float y1, float x2, float y2) : p1(x1, y1), p2(x2, y2) {}

    /**
     * @brief Gets length of line
     *
     * @return Float of length of line
     */
    float Length() const {
        return this->p1.Distance(p2);
    }

    /**
     * @brief Gets closest point on line to given point
     *
     * @param p Point to find closest point on line to 
     * @return Point on line closest to given param
     */
    Point2D ClosestPoint(const Point2D &p) const {
        float point_x = (this->p2.x - this->p1.x) / Length(); 
        float point_y = (this->p2.y - this->p1.y) / Length(); 
        float p1p_length = ((p2 - p1).Dot(p - p1)) / Length();
        Point2D temp = (point_x, point_y);
        Point2D x = p1 + (temp*p1p_length);
        return x;
    }
    bool Crosses(Line other, Point2D &crossingPoint) const {
        // TODO: write this code
        return false;
    }
};

static std::ostream &operator<<(std::ostream &os, const Line &l) {
    // TODO: write this code
    return os;
}

struct Circle {
    Point2D center;
    float radius;

    Circle(Point2D c = {0, 0}, float r = 0) : center(c), radius(r) {}

    Circle(float x, float y, float r) : center(x, y), radius(r) {}
};

struct Rect {
    Point2D topLeft;
    float width, height;

    Rect(float left, float top, float width, float height)
        : topLeft(Point2D(left, top)), width(width), height(height) {}

    Rect(Point2D tl = {0, 0}, int w = 0, int h = 0) : topLeft(tl), width(w), height(h) {}

    // Creates bounding box around p1 and p2 with positive width/height
    Rect(Point2D p1, Point2D p2)
        : topLeft(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
          width(fabs(p1.x - p2.x)),
          height(fabs(p1.y - p2.y)) {}

    Rect(Point2D center, float radius)
        : topLeft(center.x - radius, center.y - radius), width(2 * radius), height(2 * radius) {}

    /**
     * @brief Modifies self to be smallest rectangle containing both self and other rectangle
     *
     * @param other Rectangle to contain within new self
     */
    Rect& operator|=(const Rect& other) {
        if (this->height <= 0 || this->width <= 0) {
            *this = other;
            return *this;
        } else if (other.height <= 0 || other.width <= 0) {
            return *this;
        }
        float temp_x = std::max(this->topLeft.x + this->width, other.topLeft.x + other.width);
        float temp_y = std::max(this->topLeft.y + this->height, other.topLeft.y + other.height);
        this->topLeft.x = std::min(this->topLeft.x, other.topLeft.x);
        this->topLeft.y = std::min(this->topLeft.y, other.topLeft.y);
        this->width = temp_x - this->topLeft.x;
        this->height = temp_y - this->topLeft.y;
        return *this;
    }

    /**
     * @brief Modifies self to be smallest rectangle containing both self and point
     *
     * @param other Point to contain within new self
     */
    Rect &operator|=(const Point2D &other) {
        if (this->height <= 0 || this->width <= 0) {
            this->topLeft.x = other.x;
            this->topLeft.y = other.y;
            this->width = 0;
            this->height = 0;
            return *this;
        } else if (other.x <= 0 || other.y <= 0) {
            return *this;
        }
        float temp_x = std::max(this->topLeft.x + this->width, other.x);
        float temp_y = std::max(this->topLeft.y + this->height, other.y);

        this->topLeft.x = std::min(this->topLeft.x, other.x);
        this->topLeft.y = std::min(this->topLeft.y, other.y);
        this->width = temp_x - this->topLeft.x;
        this->height = temp_y - this->topLeft.y;
        return *this;
    }

    /**
     * @brief Modifies self to be smallest rectangle containing both self and line
     *
     * @param other Line to contain within new self
     */
    Rect& operator|=(const Line& other) {
        this->topLeft.x = std::min({this->topLeft.x, other.p1.x, other.p2.x});
        this->topLeft.y = std::min({this->topLeft.y, other.p1.y, other.p2.y});
        this->width = std::max({this->width, other.p1.x, other.p2.x});
        this->height = std::max({this->height, other.p1.y, other.p2.y});
        return *this;
    }

    /**
     * @brief Modifies self to be the intersection between original self and other rectangle
     *
     * @param other Target rectangle
     */
    Rect &operator&=(const Rect &other) {
        if (this->height <= 0 || this->width <= 0) {
            this->width = 0;
            this->height = 0;
            return *this;
        } else if (other.height <= 0 || other.width <= 0) {
            this->width = 0;
            this->height = 0;
            return *this;
        }
        float temp_x = std::min(this->topLeft.x + this->width, other.topLeft.x + other.width);
        float temp_y = std::min(this->topLeft.y + this->height, other.topLeft.y + other.height);
        this->topLeft.x = std::max(this->topLeft.x, other.topLeft.x);
        this->topLeft.y = std::max(this->topLeft.y, other.topLeft.y);
        this->width = temp_x - this->topLeft.x;
        this->height = temp_y - this->topLeft.y;
        return *this;
    }
    Rect &operator+=(const Point2D &other) {
        // TODO: write this code
        return *this;
    }
    Rect operator+(const Point2D &other) const {
        // TODO: write this code
        return *this;
    }

    /**
     * @brief Shrinks self by input on every side 
     *
     * @param inset Amount to shrink self by 
     */
    void Inset(int inset) {
        this->width -= inset * 2;
        this->height -= inset * 2;
        this->topLeft.x += inset;
        this->topLeft.y += inset;
    }

    /**
     * @brief Check if a point is inside self
     *
     * @param p Point to check
     * @return True/false depending if point is within self. 
     */
    bool IsInside(const Point2D &p) const {
        if (this->topLeft.x < p.x && p.x < this->topLeft.x + width && this->topLeft.y < p.y && p.y < this->topLeft.y + height) {
            return true;
        } else {
            return false;
        }
    }
};

/**
 * @brief Prints info about a rectangle
 *
 * @param os Stream to print to
 * @param l Rectangle to print
 * @return Reference to printing stream
 */
static std::ostream &operator<<(std::ostream &os, const Rect &l) {
    os << "Rect x: ";
    os << l.topLeft.x;
    os << " y: ";
    os << l.topLeft.y;
    os << ", width: ";
    os << l.width;
    os << " height: ";
    os << l.height;
    return os;
}

}  // namespace CMPUT350

#endif  // MATHUTIL_H
