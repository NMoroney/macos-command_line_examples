# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=vcg_04_torus


VCG=/add/path/to/vcglib
EIGEN=/add/path/to/eigen
HAPPLY=/add/path/to/happly

OPT=-std=c++17 -O3


torus :
	g++ $(OPT) $(EXE).cc -I $(VCG) -I $(EIGEN) -I $(HAPPLY) -o $(EXE)
	./$(EXE)

