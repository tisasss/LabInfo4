#include "BinaryTree.h"
#include <cassert>
#include <string>

void testBinaryTree() {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    std::stringstream ss;
    tree.preOrder(ss);
    assert(ss.str() == "5 3 7 ");

    auto doubled = tree.map<int>([](int x) { return x * 2; });
    ss.str("");
    doubled.preOrder(ss);
    assert(ss.str() == "10 6 14 ");

    auto even = tree.where([](int x) { return x % 2 == 0; });
    assert(even.isEmpty());

    BinaryTree<int> tree2;
    tree2.insert(4);
    auto merged = tree.merge(tree2);
    assert(merged.contains(4));

    auto subtree = tree.getSubtree(3);
    ss.str("");
    subtree.preOrder(ss);
    assert(ss.str() == "3 ");

    std::string serialized = tree.serialize();
    BinaryTree<int> deserialized;
    deserialized.deserialize(serialized);
    ss.str("");
    deserialized.preOrder(ss);
    assert(ss.str() == "5 3 7 ");

    assert(tree.findByPath("L") == 3);

    BinaryTree<double> doubleTree;
    doubleTree.insert(5.5);
    doubleTree.insert(3.3);
    doubleTree.insert(7.7);
    ss.str("");
    doubleTree.preOrder(ss);
    assert(ss.str() == "5.5 3.3 7.7 ");

    BinaryTree<std::string> stringTree;
    stringTree.insert("middle");
    stringTree.insert("left");
    stringTree.insert("right");
    ss.str("");
    stringTree.preOrder(ss);
    assert(ss.str() == "middle left right ");

    std::cout << "All tests passed!" << std::endl;
}

