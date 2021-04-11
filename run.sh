export DISPLAY=:0
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
echo running...
./sfml-app