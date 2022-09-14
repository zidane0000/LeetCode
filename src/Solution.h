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

//1. Two Sum
//初解 runtime beats:12.97% memory beats:89.01%
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    int a, b;
    std::vector<int> ans;
    for (int i = 0; i < nums.size(); i++) {
        a = nums.at(i);
        for (int j = i + 1; j < nums.size(); j++) {
            b = nums.at(j);
            if (a + b == target) {
                ans.push_back(i);
                ans.push_back(j);
                return ans;
            }
        }
    }
    return ans;
}

//二解 runtime beats:55.88% memory beats:42.01%
std::vector<int> twoSum_2(std::vector<int>& nums, int target) {
    std::map<int, int> a;
    std::map<int, int>::iterator a_itr;
    for (int i = 0; i < nums.size(); i++) {
        a_itr = a.find(target - nums.at(i));
        if (a_itr != a.end()) {
            return std::vector<int>{ a_itr->second, i };
        }
        else {
            a[nums.at(i)] = i;
        }
    }
    return std::vector<int>();
}

//三解 runtime beats:55.88% memory beats:42.01%
std::vector<int> twoSum_3(std::vector<int>& nums, int target) {
    std::map<int, int> a;
    for (int i = 0; i < nums.size(); i++) {
        if (a.find(target - nums.at(i)) != a.end()) {
            return std::vector<int>{ a[target - nums.at(i)], i };
        }
        else {
            a[nums.at(i)] = i;
        }
    }
    return std::vector<int>();
}

//2. Add Two Numbers
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}    
};
//初解 runtime beats:06.14% memory beats:07.45%
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* ans = nullptr;
    ListNode* cur = nullptr;
    int i = 0;
    while (l1 || l2) {
        if (l1) {
            i += l1->val;
            l1 = l1->next;
        }

        if (l2) {
            i += l2->val;
            l2 = l2->next;
        }

        if (ans) {
            ListNode* nw = new ListNode;
            nw->val = i % 10;
            i = i / 10;
            cur->next = nw;
            cur = cur->next;
        }
        else {
            ans = new ListNode;
            ans->val = i % 10;
            i = i / 10;
            cur = ans;
        }
    }

    if (i != 0) {
        ListNode* nw = new ListNode;
        nw->val = i;
        cur->next = nw;
        cur = cur->next;
    }
    return ans;
}

//二解 runtime beats:06.14% memory beats:19.45%
ListNode* addTwoNumbers_2(ListNode* l1, ListNode* l2) {
    ListNode* ans = nullptr;
    ListNode* cur = nullptr;
    short i = 0;
    while (l1 || l2) {
        if (l1) {
            i += l1->val;
            l1 = l1->next;
        }

        if (l2) {
            i += l2->val;
            l2 = l2->next;
        }

        if (ans) {
            ListNode* nw = new ListNode;
            nw->val = i % 10;
            i = i / 10;
            cur->next = nw;
            cur = cur->next;
        }
        else {
            ans = new ListNode;
            ans->val = i % 10;
            i = i / 10;
            cur = ans;
        }
    }

    if (i != 0) {
        ListNode* nw = new ListNode;
        nw->val = i;
        cur->next = nw;
        cur = cur->next;
    }
    return ans;
}

//三解 runtime beats:84.20% memory beats:55.78%
ListNode* addTwoNumbers_3(ListNode* l1, ListNode* l2) {
    ListNode* ans = new ListNode;
    ListNode* cur = ans;
    short i = 0;
    while (l1 || l2) {
        if (l1) {
            i += l1->val;
            l1 = l1->next;
        }

        if (l2) {
            i += l2->val;
            l2 = l2->next;
        }

        cur->val = i % 10;
        i = i / 10;
        if (l1 || l2) {
            cur->next = new ListNode;
            cur = cur->next;
        }
    }

    if (i != 0) {
        ListNode* nw = new ListNode;
        nw->val = i;
        cur->next = nw;
        cur = cur->next;
    }
    return ans;
}

//網解 runtime beats:17.38% memory beats:35.43%
ListNode* addTwoNumbers_network(ListNode* l1, ListNode* l2) {
    ListNode* walk_1 = l1;
    ListNode* walk_2 = l2;
    ListNode* answer = new ListNode();
    ListNode* root = answer;
    auto v1 = 0;
    auto v2 = 0;
    auto carry = 0;
    auto sum = 0;

    while (walk_1->next || walk_2->next) {
        v1 = walk_1->val;
        v2 = walk_2->val;
        sum = v1 + v2 + carry;
        carry = 0;
        if ((carry = (sum > 9))) sum -= 10;
        answer->val = sum;
        answer->next = new ListNode();
        answer = answer->next;
        if (walk_1->next) walk_1 = walk_1->next;
        else walk_1->val = 0;
        if (walk_2->next) walk_2 = walk_2->next;
        else walk_2->val = 0;
    }
    v1 = walk_1->val;
    v2 = walk_2->val;
    sum = v1 + v2 + carry;
    carry = 0;
    if ((carry = (sum > 9))) sum -= 10;
    answer->val = sum;
    if (carry) answer->next = new ListNode(carry);

    return root;
}

//3. Longest Substring Without Repeating Characters 
//初解 runtime beats:98.72% memory beats:83.53%
int lengthOfLongestSubstring(std::string s) {
    int max_len = 0;
    int len = 0;
    int str = 0;
    for (int i = 0; i < s.size(); i++) {
        //從str位置往後找s[i]，若找到的位置大於i-1代表說，過往沒有重複，substring長度加一
        if ((int)s.find(s[i], str) > (i-1))
            len++;
        else {
            max_len = max_len > len ? max_len : len;
            //substring長度是
            len = i - (int)s.find(s[i], str);
            //substring從上一個重複char的位置+1開始
            str = (int)s.find(s[i], str)+1;
        }            
    }

    max_len = max_len > len ? max_len : len;

    return max_len;
}

//4. Median of Two Sorted Arrays
//初解 runtime beats:89.56% memory beats:17.58%
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    auto tar_posi = (nums1.size() + nums2.size()) / 2 + 1;    //多塞一個
    auto tar_posi_tmp = tar_posi;
    std::vector<int*> tmp;
    int nums1_posi = 0, nums2_posi = 0;
    while (tar_posi_tmp--) {
        if (nums1_posi >= nums1.size())
        {
            tmp.push_back(&nums2[nums2_posi]);
                nums2_posi++;
        }
        else if (nums2_posi >= nums2.size()) {
            tmp.push_back(&nums1[nums1_posi]);
                nums1_posi++;
        }
        else {
            if (nums1[nums1_posi] < nums2[nums2_posi]) {
                tmp.push_back(&nums1[nums1_posi]);
                    nums1_posi++;
            }
            else {
                tmp.push_back(&nums2[nums2_posi]);
                    nums2_posi++;
            }
        }
    }

    if ((nums1.size() + nums2.size()) % 2)
        return (double)(*tmp[tar_posi - 1]);
    else
        return ((double)(*tmp[tar_posi - 2]) + (double)(*tmp[tar_posi - 1])) / 2;
}

//二解 runtime beats:09.40% memory beats:31.19%
double findMedianSortedArrays_2(std::vector<int>& nums1, std::vector<int>& nums2) {
    auto tar_posi = ((float)nums1.size() + nums2.size()) / 2;
    short tmp_size = tar_posi + 1;                       //多塞一個
    std::vector<int> tmp;
    while (tmp_size--) {
        if (nums1.size() == 0)
        {
            tmp.push_back(nums2.front());
            nums2.erase(nums2.begin());
        }
        else if (nums2.size() == 0) {
            tmp.push_back(nums1.front());
            nums1.erase(nums1.begin());
        }
        else {
            if (nums1.front() < nums2.front()) {
                tmp.push_back(nums1.front());
                nums1.erase(nums1.begin());
            }
            else {
                tmp.push_back((nums2.front()));
                nums2.erase(nums2.begin());
            }
        }
    }

    if (tar_posi - (short)tar_posi)
        return (double)(tmp[tar_posi]);
    else
        return ((double)(tmp[tar_posi - 1]) + (double)(tmp[tar_posi])) / 2;
}

//網解 runtime beats:95.44% memory beats:89.75%
double findMedianSortedArrays_network(std::vector<int>& nums1, std::vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size(), total = n1 + n2;
    if (n1 > n2) return findMedianSortedArrays(nums2, nums1);

    int i = 0, j = n1;
    while (i <= j)
    {
        int left1 = i + (j - i) / 2;
        int left2 = total / 2 + (total % 2 == 1 ? 1 : 0) - left1;

        int max1 = left1 - 1 >= 0 ? nums1[left1 - 1] : INT_MIN, max2 = left2 - 1 >= 0 ? nums2[left2 - 1] : INT_MIN;
        int min1 = left1 < n1 ? nums1[left1] : INT_MAX, min2 = left2 < n2 ? nums2[left2] : INT_MAX;

        if (max1 <= min2 && max2 <= min1)
            return total % 2 == 0 ? (std::max(max1, max2) + std::min(min1, min2)) / 2 : std::max(max1, max2);
        else if (max1 > min2)
            j = left1 - 1;
        else i = left1 + 1;
    }
    return -1;

}

//5. Longest Palindromic Substring
//參考網址：https://www.cnblogs.com/grandyang/p/4464476.html
//網解 runtime beats:90.65% memory beats:61.59%
//Manacher's Algorithm
std::string longestPalindrome_network(std::string s) {
    std::string t = "&#";
    for (int i = 0; i < s.size(); ++i) {
        t += s[i];
        t += '#';
    }
    std::vector<int> p = std::vector<int>(t.size(), 0);

    int id = 0, mx = 0, resId = 0, resMx = 0;
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? std::min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (resMx < p[i]) {
            resMx = p[i];
            resId = i;
        }
    }
    return s.substr((resId - resMx) / 2, resMx - 1);
}

//9. Palindrome Number
//初解 runtime beats:92.39% memory beats:63.63%
bool isPalindrome(int x) {
    std::string x_s = std::to_string(x);

    for (int i = 0; i < (x_s.size() / 2); i++) {
        if (x_s[i] != x_s[x_s.size() - 1 - i])
            return false;
    }
    return true;
}

//二解 runtime beats:92.39% memory beats:63.63%
bool isPalindrome_2(int x) {
    if (x < 0) return false;
    std::string x_s = std::to_string(x);

    for (int i = 0; i < (x_s.size() / 2); i++) {
        if (x_s[i] != x_s[x_s.size() - 1 - i])
            return false;
    }
    return true;
}

//10. Regular Expression Matching
//https://knightzone.studio/2018/09/30/3644/leetcode%EF%BC%9A10-regular-expression-matching/
//網解 runtime beats:58.66% memory beats:42.67%
bool isMatch(std::string s, std::string p) {
    std::vector<std::vector<bool>> dp(s.length() + 1, std::vector<bool>(p.length() + 1, false));

    /* Empty String */
    dp[0][0] = true;

    /* "" v.s. X*X*X*..... */
    for (int i = 2; i <= p.length() && p[i - 1] == '*'; i += 2) {
        dp[0][i] = true;
    }

    /* s[0...i-1] v.s. p[0...j-1] */
    for (int i = 1; i <= s.length(); ++i) {
        for (int j = 1; j <= p.length(); ++j) {
            int sIndex = i - 1;
            int pIndex = j - 1;

            if (p[pIndex] == '.' || s[sIndex] == p[pIndex]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if (p[pIndex] == '*') {
                dp[i][j] = dp[i][j - 2] || ((s[sIndex] == p[pIndex - 1] || p[pIndex - 1] == '.') && dp[i - 1][j]);
            }
        }
    }

    return dp[s.length()][p.length()];
}

//11. Container With Most Water
//初解 runtime beats:90.66% memory beats:41.36%
int maxArea(std::vector<int>& height) {
    if (height.size() == 2) {
        return height[0] < height[1] ? height[0] : height[1];
    }

    int l = 0, r = height.size() - 1;
    int max_area = 0;
    while (l < r) {
        int tmp = (height[l] < height[r] ? height[l] : height[r]) * (r - l);
        if (tmp > max_area)
            max_area = tmp;

        if (height[l] < height[r])
            l++;
        else
            r--;
    }
    return max_area;
}

//二解 runtime beats:16.97% memory beats:87.56%
int maxArea_2(std::vector<int> & height) {
    if (height.size() == 2) {
        return height[0] < height[1] ? height[0] : height[1];
    }

    int l = 0, r = height.size() - 1;
    int max_area = 0;
    while (l < r) {
        max_area = 
            (height[l] < height[r] ? height[l] : height[r]) * (r - l) > max_area ? (height[l] < height[r] ? 
                height[l] : height[r]) * (r - l) : max_area;
        
        if (height[l] < height[r])
            l++;
        else
            r--;
    }
    return max_area;
}

//14. Longest Common Prefix
//初解 runtime beats:74.28% memory beats:62.31%
std::string longestCommonPrefix(std::vector<std::string>& strs) {
    int strs_size = strs.size();
    if (strs_size == 0)
        return "";
    
    int posi = 0;
    for (posi = 0; posi < strs[0].size(); posi++) {
        for (int j = 0; j < strs_size - 1; j++) {
            if (strs[j][posi] != strs[j + 1][posi])
                return strs[j].substr(0, posi);
        }
    }
    
    return strs[0].substr(0, posi);
}

//15. 3Sum
//網解 runtime beats:35.80% memory beats:99.73%
std::vector<std::vector<int>> threeSum_network(std::vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    std::vector<std::vector<int> > ans;
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            while (i < n && nums[i] == nums[i - 1])
                i++;

            if (i == n)
                break;
        }

        int l = i + 1, r = n - 1;
        int val = nums[i];

        while (l < r) {
            if (val + nums[l] + nums[r] == 0) {
                ans.push_back({ val,nums[l],nums[r] });
                r--, l++;
            }
            else if (val + nums[l] + nums[r] < 0)
                l++;
            else
                r--;

            if (l > i + 1)
                while (l < n && nums[l] == nums[l - 1])
                    l++;

            if (r < n - 1)
                while (r > 0 && nums[r] == nums[r + 1])
                    r--;
        }
    }

    return ans;
}

//網解 runtime beats:90.94% memory beats:75.02%
std::vector<std::vector<int>> threeSum_network_2(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++) {
        int curr = nums[i];
        int target = -curr;
        int front = i + 1;
        int end = n - 1;
        while (front < end) {
            int sum = nums[front] + nums[end];
            if (sum == target) {
                res.push_back({ curr,nums[front],nums[end] });
                int temp1 = nums[front];
                int temp2 = nums[end];
                while (front < end && nums[front] == temp1)
                    front++;
                while (front < end && nums[end] == temp2)
                    end--;
            }
            else if (sum < target) { front++; }
            else { end--; }
        }
        while (i + 1 < n && nums[i + 1] == curr)
            i++;
    }
    return res;
}

//https://www.cnblogs.com/grandyang/p/4481576.html
//網解 runtime beats:93.07% memory beats:78.92%
std::vector<std::vector<int>> threeSum_network_3(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    sort(nums.begin(), nums.end());
    if (nums.empty() || nums.back() < 0 || nums.front() > 0) return {};
    for (int k = 0; k < (int)nums.size() - 2; ++k) {
        if (nums[k] > 0) break;
        if (k > 0 && nums[k] == nums[k - 1]) continue;
        int target = 0 - nums[k], i = k + 1, j = (int)nums.size() - 1;
        while (i < j) {
            if (nums[i] + nums[j] == target) {
                res.push_back({ nums[k], nums[i], nums[j] });
                while (i < j && nums[i] == nums[i + 1]) ++i;
                while (i < j && nums[j] == nums[j - 1]) --j;
                ++i; --j;
            }
            else if (nums[i] + nums[j] < target) ++i;
            else --j;
        }
    }
    return res;
}

//16. 3Sum Closest
//初解 runtime beats:8.01% memory beats:89.32%
int threeSumClosest(std::vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int size = nums.size();
    int ans = INT_MAX;
    for (int k = 0; k < size - 2; k++) {
        if (k > 0 && nums[k] == nums[k - 1]) continue;
        int dif = target - nums[k], i = k + 1, j = size - 1;        
        for (int i = k + 1; i < size - 1; i++)
            for (int j = size - 1; j > i; j--) {
                int tmp = dif - nums[i] - nums[j];
                if (abs(tmp) < abs(ans))
                    if (tmp == 0)
                        return target;
                    else
                        ans = tmp;
            }
    }
    return target - ans;
}

//網解 runtime beats:93.31% memory beats:19.81%
int threeSumClosest_network(std::vector<int>& nums, int target) {
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

//17. Letter Combinations of a Phone Number
//初解 runtime beats:100.00% memory beats:81.11%
std::vector<std::string> letterCombinations(std::string digits) {
    //'a':97 , '2':50
    std::vector<std::string> ans;
    if (digits.size() == 0)
        return ans;
    ans.push_back("");
    for (auto num : digits)
    {
        int ans_size = ans.size();
        for (int i = 0; i < ans_size; i++) {
            std::string tmp = ans.front();
            if (num == '7') {
                ans.push_back(tmp + (char)(112));
                ans.push_back(tmp + (char)(113));
                ans.push_back(tmp + (char)(114));
                ans.push_back(tmp + (char)(115));
            }
            else if (num == '8') {
                ans.push_back(tmp + (char)(116));
                ans.push_back(tmp + (char)(117));
                ans.push_back(tmp + (char)(118));
            }
            else if (num == '9') {
                ans.push_back(tmp + (char)(119));
                ans.push_back(tmp + (char)(120));
                ans.push_back(tmp + (char)(121));
                ans.push_back(tmp + (char)(122));
            }
            else {
                ans.push_back(tmp + (char)(97 + (((short)(num)) - 50) * 3));
                ans.push_back(tmp + (char)(98 + (((short)(num)) - 50) * 3));
                ans.push_back(tmp + (char)(99 + (((short)(num)) - 50) * 3));
            }
            ans.erase(ans.begin());
        }
    }

    return ans;
}

//19. Remove Nth Node From End of List
//初解 runtime beats:80.29% memory beats:05.19%
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if ((n == 1) && (head->next == NULL))
        return NULL;

    std::vector<ListNode*> l;
    ListNode* cur = head;
    while (cur) {
        l.push_back(cur);
        cur = cur->next;
    }

    if (n == l.size())
        return l[1];
    else
        l[l.size() - 1 - n]->next = l[l.size() - 1 - n]->next->next;
    return head;
}

//二解 runtime beats:21.49% memory beats:90.55%
ListNode* removeNthFromEnd_2(ListNode* head, int n) {
    if ((n == 1) && (head->next == NULL))
        return NULL;

    n--;
    ListNode* before = head;
    ListNode* target = head;
    ListNode* current = head;

    while (current) {
        if (n-- < 0) {
            before = target;
            target = target->next;
        }
        current = current->next;
    }

    if (before == target) {
        if ((before != NULL) && (before->next != NULL))
            return before->next;
        else
            return NULL;
    }
    else {
        if (before->next != NULL)
            before->next = before->next->next;
    }

    return head;
}

//20. Valid Parentheses
//初解 runtime beats:30.31% memory beats:51.04%
bool isValid(std::string s) {
    std::vector<char> s_splt;

    for (auto c_s : s) {
        if (c_s == '(' || c_s == '{' || c_s == '[')
            s_splt.push_back(c_s);
        else {
            if (c_s == ')') {
                if (s_splt.size() < 1)
                    return false;

                if (s_splt[s_splt.size() - 1] != '(')
                    return false;
                else
                    s_splt.pop_back();
            }
            else if (c_s == '}') {
                if (s_splt.size() < 1)
                    return false;

                if (s_splt[s_splt.size() - 1] != '{')
                    return false;
                else
                    s_splt.pop_back();
            }
            else if (c_s == ']') {
                if (s_splt.size() < 1)
                    return false;

                if (s_splt[s_splt.size() - 1] != '[')
                    return false;
                else
                    s_splt.pop_back();
            }
        }
    }

    if (s_splt.size() != 0)
        return false;
    else
        return true;
}

//網解 runtime beats:30.31% memory beats:95.93%
bool isValid_network(std::string s)
{
    bool val = false;
    int keycount = 0;
    if (s.size() == 0)
        return true;
    else if ((s.size() % 2 != 0) && (s.size() != 0))
        return val;
    else
    {
        std::map<char, char> mp;
        mp['}'] = '{';
        mp[')'] = '(';
        mp[']'] = '[';

        for (unsigned int i = 0; i < s.size(); i++) {
            auto it = mp.find(s[i]);
            if (it != mp.end()) {
                for (int j = 0; j < i; j++) {
                    if ((mp[s[i]] == s[j]) && ((i - j) % 2 != 0)) {
                        s[i] = ' ';
                        s[j] = ' ';
                        keycount--;
                        if ((keycount == 0) && (s.size() - i == 1)) {
                            val = true;
                            break;
                        }
                    }
                }
            }
            else
                keycount++;
        }
    }
    return val;
}

//21. Merge Two Sorted Lists
//初解 runtime beats:29.53% memory beats:76.65%
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == NULL && l2 == NULL)
        return NULL;
    else if (l1 == NULL)
        return l2;
    else if (l2 == NULL)
        return l1;

    ListNode* m;
    if (l1->val < l2->val) {
        m = l1;
        l1 = l1->next;
    }
    else {
        m = l2;
        l2 = l2->next;
    }

    ListNode* cur = m;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            cur->next = l1;
            cur = cur->next;
            l1 = l1->next;
        }
        else {
            cur->next = l2;
            cur = cur->next;
            l2 = l2->next;
        }
    }

    while (l1) {
        cur->next = l1;
        cur = cur->next;
        l1 = l1->next;
    }

    while (l2) {
        cur->next = l2;
        cur = cur->next;
        l2 = l2->next;
    }

    return m;
}

//二解 runtime beats:29.53% memory beats:94.64%
ListNode* mergeTwoLists_2(ListNode* l1, ListNode* l2) {
    if (l1 == NULL && l2 == NULL)
        return NULL;
    else if (l1 == NULL)
        return l2;
    else if (l2 == NULL)
        return l1;

    if (l1->val > l2->val)
        return mergeTwoLists_2(l2, l1);

    ListNode* l1_p = l1;
    ListNode* l2_p = l2;
    while (l2_p) {
        if (l1_p->next == NULL) {
            l1_p->next = l2_p;
            return l1;
        }
        else if (l1_p->next->val > l2_p->val) {
            ListNode* tmp = l2_p;
            l2_p = l2_p->next;
            tmp->next = l1_p->next;
            l1_p->next = tmp;
        }
        else {
            l1_p = l1_p->next;
        }            
    }

    return l1;
}

//22. Generate Parentheses
//初解 runtime beats:07.94% memory beats:88.57%
void ParenthesisChange(std::map<std::string, int>& m ,std::string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ')') {
            std::string tmp = s;

            int r = tmp.find('(', i);
            if (r != -1) {
                tmp[r] = ')';
                tmp[i] = '(';

                if (m[tmp] != 1) {
                    m[tmp] = 1;

                    ParenthesisChange(m, tmp);                    
                }
            }
            else
                i = s.length();            
        }
    }
}

std::vector<std::string> generateParenthesis(int n) {
    if (n < 0)
        return std::vector<std::string>();

    std::vector<std::string> ans;
    std::string s = "";
    while (n--) {
        s += "()";
    }

    std::map<std::string, int> m;
    ParenthesisChange(m, s);
    m[s] = 1;
    std::map<std::string, int>::iterator m_itr;
    for (m_itr = m.begin(); m_itr != m.end(); m_itr++)
        if (m_itr->second == 1)
            ans.push_back(m_itr->first);

    return ans;
}

//網解 runtime beats:49.63% memory beats:26.09%
void dfs(std::vector<std::string>& res, std::string s, int left, int right) {
    if (left == 0 && right == 0) {
        res.push_back(s);
    }
    if (left > 0) { dfs(res, s + '(', left - 1, right); }
    if (right > left) { dfs(res, s + ')', left, right - 1); }
}

std::vector<std::string> generateParenthesis_network(int n) {
    if (n == 0) { return {}; }
    std::vector<std::string> res;
    dfs(res, "", n, n);
    return res;
}

//網解 runtime beats:87.16% memory beats:98.54%
std::vector<std::string> generateParenthesis_network_2(int n) {
    std::string p = "";
    for (int i = 0; i < n; i++) p += '(';
    for (int i = 0; i < n; i++) p += ')';

    std::vector<std::string> wellFormed;

    do {
        int level = 0;
        bool valid = true;
        for (int i = 0; i < n * 2; i++) {
            if (p[i] == '(') {
                level++;
            }
            else {
                level--;
                if (level < 0) {
                    valid = false;
                    break;
                }
            }
        }
        valid = valid && level == 0;

        if (valid) {
            wellFormed.push_back(p);
        }
    } while (next_permutation(p.begin(), p.end())); //next_permutation:生成n個數的全排列

    return wellFormed;
}

//23. Merge k Sorted Lists
//初解 runtime beats:23.65% memory beats:74.41%
ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.size() == 0)
        return NULL;
    else if (lists.size() == 1)
        return lists[0];

    ListNode* m = lists[0];

    for (int i = 1; i < lists.size(); i++) {
        m = mergeTwoLists_2(m,lists[i]);
    }

    return m;
}

//網解 runtime beats:75.68% memory beats:44.58%
ListNode* merge(ListNode* l, ListNode* r) {
    ListNode* dummy = new ListNode(0);
    ListNode* head = dummy;
    while (l && r) {
        if (l->val < r->val) {
            dummy->next = l;
            dummy = dummy->next;
            l = l->next;
        }
        else {
            dummy->next = r;
            dummy = dummy->next;
            r = r->next;
        }
    }
    if (l) {
        dummy->next = l;
    }
    if (r) {
        dummy->next = r;
    }
    return head->next;
}

ListNode* mergeKLists_network(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    int n = lists.size();

    while (n != 1) {
        for (int i = 0; i < n / 2; i++) {
            int k = (n + 1) / 2;
            lists[i] = merge(lists[i], lists[i + k]);
        }
        n = (n + 1) / 2;
    }
    return lists[0];
}

//24. Swap Nodes in Pairs
//初解 runtime beats:100.00% memory beats:73.69%
ListNode* swapPairs(ListNode* head) {
    if (head == NULL)
        return NULL;

    ListNode* f = new ListNode;
    f->next = head;
    ListNode* s = head;
    ListNode* t = s->next;
    if (t == NULL)
        return s;

    ListNode* new_head = t;
    while ((f != NULL) && (s != NULL) && (t != NULL)) {
        s->next = t->next;
        t->next = s;
        f->next = t;
        
        f = s;
        s = f->next;
        if (s == NULL)
            t = NULL;
        else
            t = s->next;
    }

    return new_head;
}