void consoleInterface() {
    std::string type;
    std::cout << "Choose data type (int, double, string): ";
    std::cin >> type;

    if (type == "int") {
        BinaryTree<int> tree;
        std::string command;
        while (true) {
            std::cout << "Commands: insert <value>, pre, in, post, map <value>, where <value>, merge <value>, subtree <value>, contains <value>, serialize, deserialize, path <path>, exit\n";
            std::cin >> command;
            try {
                if (command == "insert") {
                    int value;
                    std::cin >> value;
                    tree.insert(value);
                } else if (command == "pre") {
                    tree.preOrder();
                    std::cout << std::endl;
                } else if (command == "in") {
                    tree.inOrder();
                    std::cout << std::endl;
                } else if (command == "post") {
                    tree.postOrder();
                    std::cout << std::endl;
                } else if (command == "map") {
                    int value;
                    std::cin >> value;
                    auto mapped = tree.map<int>([value](int x) { return x + value; });
                    mapped.preOrder();
                    std::cout << std::endl;
                } else if (command == "where") {
                    int value;
                    std::cin >> value;
                    auto filtered = tree.where([value](int x) { return x > value; });
                    filtered.preOrder();
                    std::cout << std::endl;
                } else if (command == "merge") {
                    BinaryTree<int> other;
                    int value;
                    std::cin >> value;
                    other.insert(value);
                    auto merged = tree.merge(other);
                    merged.preOrder();
                    std::cout << std::endl;
                } else if (command == "subtree") {
                    int value;
                    std::cin >> value;
                    auto subtree = tree.getSubtree(value);
                    subtree.preOrder();
                    std::cout << std::endl;
                } else if (command == "contains") {
                    int value;
                    std::cin >> value;
                    std::cout << (tree.contains(value) ? "Found" : "Not found") << std::endl;
                } else if (command == "serialize") {
                    std::cout << tree.serialize() << std::endl;
                } else if (command == "deserialize") {
                    std::string data;
                    std::cin.ignore();
                    std::getline(std::cin, data);
                    tree.deserialize(data);
                } else if (command == "path") {
                    std::string path;
                    std::cin >> path;
                    std::cout << tree.findByPath(path) << std::endl;
                } else if (command == "exit") {
                    break;
                } else {
                    std::cout << "Unknown command\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    } else if (type == "double") {
        BinaryTree<double> tree;
        std::string command;
        while (true) {
            std::cout << "Commands: insert <value>, pre, in, post, map <value>, where <value>, merge, subtree <value>, contains <value>, serialize, deserialize, path <path>, exit\n";
            std::cin >> command;
            try {
                if (command == "insert") {
                    double value;
                    std::cin >> value;
                    tree.insert(value);
                } else if (command == "pre") {
                    tree.preOrder();
                    std::cout << std::endl;
                } else if (command == "in") {
                    tree.inOrder();
                    std::cout << std::endl;
                } else if (command == "post") {
                    tree.postOrder();
                    std::cout << std::endl;
                } else if (command == "map") {
                    double value;
                    std::cin >> value;
                    auto mapped = tree.map<double>([value](double x) { return x + value; });
                    mapped.preOrder();
                    std::cout << std::endl;
                } else if (command == "where") {
                    double value;
                    std::cin >> value;
                    auto filtered = tree.where([value](double x) { return x > value; });
                    filtered.preOrder();
                    std::cout << std::endl;
                } else if (command == "merge") {
                    BinaryTree<double> other;
                    double value;
                    std::cin >> value;
                    other.insert(value);
                    auto merged = tree.merge(other);
                    merged.preOrder();
                    std::cout << std::endl;
                } else if (command == "subtree") {
                    double value;
                    std::cin >> value;
                    auto subtree = tree.getSubtree(value);
                    subtree.preOrder();
                    std::cout << std::endl;
                } else if (command == "contains") {
                    double value;
                    std::cin >> value;
                    std::cout << (tree.contains(value) ? "Found" : "Not found") << std::endl;
                } else if (command == "serialize") {
                    std::cout << tree.serialize() << std::endl;
                } else if (command == "deserialize") {
                    std::string data;
                    std::cin.ignore();
                    std::getline(std::cin, data);
                    tree.deserialize(data);
                } else if (command == "path") {
                    std::string path;
                    std::cin >> path;
                    std::cout << tree.findByPath(path) << std::endl;
                } else if (command == "exit") {
                    break;
                } else {
                    std::cout << "Unknown command\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    } else if (type == "string") {
        BinaryTree<std::string> tree;
        std::string command;
        while (true) {
            std::cout << "Commands: insert <value>, pre, in, post, map <value>, where <value>, merge, subtree <value>, contains <value>, serialize, deserialize, path <path>, exit\n";
            std::cin >> command;
            try {
                if (command == "insert") {
                    std::string value;
                    std::cin >> value;
                    tree.insert(value);
                } else if (command == "pre") {
                    tree.preOrder();
                    std::cout << std::endl;
                } else if (command == "in") {
                    tree.inOrder();
                    std::cout << std::endl;
                } else if (command == "post") {
                    tree.postOrder();
                    std::cout << std::endl;
                } else if (command == "map") {
                    std::string value;
                    std::cin >> value;
                    auto mapped = tree.map<std::string>([value](const std::string& x) { return x + value; });
                    mapped.preOrder();
                    std::cout << std::endl;
                } else if (command == "where") {
                    std::string value;
                    std::cin >> value;
                    auto filtered = tree.where([value](const std::string& x) { return x > value; });
                    filtered.preOrder();
                    std::cout << std::endl;
                } else if (command == "merge") {
                    BinaryTree<std::string> other;
                    std::string value;
                    std::cin >> value;
                    other.insert(value);
                    auto merged = tree.merge(other);
                    merged.preOrder();
                    std::cout << std::endl;
                } else if (command == "subtree") {
                    std::string value;
                    std::cin >> value;
                    auto subtree = tree.getSubtree(value);
                    subtree.preOrder();
                    std::cout << std::endl;
                } else if (command == "contains") {
                    std::string value;
                    std::cin >> value;
                    std::cout << (tree.contains(value) ? "Found" : "Not found") << std::endl;
                } else if (command == "serialize") {
                    std::cout << tree.serialize() << std::endl;
                } else if (command == "deserialize") {
                    std::string data;
                    std::cin.ignore();
                    std::getline(std::cin, data);
                    tree.deserialize(data);
                } else if (command == "path") {
                    std::string path;
                    std::cin >> path;
                    std::cout << tree.findByPath(path) << std::endl;
                } else if (command == "exit") {
                    break;
                } else {
                    std::cout << "Unknown command\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    } else {
        std::cout << "Invalid type. Supported types: int, double, string\n";
    }
}

int main() {
    testBinaryTree();
    consoleInterface();
    return 0;
}
