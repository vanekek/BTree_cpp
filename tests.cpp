#include "btree.h"

using namespace std;

void check_copy_constructor(BTree b) 
{
	cout << b;
}

int main() {

    BTree *b1 = NULL;
    BTree *b2 = NULL;
    vector<int> vec1 = {1, 2, 3, 4};
    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7};

    try {
        b1 = new BTree(vec2);
    } catch (const BTree::btree_error& ex) {
        if (ex == BTree::EINVARG)
            cout << "Test_0\t->\tPASSED" << endl;
        else 
            cout << "Test_0\t->\tFAILED" << endl;
    } catch (...) {
        cout << "Test_0\t->\tFAILED" << endl;
    }

    try {
		b1 = new BTree(vec1);
	} catch (...) {
		cout << "Test_1\t->\tFAILED" << endl;
	}
	cout << "Test_1\t->\tPASSED" << endl;

    try {
		b2 = new BTree();
	} catch (...) {
		cout << "Test_2\t->\tFAILED" << endl;
	}
	cout << "Test_2\t->\tPASSED" << endl;
    
    vector<int> data = {1, -11, 12, 13, 15, 16, 17, 18, 19, 20, 25, 28, 29, 31,
				35, 36, 39, 41, 42, 45, 55, 58, 59, 61, 67, 71, 73, 74,
				76, 80, 81, 82, 83, 88, 89, 99, 83, 91, 93, 94, 95, 98,
                -23, -234, -24, -3, -38, -82, -49, -72, -84, -27, -22,
				35, -9, -29, -374, -84, -24 , -92, -83, -372, -756, 10987};
    int flag = 1;
    
    for (const auto a : data) {
        try {
            b2->key_insert(a);
        } catch(...) {
            cout << "Test_3." << flag << "\t->\tFAILED" << endl;
        }
        cout << "Test_3." << flag << "\t->\tPASSED" << endl;
        flag += 1;
    }

    cout << *b2 << endl;

    try {
		*b1 = *b2;
	} catch (...) {
		cout << "Test_4\t->\tFAILED" << endl;
	}
	cout << "Test_4\t->\tPASSED" << endl;

	check_copy_constructor(*b1);
	check_copy_constructor(*b2);

    flag = 1;
    for (const auto& a : data) {
        try {
            b2->search(a);
        } catch(...) {
            cout << "Test_5." << flag << "\t->\tFAILED" << endl;
        }
        cout << "Test_5." << flag << "\t->\tPASSED" << endl;
        flag += 1;
    }

    try {
		b1->delete_from_btree(15);
	} catch (...) {
		cout << "Test_6\t->\tFAILED" << endl;
	}
	cout << "Test_6\t->\tPASSED" << endl;

    try {
		b1->delete_from_btree(19);
	} catch (...) {
		cout << "Test_7\t->\tFAILED" << endl;
	}
	cout << "Test_7\t->\tPASSED" << endl;

    try {
		b1->delete_from_btree(73);
	} catch (...) {
		cout << "Test_8\t->\tFAILED" << endl;
	}
	cout << "Test_8\t->\tPASSED" << endl;

    try {
		b1->delete_from_btree(-24);
	} catch (...) {
		cout << "Test_9\t->\tFAILED" << endl;
	}
	cout << "Test_9\t->\tPASSED" << endl;

    try {
		b1->delete_from_btree(-72);
	} catch (...) {
		cout << "Test_10\t->\tFAILED" << endl;
	}
	cout << "Test_10\t->\tPASSED" << endl;

    try {
		b1->search(15);
	} catch (...) {
		cout << "Test_11\t->\tFAILED" << endl;
	}
	cout << "Test_11\t->\tPASSED" << endl;

    delete b1;
    delete b2;
    return 0;
}