/*
AIM:
A Dictionary stores keywords & its meanings.
Use Binary Search Tree-AVL concept for implementation.
Provide facility to:
i. Insert new Keyword
ii.Display whole data sorted in dictionary.
iii. Use Height Balance Tree concept to balance the AVL

INPUT: Keyword - meaning
OUTPUT: Balanced AVL with keywords as the data 

Author: Ashish Dange
*/
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Using a struct for the dictionary entry
struct Word {
  string key;
  string meaning;
};

// Node structure for the AVL tree
struct Node {
  Word data;
  Node *left, *right;
  int height;

  Node(Word w) : data(w), left(nullptr), right(nullptr), height(1) {}
};

class AVLDictionary {
  private:
    Node* root;
    int getHeight(Node* n) {
      return n ? n->height : 0;
    }
    int getBalance(Node* n) {
      return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }
    Node* rotateRight(Node* y) {
      Node* x = y->left;
      Node* T2 = x->right;
      x->right = y;
      y->left = T2;
      y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
      x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
      return x;
    }
    Node* rotateLeft(Node* x) {
      Node* y = x->right;
      Node* T2 = y->left;
      y->left = x;
      x->right = T2;
      x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
      y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
      return y;
    }
    Node* insertNode(Node* node, Word w) {
      if (!node) return new Node(w);
      if (w.key < node->data.key)
        node->left = insertNode(node->left, w);
      else if (w.key > node->data.key)
        node->right = insertNode(node->right, w);
      else 
        return node; // Duplicate keys not allowed
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
      int balance = getBalance(node);
      // LL Case
      if (balance > 1 && w.key < node->left->data.key)
        return rotateRight(node);

      // RR Case
      if (balance < -1 && w.key > node->right->data.key)
        return rotateLeft(node);

      // LR Case
      if (balance > 1 && w.key > node->left->data.key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
      }

      // RL Case
      if (balance < -1 && w.key < node->right->data.key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
      }
      return node;
    }

    void display(Node* root) {
      if (root) {
        display(root->left);
        cout << "Keyword: " << root->data.key << " | Meaning: " << root->data.meaning << endl;
        display(root->right);
      }
    }

  public:
    AVLDictionary() : root(nullptr) {}

    void add(string k, string m) {
      root = insertNode(root, {k, m});
    }

    void showAll() {
      if (!root) cout << "Dictionary is empty.\n";
      else display(root);
    }
};

int main() {
  AVLDictionary dict;
  int choice;
  string k, m;

  do {
    cout << "\n--- AVL Dictionary ---\n1. Add Word\n2. Display All\n3. Exit\nChoice: ";
    cin >> choice;
    cin.ignore(); // Clear newline

    if (choice == 1) {
      cout << "Enter Keyword: "; getline(cin, k);
      cout << "Enter Meaning: "; getline(cin, m);
      dict.add(k, m);
    } else if (choice == 2) {
      dict.showAll();
    }
  } while (choice != 3);

  return 0;
}
