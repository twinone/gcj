#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve(int n) {
  int l; cin >> l;
  vector<int> a;
  vector<int> b;
  for (int i = 0; i < l; i++) {
    int tmp; cin >> tmp;
    if (i%2==0) a.push_back(tmp);
    else b.push_back(tmp);
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  for (int i = 0; i < l-1; i++) {
      int x, y;
      if (i%2==0) { x = a[i/2]; y = b[i/2]; }
      else { x = b[i/2]; y = a[i/2+1]; }
      if (x > y) {
        cout << "Case #" << n << ": " << i << endl;
        return;
      }
  }
  cout << "Case #" << n << ": OK" << endl;
}

int main() {
  int n; cin >> n;
  for (int i = 0; i < n; i++) solve(i+1);
}

