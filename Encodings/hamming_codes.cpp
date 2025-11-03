// Solution to https://codeforces.com/contest/2168/problem/C

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

/*
// SET WITH INDEXING
// Implements logarithmic find_by_order() and order_of_key()
// erase does not work with less_equal<T>!
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/

/*  // RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

template<unsigned PARITY_BITS, size_t BLOCK_SIZE = (1 << PARITY_BITS) - PARITY_BITS - 1, size_t CODE_SIZE = (1 << PARITY_BITS) - 1>
std::bitset<CODE_SIZE> encode(std::bitset<BLOCK_SIZE> block){
    std::bitset<CODE_SIZE> code = 0;
    unsigned j = 2;
    for(unsigned i = 0; i < BLOCK_SIZE; ++i){
        code[j] = block[i];
        ++j;
        if(__builtin_popcount(j + 1) == 1) ++j;
    }
    for(unsigned parity_bit = 0; parity_bit < PARITY_BITS; ++parity_bit){
        size_t parity_bit_pos = (1 << parity_bit) - 1;
        bool parity = 0;
        for(unsigned j = parity_bit_pos + 1; j < CODE_SIZE; ++j){
            if(((j + 1) >> parity_bit) & 1){
                parity ^= code[j];
            }
        }
        code[parity_bit_pos] = parity;
    }
    return code;
}

template<unsigned PARITY_BITS, size_t BLOCK_SIZE = (1 << PARITY_BITS) - PARITY_BITS - 1, size_t CODE_SIZE = (1 << PARITY_BITS) - 1>
std::bitset<CODE_SIZE> correct(std::bitset<CODE_SIZE> code){
    unsigned syn = 0;
    for(unsigned parity_bit = 0; parity_bit < PARITY_BITS; ++parity_bit){
        size_t parity_bit_pos = (1 << parity_bit) - 1;
        bool parity = 0;
        for(unsigned j = parity_bit_pos + 1; j < CODE_SIZE; ++j){
            if(((j + 1) >> parity_bit) & 1){
                parity ^= code[j];
            }
        }
        if(code[parity_bit_pos] != parity) syn += parity_bit_pos + 1;
    }
    if(syn) code.flip(syn - 1);
    return code;
}

template<unsigned PARITY_BITS, size_t BLOCK_SIZE = (1 << PARITY_BITS) - PARITY_BITS - 1, size_t CODE_SIZE = (1 << PARITY_BITS) - 1>
inline std::bitset<BLOCK_SIZE> decode(std::bitset<CODE_SIZE> code){
    code = correct<PARITY_BITS, BLOCK_SIZE, CODE_SIZE>(code);
    std::bitset<BLOCK_SIZE> block;
    for(unsigned i = 0, j = 0; i < CODE_SIZE; ++i){
        if(__builtin_popcount(i + 1) == 1) continue;
        block[j++] = code[i];
    }
    return block;
}

int main(){
    /*
    auto start = chrono::high_resolution_clock::now();
    */
    
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    string round; cin >> round;
    if(round == "first"){
        int T;
        cin >> T;
        loop(t, T){
            int x; cin >> x;
            bitset<20> h = encode<5, 15, 20>(x);
            cout << h.count() << endl;
            loop(i, 20){
                if(h[i]) cout << i + 1 << " ";
            }
            cout << endl;
        }
    }else{
        int T;
        cin >> T;
        loop(t, T){
            int n; cin >> n;
            int h = 0;
            loop(i, n){
                int u; cin >> u;
                h |= 1 << (u - 1);
            }
            int x = decode<5, 15, 20>(h).to_ulong();
            if(!x) x = 1 << 15;
            cout << x << endl;
        }
    }

    /*
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
    */
    return 0;
}
