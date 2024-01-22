// © 2024 : github.com/NMoroney
// MIT License 
//

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// bvh : version 1 - https://github.com/madmann91/bvh/tree/v1
//
#include <bvh/bvh.hpp>
#include <bvh/vector.hpp>
#include <bvh/triangle.hpp>
#include <bvh/ray.hpp>
#include <bvh/sweep_sah_builder.hpp>
#include <bvh/single_ray_traverser.hpp>
#include <bvh/primitive_intersectors.hpp>

// happly : version 2 - https://github.com/nmwsharp/happly
//
#include "happly.h"


namespace n8m {

  // bvh aliases
  //
  using Scalar      = float;
  using Vector3     = bvh::Vector3<Scalar>;
  using Triangle    = bvh::Triangle<Scalar>;
  using Triangles   = std::vector<Triangle>;
  using Ray         = bvh::Ray<Scalar>;
  using BVH         = bvh::Bvh<Scalar>;
  using Builder     = bvh::SweepSahBuilder<BVH>;
  using Intersector = bvh::ClosestPrimitiveIntersector<BVH, Triangle>;
  using Traverser   = bvh::SingleRayTraverser<BVH>;

  // happly aliases
  //
  using Vertices = std::vector<std::array<float, 3> >;
  using Faces    = std::vector<std::vector<size_t> >;

  // other aliases
  //
  using T       = float; 
  using Point3D = std::array<T, 3>;
  using Points  = std::vector<Point3D>;
  using RGB     = std::array<int, 3>;
  using RGBs    = std::vector<RGB>;


  Triangles to_triangles(const Vertices& vs,
                         const Faces& faces) {
    Triangles triangles;
    for (auto f : faces) {
      triangles.emplace_back(
        Vector3(vs[f[0]][0], vs[f[0]][1], vs[f[0]][2]),
        Vector3(vs[f[1]][0], vs[f[1]][1], vs[f[1]][2]),
        Vector3(vs[f[2]][0], vs[f[2]][1], vs[f[2]][2])
      );
    }
    return triangles;
  }


  Point3D xyz_intersection(const Triangles& triangles,
		           const int index,
			   const Scalar u,
		 	   const Scalar v,
			   const Scalar w) {

    auto xyz = (triangles[index].p0   * w) + 
	       (triangles[index].p1() * u) + 
	       (triangles[index].p2() * v);

    Point3D point { xyz[0], xyz[1], xyz[2] };

    return point;
  };


  void virtual_3d_scanner_one() {
    using std::cout;
    cout << "virtual 3d scanner one :\n";

    happly::PLYData plyIn("../../data/tverse-2288923-triceratops-4k.ply");

    // This allows reading as floats, does not do the type promotion
    // that plyIn.getVertexPositions performs
    //
    std::vector<float> xPos = plyIn.getElement("vertex").getProperty<float>("x");
    std::vector<float> yPos = plyIn.getElement("vertex").getProperty<float>("y");
    std::vector<float> zPos = plyIn.getElement("vertex").getProperty<float>("z");
    
    Vertices vs(xPos.size());
    for (size_t i = 0; i < vs.size(); i++) {
      vs[i][0] = xPos[i];
      vs[i][1] = yPos[i];
      vs[i][2] = zPos[i];
    }

    // Type promotion means can't read vertices as floats, hence the above
    //
    // std::vector<std::array<double, 3> > vs = plyIn.getVertexPositions<float>();
    // std::vector<std::array<float, 3> > vs = plyIn.getVertexPositions<float>();

    std::vector<std::vector<size_t> > fs = plyIn.getFaceIndices<size_t>();

    auto triangles = to_triangles(vs, fs);

    auto [bboxes, centers] = bvh::compute_bounding_boxes_and_centers(triangles.data(), triangles.size());
    auto global_bbox = bvh::compute_bounding_boxes_union(bboxes.get(), triangles.size());

    auto min { global_bbox.min }, max { global_bbox.max };
    Vector3 center { (max[0] + min[0]) / 2.0f,
	             (max[1] + min[1]) / 2.0f,
		     (max[2] + min[2]) / 2.0f };
    Vector3 range { max[0] - min[0], max[1] - min[1], max[2] - min[2] };


    int pad { 1 };  // 10
    int wide { (int)(range[0]) + pad }, high { (int)(range[1] + pad) };

    if (false) {
      cout << "min    : " << min[0] << " " << min[1] << " " << min[2] << "\n"
           << "max    : " << max[0] << " " << max[1] << " " << max[2] << "\n"
           << "range  : " << range[0] << " " << range[1] << " " << range[2] << "\n"
           << "center : " << center[0] << " " << center[1] << " " << center[2] << "\n"
           << "wide   : " << wide << "\n"
           << "high   : " << high << "\n";
    }

    BVH bvh;
    Builder builder(bvh);
    builder.build(global_bbox, bboxes.get(), centers.get(), triangles.size());

    Intersector intersector(bvh, triangles.data());
    Traverser traverser(bvh);

    Vector3 direction(0.0, 0.0, -1);

    Scalar min_distance(0.0), max_distance(range[2] * 2.0f); 

    RGB red { 255, 0, 0 }, blue { 0, 0, 255 }, 
	c1 { red }, c2 { blue };
    RGBs rgbs;

    Points xyzs;
    float zr { max[2] + pad };
    for (int y = (high - 1); y >= 0; --y) {
      for (int x = 0; x < wide; ++x) {
        float xr { (float)(x) + min[0] };
        float yr { (float)(y) + min[1] };
        Vector3 origin(xr, yr, zr);
        Ray ray(origin, direction, min_distance, max_distance);

	xyzs.push_back(Point3D { xr, yr, zr });
	rgbs.push_back(c1);

	auto hit = traverser.traverse(ray, intersector);

	if (hit) {
          auto intersection = hit->intersection;
          auto w = 1.0 - intersection.u - intersection.v;

          auto xyz = xyz_intersection(triangles, 
			              hit->primitive_index,
				      intersection.u,
				      intersection.v,
				      w);
          xyzs.push_back(xyz);
	  rgbs.push_back(c2);
        }
      }
    }

    cout << "xyzs size : " << xyzs.size() << "\n";

    std::ofstream ofs("points-xyzrgb.xyz");
    for (int i = 0; i < xyzs.size(); ++i) {
      ofs << xyzs[i][0] << " " << xyzs[i][1] << " " << xyzs[i][2] << " "
          << rgbs[i][0] << " " << rgbs[i][1] << " " << rgbs[i][2] << "\n";
    }

  }

}


int main() {

  n8m::virtual_3d_scanner_one();     // single mesh view to point cloud

  return 0;

}

