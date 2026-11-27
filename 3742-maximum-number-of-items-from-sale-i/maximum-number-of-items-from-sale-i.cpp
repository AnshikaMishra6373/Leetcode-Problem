
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        int minPrice = INT_MAX;

        for (auto &item : items) {
            minPrice = min(minPrice, item[1]);
        }

        vector<int> val(n);

        for (int i = 0; i < n; i++) {
            val[i] = 1;

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    val[i]++;
                }
            }
        }

        const long long NEG = -1e18;

        vector<vector<long long>> dp(
            2, vector<long long>(budget + 1, NEG)
        );

        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int isMin = (price == minPrice);

            for (int b = budget; b >= price; b--) {
                for (int flag = 0; flag <= 1; flag++) {
                    if (dp[flag][b - price] == NEG)
                        continue;

                    int newFlag = flag || isMin;

                    dp[newFlag][b] = max(
                        dp[newFlag][b],
                        dp[flag][b - price] + val[i]
                    );
                }
            }
        }

        long long ans = 0;

        for (int b = 0; b <= budget; b++) {
            if (dp[1][b] != NEG) {
                ans = max(ans, dp[1][b] +
                          (budget - b) / minPrice);
            }

            if (budget - b < minPrice) {
                ans = max(ans, dp[0][b]);
            }
        }

        return (int)ans;
    }
};
