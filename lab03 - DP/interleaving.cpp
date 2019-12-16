#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    static bool isInterleave(string s1, string s2, string s3)
    {
        auto n = s1.size(), m = s2.size(), p = s3.size();
        
        if (p != n + m) return false;
        
        auto sol = vector<bool>(m + 1, true);

        for (auto j = 1; j <= m; ++j)
            sol[j] = sol[j - 1] && (s2[j - 1] == s3[j - 1]);

        for (auto i = 1; i <= n; ++i)
        {
            sol[0] = sol[0] && (s1[i - 1] == s3[i - 1]);

            for (auto j = 1; j <= m; ++j)
            {
                sol[j] = (sol[j] && (s1[i - 1] == s3[i + j - 1]))
                      || (sol[j - 1] && (s2[j - 1] == s3[i + j - 1]));
            }
        }
        
        return sol[m];
    }
};

int main()
{
    cout << boolalpha::Solution::isInterleave("aabcc", "dbbca", "aadbbcbcac") << endl;
}