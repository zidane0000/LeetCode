#include "Solution.h"
//#include "Solution_2020.h"

#define null -1

using std::cout;
using std::endl;


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
    TreeNode* root = nullptr;
    std::queue<TreeNode*> q;
    int i = 0;
    TreeNode* t = arr[i] == null ? nullptr : new TreeNode(arr[i]);
    root = t;
    q.push(root);
    i++;
    while (!q.empty() && i < arr.size()) {
        TreeNode* t1 = q.front();
        q.pop();
        if (t1 != nullptr) {
            t1->left = arr[i] == null ? nullptr : new TreeNode(arr[i]);
            q.push(t1->left);
            i++;
            if (i >= arr.size()) {
                break;
            }
            t1->right = arr[i] == null ? nullptr : new TreeNode(arr[i]);
            q.push(t1->right);
            i++;
        }
    }
    return root;
}

//Node* toNode(std::vector<int> arr) {
//    Node* root = NULL;
//    std::queue<Node*> q;
//    int i = 0;
//    Node* t = arr[i] == NULL ? NULL : new Node(arr[i]);
//    root = t;
//    q.push(root);
//    i++;
//    while (!q.empty() && i < arr.size()) {
//        Node* t1 = q.front();
//        q.pop();
//        if (t1 != NULL) {
//            t1->left = arr[i] == NULL ? NULL : new Node(arr[i]);
//            q.push(t1->left);
//            i++;
//            if (i >= arr.size()) {
//                break;
//            }
//            t1->right = arr[i] == NULL ? NULL : new Node(arr[i]);
//            q.push(t1->right);
//            i++;
//        }
//    }
//    return root;
//}

