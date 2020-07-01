#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

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