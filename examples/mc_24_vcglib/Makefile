#
# [2312] [2402]
#

EXE=vcg_04_torus


VCG=/Users/nathan/praktijk/mac_sonoma/mac_25_vcglib/vcglib-main
EIGEN=/Users/nathan/praktijk/mac_sonoma/mac_03_eigen/eigen-3.4.0
HAPPLY=/Users/nathan/tools/useful/happly

OPT=-std=c++17 -O3


torus :
	g++ $(OPT) $(EXE).cc -I $(VCG) -I $(EIGEN) -I $(HAPPLY) -o $(EXE)
	./$(EXE)

