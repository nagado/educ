CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = main
RM = rm
RMFLAGS = -f
GFLAGS = -lsfml-graphics -lsfml-window -lsfml-system


all: main.o Game.o Utils.o Ball.o Racquet.o Wall.o main clean

main.o:
	$(CC) -c $(TARGET).cpp $(CFLAGS)

Game.o: 
	$(CC) -c Game.cpp $(CFLAGS)

Utils.o:
	$(CC) -c Utils.cpp $(CFLAGS)

Ball.o:
	$(CC) -c Ball.cpp $(CFLAGS)

Racquet.o:
	$(CC) -c Racquet.cpp $(CFLAGS)

Wall.o:
	$(CC) -c Wall.cpp $(CFLAGS)

main: main.o Game.o Utils.o Ball.o Racquet.o Wall.o
	$(CC) -o $(TARGET) $(TARGET).o Game.o Utils.o Ball.o Racquet.o Wall.o $(GFLAGS)

clean:
	$(RM) $(RMFLAGS) *.o
