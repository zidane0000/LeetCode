#pragma once
#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>
#include <stack>
#include <set>
#include <unordered_set>
#include <queue>
#include <functional>
#include <unordered_map>
#include <sstream>          //stringstream
#include <bitset>
#include <numeric>

#include "class.h"

// 6. Zigzag Conversion
//��� runtime beats:44.06% memory beats:49.42%
std::string convert(std::string s, int numRows) {
    if (numRows == 1)
        return s;

    std::vector<std::string> ans(numRows, "");
    int len = s.length();
    int row_posi = 0;
    int arrow = 1;
    for (int i = 0; i < len; i++) {
        ans[row_posi] = ans[row_posi] + s[i];
        if (i % (numRows - 1) == 0 && i != 0) { arrow *= -1; }
        row_posi += arrow;
    }
    
    s = "";
    for (int i = 0; i < numRows; i++) { s += ans[i]; }
    return s;
}

// 7. Reverse Integer
//��� runtime beats:100.00% memory beats:76.02%
int reverse(int x) {
    if (INT_MIN >= x or INT_MAX <= x)
        return 0;

    long ans = 0;
    bool is_negative = false;
    if (x < 0) {
        x = -x;
        is_negative = true;
    }

    while (x > 0) {
        if (ans * 10 > INT_MAX) return 0;
        ans = ans * 10 + x % 10;
        x = x / 10;
    }

    if (is_negative) ans = -ans;
    return (int)ans;
}

// 8. String to Integer (atoi)
//��� runtime beats:82.99% memory beats:12.81%
int myAtoi(std::string s) {
    int posi = 0;
    int len = s.length();
    bool is_negative = false;
    bool have_ans = false;

    while (posi < len) {
        // ascii code :  ' ' -> 32, + -> 43, - -> 45, 0 -> 48, 9 -> 57
        int ascii = int(s[posi++]);

        // step1. Read in and ignore any leading whitespace.
        if (ascii == 32) {
            if (have_ans) break;
            else continue;
        }

        // step2. Check if the next character (if not already at the end of the string) is '-' or '+'
        if (ascii == 43 or ascii == 45 or (ascii >= 48 and ascii <= 57)) {
            if (ascii == 45) is_negative = true;
            // step3. Read in next the characters until the next non-digit character or the end of the input is reached. The rest of the string is ignored.
            while (posi < len) {
                have_ans = true;
                ascii = int(s[posi++]);
                if (ascii >= 48 and ascii <= 57) {
                    continue;
                }
                else
                    break;
            }
        }
        else
            break;

        if (have_ans) break;
    }

    // step4. Convert these digits into an integer. If no digits were read, then the integer is 0. Change the sign as necessary.
    int ans = 0;
    s = s.substr(0, posi);
    len = s.length();
    posi = 0;
    while (posi < len) {
        int ascii = int(s[posi]);
        posi++;
        if (ascii >= 48 and ascii <= 57) {
            // step5. If the integer is out of the 32-bit signed integer range, then clamp the integer so that it remains in the range.
            if (ans > (INT_MAX / 10)) { return is_negative ? INT_MIN : INT_MAX; }
            ans = ans * 10;
            if (ans == INT_MAX - 7 and (ascii - 48) > 7) { return is_negative ? INT_MIN : INT_MAX; }
            ans = ans + (ascii - 48);
        }
    }
    ans = is_negative ? -ans : ans;

    // step6. Return the integer as the final result
    return (int)ans;
}

// 13. Roman to Integer
//��� runtime beats:77.18% memory beats:64.52%
int romanToInt(std::string s) {
    /*
    Symbol       Value
    I            1
    V            5
    X            10
    L            50
    C            100
    D            500
    M            1000

    It is guaranteed that s is a valid roman numeral in the range [1, 3999]
    I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.
    */
    int ans = 0;
    int len = s.length();
    int before = 0;
    for (int i = 0; i < len; i++) {
        before = i - 1;
        if (s[i] == 'I') { ans += 1; }
        else if (s[i] == 'V') {
            if (before > -1 and s[before] == 'I') { ans += 3; }
            else { ans += 5; }
        }
        else if (s[i] == 'X') {
            if (before > -1 and s[before] == 'I') { ans += 8; }
            else { ans += 10; }
        }
        else if (s[i] == 'L') {
            if (before > -1 and s[before] == 'X') { ans += 30; }
            else { ans += 50; }
        }
        else if (s[i] == 'C') {
            if (before > -1 and s[before] == 'X') { ans += 80; }
            else { ans += 100; }
        }
        else if (s[i] == 'D') {
            if (before > -1 and s[before] == 'C') { ans += 300; }
            else { ans += 500; }
        }
        else if (s[i] == 'M') {
            if (before > -1 and s[before] == 'C') { ans += 800; }
            else { ans += 1000; }
        }
    }

    return ans;
}

// 29. Divide Two Integers
//https://medium.com/@ChYuan/leetcode-29-divide-two-integers-%E5%BF%83%E5%BE%97-medium-91e5fccb29fa
//���� runtime beats:100.00% memory beats:29.23%
int divide(int dividend, int divisor) {
    //  divide two integers without using multiplication, division, and mod operator
    if (divisor == 1) return dividend;
    if (divisor == -1) {
        if (dividend == INT_MIN) { return INT_MAX; }
        else { return -dividend; }
    }

    int sign = ((dividend >= 0) ^ (divisor >= 0)) ? -1 : 1;
    long long int quotient = 0;
    long long int sum = 0;

    long long int dividendL = dividend;
    dividendL = abs(dividendL);
    long long int divisorL = divisor;
    divisorL = abs(divisorL);

    for (int i = 31; i >= 0; i--)
    {
        if ((dividendL >> i) >= divisorL)
        {
            dividendL -= (divisorL << i);
            quotient += (1LL << i);
        }
    }

    if (sign * quotient > INT_MAX)
        return INT_MAX;

    return sign * quotient;
}

//https://www.youtube.com/watch?v=6kFp_s_UtPE
//���� runtime beats:10.53% memory beats:76.31%
int divide_2(int dividend, int divisor) {
    // long long int for abs(INT_MIN)
    long long int dividendLL = dividend;
    long long int divisorLL = divisor;

    long long int d = abs(dividendLL);
    long long int dv = abs(divisorLL);
    long long int ans = 0;

    long long int tmp_dv, multiple;
    while (d >= dv) {
        tmp_dv = dv;
        multiple = 1;
        while (d >= tmp_dv) {
            d -= tmp_dv;
            ans += multiple;
            // double tmp divisor
            tmp_dv += tmp_dv;
            multiple += multiple;
        }
    }

    ans = ((dividend >= 0) ^ (divisor >= 0)) ? -ans : ans;
    ans = ans > INT_MIN ? ans : INT_MIN;
    ans = ans > INT_MAX ? INT_MAX : ans;
    return ans;
}

// 543. Diameter of Binary Tree
//��� runtime beats:58.77% memory beats:93.14%
int getDeepest(int* ans, TreeNode* node) {
    int left_deepest = 0, right_deepest = 0;
    if (node->left) { left_deepest = getDeepest(ans, node->left) + 1; }

    if (node->right) { right_deepest = getDeepest(ans, node->right) + 1; }
    node->val = left_deepest + right_deepest;
    *ans = (*ans > node->val) ? *ans : node->val;
    return left_deepest > right_deepest ? left_deepest : right_deepest;
}

int diameterOfBinaryTree(TreeNode* root) {
    int ans = -1;
    getDeepest(&ans, root);
    return ans;
}

// 347. Top K Frequent Elements
//��� runtime beats:05.22% memory beats:99.98%
//std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
//    std::vector<int> ans;
//    std::vector<int> count;
//    int index = 0, index_before = 0, tmp = 0;
//    for (int i = 0; i < nums.size(); i++) {
//        auto it = std::find(ans.begin(), ans.end(), nums[i]);
//        if (it == ans.end()) {
//            ans.push_back(nums[i]);
//            count.push_back(1);
//        }
//        else {
//            index = std::distance(ans.begin(), it);
//            count[index]++;
//
//            index_before = index - 1;
//            while ((index_before > -1) and (count[index] > count[index_before])) {
//                // switch index and index_before
//                tmp = count[index];
//                count[index] = count[index_before];
//                count[index_before] = tmp;
//
//                tmp = ans[index];
//                ans[index] = ans[index_before];
//                ans[index_before] = tmp;
//
//                index--;
//                index_before = index - 1;
//            }
//        }
//    }
//        
//    return std::vector<int>(ans.begin(), ans.begin()+k);
//}

//https://www.youtube.com/watch?v=YPTqKIgVk-k
//���� runtime beats:86.35% memory beats:06.25%
std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    // bucket sort
    std::unordered_map<int, int> count;

    for (auto num : nums) { count[num] = 1 + count[num]; }

    int len = nums.size();
    std::vector<std::vector<int>> freq(len);
    for (auto it : count) { freq[it.second - 1].push_back(it.first); }

    std::vector<int> ans;
    for (int i = 0; i < len; i++) {
        std::vector<int> part_ans = freq[len - 1 - i];
        ans.insert(ans.end(), part_ans.begin(), part_ans.end());
        if (ans.size() >= k) { break; }
    }

    return ans;
}

//378. Kth Smallest Element in a Sorted Matrix
//��� runtime beats:11.05% memory beats:05.69%
int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
    int n = matrix[0].size();

    std::multiset<int> mset;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mset.insert(matrix[i][j]);
        }
    }

    int ans = *std::next(mset.begin(), k - 1);
    return ans;
}

//https://yoyoman822.pixnet.net/blog/post/65621230
//���� runtime beats:48.20% memory beats:92.86%
//int m, n;
//int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
//    m = matrix.size(), n = matrix[0].size(); // For general, the matrix need not be a square
//    int left = matrix[0][0], right = matrix[m - 1][n - 1], ans = -1;
//    while (left <= right) {
//        int mid = (left + right) >> 1;
//        if (countLessOrEqual(matrix, mid) >= k) {
//            ans = mid;
//            right = mid - 1; // try to looking for a smaller value in the left side
//        }
//        else left = mid + 1; // try to looking for a bigger value in the right side
//    }
//    return ans;
//}
//
//int countLessOrEqual(std::vector<std::vector<int>>& matrix, int x) {
//    int cnt = 0, c = n - 1; // start with the rightmost column
//    for (int r = 0; r < m; ++r) {
//        while (c >= 0 && matrix[r][c] > x) --c;  // decrease column until matrix[r][c] <= x
//        cnt += (c + 1);
//    }
//    return cnt;
//}

//394. Decode String
//��� runtime beats:100.00% memory beats:56.76%
std::string decodeString(std::string s) {
    int squareBracketsCount = 0;

    std::stack<int> times;
    std::stack<std::string> candidates;
    std::string ans = "";
    int ascii;
    for (char c : s) {
        if (c == '[') { //square brackets
            squareBracketsCount += 1;
            candidates.push("");
        }
        else if (c == ']') {
            squareBracketsCount--;

            std::string part_ans = "";
            for (int i = 0; i < times.top(); i++) {
                part_ans += candidates.top();
            }
            candidates.pop();
            times.pop();
            
            if ((squareBracketsCount <= 0) or (squareBracketsCount > times.size())) {
                ans += part_ans;
            }
            else {
                if (!candidates.empty()) {
                    part_ans = candidates.top() + part_ans;
                    candidates.pop();
                }
                candidates.push(part_ans);
            }
        }

        ascii = int(c);
        if (ascii >= 48 and ascii < 58) { //digits
            if ((times.empty()) or (squareBracketsCount >= times.size())) {
                times.push(ascii - 48);
            }
            else {
                int tmp = times.top();
                times.pop();
                times.push(tmp * 10 + ascii - 48);
            }
        }
        else if (ascii >= 97 and ascii <= 122) { //lowercase English letters
            if (squareBracketsCount == 0) {
                ans += c;
            }
            else if ((candidates.empty()) or (squareBracketsCount > candidates.size())) {
                candidates.push(std::string(1, c));
            }
            else {
                std::string tmp = candidates.top();
                candidates.pop();
                candidates.push(tmp + c);
            }
        }
    }

    while (!candidates.empty()) {
        ans = ans + candidates.top();
        candidates.pop();
    }
    return ans;
}

//437. Path Sum III
//��� runtime beats:05.57% memory beats:05.03%
//void RecrsivePathSum(TreeNode* node, int& targetSum, int& ans, std::queue<long long> candidates, std::queue<long long> new_candidates) {
//    if (!node) return;
//    int node_val = node->val;
//    if (node_val == targetSum)
//        ans += 1;
//
//    new_candidates.push(node_val);
//
//    while (!candidates.empty()) {
//        long long front = candidates.front();
//        if ((front + node_val) == targetSum)
//            ans += 1;
//        new_candidates.push(front + node_val);
//        candidates.pop();
//    }
//
//    if (node->left)
//        RecrsivePathSum(node->left, targetSum, ans, new_candidates, candidates);
//
//    if (node->right)
//        RecrsivePathSum(node->right, targetSum, ans, new_candidates, candidates);
//
//    while (!new_candidates.empty()) {
//        long long front = new_candidates.front();
//        candidates.push(front - node_val);
//        new_candidates.pop();
//    }
//}
//
//
//int pathSum3(TreeNode* root, int targetSum) {
//    int ans = 0;
//    std::queue<long long> candidates;
//    std::queue<long long> new_candidates;
//    RecrsivePathSum(root, targetSum, ans, candidates, new_candidates);
//    return ans;
//}

