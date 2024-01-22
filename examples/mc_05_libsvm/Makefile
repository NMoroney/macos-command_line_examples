// © 2024 : github.com/NMoroney
// MIT License 
//

EXE=data_process_libsvm

OPT=-std=c++11 -O3


svm :
	g++ $(OPT) $(EXE).cc -o $(EXE)
	./$(EXE) 1
	echo


LSVM=/add/path/to/compiled/libsvm/binaries

train :
	$(LSVM)svm-train -s 0 -t 2 train_orange_svm.txt 
	echo

predict :
	$(LSVM)svm-predict validate_orange_svm.txt train_orange_svm.txt.model validate_predicted.txt
	echo

grid :
	$(LSVM)svm-predict grid_svm.txt train_orange_svm.txt.model grid_predicted.txt
	echo


xyzrgb :
	./$(EXE) 2


all : svm train predict grid xyzrgb


clean :
	rm *svm.txt
	rm *predicted.txt
	rm *.model
	rm *xyzrgb.tsv

