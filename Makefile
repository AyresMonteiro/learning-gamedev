CXXFLAGS := $(shell pkg-config --cflags sfml-all)
LDLIBS := $(shell pkg-config --libs sfml-all)

main: main.cpp ./build/classes/GameScreen.class.o ./build/classes/CommonDrawingFX.class.o ./build/classes/Character.class.o
	g++ $(CXXFLAGS) ./main.cpp ./build/classes/Character.class.o ./build/classes/CommonDrawingFX.class.o ./build/classes/GameScreen.class.o ./build/classes/Map.class.o -o main $(LDLIBS)

./build/classes/Character.class.o: ./src/classes/Character.class.cpp
	g++ $(CXXFLAGS) ./src/classes/Character.class.cpp -c -o ./build/classes/Character.class.o $(LDLIBS)

./build/classes/CommonDrawingFX.class.o: ./src/classes/CommonDrawingFX.class.cpp
	g++ $(CXXFLAGS) ./src/classes/CommonDrawingFX.class.cpp -c -o ./build/classes/CommonDrawingFX.class.o $(LDLIBS)

./build/classes/GameScreen.class.o: ./src/classes/GameScreen.class.cpp
	g++ $(CXXFLAGS) ./src/classes/GameScreen.class.cpp -c -o ./build/classes/GameScreen.class.o $(LDLIBS)

./build/classes/Map.class.o: ./src/classes/Map.class.cpp
	g++ $(CXXFLAGS) ./src/classes/Map.class.cpp -c -o ./build/classes/Map.class.o $(LDLIBS)

clean:
	rm ./build/classes/* && rm ./main
