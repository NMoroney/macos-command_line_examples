// © 2024 : github.com/NMoroney
// MIT License 
//

#include <iostream>

namespace n8m {

  void hello_world() {

    std::cout << "\n\n  "
              << (char)0xE1 << (char)0x9A << (char)0xBA    // haglazh_h
              << (char)0xC6 << (char)0x8F                  // upsidedown_e
              << (char)0xE1 << (char)0x92 << (char)0xB9    // mwaa_l
              << (char)0xE1 << (char)0x92 << (char)0xB9    // mwaa_l
              << (char)0xE2 << (char)0x97 << (char)0x89    // fisheye_o
              << "\n  "
              << (char)0xD7 << (char)0xA9                  // shin_w
              << (char)0xE2 << (char)0x97 << (char)0x89    // fisheye_o
              << (char)0xE2 << (char)0x84 << (char)0x9C    // blackletter_r
              << (char)0xE1 << (char)0x92 << (char)0xB9    // mwaa_l
              << (char)0xE2 << (char)0x82 << (char)0xAB    // dong_d
              << "\n\n";
  }

}

int main() {

  n8m::hello_world();

  return 0;
}
