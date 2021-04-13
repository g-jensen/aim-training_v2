#include <iostream>
#include "assets/Game.hpp"
#include "assets/Button.hpp"
#include "assets/Text.hpp"


std::string roundString (std::string s, int index) {
    int indexOfPeriod = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s.substr(i,1) == ".") {
            indexOfPeriod = i;
            break;
        }
    }
    std::string substring = s.substr(0,indexOfPeriod);
    return s.substr(0,indexOfPeriod+index+1);
}

int main () {

    int windowWidth = 1100;
    int windowHeight = 900;

    sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight),"Aim Training");
    
    Aim::Game game;

    if (game.misses == 0) {
        game.ratio = game.hits/1;
    } else {
        game.ratio = game.hits/game.misses;
    }
    
    Aim::Game::AimBlocksHandler gameBlock;
    
    Aim::Button startButton(200,50,windowWidth/2-200/2,(windowHeight/2-50/2));
    
    Aim::Button restartButton(100,35,10,130);

    sf::Font mainFont;

    if (!mainFont.loadFromFile("./assets/fonts/DejaVuSans-Bold.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Clock clock;

    Aim::Text hitText(10,10,mainFont,"hits " + roundString(std::to_string(game.hits),-1));
    hitText.texture.setCharacterSize(15);

    Aim::Text missText(10,50,mainFont,"misses: " + roundString(std::to_string(game.misses),-1));
    missText.texture.setCharacterSize(15);

    Aim::Text ratioText(10,90,mainFont,"ratio: " + roundString(std::to_string(game.ratio),2));
    ratioText.texture.setCharacterSize(15);

    Aim::Text timerText(10,177,mainFont,"time: " + roundString(std::to_string(clock.getElapsedTime().asSeconds()),2));
    timerText.texture.setCharacterSize(15);

    Aim::Text mainMenuText(sf::Vector2f(windowWidth/2-(50*3.5),windowHeight/2-(130)),mainFont,"Aim Training");
    mainMenuText.texture.setCharacterSize(50);

    Aim::Text mainButtonText(sf::Vector2f(windowWidth/2-35,(windowHeight/2-50/2)+8),mainFont,"PLAY");
    mainButtonText.texture.setCharacterSize(25);
    mainButtonText.texture.setFillColor(sf::Color::Black);

    Aim::Text restartButtonText(sf::Vector2f(20,137),mainFont,"RESTART");
    restartButtonText.texture.setCharacterSize(15);
    restartButtonText.texture.setFillColor(sf::Color::Black);

    while (window.isOpen()) {

        if (clock.getElapsedTime().asSeconds() <= game.timeLimit) {
            timerText.texture.setFillColor(sf::Color::White);
            timerText.setString("time: " + roundString(std::to_string(clock.getElapsedTime().asSeconds()),2));
        } else {
            timerText.texture.setFillColor(sf::Color(255,0,0));
        }

        game.gotHit = false;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (game.hasStarted) {
                    int iterator = 0;
                    for (auto block : gameBlock.blockVec) {
                        if (block.button.contains(sf::Mouse::getPosition(window))) {
                            game.hits++;
                            gameBlock.newBlock();
                            gameBlock.blockVec.erase(gameBlock.blockVec.begin()+iterator);
                            game.gotHit = true;
                            break;
                        }
                        iterator++;
                    }
                    if (game.gotHit == false) {
                        game.misses++;
                    }
                }
                if (startButton.contains(sf::Mouse::getPosition(window)) && (game.hasStarted == false)) {
                    game.hasStarted = true;
                    clock.restart();
                }
                if (restartButton.contains(sf::Mouse::getPosition(window))) {
                    gameBlock.blockVec.clear();
                    gameBlock.newBlock();
                    gameBlock.newBlock();
                    gameBlock.newBlock();
                    game.hasStarted = false;
                    game.hits = 0.0f;
                    game.misses = 0.0f;
                    game.ratio = 0.0f;
                }
                if (clock.getElapsedTime().asSeconds() <= game.timeLimit) {
                    hitText.setString("hits: " + roundString(std::to_string(game.hits),-1));
                    missText.setString("misses: " + roundString(std::to_string(game.misses),-1));
                    if (game.misses == 0) {
                        game.ratio = game.hits/1;
                    } else {
                        game.ratio = game.hits/game.misses;
                    }
                    ratioText.setString("ratio: " + roundString(std::to_string(game.ratio),2));
                }
            }
        }
        window.clear();
        if (game.hasStarted) {
            for (auto block : gameBlock.blockVec) {window.draw(block.button.texture);}
            window.draw(hitText.texture);
            window.draw(missText.texture);
            window.draw(ratioText.texture);
            window.draw(restartButton.texture);
            window.draw(restartButtonText.texture);
            window.draw(timerText.texture);
        } else {
            window.draw(startButton.texture);
            window.draw(mainMenuText.texture);
            window.draw(mainButtonText.texture);
        }
        window.display();
    }
    return 0;
}