# aim-training_v2
# aim-training is a game that gives you 30 seconds to click as many rectangles as possibe.
# [example video](https://www.youtube.com/watch?v=rjJxVvve58c)
A refactor of aim-training_v1

SFML is a graphics library for C++

If you want to run this program you can install SFML:

```sudo apt-get install libsfml-dev```

or go to the website ```https://www.sfml-dev.org```

If you are on linux, you can [```bash run.sh```](https://github.com/g-jensen/aim-training_v2/blob/main/run.sh).

Or if you want to manually compile the program, you can do:

```g++ -c main.cpp```

then:

```g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system```

and to run it:

```./sfml-app```
