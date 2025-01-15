#include "Graph.h"
#include "utils.h"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  Graph<std::string> g;
  for (int arg = 1; arg < argc; arg++) {
    utils::readFile(argv[arg], g);
  }
  std::ofstream oFile("output.txt");
  if (oFile.is_open())
    oFile << g;
  oFile.close();

  std::string text;

  std::cout << "USAGE: <node> or ‘exit’ to terminate" << '\n';
  while (true) {
    std::cin >> text;
    if (text == "exit")
      break;

    std::string output = g.getAllLinkedVerticles(text);
    if (utils::analyzeOutput(output, text)) {
      std::cout << output << std::endl;
    }
  }
  return 0;
}
