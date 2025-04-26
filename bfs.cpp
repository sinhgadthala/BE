#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Function to insert nodes in level order
Node* insert(Node* root, int data) {
    if (!root) {
        return new Node(data);
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if (!temp->left) {
            temp->left = new Node(data);
            return root;
        } else {
            q.push(temp->left);
        }

        if (!temp->right) {
            temp->right = new Node(data);
            return root;
        } else {
            q.push(temp->right);
        }
    }
    return root;
}

// Parallel Breadth-First Search (BFS)
void parallel_bfs(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    cout << "Nodes visited in BFS order: ";
    
    while (!q.empty()) {
        int qSize = q.size();

        #pragma omp parallel for
        for (int i = 0; i < qSize; i++) {
            Node* currNode;

            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << currNode->data << " ";
            }

            #pragma omp critical
            {
                if (currNode->left) q.push(currNode->left);
                if (currNode->right) q.push(currNode->right);
            }
        }
    }
    cout << endl;
}

int main() {
    Node* root = nullptr;
    int data;
    char ans;

    do {
        cout << "\nEnter data: ";
        cin >> data;
        root = insert(root, data);
        cout << "Do you want to insert another node? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    parallel_bfs(root);
    return 0;
}
