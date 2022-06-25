#include<bits/stdc++.h>
using namespace std;

#include"../lib/union_find.h"

// Functional Graphからサイクルを抽出するやつ。
// サイクルの外からサイクルに入っていく"ひげ"の部分は出力に含まれない。

vector<vector<int>> extract_cycles(const vector<int> &adj) {
  // O(n)
  // extract cycles from functional graph
  int n = adj.size();
  UnionFind uf(n);
  vector<vector<int>> cycles;
  for(int v=0; v<n; ++v) {
    if(!uf.same(v, adj[v])) {
      uf.unite(v, adj[v]);
      continue;
    }
    cycles.push_back(vector<int>());
    vector<int> &c = cycles.back();
    int u = v;
    do {
      c.push_back(u);
      u = adj[u];
    } while (u != v);
  }
  return cycles; 
}

int main() {
  // https://atcoder.jp/contests/abc256/tasks/abc256_e
  int n; cin >> n;
  vector<int> adj(n);
  for(int i=0; i<n; ++i) {
    int u; cin >> u; --u;
    adj[i] = u; 
  }
  vector<int> cost(n);
  for(int i=0; i<n; ++i) cin >> cost[i];

  long long ans = 0;
  auto cycles = extract_cycles(adj);
  for(auto &c : cycles) {
    int mn = cost[c[0]];
    for(int v : c) mn = min(mn, cost[v]);
    ans += mn;
  }
  cout << ans << '\n';
}
