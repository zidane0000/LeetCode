#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>
#include <stack>
#include <set>

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
            return total % 2 == 0 ? ((std::max(max1, max2)) + std::min(min1, min2)) / 2.0 : std::max(max1, max2);
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
        if (before->next)
            return before->next;
        else
            return NULL;
    }
    else {
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
        if (--letterCnt[s[i]] >= 0) ++cnt;
        while (cnt == t.size()) {
            if (minLen > i - left + 1) {
                minLen = i - left + 1;
                minLeft = left;
            }
            if (++letterCnt[s[left]] > 0) --cnt;
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

std::vector<std::vector<int>> combine(int n, int k) {
    std::vector<std::vector<int>> ans;
    std::vector<int> temp;
    combine(1, n, k, ans, temp); //call fuction to get combination of k numbers which range is 1-n
    return ans;
}