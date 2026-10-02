#include "DrawContext.h"

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

/**
 * @brief Draws centered text.
 *
 * @param text: Text string to be printed.
 * @param pixelSize: Font size to be printed as.
 * @param p: Position to set the text.
 * @param c: Color to set the text.
 */
void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    // https://stackoverflow.com/questions/27806077/sfml-drawing-centered-text#comment44029433_27806198
    sf::Text textstring(*mFont);
    textstring.setString(text);
    textstring.setCharacterSize(pixelSize);
    textstring.setFillColor(sf::Color(c.r, c.g, c.b));
    textstring.setPosition({p.x - textstring.getGlobalBounds().size.x / 2, p.y});
    mWindow->draw(textstring);
}

/**
 * @brief Draws (non-centered) text.
 *
 * @param text: Text string to be printed.
 * @param pixelSize: Font size to be printed as.
 * @param p: Position to set the text.
 * @param c: Color to set the text.
 */
void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text textstring(*mFont);
    textstring.setString(text);
    textstring.setCharacterSize(pixelSize);
    textstring.setFillColor(sf::Color(c.r, c.g, c.b));
    textstring.setPosition({p.x, p.y});
    mWindow->draw(textstring);
}

/**
 * @brief Draws a circle.
 *
 * @param p: Center point of the circle.
 * @param radius: Radius of the circle.
 * @param c: Color of the circle to be drawn.
 */
void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(c.r, c.g, c.b));
    circle.setOrigin({radius, radius});
    circle.setPosition({p.x, p.y});
    mWindow->draw(circle);
}

/**
 * @brief Draws a rectangle.
 *
 * @param r: Rectangle object to be drawn.
 * @param c: Color of the rectangle to be drawn.
 */
void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rectangle({r.width, r.height});
    rectangle.setFillColor(sf::Color(c.r, c.g, c.b));
    rectangle.setPosition({r.topLeft.x, r.topLeft.y});
    mWindow->draw(rectangle);
}

/**
 * @brief Draws the outline of a rectangle.
 *
 * @param r: Rectangle object to be drawn.
 * @param width: Width of the outline to be drawn.
 * @param c: Color of the outline to be drawn.
 */
void DrawContext::FrameRect(Rect r, float width, RGBColor c) {
    sf::RectangleShape rectangle({r.width, r.height});
    rectangle.setOutlineColor(sf::Color(c.r, c.g, c.b));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(width);
    rectangle.setPosition({r.topLeft.x, r.topLeft.y});
    mWindow->draw(rectangle);
}

/**
 * @brief Draws a line between two points with a specified width and color.
 *
 * @param from The starting point of the line (Point2D).
 * @param to The ending point of the line (Point2D).
 * @param width The width of the line in pixels.
 * @param c The color of the line, specified as an RGBColor object.
 *
 * This function calculates the distance and angle between the two points
 * and uses a polygone shape to represent the line. The line is drawn
 * relative to the world offset and rendered onto the associated window.
 */
void DrawContext::DrawLine(Point2D from, Point2D to, float width, RGBColor c) {
    float length = Line(from, to).Length();
    float fromx_1 = from.x - (width / 2) * ((to.y - from.y) / length);
    float fromy_1 = from.y + (width / 2) * ((to.x - from.x) / length);
    float fromx_2 = from.x + (width / 2) * ((to.y - from.y) / length);
    float fromy_2 = from.y - (width / 2) * ((to.x - from.x) / length);
    float tox_1 = to.x - (width / 2) * ((to.y - from.y) / length);
    float toy_1 = to.y + (width / 2) * ((to.x - from.x) / length);
    float tox_2 = to.x + (width / 2) * ((to.y - from.y) / length);
    float toy_2 = to.y - (width / 2) * ((to.x - from.x) / length);
    sf::ConvexShape line;
    line.setPointCount(4);
    line.setPoint(0, {fromx_1, fromy_1});
    line.setPoint(1, {tox_1, toy_1});
    line.setPoint(2, {tox_2, toy_2});
    line.setPoint(3, {fromx_2, fromy_2});
    line.setFillColor(sf::Color(c.r, c.g, c.b));
    mWindow->draw(line);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

/**
 * @brief Sets all drawing offset.
 *
 * @param p Point2D containing x and y of offset.
 *
 * Sets offset for all drawing commands. 
 */
void DrawContext::SetContextOffset(Point2D p) { contextOffset = p; }

/**
 * @brief Sets all rotation.
 *
 * @param rotation Amount of rotation.
 *
 * Sets rotation for all drawing commands.
 */
void DrawContext::SetContextRotation(float rotation) { contextRotation = rotation; }

/**
 * @brief Transforms a point from object space to screen space. 
 *
 * @param p Point2D to transform from its local object space back to screen space.
 *
 * @return Point2D of point in screen space
 */
Point2D DrawContext::Transform(Point2D p) const { return p + contextOffset; }

/**
 * @brief Transforms a point from screen space to object space.
 *
 * @param p Point2D to transform from its screen space back into local object space.
 *
 * @return Point2D of point in local object space
 */
Point2D DrawContext::ReverseTransform(Point2D p) const { return p - contextOffset; } //"multiplying by the inverted transform matrix"??

/**
 * @brief Rotates rectangle (changes topLeft) and computes new bounding box after rotation
 *
 * @param r Rectangle to rotate.
 *
 * @return Rectangle of bounding box after rotation.
 */
Rect DrawContext::Transform(Rect r) const {
    float point1Radius = r.topLeft.Distance({0, 0});
    Point2D newTopLeft = 
        {std::cos((std::acos(r.topLeft.x / point1Radius)) + contextRotation) * point1Radius,
        std::sin((std::asin(r.topLeft.y / point1Radius)) + contextRotation) * point1Radius};
    r.topLeft = newTopLeft;
    float point2Radius = (r.topLeft + r.width).Distance({0, 0});
    Point2D newSecondPt = {
        std::cos((std::acos((r.topLeft + r.width).x / point2Radius)) + contextRotation) *
            point2Radius,
        std::sin((std::asin((r.topLeft + r.width).y / point2Radius)) + contextRotation) *
            point2Radius};
    float point3Radius = (r.topLeft + r.height).Distance({0, 0});
    Point2D newThirdPt = {
        std::cos((std::acos((r.topLeft + r.height).x / point3Radius)) + contextRotation) *
            point3Radius,
        std::sin((std::asin((r.topLeft + r.height).y / point3Radius)) + contextRotation) *
            point3Radius};
    float point4Radius = (r.topLeft + r.width + r.height).Distance({0, 0});
    Point2D newFourthPt = {
        std::cos((std::acos((r.topLeft + r.width + r.height).x / point4Radius)) + contextRotation) *
            point4Radius,
        std::sin((std::asin((r.topLeft + r.width + r.height).y / point4Radius)) + contextRotation) *
            point4Radius};

    Rect boundingBox;
    boundingBox.topLeft.x = std::min({r.topLeft.x, newSecondPt.x, newThirdPt.x, newFourthPt.x});
    boundingBox.topLeft.y = std::min({r.topLeft.y, newSecondPt.y, newThirdPt.y, newFourthPt.y});
    boundingBox.width =
        std::max({r.topLeft.x, newSecondPt.x, newThirdPt.x, newFourthPt.x}) - boundingBox.topLeft.x;
    boundingBox.height =
        std::max({r.topLeft.y, newSecondPt.y, newThirdPt.y, newFourthPt.y}) - boundingBox.topLeft.y;
    return boundingBox;
}

}  // namespace CMPUT350
