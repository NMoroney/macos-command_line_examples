# © 2024 : github.com/NMoroney
# MIT License 
#


EXE=mlpack-spectral_autoencoder

OPT=-std=c++20 -O3 -w -DMLPACK_ENABLE_ANN_SERIALIZATION


ae :
	g++ $(OPT) $(EXE).cc -larmadillo -o $(EXE)     
	./$(EXE)


# compile time with -O3    : 222.63s user 17.61s system 92% cpu 4:19.55 total
# compile time without -O3 : 128.24s user 8.51s system 99% cpu 2:18.10 total
#
