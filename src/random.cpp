#include <random>
#include <iostream>

int RandomValue(int range) {
  std::random_device rd;
  std::mt19937 random_eng(rd());
  std::uniform_int_distribution<int> dist(0, range);
  return dist(random_eng);
}

// Test
int main() {
  for (int i = 0; i < 10; i++)
    std::cout << RandomValue(10) << std::endl;
  return 0;
}