//二解 runtime beats:54.37% memory beats:61.37%
ListNode* swapPairs_2(ListNode* head) {
    if (head == NULL)
        return NULL;

    ListNode* f = NULL;
    ListNode* s = head;
    ListNode* t = s->next;
    if (t == NULL)
        return s;

    ListNode* new_head = t;
    while ((s != NULL) && (t != NULL)) {
        s->next = t->next;
        t->next = s;
        if(f)
            f->next = t;

        f = s;
        s = f->next;
        if (s == NULL)
            t = NULL;
        else
            t = s->next;
    }

    return new_head;
}

//25. Reverse Nodes in k-Group
//初解 runtime beats:16.58% memory beats:12.35%
ListNode* reverseKGroup(ListNode* head, int k) {
    if (head == NULL)
        return NULL;

    ListNode* cur = head;
    ListNode* new_head;
    int i = 1;
    while (i < k) {
        if (cur != NULL) {
            cur = cur->next;
            i++;
        }
        else
            return head;
    }

    if (cur == NULL)
        return head;

    new_head = cur;
    cur = head;
    ListNode* old_end = NULL;
    std::vector<ListNode*> list;
    while (cur) {

        i = 0;
        list.clear();
        while (i < k) {
            if (cur != NULL) {
                list.push_back(cur);
                cur = cur->next;
                i++;
            }
            else
                i = k;
        }

        if (list.size() == k) {
            list[0]->next = list[k - 1]->next;
            for (i = 0; i < k - 1; i++) {
                list[k - i - 1]->next = list[k - i - 2];
            }

            if (old_end)
                old_end->next = list[k - 1];

            old_end = list[0];
        }
    }

    return new_head;
}

//網解 runtime beats:76.96% memory beats:97.95%
ListNode* reverseList(ListNode* head, int k)
{
    ListNode* pre = NULL;
    ListNode* cur = head;
    while (k > 0)
    {
        ListNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
        --k;
    }

    return pre;
}

ListNode* reverseKGroup_network(ListNode* head, int k) {
    int count = 0;
    ListNode* runner = head;
    while (count < k && runner)
    {
        runner = runner->next;
        count++;
    }

    if (count == k)
    {
        ListNode* head1 = reverseList(head, k);
        head->next = reverseKGroup_network(runner, k);
        return head1;
    }
    return head;
}

//31. Next Permutation
//題目意思：給一個數字，請給下一個比該數字大但最接近的數字，且兩數字使用之數字一樣，例如給'123'，最接近'123'且用'1','2','3'組成的數字為'132'
//初解 runtime beats:58.26% memory beats:82.06%
void nextPermutation(std::vector<int>& nums) {
    
    int nums_size = nums.size();
    int p1 = nums_size - 2;
    bool keepGo = true;
    while (p1 > -1 && keepGo) {
        if (nums[p1 + 1] > nums[p1]) {  //升冪
            int p2_record = p1 + 1;
            int p2_minus = INT_MAX;
            for (int p2 = p1 + 1; p2 < nums_size; p2++) {
                if (p2_minus >= (nums[p2] - nums[p1]) && ((nums[p2] - nums[p1]) > 0)) {
                    p2_minus = nums[p2] - nums[p1];
                    p2_record = p2;
                }
            }

            int tmp = nums[p2_record];
            nums[p2_record] = nums[p1];
            nums[p1] = tmp;

            keepGo = false;
        }
        else
            p1--;
    }

    for (int i = 1; i <= (nums_size - p1 - 1) / 2; i++) {
        int tmp = nums[nums_size - i];
        nums[nums_size - i] = nums[p1 + i];
        nums[p1 + i] = tmp;
    }
}

//網解 runtime beats:92.81% memory beats:50.25%
void nextPermutation_network(std::vector<int>& nums) {
    std::next_permutation(nums.begin(), nums.end());
}

//32. Longest Valid Parentheses
//網解 runtime beats:87.24% memory beats:79.15%
int longestValidParentheses_network(std::string s) {
    int res = 0, start = 0, n = s.size();
    std::stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') st.push(i);
        else if (s[i] == ')') {
            if (st.empty()) start = i + 1;
            else {
                st.pop();
                res = st.empty() ? std::max(res, i - start + 1) : std::max(res, i - st.top());
            }
        }
    }
    return res;
}

//初解 runtime beats:08.75% memory beats:53.26%
int longestValidParentheses(std::string s) {
    int res = 0, start = 0, n = s.size();
    std::vector<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') st.push_back(i);
        else if (s[i] == ')') {
            if (st.empty()) start = i + 1;
            else {
                st.pop_back();
                res = st.empty() ? std::max(res, i - start + 1) : std::max(res, i - st.back());
            }
        }
    }
    return res;
}

//33. Search in Rotated Sorted Array
//初解 runtime beats:65.96% memory beats:75.43%
int search(std::vector<int>& nums, int target) {
    int nums_size = nums.size();
    for (int i = 0; i < nums_size; i++) {
        if (nums[i] == target)
            return i;
    }
    return -1;
}

//二解 runtime beats:65.96% memory beats:66.92%
int search_2(std::vector<int>& nums, int target) {
    int i = 0;
    std::vector<int>::iterator nums_itr = nums.begin();
    while (nums_itr != nums.end()) {
        if (*nums_itr == target)
            return i;
        nums_itr++;
        i++;
    }

    return -1;
}

//三解 runtime beats:65.96% memory beats:51.38%
int search_3(std::vector<int>& nums, int target) {
    int nums_size = nums.size();
    int i = 0;
    for (i = 0; i < nums_size; i++) {
        if (nums[i] > target)
            i = nums_size;
        else if(nums[i] == target)
            return i;
    }

    for (i = nums_size-1; i >= 0; i--) {
        if (nums[i] < target)
            i = 0;
        else if (nums[i] == target)
            return i;
    }

    return -1;
}

//網解 runtime beats:96.62% memory beats:97.67%
int search_network(std::vector<int>& nums, int target) {
    int pivotindex;
    int low, high, mid;
    int n = nums.size();
    if (n == 0) return -1;
    if (nums[0] < nums[n - 1])
        pivotindex = 0;
    else
    {
        low = 0; high = n - 1;
        while (low < high) {
            mid = low + (high - low) / 2;
            if (nums[mid] < nums[0])high = mid;
            else
                low = mid + 1;
        }
        pivotindex = low;
    }

    if (target == nums[pivotindex])
        return pivotindex;

    if (pivotindex == 0) {
        low = 0;
        high = n - 1;
    }
    else if (target < nums[0]) {
        low = pivotindex;
        high = n - 1;
    }
    else if (target > nums[0]) {
        low = 0;
        high = pivotindex - 1;
    }
    else if (target == nums[0])
        return 0;

    while (low < high) {
        mid = low + (high - low + 1) / 2;
        if (nums[mid] > target)
            high = mid - 1;
        else
            low = mid;
    }
    if (nums[low] == target)
        return low;
    else
        return -1;
}

//34. Find First and Last Position of Element in Sorted Array
//初解 runtime beats:58.74% memory beats:55.39%
std::vector<int> searchRange(std::vector<int>& nums, int target) {
    int nums_size = nums.size();
    if(nums_size == 0)
        return { -1,-1 };
        
    int left = 0, right = nums_size - 1;

    while (left < right) {
        int mid = left + (right - left + 1) / 2;
        if (nums[mid] > target)
            right = mid - 1;
        else
            left = mid;
    }
    
    if (nums[left] != target)
        return { -1,-1 };

    while ((left - 1 >= 0) && nums[left - 1] == target) {
        left--;
    }

    while ((right + 1) < nums_size && nums[right + 1] == target) {
        right++;
    }

    return { left,right };
}

//二解 runtime beats:15.07% memory beats:56.99%
std::vector<int> searchRange_2(std::vector<int>& nums, int target) {
    std::vector<int>::iterator itr = nums.begin();
    int i = 0;
    while (itr != nums.end()) {
        if (*itr > target) {
            return { -1, -1 };
        }
        else if (*itr == target) {
            int j = i;
            while (itr != nums.end() && *itr == target) {
                itr++;
                j++;
            }
            return { i,j-1 };
        }
        itr++;
        i++;
    }
    return { -1,-1 };
}

//網解 runtime beats:58.74% memory beats:83.68%
std::vector<int> searchRange_network(std::vector<int>& nums, int target) {
    std::vector<int> res(2, -1);
    int start_ = 0, end_ = nums.size() - 1;
    while (start_ <= end_) {
        int mid_ = (start_ + end_) / 2;
        if (nums[mid_] > target) end_ = mid_ - 1;
        else if (nums[mid_] < target) start_ = mid_ + 1;
        else {
            start_ = mid_;
            end_ = mid_;
            for (; start_ > -1;) {
                if (nums[start_] == target) { res[0] = start_; --start_; }
                else break;
            }
            for (; end_ < nums.size();) {
                if (nums[end_] == target) { res[1] = end_; ++end_; }
                else break;
            }
            break;
        }
    }
    return res;
}

//35. Search Insert Position
//初解 runtime beats:58.18% memory beats:31.13%
int searchInsert(std::vector<int>& nums, int target) {
    int s = nums.size();
    for (int i = 0; i < s; i++) {
        if (nums[i] > target)
            return i;
        else if (nums[i] == target)
            return i;
    }
    return s;
}

//36. Valid Sudoku
//初解 runtime beats:05.22% memory beats:05.02%
bool isValidSudoku(std::vector<std::vector<char>>& board) {
    //9x9
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            //sub-boxes
            if (i % 3 == 0 && j % 3 == 0) {
                std::map<char, int> subboxes;
                for (int i_off = 0; i_off < 3; i_off++) {
                    for (int j_off = 0; j_off < 3; j_off++) {
                        if (((i != i + i_off) || (j != j + j_off)) 
                            && (board[i + i_off][j + j_off] != '.') 
                            && (subboxes.find(board[i + i_off][j + j_off]) != subboxes.end())) {
                            return false;
                        }
                        else {
                            subboxes[board[i + i_off][j + j_off]] = 1;
                        }
                    }
                }
            }

            if (board[i][j] != '.') {
                
                int i1 = i + 1, j1 = j + 1;
                //行
                for (i1; i1 < 9; i1++) {
                    if (board[i][j] == board[i1][j]) {
                        return false;
                    }
                }

                //列
                for (j1; j1 < 9; j1++) {
                    if (board[i][j] == board[i][j1]) {
                        return false;
                    }
                }
            }       
        }
    }

    return true;
}

//二解 runtime beats:26.30% memory beats:19.15%
bool isValidSudoku_2(std::vector<std::vector<char>>& board) {
    //9x9
    int i, j;
    std::map<char, int> subboxes;
    //sub-boxes
    for (i = 0; i < 7; i += 3)
        for (j = 0; j < 7; j += 3) {
            subboxes.clear();
            for (int i_off = 0; i_off < 3; i_off++) {
                for (int j_off = 0; j_off < 3; j_off++) {
                    if (((i != i + i_off) || (j != j + j_off))
                        && (board[i + i_off][j + j_off] != '.')
                        && (subboxes.find(board[i + i_off][j + j_off]) != subboxes.end())) {
                        return false;
                    }
                    else
                        subboxes[board[i + i_off][j + j_off]] = 1;
                }
            }
        }

    //逐行檢查
    for (i = 0; i < 9; i++) {
        subboxes.clear();
        for (j = 0; j < 9; j++) {
            if ((board[i][j] != '.') && (subboxes.find(board[i][j]) != subboxes.end())) {
                return false;
            }
            else
                subboxes[board[i][j]] = 1;
        }
    }

    //逐列檢查
    for (i = 0; i < 9; i++) {
        subboxes.clear();
        for (j = 0; j < 9; j++) {
            if ((board[j][i] != '.') && (subboxes.find(board[j][i]) != subboxes.end())) {
                return false;
            }
            else
                subboxes[board[j][i]] = 1;
        }
    }

    return true;
}

//網解 runtime beats:46.20% memory beats:91.75%
bool isValidSudoku_network(std::vector<std::vector<char>>& a) {
    bool row[10][10];
    bool col[10][10];
    memset(row, false, sizeof(row));
    memset(col, false, sizeof(col));
    int i, j, k, l;
    for (k = 0; k < 9; k++) {
        for (l = 0; l < 9; l++) {
            char c = a[k][l];
            if (c == '.') {
                continue;
            }
            if (row[c - '0'][k] == true) {
                return false;
            }
            else if (col[c - '0'][l] == true) {
                return false;
            }
            else {
                int boxi = k / 3, boxj = l / 3;
                for (i = boxi * 3; i < boxi * 3 + 3; i++) {
                    for (j = boxj * 3; j < boxj * 3 + 3; j++) {
                        if (a[i][j] == a[k][l] && (i != k || j != l)) {
                            return false;
                        }
                    }
                }
                row[c - '0'][k] = true; col[c - '0'][l] = true;
            }
        }
    }
    return true;
}

//39. Combination Sum
//初解 runtime beats:98.93% memory beats:79.43%
void combinationSum_helper(std::vector<std::vector<int>>& ans, std::vector<int>& sub_ans, std::vector<int>& candidates, int start, int end, int target) {
    if (target < 0)
        return;

    for (int i = start; i < end; i++) {
        sub_ans.push_back(candidates[i]);
        if (candidates[i] == target)
            ans.push_back(sub_ans);
        else
            combinationSum_helper(ans, sub_ans, candidates, i, end, target - candidates[i]);
        sub_ans.pop_back();
    }
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> ans;
    std::vector<int> sub_ans;
    combinationSum_helper(ans, sub_ans, candidates, 0, candidates.size(), target);
    return ans;
}

//40. Combination Sum II
//初解 runtime beats:27.36% memory beats:70.38%
void combinationSum2_helper(std::set<std::vector<int>>& ans, std::vector<int>& sub_ans, std::vector<int>& candidates, int start, int end, int target) {
    if (target < 0)
        return;

    for (int i = start; i < end; i++) {
        if (sub_ans.empty() && (i > 0) && (candidates[i] == candidates[i - 1]))
            continue;
        sub_ans.push_back(candidates[i]);
        if (candidates[i] == target)
            ans.insert(sub_ans);
        else
            combinationSum2_helper(ans, sub_ans, candidates, i + 1, end, target - candidates[i]);
        sub_ans.pop_back();
    }
}

std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
    std::set<std::vector<int>> ans;
    std::vector<int> sub_ans;
    sort(candidates.begin(), candidates.end());
    combinationSum2_helper(ans, sub_ans, candidates, 0, candidates.size(), target);
    return { ans.begin(), ans.end() };
}

//網解 runtime beats:100.00% memory beats:70.73%
void findcomb(std::vector<int>& candidates, std::vector<std::vector<int>>& result, std::vector<int>& com, int start, int target)
{
    if (target == 0) {
        result.push_back(com);
        return;
    }

    for (int i = start; i < candidates.size(); i++) {
        if (i != start && candidates[i] == candidates[i - 1])
            continue;
        if (candidates[i] > target)
            break;
        com.push_back(candidates[i]);
        findcomb(candidates, result, com, i + 1, target - candidates[i]);
        com.pop_back();
    }
}

std::vector<std::vector<int>> combinationSum2_network(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    if (candidates.size() == 0)
        return result;
    sort(candidates.begin(), candidates.end());
    std::vector<int> com;
    findcomb(candidates, result, com, 0, target);
    return result;
}

//41. First Missing Positive
//初解 runtime beats:07.31% memory beats:87.72%
int firstMissingPositive(std::vector<int>& nums) {
    int s = nums.size();
    if (s == 0)
        return 1;

    sort(nums.begin(), nums.end());

    int smallest = 1;
    for (int i = 0; i < s; i++) {
        if (nums[i] > smallest)
            return smallest;
        else if (nums[i] == smallest)
            smallest++;
    }

    return smallest;
}

//二解 runtime beats:84.53% memory beats:86.24%
int firstMissingPositive_2(std::vector<int>& nums) {
    int s = nums.size();
    if (s == 0)
        return 1;

    int smallest = 1;
    for (int i = 0; i < s; i++) {
        for (int j = i + 1; j < s; j++) {
            if (nums[i] > nums[j]) {
                int tmp = nums[j];
                nums[j] = nums[i];
                nums[i] = tmp;
            }
        }

        if (nums[i] > smallest)
            return smallest;
        else if (nums[i] == smallest)
            smallest++;
    }

    return smallest;
}

//42. Trapping Rain Water
//初解 runtime beats:62.06% memory beats:64.38%
int trap(std::vector<int>& height) {
    if (height.size() < 3) {
        return 0;
    }
    
    int s = height.size();
    int posi = 0;
    int mid_count = 0, total_area = 0;
    //從左到右
    for (int i = 1; i < s; i++) {
        if (height[posi] <= height[i]) {
            total_area += ((i - posi - 1) * (height[posi] < height[i] ? height[posi] : height[i])) - mid_count;
            mid_count = 0;
            posi = i;
        }
        else {
            mid_count = mid_count + height[i];
        }
    }

    if(mid_count == 0)
        return total_area;

    //從右到左
    int p_plus = posi;
    posi = s - 1;
    mid_count = 0;
    for (int i = s - 2; i > p_plus - 1; i--) {
        if (height[posi] <= height[i]) {
            total_area += ((posi - i - 1) * (height[posi] < height[i] ? height[posi] : height[i])) - mid_count;
            mid_count = 0;
            posi = i;
        }
        else {
            mid_count = mid_count + height[i];
        }
    }

    return total_area;
}

//int trap_2(std::vector<int>& height) {
//    if (height.size() < 3) {
//        return 0;
//    }
//    height.push_back(0);
//    int s = height.size();
//    int compare_peak = -1, old_peak = 0, peak = -1;
//    int mid_count = 0, total_area = 0;
//    for (int i = 0; i < s - 1; i++) {
//        if (height[i] > height[i + 1]) {    //  下坡
//            if (peak != -1) {   //過峰點
//                total_area += ((peak - old_peak - 1) * (height[peak] < height[old_peak] ? height[peak] : height[old_peak])) - (mid_count - height[peak]);
//                mid_count = height[i + 1];
//
//                if (compare_peak != -1 && old_peak < peak)
//                    total_area += ((peak - compare_peak - 1) * ((height[peak] < height[compare_peak] ? height[peak] : height[compare_peak]) - height[old_peak]));
//
//                compare_peak = height[peak] < height[old_peak] ? old_peak : -1; //當舊的peak大於新的peak，觸發補償機制
//                old_peak = peak;
//                peak = -1;
//            }
//            else {
//                mid_count += height[i + 1];
//            }
//        }
//        else {  //  上坡
//            peak = i + 1;
//            mid_count += height[i + 1];
//        }
//    }
//
//    return total_area;
//}

//網解 runtime beats:62.06% memory beats:92.89%
int trap_network(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 2)
        return 0;
    // initialize output 
    int result = 0;

    // maximum element on left and right 
    int left_max = 0, right_max = 0;

    // indices to traverse the array 
    int lo = 0, hi = n - 1;

    while (lo <= hi) {
        if (arr[lo] < arr[hi]) {    //right max than left
            if (arr[lo] > left_max)
                // update max in left 
                left_max = arr[lo];
            else
                // water on curr element = max - curr 
                result += left_max - arr[lo];
            lo++;
        }
        else {
            if (arr[hi] > right_max)
                // update right maximum 
                right_max = arr[hi];
            else
                result += right_max - arr[hi];
            hi--;
        }
    }

    return result;
}

//45. Jump Game II
//網解 runtime beats:52.28% memory beats:70.17%
int jump_network(std::vector<int>& nums) {
    int count = 0;//計步器
    int cur = 0;//當前走到底幾位
    int maxNext = 0;//最大的下一個
    for (int i = 0; i < nums.size() - 1; i++) {
        maxNext = std::max(maxNext, nums[i] + i);
        //nums[i]+i可以知道跳到第幾步 i=要跳的步數 nums[i]指的是這次能跳的步數
        if (i == cur) {//因為是用nums.length-1 所以這邊要先++ 
            count++;
            cur = maxNext;
        }
    }
    return count;
}

//46. Permutations
//初解 runtime beats:37.58% memory beats:46.35%
void DFS(std::vector<std::vector<int>>& ans, std::vector<int>& part, std::vector<int>& rest)
{
    int rest_size = rest.size();
    if (rest_size == 0) {
        ans.push_back(part);
        return;
    }

    for (int i = 0; i < rest_size; i++) {
        part.push_back(rest[i]);

        std::vector<int> new_rest;
        for (auto r : rest) {
            if (r != rest[i])
                new_rest.push_back(r);
        }

        DFS(ans, part, new_rest);
        part.pop_back();
    }
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> ans;
    std::vector<int> sub_ans;
    DFS(ans, sub_ans, nums);

    return ans;
}

//48. Rotate Image
//初解 runtime beats:64.33% memory beats:49.52%
void rotate(std::vector<std::vector<int>>& matrix) {
    int  s = matrix.size();
    if (s < 1)
        return;

    int x1 = 0, y1 = 0,
        x2 = s - 1, y2 = 0,
        x3 = s - 1, y3 = s - 1,
        x4 = 0, y4 = s - 1;

    int shrink = 0;
    while (shrink < (s - 2) / 2 + 1) {
        int tmp = matrix[x1][y1];
        matrix[x1][y1] = matrix[x2][y2];
        matrix[x2][y2] = matrix[x3][y3];
        matrix[x3][y3] = matrix[x4][y4];
        matrix[x4][y4] = tmp;

        x1++; y2++; x3--; y4--;
        if (x1 == s - 1 - shrink && y2 == s - 1 - shrink && x3 == shrink && y4 == shrink) { //  內縮一圈
            shrink++;
            x1 = shrink, y1 = shrink, x2 = s - 1 - shrink, y2 = shrink, x3 = s - 1 - shrink, y3 = s - 1 - shrink, x4 = shrink, y4 = s - 1 - shrink;
        }
    }
}

//網解 runtime beats:100.00% memory beats:92.23%
void rotate_network(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            std::swap(matrix[i][j], matrix[j][i]);
}

//49. Group Anagrams
//初解 runtime beats:41.91% memory beats:82.06%
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
    int s = strs.size();
    if (s < 1)
        return { {} };

    std::map<std::string , int> sort_map;
    std::vector<std::vector<std::string>> ans;

    for (int i = 0; i < s; i++) {
        std::string sort_str = strs[i];
        std::sort(sort_str.begin(), sort_str.end());

        if (sort_map.find(sort_str) != sort_map.end()) {
            ans[sort_map[sort_str]].push_back(strs[i]);
        }
        else {
            std::vector<std::string> sub_ans;
            sub_ans.push_back(strs[i]);
            ans.push_back(sub_ans);
            sort_map[sort_str] = ans.size() - 1;
        }
    }

    return ans;
}

//53. Maximum Subarray
//初解 runtime beats:46.64% memory beats:70.04%
//int maxSubArray(std::vector<int>& nums) {
//    if (nums.size() == 0)
//        return INT_MIN;
//
//    int max_Sub = INT_MIN;
//    int Sub = 0;
//    for (auto num : nums) {
//        Sub += num;
//        max_Sub = max_Sub > Sub ? max_Sub : Sub;
//        if (Sub < 0)
//            Sub = 0;
//    }
//
//    return max_Sub;
//}

//55. Jump Game
//初解 runtime beats:81.88% memory beats:37.69%
//bool canJump(std::vector<int>& nums) {
//    int cur = 0;        //當前走到底幾位
//    int maxNext = 0;    //最大的下一個
//    int s = nums.size();
//    for (int i = 0; i < s - 1; i++) {
//        maxNext = std::max(maxNext, nums[i] + i);
//        //nums[i]+i可以知道跳到第幾步 i=要跳的步數 nums[i]指的是這次能跳的步數
//        if (i == cur) {//因為是用nums.length-1 所以這邊要先++ 
//            cur = maxNext;
//            if (cur >= s - 1)
//                return true;
//        }
//    }
//
//    if (cur < s - 1)
//        return false;
//    else
//        return true;
//}

//56. Merge Intervals
//初解 runtime beats:65.74% memory beats:61.10%
std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    int s = intervals.size();
    if (s < 2)
        return intervals;
    sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> ans;
    int x = intervals[0][0], y = intervals[0][1];
    for (int i = 1; i < s; i++) {
        if (y >= intervals[i][0]) {
            if (y < intervals[i][1])
                y = intervals[i][1];
        }
        else {
            ans.push_back({ x, y });
            x = intervals[i][0], y = intervals[i][1];
        }
    }
    ans.push_back({ x, y });
    return ans;
}

//網解 runtime beats:74.07% memory beats:76.75%
std::vector<std::vector<int>> merge_network(std::vector<std::vector<int>>& in) {
    std::vector<std::vector<int>>a;
    for (int i = 0; i < in.size(); i++)
    {
        if (in[i][0] == -1 && in[i][1] == -1)continue;
        int s = in[i][0];
        int f = in[i][1];
        in[i][0] = -1;
        in[i][1] = -1;
        for (int j = 0; j < in.size(); j++)
        {
            if (in[j][0] == -1)continue;
            if (in[j][0] >= s && in[j][0] <= f && in[j][1] >= s && in[j][1] <= f)
            {
                in[j][0] = -1;
                in[j][1] = -1;
                continue;
            }
            if ((in[j][0] > s && in[j][0] > f) && (in[j][1] > s && in[j][1] > f))continue;
            if (in[j][0] < s && in[j][0] < f && in[j][1] < s && in[j][1] < f)continue;
            if (in[j][0] <= s && in[j][1] >= s && in[j][1] <= f && in[j][0] < f)
            {
                s = in[j][0];
                in[j][0] = -1;
                in[j][1] = -1;
                j = -1; continue;
            }
            if (in[j][0] > s && in[j][0] <= f && in[j][1] > s && in[j][1] > f)
            {
                f = in[j][1];
                in[j][0] = -1;
                in[j][1] = -1;
                j = -1; continue;
            }
            if (in[j][0] <= s && in[j][1] >= s && in[j][0] <= f && in[j][1] >= f)
            {
                s = in[j][0];
                f = in[j][1];
                in[j][0] = -1;
                in[j][1] = -1;
                j = -1; continue;

            }
        }
        std::vector<int>x;
        x.push_back(s);
        x.push_back(f);
        a.push_back(x);
    }

    return a;
}

