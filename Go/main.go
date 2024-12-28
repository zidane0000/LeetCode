package main

import (
	"fmt"
	"math"
	"slices"
	"sort"
	"strconv"
	"strings"
)

// 2446. Determine if Two Events Have Conflict
// First solution runtime beats:100.00% memory beats: 83.33%
func haveConflict(event1 []string, event2 []string) bool {
	if event1[0] < event2[0] {
		return !(event1[1] < event2[0])
	} else {
		return !(event2[1] < event1[0])
	}
}

// 66. Plus One
// First solution runtime beats:100.00% memory beats:16.83%
func plusOne(digits []int) []int {
	current := len(digits) - 1
	for digits[current] == 9 {
		digits[current] = 0
		if current == 0 {
			digits = append([]int{0}, digits...)
		} else {
			current--
		}
	}
	digits[current]++
	return digits
}

// 1014. Best Sightseeing Pair
// First solution runtime beats:100.00% memory beats:28.57%
func maxScoreSightseeingPair(values []int) int {
	maxSpot, maxScore := 0, values[0]-1
	for i := 1; i < len(values); i++ {
		maxSpot = max(maxSpot-1, values[i-1]-1)
		maxScore = max(maxScore, maxSpot+values[i])
	}
	return maxScore
}

// 494. Target Sum
// First solution runtime beats:31.93% memory beats:85.29%
func findTargetSumWays(nums []int, target int) int {
	ans, n := 0, len(nums)
	var dp func(int, int)
	dp = func(sum, posi int) {
		if posi == n-1 {
			if sum+nums[posi] == target {
				ans++
			}

			if sum-nums[posi] == target {
				ans++
			}
		} else {
			dp(sum+nums[posi], posi+1)
			dp(sum-nums[posi], posi+1)
		}
	}

	dp(0, 0)

	return ans
}

// 61. Rotate List
// First solution runtime beats:100.00% memory beats:6.28%
func rotateRight(head *ListNode, k int) *ListNode {
	if head == nil || k == 0 {
		return head
	}

	n := 0
	NodeMap := make(map[int]*ListNode)

	for head != nil {
		NodeMap[n] = head
		n++
		head = head.Next
	}

	nMod := n - k%n
	if k%n == 0 {
		nMod = 0
	}
	head = NodeMap[nMod]
	if nMod > 0 {
		pre := NodeMap[nMod-1]
		pre.Next = nil
		NodeMap[n-1].Next = NodeMap[0]
	}

	return head
}

// 274. H-Index
// First solution runtime beats:100.00% memory beats:22.62%
func hIndex(citations []int) int {
	n := len(citations)
	possible := make([]int, n)

	for i := 0; i < n; i++ {
		for j := 0; j < min(n, citations[i]); j++ {
			possible[j]++
		}
	}

	for i := n - 1; i >= 0; i-- {
		if possible[i] > i {
			return i + 1
		}
	}
	return 0
}

// 88. Merge Sorted Array
// First solution runtime beats:100.00% memory beats:19.18%
// func merge(nums1 []int, m int, nums2 []int, n int) {
// 	i, j, k := 0, 0, 0
// 	nums1Copy := make([]int, m)
// 	copy(nums1Copy, nums1[:m])
// 	for i < m && j < n {
// 		if nums1Copy[i] < nums2[j] {
// 			nums1[k] = nums1Copy[i]
// 			i++
// 		} else {
// 			nums1[k] = nums2[j]
// 			j++
// 		}
// 		k++
// 	}

// 	for i < m {
// 		nums1[k] = nums1Copy[i]
// 		i++
// 		k++
// 	}

// 	for j < n {
// 		nums1[k] = nums2[j]
// 		j++
// 		k++
// 	}
// }

// Second solution runtime beats:100.00% memory beats:5.25%
func merge(nums1 []int, m int, nums2 []int, n int) {
	// sort from back
	i, j, k := m-1, n-1, m+n-1

	for i >= 0 && j >= 0 {
		if nums1[i] > nums2[j] {
			nums1[k] = nums1[i]
			i--
		} else {
			nums1[k] = nums2[j]
			j--
		}
		k--
	}

	for i >= 0 {
		nums1[k] = nums1[i]
		i--
		k--
	}

	for j >= 0 {
		nums1[k] = nums2[j]
		j--
		k--
	}
}

