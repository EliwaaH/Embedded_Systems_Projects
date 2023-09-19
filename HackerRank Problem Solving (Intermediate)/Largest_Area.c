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