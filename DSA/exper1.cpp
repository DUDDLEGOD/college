/*A Dictionary stores keywords & its meanings.
  Provide facility for:
  i. adding new keywords
  ii. deleting keywords
  iii. updating values of any entry.
  iv. Provide facility to display whole data sorted in ascending/ Descending order.
  v. Also find how many maximum comparisons may require for finding any keyword.
  Use Binary Search Tree for implementation.

INPUT: A word & its meaning

OUTPUT:BST of dictionary words

AUTHOR: Ashish Dange
*/
#include <iostream>
#include <string>

using namespace std;

const int MAX_STACK = 100;

struct Node {
  string word;
  string meaning;
  Node *left, *right;

  Node(string w, string m) : word(w), meaning(m), left(nullptr), right(nullptr) {}
};

class Stack {
  private:
    Node* arr[MAX_STACK];
    int topIdx;
  public:
    Stack() : topIdx(-1) {}

    void push(Node* val) {
      if (topIdx < MAX_STACK - 1) {
        arr[++topIdx] = val;
      } else {
        cout << "\nStack Overflow!";
      }
    }

    Node* pop() {
      if (!isEmpty()) return arr[topIdx--];
      return nullptr;
    }

    bool isEmpty() { return topIdx == -1; }
};

class BST {
  private:
    Node *root;
    Stack S;

    Node* insertRecursive(Node* node, string w, string m) {
      if (!node) return new Node(w, m);

      if (w < node->word)
        node->left = insertRecursive(node->left, w, m);
      else if (w > node->word)
        node->right = insertRecursive(node->right, w, m);
      else 
        cout << "\nWord already exists in dictionary!\n";

      return node;
    }

    Node* deleteRecursive(Node* node, string key) {
      if (node == nullptr) {
        return node;
      }

      if (key < node->word) {
        node->left = deleteRecursive(node->left, key);
      } else if (key > node->word) {
        node->right = deleteRecursive(node->right, key);
      } else {
        if (node->left == nullptr) {
          Node* temp = node->right;
          delete node;
          return temp;
        } else if (node->right == nullptr) {
          Node* temp = node->left;
          delete node;
          return temp;
        } else {
          Node* successor = node->right;
          while (successor && successor->left != nullptr) {
            successor = successor->left;
          }
          node->word = successor->word;
          node->meaning = successor->meaning;
          node->right = deleteRecursive(node->right, successor->word);
        }
      }
      return node;
    }

    void displayAsc(Node* node) {
      if (node) {
        displayAsc(node->left);
        cout << "[" << node->word << " : " << node->meaning << "]\n";
        displayAsc(node->right);
      }
    }

    void pushInOrder(Node* node) {
      if (node) {
        pushInOrder(node->left);
        S.push(node);
        pushInOrder(node->right);
      }
    }

    void clear(Node* node) {
      if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
      }
    }

  public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void add(string word, string meaning) {
      root = insertRecursive(root, word, meaning);
    }

    void remove(string word) {
      if (!root) { cout << "\nTree is empty!\n"; return; }
      root = deleteRecursive(root, word);
    }

    void update(string word) {
      Node* curr = root;
      while (curr) {
        if (word == curr->word) {
          cout << "Current meaning: " << curr->meaning << "\nEnter new meaning: ";
          getline(cin, curr->meaning);
          cout << "Updated successfully!\n";
          return;
        }
        curr = (word < curr->word) ? curr->left : curr->right;
      }
      cout << "\nWord not found to update!\n";
    }

    void search(string key) {
      Node* curr = root;
      int comps = 0;

      while (curr) {
        comps++;
        if (key == curr->word) {
          cout << "\nFound! [" << curr->word << " : " << curr->meaning << "]\n";
          cout << "Total comparisons: " << comps << "\n";
          return;
        }
        curr = (key < curr->word) ? curr->left : curr->right;
      }
      cout << "\nWord not found. Comparisons made: " << comps << "\n";
    }

    void printAscending() {
      if (!root) cout << "Dictionary is empty.\n";
      else displayAsc(root);
    }

    void printDescending() {
      if (!root) {
        cout << "Dictionary is empty.\n";
        return;
      }
      pushInOrder(root);
      while (!S.isEmpty()) {
        Node* t = S.pop();
        cout << "[" << t->word << " : " << t->meaning << "]\n";
      }
    }
};

int main() {
  BST dict;
  int choice = 0;
  string word, meaning;

  while (choice != 7) {
    cout << "\n--- BST Dictionary ---\n";
    cout << "1. Add Word\n2. Display Ascending\n3. Display Descending\n";
    cout << "4. Update Word\n5. Search Word\n6. Delete Word\n7. Exit\n";
    cout << "Choice: ";

    cin >> choice;
    cin.ignore();
    switch (choice) {
      case 1:
        cout << "Enter Word: "; getline(cin, word);
        cout << "Enter Meaning: "; getline(cin, meaning);
        dict.add(word, meaning);
        break;
      case 2:
        cout << "\n--- Ascending Order ---\n";
        dict.printAscending();
        break;
      case 3:
        cout << "\n--- Descending Order ---\n";
        dict.printDescending();
        break;
      case 4:
        cout << "Enter Word to update: "; getline(cin, word);
        dict.update(word);
        break;
      case 5:
        cout << "Enter Word to search: "; getline(cin, word);
        dict.search(word);
        break;
      case 6:
        cout << "Enter Word to delete: "; getline(cin, word);
        dict.remove(word);
        break;
      case 7:
        cout << "Exiting...\n";
        break;
      default:
        cout << "Invalid choice!\n";
    }
  }
  return 0;
}
