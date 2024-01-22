// © 2024 : github.com/NMoroney
// MIT License 
//

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <mlpack/core.hpp>

#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/layer/identity.hpp>
#include <mlpack/methods/ann/layer/linear.hpp>
#include <mlpack/methods/ann/loss_functions/mean_squared_error.hpp>
#include <mlpack/methods/ann/ffn.hpp>


namespace n8m {

  using Matrix     = arma::mat;
  using Tokens     = std::vector<std::vector<std::string> >;
  using Labels     = arma::Row<size_t>;
  using Prediction = arma::Row<size_t>;
  using Row        = arma::Row<size_t>;

  using MSE              = mlpack::MeanSquaredError;
  using RandomInitialize = mlpack::RandomInitialization;
  using FFN              = mlpack::FFN<MSE, RandomInitialize>;
  using Linear           = mlpack::Linear;
  using Identity         = mlpack::Identity;


  auto split_string = [] (const std::string& s) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string token;
    while (iss >> token) {
      tokens.push_back(token);
    }
    return tokens;
  };

  void mlpack_read(const std::string& name,
		   Matrix& data) {
    using std::cout;

    std::vector<std::string> lines;
    std::string line;
    std::ifstream ifs(name);
    while (std::getline(ifs, line)) {
      lines.push_back(line);
    }

    Tokens tokens;
    for (auto& line : lines) {
      auto fields = split_string(line);
      tokens.push_back(fields);
    }

    int wide { int(tokens[0].size()) };
    int high { int(lines.size()) };

    cout << "wide : " << wide << "\n";
    cout << "high : " << high << "\n";

    data.resize(wide, high);

    for (auto y = 0; y < tokens.size(); ++y) {
      for (auto x = 0; x < wide; ++x) {
        data(x, y) = std::stod(tokens[y][x]);
      }
    }

    cout << "\ndata :\n";
    cout << "n rows : " << data.n_rows << "\n";
    cout << "n cols : " << data.n_cols << "\n\n";
  }


  void mlpack_spectral_autoencoder() {
    using std::cout;
    using std::to_string;

    cout << "mlpack spectral autoencoder :\n";

    Matrix data, labels;

    std::string name { "munsell_matte_1269-measured_400-700nm-d_10nm.txt" };

    mlpack_read(name, data);
    mlpack_read(name, labels);     // for autoencoding, labels is the same as data

    const size_t input_size        = data.n_rows;
    const size_t output_size       = data.n_rows;
    const size_t hidden_layer_size = 3;

    FFN ffn(MSE(), RandomInitialize(-1,1));


    ffn.Add<Identity>(); 
    ffn.Add<Linear>(hidden_layer_size);   // encoder                         
    ffn.Add<Identity>();
    ffn.Add<Linear>(output_size);         // decoder
    ffn.Add<Identity>();

    ffn.Train(data, labels);

    Matrix encoded;
    ffn.Forward(data, encoded, 0, 1);  // compute 3d encoded data using layers 0 and 1

    cout << "encoded :\n"
         << "n rows  : " << encoded.n_rows << " "
	 << "n cols  : " << encoded.n_cols << "\n";

    std::string tsv { "d1\td2\td3\n" };
    using std::to_string;
    for (auto col = 0; col < encoded.n_cols; ++col) {
      tsv += to_string(encoded(0, col)) + "\t";
      tsv += to_string(encoded(1, col)) + "\t";
      tsv += to_string(encoded(2, col)) + "\n";
    }

    std::ofstream ofs_tsv("autoencoded_3d.tsv");
    ofs_tsv << tsv;
 
    mlpack::data::Save("autoencoder.xml", "model", ffn, false);

  }

}


int main() {

  n8m::mlpack_spectral__autoencoder();            // read data, train auto-encoder and save

  return 0;
}

