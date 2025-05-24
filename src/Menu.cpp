#include "Menu.h"

Menu::Menu(sf::RenderWindow &win) : window(win),
                                    font("../assets/fonts/JetBrainsMono-VariableFont_wght.ttf"),
                                    title(font, "Main Menu"), statsButton(font, "Statistics"),
                                    nicknameText(font, ""), playerNickname(""),
                                    levelSelectedPopup(win, font), state(States::MAIN_MENU) {
    // Main menu
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition({win.getSize().x / 2 - title.getGlobalBounds().size.x / 2, 50});

    // Stats button
    statsButton.setCharacterSize(30);
    statsButton.setFillColor(sf::Color::White);
    statsButton.setPosition({20, static_cast<float>(win.getSize().y - 50)});

    nicknameBox.setSize(sf::Vector2f(200, 30));
    nicknameBox.setFillColor(sf::Color::Transparent);
    nicknameBox.setOutlineThickness(2);
    nicknameBox.setOutlineColor(sf::Color::White);
    nicknameBox.setPosition({static_cast<float>(win.getSize().x - 210), 20});

    nicknameText.setCharacterSize(20);
    nicknameText.setFillColor(sf::Color::White);
    nicknameText.setPosition({static_cast<float>(win.getSize().x - 205), 20});


    levelNames = {"Level1", "Level2", "Level3", "Level4", "Level4"};
    for (size_t i = 0; i < levelNames.size(); ++i) {
        sf::Text button(font, levelNames[i]);
        button.setCharacterSize(30);
        button.setFillColor(sf::Color::White);

        float xPos = win.getSize().x / 2 - button.getGlobalBounds().size.x / 2;
        float yPos = 150 + i * 60;
        button.setPosition({xPos, yPos});
        levelButtons.push_back(button);
    }
}

void Menu::draw() {

//    levelSelectedPopup.show();
//    levelSelectedPopup.draw(window);

    if (state == States::STATISTIC) {
        drawStatistics();
        window.draw(statsButton);
    } else if (state == States::MAIN_MENU || state == States::TYPING_NICKNAME) {
        window.draw(title);
        for (auto &button: levelButtons) {
            window.draw(button);
        }
        window.draw(nicknameBox);
        window.draw(nicknameText);
        window.draw(statsButton);
    } else if (state == States::POPUP) {
        levelSelectedPopup.draw(window, playerNickname.empty(), selectedLevel);
    }
}

void Menu::drawStatistics() {
    sf::Text statsTitle(font, "Game Statistics");
    statsTitle.setCharacterSize(40);
    statsTitle.setFillColor(sf::Color::White);
    statsTitle.setPosition({window.getSize().x / 2 - statsTitle.getGlobalBounds().size.x / 2, 50});
    window.draw(statsTitle);

    sf::Text statsText(font, "Player:  Total score: 1450\n");
    statsText.setCharacterSize(25);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition({150, 130});
    window.draw(statsText);
}

void Menu::handleMouseOn() {
    handleLevelsButtonMouseOn();
    handleStatsButtonMouseOn();
    handlePlayerBoxOn();
}

void Menu::handleStatsButtonMouseOn() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    auto mouseOnColor = state != States::STATISTIC ? sf::Color::Yellow : sf::Color::White;
    auto mouseOutColor = (state == States::STATISTIC) ? sf::Color::Yellow : sf::Color::White;
    if (statsButton.getGlobalBounds().contains(mousePos)) {
        statsButton.setFillColor(mouseOnColor);
    } else {
        statsButton.setFillColor(mouseOutColor);
    }
}

void Menu::handleStatsButtonClick() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (statsButton.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
        if (state == States::MAIN_MENU)
            state = States::STATISTIC;
        else if (state == States::STATISTIC)
            state = States::MAIN_MENU;
    }
}

void Menu::handleLevelsButtonMouseOn() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (size_t i = 0; i < levelButtons.size(); ++i) {
        if (levelButtons[i].getGlobalBounds().contains(mousePos)) {
            levelButtons[i].setFillColor(sf::Color::Yellow);
        } else {
            levelButtons[i].setFillColor(sf::Color::White);
        }
    }
}


