#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <chrono>
                                                         // очищать дерево
using namespace std;                                     // Читка из файл
using namespace chrono;



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



void writeTree(Tree* root, ofstream& outFile, string indent, bool isLeft) {
    if(root == nullptr){
        return;
    }

    outFile << indent;

    if(isLeft){
        outFile << "*-- ";
        indent += "|   ";
    }
    else{
        outFile << "`-- ";
        indent += "    ";
    }

    outFile << root->key << endl;

    writeTree(root->left, outFile, indent, false);
    writeTree(root->right, outFile, indent, true);
}



void writeOperations(Tree* root, const string& filename, int insertedValue, int deletedValue, int searchValue){

    ofstream outFile(filename, ios::app);
    if(!outFile){
        cout << "Failed to open file: " << filename << endl;
        return;
    }


    outFile << "Inserted value: " << insertedValue << endl;
    outFile << "Deleted value: " << deletedValue << endl;
    outFile << "Searched value: " << searchValue << endl;
    outFile << "\nBinary tree:" << endl;

    writeTree(root, outFile, "", true);
    outFile << "\n------------------------------------------------------------------------------------\n\n";
    outFile.close();

    cout << "Binary tree written to file: " << filename << endl;
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



void bypassSymmetrical(Tree* root){
    if(root == nullptr){
        return;
    }
    bypassSymmetrical(root->left);
    cout << root->key << " ";
    bypassSymmetrical(root->right);
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
    int insertedValue, deletedValue, searchValue;


    while(true){
        int choice;
        cout << "\nChoice an option:\n";
        cout << "1. Create a binary tree with random numbers\n";
        cout << "2. Create a binary tree from entered numbers\n";
        cout << "3. Output a binary tree from file\n";
        cout << "4. Print binary tree\n";
        cout << "5. Insert an element\n";
        cout << "6. Delete an element\n";
        cout << "7. Get an element\n";
        cout << "8. Direct bypass binary tree\n";
        cout << "9. Reverse bypass binary tree\n";
        cout << "10. Symmetrical bypass binary tree\n";
        cout << "11. Write tree and options to file\n";
        cout << "12. Clear tree\n";
        cout << "13. Exit\n";
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
                ifstream File;
                File.open("C:\\Users\\User\\CLionProjects\\coursework2\\output_tree.txt");
                if(File.is_open()){

                }
                else{
                    cout << "Error";
                }
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
                int value;
                cout << "Enter the element to insert: ";
                cin >> value;

                auto start = high_resolution_clock::now();

                insertNode(root, value);
                insertedValue = value;

                auto end = high_resolution_clock::now();

                cout << "Value: " << value << " inserted into the binary tree\n";

                auto duration = duration_cast<nanoseconds>(end - start);
                cout << "Time taken to insert element: " << duration.count() << " ns\n";

                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 6: {
                int value;
                cout << "Enter the element to delete: ";
                cin >> value;

                auto start = high_resolution_clock::now();

                deleteNode(root, value);
                deletedValue = value;

                auto end = high_resolution_clock::now();

                cout << "Value: " << value << " deleted from the binary tree\n";

                auto duration = duration_cast<nanoseconds>(end - start);
                cout << "Time taken to delete element: " << duration.count() << " ns\n";

                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 7: {
                int value;
                cout << "Search an element: ";
                cin >> value;

                auto start = high_resolution_clock::now();

                Tree* foundNode = searchNode(root, value);
                if(foundNode){
                    searchValue = value;
                    cout << "Value: " << value << " found in the binary tree\n";
                }
                else {
                    cout << "Value: " << value << " not found in the binary tree\n";
                }
                auto end = high_resolution_clock::now();

                auto duration = duration_cast<nanoseconds>(end - start);
                cout << "Time taken to get element " << duration.count() << "ns\n";
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
                cout << "Symmetrical bypass: ";
                bypassSymmetrical(root);
                cout << endl;
                printTree(root);
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 11: {
                string path = "C:\\Users\\User\\CLionProjects\\coursework2\\tree.txt";

                ofstream fout;

                fout.open(path, ofstream::app);

                if(!fout.is_open()){
                    cout << "File opening error\n";
                }
                else{
                    writeOperations(root, path, insertedValue, deletedValue, searchValue);
                }
                break;
            }
            case 12: {
                deleteTree(root);
                cout << "Tree is clean\n";
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
            case 13: {
                return 0;
            }
            default: {
                cout << "Invalid option. Please try again\n";
                cout << "\n------------------------------------------------------------------------------------\n";
                break;
            }
        }
    }
}