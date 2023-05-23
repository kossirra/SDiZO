#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

struct Node {  
    int data;  
    Node *left;  
    Node *right;  
};  
Node* create(int item)  
{  
    Node* node = new Node;  
    node->data = item;  
    node->left = node->right = NULL;  
    return node;  
}  
/*Inorder traversal of the tree formed*/  
void inorder(Node *root)  
{  
    if (root == NULL)  
        return;  
    inorder(root->left); //traverse left subtree  
    cout<< root->data << "   "; //traverse root node  
    inorder(root->right); //traverse right subtree  
}  
Node* findMinimum(Node* cur) /*To find the inorder successor*/  
{  
    while(cur->left != NULL) {  
        cur = cur->left;  
    }  
    return cur;  
}  
Node* insertion(Node* root, int item) /*Insert a node*/  
{  
    if (root == NULL)  
        return create(item); /*return new node if tree is empty*/  
    if (item < root->data)  
        root->left = insertion(root->left, item);  
    else  
        root->right = insertion(root->right, item);  
    return root;  
}  
bool search(Node* root, int value) {
    if (root == nullptr) {
        return false;
    }

    if (value == root->data) {
        return true;
    } else if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

Node* deletion(Node* root, int item)
{
    if (root == NULL)
        return NULL;
    if (item < root->data)
        root->left = deletion(root->left, item);
    else if (item > root->data)
        root->right = deletion(root->right, item);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* succ = findMinimum(root->right);
        root->data = succ->data;
        root->right = deletion(root->right, succ->data);
    }
    return root;
}



int main() {
    Node* root = NULL;

     string filename = "small_numbers.csv";
    ifstream file(filename);
    if (!file) {
        cout << "Nie udało się otworzyć pliku. " << endl;
        return 1;
    }

    string line;
    while (getline(file, line, ',')) {
        int val = stoi(line);
        if (val >= -20 && val <= 20) {
            root = insertion(root, val);
        }
        else {
            cout << "Brak liczby w przedziale" << val << ". Pomijam." << endl;
        }
    }
    file.close();

    cout<<endl;

    printf("The inorder traversal of the given binary tree is - \n");  
    inorder(root);  
    cout<<endl;

    char choice = ' ';
    while (choice != 'T') {
        cout << "Wybierz co chcesz zrobić: " << endl
             << "1 - wyszukiwanie" << endl
             << "2 - dodawanie" << endl
             << "3 - usuwanie" << endl
             << "4 - Zamknij program" << endl
             << endl;
        cin >> choice;

        switch (choice) {
            case '1': {
                int value;
                cout << "Wpisz wartość, którą chcesz wyszukać?" << endl;
                cin >> value;
                if (search(root, value)) {
                    cout << "Wartość " << value << " została znaleziona w drzewie." <<endl;
                } else {
                    cout << "Wartość " << value << " nie została znaleziona w drzewie." <<endl;
                }
                break;
            }
            case '2': {
                int value;
                cout << "Wpisz wartość, którą chcesz dodać?" << endl;
                cin >> value;
                insertion(root, value);
                printf("\nAfter inserting node, the inorder traversal of the given binary tree is - \n");
                inorder(root);
                cout<<endl;
                break;
            }
            case '3': {
                int value;
                cout << "Wpisz wartość, którą chcesz usunąć?" << endl;
                cin >> value;
                deletion(root, value);
                printf("\nAfter deleting node, the inorder traversal of the given binary tree is - \n");
                inorder(root);
                cout << endl;
                break;
            }
            case '4': {
                char closeChoice;
                cout << "Czy na pewno chcesz zamknąć program? (T - Tak / N - Nie)" << endl;
                cin >> closeChoice;
                if (closeChoice == 'T') {
                    cout << "Zamykanie programu..." << endl;
                    return 0;
                }
                break;
            }
            default:
                cout << "Nieprawidłowy wybór. Wybierz opcję od 1 do 4." << endl;
                break;
        }
    }

    return 0;
}