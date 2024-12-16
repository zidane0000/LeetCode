package main

import "fmt"

func Abs[T int | int64](x T) T {
	if x < 0 {
		return -x
	}
	return x
}

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func CreateTreeNode(nums []int) *TreeNode {
	if len(nums) == 0 {
		return nil
	}

	root := &TreeNode{Val: nums[0]}
	queue := []*TreeNode{root}
	i := 1

	for i < len(nums) {
		current := queue[0]
		queue = queue[1:]

		if i < len(nums) && nums[i] != -1 {
			current.Left = &TreeNode{Val: nums[i]}
			queue = append(queue, current.Left)
		}
		i++

		if i < len(nums) && nums[i] != -1 {
			current.Right = &TreeNode{Val: nums[i]}
			queue = append(queue, current.Right)
		}
		i++
	}

	return root
}

// PrintTree prints the tree nodes in a level-order traversal.
func PrintTree(root *TreeNode) {
	if root == nil {
		fmt.Println("The tree is empty.")
		return
	}

	queue := []*TreeNode{root}

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		if current != nil {
			fmt.Print(current.Val, " ")
			queue = append(queue, current.Left)
			queue = append(queue, current.Right)
		} else {
			fmt.Print("nil ")
		}
	}
	fmt.Println()
}

type ListNode struct {
	Val  int
	Next *ListNode
}

func CreateListNode(nums []int) *ListNode {
	if len(nums) == 0 {
		return nil
	}

	head := &ListNode{Val: nums[0]}
	current := head

	for _, num := range nums[1:] {
		current.Next = &ListNode{Val: num}
		current = current.Next
	}

	return head
}

func ListNodeToSlice(head *ListNode) []int {
	var result []int
	current := head
	for current != nil {
		result = append(result, current.Val)
		current = current.Next
	}
	return result
}
