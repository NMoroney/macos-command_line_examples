// © 2024 : github.com/NMoroney
// MIT License 
//

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "ceres/ceres.h"
#include "glog/logging.h"

namespace n8m {

  using ceres::AutoDiffCostFunction;
  using ceres::CostFunction;
  using ceres::Problem;
  using ceres::Solve;
  using ceres::Solver;


  // fit : 
  //   y = ((gain * x) + offset)^gamma
  //
  class gain_offset_gamma_residual {
    public:
      gain_offset_gamma_residual(double digital_count, double luminance)
          : digital_count_(digital_count), luminance_(luminance) {}

      template <typename T>
      bool operator()(const T *const gain,
                      const T *const offset,
                      const T *const gamma,
                      T *residual) const
      {

        residual[0] = luminance_ - pow(((digital_count_ * gain[0]) + offset[0]), gamma[0]);

        return true;
      }

    private:
      const double digital_count_, luminance_;
  };

  void fit_display_model(const char* program_name,
                         const char* name_data) {

    google::InitGoogleLogging(program_name);

    std::ifstream ifs(name_data);

    double digital_count, luminance;
    std::vector<double> digital_counts, luminances;
    while (ifs >> digital_count >> luminance) {
      digital_counts.push_back(digital_count);
      luminances.push_back(luminance);
    }

    // normalize digital counts and luminances to be in the range 0 to 1
    //
    for (int i = 0; i < digital_counts.size(); ++i) {
      digital_counts[i] /= digital_counts.back();
      luminances[i]     /= luminances.back();
    }

    double gain { 1.1 }, offset { 0.05 }, gamma { 1.1 };

    int size = digital_counts.size();
    Problem problem;
    for (int i = 0; i < size; i++) {

      problem.AddResidualBlock(
          new AutoDiffCostFunction<gain_offset_gamma_residual, 1, 1,1,1>(
          new gain_offset_gamma_residual(digital_counts[i], luminances[i])),
          nullptr, &gain, &offset, &gamma);

    }

    Solver::Options options;
    options.max_num_iterations = 1000;
    options.linear_solver_type = ceres::DENSE_QR;

    options.minimizer_progress_to_stdout = true;
    Solver::Summary summary;
    Solve(options, &problem, &summary);

    std::cout<<summary.BriefReport()<<std::endl;
    
    std::cout << "\ndisplay fit :\n"
              << "  gain   : " << gain   << "\n"
              << "  offset : " << offset << "\n"
              << "  gamma  : " << gamma  << "\n\n";

    std::ofstream ofs("temp_out_xyrgb.tsv");
    for (int i = 0; i <= 100; ++i) {
      double x { (double)i / (double)100.0 };
      double y = pow(((x * gain) + offset), gamma);
      ofs << x << "\t" << y << "\t52\t179\t168\n";   // teal
    }

    for (int i = 0; i < digital_counts.size(); ++i) {
      ofs << digital_counts[i] << "\t"
          << luminances[i] << "\t248\t125\t31\n";   // orange
    }
  }

}


int main(int argc, char const *argv[]) {

  n8m::fit_display_model(argv[0], "z31-gray_dc-vs-measured_luminance.tsv");

  return 0;
}


