#include "DrawContext.h"

namespace CMPUT350 {

DrawContext::DrawContext(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font)
    : mWindow(window), mFont(font) {}

void DrawContext::DrawCenteredText(const std::string &text, int pixelSize, Point2D p, RGBColor c) {
    // https://stackoverflow.com/questions/27806077/sfml-drawing-centered-text#comment44029433_27806198
    sf::Text textstring(*mFont);
    textstring.setString(text);
    textstring.setCharacterSize(pixelSize);
    textstring.setFillColor(sf::Color::Color(c.r, c.g, c.b));
    textstring.setPosition({p.x - textstring.getGlobalBounds().size.x / 2, p.y});
    mWindow->draw(textstring);
}

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
    circle.setOrigin({radius, radius});
    circle.setPosition({p.x, p.y});
    mWindow->draw(circle);
}

void DrawContext::DrawRect(Rect r, RGBColor c) {
    sf::RectangleShape rectangle({r.width, r.height});
    rectangle.setFillColor(sf::Color::Color(c.r, c.g, c.b));
    rectangle.setPosition({r.topLeft.x, r.topLeft.y});
    mWindow->draw(rectangle);
}

void DrawContext::FrameRect(Rect r, float width, RGBColor c) {
    sf::RectangleShape rectangle({r.width, r.height});
    rectangle.setOutlineColor(sf::Color::Color(c.r, c.g, c.b));
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
    line.setFillColor(sf::Color::Color(c.r, c.g, c.b));
    mWindow->draw(line);
}

int DrawContext::GetWindowWidth() { return mWindow->getSize().x; }

int DrawContext::GetWindowHeight() { return mWindow->getSize().y; }

}  // namespace CMPUT350
