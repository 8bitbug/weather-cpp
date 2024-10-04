#include "include/extract/extract.hpp"
#include "include/fetch/fetch.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

auto ISOTime() -> std::string {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  time_t now_time = std::chrono::system_clock::to_time_t(now);

  std::tm tm_utc = *std::gmtime(&now_time);

  std::ostringstream oss;
  oss << std::put_time(&tm_utc, "%Y-%m-%dT%H:00");

  return oss.str();
};

auto open_meteo_url(const std::string &loc) -> std::string {
  return "https://api.open-meteo.com/v1/forecast?latitude=" +
         std::to_string(extract::decimal(loc, 0)) +
         "&longitude=" + std::to_string(extract::decimal(loc, 1)) +
         ",&hourly=temperature_2m";
}

auto main(void) -> int {
  nlohmann::json ipinfo = fetch::json("https://ipinfo.io/json");
  const std::string loc = ipinfo["loc"].dump();

  nlohmann::json weatherinfo = fetch::json(open_meteo_url(loc).c_str());

  const std::vector<std::string> times =
      weatherinfo["hourly"]["time"].get<std::vector<std::string>>();
  const std::vector<double> temparatures =
      weatherinfo["hourly"]["temperature_2m"].get<std::vector<double>>();

  bool found = false;
  for (size_t i = 0; i < times.size(); i++) {
    if (times[i] == ISOTime()) {
      std::cout << "Tempature at " << temparatures[i] << " C" << std::endl;
      found = true;
      break;
    }
  }

  if (!found) {
    std::cout << "Could not find temparature" << std::endl;
  }

  return 0;
}