//57. Insert Interval
//初解 runtime beats:05.29% memory beats:52.84%
std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
    intervals.push_back(newInterval);
    int s = intervals.size();
    if (s < 2)
        return intervals;
    sort(intervals.begin(), intervals.end());
    std::vector<std::vector<int>> ans;
    int x = intervals[0][0], y = intervals[0][1];
    for (int i = 1; i < s; i++) {
        if (y >= intervals[i][0]) {
            if (y < intervals[i][1])
                y = intervals[i][1];
        }
        else {
            ans.push_back({ x, y });
            x = intervals[i][0], y = intervals[i][1];
        }
    }
    ans.push_back({ x, y });
    return ans;
}

//60. Permutation Sequence
//初解 runtime beats:05.04% memory beats:32.76%
std::string DFS(std::vector<int>& parts, std::vector<int>& rest, int& k)
{
    int rest_size = rest.size();
    if (rest_size == 0) {
        k--;
        if (k == 0) {
            std::string s_part;
            for (auto part : parts)
                s_part += std::to_string(part);
            return s_part;
        }
        else
            return "";
    }

    for (int i = 0; i < rest_size; i++) {
        parts.push_back(rest[i]);

        int rest_i = rest[i];
        rest.erase(rest.begin() + i);
        std::string fromDFS = DFS(parts, rest, k);
        rest.insert(rest.begin() + i, rest_i);

        if (fromDFS != "")
            return fromDFS;
        parts.pop_back();
    }
    return "";
}

int n_factorial(int k) {
    if (k < 2)
        return 1;
    else
        return k * n_factorial(k - 1);
}

std::string getPermutation(int n, int k) {
    std::vector<int> parts;
    std::vector<int> rest;
    int count = 0;
    for (int i = 1; i <= n; i++) {
        rest.push_back(i);
    }
    
    int if_1 = n_factorial(n - 1);
    if (k % if_1 != 0) {
        int part = (k / if_1) + 1;
        count = if_1 * (part - 1);
        parts.push_back(part);
        rest.erase(rest.begin() + part - 1);
    }
    else {
        int part = (k / if_1);
        count = if_1 * (part - 1);
        parts.push_back(part);
        rest.erase(rest.begin() + part - 1);
    }
    k = k - count;
    return DFS(parts, rest, k);
}

//二解 runtime beats:30.03% memory beats:05.04%
std::string getPermutation_2(int n, int k) {
    std::vector<int> parts;
    std::vector<int> rests;
    int count = 0;
    for (int i = 1; i <= n; i++) {
        rests.push_back(i);
    }

    while (n > 0) {
        int if_1 = n_factorial(n - 1);
        if (k % if_1 != 0) {
            int posi = (k / if_1);
            if (posi == 0) {
                int k_plus = k % if_1;
                if (k_plus == 1) {
                    for (auto rest : rests)
                        parts.push_back(rest);
                    n = 0;
                }
                else {
                    return DFS(parts, rests, k_plus);
                }
            }
            else {
                int part = rests[posi];
                count = if_1 * (posi);
                parts.push_back(part);
                rests.erase(rests.begin() + posi);
            }            
        }
        else {
            int posi = (k / if_1) - 1;
            int part = rests[posi];
            count = if_1 * (posi);
            parts.push_back(part);
            rests.erase(rests.begin() + posi);
        }
        n--;
        k = k - count;
    }    

    std::string str;
    for (auto part : parts)
        str += std::to_string(part);
    return str;
}

//網解 runtime beats:100.00% memory beats:12.73%
void helper(std::string& ans, std::vector<int>& nums, std::vector<int> fact, int n, int k)
{
    if (n == 1) {
        ans += std::to_string(nums.back());
        return;
    }

    int ind = (k / fact[n - 1]);
    if (k % fact[n - 1] == 0)
        ind--;

    ans += std::to_string(nums[ind]);
    nums.erase(nums.begin() + ind);
    k -= fact[n - 1] * ind;
    helper(ans, nums, fact, n - 1, k);
}

std::string getPermutation_network(int n, int k)
{
    std::string ans = "";
    if (n == 1)
        return "1";

    std::vector <int> nums;
    for (int i = 1; i <= n; i++)
        nums.push_back(i);

    std::vector <int> fact = { 1,1,2,6,24,120,720,5040,40320,362880 };

    helper(ans, nums, fact, n, k);

    return ans;
}

//62. Unique Paths
//初解 runtime beats:18.41% memory beats:97.66%
int uniquePaths(int m, int n) {
    if (m == 1 || n == 1)
        return 1;
    else if (n == 2)    //從n == 2之後皆是為了加速計算速度而找出的規律
        return m;
    else if (n == 3)
        return (1 + m) * m / 2;
    else if (n == 4) {
        int tmp = 0;
        for (int i = 1; i <= m; i++)
            tmp += ((1 + i) * i / 2);
        return tmp;
    }
    return uniquePaths(m, n - 1) + uniquePaths(m - 1, n);
}

//https://www.cnblogs.com/grandyang/p/4353555.html
//網解 runtime beats:100.00% memory beats:75.88%
int uniquePaths_netwrok(int m, int n) {
    std::vector<int> dp(n, 1);
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[j] += dp[j - 1];
        }
    }
    return dp[n - 1];
}

//網解 runtime beats:100.00% memory beats:99.40%
int uniquePaths_netwrok_2(int m, int n) {
    double num = 1, denom = 1;
    double tmp;
    int small = m > n ? n : m;
    for (int i = 1; i <= small - 1; ++i) {
        tmp = m;
        tmp += n;
        tmp = tmp - 1 - i;
        num = num * tmp;
        denom *= i;
    }
    return (int)(num / denom);
}

//63. Unique Paths II
//https://www.cnblogs.com/grandyang/p/4353680.html
//網解 runtime beats:97.01% memory beats:34.45%
int uniquePathsWithObstacles_network(std::vector<std::vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty() || obstacleGrid[0][0] == 1)
        return 0;
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    //+1是為了處理邊緣是障礙物的情況
    std::vector<std::vector<long>> dp(m + 1, std::vector<long>(n + 1, 0));
    dp[0][1] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (obstacleGrid[i - 1][j - 1] != 0) continue;
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m][n];
}

//網解 runtime beats:43.85% memory beats:78.91%
int uniquePathsWithObstacles_network_2(std::vector<std::vector<int>>& obstacleGrid) {
    if (obstacleGrid.empty() || obstacleGrid[0].empty() || obstacleGrid[0][0] == 1) return 0;
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    std::vector<long> dp(n, 0);
    dp[0] = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[i][j] == 1) dp[j] = 0;
            else if (j > 0) dp[j] += dp[j - 1];
        }
    }
    return dp[n - 1];
}

//64. Minimum Path Sum
//初解 runtime beats:08.58% memory beats:94.01%
int minPathSum(std::vector<std::vector<int>>& grid) {
    int layer1_size = grid.size();
    if (layer1_size == 0)
        return 0;

    int layer2_size = grid[0].size();
    int i = 0, j = 0;
    for (i = 1; i < layer1_size; i++) {
        grid[i][0] += grid[i - 1][0];
    }

    for (j = 1; j < layer2_size; j++) {
        grid[0][j] += grid[0][j - 1];
    }
  
    for (i = 1; i < layer1_size; i++) {
        for (j = 1; j < layer2_size; j++) {
            grid[i][j] += std::min(grid[i - 1][j], grid[i][j - 1]);
        }
    }

    return grid[layer1_size - 1][layer2_size - 1];
}

//67. Add Binary
//初解 runtime beats:92.85% memory beats:05.03%
std::string addBinary(std::string a, std::string b) {
    int a_size = a.size();
    int b_size = b.size();
    if (a_size > b_size)
        return addBinary(b, a);

    //a比b短
    std::string ans = "";
    bool iscarry = false;
    int i = b_size - a_size;

    while (i--) {   //前面補0
        a = "0" + a;
    }

    for (i = b_size - 1; i >= 0; i--) {
        if (iscarry) {
            if (a[i] == '1' && b[i] == '1')
                ans = "1" + ans;
            else if (a[i] == '1') 
                ans = "0" + ans;
            else if (b[i] == '1') 
                ans = "0" + ans;
            else {
                ans = "1" + ans;
                iscarry = false;
            }
        }
        else {
            if (a[i] == '1' && b[i] == '1') {
                ans = "0" + ans;
                iscarry = true;
            }
            else if (a[i] == '1')
                ans = "1" + ans;
            else if (b[i] == '1')
                ans = "1" + ans;
            else
                ans = "0" + ans;
        }
    }

    if(iscarry)
        ans = "1" + ans;
    
    return ans;
}

//二解 runtime beats:92.85% memory beats:45.78%
std::string addBinary_2(std::string a, std::string b) {
    int a_size = a.size();
    int b_size = b.size();
    if (a_size > b_size)
        return addBinary_2(b, a);

    //a比b短
    bool iscarry = false;
    int i = b_size - a_size;
    while (i--) {   //前面補0
        a = "0" + a;
    }

    for (i = b_size - 1; i >= 0; i--) {
        if (iscarry) {
            if (a[i] == '1' && b[i] == '1')
                a[i] = '1';
            else if (a[i] == '1')
                a[i] = '0';
            else if (b[i] == '1')
                a[i] = '0';
            else {
                a[i] = '1';
                iscarry = false;
            }
        }
        else {
            if (a[i] == '1' && b[i] == '1') {
                a[i] = '0';
                iscarry = true;
            }
            else if (a[i] == '1')
                a[i] = '1';
            else if (b[i] == '1')
                a[i] = '1';
            else
                a[i] = '0';
        }
    }

    if (iscarry)
        a = "1" + a;

    return a;
}

//70. Climbing Stairs
//初解 runtime beats:13.94% memory beats:70.44%
//int climbStairs(int n) {
//    std::vector<int> stairs{ 0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
//    for (int i = 11; i < n; i++) {
//        stairs.push_back(stairs[i] + stairs[i - 1]);
//    }
//    return stairs[n];
//}

//二解 runtime beats:100.00% memory beats:80.69%
//int climbStairs_2(int n) {
//    if (n < 4)
//        return n;
//
//    int a = 2, b = 3;
//    n += -3;
//
//    while (n--) {
//        int tmp = a;
//        a = b;
//        b = b + tmp;
//    }
//        
//    return b;
//}

//73. Set Matrix Zeroes
//初解 runtime beats:30.94% memory beats:56.66%
void setZeroes(std::vector<std::vector<int>>& matrix) {
    int cols_size = matrix.size();
    if (cols_size < 1)
        return;

    int rows_size = matrix[0].size();
    int i, j;
    std::set<int> cols;
    bool needclear = false;

    for (i = 0; i < cols_size; i++) {
        for (j = 0; j < rows_size; j++) {
            if (matrix[i][j] == 0) {
                cols.insert(j);
                needclear = true;
            }
        }

        if (needclear) {
            matrix[i].assign(rows_size, 0);
            needclear = false;
        }
    }

    for (std::set<int>::iterator it = cols.begin(); it != cols.end(); ++it)
        for (i = 0; i < cols_size; i++)
            matrix[i][*it] = 0;    
}

//74. Search a 2D Matrix
//初解 runtime beats:80.89% memory beats:49.57%
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    int rows = matrix.size();
    if (rows == 0)
        return false;

    int cols = matrix[0].size();
    if (cols == 0)
        return false;
    int i;
    for (i = 0; i < rows - 1; i++) {
        if ((matrix[i][0] <= target) && (matrix[i + 1][0] > target)) {
            for (auto col : matrix[i]) {
                if (col == target)
                    return true;
                else if (col > target)
                    return false;
            }
            return false;
        }
    }

    //last rows
    if ((matrix[rows - 1][0] <= target) && (matrix[rows - 1][cols - 1] >= target)) {
        for (auto col : matrix[rows - 1]) {
            if (col == target)
                return true;
            else if (col > target)
                return false;
        }
    }

    return false;
}

//75. Sort Colors
//初解 runtime beats:100.00% memory beats:17.43%
void sortColors(std::vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[i] > nums[j]) {
                std::swap(nums[i], nums[j]);
            }
        }
    }
}

//76. Minimum Window Substring
//網解 runtime beats:91.42% memory beats:61.38%
std::string minWindow_network(std::string s, std::string t) {
    std::vector<int> letterCnt(128, 0);
    int left = 0, cnt = 0, minLeft = -1, minLen = INT_MAX;

    for (auto c : t) ++letterCnt[c];

    for (int i = 0; i < s.size(); ++i) {
        if (--letterCnt[s[i]] >= 0)
            ++cnt;
        while (cnt == t.size()) {
            if (minLen > i - left + 1) {
                minLen = i - left + 1;
                minLeft = left;
            }
            if (++letterCnt[s[left]] > 0)
                --cnt;
            ++left;
        }
    }
    return minLeft == -1 ? "" : s.substr(minLeft, minLen);
}

//77. Combinations
//初解 runtime beats:20.54% memory beats:26.08%
void DFS(std::vector<std::vector<int>>& ans, std::vector<int>& a, std::vector<int> b, int depth, int depth_max) {
    while(b.size() > 0){
        a.push_back(b[0]);
        b.erase(b.begin());

        if (depth == depth_max - 1) {
            ans.push_back(a);
        }
        else {
            DFS(ans, a, b, depth + 1, depth_max);
        }
        a.pop_back();
    }
}

std::vector<std::vector<int>> combine(int n, int k) {
    if (n == 0)
        return {};
    if (k == 0)
        return { {} };

    std::vector<int> n_combi;
    while (n > 0) {
        n_combi.push_back(n);
        n--;
    }

    reverse(n_combi.begin(), n_combi.end());
    
    std::vector<std::vector<int>> ans;
    std::vector<int> a;
    DFS(ans, a, n_combi, 0, k);
    return ans;
}

//網解 runtime beats:92.87% memory beats:88.06%
void combine(int begin, int n, int k, std::vector<std::vector<int>>& ans, std::vector<int>& temp) {
    if (k == 0) {
        ans.push_back(temp);
        return;
    }
    //condition : n-i+1 is the range, range must greater than k
    for (int i = begin; n - i + 1 >= k; i++) { // for the ith iteration, get the combination of i and k-1 numbers differ from i.
        temp.push_back(i);
        combine(i + 1, n, k - 1, ans, temp);// get the combination of k-1 numbers which range is(i+1,n) 
        temp.pop_back();
    }
}

std::vector<std::vector<int>> combine_network(int n, int k) {
    std::vector<std::vector<int>> ans;
    std::vector<int> temp;
    combine(1, n, k, ans, temp); //call fuction to get combination of k numbers which range is 1-n
    return ans;
}

//78. Subsets
//初解 runtime beats:66.40% memory beats:44.33%
void Subsets(int begin, int k, std::vector<std::vector<int>>& ans, std::vector<int> sets, std::vector<int>& temp) {
    ans.push_back(temp);
    for (int i = begin; i < k; i++) {
        temp.push_back(sets[i]);
        Subsets(i + 1, k, ans, sets, temp);
        temp.pop_back();
    }
}

std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> ans;
    std::vector<int> temp;

    Subsets(0, nums.size(), ans, nums, temp);

    return ans;
}

//網解 runtime beats:100.00% memory beats:68.55%
std::vector<std::vector<int>> subsets_network(std::vector<int>& nums) {
    const int n = nums.size();
    std::vector<std::vector<int>> results;
    for (int i = 0; i < pow(2, n); i++) {
        std::vector<int> v;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                v.push_back(nums[j]);
            }
        }
        results.push_back(move(v));
    }
    return results;
}

//79. Word Search
//初解 runtime beats:05.02% memory beats:05.43%
bool exist(std::vector<std::vector<char>>& board, int rows, int cols, std::vector<std::vector<bool>> bool_board, int i, int j, int word_posi, std::string word) {
    if (word_posi == word.size())
        return true;
    
    if (i != 0)
        if (bool_board[i -1][j])
            if (board[i - 1][j] == word[word_posi]) {
                bool_board[i - 1][j] = false;
                if (exist(board, rows, cols, bool_board, i - 1, j, word_posi + 1, word))
                    return true;
                bool_board[i - 1][j] = true;
            }                

    if (i != rows)
        if (bool_board[i + 1][j])
            if (board[i + 1][j] == word[word_posi]) {
                bool_board[i + 1][j] = false;
                if (exist(board, rows, cols, bool_board, i + 1, j, word_posi + 1, word))
                    return true;
                bool_board[i + 1][j] = true;
            }
                

    if (j != 0)
        if (bool_board[i][j - 1])
            if (board[i][j - 1] == word[word_posi]) {
                bool_board[i][j - 1] = false;
                if (exist(board, rows, cols, bool_board, i, j - 1, word_posi + 1, word))
                    return true;
                bool_board[i][j - 1] = true;
            }

    if (j != cols)
        if (bool_board[i][j + 1])
            if (board[i][j + 1] == word[word_posi]) {
                bool_board[i][j + 1] = false;
                if (exist(board, rows, cols, bool_board, i, j + 1, word_posi + 1, word))
                    return true;
                bool_board[i][j + 1] = true;
            }                

    return false;
}

bool exist(std::vector<std::vector<char>>& board, std::string word) {
    int rows = board.size();
    if (rows == 0)
        return false;
    
    int cols = board[0].size();
    if (cols == 0)
        return false;

    int i, j;

    std::vector<std::vector<bool>> bool_board(rows, std::vector<bool>(cols, true));
    for(i=0;i<rows;i++)
        for (j = 0; j < cols; j++) {
            if (board[i][j] == word[0]) {
                bool_board[i][j] = false;
                if (exist(board, rows - 1, cols - 1, bool_board, i, j, 1, word))
                    return true;
                bool_board[i][j] = true;
            }
        }

    return false;
}

//網解 runtime beats:97.90% memory beats:78.72%
bool exist(std::vector<std::vector<char>>& board, int i, int j, std::string& word, int mindex) {
    if (mindex == word.size()) 
        return true;
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
        return false;
    if (word[mindex] != board[i][j])
        return false;

    char c = board[i][j];
    board[i][j] = '*';   //to prevent selecting this cell twice
    bool ret = exist(board, i + 1, j, word, mindex + 1) || exist(board, i - 1, j, word, mindex + 1) || exist(board, i, j + 1, word, mindex + 1) || exist(board, i, j - 1, word, mindex + 1);
    board[i][j] = c;
    return ret;
}

bool exist_network(std::vector<std::vector<char>>& board, std::string word) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (exist(board, i, j, word, 0))
                return true;
        }
    }
    return false;
}

//80. Remove Duplicates from Sorted Array II
//初解 runtime beats:99.21% memory beats:78.99%
int removeDuplicates(std::vector<int>& nums) {
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i - 1] == nums[i]) {
            i++;
            while ((i < nums.size()) && (nums[i - 1] == nums[i])) {
                nums.erase(nums.begin() + i);
            }
        }
    }

    return nums.size();
}

//81. Search in Rotated Sorted Array II
//初解 runtime beats:96.60% memory beats:72.85%
bool searchII(std::vector<int>& nums, int target) {
    int nums_size = nums.size();
    for (int i = 0; i < nums_size; i++) {
        if (nums[i] == target)
            return true;
    }
    return false;
}

//82. Remove Duplicates from Sorted List II
//網解 runtime beats:99.35% memory beats:78.46%
ListNode* deleteDuplicates_network(ListNode* head) {
    if (head == nullptr)
        return head;
    ListNode* p1 = head->next;
    if (p1 && p1->val == head->val) {
        while (p1 && p1->val == head->val) {
            ListNode* p2 = p1;
            p1 = p1->next;
            p2->next = nullptr;
        }
        return deleteDuplicates_network(p1);
    }
    else
        head->next = deleteDuplicates_network(head->next);
    return head;
}

//84. Largest Rectangle in Histogram
//https://www.cnblogs.com/boring09/p/4231906.html
//網解 runtime beats:64.06% memory beats:72.64%
int largestRectangleArea_network(std::vector<int>& height) {
    height.push_back(0);
    std::stack<int> st;
    int n = height.size();
    int maxArea = 0;
    int h, w;

    for (int i = 0; i < n; i++) {
        if (st.empty() || height[st.top()] < height[i])
            st.push(i);
        else {
            while (!st.empty() && height[i] <= height[st.top()]) {
                h = height[st.top()];
                st.pop();
                w = st.empty() ? i : i - (st.top() + 1);
                maxArea = std::max(maxArea, h * w);
            }
            st.push(i);
        }
    }

    return maxArea;
}

//https://www.cnblogs.com/grandyang/p/4322653.html
//網解 runtime beats:87.52% memory beats:94.84%
int largestRectangleArea_network_2(std::vector<int>& heights) {
    int res = 0;
    std::stack<int> st;
    heights.push_back(0);
    for (int i = 0; i < heights.size(); ++i) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            int cur = st.top(); 
            st.pop();
            res = std::max(res, heights[cur] * (st.empty() ? i : (i - st.top() - 1)));
        }
        st.push(i);
    }
    return res;
}

//85. Maximal Rectangle
//int maximalRectangle(std::vector<std::vector<char>>& matrix) {
//
//}

//86. Partition List
//初解 runtime beats:100.00% memory beats:61.95%
ListNode* partition(ListNode* head, int x) {
    if ((head == nullptr) || (head->next == nullptr))
        return head;

    ListNode* push = new ListNode;
    push->next = head;
    ListNode* cur_push = push;
    ListNode* start = head;
    while ((start != nullptr) && (start->val < x)) {
        cur_push = start;
        start = start->next;
    }

    while (start != nullptr) {
        if ((start->next != nullptr) && (start->next->val < x)) {
            ListNode* tmp = start->next;
            start->next = start->next->next;
            tmp->next = cur_push->next;
            cur_push->next = tmp;
            cur_push = cur_push->next;
        }
        else
            start = start->next;
    }

    return push->next;
}

//90. Subsets II
//初解 runtime beats:06.48% memory beats:05.08%
void subsetsWithDup(int begin, int k, std::vector<std::vector<int>>& ans, std::vector<int> sets, std::vector<int>& temp) {
    for (auto an : ans)
        if (std::equal(an.begin(), an.end(), temp.begin(), temp.end()))
            return;
    ans.push_back(temp);
    for (int i = begin; i < k; i++) {
        temp.push_back(sets[i]);
        subsetsWithDup(i + 1, k, ans, sets, temp);
        temp.pop_back();
    }
}

std::vector< std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
    std::vector<std::vector<int>> ans;
    std::vector<int> temp;
    std::sort(nums.begin(), nums.end());
    subsetsWithDup(0, nums.size(), ans, nums, temp);
    return ans;
}

//網解 runtime beats:100.00% memory beats:100.00%
void backtrack(std::vector<std::vector<int>>& res, std::vector<int>& nums, int i, int n, std::vector<int>& tmp) {
    if (i == nums.size()) return;

    int m = res.size();
    if (nums[i] != nums[i - 1])
        n = m;
    for (int j = m - n; j < m; ++j) {
        tmp = res[j];
        tmp.emplace_back(nums[i]);
        res.emplace_back(tmp);
    }

    backtrack(res, nums, ++i, n, tmp);
}

std::vector<std::vector<int>> subsetsWithDup_network(std::vector<int>& nums) {
    if (nums.empty()) return { {} };
    sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res{ {} };
    std::vector<int> tmp;
    res.emplace_back(std::vector<int>{nums[0]});
    backtrack(res, nums, 1, 1, tmp);
    return res;
}

//92. Reverse Linked List II
//初解 runtime beats:57.90% memory beats:29.00%
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (m == n)
        return head;
    m--;
    n--;
    std::vector<ListNode*> list;
    while (head != NULL) {
        list.emplace_back(head);
        head = head->next;
    }
    
    for (int i = n; i > m; i--) {
        list[i]->next = list[i - 1];
    }

    if (list.size() < n + 2)
        list[m]->next = NULL;
    else
        list[m]->next = list[n + 1];

    if (m - 1 >= 0)
        list[m - 1]->next = list[n];
    else
        return list[n];

    return list[0];
}

//網解 runtime beats:100.00% memory beats:34.02%
ListNode* reverseBetween_network(ListNode* head, int m, int n) {
    if (head == nullptr or (n - m) == 0)
        return head;
    ListNode* prevList = nullptr, * curr = head;
    int cnt = 1;
    while (cnt < m) {
        prevList = curr;
        curr = curr->next;
        cnt++;
    }
    ListNode* prevCurr = curr, * prev = nullptr;
    cnt = 0;
    while (cnt <= n - m) {
        ListNode* save = curr->next;
        curr->next = prev;
        prev = curr;
        curr = save;
        cnt++;
    }
    prevCurr->next = curr;
    if (prevList) {
        prevList->next = prev;
    }
    else
        head = prev;
    return head;
}

//94. Binary Tree Inorder Traversal
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}   
};

void traversalTree(std::vector<int>& ans, TreeNode* root, int& posi) {
    if (root->left != nullptr) {        
        ans.insert(ans.begin() + posi, root->left->val);
        traversalTree(ans, root->left, posi);
    }
   
    if (root->right != nullptr) {
        if (posi + 1 >= ans.size())
            ans.push_back(root->right->val);
        else
            ans.insert(ans.begin() + posi + 1, root->right->val);
        posi++;
        traversalTree(ans, root->right, posi);
        posi--;
    }
}

//初解 runtime beats:100.00% memory beats:10.03%
//std::vector<int> inorderTraversal(TreeNode* root) {
//    std::vector<int> ans;
//    int posi = 0;
//    if (root != nullptr) {
//        ans.push_back(root->val);
//        traversalTree(ans, root, posi);
//    }
//    
//    return ans;
//}

//95. Unique Binary Search Trees II
//網解 runtime beats:92.68% memory beats:87.69%
std::vector<TreeNode*> helper(int start, int end, std::vector<std::vector<std::vector<TreeNode*>>>& memo) {
    if (start > end) return { nullptr };
    if (!memo[start - 1][end - 1].empty()) return memo[start - 1][end - 1];
    std::vector<TreeNode*> res;
    for (int i = start; i <= end; ++i) {
        auto left = helper(start, i - 1, memo), right = helper(i + 1, end, memo);
        for (auto a : left) {
            for (auto b : right) {
                TreeNode* node = new TreeNode(i);
                node->left = a;
                node->right = b;
                res.push_back(node);
            }
        }
    }
    return memo[start - 1][end - 1] = res;
}

std::vector<TreeNode*> generateTrees_network(int n) {
    if (n == 0) return {};
    std::vector<std::vector<std::vector<TreeNode*>>> memo(n, std::vector<std::vector<TreeNode*>>(n));
    return helper(1, n, memo);
}

