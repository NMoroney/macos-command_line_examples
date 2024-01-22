// © 2024 : github.com/NMoroney
// MIT License 
//

#include <iostream>
#include <string>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <opencv2/opencv.hpp>

namespace n8m {

  void ocr_tesseract_one(const char* cc) {
    using std::cout;
    cout << "ocr tessearct one :\n";

    auto gray = cv::imread(cc);

    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
    ocr->SetImage(gray.data, gray.cols, gray.rows, 3, gray.step);

    auto text = std::string(ocr->GetUTF8Text());

    cout << "\nocr result :\n" << text << "\n";

    ocr->End();
  }

}


int main(int argc, char* argv[]) {

  if (argc == 2) {
    n8m::ocr_tesseract_one(argv[1]);
  } else {
    std::cout << "\n\nocr_tesseract in\n\n";
  }

  return 0;

}
