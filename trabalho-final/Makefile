CC = g++
OPENCV = -I /usr/local/include/opencv4 -g
CFLAGS = -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -std=c++11
SRC=src/
OBJ=obj/
BIN=bin/

OBJS = main.o filtro.o trocaQuadrante.o

all: folder app run

app: $(OBJS)
	${CC} $(OPENCV) $(OBJ)main.o $(OBJ)filtro.o $(OBJ)trocaQuadrante.o -o $(BIN)app $(CFLAGS)
	
main.o: $(SRC)main.cpp
	${CC} -c $(OPENCV) $(SRC)main.cpp -o $(OBJ)main.o

filtro.o: $(SRC)filtro.cpp
	${CC} -c $(OPENCV) $< -o $(OBJ)filtro.o

trocaQuadrante.o: $(SRC)trocaQuadrante.cpp
	${CC} -c $(OPENCV) $< -o $(OBJ)trocaQuadrante.o

folder: 
	mkdir -p bin obj

run:
	@./$(BIN)app

clean:
	rm obj/ bin/ -rf obj/