//96. Unique Binary Search Trees
//https://medium.com/@bill800227/leetcode-96-unique-binary-search-trees-abce6e62a7a0
//網解 runtime beats:100.00% memory beats:45.28%
int numTrees_network(int n) {
    //Time complexity: O(n^2) space complexity: O(n)
    if (n == 0) return 1;
    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] += dp[j] * dp[i - j - 1];
        }
    }
    return dp.back();
}

//https://www.cnblogs.com/grandyang/p/4299608.html
//網解 runtime beats:100.00% memory beats:60.29%
int numTrees_network_2(int n) {
    //Catalan Number
    //https://en.wikipedia.org/wiki/Catalan_number
    //                     (2n)!        (n+1)(n+2)(n+3) ... (2n)
    //Catalan Number = ------------- = --------------------------
    //                  (n+1)!(n)!              (n+1)!
    
    long res = 1;
    for (int i = n + 1; i <= 2 * n; ++i) {
        res = res * i / (i - n);
    }
    return res / (n + 1);
}

//97. Interleaving String
//網解 runtime beats:84.84% memory beats:15.95%
//https://medium.com/@bill800227/leetcode-97-interleaving-string-18b1202fb0ea
bool isInterleave_DFS(std::string s1, int p1, std::string s2, int p2, std::string s3, int p3, std::unordered_set<int>& memo) {
    int key = p1 * s3.size() + p2;
    if (memo.find(key) != memo.end())   //memo儲存的是錯誤，若在memo中找到key代表該key的答案是false
        return false;
    
    if (p1 == s1.size()) //代表s1已經全比對完成
        return s2.substr(p2) == s3.substr(p3);

    if (p2 == s2.size()) //代表s2已經全比對完成
        return s1.substr(p1) == s3.substr(p3);

    if (s1[p1] == s3[p3] && isInterleave_DFS(s1, p1 + 1, s2, p2, s3, p3 + 1, memo))
        return true;

    if (s2[p2] == s3[p3] && isInterleave_DFS(s1, p1, s2, p2 + 1, s3, p3 + 1, memo))
        return true;

    memo.insert(key);
    return false;
}

bool isInterleave_network(std::string s1, std::string s2, std::string s3) {
    if (s1.size() + s2.size() < s3.size())
        return false;

    std::unordered_set<int> memo;
    return isInterleave_DFS(s1, 0, s2, 0, s3, 0, memo);
}

//網解 runtime beats:100.00% memory beats:93.75%
bool isInterleave_network_2(std::string s1, std::string s2, std::string s3) {
    int m = s1.length(), n = s2.length(), l = s3.length();
    if (m > n) return isInterleave_network_2(s2, s1, s3);
    if (l != m + n) return false;
    bool* dp = new bool[m + 1];
    dp[0] = true;
    for (int i = 1; i <= m; i++)
        dp[i] = dp[i - 1] && s3[i - 1] == s1[i - 1];
    for (int j = 1; j <= n; j++) {
        dp[0] = dp[0] && s3[j - 1] == s2[j - 1];
        for (int i = 1; i <= m; i++)
            dp[i] = (dp[i - 1] && s3[i + j - 1] == s1[i - 1]) || (dp[i] && s3[i + j - 1] == s2[j - 1]);
    }
    return dp[m];
}

//98. Validate Binary Search Tree
//https://www.cnblogs.com/grandyang/p/4298435.html
//網解 runtime beats:66.61% memory beats:51.39%
void inorder(TreeNode* root, std::vector<int>& vals) {
    if (!root) return;
    //中序遍歷
    inorder(root->left, vals);
    vals.push_back(root->val);
    inorder(root->right, vals);
}

bool isValidBST(TreeNode* root) {
    if (!root) return true;
    std::vector<int> vals;
    inorder(root, vals);
    for (int i = 0; i < vals.size() - 1; ++i) {
        if (vals[i] >= vals[i + 1]) return false;
    }
    return true;
}

//100. Same Tree
//初解 runtime beats:100.00% memory beats:63.73%
bool isSameTree_DFS(TreeNode* p, TreeNode* q) {
    if (!p && !q)
        return true;
    else if (!p)
        return false;
    else if (!q)
        return false;

    if (p->val == q->val) {
        return isSameTree_DFS(p->left, q->left) && isSameTree_DFS(p->right, q->right);
    }
    else
        return false;
}

bool isSameTree(TreeNode* p, TreeNode* q) {   

    return isSameTree_DFS(p, q);
}

//101. Symmetric Tree
//初解 runtime beats:67.13% memory beats:66.67%
bool isSymmetric_DFS(TreeNode* L, TreeNode* R) {
    if (!L && !R)
        return true;
    else if (!L)
        return false;
    else if (!R)
        return false;

    if (L->val == R->val) {
        return isSymmetric_DFS(L->left, R->right) && isSymmetric_DFS(L->right, R->left);
    }
    else
        return false;
}

bool isSymmetric(TreeNode* root) {
    if (!root)
        return true;

    return isSymmetric_DFS(root->left, root->right);
}

//102. Binary Tree Level Order Traversal
//初解 runtime beats:54.91% memory beats:15.87%
void Traverse_Tree_DFS(std::vector<std::vector<int>>& ans, TreeNode* node, int level) {
    if (!node)
        return;

    if (ans.size() == level)
        ans.push_back(std::vector<int>());

    ans[level].push_back(node->val);
    Traverse_Tree_DFS(ans, node->left, level + 1);
    Traverse_Tree_DFS(ans, node->right, level + 1);
}

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> ans;
    Traverse_Tree_DFS(ans, root, 0);
    return ans;
}

//二解 runtime beats:91.33% memory beats:94.76%
std::vector<std::vector<int>> levelOrder_2(TreeNode* root) {
    if (!root)
        return {};
    std::vector<std::vector<int>> ans;
    //BFS
    std::queue<TreeNode*> wait_queue;
    wait_queue.push(root);
    int old_count = 1;
    int new_count = 0;
    while (!wait_queue.empty()) {
        ans.push_back({});
        while (old_count--) {
            TreeNode* node = wait_queue.front();
            wait_queue.pop();
            ans[ans.size() - 1].push_back(node->val);
            if (node->left) {
                wait_queue.push(node->left);
                new_count++;
            }

            if (node->right) {
                wait_queue.push(node->right);
                new_count++;
            }
        }
        old_count = new_count;
        new_count = 0;
    }

    return ans;
}

//103. Binary Tree Zigzag Level Order Traversal
//初解 runtime beats:100.00% memory beats:98.34%
std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root)
        return {};
    std::vector<std::vector<int>> ans;
    //BFS
    std::queue<TreeNode*> wait_queue;
    wait_queue.push(root);
    int old_count = 1;
    int new_count = 0;
    bool iszigzag = true;
    while (!wait_queue.empty()) {
        ans.push_back({});
        while (old_count--) {
            TreeNode* node = wait_queue.front();
            wait_queue.pop();

            if (iszigzag)
                ans[ans.size() - 1].push_back(node->val);
            else
                ans[ans.size() - 1].insert(ans[ans.size() - 1].begin(), node->val);

            if (node->left) {
                wait_queue.push(node->left);
                new_count++;
            }

            if (node->right) {
                wait_queue.push(node->right);
                new_count++;
            }
        }
        old_count = new_count;
        new_count = 0;
        iszigzag = !iszigzag;
    }

    return ans;
}

//104. Maximum Depth of Binary Tree
//初解 runtime beats:77.93% memory beats:08.59%
int Traverse_Tree_DFS(TreeNode* node, int level) {
    if (!node)
        return level;

    return std::max(Traverse_Tree_DFS(node->left, level + 1), Traverse_Tree_DFS(node->right, level + 1));
}

int maxDepth(TreeNode* root) {
    if (!root)
        return 0;

    return Traverse_Tree_DFS(root, 0);
}

//二解 runtime beats:48.35% memory beats:49.87%
int maxDepth_2(TreeNode* root) {
    if (!root)
        return 0;
    int level = 0;
    //BFS
    std::queue<TreeNode*> wait_queue;
    wait_queue.push(root);
    int old_count = 1;
    int new_count = 0;
    while (!wait_queue.empty()) {
        level++;
        while (old_count--) {
            TreeNode* node = wait_queue.front();
            wait_queue.pop();

            if (node->left) {
                wait_queue.push(node->left);
                new_count++;
            }

            if (node->right) {
                wait_queue.push(node->right);
                new_count++;
            }
        }
        old_count = new_count;
        new_count = 0;
    }

    return level;
}

//105. Construct Binary Tree from Preorder and Inorder Traversal
//https://medium.com/@ChYuan/leetcode-no-105-construct-binary-tree-from-preorder-and-inorder-traversal-%E5%BF%83%E5%BE%97-medium-12dd4fcfa654
//網解 runtime beats:84.37% memory beats:91.49%
TreeNode* build(std::vector<int>& preorder, std::vector<int>& inorder, int& in, int& pre, int stop) {
    if (pre >= preorder.size()) return NULL;
    if (inorder[in] == stop) {
        in++;
        return NULL;
    }
    TreeNode* node = new TreeNode(preorder[pre++]);
    node->left = build(preorder, inorder, in, pre, node->val);
    node->right = build(preorder, inorder, in, pre, stop);
    return node;
}

TreeNode* buildTree_network(std::vector<int> preorder, std::vector<int> inorder) {
    int in = 0;
    int pre = 0;
    return build(preorder, inorder, in, pre, INT_MIN);
}

//網解 runtime beats:74.95% memory beats:99.55%
TreeNode* buildTree_network_2(std::vector<int>& preorder, std::vector<int>& inorder) {
    if (!preorder.size()) return NULL;
    int i(0), p(0);
    TreeNode* root = new TreeNode(preorder[p++]), * q(NULL);
    std::stack<TreeNode*> stk({ root });
    while (!stk.empty()) {
        while (stk.top()->val != inorder[i]) {
            stk.push(stk.top()->left = new TreeNode(preorder[p++]));
        }
        while (!stk.empty() && stk.top()->val == inorder[i]) {
            q = stk.top(); stk.pop();
            ++i;
        }
        if (p < preorder.size())
            if (q)
                stk.push(q->right = new TreeNode(preorder[p++]));
    }
    return root;
}

//107. Binary Tree Level Order Traversal II
//初解 runtime beats:33.88% memory beats:99.38%
std::vector<std::vector<int>> levelOrderBottom(TreeNode* root) {
    if (!root)
        return {};
    std::vector<std::vector<int>> ans;
    //BFS
    std::queue<TreeNode*> wait_queue;
    wait_queue.push(root);
    int old_count = 1;
    int new_count = 0;
    while (!wait_queue.empty()) {
        ans.push_back({});
        while (old_count--) {
            TreeNode* node = wait_queue.front();
            wait_queue.pop();
            ans[ans.size() - 1].push_back(node->val);
            if (node->left) {
                wait_queue.push(node->left);
                new_count++;
            }

            if (node->right) {
                wait_queue.push(node->right);
                new_count++;
            }
        }
        old_count = new_count;
        new_count = 0;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

//網解 runtime beats:100.00% memory beats:96.51%
std::vector<std::vector<int>> levelOrderBottom_network(TreeNode* root)
{
    std::vector<std::vector<int>>ans;
    if (!root)
        return ans;
    std::vector<int>res;
    TreeNode* temp;
    int level = 0;
    std::queue<TreeNode*>q;
    res.push_back(root->val);
    q.push(root);
    while (!q.empty())
    {
        if (level == 0)
        {
            level = q.size();
            ans.push_back(res);
            res.clear();
        }
        temp = q.front();
        q.pop();
        if (temp->left)
        {
            res.push_back(temp->left->val);
            q.push(temp->left);
        }
        if (temp->right)
        {
            res.push_back(temp->right->val);
            q.push(temp->right);
        }
        level--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

//108. Convert Sorted Array to Binary Search Tree
//初解 runtime beats:62.98% memory beats:88.00%
TreeNode* ArrayToBST_DFS(std::vector<int>& nums, int start, int end) {
    if ((start == end))
        return NULL;

    TreeNode* node = new TreeNode(nums[(start + end) / 2]);
    node->left = ArrayToBST_DFS(nums, start, (start + end) / 2);
    node->right = ArrayToBST_DFS(nums, (start + end) / 2 + 1, end);
    return node;
}

TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    int size = nums.size();
    if (size == 0)
        return NULL;

    return  ArrayToBST_DFS(nums, 0, size);
}

//網解 runtime beats:84.55% memory beats:99.52%
void build(TreeNode* root, int start, int end, std::vector<int>& nums, bool l) {
    if (start > end) return;
    TreeNode* a = new TreeNode(nums[(start + end) / 2]);
    if (l) root->left = a;
    else root->right = a;
    build(a, start, (start + end) / 2 - 1, nums, true);
    build(a, (start + end) / 2 + 1, end, nums, false);
}

TreeNode* sortedArrayToBST_network(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return NULL;
    TreeNode* root = new TreeNode(nums[n / 2]);
    build(root, 0, n / 2 - 1, nums, true);
    build(root, n / 2 + 1, n - 1, nums, false);
    return root;
}

//109. Convert Sorted List to Binary Search Tree
//初解 runtime beats:18.07% memory beats:24.86%
TreeNode* sortedListToBST(ListNode* head) {
    if (!head)
        return NULL;
    std::vector<int> nums;
    while (head != NULL) {
        nums.push_back(head->val);
        head = head->next;
    }

    return  ArrayToBST_DFS(nums, 0, nums.size());
}

//110. Balanced Binary Tree
//初解 runtime beats:88.34% memory beats:25.29%
bool isBalanced(TreeNode* root) {
    if (!root)
        return true;

    if (abs(Traverse_Tree_DFS(root->left, 0) - Traverse_Tree_DFS(root->right, 0)) > 1)
        return false;
    else
        return isBalanced(root->left) && isBalanced(root->right);
}

//網解 runtime beats:88.34% memory beats:99.20%
int height(TreeNode* root) {
    if (root == NULL)
        return 0;
    else {
        int ldepth = height(root->left);
        int rdepth = height(root->right);
        if (ldepth > rdepth)
            return ldepth + 1;
        else
            return rdepth + 1;
    }
}

bool isBalanced_network(TreeNode* root) {
    if (root == NULL)
        return true;
    if (abs(height(root->left) - height(root->right)) > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}

//111. Minimum Depth of Binary Tree
//初解 runtime beats:73.34% memory beats:05.33%
int minDepth(TreeNode* root) {
    if (root == NULL)
        return 0;
    
    if (root->left != NULL && root->right != NULL) {
        return std::min(minDepth(root->left), minDepth(root->right)) + 1;
    }
    else if (root->left != NULL)
        return minDepth(root->left) + 1;
    else if (root->right != NULL)
        return minDepth(root->right) + 1;
    else
        return 1;
}

//網解 runtime beats:23.11% memory beats:98.73%
int solve(TreeNode* root)
{
    if (root == NULL)
        return INT_MAX;

    if (root->left == NULL && root->right == NULL)
        return 1;

    int lc = solve(root->left);
    int rc = solve(root->right);
    return lc > rc ? rc + 1 : lc + 1;
}

int minDepth_network(TreeNode* root) {
    if (root == NULL)
        return 0;
    else {
        int ans = solve(root);
        return ans;
    }
}

//112. Path Sum
//初解 runtime beats:15.45% memory beats:82.93%
bool hasPathSum(TreeNode* root, int sum) {
    if (!root)
        return false;

    if (root->left || root->right)
        return (root->left && hasPathSum(root->left, sum - root->val)) || (root->right && hasPathSum(root->right, sum - root->val));
    else
        return root->val == sum;
}

//113. Path Sum II
//初解 runtime beats:53.67% memory beats:28.84%
void ToPathSum(std::vector<std::vector<int>>& ans,std::vector<int> sub_ans, TreeNode* root, int sum) {
    if (!root)
        return;
    sub_ans.push_back(root->val);
    if (root->left || root->right) {
        ToPathSum(ans, sub_ans, root->left, sum - root->val);
        ToPathSum(ans, sub_ans, root->right, sum - root->val);
    }
    else
        if (root->val == sum)
            ans.push_back(sub_ans);
    return;            
}

std::vector<std::vector<int>> pathSum(TreeNode* root, int sum) {
    std::vector<std::vector<int>> ans;
    ToPathSum(ans, {}, root, sum);
    return ans;
}

//網解 runtime beats:96.78% memory beats:89.30%
void dfs(TreeNode* node, int sum, std::vector<std::vector<int>>& res, std::vector<int>& tmp) {
    if (!node) return;
    tmp.push_back(node->val);
    if (!node->left && !node->right) {
        if (sum == node->val)
            res.push_back(tmp);
        tmp.pop_back();
        return;
    }
    sum -= node->val;
    dfs(node->left, sum, res, tmp);
    dfs(node->right, sum, res, tmp);
    tmp.pop_back();
}

std::vector<std::vector<int>> pathSum_network(TreeNode* root, int sum) {
    std::vector<std::vector<int>> ans;
    std::vector<int> tmp;
    dfs(root, sum, ans, tmp);
    return ans;
}

//114. Flatten Binary Tree to Linked List
//初解 runtime beats:96.98% memory beats:43.80%
void flatten(TreeNode* root) {
    if (!root)
        return;

    if (root->left)
        flatten(root->left);

    if(root->right)
        flatten(root->right);

    TreeNode* left_bottom = root->left;
    while (left_bottom && left_bottom->right != NULL) {
        left_bottom = left_bottom->right;
    }

    if (left_bottom) {
        if (!root->right) {
            root->right = root->left;
            root->left = NULL;
        }
        else {
            left_bottom->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }
    }
}

//網解 runtime beats:24.31% memory beats:99.79%
TreeNode* flattenInternal(TreeNode* node)
{
    if (node == nullptr)
        return node;
    else if (node->left == nullptr && node->right == nullptr)
        return node;    // No children

    auto leftTail = flattenInternal(node->left);
    auto rightTail = flattenInternal(node->right);

    if (leftTail != nullptr) {
        leftTail->right = node->right;
        node->right = node->left;
        node->left = nullptr;
    }

    // Return the "right-most" node
    return (rightTail != nullptr) ? rightTail : leftTail;
}

void flatten_network(TreeNode* root) {
    flattenInternal(root);
}

//115. Distinct Subsequences
//初解 runtime beats:11.13% memory beats:05.26%
int numDistinct_DP(std::map<int, int>& DP, std::string s, std::string t, int offset) {
    int t_size = t.size();
    int s_size = s.size();
    if (t_size > s_size || t_size == 0)
        return 0;
    int key = s_size * offset + t_size;

    if (DP.find(key) != DP.end()) {
        return DP[key];
    }

    int count = 0;
    int posi;
    std::string str = s;
    while ((posi = str.find(t[0])) != s.npos) {
        str = str.substr(posi + 1, s_size - posi);
        if (t_size != 1)
            count += numDistinct_DP(DP, str, t.substr(1, t_size - 1), offset);
        else
            count++;
    }

    DP[key] = count;
    return count;
}

int numDistinct(std::string s, std::string t) {
    std::map<int, int> DP;

    int offset = 10;
    int tsize = t.size();
    while (t.size() / offset) {
        offset = offset * 10;
    }

    return numDistinct_DP(DP, s, t, offset);
}

//網解 runtime beats:77.45% memory beats:98.54%
int numDistinct_network(std::string s, std::string t) {
    int m = t.length(), n = s.length();
    std::vector<long long> cur(m + 1, 0L);
    cur[0] = 1;
    for (int j = 1; j <= n; j++) {
        int prev = 1;
        for (int i = 1; i <= m; i++) {
            int temp = cur[i];
            cur[i] = cur[i] + (s[j - 1] == t[i - 1] ? prev : 0);
            prev = temp;
        }
    }
    return cur[m];
}

//116. Populating Next Right Pointers in Each Node
//class Node {
//public:
//    int val;
//    Node* left;
//    Node* right;
//    Node* next;
//
//    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
//
//    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
//
//    Node(int _val, Node* _left, Node* _right, Node* _next)
//        : val(_val), left(_left), right(_right), next(_next) {}
//};

//初解 runtime beats:52.14% memory beats:16.94%
//Node* connect(Node* root) {
//    if (!root)
//        return root;
//    
//    //BFS
//    std::queue<Node*> wait_queue;
//    std::queue<Node*> next_queue;
//    wait_queue.push(root);
//
//    while (!wait_queue.empty()) {
//        Node* tmp = wait_queue.front();
//        wait_queue.pop();
//        if (tmp->left)
//            next_queue.push(tmp->left);
//
//        if (tmp->right)
//            next_queue.push(tmp->right);
//
//        while (!wait_queue.empty()) {
//            Node* tmp_2 = wait_queue.front();
//            wait_queue.pop();
//            if (tmp_2->left)
//                next_queue.push(tmp_2->left);
//
//            if (tmp_2->right)
//                next_queue.push(tmp_2->right);
//
//            tmp->next = tmp_2;
//            tmp = tmp->next;
//        }
//
//        while (!next_queue.empty()) {
//            tmp = next_queue.front();
//            next_queue.pop();
//            wait_queue.push(tmp);
//        }
//    }
//
//    return root;
//}
//
////網解 runtime beats:94.58% memory beats:99.90%
//Node* connect_network(Node* root) {
//    if (!root)
//        return nullptr;
//    Node* l = root->left;
//    Node* last;
//    std::queue<Node*> q;
//    if (root->right)
//        q.push(root->right);
//
//    while (l && !q.empty())
//    {
//        last = l;
//        int initial_size = q.size();
//        if (l->right)
//            q.push(l->right);
//        for (int i = 1; i <= initial_size; i++)
//        {
//            Node* curr = q.front();
//            if (curr->left)
//                q.push(curr->left);
//            if (curr->right)
//                q.push(curr->right);
//            curr->left = curr->right = nullptr;
//            last->next = curr;
//            last = last->next;
//            q.pop();
//        }
//        l = l->left;
//    }
//    return root;
//}

//118. Pascal's Triangle
//初解 runtime beats:100.00% memory beats:45.15%
std::vector<std::vector<int>> generate(int numRows) {
    std::vector<std::vector<int>> ans;

    for (int i = 1; i <= numRows; i++)
        ans.push_back(std::vector<int>(i, 1));

    for (int i = 2; i < numRows; i++) {
        for (int j = 1; j < ans[i].size() - 1; j++) {
            ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
        }
    }

    return ans;
}

//119. Pascal's Triangle II
//初解 runtime beats:100.00% memory beats:79.38%
std::vector<int> getRow(int numRows) {
    std::vector<std::vector<int>> ans;

    for (int i = 1; i <= numRows + 1; i++)
        ans.push_back(std::vector<int>(i, 1));

    for (int i = 2; i < numRows + 1; i++) {
        for (int j = 1; j < ans[i].size() - 1; j++) {
            ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
        }
    }

    return ans[numRows];
}

//網解 runtime beats:100.00% memory beats:96.35%
std::vector<int> getRow_network(int rowIndex) {
    std::vector<int> v;
    v.push_back(1);
    for (int i = 1; i <= rowIndex; i++)
    {
        int temp = 0;
        for (int j = 1; j <= i; j++)
        {
            int temp1 = v[j - 1];       //將原始數字紀錄，用於在下一位時當作左上方之數字
            v[j - 1] = v[j - 1] + temp; //右上方之數字在該欄中，將上次紀錄的左上方之數字加上該欄等於新的欄位
            temp = temp1;
        }
        v.push_back(1);
    }
    return v;
}

//120. Triangle
//初解 runtime beats:63.02% memory beats:74.89%
int minimumTotal(std::vector<std::vector<int>>& triangle) {
    int t_size = triangle.size();
    int i;
    for (i = 1; i < t_size; i++) {
        int i_size = triangle[i].size();
        for (int j = 0; j < i_size; j++) {
            if (j == 0)
                triangle[i][j] += triangle[i - 1][j];
            else if (j == i_size - 1)
                triangle[i][j] += triangle[i - 1][j - 1];
            else
                triangle[i][j] = std::min(triangle[i][j] + triangle[i - 1][j - 1], triangle[i][j] + triangle[i - 1][j]);
        }
    }

    int ans = INT_MAX;
    for (i = 0; i < triangle[t_size - 1].size(); i++) {
        ans = std::min(ans, triangle[t_size - 1][i]);
    }

    return ans;
}

//網解 runtime beats:97.45% memory beats:85.05%
int minimumTotal_network(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();
    std::vector<int> dp(n), tmp;
    for (int i = 0; i < n; i++) {
        tmp = dp;
        dp[0] = tmp[0] + triangle[i][0];
        for (int j = 1; j < i; j++) {
            dp[j] = triangle[i][j] + std::min(tmp[j], tmp[j - 1]);
        }
        if (i) dp[i] = triangle[i][i] + tmp[i - 1];
    }
    int res = INT_MAX;
    for (int i : dp) res = std::min(res, i);
    return res;
}

//121. Best Time to Buy and Sell Stock
//初解 runtime beats:78.41% memory beats:60.88%
int maxProfit(std::vector<int>& prices) {
    int p_size = prices.size();
    if (p_size == 0)
        return 0;

    int min_price = INT_MAX;
    int max_profile = 0;

    for (int i = 0; i < prices.size(); i++) {
        if (min_price > prices[i]) {
            min_price = prices[i];
        }
        else {
            max_profile = std::max(max_profile, prices[i] - min_price);
        }
    }
    return max_profile;
}

//124. Binary Tree Maximum Path Sum
//網解 runtime beats:28.29% memory beats:98.99%
int solve(TreeNode* root, int& ans)
{
    if (root == NULL) {
        return 0;
    }

    int lv = solve(root->left, ans);
    int rv = solve(root->right, ans);
    int cv = lv + rv + root->val > root->val ? lv + rv + root->val : root->val;
    cv = cv > lv + root->val ? cv : lv + root->val;
    cv = cv > rv + root->val ? cv : rv + root->val;
    ans = ans > cv ? ans : cv;
    int retv = lv > rv ? lv + root->val : rv + root->val;
    retv = retv > root->val ? retv : root->val;
    return retv;
}
int maxPathSum_network(TreeNode* root) {
    int ans = INT_MIN;
    solve(root, ans);
    return ans;
}

//網解 runtime beats:88.78% memory beats:77.04%
int calcPathSum(TreeNode* root, int& maxSum) {
    if (root == NULL) return 0;

    int ls = calcPathSum(root->left, maxSum);
    int rs = calcPathSum(root->right, maxSum);

    // Path sum to return to the parent. The path can contain
    // atmost one child.
    int returnSum = std::max(std::max(ls + root->val, rs + root->val),
        root->val);

    maxSum = std::max(maxSum, std::max(returnSum, ls + rs + root->val));
    return returnSum;
}

int maxPathSum_network_2(TreeNode* root) {
    int maxSum = INT_MIN;
    calcPathSum(root, maxSum);
    return maxSum;
}

//128. Longest Consecutive Sequence
//網解 runtime beats:93.09% memory beats:73.79%
//https://www.cnblogs.com/grandyang/p/4276225.html
int longestConsecutive(std::vector<int>& nums) {
    int res = 0;
    std::unordered_set<int> s(nums.begin(), nums.end());
    for (int val : nums) {
        if (!s.count(val)) continue;
        s.erase(val);
        int pre = val - 1, next = val + 1;
        while (s.count(pre)) s.erase(pre--);
        while (s.count(next)) s.erase(next++);
        res = std::max(res, next - pre - 1);
    }
    return res;
}

//129. Sum Root to Leaf Numbers
//初解 runtime beats:100.00% memory beats:74.77%
void sumNumbers_DFS(TreeNode* root, int past, int& ans) {
    if (!root)
        return;

    if (!root->left && !root->right)
        ans += (past * 10) + root->val;
    else {
        sumNumbers_DFS(root->left, (past * 10) + root->val, ans);
        sumNumbers_DFS(root->right, (past * 10) + root->val, ans);
    }
}

int sumNumbers(TreeNode* root) {
    int ans = 0;
    sumNumbers_DFS(root, 0, ans);
    return ans;
}

//130. Surrounded Regions
//初解 runtime beats:07.73% memory beats:07.44%
bool helper_solve(int i, int j, int x_size, int y_size,
    std::vector<std::vector<bool>>& dp_board,
    std::vector<std::vector<char>>& board,
    std::vector<char*>& candidate) {

    if (!dp_board[i][j])
        return true;

    //board
    if ((i == 0) || (i == (x_size - 1)) || (j == 0) || (j == (y_size - 1))) {
        if (board[i][j] == 'O')
            return false;
        else
            return true;
    }

    if ((board[i][j] == 'O')) {
        candidate.push_back(&board[i][j]);
        dp_board[i][j] = false;

        bool ans = helper_solve(i - 1, j, x_size, y_size, dp_board, board, candidate);
        ans = helper_solve(i + 1, j, x_size, y_size, dp_board, board, candidate) && ans;
        ans = helper_solve(i, j - 1, x_size, y_size, dp_board, board, candidate) && ans;
        ans = helper_solve(i, j + 1, x_size, y_size, dp_board, board, candidate) && ans;
        return ans;
    }
    return true;
}

void solve(std::vector<std::vector<char>>& board) {
    int x_size = board.size();
    if (x_size < 3)
        return;
    int y_size = board[0].size();
    if (y_size < 3)
        return;

    std::vector<std::vector<bool>> dp_board(x_size, std::vector<bool>(y_size, true));
    std::vector<std::vector<char*>> candidates;
    std::vector<char*> candidate;
    for(int i=1; i< x_size - 1;i++)
        for (int j = 1; j < y_size - 1; j++) {
            if (dp_board[i][j] && board[i][j] == 'O') {
                if (helper_solve(i, j, x_size, y_size, dp_board, board, candidate))
                    candidates.push_back(candidate);
                candidate.clear();
            }
        }

    for (auto c1 : candidates)
        for (auto c2 : c1)
            *c2 = 'X';
}

//網解 runtime beats:77.90% memory beats:56.75%
void escape(std::vector<std::vector<char>>& board, int i, int j, int& rows, int& cols) {
    if (i < 0 || i > rows - 1 || j < 0 || j > cols - 1) return;
    if (board[i][j] == 'X' || board[i][j] == 'E') return;
    board[i][j] = 'E';
    escape(board, i + 1, j, rows, cols);
    escape(board, i - 1, j, rows, cols);
    escape(board, i, j - 1, rows, cols);
    escape(board, i, j + 1, rows, cols);
}

void mark(std::vector<std::vector<char>>& board, int& rows, int& cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] == 'E') {
                board[i][j] = 'O';
            }
            else if (board[i][j] == 'O') {
                board[i][j] = 'X';
            }
        }
    }
}

