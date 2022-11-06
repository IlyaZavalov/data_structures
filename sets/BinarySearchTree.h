//
// Created by ilyazavalov on 29/10/22.
//

#ifndef DATA_STRUCTURES_BINARYSEARCHTREE_H
#define DATA_STRUCTURES_BINARYSEARCHTREE_H

#include <utility>

namespace ds {
    template<typename T>
    class BinarySearchTree {
    public:
        class Node {
        protected:
            T key;
            Node *left, *right, *parent;
        public:
            explicit Node(const T& k, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : key(k), left(l), right(r), parent(p) { }

            virtual ~Node() = default;

            virtual Node* get_left() {
                return left;
            }

            virtual Node* get_right() {
                return right;
            }

            virtual Node* get_parent() {
                return parent;
            }

            T get_key() {
                return key;
            }
            friend class BinarySearchTree;
        };


        virtual Node* find(const T& x) = 0;
        virtual Node* insert(const T& x) = 0;
        virtual bool erase(const T& x) = 0;
        virtual bool contains(const T& x) = 0;

        static Node* bt_search(Node* current, const T& x) {
            if(current == nullptr) {
                return nullptr;
            }
            if(current->key == x) {
                return current;
            }
            else if(current->key < x) {
                return bt_search(current->right, x);
            }
            else if(current->key > x) {
                return bt_search(current->left, x);
            }
        }
    };

} // ds

#endif //DATA_STRUCTURES_BINARYSEARCHTREE_H
