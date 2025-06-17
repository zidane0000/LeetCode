#pragma once
#include "class.h"

//80. Remove Duplicates from Sorted Array II
//https://youtu.be/bGuWrXKmnSM
//Network solution runtime beats:41.42% memory beats:21.10%
int removeDuplicates(std::vector<int>& nums) {
    // Core is use two pointer(i, k)
    // It's sorted in non-decreasing order and accept element appears at most twice, so we don't need to care first 2 elements
    // i record when we point to, k record the last position is over 2 times
    // Every time we compare current number(= i) with the number at k - 2

    int k = 2;
    if (nums.size() <= 2) return nums.size();
    
    for (int i = 2; i < nums.size(); i++) {
        if (nums[i] != nums[k - 2]) {
            nums[k] = nums[i];
            k++;
        }
    }

    return k;
}

//380. Insert Delete GetRandom O(1)
//First solution runtime beats:07.22%  memory beats:55.69%
// class RandomizedSet {
// //Didn't follow the rule: implement the functions of the class such that each function works in average O(1) time complexity
// public:
//     RandomizedSet() {
//         unique.clear();
//     }
    
//     bool insert(int val) {
//         if(unique.find(val) != unique.end()){
//             return false;
//         }
//         unique.insert(val);
//         return true;
//     }
    
//     bool remove(int val) {
//         auto position = unique.find(val);
//         if(position == unique.end()){
//             return false;
//         }
//         unique.erase(position);
//         return true;        
//     }
    
//     int getRandom() {
//         auto it = unique.begin();
//         std::advance(it, int(rand() % unique.size()));
//         return *it;
//     }
// private:
//     // std::set is typically implemented as a balanced binary search tree (usually a Red-Black Tree), find and insert are O(log n)
//     // If use std::unordered_set (hash table), both find and insert are O(1) on average, but O(n) in the worst case.
//     std::set<int> unique;
// };

//https://leetcode.com/problems/insert-delete-getrandom-o1/solutions/1377728/real-practical-applications-c-optimalarr-qw65/
//Network solution runtime beats:92.78%  memory beats:26.10%
class RandomizedSet {
	// Average Time O(1) & Auxiliary Space O(N)
private:
    std::vector<int> array; // array vector
    std::unordered_map<int,int> exist; // Unordered Map does searching, insertion & deletion of element in average O(1) time
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
    // No need to initialise array & exist as they are initialised automatically
	// to 0 as and when their container size increases.
    }
    
    /** Inserts a value to the array vector. Returns true if the array did not already contain the specified element. */
    bool insert(int val) {
        if(exist.find(val)!=exist.end())
            return false;
        else{
            array.push_back(val);
            exist[val]=array.size()-1; // unordered_map[key]=value stores the array element and its index as key=array element & value=array element index
            return true;
        }
    }
    
    /** Removes a value from the array vector. Returns true if the array contained the specified element. */
    bool remove(int val) {
        if(exist.find(val)==exist.end()) // val not present in the array vector
            return false;
        else{
	        // val present in the array vector
	        // For example: array=[8,4,3,2], exist={[8,0],[4,1],[3,2],[2,3]}, val=4, last=2
	        // After array[exist[val]]=array.back(); array=[8,2,3,2], exist={[8,0],[4,1],[3,2],[2,3]}
	        // After array.pop_back(); array=[8,2,3], exist={[8,0],[4,1],[3,2],[2,3]}
	        // After exist[last]=exist[val]; array=[8,2,3], exist={[8,0],[4,1],[3,2],[2,1]}
	        // After exist.erase(val); array=[8,2,3], exist={[8,0],[3,2],[2,1]}
            int last=array.back();  // back() fetches last element of the array vector
            array[exist[val]]=array.back(); // exist[val] locates the index of val in the array vector.
				                // Then we copy array last element value to the val location in the array
            array.pop_back();	    // Delete the last element of the array 
            exist[last]=exist[val];	    // In hashmap, assign index of val in array to the index of the last element   
            exist.erase(val);	    // Delete the val entry from map
            return true;
        }
    }
    
    /** Get a random element from the array vector */
    int getRandom() {
	    // rand() function gives random value in the range of 0 to RAND_MAX(whose value is 32767). x%y gives 
 	    // remainder when x is divided by y and this remainder is in the range of 0 to y-1.
	    // rand()%array.size() gives random value in the range of (0 to array.size()-1).
	    // array[rand()%array.size()] will give random value of array in the range of array[0] to array[array.size()-1].
        return array[rand()%array.size()];
    }
};

//528. Random Pick with Weight
//First solution runtime beats:45.49%  memory beats:06.11%
// class Solution {
// public:
//     Solution(std::vector<int>& w) : weights(w) {
//         std::random_device rd;
//         gen = std::mt19937(rd());
//         dist = std::discrete_distribution<>(weights.begin(), weights.end());
//     }

//     int pickIndex() {
//         return dist(gen);
//     }
// private:
//     std::vector<int> weights;
//     std::mt19937 gen;
//     std::discrete_distribution<> dist;
// };

//Second solution runtime beats:06.93%  memory beats:06.11%
class Solution {
public:
    Solution(std::vector<int>& w) : weights(w) {
        sum = std::reduce(weights.begin(), weights.end());
    }

    int pickIndex() {
        int random = std::rand() % sum;
        if(check.find(random) != check.end()){
            return check[random];
        }

        int countDown = random;
        for(int i = 0; i<weights.size();i++){
            if((countDown -= weights[i]) < 0){
                check[random] = i;
                return check[random];
            }
        }
        return check[random];
    }
private:
    std::vector<int> weights;
    std::unordered_map<int,int> check;
    int sum;
};

//https://leetcode.com/problems/random-pick-with-weight/solutions/671632/c-simple-and-easy-solution-with-explanation/
//Network solution runtime beats:79.30%  memory beats:47.67%
class Solution {
public:
    std::vector<int> v;
    Solution(std::vector<int>& w) {
        // Using Prefix sum convert the weight vector
        v.push_back(w[0]);
        for(int i=1;i<w.size();i++){
            v.push_back(v[i-1]+w[i]);
        }
    }
    
    int pickIndex() {
        // Return the index of the upperbound of the random generated number from vector
        int n= rand()%v[v.size()-1];
        auto it=upper_bound(v.begin(),v.end(),n);
        return it-v.begin();
    }
};