//https://www.cnblogs.com/grandyang/p/6007336.html
//���� runtime beats:51.58% memory beats:76.91%
int sumUp(TreeNode* node, long long pre, int& sum) {
    if (!node) return 0;
    long long cur = pre + node->val;
    return (cur == sum) + sumUp(node->left, cur, sum) + sumUp(node->right, cur, sum);
}

int pathSum3(TreeNode* root, int sum) {
    if (!root) return 0;
    return sumUp(root, 0, sum) + pathSum3(root->left, sum) + pathSum3(root->right, sum);
}

//560. Subarray Sum Equals K
//��� runtime beats:51.58% memory beats:76.91%
int RecursiveSubarraySum(std::vector<int>& nums, int& k, int posi, int sum) {
    if (posi >= nums.size()) { 
        return sum == k; 
    }
    int c = RecursiveSubarraySum(nums, k, posi + 1, sum);
    int d = RecursiveSubarraySum(nums, k, posi + 1, sum + nums[posi]);
    return c + d;
}

int subarraySum(std::vector<int>& nums, int k) {
    // Given an array of integers numsand an integer k, return the total number of subarrays whose sum equals to k.
    // A subarray is a contiguous non - empty sequence of elements within an array.
    return RecursiveSubarraySum(nums, k, 0, 0);
}

//1448. Count Good Nodes in Binary Tree
//��� runtime beats:09.50% memory beats:91.25%
void goodNodesDFS(TreeNode* node, int max, int& goods) {
    if (!node) return;
    if (node->val >= max) {
        goods = goods + 1;
        max = node->val;
    }

    goodNodesDFS(node->left, max, goods);
    goodNodesDFS(node->right, max, goods);
}

int goodNodes(TreeNode* root) {
    int goods = 0;
    goodNodesDFS(root, INT_MIN, goods);
    return goods;      
}

//54. Spiral Matrix
//��� runtime beats:28.19% memory beats:29.77%
void getLine(std::vector<std::vector<int>>& matrix, std::vector<int>& ans, bool head) {
    if (head) {
        for (std::vector<std::vector<int>>::reverse_iterator i = matrix.rbegin(); i != matrix.rend(); ++i) {
            std::vector<int>& m_vector = *i;
            if (m_vector.size() > 0) {
                ans.push_back(m_vector.front());
                m_vector.erase(m_vector.begin());
            }
        }
    }
    else {
        for (std::vector<int>& m : matrix) {
            if (m.size() > 0) {
                ans.push_back(m.back());
                m.erase(m.end() - 1);
            }
        }
    }
}

std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    std::vector<int> ans;

    while (!matrix.empty()) {
        if (!matrix.empty()) {
            ans.insert(ans.end(), matrix.front().begin(), matrix.front().end());
            matrix.erase(matrix.begin());
        }

        if (!matrix.empty())
            getLine(matrix, ans, false);

        if (!matrix.empty()) {
            ans.insert(ans.end(), matrix.back().rbegin(), matrix.back().rend());
            matrix.erase(matrix.end() - 1);
        }

        if (!matrix.empty())
            getLine(matrix, ans, true);
    }
    return ans;
}

//739. Daily Temperatures
//https://leetcode.com/problems/daily-temperatures/discuss/384123/100-Speed-and-100-Space-C++
//���� runtime beats:27.47% memory beats:71.67%
std::vector<int> dailyTemperatures(std::vector<int>& T) {
    if (T.empty()) { return {}; }

    // A stack with values:  
    // <T[i], Number of days to the next larger number in T>
    std::stack<std::pair<int, int>> s;

    // The last number in T must have no value larger than it.
    s.push(std::make_pair(T.back(), 0));

    std::vector<int> ans(T.size(), 0);

    // Start from the back.
    for (int i = T.size() - 2; i >= 0; i--) {
        int counter = 1;

        // Pop the stack until its empty or the top number is smaller or equal to T[i]
        // The counter + the number of elements to the next larger number in T.
        while (!s.empty() && T[i] >= s.top().first)
        {
            counter += s.top().second;
            s.pop();
        }

        // If no number on stack is larger than T[i].
        if (s.empty()) {
            s.push(std::make_pair(T[i], 0));
        }
        else {
            s.push(std::make_pair(T[i], counter));
            ans[i] = counter;
        }
    }

    return ans;
}

//637. Average of Levels in Binary Tree
//��� runtime beats:65.95% memory beats:72.83%
std::vector<double> averageOfLevels(TreeNode* root) {
    std::vector<double> ans({0.0});

    //BFS
    std::queue<TreeNode*> q({ root });
    int now = 1; // first level count
    int now_record = 1;
    int next = 0;

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        now--;
        ans[ans.size() - 1] += node->val;

        if (node->left) {
            q.push(node->left);
            next++;
        }

        if (node->right) {
            q.push(node->right);
            next++;
        }

        if (now == 0) {
            //next level;
            ans[ans.size() - 1] = ans[ans.size() - 1] / now_record;
            if (next > 0)
                ans.push_back(0);
            now = now_record = next;
            next = 0;
        }
    }

    return ans;
}

//967. Numbers With Same Consecutive Differences
//https://haren-lin-1.gitbook.io/leetcode-training/backtracking/967.-numbers-with-same-consecutive-differences
//���� runtime beats:100.00% memory beats:90.47%
std::vector<int> numsSameConsecDiff(int n, int k) {
    // 1. Maintain a queue for BFS traversal
    std::deque<int> que;
    for (int startnum = 1; startnum < 10; startnum++) que.push_back(startnum);
    // 2. Traversal by bit numbers, stop when n is reached
    for (int i = 1; i < n; i++) {
        int que_size = que.size();
        // BFS traveral
        for (int i = 0; i < que_size; i++) {
            int curNum = que.front(); que.pop_front();
            int right_most_num = curNum % 10;
            if (right_most_num + k < 10)
                que.push_back(curNum * 10 + right_most_num + k);
            if (k != 0 && right_most_num - k >= 0)
                que.push_back(curNum * 10 + right_most_num - k);
        }
    }
    // 3. Push the valid numbers from queue into results
    std::vector<int> res(que.begin(), que.end());
    return res;
}

//Weekly Contest 309
//2399. Check Distances Between Same Letters
//��� runtime beats:100.00% memory beats:50.00%
bool checkDistances(std::string s, std::vector<int>& distance) {
    int distance_record[26] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
    int posi = -1;
    for (int i = 0; i < s.size(); i++) {
        posi = int(s.at(i)-97);
        if (distance_record[posi] == -1) {
            distance_record[posi] = i;
        }
        else {
            if ((i - distance_record[posi] - 1) != distance[posi])
                return false;
            distance_record[posi] = i;
        }
    }

    return true;
}

//2400. Number of Ways to Reach a Position After Exactly k Steps
//https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/discuss/2527267/Top-Down-+-Bottom-Up-DP
//���� runtime beats:50.00% memory beats:50.00%
//int numberOfWaysDFS(int d, int k, int dp[][1001], int& mod) {
//    if (d >= k)
//        return d == k;
//    if (dp[d][k] == 0)
//        dp[d][k] = (1 + numberOfWaysDFS(d + 1, k - 1, dp, mod) + numberOfWaysDFS(abs(d - 1), k - 1, dp, mod)) % mod;
//    return dp[d][k] - 1;
//}
//
//int numberOfWays(int startPos, int endPos, int k) {
//    // will cause stack overflow
//    int dp[1001][1001] = {}, mod = 1000000007;
//    return numberOfWaysDFS(abs(startPos - endPos), k, dp, mod);
//}

//2401. Longest Nice Subarray
//��� runtime beats:33.33% memory beats:100.00%
int longestNiceSubarray(std::vector<int>& nums) {
    if (nums.size() == 1)
        return 1;
    int ans = 1;
    int start = 0;
    int end = 1;
    int sum = nums[start]; // sum of start to end-1
    int size = nums.size();
    while(start < size and end < size) {
        if ((sum & nums[end]) == 0) { //nice
            sum = sum | nums[end];
            end++;
            ans = ans > (end - start) ? ans : (end - start);
        }
        else {
            if ((end - start) == 1) {
                end++;
                start++;
                sum = nums[start];
            }
            else {
                sum = sum ^ nums[start];
                start++;
            }
        }
    }
    return ans;
}

//2402. Meeting Rooms III
//��� runtime beats:50.00% memory beats:50.00%
int mostBooked(int n, std::vector<std::vector<int>>& meetings) {
    return 0;
}

//987. Vertical Order Traversal of a Binary Tree
//��� runtime beats:39.72% memory beats:63.58%
void verticalTraversalDFS(TreeNode* node, int row, int col, int& col_offset, 
    std::vector<std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>>& tmp) {
    if (!node)
        return;

    if (node->left) {
        verticalTraversalDFS(node->left, row + 1, col - 1, col_offset, tmp);
    }

    if (col_offset > col) {
        for (int i = 0; i < (col_offset - col); i++) {
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> new_col;
            tmp.insert(tmp.begin(), new_col);
        }
        col_offset = col;
    }

    if (tmp.size() > (col - col_offset)) {
        tmp[(col - col_offset)].push(std::make_pair(row, node->val));
    }
    else {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> new_col;
        new_col.push(std::make_pair(row, node->val));
        tmp.push_back(new_col);
    }

    if (node->right) {
        verticalTraversalDFS(node->right, row + 1, col + 1, col_offset, tmp);
    }
}

std::vector<std::vector<int>> verticalTraversal(TreeNode* root) {
    std::vector<std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>>> tmp;
    int col_offset = 0;
    verticalTraversalDFS(root, 0, 0, col_offset, tmp);

    std::vector<std::vector<int>> ans;
    for (auto& vec : tmp) {
        std::vector<int> priority_queue_2_vec;

        while (!vec.empty()) {
            auto top = vec.top(); vec.pop();
            priority_queue_2_vec.push_back(top.second);
        }

        ans.push_back(priority_queue_2_vec);
    }
    return ans;
}

//429. N-ary Tree Level Order Traversal
//��� runtime beats:38.04% memory beats:86.69%
std::vector<std::vector<int>> levelOrder(Node* root) {
    if (!root) { return {}; }
    std::vector<std::vector<int>> ans({ {} });

    // BFS
    std::queue<Node*> q({ root });
    int count = 1; // count the same layer
    int next_count = 0;

    while (!q.empty()) {
        Node* front = q.front(); q.pop();

        for (auto child : front->children) {
            q.push(child);
            next_count++;
        }

        ans.back().push_back(front->val);
        count--;

        if (count <= 0 and next_count > 0) {
            count = next_count;
            next_count = 0;
            ans.push_back({});
        }
    }
    return ans;
}

//814. Binary Tree Pruning
//��� runtime beats:100.00% memory beats:99.74%
TreeNode* pruneTree(TreeNode* root) {
    if (!root)
        return root;

    if (root->left) {
        pruneTree(root->left);
        if ((root->left->val == 0) && !(root->left->left) && !(root->left->right))
            root->left = nullptr;
    }

    if (root->right) {
        pruneTree(root->right);
        if ((root->right->val == 0) && !(root->right->left) && !(root->right->right))
            root->right = nullptr;
    }

    if ((root->val == 0) && !(root->left) && !(root->right))
        return nullptr;
    else
        return root;
}

//606. Construct String from Binary Tree
//��� runtime beats:55.39% memory beats:96.64%
void tree2strDFS(TreeNode* node, std::string& ans) {
    if (!node)
        return;

    //if (node->val and !node->left and !node->right)
    ans += std::to_string(node->val);

    if (node->left) {
        ans += "(";
        tree2strDFS(node->left, ans);
        ans += ")";
    }

    if (node->right) {
        if (!node->left)
            ans += "()";
        ans += "(";
        tree2strDFS(node->right, ans);
        ans += ")";
    }
}

std::string tree2str(TreeNode* root) {
    std::string ans;
    tree2strDFS(root, ans);
    return ans;
}

//94. Binary Tree Inorder Traversal
//��� runtime beats:100.00% memory beats:75.10%
void inorderTraversalTreeNode(TreeNode* node, std::vector<int>& ans) {
    if (!node)
        return;

    if (node->left) { inorderTraversalTreeNode(node->left, ans); }
    ans.push_back(node->val);
    if (node->right) { inorderTraversalTreeNode(node->right, ans); }
}

