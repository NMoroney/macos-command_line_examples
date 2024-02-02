# © 2024 : github.com/NMoroney
# MIT License 
#

EXE=pcl-color_cloud


OCV=/usr/local/

OCVINC=$(OCV)include/opencv4
OCVLIB=$(OCV)lib

OCVCORE=-lopencv_core
OCVCODEC=-lopencv_imgcodecs
OCVPROC=-lopencv_imgproc

OCVLIBS=-Wl,-rpath,$(OCVLIB) $(OCVCORE) $(OCVCODEC) $(OCVPROC)


EIGEN=/add/path/to/eigen
BOOSTINC=/add/path/to/boost


PCLINC=/usr/local/opt/pcl/include/pcl-1.13
PCLLIBS=-lpcl_common -lpcl_io -lpcl_visualization


VTKINC=/usr/local/include/vtk-9.2

VTKVER=9.2.1
VTKCOMMON=-lvtkCommonCore-$(VTKVER)
VTKDMODEL=-lvtkCommonDataModel-$(VTKVER)
VTKREND=-lvtkRenderingCore-$(VTKVER)
VTKMATH=-lvtkCommonMath-$(VTKVER)
VTKRLOD=-lvtkRenderingLOD-$(VTKVER)
VTKSYS=-lvtksys-$(VTKVER)
VTKLIBS=$(VTKCOMMON) $(VTKDMODEL) $(VTKREND) $(VTKMATH) $(VTKRLOD) $(VTKSYS)


INCLUDES=-I $(OCVINC) -I $(EIGEN) -I $(PCLINC) -I $(BOOSTINC) -I$(VTKINC)

LIBRARIES=$(OCVLIBS) $(PCLLIBS) $(VTKLIBS)


OPT=-std=c++17 -O3 -w


all :
	g++ $(OPT) $(EXE).cc $(INCLUDES) $(LIBRARIES) -o $(EXE)
	./$(EXE)

