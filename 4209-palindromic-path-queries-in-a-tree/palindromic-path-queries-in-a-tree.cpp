class Solution {
    vector<vector<int>> adj, up;
    vector<int> tin, tout, depth, pref, bit;
    int timer, LOG;

    void add(int i, int x) {
        for (; i < bit.size(); i += i & -i)
            bit[i] ^= x;
    }

    int sum(int i) {
        int x = 0;
        for (; i > 0; i -= i & -i)
            x ^= bit[i];
        return x;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int d = depth[u] - depth[v];
        for (int k = 0; k < LOG; k++)
            if (d & (1 << k)) u = up[k][u];

        if (u == v) return u;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        adj.assign(n, {});
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        up.assign(LOG, vector<int>(n));
        tin.resize(n);
        tout.resize(n);
        depth.assign(n, 0);
        pref.assign(n, 0);
        bit.assign(n + 2, 0);
        timer = 0;

        vector<tuple<int, int, bool>> st;
        st.push_back({0, 0, true});

        while (!st.empty()) {
            auto [u, p, enter] = st.back();
            st.pop_back();

            if (enter) {
                tin[u] = ++timer;
                up[0][u] = p;

                for (int k = 1; k < LOG; k++)
                    up[k][u] = up[k - 1][up[k - 1][u]];

                pref[u] = (u == 0 ? 0 : pref[p])
                        ^ (1 << (s[u] - 'a'));

                st.push_back({u, p, false});

                for (int v : adj[u]) {
                    if (v != p) {
                        depth[v] = depth[u] + 1;
                        st.push_back({v, u, true});
                    }
                }
            } else {
                tout[u] = timer;
            }
        }

        vector<bool> ans;

        for (auto &q : queries) {
            string type;
            int u, v;
            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int x = (1 << (s[u] - 'a')) ^
                        (1 << (c - 'a'));

                add(tin[u], x);
                add(tout[u] + 1, x);
                s[u] = c;
            } else {
                ss >> v;
                int w = lca(u, v);

                int mask = (pref[u] ^ sum(tin[u]))
                         ^ (pref[v] ^ sum(tin[v]))
                         ^ (1 << (s[w] - 'a'));

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};