std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> ans;
    inorderTraversalTreeNode(root, ans);
    return ans;
}

//1996. The Number of Weak Characters in the Game
//https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/discuss/1445186/EASY-C++-solution-with-great-explanation-and-comments-(nlogn)-sorting
//���� runtime beats:08.23% memory beats:91.78%
static bool comp(std::vector<int>& a, std::vector<int>& b){
    if (a[0] == b[0]) { return a[1] > b[1]; }
    return a[0] < b[0];
}

int numberOfWeakCharacters(std::vector<std::vector<int>>& properties)
{
    sort(properties.begin(), properties.end(), comp); //sorting the array
    int mtn = INT_MIN;                                //max till now while moving from right
    int ans = 0;

    for (int i = properties.size() - 1; i >= 0; i--) {
        if (properties[i][1] < mtn) // if the second parameter is also less increase the ans
            ans++;
        mtn = std::max(mtn, properties[i][1]);
    }
    return ans;
}

//188. Best Time to Buy and Sell Stock IV
//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-188-best-time-to-buy-and-sell-stock-iv/
//���� runtime beats:83.97% memory beats:98.77%
int maxProfitIV(int k, std::vector<int>& prices) {
    const int n = prices.size();
    std::vector<int> balance(k + 1, INT_MIN);   // balance[i][j] : = max balance by making at to up j buys in first i days. (Most hold a share)
    std::vector<int> profit(k + 1, 0);          // profit [i][j] : = max profit by making up to j sells in first i days. (Do not hold any share)
    for (int i = 0; i < n; ++i)
        for (int j = 1; j <= k; ++j) {
            balance[j] = std::max(balance[j], profit[j - 1] - prices[i]);
            profit[j] = std::max(profit[j], balance[j] + prices[i]);
        }
    return profit[k];
}

//509. Fibonacci Number
//��� runtime beats:07.99% memory beats:96.11%
int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

//1137. N-th Tribonacci Number
//��� runtime beats:100.00% memory beats:20.99%
int tribonacci_recursive(int n, std::vector<int>& dp) {
    if (dp[n] != INT_MIN)
        return dp[n];
    dp[n] = tribonacci_recursive(n - 1, dp) + tribonacci_recursive(n - 2, dp) + tribonacci_recursive(n - 3, dp);
    return dp[n];
}

int tribonacci(int n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;

    std::vector<int> dp(n + 1, INT_MIN);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    return tribonacci_recursive(n, dp);
}

//Weekly Contest 310
//Most Frequent Even Element
int mostFrequentEven(std::vector<int>& nums) {
    int ans = -1, times = 0;

    std::map<int, int> frequency;
    for (int num : nums) {
        if (num % 2 == 0) {
            frequency[num]++;
        }
    }

    for (auto element : frequency) {
        if (times < element.second) {
            times = element.second;
            ans = element.first;
        }
    }
    return ans;
}

//Optimal Partition of String
int partitionString(std::string s) {
    int ans = 0;
    std::string substring;

    for (char c : s) {
        if (substring.find(c) != std::string::npos) {
            ans++;
            substring = c;
        }
        else {
            substring += c;
        }
    }

    ans += 1;
    substring = "";

    return ans;
}

//Divide Intervals Into Minimum Number of Groups
static bool minGroupsCompare(std::vector<int>& a, std::vector<int>& b) {
    if (a[0] == b[0]) { return a[1] > b[1]; }
    return a[0] < b[0];
}

int minGroups(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end(), minGroupsCompare);
    int ans = 1;
    int end = intervals[0][1];
    std::priority_queue <int, std::vector<int>, std::greater<int> > candidates;
    for (int i = 1; i < intervals.size(); i++) {
        if (end > intervals[i][0]) {
            if (!candidates.empty() and candidates.top() < intervals[i][0])
                candidates.pop();
            else
                ans++;
            candidates.push(end);
        }
        end = intervals[i][1];
    }
    return ans;
}

//Longest Increasing Subsequence II
int lengthOfLIS(std::vector<int>& nums, int k) {
    return -1;
}

//70. Climbing Stairs
//��� runtime beats:100.00% memory beats:16.06%
int climbStarisRecursive(int n, std::vector<int>& dp) {
    if (dp[n] != INT_MIN)
        return dp[n];

    if (n < 3)
        dp[n] = n;
    else
        dp[n] = climbStarisRecursive(n - 1, dp) + climbStarisRecursive(n - 2, dp);
    return dp[n];
}

int climbStairs(int n) {
    std::vector<int> dp(n + 1, INT_MIN);
    return climbStarisRecursive(n, dp);
}

//746. Min Cost Climbing Stairs
//��� runtime beats:55.42% memory beats:96.77%
int minCostClimbingStairs(std::vector<int>& cost) {
    int size = cost.size();
    if (size == 2)
        for (int i = size - 3; i >= 0; --i)
            cost[i] = cost[i] + std::min(cost[i + 1], cost[i + 2]);
    return std::min(cost[0], cost[1]);
}

//1383. Maximum Performance of a Team
//https://youtu.be/Y7UTvogADH0
//���� runtime beats:23.24% memory beats:56.16%
int maxPerformance(int n, std::vector<int>& speed, std::vector<int>& efficiency, int k) {
    /*
    ���D����G
    �]�D�س]�p�̦h�� k ��u�{�v�A��ܥi�H��p�� k ��
    1. �ھ� efficiency �ƧǨC��u�{�v
    2. �b�� i ��u�{�v���F�����̤j�Ĳv�A���o��� efficiency �C��ۤv���u�{�v (�o�S���M�ҩҦ����p�A���L�O�i��̨θ�)
    3. �e(��)��ۤv���u�{�v�A�]���ۤv���̧C�� efficiency�A�ҥH���ΦҼ{�e���u�{�v�� efficiency�A�u�ݦb�N speed�A�]����� k - 1 �ӳ̤j����ۤv���u�{�v
    4. �ھ��D�ةw�q�A�^�� modulo 1e9 + 7
    */

    std::vector<std::pair<int, int>> efficiency_speed;  //�ھ� efficiency �ƧǨC��u�{�v
    for (int i = 0; i < n; ++i)
        efficiency_speed.push_back({ efficiency[i], speed[i] });
    sort(efficiency_speed.rbegin(), efficiency_speed.rend());   

    std::priority_queue<int, std::vector<int>, std::greater<int>> candidates;        //k �Ӥu�{�v(k - 1 �ӳ̤j����ۤv���u�{�v + �ۤv)
    long speed_sum = 0;
    long ans = 0;                                //�̤j��
    for (int i = 0; i < n; ++i) {
        speed_sum += efficiency_speed[i].second;
        candidates.push(efficiency_speed[i].second);
        if (candidates.size() > k) {
            speed_sum -= candidates.top();
            candidates.pop();
        }
        ans = std::max(ans, speed_sum * efficiency_speed[i].first);
    }

    return ans % static_cast<int>(1e9 + 7); // �^�� modulo 1e9 + 7
}

//198. House Robber
//��� runtime beats:100.00% memory beats:77.67%
int rob(std::vector<int>& nums) {
    int size = nums.size();
    if (size < 3)
        return *std::max_element(nums.begin(), nums.end());

    nums[2] += nums[0];
    for (int i = 3; i < size; i++)
        nums[i] = nums[i] + std::max(nums[i - 2], nums[i - 3]);
    return *std::max_element(nums.begin(), nums.end());
}

//213. House Robber II
//��� runtime beats:100.00% memory beats:20.36%
int rob2(std::vector<int>& nums) {
    int size = nums.size();
    if (size < 3)
        return *std::max_element(nums.begin(), nums.end());

    // �]���̫�@���P�Ĥ@���۾F�A�ҥH�Ҽ{�����Ĥ@���H�γ̫�@�����̤j��
    std::vector<int> nums_no_top = nums;
    nums_no_top.pop_back();
    nums.erase(nums.begin());

    return std::max(rob(nums_no_top), rob(nums));
}

//740. Delete and Earn
//��� runtime beats:82.61% memory beats:51.55%
int deleteAndEarn(std::vector<int>& nums) {
    // ���N nums �ഫ�� 1 ~ 10000 ������ dp�A���U�ӴN�p House Robber �@��
    const int max_value = 10000;
    std::vector<int> dp(max_value, 0); // 1 <= nums[i] <= 1e4
    for (int i : nums)
        dp[i - 1] += i;

    dp[2] += dp[0];
    for (int i = 3; i < max_value; i++)
        dp[i] += std::max(dp[i - 2], dp[i - 3]);

    return *max_element(dp.begin(), dp.end());
}

//948. Bag of Tokens
//��� runtime beats:72.03% memory beats:27.39%
int bagOfTokensScore(std::vector<int>& tokens, int power) {
    std::sort(tokens.begin(), tokens.end());
    if (tokens.size() == 0 or power < tokens[0])
        return 0;

    int score = 0;
    bool keepGo = true;
    std::deque<int> dq(tokens.begin(), tokens.end());
    while (!dq.empty() && keepGo) {
        if (power >= dq.front()) {
            power -= dq.front();
            dq.pop_front();
            score++;
        }
        else {
            // power not enough for tokens
            if (dq.size() <= 1) {
                keepGo = false;
            }
            else {
                score--;
                power += dq.back();
                dq.pop_back();
            }
        }
    }

    return score;
}

//393. UTF-8 Validation
//��� runtime beats:72.82% memory beats:76.31%
bool validUtf8(std::vector<int>& data) {
    int NumOfBytes = 0;
    for (int& i : data) {
        if (NumOfBytes == 0) {
            //CountBytes
            if ((i >> 3) == 0b11110) { NumOfBytes = 3; }       // 4 bytes
            else if ((i >> 4) == 0b1110) { NumOfBytes = 2; }   // 3 bytes
            else if ((i >> 5) == 0b110) { NumOfBytes = 1; }    // 2 bytes
            else if ((i >> 7) == 0) { NumOfBytes = 0; }        // 1 bytes
            else return false;
        }
        else {
            if ((i >> 6) == 0b10) { NumOfBytes -= 1; }
            else return false;
        }
    }
    return NumOfBytes == 0;
}

//55. Jump Game
//��� runtime beats:64.09% memory beats:18.18%
bool canJump(std::vector<int>& nums) {
    const int size = nums.size();
    std::vector<bool> isJump(size, false);
    isJump[0] = true;

    for (int i = 0; i < size - 1; i++) {
        if (isJump[i]) {
            int fillNum = nums[i] > (size - 1 - i) ? (size - 1 - i) : nums[i];
            std::fill(isJump.begin() + 1 + i, isJump.begin() + 1 + i + fillNum, true);
        }
    }
    return isJump[size - 1];
}

//45. Jump Game II
//��� runtime beats:27.53% memory beats:27.57%
int jump(std::vector<int>& nums) {
    const int size = nums.size();
    std::vector<int> isJump(size, INT_MAX);
    isJump[0] = 0;

    for (int i = 0; i < size - 1; i++) {
        if (isJump[i] != INT_MAX) {
            int fillNum = nums[i] > (size - 1 - i) ? (size - 1 - i) : nums[i];
            for (int j = i + 1; j < i + 1 + fillNum; j++) {
                isJump[j] = std::min(isJump[j], isJump[i] + 1);
            }
        }
    }
    return isJump[size - 1];
}

//1457. Pseudo-Palindromic Paths in a Binary Tree
//��� runtime beats:11.59% memory beats:21.48%
void pseudoPalindromicPaths_DFS(TreeNode* node, std::set<int>& candidates, int& ans) {
    // �P candidates �t��A�t�令�\�Y����
    if (candidates.count(node->val))
        candidates.erase(node->val);
    else
        candidates.insert(node->val);

    if (!node->left and !node->right and (candidates.size() <= 1)) {        
        // �O�̫�@�Ӹ`�I�A�B�Կ�H�p�󵥩�1(����1�i�H�񤤶�)�A�N���^��
        ans++;
    }
    else {
        if (node->left) pseudoPalindromicPaths_DFS(node->left, candidates, ans);
        if (node->right) pseudoPalindromicPaths_DFS(node->right, candidates, ans);
    }

    // �b�̫�`�I�A�p�G�S���ۤv���ȥN��w�g�t��A�ҥH�n�ɦ^�h
    if (candidates.count(node->val))
        candidates.erase(node->val);
    else
        candidates.insert(node->val);
}

//int pseudoPalindromicPaths(TreeNode* root) {
//    std::set<int> candidates;
//    int ans = 0;
//    pseudoPalindromicPaths_DFS(root, candidates, ans);
//    return ans;
//}

