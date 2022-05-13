#include <iostream>
#include <vector>

#define node_order		3  //degree of tree//
#define node_pointers	(node_order*2)
#define node_keys		node_pointers - 1

using namespace std;

struct Node 
{
    int keys[node_keys];
    struct Node *child[node_pointers];
    unsigned int current_size;
    bool leaf;
};

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
    BTree(vector<int> arr);
    BTree(const BTree &tree);
    ~Btree();

    void key_insert(const int key);
    void delete_from_btree(const int key);
    void search(Node *node, const int key);

    BTree &operator=(const BTree &tree);

    Node *get_data() const { return root; };

    static void perform_recursive_output(std::ostream& output, const Node &n, int ots) {
        for (int i = 0; i < ots; i++) {
            output << "\t";
        }

        for (unsigned i = 0; i < n.current_size; i++) {
            output << n.keys[i] << " ";
        }
        output << endl;
        if (n.leaf == false) {
            ots++;
            for (unsigned i = 0; i <= n.current_size; i++) {
                perform_recursive_output(output, *n.child[i], ots);
            }
        }
    }
    friend ostream &operator<<(ostream &output, const BTree &tree) {
        Node *n = tree.get_data();
        perform_recursive_output(output, *n, 2);
		return output;
	};
private:
    int insert_node(Node *node, const int key);
    void split_child(Node *parent, const int i);

    int delete_from_node(Node *node, int i);                                                        
    int merge_children(Node *parent, int i);
    int check_size(Node *parent, int i);
    //root of btree -- contains all the info//
    Node *root;
};
