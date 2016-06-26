/* BIG MOD */
int bigmod (int base, int expo, int mod)
{
    int res = 1;
    while (expo)
    {
        if (expo & 1) res = (res * base) % mod;
        expo >>= 1; // Divided By 2
        base = (base * base) % mod;
    }
    return res;
}

int firstMOD (int base, int expo, int mod) // 2^10 = 1024 ans is 10 if mod 100 
{
    double x = (expo * log10(base));
    x -= (int) x;

    return pow(10, x) * mod;
}
// END OF BIG MOD ************************************************************

/* Moduler Multiplicative Inverse */ //***************************************
int modInverse (int a, int mod)
{
    return bigmod(a, mod-2, mod);
}
// END OF Moduler Multiplicative Inverse

// ********** Generate Primes (Sieve) *************************//
#define MX 10000010
vector<int>primes;
bool flag[MX];
int sz;

void sieve ()
{
    int lmt = (sqrt(MX));
    for (int i=3 ; i<=lmt ; i+=2)
        if (!flag[i])
            for (int j=i*i ; j<MX ; j+=i+i)
                flag[j] = 1;

    primes.push_back(2);
    for (int i=3 ; i<MX ; i+=2)
        if (!flag[i])
            primes.push_back(i);

    sz = primes.size();
}
// END OF SIEVE // ********************************* //

// ************ Prime Factorization ***********
// SZ is primes.size()
int expos[10000001], div; // Power of i'th Prime saved here
void primePower (int n)
{
    for (int i=0 ; i<sz && n ; i++)
    {
        if (n%primes[i] == 0)
        {
            div = expos[i] = 0;
            while (n && n%primes[i] == 0) n /= primes[i], div++;
            expos[i] = div;
        }
    }
}
// END OF PRIME FACTORIZATION // ********************************************* //

/// Prime Exponent for a factorial n!
int factoPrimeExpo (int n, int p) // n! and prime
{
    int res = 0;
    n /= p;
    do
    {
        res += n;
        n /= p;
    }while (n);
    return res; // Returns exponent of p
}
// END OF Prime Exponent for an factorial integer n

/* GCD */

int gcd (int a, int b)
{
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}
// END OF GCD *********************

/* LCM */

int lcm (int a, int b)
{
    return a*b / gcd(a, b);
}
// END OF LCM *********************

// ******** Extended GCD for solving aX + bY = D, where a, b given
int x, y, d;
void extendedGCD (int a, int b)
{
    if (b == 0) {x = 1, y = 0, d = a; return;}
    extendedGCD(b, a%b);

    int x1 = y, y1 = x - (a/b)*y;
    x = x1, y = y1;
}
// ************ END OF EXTENDED GCD ********************
