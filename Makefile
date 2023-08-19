LINUX_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main: main.cpp ./build/classes/GameScreen.class.o ./build/classes/CommonDrawingFX.class.o ./build/classes/Character.class.o ./build/classes/Map.class.o
	g++ ./main.cpp ./build/classes/Character.class.o ./build/classes/CommonDrawingFX.class.o ./build/classes/GameScreen.class.o ./build/classes/Map.class.o -o main $(LINUX_LIBS)

./build/classes/Character.class.o: ./src/classes/Character.class.cpp
	g++ ./src/classes/Character.class.cpp -c -o ./build/classes/Character.class.o $(LINUX_LIBS)

./build/classes/CommonDrawingFX.class.o: ./src/classes/CommonDrawingFX.class.cpp
	g++ ./src/classes/CommonDrawingFX.class.cpp -c -o ./build/classes/CommonDrawingFX.class.o $(LINUX_LIBS)

./build/classes/GameScreen.class.o: ./src/classes/GameScreen.class.cpp
	g++ ./src/classes/GameScreen.class.cpp -c -o ./build/classes/GameScreen.class.o $(LINUX_LIBS)

./build/classes/Map.class.o: ./src/classes/Map.class.cpp
	g++ ./src/classes/Map.class.cpp -c -o ./build/classes/Map.class.o $(LINUX_LIBS)

clean:
	rm ./build/classes/* && rm ./main