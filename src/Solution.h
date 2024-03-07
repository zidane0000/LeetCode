#pragma once
#include "class.h"

//1768. Merge Strings Alternately
//初解 runtime beats:06.54% memory beats:09.06%
std::string mergeAlternately(std::string word1, std::string word2) {
    std::string ans = "";
    int posi = 0;
    for (posi = 0; posi < word1.size() && posi < word2.size(); posi++) {
        ans = ans + word1[posi] + word2[posi];
    }
    ans.append(word1.begin() + posi, word1.end());
    ans.append(word2.begin() + posi, word2.end());
    return ans;
}

//1071. Greatest Common Divisor of Strings
//初解 runtime beats:18.68% memory beats:05.08%
//std::string gcdOfStrings(std::string str1, std::string str2) {
//    if (str1 == str2) return str1;
//
//    auto isDivide = [](std::string str, std::string divisor) {
//        if (str.size() % divisor.size() != 0) {
//            // 字串長度不能被除數長度整除，視為無法整除
//            return false;
//        }
//
//        for (size_t i = 0; i < str.size(); i += divisor.size()) {
//            // 檢查每個子字串是否與除數相等
//            if (str.substr(i, divisor.size()) != divisor) {
//                return false;
//            }
//        }
//        return true;
//    };
//
//    int minLen = str1.size() < str2.size() ? str1.size() : str2.size();
//    for (minLen; minLen > 0; minLen--) {
//        std::string divisor = str1.substr(0, minLen);
//        if (divisor != str2.substr(0, minLen)) return "";
//        if (isDivide(str1, divisor) && isDivide(str2, divisor)) return divisor;
//    };
//    return "";
//}

//網解 runtime beats:100.00% memory beats:85.53%
std::string gcdOfStrings(const std::string& s1, const std::string& s2)
{
    /*
    Explanation:
    s1+s2 == s2+s1 if & only if s1 is a multiple of s2 or vice-versa
    e.g. s1=abcabc, s2=abc, then s1+s2 = abcabcabc = s2+s1
    This is a requirement for the strings to have a gcd. If one of them is NOT a multiple of other, gcd is ''
    Since they are multiples, next step is simply to find the gcd of the lengths of 2 strings e.g. gcd(6,3) = 3, and get the substring of length 3 from either s1 or s2.
    Which is what s1.substr(0, gcd) does... and in Python, that would be s1[:gcd] or s2[:gcd]
    */
    return (s1 + s2 == s2 + s1) ? s1.substr(0, std::gcd(size(s1), size(s2))) : "";
}

//1431. Kids With the Greatest Number of Candies
//初解 runtime beats:100.00% memory beats:13.79%
std::vector<bool> kidsWithCandies(std::vector<int>& candies, int extraCandies) {
    std::vector<bool> ans(candies.size());
    auto greatestCandies = std::max_element(candies.begin(), candies.end());
    for (int i = 0; i < candies.size(); i++) {
        if (candies[i] + extraCandies >= *greatestCandies) ans[i] = true;
    }
    return ans;
}

//605. Can Place Flowers
//初解 runtime beats:80.38% memory beats:65.79% 
bool canPlaceFlowers(std::vector<int>& flowerbed, int n) {
    if (n == 0) return true;
    for (int i = 0; i < flowerbed.size(); i++) {
        if (flowerbed[i] == 1) { i++; }
        else {
            if ((i + 1) == flowerbed.size() ? 1 : flowerbed[i + 1] == 0) {
                n--;
                i++;
            }
        }
        if (n == 0) return true;
    }
    return false;
}

