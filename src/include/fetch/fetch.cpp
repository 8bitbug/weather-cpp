#include "fetch.hpp"

#include <curl/curl.h>
#include <iostream>

auto WriteCallBack(
    void *contents,
    size_t size,
    size_t nmemb,
    std::string *userp
) -> size_t {
  size_t totalSize = size * nmemb;
  userp->append(static_cast<char *>(contents), totalSize);
  return totalSize;
}

struct request_params {
private:
  std::string m_url;

public:
  request_params(const char *url) : m_url(url), json() {}

  CURL *curl;
  CURLcode res;
  std::string json;

  auto getURL() const -> std::string { return m_url; }
};

auto fetch::json(const char *url) -> nlohmann::json {
  request_params api(url);

  api.curl = curl_easy_init();
  if (!api.curl) {
    std::cerr << "Failed to initialize CURL." << std::endl;
    throw std::runtime_error("CURL initialization failed");
  }

  curl_easy_setopt(api.curl, CURLOPT_URL, api.getURL().c_str());
  curl_easy_setopt(api.curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
  curl_easy_setopt(api.curl, CURLOPT_WRITEDATA, &api.json);

  api.res = curl_easy_perform(api.curl);
  curl_easy_cleanup(api.curl);

  if (api.res == CURLE_OK) {
    try {
      return nlohmann::json::parse(api.json);
    } catch (const nlohmann::json::parse_error &e) {
      std::cerr << "JSON Parse error: " << e.what() << std::endl;
      throw std::runtime_error("JSON parsing failed");
    }
  } else {
    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(api.res)
              << std::endl;
    throw std::runtime_error("CURL request failed");
  }
}
