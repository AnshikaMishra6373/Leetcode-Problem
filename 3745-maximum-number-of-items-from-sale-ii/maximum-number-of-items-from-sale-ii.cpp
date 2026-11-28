
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);
        int mn = INT_MAX;

        for (auto &x : items) {
            freq[x[0]]++;
            mn = min(mn, x[1]);
        }

        vector<int> gain(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            if (freq[i] == 0) continue;

            for (int j = i; j <= n; j += i) {
                gain[i] += freq[j];
            }

            gain[i]--;
        }

        vector<pair<int, int>> deals;

        for (auto &x : items) {
            int f = x[0];
            int p = x[1];

            if (p < 2LL * mn && gain[f] > 0) {
                deals.push_back({p, gain[f]});
            }
        }

        sort(deals.begin(), deals.end());

        long long ans = 0;
        long long rem = budget;

        for (auto &[p, cnt] : deals) {
            long long take = min((long long)cnt, rem / p);

            ans += 2 * take;
            rem -= take * p;
        }

        ans += rem / mn;

        return (int)ans;
    }
};
