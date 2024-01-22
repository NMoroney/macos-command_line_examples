// © 2024 : github.com/NMoroney
// MIT License 
//

#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/convex_hull_3.h>

#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh/IO/PLY.h>

namespace n8m {

  void convex_hull_one() {
    using std::cout;
    cout << "convex hull one :\n";

    using Kernel        = CGAL::Exact_predicates_inexact_constructions_kernel;
    using Mesh          = CGAL::Surface_mesh<Kernel::Point_3>;
    using Polyhedron_3  = CGAL::Polyhedron_3<Kernel>;
    using Point_3       = Kernel::Point_3;
    using Points        = std::vector<Point_3>;

    cout << "cgal version : " << CGAL_VERSION_STR << "\n";

    std::ifstream ifs("../../data/tverse-2288923-triceratops-4k.ply");

    std::string comments;
    bool is_verbose { false };
    Mesh mesh;
    auto b = CGAL::IO::read_PLY(ifs, mesh, comments, is_verbose);

    cout << "mesh :\n"
         << "  number of vertices : " << mesh.number_of_vertices() << "\n"
         << "  number of faces    : " << mesh.number_of_faces()    << "\n";

    if (false) {
      int n { 0 };
      for(auto p : mesh.points()){
        if (n < 10) {
          cout << p << "\n";
        }
        ++n;
      }
    }

    Polyhedron_3 convex_hull;
    CGAL::convex_hull_3(mesh.points().begin(), mesh.points().end(), convex_hull);

    cout << "convex hull : number vertices : ";
    cout << num_vertices(convex_hull) << "\n";

    std::ofstream ofs("temp_out.off");
    ofs << convex_hull;

  }

}

int main() {

  n8m::convex_hull_one();

  return 0;

}

