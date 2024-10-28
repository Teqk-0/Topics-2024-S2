#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

int main(void) {
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  // File pointer
  std::fstream fin, fout;

  // Open an existing record
  fin.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/Max Combined Bad.csv",
      std::ios::in);

  // Operate in file.
  std::vector<float> dataPoints[5];
  std::string line;
  int row = 0;
  while (std::getline(fin, line)) {
    if (row == 0) {
      row++;
      continue;
    }
    std::stringstream ss(line);
    std::string cell;
    int col = 0;
    while (getline(ss, cell, ',')) {
      if (!cell.empty() && cell[cell.size() - 1] == '\r') {
        cell.pop_back();
      }
      if (col > 2) {
        if (!cell.empty()) {
          dataPoints[col - 3].push_back(std::stof(cell));
        }
      }
      col++;
    }
    row++;
  }

  fin.close();

  float stationAverages[5] = {0};
  for (int a = 0; a < 5; a++) {
    for (int b = 0; b < int(dataPoints[a].size()); b++) {
      stationAverages[a] += dataPoints[a][b];
    }
    stationAverages[a] =
        round((stationAverages[a] / dataPoints[a].size()) * 10) / 10;
  }

  // Open an existing record
  fin.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/Max Combined Bad.csv",
      std::ios::in);

  // Create a new file to store updated data
  fout.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/Simple Average.csv",
      std::ios::out);

  // Operate in file.
  std::string line2;
  row = 0;
  while (std::getline(fin, line2)) {
    if (row == 0) {
      fout << line2 << "\n";
      row++;
      continue;
    }
    std::stringstream ss(line2);
    std::string cell;
    int col = 0;
    while (getline(ss, cell, ',')) {
      if (!cell.empty() && cell[cell.size() - 1] == '\r') {
        cell.pop_back();
      }
      if (cell == "") {
        fout << stationAverages[col - 3];
      } else {
        fout << cell;
      }

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

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout << "Time difference = "
            << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     begin)
                   .count() / float(1000)
            << "[ms]" << std::endl;
  return 0;
}
