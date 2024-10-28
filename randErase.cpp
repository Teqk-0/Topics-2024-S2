#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

int main(void) {
  bool doErase = false;
  srand(time(0));
  // File pointer
  std::fstream fin, fout;

  // Open an existing record
  fin.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 2/Max/tester.csv",
      std::ios::in);

  // Create a new file to store updated data
  fout.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 2/Max/testerNew.csv",
      std::ios::out);

  // Operate in file.
  std::string line;
  int row = 0;
  while (std::getline(fin, line)) {
    if (row == 0) {
      fout << line << "\n";
      row++;
      continue;
    }
    std::stringstream ss(line);
    std::string cell;
    int col = 0;
    int key = 0;
    while (getline(ss, cell, ',')) {
      if (doErase) {
        if (col >= 3 && rand() % 20 == 0) {
          cell = "";
        }
        
      } else {
        if (col == 0 && stoi(cell) == 2018) {
          key++;
        }
        if (col == 1 && stoi(cell) == 7) {
          key++;
        }
        if (key == 2) {
          doErase = true;
        }
      }

      fout << cell;
      if (col == 7) {
        fout << "\n";
      } else {
        fout << ",";
      }
      col++;
    }
    row++;
  }

  // close the file after read opeartion is complete
  fin.close();
  fout.close();

  // removing the existing file
  remove(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/tester.csv");

  // renaming the updated file with the existing file name
  rename(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/testerNew.csv",
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/tester.csv");

  return 0;
}
