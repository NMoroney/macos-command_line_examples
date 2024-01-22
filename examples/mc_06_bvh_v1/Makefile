# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=bvh-virtual_3d_scanner

BVH=/add/path/to/bvh
HAPPLY=/add/path/to/happly

OPT=-std=c++17 -O3


points :
	g++ $(OPT) $(EXE).cc -I $(BVH) -I $(HAPPLY) -o $(EXE)
	./$(EXE)

