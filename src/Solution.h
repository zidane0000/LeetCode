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