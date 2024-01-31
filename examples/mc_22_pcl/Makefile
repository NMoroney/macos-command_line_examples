# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=pcl_outliers

HAPPLY=/add/path/to/happly

EIGEN=/add/path/to/eigen

PCLINC=/usr/local/opt/pcl/include/pcl-1.13
PCLLIBS=-lpcl_common -lpcl_io -lpcl_features -lpcl_filters

BOOSTINC=/usr/local/opt/boost/include

OPT=-std=c++17 -O3


all :
	g++ $(OPT) $(EXE).cc -I $(HAPPLY) -I $(EIGEN) -I $(PCLINC) -I $(BOOSTINC) $(PCLLIBS)  -o $(EXE)
	./$(EXE)


clean :
	rm temp*

