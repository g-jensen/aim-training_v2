#include <iostream>
#include "assets/Game.hpp"

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
    Aim::Game::GameBlocks gameBlock;
    Aim::Button startButton(200,50,windowWidth/2-200/2,(windowHeight/2-50/2));
    Aim::Button restartButton(100,35,10,130);

    sf::Font mainFont;
    if (!mainFont.loadFromFile("./assets/fonts/DejaVuSans-Bold.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Clock clock;

    float hits = 0;
    float misses = 0;
    float ratio = 0;

    if (misses == 0) {
        ratio = hits/1;
    } else {
        ratio = hits/misses;
    }

    bool gotHit;

    sf::Text hitText;
        hitText.setFont(mainFont);
        hitText.setString("hits: " + roundString(std::to_string(hits),-1));
        hitText.setPosition(sf::Vector2f(10,10));
        hitText.setCharacterSize(15);

    sf::Text missText;
        missText.setFont(mainFont);
        missText.setString("misses: " + roundString(std::to_string(misses),-1));
        missText.setPosition(sf::Vector2f(10,50));
        missText.setCharacterSize(15);

    sf::Text ratioText;
        ratioText.setFont(mainFont);
        ratioText.setString("ratio: " + roundString(std::to_string(ratio),2));
        ratioText.setPosition(sf::Vector2f(10,90));
        ratioText.setCharacterSize(15);

    sf::Text timerText;
        timerText.setFont(mainFont);
        timerText.setString("time: " + roundString(std::to_string(clock.getElapsedTime().asSeconds()),2));
        timerText.setPosition(sf::Vector2f(10,177));
        timerText.setCharacterSize(15); 


    sf::Text mainMenuText;
        mainMenuText.setFont(mainFont);
        mainMenuText.setString("Aim Training");
        mainMenuText.setPosition(sf::Vector2f(windowWidth/2-(50*3.5),windowHeight/2-(130)));
        mainMenuText.setCharacterSize(50);

    sf::Text mainButtonText;
        mainButtonText.setFont(mainFont);
        mainButtonText.setString("PLAY");
        mainButtonText.setPosition(sf::Vector2f(windowWidth/2-35,(windowHeight/2-50/2)+8));
        mainButtonText.setCharacterSize(25);
        mainButtonText.setFillColor(sf::Color::Black);

    sf::Text restartButtonText;
        restartButtonText.setFont(mainFont);
        restartButtonText.setString("RESTART");
        restartButtonText.setPosition(sf::Vector2f(20,137));
        restartButtonText.setCharacterSize(15);
        restartButtonText.setFillColor(sf::Color::Black);


    

    while (window.isOpen()) {

        if (clock.getElapsedTime().asSeconds() <= game.timeLimit) {
            timerText.setFillColor(sf::Color::White);
            timerText.setString("time: " + roundString(std::to_string(clock.getElapsedTime().asSeconds()),2));
        } else {
            timerText.setFillColor(sf::Color(255,0,0));
        }

        gotHit = false;

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
                            hits++;
                            gameBlock.newBlock();
                            gameBlock.blockVec.erase(gameBlock.blockVec.begin()+iterator);
                            gotHit = true;
                            break;
                        }
                        iterator++;
                    }
                    if (gotHit == false) {
                        misses++;
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
                    hits = 0.0f;
                    misses = 0.0f;
                    ratio = 0.0f;
                }
                if (clock.getElapsedTime().asSeconds() <= game.timeLimit) {
                    hitText.setString("hits: " + roundString(std::to_string(hits),-1));
                    missText.setString("misses: " + roundString(std::to_string(misses),-1));
                    if (misses == 0) {
                        ratio = hits/1;
                    } else {
                        ratio = hits/misses;
                    }
                    ratioText.setString("ratio: " + roundString(std::to_string(ratio),2));
                }
            }
        }
        window.clear();
        if (game.hasStarted) {
            for (auto block : gameBlock.blockVec) {window.draw(block.button.texture);}
            window.draw(hitText);
            window.draw(missText);
            window.draw(ratioText);
            window.draw(restartButton.texture);
            window.draw(restartButtonText);
            window.draw(timerText);
        } else {
            window.draw(startButton.texture);
            window.draw(mainMenuText);
            window.draw(mainButtonText);
        }
        window.display();
    }
    return 0;
}