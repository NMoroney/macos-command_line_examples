// © 2024 : github.com/NMoroney
// MIT License 
//

#include <array>
#include <fstream>
#include <iostream>
#include <vector>

#include <opencv2/opencv.hpp>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/pcl_config.h>
#include <pcl/common/transforms.h>

#include <pcl/visualization/pcl_visualizer.h>


namespace n8m {

  using T = float;
  using Point3D = std::array<T, 3>;
  using Points  = std::vector<Point3D>;

  using XYZRGB   = pcl::PointXYZRGB;
  using Cloud    = pcl::PointCloud<XYZRGB>;
  using CloudPtr = pcl::PointCloud<XYZRGB>::Ptr;
  using Viewer   = pcl::visualization::PCLVisualizer;


  std::string about(const cv::Mat& m) {
    std::string s;
    using std::to_string;
    s += "rows     : " + to_string(m.rows)       + "\n" +
         "cols     : " + to_string(m.cols)       + "\n" +
         "channels : " + to_string(m.channels()) + "\n";
 
    return s;
  }

  void pcl_color_cloud_one() {
    using std::cout;
    cout << "pcl color cloud one :\n";

    auto bgr   = cv::imread("IMG_7884-hello-640px.jpg", 1);
    auto depth = cv::imread("IMG_7884-hello-640px_depth.jpg", 1);

    cv::Mat gray;
    cv::cvtColor(depth, gray, cv::COLOR_BGR2GRAY);

    cout << "bgr  :\n" << about(bgr)  << "\n"
         << "gray :\n" << about(gray) << "\n";

    CloudPtr cp(new Cloud());
    cp->width    = bgr.rows * bgr.cols;
    cp->height   = 1;
    cp->is_dense = false;
    cp->points.resize(cp->width * cp->height);
 
    T z_scale { 0.75 }; 
    for (int r = 0, k = 0; r < gray.rows; ++r) {
      for (int c = 0; c < gray.cols; ++c, ++k) {
        cp->points[k].x = c;
        cp->points[k].y = bgr.rows - r;
        auto gz = gray.at<unsigned char>(r, c);
        cp->points[k].z = (T)(gz) * z_scale;

        cv::Vec3b pixel = bgr.at<cv::Vec3b>(r, c);
        std::uint32_t color = ((std::uint32_t)(pixel[2]) << 16 |
                               (std::uint32_t)(pixel[1]) <<  8 |
                               (std::uint32_t)(pixel[0]));
        cp->points[k].rgb = *reinterpret_cast<float*>(&color);
      }
    } 


    Viewer viewer("PCL : Color Cloud Viewer");

    viewer.addPointCloud(cp, "source");

    viewer.addCoordinateSystem(1.0, "original", 0);
    viewer.setBackgroundColor(1.0, 1.0, 1.0, 0);

    auto point_size = pcl::visualization::PCL_VISUALIZER_POINT_SIZE;

    viewer.setPointCloudRenderingProperties(point_size, 3, "source");

    while (!viewer.wasStopped ()) {
      viewer.spinOnce ();
    }

  }

}


int main() {

  n8m::pcl_color_cloud_one();   // read in image and corresponding MiDaS depth estimation,
                                // use these images to generate an XYZRGB point cloud,
                                // and start an interactive viewer to visualize

  return 0;

}
