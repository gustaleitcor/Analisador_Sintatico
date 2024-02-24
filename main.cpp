#include "./Sintatico.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {

  std::string token, type, line_str;
  unsigned long line_ul;
  std::ifstream input_file("test1");
  Sintatico sintatico;

  while (input_file >> type) {
    input_file >> token;
    input_file >> line_str;
    line_ul = std::stoul(line_str);

    sintatico.tokens.push_back(
        (Token){.type = stringToType(type), .name = token, .line = line_ul});
  }

  sintatico.analyse();
  sintatico.saveToFile("out.txt");

  for (auto token : sintatico.tokens) {
    std::cout << token.type << ' ' << token.name << std::endl;
  }

  input_file.close();

  return 0;
}
