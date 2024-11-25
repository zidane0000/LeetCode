package main

import (
	"math"
	"strconv"
)

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
	println("2390. Removing Stars From a String:", removeStars("leet**cod*e"))

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
