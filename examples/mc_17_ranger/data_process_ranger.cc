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


  void ranger_format_input() {
    using std::cout;
    cout << "ranger format data :\n";

    auto to_string = [] (const RGB& rgb) {
      std::string s { std::to_string(rgb[0]) + "\t" +
                      std::to_string(rgb[1]) + "\t" +
                      std::to_string(rgb[2]) + "\t" };
      return s;
    };

    // format training data for ranger
    //
    std::string i1 { "../../data/rgbs_train_orange.tsv" },
                i2 { "../../data/rgbs_train_other.tsv" },
                o1 { "train_orange_ranger.data" };

    std::ifstream ifs_i1(i1), ifs_i2(i2);
    std::ofstream ofs_o1(o1);

    ofs_o1 << "red\tgreen\tblue\tname\n";

    RGB rgb;
    while (ifs_i1 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o1 << to_string(rgb) << "1\n";
    }
    while (ifs_i2 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o1 << to_string(rgb) << "2\n";
    }

    // format validation data for ranger
    //
    std::string i3 { "../../data/rgbs_validate_orange.tsv" },
                i4 { "../../data/rgbs_validate_other.tsv" },
                o2 { "validate_orange_ranger.data" };
    std::ifstream ifs_i3(i3), ifs_i4(i4);
    std::ofstream ofs_o2(o2);

    ofs_o2 << "red\tgreen\tblue\tname\n";

    while (ifs_i3 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o2 << to_string(rgb) << "1\n";
    }
    while (ifs_i4 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o2 << to_string(rgb) << "2\n";
    }

    // format grid sampling for ranger, including a +1 dummy variable
    //
    std::string i5 { "../../data/grid_rgb_17x17x17.tsv" },
                o3 { "grid_ranger.data" };

    std::ifstream ifs_i5(i5);
    std::ofstream ofs_o3(o3);

    ofs_o3 << "red\tgreen\tblue\tname\n";

    while (ifs_i5 >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs_o3 << to_string(rgb) << "1\n";    // dummy added
    }

  }


  void ranger_format_grid() {
    using std::cout;
    cout << "ranger format grid :\n";

    std::ifstream ifs_i1("grid.prediction"), ifs_i2("../../data/grid_rgb_17x17x17.tsv");
    std::ofstream ofs("grid_xyzrgb.tsv");

    std::vector<int> labels;

    int label;
    std::string s;
    ifs_i1 >> s;
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


  void ranger_format_lab_grid() {
    using std::cout;
    cout << "ranger format lab grid :\n";

    std::ifstream ifs_i1("lab_grid.prediction"), ifs_i2("lab_grid-abl_rgb.tsv");
    std::ofstream ofs("lab_grid_abl_rgb.tsv");

    std::vector<int> labels;

    int label;
    std::string s;
    ifs_i1 >> s;
    while (ifs_i1 >> label) {
      labels.push_back(label);
    }

    ofs << "a*\tb*\tL*\tr\tg\tb\n";
    T a, b, l;
    RGB rgb;
    int i { 0 };
    while (ifs_i2 >> a >> b >> l >> rgb[0] >> rgb[1] >> rgb[2]) {
      ofs << a << "\t" << b << "\t" << l << "\t";
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
              << "data_process_ranger -mode\n"
              << "\n"
              << "mode = 1 to format input data\n"
              << "mode = 2 to format grid data\n"
              << "mode = 3 to format lab grid data\n"
              << "\n";
  } else {

    if (std::stoi(argv[1]) == 1) {
      n8m::ranger_format_input();
    }
    if (std::stoi(argv[1]) == 2) {
      n8m::ranger_format_grid();
    }
    if (std::stoi(argv[1]) == 3) {
      n8m::ranger_format_lab_grid();
    }

  }

  return 0;
}

