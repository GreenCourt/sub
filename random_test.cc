#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#include"../lib/random_test.h"

namespace solver1 {
#include "x.cc"
}

namespace solver2 {
#include "y.cc"
}

struct testcase {
  int n;

  testcase() {
    n = randint(1,10);
  }

  bool ac() const {
    const auto s1 = solver1::solver(n);
    const auto s2 = solver2::solver(n);
    return s1.ans == s2.ans;
  }

  void dump(ostream &os) const {
    os << n << '\n';
  }

  friend ostream &operator<<(ostream &os, const testcase &t) { t.dump(os); return os; }
};

int main() {
  //testcase t; t.dump(cout); exit(0);
  for(int i=0; ; ++i) {
    cout << "\r" << i;
    testcase t;
    if(!t.ac()) {
      ofstream("failed") << t << flush;
      cout << "\r=== failed ===\n" << t;
      break;
    }
  }
}
