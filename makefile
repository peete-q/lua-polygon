CC = g++
CFLAGS = -I../include -I../poly2tri -static-libgcc -static-libstdc++ -g
LFLAGS = -L../lib -llua51 -L../poly2tri -lpoly2tri -static-libgcc -static-libstdc++
TARGET = polygon

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<
	
all : $(OBJ)
	$(CC) -lmingw32 --share -o $(TARGET) $(OBJ) $(LFLAGS)

clean :
	rm -f $(TARGET) $(OBJ)
