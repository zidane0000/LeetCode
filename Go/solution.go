package main

import (
	"strings"
	"unicode"
)

// 125. Valid Palindrome
// First solution runtime beats:21.79%  memory beats:30.24%
// func isPalindrome(s string) bool {
// 	reg, _ := regexp.Compile("[^a-zA-Z0-9]+")
// 	s = reg.ReplaceAllString(s, "")
// 	s = strings.ToLower(s)

// 	i := 0
// 	k := len(s) - 1
// 	for i < k {
// 		if s[i] != s[k] {
// 			return false
// 		}
// 		i++
// 		k--
// 	}
// 	return true
// }

// Second solution runtime beats:37.77%  memory beats:54.80%
func isPalindrome(s string) bool {
	s = strings.ToLower(s)
	isAlnum := func(r rune) bool {
		return unicode.IsLetter(r) || unicode.IsDigit(r)
	}

	i := 0
	k := len(s) - 1
	for i < k {
		if !isAlnum(rune(s[i])) {
			i++
			continue
		}
		if !isAlnum(rune(s[k])) {
			k--
			continue
		}

		if s[i] != s[k] {
			return false
		}
		i++
		k--
	}

	return true
}

// 2062. Count Vowel Substrings of a String
// https://leetcode.com/problems/count-vowel-substrings-of-a-string/solutions/1563737/sliding-window/
// Network solution runtime beats:21.79%  memory beats:30.24%
func countVowelSubstrings(w string) int {
	// Mark windowStart(start of an "all-vowel" substring). We advance it every time we see a consonant
	// Mark the current position, and the smallest window with all 5 vowels.
	distinctVowels := 0              // Count of distinct vowels in current window
	totalCount := 0                  // Result: total valid substrings
	vowelCount := make(map[rune]int) // Tracks frequency of each vowel
	vowels := "aeiou"                // Valid vowel set
	windowStart, shrinkPos := 0, 0   // Sliding window pointers

	for currentPos, char := range w {
		if strings.ContainsRune(vowels, char) {
			// Update counts for current character
			vowelCount[char]++
			if vowelCount[char] == 1 { // New distinct vowel added
				distinctVowels++
			}

			// Shrink window from left until we have <5 distinct vowels
			for distinctVowels == 5 {
				leftChar := rune(w[shrinkPos])
				vowelCount[leftChar]--
				if vowelCount[leftChar] == 0 { // A vowel was removed completely
					distinctVowels--
				}
				shrinkPos++
			}

			// All substrings between windowStart and shrinkPos-1 are valid
			totalCount += shrinkPos - windowStart
		} else {
			// Reset state for non-vowel characters
			vowelCount['a'], vowelCount['e'], vowelCount['i'], vowelCount['o'], vowelCount['u'] = 0, 0, 0, 0, 0
			distinctVowels = 0
			windowStart = currentPos + 1
			shrinkPos = currentPos + 1
		}
	}
	return totalCount
}