void solve_network(std::vector<std::vector<char>>& board) {
    int rows = board.size();
    if (rows == 0) return;
    int cols = board[0].size();
    if (cols == 0) return;
    for (int i = 0; i < cols; ++i) {
        escape(board, 0, i, rows, cols);
        escape(board, rows - 1, i, rows, cols);
    }

    for (int i = 1; i < rows - 1; ++i) {
        escape(board, i, 0, rows, cols);
        escape(board, i, cols - 1, rows, cols);
    }

    mark(board, rows, cols);
}

//131. Palindrome Partitioning
//網解 runtime beats:93.40% memory beats:98.36%
std::vector<std::vector<std::string>> partition_network(std::string s) {
    std::vector<std::vector<std::string>> ans;
    auto isPalindrome = [&](int i, int j) {
        while (i < j) {
            if (s[i] == s[j]) {
                i++;
                j--;
            }
            else {
                return false;
            }
        }
        return true;
    };
    std::function<void(int, std::vector<std::string>&)> dfs = [&](int i, std::vector<std::string>& curr) {
        if (i >= s.length()) {
            ans.push_back(std::vector<std::string>(curr.begin(), curr.end()));
        }
        for (int k = i; k < s.length(); k++) {
            if (isPalindrome(i, k)) {
                curr.push_back(s.substr(i, k - i + 1));
                dfs(k + 1, curr);
                curr.pop_back();
            }
        }
    };
    std::vector<std::string> curr;
    dfs(0, curr);
    return ans;
}

//初解 runtime beats:99.41% memory beats:95.49%
bool isPalindrome(std::string& s, int i, int j) {
    while (i < j) {
        if (s[i] == s[j]) {
            i++;
            j--;
        }
        else
            return false;
    }
    return true;
}

void dfs(std::string& s, int i, std::vector<std::string>& curr, std::vector<std::vector<std::string>>& ans) {
    if (i >= s.length())
        ans.push_back(curr);

    for (int k = i; k < s.length(); k++) {
        if (isPalindrome(s, i, k)) {
            curr.push_back(s.substr(i, k - i + 1));
            dfs(s, k + 1, curr, ans);
            curr.pop_back();
        }
    }
}

std::vector<std::vector<std::string>> partition(std::string s) {
    std::vector<std::vector<std::string>> ans;
    std::vector<std::string> curr;
    dfs(s, 0, curr, ans);
    return ans;
}

//132. Palindrome Partitioning II
//https://www.cnblogs.com/grandyang/p/4271456.html
//網解 runtime beats:99.94% memory beats:94.32%
int minCut_network(std::string s) {
    if (s.empty()) return 0;
    int n = s.size();
    std::vector<int> dp(n + 1, INT_MAX);
    dp[0] = -1;
    for (int i = 0; i < n; ++i) {
        for (int len = 0; i - len >= 0 && i + len < n && s[i - len] == s[i + len]; ++len)
            dp[i + len + 1] = std::min(dp[i + len + 1], 1 + dp[i - len]);

        for (int len = 0; i - len >= 0 && i + len + 1 < n && s[i - len] == s[i + len + 1]; ++len)
            dp[i + len + 2] = std::min(dp[i + len + 2], 1 + dp[i - len]);
    }

    return dp[n];
}

//https://medium.com/@bill800227/leetcode-132-palindrome-partitioning-ii-d8aac7794ebc
//網解 runtime beats:55.57% memory beats:59.09%
int minCut_network_2(std::string s) {
    int n = s.size();
    std::vector<std::vector<bool>> isPalin(n, std::vector<bool>(n, false));
    //isPalin[j][i] represents if s[j:i] is palindrome
    std::vector<int> dp(n, 0);
    //dp[i] represents the minCut of s[0:i]

    for (int i = 0; i < n; ++i) {
        dp[i] = i;  //max num of cut of s[0:i]
        for (int j = 0; j <= i; ++j) {
            if (s[i] == s[j] && (i - j <= 2 || isPalin[j + 1][i - 1])) {
                isPalin[j][i] = true;
                dp[i] = j == 0 ? 0 : std::min(dp[i], dp[j - 1] + 1);
            }
        }
    }

    return dp.back();
}

//134. Gas Station
//初解 runtime beats:18.60% memory beats:77.33%
int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
    int size = gas.size();
    if (size == 0)
        return -1;

    for (int i = 0; i < size; i++) {
        int g = gas[i] - cost[i];
        if (g < 0)
            continue;

        for (int j = 1; j < size; j++) {
            if ((i + j) < size) {
                g = g + gas[i + j] - cost[i + j];
                if (g < 0) {
                    j = size;
                    continue;
                } 
            }
            else {
                g = g + gas[i + j - size] - cost[i + j - size];
                if (g < 0) {
                    j = size;
                    continue;
                }
            }
        }

        if (g >= 0)
            return i;
    }

    return -1;
}

//網解 runtime beats:96.74% memory beats:42.44%
int canCompleteCircuit_network(std::vector<int>& gas, std::vector<int>& cost) {
    int start = 0;
    int tank = 0;
    int sum_gas = 0;
    int sum_cost = 0;
    for (int i = 0; i < gas.size(); i++) {
        sum_gas += gas[i];
        sum_cost += cost[i];
        tank += gas[i] - cost[i];
        if (tank < 0) {
            tank = 0;
            start = i + 1;
        }
    }
    if (sum_gas < sum_cost)
        return -1;
    return start;
}

//136. Single Number
//初解 runtime beats:05.20% memory beats:77.40%
int singleNumber(std::vector<int>& nums) {
    int i = 1;
    while ((nums.size() > 1) && (i < nums.size())) {
        if (nums[0] == nums[i]) {
            nums.erase(nums.begin() + i);
            nums.erase(nums.begin());
            i = 1;
        }
        else
            i++;
    }

    if (nums.empty())
        return 0;
    else
        return nums.front();
}

//二解 runtime beats:07.30% memory beats:83.29%
int singleNumber_2(std::vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int size = nums.size();
    if (size == 1)
        return nums[0];

    for (int i = 0; i < size - 1; i++) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
        else {
            while ((i < (size - 1)) && (nums[i] == nums[i + 1]))
                i++;
        }
    }

    if (nums[size - 1] != nums[size - 2])
        return nums[size - 1];
    else
        return 0;
}

//三解 runtime beats:18.55% memory beats:07.67%
int singleNumber_3(std::vector<int>& nums) {
    int size = nums.size();
    if (size == 1)
        return nums[0];

    std::map<int, int> map_num;
    for (int i = 0; i < size; i++)
        map_num[nums[i]]++;

    for (auto it = map_num.begin(); it != map_num.end(); ++it)
        if (it->second == 1)
            return it->first;

    return 0;
}

//網解 runtime beats:93.21% memory beats:83.29%
int singleNumber_network(std::vector<int>& nums) {
    // use property of xor, any number xor with 0 is still itself
    // every number xor with itself will be 0
    // eg: 0 ^ 3 ^ 4 ^ 3 = 4
    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
        sum ^= nums[i];
    return sum;
}

//138. Copy List with Random Pointer
class rand_Node {
public:
    int val;
    rand_Node* next;
    rand_Node* random;

    rand_Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

//初解 runtime beats:37.50% memory beats:82.21%
rand_Node* copyRandomList(rand_Node* head) {
    std::vector<rand_Node*> vec;
    while (head != NULL) {
        vec.push_back(head);
        head = head->next;
    }

    int size = vec.size();
    if (size == 0)
        return NULL;
    int i = 0;
    std::vector<rand_Node*> new_vec;
    for (i = 0; i < size; i++)
        new_vec.push_back(new rand_Node(vec[i]->val));

    new_vec.push_back(NULL);
    for (i = 0; i < size; i++) {
        new_vec[i]->next = new_vec[i + 1];

        int posi = 0;
        while ((posi < size) && (vec[i]->random != vec[posi])) {
            posi++;
            if (vec[i]->random == NULL)
                posi = size;
        }

        if (posi >= size)
            new_vec[i]->random = NULL;
        else
            new_vec[i]->random = new_vec[posi];
    }
    return new_vec.front();
}

//https://www.cnblogs.com/grandyang/p/4261431.html
//網解 runtime beats:93.25% memory beats:92.49% 
rand_Node* copyRandomList_network(rand_Node* head) {
    if (!head) return nullptr;
    rand_Node* cur = head;
    while (cur) {
        rand_Node* t = new rand_Node(cur->val);
        t->next = cur->next;
        cur->next = t;
        cur = t->next;
    }
    cur = head;
    while (cur) {
        if (cur->random) cur->next->random = cur->random->next;
        cur = cur->next->next;
    }
    cur = head;
    rand_Node* res = head->next;
    while (cur) {
        rand_Node* t = cur->next;
        cur->next = t->next;
        if (t->next) t->next = t->next->next;
        cur = cur->next;
    }
    return res;
}

//139. Word Break
//初解 runtime beats:48.19% memory beats:37.24%
bool helper_wordBreak(std::string s, std::unordered_set<std::string>& un_set, std::vector<bool>& memo) {
    if (s == "")
        return true;

    for (int i = 1; i <= s.size(); i++)
        if (un_set.find(s.substr(0, i)) != un_set.end())
            if (memo[i] != false)
                if (helper_wordBreak(s.substr(i, s.size() - i), un_set, memo))
                    return true;
                else
                    memo[i] = false;

    return false;
}

bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    std::unordered_set<std::string> un_set(wordDict.begin(), wordDict.end());
    std::vector<bool> memo (s.size(), true);    //紀錄第i個到最後，是否有在wordDict找到過
    return helper_wordBreak(s, un_set, memo);
}

//網解 runtime beats:78.37% memory beats:89.44%
bool wordBreak_network(std::string s, std::vector<std::string>& wordDict) {
    if (wordDict.empty()) return false;
    std::vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    for (int i = 1; i <= s.size(); ++i) {
        for (const auto& word : wordDict) {
            if (word == s.substr(i - 1, word.size()) && dp[i - 1]) {
                dp[i + word.size() - 1] = true;
            }
        }
    }
    return dp[s.size()];
}

//140. Word Break II
//https://www.cnblogs.com/grandyang/p/4576240.html
//網解 runtime beats:49.42% memory beats:70.49%
std::vector<std::string> wordBreak2_helper(std::string s, std::vector<std::string>& wordDict, std::unordered_map<std::string, std::vector<std::string>>& m) {
    if (m.count(s)) 
        return m[s];
    if (s.empty()) return { "" };
    std::vector<std::string> res;
    for (std::string word : wordDict) {
        if (s.substr(0, word.size()) != word) continue;
        std::vector<std::string> rem = wordBreak2_helper(s.substr(word.size()), wordDict, m);
        for (std::string str : rem) {
            res.push_back(word + (str.empty() ? "" : " ") + str);
        }
    }
    return m[s] = res;
}

std::vector<std::string> wordBreak2(std::string s, std::vector<std::string>& wordDict) {
    if (wordDict.empty() || s == "")
        return {};

    std::unordered_map<std::string, std::vector<std::string>> m;
    return wordBreak2_helper(s, wordDict, m);
}

//網解 runtime beats:92.62% memory beats:100.00%
// check for invalid characters in s that are not in dict
bool validateWords(std::string& s, std::vector<std::string>& wordDict) {
    std::unordered_set<char> cs;
    for (std::string& word : wordDict)
        for (char c : word)
            cs.insert(c);

    for (char c : s)
        if (cs.find(c) == cs.end())
            return false;

    return true;
}

std::vector<std::string> wordBreak2_network(std::string s, std::vector<std::string>& wordDict) {
    if (!validateWords(s, wordDict))
        return {};

    std::vector<std::string> res;
    std::vector<int> pos;

    const int n = s.size();

    for (std::string& word : wordDict) {
        const int wn = word.size();
        if (s.compare(0, wn, word) == 0) {
            res.push_back(word);
            pos.push_back(wn);
        }
    }

    for (;;) {
        const int m = res.size();
        int up{};
        for (int i{}; i < m; ++i) {
            if (pos[i] < n) {
                std::string curr = res[i];
                int loc = pos[i];
                int j{};
                for (std::string& word : wordDict) {
                    int wn = word.size();
                    if (s.compare(loc, wn, word) == 0) {
                        if (j) {
                            res.push_back(curr + " " + word);
                            pos.push_back(loc + wn);
                        }
                        else {
                            res[i] += " " + word;
                            pos[i] += wn;
                        }
                        ++j;
                    }
                }
                up += j;
            }
        }
        if (up == 0) { break; }
    }

    for (int i{}; i < pos.size();) {
        if (pos[i] < n) {
            res.erase(res.begin() + i);
            pos.erase(pos.begin() + i);
        }
        else {
            ++i;
        }
    }
    return res;
}

//141. Linked List Cycle
//初解 runtime beats:21.57% memory beats:07.88%
bool hasCycle(ListNode* head) {
    std::unordered_set<ListNode*> list;
    while (head != NULL && (list.find(head) == list.end())) {
        list.insert(head);
        head = head->next;
    }

    if (head == NULL)
        return false;
    else
        return true;
}

//網解 runtime beats:96.32% memory beats:69.53%
bool hasCycle_network(ListNode* head) {
    //邏輯為temp一次走兩步，head一次走一步
    //若有cycle，當進入cycle之後，temp會以每個cycle與head距離減少1的速度接近head
    //最終temp == head
    ListNode* temp = NULL;
    while (head) {
        if (temp == head)
            return true;
        if (head->next == NULL)
            break;
        if (!temp)
            temp = head->next->next;
        else {
            if (temp->next == NULL)
                break;
            temp = temp->next->next;
        }
        head = head->next;
    }
    return false;
}

//142. Linked List Cycle II
//初解 runtime beats:39.50% memory beats:18.49%
ListNode* detectCycle(ListNode* head) {
    std::unordered_set<ListNode*> list;
    while (head != NULL && (list.find(head) == list.end())) {
        list.insert(head);
        head = head->next;
    }

    return head;
}

//143. Reorder List
//初解 runtime beats:92.37% memory beats:21.52%
void reorderList(ListNode* head) {
    if (head == NULL || head->next == NULL || head->next->next == NULL)
        return;

    std::vector<ListNode*> list;
    while (head != NULL) {
        list.push_back(head);
        head = head->next;
    }

    int size = list.size();
    for (int i = 1; i < ((size / 2) + (size % 2)); i++) {
        list[size - i]->next = list[i];
        list[i - 1]->next = list[size - i];
    }

    list[size / 2]->next = NULL;
    return;
}

//144. Binary Tree Preorder Traversal
//初解 runtime beats:100.00% memory beats:71.55%
void preorderTraversal(TreeNode* node, std::vector<int>& ans) {
    if (!node)
        return;
    ans.push_back(node->val);
    preorderTraversal(node->left, ans);
    preorderTraversal(node->right, ans);
}

std::vector<int> preorderTraversal(TreeNode* root) {    //>mid->left->right
    std::vector<int> ans;
    preorderTraversal(root, ans);
    return ans;
}

//145. Binary Tree Postorder Traversal
//初解 runtime beats:100.00% memory beats:31.67%
void postorderTraversal(TreeNode* node, std::vector<int>& ans) {
    if (!node)
        return;
    if(node->left)
        postorderTraversal(node->left, ans);
    if(node->right)
        postorderTraversal(node->right, ans);
    ans.push_back(node->val);
}

std::vector<int> postorderTraversal(TreeNode* root) {   //left->right->mid
    std::vector<int> ans;
    postorderTraversal(root, ans);
    return ans;
}

//146. LRU Cache
//初解 runtime beats:08.53% memory beats:45.17%
class LRUCache {    //最近最少使用
public:
    LRUCache(int capacity) {
        private_capacity = capacity;
        key_value.clear();
        FIFO.clear();
    }

    int get(int key) {
        if (key_value.find(key) == key_value.end())
            return -1;
        else {
            FIFO.erase(find(FIFO.begin(), FIFO.end(), key));
            FIFO.push_back(key);
            return key_value[key];
        }
    }

    void put(int key, int value) {
        if (key_value.find(key) != key_value.end()) {
            key_value[key] = value;
            FIFO.erase(find(FIFO.begin(), FIFO.end(), key));
            FIFO.push_back(key);
            return;
        }

        if (key_value.size() >= private_capacity) {
            key_value.erase(key_value.find(*FIFO.begin()));
            FIFO.erase(FIFO.begin());
        }
        key_value[key] = value;
        FIFO.push_back(key);
    }
private:
    int private_capacity;
    std::unordered_map<int, int> key_value;
    std::list<int> FIFO;              //FIFO
};

//網解 runtime beats:99.48% memory beats:80.69%
class LRUCache_network {
public:
    struct ListNode {
        int key;
        int val;
        ListNode* prev;
        ListNode* next;

        ListNode(int value) {
            key = 0;
            val = value;
            prev = nullptr;
            next = nullptr;
        }
    };

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    std::unordered_map<int, ListNode*> m;
    int sz;

    LRUCache_network(int capacity) {
        sz = capacity;
        std::ios_base::sync_with_stdio(false);        //取消同步
        std::cin.tie(NULL);
    }

    int get(int key) {
        auto it = m.find(key);
        if (it == m.end())
            return -1;
        else {
            ListNode* t = it->second;
            if (t == this->head)
                return t->val;
            t->prev->next = t->next;
            if (t != tail)
                t->next->prev = t->prev;
            else
                this->tail = t->prev;
            t->next = this->head;
            t->prev = nullptr;
            this->head->prev = t;
            this->head = t;
            return t->val;
        }
    }

    void put(int key, int value) {
        if (m.size() == 0) {
            ListNode* temp = new ListNode(value);
            temp->key = key;
            this->head = temp;
            this->tail = temp;
            m[key] = temp;
            return;
        }

        auto it = m.find(key);
        if (it != m.end()) {
            ListNode* t = it->second;
            if (t->val != value) {
                if (t == this->head) {
                    t->val = value;
                    return;
                }
                t->prev->next = t->next;
                if (t != tail)
                    t->next->prev = t->prev;
                else
                    this->tail = t->prev;
                t->val = value;
                t->next = this->head;
                t->prev = nullptr;
                this->head->prev = t;
                this->head = t;
            }
            return;
        }

        if (m.size() < sz) {
            struct ListNode* temp = new ListNode(value);
            temp->key = key;
            temp->next = this->head;
            temp->prev = nullptr;
            this->head->prev = temp;
            this->head = temp;
            m[key] = temp;
        }
        else if (m.size() == sz) {
            struct ListNode* n = this->tail;
            this->tail = this->tail->prev;
            m.erase(n->key);
            delete(n);
            if (m.size() == 0) {
                ListNode* temp = new ListNode(value);
                temp->key = key;
                this->head = temp;
                this->tail = temp;
                m[key] = temp;
            }
            else {
                struct ListNode* temp = new ListNode(value);
                temp->key = key;
                this->head->prev = temp;
                temp->next = this->head;
                this->head = temp;
                m[key] = temp;
            }
        }
    }
};

//148. Sort List
//https://www.cnblogs.com/grandyang/p/4249905.html
//網解 runtime beats:89.72% memory beats:88.98%
void sortListTree(ListNode* start, ListNode* end) {
    if (start->next == end)
        return;
    ListNode* fast = start;
    ListNode* slow = start;
    while (fast != end && fast->next != end) {
        fast = fast->next->next;
        slow = slow->next;
    }
    ListNode* mid = slow;

    ListNode* cur = start->next;
    ListNode* back = start;

    while (cur != mid) {
        if (cur->val > mid->val) {
            back->next = cur->next;
            ListNode* tmp = mid->next;
            mid->next = cur;
            cur->next = tmp;
            cur = back->next;
        }
        else {
            back = back->next;
            cur = cur->next;
        }
    }

    cur = mid->next;
    back = mid;
    while (cur != end) {
        if (cur->val < mid->val) {
            back->next = cur->next;
            ListNode* tmp = start->next;
            start->next = cur;
            cur->next = tmp;
            cur = back->next;
        }
        else {
            back = back->next;
            cur = cur->next;
        }
    }
    sortListTree(start, mid);
    sortListTree(mid, end);

}

ListNode* sortList_network(ListNode* head) {
    ListNode* dummy = new ListNode(INT_MIN);
    dummy->next = head;
    ListNode* cur = dummy;
    while (cur && cur->next) {
        cur = cur->next;
    }
    ListNode* end = new ListNode(INT_MAX);
    cur->next = end;
    sortListTree(dummy, end);
    ListNode* front = dummy;
    ListNode* back = dummy;
    bool flag = false;
    while (front && front->next) {
        if (flag == true)
            back = back->next;
        flag = true;
        front = front->next;
    }
    back->next = NULL;
    return dummy->next;
}

//網解 runtime beats:97.49% memory beats:47.35%
ListNode* sortList_merge(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val < l2->val) {
        l1->next = sortList_merge(l1->next, l2);
        return l1;
    }
    else {
        l2->next = sortList_merge(l1, l2->next);
        return l2;
    }
}

