# © 2024 : github.com/NMoroney
# MIT License 
#
# * tesseract brew installed with ffmpeg
#

EXE=tesseract_ocr


OCV=/usr/local/

OCVINC=$(OCV)include/opencv4
OCVLIB=$(OCV)lib

LCORE=-lopencv_core
LCODEC=-lopencv_imgcodecs
LPROC=-lopencv_imgproc

OCVDYNAMIC=-Wl,-rpath,$(OCVLIB) $(LCORE) $(LCODEC) $(LPROC)

OPT=-std=c++11 -O3 -w

IMG=camera_image_quality_benchmarking-page_9.jpg


all :
	g++ $(OPT) $(EXE).cc -I $(OCVINC) $(OCVDYNAMIC) -ltesseract -o $(EXE)
	./$(EXE) $(IMG) > text_out.txt
	cat text_out.txt

