#include "Menu.h"

Menu::Menu(sf::RenderWindow &win) : window(win),
                                    font("../assets/fonts/JetBrainsMono-VariableFont_wght.ttf"),
                                    title(font, "Main Menu"), statsButton(font, "Statistics"),
                                    nicknameText(font, "Player"), playerNickname("Player") {
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
    nicknameBox.setPosition({static_cast<float>(win.getSize().x - 200), 20});

    nicknameText.setCharacterSize(20);
    nicknameText.setFillColor(sf::Color::White);
    nicknameText.setPosition({static_cast<float>(win.getSize().x - 195), 20});


    levelNames = {"Level1", "Level2", "Level3", "Level4"};
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
    window.draw(title);
    window.draw(statsButton);

    if (showStats) {
        drawStatistics();
    } else {
        for (auto &button: levelButtons) {
            window.draw(button);
        }
        window.draw(nicknameBox);
        window.draw(nicknameText);
    }
}

void Menu::drawStatistics() {
    sf::Text statsTitle(font, "Game Statistics");
    statsTitle.setCharacterSize(40);
    statsTitle.setFillColor(sf::Color::White);
    statsTitle.setPosition({window.getSize().x / 2 - statsTitle.getGlobalBounds().size.x / 2, 120});
    window.draw(statsTitle);

    sf::Text statsText(font, "Player: " + playerNickname + "Total score: 1450\n");
    statsText.setCharacterSize(25);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition({150, 200});
    window.draw(statsText);
}

void Menu::handleMouseOn() {
    handleLevelsButtonMouseOn();
    handleStatsButtonMouseOn();
    handlePlayerBoxOn();
}

void Menu::handleStatsButtonMouseOn() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    auto mouseOnColor = !showStats ? sf::Color::Yellow : sf::Color::White;
    auto mouseOutColor = showStats ? sf::Color::Yellow : sf::Color::White;
    if (statsButton.getGlobalBounds().contains(mousePos)) {
        statsButton.setFillColor(mouseOnColor);
    } else {
        statsButton.setFillColor(mouseOutColor);
    }
}

void Menu::handleStatsButtonClick() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (statsButton.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
        showStats = !showStats;
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
                selectedLevel = i;
            }
        } else {
            levelButtons[i].setFillColor(sf::Color::White);
        }
    }
}


void Menu::handlePlayerBoxOn() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (nicknameBox.getGlobalBounds().contains(mousePos) || typingNickname) {
        nicknameBox.setOutlineColor(sf::Color::Yellow);
    } else {
        nicknameBox.setOutlineColor(sf::Color::White);
    }
}

void Menu::handlePlayerBoxClick() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (nicknameBox.getGlobalBounds().contains(mousePos)) {
        typingNickname = true;
        if (playerNickname == "Player") {
            playerNickname = "";
            nicknameText.setString("");
        }
    } else {
        typingNickname = false;
        if (playerNickname.empty()) {
            playerNickname = "Player";
            nicknameText.setString("Player");
        }
    }
}

void Menu::handleTextInput(char32_t symb) {
    if (!typingNickname) {
        return;
    }
    if (symb < 128) {
        if (symb == '\b') {
            if (!playerNickname.empty()) {
                playerNickname.pop_back();
            }
        } else if (symb == '\r') {
            typingNickname = false;
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









