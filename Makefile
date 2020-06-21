SDL_FLAG=-lSDL2 -lSDL2_image

run: link
	./jogo

link: test.o main.o
	g++ main.o test.o $(SDL_FLAG) -o jogo

test.o: src/test.cpp
	g++ -o test.o -c src/test.cpp

main.o: src/main.cpp include/test.hpp
	g++ -o main.o -c src/main.cpp

clean: 
	rm -rf *.o jogo