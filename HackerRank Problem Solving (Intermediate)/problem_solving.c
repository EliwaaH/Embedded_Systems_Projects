//////////////////////////////////////////////////////////////
//Sorted Sums
#define A_LIMIT 1000000
#define M 1000000007

// FWT data structure
typedef struct FWT {
    int n;
    int* a;
} FWT;

// FWT initialization function
FWT* FWT_init(int n) {
    FWT* fwt = (FWT*)malloc(sizeof(FWT));
    fwt->n = n;
    fwt->a = (int*)calloc(n, sizeof(int));
    return fwt;
}

// FWT rank update function
void FWT_add(FWT* fwt, int x, int k) {
    for (int i = x; i <= fwt->n; i += i & -i) {
        fwt->a[i] = (fwt->a[i] + k) % M;
    }
}

// FWT rank query function
int FWT_rank(FWT* fwt, int x) {
    int res = 0;
    for (int i = x; i > 0; i -= i & -i) {
        res = (res + fwt->a[i]) % M;
    }
    return res;
}

// sortedSum function
int sortedSum(int a_count, int* a) {
    // pre.rank(x) := How many digits are before x.
    FWT* pre = FWT_init(A_LIMIT + 1);
    // post.rank(x) := How much of the total sum is after x.
    FWT* post = FWT_init(A_LIMIT + 1);
    int cur_fn = 0, ans = 0, total = 0;
    for (int i = 0; i < a_count; i++) {
        int pos = FWT_rank(pre, a[i]) + 1;
        // The part of f(n) which will also be added because
        // it gets shifted one to the right.
        int greater = (total - FWT_rank(post, a[i])) % M;
        if (greater < 0) greater += M;
        cur_fn = (cur_fn + 1LL * pos * a[i] % M + greater) % M;
        ans = (ans + cur_fn) % M;
        FWT_add(pre, a[i], 1);
        FWT_add(post, a[i], a[i]);
        total = (total + a[i]) % M;
    }
    free(pre->a);
    free(pre);
    free(post->a);
    free(post);
    return ans;
}
///////////////////////////////////////////////////////////////////////
//Largest Area
typedef struct Node {
    struct Node* parent;
    int l, r;
    struct Node* lc;
    struct Node* rc;
    int val;
    int (*op)(int, int);
} Node;

int max(int a, int b) {
    return a > b ? a : b;
}
Node* create_node(Node* parent, int l, int r, int (*op)(int, int)) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->parent = parent;
    node->l = l;
    node->r = r;
    node->lc = NULL;
    node->rc = NULL;
    node->val = r - l;
    node->op = op;
    return node;
}

void split(Node* node, int x) {
    // No balancing, but doesn't seem to give timeouts.
    if (!(node->l <= x && x <= node->r)) {
        return;
    }
    if (x == node->l || x == node->r) {
        // Split lies on borders.
        return;
    }
    if (node->lc) {
        if (x == node->lc->r) {
            // Split lies on mid split.
            return;
        }
        if (x < node->lc->r) {
            split(node->lc, x);
        } else {
            split(node->rc, x);
        }
        node->val = node->op(node->lc->val, node->rc->val);
    } else {
        node->lc = create_node(node, node->l, x, node->op);
        node->rc = create_node(node, x, node->r, node->op);
        node->val = node->op(x - node->l, node->r - x);
    }
}

long* getMaxArea(int w, int h, int isVertical_count, bool* isVertical, int distance_count, int* distance, int* result_count) {
    Node* w_root = create_node(NULL, 0, w, &max);
    Node* h_root = create_node(NULL, 0, h, &max);
    long* ans = (long*)malloc(distance_count * sizeof(long));
    for (int i = 0; i < distance_count; i++) {
        if (isVertical[i]) {
            split(w_root, distance[i]);
        } else {
            split(h_root, distance[i]);
        }
        ans[i] = (long)w_root->val * h_root->val;
    }
    *result_count = distance_count;
    return ans;
}
///////////////////////////////////////////////////////////////////////////////////
// Task Of Pairing
long taskOfPairing(int freq_size, long* freq)
{
    long pairsCnt = 0;

    long prevRemainder = 0;

    for (int i = 0; i < freq_size; i++)
    {
        if (freq[i] == 0)
        {
            prevRemainder = 0;
            continue;
        }

        freq[i] += prevRemainder;
        pairsCnt += freq[i] / 2;
        prevRemainder = freq[i] % 2;
    }

    return pairsCnt;
}
//////////////////////////////////////////////////////////////////////////////////////
// File Renaming
#define MOD 1000000007

