# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=libigl_blue_noise

IGL=/add/full/path/to/libigl/here

EIGEN=/add/full/path/to/eigen/here

OPT=-std=c++11 -O3


all :
	g++ $(OPT) -I $(IGL) -I $(EIGEN) $(EXE).cc -o $(EXE)
	./$(EXE)

