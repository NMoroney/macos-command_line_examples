// © 2024 : github.com/NMoroney
// MIT License 
//

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/pcl_config.h>

#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include "happly.h"


namespace n8m {

  using T  = double;
  using Ts = std::vector<T>;
  using Cloud     = pcl::PointCloud<pcl::PointXYZ>;
  using CloudPtr  = Cloud::Ptr;
  using XYZ       = pcl::PointXYZ;
  using Estimator = pcl::MomentOfInertiaEstimation<XYZ>;
  using Filter    = pcl::StatisticalOutlierRemoval<XYZ>;


  std::string to_string(const XYZ& p) {
    return std::string { std::to_string(p.x) + "\t" + 
                         std::to_string(p.y) + "\t" + 
                         std::to_string(p.z) };
  }


  void pcl_outliers_one() {
    using std::cout;
    cout << "pcl outliers one :\n";

    cout << "Point Cloud Library version number : "
         << PCL_VERSION_PRETTY << "\n";

    happly::PLYData plyIn("../../data/tverse-2288923-triceratops-4k.ply");

    Ts xs = plyIn.getElement("vertex").getProperty<T>("x");
    Ts ys = plyIn.getElement("vertex").getProperty<T>("y");
    Ts zs = plyIn.getElement("vertex").getProperty<T>("z");

    T rand_max { (T)RAND_MAX };
    int number_rand { (int)((T)xs.size() * 0.1) },
        total_count { (int)xs.size() + number_rand };

    cout << "xs size     : " << xs.size() << "\n"
         << "number rand : " << number_rand << "\n"
         << "total count : " << total_count << "\n";

    CloudPtr cp(new Cloud());
    cp->width    = total_count;
    cp->height   = 1;
    cp->is_dense = false;
    cp->points.resize(cp->width * cp->height);

    for (int i = 0; i < xs.size(); ++i) {
      cp->points[i].x = xs[i];
      cp->points[i].y = ys[i];
      cp->points[i].z = zs[i];
    }

    Estimator estimator;
    estimator.setInputCloud(cp);
    estimator.compute();

    XYZ min, max;
    estimator.getAABB(min, max);
    XYZ range { max.x - min.x, max.y - min.y, max.z - min.z };

    cout << "min   : " << to_string(min)   << "\n"
         << "max   : " << to_string(max)   << "\n"
         << "range : " << to_string(range) << "\n";

    for (int i = xs.size(); i < total_count; ++i) {
      T rx { (range.x * ((T)rand() / rand_max)) + min.x },
        ry { (range.y * ((T)rand() / rand_max)) + min.y },
        rz { (range.z * ((T)rand() / rand_max)) + min.z };
      cp->points[i].x = rx;
      cp->points[i].y = ry;
      cp->points[i].z = rz;
    }

    CloudPtr filtered(new Cloud());

    Filter filter;
    filter.setInputCloud(cp);
    filter.setMeanK(50);
    filter.setStddevMulThresh(1.0);
    filter.filter(*filtered);

    cout << "filtered width : " << filtered->width << "\n";

    // an aside : std::set<XYZ> fails to compile
    //
    using Point3D = std::array<T, 3>;
    std::set<Point3D> points;
    for (auto point : *(filtered)) {
      points.insert(Point3D { point.x, point.y, point.z });
    }

    std::ofstream ofs("temp_01.xyz");
    for (auto point : *(cp)) {
      ofs << point.x << " " << point.y << " " << point.z << "\n";
    }

    std::ofstream ofs_two("temp_01_filtered.xyz");
    for (auto point : *(filtered)) {
      ofs_two << point.x << " " << point.y << " " << point.z << "\n";
    }

    std::ofstream ofs_rgb("temp_01_xyz_rgb.xyz");
    for (auto point : *(cp)) {
      ofs_rgb << point.x << " " << point.y << " " << point.z << " ";
      Point3D pt { point.x, point.y, point.z };
      if (points.find(pt) != points.end()) {
        ofs_rgb << "52 179 168\n";
      } else {
        ofs_rgb << "248 125 31\n"; 
      } 
    }

  }

}

int main() {

  n8m::pcl_outliers_one();   // read mesh vertices and add some noise based on
                             // bounding box. then filter with outlier removal

  return 0;

}
