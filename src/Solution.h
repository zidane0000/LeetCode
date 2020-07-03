#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>

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