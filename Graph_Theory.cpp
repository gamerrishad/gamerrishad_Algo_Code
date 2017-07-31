// **************** Maximum Matching (Hopcroft) *********************** // 
#define MAX 100001
#define NIL 0
#define INF (1<<28)

vector< int > G[MAX];
int n, m, match[MAX], dist[MAX];
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]

bool bfs() {
    int i, u, v, len;
    queue< int > Q;
    for(i=1; i<=n; i++) {
        if(match[i]==NIL) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=NIL) {
            len = G[u].size();
            for(i=0; i<len; i++) {
                v = G[u][i];
                if(dist[match[v]]==INF) {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL]!=INF);
}

bool dfs(int u) {
    int i, v, len;
    if(u!=NIL) {
        len = G[u].size();
        for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[match[v]]==dist[u]+1) {
                if(dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int hopcroft_karp() {
    int matching = 0, i;
    // match[] is assumed NIL for all vertex in G
    while(bfs())
        for(i=1; i<=n; i++)
            if(match[i]==NIL && dfs(i))
                matching++;
    return matching;
}

/////////////////////// END OF Maximum Matching (Hopcroft) // ********

// ******************* Finding Articulation Point and Bridges ************************** //
int seen[1001];
int parent[1001], low[1001], dis[1001];

void bridge (vector<int>Adj[], int u)
{
    static int tm=0;
    seen[u] = 1;
    low[u] = dis[u] = ++tm;

    for (int i=0 ; i<Adj[u].size() ; i++)
    {
        int v = Adj[u][i];
        if (!seen[v])
        {
            parent[v] = u;
            bridge(Adj, v);
            printf("%d %d\n", u, v);
            if (low[v] > dis[u]) printf("%d %d\n", v, u); // v -> u is a bridge
            low[u] = min(low[u], low[v]);
        }
        else if (seen[v] == 1 && v != parent[u])
        {
            printf("%d %d\n", u, v);
            low[u] = min(low[u], dis[v]);
        }
    }
    seen[u] = 2;
}
////////////////////// END OF Finding Articulation Point and Bridges //////////////////////////////
