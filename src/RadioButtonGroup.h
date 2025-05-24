#ifndef RADIO_BUTTON_GROUP_H
#define RADIO_BUTTON_GROUP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class RadioButtonGroup {
public:
    RadioButtonGroup();
    void add_button(const std::string& label, const sf::Vector2f& size);
    void update_positions(const sf::Vector2u& window_size);
    void handle_event(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target) const;
    int get_selected_index() const;
    void reset_selection();
    void delete_button(size_t index);

private:
    struct Button {
        sf::RectangleShape shape;
        sf::Text text;
        bool is_pressed = false;
        Button(const sf::Font& font) : text(font, "", 16), is_pressed(false) {
            shape.setFillColor(sf::Color(200, 200, 200));
            shape.setOutlineThickness(1.f);
            shape.setOutlineColor(sf::Color::Black);
            text.setFillColor(sf::Color::Black);
        }
    };

    std::vector<Button> buttons;
    int selected_index = -1; // -1 means none selected
    sf::Font font;
    float padding = 5.f;
};

#endif