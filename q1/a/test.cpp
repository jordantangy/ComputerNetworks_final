#include <iostream>
using namespace std;
typedef struct node {
char number;
node* right;
node* left;
node* previous;
} Node;

int main(){


    Node* n = new Node();
    cout << n << endl;
    delete n;
    n = NULL;
    cout << n << endl;


}