//�G�� runtime beats:34.77% memory beats:50.95%
int pseudoPalindromicPaths(TreeNode* root) {
    // �Φ��^��Y�ƭȨ�⦨��
    // �Q�έȤ���1-9 �����S�ʡA�N 1 - 9 �s�b 1��9�� bit�A�Y�i�`�ٰO����
    int ans = 0;
    std::stack<std::pair<TreeNode*, int>> candidates({ {root, 0} });

    while (!candidates.empty()) {
        TreeNode* node = candidates.top().first;
        int value = candidates.top().second;
        candidates.pop();
        value = value ^ (1 << node->val);
        if (!node->left and !node->right and !(value & (value - 1))) ans += 1;
        if (node->right) candidates.push({ node->right, value });
        if (node->left) candidates.push({ node->left, value });
    }

    return ans;
}

//53. Maximum Subarray
//��� runtime beats:05.04% memory beats:90.50%
int maxSubArray(std::vector<int>& nums) {
    int size = nums.size();
    int ans = nums[0];
    for (int i = 1; i < size; i++) {
        nums[i] = std::max(nums[i - 1], 0) + nums[i];
        ans = std::max(ans, nums[i]);
    }
    return ans;
}

//918. Maximum Sum Circular Subarray
//https://leetcode.com/problems/maximum-sum-circular-subarray/discuss/178422/One-Pass
//���� runtime beats:23.39% memory beats:33.15%
int maxSubarraySumCircular(std::vector<int>& A) {
    /*
    �]���D�ج����ΡA�ҥH����إi��A�Ĥ@�جO�P53�D�@�ˡA�ĤG�جO������ӼƲլۥ[�H�̤j�l�Ʋ�
    �b�ĤG�ر��p�U�A�i�H�ϵ��]���n�ۥ[������ݪ��l�ƲաA�N�������@�q���n���A�ӳo�Ӥ��n���O�̤p�l�Ʋ�
    �]���i�N�ĤG�ر��p�����Nvector���H-1����̤j�l�Ʋ�(�Y���̤p�l�Ʋ�)
    ���L�����p���ҥ~�A�N�O��vector���O�p�󵥩�0�A�b�����p�U���ר̲Ĥ@�ج��D
    */
    int sum = 0, mn = INT_MAX, mx = INT_MIN, curMax = 0, curMin = 0;
    for (int num : A) {
        curMin = std::min(curMin + num, num);
        mn = std::min(mn, curMin);
        curMax = std::max(curMax + num, num);
        mx = std::max(mx, curMax);
        sum += num;
    }
    return (sum - mn == 0) ? mx : std::max(mx, sum - mn);
}

//2007. Find Original Array From Doubled Array
//��� runtime beats:89.77% memory beats:87.90%
std::vector<int> findOriginalArray(std::vector<int>& changed) {
    if (changed.size() % 2)
        return {};
    std::sort(changed.begin(), changed.end());
    bool need_record = true;
    std::unordered_map<int, int> hashmap;
    std::vector<int> ans;
    for (int i : changed) {
        need_record = true;
        auto double_i = hashmap.find(i * 2);
        if (double_i != hashmap.end()) {
            need_record = false;
            double_i->second -= 1;
            ans.push_back(i);
            if (double_i->second == 0)
                hashmap.erase(double_i);
        }

        auto half_i = hashmap.end();
        if (need_record and (i % 2 == 0)) {
            half_i = hashmap.find(i / 2);
            if (half_i != hashmap.end()) {
                need_record = false;
                half_i->second -= 1;
                ans.push_back(i / 2);
                if (half_i->second == 0) {
                    hashmap.erase(half_i);
                }
            }
        }

        if (need_record)
            hashmap[i] += 1;
    }

    if (hashmap.size())
        return {};
    else
        return ans;
}

//152. Maximum Product Subarray
//��� runtime beats:46.93% memory beats:71.04%
int maxProduct(std::vector<int>& nums) {
    int ans = nums[0], min = 0, a, b, c;
    /*
    �b num[i] �ɷ|�x�s�̤j�i��A�Ҷq��|���t�ƪ���]�A�Q�� min �x�s�b num[i-1] �ɪ��̤p�i��
    �ҥH num[i] �|�O�T�ӼƦr(num[i], num[i]*num[i-1], num[i] * min)���̤j
    �� min �|�O�T�ӼƦr(num[i], num[i]*num[i-1], num[i] * min)���̤p
    */
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i - 1] || min) { // previous / min not zero
            a = nums[i] * nums[i - 1];
            b = nums[i];
            c = nums[i] * min;
            min = a < b ? a : b;
            min = min < c ? min : c;
            nums[i] = a > b ? a : b;
            nums[i] = nums[i] > c ? nums[i] : c;
        }
        ans = std::max(ans, nums[i]);
    }
    return ans;
}

//1567. Maximum Length of Subarray With Positive Product
//��� runtime beats:11.23% memory beats:75.53%
int getMaxLen(std::vector<int>& nums) {
    int max_len = 0;
    // len is record highest len no matter sign, len_first_negative record the first time sign changed to negative, so when nums[i] is positive, the max length is len - len_first_negative
    int len = 0, len_first_negative = 0;
    bool sign = true;  // product is positive or negative, and like nums[i-1] (last condition)

    for (int num : nums) {
        if (num) { // not zero
            sign = !(sign ^ (num > 0));
            len++;
            if (sign)
                max_len = std::max(max_len, len);
            else if (!sign and (num > 0))
                max_len = std::max(max_len, len - len_first_negative);
            else  if (!sign and (len_first_negative == 0) and (num < 0))
                len_first_negative = len;
        }
        else {
            len = 0;
            len_first_negative = 0;
            sign = true;
        }
    }

    return max_len;
}

//1770. Maximum Score from Performing Multiplication Operations
//https://youtu.be/8sMdqZ8z1l0
//���� runtime beats:06.19% memory beats:64.78%
int maximumScore(std::vector<int>& nums, std::vector<int>& multipliers) {
    // Top - Down
    const int m = multipliers.size();
    const int n = nums.size();
    std::vector<std::vector<int>> cache(m, std::vector<int>(m, INT_MIN));
    std::function<int(int, int)> dp = [&](int i, int j) { // i is left posi in nums, j is right posi in nums, k is position in multipliers
        const int k = n - (j - i + 1);
        if (k == m) return 0;
        int& ans = cache[i][k];
        if (ans != INT_MIN) return ans;
        return ans = std::max(dp(i + 1, j) + multipliers[k] * nums[i],
            dp(i, j - 1) + multipliers[k] * nums[j]);
    };
    return dp(0, n - 1);
}

//336. Palindrome Pairs
//https://www.cnblogs.com/grandyang/p/5272039.html
//���� runtime beats:91.66% memory beats:61.25%
std::vector<std::vector<int>> palindromePairs(std::vector<std::string>& words) {
    // 1. use lamba function to check if 
    std::function<bool(std::string&, int, int)> is_palindrome = [&](std::string& s, int i, int j) {
        while (i < j) {
            if (s[i] != s[j]) return false;
            i++;j--;
        }
        return true;
    };
    /*
    �N�w����word�bmap���O����m�A�bset���O������
    ���s�M��words�A�N�C��word�����M�O�_�s�b�A�Y�s�b�h�s�W����(�u�ݷs�W�@���A�]���M����t�~�@�Ӯɷ|�s�W�e�ᶶ���A�˪�����)
    ��C��word�ˬd�A�p�G�N��h�w������(set��)����r�ˬd�O�_�^��A�Y���^��A�h��Mword�Ѿl��r�O�_�s�bmap��
    ���ɦ���إi��A�@�جO�w�����ת���r��b�e�A�s�W(�w�����פ�r, word)�A�Ϊ̬O�w�����פ�r��b��
    */
    std::vector<std::vector<int>> ans;
    std::unordered_map<std::string, int> hash_map;  // map candidates to words position
    std::set<int> s;    // record known words length
    int size = words.size();

    for (int i = 0; i < size; ++i) { // Why ++i is often better than i++ (pre-increment vs. post-increment) -> https://betterprogramming.pub/stop-using-i-in-your-loops-1f906520d548
        hash_map[words[i]] = i;
        s.insert(words[i].size());
    }

    for (int i = 0; i < size; ++i) {
        // only consider same or shorter length as words[i]
        std::string rv_i(words[i].rbegin(), words[i].rend());
        if (hash_map.count(rv_i) and hash_map[rv_i] != i)
            ans.push_back({ i, hash_map[rv_i] }); // if there word[i] reverse word[j] exists. means word[j] reverse is word[i], so no need append {j, i}

        int len = words[i].size();
        auto a = s.find(len);
        // if words[i] minus existing word length from begin or end is palindrome, append {i, map[words[i].substr(begin or end)]}
        for (auto it = s.begin(); it != a; ++it) {            
            int d = *it;    // existing word length
            if (is_palindrome(rv_i, 0, len - d - 1) && hash_map.count(rv_i.substr(len - d)))    // words[i]
                ans.push_back({ i, hash_map[rv_i.substr(len - d)] });
            if (is_palindrome(rv_i, d, len - 1) && hash_map.count(rv_i.substr(0, d)))
                ans.push_back({ hash_map[rv_i.substr(0, d)], i });
        }
    }
    return ans;
}

//42. Trapping Rain Water
//https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-42-trapping-rain-water/
//���� runtime beats:39.49% memory beats:36.03%
//int trap(std::vector<int>& height) {
//    /*
//    height �� n �ӡA�p��b height[i] ���x�s�����q
//    �Y�����p��X�A�b height[i] �ɡA�̰�������H�Υk��A�h�x�s���q�� min(��,�k) - height[i]
//    */
//    int size = height.size();
//    std::vector<int> left(size);    // record the highest left in height[0~i]
//    std::vector<int> right(size);   // record the highest right in height[i~size-1]
//    for (int i = 0; i < size; i++) {
//        left[i] = i ? std::max(left[i - 1], height[i]) : height[i];
//        right[size - 1 - i] = i ? std::max(height[size - 1 - i], right[size - i]) : height[size - 1 - i];
//    }
//
//    int ans = 0;
//    for (int i = 0; i < size; ++i)
//        ans += std::min(left[i], right[i]) - height[i];
//
//    return ans;
//}

//609. Find Duplicate File in System
//��� runtime beats:89.69% memory beats:13.74%
std::vector<std::vector<std::string>> findDuplicate(std::vector<std::string>& paths) {
    std::vector<std::vector<std::string>> ans;
    std::unordered_map<std::string, int> m;
    
    int left, right, space;
    std::string directory, file, content, remain;
    for (auto& path : paths) {
        while (path != "") {
            left = path.find('(');
            space = path.find(' ');
            right = path.find(')');
            if (left == std::string::npos or right == std::string::npos)
                path = "";
            else {
                directory = path.substr(0, space);
                file = path.substr(space + 1, left - space - 1);
                content = path.substr(left + 1, right - left - 1);
                remain = path.substr(right + 1);
                path = directory + remain;
                if (m.count(content))
                    ans[m[content]].push_back(directory + "/" + file);
                else {
                    ans.push_back({ directory + "/" + file });
                    m[content] = ans.size() - 1;
                }
            }
        }
    }

    ans.erase(std::remove_if(ans.begin(), ans.end(), [](const std::vector<std::string>& x) {
        return x.size() < 2; // put your condition here
        }), ans.end());
    

    return ans;
}

//718. Maximum Length of Repeated Subarray
//��� runtime beats:12.57% memory beats:59.41%
int findLength(std::vector<int>& nums1, std::vector<int>& nums2) {
    // DP[i][j] �� n1[i] �P n2[j] ���e�s��h�֡ADP[i][j] = n1[i] == n2[j] ? 1 + dp[i-1][j-1] : 0;    
    int n1 = nums1.size(), n2 = nums2.size(), ans = INT_MIN;
    std::vector<std::vector<int>> dp(n1, std::vector<int>(n2, 0));
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (i and j)  // not border
                dp[i][j] = nums1[i] == nums2[j] ? 1 + dp[i - 1][j - 1] : 0;
            else
                dp[i][j] = nums1[i] == nums2[j];
            ans = std::max(ans, dp[i][j]);
        }
    }
    return ans;
}

//1014. Best Sightseeing Pair
//��� runtime beats:54.28%  memory beats:26.07%
int maxScoreSightseeingPair(std::vector<int>& values) {
    // �����̰����I�A�Ӵ��I�C���ʤ@���n��@
    int size = values.size(), maxScore = values[0] - 1, maxSpot = 0;
    for (int i = 1; i < size; i++) {
        maxSpot = std::max(maxSpot - 1, values[i - 1] - 1);
        maxScore = std::max(maxScore, maxSpot + values[i]);
    }
    return maxScore;
}

//121. Best Time to Buy and Sell Stock
//��� runtime beats:67.44%  memory beats:89.07%
//int maxProfit(std::vector<int>& prices) {
//    // �b prices[i-1] �x�s�̤p price
//    int size = prices.size(), maxprofit = 0;
//    for (int i = 1; i < size; i++) {
//        prices[i - 1] = i > 1 ? std::min(prices[i - 1], prices[i - 2]) : prices[i - 1];
//        maxprofit = std::max(maxprofit, prices[i] - prices[i-1]);
//    }
//    return maxprofit;
//}

