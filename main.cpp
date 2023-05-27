#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <chrono>
                                                         // 6. симметричный обход
using namespace std;                                     // 7. Не записывается в файл
using namespace chrono;
                                                         // 9.Посмотреть пукт 5 на степике


struct Tree{
    int key;
    Tree* left;
    Tree* right;

    Tree(int value){
        key = value;
        left = nullptr;
        right = nullptr;
    }
};



Tree* insertNode(Tree* root, int value){
    if(root == nullptr){
        return new Tree(value);
    }

    if(value < root->key){
        root->left = insertNode(root->left, value);
    }
    else if (value > root->key){
        root->right = insertNode(root->right, value);
    }

    return root;
}



Tree* createTree(const vector<int>& array){
    Tree* root = nullptr;
    for(int num : array) {
        root = insertNode(root, num);
    }
    return root;
}



Tree* searchNode(Tree *root, int value){
    if(root == nullptr || root->key == value){
        return root;
    }
    if(value < root->key){
        return searchNode(root->left, value);
    }
    else{
        return searchNode(root->right, value);
    }
}



Tree* findMinimum(Tree* node){
    while(node->left != nullptr){
        node = node->left;
    }
    return node;
}



Tree* deleteNode(Tree* root, int value){
    if(root == nullptr){
        return root;
    }

    if(value < root->key){
        root->left = deleteNode(root->left, value);
    }
    else if(value > root->key){
        root->right = deleteNode(root->right, value);
    }
    else{
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
        }
        else if(root->left == nullptr){
            Tree* temp = root;
            root = root->left;
            delete temp;
        }
        else if(root->right == nullptr){
            Tree* temp = root;
            root = root->left;
            delete temp;
        }
        else{
            Tree* temp = findMinimum(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}



void printTree(Tree* root, string indent = "", bool isLeft = false){
    if(root == nullptr){
        return;
    }

    cout << indent;

    if(isLeft){
        cout << "*-- ";
        indent += "|   ";
    }
    else{
        cout << "`-- ";
        indent += "    ";
    }

    cout << root->key << endl;

    printTree(root->left, indent, true);
    printTree(root->right, indent, false);
}



void bypassDirect(Tree* root){
    if(root == nullptr){
        return;
    }

    cout << root->key << " ";
    bypassDirect(root->left);
    bypassDirect(root->right);
}



void bypassReverse(Tree* root){
    if(root == nullptr){
        return;
    }

    bypassReverse(root->left);
    bypassReverse(root->right);
    cout << root->key << " ";
}



void bypassIsWidth(Tree* root){
    if(root == nullptr){
        return;
    }
    bypassIsWidth(root->left);
    cout << root->key << " ";
    bypassIsWidth(root->right);
}



void deleteTree(Tree *root){
    if(root == nullptr){
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}



int main() {

    Tree* root = nullptr;
    vector<int> elements;

    while(true){
        int choice;
        cout << "\nChoice an option:\n";
        cout << "1. Create a binary tree with random numbers\n";
        cout << "2. Create a binary tree from entered numbers\n";
        cout << "3. FILE\n";
        cout << "4. Print binary tree\n";
        cout << "5. Insert an element\n";
        cout << "6. Delete an element\n";
        cout << "7. Get an element\n";
        cout << "8. Direct bypass binary tree\n";
        cout << "9. Reverse bypass binary tree\n";
        cout << "10. Bypass in width binary tree\n";
        cout << "Choice: ";
        cin >> choice;
        cout << "\n------------------------------------------------------------------------------------\n";
        switch(choice){
            case 1: {
                int numElements;
                cout << "Enter the number of elements:";
                cin >> numElements;

                for(int i = 0; i < numElements; i++){
                    int num = rand() % 199 - 99;
                    elements.push_back(num);
                }
                auto start = high_resolution_clock::now();

                root = createTree(elements);

                auto end = high_resolution_clock::now();

                auto duration = duration_cast<nanoseconds>(end - start);
                cout << "Time: " << duration.count() << "ns\n";

                cout << "Binary tree created\n";
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 2: {
                int num, numElements;
                cout << "Enter the number of elements:\n";
                cin >> numElements;

                cout << "Enter elements:";
                for(int i = 0; i < numElements; i++){
                    cin >> num;
                    elements.push_back(num);
                }
                auto start = high_resolution_clock::now();

                root = createTree(elements);

                auto end = high_resolution_clock::now();

                auto duration = duration_cast<nanoseconds>(end - start);
                cout << "Time: " << duration.count() << "ns\n";

                cout << "Binary tree created\n";
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 3: {

                break;
            }
            case 4: {
                if(root == nullptr){
                    cout << "Binary tree is empty\n";
                }
                else{
                    cout << "Binary tree: \n";
                    printTree(root);
                    cout << "\n------------------------------------------------------------------------------------\n";
                }
                break;
            }
            case 5: {
                int insertValue;
                cout << "Enter the element to insert: ";
                cin >> insertValue;

                auto start = high_resolution_clock::now();

                insertNode(root, insertValue);

                auto end = high_resolution_clock::now();

                auto duration = duration_cast<nanoseconds>(end - start);
                cout << "Time taken to insert element: " << duration.count() << " ns\n";

                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 6: {
                int deleteValue;
                cout << "Enter the element to delete: ";
                cin >> deleteValue;

                auto start = high_resolution_clock::now();

                deleteNode(root, deleteValue);

                auto end = high_resolution_clock::now();

                auto duration = duration_cast<nanoseconds>(end - start);
                cout << "Time taken to delete element: " << duration.count() << " ns\n";

                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 7: {
                int valueToSearch;
                cout << "Search an element: ";
                cin >> valueToSearch;

                auto start = high_resolution_clock::now();

                Tree* foundNode = searchNode(root, valueToSearch);
                if(foundNode){
                    cout << "Element found: " << foundNode->key << endl;
                }
                else {
                    cout << "Element not found\n";
                }
                auto end = high_resolution_clock::now();

                auto duration = duration_cast<milliseconds>(end - start);
                cout << "Time taken to get element " << duration.count() << "ms\n";
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 8: {
                cout << "Direct bypass: ";
                bypassDirect(root);
                cout << endl;
                printTree(root);
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 9: {
                cout << "Reverse bypass: ";
                bypassReverse(root);
                cout << endl;
                printTree(root);
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 10: {
                cout << "Bypass in width: ";
                bypassIsWidth(root);
                cout << endl;
                printTree(root);
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            default: {
                cout << "Error\n";
                break;
            }
        }
    }
}