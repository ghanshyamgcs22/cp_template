// https://github.com/ghanshyamgcs22/cp_template/blob/main/tree.cpp

/*   
Author ghanshyamgcs22
*/
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define FAST               ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
vector<pair<ll,ll>>dir={{1,0},{-1,0},{0,1},{0,-1}};
// <----------------------Dijsktra------------------------------->
using pii=pair<ll, ll> ; 

vector<ll> dijkstra(ll n, vector<vector<pii>>& graph) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<ll> dist(n + 1, INF);
    vector<ll> parent(n + 1, -1);

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue; 

        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

   
    if (dist[n] == INF) return {};

    
    vector<ll> path;
    for (int v = n; v != -1; v = parent[v])
        path.push_back(v);
    
    reverse(path.begin(), path.end());
    return path;
}

// <----------------------Dijsktra- END------------------------------->

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
            rank[pv]++;// increase rank of the new root
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

//<--------------------------- KRUSKAL------------------------------->

void kruskalMST()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>>edges;
    for(int i=0;i<m;i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        edges.push_back({wt,{u,v}});
    }
    
    sort(edges.begin(),edges.end());
    dsu d(n);
    int cost=0;
    for(auto&it:edges)
    {
        int wt=it.first;
        int u=it.second.first;
        int v=it.second.second;
        
        if(d.findPar(u)!=d.findPar(v))
        {
            d.unionByRank(u,v);
            cost+=wt;
            cout<<u<<" "<<v<<endl;
        }
    }
    
    cout<<cost<<endl;
}

//<--------------------------- KRUSKAL END---------------------------->

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

// vector<int> level;
void binary_lifting(int node,int par,vector<ll>adj[], vector<vector<ll>>&dp)
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
	       level[it] = level[node] + 1;
        binary_lifting(it,node,adj,dp);
      }

}

int lca(int u, int v) {
    if (level[u] < level[v])
        swap(u, v);

    // lift u to the same level 
    for (int i = 16; i >= 0; i--) {
        if (level[u] - (1 << i) >= level[v])
            u = dp[u][i];
    }

    if (u == v) return u;

   
    for (int i = 16; i >= 0; i--) {
        if (dp[u][i] != dp[v][i]) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }

    return dp[u][0]; 
}


template<typename Node, typename Update>
struct SegTree {
	vector<Node> tree;
	vector<ll> arr; // type may change
	int n;
	int s;
	SegTree(int a_len, vector<ll> &a) { // change if type updated
		arr = a;
		n = a_len;
		s = 1;
		while(s < 2 * n){
			s = s << 1;
		}
		tree.resize(s); fill(all(tree), Node());
		build(0, n - 1, 1);
	}
	void build(int start, int end, int index)  // Never change this
	{
		if (start == end)	{
			tree[index] = Node(arr[start]);
			return;
		}
		int mid = (start + end) / 2;
		build(start, mid, 2 * index);
		build(mid + 1, end, 2 * index + 1);
		tree[index].merge(tree[2 * index], tree[2 * index + 1]);
	}
	void update(int start, int end, int index, int query_index, Update &u)  // Never Change this
	{
		if (start == end) {
			u.apply(tree[index]);
			return;
		}
		int mid = (start + end) / 2;
		if (mid >= query_index)
			update(start, mid, 2 * index, query_index, u);
		else
			update(mid + 1, end, 2 * index + 1, query_index, u);
		tree[index].merge(tree[2 * index], tree[2 * index + 1]);
	}
	Node query(int start, int end, int index, int left, int right) { // Never change this
		if (start > right || end < left)
			return Node();
		if (start >= left && end <= right)
			return tree[index];
		int mid = (start + end) / 2;
		Node l, r, ans;
		l = query(start, mid, 2 * index, left, right);
		r = query(mid + 1, end, 2 * index + 1, left, right);
		ans.merge(l, r);
		return ans;
	}
	void make_update(int index, ll val) {  // pass in as many parameters as required
		Update new_update = Update(val); // may change
		update(0, n - 1, 1, index, new_update);
	}
	Node make_query(int left, int right) {
		return query(0, n - 1, 1, left, right);
	}
};

struct Node1 {
	ll val; // may change
	Node1() { // Identity element
		val = 0;	// may change
	}
	Node1(ll p1) {  // Actual Node
		val = p1; // may change
	}
	void merge(Node1 &l, Node1 &r) { // Merge two child nodes
		val = l.val ^ r.val;  // may change
	}
};

struct Update1 {
	ll val; // may change
	Update1(ll p1) { // Actual Update
		val = p1; // may change
	}
	void apply(Node1 &a) { // apply update to given node
		a.val = val; // may change
	}
};

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

FAST;
	solve_tree(); 
	

}
