SDL_FLAG=-lSDL2 -lSDL2_image

run: link
	./jogo

link: map.o test.o main.o
	g++ main.o test.o map.o $(SDL_FLAG) -o jogo

map.o: src/map.cpp
	g++ -o map.o -c src/map.cpp

test.o: src/test.cpp
	g++ -o test.o -c src/test.cpp

main.o: src/main.cpp include/test.hpp include/map.hpp
	g++ -o main.o -c src/main.cpp

clean: 
	rm -rf *.o jogo