void Menu::handleLevelsButtonClick() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (size_t i = 0; i < levelButtons.size(); ++i) {
        if (levelButtons[i].getGlobalBounds().contains(mousePos)) {
            levelButtons[i].setFillColor(sf::Color::Yellow);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                state = States::POPUP;
                selectedLevel = i;
            }
        } else {
            levelButtons[i].setFillColor(sf::Color::White);
        }
    }
}


void Menu::handlePlayerBoxOn() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (nicknameBox.getGlobalBounds().contains(mousePos) || state == States::TYPING_NICKNAME) {
        nicknameBox.setOutlineColor(sf::Color::Yellow);
    } else {
        nicknameBox.setOutlineColor(sf::Color::White);
    }
}

void Menu::handlePlayerBoxClick() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (nicknameBox.getGlobalBounds().contains(mousePos)) {
        state = States::TYPING_NICKNAME;
        if (playerNickname == "Player") {
            playerNickname = "";
            nicknameText.setString("");
        }
    } else {
        if (state == States::TYPING_NICKNAME)
            state = States::MAIN_MENU;
    }
}

void Menu::handlePopupButtonsClick() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if(levelSelectedPopup.closeButtonClick(mousePos)){
        selectedLevel = -1;
        state = States::MAIN_MENU;
    }
    if(levelSelectedPopup.startButtonClick(mousePos) && selectedLevel != -1){
        window.close();
    }
}

void Menu::handleTextInput(char32_t symb) {
    if (state != States::TYPING_NICKNAME) {
        return;
    }
    if (symb < 128) {
        if (symb == '\b') {
            if (!playerNickname.empty()) {
                playerNickname.pop_back();
            }
        } else if (symb == '\r') {
            state = States::MAIN_MENU;
            if (playerNickname.empty()) {
                playerNickname = "Player";
            }
        } else if (playerNickname.size() < 15) {
            playerNickname += static_cast<char>(symb);
        }
        nicknameText.setString(playerNickname);
    }
}

int Menu::getSelectedLevel() const {
    return selectedLevel;
}

std::string Menu::getPlayerNickname() const {
    return playerNickname;
}

Menu::PopupWindow::PopupWindow(sf::RenderWindow &window, sf::Font &font) : message(font, ""),
                                                                           closeButton(font, "Close"),
                                                                           startButton(font, "Start") {
    // Затемненный фон
    background.setSize(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(30, 30, 45, 150)); // Полупрозрачный черный

    // Само popup-окно
    popup.setSize(sf::Vector2f(600, 400));
    popup.setFillColor(sf::Color(70, 70, 70));
    popup.setOutlineThickness(2);
    popup.setOutlineColor(sf::Color::White);
    popup.setPosition({100, 100});

    // Текст сообщения
    message.setCharacterSize(24);
    message.setFillColor(sf::Color::White);
    message.setPosition({popup.getPosition().x + 20, popup.getPosition().y + 30});

    // Кнопка закрытия
    closeButton.setCharacterSize(30);
    closeButton.setFillColor(sf::Color::White);
    closeButton.setPosition({popup.getPosition().x + closeButton.getGlobalBounds().size.x,
                             popup.getPosition().y + popup.getSize().y - 40});

    startButton.setCharacterSize(30);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(
            {popup.getPosition().x + popup.getGlobalBounds().size.x - 2 * startButton.getGlobalBounds().size.x,
             popup.getPosition().y + popup.getSize().y - 40});
}

void Menu::PopupWindow::draw(sf::RenderWindow &window, bool isNickNameIsEmpty, int& level) {
    window.draw(background);
    window.draw(popup);
    if(isNickNameIsEmpty){
        level=-1;
        message.setString("Nickname is empty, please enter your name");
        window.draw(message);
        window.draw(closeButton);
    }else{
        message.setString("Level " +std::to_string(level+1)+ " is chosen. Do you want to play?");
        window.draw(message);
        window.draw(closeButton);
        window.draw(startButton);
    }
}


bool Menu::PopupWindow::closeButtonClick(sf::Vector2f mousePos) {
    return closeButton.getGlobalBounds().contains(mousePos);
}

bool Menu::PopupWindow::startButtonClick(sf::Vector2f mousePos) {
    return startButton.getGlobalBounds().contains(mousePos);
}

