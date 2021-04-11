#include <SFML/Graphics.hpp>
#include "Button.hpp"

namespace Aim {
    class Game {
        

        public:
            class GameBlocks;
            class AimBlocks;
            bool hasStarted;
            float timeLimit;

            Game() {
                hasStarted = false;
                timeLimit = 30.01f;
            }
            
        private:

    };

    class Game::AimBlocks {
        public:
            Aim::Button button;
            int id;
            int blockId;
            AimBlocks (Aim::Button b, int i, int bId) {
                button = b;
                int id = i;
                int blockId = bId;
            }
    };

    class Game::GameBlocks {
        private:
            int currentPos = 0;
            int initialBlockCnt = 3;
            void initPossiblePositions () {
                for (int k = 0; k <= 4; k++) {
                    for (int p = 0; p <= 4; p++) {
                        possiblePositions.push_back(sf::Vector2f{200+(140*p),50+(160*k)});
                    }
                }
            }
            void BlocksInit () {
                int randomPos = 0;
                for (int i = 0; i < initialBlockCnt; i++) {
                    randomPos = rand () % possiblePositions.size();
                    while (checkInVec(blockVec,randomPos)) {
                        randomPos = rand() % possiblePositions.size();
                    }
                    Aim::Button newButton(140,160,possiblePositions[randomPos]);
                    Aim::Game::AimBlocks ab(newButton,currentPos,randomPos);
                    ab.button = newButton;
                    blockVec.push_back(ab);
                    currentPos++;
                }
            }
        public:
            std::vector<sf::Vector2f> possiblePositions;
            std::vector<Aim::Game::AimBlocks> blockVec;

            void newBlock () {
                int randomPos = 0;
                randomPos = rand () % possiblePositions.size();
                
                while (checkInVec(blockVec,randomPos)) {
                    randomPos = rand() % possiblePositions.size();
                }
                Aim::Button newButton(140,160,possiblePositions[randomPos]);
                Aim::Game::AimBlocks ab(newButton,currentPos,randomPos);
                ab.button = newButton;
                ab.blockId = randomPos;
                blockVec.push_back(ab);
                currentPos++;
            }

            bool checkInVec (std::vector<Aim::Game::AimBlocks> vec,int value) {
                for (int i = 0; i < vec.size(); i++) {
                    if (value == vec[i].blockId) {
                        return true;
                    }
                }
                return false;
            }

            GameBlocks () {
                unsigned seed = time(0);
                srand(seed);
                initPossiblePositions();
                BlocksInit();
            }
    };
}