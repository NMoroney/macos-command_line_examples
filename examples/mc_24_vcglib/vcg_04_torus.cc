// 2024 : github.com/NMoroney
// MIT License 
//

//
// * https://github.com/cnr-isti-vclab/vcglib
//

#include <iostream>
#include <map>

#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/update/topology.h>
#include <vcg/complex/algorithms/update/normal.h>

#include <vcg/complex/algorithms/create/platonic.h>

#include "happly.h"


namespace n8m {

  using T        = double;
  using Point3D  = std::array<T, 3>;
  using Points   = std::vector<Point3D>;
  using Vertices = std::vector<Point3D>;
  using Face     = std::vector<size_t>;
  using Faces    = std::vector<Face>;

  // vcglib aliases
  //
  class MeshFace;
  class MeshVertex;

  struct MeshTypes : public vcg::UsedTypes< vcg::Use<MeshVertex>::AsVertexType,
                                            vcg::Use<MeshFace>::AsFaceType > { };
  class MeshVertex : public vcg::Vertex< MeshTypes,
                                         vcg::vertex::VFAdj,
                                         vcg::vertex::Coord3f,
                                         vcg::vertex::Normal3f,
                                         vcg::vertex::BitFlags > { };
  class MeshFace : public vcg::Face< MeshTypes,
                                     vcg::face::VFAdj,
                                     vcg::face::FFAdj,      // convex hull
                                     vcg::face::Normal3f,
                                     vcg::face::VertexRef,
                                     vcg::face::BitFlags > { };
  class VCGTriangles : public vcg::tri::TriMesh< std::vector<MeshVertex>,
                                                 std::vector<MeshFace> > { };


  Points vcg_triangles_to_mesh(const VCGTriangles& t) {
    Points m;
    for (int i = 0; i < t.FN(); i++) {
      auto i1 { vcg::tri::Index(t, t.face[i].cV(0)) },
           i2 { vcg::tri::Index(t, t.face[i].cV(1)) },
           i3 { vcg::tri::Index(t, t.face[i].cV(2)) };

      Point3D v1 { t.vert[i1].cP()[0], t.vert[i1].cP()[1], t.vert[i1].cP()[2] },
              v2 { t.vert[i2].cP()[0], t.vert[i2].cP()[1], t.vert[i2].cP()[2] },
              v3 { t.vert[i3].cP()[0], t.vert[i3].cP()[1], t.vert[i3].cP()[2] };

      m.push_back(v1);
      m.push_back(v2);
      m.push_back(v3);
    }
    return m;
  }


  void vcglib_torus() {
    using std::cout;
    cout << "vcglib torus :\n";

    VCGTriangles t;
    T h_radius { (T)16  }, 
      v_radius { (T)1.5 };
    int h_div { 90 }, 
	v_div { 30 };
    vcg::tri::Torus<VCGTriangles>(t, h_radius, v_radius, h_div, v_div);

    auto m = vcg_triangles_to_mesh(t);

    cout << "m size : " << m.size() << "\n";

    std::map<Point3D, int> point_to_index;
    std::map<int, Point3D> index_to_point;
    int i = 0;
    for (auto& point : m) {
      auto itr = point_to_index.find(point);
      if (itr == point_to_index.end()) {
        point_to_index[point] = i;
        index_to_point[i] = point;
        ++i;
      }
    }

    Points vertices;
    for (int j = 0; j < index_to_point.size(); ++j) {
      vertices.push_back(index_to_point[j]);
    }

    Faces indices;
    for (int j = 0; j < m.size(); j += 3) {
      Face face;
      face.push_back(point_to_index[m[j    ]]);
      face.push_back(point_to_index[m[j + 1]]);
      face.push_back(point_to_index[m[j + 2]]);
      indices.push_back(face);
    }

    happly::PLYData ply;
    ply.addVertexPositions(vertices);
    ply.addFaceIndices(indices);
    ply.write("torus_35_3.ply", happly::DataFormat::Binary);

  }

}

int main() {

  n8m::vcglib_torus();

  return 0;

}
