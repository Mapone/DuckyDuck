sfml-app: sfmlTest.cpp
		g++ -std=c++11 -c sfmlTest.cpp
		g++ sfmlTest.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system