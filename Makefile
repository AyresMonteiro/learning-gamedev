main: main.cpp ./build/classes/GameScreen.class.o
	g++ ./main.cpp ./build/classes/GameScreen.class.o -o main -lsfml-graphics -lsfml-window -lsfml-system

./build/classes/GameScreen.class.o: ./src/classes/GameScreen.class.cpp
	g++ ./src/classes/GameScreen.class.cpp -c -o ./build/classes/GameScreen.class.o -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm ./build/classes/* && rm ./main