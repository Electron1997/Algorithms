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