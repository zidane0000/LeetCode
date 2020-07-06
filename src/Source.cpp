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
    //std::vector<int> height{ 1, 2, 3, 4, 5, 25, 24, 3, 4 };
    //int a = maxArea(height);

    //15. 3Sum
    //std::vector<int> nums{ -1, 0, 1, 2, -1, -4 };
    //std::vector<int> nums{ -2, 0, 1, 1, 2 };
    //std::vector<int> nums{ -4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6 };
    //std::vector<int> nums{ 7, 5, -8, -6, -13, 7, 10, 1, 1, -4, -14, 0, -1, -10, 1, -13, -4, 6, -11, 8, -6, 0, 0, -5, 0, 11, -9, 8, 2, -6, 4, -14, 6, 4, -5, 0, -12, 12, -13, 5, -6, 10, -10, 0, 7, -2, -5, -12, 12, -9, 12, -9, 6, -11, 1, 14, 8, -1, 7, -13, 8, -11, -11, 0, 0, -1, -15, 3, -11, 9, -7, -10, 4, -2, 5, -4, 12, 7, -8, 9, 14, -11, 7, 5, -15, -15, -4, 0, 0, -11, 3, -15, -15, 7, 0, 0, 13, -7, -12, 9, 9, -3, 14, -1, 2, 5, 2, -9, -3, 1, 7, -12, -3, -1, 1, -2, 0, 12, 5, 7, 8, -7, 7, 8, 7, -15 };
    //std::vector<std::vector<int>> r = threeSum_network(nums);

    //17. Letter Combinations of a Phone Number
    //std::vector<std::string> r = letterCombinations("23");

    //19. Remove Nth Node From End of List
    //ListNode* r = removeNthFromEnd(toList({1}), 1);
    //ListNode* r = removeNthFromEnd_2(toList({ 1 }), 1);

    //20. Valid Parentheses
    //bool r = isValid("()[]{}");
    //r = isValid("(]");
    //r = isValid("([)]");
    //r = isValid("{[]}");
    //r = isValid_network("]}");
    //r = isValid_network("{]}");
    //r = isValid_network("{}");
    //r = isValid_network("{}()[]");
    //r = isValid_network("{}()()[]");
    //r = isValid_network("{}()[][");
    //r = isValid_network("[()]");
    //r = isValid_network("{()}");

    //21. Merge Two Sorted Lists
    //ListNode* r = mergeTwoLists(toList({ 1,2,4 }), toList({ 1,3,4 }));
    //ListNode* r = mergeTwoLists(toList({ 5 }), toList({ 1,3,4 }));
    //ListNode* r = mergeTwoLists_2(toList({ 1,2,4 }), toList({ 1,3,4 }));
    //ListNode* r = mergeTwoLists_2(toList({ 5 }), toList({ 1,3,4 }));
    //ListNode* r = mergeTwoLists_2(toList({ 1 }), toList({ 2 }));
    
    //22. Generate Parentheses
    //std::vector<std::string> r = generateParenthesis(6);
    //std::vector<std::string> r = generateParenthesis_network(6);
    //std::vector<std::string> r = generateParenthesis_network2(3);

    //23. Merge k Sorted Lists
    //std::vector<ListNode*> lists;
    //lists.push_back(toList({ 1,4,5 }));
    //lists.push_back(toList({ 1,3,4 }));
    //lists.push_back(toList({ 2,6 }));
    //ListNode* r = mergeKLists(lists);

    //24. Swap Nodes in Pairs
    //ListNode* r = swapPairs(toList({ 1 }));
    //ListNode* r = swapPairs_2(toList({ 1 }));

    //25. Reverse Nodes in k-Group
    //ListNode* r = reverseKGroup(toList({ 1,2,3,4,5 }), 3);
    //ListNode* r = reverseKGroup_network(toList({ 1,2,3,4,5,6,7,8,9 }), 3);

    //31. Next Permutation
    //std::vector<int> nums{1,2,7,4,3,1};
    //std::vector<int> nums{ 3,2,1 };
    //std::vector<int> nums{ 1 };
    //std::vector<int> nums{ 1,2,4,3 };
    //std::vector<int> nums{ 2,3,1,3,3 };
    //std::vector<int> nums{ 11,12,0,27,3,11,21,9,0,15,26,27,17,24,0,16,4,17,14,8,15,8,2,16,10,6,6,24,16,2,18,19,6,10,17,10,21,0,11,13,7,7,2,16,24,25,2,20,12,9,20,19 };
    //nextPermutation(nums);

    //32. Longest Valid Parentheses
    int r = longestValidParentheses("(()");
    //r = longestValidParentheses(")()())");
    //r = longestValidParentheses("(()())");
    //r = longestValidParentheses("(())())"); 
    //r = longestValidParentheses("()()()()()()(()()");
    r = longestValidParentheses(")))()())(()((()()((()(()()(()()))()(((()())))()(((()(((())()))(()))(())((())())())))(()))((()(()())((((((()()(((())()()(((((())(((()())())(()(())))");
    

    return 0;
}