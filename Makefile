main: main.cpp ./build/classes/GameScreen.class.o ./build/classes/CommonDrawingFX.class.o ./build/classes/Character.class.o ./build/classes/Map.class.o
	g++ ./main.cpp ./build/classes/Character.class.o ./build/classes/CommonDrawingFX.class.o ./build/classes/GameScreen.class.o ./build/classes/Map.class.o -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

./build/classes/Character.class.o: ./src/classes/Character.class.cpp
	g++ ./src/classes/Character.class.cpp -c -o ./build/classes/Character.class.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

./build/classes/CommonDrawingFX.class.o: ./src/classes/CommonDrawingFX.class.cpp
	g++ ./src/classes/CommonDrawingFX.class.cpp -c -o ./build/classes/CommonDrawingFX.class.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

./build/classes/GameScreen.class.o: ./src/classes/GameScreen.class.cpp
	g++ ./src/classes/GameScreen.class.cpp -c -o ./build/classes/GameScreen.class.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

./build/classes/Map.class.o: ./src/classes/Map.class.cpp
	g++ ./src/classes/Map.class.cpp -c -o ./build/classes/Map.class.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm ./build/classes/* && rm ./main