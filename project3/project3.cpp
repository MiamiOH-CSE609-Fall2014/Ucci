#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;

void parseFastaFile(string filepath);

int main() {
  parseFastaFile("human22.txt");
  return 0;
}
