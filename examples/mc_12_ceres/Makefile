# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=ceres-display_fit

EIGEN=/Users/nathan/praktijk/mac_sonoma/mac_03_eigen/eigen-3.4.0

OPT=-Wno-deprecated-declarations -pthread


fit :
	g++ -std=c++17 $(OPT) $(EXE).cc -lglog -lgflags -llapack -lceres -I $(EIGEN) -o $(EXE)
	./$(EXE)

