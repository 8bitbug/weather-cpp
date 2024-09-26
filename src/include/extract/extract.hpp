#ifndef EXTRACT_HPP
#define EXTRACT_HPP

#include <string>

namespace extract {
auto word(const std::string &string, int index) -> std::string;
auto number(const std::string &string, int index) -> int;
auto decimal(const std::string &string, int index) -> float;
} // namespace extract

#endif
