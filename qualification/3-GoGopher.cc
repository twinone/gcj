#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#define SIZE 50

using namespace std;

typedef vector< std::vector<bool> > BoolMat;
typedef vector< std::vector<uint8_t> > IntMat;

void findBest(IntMat &m, int goWith, int &outX, int& outY) {
  int x = m[0].size();
  int y = m.size();
  int max = 0;
  int resX, resY;

  for (outY = 1; outY < y-1; outY++) {
    for (outX = 1; outX < x-1; outX++) {
      int v = m[outY][outX];
      if (v == goWith) return;
      if (v > max) { max = v; resX = outX; resY = outY; }
    }
  }
  outX = resX; outY = resY;
}

void decrease3x3(IntMat &m, int rX, int rY) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int x = rX-1 + j;
      int y = rY-1 + i;
      if (x < 0 || y < 0) continue;
      if (x >= m[0].size() || y >= m.size()) continue;
      m[y][x]--;
    }
  }
}

void printMat(IntMat &m) {
  int x = m[0].size();
  int y = m.size();
  cout << "size " << x << " " << y << endl;
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      cout << (0+m[i][j]) << " ";
    }
    cout << endl;
  }
  cout << "--------------" << endl;
}
int rng() {
  return (rand() % 3) - 1;
}

void solve(int n) {
  BoolMat b(SIZE, vector<bool>(SIZE, 0));
  int attempts = 0;
  int prepared = 0;
  int needed; cin >> needed;
  int x, y;
  if (needed == 20) { x = 5; y = 4; }
  // else { x = 4; y = 50; }
  else { x = 8; y = 25; }
  // else { x = 5; y = 40; }
  // else { x = 10; y = 20; }

  IntMat m(y, std::vector<uint8_t>(x, 9));
  int goWith = 9; // if we find this value, go with it
  // begin
  while (attempts < 1000 && prepared < needed) {
    // choose best square
    //printMat(m);
    int sX = 1;
    int sY = 1;
    findBest(m, goWith, sX, sY);
    goWith = m[sY][sX];

    cout << sY+1 << " " << sX+1 << endl;
    fflush(stdout);

    int rY, rX;
    cin >> rY >> rX;
    if (rY == 0 && rX == 0) return;
    if (rY == -1 && rX == -1) exit(0);

    //rX = sX+1 + rng(); rY = sY+1 + rng();
    attempts++;
    if (b[rY][rX]) continue;

    b[rY][rX] = true;
    prepared++;
    decrease3x3(m, rX, rY);
  }
  //printMat(m);

  //cout << "attempts: " << prepared << "/" << attempts << endl;
}

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) solve(i+1);
}
