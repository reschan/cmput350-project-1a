#include "DrawContext.h"

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {}

void DrawContext::DrawText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    sf::Text textstring(*mFont);
    textstring.setString(text);
    textstring.setCharacterSize(pixelSize);
    textstring.setFillColor(sf::Color::Color(c.r, c.g, c.b));
    textstring.setPosition({p.x, p.y});
    mWindow->draw(textstring);
}

void DrawContext::DrawCircle(Point2D p, float radius, RGBColor c) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Color(c.r, c.g, c.b));
    circle.setPosition({p.x, p.y});
    mWindow->draw(circle);
}

void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rectangle({r.width, r.height});
    rectangle.setFillColor(sf::Color::Color(c.r, c.g, c.b));
    rectangle.setPosition({r.topLeft.x, r.topLeft.y});
    mWindow->draw(rectangle);
}

void DrawContext::FrameRect(Rect r, float width, RGBColor c) {}

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
    sf::ConvexShape line;
    line.setPointCount(2);
    line.setPoint(0, {from.x, from.y});
    line.setPoint(1, {to.x, to.y});
    line.setOutlineThickness(width);
    line.setFillColor(sf::Color::Color(c.r, c.g, c.b));
    line.setPosition({from.x, from.y});
    mWindow->draw(line);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

}  // namespace CMPUT350