//345. Reverse Vowels of a String
//初解 runtime beats:100.00% memory beats:63.74%
std::string reverseVowels(std::string s) {
    auto isVowels = [](char c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'; };
    int front = 0, end = s.size() - 1;
    while (front < end) {
        while (front < end && !isVowels(s[front])) {
            front++;
        }

        while (end > front && !isVowels(s[end])) {
            end--;
        }

        std::swap(s[front], s[end]);
        front++;
        end--;
    }

    return s;
}

//Weekly Contest 380
//3005.Count Elements With Maximum Frequency
int maxFrequencyElements(std::vector<int>& nums) {
    std::vector<int> count(*std::max_element(nums.begin(), nums.end()) + 1, 0);
    for (int num : nums) {
        count[num]++;
    }

    int ans = 0;
    int max_count = *std::max_element(count.begin(), count.end());
    for (int c : count) {
        if (c == max_count) {
            ans += c;
        }
    }
    return ans;
}

//3006. Find Beautiful Indices in the Given Array I
std::vector<int> beautifulIndices(std::string s, std::string a, std::string b, int k) {
    std::vector<int> ans;

    auto candidates = [](std::string str, std::string target) {
        std::vector<int> candidates;
        size_t pos = str.find(target);
        while (pos != std::string::npos) {
            candidates.push_back(pos);
            pos = str.find(target, pos + 1);
        }
        return candidates;
    };

    auto candidates_a = candidates(s, a);
    auto candidates_b = candidates(s, b);

    for (int candidate_a : candidates_a) {
        for (int candidate_b : candidates_b) {
            if (std::abs(candidate_a - candidate_b) <= k) {
                ans.push_back(candidate_a);
                break;
            }
        }
    }

    return ans;
}

//3007. Maximum Number That Sum of the Prices Is Less Than or Equal to K
long long findMaximumNumber(long long k, int x) {
    auto countPrice = [](long long n, int x) {
        int count = 0;
        if (x != 1) n >>= (x - 1);
        while (n) {
            count += n & 1;
            n >>= x;
        }
        return count;
    };

    long long pricesSum = 0;
    for (int i = 0; ; i++) {
        int price = countPrice(i, x);
        if (price == 0) {
            i <<= x-1;
        }
        pricesSum += price;
        if (pricesSum > k) {
            return i - 1;
        }
    }
}

//151. Reverse Words in a String
//初解 runtime beats:13.66% memory beats:11.66%
//std::string reverseWords(std::string s) {
//    std::vector<std::string> splits;
//    std::stringstream ss(s);
//    std::string ans;
//    while (getline(ss, ans, ' ')) {
//        if(ans != "") splits.push_back(ans);
//    }
//
//    ans = "";
//    for (auto split : splits) {
//        ans = split + " " + ans;
//    }
//    return ans.substr(0, ans.size() - 1);
//}

//二解 runtime beats:15.61% memory beats:10.49%
std::string reverseWords(std::string s) {
    s = s + " "; // because end is find first white space behind the front, so if s = " blue", first = 2 and end will be -1, to prevent this, we can add white space first
    int front = s.find_first_not_of(" ");
    int end = s.find_first_of(" ", front + 1);
    std::string ans = "";
    while (s.size() > 0 && front != std::string::npos && end != std::string::npos) {
        ans = s.substr(front, end - front) + " " + ans;
        s = s.substr(end, s.size() - end);
        front = s.find_first_not_of(" ");
        end = s.find_first_of(" ", front + 1);
    }
    return ans.substr(0, ans.size()-1);
}

//443. String Compression
//初解 runtime beats:39.33% memory beats:05.75%
//int compress(std::vector<char>& chars) {
//    int posi = 0;
//    std::string s;
//    for (int i = 0; i < chars.size(); i++) {
//        if (posi != i) {
//            if (chars[i] != chars[posi]) {
//                s = (i - posi) == 1 ? s + chars[posi] : s + chars[posi] + std::to_string(i - posi);
//                posi = i;
//            }
//        }
//    }
//    s = (chars.size() - posi) == 1 ? s + chars[posi] : s + chars[posi] + std::to_string(chars.size() - posi);
//    chars.clear();
//    std::copy(s.begin(), s.end(), std::back_inserter(chars));
//    return s.size();
//}

//參考網址：https://leetcode.com/problems/string-compression/discuss/222499/Simple-C%2B%2B-Solution
//網解 runtime beats:84.46% memory beats:47.33%
int compress(std::vector<char>& chars) {
    int size = chars.size();
    if (size < 2) return size;

    int left = 0, right = 0;

    while (right < size) {
        chars[left] = chars[right];
        int count = 0;
        while (right < size && chars[left] == chars[right]) {
            count++;
            right++;
        }

        if (count == 1) {
            left++;
        }
        else {
            std::string cnt = std::to_string(count);
            for (auto digit : cnt) {
                chars[++left] = digit;
            }
            left++;
        }
    }

    return left;
}

//392. Is Subsequence
//初解 runtime beats:100.00% memory beats:44.95%
bool isSubsequence(std::string s, std::string t) {
    if (s.size() > t.size()) return false;
    if (s == "") return true;
    int posi = 0;
    for (char c : t) {
        if (c == s[posi]) {
            posi++;
            if (posi == s.size()) return true;
        }
    }
    return false;
}

//1679. Max Number of K-Sum Pairs
//初解 runtime beats:15.72% memory beats:05.09%
int maxOperations(std::vector<int>& nums, int k) {
    // A map store the num, and find the diff between num and k exist in map
    int ans = 0;
    std::map<int, int> find;
    for (int num : nums) {
        if (find[k - num] > 0) {
            find[k - num]--;
            ans++;
        }
        else {
            find[num]++;
        }
    }
    return ans;
}

//643. Maximum Average Subarray I
//初解 runtime beats:96.19% memory beats:14.74%
double findMaxAverage(std::vector<int>& nums, int k) {
    int ans = std::accumulate(nums.begin(), nums.begin() + k, 0), sum = ans;
    for (int i = k; i < nums.size(); i++) {
        sum = sum - nums[i - k] + nums[i];
        ans = ans > sum ? ans : sum;
    }
    return (double)ans / k;
}

//1456. Maximum Number of Vowels in a Substring of Given Length
//初解 runtime beats:97.37% memory beats:05.10%
int maxVowels(std::string s, int k) {
    auto isVowel = [](char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int maxVowelsCount = std::count_if(s.begin(), s.begin() + k, isVowel), currentVowelsCount = maxVowelsCount;
    for (int i = k; i < s.size(); i++) {
        currentVowelsCount = currentVowelsCount - isVowel(s[i - k]) + isVowel(s[i]);
        maxVowelsCount = maxVowelsCount > currentVowelsCount ? maxVowelsCount : currentVowelsCount;
    }

    return maxVowelsCount;
}

//1004. Max Consecutive Ones III
//參考網址：https://leetcode.com/problems/max-consecutive-ones-iii/discuss/247564/JavaC%2B%2BPython-Sliding-Window
//網解 runtime beats:84.38% memory beats:05.86%
int longestOnes(std::vector<int>& A, int K) {
    /*
    * 從程式碼可以看到，j不斷向右移動。這裡的K可以認為是剩餘的可行翻轉次數，反映了目前的範圍（即從i到j）。
    * 當 K < 0 時，它不是可行解；當 K >= 0 時，它是可行解。
    * 如果目前範圍是還不是可行的解決方案或優於當前「記憶」幀（即K<0判斷），i 將嘗試跟進 j 並且 j-i（幀大小）保持不變，保持當前最大大小不變。
    * 每當當前範圍（即仍然 i 到 j）的翻轉計數 K 大於或等於 0 時，就意味著可以擴展我們的框架。（i 保持不變，因為它不會進入 K < 0 ，並且當 K >= 0 時 j 保持移動）
    * 最終當 j 到達末端時，「記憶體」框架將自動（當然是設計的）為我們提供整個陣列的最大範圍。    
    */
    int i = 0, j;
    for (j = 0; j < A.size(); ++j) {
        if (A[j] == 0) K--;
        if (K < 0 && A[i++] == 0) K++;
    }
    return j - i;
}

//1732. Find the Highest Altitude
//初解 runtime beats:100.00% memory beats:05.34%
int largestAltitude(std::vector<int>& gain) {
    int ans = gain[0] > 0 ? gain[0] : 0;
    for (int i = 1; i < gain.size(); i++) {
        gain[i] = gain[i] + gain[i - 1];
        ans = ans > gain[i] ? ans : gain[i];
    }
    return ans;
}

//724. Find Pivot Index
//初解 runtime beats:91.45% memory beats:06.20%
int pivotIndex(std::vector<int>& nums) {
    int left = 0, right = std::accumulate(nums.begin() + 1, nums.end(), 0);
    if (left == right) return 0;
    for (int i = 1; i < nums.size(); i++) {
        left += nums[i - 1];
        right -= nums[i];
        if (left == right) return i;
    }
    return -1;
}

//1493. Longest Subarray of 1's After Deleting One Element
//初解 runtime beats:22.21% memory beats:33.96%
//int longestSubarray(std::vector<int>& nums) {
//    nums.push_back(0);
//    int ans = 0, previousSubarray = -1, currentSubarray = -1, firstZeroPosition = -1;
//    for (int i = 0; i < nums.size(); i++) {
//        if (nums[i] == 0) {
//            if (firstZeroPosition == -1) {
//                firstZeroPosition = i;
//                previousSubarray = i;
//            }
//            else {
//                currentSubarray = i - firstZeroPosition - 1;
//                ans = ans > previousSubarray + currentSubarray ? ans : previousSubarray + currentSubarray;
//                firstZeroPosition = i;
//                previousSubarray = currentSubarray;
//            }
//        }
//    }
//
//    if (currentSubarray == -1) ans = nums.size() - 2;
//    return ans;
//}

//二解 runtime beats:92.80% memory beats:33.96%
int longestSubarray(std::vector<int>& nums) {
    int ans = 0, previousSubarray = -1, currentSubarray = -1, firstZeroPosition = -1;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 0) {
            if (firstZeroPosition == -1) {
                firstZeroPosition = i;
                previousSubarray = i;
            }
            else {
                currentSubarray = i - firstZeroPosition - 1;
                ans = ans > previousSubarray + currentSubarray ? ans : previousSubarray + currentSubarray;
                firstZeroPosition = i;
                previousSubarray = currentSubarray;
            }
        }
    }

    if (nums.back() == 1) {
        currentSubarray = nums.size() - firstZeroPosition - 1;
        ans = ans > previousSubarray + currentSubarray ? ans : previousSubarray + currentSubarray;
    }

    if (previousSubarray == -1 && currentSubarray == -1) ans = nums.size() - 2;
    return ans;
}

