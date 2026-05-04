/*Use the map of the area around the college as the graph.
  Identify the prominent land marks as nodes.
  Represent a given graph using adjacency matrix/list 
  to perform DFS 
  and 
  using adjacency list to perform BFS.

INPUT: Graph G

OUTPUT:DFS / BFS travesals

AUTHOR: Ashish Dange
*/
#include <iostream>
#include <string>

using namespace std;

const int MAX_NODES = 10;

struct Node {
  int val;
  Node* next;

  Node(int data) : val(data), next(nullptr) {}
};

class Queue {
  private:
    int arr[MAX_NODES];
    int frontIdx, rearIdx;
  public:
    Queue() : frontIdx(-1), rearIdx(-1) {}

    bool isEmpty() { return frontIdx == -1; }

    void enqueue(int val) {
      if (rearIdx == MAX_NODES - 1) {
        cout << "\nQueue Full!";
        return;
      }
      if (frontIdx == -1) frontIdx = 0;
      arr[++rearIdx] = val;
    }

    int dequeue() {
      if (isEmpty()) return -1;
      int val = arr[frontIdx];
      if (frontIdx == rearIdx) {
        frontIdx = rearIdx = -1; 
      } else {
        frontIdx++;
      }
      return val;
    }
};

class CampusGraph {
  private:
    int matrix[MAX_NODES][MAX_NODES]; 
    Node* adjList[MAX_NODES]; 
    bool visited[MAX_NODES];

    int numNodes;
    string landmarks[MAX_NODES] = {"Admin", "Canteen", "Library", "Sports", "Workshop"};

    void dfsRecursive(int current) {
      visited[current] = true;
      cout << "[" << landmarks[current] << "] -> ";

      for (int i = 0; i < numNodes; i++) {
        if (matrix[current][i] == 1 && !visited[i]) {
          dfsRecursive(i);
        }
      }
    }

  public:
    CampusGraph() : numNodes(0) {
      for (int i = 0; i < MAX_NODES; i++) {
        adjList[i] = nullptr;
        for (int j = 0; j < MAX_NODES; j++) {
          matrix[i][j] = 0;
        }
      }
    }

    ~CampusGraph() {
      for (int i = 0; i < MAX_NODES; i++) {
        Node* current = adjList[i];
        while (current) {
          Node* temp = current;
          current = current->next;
          delete temp;
        }
      }
    }

    void resetVisited() {
      for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
      }
    }

    void createGraph() {
      cout << "\n--- Building Campus Graph ---\n";
      cout << "Available Landmarks (Nodes):\n";
      for (int i = 0; i < 5; i++) {
        cout << i << " : " << landmarks[i] << "\n";
      }

      cout << "\nHow many nodes are in your graph (Max 5)? ";
      cin >> numNodes;

      if (numNodes > 5 || numNodes < 1) {
        cout << "Limiting to 5 nodes.\n";
        numNodes = 5;
      }

      int edges, src, dest;
      cout << "How many paths (edges) connect them? ";
      cin >> edges;

      for (int i = 0; i < edges; i++) {
        cout << "Enter path " << i + 1 << " (Source Destination): ";
        cin >> src >> dest;

        if (src >= 0 && src < numNodes && dest >= 0 && dest < numNodes) {
          matrix[src][dest] = 1;
          matrix[dest][src] = 1; 

          Node* newNode1 = new Node(dest);
          newNode1->next = adjList[src];
          adjList[src] = newNode1;

          Node* newNode2 = new Node(src);
          newNode2->next = adjList[dest];
          adjList[dest] = newNode2;
        } else {
          cout << "Invalid nodes! Skip.\n";
        }
      }
    }

    void displayMatrix() {
      cout << "\n--- Adjacency Matrix ---\n\t";
      for (int i = 0; i < numNodes; i++) cout << i << "\t";
      cout << "\n";

      for (int i = 0; i < numNodes; i++) {
        cout << i << "\t";
        for (int j = 0; j < numNodes; j++) {
          cout << matrix[i][j] << "\t";
        }
        cout << "\n";
      }
    }

    void displayList() {
      cout << "\n--- Adjacency List ---\n";
      for (int i = 0; i < numNodes; i++) {
        cout << "[" << landmarks[i] << "] -> ";
        Node* current = adjList[i];
        while (current) {
          cout << landmarks[current->val] << " -> ";
          current = current->next;
        }
        cout << "NULL\n";
      }
    }

    void startDFS(int startNode) {
      if (startNode < 0 || startNode >= numNodes) return;
      cout << "\nDFS Traversal (Using Matrix): \n";
      resetVisited();
      dfsRecursive(startNode);
      cout << "END\n";
    }

    void startBFS(int startNode) {
      if (startNode < 0 || startNode >= numNodes) return;
      cout << "\nBFS Traversal (Using Adjacency List): \n";
      resetVisited();
      Queue Q;
      Q.enqueue(startNode);
      visited[startNode] = true;
      while (!Q.isEmpty()) {
        int current = Q.dequeue();
        cout << "[" << landmarks[current] << "] -> ";

        Node* neighbor = adjList[current];
        while (neighbor) {
          if (!visited[neighbor->val]) {
            Q.enqueue(neighbor->val);
            visited[neighbor->val] = true;
          }
          neighbor = neighbor->next;
        }
      }
      cout << "END\n";
    }
};

int main() {
  CampusGraph campus;
  int choice = 0, startNode;

  while (choice != 6) {
    cout << "\n--- Campus Map Operations ---\n";
    cout << "1. Create Graph Paths\n";
    cout << "2. Display Matrix\n";
    cout << "3. Display Adjacency List\n";
    cout << "4. Traverse via DFS\n";
    cout << "5. Traverse via BFS\n";
    cout << "6. Exit\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
      case 1: 
        campus.createGraph(); 
        break;
      case 2: 
        campus.displayMatrix(); 
        break;
      case 3: 
        campus.displayList(); 
        break;
      case 4:
        cout << "Enter Starting Node (0 to 4): ";
        cin >> startNode;
        campus.startDFS(startNode);
        break;
      case 5:
        cout << "Enter Starting Node (0 to 4): ";
        cin >> startNode;
        campus.startBFS(startNode);
        break;
      case 6: 
        cout << "Exiting...\n"; 
        break;
      default: 
        cout << "Invalid choice!\n";
    }
  }
  return 0;
}
