#include "RadioButtonGroup.h"
#include <stdexcept>

RadioButtonGroup::RadioButtonGroup() {
    if (!font.openFromFile("../assets/fonts/JetBrainsMono-VariableFont_wght.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
}

void RadioButtonGroup::add_button(const std::string& label, const sf::Vector2f& size) {
    Button new_button(font);
    new_button.shape.setSize(size);
    new_button.text.setString(label);

    buttons.push_back(new_button);
}

void RadioButtonGroup::update_positions(const sf::Vector2u& window_size) {
    float total_height = 0.f;
    for (const auto& button : buttons) {
        total_height += button.shape.getSize().y + padding;
    }

    float y_pos = padding; // Start from top with padding
    for (auto& button : buttons) {
        button.shape.setPosition(sf::Vector2f(
            window_size.x - button.shape.getSize().x - padding, // Right side
            y_pos
        ));

        // Center text in button
        sf::FloatRect text_rect = button.text.getLocalBounds();
        button.text.setOrigin(text_rect.position + text_rect.size / 2.0f);
        button.text.setPosition(button.shape.getPosition() + button.shape.getSize() / 2.0f);

        y_pos += button.shape.getSize().y + padding;
    }
}

void RadioButtonGroup::handle_event(const sf::Event& event, const sf::RenderWindow& window) {
    if (const auto* mouse_click = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouse_click->button == sf::Mouse::Button::Left) {
            sf::Vector2f mouse_pos = window.mapPixelToCoords(mouse_click->position);
            for (size_t i = 0; i < buttons.size(); ++i) {
                if (buttons[i].shape.getGlobalBounds().contains(mouse_pos)) {
                    // If this button was already selected, deselect it
                    if (selected_index == static_cast<int>(i)) {
                        selected_index = -1;
                        buttons[i].is_pressed = false;
                        buttons[i].shape.setFillColor(sf::Color(200, 200, 200));
                    }
                    else {
                        // Deselect previously selected button
                        if (selected_index != -1) {
                            buttons[selected_index].is_pressed = false;
                            buttons[selected_index].shape.setFillColor(sf::Color(200, 200, 200));
                        }

                        // Select new button
                        selected_index = static_cast<int>(i);
                        buttons[i].is_pressed = true;
                        buttons[i].shape.setFillColor(sf::Color(150, 150, 250));
                    }
                    break;
                }
            }
        }
    }
}

void RadioButtonGroup::draw(sf::RenderTarget& target) const {
    for (const auto& button : buttons) {
        target.draw(button.shape);
        target.draw(button.text);
    }
}

int RadioButtonGroup::get_selected_index() const {
    return selected_index;
}

void RadioButtonGroup::reset_selection() {
    if (selected_index != -1) {
        buttons[selected_index].is_pressed = false;
        buttons[selected_index].shape.setFillColor(sf::Color(200, 200, 200));
        selected_index = -1;
    }
}

void RadioButtonGroup::delete_button(size_t index)
{
    buttons.erase(buttons.begin() + index);
}
