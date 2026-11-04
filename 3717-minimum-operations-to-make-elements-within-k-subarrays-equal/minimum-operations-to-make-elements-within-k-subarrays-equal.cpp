class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> l, r;
        long long sl = 0, sr = 0;

        auto balance = [&]() {
            int need = min((x + 1) / 2, (int)(l.size() + r.size()));

            while (l.size() > need) {
                int v = *l.rbegin();
                l.erase(prev(l.end()));
                sl -= v;
                r.insert(v);
                sr += v;
            }

            while (l.size() < need) {
                int v = *r.begin();
                r.erase(r.begin());
                sr -= v;
                l.insert(v);
                sl += v;
            }
        };

        auto add = [&](int v) {
            if (l.empty() || v <= *l.rbegin()) {
                l.insert(v);
                sl += v;
            } else {
                r.insert(v);
                sr += v;
            }
            balance();
        };

        auto remove = [&](int v) {
            auto it = l.find(v);

            if (it != l.end()) {
                l.erase(it);
                sl -= v;
            } else {
                it = r.find(v);
                r.erase(it);
                sr -= v;
            }
            balance();
        };

        auto getCost = [&]() -> long long {
            long long m = *l.rbegin();
            return m * l.size() - sl + sr - m * r.size();
        };

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++)
            add(nums[i]);

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);
            cost[i - x + 1] = getCost();
        }

        const long long INF = LLONG_MAX / 2;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};