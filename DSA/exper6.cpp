/*AIM:
Consider telephone book database of N clients.
Make use of a hash table implementation to quickly look up 
client‘s telephone number.
Make use of two collision handling techniques and 
compare them using number of comparisons required 
to find a set of telephone numbers.

INPUT: Client Information, name and telephone number

OUTPUT: Search and display Client telephone number

Author: Ashish Dange

Linear Probing - hf=key%sizeoftable
Quadratic Probing - 
	i=1
	hi= (i^2+key)%sizeoftable
*/
#include <iostream>
#include <string>

using namespace std;

const int SIZE = 10;

struct Client {
  long long phone;
  string name;
  // -1 = Empty, -2 = Deleted (Tombstone)
  Client() : phone(-1), name("") {}
  Client(long long p, string n) : phone(p), name(n) {}
};

class TelephoneDirectory {
  private:
    Client linearTable[SIZE];
    Client quadTable[SIZE];

    int getNextIndex(int baseHash, int step, bool isQuadratic) {
      if (isQuadratic) {
        return (baseHash + (step * step)) % SIZE;
      } else {
        return (baseHash + step) % SIZE;
      }
    }

  public:
    void insert(long long phone, string name, bool isQuadratic) {
      Client* table = isQuadratic ? quadTable : linearTable;
      int baseHash = phone % SIZE;
      int i = 0;

      while (i < SIZE) {
        int index = getNextIndex(baseHash, i, isQuadratic);

        // Insert if the slot is Empty (-1) or was previously Deleted (-2)
        if (table[index].phone == -1 || table[index].phone == -2) {
          table[index] = Client(phone, name);
          cout << "Inserted [" << name << "] at index " << index 
            << " using " << (isQuadratic ? "Quadratic" : "Linear") << " Probing.\n";
          return;
        }
        i++;
      }
      cout << "Error: Hash Table is full!\n";
    }

    void search(long long phone, bool isQuadratic) {
      Client* table = isQuadratic ? quadTable : linearTable;
      int baseHash = phone % SIZE;
      int i = 0;
      int comparisons = 0;

      while (i < SIZE) {
        int index = getNextIndex(baseHash, i, isQuadratic);
        comparisons++;

        if (table[index].phone == phone) {
          cout << "Found [" << table[index].name << "] at index " << index 
            << " after " << comparisons << " comparisons.\n";
          return;
        }
        else if (table[index].phone == -1) {
          break; 
        }
        i++;
      }
      cout << "Record not found. Total comparisons: " << comparisons << "\n";
    }

    void display() {
      cout << "\n--- Hash Tables Status ---\n";
      cout << "Index\tLinear Probing\t\tQuadratic Probing\n";
      cout << "--------------------------------------------------------\n";

      for (int i = 0; i < SIZE; i++) {
        cout << i << "\t";

        if (linearTable[i].phone > 0) 
          cout << "[" << linearTable[i].phone << " : " << linearTable[i].name << "]";
        else 
          cout << "[ Empty ]";

        cout << "\t\t";

        if (quadTable[i].phone > 0) 
          cout << "[" << quadTable[i].phone << " : " << quadTable[i].name << "]";
        else 
          cout << "[ Empty ]";

        cout << "\n";
      }
      cout << "--------------------------------------------------------\n";
    }
};

int main() {
  TelephoneDirectory directory;
  int choice = 0;
  long long phone;
  string name;

  while (choice != 4) {
    cout << "\n--- Telephone Directory (Hash Tables) ---\n";
    cout << "1. Insert Record\n2. Search Record\n3. Display Tables\n4. Exit\n";
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        cout << "Enter Phone Number: "; cin >> phone;
        cout << "Enter Name: "; cin >> ws; getline(cin, name);

        directory.insert(phone, name, false); // Linear
        directory.insert(phone, name, true);  // Quadratic
        break;

      case 2:
        cout << "Enter Phone Number to search: "; cin >> phone;

        cout << "\n[Linear Probing Search]\n";
        directory.search(phone, false);

        cout << "\n[Quadratic Probing Search]\n";
        directory.search(phone, true);
        break;

      case 3:
        directory.display();
        break;

      case 4:
        cout << "Exiting...\n";
        break;

      default:
        cout << "Invalid choice!\n";
    }
  }
  return 0;
}
