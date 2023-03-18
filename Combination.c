/*
Author: John
Time: 2023/3
Compiler: https://www.onlinegdb.com/online_c_compiler
*/

#include <stdio.h>
#include <stdlib.h>

// Combination N elements select K elements (select without sequence)
// select element[i] from [0 ~ N]
// loop (until reach K)
//    select element[j] from [i + 1 ~ N] without [i] without [already in the selection]

void backtrack(int* nums, int numsSize, int k, int* returnSize, int** rt, int* used, int* arr, int nm, int id) {
    // valid
    if (used[nm]) return;
    // place
    arr[id] = nums[nm];
    used[nm] = 1;
    // solution
    if (id == k - 1) {// k - 1
        // storage
        for (int i = 0; i < k; i++) rt[*returnSize][i] = arr[i];
        *returnSize += 1;
        // retrieve
        used[nm] = 0;
        return;
    }
    // next
    for (int i = nm + 1; i < numsSize; i++) {// i = nm + 1 好漢不吃回頭草
        if (i == nm) continue;
        backtrack(nums, numsSize, k, returnSize, rt, used, arr, i, id + 1);
    }
    // retrieve
    used[nm] = 0;
}


int** combine(int n, int k, int* returnSize, int** returnColumnSizes){
    //
    int* nums = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) nums[i] = i + 1;
    int numsSize = n;

    //
    int tol = 1;
    for (int i = 1; i <= numsSize; i++) tol *= i;
    for (int i = 1; i <= k; i++) tol /= i;
    for (int i = 1; i <= (numsSize - k); i++) tol /= i;
    
    //
    int** rt = (int**)calloc(tol, sizeof(int*));
    for (int i = 0; i < tol; i++) rt[i] = (int*)calloc(k, sizeof(int));
    int* used = calloc(k, sizeof(int));
    int* arr = calloc(k, sizeof(int));
    
    //
    //*returnSize = 0;
    for (int i = 0; i < numsSize; i++) {
        backtrack(nums, numsSize, k, returnSize, rt, used, arr, i, 0);
    }

    //
    *returnColumnSizes = (int*)calloc(tol, sizeof(int));
    for (int i = 0; i < tol; i++) (*returnColumnSizes)[i] = k;

    //
    free(used);
    free(arr);
    return rt;
}



int main()
{
    int returnSize = 0;
    int* returnColumnSizes;
    int** res = combine(6, 3, &returnSize, &returnColumnSizes);
    
    printf("tol: %d\n", returnSize);
    printf("col: %d\n", returnColumnSizes[0]);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) printf(" %d", res[i][j]);
        puts("");
    }
    
    for (int i = 0; i < returnSize; i++) free(res[i]);;
    free(res);
    free(returnColumnSizes);
    return 0;
}
