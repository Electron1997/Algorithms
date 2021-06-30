// Solution to https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=251

#include <bits/stdc++.h>

#define f first
#define s second
#define loop(i, n) for (int i = 0; i < n; ++i)
#define read(a, n) loop($, n) cin >> a[$];
#define show(a, n)                  \
    loop($, n) cout << a[$] << " "; \
    cout << endl;

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

const int N = 10005;

int id, in[N];

vector<int> graph[N];

set<int> articulation_points;

int dfs(int v){
    int low = in[v] = id++;
    for(int u : graph[v]){
        if(!in[u]){ 
            int lo = dfs(u);
            if(lo >= in[v]){
                articulation_points.insert(v);
            }
            low = min(low, lo);
        }else{
            low = min(low, in[u]);
        }
    }
    return low;
}

inline void find_articulation_points(int n = N){
    articulation_points.clear();
    id = 1;
    memset(in, 0, n * sizeof(int));
    int c = 0;
    in[0] = id++;
    for(int u : graph[0]){
        if(!in[u]){
            ++c;
            dfs(u);
        }
    }
    if(c > 1){
        articulation_points.insert(0);
    }
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    while(true){
        int n;
        cin >> n;
        cin.ignore();
        if(n == 0){
            break;
        }
        loop(i, n){
            graph[i].clear();
        }
        string s;
        while(true){
            getline(cin, s);
            stringstream sc(s);
            int u;
            sc >> u;
            if(u == 0){
                break;
            }
            int v;
            while(sc >> v){
                graph[u - 1].push_back(v - 1);
                graph[v - 1].push_back(u - 1);
            }
        }
        find_articulation_points(n);
        cout << articulation_points.size() << endl;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
