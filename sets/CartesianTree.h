//
// Created by ilyazavalov on 29/10/22.
//

#ifndef DATA_STRUCTURES_CARTESIANTREE_H
#define DATA_STRUCTURES_CARTESIANTREE_H

#include <random>
#include "BinarySearchTree.h"
#include "../utility_classes/RandomNumberGenerator.h"


namespace ds {
    template<typename T, typename RNG = RandomNumberGenerator>
    class CartesianTree: public BinarySearchTree<T> {
    public:
        class Node;
    private:
        RNG rng;
        std::size_t sz;
        Node* root;

        static std::pair<Node*, Node*> split(Node* c, const T& x) {
            if(c == nullptr) {
                return {nullptr, nullptr};
            }
            if(c->key < x) {
                auto [ls, rs] = split(c->get_right(), x);
                c->right = ls;
                if(rs != nullptr) {
                    rs->parent = nullptr;
                }
                if(c->get_right() != nullptr) {
                    c->get_right()->parent = c;
                }
                return {c, rs};
            }
            auto [ls, rs] = split(c->get_left(), x);
            c->left = rs;
            if(ls != nullptr) {
                ls->parent = nullptr;
            }
            if(c->get_left() != nullptr) {
                c->get_left()->parent = c;
            }
            return {ls, c};
        }

        static Node* merge(Node* l, Node* r) {
            if(l == nullptr) {
                return r;
            }
            if(r == nullptr) {
                return l;
            }

            if(l->prior > r->prior) {
                l->right = merge(l->get_right(), r);
                if(l->get_right() != nullptr) {
                    l->get_right()->parent = l;
                }
                return l;
            }
            r->left = merge(l, r->get_left());
            if(r->get_left() != nullptr) {
                r->get_left()->parent = r;
            }
            return r;
        }

        static Node* find_leftmost(Node* current) {
            if(current == nullptr) {
                return nullptr;
            }
            if(current->left == nullptr) {
                return current;
            }
            return find_leftmost(current->get_left());
        }

    public:
        class Node : public BinarySearchTree<T>::Node {
        private:
            int prior;
        public:
            explicit Node(RNG& generator, const T& k, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : BinarySearchTree<T>::Node(k, p, l, r) {
                prior = generator();
            }
            Node* get_left() {
                return dynamic_cast<Node*>(this->left);
            }

            Node* get_right() {
                return dynamic_cast<Node*>(this->right);
            }

            Node* get_parent() {
                return dynamic_cast<Node*>(this->parent);
            }
            friend class CartesianTree;
        };

        CartesianTree() {
            sz = 0;
            root = nullptr;
        }

        Node* find(const T& x) {
            return dynamic_cast<Node*>(BinarySearchTree<T>::bt_search(root, x));
        }

        Node* insert(const T& x) {
            if(contains(x)) {
                return nullptr;
            }
            auto new_node = new Node(rng, x);
            auto [l, r] = split(root, x);
            root = merge(merge(l, new_node), r);
            sz++;
            return new_node;
        }

        bool erase(const T& x) {
            if(!contains(x)) {
                return false;
            }
            auto [l, r] = split(root, x);
            auto leftmost = find_leftmost(r);

            if(leftmost->get_parent() != nullptr) {
                leftmost->get_parent()->left = nullptr;
                root = merge(l, r);
            }
            else {
                if(leftmost->get_right() != nullptr) {
                    leftmost->get_right()->parent = nullptr;
                }
                root = merge(l, leftmost->get_right());
            }

            delete leftmost;
            sz--;
            return true;
        }

        bool contains(const T& x) {
            return find(x) != nullptr;
        }

        bool empty() {
            return sz == 0;
        }

        std::size_t size() {
            return sz;
        }

//        template<typename U>
//        friend void debug_output(CartesianTree<U> &obj);
    };

//    template<typename U>
//    void debug_output(typename CartesianTree<U>::Node *cur) {
//        if(cur == nullptr) {
//            return;
//        }
//        std::cout << cur->get_key() << " " << (cur->get_left() ? cur->get_left()->get_key() : 0) << " " << (cur->get_right() ? cur->get_right()->get_key() : 0)  << " " << (cur->get_parent() ? cur->get_parent()->get_key() : 0)<< std::endl;
//        debug_output<U>(cur->get_left());
//        debug_output<U>(cur->get_right());
//    }
//
//    template<typename U>
//    void debug_output(CartesianTree<U> &obj) {
//        debug_output<U>(obj.root);
//        std::cout << std::endl;
//    }
} // ds

#endif //DATA_STRUCTURES_CARTESIANTREE_H
