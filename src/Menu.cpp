#include "Menu.h"
#include "LevelProducer.h"

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

    auto levelsNames = LevelProducer::instance().list_levels();
    for (int i = 0; i < levelsNames.size(); ++i) {
        auto [roadsCount, planesCount] = LevelProducer::instance().get_level_info(levelsNames[i]);
        levels.push_back({levelsNames[i], roadsCount, planesCount});
    }
    for (size_t i = 0; i < levelsNames.size(); ++i) {
        sf::Text button(font, levelsNames[i]);
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
        levelSelectedPopup.draw(window, playerNickname.empty(), selectedLevel, levels);
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
    if (levelSelectedPopup.closeButtonClick(mousePos)) {
        selectedLevel = -1;
        state = States::MAIN_MENU;
    }
    if (levelSelectedPopup.startButtonClick(mousePos) && selectedLevel != -1) {
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

std::string Menu::getSelectedLevel() const {
    return selectedLevel == -1 ? "" : levels[selectedLevel].name;
}

std::string Menu::getPlayerNickname() const {
    return playerNickname;
}

Menu::PopupWindow::PopupWindow(sf::RenderWindow &window, sf::Font &font) : message(font, ""), continueAgreement(font),
                                                                           closeButton(font, "Close"),
                                                                           startButton(font, "Start"), roadsCount(font),
                                                                           planesCount(font) {
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

    // Текст сообщения
    continueAgreement.setString("Do you want to continue?");
    continueAgreement.setCharacterSize(24);
    continueAgreement.setFillColor(sf::Color::White);
    continueAgreement.setPosition(
            {popup.getPosition().x + popup.getSize().x / 2 - continueAgreement.getGlobalBounds().size.x/2,
             popup.getPosition().y + popup.getSize().y - 120});

    // Информация об уровне
    roadsCount.setCharacterSize(24);
    roadsCount.setFillColor(sf::Color::White);
    roadsCount.setPosition({popup.getPosition().x + 20, popup.getPosition().y + 90});

    planesCount.setCharacterSize(24);
    planesCount.setFillColor(sf::Color::White);
    planesCount.setPosition({popup.getPosition().x + 20, popup.getPosition().y + 120});

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

void
Menu::PopupWindow::draw(sf::RenderWindow &window, bool NickNameIsEmpty, int &level, std::vector<LevelInfo> &levels) {
    window.draw(background);
    window.draw(popup);
    if (NickNameIsEmpty) {
        message.setString("Nickname is empty, please enter your name");
        window.draw(message);
        window.draw(closeButton);
    } else {
        message.setString("Level " + levels[level].name + " is chosen.");
        roadsCount.setString("Number of roads: " + std::to_string(levels[level].roadsCount));
        window.draw(roadsCount);
        planesCount.setString("Number of planes: " + std::to_string(levels[level].planesCount));
        window.draw(planesCount);
        window.draw(message);
        window.draw(continueAgreement);
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

