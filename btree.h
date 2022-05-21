#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <vector>

#define node_order		3  //degree of tree//
#define node_pointers	node_order*2
#define node_keys		node_pointers - 1

using namespace std;

template<typename T>
class Node
{
    T keys[node_keys];
    Node<T> *child[node_pointers];
    int current_size;
    bool leaf;

    template <typename U>
    friend class BTree;
};

template<typename T>
class BTree
{
public:
    enum btree_error {
        ESUCCESS = 0,
	    EINVARG,
	    EEMPTY,
	    EMALLOC
    };

    BTree();
    BTree(vector<T> arr);
    BTree(const BTree &tree);
    ~BTree();

    void key_insert(T key);
    void delete_from_btree(T key);
    void search(T key);

    BTree<T>& operator=(const BTree<T> &tree);

    bool operator > (const BTree<T> &tree1);

    bool operator < (const BTree<T> &tree1);

    bool operator == (const BTree<T> &tree1);

    bool operator != (const BTree<T> &tree1);

    bool operator <= (const BTree<T> &tree1);

    bool operator >= (const BTree<T> &tree1);

    Node<T> *get_data() const { return root; };

    static void perform_recursive_output(std::ostream& output, Node<T> *n, int ots) {
        for (int i = 0; i < ots; i++) {
            output << "\t";
        }

        for (int i = 0; i < n->current_size; i++) {
            output << n->keys[i] << " ";
        }
        output << endl;
        if (n->leaf == false) {
            ots++;
            for (int i = 0; i <= n->current_size; i++) {
                perform_recursive_output(output, n->child[i], ots);
            }
        }
    }
    friend ostream &operator<<(ostream &output, const BTree &tree) {
        Node<T> *n = tree.get_data();
        perform_recursive_output(output, n, 2);
		return output;
	}

private:
    void create_node(Node<T> *node);

    void search_in_node(Node<T> *node, T key);

    int insert_node(Node<T> *node, T key);
    void split_child(Node<T> *parent, const int i);

    T delete_from_node(Node<T> *node, int i);                                                        
    int merge_children(Node<T> *parent, int i);
    int check_size(Node<T> *parent, int i);

    //void bnode_delete(Node *node);

    //root of btree -- contains all the info//
    Node<T> *root;
};

#endif  // _STACK_H_