ListNode* sortList_network_2(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* slow = head, * fast = head, * pre = head;
    while (fast && fast->next) {
        //將鏈表從中間斷開的方法，采用的就是快慢指針，大家可能對快慢指針找鏈表中的環比較熟悉
        //其實找鏈表中的中點同樣好使
        //因為"快指針每次走兩步，慢指針每次走一步，當快指針到達鏈表末尾時，慢指針正好走到中間位置"
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = NULL;
    return merge(sortList_network_2(head), sortList_network_2(slow));
}

//150. Evaluate Reverse Polish Notation
//初解 runtime beats:27.18% memory beats:42.28%
int evalRPN(std::vector<std::string>& tokens) {
    std::stack<int> LIFO;

    for (auto token : tokens) {
        if (token == "+") {
            int b = LIFO.top();
            LIFO.pop();
            int a = LIFO.top();
            LIFO.pop();
            LIFO.push(a + b);
        }
        else if (token == "-") {
            int b = LIFO.top();
            LIFO.pop();
            int a = LIFO.top();
            LIFO.pop();
            LIFO.push(a - b);
        }
        else if (token == "*") {
            int b = LIFO.top();
            LIFO.pop();
            int a = LIFO.top();
            LIFO.pop();
            LIFO.push(a * b);
        }
        else if (token == "/") {
            int b = LIFO.top();
            LIFO.pop();
            int a = LIFO.top();
            LIFO.pop();
            LIFO.push(a / b);
        }
        else
            LIFO.push(std::stoi(token));
    }

    return LIFO.top();
}

//網解 runtime beats:55.30% memory beats:32.52%
int evalRPN_network(const std::vector<std::string>& tokens) {
    std::vector<int> s;
    for (auto token : tokens) {
        if (token != "+" && token != "-" && token != "*" && token != "/") {
            s.push_back(stoi(token));
        }
        else {
            int num2 = s.back(); s.pop_back();
            int num1 = s.back(); s.pop_back();
            int res;
            switch (token[0]) {
            case '+': res = num1 + num2; break;
            case '-': res = num1 - num2; break;
            case '*': res = num1 * num2; break;
            case '/': res = num1 / num2; break;
            }
            s.push_back(res);
        }
    }
    return s.back();
}

//152. Maximum Product Subarray
//http://bangbingsyb.blogspot.com/2014/11/leetcode-maximum-product-subarray.html
//網解 runtime beats:80.49% memory beats:46.85%
int maxProduct_network(std::vector<int>& nums) {
    int size = nums.size();
    if (size == 1)
        return nums[0];

    int ans, curMax, curMin;
    ans = curMax = curMin = nums[0];
    for (int i = 1; i < size; i++) {
        int temp = curMax;
        curMax = std::max(std::max(curMax * nums[i], curMin * nums[i]), nums[i]);
        curMin = std::min(std::min(temp * nums[i], curMin * nums[i]), nums[i]);
        ans = std::max(ans, curMax);
    }
    return ans;
}

//網解 runtime beats:98.29% memory beats:46.85%
int maxProduct_network_2(std::vector<int>& nums) {
    int r = nums[0];
    int maxi = r;
    int mini = r;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < 0) {      //當nums[i] < 0時，乘上最小值變成其最大值，但不一定是答案，假設mini原本是正數，若nums[i]<0，其maxi會變負數
            int temp = maxi;
            maxi = mini;
            mini = temp;
        }
        maxi = std::max(nums[i], nums[i] * maxi);
        mini = std::min(nums[i], nums[i] * mini);   //紀錄最小值
        r = std::max(r, maxi);
    }
    return r;
}

//153. Find Minimum in Rotated Sorted Array
//初解 runtime beats:98.29% memory beats:88.67%
int findMin(std::vector<int>& nums) {
    int ans = INT_MAX;
    for (auto num : nums)
        ans = std::min(num, ans);
    return ans;
}

//155. Min Stack
//初解 runtime beats:05.01% memory beats:81.19%
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }

    void push(int x) {
        s.push_back(x);
    }

    void pop() {
        s.erase(s.begin() + s.size() - 1);
    }

    int top() {
        return s[s.size() - 1];
    }

    int getMin() {
        int min = INT_MAX;
        for (auto num : s)
            min = std::min(min, num);
        return min;
    }
private:
    std::vector<int> s;
};

//160. Intersection of Two Linked Lists
//初解 runtime beats:07.98% memory beats:05.34%
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    std::set<ListNode*> unique;
    while (headB != NULL) {
        unique.insert(headB);
        headB = headB->next;
    }

    while (headA != NULL) {
        if (unique.count(headA))
            return headA;
        unique.insert(headA);
        headA = headA->next;
    }

    return NULL;
}

//167. Two Sum II - Input array is sorted
//初解 runtime beats:69.97% memory beats:06.00%
std::vector<int> twoSum2(std::vector<int>& numbers, int target) {
    std::unordered_map<int, int> map;
    int size = numbers.size();

    for (int i = 0; i < numbers.size(); i++) {
        if (map.find(target - numbers[i]) != map.end())
            return { map[target - numbers[i]], i + 1 };
        else
            map[numbers[i]] = i + 1;
    }
    return { -1,-1 };
}

//網解 runtime beats:96.92% memory beats:68.33%
std::vector<int> twoSum2_network(std::vector<int>& nums, int target) {
    int l = 0;
    int r = nums.size() - 1;

    while (l < r) {
        int sum = nums[l] + nums[r];

        if (sum == target)
            return { l + 1, r + 1 };
        else if (sum < target)
            l++;
        else
            r--;
    }
    return { -1, -1 };
}

//168. Excel Sheet Column Title
//初解 runtime beats:100.00% memory beats:60.85%
std::string convertToTitle(int n) {
    std::string ans = "";
    int base = 26;
    n--;
    while (n >= 0) {
        ans = (char)(65 + n % base) + ans;
        n = n / base - 1;
    }

    return ans;
}

//網解 runtime beats:100.00% memory beats:92.12%
std::string convertToTitle_network(int n) {
    std::string str;
    char tmp;
    while (n) {
        n = n - 1;
        tmp = 'A' + n % 26;
        str = tmp + str;
        n = n / 26;
    }
    return str;
}

//169. Majority Element
//初解 runtime beats:73.77% memory beats:27.05%
int majorityElement(std::vector<int>& nums) {
    std::unordered_map<int, int> majority;

    for (auto num : nums)
        majority[num]++;

    std::pair<int, int>ans(-1,-1);
    for (auto maj : majority) {
        if (ans.second < maj.second)
            ans = maj;
    }
    
    return ans.first;
}

//網解 runtime beats:97.66% memory beats:41.27%
int majorityElement_network(std::vector<int>& nums) {
    int maj_elem = nums[0];
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == maj_elem)
            count++;
        else {
            count--;
            if (count == 0) {
                maj_elem = nums[i];
                count = 1;
            }
        }
    }
    return maj_elem;
}

//171. Excel Sheet Column Number
//初解 runtime beats:100.00% memory beats:28.89%
int titleToNumber(std::string s) {
    long ans = 0;
    long tmp;
    for (int i = 0; i < s.size(); i++) {
        tmp = s[i] - 64;
        ans = ans + pow(26, s.size() - 1 - i) * tmp;
    }
        
    return ans;
}

//網解 runtime beats:100.00% memory beats:67.40%
int titleToNumber_network(std::string s) {
    long ans = 0;
    for (char c : s) ans = ans * 26 + c - 'A' + 1;
    return ans;
}

//173. Binary Search Tree Iterator
//初解 runtime beats:43.72% memory beats:05.02%
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        Root = root;
        BST_DFS(Root);
    }

    /** @return the next smallest number */
    int next() {
        int b = *i_set.begin();
        i_set.erase(i_set.begin());
        return b;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if (i_set.empty())
            return false;
        else
            return true;
    }

    void BST_DFS(TreeNode* node) {
        if (!node)
            return;

        i_set.insert(node->val);
        BST_DFS(node->left);
        BST_DFS(node->right);
    }
private:
    TreeNode* Root;
    std::set<int> i_set;
};

//二解 runtime beats:96.80% memory beats:05.02%
class BSTIterator_2 {
public:
    BSTIterator_2(TreeNode* root) {
        Root = root;
        BST_BFS(Root);
    }

    /** @return the next smallest number */
    int next() {
        int b = *i_set.begin();
        i_set.erase(i_set.begin());
        return b;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if (i_set.empty())
            return false;
        else
            return true;
    }

    void BST_BFS(TreeNode* node) {
        if (!node)
            return;

        std::queue<TreeNode*> wait;
        wait.push(node);
        while (!wait.empty()) {
            i_set.insert(wait.front()->val);

            if (wait.front()->left)
                wait.push(wait.front()->left);

            if (wait.front()->right)
                wait.push(wait.front()->right);
            wait.pop();
        }
    }

private:
    TreeNode* Root;
    std::set<int> i_set;
};

//網解 runtime beats:91.31% memory beats:99.00%
class BSTIterator_network {
public:
    //vector<TreeNode *> st;
    TreeNode* head;
    BSTIterator_network(TreeNode* root) {
        head = root;
    }

    /** @return the next smallest number */
    int next() {
        int ans = 0;
        while (head) {
            if (!head->left) {
                ans = head->val;
                head = head->right;
                break;
            }
            else {
                TreeNode* prev = head->left;
                while (prev->right && prev->right != head) {
                    prev = prev->right;
                }
                if (!prev->right) {
                    prev->right = head;
                    head = head->left;
                }
                else {
                    ans = head->val;
                    prev->right = NULL;
                    head = head->right;
                    break;
                }
            }
        }
        return ans;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return head != NULL;
    }
};

//179. Largest Number
//初解 runtime beats:05.28% memory beats:77.40%
std::string largestNumber(std::vector<int>& nums) {
    std::string ans;

    int size = nums.size();
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((std::to_string(nums[j]) + std::to_string(nums[i])) > (std::to_string(nums[i]) + std::to_string(nums[j]))) {
                int tmp = nums[j];
                nums[j] = nums[i];
                nums[i] = tmp;
            }
        }
    }

    for (auto num : nums)
        ans += std::to_string(num);

    return ans[0] == '0' ? "0" : ans;
}

//網解 runtime beats:43.80% memory beats:80.71%
std::string largestNumber_network(std::vector<int>& nums) {
    std::string res;
    sort(nums.begin(), nums.end(), [](int a, int b) {
        return std::to_string(a) + std::to_string(b) > std::to_string(b) + std::to_string(a);
        });
    for (int i = 0; i < nums.size(); ++i) {
        res += std::to_string(nums[i]);
    }
    return res[0] == '0' ? "0" : res;
}

//網解 runtime beats:99.05% memory beats:23.09%
struct Comp {
    bool operator () (const std::string& a, const std::string& b) {
        int len = std::min(a.size(), b.size());
        for (int i = 0; i < len; i++) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return a + b < b + a;
    }
};

std::string largestNumber_network_2(std::vector<int>& nums) {
    std::vector<std::string> strs;
    for (int num : nums) {
        strs.push_back(std::to_string(num));
    }
    sort(strs.begin(), strs.end(), Comp());
    std::string res;
    for (int i = strs.size() - 1; i >= 0; i--) {
        res += strs[i];
        if (res == "0") {
            break;
        }
    }
    return res;
}

//187. Repeated DNA Sequences
//網解 runtime beats:81.32% memory beats:66.99%
std::vector<std::string> findRepeatedDnaSequences_network(std::string s) {
    std::unordered_set<std::string> res, st;
    for (int i = 0; i + 9 < s.size(); ++i) {
        std::string t = s.substr(i, 10);
        if (st.count(t))
            res.insert(t);
        else
            st.insert(t);
    }
    return std::vector<std::string>{res.begin(), res.end()};
}

//網解 runtime beats:81.32% memory beats:66.99%
std::vector<std::string> findRepeatedDnaSequences_network_2(std::string s) {
    //A:0100 0001 -> 001
    //C:0100 0011 -> 011
    //G:0100 0111 -> 111
    //T:0101 0100 -> 100
    //
    std::unordered_set<std::string> res;
    std::unordered_set<int> st;
    int cur = 0;
    for (int i = 0; i < 9; ++i)         //原本的cur先左移3bit在接上s[i]的後3bit
        cur = cur << 3 | (s[i] & 7);    //先做前27bit

    for (int i = 9; i < s.size(); ++i) {
        cur = ((cur & 0x7ffffff) << 3) | (s[i] & 7);        //接上28-30bit，在st中尋找，若存在則存入res
        if (st.count(cur)) res.insert(s.substr(i - 9, 10));
        else st.insert(cur);
    }
    return std::vector<std::string>(res.begin(), res.end());
}

//189. Rotate Array
//初解 runtime beats:08.09% memory beats:80.70%
void rotate(std::vector<int>& nums, int k) {
    k = k % nums.size();
    if (k == 0)
        return;

    while (k--) {
        nums.insert(nums.begin(), *(nums.end() - 1));
        nums.pop_back();
    }
}

//二解 runtime beats:88.58% memory beats:33.31%
void rotate_2(std::vector<int>& nums, int k) {
    k = k % nums.size();
    if (k == 0)
        return;

    std::vector<int> tmp(nums.end() - k, nums.end());
    nums.erase(nums.end() - k, nums.end());
    nums.insert(nums.begin(), tmp.begin(), tmp.end());
}

//190. Reverse Bits
//初解 runtime beats:69.68% memory beats:82.94%
uint32_t reverseBits(uint32_t n) {
    int count = 32;
    uint32_t ans = 0;
    while (count--) {
        ans <<= 1;
        ans += n & 1;
        n >>= 1;
    }
    return ans;
}

//191. Number of 1 Bits
//初解 runtime beats:100.00% memory beats:97.21%
int hammingWeight(uint32_t n) {
    unsigned char ans = 0;
    while (n) {
        ans += n & 1;
        n >>= 1;
    }
    return ans;
}

//198. House Robber
//初解 runtime beats:100.00% memory beats:95.05%
//int rob(std::vector<int>& nums) {
//    int size = nums.size();
//    if (size == 0)
//        return 0;
//    else if (size == 1)
//        return nums[0];
//    else if (size > 3)
//        nums[2] += nums[0];
//
//    for (int i = 3; i < size; i++)
//        nums[i] += std::max(nums[i - 2], nums[i - 3]);
//
//    return std::max(nums[size - 1], nums[size - 2]);
//}

//199. Binary Tree Right Side View
//初解 runtime beats:80.47% memory beats:11.44%
std::vector<int> rightSideView(TreeNode* root) {
    if (!root)
        return {};
    std::vector<int> ans;
    //BFS
    std::queue<TreeNode*> q1, q2;
    q1.push(root);
    ans.push_back(root->val);

    while (!q1.empty()) {
        TreeNode* tmp = q1.front();
        q1.pop();
        if (tmp->right)
            q2.push(tmp->right);

        if (tmp->left)
            q2.push(tmp->left);

        if (q1.empty() && !q2.empty()) {
            ans.push_back(q2.front()->val);
            while (!q2.empty()) {
                tmp = q2.front();
                q2.pop();
                q1.push(tmp);
            }
        }
    }

    return ans;
}

//二解 runtime beats:80.47% memory beats:51.17%
void rightSideView_DFS(TreeNode* node, std::vector<int>& ans, int& level) {
    if (ans.size() <= level) {
        ans.push_back(node->val);
    }

    if (node->right) {
        level += 1;
        rightSideView_DFS(node->right, ans, level);
        level -= 1;
    }

    if (node->left) {
        level += 1;
        rightSideView_DFS(node->left, ans, level);
        level -= 1;
    }
}

std::vector<int> rightSideView_2(TreeNode* root) {
    if (!root)
        return {};
    std::vector<int> ans;
    int level = 0;
    rightSideView_DFS(root, ans, level);
    return ans;
}

//200. Number of Islands
//初解 runtime beats:89.97% memory beats:71.50%
void numIslands_helper(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& DP, int i, int j) {
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size())
        return;

    if (grid[i][j] == '0') {
        DP[i][j] = false;
        return;
    }
    else {
        if (DP[i][j]) {
            DP[i][j] = false;
            numIslands_helper(grid, DP, i + 1, j);
            numIslands_helper(grid, DP, i, j + 1);
            numIslands_helper(grid, DP, i - 1, j);
            numIslands_helper(grid, DP, i, j - 1);
        }
    }
}

int numIslands(std::vector<std::vector<char>>& grid) {
    int ans = 0;
    int h = grid.size();
    if (h == 0)
        return ans;
    int w = grid[0].size();
    std::vector<std::vector<bool>> DP(h, std::vector<bool>(w, true));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (DP[i][j] && grid[i][j] == '1') {
                ans++;
                numIslands_helper(grid, DP, i, j);
            }
        }
    }

    return ans;
}

//201. Bitwise AND of Numbers Range
//初解 runtime beats:05.04% memory beats:98.73%
int rangeBitwiseAnd(long m, long n) {
    if (m == 0)
        return 0;
    int ans = m;
    while ((++m) <= n) {
        ans &= m;
        if (ans == 0)
            return 0;
    }

    return ans;
}

//https://www.cnblogs.com/grandyang/p/4431646.html
//網解 runtime beats:67.96% memory beats:61.70%
int rangeBitwiseAnd_network(int m, int n) {
    unsigned int d = INT_MAX;
    while ((m & d) != (n & d))
        d <<= 1;
    return m & d;
}

//202. Happy Number
//初解 runtime beats:63.86%  memory beats:33.09%
bool isHappy(int n) {
    std::set<int> exist;
    exist.insert(n);
    int tmp = 0;
    while (n != 1 || tmp != 0) {
        tmp += std::pow(n % 10, 2);
        n /= 10;
        if (n == 0 && tmp != 0) {
            n = tmp;
            if (!exist.count(n))
                exist.insert(n);
            else
                return false;
            tmp = 0;
        }            
    }

    return true;
}

//網解 runtime beats:100.00%  memory beats:77.58%
int isHappy_next(int n) {
    int res = 0;
    while (n > 0) {
        int sum = n % 10;
        res += (sum * sum);
        n /= 10;
    }
    return res;
}

bool isHappy_network(int n) {
    int slow = n, fast = n; //利用快慢指針，當快慢指針相同時，代表一定會陷入迴圈
    while (true) {
        slow = isHappy_next(slow);
        fast = isHappy_next(fast);
        fast = isHappy_next(fast);
        if (slow == fast)break;
    }
    return slow == 1;
}

//203. Remove Linked List Elements
//初解 runtime beats:91.80%  memory beats:59.93%
ListNode* removeElements(ListNode* head, int val) {
    while (head && head->val == val)
        head = head->next;
    if (!head)
        return head;
    ListNode* pre = head;
    ListNode* cur = pre->next;
    while (cur) {
        if (cur->val == val) {
            while (cur && cur->val == val)
                cur = cur->next;
            pre->next = cur;
        }
        else {
            pre = pre->next;
            cur = pre->next;
        }
    }
    return head;
}

//204. Count Primes
//https://www.cnblogs.com/grandyang/p/4462810.html
//網解 runtime beats:91.80%  memory beats:59.93%
int countPrimes_network(int n) {
    //埃拉托斯特尼篩法
    //https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
    int res = 0;
    std::vector<bool> prime(n, true);
    for (int i = 2; i < n; ++i) {
        if (!prime[i])
            continue;
        ++res;
        for (int j = 2; i * j < n; ++j)
            prime[i * j] = false;
    }
    return res;
}

//205. Isomorphic Strings
//https://www.cnblogs.com/grandyang/p/4465779.html
//網解 runtime beats:99.46%  memory beats:70.87%
bool isIsomorphic(std::string s, std::string t) {
    //s跟t中的各字元存在1對1映射之關係
    int m1[256] = { 0 }, m2[256] = { 0 }, n = s.size();
    for (int i = 0; i < n; ++i) {
        if (m1[s[i]] != m2[t[i]])   
            return false;
        //在m1,m2中要記錄出現的位置
        //為了與初始值0做區隔，所以+1
        m1[s[i]] = i + 1;
        m2[t[i]] = i + 1;
    }
    return true;
}

//206. Reverse Linked List
//初解 runtime beats:96.55%  memory beats:66.14%
ListNode* reverseList(ListNode* head) {
    ListNode* pre = NULL;
    ListNode* cur = head;
    while (cur) {
        ListNode* next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }

    return pre;
}

//207. Course Schedule
//https://www.cnblogs.com/grandyang/p/4484571.html
//網解 runtime beats:89.64%  memory beats:65.09%
bool canFinish(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    //建立有向圖
    std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
    std::vector<int> in(numCourses);    //紀錄indegree，in[1]代表說從1->x
    for (auto a : prerequisites) {
        graph[a[1]].push_back(a[0]);
        ++in[a[0]];
    }
    std::queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (in[i] == 0)     //代表說沒有前置條件即可修的課程
            q.push(i);

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (auto a : graph[t]) {           //在有向圖graoh中，t滿足a
            --in[a];                        //所以--a，因為也許a的前置條件不只t
            if (in[a] == 0) q.push(a);      //若a滿足則push至q
        }
    }

    for (int i = 0; i < numCourses; ++i)
        if (in[i] != 0) return false;

    return true;
}

//208. Implement Trie (Prefix Tree)
//初解 runtime beats:06.47%  memory beats:96.70%
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        trie_set.clear();
        trie_splt_set.clear();
    }

    /** Inserts a word into the trie. */
    void insert(std::string word) {
        trie_set.insert(word);

        std::string c_m = "";
        for (auto c : word) {
            c_m += c;
            trie_splt_set.insert(c_m);
        }            
    }

    /** Returns if the word is in the trie. */
    bool search(std::string word) {
        return trie_set.count(word);
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix) {
        return trie_splt_set.count(prefix);
    }

private:
    std::set<std::string> trie_set;
    std::set<std::string> trie_splt_set;
};

//網解 runtime beats:99.09%  memory beats:51.04%
class Trie_network {
    struct Trienode {
        char val;
        int count;
        int endsHere;
        Trienode* child[26];
    };
    Trienode* root;

    Trienode* getNode(int index) {
        Trienode* newnode = new Trienode;
        newnode->val = 'a' + index;
        newnode->count = newnode->endsHere = 0;
        for (int i = 0; i < 26; ++i)
            newnode->child[i] = NULL;
        return newnode;
    }
public:
    /** Initialize your data structure here. */
    Trie_network() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        root = getNode('/' - 'a');
    }

    /** Inserts a word into the trie. */
    void insert(std::string word) {
        Trienode* curr = root;
        int index;
        for (int i = 0; word[i] != '\0'; ++i) {
            index = word[i] - 'a';
            if (curr->child[index] == NULL)
                curr->child[index] = getNode(index);
            curr->child[index]->count += 1;
            curr = curr->child[index];
        }
        curr->endsHere += 1;
    }

    /** Returns if the word is in the trie. */
    bool search(std::string word) {
        Trienode* curr = root;
        int index;
        for (int i = 0; word[i] != '\0'; ++i)
        {
            index = word[i] - 'a';
            if (curr->child[index] == NULL)
                return false;
            curr = curr->child[index];
        }
        return (curr->endsHere > 0);
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string prefix) {
        Trienode* curr = root;
        int index;
        for (int i = 0; prefix[i] != '\0'; ++i)
        {
            index = prefix[i] - 'a';
            if (curr->child[index] == NULL)
                return false;
            curr = curr->child[index];
        }
        return (curr->count > 0);
    }
};

//209. Minimum Size Subarray Sum
//初解 runtime beats:05.02%  memory beats:66.44%
int minSubArrayLen(int s, std::vector<int>& nums) {
    int size = nums.size();
    if (size == 0)
        return 0;
    int ans = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (nums[i] >= s)
            return 1;
        
        for (int j = i + 1; j < size; j++) {
            nums[i] += nums[j];
            if (nums[i] >= s) {
                ans = std::min(ans, j - i + 1);
                j = size;
            }
        }
    }

    if (ans == INT_MAX)
        return 0;
    else
        return ans;
}

//https://www.cnblogs.com/grandyang/p/4501934.html
//網解 runtime beats:84.79%  memory beats:63.96%
int minSubArrayLen_network(int s, std::vector<int>& nums) {
    if (nums.empty()) return 0;
    int left = 0, right = 0, sum = 0, len = nums.size(), res = len + 1;
    while (right < len) {
        while (sum < s && right < len) {
            sum += nums[right++];
        }
        while (sum >= s) {
            res = std::min(res, right - left);
            sum -= nums[left++];
        }
    }
    return res == len + 1 ? 0 : res;
}

//210. Course Schedule II
//初解 runtime beats:91.10%  memory beats:54.85%
std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites) {
    std::vector<int> ans;
    //BFS
    //建立有向圖
    std::vector<std::vector<int>> graph(numCourses, std::vector<int>());
    std::vector<int> in(numCourses);    //紀錄indegree，in[1]代表說從1->x
    for (auto a : prerequisites) {
        graph[a[1]].push_back(a[0]);
        ++in[a[0]];
    }

    std::queue<int> q;
    for (int i = 0; i < numCourses; ++i)
        if (in[i] == 0)     //代表說沒有前置條件即可修的課程
            q.push(i);

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        ans.push_back(t);                   //修t課程
        for (auto a : graph[t]) {           //在有向圖graoh中，t滿足a
            --in[a];                        //所以--a，因為也許a的前置條件不只t
            if (in[a] == 0) q.push(a);      //若a滿足則push至q
        }
    }

    if (ans.size() == numCourses)           //若修行課程數量與課程數量一致代表課程已全數修讀
        return ans;
    else
        return {};
}

//211. Design Add and Search Words Data Structure
//初解 runtime beats:99.80%  memory beats:77.46%
class WordDictionary {

private:
    struct Trienode {
        char val;
        int count;
        int endsHere;
        Trienode* child[26];
    };
    Trienode* root = NULL;

    Trienode* getNode(int index) {
        Trienode* newnode = new Trienode;
        newnode->val = 'a' + index;
        newnode->count = newnode->endsHere = 0;
        for (int i = 0; i < 26; ++i)
            newnode->child[i] = NULL;
        return newnode;
    }

    bool search_DFS(Trienode* curr, std::string& word, int i) {
        if (i == word.size())
            return (curr->endsHere > 0);
        int index = 0;
        if (word[i] == '.') {
            for (index = 0; index < 26; index++) {
                if (curr->child[index] != NULL)
                    if (search_DFS(curr->child[index], word, i + 1))
                        return true;
            }
            return false;
        }

        index = word[i] - 'a';
        if (curr->child[index] == NULL)
            return false;
        return search_DFS(curr->child[index], word, i + 1);
    }

public:
    /** Initialize your data structure here. */
    WordDictionary() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        root = getNode('/' - 'a');
    }

    /** Adds a word into the data structure. */
    void addWord(std::string word) {
        Trienode* curr = root;
        int index;
        for (int i = 0; word[i] != '\0'; ++i) {
            index = word[i] - 'a';
            if (curr->child[index] == NULL)
                curr->child[index] = getNode(index);
            curr->child[index]->count += 1;
            curr = curr->child[index];
        }
        curr->endsHere += 1;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(std::string word) {
        Trienode* curr = root;
        return search_DFS(root, word, 0);
    }
};

//212. Word Search II
//初解 runtime beats:05.00%  memory beats:99.23%
std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
    std::vector<std::string> ans;

    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[0].size(); j++)
            for (int p = 0; p < words.size(); p++) {
                if (exist(board, i, j, words[p], 0)) {
                    ans.push_back(words[p]);
                    words.erase(words.begin() + p);
                    p--;
                }
            }
    return ans;
}

//網解 runtime beats:99.37%  memory beats:79.11%
class findWords_netword_Solution {
public:
    std::vector<std::string> findWords_network(std::vector<std::vector<char>>& board, std::vector<std::string>& words) {
        std::vector<std::string> res;
        if (board.empty() || board[0].empty() || words.empty()) return res;
        auto root = buildTrie(words);
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                dfs(board, words, res, root, i, j);
            }
        }
        return res;
    }

