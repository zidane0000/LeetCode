package main

import (
	"fmt"
	"math"
	"slices"
	"strconv"
	"strings"
)

// 841. Keys and Rooms
// First solution runtime beats:100.00% memory beats:12.18%
// func canVisitAllRooms(rooms [][]int) bool {
// 	count := len(rooms)
// 	IsOpen := make(map[int]bool, count)
// 	IsOpen[0] = true
// 	canOpen := rooms[0]
// 	i := 0
// 	for i < len(canOpen) {
// 		println(canOpen[i])
// 		fmt.Printf("IsOpen:%v\n", IsOpen)
// 		if !IsOpen[canOpen[i]] {
// 			IsOpen[canOpen[i]] = true
// 			canOpen = append(canOpen, rooms[canOpen[i]]...)
// 			count--
// 		}
// 		i++
// 	}
// 	return count == 1
// }

// https://leetcode.com/problems/keys-and-rooms/discuss/3603371/O(n%2Be)-DFS-Runtime-100-or-Memory-92.6
// Network solution runtime beats:100.00% memory beats:33.97%
func canVisitAllRooms(rooms [][]int) bool {
	counter := 0
	visitedRooms := make([]bool, len(rooms))

	var walkRoom func(int)
	walkRoom = func(room int) {
		if visitedRooms[room] {
			return
		}
		visitedRooms[room] = true
		counter++
		for _, rm := range rooms[room] {
			walkRoom(rm)
		}
	}

	walkRoom(0)

	return counter == len(rooms)
}

// 1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence
// First solution runtime beats:100.00% memory beats:33.33%
func isPrefixOfWord(sentence string, searchWord string) int {
	words := strings.Split(sentence, " ")
	for i, word := range words {
		if strings.HasPrefix(word, searchWord) {
			return i + 1
		}
	}
	return -1
}

// 450. Delete Node in a BST
// comment from skyblue_cat in https://leetcode.com/problems/delete-node-in-a-bst/discuss/93296/Recursive-Easy-to-Understand-Java-Solution
// Network solution runtime beats:100.00% memory beats:13.89%
func deleteNode(root *TreeNode, key int) *TreeNode {
	if root == nil {
		return nil
	}

	if root.Val > key {
		root.Left = deleteNode(root.Left, key)
	} else if root.Val < key {
		root.Right = deleteNode(root.Right, key)
	} else {
		if root.Left == nil {
			return root.Right
		}
		if root.Right == nil {
			return root.Left
		}

		// key is set root left to right smallest node left
		rightSmallest := root.Right
		for rightSmallest.Left != nil {
			rightSmallest = rightSmallest.Left
		}
		rightSmallest.Left = root.Left
		return root.Right
	}
	return root
}

// 700. Search in a Binary Search Tree
// First solution runtime beats:100.00% memory beats:6.82%
// func searchBST(root *TreeNode, val int) *TreeNode {
// 	queue := []*TreeNode{root}
// 	nextQueue := []*TreeNode{}

// 	for len(queue) != 0 {
// 		for _, candidate := range queue {
// 			if candidate.Val == val {
// 				return candidate
// 			}

// 			if candidate.Left != nil {
// 				nextQueue = append(nextQueue, candidate.Left)
// 			}
// 			if candidate.Right != nil {
// 				nextQueue = append(nextQueue, candidate.Right)
// 			}
// 		}
// 		queue = nextQueue
// 		nextQueue = []*TreeNode{}
// 	}

// 	return nil
// }

// Second solution runtime beats:100.00% memory beats:51.85%
func searchBST(root *TreeNode, val int) *TreeNode {
	if root == nil || root.Val == val {
		return root
	}

	if root.Val > val {
		return searchBST(root.Left, val)
	}
	return searchBST(root.Right, val)
}

// 1372. Longest ZigZag Path in a Binary Tree
// First solution runtime beats:57.14% memory beats:16.08%
// func longestZigZag(root *TreeNode) int {
// 	max := func(a int, b int) int {
// 		if a > b {
// 			return a
// 		} else {
// 			return b
// 		}
// 	}

// 	// direction: 0 means left, 1 means right
// 	var zigZag func(node *TreeNode, len int, direction int) int
// 	zigZag = func(node *TreeNode, len int, direction int) int {
// 		if node == nil {
// 			return len - 1
// 		}

// 		var leftLen, rightLin int
// 		if direction == 0 {
// 			leftLen = zigZag(node.Left, 1, 0)
// 			rightLin = zigZag(node.Right, len+1, 1)
// 		} else {
// 			leftLen = zigZag(node.Left, len+1, 0)
// 			rightLin = zigZag(node.Right, 1, 1)
// 		}

// 		return max(leftLen, rightLin)
// 	}

// 	return max(zigZag(root.Left, 1, 0), zigZag(root.Right, 1, 1))
// }

