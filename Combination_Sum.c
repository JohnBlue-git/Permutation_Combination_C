/*
Author: John
Time: 2023/3
Compiler: https://www.onlinegdb.com/online_c_compiler
*/

#include <stdio.h>
#include <stdlib.h>

// Combination (can repeat element) ... under sum == target

void bck_trk(int* cand, int candSz, int target, int* rSz, int* rCSz, int** tb, int* arr, int st, int id) {
    // valid
    if (arr[20] + cand[st] > target) return;
    // place
    arr[id] = cand[st];
    arr[20] += cand[st];
    // solution
    if (arr[20] == target) {
        tb[*rSz] = (int*)calloc(id + 1, sizeof(int));
        for (int i = 0; i < id + 1; i++) tb[*rSz][i] = arr[i];
        
        rCSz[*rSz] = id + 1;

        *rSz += 1;

        // retrieve
        arr[20] -= cand[st];
        return;
    }
    // next
    for (int i = st; i < candSz; i++) {// i = st ... can repeat, but no return
        bck_trk(cand, candSz, target, rSz, rCSz, tb, arr, i, id + 1);
    }
    // retrieve
    arr[20] -= cand[st];
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    //
    // candidates[1 ~ 40] col buffer 給 40 個
    // candidates[i] = 2 ~ 40 arr 估計最多用到 20 個
    int* colSize = (int*)calloc(40, sizeof(int));
    int** table = (int**)calloc(40, sizeof(int*));
    int* arr = (int*)calloc(21, sizeof(int));// arr[20] 計算 sum

    //
    *returnSize = 0;
    for (int i = 0; i < candidatesSize; i++) {
        bck_trk(candidates, candidatesSize, target, returnSize, colSize, table, arr, i, 0);
    }

    //
    int** rt = (int**)calloc(*returnSize, sizeof(int*));
    *returnColumnSizes = (int*)calloc(*returnSize, sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        rt[i] = table[i];
        (*returnColumnSizes)[i] = colSize[i];
    }
    
    //
    free(colSize);
    free(arr);
    return rt;
}



int main()
{
    // Input: candidates = [2,3,5], target = 8
    // Output: [[2,2,2,2],[2,3,3],[3,5]]

    //int candidates[3] = {9,10,11};
    int candidates[3] = {2,3,5};
    int returnSize = 0;
    int* returnColumnSizes;
    int** res = combinationSum((int*)candidates, 3, 8, &returnSize, &returnColumnSizes);
    
    printf("tol: %d\n", returnSize);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) printf(" %d", res[i][j]);
        puts("");
    }
    
    for (int i = 0; i < returnSize; i++) free(res[i]);;
    free(res);
    free(returnColumnSizes);
    return 0;
}
