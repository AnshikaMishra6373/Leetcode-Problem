class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));

        priority_queue<
            tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>
        > pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [cost, u, cnt] = pq.top();
            pq.pop();

            if (cost != dist[u][cnt]) continue;

            for (auto &e : adj[u]) {
                int v = e.first;
                int w = e.second;

                int nextCnt = (labels[u] == labels[v]) ? cnt + 1 : 1;

                if (nextCnt > k) continue;

                int newCost = cost + w;

                if (newCost < dist[v][nextCnt]) {
                    dist[v][nextCnt] = newCost;
                    pq.push({newCost, v, nextCnt});
                }
            }
        }

        int ans = INT_MAX;

        for (int i = 1; i <= k; i++) {
            ans = min(ans, dist[n - 1][i]);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};