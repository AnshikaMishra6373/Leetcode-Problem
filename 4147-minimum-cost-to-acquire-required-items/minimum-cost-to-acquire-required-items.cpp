
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        
        long long both = min(need1, need2);
        
        long long costA = both * costBoth
                        + (need1 - both) * cost1
                        + (need2 - both) * cost2;
        
        long long costB = 1LL * max(need1, need2) * costBoth;
        
        long long costC = 1LL * need1 * cost1
                        + 1LL * need2 * cost2;
        
        return min({costA, costB, costC});
    }
};
