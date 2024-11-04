#include <iostream>
#include <vector>

class TreeNode{
    public:
    int sum;
    int start;
    int end;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int start, int end, int sum = 1){
        this->sum = sum;
        this->start = start;
        this->end = end;
        this->left = this->right = NULL;
    }
};

void modify(TreeNode* node, int s, int e, bool c){
    if (node->start == s && node->end == e){
        if (c)
            node->sum = e - s + 1;
        else
            node->sum = 0;
        return;
    }
    int mid = (node->start + node->end) / 2;
    int isBlack = node->sum == node->end - node->start + 1 ? 1 : 0;
    if (!node->left && node->start != node->end)
        node->left = new TreeNode(node->start, mid, isBlack * mid);

    if (!node->right && node->end - node->start > 0)
        node->right = new TreeNode(mid + 1, node->end, isBlack * (node->start + node->end - mid));
    
    if (e <= mid)
        modify(node->left, s, e, c);
    else if (s > mid)
        modify(node->right, s, e, c);
    else{
        modify(node->left, s, mid, c);
        modify(node->right, mid + 1, e, c);
    }
    node->sum = node->left->sum + node->right->sum;
}

void deleteTree(TreeNode* node){
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m, s, e;
    std::cin >> n >> m;
    char c;
    TreeNode* root = new TreeNode(0, n - 1, n - 1);
    for (int i = 0; i < m; i++){
        std::cin >> s >> e >> c;
        modify(root, s, e, c == 'C');
        std::cout << root->sum << "\n";
    }
    deleteTree(root);
    return 0;
}