all:
	g++ -c *.cpp -std=c++20 -m64 -O3 -Wall -I include && g++ *.o -o bin/release/main -s -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf && ./bin/release/main