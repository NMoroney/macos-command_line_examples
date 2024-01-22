# © 2024 : github.com/NMoroney
# MIT License 
#


EXE=fit_sphere_to_3d_points


OPT=-std=c++11 -O -w 
# OPT=-std=c++11 -O

# WARNING: SuperLU headers not found; using built-in definitions [-W#pragma-messages]


fit :
	g++ $(OPT) $(EXE).cc -larmadillo -o $(EXE)
	./$(EXE)


