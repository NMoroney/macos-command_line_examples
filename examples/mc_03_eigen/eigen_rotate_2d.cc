// © 2024 : github.com/NMoroney
// MIT License 
//

// * https://eigen.tuxfamily.org/dox/classEigen_1_1Rotation2D.html
//

#include <array>
#include <fstream>
#include <iostream>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/Geometry>


namespace n8m {

  using T = float;
  using Point2D = std::array<T, 2>;
  using Points  = std::vector<Point2D>;


  Points generate_rose_sinusoid(const T n,
                                const T d,
                                const T a,
                                const T max_radians,
                                const int steps) {
    T k { n / d }, radians_step { max_radians / (T)steps }, theta { 0 };
    Points samples;
    for (int i = 0; i < steps; ++i) {
      T x { a * cos(k * theta) * cos(theta) }, 
        y { a * cos(k * theta) * sin(theta) };
      samples.push_back(Point2D { x, y });
      theta += radians_step;
    }
    return samples;
  }

  Points to_rotated_2d(const Points& xys, 
                       const T radians) {

    Eigen::Rotation2D<T> rotation_2d(radians);
    auto m = rotation_2d.toRotationMatrix();

    if (true) { 
      std::cout << "radians : " << radians << "\n" << m << "\n"; 
    }

    Points rotated;
    for (auto xy : xys) {
      T rx { (xy[0] * m(0,0)) + (xy[1] * m(0,1)) },
        ry { (xy[0] * m(1,0)) + (xy[1] * m(1,1)) };
      rotated.push_back(Point2D { rx, ry });
    }

    return rotated;
  }


  void eigen_rotate_2d() {
    using std::cout;
    cout << "eigen rotate 2d :\n";

    cout << "eigen version :\n" 
         << "  world : " << EIGEN_WORLD_VERSION << "\n"
         << "  major : " << EIGEN_MAJOR_VERSION << "\n"
         << "  minor : " << EIGEN_MINOR_VERSION << "\n\n";

    T n { 3 }, d { 1 }, a { 10 }, pi { (T)acos(-1) },
      max_radians { 2 * pi };
    int steps { 1000 };

    auto samples = generate_rose_sinusoid(n, d, a, max_radians, steps);

    T degrees { 60 };
    T radians { (degrees * pi)/(T)180 };
    auto rotated = to_rotated_2d(samples, radians);

    T scale { 0.5 };
    for (auto& r : rotated) {
      r[0] *= scale;
      r[1] *= scale;
    }

    std::ofstream ofs("temp_xy_rgb.tsv");
    ofs << "x\ty\tr\tg\tb\n";
    for (auto s : samples) {
      ofs << s[0] << "\t" << s[1] << "\t52\t179\t168\n";   // teal
    }
    for (auto r : rotated) {
      ofs << r[0] << "\t" << r[1] << "\t248\t125\t31\n";   // orange
    }

  }

}

int main() {

  n8m::eigen_rotate_2d();    // generate rose sinusoid XY sampling and create
                             // eigen 2D rotated (and scaled) data 

  return 0;

}

