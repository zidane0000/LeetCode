#include "Solution.h"

#define null NULL

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

//ListNode* toList(std::vector<int> vec, int posi) {
//    ListNode* a = nullptr;
//    ListNode* cur = nullptr;
//    for (auto i : vec) {
//        if (a) {
//            ListNode* b = new ListNode;
//            b->val = i;
//            cur->next = b;
//            cur = b;
//        }
//        else {
//            a = new ListNode;
//            a->val = i;
//            cur = a;
//        }
//    }
//
//    ListNode* tmp  = a;
//    while ((posi--) && (tmp != NULL))
//        tmp = tmp->next;
//    cur->next = tmp;
//
//    return a;
//}

//https://leetcode.com/problems/invert-binary-tree/discuss/62896/Just-wonder-how-to-write-custom-testcase.-Any-examples/499471
TreeNode* toTree(std::vector<int> arr) {
    TreeNode* root = NULL;
    std::queue<TreeNode*> q;
    int i = 0;
    TreeNode* t = arr[i] == NULL ? NULL : new TreeNode(arr[i]);
    root = t;
    q.push(root);
    i++;
    while (!q.empty() && i < arr.size()) {
        TreeNode* t1 = q.front();
        q.pop();
        if (t1 != NULL) {
            t1->left = arr[i] == NULL ? NULL : new TreeNode(arr[i]);
            q.push(t1->left);
            i++;
            if (i >= arr.size()) {
                break;
            }
            t1->right = arr[i] == NULL ? NULL : new TreeNode(arr[i]);
            q.push(t1->right);
            i++;
        }
    }
    return root;
}

