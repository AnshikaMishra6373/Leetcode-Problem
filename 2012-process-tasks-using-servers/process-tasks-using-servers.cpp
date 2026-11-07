class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> free;

        priority_queue<pair<long long,pair<int,int>>,
            vector<pair<long long,pair<int,int>>>,
            greater<pair<long long,pair<int,int>>>> busy;

        for(int i = 0; i < n; i++) {
            free.push({servers[i], i});
        }

        vector<int> ans(m);
        long long time = 0;

        for(int j = 0; j < m; j++) {

            time = max(time, (long long)j);

            while(!busy.empty() && busy.top().first <= time) {
                auto x = busy.top();
                busy.pop();

                free.push({x.second.first, x.second.second});
            }

            if(free.empty()) {
                time = busy.top().first;

                while(!busy.empty() && busy.top().first <= time) {
                    auto x = busy.top();
                    busy.pop();

                    free.push({x.second.first, x.second.second});
                }
            }

            auto x = free.top();
            free.pop();

            int weight = x.first;
            int index = x.second;

            ans[j] = index;

            busy.push({time + tasks[j], {weight, index}});
        }

        return ans;
    }
};