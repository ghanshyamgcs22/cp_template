// https://github.com/ghanshyamgcs22/cp_template/blob/main/tree.cpp

/*   
Author ghanshyamgcs22
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
//<-------------------------- Re-rooting ------------------------>
// ll in[200005];
// ll out[200005];

// void dfs(int node, int par, vector<ll> adj[]) {
//     in[node] = 0;
    
//     for (auto &it : adj[node]) {
//         if (it == par) continue;
//         dfs(it, node, adj);
//         in[node] = max(in[node], 1 + in[it]);
//     }
// }

// void dfs2(int node, int par, vector<ll> adj[]) {
//     ll mx1 = -1, mx2 = -1, child = -1;
    
//     for (auto &it : adj[node]) {
//         if (it != par) {
//             if (in[it] + 1 > mx1) {
//                 mx2 = mx1;
//                 mx1 = in[it] + 1;
//                 child = it;
//             } else if (in[it] + 1 > mx2) {
//                 mx2 = in[it] + 1;
//             }
//         }
//     }

//     for (auto &it : adj[node]) {
//         if (it == par) continue;

//         int longest=mx1;
//         if(it==child)
//         longest=mx2;

//         // **Fix: Ensure out[it] also considers out[node]**
//         out[it] = 1+max(out[node], longest);
 
//         dfs2(it, node, adj);
//     }
// }
//  dfs(1, -1, adj);
   
//     dfs2(1, -1, adj);

//     for (int i = 1; i <= n; i++) {
//         cout << max(out[i],in[i]) << " ";
//     }

//<-------------------------- Re-rooting End------------------------>



// <--------------------------DSU------------------------------------>
class dsu {
    vector<int> parent, size,rank;

public:
    dsu(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        rank.resize(n + 1, 0);
 
        for (int i = 0; i <= n; i++)
            parent[i] = i;
    }

    int findPar(int node) {
        if (parent[node] == node)
            return node;
        return parent[node] = findPar(parent[node]); // path compression
    }

    void unionBySize(int u, int v) {
        int pu = findPar(u);
        int pv = findPar(v);

        if (pu == pv) // same component
            return;

        if (size[pu] < size[pv]) { // attach smaller tree to larger
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
    
    void unionByRank(int u,int v)
    {
        int pu=findPar(u);
        int pv=findPar(v);
        if(pu==pv)
        return;
        
        if(rank[pu]==rank[pv])
        {
            parent[pu]=pv;// make of them parent
            rank[pu]++;// increase rank of the new root
        }
        
        else if(rank[pu]<rank[pv])
        {
            parent[pu]=pv;
            
        }
        
        else
        {
            parent[pv]=pu;
        }
    }
};

// <--------------------------DSU End-------------------------------->

vector<ll> eulr_tour_type1_v;
unordered_map<ll, ll> tour_type1_mp1;
ll tour_type1_idx = 0;

void dfs_eulr_tour_type1(int node, int par, vector<ll> adj[]) {
    eulr_tour_type1_v.push_back(node);
    tour_type1_mp1[tour_type1_idx] = node;
    tour_type1_idx++;

    for (auto &it : adj[node]) {
        if (it != par) {
            dfs_eulr_tour_type1(it, node, adj);
            eulr_tour_type1_v.push_back(node);
            tour_type1_mp1[tour_type1_idx] = node;
            tour_type1_idx++;
        }
    }
}


vector<ll> eulr_tour_type2_v;
unordered_map<ll, pair<ll, ll>> tour_type2_mp;
int tour_type2_idx = 0;

void dfs_eulr_tour_type2(int node, int par, vector<ll> adj[]) {
    eulr_tour_type2_v.push_back(node);
    tour_type2_mp[tour_type2_idx].first = node;
    int curr_idx = tour_type2_idx;  
    tour_type2_idx++;

    for (auto &it : adj[node]) {
        if (it != par) {
            dfs_eulr_tour_type2(it, node, adj);
        }
    }

    eulr_tour_type2_v.push_back(node);
    tour_type2_mp[curr_idx].second = node;
}


 ll dp_tsp[13][1 << 13];

    ll tsp(int i, int mask, vector<vector<ll>>& cost) {
        if (mask == 0) return 0; // All nodes visited

        if (dp_tsp[i][mask] != -1) return dp_tsp[i][mask];

        ll ans = INT_MAX;
        for (int j = 0; j < cost.size(); j++) {
            if (mask & (1 << j)) { // If node `j` is not visited
                ans = min(ans, cost[i][j] + tsp(j, mask ^ (1 << j), cost));
            }
        }

        return dp_tsp[i][mask] = ans;
    }
void dp_on_tree(int node,vector<ll>adj[],int par,vector<ll>&dp)
{

    dp[node]=1;
    for(auto it: adj[node])
    {

          if(it==par)continue; 
        dp_on_tree(it,adj,node,dp);
        dp[node]+=dp[it];
    }
}
 
void binary_lifting(int node,int par,vector<ll>adj, vector<vecor<ll>>&dp)
{
     //  base case
     dp[node][0]=par;
      for(int i=1;i<=16;i++)
      {
        dp[node][i]=dp[dp[node][i-1]][i-1]; 

      }

      for(auto&it:adj[node])
      {
        if(it==par)continue;
        binary_lifting(it,node,adj,dp);
      }

}
void solve_tree()
{
   int n;
	cin>>n;
	vector<ll>adj[n+1];
	
	// vector<int>dp(n+1);
	for(int i=0;i<n-1;i++)
	{ 
        ll u,v;cin>>u>>v;
	    adj[u].push_back(v);
	    adj[v].push_back(u);
	}

    int q;
    cin>>q;
    vector<vecor<ll>>dp(n+1,vector<int>(17,0));
    binary_lifting(1,0,adj,dp);  
    while(q--)
    {
         int node,k;// node's kth parent
         cin>>node>>k;
        //  while(k)
        //  {
        //     if(k&1)
        //     node=dp[node][cnt];

        //     cnt++;
        //     k>>1;
        //  }

        for(int i=17  ;i>=0;i--)
        {
            if((k>>i)&1)  // that bit in k is set or not 
            node=dp[node][ i]; 
        }

        cout<<endl; 
    }
	// tc O(nlogn)-->dfs+O(qlogk)-->quires
}

int main() {
	// your code goes here
	solve_tree(); 
	

}
