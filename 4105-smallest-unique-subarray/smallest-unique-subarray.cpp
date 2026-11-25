class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, int> freq;
        for (int x : nums) freq[x]++;

        for (int x : nums) {
            if (freq[x] == 1) return 1;
        }

        // Check all subarrays using rolling hash
        const long long MOD = 1000000007;
        const long long BASE = 31;

        vector<long long> hash(n + 1, 0), power(n + 1, 1);

        for (int i = 0; i < n; i++) {
            hash[i + 1] = (hash[i] * BASE + nums[i]) % MOD;
            power[i + 1] = (power[i] * BASE) % MOD;
        }

        auto check = [&](int len) {
            unordered_map<long long, int> mp;

            for (int i = 0; i + len <= n; i++) {
                long long h = (hash[i + len] -
                    hash[i] * power[len] % MOD + MOD) % MOD;

                if (++mp[h] == 1) continue;
            }

            for (auto &p : mp) {
                if (p.second == 1) return true;
            }

            return false;
        };

        int low = 1, high = n, ans = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};