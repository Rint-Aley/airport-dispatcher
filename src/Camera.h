#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/RenderWindow.hpp>

class Camera {
    sf::RenderWindow& window;
    sf::View view;
    float current_zoom;

public:
    explicit Camera(sf::RenderWindow& window) : window(window), view(window.getDefaultView()), current_zoom(1) {}

    void set_center(const sf::Vector2f& center) {
        view.setCenter(center);
        window.setView(view);
    }

    void move(const sf::Vector2f& offset) {
        view.move(offset);
        window.setView(view);
    }

    void zoom(const float factor, const sf::Vector2i& coord) {
        const sf::Vector2f before = window.mapPixelToCoords(coord, view);

        current_zoom *= factor;
        view.zoom(factor);

        const sf::Vector2f after = window.mapPixelToCoords(coord, view);

        const sf::Vector2f offset = before - after;
        view.move(offset);

        window.setView(view);
    }

    void reset_zoom() {
        view = window.getDefaultView();
        current_zoom = 1;
        window.setView(view);
    }

    float get_zoom() const { return current_zoom; }
    const sf::View& get_view() const { return view; }
};

sf::Vector2f screen_to_world(const sf::Vector2i& screenPos, const sf::RenderWindow& window)
{
    return window.mapPixelToCoords(screenPos);
}

#endif
