#ifndef AIRPORT_SIMULATOR_MENU_H
#define AIRPORT_SIMULATOR_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>


class Menu {
private:
    class PopupWindow {
    private:
        sf::RectangleShape background;
        sf::RectangleShape popup;
        sf::Text message;
        sf::Text closeButton;
        sf::Text startButton;

    public:
        PopupWindow(sf::RenderWindow &window, sf::Font &font);

        void draw(sf::RenderWindow &window,  bool isNickNameIsEmpty, int& level);

        bool closeButtonClick(sf::Vector2f mousePos);

        bool startButtonClick(sf::Vector2f mousePos);
    };

    sf::RenderWindow &window;
    sf::Font font;

    // кнопки
    std::vector<sf::Text> levelButtons;
    std::vector<std::string> levelNames;
    sf::Text title;
    sf::Text statsButton;
    sf::RectangleShape nicknameBox;
    sf::Text nicknameText;

    PopupWindow levelSelectedPopup;

    // состояния
    int selectedLevel = -1;
    std::string playerNickname;

    enum class States {
        MAIN_MENU,
        STATISTIC,
        TYPING_NICKNAME,
        POPUP,
    };
    States state;
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


    void handlePopupButtonsClick();

    void handleTextInput(char32_t symb);

    int getSelectedLevel() const;

    std::string getPlayerNickname() const;
};


#endif