class Solution {
public:
    int solve(string &s, string &t, int i, int j){
        if(j >= t.size()) return 1;
        if(i >= s.size()) return 0;

        int ans;
        if(s[i] == t[j]){
            ans = solve(s, t, i+1, j+1) + solve(s, t, i+1, j);
        }
        else{
            ans = solve(s, t, i+1, j);
        }

        return ans;
    }

    int solveMem(string &s, string &t, int i, int j, vector<vector<int>> &dp){
        if(j >= t.size()) return 1;
        if(i >= s.size()) return 0;

        if(dp[i][j] != -1){
            return dp[i][j];
        }

        int ans;
        if(s[i] == t[j]){
            ans = solveMem(s, t, i+1, j+1, dp) + solveMem(s, t, i+1, j, dp);
        }
        else{
            ans = solveMem(s, t, i+1, j, dp);
        }

        return dp[i][j] = ans;
    }

    int solveTab(string s, string t){
        static int MOD = (int)1e9 + 7;
        int n = s.size();
        int m = t.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for(int i=0; i<n+1; i++){
            dp[i][m] = 1;
        }

        for(int i=n-1; i>=0; i--){
            int ans;
            for(int j=m-1; j>=0; j--){
                if(s[i] == t[j]){
                    ans = dp[i+1][j+1]%MOD + dp[i+1][j]%MOD;
                }
                else{
                    ans = dp[i+1][j];
                }

                dp[i][j] = ans;
            }
        }

        return dp[0][0];
    }

    int solveSO(string s, string t){
        static int MOD = (int)1e9 + 7;
        int n = s.size();
        int m = t.size();

        vector<int> curr(m+1, 0);
        vector<int> next(m+1, 0);

        for(int i=n-1; i>=0; i--){
            next[m] = 1;
            int ans;

            for(int j=m-1; j>=0; j--){
                if(s[i] == t[j]){
                    ans = next[j+1]%MOD + next[j]%MOD;
                }
                else{
                    ans = next[j];
                }

                curr[j] = ans;
            }

            next = curr;
        }

        return curr[0];
    }

    int numDistinct(string s, string t) {
        // int n = s.size();
        // int m = t.size();
        // vector<vector<int>> dp(n, vector<int>(m, -1));

        // return solveMem(s, t, 0, 0, dp);

        return solveSO(s, t);
    }
};