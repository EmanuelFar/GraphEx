#include "Graph.h"
#include <iostream>

class utils {
public:
  static void readFile(const std::string &fileName, Graph<std::string> &g) {
    std::string text;
    std::ifstream *file = utils::tryOpenFile(fileName);
    std::string startPoint, endPoint;
    int hopTime;
    *file >> startPoint;
    *file >> endPoint;
    *file >> hopTime;
    if (hopTime < 0) {
      delete file;
      std::cerr << "ERROR: node definition in " << fileName << " is invalid\n";
      return;
    } else if (startPoint == "exit" || endPoint == "exit") {
      delete file;
      std::cerr << "ERROR: point cannot be named exit" << '\n';
    }
    g.addVerticle(startPoint);
    g.addVerticle(endPoint);
    g.addEdge(startPoint, endPoint, hopTime);
  }

  static std::ifstream *tryOpenFile(const std::string &fileName) {
    std::ifstream *file = new std::ifstream(fileName);
    if (file->is_open()) {
      return file;
    } else {
      delete file;
      std::cerr << "ERROR: " << fileName
                << " does not exist or cannot be opened" << '\n';
      exit(-1);
    }
  }

  static bool analyzeOutput(const std::string &output,
                            const std::string &source) {
    if (output == "") {
      std::cout << source << " does not exist in the current network" << '\n';
      std::cout << "USAGE: <node> or ‘exit’ to terminate" << '\n';
      return false;
    }
    if (output == source) {
      std::cout << source << " : no outbound travel" << '\n';
      return false;
    }
    return true;
  }
};
