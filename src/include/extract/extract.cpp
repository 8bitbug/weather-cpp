#include "extract.hpp"

#include <cctype>

struct word_data {
  word_data(int num) : index(num) {}

  std::string result;
  bool inside;
  int current;
  int index;
};

auto extract::word(const std::string &string, int index) -> std::string {
  word_data word(index);
  for (const char &ch : string) {
    if (ch != ' ') {
      if (!word.inside) {
        word.inside = true;
        if (word.current == word.index) {
          word.result.push_back(ch);
        }
      } else if (word.current == word.index) {
        word.result.push_back(ch);
      }
    } else {
      if (word.inside) {
        ++word.current;
        word.inside = false;
      }
    }
  }
  return !word.result.empty() ? word.result : "Index out of range";
}

auto extract::number(const std::string &string, int index) -> int {
  word_data numeric(index);
  for (const char &ch : string) {
    if (ch != ' ' || !isalpha(ch)) {
      if (!numeric.inside) {
        numeric.inside = true;
        if (numeric.current == numeric.index) {
          if (std::isdigit(ch) || (ch == '-' && numeric.result.empty())) {
            numeric.result.push_back(ch);
          }
        }
      } else if (numeric.current == numeric.index) {
        if (std::isdigit(ch)) {
          numeric.result.push_back(ch);
        }
      }
    } else {
      if (numeric.inside) {
        numeric.inside = false;
        ++numeric.current;
      }
    }
  }

  return numeric.result.length() < 1 ? std::stoi(numeric.result) : 0;
}

auto extract::decimal(const std::string &string, int index) -> float {
  word_data decimal(index);
  bool has_decimal_point = false;
  bool parsing_number = false;
  int current_decimal_index = 0;

  for (const char &ch : string) {
    if (std::isdigit(ch)) {
      if (!parsing_number) {
        parsing_number = true;
        decimal.result.clear();
      }
      decimal.result.push_back(ch);
    } else if (ch == '.' && !has_decimal_point && parsing_number) {
      decimal.result.push_back(ch);
      has_decimal_point = true;
    } else if (parsing_number) {
      parsing_number = false;
      has_decimal_point = false;

      if (current_decimal_index == decimal.index) {
        break;
      }

      ++current_decimal_index;
    }
  }

  return decimal.result.length() < 1 ? 0.0f : std::stof(decimal.result);
}
