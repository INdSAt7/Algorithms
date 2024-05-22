#include <iostream>
#include "AVLTree.h"

void displayMenu() {
    cout << "1. Add a node\n";
    cout << "2. Remove a node\n";
    cout << "3. Search for a node\n";
    cout << "4. Get balance of current subtree\n";
    cout << "5. Get height of current subtree\n";
    cout << "6. Traversal\n";
    cout << "7. Exit\n";
}

void displayTraversalMenu() {
    cout << "1. Go to root\n";
    cout << "2. Move to left child\n";
    cout << "3. Move to right child\n";
    cout << "4. Move to parent\n";
    cout << "5. Print current node\n";
    cout << "6. Check balance of current subtree\n";
    cout << "7. Check height of current subtree\n";
    cout << "8. Return to main menu\n";
}

int main() {
    AVLTree tree;
    int choice, key;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter key to insert: ";
                std::cin >> key;
                tree.insert(key);
                break;
            case 2:
                std::cout << "Enter key to remove: ";
                std::cin >> key;
                tree.deleteNode(key);
                break;
            case 3:
                std::cout << "Enter key to search: ";
                std::cin >> key;
                if (tree.search(key)) {
                    std::cout << "Node found.\n";
                } else {
                    std::cout << "Node not found.\n";
                }
                break;
            case 4:
                std::cout << "Balance of current subtree: " << tree.getCurrentBalance() << std::endl;
                break;
            case 5:
                std::cout << "Height of current subtree: " << tree.getCurrentHeight() << std::endl;
                break;
            case 6:
                while (true) {
                    displayTraversalMenu();
                    std::cout << "Enter your choice: ";
                    std::cin >> choice;

                    if (choice == 6.8) {
                        break;
                    }

                    switch (choice) {
                        case 1:
                            tree.startTraversal();
                            std::cout << "Moved to root.\n";
                            break;
                        case 2:
                            tree.moveLeft();
                            break;
                        case 3:
                            tree.moveRight();
                            break;
                        case 4:
                            tree.moveParent();
                            break;
                        case 5:
                            if (tree.getCurrentNode()) {
                                std::cout << "Current node: " << tree.getCurrentNode()->key << std::endl;
                            } else {
                                std::cout << "Current node is null.\n";
                            }
                            break;
                        case 6:
                            std::cout << "Balance of current subtree: " << tree.getCurrentBalance() << std::endl;
                            break;
                        case 7:
                            std::cout << "Height of current subtree: " << tree.getCurrentHeight() << std::endl;
                            break;
                        default:
                            std::cout << "Invalid choice.\n";
                            break;
                    }
                }
                break;
            case 7:
                return 0;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }
    }

    return 0;
}