// https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/discuss/6032839/EASY-oror-94-BEATS-PROOF-oror-JAVA-oror-BEGINNER-FRIENDLY-oror-DETAILED-EXPLANATION
// Network solution runtime beats:98.41% memory beats:73.37%
func longestZigZag(root *TreeNode) int {
	max := func(a int, b int) int {
		if a > b {
			return a
		}
		return b
	}

	longestLen := math.MinInt

	// direction: 0 means left, 1 means right
	var zigZag func(node *TreeNode, len int, isLeft bool)
	zigZag = func(node *TreeNode, len int, isLeft bool) {
		if node == nil {
			return
		}

		longestLen = max(longestLen, len)

		if isLeft {
			zigZag(node.Left, 1, true)
			zigZag(node.Right, len+1, false)
		} else {
			zigZag(node.Left, len+1, true)
			zigZag(node.Right, 1, false)
		}
	}

	zigZag(root.Left, 1, true)
	zigZag(root.Right, 1, false)

	return longestLen
}

// 1161. Maximum Level Sum of a Binary Tree
// First solution runtime beats:89.14% memory beats:32.38%
func maxLevelSum(root *TreeNode) int {
	var currentLevel, maxLevel, maxLevelSum, levelSum int = 1, 0, math.MinInt, 0
	var levelQueue, nextQueue []*TreeNode = []*TreeNode{root}, []*TreeNode{}

	// Breadth-first search
	for len(levelQueue) != 0 {
		for _, node := range levelQueue {
			levelSum += node.Val
			if node.Left != nil {
				nextQueue = append(nextQueue, node.Left)
			}
			if node.Right != nil {
				nextQueue = append(nextQueue, node.Right)
			}
		}

		if maxLevelSum < levelSum {
			maxLevelSum = levelSum
			maxLevel = currentLevel
		}

		levelSum = 0
		levelQueue = nextQueue
		currentLevel++
		nextQueue = []*TreeNode{}
	}
	return maxLevel
}

// 872. Leaf-Similar Trees
// First solution runtime beats:100.00% memory beats:21.52%
// func leafSimilar(root1 *TreeNode, root2 *TreeNode) bool {
// 	var findLeaf func(root *TreeNode, LeafList *[]*TreeNode)
// 	findLeaf = func(root *TreeNode, LeafList *[]*TreeNode) {
// 		if root.Left != nil {
// 			findLeaf(root.Left, LeafList)
// 		}

// 		if root.Right != nil {
// 			findLeaf(root.Right, LeafList)
// 		}

// 		if root.Left == nil && root.Right == nil {
// 			*LeafList = append(*LeafList, root)
// 		}
// 	}

// 	var LeafList1, LeafList2 []*TreeNode
// 	findLeaf(root1, &LeafList1)
// 	findLeaf(root2, &LeafList2)

// 	if len(LeafList1) != len(LeafList2) {
// 		return false
// 	}

// 	for index, Leaf := range LeafList1 {
// 		if LeafList2[index].Val != Leaf.Val {
// 			return false
// 		}
// 	}

// 	return true
// }

// https://leetcode.com/problems/leaf-similar-trees/discuss/2888866/Go
// Network solution runtime beats:100.00% memory beats:5.76%
// func leafSimilar(root1 *TreeNode, root2 *TreeNode) bool {
// 	// define inner function to get leaf TreeNode Val
// 	var getLeafVal func(root *TreeNode, vals *[]int)
// 	getLeafVal = func(root *TreeNode, vals *[]int) {
// 		if root != nil {
// 			if (root.Left == nil) && (root.Right == nil) {
// 				*vals = append(*vals, root.Val)
// 				return
// 			}

// 			getLeafVal(root.Left, vals)
// 			getLeafVal(root.Right, vals)
// 		}
// 	}

// 	var leafVals1, leafVals2 []int
// 	getLeafVal(root1, &leafVals1)
// 	getLeafVal(root2, &leafVals2)

// 	return reflect.DeepEqual(leafVals1, leafVals2)
// }

// Second solution runtime beats:100.00% memory beats:5.76%
func leafSimilar(root1 *TreeNode, root2 *TreeNode) bool {
	var findLeaf func(root *TreeNode, LeafList *[]int)
	findLeaf = func(root *TreeNode, LeafList *[]int) {
		if root == nil {
			return
		} else if root.Left == nil && root.Right == nil {
			*LeafList = append(*LeafList, root.Val)
		} else {
			findLeaf(root.Left, LeafList)
			findLeaf(root.Right, LeafList)
		}
	}

	var LeafValList1, LeafValList2 []int
	findLeaf(root1, &LeafValList1)
	findLeaf(root2, &LeafValList2)

	return slices.Equal(LeafValList1, LeafValList2)
}

