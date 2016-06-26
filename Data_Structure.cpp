/* Inversion Index With MergeSort O(nlogn) */

int inverse = 0;
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    for(i = 0; i < n1; i++) L[i] = arr[l + i];
    for(j = 0; j < n2; j++) R[j] = arr[m + 1+ j];
    i = j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) arr[k] = L[i], i++;
        else arr[k] = R[j], j++, inverse += (n1 - i);
        k++;
    }
    while (i < n1) arr[k] = L[i], i++, k++;
    while (j < n2) arr[k] = R[j], j++, k++;
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// Initial inverse = 0;
// Call With mergeSort(arr, left_index, right_index);

// ******************** Suffix Array O(nlog n) *****************************
#define MX 101000

int T[MX];
int SA[MX], RA[MX], c[MX], temp[MX];

void countingSort (int k, int n)
{
    int maxi = max(150, n);
    for (int i=0 ; i<=maxi ; i++) c[i] = 0;
    for (int i=0 ; i<n ; i++) c[i+k < n ? RA[i+k] : 0]++;
    for (int i=0, sum=0, t; i<maxi ; i++) t = c[i], c[i] = sum, sum += t;
    for (int i=0 ; i<n ; i++) temp[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
    for (int i=0 ; i<n ; i++) SA[i] = temp[i];
}

void buildSA(int n)
{
    for (int i=0 ; i<n ; i++) RA[i] = T[i], SA[i] = i;
    for (int k=1, r=0 ; k<n ; k <<= 1, r=0)
    {
        countingSort(k, n);
        countingSort(0, n);

        temp[SA[0]] = 0;
        for (int i=1 ; i<n ; i++) temp[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;

        for (int i=0 ; i<n ; i++) RA[i] = temp[i];
        if (RA[SA[n-1]] == n-1) return;
    }
}


int phi[MX], LCP[MX], PLCP[MX];
void computeLCP(int n)
{
    phi[SA[0]] = -1;
    for (int i=1 ; i<n ; i++) phi[SA[i]] = SA[i-1];
    for (int i=0, L=0 ; i<n ; i++)
    {
        if (phi[i] == -1)
        {
            PLCP[i] = 0;
            continue;
        }
        while (T[i+L] == T[phi[i]+L]) L++;
        PLCP[i] = L;
        L = max(L-1, 0);
    }
    for (int i=0 ; i<n ; i++) LCP[i] = PLCP[SA[i]];
}

ii stringMatching()                        // string matching in O(m log n)
{
    int lo = 0, hi = n-1, mid = lo;              // valid matching = [0..n-1]
    while (lo < hi)                                       // find lower bound
    {
        mid = (lo + hi) / 2;                              // this is round down
        int res = strncmp(T + SA[mid], P, m);  // try to find P in suffix 'mid'
        if (res >= 0) hi = mid;        // prune upper half (notice the >= sign)
        else          lo = mid + 1;           // prune lower half including mid
    }                                      // observe `=' in "res >= 0" above
    if (strncmp(T + SA[lo], P, m) != 0) return ii(-1, -1);    // if not found
    ii ans;
    ans.first = lo;
    lo = 0;
    hi = n - 1;
    mid = lo;
    while (lo < hi)              // if lower bound is found, find upper bound
    {
        mid = (lo + hi) / 2;
        int res = strncmp(T + SA[mid], P, m);
        if (res > 0) hi = mid;                              // prune upper half
        else         lo = mid + 1;            // prune lower half including mid
    }                           // (notice the selected branch when res == 0)
    if (strncmp(T + SA[hi], P, m) != 0) hi--;                 // special case
    ans.second = hi;
    return ans;
} // return lower/upperbound as first/second item of the pair, respectively

ii LRS()                   // returns a pair (the LRS length and its index)
{
    int i, idx = 0, maxLCP = -1;
    for (i = 1; i < n; i++)                         // O(n), start from i = 1
        if (LCP[i] > maxLCP)
            maxLCP = LCP[i], idx = i;
    return ii(maxLCP, idx);
}

int owner(int idx) // Build with an array or use this!
{
    return (idx < n-m-1) ? 1 : 2;
}

ii LCS()                   // returns a pair (the LCS length and its index)
{
    int i, idx = 0, maxLCP = -1;
    for (i = 1; i < n; i++)                         // O(n), start from i = 1
        if (owner(SA[i]) != owner(SA[i-1]) && LCP[i] > maxLCP)
            maxLCP = LCP[i], idx = i;
    return ii(maxLCP, idx);
}
//**********************// END OF Suffix Array ALGORITHM /// *************************************************////////////
/*************************** KMP **************************/
int go[SZ];
go[0] = -1;
int i=0, j=-1;
while (i < P.size())
{
    while (j >= 0 && P[i] != P[j]) j = go[j];
    i++, j++;
    go[i] = j;
}

i = j = 0;
while (i < S.size())
{
    while (j >= 0 && S[i] != P[j]) j = go[j];
    i++, j++;
}

// ****************** END OF KMP *****************************//
