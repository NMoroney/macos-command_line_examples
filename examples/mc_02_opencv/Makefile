# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=ocv_distance_transform

OCV=/usr/local/

OCVINC=$(OCV)include/opencv4
OCVLIB=$(OCV)lib

LCORE=-lopencv_core
LCODEC=-lopencv_imgcodecs
LPROC=-lopencv_imgproc

OCVLIBS=-Wl,-rpath,$(OCVLIB) $(LCORE) $(LCODEC) $(LPROC)

OPT=-std=c++17 -O3 -w


ocv :
	g++ $(OPT) $(EXE).cc -I $(OCVINC) $(OCVLIBS) -o $(EXE)
	./$(EXE)


