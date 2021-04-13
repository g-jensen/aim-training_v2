#include <SFML/Graphics.hpp>

#ifndef TEXT_H
#define TEXT_H

    namespace Aim {
        class Text : hasTexture {
            private:
                sf::Font t_font;
                std::string t_string;
                sf::Vector2f pos;
                float xPos;
                float yPos;

                void init () {
                    texture.setPosition(pos);
                    texture.setFont(t_font);
                    texture.setString(t_string);
                }

            public:
                sf::Text texture;

                Text(float x, float y, sf::Font font, std::string string) {
                    t_font = font;
                    t_string = string;
                    pos = {x,y};
                    xPos = x;
                    yPos = y;
                    init ();
                }

                Text(sf::Vector2f p, sf::Font font, std::string string) {
                    t_font = font;
                    t_string = string;
                    pos = p;
                    xPos = p.x;
                    yPos = p.y;
                    init();
                }

                void setCharacterSize (int size) {
                    texture.setCharacterSize(size);
                }

                int getCharacterSize () {
                    return texture.getCharacterSize();
                }

                void setFont(sf::Font font) {
                    t_font = font;
                    init();
                }

                sf::Font getFont() {
                    return t_font;
                }

                void setString(std::string string) {
                    t_string = string;
                    init();
                }

                std::string getString () {
                    return t_string;
                }

                void setPos(float x, float y) {
                    pos = {x,y};
                    xPos = x;
                    yPos = y;
                    init();
                }

                void setPos(sf::Vector2f p) {
                    pos = p;
                    xPos = p.x;
                    yPos = p.y;
                }

                sf::Vector2f getPos() {
                    return pos;
                }

        };
    }

#endif