// 2130. Maximum Twin Sum of a Linked List
// First solution runtime beats:47.40% memory beats:55.05%
func pairSum(head *ListNode) int {
	// find the half of List
	var half, end *ListNode = head, head.Next
	for end.Next != nil {
		half = half.Next
		end = end.Next.Next
	}

	// reverse twins of List
	twinsHead := reverseList(half.Next)

	// find Maximum Twin Sum
	MaximumTwinSum := math.MinInt
	for head != nil && twinsHead != nil {
		if head.Val+twinsHead.Val > MaximumTwinSum {
			MaximumTwinSum = head.Val + twinsHead.Val
		}
		head = head.Next
		twinsHead = twinsHead.Next
	}

	return MaximumTwinSum
}

// 206. Reverse Linked List
// First solution runtime beats:100.00% memory beats:9.86%
func reverseList(head *ListNode) *ListNode {
	var pre, cur *ListNode = nil, head
	for cur != nil {
		next := cur.Next
		cur.Next = pre
		pre = cur
		cur = next
	}

	return pre
}

// 328. Odd Even Linked List
// First solution runtime beats:100.00% memory beats:11.33%
func oddEvenList(head *ListNode) *ListNode {
	if head == nil {
		return head
	}

	var current, tailHead, tailCurrent *ListNode = head, head.Next, head.Next
	for current.Next != nil && tailCurrent != nil {
		current.Next = tailCurrent.Next
		if current.Next != nil {
			current = current.Next
			if current != nil {
				tailCurrent.Next = current.Next
				tailCurrent = tailCurrent.Next
			}
		}
	}
	current.Next = tailHead
	return head
}

// 735. Asteroid Collision
// First solution runtime beats:100.00% memory beats:10.78%
func asteroidCollision(asteroids []int) []int {
	var ans []int
	for i := 0; i < len(asteroids); i++ {
		if len(ans) == 0 || asteroids[i] > 0 {
			ans = append(ans, asteroids[i])
		} else {
			posi := len(ans) - 1
			for posi >= 0 && ans[posi] > 0 && (ans[posi]+asteroids[i] < 0) {
				posi--
			}

			if posi < 0 {
				ans = []int{asteroids[i]}
			} else if ans[posi] < 0 {
				ans = append(ans[:posi+1], asteroids[i])
			} else {
				// ans[posi] is not less than asteroids[i]
				if ans[posi]+asteroids[i] == 0 {
					ans = ans[:posi]
				} else {
					ans = ans[:posi+1]
				}
			}
		}
	}

	return ans
}

// 933. Number of Recent Calls
// First solution runtime beats:86.22% memory beats:76.15%
type RecentCounter struct {
	record []int
}

func Constructor() RecentCounter {
	return RecentCounter{}
}

func (this *RecentCounter) Ping(t int) int {
	this.record = append(this.record, t)

	len := len(this.record)
	for i, v := range this.record {
		if t-v <= 3000 {
			this.record = this.record[i:]
			return len - i
		}
	}
	return 1
}

// 2390. Removing Stars From a String
// First solution runtime beats:35.90% memory beats:30.66%
func removeStars(s string) string {
	stack := []rune{}
	for _, c := range s {
		if c == '*' {
			stack = stack[:len(stack)-1]
		} else {
			stack = append(stack, c)
		}
	}

	return string(stack)
}

// 2352. Equal Row and Column Pairs
// First solution runtime beats:16.84% memory beats:5.03%
func equalPairs(grid [][]int) int {
	ans := 0
	var row, column string
	rowMap := map[string]int{}
	columnMap := map[string]int{}
	n := len(grid)

	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			row = row + "," + strconv.Itoa(grid[i][j])
			column = column + "," + strconv.Itoa(grid[j][i])
		}

		rowMap[row] += 1
		columnMap[column] += 1
		ans += columnMap[row]
		ans += rowMap[column]

		if row == column {
			// because calc one more time
			ans--
		}
		row = ""
		column = ""
	}

	return ans
}

// 1975. Maximum Matrix Sum
// First solution runtime beats:100.00% memory beats:71.43%
func maxMatrixSum(matrix [][]int) int64 {
	/*
		key: Since all negative adjacent pairs can multiply to a positive number,
			if the count of negative numbers is even, the result will be the sum of the others minus the minimum
	*/
	var total int64 = 0
	var absMin int64 = math.MaxInt64
	var abs int64 = 0
	negativeCount := 0
	n := len(matrix)

	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			if matrix[i][j] < 0 {
				negativeCount++
			}

			abs = Abs(int64(matrix[i][j]))
			if absMin > abs {
				absMin = abs
			}

			total += abs
		}
	}

	if negativeCount%2 == 0 {
		return total
	} else {
		return total - absMin*2
	}
}

