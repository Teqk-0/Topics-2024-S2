#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

int main(void) {
  const fs::path pathToShow{
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 2/Max"};

  int globalLevelMax = 0;

  for (auto itEntry = fs::recursive_directory_iterator(pathToShow);
       itEntry != fs::recursive_directory_iterator(); ++itEntry) {
    const auto parentName = itEntry->path().parent_path().filename().string();

    if (itEntry->path().extension() == ".csv" && itEntry.depth() == 1) {
      std::cout << parentName << ":" << std::endl;

      int fileLevelMax = 0;

      // Open the CSV file
      std::ifstream file(itEntry->path().string());
      if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
      }
      
      // Operate in file.
      std::string line;
      int row = 0;
      while (std::getline(file, line)) {
        if (row == 0) {
          row++;
          continue;
        }
        std::stringstream ss(line);
        std::string cell;
        int col = 0;
        while (getline(ss, cell, ',')) {
          if (col == 6 && cell != "" && fileLevelMax < stoi(cell)) {
            fileLevelMax = stoi(cell);
          }
          col++;
        }
        row++;
      }

      // close the file after read opeartion is complete
      file.close();

      std::cout << "fileLevelMax = " << fileLevelMax << std::endl << std::endl;

      if (fileLevelMax > globalLevelMax) {
        globalLevelMax = fileLevelMax;
      }
    }

    // std::cout << std::setw(itEntry.depth() * 3) << "";
    // std::cout << "dir:  " << filenameStr << " | My parent is " << parentName
    // << '\n';
  }

  std::cout << std::endl << "globalLevelMax = " << globalLevelMax << std::endl;

  return 0;
}