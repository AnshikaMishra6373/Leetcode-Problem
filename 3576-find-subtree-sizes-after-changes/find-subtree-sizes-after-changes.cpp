class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);
        vector<int> saved(n, -1);

        // DFS on original tree using enter/exit states
        stack<pair<int, int>> st;
        st.push({0, 0});

        while (!st.empty()) {
            auto [node, state] = st.top();
            st.pop();

            int ch = s[node] - 'a';

            if (state == 0) {
                // Save previous ancestor of this character
                saved[node] = last[ch];

                // Find nearest same-character ancestor
                if (last[ch] != -1) {
                    newParent[node] = last[ch];
                }

                // Current node becomes nearest ancestor
                last[ch] = node;

                // Exit state
                st.push({node, 1});

                // Children
                for (int child : adj[node]) {
                    st.push({child, 0});
                }
            }
            else {
                // Restore previous value
                last[ch] = saved[node];
            }
        }

        // Build modified tree
        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        // DFS traversal order
        vector<int> order;
        stack<int> stk;
        stk.push(0);

        while (!stk.empty()) {
            int node = stk.top();
            stk.pop();

            order.push_back(node);

            for (int child : tree[node]) {
                stk.push(child);
            }
        }

        // Subtree sizes
        vector<int> ans(n, 1);

        for (int i = n - 1; i >= 0; i--) {
            int node = order[i];

            for (int child : tree[node]) {
                ans[node] += ans[child];
            }
        }

        return ans;
    }
};