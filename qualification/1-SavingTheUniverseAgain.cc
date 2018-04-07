#include <iostream>
#include <vector>
#include <string>

using namespace std;

int calcDamage(string &s) {
  int robotDamage = 0;
  int robotStrength = 1;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == 'C') robotStrength*=2;
    else robotDamage += robotStrength;
  }
  return robotDamage;
}

void swapLast(string &s) {
  int robotDamage = 0;
  int robotStrength = 1;
  for (int i = s.length()-2; i >= 0; i--) {
    if (s[i] == 'C' && s[i+1]=='S') {
      s[i] = 'S'; s[i+1] = 'C';
      return;
    }
  }
}


void solve(int n) {
  int shield; string program; cin >> shield >> program;
  int sol = 0;
  int damage = calcDamage(program);
  while (damage > shield) {
    swapLast(program);
    sol++;
    int newDamage = calcDamage(program);
    if (newDamage == damage) {
      cout << "Case #" << n << ": IMPOSSIBLE" << endl;
      return;
    }
    damage = newDamage;
  }
  cout << "Case #" << n << ": " << sol << endl;
}

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) solve(i+1);
}
