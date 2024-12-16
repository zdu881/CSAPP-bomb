// ...existing code...
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

void read_six_numbers(int numbers[]) {
    printf("请输入六个数字（1-6）:\n");
    for(int i = 0; i < 6; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            explode_bomb();
        }
    }
}

void explode_bomb() {
    printf("炸弹爆炸！\n");
    exit(1);
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        Node* new_node = malloc(sizeof(Node));
        if (!new_node) {
            explode_bomb();
        }
        new_node->value = value;
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    } else {
        // 如果值重复，触发炸弹
        explode_bomb();
    }
    return root;
}

int is_balanced(Node* root) {
    if (root == NULL) return 1;

    int left_height = 0, right_height = 0;
    Node* current = root;

    // 计算左子树高度
    current = root->left;
    while (current) {
        left_height++;
        current = current->left;
    }

    // 计算右子树高度
    current = root->right;
    while (current) {
        right_height++;
        current = current->right;
    }

    if (abs(left_height - right_height) > 1)
        return 0;

    return is_balanced(root->left) && is_balanced(root->right);
}

void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int phase_6() {
    int numbers[6];
    // 读取用户输入
    read_six_numbers(numbers);
    
    // 输入范围检查
    for(int i = 0; i < 6; i++) {
        if (numbers[i] < 1 || numbers[i] > 6) {
            explode_bomb();
        }
    }
    
    // 构建二叉搜索树
    Node* root = NULL;
    for(int i = 0; i < 6; i++) {
        root = insert(root, numbers[i]);
    }
    
    // 验证树的平衡性
    if (!is_balanced(root)) {
        free_tree(root);
        explode_bomb();
    }
    
    // 释放内存
    free_tree(root);
    
    printf("验证通过，继续下一阶段。\n");
    return 0;
}
// ...existing code...
#include <stdio.h>

// 声明 phase_6 函数

int main() {
    printf("开始测试 phase_6...\n");
    phase_6();
    printf("phase_6 测试完成。\n");
    return 0;
}//4 3 2 1 6 5 is a possible answer
