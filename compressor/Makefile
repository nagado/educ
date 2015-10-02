CC = g++
CFLAGS = -std=c++11 -Wall
TARGET = compressor
CLASSES = BitCashier.cpp OffsetAndLength.cpp utils.cpp
RM = rm

all: $(TARGET).cpp
	$(CC) -o $(TARGET) $(TARGET).cpp $(CLASSES) $(CFLAGS)

clean:
	$(RM) $(TARGET) *.o *~
