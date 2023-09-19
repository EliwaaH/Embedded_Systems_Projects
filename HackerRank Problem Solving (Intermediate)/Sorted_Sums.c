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