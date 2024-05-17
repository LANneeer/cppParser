//
// Created by Laner on 16/05/2024.
//

#ifndef FINAL_RBNTREE_H
#define FINAL_RBNTREE_H

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include "otherStructs.h"

using namespace std;

enum Color {
    RED,
    BLACK
};

struct Node {
    shared_ptr<Node> parent;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    Color color;
    shared_ptr<Book> book;

    Node(shared_ptr<Book> book)
        : parent(nullptr), left(nullptr), right(nullptr), color(RED), book(book) {}
};


class RBNTree {
private:
    shared_ptr<Node> root;
    shared_ptr<Node> nil;

    void inorderHelper(shared_ptr<Node> node, std::function<void(shared_ptr<Book>)> visit) const {
        if (node != nil) {
            inorderHelper(node->left, visit);
            visit(node->book);
            inorderHelper(node->right, visit);
        }
    }

public:
    RBNTree() {
        nil = make_shared<Node>(nullptr);
        nil->color = BLACK;
        root = nil;
    }

    void leftRotate(shared_ptr<Node> xnode) {
        shared_ptr<Node> ynode = xnode->right;
        xnode->right = ynode->left;
        if (ynode->left != nil) {
            ynode->left->parent = xnode;
        }
        ynode->parent = xnode->parent;
        if (xnode->parent == nil) {
            root = ynode;
        } else if (xnode == xnode->parent->left) {
            xnode->parent->left = ynode;
        } else {
            xnode->parent->right = ynode;
        }
        ynode->left = xnode;
        xnode->parent = ynode;
    }

    void rightRotate(shared_ptr<Node> xnode) {
        shared_ptr<Node> ynode = xnode->left;
        xnode->left = ynode->right;
        if (ynode->right != nil) {
            ynode->right->parent = xnode;
        }
        ynode->parent = xnode->parent;
        if (xnode->parent == nil) {
            root = ynode;
        } else if (xnode == xnode->parent->right) {
            xnode->parent->right = ynode;
        } else {
            xnode->parent->left = ynode;
        }
        ynode->right = xnode;
        xnode->parent = ynode;
    }

    void insert(shared_ptr<Book> book) {
        shared_ptr<Node> znode = make_shared<Node>(book);
        shared_ptr<Node> ynode = nil;
        shared_ptr<Node> xnode = root;
        while (xnode != nil) {
            ynode = xnode;
            if (znode->book->getPriceWithoutTax() < xnode->book->getPriceWithoutTax()) {
                xnode = xnode->left;
            } else {
                xnode = xnode->right;
            }
        }
        znode->parent = ynode;
        if (ynode == nil) {
            root = znode;
        } else if (znode->book->getPriceWithoutTax() < ynode->book->getPriceWithoutTax()) {
            ynode->left = znode;
        } else {
            ynode->right = znode;
        }
        znode->left = nil;
        znode->right = nil;
        znode->color = RED;
        insertFixup(znode);
    }

    void insertFixup(shared_ptr<Node> znode) {
        while (znode->parent->color == RED) {
            if (znode->parent == znode->parent->parent->left) {
                shared_ptr<Node> ynode = znode->parent->parent->right;
                if (ynode->color == RED) {
                    znode->parent->color = BLACK;
                    ynode->color = BLACK;
                    znode->parent->parent->color = RED;
                    znode = znode->parent->parent;
                } else {
                    if (znode == znode->parent->right) {
                        znode = znode->parent;
                        leftRotate(znode);
                    }
                    znode->parent->color = BLACK;
                    znode->parent->parent->color = RED;
                    rightRotate(znode->parent->parent);
                }
            } else {
                shared_ptr<Node> ynode = znode->parent->parent->left;
                if (ynode->color == RED) {
                    znode->parent->color = BLACK;
                    ynode->color = BLACK;
                    znode->parent->parent->color = RED;
                    znode = znode->parent->parent;
                } else {
                    if (znode == znode->parent->left) {
                        znode = znode->parent;
                        rightRotate(znode);
                    }
                    znode->parent->color = BLACK;
                    znode->parent->parent->color = RED;
                    leftRotate(znode->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void inorder() const {
        inorderHelper(root, [](shared_ptr<Book> book) {
            cout << "Title: " << book->getTitle() << "| Price without tax: " << book->getPriceWithoutTax() << endl;
            cout << "Availability: " << book->getAvailability() << "| Rate: " << book->getRate() << endl;
            cout << "------------------------------------------------" << endl;
        });
    }

    void inorder(std::function<void(shared_ptr<Book>)> visit) const {
        inorderHelper(root, visit);
    }
};

#endif //FINAL_RBNTREE_H
