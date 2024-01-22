// © 2024 : github.com/NMoroney
// MIT License 
//

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include <armadillo>


namespace n8m {

  using T  = float;
  using Ts = std::vector<T>;
  using Point3D = std::array<T, 3>;
  using Points  = std::vector<Point3D>;


  // attribution :
  //   https://math.stackexchange.com/questions/1585975/how-to-generate-random-points-on-a-sphere
  // 
  Points random_points_on_unit_sphere_surface(const int n) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, 1);

    Points samples;
    for (int i = 0; i < n; ++i) {
      T x { (T)distribution(generator) }, 
        y { (T)distribution(generator) }, 
        z { (T)distribution(generator) };

      if ((x != 0) && (y != 0) && (z != 0)) {
        T length { (T)sqrt((x * x) + (y * y) + (z * z)) };

        x *= (T)1 / length;
        y *= (T)1 / length;
        z *= (T)1 / length;

        samples.push_back(Point3D { x, y, z });
      }
    }

    return samples;
  }

  void as_offset(Points& ps, const T ox, const T oy, const T oz) {
    for (auto& p : ps) {
      p[0] += ox;
      p[1] += oy;
      p[2] += oz;
    }
  }

  void as_scaled(Points& ps, const T s) {
    for (auto& p : ps) {
      p[0] *= s;
      p[1] *= s;
      p[2] *= s;
    }
  }

  void as_jittered(Points& ps, const T amount) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, amount);

    for (auto& p : ps) {
      T noise { (T)distribution(generator) };
      p[0] += (p[0] * noise);
      p[1] += (p[1] * noise);
      p[2] += (p[2] * noise);
    }
  }

  // attribution : 
  //   https://paulbourke.net/geometry/circlesphere/spheretest.c
  //
  bool fit_sphere_to_4_points(const Point3D& a,
                              const Point3D& b,
                              const Point3D& c,
                              const Point3D& d,
                              Point3D& center, T& radius) {

    arma::mat m { { a[0], a[1], a[2], 1 },
                  { b[0], b[1], b[2], 1 },
                  { c[0], c[1], c[2], 1 },
                  { d[0], d[1], d[2], 1 } };
    auto m11 = det(m);

    arma::vec n(4);
    for (int i = 0; i < 4; ++i) {
      n(i) = (m(i, 0) * m(i, 0)) +
             (m(i, 1) * m(i, 1)) +
             (m(i, 2) * m(i, 2));
    }

    arma::mat p {  { n[0], a[1], a[2], 1 },
                   { n[1], b[1], b[2], 1 },
                   { n[2], c[1], c[2], 1 },
                   { n[3], d[1], d[2], 1 } };
    auto m12 = det(p);

    arma::mat q { { a[0], n[0], a[2], 1 },
                  { b[0], n[1], b[2], 1 },
                  { c[0], n[2], c[2], 1 },
                  { d[0], n[3], d[2], 1 } };
    auto m13 = det(q);
   
    arma::mat r { { a[0], a[1], n[0], 1 },
                  { b[0], b[1], n[1], 1 },
                  { c[0], c[1], n[2], 1 },
                  { d[0], d[1], n[3], 1 } };
    auto m14 = det(r);

    arma::mat s {  { n[0], a[0], a[1], a[2] },
                   { n[1], b[0], b[1], b[2] },
                   { n[2], c[0], c[1], c[2] },
                   { n[3], d[0], d[1], d[2] } };
    auto m15 = det(s);

    if (m11 != 0) {
        center[0] = (T)(0.5 * m12 / m11);
        center[1] = (T)(0.5 * m13 / m11);
        center[2] = (T)(0.5 * m14 / m11);

        radius = (T)(sqrt((center[0] * center[0]) +
                          (center[1] * center[1]) +
                          (center[2] * center[2]) - (m15 / m11)));
    }

    return m11 != 0;
  }

  // A variation on : https://en.wikipedia.org/wiki/Theil–Sen_estimator
  // 
  void fit_sphere_to_points(const Points& points, const int number_fits, 
                            Point3D& center, T& radius) {
    Points ps { points };
    std::random_shuffle(ps.begin(), ps.end());

    Ts xs, ys, zs, rs;

    int k { 0 }, i { 0 };
    auto reset { ps.size() - 5 };;
    Point3D c;
    T r;
    while (k < number_fits) {
      fit_sphere_to_4_points(ps[i], ps[i + 1], ps[i + 2], ps[i + 3], c, r);

      xs.push_back(c[0]);
      ys.push_back(c[1]);
      zs.push_back(c[2]);
      rs.push_back(r);

      i += 4;
      ++k;

      if (i > reset) {
        std::random_shuffle(ps.begin(), ps.end());
        i = 0;
      }
    }

    auto median = [] (const Ts& ts) {
      Ts data(ts);  // temporary local copy
      auto n = data.size() / 2;
      nth_element(data.begin(), data.begin() + n, data.end());
      return *(data.begin() + n);
    };

    center[0] = median(xs);
    center[1] = median(ys);
    center[2] = median(zs);
    radius = median(rs);
  }

  void fit_3d_points_to_sphere_one() {
    using std::cout;
    cout << "fit 3d points to sphere one :\n";

    int n { 500 };
    auto samples = random_points_on_unit_sphere_surface(n);

    as_jittered(samples, 0.1);
    as_scaled(samples, 10.0);
    as_offset(samples, 3.0, 4.0, 5.0);

    cout << "samples size : " << samples.size() << "\n";

    std::ofstream ofs("temp_points_3d.xyz");
    for (auto s : samples) {
      ofs << s[0] << "\t" << s[1] << "\t" << s[2] << "\n";
    }

    Point3D cf;
    T rf;
    int number_fits { 1000 };

    fit_sphere_to_points(samples, number_fits, cf, rf);

    cout << "\n"
         << "center fit : " << cf[0] << " " << cf[1] << " " << cf[2] << "\n"
         << "radius fit : " << rf << "\n";

  }

}


int main() {

  n8m::fit_3d_points_to_sphere_one();

  return 0;

}

