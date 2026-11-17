
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();

        vector<vector<int>> cost(n, vector<int>(n, 0));

        // Step 1: Precompute substring costs
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;
                int best = 1e9;

                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    for (int x = 0; x < d; x++) {
                        int l = i + x;
                        int r = i + x + ((j - (i + x)) / d) * d;

                        while (l < r) {
                            if (s[l] != s[r]) {
                                changes++;
                            }

                            l += d;
                            r -= d;
                        }
                    }

                    best = min(best, changes);
                }

                cost[i][j] = best;
            }
        }

        // Step 2: Dynamic Programming
        const int INF = 1e9;

        vector<vector<int>> dp(k + 1,
                               vector<int>(n + 1, INF));

        dp[0][0] = 0;

        for (int p = 1; p <= k; p++) {
            for (int i = 2 * p; i <= n; i++) {
                for (int j = 2 * (p - 1); j <= i - 2; j++) {

                    dp[p][i] = min(
                        dp[p][i],
                        dp[p - 1][j] + cost[j][i - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