Node* toNode(std::vector<int> arr) {
    Node* root = NULL;
    std::queue<Node*> q;
    int i = 0;
    Node* t = arr[i] == NULL ? NULL : new Node(arr[i]);
    root = t;
    q.push(root);
    i++;
    while (!q.empty() && i < arr.size()) {
        Node* t1 = q.front();
        q.pop();
        if (t1 != NULL) {
            t1->left = arr[i] == NULL ? NULL : new Node(arr[i]);
            q.push(t1->left);
            i++;
            if (i >= arr.size()) {
                break;
            }
            t1->right = arr[i] == NULL ? NULL : new Node(arr[i]);
            q.push(t1->right);
            i++;
        }
    }
    return root;
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

    //14. Longest Common Prefix
    //std::vector<std::string> strs = { "aa","aa","aa" };
    //std::string r = longestCommonPrefix(strs);

    //15. 3Sum
    //std::vector<int> nums{ -1, 0, 1, 2, -1, -4 };
    //std::vector<int> nums{ -2, 0, 1, 1, 2 };
    //std::vector<int> nums{ -4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6 };
    //std::vector<int> nums{ 7, 5, -8, -6, -13, 7, 10, 1, 1, -4, -14, 0, -1, -10, 1, -13, -4, 6, -11, 8, -6, 0, 0, -5, 0, 11, -9, 8, 2, -6, 4, -14, 6, 4, -5, 0, -12, 12, -13, 5, -6, 10, -10, 0, 7, -2, -5, -12, 12, -9, 12, -9, 6, -11, 1, 14, 8, -1, 7, -13, 8, -11, -11, 0, 0, -1, -15, 3, -11, 9, -7, -10, 4, -2, 5, -4, 12, 7, -8, 9, 14, -11, 7, 5, -15, -15, -4, 0, 0, -11, 3, -15, -15, 7, 0, 0, 13, -7, -12, 9, 9, -3, 14, -1, 2, 5, 2, -9, -3, 1, 7, -12, -3, -1, 1, -2, 0, 12, 5, 7, 8, -7, 7, 8, 7, -15 };
    //std::vector<std::vector<int>> r = threeSum_network(nums);

    //16. 3Sum Closest
    //std::vector<int> nums{ -1,0,1,1,55 };
    //int r = threeSumClosest(nums, 3);

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
    //std::vector<std::string> r = generateParenthesis_network_2(3);

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
    //int r = longestValidParentheses("(()");
    //r = longestValidParentheses(")()())");
    //r = longestValidParentheses("(()())");
    //r = longestValidParentheses("(())())"); 
    //r = longestValidParentheses("()()()()()()(()()");
    //r = longestValidParentheses(")))()())(()((()()((()(()()(()()))()(((()())))()(((()(((())()))(()))(())((())())())))(()))((()(()())((((((()()(((())()()(((((())(((()())())(()(())))");

    //33. Search in Rotated Sorted Array
    //std::vector<int> nums{4,5,6,7,0,1,2};
    //int r = search_3(nums, 0);
    //int r = search_network(nums, 1);

    //34. Find First and Last Position of Element in Sorted Array
    //std::vector<int> nums{ 4,5,6,6,7 };
    //std::vector<int> r = searchRange(nums, 2);
    //std::vector<int> r = searchRange_2(nums, 8);

    //35. Search Insert Position
    //std::vector<int> nums{ 4,5,6,6,7 };
    //int r = searchInsert(nums, 5);

    //36. Valid Sudoku
    //std::vector<std::vector<char>> board {
    //  {'5','3','.','.','7','.','.','.','.'},
    //  {'6','.','.','1','9','5','.','.','.'},
    //  {'.','9','8','.','.','.','.','6','.'},
    //  {'8','.','.','.','6','.','.','.','3'},
    //  {'4','.','.','8','.','3','.','.','1'},
    //  {'7','.','.','.','2','.','.','.','6'},
    //  {'.','6','.','.','.','.','2','8','.'},
    //  {'.','.','.','4','1','9','.','.','5'},
    //  {'.','.','.','.','8','.','.','7','9'}
    //};
    //std::vector<std::vector<char>> board {
    //    {'5', '3', '.', '.', '7', '.', '.', '9', '.'}, 
    //    {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, 
    //    {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, 
    //    {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, 
    //    {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, 
    //    {'7', '.', '.', '.', '2', '.', '.', '.', '6'}, 
    //    {'.', '6', '.', '9', '.', '.', '2', '8', '.'},
    //    {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, 
    //    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}}
    //;
    //std::vector<std::vector<char>> board { 
    //    {'.', '.', '5', '.', '.', '.', '.', '.', '.'}, 
    //    {'.', '.', '.', '8', '.', '.', '.', '3', '.'},
    //    {'.', '5', '.', '.', '2', '.', '.', '.', '.'},
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '9'}, 
    //    {'.', '.', '.', '.', '.', '.', '4', '.', '.'}, 
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '7'}, 
    //    {'.', '1', '.', '.', '.', '.', '.', '.', '.'}, 
    //    {'2', '4', '.', '.', '.', '.', '9', '.', '.'} 
    //};
    //std::vector<std::vector<char>> board {
    //    {'.', '.', '.', '1', '8', '.', '.', '.', '7'}, 
    //    {'.', '.', '.', '.', '.', '.', '2', '.', '.'}, 
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '3'}, 
    //    {'4', '.', '3', '.', '.', '.', '.', '1', '9'}, 
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
    //    {'1', '.', '.', '.', '5', '.', '.', '.', '.'},
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
    //    {'.', '.', '.', '5', '.', '.', '.', '.', '6'} 
    //};
    //std::vector<std::vector<char>> board {
    //    {'.', '.', '4', '.', '.', '.', '6', '3', '.'}, 
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
    //    {'5', '.', '.', '.', '.', '.', '.', '9', '.'}, 
    //    {'.', '.', '.', '5', '6', '.', '.', '.', '.'},
    //    {'4', '.', '3', '.', '.', '.', '.', '.', '1'},
    //    {'.', '.', '.', '7', '.', '.', '.', '.', '.'},
    //    {'.', '.', '.', '5', '.', '.', '.', '.', '.'},
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '.'}, 
    //    {'.', '.', '.', '.', '.', '.', '.', '.', '.'} 
    //};
    //bool r = isValidSudoku_2(board);

    //39. Combination Sum
    //std::vector<int> candidates{ 2,3,5,7 };
    //std::vector<std::vector<int>> r = combinationSum(candidates, 7);

    //40. Combination Sum
    //std::vector<int> candidates{ 1,2,2,2,5 };
    //std::vector<std::vector<int>> r = combinationSum2(candidates, 5);

    //41. First Missing Positive
    //std::vector<int> nums{ -1,0,1 };
    //int r = firstMissingPositive(nums);
    //int r = firstMissingPositive_2(nums);

    //42. Trapping Rain Water
    //std::vector<int> height{ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    //std::vector<int> height{ 4, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
    //int r = trap(height);
    //int r = trap_2(height);

    //45. Jump Game II
    //std::vector<int> nums{ 2,3,1,1,4 };
    //std::vector<int> nums{ 5, 6, 4, 4, 6, 9, 4, 4, 7, 4, 4, 8, 2, 6, 8, 1, 5, 9, 6, 5, 2, 7, 9, 7, 9, 6, 9, 4, 1, 6, 8, 8, 4, 4, 2, 0, 3, 8, 5 };
    //int r = jump_network(nums);

    //46. Permutations
    //std::vector<int> nums{ 1,2,3 };
    //std::vector<std::vector<int>> r = permute(nums);

    //48. Rotate Image
    //std::vector<std::vector<int>> matrix{ 
    //    { 1, 2, 3, 4, 5, 6},
    //    { 7, 8, 9,10,11,12},
    //    {13,14,15,16,17,18},
    //    {19,20,21,22,23,24},
    //    {25,26,27,28,29,30},
    //    {31,32,33,34,35,36} };
    //rotate(matrix);


    //49. Group Anagrams
    //std::vector<std::string> strs{ "eata", "tea", "tan", "ate", "nat", "bat" };
    //std::vector<std::vector<std::string>> r = groupAnagrams(strs);

    //53. Maximum Subarray
    //std::vector<int> nums{ -1 };
    //int r = maxSubArray(nums);

    //55. Jump Game
    //ªì¸Ñ runtime beats:46.64% memory beats:70.04%
    //std::vector<int> nums{2,0,0,1};
    //bool r = canJump(nums);

    //56. Merge Intervals
    //std::vector<std::vector<int>> intervals{ {1,3},{2,6},{8,10},{15,18} };
    //std::vector<std::vector<int>> intervals{ {1,2},{2,3},{3,4},{4,5},{5,6},{7,8},{9,10} };
    //std::vector<std::vector<int>> intervals{ {1,3},{2,6},{8,10},{15,18} };
    //std::vector<std::vector<int>> r =  merge(intervals);

    //60. Permutation Sequence
    //std::string r = getPermutation(9, 219601);
    //std::string r = getPermutation_2(4, 2);

    //62. Unique Paths
    //int m = 4;
    //int r = uniquePaths(1, m);
    //r = uniquePaths(2, m);
    //r = uniquePaths(3, m);
    //r = uniquePaths(4, m);
    //r = uniquePaths(5, m);
    //r = uniquePaths(6, m);
    //r = uniquePaths(7, m);
    //r = uniquePaths(8, m);
    //r = uniquePaths(9, m);

    //64. Minimum Path Sum
    //std::vector<std::vector<int>> grid{
    //    {1,3,1},
    //    {1,5,1},
    //    {4,2,1}
    //};
    //int r = minPathSum(grid);

    //67. Add Binary
    //std::string r = addBinary("110010", "10111");

    //70. Climbing Stairs
    //int r = climbStairs(12);

    //73. Set Matrix Zeroes
    //std::vector<std::vector<int>> matrix{
    //    {1,2,1},
    //    {1,0,1},
    //    {1,2,1}
    //};
    //setZeroes(matrix);

    //74. Search a 2D Matrix
    //std::vector<std::vector<int>> matrix{
    //    {1},
    //    {3}
    //};
    //bool r = searchMatrix(matrix, 3);

    //76. Minimum Window Substring
    //std::string r = minWindow_network("ADOBECODEBANC", "ABC");

    //77. Combinations
    //std::vector<std::vector<int>> r = combine(5, 2);

    //78. Subsets
    //std::vector<int> nums{1,2,3};
    //std::vector<std::vector<int>> r = subsets(nums);

    //79. Word Search
    //std::vector<std::vector<char>> board{
        //{'A','B','C','E'},
        //{'S','F','C','S'},
        //{'A','D','E','E'},
        //{'A','A'},
        //{'A','A'}
    //    {'A','B','C','E'},{'S','F','E','S'},{'A','D','E','E'}
    //};
    //bool r = exist(board, "ABCESEEEFS");

    //80. Remove Duplicates from Sorted Array II
    //std::vector<int> nums{1,1,1};
    //int r = removeDuplicates(nums);

    //82. Remove Duplicates from Sorted List II
    //ListNode* r = deleteDuplicates_network(toList({ 1,2,2,3,3,4,4,4,5,6 }));

    //86. Partition List
    //ListNode* r = partition(toList({3,1,2}), 3);

    //90. Subsets II
    //std::vector<int> nums{ 1,2,2 };
    //std::vector< std::vector<int>> r = subsetsWithDup_network(nums);

    //92. Reverse Linked List II
    //ListNode* r = reverseBetween(toList({ 1,2,3,4,5 }), 1, 4);

    //95. Unique Binary Search Trees II
    //std::vector<TreeNode*> r = generateTrees(8);

    ////96. Unique Binary Search Trees
    //int r = numTrees_network(3);
    //r = numTrees_network_2(3);

    //97. Interleaving String
    //bool  r = isInterleave_network("aabcc", "dbbca", "aadbbbaccc");

    //102. Binary Tree Level Order Traversal
    //std::vector<std::vector<int>> r = levelOrder(toTree({ 1,2,3,NULL,NULL,4,5,NULL,NULL,7 }));
    //std::vector<std::vector<int>> r = levelOrder_2(toTree({ 1,2,3,NULL,NULL,4,5,NULL,NULL,7 }));

    //103. Binary Tree Zigzag Level Order Traversal
    //std::vector<std::vector<int>> r = zigzagLevelOrder(toTree({ 3,9,20,NULL,NULL,15,7 }));

    //105. Construct Binary Tree from Preorder and Inorder Traversal
    //std::vector<int>preorder{ 3,9,20,15,7 };
    //std::vector<int>inorder{ 9,3,15,20,7 };
    //TreeNode* r = buildTree_network_2(preorder, inorder);

    //107. Binary Tree Level Order Traversal II
    //std::vector<std::vector<int>> r = levelOrderBottom(toTree({ 3,9,20,NULL,NULL,15,7 }));

    //108. Convert Sorted Array to Binary Search Tree
    //std::vector<int> nums{-15,-10,-3,0,3,5,9};
    //TreeNode* r = sortedArrayToBST(nums);

    //111. Minimum Depth of Binary Tree
    //int r = minDepth(toTree({ 1,2,NULL,3,NULL,4,NULL,5 }));

    //114. Flatten Binary Tree to Linked List
    //TreeNode* root = toTree({ 1,2,5,3,4,NULL,6,NULL,NULL,7,8 });
    //flatten(root);

    //115. Distinct Subsequences
    //int r = numDistinct_network("adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabcaaaeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdccabddaddacdddc", "bcddceeeebecbc");

    //116. Populating Next Right Pointers in Each Node
    //Node* r = connect_network(toNode({1,2,3,4,5,6,7}));

    //118. Pascal's Triangle
    //std::vector<std::vector<int>> r = generate(5);

    //119. Pascal's Triangle II
    //std::vector<int> r = getRow_network(5);

    //120. Triangle
    //std::vector<std::vector<int>> triangle{
    //    {2},
    //    {3,4},
    //    {6,5,7},
    //    {1,2,8,7},
    //    {9,5,4,7,3}
    //};
    //int r = minimumTotal(triangle);

    //121. Best Time to Buy and Sell Stock
    //std::vector<int> prices{ 7,1,5,3,6,4 };
    //int r = maxProfit(prices);

    //124. Binary Tree Maximum Path Sum
    //int r = maxPathSum_network(toTree({ 1,-2,-3,1,3,-2,NULL,-1 }));

    //130. Surrounded Regions
    //std::vector<std::vector<char>> board {
    //    {'X','X','X','X'},
    //    {'X','O','O','X'},
    //    {'X','O','O','X'},
    //    {'X','O','X','X'}
    //};
    //solve(board);

    //131. Palindrome Partitioning
    //std::vector<std::vector<std::string>> r = partition("aabbaa");

    //132. Palindrome Partitioning II
    //int r = minCut_network_2("abbab");

    //134. Gas Station
    //std::vector<int> gas{ 5,1,2,3,4 };
    //std::vector<int> cost{ 4,4,1,5,1 };
    //int r = canCompleteCircuit(gas, cost);

    //136. Single Number
    //std::vector<int> nums{ 3,1,1,2,2 };
    //int r = singleNumber_network(nums);

    //139. Word Break
    //std::vector<std::string> wordDict{ "a","abc","b","cd" };
    //bool r = wordBreak_network("abcd", wordDict);

    //140. Word Break II
    //std::vector<std::string> wordDict{ "cat", "cats", "and", "sand", "dog" };
    //std::vector<std::string> r = wordBreak2("catsanddog", wordDict);
    //std::vector<std::string> wordDict{ "apple", "pen", "applepen", "pine", "pineapple" };
    //std::vector<std::string> r = wordBreak2("pineapplepenapple", wordDict);

    //141. Linked List Cycle
    //bool r = hasCycle_network(toList({ 1,2,4 }, 1));

    //143. Reorder List
    //ListNode* head = toList({ 1,2,3,4,5,6 });
    //reorderList(head);

    //144. Binary Tree Preorder Traversal
    //std::vector<int> r = preorderTraversal(toTree({ 1,2,3,4,5 }));

    //146. LRU Cache
    //LRUCache cache = LRUCache(2 /* capacity */);
    //cache.put(1, 1);
    //cache.put(2, 2);
    //std::cout << cache.get(1) << std::endl;       // returns 1
    //cache.put(3, 3);    // evicts key 2
    //std::cout << cache.get(2) << std::endl;       // returns -1 (not found)
    //cache.put(4, 4);    // evicts key 1
    //std::cout << cache.get(1) << std::endl;       // returns -1 (not found)
    //std::cout << cache.get(3) << std::endl;       // returns 3
    //std::cout << cache.get(4) << std::endl;       // returns 4

    //155. Min Stack
    //MinStack minStack = MinStack();
    //minStack.push(-2);
    //minStack.push(0);
    //minStack.push(-3);
    //minStack.getMin(); // return -3
    //minStack.pop();
    //minStack.top();    // return 0
    //minStack.getMin(); // return -2

    //168. Excel Sheet Column Title
    //std::string r = convertToTitle(701);

    //169. Majority Element
    //std::vector<int> nums{ 1,2,3,4,4,4,4,4,4 };
    //int r = majorityElement(nums);

    //171. Excel Sheet Column Number
    //int r = titleToNumber("A");
    //r = titleToNumber("AA");
    //r = titleToNumber("FXSHRXW");
    //r = titleToNumber("FXSHRXA");
    
    //173. Binary Search Tree Iterator
    //BSTIterator iterator = BSTIterator(toTree({ 3, 7, 15, NULL, NULL, 9, 20 }));
    //iterator.next();    // return 3
    //iterator.next();    // return 7
    //iterator.hasNext(); // return true
    //iterator.next();    // return 9
    //iterator.hasNext(); // return true
    //iterator.next();    // return 15
    //iterator.hasNext(); // return true
    //iterator.next();    // return 20
    //iterator.hasNext(); // return false

    //179. Largest Number
    //std::vector<int> nums{ 1,12,24,59,9 };
    //std::string r = largestNumber(nums);

    //187. Repeated DNA Sequences
    //std::vector<std::string> r = findRepeatedDnaSequences_network("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");

    //189. Rotate Array
    //std::vector<int> nums{ -1,2,3,4,5,6 };
    //rotate(nums, 2);

    //190. Reverse Bits
    //uint32_t r = reverseBits(2);

    //200. Number of Islands
    //std::vector<std::vector<char>> grid{
    //    {'1','1','0','0','1'},
    //    {'1','1','0','0','1'},
    //    {'0','1','0','0','1'},
    //    {'0','1','0','0','1'},
    //    {'1','1','0','0','1'}
    //};
    //int r = numIslands(grid);

    //202. Happy Number
    //bool r = isHappy(20);

    //203. Remove Linked List Elements
    //ListNode* r = removeElements(toList({ 1,2,3,6,6,4,5,6 }), 6);

    //205. Isomorphic Strings
    //bool r = isIsomorphic("a", "b");

    //207. Course Schedule
    //std::vector<std::vector<int>> prerequisites{ {0,2},{1,2},{2,0} };
    //bool r = canFinish(3, prerequisites);

    //209. Minimum Size Subarray Sum
    //std::vector<int> nums{ 2,3,1,2,4,3 };
    //int r = minSubArrayLen( 7, nums);

    //211. Design Add and Search Words Data Structure
    //WordDictionary wordDictionary = WordDictionary();
    //wordDictionary.addWord("bad");
    //wordDictionary.addWord("dad");
    //wordDictionary.addWord("mad");
    //wordDictionary.search("pad"); // return False
    //wordDictionary.search("bad"); // return True
    //wordDictionary.search(".ad"); // return True
    //wordDictionary.search("c.."); // return True

    //212. Word Search II
    //std::vector<std::vector<char>> board{
    //    {'o','a','a','n'},
    //    {'e','t','a','e'},
    //    {'i','h','k','r'},
    //    {'i','f','l','v'}
    //};
    //std::vector<std::string> words{ "oath","pea","eat","rain" };
    //std::vector<std::string> r = findWords(board, words);

    //216. Combination Sum III
    //std::vector<std::vector<int>> r = combinationSum3(4, 30);

    //221. Maximal Square
    //std::vector<std::vector<char>> matrix{
    //    {'1','1','1','0','1','1','1','1'},
    //    {'1','1','1','0','1','1','1','1'},
    //    {'1','1','1','0','1','1','1','1'}
    //};
    //int r = maximalSquare(matrix);

    //230. Kth Smallest Element in a BST
    int r = kthSmallest(toTree({ 5,3,6,2,4,null,null,1 }), 2);

    return 0;
}