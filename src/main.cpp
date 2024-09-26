#include "include/extract/extract.hpp"
#include "include/fetch/fetch.hpp"
#include <iostream>

auto main(void) -> int {
  nlohmann::json ipinfo = fetch::json("https://ipinfo.io/json");
  std::cout << "Info: " << ipinfo;

  return 0;
}
