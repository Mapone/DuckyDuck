NAME=sfml-app

sfml-app: sfmlTest.cpp
		g++ -std=c++11 -c sfmlTest.cpp
		g++ sfmlTest.o -o $(NAME) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	@rm *.o $(NAME)
