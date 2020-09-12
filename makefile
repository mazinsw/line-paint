CPP  = g++
OBJ = main.o \
	  linha.o \
	  classes/display.o \
	  classes/glwindow.o
LIBS=-lSDL -lSDLmain -lGL -lGLU
FLAGS=

all: linepaint

clean:
	rm -rf $(OBJ) linepaint

linepaint: $(OBJ)
	$(CPP) -o linepaint $(OBJ) $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(FLAGS)

linha.o: linha.cpp
	$(CPP) -c linha.cpp -o linha.o $(FLAGS)

classes/glwindow.o: classes/glwindow.cpp
	$(CPP) -c classes/glwindow.cpp -o classes/glwindow.o $(FLAGS)

classes/display.o: classes/display.cpp
	$(CPP) -c classes/display.cpp -o classes/display.o $(FLAGS)

