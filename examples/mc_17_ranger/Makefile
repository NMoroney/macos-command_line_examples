# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=data_process_ranger

RANGER=/Users/nathan/praktijk/mac_sonoma/mac_17_ranger/ranger-master/cpp_version/build/ranger

OPT=-std=c++17 -O3


help :
	$(RANGER) --help
	$(RANGER) --version


prep :
	g++ $(OPT) $(EXE).cc -o $(EXE)
	./$(EXE) 1


train :
	$(RANGER) --verbose --file train_orange_ranger.data --depvarname name --treetype 1 --ntree 1000 --nthreads 4 --write --outprefix oranges_tree


predict :
	$(RANGER) --verbose --file validate_orange_ranger.data --depvarname name --treetype 1 --ntree 1000 --nthreads 4 --predict oranges_tree.forest --outprefix validate_oranges
	$(RANGER) --verbose --file grid_ranger.data --depvarname name --treetype 1 --ntree 1000 --nthreads 4 --predict oranges_tree.forest --outprefix grid


grid :
	./$(EXE) 2


lab_grid :
	./lab_grid-format.sh
	$(RANGER) --verbose --file lab_grid-rgb-ranger.data --depvarname name --treetype 1 --ntree 1000 --nthreads 4 --predict oranges_tree.forest --outprefix lab_grid
	./$(EXE) 3


gif :
	ffmpeg -framerate 1 -pattern_type glob -i 'cie*.jpg' ranger-random_forest-orange_classifier.gif
	ffmpeg -framerate 1 -pattern_type glob -i 'cie*.jpg' -filter:v "crop=200:200:241:134" ranger-random_forest-orange_classifier-02.gif

