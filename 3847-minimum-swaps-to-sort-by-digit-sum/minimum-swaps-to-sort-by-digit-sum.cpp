
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<tuple<int, int, int>> a;

        for (int i = 0; i < n; i++) {
            int x = nums[i], sum = 0;

            while (x > 0) {
                sum += x % 10;
                x /= 10;
            }

            a.push_back({sum, nums[i], i});
        }

        sort(a.begin(), a.end());

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || get<2>(a[i]) == i)
                continue;

            int j = i, cycle = 0;

            while (!visited[j]) {
                visited[j] = true;
                j = get<2>(a[j]);
                cycle++;
            }

            swaps += cycle - 1;
        }

        return swaps;
    }
};
