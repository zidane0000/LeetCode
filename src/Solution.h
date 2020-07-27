#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>
#include <stack>
#include <set>
#include <unordered_set>
#include <queue>

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
        if (before->next != NULL)
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
std::vector<std::string> generateParenthesis_network2(int n) {
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
//Fail

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
int maxSubArray(std::vector<int>& nums) {
    if (nums.size() == 0)
        return INT_MIN;

    int max_Sub = INT_MIN;
    int Sub = 0;
    for (auto num : nums) {
        Sub += num;
        max_Sub = max_Sub > Sub ? max_Sub : Sub;
        if (Sub < 0)
            Sub = 0;
    }

    return max_Sub;
}

//54. Spiral Matrix
//fail

//55. Jump Game
//初解 runtime beats:81.88% memory beats:37.69%
bool canJump(std::vector<int>& nums) {
    int cur = 0;        //當前走到底幾位
    int maxNext = 0;    //最大的下一個
    int s = nums.size();
    for (int i = 0; i < s - 1; i++) {
        maxNext = std::max(maxNext, nums[i] + i);
        //nums[i]+i可以知道跳到第幾步 i=要跳的步數 nums[i]指的是這次能跳的步數
        if (i == cur) {//因為是用nums.length-1 所以這邊要先++ 
            cur = maxNext;
            if (cur >= s - 1)
                return true;
        }
    }

    if (cur < s - 1)
        return false;
    else
        return true;
}

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
    if (m == 1)
        return 1;
    else if (n == 1)
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
int climbStairs(int n) {
    std::vector<int> stairs{ 0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144 };
    for (int i = 11; i < n; i++) {
        stairs.push_back(stairs[i] + stairs[i - 1]);
    }
    return stairs[n];
}

//二解 runtime beats:100.00% memory beats:80.69%
int climbStairs_2(int n) {
    if (n < 4)
        return n;

    int a = 2, b = 3;
    n += -3;

    while (n--) {
        int tmp = a;
        a = b;
        b = b + tmp;
    }
        
    return b;
}

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
std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> ans;
    int posi = 0;
    if (root != nullptr) {
        ans.push_back(root->val);
        traversalTree(ans, root, posi);
    }
    
    return ans;
}

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
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

//初解 runtime beats:52.14% memory beats:16.94%
Node* connect(Node* root) {
    if (!root)
        return root;
    
    //BFS
    std::queue<Node*> wait_queue;
    std::queue<Node*> next_queue;
    wait_queue.push(root);

    while (!wait_queue.empty()) {
        Node* tmp = wait_queue.front();
        wait_queue.pop();
        if (tmp->left)
            next_queue.push(tmp->left);

        if (tmp->right)
            next_queue.push(tmp->right);

        while (!wait_queue.empty()) {
            Node* tmp_2 = wait_queue.front();
            wait_queue.pop();
            if (tmp_2->left)
                next_queue.push(tmp_2->left);

            if (tmp_2->right)
                next_queue.push(tmp_2->right);

            tmp->next = tmp_2;
            tmp = tmp->next;
        }

        while (!next_queue.empty()) {
            tmp = next_queue.front();
            next_queue.pop();
            wait_queue.push(tmp);
        }
    }

    return root;
}

//網解 runtime beats:94.58% memory beats:99.90%
Node* connect_network(Node* root) {
    if (!root)
        return nullptr;
    Node* l = root->left;
    Node* last;
    std::queue<Node*> q;
    if (root->right)
        q.push(root->right);

    while (l && !q.empty())
    {
        last = l;
        int initial_size = q.size();
        if (l->right)
            q.push(l->right);
        for (int i = 1; i <= initial_size; i++)
        {
            Node* curr = q.front();
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
            curr->left = curr->right = nullptr;
            last->next = curr;
            last = last->next;
            q.pop();
        }
        l = l->left;
    }
    return root;
}

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