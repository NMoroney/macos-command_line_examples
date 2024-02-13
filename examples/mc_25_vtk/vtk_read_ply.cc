// © 2024 : github.com/NMoroney
// MIT License 
//

#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>     
#include <assimp/Exporter.hpp>      

#include <vtkActor.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPLYReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


namespace n8m {

  void fbx_to_ply() {
    using std::cout;
    cout << "read fbx :\n";

    // * https://github.com/LluisV/Z-Anatomy/tree/PC-Version/Resources/Models/FBX
    //
    std::vector<std::string> models {   "CardioVascular41.fbx",
                                        "MuscularSystem100.fbx",
                                        "Regions_of_human_body100.fbx",
                                        "Joints100.fbx",
                                        "NervousSystem100.fbx",
                                        "SkeletalSystem100.fbx",
                                        "LymphoidOrgans100.fbx",
                                        "References100.fbx",
                                        "VisceralSystem100.fbx" };

    std::string path  { "/Users/nathan/bulk/Z-Anatomy-PC-Version/Resources/Models/FBX/" },
                model { models[0] },
                name  { path + model };

    cout << "path  : " << path  << "\n"
         << "model : " << model << "\n"
         << "name  : " << name  << "\n";

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(name,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType            |
        aiProcess_ValidateDataStructure);

    int number_meshes { (int)scene->mNumMeshes };

    cout << "number of meshes : " << number_meshes << "\n" << "  ";

    for (int i = 0; i < number_meshes; ++i) {
      int number_vertices = scene->mMeshes[i]->mNumVertices;
      cout << number_vertices << " ";
    }
    cout << "\n";

    if (scene == nullptr) {
      cout << "scene import failed.\n";
    } else {

      Assimp::Exporter exporter;

      exporter.Export(scene, "plyb", "temp_out.ply", 0);
    }
  }


  // * https://examples.vtk.org/site/Cxx/IO/ReadPLY/
  //
  using NamedColors = vtkNew<vtkNamedColors>;
  using Color       = vtkColor3d;
  using PLYReader   = vtkNew<vtkPLYReader>;
  using Mapper      = vtkNew<vtkPolyDataMapper>;
  using Actor       = vtkNew<vtkActor>;
  using Renderer    = vtkNew<vtkRenderer>;
  using Window      = vtkNew<vtkRenderWindow>;
  using Interactor  = vtkNew<vtkRenderWindowInteractor>;

  int vtk_read_ply() {

    NamedColors colors;
    auto white     { colors->GetColor3d("White") },
         dark_gray { colors->GetColor3d("DarkGray") };

    PLYReader reader;
    reader->SetFileName("temp_out.ply");

    Mapper mapper;
    mapper->SetInputConnection(reader->GetOutputPort());

    Actor actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(dark_gray.GetData());

    Renderer renderer;
    Window window;
    window->AddRenderer(renderer);
    window->SetWindowName("Read PLY");

    Interactor interactor;
    interactor->SetRenderWindow(window);

    renderer->AddActor(actor);
    renderer->SetBackground(white.GetData());

    window->Render();
    interactor->Start();

    return EXIT_SUCCESS;
  }

}


int main(int, char*[]) {

  n8m::fbx_to_ply();             // use assimp to read z-anatomy fbx and save as binary ply

  return n8m::vtk_read_ply();    // use vtk to read and display a ply file

}

