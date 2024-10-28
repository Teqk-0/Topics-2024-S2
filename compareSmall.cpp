#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

int main(void) {
  // File pointer
  std::fstream fin1, fin2, fin3;

  // Open an existing record
  fin1.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/Max Combined Good.csv",
      std::ios::in);
  fin2.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/Max Combined Bad.csv",
      std::ios::in);
  fin3.open(
      "/mnt/c/Users/Finlay/OneDrive - University of "
      "Adelaide/Coursework/Topics/Data/Dataset 1/Max/Combination.csv",
      std::ios::in);

  // Operate in file.
  std::vector<float> sumAll;
  std::vector<float> sumMissings;
  std::string line[3];
  int row = 0;
  while (std::getline(fin1, line[0])) {
    std::getline(fin2, line[1]);
    std::getline(fin3, line[2]);
    if (row == 0) {
      row++;
      continue;
    }
    std::stringstream ss1(line[0]);
    std::stringstream ss2(line[1]);
    std::stringstream ss3(line[2]);
    std::string cell[3];
    int col = 0;
    int year = 0;
    while (getline(ss1, cell[0], ',')) {
      getline(ss2, cell[1], ',');
      getline(ss3, cell[2], ',');

      if (col == 0) {
        if (stoi(cell[0]) < 2020) {
          break;
        } else {
          year = stoi(cell[0]);
        }
      }
      if (col == 1 && (year == 2020 && stoi(cell[0]) < 3)) {
        break;
      }

      if (col < 3) {
        col++;
        continue;
      }

      if (!cell[1].empty() && cell[1][cell[1].size() - 1] == '\r') {
        cell[1].pop_back();
      }

      float vals[2] = {0};
      vals[0] = stof(cell[0]);
      vals[1] = stof(cell[2]);

      sumAll.push_back(fabs(vals[0] - vals[1]));

      if (cell[1].empty()) {
        sumMissings.push_back(sumAll.back());
      }
      col++;
    }
    row++;
  }

  fin1.close();
  fin2.close();
  fin3.close();

  float averages[2] = {0};
  float worstDiff = sumMissings[0];

  for (int a = 0; a < int(sumAll.size()); a++) {
    averages[0] += sumAll[a];
  }
  for (int a = 0; a < int(sumMissings.size()); a++) {
    averages[1] += sumMissings[a];
    if (worstDiff < sumMissings[a]) {
      worstDiff = sumMissings[a];
    }
  }

  averages[0] = round((averages[0] / sumAll.size()) * 100) / 100;
  averages[1] = round((averages[1] / sumMissings.size()) * 100) / 100;

  std::cout << "Average difference = " << averages[0] << std::endl;
  std::cout << "Average missings difference = " << averages[1] << std::endl;
  std::cout << "Worst difference = " << worstDiff << std::endl;

  return 0;
}
