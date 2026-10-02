#include <span>
#include <cmath>

#include "Bezier.h"
#include "MathUtil.h"
#include <vector>
#include <span>

namespace CMPUT350 {

Bezier::Bezier(const std::vector<Point2D>& pts) : pts(pts) {}

Point2D Bezier::GetPoint(float t) const { return this->GetPoint(pts, t); }
Point2D Bezier::GetSlope(float t) const { return this->GetSlope(pts, t); }

Point2D Bezier::GetPoint(const std::vector<Point2D>& pts, float t) {
    float segCount = std::floor(pts.size() / 3);

    if (t > segCount || t < 0) { throw std::out_of_range("t out of range."); }
    if (pts.size() % 3 != 1) { throw std::exception("invalid number of point."); }

    std::span spanPts = std::span<const Point2D>(pts);
    if (t <= 1.0f) {
        spanPts = spanPts.subspan(0, 4);
    } else {
        spanPts = spanPts.subspan((int)3 * t, 4);
    }

    float xa = std::lerp(spanPts[0].x, spanPts[1].x, t);
    float ya = std::lerp(spanPts[0].y, spanPts[1].y, t);
    float xb = std::lerp(spanPts[1].x, spanPts[2].x, t);
    float yb = std::lerp(spanPts[1].y, spanPts[2].y, t);
    float xc = std::lerp(spanPts[2].x, spanPts[3].x, t);
    float yc = std::lerp(spanPts[2].y, spanPts[3].y, t);

    float xm = std::lerp(xa, xb, t);
    float ym = std::lerp(ya, yb, t);
    float xn = std::lerp(xb, xc, t);
    float yn = std::lerp(yb, yc, t);

    float x = std::lerp(xm, xn, t);
    float y = std::lerp(ym, yn, t);

    return Point2D(x, y);
}

Point2D Bezier::GetSlope(const std::vector<Point2D>& pts, float t) {
    float segCount = std::floor(pts.size() / 3);

    if (t > segCount || t < 0) {
        throw std::out_of_range("t out of range.");
    }
    if (pts.size() % 3 != 1) {
        throw std::runtime_error("invalid number of point.");
    }

    std::span spanPts = std::span<const Point2D>(pts);
    if (t <= 1.0f) {
        spanPts = spanPts.subspan(0, 4);
    } else {
        spanPts = spanPts.subspan((int)3 * t, 4);
    }

    return Point2D({3 * ((1 - t) * (1 - t) * (spanPts[1].x - spanPts[0].x) +
              2 * t * (spanPts[2].x - spanPts[1].x) + t * t * (spanPts[3].x - spanPts[2].x)),
         3 * ((1 - t) * (1 - t) * (spanPts[1].y - spanPts[0].y) +
              2 * t * (spanPts[2].y - spanPts[1].y) + t * t * (spanPts[3].y - spanPts[2].y))});
}

}

