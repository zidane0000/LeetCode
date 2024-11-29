package main

import (
	"fmt"
	"math"
	"strconv"
)

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
	fmt.Printf("2130. Maximum Twin Sum of a Linked List: %v\n", pairSum(CreateListNode([]int{1, 2, 3, 40, 5, 6, 7, 8})))
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
