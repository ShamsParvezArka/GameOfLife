set -xe

mkdir bin/
#gcc -o bin/gol src/game_of_life_CLI.c -Wall -Wextra -Wformat -std=c11
gcc -o bin/raygol src/game_of_life_GUI.c -Wall -Wextra -Wformat -std=c11 -lm -lraylib -lGL -lpthread -ldl -lrt -lX11
