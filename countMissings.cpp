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

  for (auto itEntry = fs::recursive_directory_iterator(pathToShow);
       itEntry != fs::recursive_directory_iterator(); ++itEntry) {
    const auto parentName = itEntry->path().parent_path().filename().string();

    if (itEntry->path().extension() == ".csv" && itEntry.depth() == 1) {
      int missings = 0;
      int maxYear = 0;

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
          bool breakOut = false;
          switch (col) {
            case 2: // Year.
              if (stoi(cell) < 2014 || stoi(cell) > 2023) {
                breakOut = true;
              } 
              maxYear = stoi(cell);
            break;
            case 3: // Month.
              // if (year == 2014 && stoi(cell) < 9) {
              //   breakOut = true;
              // } else if (year == 2024 && stoi(cell) > 8) {
              //   breakOut = true;
              // }
            break;
            case 5: // Data.
              if (cell == "") {
                missings++;
              }
              breakOut = true;
            break;
            default: // Other.
              // ...
            break;
          }
          if (breakOut) {
            break;
          }
          col++;
        }
        row++;
      }

      // close the file after read opeartion is complete
      file.close();

      if (maxYear == 2024) {
        std::cout << parentName << ":" << std::endl;
        std::cout << "missings = " << missings << std::endl << std::endl;
      }
      
    }

    // std::cout << std::setw(itEntry.depth() * 3) << "";
    // std::cout << "dir:  " << filenameStr << " | My parent is " << parentName
    // << '\n';
  }

  return 0;
}