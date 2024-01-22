# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=eigen_rotate_2d

EIGEN=/add/full/path/to/eigen/here

OPT=-std=c++11 -O3


rotate :
	g++ $(OPT) $(EXE).cc -I $(EIGEN) -o $(EXE)
	./$(EXE)

clean :
	rm temp*