func main() {
	fmt.Printf("841. Keys and Rooms: %v\n", canVisitAllRooms([][]int{{1}, {2}, {3}, {}}))
	fmt.Printf("841. Keys and Rooms: %v\n", canVisitAllRooms([][]int{{1, 3}, {3, 0, 1}, {2}, {0}}))

	// fmt.Println("450. Delete Node in a BST:")
	// PrintTree(deleteNode(CreateTreeNode([]int{4, 2, 7, 1, 3}), 2))
	// fmt.Println("450. Delete Node in a BST:")
	// PrintTree(deleteNode(CreateTreeNode([]int{4, 2, 7, 1, 3}), 3))
	// fmt.Println("450. Delete Node in a BST:")
	// PrintTree(deleteNode(CreateTreeNode([]int{4, 2, 7, 1, 3}), 5))

	// fmt.Printf("700. Search in a Binary Search Tree: %v\n", searchBST(CreateTreeNode([]int{4, 2, 7, 1, 3}), 3))
	// fmt.Printf("700. Search in a Binary Search Tree: %v\n", searchBST(CreateTreeNode([]int{4, 2, 7, 1, 3}), 5))

	// fmt.Printf("1372. Longest ZigZag Path in a Binary Tree: %v\n", longestZigZag(CreateTreeNode([]int{1, 1, 1, -1, 1, -1, -1, 1, 1, -1, 1})))
	// fmt.Printf("1372. Longest ZigZag Path in a Binary Tree: %v\n", longestZigZag(CreateTreeNode([]int{1})))

	// fmt.Printf("872. Leaf-Similar Trees: %v\n", leafSimilar(CreateTreeNode([]int{3, 5, 1, 6, 2, 9, 8, -1, -1, 7, 4}), CreateTreeNode([]int{3, 5, 1, 6, 7, 4, 2, -1, -1, -1, -1, -1, -1, 9, 8})))
	// fmt.Printf("872. Leaf-Similar Trees: %v\n", leafSimilar(CreateTreeNode([]int{1, 2, 3}), CreateTreeNode([]int{1, 3, 2})))

	// fmt.Printf("2130. Maximum Twin Sum of a Linked List: %v\n", pairSum(CreateListNode([]int{1, 2, 3, 40, 5, 6, 7, 8})))
	// fmt.Printf("2130. Maximum Twin Sum of a Linked List: %v\n", pairSum(CreateListNode([]int{1, 20, 3, 4, 5, 6, 7, 8})))
	// fmt.Printf("2130. Maximum Twin Sum of a Linked List: %v\n", pairSum(CreateListNode([]int{1, 2, 3, 4, 5, 6, 7, 8})))

	// fmt.Printf("206. Reverse Linked List: %v\n", ListNodeToSlice(reverseList(CreateListNode([]int{1, 2, 3, 4, 5, 6, 7, 8}))))

	// fmt.Printf("328. Odd Even Linked List: %v\n", ListNodeToSlice(oddEvenList(CreateListNode([]int{1, 2, 3, 4, 5, 6, 7, 8}))))
	// fmt.Printf("328. Odd Even Linked List: %v\n", ListNodeToSlice(oddEvenList(CreateListNode([]int{1, 2, 3, 4, 5}))))
	// fmt.Printf("328. Odd Even Linked List: %v\n", ListNodeToSlice(oddEvenList(CreateListNode([]int{2, 1, 3, 5, 6, 4, 7}))))
	// fmt.Printf("328. Odd Even Linked List: %v\n", ListNodeToSlice(oddEvenList(CreateListNode([]int{1, 3, 4}))))

	// fmt.Printf("933. Number of Recent Calls: %v\n", asteroidCollision([]int{8, -8}))
	// fmt.Printf("933. Number of Recent Calls: %v\n", asteroidCollision([]int{8, 1, 2, 3, 4, -8}))
	// fmt.Printf("933. Number of Recent Calls: %v\n", asteroidCollision([]int{9, 1, 2, 3, 4, -8}))
	// fmt.Printf("933. Number of Recent Calls: %v\n", asteroidCollision([]int{-2, -1, 1, 2}))
	// fmt.Printf("933. Number of Recent Calls: %v\n", asteroidCollision([]int{-2, -2, 1, -2}))

	// println("2390. Removing Stars From a String:", removeStars("leet**cod*e"))

	// println("1975. Maximum Matrix Sum:", maxMatrixSum([][]int{
	// 	{1, 2, 3},
	// 	{-1, -2, -3},
	// 	{1, 2, 3},
	// }))

	// println("2352. Equal Row and Column Pairs:", equalPairs([][]int{
	// 	{3, 1, 2, 2},
	// 	{1, 4, 4, 5},
	// 	{2, 4, 2, 2},
	// 	{2, 4, 2, 2},
	// }))
}
