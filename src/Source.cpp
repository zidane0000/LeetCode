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
    //std::vector<int> nums{ 2,7,11,15 };
    //twoSum(nums, 9);
    //twoSum_2(nums, 9);
    //twoSum_3(nums, 9);

    //2. Add Two Numbers
    //addTwoNumbers(toList({ 5,1 }), toList({  }));
    //addTwoNumbers_3(toList({ 5 }), toList({ 5 }));

    //3. Longest Substring Without Repeating Characters
    //lengthOfLongestSubstring("abcabcab");
    //lengthOfLongestSubstring("pwwkew");
    //lengthOfLongestSubstring("bbbbbb");
    //lengthOfLongestSubstring(" ");
    //lengthOfLongestSubstring("dvdf");

    //4. Median of Two Sorted Arrays
    //std::vector<int> nums1{ 1 };
    //std::vector<int> nums2{  };
    //double t = findMedianSortedArrays(nums1, nums2);
    //double t = findMedianSortedArrays_2(nums1, nums2);

    //5. Longest Palindromic Substring
    //std::string s = longestPalindrome_network("civilwartestingwhetherthatnaptionoranynartionsoconceivedandsodedicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWehavecometodedicpateaportionofthatfieldasafinalrestingplaceforthosewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfangandproperthatweshoulddothisButinalargersensewecannotdedicatewecannotconsecratewecannothallowthisgroundThebravelmenlivinganddeadwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddordetractTgheworldadswfilllittlenotlenorlongrememberwhatwesayherebutitcanneverforgetwhattheydidhereItisforusthelivingrathertobededicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfarsonoblyadvancedItisratherforustobeherededicatedtothegreattdafskremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevotiontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatweherehighlyresolvethatthesedeadshallnothavediedinvainthatthisnationunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthepeoplebythepeopleforthepeopleshallnotperishfromtheearth");
    //s = longestPalindrome_network("abcba");

    //9. Palindrome Number
    //bool r = isPalindrome(-121);

    //10. Regular Expression Matching
    //bool r = isMatch("aaa", "a*a");
    //r = isMatch("aa", "aaaa");
    //r = isMatch("aa", "a");
    //r = isMatch("aa", "aa");
    //r = isMatch("aa", "a*");
    //r = isMatch("aa", "c*a*");
    //r = isMatch("ab", ".*");                    //true
    //r = isMatch("ab", ".*c");                   //false
    //r = isMatch("mississippi", "mis*is*p*.");   //false
    //r = isMatch("aaa", "ab*a*c*a");   //false

    //11. Container With Most Water
    //std::vector<int> height{ 1,8,6,2,5,4,8,3,7 };
    //std::vector<int> height{ 1,2,1 };
    //std::vector<int> height{ 2, 3, 4, 5, 18, 17, 6 };
    std::vector<int> height{ 1, 2, 3, 4, 5, 25, 24, 3, 4 };
    int a = maxArea(height);

    return 0;
}