// 2471. Minimum Number of Operations to Sort a Binary Tree by Level
// First solution runtime beats:10.00% memory beats:60.00%
func minimumOperations(root *TreeNode) int {
	queue := []*TreeNode{root}
	queueValue := []int{root.Val}
	swap := 0

	var pickSmall func(slice []int) int
	pickSmall = func(slice []int) int {
		if len(slice) == 1 {
			return 0
		}

		smallIndex := 0
		for i := 1; i < len(slice); i++ {
			if slice[smallIndex] > slice[i] {
				smallIndex = i
			}
		}

		if smallIndex != 0 {
			temp := slice[smallIndex]
			slice[smallIndex] = slice[0]
			slice[0] = temp
			return 1 + pickSmall(slice[1:])
		}
		return 0 + pickSmall(slice[1:])
	}

	for len(queue) > 0 {
		swap += pickSmall(queueValue)

		nextQueue := []*TreeNode{}
		nextQueueValue := []int{}
		for _, q := range queue {
			if q.Left != nil {
				nextQueue = append(nextQueue, q.Left)
				nextQueueValue = append(nextQueueValue, q.Left.Val)
			}

			if q.Right != nil {
				nextQueue = append(nextQueue, q.Right)
				nextQueueValue = append(nextQueueValue, q.Right.Val)
			}
		}
		queue = nextQueue
		queueValue = nextQueueValue
	}

	return swap
}

// 399. Evaluate Division
// First solution runtime beats:100.00% memory beats:25.51%
func calcEquation(equations [][]string, values []float64, queries [][]string) []float64 {
	candidate := make(map[string][]string)
	equationsMap := make(map[string]float64)
	for i, equation := range equations {
		equationsMap[equation[0]+" "+equation[1]] = values[i]
		equationsMap[equation[1]+" "+equation[0]] = 1 / values[i]
		equationsMap[equation[0]+" "+equation[0]] = 1
		equationsMap[equation[1]+" "+equation[1]] = 1
		candidate[equation[0]] = append(candidate[equation[0]], equation[1])
		candidate[equation[1]] = append(candidate[equation[1]], equation[0])
	}

	var solve func(front, back string, visited map[string]bool) float64
	solve = func(front, back string, visited map[string]bool) float64 {
		if ans, exist := equationsMap[front+" "+back]; exist {
			return ans
		}

		if visited[front] {
			return -1.0
		}
		visited[front] = true

		for _, cand := range candidate[front] {
			if ans := solve(cand, back, visited); ans != -1.0 {
				equationsMap[front+" "+back] = equationsMap[front+" "+cand] * ans
				return equationsMap[front+" "+back]
			}
		}
		return -1.0
	}

	ans := []float64{}
	for _, query := range queries {
		visited := make(map[string]bool)
		ans = append(ans, solve(query[0], query[1], visited))
	}
	return ans
}

// 374. Guess Number Higher or Lower
// First solution runtime beats:71.07% memory beats:30.37%
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * func guess(num int) int;
 */
// func guessNumber(n int) int {
// 	left, right := 1, n
// 	for left < right {
// 		mid := left + (right-left)/2
// 		switch guess(mid) {
// 		case -1:
// 			right = mid - 1
// 		case 1:
// 			left = mid + 1
// 		case 0:
// 			return mid
// 		}
// 	}
// 	return left
// }

// 1046. Last Stone Weight
// First solution runtime beats:100.00% memory beats:23.16%
func lastStoneWeight(stones []int) int {
	for len(stones) > 1 {
		sort.Slice(stones, func(i, j int) bool {
			return stones[i] > stones[j]
		})

		if stones[0] == stones[1] {
			stones = stones[2:]
		} else if stones[0] > stones[1] {
			stones[1] = stones[0] - stones[1]
			stones = stones[1:]
		}
	}

	if len(stones) == 1 {
		return stones[0]
	}
	return 0
}

// 506. Relative Ranks
// Official solution runtime beats:49.53% memory beats:26.61%
// func findRelativeRanks(score []int) []string {
// 	n := len(score)
// 	scoreCopy := make([]int, n)
// 	copy(scoreCopy, score)

// 	scoreToIndex := make(map[int]int)
// 	for i := 0; i < n; i++ {
// 		scoreToIndex[scoreCopy[i]] = i
// 	}

// 	sort.Slice(scoreCopy, func(i, j int) bool {
// 		return scoreCopy[i] > scoreCopy[j]
// 	})

