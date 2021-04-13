#include <SFML/Graphics.hpp>

#ifndef BUTTON_H
#define BUTTON_H

namespace Aim {

    class Button {
        private:
            float width;
            float height;
            float xPos;
            float yPos;
            sf::Vector2f pos;
            sf::Vector2f size;

            void init () {
                texture.setPosition(pos);
                texture.setSize(size);
                sf::IntRect hb(xPos,yPos,width,height);
                hitbox = hb;
            }

        public:
        sf::RectangleShape texture;
        sf::IntRect hitbox;
        Button(float w, float h, float x, float y) {
            width=w;
            height=h;
            size={w,h};
            xPos=x;
            yPos=y;
            pos={x,y};
            init();
        }
        Button(float w, float h, sf::Vector2f p) {
            width=w;
            height=h;
            size={w,h};
            xPos=p.x;
            yPos=p.y;
            pos=p;
            init();
        }
        Button(sf::Vector2f s, float x, float y) {
            width=s.x;
            height=s.y;
            size=s;
            xPos=x;
            yPos=y;
            pos={x,y};
            init ();
        }
        Button(sf::Vector2f s, sf::Vector2f p) {
            width=s.x;
            height=s.y;
            size=s;
            xPos=p.x;
            yPos=p.y;
            pos=p;
            init ();
        }
        Button () {
            
        }
        sf::Vector2f getSize() {
            return size;
        }
        void setSize(float w, float h) {
            width=w;
            height=h;
            size={w,h};
            init ();
        }
        void setSize(sf::Vector2f s) {
            width=s.x;
            height=s.y;
            size=s;
            init ();
        }
        sf::Vector2f getPos() {
            return pos;
        }
        void setPos(float x, float y) {
            xPos=x;
            yPos=y;
            pos={x,y};
            init ();
        }
        void setPos(sf::Vector2f p) {
            xPos=p.x;
            yPos=p.y;
            pos=p;
            init ();
        }
        bool contains(sf::Vector2i p) {
            return hitbox.contains(p);
        }
    };

}

#endif