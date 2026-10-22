
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int z = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                z = i;
                break;
            }
        }

        bool inc = true, dec = true;

        for (int i = 0; i < n; i++) {
            if (nums[(z + i) % n] != i)
                inc = false;

            if (nums[(z - i + n) % n] != i)
                dec = false;
        }

        int ans = INT_MAX;

        if (inc)
            ans = min(ans, min(z, n - z + 2));

        if (dec)
            ans = min(ans, min(z + 2, n - z));

        return ans == INT_MAX ? -1 : ans;
    }
};
