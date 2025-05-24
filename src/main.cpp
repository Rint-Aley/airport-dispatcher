#include <iostream>
#include "Game.h"
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Game Menu", sf::Style::Close);
    window.setFramerateLimit(60);

    Menu menu(window);
    const auto onClose = [&window](const sf::Event::Closed &) {
        window.close();
    };

    const auto onTextEntered = [&menu](const sf::Event::TextEntered &event) {
        menu.handleTextInput(event.unicode);
    };

    const auto onLeftMousePressed = [&menu](const sf::Event::MouseButtonPressed &event) {
        menu.handleStatsButtonClick();
        menu.handleLevelsButtonClick();
        menu.handlePlayerBoxClick();
        menu.handlePopupButtonsClick();
    };

    while (window.isOpen()) {
        window.handleEvents(onClose, onTextEntered, onLeftMousePressed);
        menu.handleMouseOn();

        window.clear(sf::Color(30, 30, 45));
        menu.draw();
        window.display();
    }

    int selectedLevel = menu.getSelectedLevel();
    std::string name = menu.getPlayerNickname();
    if (selectedLevel != -1) {
        std::cout << "Level " << selectedLevel + 1 << " selected by "
                  << name << std::endl;
    }

    if(selectedLevel != -1){
        Game game;
        game.launch_game();
    }

    return 0;
}