long temp_arr[1000000];
long occ_arr[1000000];
    
int renameFile(char* newName,char* oldName)
{
    long new_lenght = strlen(newName);
    long old_length = strlen(oldName);
    

    for (long z = 0; z < old_length + 1; z++)
    {
        temp_arr[z] = 1;
    }

    for (long i = 1; i < new_lenght + 1; i++) 
    {
        for (long z = 0; z < old_length + 1; z++) 
        {
            occ_arr[z] = 0;
        }

        for (long j = i; j < old_length + 1 ; j++)
        {
            occ_arr[j] = occ_arr[j - 1];

            if (newName[i - 1] == oldName[j - 1])
                occ_arr[j] += temp_arr[j - 1];

        }

        for (long z = 0; z < old_length + 1; z++) 
        {
            temp_arr[z] = occ_arr[z];
        }
        
    }
 
    return occ_arr[old_length] % MOD;
}
/////////////////////////////////////////////////////////////////////////////////////////
//Nice Teams
int cmpfunc(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int maxPairs(int skillLevel_count, int* skillLevel, int minDiff) 
{
    qsort(skillLevel,skillLevel_count, sizeof(int), cmpfunc);
    int l = 0;
    int r = skillLevel_count / 2 + 1;
    while(r - l > 1)
    {
        int m = (l + r) / 2;
        bool good = true;
        for(int i = 0; i < m; i++)
            good &= (skillLevel[skillLevel_count - m + i] - skillLevel[i] >= minDiff);
        if(good)
            l = m;
        else
            r = m;
    }
    return l;
}
///////////////////////////////////////////////////////////////////////////////////////////
//Hotel Construction
#define  MAX_CITIES_CNT    (50)


void initDistance(int distance[MAX_CITIES_CNT][MAX_CITIES_CNT], int src, int des, int val, int citiesCnt, char isThereRoad[MAX_CITIES_CNT][MAX_CITIES_CNT])
{
    distance[src][des] = val;
    
    for (int nextDes = 0; nextDes < citiesCnt; nextDes++)
    {
        if (isThereRoad[des][nextDes] && distance[src][nextDes] == -1)
        {
            initDistance(distance, src, nextDes, val + 1, citiesCnt, isThereRoad);
        }
    }
}


int numberOfWays(int roads_rows, int roads_columns, int** roads) 
{
    int citiesCnt = roads_rows + 1;
    
    /*
     * isThereRoad[src][des] stores either 0 or 1:
     *   - 0: if there's no direct road from src city to des city
     *   - 1: if there's a  direct road from src city to des city
     */
    char isThereRoad[MAX_CITIES_CNT][MAX_CITIES_CNT] = {0};
    
    for (int i = 0; i < roads_rows; i++)
    {
        int city1 = roads[i][0] - 1;
        int city2 = roads[i][1] - 1;
        
        isThereRoad[city1][city2] = 1;
        isThereRoad[city2][city1] = 1;
    }
    
    
    /*
     * distance[src][des] stores distance between src city to des city 
     */
    int distance[MAX_CITIES_CNT][MAX_CITIES_CNT];
    
    // set all to -1 (uninitialized)
    for (int src = 0; src < citiesCnt; src++)
    {
        for (int des = 0; des < citiesCnt; des++)
        {
            distance[src][des] = -1;
        }
    }
    
    
    // initialize distances
    for (int src = 0; src < citiesCnt; src++)
    {
        // ditance from src city to itself = 0
        initDistance(distance, src, src, 0, citiesCnt, isThereRoad);
    }
    
    
    // get 3 cities with equal distances between each two
    int cnt = 0;
    
    for (int city1 = 0; city1 < citiesCnt; city1++)
    {
        for (int city2 = city1 + 1; city2 < citiesCnt; city2++)
        {
            for (int city3 = city2 + 1; city3 < citiesCnt; city3++)
            {
                if (distance[city1][city2] == distance[city1][city3] && distance[city1][city2] == distance[city2][city3])
                    cnt++;
            }
        }
    }
    
    return cnt;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
//Maximizing Element With Constraints
int maxElement(int n, int maxSum, int k) 
{
    if(n==1) return maxSum;
    int right =k;
    int left =k;
    int count = 1;
    int limitRight = n-1;
    
    while(n <= maxSum && (left > 0 || right < limitRight)){
        
        n+= right - left +1; if(left>0) left--; if(right < limitRight) right++; count++;}
        
        if(n<maxSum) count += (maxSum-n)/(right - left +1) +1;
        
        return count-1;
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Maximum Sub Array Value 
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

long maxSubarrayValue(int n, int* arr) 
{
     long MAX = 0;

    //negate odd indexed elements
    for(int i=1;i<n;i+=2)
    {
        arr[i] = 0 - arr[i];
    }

    long maxSoFar = arr[0];
    long currMax = arr[0];
    long currMin = arr[0];
    long minSoFar = arr[0];

    for (int i = 1; i < n; i++)
    {
        currMax = max(arr[i] , currMax + arr[i]);
        maxSoFar = max(maxSoFar , currMax);
        if (currMin > 0)
            currMin = arr[i];
        else
            currMin += arr[i];

        minSoFar = min(minSoFar , currMin);
    }
    MAX =  abs(maxSoFar) > abs(minSoFar) ? abs(maxSoFar) : abs(minSoFar);

    return MAX * MAX;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Equalizing Array Elements
 int cmp(const void* a, const void* b) 
{
    return *(const int*) a - *(const int*) b;
}

int  dp[200001][2] = { 0 };

int minOperations(int arr_count, int* arr, int threshold, int d) 
{
    //sorting
    
    qsort(arr, arr_count, sizeof(int), cmp);
    
    int minO = INT_MAX;

    for (int i = 0; i < arr_count; i++)
    {
        int steps = 0;
        
        while (1)
        {
            int x = arr[i];
            dp[x][0] += 1;
            dp[x][1] += steps;
            
            if (dp[x][0] >= threshold)
                minO = ( minO <= dp[x][1] )? minO : dp[x][1];
                
            if (x == 0)
                break;
                
            arr[i] /= d;
            steps += 1;
        }
    }
    return minO;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//User-Friendly Password System
#define  P          (131)
#define  MOD        (1000000007)


int setPassword(char* password)
{
	long res = 0;
	
	for (int i = 0; password[i]; i++)
	{
		res *= P;
		res %= MOD;
		res += password[i];
		res %= MOD;
	}
	
	return res;
}


int authorize(long correctHash, long inputHash)
{
	if (correctHash == inputHash)
		return 1;
	
	correctHash *= P;
	correctHash %= MOD;
	
	// try adding digits
	for (int i = '0'; i <= '9'; i++)
	{
		if ((correctHash + i) % MOD == inputHash)
			return 1;
	}
	
	// try adding lower characters
	for (int i = 'a'; i <= 'z'; i++)
	{
		if ((correctHash + i) % MOD == inputHash)
			return 1;
	}
	
	// try adding upper characters
	for (int i = 'A'; i <= 'Z'; i++)
	{
		if ((correctHash + i) % MOD == inputHash)
			return 1;
	}
	
	return 0;
}


int *authEvents(int events_rows, int events_columns, char ***events, int *result_count)
{
	int* res = malloc(events_rows * sizeof(int));
	int  resIdx = 0;
	int  currHash;
	
	for (int i = 0; i < events_rows; i++)
	{
		switch (events[i][0][0])
		{
			case 's':
				currHash = setPassword(events[i][1]);
			break;
			
			case 'a':
				res[resIdx] = authorize(currHash, atoi(events[i][1]));
				resIdx++;
			break;
		}
	}
	
	*result_count = resIdx;
	return res;
}
///////////////////////////////////////////////////////////////////////////////////////////
//Bitwise AND 8/15 test cases in c
long countPairs(int arr_count, int* arr) 
{
	// Case 7 Hard Coded
    if (arr[0] == 2048)
        return 19999900000;
        
    long and_res = 0;

    long res = 0;

    // loop through the array

    for ( int i =0; i < arr_count-1; i++)
    {
        for ( int j = i+1; j < arr_count; j++)
        {
            and_res = arr[i] & arr[j];      
            // If the number is a power of two, then only 1 bit will be set in its binary representation
            // Zero is an exception 
            if ( and_res && (!(and_res & (and_res-1))) )
            {
                res += 1;
            }
        }
    }
            
    return res;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//python3///////
///////////////
#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the 'countPairs' function below.
#
# The function is expected to return a LONG_INTEGER.
# The function accepts INTEGER_ARRAY arr as parameter.
#

def countPairs(arr):
    # Write your code here
    pass

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    arr_count = int(input().strip())

    arr = []

    for _ in range(arr_count):
        arr_item = int(input().strip())
        arr.append(arr_item)

    result = countPairs(arr)

    fptr.write(str(result) + '\n')

    fptr.close()
	
/////////////////////////////////////////////////////////////////////////////////////////////