//2215. Find the Difference of Two Arrays
//初解 runtime beats:85.68% memory beats:60.37%
std::vector<std::vector<int>> findDifference(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<std::vector<int>> ans({ {},{} });
    std::set<int> set1(nums1.begin(), nums1.end());
    std::set<int> set2(nums2.begin(), nums2.end());
    for (int num : set1)
        if (set2.find(num) == set2.end()) ans[0].push_back(num);
    for (int num : set2)
        if (set1.find(num) == set1.end()) ans[1].push_back(num);
    return ans;
}

//1207. Unique Number of Occurrences
//初解 runtime beats:100.00% memory beats:06.20%
//bool uniqueOccurrences(std::vector<int>& arr) {
//    std::unordered_map<int, int> occurrences;
//    for (auto i : arr) {
//        occurrences[i]++;
//    }
//
//    std::unordered_map<int, int> isUnique;
//    for (auto occurrence : occurrences) {
//        if (isUnique[occurrence.second] > 0) return false;
//        isUnique[occurrence.second]++;
//    }
//
//    return true;
//}

//二解 runtime beats:35.19% memory beats:12.59%
bool uniqueOccurrences(std::vector<int>& arr) {
    int size = arr.size();
    if (size < 2) return false;

    std::sort(arr.begin(), arr.end());
    std::set<int> occurr;
    int count = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i - 1] != arr[i]) {
            if (occurr.find(count) != occurr.end()) return false;
            occurr.insert(count);
            count = 1;
        }
        else {
            count++;
        }
    }

    if (occurr.find(count) != occurr.end()) return false;
    return true;
}

//1657. Determine if Two Strings Are Close
//https://leetcode.com/problems/determine-if-two-strings-are-close/discuss/935920/C%2B%2B-Short-and-Simple-oror-O(-N-)-solution
//網解 runtime beats:86.69% memory beats:09.68%
bool closeStrings(std::string word1, std::string word2) {
    //All the unique char which there in String1 need's to there as well In string2
    std::vector<char>unique1(26,0), unique2(26,0);
    //Frequency of Char need's to be same there both of string as we can do Transform every occurrence of one existing character into another existing character
    std::vector<int> freq1(26, 0), freq2(26, 0);
    for (char c : word1) {
        freq1[c - 'a']++;
        unique1[c - 'a'] = 1;
    }
    for (char c : word2) {
        freq2[c - 'a']++;
        unique2[c - 'a'] = 1;
    }
    std::sort(begin(freq1), end(freq1));
    std::sort(begin(freq2), end(freq2));
    return freq1 == freq2 && unique1 == unique2;
}