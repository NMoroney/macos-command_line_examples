// © 2024 : github.com/NMoroney
// MIT License 
//

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include <igl/readPLY.h>
#include <igl/blue_noise.h>
#include <igl/per_vertex_normals.h>
#include <igl/barycentric_interpolation.h>


namespace n8m {

  using T = double;
  using Point3D = std::array<T, 3>;
  using Points  = std::vector<Point3D>;


  double estimate_blue_noise_radius(const Eigen::MatrixXd& V,
                                    const Eigen::MatrixXi& F,
                                    const int n) {
    Eigen::VectorXd A;
    igl::doublearea(V, F, A);
    double pi { acos(-1) };
    return sqrt((A.sum() * 0.5 / (n * 0.6162910373)) / pi);     
  }

  Points blue_noise_sample_surface(const Eigen::MatrixXd& V,
                                   const Eigen::MatrixXi& F,
                                   const int n,
                                   const int seed) {
    srand(seed);

    Eigen::MatrixXd N;
    igl::per_vertex_normals(V,F,N);

    Eigen::MatrixXd P_blue, N_blue;

    auto radius = n8m::estimate_blue_noise_radius(V, F, n);

    if (true) {
      std::cout << "number points     : " << n << "\n"
                << "blue noise radius : " << radius << "\n";
    }

    Eigen::MatrixXd B;     // barycentric coordinates
    Eigen::VectorXi I;     // face indices
    igl::blue_noise(V,F,radius,B,I,P_blue);

    igl::barycentric_interpolation(N,F,B,I,N_blue);
    N_blue.rowwise().normalize();

    Points samples;
    for (int row = 0; row < P_blue.rows(); ++row) {
      Point3D p { P_blue(row, 0), P_blue(row, 1), P_blue(row, 2) };
      samples.push_back(p);
    }
    return samples;
  }

  void libigl_blue_noise_one() {
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    igl::readPLY("../../data/tverse-2288923-triceratops-4k.ply", V, F);

    int number_points { 5000 }, seed { 1979 };
    auto samples = n8m::blue_noise_sample_surface(V, F, number_points, seed);

    std::ofstream ofs("temp_blue.xyz");
    for (auto s : samples) {
      ofs << s[0] << "\t" << s[1] << "\t" << s[2] << "\n";
    }
  }

}


int main(int argc, char *argv[]) {

  n8m::libigl_blue_noise_one();

}

// [x] works with non-manifold meshes
//

