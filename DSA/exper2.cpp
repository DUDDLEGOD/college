/*
   Construct an expression tree from the given prefix expression 
   eg. +--a*bc/def and 
   traverse it using post-order traversal(non recursive) 
   and then delete the entire tree.

INPUT: A prefix expression

OUTPUT: Expression tree

AUTHOR: Ashish Dange
*/
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_STACK = 50;

struct Node {
  char data;
  Node *left;
  Node *right;

  Node(char d) : data(d), left(nullptr), right(nullptr) {}
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
        cout << "\nStack Overflow!\n";
      }
    }

    Node* pop() {
      if (!isEmpty()) return arr[topIdx--];
      return nullptr;
    }

    bool isEmpty() { return topIdx == -1; }
};

class ExpressionTree {
  private:
    Node* root;
    char prefixExp[50]; // Increased buffer size
    bool isOperator(char c) {
      return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }
    bool isOperand(char c) {
      return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }
    void displayInOrder(Node* node) {
      if (node) {
        if (isOperator(node->data)) cout << "(";
        displayInOrder(node->left);
        cout << node->data;
        displayInOrder(node->right);
        if (isOperator(node->data)) cout << ")";
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
    ExpressionTree() : root(nullptr) {
      prefixExp[0] = '\0'; // Initialize empty string
    }

    ~ExpressionTree() { 
      clear(root); 
    }

    void readExpression() {
      cout << "\nEnter Prefix Expression (e.g., +--a*bc/def): ";
      cin >> ws; // Clear leading whitespace
      cin.getline(prefixExp, 50);
    }

    void printExpression() {
      if (strlen(prefixExp) == 0) {
        cout << "\nNo expression entered yet!\n";
        return;
      }
      cout << "\nCurrent Prefix Expression: " << prefixExp << "\n";
    }

    void buildTree() {
      if (strlen(prefixExp) == 0) {
        cout << "\nPlease read an expression first!\n";
        return;
      }
      clear(root);
      root = nullptr;
      Stack S;
      for (int i = strlen(prefixExp) - 1; i >= 0; i--) {
        char currentToken = prefixExp[i];
        if (currentToken == ' ') continue;
        Node* newNode = new Node(currentToken);
        if (isOperand(currentToken)) {
          S.push(newNode);
        } 
        else if (isOperator(currentToken)) {
          newNode->left = S.pop();
          newNode->right = S.pop();
          S.push(newNode);
        }
      }
      root = S.pop();
      cout << "\nTree built successfully!\n";
    }

    void printInOrder() {
      if (!root) {
        cout << "\nTree is empty! Build it first.\n";
        return;
      }
      cout << "\nIn-Order Traversal (Infix Expression): ";
      displayInOrder(root);
      cout << "\n";
    }

    void printPostOrderNonRecursive() {
      if (!root) {
        cout << "\nTree is empty! Build it first.\n";
        return;
      }
      Stack stack1, stack2;
      stack1.push(root);
      while (!stack1.isEmpty()) {
        Node* current = stack1.pop();
        stack2.push(current);
        if (current->left) stack1.push(current->left);
        if (current->right) stack1.push(current->right);
      }
      cout << "\nPost-Order Traversal (Postfix Expression): ";
      while (!stack2.isEmpty()) {
        cout << stack2.pop()->data;
      }
      cout << "\n";
    }
};

int main() {
  ExpressionTree tree;
  int choice = 0;

  while (choice != 6) {
    cout << "\n--- Expression Tree Menu ---\n";
    cout << "1. Enter Prefix Expression\n";
    cout << "2. View Current Expression\n";
    cout << "3. Build Expression Tree\n";
    cout << "4. Print In-Order (Infix)\n";
    cout << "5. Print Post-Order (Postfix, Non-Recursive)\n";
    cout << "6. Exit\n";
    cout << "Choice: ";

    cin >> choice;

    switch (choice) {
      case 1: tree.readExpression(); break;
      case 2: tree.printExpression(); break;
      case 3: tree.buildTree(); break;
      case 4: tree.printInOrder(); break;
      case 5: tree.printPostOrderNonRecursive(); break;
      case 6: cout << "\nExiting...\n"; break;
      default: cout << "\nInvalid choice!\n";
    }
  }
  return 0;
}