private:
    struct TrieNode {
        TrieNode* next[26] = { nullptr };
        int wordIdx;

        TrieNode() {
            for (auto& n : next) n = nullptr;
            wordIdx = -1;
        }
    };

    TrieNode* buildTrie(std::vector<std::string>& words) {
        auto root = new TrieNode();
        for (int i = 0; i < words.size(); ++i) {
            TrieNode* node = root;
            for (char c : words[i]) {
                c -= 'a';
                if (!node->next[c]) node->next[c] = new TrieNode();
                node = node->next[c];
            }
            node->wordIdx = i;
        }
        return root;
    }

    void dfs(std::vector<std::vector<char>>& board, std::vector<std::string>& words, std::vector<std::string>& res, TrieNode* node, int i, int j) {
        char c = board[i][j];
        if (c == '#' || !node->next[c - 'a']) return;
        node = node->next[c - 'a'];
        if (node->wordIdx != -1) {
            res.push_back(words[node->wordIdx]);
            node->wordIdx = -1;
        }

        board[i][j] = '#';
        if (i > 0) dfs(board, words, res, node, i - 1, j);
        if (i < board.size() - 1) dfs(board, words, res, node, i + 1, j);
        if (j > 0) dfs(board, words, res, node, i, j - 1);
        if (j < board[0].size() - 1) dfs(board, words, res, node, i, j + 1);
        board[i][j] = c;
    }
};

//213.213. House Robber II
//https://www.cnblogs.com/grandyang/p/4518674.html
//網解 runtime beats:52.12%  memory beats:11.18%
int rob2_helper(std::vector<int>& nums, int left, int right) {
    if (right - left <= 1)
        return nums[left];
    std::vector<int> dp(right, 0);
    dp[left] = nums[left];
    dp[left + 1] = std::max(nums[left], nums[left + 1]);
    for (int i = left + 2; i < right; ++i)
        dp[i] = std::max(nums[i] + dp[i - 2], dp[i - 1]);

    return dp.back();
}

int rob2_network(std::vector<int>& nums) {
    if (nums.size() <= 1)
        return nums.empty() ? 0 : nums[0];

    return std::max(rob2_helper(nums, 0, nums.size() - 1), rob2_helper(nums, 1, nums.size()));
}

//215. Kth Largest Element in an Array
//初解 runtime beats:68.83%  memory beats:99.06%
int findKthLargest(std::vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() - k];
}

//216. Combination Sum III
//初解 runtime beats:100.00%  memory beats:97.35%
void combinationSum3_helper(std::vector<std::vector<int>>& ans, std::vector<int>& sub_ans, int& sum, int start, int& k, int& n) {
    if (sub_ans.size() == k && sum == n) {
        ans.push_back(sub_ans);
        return;
    }

    for (int i = start; i < 10; i++) {
        sub_ans.push_back(i);
        sum += i;
        combinationSum3_helper(ans, sub_ans, sum, i + 1, k, n);
        sum -= i;
        sub_ans.pop_back();
    }
}

std::vector<std::vector<int>> combinationSum3(int k, int n) {
    std::vector<std::vector<int>> ans;
    std::vector<int> sub_ans;
    int sum = 0;
    combinationSum3_helper(ans, sub_ans, sum, 1, k, n);
    return ans;
}

//217. Contains Duplicate
//初解 runtime beats:19.48%  memory beats:93.68%
bool containsDuplicate(std::vector<int>& nums) {
    if (nums.size() < 2)
        return false;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 1; i++)
        if (nums[i] == nums[i + 1])
            return true;

    return false;
}

//二解 runtime beats:74.18%  memory beats:60.41%
bool containsDuplicate_2(std::vector<int>& nums) {
    if (nums.size() < 2)
        return false;
    
    std::unordered_set<int> once;
    for (auto num : nums)
        if (once.count(num) != 0)
            return true;
        else
            once.insert(num);

    return false;
}

//221. Maximal Square
//網解 runtime beats:96.40%  memory beats:94.70%
int maximalSquare(std::vector<std::vector<char>>& matrix) {
    int result = 0;
    for (int i = 1; i < matrix.size(); i++)
        for (int j = 1; j < matrix[0].size(); j++)
            //邏輯：m[i][j]是'1'且左上，上，左皆非'0'，即形成一正方形
            if (matrix[i][j] == '1' && matrix[i - 1][j - 1] > '0' && matrix[i][j - 1] > '0' && matrix[i - 1][j] > '0') {
                int mini = std::min(std::min(matrix[i - 1][j - 1], matrix[i][j - 1]), matrix[i - 1][j]);
                matrix[i][j] = mini + 1;
            }

    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[0].size(); j++)
            result = std::max((matrix[i][j] - '0') * (matrix[i][j] - '0'), result);

    return result;
}

//222. Count Complete Tree Nodes
//初解 runtime beats:21.84%  memory beats:06.75%
int countNodes(TreeNode* root) {
    if (!root)
        return 0;
    std::queue<TreeNode*> wait;
    wait.push(root);
    int ans = 0;
    while (!wait.empty()) {
        ans++;
        root = wait.front();
        wait.pop();
        if (root->left)
            wait.push(root->left);
        if (root->right)
            wait.push(root->right);
    }
    return ans;
}

//二解 runtime beats:41.45%  memory beats:65.02%
void countNodes_DFS(TreeNode* node, int& ans) {
    if (!node)
        return;
    ans++;
    countNodes_DFS(node->left, ans);
    countNodes_DFS(node->right, ans);
}

int countNodes_2(TreeNode* root) {
    int ans = 0;
    countNodes_DFS(root, ans);
    return ans;
}

//226. Invert Binary Tree
//初解 runtime beats:100.00%  memory beats:81.89%
void invertTree_DFS(TreeNode* node) {
    if (!node)
        return;

    TreeNode* tmp = node->left;
    node->left = node->right;
    node->right = tmp;
    invertTree_DFS(node->left);
    invertTree_DFS(node->right);
}

//227. Basic Calculator II
//網解 runtime beats:93.43%  memory beats:98.14%
int calculate(std::string s) {
    int temp = 0, sum = 0;
    char sign = '+';
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (isdigit(c))
            num = (num * 10) + (c - '0');
        if (!isdigit(c) && c != ' ' || i == s.length() - 1) {
            if (sign == '+') {
                sum += temp;
                temp = num;
            }
            else if (sign == '-') {
                sum += temp;
                temp = -num;
            }
            else if (sign == '/') {
                temp /= num;
            }
            else if (sign == '*') {
                temp *= num;
            }
            sign = c;
            num = 0;
        }
    }
    sum += temp;
    return sum;
}

//https://www.cnblogs.com/grandyang/p/4601208.html
//網解 runtime beats:52.04%  memory beats:48.44%
int calculate_network(std::string s) {
    long res = 0, num = 0, n = s.size();
    char op = '+';
    std::stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] >= '0')
            num = num * 10 + s[i] - '0';
        if ((s[i] < '0' && s[i] != ' ') || i == n - 1) {
            if (op == '+') st.push(num);
            if (op == '-') st.push(-num);
            if (op == '*' || op == '/') {
                int tmp = (op == '*') ? st.top() * num : st.top() / num;
                st.pop();
                st.push(tmp);
            }
            op = s[i];
            num = 0;
        }
    }
    while (!st.empty()) {
        res += st.top();
        st.pop();
    }
    return res;
}

TreeNode* invertTree(TreeNode* root) {
    invertTree_DFS(root);
    return root;
}

//229. Majority Element II
//初解 runtime beats:35.40%  memory beats:38.24%
std::vector<int> majorityElement2(std::vector<int>& nums) {
    std::set<int> ans;
    std::unordered_map<int, int> exist;
    int a = nums.size() / 3;
    for (auto num : nums) {
        exist[num]++;
        if (exist[num] > a)
            ans.insert(num);
    }

    return { ans.begin(), ans.end() };
}

//https://www.cnblogs.com/grandyang/p/4606822.html
//網解 runtime beats:35.61%  memory beats:36.90%
std::vector<int> majorityElement2_network(std::vector<int>& nums) {
    std::vector<int> res;
    int a = 0, b = 0, cnt1 = 0, cnt2 = 0, n = nums.size();
    for (int num : nums) {
        if (num == a) ++cnt1;
        else if (num == b) ++cnt2;
        else if (cnt1 == 0) { a = num; cnt1 = 1; }
        else if (cnt2 == 0) { b = num; cnt2 = 1; }
        else { --cnt1; --cnt2; }
    }
    cnt1 = cnt2 = 0;
    for (int num : nums) {
        if (num == a) ++cnt1;
        else if (num == b) ++cnt2;
    }
    if (cnt1 > n / 3) res.push_back(a);
    if (cnt2 > n / 3) res.push_back(b);
    return res;
}

//230. Kth Smallest Element in a BST
//初解 runtime beats:76.14%  memory beats:80.97%
void kthSmallest_helper(TreeNode* node, int& k, int& ans) {
    if (!node || k == 0)
        return;

    kthSmallest_helper(node->left, k, ans);
    k--;
    if (k == 0)
        ans = node->val;
    kthSmallest_helper(node->right, k, ans);
}

int kthSmallest(TreeNode* root, int k) {
    int ans = root->val;
    kthSmallest_helper(root, k, ans);
    return ans;
}

//231. Power of Two
//初解 runtime beats:100.00%  memory beats:68.20%
bool isPowerOfTwo(int n) {
    if (n == 1)
        return true;
    long a = 2;

    while (a < n)
        a *= 2;

    if (a == n)
        return true;
    else
        return false;
}

//二解 runtime beats:100.00%  memory beats:20.26%
bool isPowerOfTwo_2(int n) {
    if (n == 0)
        return false;
    else if (n == 1 || n == 2)
        return true;

    if (n % 2 == 0)
        return isPowerOfTwo(n / 2);
    else
        return false;
}

//232. Implement Queue using Stacks
//初解 runtime beats:100.00%  memory beats:78.63%
class MyQueue {
private:
    std::stack<int> st;
public:
    /** Initialize your data structure here. */
    MyQueue() {
        while (!st.empty())
            st.pop();
    }

    /** Push element x to the back of queue. */
    void push(int x) {
        std::stack<int> tmp;
        while (!st.empty()) {
            tmp.push(st.top());
            st.pop();
        }
        tmp.push(x);
        while (!tmp.empty()) {
            st.push(tmp.top());
            tmp.pop();
        }
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int top = st.top();
        st.pop();
        return top;
    }

    /** Get the front element. */
    int peek() {
        return st.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return st.empty();
    }
};

//234. Palindrome Linked List
//初解 runtime beats:42.50%   memory beats:14.12%
bool isPalindrome(ListNode* head) {
    std::vector<ListNode*> list;
    while (head) {
        list.push_back(head);
        head = head->next;
    }

    for (int i = 0; i < (list.size() / 2); i++) {
        if (list[i]->val != list[list.size() - 1 - i]->val)
            return false;
    }
    return true;
}

//網解 runtime beats:88.70%  memory beats:94.21%
bool isPalindrome_network(ListNode* head) {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr);
    int count = 0;
    if (!head || !head->next)
        return true;
    ListNode* r1 = head, * r2 = head->next;
    while (r1 && r2) {
        r1 = r1->next;
        r2 = r2->next;
        if (r2)
            r2 = r2->next;
        count++;
    }
    ListNode* halfRev = reverseList(r1);
    r1 = head;
    for (int i = 0; i < count; i++) {
        if (halfRev->val ^ r1->val)
            return false;
        halfRev = halfRev->next;
        r1 = r1->next;
    }
    return true;
}

//https://www.cnblogs.com/grandyang/p/4635425.html
//網解 runtime beats:68.16%   memory beats:48.67%
bool isPalindrome_network_2(ListNode* head) {
    if (!head || !head->next) 
        return true;
    //利用快慢指針找到一半
    ListNode* slow = head, * fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* last = slow->next, * pre = head;

    while (last->next) {
        ListNode* tmp = last->next;
        last->next = tmp->next;
        tmp->next = slow->next;
        slow->next = tmp;
    }

    while (slow->next) {
        slow = slow->next;
        if (pre->val != slow->val) return false;
        pre = pre->next;
    }
    return true;
}

//235. Lowest Common Ancestor of a Binary Search Tree
//初解 runtime beats:94.34%   memory beats:05.11%
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val > q->val)
        return lowestCommonAncestor(root, q, p);

    if (root->val < p->val)
        return lowestCommonAncestor(root->right, p, q);
    else if (root->val > q->val)
        return lowestCommonAncestor(root->left, p, q);
    
    return root;
}

//236. Lowest Common Ancestor of a Binary Tree
//https://www.cnblogs.com/grandyang/p/4641968.html.
//網解 runtime beats:43.40%   memory beats:26.75%
TreeNode* lowestCommonAncestor_network(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || p == root || q == root)
        return root;

    TreeNode* left = lowestCommonAncestor_network(root->left, p, q);
    TreeNode* right = lowestCommonAncestor_network(root->right, p, q);
    if (left && right) 
        return root;
    return left ? left : right;
}

//網解 runtime beats:89.35%   memory beats:78.78%
TreeNode* lowestCommonAncestor_network_2(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || p == root || q == root)
        return root;
    TreeNode* left = lowestCommonAncestor_network_2(root->left, p, q);
    if (left && left != p && left != q)
        return left;
    TreeNode* right = lowestCommonAncestor_network_2(root->right, p, q);
    if (left && right)
        return root;

    return left ? left : right;
}

//238. Product of Array Except Self
//初解 runtime beats:38.57%   memory beats:32.62%
std::vector<int> productExceptSelf(std::vector<int>& nums) {
    //參考題目solution
    int size = nums.size();
    std::vector<int> L(size, 1), R(size, 1);
    int i = 0;

    for (i = 1; i < size; i++)
        L[i] = L[i - 1] * nums[i - 1];

    for (i = size - 2; i >= 0; i--)
        R[i] = R[i + 1] * nums[i + 1];

    for (i = 0; i < size; i++)
        nums[i] = L[i] * R[i];

    return nums;
}

//二解 runtime beats:85.81%  memory beats:57.38%
std::vector<int> productExceptSelf_2(std::vector<int>& nums) {
    //參考題目solution
    int size = nums.size();
    std::vector<int> ans(size, 1);
    int i = 0;
    for (i = 1; i < size; i++)
        ans[i] = ans[i - 1] * nums[i - 1];
    int right = 1;
    for (i = size - 1; i >= 0; i--) {
        ans[i] *= right;
        right *= nums[i];
    }

    return ans;
}

//239. Sliding Window Maximum
//初解 runtime beats:05.23%   memory beats:05.08%
std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    int size = nums.size();
    if (size < k)
        return {};
    std::vector<int> ans;
    std::multiset<int> max;
    int i = 0;
    for (i = 0; i < k; i++)
        max.insert(nums[i]);
    
    if(!max.empty())
        ans.push_back(*(--max.end()));

    for (i = k; i < nums.size(); i++) {
        max.insert(nums[i]);
        max.erase(max.find(nums[i - k]));
        ans.push_back(*(--max.end()));
    }

    return ans;
}

//網解 runtime beats:43.48%   memory beats:99.77%
std::vector<int> maxSlidingWindow_network(std::vector<int>& nums, int k) {
    if (k == 0)
        return nums;

    if (nums.size() == 0 || nums.size() < k)
        return {};

    int n = nums.size();
    std::vector<int> result(n - k + 1);
    int maxVal = INT_MIN;
    int maxId = -1;
    for (int i = 0; i < k; i++) {
        if (maxVal < nums[i]) {
            maxId = i;
            maxVal = nums[i];
        }
    }
    result[0] = maxVal;
    for (int i = 1; i < (n - k + 1); i++) {
        if (i <= maxId) {
            if (maxVal < nums[i + k - 1]) {
                maxId = i + k - 1;
                maxVal = nums[i + k - 1];
            }
        }
        else {
            maxVal = INT_MIN;
            maxId = -1;
            for (int j = i; j < (i + k); j++) {
                if (maxVal < nums[j]) {
                    maxId = j;
                    maxVal = nums[j];
                }
            }
        }
        result[i] = maxVal;
    }
    return result;
}

//https://www.cnblogs.com/grandyang/p/4656517.html
//網解 runtime beats:61.26% memory beats:69.87%
std::vector<int> maxSlidingWindow_network_2(std::vector<int>& nums, int k) {
    std::vector<int> res;
    std::deque<int> q;
    for (int i = 0; i < nums.size(); ++i) {
        if (!q.empty() && q.front() == i - k)
            q.pop_front();
        while (!q.empty() && nums[q.back()] < nums[i])
            q.pop_back();
        q.push_back(i);
        if (i >= k - 1)
            res.push_back(nums[q.front()]);
    }
    return res;
}

//240. Search a 2D Matrix II
//網解 runtime beats:99.02% memory beats:98.39%
bool searchMatrix2_network(std::vector<std::vector<int>>& matrix, int target) {
    std::ios::sync_with_stdio(0);
    if (matrix.size() == 1 && matrix[0].size() == 0)
        return false;

    while (matrix.size() != 0) {
        int temp = matrix[0][matrix[0].size() - 1];
        if (temp == target)
            return true;
        else if (temp > target) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i].pop_back();
                if (matrix[i].size() == 0)
                    matrix.erase(matrix.begin() + i);
            }
        }
        else
            matrix.erase(matrix.begin());
    }
    return false;
}

//初解 runtime beats:22.90% memory beats:97.06%
bool searchMatrix2(std::vector<std::vector<int>>& matrix, int target) {
    //從左下角往右或往上
    //從右上角往左或往下
    std::ios::sync_with_stdio(0);
    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;

    int i = matrix.size() - 1, j = 0;   //左下角
    while (i >= 0 && j < matrix[0].size() && matrix[i][j] != target) {
        if (matrix[i][j] < target)
            j++;    //比目標小，要往大的找
        else
            i--;
    }

    if (i < 0 || j >= matrix[0].size() || matrix[i][j] != target)
        return false;
    else
        return true;
}

//242. Valid Anagram
//初解 runtime beats:29.03% memory beats:45.12%
bool isAnagram(std::string s, std::string t) {
    if (s.size() != t.size())
        return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s == t;
}

//257. Binary Tree Paths
//初解 runtime beats:100.00% memory beats:38.29%
void binaryTreePaths_DFS(TreeNode* node, std::string Path, std::vector<std::string>& ans) {
    if (!node)
        return;
        
    if (!node->left && !node->right) {
        ans.push_back(Path + "->" + std::to_string(node->val));
        return;
    }

    binaryTreePaths_DFS(node->left, Path + "->" + std::to_string(node->val), ans);
    binaryTreePaths_DFS(node->right, Path + "->" + std::to_string(node->val), ans);
}

std::vector<std::string> binaryTreePaths(TreeNode* root) {
    if (!root)
        return {};

    std::vector<std::string> ans;
    if (!root->left && !root->right) {
        ans.push_back(std::to_string(root->val));
        return ans;
    }

    binaryTreePaths_DFS(root->left, std::to_string(root->val), ans);
    binaryTreePaths_DFS(root->right, std::to_string(root->val), ans);
    return ans;
}

//260. Single Number III
//初解 runtime beats:15.06% memory beats:05.16%
std::vector<int> singleNumber3(std::vector<int>& nums) {
    if (nums.size() < 3)
        return nums;
    
    std::multiset<int> mulst(nums.begin(), nums.end());
    std::vector<int> ans;

    for (auto num : nums) {
        if (mulst.count(num) == 1) {
            ans.push_back(num);
            if (ans.size() == 2)
                return ans;
        }            
    }

    return ans;
}

//網解 runtime beats:94.67% memory beats:98.06%
std::vector<int> singleNumber3_network(std::vector<int>& nums) {
    sort(nums.begin(), nums.end());
    std::vector<int> vc;
    for (int i = 0; i < nums.size() - 1; i++) {
        if (nums[i] != nums[i + 1])
            vc.push_back(nums[i]);
        else
            i++;
    }
    if (nums.size() > 1 && nums[nums.size() - 1] != nums[nums.size() - 2])
        vc.push_back(nums[nums.size() - 1]);
    return vc;
}

//264. Ugly Number II
//網解 runtime beats:97.58% memory beats:62.44%
int nthUglyNumber_network(int n) {
    std::vector<int> dp(n, 0);
    dp[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;
    int n2 = 2, n3 = 3, n5 = 5;
    for (int i = 1; i < n; i++) {
        int next = std::min(n2, std::min(n3, n5));
        dp[i] = next;
        if (next == n2) {
            i2++;
            n2 = dp[i2] * 2;
        }
        if (next == n3) { i3++; n3 = dp[i3] * 3; }
        if (next == n5) { i5++; n5 = dp[i5] * 5; }
    }
    return dp.back();
}

//278. First Bad Version
//網解 runtime beats:100.00% memory beats:54.89%
bool isBadVersion(int version) {
    if (version >= 4)
        return true;
    else
        return false;
}

int firstBadVersion(int n) {
    int first = 1;
    while (first <= n) {
        int mid = first + (n - first) / 2;
        bool isBad = isBadVersion(mid);
        if (isBad && !isBadVersion(mid - 1))
            return mid;

        if (!isBad)
            first = mid + 1;
        else
            n = mid;
    }
    return -1;
}

//279. Perfect Squares
//https://www.cnblogs.com/grandyang/p/4800552.html
//網解 runtime beats:100.00% memory beats:99.53%
int numSquares(int n) {
    while (n % 4 == 0) n /= 4;
    if (n % 8 == 7) return 4;
    for (int a = 0; a * a <= n; ++a) {
        int b = sqrt(n - a * a);
        if (a * a + b * b == n) {
            return !!a + !!b;
        }
    }
    return 3;
}

//283. Move Zeroes
//初解 runtime beats:58.98% memory beats:57.69%
void moveZeroes(std::vector<int>& nums) {
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
        if (*it == 0) {
            nums.erase(--(it.base()));
            nums.push_back(0);
        }
    }
}

//網解 runtime beats:99.69% memory beats:73.38%
void moveZeroes_network(std::vector<int>& nums) {
    int i = 0;
    for (int j = 0; j < nums.size(); j++) {
        if (nums[j] != 0) {
            nums[i] = nums[j];
            i++;
        }
    }
    while (i < nums.size()) {
        nums[i] = 0;
        i++;
    }
}

//287. Find the Duplicate Number
//初解 runtime beats:17.68% memory beats:12.39%
int findDuplicate(std::vector<int>& nums) {
    std::set<int> exist;
    for (auto num : nums) {
        if (exist.count(num) > 0)
            return num;
        else
            exist.insert(num);
    }
    return 0;
}

//https://www.cnblogs.com/grandyang/p/4843654.html
//網解 runtime beats:97.43% memory beats:71.57%
int findDuplicate_network(std::vector<int>& nums) {
    int slow = 0, fast = 0, t = 0;
    while (true) {              //設true因為slow跟fast初始數值一致
        slow = nums[slow];
        fast = nums[nums[fast]];
        if (slow == fast) break;
    }
    while (true) {
        slow = nums[slow];
        t = nums[t];
        if (slow == t) break;
    }
    return slow;
}

//289. Game of Life
//初解 runtime beats:100.00% memory beats:11.67%
void gameOfLife(std::vector<std::vector<int>>& board) {
    //https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
    //Remember that the board needs to be updated at the same time
    int x_size = board.size();
    if (x_size == 0)
        return;
    int y_size = board[0].size();
    std::vector<std::vector<int>> world(x_size + 2, std::vector<int>(y_size + 2, 0));

    int i, j, alive;
    for (i = 0; i < x_size; i++)
        for (j = 0; j < y_size; j++)
            world[i + 1][j + 1] = board[i][j];

    for (i = 1; i < x_size + 1; i++)
        for (j = 1; j < y_size + 1; j++) {
            alive = world[i - 1][j - 1] + world[i - 1][j] + world[i - 1][j + 1] +
                world[i][j - 1] + world[i][j + 1] +
                world[i + 1][j - 1] + world[i + 1][j] + world[i + 1][j + 1];
            if (alive == 3)
                board[i - 1][j - 1] = 1;
            else if (alive > 3 || alive < 2)
                board[i - 1][j - 1] = 0;
        }
}

//https://www.cnblogs.com/grandyang/p/4854466.html
//網解 runtime beats:100.00% memory beats:27.99%
void gameOfLife_network(std::vector<std::vector<int> >& board) {
    int m = board.size(), n = m ? board[0].size() : 0;
    std::vector<int> dx{ -1, -1, -1, 0, 1, 1, 1, 0 };
    std::vector<int> dy{ -1, 0, 1, 1, 1, 0, -1, -1 };
    //概念為因為要in-place，所以將細胞變化可能列出，所以就算狀態改變還是會知道身前是死是活
    //狀態0:死轉死
    //狀態1:活轉活
    //狀態2:活轉死
    //狀態3:死轉活
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int cnt = 0;
            for (int k = 0; k < 8; ++k) {
                int x = i + dx[k], y = j + dy[k];
                if (x >= 0 && x < m && y >= 0 && y < n && (board[x][y] == 1 || board[x][y] == 2))
                    ++cnt;
            }
            if (board[i][j] && (cnt < 2 || cnt > 3))
                board[i][j] = 2;                //2表示狀態2->活轉死
            else if (!board[i][j] && cnt == 3)
                board[i][j] = 3;                //狀態3->死轉活
        }
    }
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            board[i][j] %= 2;
}

//290. Word Pattern
//初解 runtime beats:100.00% memory beats:05.04%
bool wordPattern(std::string pattern, std::string str) {
    str += " ";
    std::unordered_map<char, std::string> map1;
    std::unordered_map<std::string, char> map2;
    int cut_p;
    std::string cut_s;
    for (char p : pattern) {
        cut_p = str.find(' ');
        cut_s = str.substr(0, cut_p);
        if (cut_s == "")
            return false;

        if (map1[p] == "")
            map1[p] = cut_s;
        else
            if (map1[p] != cut_s)
                return false;

        if (!map2[cut_s])
            map2[cut_s] = p;
        else
            if (map2[cut_s] != p)
                return false;
        str = str.substr(cut_p + 1, str.size() - cut_p);
    }

    if (str == "")
        return true;
    else
        return false;
}

//網解 runtime beats:100.00% memory beats:05.04%
bool wordPattern_network(std::string pattern, std::string str) {
    std::vector<std::string> words;
    std::string token;
    std::stringstream ss(str);
    while (getline(ss, token, ' ')) 
        words.push_back(token);
    if (pattern.size() != words.size()) return false;
    for (int i = 0; i < words.size() - 1; i++)
    {
        for (int j = i + 1; j < words.size(); j++)
        {
            if (pattern[i] == pattern[j] and words[i] == words[j]) continue;
            else if (pattern[i] != pattern[j] and words[i] != words[j]) continue;
            else return false;
        }
    }
    return true;
}

