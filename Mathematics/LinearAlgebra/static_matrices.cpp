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

/* // TIME
auto start = chrono::high_resolution_clock::now();
// ...
auto stop = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
cout << duration.count() << endl;
*/

const ull MD = 1e9 + 7;

mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());

template<ull MOD>
struct modint{
    
    ull val;

    modint() : val(0) {}

    modint(ull n) : val(n % MOD) {}

    modint operator + (const modint &b) const {
        return (val + b.val) % MOD;
    }

    modint operator * (const modint &b) const {
        return (val * b.val) % MOD;
    }

    friend ostream &operator << (ostream &out, const modint &mi){
        out << mi.val;
        return out;
    }

    friend istream &operator >> (istream &in, modint &mi){
        in >> mi.val;
        return in;
    }

};

typedef modint<MD> MI;

template<class type>
type zero(){
    return MI(0);
}

template<class type>
type one(){
    return MI(1);
}

template<class type, size_t N, size_t M>
struct matrix{

    type data[N][M];

    matrix(){
        for(size_t i = 0; i < N; ++i){
            for(size_t j = 0; j < M; ++j){
                data[i][j] = zero<type>();
            }
        }
    }

    matrix(type *ptr){
        for(size_t i = 0; i < N; ++i){
            for(size_t j = 0; j < M; ++j){
                data[i][j] = *(ptr + M * i + j);
            }
        }
    }

    friend ostream &operator << (ostream &out, const matrix &A){
        for(size_t i = 0; i < N; ++i){
            for(size_t j = 0; j < M; ++j){
                out << A.data[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }

    friend istream &operator >> (istream &in, matrix &A){
        for(size_t i = 0; i < N; ++i){
            for(size_t j = 0; j < M; ++j){
                in >> A.data[i][j];
            }
        }
    }

};

template<class type, size_t N>
matrix<type, N, N> identity(){
    matrix<type, N, N> I = *(new matrix<type, N, N>());
    for(size_t i = 0; i < N; ++i){
        I.data[i][i] = one<type>();
    }
    return I;
}

template<class type, size_t N, size_t M>
matrix<type, N, M> ones(){
    matrix<type, N, M> O = *(new matrix<type, N, M>());
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < M; ++j){
            O.data[i][j] = one<type>();
        }
    }
    return O;
}

template<size_t N, size_t M>
matrix<double, N, M> random(){
    uniform_real_distribution<> uar(0, 1);
    matrix<double, N, M> A = *(new matrix<double, N, M>());
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < N; ++j){
            A.data[i][j] = uar(RNG);
        }
    }
    return A;
}

template<class type, size_t N, size_t M>
matrix<type, N, M> sum(matrix<type, N, M> &A, matrix<type, N, M> &B){
    matrix<type, N, M> S = *(new matrix<type, N, M>());
    memcpy(S.data, A.data, N * M * sizeof(type));
    for(size_t i = 0; i < N; ++i){
        for(size_t j = 0; j < M; ++j){
            S.data[i][j] = S.data[i][j] + B.data[i][j];
        }
    }
    return S;
}

template<class type, size_t L, size_t N, size_t M>
matrix<type, L, M> product(matrix<type, L, N> &A, matrix<type, N, M> &B){
    matrix<type, L, M> P = *(new matrix<type, L, M>());
    for(size_t i = 0; i < L; ++i){
        for(size_t j = 0; j < M; ++j){
            for(size_t k = 0; k < N; ++k){
                P.data[i][j] = P.data[i][j] + A.data[i][k] * B.data[k][j];
            }
        }
    }
    return P;
}

// Time: O(N^3log(n)) (could be sped up to O(N^3 + t(N) + Nlog(n)) with O(t(N)) eigendecomposition)
template<class type, size_t N>
matrix<type, N, N> power(matrix<type, N, N> &A, ull n){
    matrix<type, N, N> P = identity<type, N>();
    while(n){
        if(n & 1){
            P = product(P, A);
        }
        A = product(A, A);
        n >>= 1;
    }
    return P;
}

inline size_t idx(char c){
    if('A' <= c && c <= 'Z') return c - 'A' + 26;
    return c - 'a';
}

const int K = 52;

int main(){

    // IO
    ios_base::sync_with_stdio(false);   // unsync C- and C++-streams (stdio, iostream)
    cin.tie(NULL);  // untie cin from cout (no automatic flush before read)

    ull n; int m, k; cin >> n >> m >> k;
    matrix<MI, K, K> DP;
    loop(i, m){
        loop(j, m){
            DP.data[i][j] = one<MI>();
        }
    }
    loop(i, k){
        string s; cin >> s;
        DP.data[idx(s[1])][idx(s[0])] = zero<MI>();
    }
    DP = power<MI, K>(DP, n - 1);
    MI sol = zero<MI>();
    loop(i, m){
        loop(j, m){
            sol = sol + DP.data[i][j];
        }
    }
    cout << sol << endl;

    return 0;
}
