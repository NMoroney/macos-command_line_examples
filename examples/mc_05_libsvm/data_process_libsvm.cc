// © 2024 : github.com/NMoroney
// MIT License 
//

#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


namespace n8m {

  using RGB  = std::array<int, 3>;
  using RGBs = std::vector<RGB>;
  using T    = float;
  using nRGB = std::array<T, 3>;


  void libsvm_format_input() {
    using std::cout;
    cout << "libsvm format data :\n";

    auto to_scaled = [] (const RGB& rgb) {
      nRGB nrgb { 2 * (((T)rgb[0] / (T)255) - (T)0.5),
                  2 * (((T)rgb[1] / (T)255) - (T)0.5),
                  2 * (((T)rgb[2] / (T)255) - (T)0.5) };
      return nrgb;
    };

    auto to_string = [] (const std::string& label, 
                         const nRGB& nrgb) {
      std::string s { label + " " };
      s += "1:" + std::to_string(nrgb[0]) + " "
           "2:" + std::to_string(nrgb[1]) + " "
           "3:" + std::to_string(nrgb[2]) + "\n";
      return s;
    };

    // format training data for libsvm
    //
    std::string i1 { "../../data/rgbs_train_orange.tsv" },
                i2 { "../../data/rgbs_train_other.tsv" },
                o1 { "train_orange_svm.txt" };

    std::ifstream ifs_i1(i1), ifs_i2(i2);
    std::ofstream ofs_o1(o1);

    RGB rgb;
    while (ifs_i1 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o1 << to_string("+1", to_scaled(rgb));
    }
    while (ifs_i2 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o1 << to_string("-1", to_scaled(rgb));
    }

    // format validation data for libsvm
    //
    std::string i3 { "../../data/rgbs_validate_orange.tsv" },
                i4 { "../../data/rgbs_validate_other.tsv" },
                o2 { "validate_orange_svm.txt" };
    std::ifstream ifs_i3(i3), ifs_i4(i4);
    std::ofstream ofs_o2(o2);

    while (ifs_i3 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o2 << to_string("+1", to_scaled(rgb));
    }
    while (ifs_i4 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o2 << to_string("-1", to_scaled(rgb));
    }

    // format grid sampling for libsvm, including a +1 dummy variable
    //
    std::string i5 { "../../data/grid_rgb_17x17x17.tsv" },
                o3 { "grid_svm.txt" };

    std::ifstream ifs_i5(i5);
    std::ofstream ofs_o3(o3);

    while (ifs_i5 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o3 << to_string("+1", to_scaled(rgb));
    }

  }


  void libsvm_format_grid() {
    using std::cout;
    cout << "libsvm format grid :\n";

    std::ifstream ifs_i1("grid_predicted.txt"), ifs_i2("../../data/grid_rgb_17x17x17.tsv");
    std::ofstream ofs("grid_xyzrgb.tsv");

    std::vector<int> labels;
    int label;
    while (ifs_i1 >> label) {
      labels.push_back(label);
    }

    ofs << "x\ty\tz\tr\tg\tb\n";
    RGB rgb;
    int i { 0 };
    while (ifs_i2 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs << rgb[0] << "\t" << rgb[1] << "\t" << rgb[2] << "\t";
      if (labels[i] == 1) {
        ofs << "248\t125\t31\n";
      } else {
        ofs << "128\t128\t128\n";
      } 
      ++i;
    }

  }

}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    std::cout << "\n"
              << "data_process_libsvm -mode\n"
              << "\n"
              << "mode = 1 to format input data\n"
              << "mode = 2 to format grid data\n"
              << "\n";
  } else {

    if (std::stoi(argv[1]) == 1) {
      n8m::libsvm_format_input();
    }
    if (std::stoi(argv[1]) == 2) {
      n8m::libsvm_format_grid();
    }

  }

  return 0;

}

