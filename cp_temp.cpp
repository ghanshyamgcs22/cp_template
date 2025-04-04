
// https://github.com/ghanshyamgcs22/cp_template/blob/main/cp_temp.cpp
#define ghanshyam gupta
 
 
#include <bits/stdc++.h>
 
using namespace std;
#define pb push_back
#define ppb pop_back
#define nl '\n'
#define yes cout<<"YES"<<'\n'
#define no cout<<"NO"<<'\n'
#define ll long long
#define inf 1e18
#define VI vector<int>
#define VL vector<ll>
#define VVI vector<vector<int>>
#define VVL vector<vector<ll>>
#define all(v) v.begin(),v.end()
#define PI pair<int,int>
#define PL pair<ll,ll>
#define fs first
#define sc second
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FAST               ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
ll set_bits(ll x){ return __builtin_popcountll(x);}
const int MOD1 = 1e9 + 7;
const int mod = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int BASE1 = 31;
const int BASE2 = 53;
vector<ll> prefixHash1, prefixHash2;
vector<ll> power1, power2;
 
struct pair_hash
{
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2> &p) const
    {
        size_t h1 = hash<T1>{}(p.first);
        size_t h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};
 
void computePrefixHash(const string &s)
{
    int n = s.size();
    prefixHash1.resize(n + 1, 0);
    prefixHash2.resize(n + 1, 0);
    power1.resize(n + 1, 1);
    power2.resize(n + 1, 1);
 
    for (int i = 1; i <= n; ++i)
    {
        power1[i] = (power1[i - 1] * BASE1) % MOD1;
        power2[i] = (power2[i - 1] * BASE2) % MOD2;
    }
 
    for (int i = 1; i <= n; ++i)
    {
        prefixHash1[i] = (prefixHash1[i - 1] * BASE1 + (s[i - 1] - 'a' + 1)) % MOD1;
        prefixHash2[i] = (prefixHash2[i - 1] * BASE2 + (s[i - 1] - 'a' + 1)) % MOD2;
    }
}
 
pair<ll, ll> getDoubleHash(ll l, ll r)
{
    ll hash1 = (prefixHash1[r] - (prefixHash1[l - 1] * power1[r - l + 1]) % MOD1 + MOD1) % MOD1;
    ll hash2 = (prefixHash2[r] - (prefixHash2[l - 1] * power2[r - l + 1]) % MOD2 + MOD2) % MOD2;
    return {hash1, hash2};
}
 
ll getSingleHash(ll l, ll r)
{
    ll hash1 = (prefixHash1[r] - (prefixHash1[l - 1] * power1[r - l + 1]) % MOD1 + MOD1) % MOD1;
    
    return hash1;
}
 
 
 
// <-----------for int values not strings------------->
 
 // void computePrefixHash(const vector<int> &path) {
 //        int n = path.size();
 //        prefixHash1.assign(n + 1, 0);
 //        prefixHash2.assign(n + 1, 0);
 //        power1.assign(n + 1, 1);
 //        power2.assign(n + 1, 1);
 
 //        for (int i = 1; i <= n; ++i) {
 //            power1[i] = (power1[i - 1] * BASE1) % MOD1;
 //            power2[i] = (power2[i - 1] * BASE2) % MOD2;
 //        }
 
 //        for (int i = 1; i <= n; ++i) {
 //            prefixHash1[i] = (prefixHash1[i - 1] * BASE1 + (path[i - 1] + 1)) % MOD1;
 //            prefixHash2[i] = (prefixHash2[i - 1] * BASE2 + (path[i - 1] + 1)) % MOD2;
 //        }
 //    }
  
 
 
 ll kadane_sum(vector<ll>&nums)
   {
      ll maxi=LLONG_MIN;
      ll sum=0;
      for(int k=0;k<nums.size();k++)
      {
          sum+=(nums[k]);
 
          maxi=max(maxi,sum);
          if(sum<0)
           sum=0;
      }
 
      return maxi;
   }
ll gcd(ll a,ll b){ if(a==0LL) return b;    return gcd(a,b%a);}
int mod_pow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
vector<ll>fact;
vector<ll>inv_fact;
void precompute_fact(int n) {
    fact.resize(n + 1, 1);
    inv_fact.resize(n + 1, 1);
 
    for (int i = 2; i <= n; ++i) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
 
    inv_fact[n] = mod_pow(fact[n], mod - 2, mod); // fermitt to inv
    for (int i = n - 1; i >= 1; --i) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    }
}
 
int comb(int n, int r) {
    if (r > n || r < 0) return 0;
    return (fact[n] * inv_fact[r] % mod * inv_fact[n - r] % mod) % mod;
}
 
class SegmentTree {
private:
    vector<int> tree;  
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            // Leaf node stores the value itself
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
 
           
            merge(node, start, end);
        }
    }
 
  
    void merge(int node, int start, int end) {
        int mid = (start + end) / 2;
        if ((start + mid) % 2 == 0) {
           
            tree[node] = (tree[2 * node] & tree[2 * node + 1]);
        } else {
            
            tree[node] = (tree[2 * node] | tree[2 * node + 1]);
        }
    }
 
  
    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            // Leaf node update
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, value);
            } else {
                update(2 * node + 1, mid + 1, end, idx, value);
            }
 
           
            merge(node, start, end);
        }
    }
 
public:
   int n;
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
 
   
    void update(int idx, int value) {
        update(1, 0, n - 1, idx, value);
    }
 
   
    int get_beauty() {
        return tree[1];
    }
};
 
vector<ll> fib(1e5 + 5, 0);
 
 
void precompute_fib() {
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < fib.size(); i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
    }
}
const int N = 1e6 + 5; 
vector<bool> is_prime(N, true);

void sieve() {
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i < N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < N; j += i)
                is_prime[j] = false;
        }
    }
}
 

// find(adj[it].begin(), adj[it].end(), it1) != adj[it].end()) to check an val presnt or not in vector of vector
void ghanshyam() {
    
    
VI
    // Please AC!!!!   
}
int main()
{
 
FAST;
    ll t;
   
//   t=1; ghanshyam();
     cin >> t;while (t--) ghanshyam();
 
 
    return 0;
}
 
 
