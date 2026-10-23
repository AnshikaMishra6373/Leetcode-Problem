
class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int ans = -1;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i) {
                if (ans == -1)
                    ans = nums[i] & i;
                else
                    ans &= (nums[i] & i);
            }
        }

        return ans == -1 ? 0 : ans;
    }
};
