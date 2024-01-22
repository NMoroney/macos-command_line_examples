# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=cgal_convex_hull

BOOSTINC=/add/path/to/boost
EIGEN=/add/path/to/eigen


OPT=-std=c++17 -O3 -DCGAL_EIGEN3_ENABLED


hull :
	g++ $(OPT) $(EXE).cc -I $(BOOSTINC) -I $(EIGEN) -lgmp -lmpfr -o $(EXE)
	./$(EXE)

