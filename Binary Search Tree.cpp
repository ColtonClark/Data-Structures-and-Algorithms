#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int data) {
        key = data;
        left = NULL;
        right = NULL;
        height = 0;
    }
};

class BST {
    Node* root;

public:
    BST() {
        root = NULL;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(Node* node) {
        if (node == NULL)
            return -1;

        return node->height;
    }

    int getBalance(Node* N) {
        if (N == NULL)
            return 0;

        return height(N->left) - height(N->right);
    }

    Node* leftRotate(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = max(height(z->left), height(z->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* rightRotate(Node* z) {
        Node* y = z->left;
        Node* T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = max(height(z->left), height(z->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* root, int key) {

        if (root == NULL)
            root = new Node(key);

        else if (key < root->key)
            root->left = insert(root->left, key);

        else if (key > root->key)
            root->right = insert(root->right, key);

        else
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && key < root->left->key)
            return rightRotate(root);

        if (balance < -1 && key > root->right->key)
            return leftRotate(root);

        if (balance > 1 && key > root->left->key) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && key < root->right->key) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    Node* search(Node* root, int data) {
        if (root == NULL || root->key == data)
            return root;

        if (root->key < data)
            return search(root->right, data);

        return search(root->left, data);
    }

    Node* search(int key) {
        return search(root, key);
    }

    Node* deletion(Node* node, int key) {

        if (node == NULL)
            return node;

        if (node->key > key)
            node->left = deletion(node->left, key);

        else if (key > node->key)
            node->right = deletion(node->right, key);

        else {
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = rightmostNode(node->left);
            node->key = temp->key;
            node->left = deletion(node->left, temp->key);
        }

        if (node == NULL)
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* rightmostNode(Node* node) {
        Node* current = node;

        while (current->right != NULL)
            current = current->right;

        return current;
    }

    Node* findMax() {
        if (root == NULL)
            return NULL;

        Node* current = root;

        while (current->right != NULL)
            current = current->right;

        return current;
    }

    Node* findMin() {
        if (root == NULL)
            return NULL;

        Node* current = root;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    void preorder(Node* root) {
        if (root != NULL) {
            cout << root->key << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void inorder(Node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

    void postorder(Node* root) {
        if (root != NULL) {
            postorder(root->left);
            postorder(root->right);
            cout << root->key << " ";
        }
    }
    void PrintBST(Node* root)
    {
        int height = root->height + 1;
        for (int i = height; i > 0; i--)
        {
            Print(i, root, height);
            cout << "\n";
        }
    }

    void Print(int height, Node* s, int h)
    {
        int spacing = pow(2, height);
        if (h == height)
        {
            printf("%*s%2d", spacing - 2, "", s->key);
        }
        else if (h > height)
        {
            if (s->left != NULL)
                Print(height, s->left, h - 1);
            else
                printf("%*s", spacing * (height - h), "");

            printf("%*s", spacing, "");

            if (s->right != NULL)
                Print(height, s->right, h - 1);
            else
                printf("%*s", spacing * (height - h), "");
        }
    }

};
int main()
{

    BST Tree;
    Node* root = NULL;
    int size;
    int arr[100] = {};
    cout << "Enter size of the Tree: \n";
    cin >> size;

    cout << "Enter " << size << " elements into the BST: \n";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "\n";

    for (int i = 0; i < size; i++)
        root = Tree.insert(root, arr[i]);
    int num = 0;
    int choice = 0;
    do {

        cout << "\nBalanced Tree \n";
        Tree.PrintBST(root);

        cout << "******************************\nWhich option would you like?" << endl << "1: Insertion \n2: Deletion\n3: Search\n4: Preorder\n5: Inorder\n6: Postorder\n7: Exit\n******************************\n";
        cin >> choice;
        switch (choice)
        {

        case 1: cout << "Enter number for insertion: ";
            cin >> num;
            if (Tree.insert(root, num))
            {
                cout << "\n********************\nInserted: " << num << "\n********************";
            }
            break;

        case 2: cout << "\nEnter number for deletion: \n";
            cin >> num;
            if (Tree.deletion(root, num))
            {
                cout << "\n********************\nDeleted: " << num << "\n********************";
            }
            break;

        case 3: cout << "\nEnter number for search: \n";
            cin >> num;
            if (Tree.search(root, num))
            {
                cout << "\n********************\nFound!\n********************";
            }
            else
            {
                cout << "\n********************\nNumber not found\n********************";
            }
            break;

        case 4: cout << "\n********************\nPreorder: \n";
            Tree.preorder(root);
            cout << "\n********************";
            break;

        case 5: cout << "\n********************\nInorder: \n";
            Tree.inorder(root);
            cout << "\n********************";
            break;

        case 6: cout << "\n********************\nPostorder: \n";
            Tree.postorder(root);
            cout << "\n********************";
            break;
        }
        cout << "\n";
    } while (choice != 7);
}