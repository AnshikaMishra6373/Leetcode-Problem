class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            vector<int> a = nums;
            bool ok = true;

            for (int i = 0; i < n; i += k) {
                int drops = 0;
                int pos = -1;

                for (int j = i; j < i + k - 1; j++) {
                    if (a[j] > a[j + 1]) {
                        drops++;
                        pos = j;
                    }
                }

                if (a[i + k - 1] > a[i]) {
                    drops++;
                }

                if (drops > 1) {
                    ok = false;
                    break;
                }

                if (pos != -1) {
                    rotate(a.begin() + i,
                           a.begin() + pos + 1,
                           a.begin() + i + k);
                }
            }

            if (ok) {
                for (int i = 1; i < n; i++) {
                    if (a[i] < a[i - 1]) {
                        ok = false;
                        break;
                    }
                }
            }

            if (ok) ans += k;
        }

        return ans;
    }
};