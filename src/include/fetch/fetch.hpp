#ifndef FETCH_HPP
#define FETCH_HPP

#include <nlohmann/json.hpp>

namespace fetch {
auto json(const char *url) -> nlohmann::json;
}

#endif
