#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build tree from extended preorder traversal
TreeNode* buildTree(vector<int>& nodes, int& index) {
    if (index >= nodes.size() || nodes[index] == -1) {
        if (index < nodes.size()) index++;
        return nullptr;
    }

    TreeNode* root = new TreeNode(nodes[index]);
    index++;
    root->left = buildTree(nodes, index);
    root->right = buildTree(nodes, index);

    return root;
}

// Prune tree - returns nullptr if the subtree should be pruned
TreeNode* pruneTree(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    // Recursively prune left and right subtrees
    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);

    // If the current node is 0 and both children are null, prune this node
    if (root->val == 0 && root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
    }

    return root;
}

// Output preorder traversal with null nodes as -1
void printPreorder(TreeNode* root) {
    if (root == nullptr) {
        cout << "-1";
        return;
    }

    cout << root->val;

    if (root->left != nullptr || root->right != nullptr) {
        cout << " ";
        printPreorder(root->left);
        cout << " ";
        printPreorder(root->right);
    } else {
        cout << " -1 -1";
    }
}

// Delete tree to avoid memory leak
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<int> nodes;
    int num;

    // Read input
    while (cin >> num) {
        if (num == -2) break;
        nodes.push_back(num);
    }

    // Build tree
    int index = 0;
    TreeNode* root = buildTree(nodes, index);

    // Prune tree
    root = pruneTree(root);

    // Print result
    printPreorder(root);
    cout << endl;

    // Clean up memory
    deleteTree(root);

    return 0;
}
