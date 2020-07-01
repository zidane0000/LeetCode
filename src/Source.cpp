#include "Solution.h"

ListNode* toList(std::vector<int> vec) {
    ListNode* a = nullptr;
    ListNode* cur = nullptr;
    for (auto i : vec) {
        if (a) {
            ListNode* b = new ListNode;
            b->val = i;
            cur->next = b;
            cur = b;
        }
        else {
            a = new ListNode;
            a->val = i;
            cur = a;
        }
    }
    return a;
}

int main()
{
    //LeetCode 1. Two Sum
    std::vector<int> nums{ 2,7,11,15 };
    //twoSum(nums, 9);
    //twoSum_2(nums, 9);
    //twoSum_3(nums, 9);

    //2. Add Two Numbers
    //addTwoNumbers(toList({ 5,1 }), toList({  }));
    //addTwoNumbers_3(toList({ 5 }), toList({ 5 }));

    //3. Longest Substring Without Repeating Characters
    lengthOfLongestSubstring("abcabcab");
    lengthOfLongestSubstring("pwwkew");
    lengthOfLongestSubstring("bbbbbb");
    lengthOfLongestSubstring(" ");
    lengthOfLongestSubstring("dvdf");
    return 0;
}