//295. Find Median from Data Stream
//初解 runtime beats:05.12% memory beats:95.33%
class MedianFinder {
private:
    std::vector<int> nums;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        nums.clear();
    }

    void addNum(int num) {
        int posi = 0;
        while (posi < nums.size() && nums[posi] < num)
            posi++;
        nums.insert(nums.begin() + posi, num);
    }

    double findMedian() {
        int size = nums.size();
        if (size % 2 == 0)
            return (double)nums[size / 2 - 1] / 2.0 + (double)nums[size / 2] / 2.0;
        else
            return nums[size / 2];
    }
};

//網解 runtime beats:92.74% memory beats:32.95%
class MedianFinder_network {
public:
    /** initialize your data structure here. */
    std::priority_queue<int, std::vector<int>, std::greater<int>> upperHeap;
    std::priority_queue<int> lowerHeap;
    int total;
    MedianFinder_network() :total(0) {

    }

    inline void moveToAnother(bool toLower) {
        if (toLower) {
            int curtop = upperHeap.top();
            upperHeap.pop();
            lowerHeap.push(curtop);
        }
        else {
            int curtop = lowerHeap.top();
            lowerHeap.pop();
            upperHeap.push(curtop);
        }
    }

    void addNum(int num) {
        ++total;
        if (lowerHeap.size() == 0 || num <= lowerHeap.top())
            lowerHeap.push(num);
        else
            upperHeap.push(num);
        // rebalance heaps
        if ((total & 1) == 0) {
            if (lowerHeap.size() > upperHeap.size())
                moveToAnother(false);
            else if (lowerHeap.size() < upperHeap.size())
                moveToAnother(true);
        }
        else if ((int)lowerHeap.size() - (int)upperHeap.size() > 1)
            moveToAnother(false);
        else if ((int)upperHeap.size() - (int)lowerHeap.size() > 1)
            moveToAnother(true);
    }

    double findMedian() {
        if (total == 0)
            return 0;
        if (total == 1)
            return lowerHeap.top();

        if ((total & 1) == 0)
            return 1. * ((double)lowerHeap.top() + upperHeap.top()) / 2;
        else
            return (upperHeap.size() > lowerHeap.size()) ? upperHeap.top() : lowerHeap.top();
    }
};

//297. Serialize and Deserialize Binary Tree
//https://www.cnblogs.com/grandyang/p/4913869.html
//網解 runtime beats:92.88% memory beats:72.40%
class Codec_network {
public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::ostringstream out;
        serialize(root, out);
        return out.str();
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        std::istringstream in(data);
        return deserialize(in);
    }
private:
    void serialize(TreeNode* root, std::ostringstream& out) {
        if (root) {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        }
        else {
            out << "# ";
        }
    }
    TreeNode* deserialize(std::istringstream& in) {
        std::string val;
        in >> val;
        if (val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};

//300. Longest Increasing Subsequence
//初解 runtime beats:44.00% memory beats:73.52%
int lengthOfLIS(std::vector<int>& nums) {
    //參考Solution
    int size = nums.size();
    if (size == 0)
        return 0;
    int ans = 1;
    std::vector<int> DP(size, 1);
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i])
                DP[i] = std::max(DP[i], DP[j] + 1);
        ans = std::max(ans, DP[i]);
    }

    return ans;
}

//301. Remove Invalid Parentheses
//https://www.cnblogs.com/grandyang/p/4944875.html
//網解 runtime beats:39.74% memory beats:46.59%
bool InvalidParentheses(std::string t) {
    int cnt = 0;
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == '(') ++cnt;
        else if (t[i] == ')' && --cnt < 0) return false;
    }
    return cnt == 0;
}

std::vector<std::string> removeInvalidParentheses_network(std::string s) {
    std::vector<std::string> res;
    std::unordered_set<std::string> visited{ {s} };
    std::queue<std::string> q{ {s} };
    bool found = false;                 //用意為若有找到一組解，則不用在往下分解'('或')'
    while (!q.empty()) {
        s = q.front(); q.pop();
        if (InvalidParentheses(s)) {
            res.push_back(s);
            found = true;
        }

        if (found) continue;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != '(' && s[i] != ')') continue;
            std::string str = s.substr(0, i) + s.substr(i + 1);
            if (!visited.count(str)) {
                q.push(str);
                visited.insert(str);
            }
        }
    }
    return res;
}

//網解 runtime beats:100.00% memory beats:83.91%
void removeInvalidParentheses_helper(std::string s, int last_i, int last_j, std::vector<char> p, std::vector<std::string>& res) {
    //last_i : 當前遍歷位置
    //last_j : 上次刪除位置
    int cnt = 0;            //表示'('出現次數
    for (int i = last_i; i < s.size(); ++i) {
        if (s[i] == p[0]) ++cnt;
        else if (s[i] == p[1]) --cnt;
        if (cnt >= 0) continue;
        //在此迴圈時，')'數量大於'('，所以做完之後可以直接return，不用重複計算'('數量大於')'之情況
        //刪除多餘的')'
        for (int j = last_j; j <= i; ++j) {
            if (s[j] == p[1] && (j == last_j || s[j] != s[j - 1])) {
                removeInvalidParentheses_helper(s.substr(0, j) + s.substr(j + 1), i, j, p, res);
            }
        }
        return;
    }
    //此時可能'('數量大於')'
    //所以將s反轉後再次計算
    std::string rev = std::string(s.rbegin(), s.rend());
    if (p[0] == '(') removeInvalidParentheses_helper(rev, 0, 0, { ')', '(' }, res);
    else res.push_back(rev);
}

std::vector<std::string> removeInvalidParentheses(std::string s) {
    std::vector<std::string> res;
    removeInvalidParentheses_helper(s, 0, 0, { '(', ')' }, res);
    return res;
}

//304. Range Sum Query 2D - Immutable
//初解 runtime beats:83.63% memory beats:95.14%
class NumMatrix {
private:
    std::vector<std::vector<int>>* DP = nullptr;
public:
    NumMatrix(std::vector<std::vector<int>>& matrix) {
        if (DP)
            DP->clear();
        int size = matrix.size();
        if (size == 0)
            return;
        DP = new std::vector<std::vector<int>>(matrix.size() + 1, std::vector<int>(matrix[0].size() + 1, 0));
        for (int i = 0; i < matrix.size(); i++)
            for (int j = 0; j < matrix[0].size(); j++)
                (*DP)[i + 1][j + 1] = (*DP)[i][j + 1] + (*DP)[i + 1][j] - (*DP)[i][j] + matrix[i][j];
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if (DP == nullptr)
            return 0;
        return (*DP)[row2 + 1][col2 + 1] - (*DP)[row2 + 1][col1] - (*DP)[row1][col2 + 1] + (*DP)[row1][col1];
    }
};

//307. Range Sum Query - Mutable
//初解 runtime beats:05.36% memory beats:97.68%
class NumArray {
private:
    std::vector<int> DP;
public:
    NumArray(std::vector<int>& nums) {
        DP.clear();
        DP.resize(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++)
            DP[i + 1] = nums[i] + DP[i];
    }

    void update(int i, int val) {
        int deviation = DP[i + 1] - DP[i] - val;
        while (i < DP.size() - 1) {
            DP[i + 1] -= deviation;
            i++;
        }
    }

    int sumRange(int i, int j) {
        return DP[j + 1] - DP[i];
    }
};

//https://www.cnblogs.com/grandyang/p/4985506.html
//網解 runtime beats:34.01% memory beats:51.62%
class NumArray_network {
public:
    NumArray_network(std::vector<int> nums) {
        n = nums.size();
        tree.resize(n * 2);
        buildTree(nums);
    }

    void buildTree(std::vector<int>& nums) {
        for (int i = n; i < n * 2; ++i)
            tree[i] = nums[i - n];
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    void update(int i, int val) {
        tree[i += n] = val;
        while (i > 0) {
            tree[i / 2] = tree[i] + tree[i ^ 1];
            i /= 2;
        }
    }

    int sumRange(int i, int j) {
        int sum = 0;
        for (i += n, j += n; i <= j; i /= 2, j /= 2) {
            if ((i & 1) == 1) sum += tree[i++];
            if ((j & 1) == 0) sum += tree[j--];
        }
        return sum;
    }

private:
    int n;
    std::vector<int> tree;
};

//309. Best Time to Buy and Sell Stock with Cooldown
//https://www.cnblogs.com/grandyang/p/4997417.html
//網解 runtime beats:88.82% memory beats:82.96%
int maxProfit_Cooldown_network(std::vector<int>& prices) {
    int buy = INT_MIN, pre_buy = 0, sell = 0, pre_sell = 0;
    for (int price : prices) {
        pre_buy = buy;
        buy = std::max(pre_sell - price, pre_buy);
        pre_sell = sell;
        sell = std::max(pre_buy + price, pre_sell);
    }
    return sell;
}

//310. Minimum Height Trees
//https://www.cnblogs.com/grandyang/p/5000291.html
//網解 runtime beats:67.00% memory beats:30.85%
std::vector<int> findMinHeightTrees_network(int n, std::vector<std::vector<int>>& edges) {
    if (n == 1) return { 0 };
    std::vector<int> res;
    std::vector<std::unordered_set<int>> adj(n);
    std::queue<int> q;
    for (auto edge : edges) {
        adj[edge[0]].insert(edge[1]);
        adj[edge[1]].insert(edge[0]);
    }

    for (int i = 0; i < n; ++i)
        if (adj[i].size() == 1)
            q.push(i);

    while (n > 2) {
        int size = q.size();
        n -= size;
        for (int i = 0; i < size; ++i) {
            int t = q.front();
            q.pop();
            for (auto a : adj[t]) {
                adj[a].erase(t);
                if (adj[a].size() == 1)
                    q.push(a);
            }
        }
    }

    while (!q.empty()) {
        res.push_back(q.front());
        q.pop();
    }

    return res;
}

//312. Burst Balloons
//https://www.cnblogs.com/grandyang/p/5006441.html
//網解 runtime beats:42.15% memory beats:37.62%
int maxCoins_network(std::vector<int>& nums) {
    int n = nums.size();
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));
    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            for (int k = i; k <= j; ++k)
                dp[i][j] = std::max(dp[i][j], nums[i - 1] * nums[k] * nums[j + 1] + dp[i][k - 1] + dp[k + 1][j]);
        }
    }
    return dp[1][n];
}

//313. Super Ugly Number
//初解 runtime beats:74.24% memory beats:51.60%
int nthSuperUglyNumber(int n, std::vector<int>& primes) {
    //參考Ugly Number II
    std::vector<int> dp(n, 0);
    dp[0] = 1;
    std::vector<int> i_primes(primes.size(), 0);
    std::vector<int> n_primes(primes.begin(), primes.end());

    for (int i = 1; i < n; i++) {
        int next = *std::min_element(n_primes.begin(), n_primes.end());
        dp[i] = next;
        for (int j = 0; j < primes.size(); j++) {
            if (next == n_primes[j]) {
                i_primes[j]++;
                n_primes[j] = dp[i_primes[j]] * primes[j];
            }
        }
    }
    return dp.back();
}

//315. Count of Smaller Numbers After Self
//https://www.cnblogs.com/grandyang/p/5078490.html
//網解 runtime beats:19.68% memory beats:90.01%
std::vector<int> countSmaller_network(std::vector<int>& nums) {
    std::vector<int> t, res(nums.size());
    for (int i = nums.size() - 1; i >= 0; --i) {
        int left = 0, right = t.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (t[mid] >= nums[i]) right = mid;
            else left = mid + 1;
        }
        res[i] = right;
        t.insert(t.begin() + right, nums[i]);
    }
    return res;
}

//316. Remove Duplicate Letters
//https://www.cnblogs.com/grandyang/p/5085379.html
//網解 runtime beats:95.10% memory beats:70.99%
std::string removeDuplicateLetters(std::string s) {
    //解題思路為先計算每個字母出現次數
    //然後再次遍歷s，若c比res.back小則將visited[res.back]設為0，意思為尚未走訪，且必須符合res.back在後面還會出現，也就是m[res.back] > 0
    //為防止res若為空無法比較res.back，給予res初始值'0' = 48，因為'0'小於任何字母
    int m[256] = { 0 }, visited[256] = { 0 };   //m:統計每個字母出現次數, visited:紀錄每個字母是否被訪問過
    std::string res = "0";
    for (auto a : s)
        ++m[a];
    for (auto a : s) {
        --m[a];
        if (visited[a]) continue;
        while (a < res.back() && m[res.back()]) {
            visited[res.back()] = 0;
            res.pop_back();
        }
        res += a;
        visited[a] = 1;
    }
    return res.substr(1);
}

//318. Maximum Product of Word Lengths
//https://www.cnblogs.com/grandyang/p/5090058.html
//網解 runtime beats:96.25% memory beats:80.75%
int maxProduct(std::vector<std::string>& words) {
    //解題思路為以int取代set來判斷words裡出現哪些字母
    //因為只有lowercase所以int(32bits)的後26bits可以代表字母
    //可以相乘的兩個word在&之後要是0，代表沒有重複的字母，才可以相乘
    int res = 0;    
    std::vector<int> mask(words.size(), 0);
    for (int i = 0; i < words.size(); ++i) {
        for (char c : words[i])
            mask[i] |= 1 << (c - 'a');
        for (int j = 0; j < i; ++j)
            if (!(mask[i] & mask[j]))
                res = std::max(res, int(words[i].size() * words[j].size()));
    }
    return res;
}

//321. Create Maximum Number
//網解 runtime beats:99.79% memory beats:95.00%
void maxNumber_getMax(int* num, int& len, int* result, int& t, int& sortedLen) {
    int n, top = 0;
    result[0] = num[0];
    const int need2drop = len - t;
    for (int i = 1; i < len; ++i) {
        n = num[i];
        while (top >= 0 && result[top] < n && (i - top) <= need2drop) --top; // i - top means already dropped i - top numbers
        if (i - top > need2drop) {
            sortedLen = std::max(1, top);
            while (++top < t)
                result[top] = num[i++];
            return;
        }
        if (++top < t)
            result[top] = n;
        else
            top = t - 1;
    }
}

void maxNumber_dp(int* num, int len, int& sortedLen, int& minL, int& maxL, int* res, int& k) {
    // create max number of different length from single vector
    int  j, * head, * prevhead = res;
    const int soi = sizeof(int);
    maxNumber_getMax(num, len, res, maxL, sortedLen);
    for (int l = maxL; l > std::max(minL, 1); --l) {
        head = prevhead + k;
        memcpy(head, prevhead, l * soi);
        for (j = sortedLen; j < l; ++j) {
            if (head[j] > head[j - 1]) {
                sortedLen = std::max(1, j - 1);
                memcpy(head + j - 1, prevhead + j, soi * (l - j));
                break;
            }
        }
        if (j == l) sortedLen = l;
        prevhead = head;
    }
}

void maxNumber_merge(int* num1, int len1, int* num2, int len2, int* result, int& resSize) {
    // merge max number created from single vector
    int i = 0, j = 0, k = 0;
    while (i < resSize) {
        if (j < len1&& k < len2) {
            if (num1[j] > num2[k])
                result[i++] = num1[j++];
            else if (num1[j] < num2[k])
                result[i++] = num2[k++];
            else {
                int remaining1 = len1 - j, remaining2 = len2 - k, tmp = num1[j];
                int flag = memcmp(num1 + j, num2 + k, sizeof(int) * std::min(remaining1, remaining2));
                flag = (flag == 0 ? (remaining1 > remaining2 ? 1 : -1) : flag);
                int* num = flag > 0 ? num1 : num2;
                int& cnt = flag > 0 ? j : k;
                int len = flag > 0 ? len1 : len2;
                while (num[cnt] == tmp && cnt < len && i < resSize) result[i++] = num[cnt++];
            }
        }
        else if (j < len1) result[i++] = num1[j++];
        else result[i++] = num2[k++];
    }
}

std::vector<int> maxNumber_network(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
    int soi = sizeof(int), len1 = nums1.size(), len2 = nums2.size(), step = k * soi;
    int minL1 = std::max(0, k - len2), maxL1 = std::min(k, len1), minL2 = k - maxL1, maxL2 = k - minL1, range = maxL1 - minL1 + 1;
    int* res = new int[range * k * 2 + 2 * k], * dp1 = res + k, * dp2 = res + range * k + k, * tmp = res + range * 2 * k + k;
    memset(res, 0, step);
    int sortedLen1 = 1, sortedLen2 = 1;
    if (len1 == 0 && len2 > 0) maxNumber_getMax(&nums2[0], len2, res, k, sortedLen2);
    else if (len1 > 0 && len2 == 0) maxNumber_getMax(&nums1[0], len1, res, k, sortedLen2);
    else if (len1 > 0 && len2 > 0) {
        maxNumber_dp(&nums1[0], len1, sortedLen1, minL1, maxL1, dp1, k);
        maxNumber_dp(&nums2[0], len2, sortedLen2, minL2, maxL2, dp2, k);
        if (sortedLen1 + sortedLen2 > k) {
            maxNumber_merge(dp1 + k * (maxL1 - sortedLen1), sortedLen1, dp2 + k * (maxL2 - sortedLen2), sortedLen2, tmp, k);
            std::vector<int> resv(tmp, tmp + k);
            delete[] res;
            return resv;
        }
        for (int i = minL1; i <= maxL1; ++i) {
            maxNumber_merge(dp1 + k * (maxL1 - i), i, dp2 + k * (maxL2 - k + i), (k - i), tmp, k);
            if (memcmp(res, tmp, step) < 0) memcpy(res, tmp, step);
        }
    }
    std::vector<int> resv(res, res + k);
    delete[] res;
    return resv;
}

//322. Coin Change
//https://www.cnblogs.com/grandyang/p/5138186.html
//網解 runtime beats:68.79% memory beats:17.03%
int coinChange_network(std::vector<int>& coins, int amount) {
    //解題思路為i為當前amount，j是在coins中的位置
    //如果i > coins[j]代表說現在的amount可以被1個coins[j] + ?個其他硬幣組合
    //?個其他硬幣就是DP，DP儲存在第i時可以被幾個硬幣組合
    //所以DP初始為amount + 1，因為在DP[0]代表0元的硬幣組合
    std::vector<int> dp(amount + 1, amount + 1);    //初使值為amount+1是因為最多就amount個硬幣，所以amount + 1就大於最大值了
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i)
        for (int j = 0; j < coins.size(); ++j)
            if (coins[j] <= i)
                dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
    return (dp[amount] > amount) ? -1 : dp[amount];
}

//網解 runtime beats:99.88% memory beats:91.38%
void coinChange_helper(int& res, std::vector<int>& coins, int target, int idx, int count) {
    if (idx < 0)
        return;
    if (target % coins[idx] == 0) {
        res = std::min(res, count + target / coins[idx]);
        return;
    }

    for (int i = target / coins[idx]; i >= 0; --i) {
        if (count + i >= res - 1) break;    // pruing
        coinChange_helper(res, coins, target - i * coins[idx], idx - 1, count + i);
    }
}

int coinChange(std::vector<int>& coins, int amount) {
    std::sort(coins.begin(), coins.end());
    int res = amount + 1;
    coinChange_helper(res, coins, amount, coins.size() - 1, 0);
    return res > amount ? -1 : res;
}


// 6. Zigzag Conversion
//初解 runtime beats:44.06% memory beats:49.42%
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
//初解 runtime beats:100.00% memory beats:76.02%
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
//初解 runtime beats:82.99% memory beats:12.81%
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
//初解 runtime beats:77.18% memory beats:64.52%
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
//網解 runtime beats:100.00% memory beats:29.23%
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
//網解 runtime beats:10.53% memory beats:76.31%
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
//初解 runtime beats:58.77% memory beats:93.14%
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
//初解 runtime beats:05.22% memory beats:99.98%
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
//網解 runtime beats:86.35% memory beats:06.25%
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
//初解 runtime beats:11.05% memory beats:05.69%
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
//網解 runtime beats:48.20% memory beats:92.86%
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
//初解 runtime beats:100.00% memory beats:56.76%
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
//初解 runtime beats:05.57% memory beats:05.03%
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
//網解 runtime beats:51.58% memory beats:76.91%
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
//初解 runtime beats:51.58% memory beats:76.91%
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
//初解 runtime beats:09.50% memory beats:91.25%
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
//初解 runtime beats:28.19% memory beats:29.77%
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
//網解 runtime beats:27.47% memory beats:71.67%
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
//初解 runtime beats:65.95% memory beats:72.83%
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
//網解 runtime beats:100.00% memory beats:90.47%
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
//初解 runtime beats:100.00% memory beats:50.00%
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
//網解 runtime beats:50.00% memory beats:50.00%
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
//初解 runtime beats:33.33% memory beats:100.00%
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
//初解 runtime beats:50.00% memory beats:50.00%
int mostBooked(int n, std::vector<std::vector<int>>& meetings) {
    return 0;
}

//987. Vertical Order Traversal of a Binary Tree
//初解 runtime beats:39.72% memory beats:63.58%
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
class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, std::vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

//初解 runtime beats:38.04% memory beats:86.69%
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
//初解 runtime beats:100.00% memory beats:99.74%
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
//初解 runtime beats:55.39% memory beats:96.64%
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
//初解 runtime beats:100.00% memory beats:75.10%
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
//網解 runtime beats:08.23% memory beats:91.78%
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
//網解 runtime beats:83.97% memory beats:98.77%
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
//初解 runtime beats:07.99% memory beats:96.11%
int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

//1137. N-th Tribonacci Number
//初解 runtime beats:100.00% memory beats:20.99%
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
//初解 runtime beats:100.00% memory beats:16.06%
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
//初解 runtime beats:55.42% memory beats:96.77%
int minCostClimbingStairs(std::vector<int>& cost) {
    int size = cost.size();
    if (size == 2)
        for (int i = size - 3; i >= 0; --i)
            cost[i] = cost[i] + std::min(cost[i + 1], cost[i + 2]);
    return std::min(cost[0], cost[1]);
}

//1383. Maximum Performance of a Team
//https://youtu.be/Y7UTvogADH0
//網解 runtime beats:23.24% memory beats:56.16%
int maxPerformance(int n, std::vector<int>& speed, std::vector<int>& efficiency, int k) {
    /*
    解題思路：
    因題目設計最多選 k 位工程師，表示可以選小於 k 位
    1. 根據 efficiency 排序每位工程師
    2. 在第 i 位工程師為了本身最大效率，不得選擇 efficiency 低於自己的工程師 (這沒有遍例所有情況，不過是可能最佳解)
    3. 前(高)於自己的工程師，因為自己有最低的 efficiency，所以不用考慮前面工程師的 efficiency，只需在意 speed，因此選擇 k - 1 個最大高於自己的工程師
    4. 根據題目定義，回傳 modulo 1e9 + 7
    */

    std::vector<std::pair<int, int>> efficiency_speed;  //根據 efficiency 排序每位工程師
    for (int i = 0; i < n; ++i)
        efficiency_speed.push_back({ efficiency[i], speed[i] });
    sort(efficiency_speed.rbegin(), efficiency_speed.rend());   

    std::priority_queue<int, std::vector<int>, std::greater<int>> candidates;        //k 個工程師(k - 1 個最大高於自己的工程師 + 自己)
    long speed_sum = 0;
    long ans = 0;                                //最大解
    for (int i = 0; i < n; ++i) {
        speed_sum += efficiency_speed[i].second;
        candidates.push(efficiency_speed[i].second);
        if (candidates.size() > k) {
            speed_sum -= candidates.top();
            candidates.pop();
        }
        ans = std::max(ans, speed_sum * efficiency_speed[i].first);
    }

    return ans % static_cast<int>(1e9 + 7); // 回傳 modulo 1e9 + 7
}

//198. House Robber
//初解 runtime beats:100.00% memory beats:77.67%
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
//初解 runtime beats:100.00% memory beats:20.36%
int rob2(std::vector<int>& nums) {
    int size = nums.size();
    if (size < 3)
        return *std::max_element(nums.begin(), nums.end());

    // 因為最後一間與第一間相鄰，所以考慮拿掉第一間以及最後一間的最大解
    std::vector<int> nums_no_top = nums;
    nums_no_top.pop_back();
    nums.erase(nums.begin());

    return std::max(rob(nums_no_top), rob(nums));
}

//740. Delete and Earn
//初解 runtime beats:82.61% memory beats:51.55%
int deleteAndEarn(std::vector<int>& nums) {
    // 先將 nums 轉換到 1 ~ 10000 之間的 dp，接下來就如 House Robber 一樣
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
//初解 runtime beats:72.03% memory beats:27.39%
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
//初解 runtime beats:72.82% memory beats:76.31%
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
//初解 runtime beats:64.09% memory beats:18.18%
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
//初解 runtime beats:27.53% memory beats:27.57%
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
//初解 runtime beats:11.59% memory beats:21.48%
void pseudoPalindromicPaths_DFS(TreeNode* node, std::set<int>& candidates, int& ans) {
    // 與 candidates 配對，配對成功即消除
    if (candidates.count(node->val))
        candidates.erase(node->val);
    else
        candidates.insert(node->val);

    if (!node->left and !node->right and (candidates.size() <= 1)) {        
        // 是最後一個節點，且候選人小於等於1(等於1可以放中間)，代表偽回文
        ans++;
    }
    else {
        if (node->left) pseudoPalindromicPaths_DFS(node->left, candidates, ans);
        if (node->right) pseudoPalindromicPaths_DFS(node->right, candidates, ans);
    }

    // 在最後節點，如果沒有自己的值代表已經配對，所以要補回去
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

//二解 runtime beats:34.77% memory beats:50.95%
int pseudoPalindromicPaths(TreeNode* root) {
    // 形成回文即數值兩兩成對
    // 利用值介於1-9 間的特性，將 1 - 9 存在 1到9位 bit，即可節省記憶體
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
//初解 runtime beats:05.04% memory beats:90.50%
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
//網解 runtime beats:23.39% memory beats:33.15%
int maxSubarraySumCircular(std::vector<int>& A) {
    /*
    因為題目為環形，所以分兩種可能，第一種是與53題一樣，第二種是首尾兩個數組相加違最大子數組
    在第二種情況下，可以反視因為要相加首尾兩端的子數組，代表中間有一段不要的，而這個不要的是最小子數組
    因此可將第二種情況視為將vector乘以-1後找到最大子數組(即找到最小子數組)
    不過此情況有例外，就是當vector都是小於等於0，在此情況下答案依第一種為主
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