Node* toNode(std::vector<int> arr) {
    std::queue<Node*> q;
    int i = 0;
    Node* root = arr[i] == NULL ? NULL : new Node(arr[i]);
    q.push(root);
    i+=2;
    while (i < arr.size()) {        
        Node* t1 = q.front();

        if (arr[i] == NULL) {
            q.pop();
        }
        else {
            Node* child = new Node(arr[i]);
            t1->children.push_back(child);
            q.push(child);
        }
        i++;
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
    //cout << cache.get(1) << endl;       // returns 1
    //cache.put(3, 3);    // evicts key 2
    //cout << cache.get(2) << endl;       // returns -1 (not found)
    //cache.put(4, 4);    // evicts key 1
    //cout << cache.get(1) << endl;       // returns -1 (not found)
    //cout << cache.get(3) << endl;       // returns 3
    //cout << cache.get(4) << endl;       // returns 4

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

    //227. Basic Calculator II
    //int r = calculate("0-2147483647");
    //int r = calculate(" 3/2 ");
    //int r = calculate("1-1+1");

    //230. Kth Smallest Element in a BST
    //int r = kthSmallest(toTree({ 5,3,6,2,4,null,null,1 }), 2);

    //238. Product of Array Except Self
    //std::vector<int> nums = { 4,5,1,8,2 };
    //std::vector<int> r = productExceptSelf(nums);

    //239. Sliding Window Maximum
    //std::vector<int> nums{ 3,4,5,6,7 };
    //std::vector<int> r = maxSlidingWindow(nums, 1);

    //240. Search a 2D Matrix II
    //std::vector<std::vector<int>> matrix{
    //    {48, 65, 70, 113, 133, 163, 170, 216, 298, 389},
    //    {89, 169, 215, 222, 250, 348, 379, 426, 469, 554},
    //    {178, 202, 253, 294, 367, 392, 428, 434, 499, 651},
    //    {257, 276, 284, 332, 380, 470, 516, 561, 657, 698},
    //    {275, 331, 391, 432, 500, 595, 602, 673, 758, 783},
    //    {357, 365, 412, 450, 556, 642, 690, 752, 801, 887},
    //    {359, 451, 534, 609, 654, 662, 693, 766, 803, 964},
    //    {390, 484, 614, 669, 684, 711, 767, 804, 857, 1055},
    //    {400, 515, 683, 732, 812, 834, 880, 930, 1012, 1130},
    //    {480, 538, 695, 751, 864, 939, 966, 1027, 1089, 1224} };
    //bool r = searchMatrix2(matrix, 20);

    //242. Valid Anagram
    //bool r = isAnagram("dsaasd", "asddsa");

    //257. Binary Tree Paths
    //std::vector<std::string> r = binaryTreePaths(toTree({ 1, 2, 3, null, 5 }));

    //260. Single Number III
    //std::vector<int> nums{ 1, 2, 1, 3, 2, 5 };
    //std::vector<int> r = singleNumber3(nums);

    //264. Ugly Number II
    //int r = nthUglyNumber_network(10);

    //278. First Bad Version
    //int r = firstBadVersion(5);
    
    //287. Find the Duplicate Number
    //std::vector<int> nums{ 1,3,4,2,2, };
    //int r = findDuplicate(nums);

    //290. Word Pattern
    //bool r = wordPattern("abba", "dog cat cat dog");

    //295. Find Median from Data Stream
    //MedianFinder obj;
    //obj.addNum(-1);
    //cout << obj.findMedian() << endl;
    //obj.addNum(-2);
    //cout << obj.findMedian() << endl;
    //obj.addNum(-3);
    //cout << obj.findMedian() << endl;
    //obj.addNum(-4);
    //cout << obj.findMedian() << endl;
    //obj.addNum(-5);
    //cout << obj.findMedian() << endl;
    //obj.addNum(6);
    //cout << obj.findMedian() << endl;
    //obj.addNum(10);
    //cout << obj.findMedian() << endl;
    //obj.addNum(2);
    //cout << obj.findMedian() << endl;
    //obj.addNum(6);
    //cout << obj.findMedian() << endl;
    //obj.addNum(5);
    //cout << obj.findMedian() << endl;
    //obj.addNum(0);
    //cout << obj.findMedian() << endl;
    //obj.addNum(6);
    //cout << obj.findMedian() << endl;
    //obj.addNum(3);
    //cout << obj.findMedian() << endl;
    //obj.addNum(1);
    //cout << obj.findMedian() << endl;
    //obj.addNum(0);
    //cout << obj.findMedian() << endl;
    //obj.addNum(0);
    //cout << obj.findMedian() << endl;

    //307. Range Sum Query - Mutable
    //std::vector<int> nums{ 1,3,4,5 };
    //NumArray a(nums);
    //cout << a.sumRange(0, 2) << endl;
    //a.update(1, 2);
    //cout << a.sumRange(0, 2) << endl;

    //309. Best Time to Buy and Sell Stock with Cooldown
    //std::vector<int> prices{ 1,2,3,0,2 };
    //int r = maxProfit_Cooldown(prices);

    //310. Minimum Height Trees
    //std::vector<std::vector<int>> edges{ {1, 0},{1, 2},{1, 3} };
    //std::vector<int> r = findMinHeightTrees(4, edges);

    //313. Super Ugly Number
    //std::vector<int> primes{ 2,7,13,19 };
    //int r = nthSuperUglyNumber(12, primes);

    //315. Count of Smaller Numbers After Self
    //std::vector<int> nums{ 2,0,1 };
    //std::vector<int> r = countSmaller_network(nums);

    //316. Remove Duplicate Letters
    //std::string r = removeDuplicateLetters("bcabc");

    //322. Coin Change
    //std::vector<int> coins{ 186, 419, 83, 408 };
    //int r = coinChange_network(coins, 6249);

    //6. Zigzag Conversion
    //convert("ABCDEFG", 4);

    // 7. Reverse Integer
    //std::cout << (0 == reverse(1563847412)) << std::endl;
    //std::cout << (2147483641 == reverse(1463847412)) << std::endl;

    // 8. String to Integer (atoi)
    //std::cout << myatoi("-3147483647") << std::endl;
    //std::cout << myatoi("3147483647") << std::endl;
    //std::cout << myatoi("- 1234 to 4567") << std::endl;
    //std::cout << myatoi("+1234 to 4567") << std::endl;
    //std::cout << myatoi("12+34 to 4567") << std::endl;
    //std::cout << myatoi("-45") << std::endl;
    //std::cout << myatoi("+5") << std::endl;
    //std::cout << myatoi(".5") << std::endl;
    //std::cout << myatoi("579878 is integer 418") << std::endl;
    //std::cout << myatoi("579878000000000") << std::endl;
    //std::cout << myatoi("words and 987") << std::endl;

    // 13. Roman to Integer
    //std::cout << romanToInt("IV") << std::endl;
    //std::cout << romanToInt("DXL") << std::endl;
    //std::cout << romanToInt("LVIII") << std::endl;
    //std::cout << romanToInt("MCMXCIV") << std::endl;

    // 29. Divide Two Integers
    //std::cout << divide(-2147483648, 2) << std::endl;
    //std::cout << divide(-2147483648, -1) << std::endl;
    //std::cout << divide(-2147483647, -1) << std::endl;
    //std::cout << divide(2147483647, -1) << std::endl;
    //std::cout << divide(2147483647, 1) << std::endl;

    // 543. Diameter of Binary Tree
    //TreeNode* tree = toTree({ 4,-7,-3,null,null,-9,-3,9,-7,-4,null,6,null,-6,-6,null,null,0,6,5,null,9,null,null,-1,-4,null,null,null,-2 }); // expect 8
    //std:cout << diameterOfBinaryTree(tree) << std::endl;

    // 347. Top K Frequent Elements
    //std::vector<int> v({ 4, 1, -1, 2, -1, 2, 3 });
    //std::vector<int> ans = topKFrequent(v, 2);
    //for (int i : ans)
    //    std::cout << i << ' ';

    // 378. Kth Smallest Element in a Sorted Matrix
    //std::vector<std::vector<int>> matrix{ {1, 5, 9},{10, 11, 13},{12, 13, 15} };
    //std::cout << kthSmallest(matrix, 8) << std::endl;

    //394. Decode String
    //std::cout << decodeString("3[z]2[2[y]pq4[2[jk]e1[f]]]ef") << std::endl;
    //std::cout << decodeString("abc3[cd]xyz") << std::endl;
    //std::cout << decodeString("2[abc]3[cd]ef") << std::endl;
    //std::cout << decodeString("3[a2[c]]") << std::endl;

    //437. Path Sum III
    //TreeNode* root = toTree({ 5,4,8,11,null,13,4,7,2,null,null,5,1 }); // expect 8
    //std::cout << pathSum3(root, 22) << std::endl;
    
    //560. Subarray Sum Equals K
    //std::vector<int> nums({ 1,2,3,-3 });
    //std::cout << subarraySum(nums, 3) << std::endl;

    //1448. Count Good Nodes in Binary Tree
    //TreeNode* root = toTree({ -4,-4,5,null,null,4,-5,-5,2,1,null,null,-2,null,5,null,null,null,-4,null,null,-4,null,2,null,-1 });
    //std::cout << goodNodes(root) << std::endl;

    //54. Spiral Matrix
    //std::vector<std::vector<int>> matrix{ {1,2,3}, {4,5,6}, {7,8,9} };
    //std::vector<std::vector<int>> matrix{ {1}, {4}, {7} };
    //std::vector<int> ans = spiralOrder(matrix);
    //for (auto a : ans)
    //    std::cout << a << " ";

    //739. Daily Temperatures
    //std::vector<int> temperatures = { 73,74,75,71,69,72,76,73 };
    //std::vector<int> ans = dailyTemperatures(temperatures);
    //for (auto a : ans)
    //    std::cout << a << " ";

    //637. Average of Levels in Binary Tree
    //TreeNode* root = toTree({ 3,9,20,15,7 });
    //std::vector<double> ans = averageOfLevels(root);

    //967. Numbers With Same Consecutive Differences
    //std::vector<int> ans = numsSameConsecDiff(2, 0);
    //for (auto a : ans)
    //    std::cout << a << " ";

    //2399. Check Distances Between Same Letters
    //std::vector<int> distance({ 1,3,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 });
    //std::cout << checkDistances("abaccb", distance) << endl;
    
    //2400. Number of Ways to Reach a Position After Exactly k Steps
    //std::cout << numberOfWays(1, 4, 7) << std::endl;

    //2401. Longest Nice Subarray
    //std::vector<int> nums({ 84139415,693324769,614626365,497710833,615598711,264,65552,50331652,1,1048576,16384,544,270532608,151813349,221976871,678178917,845710321,751376227,331656525,739558112,267703680 });
    //std::vector<int> nums({ 3,1,5,11,13 });
    //std::cout << longestNiceSubarray(nums) << std::endl;

    //2402. Meeting Rooms III
    //int mostBooked(int n, std::vector<std::vector<int>>& meetings)

    //987. Vertical Order Traversal of a Binary Tree
    //TreeNode* root = toTree({ -1,10,1,null,null,2,4,3,5,null,null,6,null,7,9,8,null,null,null,null,11,null,null,12 });
    //std::vector<std::vector<int>> ans = verticalTraversal(root);
    //for (auto vec : ans) {
    //    for (auto i : vec) {
    //        std::cout << i << " ";
    //    }
    //    std::cout << std::endl;
    //}

    //429. N-ary Tree Level Order Traversal
    //Node* root = toNode({ 1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14 });
    //std::vector<std::vector<int>> ans = levelOrder(root);
    //for (auto vec : ans) {
    //    for (auto i : vec) {
    //        std::cout << i << " ";
    //    }
    //    std::cout << std::endl;
    //}

    //814. Binary Tree Pruning
    //TreeNode* root = toTree({ 0,null,0,1,1,null,1,null,1,null,null,null,null });
    //TreeNode* res = pruneTree(root);

    //606. Construct String from Binary Tree
    //std::cout << tree2str(toTree({1,2,3,4})) << std::endl;

    //94. Binary Tree Inorder Traversal
    //TreeNode* root = toTree({ 1,2,3,null,4,null,5,6,7,8 };
    //std::vector<int> res = inorderTraversal(root);
    //for (int i : res) {
    //    std::cout << i << "  ";
    //}

    //1996. The Number of Weak Characters in the Game
    //std::vector<std::vector<int>> properties({ {1,1}, {1,2}, {2,2}, {2,1} });
    //std::vector<std::vector<int>> properties({ {5,5}, {6,3}, {3,6} });
    //std::vector<std::vector<int>> properties({ {7, 7}, {1, 2}, {9, 7}, {7, 3}, {3, 10}, {9, 8}, {8, 10}, {4, 3}, {1, 5}, {1, 5} });
    //std::cout << numberOfWeakCharacters(properties) << std::endl;

    //188. Best Time to Buy and Sell Stock IV
    //std::vector<int> prices({2,1,0,7,4,10,9});
    //std::cout << maxProfitIV(3, prices) << std::endl;

    //1137. N-th Tribonacci Number
    //std::cout << tribonacci(4) << std::endl;

    //Weekly Contest 310
    //Most Frequent Even Element
    //std::vector<int> nums({ 29,47,21,41,13,37,25,7 });
    //std::cout << mostFrequentEven(nums) << std::endl;

    //Optimal Partition of String
    //std::cout << partitionString("abacaba") << std::endl; // expected 4

    //Divide Intervals Into Minimum Number of Groups
    //std::vector<std::vector<int>> intervals({{5, 10}, {6, 8}, {1, 5}, {2, 3}, {1, 10}} );
    //std::vector<std::vector<int>> intervals({{351436, 933571}, {667214, 975379}, {782454, 919174}, {231661, 764081}, {848495, 902497}, {332817, 520328}, {740795, 762394}, {665739, 726786}, {546865, 686588}, {360501, 846864}} );
    //std::cout << minGroups(intervals) << std::endl; // expected 4

    //70. Climbing Stairs
    //std::cout << climbStairs(15) << std::endl;

    //746. Min Cost Climbing Stairs
    //std::vector<int> cost({10, 15, 20, 40});
    //std::cout << minCostClimbingStairs(cost) << std::endl;

    //1383. Maximum Performance of a Team
    //std::vector<int> speed({ 2,10,3,1,5,8 });
    //std::vector<int> efficiency({ 5,4,3,9,7,2 });
    //std::cout << maxPerformance(6, speed, efficiency, 3) << std::endl;

    //198. House Robber
    //std::vector<int> nums({ 2,7,9,3,1 });
    //std::cout << rob(nums) << std::endl;

    //213. House Robber II
    //std::vector<int> nums({1,2,3,1 });
    //std::cout << rob2(nums) << std::endl;

    //948. Bag of Tokens
    //std::vector<int> tokens({100, 200});
    //std::cout << bagOfTokensScore(tokens, 150) << std::endl;

    //393. UTF-8 Validation
    //std::vector<int> data({ 235,140,4 });
    //std::cout << validUtf8(data) << std::endl;

    //55. Jump Game
    //std::vector<int> nums({ 2,4,1,1,4 });
    //std::cout << canJump(nums) << std::endl;

    //45. Jump Game II
    //std::vector<int> nums({ 2,3,1,1,4 });
    //std::cout << jump(nums) << std::endl;

    //1457. Pseudo-Palindromic Paths in a Binary Tree
    //TreeNode* root = toTree({ 2,3,1,3,1,null,1 });
    //std::cout << pseudoPalindromicPaths(root)<< std::endl;     

    //918. Maximum Sum Circular Subarray
    //std::vector<int> nums({ -1,3,-3,9,-6,8,-5,-5,-6,10 });
    //cout << maxSubarraySumCircular(nums) << endl;

    //2007. Find Original Array From Doubled Array
    //std::vector<int> changed({2,1,2,4,2,4});
    //std::vector<int> ans = findOriginalArray(changed);
    //for (int i : ans)
    //    cout << i << endl;

    //152. Maximum Product Subarray
    //std::vector<int> nums({ -2,-1,0,1,-1,3,-2 });
    //cout << maxProduct(nums) << endl;

    //1567. Maximum Length of Subarray With Positive Product
    //std::vector<int> nums({ 1,2,3,5,-6,4,0,10 });
    //std::vector<int> nums({ 5,-20,-20,-39,-5,0,0,0,36,-32,0,-7,-10,-7,21,20,-12,-34,26,2 });
    //cout << getMaxLen(nums) << endl;

    //1770. Maximum Score from Performing Multiplication Operations
    //std::vector<int> nums({ -5,-3,-3,-2,7,1 });
    //std::vector<int> multipliers({ -10,-5,3,4,6 });
    //cout << maximumScore(nums, multipliers) << endl;

    //336. Palindrome Pairs
    //std::vector<std::string> words({ "abcd","dcba","lls","s","sssll" });
    //std::vector<std::vector<int>> ans = palindromePairs(words);
    //for (auto a : ans)
    //    cout << "[" << a[0] << "," << a[1] << "]" << endl;

    //42. Trapping Rain Water
    //std::vector<int> height({ 0,1,0,2,1,0,1,3,2,1,2,1 });
    //cout << trap(height) << endl;

    //609. Find Duplicate File in System
    //std::vector<std::string> paths({ "root/a 1.txt(abcd) 2.txt(efsfgh)","root/c 3.txt(abdfcd)","root/c/d 4.txt(efggdfh)" });
    //std::vector<std::vector<std::string>> ans = findDuplicate(paths);

    //718. Maximum Length of Repeated Subarray
    //std::vector<int> nums1({ 1,2,3,2,1 });
    //std::vector<int> nums2({ 3,2,1,4,7 });
    //cout << findLength(nums1, nums2) << endl;

    //121. Best Time to Buy and Sell Stock
    //std::vector<int> prices({ 3,2,1,9,3,4,7 });
    //cout << maxProfit(prices) << endl;

    //985. Sum of Even Numbers After Queries
    //std::vector<int> nums({ 1,2,3,4 });
    //std::vector<std::vector<int>> queries({ {1,0},{-3,1},{-4,0},{2,3} });
    //std::vector<int> ans = sumEvenAfterQueries(nums, queries);

    //309. Best Time to Buy and Sell Stock with Cooldown
    //std::vector<int> prices({ 1,3,9,1,3,8 });
    //cout << maxProfit(prices) << endl;

    //557. Reverse Words in a String III
    //std::string s = "Let's take LeetCode contest";
    //cout << reverseWords(s) << endl;

    //139. Word Break
    //std::vector<std::string> wordDict({ "a", "abc", "b", "cd" });
    //cout << wordBreak("abcd",wordDict) << endl;

    //42. Trapping Rain Water
    //std::vector<int> height({ 0,1,0,2,1,0,1,3,2,1,2,1 });
    //cout << trap(height) << endl;

    //1680. Concatenation of Consecutive Binary Numbers
    //cout << concatenatedBinary(12) << endl;

    //113. Path Sum II
    //TreeNode* root = toTree({ 5,4,8,11,null,13,4,7,2,null,null,5,1 });
    //int targetSum = 22;
    //std::vector<std::vector<int>> ans = pathSum(root, targetSum);

    //Longest Subarray With Maximum Bitwise AND
    //std::vector<int> nums({ 96317,96317,96317,96317,96317,96317,96317,96317,96317,279979 });
    //cout << longestSubarray(nums) << endl;

    //Find All Good Indices
    //std::vector<int> nums({ 87,20,17,9,3,32,47,59,84,97 });
    //std::vector<int> nums({ 600893, 574876, 721681, 967255, 165135, 675265, 231773, 201242, 11638, 6145, 355, 81, 75, 34, 23, 21, 17, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2644, 637527, 862482, 995085, 997146, 999484, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000 });
    //std::vector<int> nums({ 253747, 459932, 263592, 354832, 60715, 408350, 959296 });
    //std::vector<int> ans = goodIndices(nums, 2);

    //990. Satisfiability of Equality Equations
    //std::vector<std::string>equations({ "a!=b","b==c","c==a", "d!=a", "g==q", "g==p" });
    //std::vector<std::string>equations({ "b!=f", "c!=e", "f==f", "d==f", "b==f", "a==f" });
    //std::vector<std::string>equations({ "n!=p", "i!=b", "d!=e", "m!=y", "v==e", "m==y", "x==x", "w==r", "t==l", "r!=i", "p!=b", "f==p", "y==x" });    
    //std::vector<std::string>equations({ "a==b", "a==c", "b==c", "a!=e" });
    //cout << equationsPossible(equations) << endl;

    //838. Push Dominoes
    //std::string dominoes = "..R.....LR..";
    //cout << pushDominoes(dominoes) << endl;

    //91. Decode Ways
    //cout << numDecodings("10") << endl;

    //19. Remove Nth Node From End of List
    //ListNode* r = removeNthFromEnd(toList({1}), 1);

    //658. Find K Closest Elements
    //std::vector<int> arr({ -2, -1, 1, 2, 4, 4, 5 });
    //std::vector<int> arr({ 0, 0, 0, 1, 3, 5, 6, 7, 8, 8 });
    //std::vector<int> arr({ 1,2,3,4,5 });
    //std::vector<int> arr({ 1,1,1,10,10,10 });
    //std::vector<int> ans = findClosestElements(arr, 6, 3);

    //264. Ugly Number II
    //cout << nthUglyNumber(10) << endl;

    //96. Unique Binary Search Trees
    //cout << numTrees(10) << endl;


    //Maximum Sum of an Hourglass
    //std::vector < std::vector<int>> grid({ {1,2,3} ,{4,5,6},{7,8,9} });
    //cout << maxSum(grid) << endl;

    //Minimize XOR
    //cout << minimizeXor(79, 74) << endl;

    //Maximum Deletions on a String
    //cout << deleteString("aaabaab") << endl;

    //1155. Number of Dice Rolls With Target Sum
    //cout << numRollsToTarget(30, 30, 500) << endl;

    //118. Pascal's Triangle
    //std::vector<std::vector<int>> ans = generate(5);

    //119. Pascal's Triangle II
    //std::vector<int> ans = getRow(5);

    //120. Triangle
    //std::vector<std::vector<int>> triangle({ {1},{2,3},{4,5,6},{7,8,9,10} });
    //cout << minimumTotal(triangle) << endl;

    //1314. Matrix Block Sum
    //std::vector<std::vector<int>> mat({ {67, 64, 78}, {99, 98, 38}, {82, 46, 46}, {6, 52, 55}, {55, 99, 45} });
    //std::vector<std::vector<int>> mat({ { 1,2,3 }, {1,2,3},{1,2,3} });
    //std::vector<std::vector<int>> ans = matrixBlockSum(mat, 3);

    //304. Range Sum Query 2D - Immutable
    //std::vector<std::vector<int>> matrix({{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}});
    //NumMatrix nummatrix(matrix);
    //cout << nummatrix.sumRegion(2, 1, 4, 3) << endl;
    //cout << nummatrix.sumRegion(1, 1, 2, 2) << endl;
    //cout << nummatrix.sumRegion(1, 2, 2, 4) << endl;

    //981. Time Based Key - Value Store
    //TimeMap timeMap;
    //timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
    //cout << timeMap.get("foo", 1) << endl;         // return "bar"
    //cout << timeMap.get("foo", 3) << endl;         // return "bar", since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
    //timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
    //cout << timeMap.get("foo", 4) << endl;         // return "bar2"
    //cout << timeMap.get("foo", 5) << endl;         // return "bar2"

    //732. My Calendar III
    //MyCalendarThree myCalendarThree;
    //myCalendarThree.book(10, 20); // return 1, The first event can be booked and is disjoint, so the maximum k-booking is a 1-booking.
    //myCalendarThree.book(50, 60); // return 1, The second event can be booked and is disjoint, so the maximum k-booking is a 1-booking.
    //myCalendarThree.book(10, 40); // return 2, The third event [10, 40) intersects the first event, and the maximum k-booking is a 2-booking.
    //myCalendarThree.book(5, 15); // return 3, The remaining events cause the maximum K-booking to be only a 3-booking.
    //myCalendarThree.book(5, 10); // return 3
    //myCalendarThree.book(25, 55); // return 3

    //334. Increasing Triplet Subsequence
    //std::vector<int> nums({ 1,5,0,7 });
    //cout << increasingTriplet(nums) << endl;  // true

    //976. Largest Perimeter Triangle
    //std::vector<int> nums({ 1,5,0,7 });
    //cout << largestPerimeter(nums) << endl;

    //2095. Delete the Middle Node of a Linked List
    //ListNode* node = deleteMiddle(toList({2,1}));
    
    //1335. Minimum Difficulty of a Job Schedule
    //std::vector<int> jobDifficulty({ 11, 111, 22, 222, 33, 333, 44, 444 });
    //cout << minDifficulty(jobDifficulty, 6) << endl;

    //221. Maximal Square
    //std::vector<std::vector<char>> matrix({ {'0','1'},{'1','0'} });
    //cout << maximalSquare(matrix) << endl;

    //692. Top K Frequent Words
    //std::vector<std::string>words({ "i","love","leetcode","i","love","coding" });
    //std::vector<std::string> ans = topKFrequent(words, 2);

    //5. Longest Palindromic Substring
    //cout << longestPalindrome("babad") << endl;
    //cout << longestPalindrome("cbbd") << endl;

    //516. Longest Palindromic Subsequence
    //cout << longestPalindromeSubseq("bbbdb") << endl;

    //76. Minimum Window Substring
    //cout << minWindow("saabcdafsz", "sz") << endl;

    //std::vector<std::string> event1({"04:00","05:00"});
    //std::vector<std::string> event2({"03:00","04:00"});
    //cout << haveConflict(event1, event2) << endl;

    //std::vector<int> nums({ 9,3,1,2,6,3 });
    //cout << subarrayGCD(nums, 3) << endl;

    //1239. Maximum Length of a Concatenated String with Unique Characters
    std::vector<std::string> arr({ "a", "abc", "d", "de", "def" });
    cout << maxLength(arr) << endl;

    return 0;
}
