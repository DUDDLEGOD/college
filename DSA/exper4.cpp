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
#include <algorithm> // For std::max

using namespace std;

struct Node {
  string key, meaning;
  Node *left = nullptr, *right = nullptr;
  int ht = 1;

  Node(string k, string m) : key(k), meaning(m) {}
};

class AVLDictionary {
  private:
    Node* root = nullptr;

    int ht(Node* n) { return n ? n->ht : 0; }
    int bal(Node* n) { return n ? ht(n->left) - ht(n->right) : 0; }

    Node* rotateRight(Node* y) {
      Node* x = y->left;
      y->left = x->right;
      x->right = y;

      y->ht = max(ht(y->left), ht(y->right)) + 1;
      x->ht = max(ht(x->left), ht(x->right)) + 1;
      return x;
    }

    Node* rotateLeft(Node* x) {
      Node* y = x->right;
      x->right = y->left;
      y->left = x;

      x->ht = max(ht(x->left), ht(x->right)) + 1;
      y->ht = max(ht(y->left), ht(y->right)) + 1;
      return y;
    }

    Node* insertNode(Node* n, string k, string m) {
      if (!n) return new Node(k, m);
      if (k < n->key) n->left = insertNode(n->left, k, m);
      else if (k > n->key) n->right = insertNode(n->right, k, m);
      else return n; // No duplicates
      n->ht = 1 + max(ht(n->left), ht(n->right));
      int b = bal(n);

      if (b > 1 && k < n->left->key) return rotateRight(n);           // LL Case
      if (b < -1 && k > n->right->key) return rotateLeft(n);          // RR Case

      if (b > 1 && k > n->left->key) {                                // LR Case
        n->left = rotateLeft(n->left);
        return rotateRight(n);
      }
      if (b < -1 && k < n->right->key) {                              // RL Case
        n->right = rotateRight(n->right);
        return rotateLeft(n);
      }
      return n;
    }

    void display(Node* n) {
      if (!n) return;
      display(n->left);
      cout << n->key << " : " << n->meaning << endl;
      display(n->right);
    }

  public:
    void add(string k, string m) { root = insertNode(root, k, m); }

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
    cin.ignore();

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
