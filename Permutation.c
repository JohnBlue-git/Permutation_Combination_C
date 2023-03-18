/*
Author: John
Time: 2023/3
Compiler: https://www.onlinegdb.com/online_c_compiler
*/

#include <stdio.h>
#include <stdlib.h>

// Permutation N elements (select with sequence)
// select element[i] from [0 ~ N]
// loop (until reach N)
//    select element[j] from [0 ~ N] without [i]

void backtrack(int* nums, int numsSize, int* returnSize, int** rt, int* used, int* arr, int nm, int id) {
    // valid
    if (used[nm]) return;
    // place
    arr[id] = nums[nm];
    used[nm] = 1;
    // solution
    if (id == numsSize - 1) {
        // storage
        for (int i = 0; i < numsSize; i++) rt[*returnSize][i] = arr[i];
        *returnSize += 1;
        // retrieve
        used[nm] = 0;
        return;
    }
    // next
    for (int i = 0; i < numsSize; i++) {
        if (i == nm) continue;
        backtrack(nums, numsSize, returnSize, rt, used, arr, i, id + 1);
    }
    // retrieve
    used[nm] = 0;
}



int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    //
    int tol = 1;
    for (int i = 1; i <= numsSize; i++) tol *= i;
    
    //
    int** rt = (int**)calloc(tol, sizeof(int*));
    for (int i = 0; i < tol; i++) rt[i] = (int*)calloc(numsSize, sizeof(int));
    int* used = calloc(numsSize, sizeof(int));// 6 elements idex
    int* arr = calloc(numsSize, sizeof(int));// 6 elements
    
    // 
    //*returnSize = 0;
    for (int i = 0; i < numsSize; i++) {
        backtrack(nums, numsSize, returnSize, rt, used, arr, i, 0);
    }
    
    // 
    //*returnSize = tol;
    *returnColumnSizes = (int*)calloc(tol, sizeof(int));
    //for (int i = 0; i < *returnSize; i++) (*returnColumnSizes)[i] = numsSize;
    for (int i = 0; i < tol; i++) (*returnColumnSizes)[i] = numsSize;
    
    //
    free(used);
    free(arr);
    return rt;
}



int main()
{
    int* nums = calloc(3, sizeof(int));
    for (int i = 0; i < 3; i++) nums[i] = i + 1;
    int numsSize = 3;
    int returnSize = 0;
    int* returnColumnSizes;
    int** res = permute(nums, numsSize, &returnSize, &returnColumnSizes);
    
    printf("tol: %d\n", returnSize);
    printf("col: %d\n", returnColumnSizes[0]);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) printf(" %d", res[i][j]);
        puts("");
    }
    
    free(nums);
    for (int i = 0; i < returnSize; i++) free(res[i]);;
    free(res);
    free(returnColumnSizes);
    return 0;
}
