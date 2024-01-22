# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=ensmallen_contour_alignment_pso

EIGEN=/Users/nathan/praktijk/mac_sonoma/mac_03_eigen/eigen-3.4.0
NFLANN=/Users/nathan/tools/useful/nanoflann

OPT=-std=c++17 -O3 -w


all :
	g++ $(OPT) $(EXE).cc -I $(EIGEN) -I $(NFLANN) -larmadillo -o $(EXE)
	./$(EXE) 7 250


