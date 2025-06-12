#pragma once
#include "class.h"

//27. Remove Element
//First solution runtime beats:06.54% memory beats:09.06%
// int removeElement(std::vector<int>& nums, int val) {
//     int len = nums.size();
//     int position = len - 1;

//     for(int i = 0;i < len; i++){
//         if(nums[i] == val){
//             while(nums[position] == val){
//                 position--;
//             }
//             std::swap(nums[i], nums[position]);
//         }
//     }
//     return;
// }
