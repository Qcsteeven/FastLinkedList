#include <time.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

int main() {
  std::default_random_engine URNG{};

  std::seed_seq::result_type seeds[]{
      std::random_device{}(),
      std::seed_seq::result_type(
          std::chrono::system_clock::now().time_since_epoch().count())};

  std::seed_seq sseq(std::begin(seeds), std::end(seeds));
  URNG.seed(sseq);
  std::uniform_int_distribution<unsigned> DIST(1, 1000);
  std::ofstream file("add.txt");
  int range = 1000000;
  file << range << '\n';
  for (int i = 0; i < range; i++) {
    unsigned num{DIST(URNG)};

    file << num << '\n';
  }

  file.close();
}