//122. Best Time to Buy and Sell Stock II
//��� runtime beats:87.52%  memory beats:89.98%
//int maxProfit(std::vector<int>& prices) {
//    // �]���u�n p[i-1] < p[i] �Y�c�� profit �W�[�A�ҥH�N�� profit[i+1] > profit[i]�A�]�i���p�� p[i] - p[i-1] �� profit
//    int size = prices.size(), profit = 0;
//    for (int i = 1; i < size; i++)
//        if (prices[i - 1] < prices[i])
//            profit = profit + prices[i] - prices[i - 1];
//    return profit;
//}

//���� runtime beats:42.67%  memory beats:30.01%
//int maxProfit(std::vector<int>& prices) {
//    /*
//    * �x�s�̤j�Q��B�̤j���l(�Ĥ@���i���ʶR�A�ҥH�]���̤p����)
//    * ���l = max(���l, �Q�� - ����)
//    * �Q�� = max(�Q��, ���l + ����) // ���l�w�g�p��ѻ������A���ɥ[�W����Y�i�o��Q��
//    */
//    int profit = 0, balance = INT_MIN;
//    for (int& price : prices) {
//        balance = std::max(balance, profit - price);
//        profit = std::max(profit, balance + price);
//    }
//    return profit;
//}

//985. Sum of Even Numbers After Queries
//��� runtime beats:89.09%  memory beats:66.47%
std::vector<int> sumEvenAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
    std::vector<int> ans;
    int even_sum = 0;
    even_sum = std::accumulate(begin(nums), end(nums), 0, [](int s, int a) { return s + (!(a % 2) ? a : 0); });

    for (auto& query : queries) {
        if (!(nums[query[1]] % 2)) even_sum -= nums[query[1]];
        nums[query[1]] = nums[query[1]] + query[0];
        if (!(nums[query[1]] % 2)) even_sum += nums[query[1]];
        ans.push_back(even_sum);
    }
    return ans;
}

//309. Best Time to Buy and Sell Stock with Cooldown
//��� runtime beats:100.00%  memory beats:91.92%
int maxProfit(std::vector<int>& prices) {
    /*
    * ���O�O�����l�B�W�����l�B�Q��B�W���Q��
    * ���p�⵲�l(�O�_�ʶR)�A�]�����l�|�v�T��Q��(�O�_��X)
    * �]���n cooldown�A�ҥH�o�����l�|�O max(�W�����l, �W���Q�� - �o������)�A��ܽ�X
    * �ӳo���Q��O max(�W���Q��, �W�����l + �o������)�A��ܶR�J
    */
    int balance = INT_MIN, pre_balance = 0, profit = 0, pre_profit = 0;
    for (int& price : prices) {
        pre_balance = balance;
        balance = std::max(pre_profit - price, pre_balance);
        pre_profit = profit;
        profit = std::max(pre_balance + price, pre_profit); // �]�����l�|���p���O���ѻ��A�ҥH���ɥ[�W�{���ѻ����Q��
    }
    return profit;
}

//714. Best Time to Buy and Sell Stock with Transaction Fee
//��� runtime beats:60.92%  memory beats:91.61%
int maxProfit(std::vector<int>& prices, int fee) {
    // �P 121. �D�@�ˡA���L�b�p�� profit �ɦh��h foo
    int balance = INT_MIN, profit = 0;
    for (int& price : prices) {
        balance = std::max(balance, profit - price);
        profit = std::max(profit, balance + price - fee);
    }
    return profit;
}

//557. Reverse Words in a String III
//��� runtime beats:05.03%  memory beats:05.00%
std::string reverseWords(std::string& s) {
    int size = s.size();
    int i = s.find(' ');;

    while (i < size and i != -1) {
        for (int j = 0; j < i / 2; j++)
            std::swap(s[j], s[i - j - 1]);            
        s = s.substr(i + 1) + s.substr(0, i) + " ";
        size = size - i - 1;
        i = s.find(' ');
    }
    i = size;
    for (int j = 0; j < i / 2; j++)
        std::swap(s[j], s[i - j - 1]);
    s = s.substr(i) + s.substr(0, i);
    return s;
}

//���� runtime beats:19.79%  memory beats:75.20%
//std::string reverseWords(std::string s) {
//    for (int i = 0; i < s.length(); i++) {
//        if (s[i] != ' ') {   // when i is a non-space
//            int j = i;
//            for (; j < s.length() && s[j] != ' '; j++) {} // move j to the next space
//            reverse(s.begin() + i, s.begin() + j);
//            i = j - 1;
//        }
//    }
//    return s;
//}

//139. Word Break
//https://www.youtube.com/watch?v=Sx9NNgInc3A
//���� runtime beats:79.54%  memory beats:95.29%
bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    /*
    * s �������e i ��P�� size - i ��
    * dp[i] �����A�� size - i ��O�_�s�b�� wordDict ��
    */
    int size = s.size();
    std::vector<bool> dp(size + 1, false); // In dp[i], seperate s to front(i) and back(size - i) all in dict, then retur true    
    dp[size] = true; // default out of s is true

    // Time complexity : O(n * m)
    for (int i = size - 1; i >= 0; i--) {
        for(std::string& word : wordDict){
            if (!dp[i] and word == s.substr(i, word.size())) { // if dp[i] is true then don't need to check
                dp[i] = true and dp[i + word.size()];
            }
        }
    }

    return dp[0];
}

//42. Trapping Rain Water
//��� runtime beats:74.45%  memory beats:10.88%
//int trap(std::vector<int>& h) {
//    /*
//    * left[i] �O���q������i��̰����I�Aright[i]�����q�k����i���̰����I
//    * �h�ֿn�B�q�� min(left[i], right[i]) - h[i]
//    * Time Complexity: O(n)
//    * Space Complexity: O(n)
//    */
//    int size = h.size();
//    std::vector<int> l(size, 0), r(size, 0);
//
//    for (int i = 0; i < size; i++) {
//        l[i] = i ? std::max(h[i], l[i - 1]) : h[i];
//        r[size -1 -i] = i ? std::max(h[size - 1 - i], r[size - i]) : h[size - 1];
//    }
//
//    int ans = 0;
//    for (int i = 0; i < size; i++)
//        ans = ans + std::max(std::min(l[i], r[i]) - h[i], 0);
//    return ans;
//}

//���� runtime beats:83.53%  memory beats:81.93%
int trap(std::vector<int>& h) {
    /*
    * Use Two Pointer
    * l record left posi, max_l reocord 0 ~ left max value
    * r record right posi, max_r reocord right ~ end max value
    * Time Complexity: O(n)
    * Space Complexity: O(1)
    */
    const int size = h.size();
    int ans = 0;
    int l = 0, r = size - 1, max_l = h[0], max_r = h[size - 1];

    while (l < r) {
        if (max_l < max_r) {
            ans += max_l - h[l];
            max_l = std::max(max_l, h[++l]);
        }
        else {
            ans += max_r - h[r];
            max_r = std::max(max_r, h[--r]);
        }
    }
    return ans;
}

//1680. Concatenation of Consecutive Binary Numbers
//https://zxi.mytechroad.com/blog/bit/leetcode-1680-concatenation-of-consecutive-binary-numbers/
//���� runtime beats:84.24%  memory beats:82.61%
int concatenatedBinary(int n) {
    /*
    * �� (i & (i - 1)) == 0 �ɡA���ץ[�@�A�Ҧp�G100(4) & 11(3) �ɡA�r����ױq�쥻 2("11") �ܦ� 3("100")
    * �D�حn�D modulo(%) 10^9 + 7
    * ����(<<)���ηN�O�]���D�ئr��O����[�A�Ҧp�G n = 3 -> 1 + 2 + 3 = "1" + "10" + "11" = "11011"
    * �p�G�N�� binary string �ন decimal number�A�̫e����"1"�w�g�Q����4(2�Ӧ۩�"10"�A2�Ӧ۩�"11")
    * �l�ƪ������O�Ʊ� ans �����w�g���l�ơA�ҥH�b ans �������L�{���W�L mod�A�n����@�� mod�A�[�W����A��@��
    */
    constexpr int kMod = 1e9 + 7; // constexpre : https://tjsw.medium.com/%E6%BD%AE-c-constexpr-ac1bb2bdc5e2
    long ans = 0;
    for (int i = 1, len = 0; i <= n; ++i) {
        if ((i & (i - 1)) == 0) ++len;
        ans = ((ans << len) % kMod + i) % kMod;
    }
    return ans;
}

//113. Path Sum II
//��� runtime beats:39.73%  memory beats:39.09%
//void pathSum2_DFS(TreeNode* node, int& targetSum, std::vector<std::vector<int>>& ans, int sum, std::vector<int> cadndiate) {
//    if (!node) return;
//    sum = sum + node->val;
//    cadndiate.push_back(node->val);
//    if (!node->left and !node->right)
//        if (sum == targetSum)
//            return ans.push_back(cadndiate);
//    if (node->left)
//        pathSum2_DFS(node->left, targetSum, ans, sum, cadndiate);
//    if (node->right)
//        pathSum2_DFS(node->right, targetSum, ans, sum, cadndiate);
//};
//
//std::vector<std::vector<int>> pathSum(TreeNode* root, int& targetSum) {
//    //DFS
//    std::vector<std::vector<int>> ans;
//    pathSum2_DFS(root, targetSum, ans, 0, {});
//    return ans;
//}

//�G�� runtime beats:44.02%  memory beats:42.16%
std::vector<std::vector<int>> pathSum(TreeNode* root, int& targetSum) {
    //BFS
    if (!root) return {};
    std::vector<std::vector<int>> ans;
    std::queue<std::tuple<TreeNode*, int, std::vector<int>>> line({ {root, 0, {}} });

    while (!line.empty()) {
        TreeNode* node;
        int sum;
        std::vector<int> candidate;
        std::tie(node, sum, candidate) = line.front();
        line.pop();
        sum += node->val;
        candidate.push_back(node->val);

        if (!node->left and !node->right)
            if (sum == targetSum)
                ans.push_back(candidate);

        if (node->left)
            line.push({ node->left, sum,candidate });
        if (node->right)
            line.push({ node->right, sum,candidate });
    }

    return ans;
}

//622. Design Circular Queue
//��� runtime beats:05.11%  memory beats:11.06%
class MyCircularQueue {
private:
    std::list<int> circular_queue;
    int size = 0;
    int max_size = 0;
public:
    MyCircularQueue(int k) {
        max_size = k;
    }

    bool enQueue(int value) {
        if (size < max_size) {
            circular_queue.push_back(value);
            size++;
            return true;
        }
        return false;
    }

    bool deQueue() {
        if (size <= 0) return false;
        circular_queue.pop_front();
        size--;
        return true;
    }

    int Front() {
        if (size <= 0) return -1;
        return circular_queue.front();
    }

    int Rear() {
        if (size <= 0) return -1;
        return circular_queue.back();
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == max_size;
    }
};

//https://leetcode.com/problems/design-circular-queue/discuss/153529/Straightforward-Implementation-in-C++-20ms
//���� runtime beats:67.96%  memory beats:82.50%
//class MyCircularQueue {
//private:
//    std::vector<int> data;
//    int head;
//    int tail;
//    // empty is the mark when the queue is empty
//    // to differentiate from queue is full
//    // because in both conditions (tail == head) stands
//    bool empty;
//public:
//    // Initialize your data structure here. Set the size of the queue to be k.
//    MyCircularQueue(int k) {
//        data.resize(k);
//        head = 0;
//        tail = 0;
//        empty = true;
//    }
//
//    // Insert an element into the circular queue. Return true if the operation is successful.
//    bool enQueue(int value) {
//        if (isFull()) return false;        
//        if (head == tail && empty) empty = false;// update the reset value when first enqueue happens
//        data[tail] = value;
//        tail = (tail + 1) % data.size();
//        return true;
//    }
//
//    // Delete an element from the circular queue. Return true if the operation is successful.
//    bool deQueue() {
//        if (isEmpty()) return false;
//        head = (head + 1) % data.size();
//        if (head == tail && !empty) empty = true;
//        return true;
//    }
//
//    int Front() {
//        if (isEmpty()) return -1;
//        return data[head];
//    }
//
//    int Rear() {
//        if (isEmpty()) return -1;
//        return data[(tail + data.size() - 1) % data.size()];
//    }
//
//    bool isEmpty() {
//        if (tail == head && empty) return true;
//        return false;
//    }
//
//    bool isFull() {
//        if (tail == head && !empty) return true; // And with not reset
//        return false;
//    }
//};

//Weekly Contest 312
//Sort the People
std::vector<std::string> sortPeople(std::vector<std::string>& names, std::vector<int>& heights) {
    int size = heights.size();
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (heights[i] < heights[j]) {
                std::swap(heights[i], heights[j]);
                std::swap(names[i], names[j]);
            }
        }
    }
    return names;
}

