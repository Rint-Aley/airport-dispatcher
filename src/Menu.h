#ifndef AIRPORT_SIMULATOR_MENU_H
#define AIRPORT_SIMULATOR_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

class Menu {
private:
    sf::RenderWindow &window;
    sf::Font font;

    // кнопки
    std::vector<sf::Text> levelButtons;
    std::vector<std::string> levelNames;
    sf::Text title;
    sf::Text statsButton;
    sf::RectangleShape nicknameBox;
    sf::Text nicknameText;

    // состояния
    int selectedLevel = -1;
    bool showStats = false;
    std::string playerNickname;
    bool typingNickname = false;

public:
    Menu(sf::RenderWindow &win);

    void draw();

    void drawStatistics();

    void handleMouseOn();

    void handlePlayerBoxOn();

    void handlePlayerBoxClick();

    void handleLevelsButtonMouseOn();

    void handleLevelsButtonClick();


    void handleStatsButtonMouseOn();

    void handleStatsButtonClick();


    void handleTextInput(char32_t symb);

    int getSelectedLevel() const;

    std::string getPlayerNickname() const;
};


#endif