// 	rank := make([]string, n)
// 	for i := range score {
// 		if i == 0 {
// 			rank[scoreToIndex[scoreCopy[i]]] = "Gold Medal"
// 		} else if i == 1 {
// 			rank[scoreToIndex[scoreCopy[i]]] = "Silver Medal"
// 		} else if i == 2 {
// 			rank[scoreToIndex[scoreCopy[i]]] = "Bronze Medal"
// 		} else {
// 			rank[scoreToIndex[scoreCopy[i]]] = strconv.Itoa(i + 1)
// 		}
// 	}
// 	return rank
// }

// AI solution runtime beats:100.00% memory beats:11.93%
func findRelativeRanks(scores []int) []string {
	// Create a copy of the scores slice and sort it in descending order
	sortedScores := make([]int, len(scores))
	copy(sortedScores, scores)
	sort.Slice(sortedScores, func(i, j int) bool {
		return sortedScores[i] > sortedScores[j]
	})

	// Define medals for the top three ranks
	medals := []string{"Gold Medal", "Silver Medal", "Bronze Medal"}

	// Create a map to store the rank of each score
	rankMapping := make(map[int]string)
	for i, score := range sortedScores {
		if i < 3 {
			rankMapping[score] = medals[i]
		} else {
			rankMapping[score] = strconv.Itoa(i + 1)
		}
	}

	// Create the result slice with the ranks corresponding to the original scores
	result := make([]string, len(scores))
	for i, score := range scores {
		result[i] = rankMapping[score]
	}

	return result
}

// 1926. Nearest Exit from Entrance in Maze
// First solution runtime beats:63.16% memory beats:25.82%
// func nearestExit(maze [][]byte, entrance []int) int {
// 	m, n, thisStep := len(maze), len(maze[0]), 0
// 	xQueue, yQueue, nextXQueue, nextYQueue := []int{entrance[0]}, []int{entrance[1]}, []int{}, []int{}

// 	for len(xQueue) > 0 {
// 		for i := range xQueue {
// 			if thisStep > 0 && (xQueue[i] == 0 || xQueue[i] == m-1 || yQueue[i] == 0 || yQueue[i] == n-1) {
// 				return thisStep
// 			}

// 			if maze[xQueue[i]][yQueue[i]] == 'x' {
// 				continue
// 			}
// 			maze[xQueue[i]][yQueue[i]] = 'x'

// 			// up
// 			if xQueue[i] > 0 && maze[xQueue[i]-1][yQueue[i]] == '.' {
// 				fmt.Println(len(nextXQueue))
// 				nextXQueue = append(nextXQueue, xQueue[i]-1)
// 				nextYQueue = append(nextYQueue, yQueue[i])
// 			}

// 			// down
// 			if xQueue[i] < m-1 && maze[xQueue[i]+1][yQueue[i]] == '.' {
// 				nextXQueue = append(nextXQueue, xQueue[i]+1)
// 				nextYQueue = append(nextYQueue, yQueue[i])
// 			}

// 			// left
// 			if yQueue[i] > 0 && maze[xQueue[i]][yQueue[i]-1] == '.' {
// 				nextXQueue = append(nextXQueue, xQueue[i])
// 				nextYQueue = append(nextYQueue, yQueue[i]-1)
// 			}

// 			// left
// 			if yQueue[i] < n-1 && maze[xQueue[i]][yQueue[i]+1] == '.' {
// 				nextXQueue = append(nextXQueue, xQueue[i])
// 				nextYQueue = append(nextYQueue, yQueue[i]+1)
// 			}
// 		}

// 		thisStep++
// 		xQueue, yQueue = nextXQueue, nextYQueue
// 		nextXQueue, nextYQueue = []int{}, []int{}
// 	}

// 	return -1
// }

// https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/discuss/2835220/Go-Solution-BFS-oror-100-memory-oror-90%2B-runtime
// Network solution runtime beats:82.78% memory beats:97.18%
func nearestExit(maze [][]byte, entrance []int) int {
	queue := [][2]int{{entrance[0], entrance[1]}}
	m, n := len(maze), len(maze[0])
	maze[entrance[0]][entrance[1]] = '+'

	steps := 0
	for len(queue) > 0 {
		for _, point := range queue {
			queue = queue[1:]
			if (point[0] == m-1 || point[1] == n-1 || point[0] == 0 || point[1] == 0) && steps > 0 {
				return steps
			}
			for _, div := range [][]int{{1, 0}, {-1, 0}, {0, 1}, {0, -1}} {
				x, y := point[0]+div[0], point[1]+div[1]
				if x >= 0 && y >= 0 && x < m && y < n && maze[x][y] != '+' {
					queue = append(queue, [2]int{x, y})
					maze[x][y] = '+'
				}
			}
		}
		steps++
	}
	return -1
}