//Longest Subarray With Maximum Bitwise AND
int longestSubarray(std::vector<int>& nums) {
    int size = nums.size();
    std::vector<int> dp(size, 0);
    int ans = 0;
    int max_num = INT_MIN;

    for (int i = 0; i < size; i++) {
        if (max_num < nums[i]) {
            max_num = nums[i];
            dp[i] = 1;
            ans = 1;
        }
        else if (max_num == nums[i]) {
            dp[i] = dp[i - 1] + 1;
        }
        ans = std::max(ans, dp[i]);
    }

    return ans;
}

//Find All Good Indices
std::vector<int> goodIndices(std::vector<int>& nums, int k) {
    // �b nums[i]�A�eK�쬰���W�[���ǦC�A��K�쬰����֪��ǦC
    std::vector<int> good_indices;
    int size = nums.size();
    std::queue<int> front;  // �x�s�ek��Ҧ��o�� not non-increasing ����m
    std::queue<int> back;   // �x�s��k��Ҧ��o�� not non-decreasing ����m

    if ((k * 2) < size) {
        for (int i = 1; i < k; i++) {
            if (nums[k - i - 1] < nums[k - i]) front.push(k - i);
            if (nums[k + i] > nums[k + i + 1]) back.push(k + i);
        }
    }

    for (int i = k; i < size - k; i++) {
        if (k > 1) {
            if (nums[i - 2] < nums[i - 1]) front.push(i - 1);
            if (nums[i + k - 1] > nums[i + k]) back.push(i + k - 1);
        }

        while (!front.empty() and (i - front.front() >= k)) front.pop();
        while (!back.empty() and (back.front() <= i)) back.pop();

        if (front.empty() and back.empty()) good_indices.push_back(i);
    }
    return good_indices;
}

//2421. Number of Good Paths
int numberOfGoodPaths(std::vector<int>& vals, std::vector < std::vector<int >>& edges) {
    return -1;
}


//990. Satisfiability of Equality Equations
//��� runtime beats:89.91%  memory beats:98.15%
int union_find(std::vector<int>& vec, int posi) {
    return vec[posi] == -1 || vec[posi] == posi ? posi : union_find(vec, vec[posi]);
}

bool equationsPossible(std::vector<std::string>& equations) {
    /*
    * �Ҭ� lowercase letter�A�ҥH�|�O 0-25�A���� vec ������m
    * vec ��������A�Y a==b�A�h vec[union_find(a)] = union_find(b)�A�Y b �� -1 �N�|�^�� b
    * ���U�ӭY a==c�A�h�|�ק� a ���������`�I b�A�N b �]�� c
    */
    std::sort(equations.begin(), equations.end(), [](std::string& a, std::string& b) { return a[1] == '=' and b[1] == '!'; });
    std::vector<int> vec(26, -1); // 0->a, 26->z, record the root of alphabet, default wth none(-1)
    for (auto& e : equations) {
        if (e[1] == '=')
            vec[union_find(vec, e[0] - 'a')] = union_find(vec, e[3] - 'a');
        if (e[1] == '!')
            if (union_find(vec, e[0] - 'a') == union_find(vec, e[3] - 'a'))
                return false;
    }
    return true;
}

//838. Push Dominoes
//��� runtime beats:12.83%  memory beats:42.63%
std::string pushDominoes(std::string& dominoes) {
    // �p��b i �ɡA�̾a�� L �P R �Z���A�� i == '.' �ɡA�h�ھڳ̤p L/R �Z�����ܤ�
    const int size = dominoes.size();
    std::vector<int> right(size, 0);
    std::vector<int> left(size, 0);

    for (int i = 0; i < size; i++) {
        if (dominoes[i] == 'R') right[i] = 1;
        else right[i] = i and right[i - 1] and dominoes[i] != 'L' ? right[i - 1] + 1 : right[i];

        if (dominoes[size - 1 - i] == 'L') left[size - 1 - i] = 1;
        else left[size - 1 - i] = i and left[size - i] and dominoes[size - 1 - i] != 'R' ? left[size - i] + 1 : left[size - 1 - i];
    }

    for (int i = 0; i < size; i++) {
        left[i] = left[i] == 0 ? INT_MAX : left[i]; 
        right[i] = right[i] == 0 ? INT_MAX : right[i];
        if (dominoes[i] == '.') {
            if (left[i] > right[i]) dominoes[i] = 'R';
            if (left[i] < right[i]) dominoes[i] = 'L';
        }
    }

    return dominoes;
}

//https://youtu.be/evUFsOb_iLY
//���� runtime beats:07.97%%  memory beats:33.28%
//std::string pushDominoes(std::string& dominoes) {
//    /*
//    * �H queue �x�s�S���p(L and R)
//    * ���۳B�z queue ����šA�o��n�T�w��V�A�Y�ѥ��ܥk�A�b�P�_�ɤ]�n�����b�k
//    * �HL���ҡA��L�ɡA�n�P�_L��m�O�_�j��0�A�P�_L�e�@��O�_��'.'
//    * ���ɭY�J��R�A�N�ݦh�P�_ R+2 �O�_�� L�A�p�G�OL�N��P(�hpop�@��) 
//    */
//    const int size = dominoes.size();
//    std::queue<std::pair<int, char>> q;
//    int i;
//    char c;
//    for (i = 0; i < size; i++)
//        if (dominoes[i] != '.') q.push({ i, dominoes[i] });
//
//    while (!q.empty()) {
//        i = q.front().first; c = q.front().second; q.pop();
//        if (c == 'L' and i > 0 and dominoes[i - 1] == '.') {
//            q.push({ i - 1, 'L' });
//            dominoes[i - 1] = 'L';
//        }
//        else if (c == 'R') {
//            if (i + 1 < size and dominoes[i + 1] == '.') {
//                if (i + 2 < size and dominoes[i + 2] == 'L')
//                    q.pop();
//                else {
//                    q.push({ i + 1, 'R' });
//                    dominoes[i + 1] = 'R';
//                }
//            }
//        }
//    }
//
//    return dominoes;
//}

//413. Arithmetic Slices
//��� runtime beats:68.37%  memory beats:49.56%
int numberOfArithmeticSlices(std::vector<int>& nums) {
    const int size = nums.size();
    if (size < 3) return 0;
    int ans = 0;
    std::vector<int> dp(size, 0);   // �����b��i��ɬ��s��X
    for (int i = 2; i < size; i++) {
        if ((nums[i] - nums[i - 1]) == (nums[i - 1] - nums[i - 2])) {
            dp[i] = dp[i - 1] + 1;
            ans += dp[i];
        }
    }
    return ans;
}

//91. Decode Ways
//https://youtu.be/OjEHST4SXfE
//���� runtime beats:29.19%  memory beats:25.93%
//int ways(std::unordered_map<int, int>& dp, std::string& s, int l, int r) {
//    if (dp.count(l)) return dp[l];
//    if (s[l] == '0') return 0;
//    if (l >= r) return 1;
//
//    int way = ways(dp, s, l + 1, r);
//    if ((s[l] == '1') or (s[l] == '2' and s[l+1] < '7'))
//        way += ways(dp, s, l + 2, r);
//    dp[l] = way;
//    return way;
//}
//
//
//int numDecodings(std::string s) {
//    /*
//    * �N s ����A�Y s = "102213" -> "02213" + "2213"�A���� "02213" �� 0�A�]���S��k�ѪR�H0�}�Y��s
//    * "2213" -> "213" + "13" -> "213"("13" + "3") + "13" -> ���� "13" �٥i�H����� "3" + ""(��)
//    * �� s ���פp�� 2 �ɡA�N��u���@�إi��ѡA���ɶ}�l�^��
//    * �̫�b map �������X�{�L�� s�A�קK���ƭp��
//    */
//    std::unordered_map<int, int> dp;
//    return ways(dp, s, 0, s.length() - 1);
//}

//���� runtime beats:63.16%  memory beats:93.17%
int numDecodings(std::string s) {
    /*
    * dp[i] ������ i ��s�b�X�ظѽX�覡�A�w�]dp[-1]���@�ӪšA�ӪŪ��ѽX�覡�u���@��
    * �]���� i �즳�|�إi��A���O��
    * 1. s[i]=0 �B s[i-1],s[i] ���b 0-26(a-z) ���A���ɥN��L�ѡA�^��0
    * 2. s[i]!=0�A�Ӳ�i��ѽX�覡�O��i-1�쪺�ѽX�覡�A�]���o�ɭԥu��s[i]�A�ӫDs[i-1],s[i]�A�ҥH�i���ܤƴN�u���@�ءA�Ydp[i] = dp[i-1]
    * 3. s[i-1],s[i] �b 0-26(a-z) ���A�P�W�A�@����s[i-1],s[i]�]�u���@�إi���ܤơA�ҥHdp[i] = dp[i-2]
    * 4. s[i]!=0 �B s[i-1],s[i] �b 0-26(a-z) ���A�o�ɭ�dp[i]�N�|�O2.��3.���[�`�A�Ydp[i]=dp[i-1]+dp[i-2]
    * ���F��֪Ŷ��A�[��W�z�|�o�{�u�ݭn���D�e�@��H�Ϋe��쪺�ѽX�覡
    * �åB�q��1��}�l�ѽX�A�]���Ĺs��u���@�ظѽX�覡�A�ӧڭ̹w�]�b�Ĺs��e���@�ӪšA�Ydp[-1]=dp[0]=1�A�p��dp[1]
    */
    if (s.empty() || s[0] == '0') return 0;
    if (s.length() == 1) return 1;

    std::function<bool(char&, char&)> isValid = [&](char& c1, char& c2) {return (c1 == '1') or (c1 == '2' and c2 < '7'); };

    const int n = s.length();
    int w1 = 1;
    int w2 = 1;
    for (int i = 1; i < n; ++i) {
        int w = 0;
        if ((s[i] == '0') && !isValid(s[i - 1], s[i])) return 0;
        if (s[i] != '0') w = w1;
        if (isValid(s[i - 1], s[i])) w += w2;
        w2 = w1;
        w1 = w;
    }
    return w1;
}

//19. Remove Nth Node From End of List
//��� runtime beats:62.15%  memory beats:32.26%
ListNode* removeNthFromEnd(ListNode* head, int n) {
    std::unordered_map<int, ListNode*> m;
    int i = 0;
    ListNode* node = head;
    while (node) {
        m[i] = node;
        node = node->next;
        i++;
    }

    node = m[i - n]; // remove node
    if (node == head) {
        head = head->next;
    }
    else {
        ListNode* pre = m[i - n - 1]; // previous node
        pre->next = node->next;
    }

    return head;
}

//https://leetcode.com/problems/remove-nth-node-from-end-of-list/discuss/1164542/JS-Python-Java-C++-or-Easy-Two-Pointer-Solution-w-Explanation
//���� runtime beats:78.73%  memory beats:75.00%
//ListNode* removeNthFromEnd(ListNode* head, int n) {
//    /*
//    * �H Fast, Slow �����AFast�|���]n��A�p�G��Fast��nullptr�ɡA�N��head�O�ڭ̭n�R�����ؼСA�ҥH�^��head->next
//    * ���U�ӦP�ɱ��i Fast �M Slow�A�� Fast ���U�@�쬰�ŮɡA�|�o�{ Slow ���b�ڭ̭n�R�����ؼЪ��e�@��A�Y Previous�A���ɱNSlow->next= slow->next->next�N�����R��
//    */
//    ListNode* fast = head, * slow = head;
//    for (int i = 0; i < n; i++) fast = fast->next;
//    if (!fast) return head->next;
//    while (fast->next) fast = fast->next, slow = slow->next;
//    slow->next = slow->next->next;
//    return head;
//}

//658. Find K Closest Elements
//��� runtime beats:11.60%  memory beats:37.52%
//std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
//    /*
//    * �Q�� Priority_queue�A�N�~�t�@��Priority�A�ҥH��PQ��size�W�LK�A�NPOP�̰�Priority���H(�Y�~�t�̦h���H)
//    */
//    int front_diff = x - arr.front();
//    int back_diff = x - arr.back();
//    if (front_diff < 0) return std::vector<int>(arr.begin(), arr.begin() + k);
//    if (back_diff > 0) return std::vector<int>(arr.end() - k, arr.end());
//
//    std::priority_queue<std::pair<int,int>> pq;
//    for(int i : arr){
//        pq.push({abs(i - x), i});
//        if(pq.size() > k)
//            pq.pop();
//    }
//    
//    std::vector<int> ans;
//    while(!pq.empty()){
//        ans.push_back(pq.top().second);
//        pq.pop();
//    }
//    std::sort(ans.begin(), ans.end());
//    return ans;
//}

