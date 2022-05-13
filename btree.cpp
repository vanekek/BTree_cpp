#include <btree.h>

using namespace std;

BTree::Btree() {
    root = new Node [sizeof(Node)];
    root->current_size = 0;
    root->leaf = true;

}

BTree::BTree(int size, vector<int> arr) {
    if (arr.size() > node_keys) {
        throw EINVARG;
    }
    root = new Node [sizeof(Node)];
    root->current_size = size;
    for (int i = 0; i < arr.size(); ++i) {
        root->keys[i] = arr[i];
    }
    root->leaf = true;
}

BTree::BTree(const BTree &tree) {
    Node *old_root = tree.get_data();
    root = new Node [sizeof(Node)];
    root->leaf = old_root->leaf;
    root->current_size = old_root->current_size;
    for (int i = 0; i < old_root->current_size; ++i) {
        root->keys[i] = old_root->keys[i];
    }
}

BTree::~BTree() {
    delete [] root;
    root = NULL;
}

void BTree::key_insert(const int key) {

    if (root->current_size == node_keys) {
		Node *new_root = new Node [sizeof(Node)];
		new_root->leaf = false;
		new_root->child[0] = root;
		root = new_root;
		split_child(new_root, 0);
	}

	Node *current_node = root;

	while(current_node->leaf == false) {

		int index = current_node->current_size - 1;
		while ((index >= 0) && (key < current_node->keys[index])) {
			index -= 1;
		}
		index += 1;

		if (current_node->child[index]->current_size == node_keys) {
			split_child(current_node, index);
			if (current_node->keys[index] < key) {
				index += 1;
			}
		}

		current_node = current_node->child[index];
	}

	insert_node(current_node, key);
}

void BTree::delete_from_btree(const int key) {
    Node *current = root;
	while (1) {
		int i = 0;
		while ((i < current->current_size) && (current->keys[i] < key)) {
			++ i;
		}

		if ((i < current->current_size) && !((current->keys[i] < key) || (key < current->keys[i]))) {
			int res = current->keys[i];

			if (current->leaf == true) {
				delete_from_node(current, i);
			} else {
				Node *left = current->child[i];
				Node *right = current->child[i + 1];

				if (left->current_size >= node_order) {
					while (left->leaf != true) {
						check_size(left, left->current_size);
						left = left->child[left->current_size];
					}
					current->keys[i] = delete_from_node(left, left->current_size - 1);
				} else if (right->current_size >= node_order) {
					while (right->leaf != true) {
						check_size(right, 0);
						right = right->child[0];
					}
					current->keys[i] = delete_from_node(right, 0);
				} else {
					merge_children(current, i);
					current = left;
					continue;
				}
			}
			cout << "Key " << res << " was successfully deleted !" << endl;
			return;
		} else {
			if (current->leaf == true) {
					throw EINVARG;
			}
			int modification = check_size(current, i);
			if (modification == 1) {
				current = root;
			} else {
				int j = 0;
				while ((j < current->current_size) && (current->keys[j] < key)) {
					++ j;
				}
				current = current->child[j];
			}
		}
	}
}

void BTree::search(Node *node, const int key) {
    int i = 0;
	while ((i < node->current_size) && (key > node->keys[i])) {
		i++;
	}

	if ((i <= node->current_size) && (key == node->keys[i])) {
		cout << "Key " << key << " is found in Node:";
		cout << " [ ";
		for (const auto& a : node->keys) {
            cout << a << " ";
		}
		cout << "]" << endl;
	} else if (node->leaf == true) {
		cout << "Key " << key << " wasn't found" << endl;
	} else {
		search(node->child[i], key);
	}
}

BTree & BTree::operator=(const BTree &tree) {
    delete [] root;
    root = new Node [sizeof(Node)];
    root->current_size = tree.root->current_size;
    root->leaf = tree.root->leaf;
    for (int i = 0; i < tree.root->current_size; ++i) {
        root->keys[i] = tree.root->keys[i];
    }
    return *this;
}

int BTree::insert_node(Node *node, const int key) {
    int index;

	for (index = node->current_size; (index > 0) && (key < node->keys[index - 1]); --index) {
		node->keys[index] = node->keys[index - 1];
		node->child[index + 1] = node->child[index];
	}

	node->keys[index] = key;
	node->child[index + 1] = node->child[index];
	node->current_size += 1;
	
	return index;
}

void BTree::split_child(Node *parent, const int i) {
    if ((i > 5) || (i < 0)) {
        throw EINVARG;
    }
    Node *splitted_node = parent->child[i];
	Node *new_node = new Node [sizeof(Node)];
	new_node->leaf = splitted_node->leaf;
	new_node->current_size = node_order - 1;

	for (int k = 0; k < node_order - 1; ++k) {
		new_node->keys[k] = splitted_node->keys[k + node_order];
	}
	if (splitted_node->leaf == false) {
		for (int j = 0; j < node_order; ++j) {
			new_node->child[j] = splitted_node->child[j+node_order];
		}
	}
	splitted_node->current_size = node_order - 1;

	insert_node(parent, splitted_node->keys[node_order - 1]); //we are lifting median key to parent//
	parent->child[i + 1] = new_node;
}



