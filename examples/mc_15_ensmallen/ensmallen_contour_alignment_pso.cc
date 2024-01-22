// © 2024 : github.com/NMoroney
// MIT License 
//

#include <cmath>
#include <cmath>
#include <fstream>
#include <iostream>

#include <ensmallen.hpp>

#include <Eigen/Dense>
#include <Eigen/Geometry>   // 2D rotation

#include "KDTreeVectorOfVectorsAdaptor.h"


namespace n8m {

  using T       = double;
  using Point2D = std::array<T, 2>;
  using Points  = std::vector<Point2D>;
  using VVector = std::vector<std::vector<T> >;


  VVector to_vvector(const Points& points) {
    VVector vv;
    for (auto p : points) {
      std::vector<T> v { p[0], p[1] };
      vv.push_back(v);
    }
    return vv;
  }

  T pi { (T)acos(-1) }, rand_max { (T)RAND_MAX };
  auto degrees_to_radians = [] (const T d) { return (d * pi) / (T)180; };
  auto radians_to_degrees = [] (const T r) { return (r * (T)180) / pi; };

  Points to_rotated_2d(const Points& xys, 
                       const T radians) {

    Eigen::Rotation2D<T> rotation_2d(radians);
    auto m = rotation_2d.toRotationMatrix();

    Points rotated;
    for (auto xy : xys) {
      T rx { (xy[0] * m(0,0)) + (xy[1] * m(0,1)) },
        ry { (xy[0] * m(1,0)) + (xy[1] * m(1,1)) };
      rotated.push_back(Point2D { rx, ry });
    }

    return rotated;
  }

  T as_random_rotated(Points& ps) {
    T degrees { (T)360 * ((T)rand() / rand_max) };
    auto rotated = to_rotated_2d(ps, degrees_to_radians(degrees));
    ps = rotated;
    return degrees;
  }

  void bounding_box(const Points& ps,
                    Point2D& min,
                    Point2D& max) {
    min = ps[0];
    max = ps[0];
    for (auto p : ps) {
      if (p[0] < min[0]) { min[0] = p[0]; }
      if (p[1] < min[1]) { min[1] = p[1]; }
      if (p[0] > max[0]) { max[0] = p[0]; }
      if (p[1] > max[1]) { max[1] = p[1]; }
    }
  }

  void as_jittered(Points& points, const T fraction) {
    Point2D min, max;
    bounding_box(points, min, max);
    Point2D range { max[0] - min[0], max[1] - min[1] };
    auto max_r = (range[0] > range[1] ? range[0] : range[1] );
    T amount { max_r * fraction }, half { amount / (T)2 };
    for (auto& p : points) {
      T drx = (amount * ((T)rand() / rand_max)) - half;
      T dry = (amount * ((T)rand() / rand_max)) - half;
      p[0] += drx;
      p[1] += dry;
    }   
  }

  void as_auto_centered(Points& ps) {
    Point2D min, max;
    bounding_box(ps, min, max);
    Point2D range { max[0] - min[0], max[1] - min[1] };
    T ox { min[0] + (range[0] / (T)2) },
      oy { min[1] + (range[1] / (T)2) };
    for (auto p : ps) {
      p[0] -= ox;
      p[1] -= oy;
    }
  }


  template <class T>
  class KNearestNeighbor {
    public:
      using VVector   = std::vector<std::vector<T> >;
      using KDTree    = KDTreeVectorOfVectorsAdaptor<VVector>;
      using Indices   = std::vector<size_t>;
      using Distances = std::vector<double>;

      Distances distances_squared() { return distances_squared_; }

      KNearestNeighbor(const int dim, const VVector& vv) :
        tree(dim, vv, max_leaf) { }

      Indices operator() (std::vector<T>& query) {
        Indices   indices(number_neighbors);
        Distances dists_sqr(number_neighbors);
        nanoflann::KNNResultSet<double> resultSet(number_neighbors);
        resultSet.init(&indices[0], &dists_sqr[0] );
        tree.index->findNeighbors(resultSet,
                                  &query[0],
                                  nanoflann::SearchParameters(max_leaf));
        distances_squared_ = dists_sqr;
        return indices;
      }

      int max_leaf { 10 }, number_neighbors { 3 };

    private:
      KDTree tree;
      KNearestNeighbor() { }
      Distances distances_squared_;
  };



  struct SummedNearestDistanceFunction {

    SummedNearestDistanceFunction(const VVector& vv, const Points& original_) : 
        knn(2, vv), original(original_) { 
      knn.number_neighbors = 1;
    }

    double Evaluate(const arma::mat& x) {

      T degrees { (T)x(0,0) }, radians { degrees_to_radians(degrees) };

      auto rotated = to_rotated_2d(original, radians);

      VVector v2;
      for (auto p : rotated) {
        std::vector<T> vt { p[0], p[1] };
        v2.push_back(vt);
      }

      T sum = 0;
      for (auto query : v2) {
        auto indices = knn(query);
        auto ds = knn.distances_squared();
        sum += ds[0];
      }

      if (is_verbose) {
        std::cout << degrees << " " << sum << "\n";
      }

      if (count == 0) { 
        max = sum;
      } else {
        if (sum > max) { max = sum; }
      }

      if (x(0,0) <   0) { sum = max; }
      if (x(0,0) > 360) { sum = max; }
      ++count;

      return sum;
    }

    KNearestNeighbor<T> knn;
    Points original;
    T max { 0 };
    int count { 0 };
    bool is_verbose { false };
  };

  void to_xy_rgb(const char* name,
                 const Points& one,
                 const Points& two) {

    std::ofstream ofs_xyr(name);
    ofs_xyr << "x\ty\tred\tgreen\tblue\n";

    for (auto p : one) {
      ofs_xyr << p[0] << "\t" << p[1] << "\t" << "248\t125\t31\n";
    }

    for (auto p : two) {
      ofs_xyr << p[0] << "\t" << p[1] << "\t" << "52\t179\t168\n";
    }
  }

  void contour_alignment_one() {
    using std::cout;
    cout << "contour alignment one :\n";

    std::ifstream ifs("california_xy.tsv");
    Points ca;
    T px, py;
    while (ifs >> px >> py) {
      ca.push_back(Point2D { px, py });
    }

    cout << "ca size : " << ca.size() << "\n";

    as_auto_centered(ca);

    Points original;
    for (auto p : ca) {
      original.push_back(p);
    }

    T fraction { 0.05 };
    as_jittered(ca, fraction);

    srand(43672);
    auto rd = as_random_rotated(ca);

    VVector v1;
    for (auto p : ca) {
      std::vector<T> vt { p[0], p[1] };
      v1.push_back(vt);
    }

    to_xy_rgb("initial_xy_rgb.tsv", ca, original);

    cout << "random degrees : " << rd << "\n";

    arma::mat x("45");   // initial degree estimate

    ens::LBestPSO optimizer(32, 0, 360, 1000, 150, 0.1, 2.05, 2.05);

    SummedNearestDistanceFunction f(v1, original);
    auto result = optimizer.Optimize(f, x);

    cout << "f count : " << f.count << "\n";

    T min_f { (T)x(0,0) }; 
    cout << "Minimum of summed nearest distance function found with "
         << "particle swarm optimization is "
         << std::fixed << min_f << "\n";


    auto fitted = to_rotated_2d(original, degrees_to_radians(min_f));

    to_xy_rgb("aligned_xy_rgb.tsv", ca, fitted);
  }

}


int main() {

  n8m::contour_alignment_one();  // use particle swarm optimization to align two 2D contours

  return 0;

}