//�G�� runtime beats:58.97%  memory beats:86.01%
std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
    /*
    * ���ˬd x �O�_�j��Τp�� arr ���Y�Χ��A�Y�ŦX�h�^�ǫek�Ϋ�k��
    * �b�ˬd arr �� size �O�_���� k�A�Y����h�^�� arr
    * ���ۥ��p��e k �쵴��~�t�X
    * ���U�ӴM��̤p����~�t�X(i~i+k���X)�o�ͪ���m i �A�ðO������~�t�X
    */
    int front_diff = x - arr.front();
    int back_diff = x - arr.back();
    if (front_diff < 0) return std::vector<int>(arr.begin(), arr.begin() + k);
    if (back_diff > 0) return std::vector<int>(arr.end() - k, arr.end());

    int size = arr.size();
    if (size == k) return arr;

    int i, sum = 0;
    for (i = 0; i < k; i++) sum += abs(arr[i] - x);

    int posi = 0, posi_sum = sum;
    for (i = k; i < size; i++) {
        sum = sum - abs(x - arr[i - k]) + abs(x - arr[i]);
        if (sum < posi_sum) { posi_sum = sum; posi = i - k + 1; }
    }
    return std::vector<int>(arr.begin() + posi, arr.begin() + posi + k);
}

//264. Ugly Number II
//https://leetcode.com/problems/ugly-number-ii/discuss/69364/My-16ms-C++-DP-solution-with-short-explanation
//���� runtime beats:74.47%  memory beats:66.75%
int nthUglyNumber(int n) {
    /*
    * �u�]�t��]�l2�B3�M5���ƺ٧@���(Ugly Number)�A�q�`��1���Ĥ@�����
    * �]�����j�h�Ƴ����O��ơA�ҥH�U�@����ƬO�|���x�s���Ҧ��w���Ʀr���H 2,3,5 ���̤p��
    */
    std::vector<int> dp(n + 1);
    dp[0] = 1;
    int t2 = 0, t3 = 0, t5 = 0; //pointers for 2, 3, 5
    for (int i = 1; i < n; i++) {
        dp[i] = std::min(dp[t2] * 2, std::min(dp[t3] * 3, dp[t5] * 5));
        if (dp[i] == (dp[t2] * 2)) t2++;
        if (dp[i] == (dp[t3] * 3)) t3++;
        if (dp[i] == (dp[t5] * 5)) t5++;
    }
    return dp[n-1];
}

//96. Unique Binary Search Trees
//��� runtime beats:37.60%  memory beats:12.02%
int numTrees(int n) {
    /*
    * https://en.wikipedia.org/wiki/Catalan_number
    *                      (2n)!        (n+1)(n+2)(n+3) ... (2n)
    * Catalan Number = ------------- = --------------------------
    *                    (n+1)!(n)!            (n+1)! 
    * ------------------------------------------------------------
    * ���j���Y�O C(0)=1; C(n+1)= (2(2n+1)/n + 2) * C(n)
    * https://leetcode.com/problems/unique-binary-search-trees/discuss/1565543/C++Python-5-Easy-Solutions-w-Explanation-or-Optimization-from-Brute-Force-to-DP-to-Catalan-O(N)
    * �ԲӸѲЩҦ��Ѫk�A�qBrute Force -> DP -> Catalan Number
    */
    std::vector<long long int> dp(n + 1, 1);
    for (int i = 0; i < n; i++) {
        dp[i + 1] = 2 * (2 * i + 1) * dp[i] / (i + 2);
    }
    return dp[n];
}

//218. The Skyline Problem
//https://zxi.mytechroad.com/blog/tree/leetcode-218-the-skyline-problem/
//���� runtime beats:71.60%  memory beats:77.75%
std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {
    /*
    * �Q�ΨC�ӥi�൪�׬��C�ɫؿv������ɧ@���̾ڡA�����ؿv�����_�l�I(����)�H�ε����I(�k��)
    * �b�_�l�I�����p�U�A�p�G�_�l�I��������̰����סA�h�N��S���ؿv���B�ר�Ӱ_�l�I�A�O����
    * �b�����I�����p�U�A�p�G�����I�O�̰����סA�h�ĤG�����I�����I����
    * �o�䶷�`�N�b�ۦP��m�����p�U�A�n���b�N�_�l�I�A�ҥH���_�l�I�����׬����A�����I�����׬��t�ñƧ�
    */
    typedef std::pair<int, int> Event; // Store start point with positive (x, h), end point with negative (y,-h)
    std::vector<Event> event_vec;
    for (const auto& b : buildings) {
        event_vec.emplace_back(b[0], b[2]);
        event_vec.emplace_back(b[1], -b[2]);
    }

    // Sort events by x, if x is same, sort by height to avoid special case
    // Ex : When two buildings are overlap in boundary, need check start point in second building before end point in first building
    std::sort(event_vec.begin(), event_vec.end(), [](const Event& e1, const Event& e2) {
        if (e1.first == e2.first) return e1.second > e2.second;
        return e1.first < e2.first;
    });

    std::vector<std::vector<int>> ans;
    std::multiset<int> buildings_height;
    std::function<int()> maxHeight = [&]() {
        if (buildings_height.empty()) return 0;
        return *buildings_height.rbegin();
    };

    /*
    * Process all the events, if is entering (height is positive), check h is biggest in history, if so, means it is answer because no building higher than this one.
    * if not entering, first erase the height in history, and check if h in history is second height(means now h > history h), h is ans.
    */ 
    for (const auto& e : event_vec) {
        int x = e.first;
        bool entering = e.second > 0;
        int h = abs(e.second);
        if (entering) {
            if (h > maxHeight()) ans.push_back({ x, h });
            buildings_height.insert(h);
        }
        else {
            buildings_height.erase(buildings_height.equal_range(h).first);
            if (h > maxHeight()) ans.push_back({ x, maxHeight() });
        }
    }
    return ans;
}

//Number of Common Factors
int commonFactors(int a, int b) {
    if (a > b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    int ans = 1; //1
    int max = 1000;
    for (int i = 2; i <= max; i++) {
        if (i > a) i = max + 1;
        if (a % i == 0 and b % i == 0)
            ans += 1;
    }
    return ans;
}

//Maximum Sum of an Hourglass
int maxSum(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int max = INT_MIN;
    for (int i = 0; i < m - 2; i++) {
        for (int j = 0; j < n - 2; j++) {
            grid[i][j] = grid[i][j] + grid[i][j + 1] + grid[i][j + 2] + grid[i + 1][j + 1] + grid[i + 2][j] + grid[i + 2][j + 1] + grid[i + 2][j + 2];
            max = std::max(max, grid[i][j]);
        }
    }
    return max;
}

//Minimize XOR
int minimizeXor(int num1, int num2) {
    // set bit ���b�G�i�줤�A���h�֦쬰 1�A1100��2�A0000��0
    std::bitset<32> bs1(num1);
    std::bitset<32> bs2(num2);
    int bs_diff = bs2.count() - bs1.count();
    int base = 1;
    int ans = num1;

    if (bs_diff > 0) { // �bnum1��¦�W��1
        while (bs_diff) {
            if ((num1 & base) == 0) {
                bs_diff--;
                ans += base;
            }
            base *= 2;
        }
    }
    else if (bs_diff < 0) { // �R��num1�̤pbs_diff��1
        while (bs_diff) {
            if (num1 & base) {
                bs_diff++;
                ans -= base;
            }
            base *= 2;
        }
    }
    return ans;
}

//Maximum Deletions on a String
int deleteString(std::string s) {
    int ans = 1;
    int compare_len = 1;
    while ((s != "") or ((compare_len * 2) > s.size())) {
        if (s.substr(0, compare_len) == s.substr(compare_len, compare_len)) {
            s = s.substr(compare_len);
            compare_len = 0;
            ans++;
        }
        compare_len++;
    }
    return ans;
}

//1155. Number of Dice Rolls With Target Sum
//https://youtu.be/J9s7402s5FA
//���� runtime beats:30.80%  memory beats:63.22%
int numRollsToTarget(int n, int k, int target) {
    /*
    * Time complexity : O(n*k*t)
    * Space comlexity : O(n*t)
    * �p�⦳i�ӻ�l���`�X��t���i��
    * �ҥH��������l�A�`�X��5�ɡA���p��l��1-3�A�ҥH�ڭ̰��]�ĤG����l��1�ɡA�Ĥ@����l����4�A�ӲĤ@����l��4���i��O0
    * �ĤG����l��2�ɡA�Ĥ@����l��3�A�i��ʬO1�A�H������
    */
    constexpr int kMod = 1e9 + 7;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(target + 1, 0)); // �O���bn�ӻ�l�ɡA�`�M�Ot���X�إi��
    dp[0][0] = 1; // �w�]0�ӻ�l�n�F��0���@�إi��
    for (int i = 1; i <= n; i++)            // i�ӻ�l
        for (int j = i; j <= target; j++) { // �`�M��j���i��
            if (j > (k * i)) continue;      // �Y�`�M�W�L��l��i*�̤j��k�A�N���i��o��
            for (int d = 1; d <= k; d++)    // �ҥH�n�[�`i-1�ӻ�l�`�X��j-d���i��
                if (d <= j)
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - d]) % kMod;
        }
    return dp[n][target];
}

//1578. Minimum Time to Make Rope Colorful
//��� runtime beats:56.65%  memory beats:84.72%
int minCost(std::string colors, std::vector<int>& neededTime) {
    const int n = colors.size();    
    int ans = 0;
    for (int i = 1; i < n; i++) {
        if (colors[i] == colors[i - 1]) {
            // ��Ӥ@�˪���y�A��ɶ���O�֪��A�åB�p�G��e��y��O�ɶ��֡A�h�N��e��O�ɶ��אּ�e�@��A�H�Q�U�@��Y�O�ۦP��y�ɤ��
            if (neededTime[i] > neededTime[i - 1])
                ans += neededTime[i - 1];
            else {
                ans += neededTime[i];
                neededTime[i] = neededTime[i - 1];
            }
        }
    }
    return ans;
}

//112. Path Sum
//��� runtime beats:77.40%  memory beats:38.76%
void hasPathSum_BFS(bool& ans, TreeNode* node, int target) {
    if (!node or ans) return;
    if (!node->left and !node->right and node->val == target) ans = true;
    else {
        hasPathSum_BFS(ans, node->left, target - node->val);
        hasPathSum_BFS(ans, node->right, target - node->val);
    }
}

bool hasPathSum(TreeNode* root, int targetSum) {
    bool ans = false;
    hasPathSum_BFS(ans, root, targetSum);
    return ans;
}

//118. Pascal's Triangle
//��� runtime beats:46.97%  memory beats:90.45%
std::vector<std::vector<int>> generate(int numRows) {
    /*
    * ���O�Ĥ@��A����for loop���ͨC�@��
    * �ӨC�@��q�Ĥ@��}�l��̫�ĤG��O�W�@��prev���P�@��m�H�Ϋe�@�Ӧ�m���M
    */
    std::vector<std::vector<int>> ans({ {1} });

    for (int i = 1; i < numRows; i++) {
        std::vector<int> now(i+1, 1);
        std::vector<int>& prev = ans.back();
        for (int j = 1; j < i; j++)
            now[j] = prev[j - 1] + prev[j];
        ans.push_back(now);
    }
    return ans;
}

//119. Pascal's Triangle II
//��� runtime beats:100.00%  memory beats:99.26%
std::vector<int> getRow(int rowIndex) {
    /*
    * ��n��|��n�ӭȡA�ҥH��l��vec�j�p��n�A�w�]�Ȭ�1
    * ��n > 2�ɡA�q�Ĥ@���̫�ĤG��|�ܤơA���L�o�ɭԦp�G�q�Y�}�l�A�|�л\���U�@��ݭn����
    * �ҥH�q��}�l
    */
    const int n = rowIndex + 1;
    std::vector<int> ans(n, 1);
    int i = 3;
    while (n > 2 and i <= n) {
        for (int j = i - 2; j >= 1; j--)
            ans[j] = ans[j - 1] + ans[j];
        i++;
    }
    return ans;
}

//931. Minimum Falling Path Sum
//��� runtime beats:30.09%  memory beats:95.79%
int minFallingPathSum(std::vector<std::vector<int>>& matrix) {
    /*
    * �M�ҩҦ���m
    * �b���O�Ĥ@��ɡA�Y��m���Ĥ@�ӡA�h��e��m�[min(�W,�k�W)
    * �Y��m�O�̫�@�ӡA�h��e��m�[min(���W,�W)
    * �_�h�N�O��e��m�[min(���W,�W,�k�W)
    * �b�̫�@��ɡA�p�⧹�Ӧ�m�̤p�M��n�P���פ���̤p��
    */
    int ans = INT_MAX;
    const int n = matrix.size();
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            for (int j = 0; j < n; j++) {
                if (j == 0)
                    matrix[i][j] = matrix[i][j] + std::min(matrix[i - 1][j], matrix[i - 1][j + 1]);
                else if (j == (n - 1))
                    matrix[i][j] = matrix[i][j] + std::min(matrix[i - 1][j - 1], matrix[i - 1][j]);
                else
                    matrix[i][j] = matrix[i][j] + std::min(std::min(matrix[i - 1][j - 1], matrix[i - 1][j]), matrix[i - 1][j + 1]);

                if (i == (n - 1))
                    ans = std::min(ans, matrix[i][j]);
            }
        }
    }
        
    return ans;
}