// 99. Recover Binary Search Tree
// https://leetcode.com/problems/recover-binary-search-tree/discuss/1962281/C%2B%2B-oror-Easy-to-understand
// Network solution runtime beats:100.00% memory beats:68.69%
func recoverTree(root *TreeNode) {
	// key point is inorder traversal Binary Search Tree, the number will be sort ascending
	// so if someone not sort ascending means it's a mistake
	var firstMistake, secondMistake *TreeNode
	pre := &TreeNode{Val: math.MinInt}
	var inorder func(*TreeNode)
	inorder = func(node *TreeNode) {
		if node == nil {
			return
		}

		inorder(node.Left)

		if firstMistake == nil && node.Val < pre.Val {
			firstMistake = pre
		}
		if firstMistake != nil && node.Val < pre.Val {
			secondMistake = node
		}
		pre = node

		inorder(node.Right)
	}

	inorder(root)

	temp := firstMistake.Val
	firstMistake.Val = secondMistake.Val
	secondMistake.Val = temp
}

// 94. Binary Tree Inorder Traversal
// First solution runtime beats:100.00% memory beats:35.33%
func inorderTraversal(root *TreeNode) []int {
	var ans []int
	var DFS func(*TreeNode)
	DFS = func(node *TreeNode) {
		if node == nil {
			return
		}

		if node.Left != nil {
			DFS(node.Left)
		}
		ans = append(ans, node.Val)

		if node.Right != nil {
			DFS(node.Right)
		}
	}
	DFS(root)

	return ans
}

// 1466. Reorder Routes to Make All Paths Lead to the City Zero
// https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/discuss/1833582/Go-Golang-DFS-Adjacency-List
// Network solution runtime beats:81.59% memory beats:34.52%
func minReorder(n int, connections [][]int) int {
	// Start at city 0
	// recursively check its neighbors
	// count outgoing edges

	neighbors := make(map[int][]int, n)
	for _, connection := range connections {
		neighbors[connection[0]] = append(neighbors[connection[0]], -connection[1]) // means arrow
		neighbors[connection[1]] = append(neighbors[connection[1]], connection[0])
	}

	visit := make([]bool, n)
	change := 0

	var DFS func(int)
	DFS = func(city int) {
		visit[city] = true
		for _, neighbor := range neighbors[city] {
			if neighbor < 0 {
				neighbor = -neighbor
				if !visit[neighbor] {
					change++
					DFS(neighbor)
				}
			} else {
				if !visit[neighbor] {
					DFS(neighbor)
				}
			}
		}
	}

	DFS(0)

	return change
}

// 547. Number of Provinces
// Official solution runtime beats:100.00% memory beats:76.26%
func findCircleNum(isConnected [][]int) int {
	n := len(isConnected)
	province := 0
	visit := make([]bool, n)
	var DFS func(int)
	DFS = func(city int) {
		visit[city] = true
		for i := 0; i < n; i++ {
			if isConnected[city][i] == 1 && !visit[i] {
				DFS(i)
			}
		}
	}

	for i := 0; i < n; i++ {
		if !visit[i] {
			province++
			DFS(i)
		}
	}
	return province
}

// 2825. Make String a Subsequence Using Cyclic Increments
// First solution runtime beats:100.00% memory beats:44.44%
func canMakeSubsequence(str1 string, str2 string) bool {
	index1, index2 := 0, 0
	for index1 < len(str1) && index2 < len(str2) {
		// also can rewrite to str1[index1] == str2[index2] || str1[index1] + 1 == str2[index2] || (str1[index1] == 'z' && (str2[index2] == 'a')
		if (str1[index1] == 'z' && (str2[index2] == 'z' || str2[index2] == 'a')) || (str2[index2]-str1[index1] < 2) {
			index2++
		}
		index1++
	}

	return index2 == len(str2)
}

// 2109. Adding Spaces to a String
// First solution Time Limit Exceeded
// func addSpaces(s string, spaces []int) string {
// 	ans := ""
// 	preSpace := 0
// 	for _, space := range spaces {
// 		ans = ans + s[preSpace:(space)] + " "
// 		println(ans)
// 		preSpace = space
// 	}
// 	ans = ans + s[preSpace:]

// 	return ans
// }

