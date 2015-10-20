CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = main
RM = rm
RMFLAGS = -f
GFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main.o main clean

main.o:
	$(CC) -c $(TARGET).cpp $(CFLAGS)

main: main.o
	$(CC) -o $(TARGET) $(TARGET).o $(GFLAGS)

clean:
	$(RM) $(RMFLAGS) *.o
