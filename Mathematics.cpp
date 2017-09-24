/******* 1. BigMod (Modding x^y from end) ******/
int BigMod (int base, int expo, int mod)
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
// ___ END OF BigMod (Modding x^y from end) ____
/*********************** 2. BigMod (Modding x from front) ********************/
int firstMOD (int base, int expo, int mod) // 2^10 = 1024 ans is 10 if mod 100 
{
    double x = (expo * log10(base));
    x -= (int) x;

    return pow(10, x) * mod;
}
// _______________ END OF BigMod (Modding x from front) ______________________
/** 3. Moduler Multiplicative Inverse (or Fermat's Law) ***/
int modInverse (int a, int mod)
{
    return BigMod(a, mod-2, mod);
}
// _END OF Moduler Multiplicative Inverse_
/****** 4. nCr % M Calculating Function **************/
ll nCr (int n, int r, vector <ll>& fact)
{
    if (r > n) return 0LL;
    ll ans = fact[n];
    ans = (ans * BigMod(fact[r], mod-2, mod)) % mod;
    ans = (ans * BigMod(fact[n-r], mod-2, mod)) % mod;
    return ans;
}

// Another for very big n while r is very small
// pre calculate inv[]
// for (int i = 1; i <= MAX_r ; i++)
    // inv[i] = BigMod(i, mod - 2LL, mod);

ll nCr (ll n, int r)
{
    if (r > n) return 0LL;
    if (n == r || r == 0) return 1LL;
    if (r > n-r) r = n-r;
    n %= mod;

    ll ans = 1LL;
    for (int i = 1; i <= r; i++)
    {
        ans = (ans * ((n - (ll)i + 1LL + mod) % mod)) % mod;
        ans = (ans * inv[i]) % mod;
    }
    return ans;
}
//_____ END OF nCr % M Calculating Function __________
/******* 4. Sieve of Eratosthenes or Generate Primes *******/
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
// ______ END OF Sieve of Eratosthenes ______
/***************** 6. Prime Factorization **********************/
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
// ___________ END OF PRIME FACTORIZATION _____________________

/******** 7.Prime Exponent for a factorial n! ********/
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
// ____ END OF Prime Exponent for an factorial integer n ____

/************* 8. GCD *************/
int gcd (int a, int b)
{
    while (b) b ^= a ^= b ^= a %= b;
    return a;
}
// _________ END OF GCD ____________

/******** 9. LCM ************/
int lcm (int a, int b)
{
    return a*b / gcd(a, b);
}
// _____ END OF LCM ________
/************ 10. Extended GCD *****************/
// for solving aX + bY = D, where a, b given
int x, y, d;
void extendedGCD (int a, int b)
{
    if (b == 0) {x = 1, y = 0, d = a; return;}
    extendedGCD(b, a%b);

    int x1 = y, y1 = x - (a/b)*y;
    x = x1, y = y1;
}
// __________ END OF EXTENDED GCD _____________
/********* 11. Sum Of Divisors of a number N ********/
ll sumofdiv (int n)
{
    int lmt = sqrt(n) + 1;
    ll ans = 1, p, s;
    for (int i=0 ; primes[i]<=lmt ; i++)
    {
        if (n%primes[i] == 0)
        {
            p = primes[i];
            while (n%primes[i] == 0)
            {
                n /= primes[i];
                p *= primes[i];
            }
            s = (p-1) / (primes[i] - 1);
            ans *= s;
        }
    }
    if (n > 1)
    {
        p = n * n;
        s = (p-1) / (n-1);
        ans *= s;
    }
    return ans;
}
// ______ END OF SUM OF DIVISORS _________

/********************************* 12. Number of Solutions to a Linear Algebraic Equation *************************************/
// p1 + p2 + p3 + ... + k = n the function returns number of solution of this equation including upper and lower bound for each p
scanf("%d %d", &k, &n);
for (int i=0 ; i<k ; i++)
     scanf("%d %d", &l[i], &u[i]), u[i]++; // Lower and Upper Together is upper-lower+1, this is why u[i]++

int lmt = (1 << k);
ll ans = 0;
for (int mask = 0 ; mask < lmt ; mask++)
{
     int del = n, bits = 0;
     for (int i=0 ; i<k ; i++)
     {
          if (mask&(1<<i)) del -= u[i], bits++;
          else del -= l[i];
     }
     if (del >= 0)
     {
          if (bits&1) ans -= nCr(del+k-1, k-1);
          else ans += nCr(del+k-1, k-1);
          ans %= MOD, ans += MOD, ans %= MOD;
     }
}
return ans;
// _____________ END OF Number of Solutions to a Linear Algebraic Equation with Upper and Lower Bound ____________________

/*********************************************** 13. Euler Phi Function ***************************************************/
// Euler's totient function, also known as phi-function ϕ(n)ϕ(n), is the number of integers between 1 and n, inclusive, 
// which are coprime to n. Two numbers are coprime if their greatest common divisor equals 1 (1 is considered to be coprime 
// to any number).
// N        1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22
// Phi(N)   1   1   2   2   4   2   6   4   6   4  10   4  12   6   8   8  16   6  18   8  12  10
const int MAX = 1000001;
int phi[MAX];
void euler_phi()
{
    phi[1] = 1;
    for(int i=2; i<MAX; i++)
    {
        if(!phi[i])
        {
            phi[i] = i-1;
            for(int j=(i<<1); j<MAX; j+=i)
            {
                if(!phi[j]) phi[j] = j;
                phi[j] = phi[j]/i*(i-1);
            }
        }
    }
}
// Another approach with Complexity O(sqrt(n))
int phi(int n) {
    int result = n;
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    if(n > 1)
        result -= result / n;
    return result;
}
// ______________________________________ END of Euler Phi Function _____________________________________________________
// *********************** Least Number of Perfect Squares that Sums to n **O(sqrt(n))*******************************
int is_square (int n)
{
    int sqrt_n = (sqrt(n));
    return (sqrt_n*sqrt_n == n);
}
int perfectSquaresLagrange (int n)
{
    if (is_square(n)) return 1;
    while ((n & 3) == 0) n >>= 2;
    if ((n & 7) == 7) return 4;
    int sqrt_n = (sqrt(n));
    for(int i = 1; i <= sqrt_n; i++)
        if (is_square(n - (i*i)))
            return 2;
    return 3;
}
//_______________________END OF Least Number of Perfect Squares that Sums to n ____________________________________________