// https://leetcode.com/problems/adding-spaces-to-a-string/discuss/5137248/Go-Easy
// Network solution runtime beats:91.43% memory beats:85.37%
func addSpaces(s string, spaces []int) string {
	b := make([]uint8, 0, len(s)+len(spaces))

	for sIndex, spaceIndex := 0, 0; sIndex < len(s); sIndex++ {
		if spaceIndex < len(spaces) && sIndex == spaces[spaceIndex] {
			b = append(b, ' ')
			spaceIndex++
		}
		b = append(b, s[sIndex])
	}

	return string(b)
}

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
	fmt.Printf("66. Plus One: %v\n", plusOne([]int{0}))
	fmt.Printf("66. Plus One: %v\n", plusOne([]int{9, 9, 9}))
	fmt.Printf("66. Plus One: %v\n", plusOne([]int{1, 2, 3}))
	fmt.Printf("66. Plus One: %v\n", plusOne([]int{1, 9, 3}))

	// fmt.Printf("494. Target Sum: %v\n", findTargetSumWays([]int{1, 1, 1, 1, 1}, 3))
	// fmt.Printf("494. Target Sum: %v\n", findTargetSumWays([]int{1, 0}, 1))

	// fmt.Printf("61. Rotate List: %v\n", ListNodeToSlice(rotateRight(CreateListNode([]int{1}), 1)))
	// fmt.Printf("61. Rotate List: %v\n", ListNodeToSlice(rotateRight(CreateListNode([]int{0, 1, 2}), 4)))
	// fmt.Printf("61. Rotate List: %v\n", ListNodeToSlice(rotateRight(CreateListNode([]int{0, 1, 2}), 24)))

	// nums1 := []int{1, 2, 3, 0, 0, 0}
	// nums2 := []int{2, 5, 6}
	// merge(nums1, 3, nums2, 3)
	// fmt.Printf("88. Merge Sorted Array: %v\n", nums1)

	// fmt.Printf("2471. Minimum Number of Operations to Sort a Binary Tree by Level: %v\n", minimumOperations(CreateTreeNode([]int{1, 4, 3, 7, 6, 8, 5, -1, -1, -1, -1, 9, -1, 10})))

	// fmt.Printf("399. Evaluate Division: %v\n", calcEquation([][]string{{"1", "2"}, {"2", "3"}, {"3", "4"}}, []float64{3.0, 4.0, 5.0}, [][]string{{"2", "4"}}))

	// fmt.Printf("1046. Last Stone Weight: %v\n", lastStoneWeight([]int{1, 2, 9, 10, 4}))

	// fmt.Printf("506. Relative Ranks: %v\n", findRelativeRanks([]int{1, 2, 9, 10, 4}))

	// fmt.Printf("1926. Nearest Exit from Entrance in Maze: %v\n", nearestExit([][]byte{{'+', '+', '.', '+'}, {'.', '.', '.', '+'}, {'+', '+', '+', '.'}}, []int{1, 2}))
	// fmt.Printf("1926. Nearest Exit from Entrance in Maze: %v\n", nearestExit([][]byte{
	// 	{'+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '+'},
	// 	{'+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+'}},
	// 	[]int{42, 4}))

	// fmt.Printf("94. Binary Tree Inorder Traversal: %v\n", inorderTraversal(CreateTreeNode([]int{4, 2, 7, 1, 3})))

	// fmt.Printf("547. Number of Provinces: %v\n", findCircleNum([][]int{
	// 	{1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
	// 	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	// 	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	// 	{0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	// 	{0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
	// 	{0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	// 	{0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
	// 	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
	// 	{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0},
	// 	{0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},
	// 	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
	// 	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
	// 	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	// 	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
	// 	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}}))

	// fmt.Printf("2825. Make String a Subsequence Using Cyclic Increments: %v\n", canMakeSubsequence("a", "a"))
	// fmt.Printf("2825. Make String a Subsequence Using Cyclic Increments: %v\n", canMakeSubsequence("a", "abc"))
	// fmt.Printf("2825. Make String a Subsequence Using Cyclic Increments: %v\n", canMakeSubsequence("abc", "ad"))

	// fmt.Printf("2109. Adding Spaces to a String: %v\n", addSpaces("abc", []int{1, 2, 3}))
	// fmt.Printf("2109. Adding Spaces to a String: %v\n", addSpaces("abcdefg", []int{1, 2, 3}))

	// fmt.Printf("841. Keys and Rooms: %v\n", canVisitAllRooms([][]int{{1}, {2}, {3}, {}}))
	// fmt.Printf("841. Keys and Rooms: %v\n", canVisitAllRooms([][]int{{1, 3}, {3, 0, 1}, {2}, {0}}))

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
