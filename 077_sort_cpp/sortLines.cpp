#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void printfuc(std::vector<std::string> ans) {
  for (size_t i = 0; i < ans.size(); i++) {
    std::cout << ans[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  //read input
  std::ifstream read;
  std::string strings;
  //hold input
  std::vector<std::string> ans;
  //read from standard input
  if (argc == 1) {
    while (!std::cin.eof()) {
      std::getline(std::cin, strings);
      ans.push_back(strings);
      //sort
      std::sort(ans.begin(), ans.end());
      //print
      printfuc(ans);
      ans.clear();
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      read.open(argv[i]);
      if (read.fail()) {
        std::cerr << "cannot read from file" << std::endl;
        return EXIT_FAILURE;
      }
      while (!read.eof()) {
        std::getline(read, strings);
        ans.push_back(strings);
      }
      //sort
      std::sort(ans.begin(), ans.end());
      //print
      printfuc(ans);
      ans.clear();
      read.close();
    }
  }
  return EXIT_SUCCESS;
}
