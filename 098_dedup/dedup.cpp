#include <dirent.h>
#include <string.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

//file read helper
std::string content(const std::string & filename) {
  std::ifstream read;
  std::string strings;
  std::stringstream ans;
  //read file
  read.open(filename);
  if (read.fail()) {
    std::cerr << "cannot read from file"
              << "\n";
    exit(EXIT_FAILURE);
  }
  while (!read.eof()) {
    //file content
    std::getline(read, strings);
    //store content
    ans << strings;
  }
  read.close();
  return ans.str();
}

//dedup function
void dedup(const char * directory, std::unordered_map<size_t, std::string> & map) {
  DIR * dir;
  struct dirent * ent;
  //open directory
  dir = opendir(directory);
  if (dir == NULL) {
    std::cerr << "cannot open directory"
              << "\n";
    exit(EXIT_FAILURE);
  }
  else {
    //read filename
    while ((ent = readdir(dir)) != NULL) {
      std::string dirStr(directory);
      if (dirStr.length() > 0 && dirStr[dirStr.length() - 1] != '/') {
        dirStr = dirStr + '/';
      }
      std::string filename(ent->d_name);
      std::string fullname = dirStr + filename;
      //symlinks
      if ((ent->d_type & DT_LNK) == DT_LNK) {
        continue;
      }
      //directory
      else if ((ent->d_type & DT_DIR) == DT_DIR) {
        //"." or ".."
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
          continue;
        }
        //other directory
        else {
          dedup(fullname.c_str(), map);
        }
      }
      //regular file
      else if ((ent->d_type & DT_REG) == DT_REG) {
        std::string filecontent = content(fullname);
        std::hash<std::string> myHash;
        size_t key = myHash(filecontent);
        std::unordered_map<size_t, std::string>::const_iterator it = map.find(key);
        //duplication
        if (it != map.end()) {
          std::cout << "#Removing " << fullname << " (duplicate of " << it->second << ")."
                    << std::endl;
          std::cout << "rm " << fullname << std::endl;
        }
        else {
          map.insert(std::pair<size_t, std::string>(key, fullname));
        }
      }
      else {
        std::cerr << "Unknown file type: " << fullname << std::endl;
      }
    }
  }
  closedir(dir);
}

int main(int argc, char ** argv) {
  //map to store information
  std::unordered_map<size_t, std::string> mymap;
  //  std::hash<std::string> myhash;
  //check arguments
  if (argc < 2) {
    std::cerr << "at least 1 argument is required"
              << "\n";
    return EXIT_FAILURE;
  }
  else {
    std::cout << "#!/bin/bash"
              << "\n";
    //dedup for every directory
    for (int i = 1; i < argc; i++) {
      dedup(argv[i], mymap);
    }
  }
  return EXIT_SUCCESS;
}
