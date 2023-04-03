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

/*  // SET WITH INDEXING
// Implements logarithmic find_by_order() and order_of_key()
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
*/

// RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(2023);
uniform_real_distribution<double> standard_uniform(0.0, 1.0);

// Maybe implement CUDA matrix multiplication some day

template<unsigned IN, unsigned OUT, typename ACTIVATION>
struct layer{
    layer *prev, *next;
    double temp[IN], weights[OUT][IN + 1];
    layer(double lower = 0.0, double upper = 1.0){
        uniform_real_distribution<double> uniform_distribution(lower, upper);
        for(size_t i = 0; i < OUT; ++i){
            for(size_t j = 0; j <= IN; ++j){
                weights[i][j] = uniform_distribution(rng);
            }
        }
    }
    void forward(){
        // Tentative
        for(size_t i = 0; i < OUT; ++i){
            double acc = 0.0;
            for(size_t j = 0; j < IN; ++j){
                acc += weights[i][j] * temp[j];
            }
            next->temp[i] = acc + weights[i][IN];
        }
    }
    void backward();
};

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    int T;
    cin >> T;
    loop(t, T){
        int n; cin >> n;
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}