# © 2024 : github.com/NMoroney
# MIT License 
#

# * https://github.com/LluisV/Z-Anatomy/tree/PC-Version/Resources/Models/FBX
# * https://examples.vtk.org/site/Cxx/IO/ReadPLY/
#

EXE=vtk_read_ply

VTKINC=/usr/local/include/vtk-9.2

VTKVER=9.2.1
VTKCOL=-lvtkCommonColor-$(VTKVER)
VTKCOMMON=-lvtkCommonCore-$(VTKVER)
VTKDMODEL=-lvtkCommonDataModel-$(VTKVER)
VTKCEM=-lvtkCommonExecutionModel-$(VTKVER)
VTKFILS=-lvtkFiltersSources-$(VTKVER)
VTKINTS=-lvtkInteractionStyle-$(VTKVER)
VTKIOPLY=-lvtkIOPLY-$(VTKVER)
VTKRCG2=-lvtkRenderingContextOpenGL2-$(VTKVER)
VTKREND=-lvtkRenderingCore-$(VTKVER)
VTKREFT=-lvtkRenderingFreeType-$(VTKVER)
VTKRG2P=-lvtkRenderingGL2PSOpenGL2-$(VTKVER)
VTKGL2=-lvtkRenderingOpenGL2-$(VTKVER)
VTKSYS=-lvtksys-$(VTKVER)
VTKLIBS=$(VTKCOL) $(VTKCOMMON) $(VTKDMODEL) $(VTKCEM) $(VTKFILS) $(VTKINTS) $(VTKIOPLY) $(VTKRCG2) $(VTKREND) $(VTKREFT) $(VTKRG2P) $(VTKRGL2) $(VTKSYS)

OPT=-std=c++17 -O3


all :
	g++ $(OPT) $(EXE).cc -I $(VTKINC) $(VTKLIBS) -lassimp -o $(EXE)
	./$(EXE)


cylinder :
	./$(EXE)


