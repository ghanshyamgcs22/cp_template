// https://github.com/ghanshyamgcs22/cp_template/blob/main/tree.cpp

/*   
Author ghanshyamgcs22
*/
#include <bits/stdc++.h>
using namespace std;
 int dp_tsp[13][1 << 13];

    int tsp(int i, int mask, vector<vector<int>>& cost) {
        if (mask == 0) return 0; // All nodes visited

        if (dp_tsp[i][mask] != -1) return dp_tsp[i][mask];

        int ans = INT_MAX;
        for (int j = 0; j < cost.size(); j++) {
            if (mask & (1 << j)) { // If node `j` is not visited
                ans = min(ans, cost[i][j] + tsp(j, mask ^ (1 << j), cost));
            }
        }

        return dp_tsp[i][mask] = ans;
    }
void dp_on_tree(int node,vector<int>adj[],int par,vector<int>&dp)
{

    dp[node]=1;
    for(auto it: adj[node])
    {

          if(it==par)continue; 
        dp_on_tree(it,adj,node,dp);
        dp[node]+=dp[it];
    }
}
 
void binary_lifting(int node,int par,vector<int>adj, vector<vecor<int>>&dp)
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
	vector<int>adj[n+1];
	
	// vector<int>dp(n+1);
	for(int i=0;i<n-1;i++)
	{ 
        int u,v;cin>>u>>v;
	    adj[u].push_back(v);
	    adj[v].push_back(u);
	}

    int q;
    cin>>q;
    vector<vecor<int>>dp(n+1,vector<int>(17,0));
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