//120. Triangle
//��� runtime beats:84.35%  memory beats:79.01%
int minimumTotal(std::vector<std::vector<int>>& triangle) {
    /*
    * ���M�O�T���ΡA���L�Y�a������A�h�̤p���|�N�p931�D�ۦ��A�u�O�S���k�W
    * �M�ҩҦ���m
    * �b���O�Ĥ@��ɡA�Y��m���Ĥ@�ӡA�h��e��m�[min(�W)
    * �Y��m�O�̫�@�ӡA�h��e��m�[min(���W)
    * �_�h�N�O��e��m�[min(���W,�W)
    * �b�̫�@��ɡA�p�⧹�Ӧ�m�̤p�M��n�P���פ���̤p��
    */
    int ans = INT_MAX;
    const int rows = triangle.size();
    for (int i = 0; i < rows; i++)
        for (int j = 0; j <= i; j++) {
            if (i > 0) {
                if (j == 0)
                    triangle[i][j] = triangle[i][j] + triangle[i - 1][j];
                else if (j == i)
                    triangle[i][j] = triangle[i][j] + triangle[i - 1][j - 1];
                else
                    triangle[i][j] = triangle[i][j] + std::min(triangle[i - 1][j - 1], triangle[i - 1][j]);
            }

            if (i == (rows - 1))
                ans = std::min(ans, triangle[i][j]);
        }
    return ans;
}

//1314. Matrix Block Sum
//��� runtime beats:22.63% memory beats:72.73%
std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>>& mat, int k) {
    /*
    * ans�O���b(i,j)�I��block sum�A�ҥH(i+1,j)�u�ݭn��h(i,j)���̥���A�[�W(i+1,j)���̥k��Y�i
    * �P�z�A
    */
    const int m = mat.size();
    const int n = mat[0].size();
    std::vector<std::vector<int>> ans(m, std::vector<int>(n, 0));

    int r, c;
    for (r = 0; r <= k; r++)
        for (c = 0; c <= k; c++)
            if(r < m and c < n)
                ans[0][0] += mat[r][c];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (i != 0 or j != 0) {
                if (i == 0) {
                    ans[i][j] = ans[i][j - 1];
                    r = i - k >= 0 ? i - k : 0;
                    for (r; r <= i + k; r++) {
                        if (j - 1 - k >= 0)ans[i][j] -= mat[r][j - 1 - k];
                        if (j + k < n)ans[i][j] += mat[r][j + k];
                    }
                }
                else {
                    ans[i][j] = ans[i-1][j];
                    c = j - k >= 0 ? j - k : 0;
                    for (c; c <= j + k; c++) {
                        if (c < n) {
                            if (i - 1 - k >= 0)
                                ans[i][j] -= mat[i - 1 - k][c];
                            if (i + k < m)
                                ans[i][j] += mat[i + k][c];
                        }
                    }
                }
            }           
        }
    return ans;
}

//304. Range Sum Query 2D - Immutable
//��� runtime beats:29.29% memory beats:54.43%
class NumMatrix {
    /*
    * �O���q(0,0) �� (i,j) �� sum�A�ҥH�Y�n�p��(i1, j1)(i2,j2)�����n
    * �N�Osum(i2,j2) - sum(i1-1, j2) - sum(i2, j1-1) + sum(i1-1, j1-1)
    * �D���|��Υi�z�L�̤j�|��δ�h�W���|��ΩM����|��Υ[�W�h�Q��@�����̤p�|��αo�쵪��
    */
private:
    std::vector<std::vector<int>> matrix_sum; //�N��q(0,0) �� (i,j) �� sum
public:    
    NumMatrix(std::vector<std::vector<int>>& matrix) {
        matrix_sum.clear();
        const int m = matrix.size();
        const int n = matrix[0].size();
        matrix_sum.resize(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                matrix_sum[i + 1][j + 1] = matrix_sum[i][j + 1] + matrix_sum[i + 1][j] - matrix_sum[i][j] + matrix[i][j];
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        // matrix ������ matrix_sum ���ݭn����1�A�U��1
        return matrix_sum[row2 + 1][col2 + 1] - matrix_sum[row2 + 1][col1] - matrix_sum[row1][col2 + 1] + matrix_sum[row1][col1];
    }
};

//623. Add One Row to Tree
//��� runtime beats:29.29% memory beats:54.43%
void addOneRow_dfs(TreeNode* node, int& val, int depth) {
    if (!node or depth < 2) return;
    if (depth == 2) { // when node is father
        TreeNode* newleft = new TreeNode(val);
        if (node->left) newleft->left = node->left;
        node->left = newleft;
        TreeNode* newRight = new TreeNode(val);
        if (node->right) newRight->right = node->right;
        node->right = newRight;
    }
    else {
        addOneRow_dfs(node->left, val, depth - 1);
        addOneRow_dfs(node->right, val, depth - 1);
    }
}

TreeNode* addOneRow(TreeNode* root, int& val, int depth) {    
    /*
    * �ϥ�DFS�A������`�I(�Y��l�`�I���ܤ�)�ɡA�P�_���`�I�O�_�����k
    * �Y���A�s�إߪ����k�N���V���`�I�����k
    * �̫�H�s�إߪ����k���N�¦����`�I�����k
    */
    if (depth <= 1) {
        TreeNode* newNode = new TreeNode(val);
        newNode->left = root;
        return newNode;
    }
    else {
        addOneRow_dfs(root, val, depth);
        return root;
    }
}

//981. Time Based Key - Value Store
//https://www.cnblogs.com/grandyang/p/14195356.html
//���� runtime beats:27.65% memory beats:19.24%
class TimeMap {
    /*
    * �Q�� hash_map �ֳt�������x�s(timestamp, value)��map
    * �b map ���H upper_bound ��M��@�w�� timestamp �j�����СA�æ^�ǫ��Ъ��e�@��
    * ���ɭY map ���� timestamp �s�b�A�h�e�@��@�w�O map[timestamp]�A�Y���s�b�A�h�O�� timestamp �p��������
    * �ҥH���ɥu�ݭn�P�_���ЬO�_�� map ���}�Y�A�]���p�G�O�}�Y�A�N��S���H�� timestamp �p��ε���A�N�^�Ǫ�
    */
private:
    std::unordered_map< std::string, std::map<int, std::string>> hashmap; // store key -> timestamp, value
public:
    TimeMap() {
    }

    void set(std::string key, std::string value, int timestamp) {
        hashmap[key].insert({ timestamp, value });
    }

    std::string get(std::string key, int timestamp) {
        auto it = hashmap[key].upper_bound(timestamp);
        return it == hashmap[key].begin() ? "" : prev(it)->second;
    }
};

//729. My Calendar I
//https://leetcode.com/problems/my-calendar-i/discuss/109475/JavaC%2B%2B-Clean-Code-with-Explanation
//���� runtime beats:62.34% memory beats:31.30%
class MyCalendar {
    /*
    * �z�Lset�x�s�ƥ�A�å��ƦCstart�b�ƦCend�A�ҥH�b�j�Mlower bound(�@�˩Τj��)��
    * �p�G���@�Ӥ����̫�@�쪺�ƥ�A��}�l�p�󥻦��ƥ󪺵����ɡA�N�����ƥ󤤦��@�Өƥ�o��
    * �p�G���@�Ӥ����Ĥ@�쪺�ƥ�A��e�@��ƥ󪺵����j�󥻦��ƥ󪺶}�l�ɡA�N�����ƥ󪺶}�l�b�@�Өƥ�o��
    */
    std::set<std::pair<int, int>> books;
public:
    bool book(int s, int e) {
        auto next = books.lower_bound({ s, e }); // first element with key not go before k (i.e., either it is equivalent or goes after).
        if (next != books.end() && next->first < e) return false; // a existing book started within the new book (next)
        if (next != books.begin() && s < (--next)->second) return false; // new book started within a existing book (prev)
        books.insert({ s, e });
        return true;
    }
};

//732. My Calendar III
//https://zxi.mytechroad.com/blog/geometry/732-my-calendar-iii/
//���� runtime beats:27.65% memory beats:19.24%
class MyCalendarThree {
public:
    MyCalendarThree() {
        counts_[INT_MIN] = 0;
        counts_[INT_MAX] = 0;
        max_count_ = 0;
    }

    int book(int start, int end) {
        auto floor = std::prev(counts_.upper_bound(start));     // floor->first < start
        auto ceiling = counts_.lower_bound(end);                // ceiling->first >= end
        for (auto curr = floor, next = curr; curr != ceiling; curr = next) {
            ++next;
            if (next->first > end) counts_[end] = curr->second;
            if (curr->first <= start && next->first > start) max_count_ = std::max(max_count_, counts_[start] = curr->second + 1);
            else max_count_ = std::max(max_count_, ++curr->second);
        }
        return max_count_;
    }
private:
    std::map<int, int> counts_;
    int max_count_;
};

//16. 3Sum Closest
//��� runtime beats:92.81% memory beats:19.24%
int threeSumClosest(std::vector<int>& nums, int target) {
    /*
    * ���N nums �ɾ��ƧǡA�ôM��Ptarget�~�t�̤p������
    * �qnums���Ĥ@��(�̤p)�}�l�A�N�ĤG�ӼƷ�@�ĤG��(�ĤG�p)�A�̫�@�ӼƷ�@�ĤT��(�̤j)
    * �T�̬ۥ[��A�p�G����target�N�^�ǡA�p�G�j��target�N��ĤT��n���e(-)�A�p�G�p��target�N��ĤG��n����(+)
    * �C���첾���ˬd�Ptarget���t���A�̫�^�ǻPtarget�t���̤p��
    */
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int diff = INT_MAX;
    for (int i = 0; i < n; i++) {
        int low = i + 1;
        int high = n - 1;
        while (low < high) {
            int sum = nums[i] + nums[low] + nums[high];
            if (sum == target)
                return target;
            else if (sum < target)
                low++;
            else
                high--;
            if (abs(diff) > abs(target - sum))
                diff = target - sum;
        }
    }
    return target - diff;
}

//653. Two Sum IV - Input is a BST
//��� runtime beats:77.58% memory beats:37.86%
bool findTarget(TreeNode* root, int k) {
    std::set<int> exist;
    std::queue<TreeNode*> q({ root });

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
        if (exist.count(k - node->val)) return true;
        exist.insert(node->val);
    }

    return false;
}

//1328. Break a Palindrome
//https://leetcode.com/problems/break-a-palindrome/discuss/489774/JavaC++Python-Easy-and-Concise
//���� runtime beats:51.67% memory beats:95.35%
std::string breakPalindrome(std::string S) {
    /*
    * Check half of the string, replace a non 'a' character to 'a'.
    * If only one character, return empty string. Otherwise repalce the last character to 'b'
    * Time Complexity : O(N), Space Complexity : O(N)
    */
    int n = S.size();
    for (int i = 0; i < n / 2; ++i) {
        if (S[i] != 'a') {
            S[i] = 'a';
            return S;
        }
    }
    // All of S is a, so replace the last char of S to 'b'
    S[n - 1] = 'b';    
    return n < 2 ? "" : S;
}

//334. Increasing Triplet Subsequence
//https://leetcode.com/problems/increasing-triplet-subsequence/discuss/78993/Clean-and-short-with-comments-C++
//���� runtime beats:90.14% memory beats:24.04%
bool increasingTriplet(std::vector<int>& nums) {
    /*
    * ���� i �O��e�̤p�ȡA�Y��e�j�� i�A�N���i��O j or k
    * �Ӧp�G��e�]�j�� j�A�h�O j = ��e�A���� i < j
    * �̫�Y��e�����ëD�̤p�ȡA�]�D�ĤG�̤p�ȮɡA�^��true
    * ---------------------
    * ���]��i�Mj��ơA�w�]��INT_MAX�Ai�Mj���O�N��bincreasingTriplet���Ĥ@��H�βĤG��
    * ���ɱNnum����k(�ĤT��)�Ak�J��i,j���T�ر��p
    * Case 1 �Ok < i & k < j => �N�� k ���ӬO i (���ɤ��Χ�sj�A��]�O)
    * Case 2 �Ok > i & k < j => �N�� k ���ӬO j
    * Case 3 �Ok > i & k > j => �N���쵪��
    * 
    * ----------- i ---------- j -------------
    *      ��           ��             ��
    *     Case 1       Case 2        Case 3
    * 
    */
    int i = INT_MAX, j = INT_MAX;
    for (int& num : nums) {
        if (num <= i)
            i = num;           // i is min seen so far (it's a candidate for 1st element)
        else if (num <= j)     // here when num > i, i.e. num might be either j or k
            j = num;           // num is better than the current j, store it
        else                   // here when we have/had c1 < c2 already and x > c2
            return true;       // the increasing subsequence of 3 elements exists
    }
    return false;
}