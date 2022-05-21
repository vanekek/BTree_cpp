#include "btree.h"

using namespace std;

void check_copy_constructor(BTree<int> b) 
{
	cout << b;
}

void check_copy_constructor_2(BTree<BTree<int>> b)
{
	cout << b;
}

int main() {

    BTree<int> *b1 = NULL;
    BTree<int> *b2 = NULL;
    vector<int> vec1 = {1, 2, 3, 4};
    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7};

    try {
        b1 = new BTree<int>(vec2);
    } catch (const BTree<int>::btree_error& ex) {
        if (ex == BTree<int>::EINVARG)
            cout << "Test_0\t->\tPASSED" << endl;
        else 
            cout << "Test_0\t->\tFAILED" << endl;
    } catch (...) {
        cout << "Test_0\t->\tFAILED" << endl;
    }

    try {
		b1 = new BTree<int>(vec1);
	} catch (...) {
		cout << "Test_1\t->\tFAILED" << endl;
	}
	cout << "Test_1\t->\tPASSED" << endl;

    try {
		b2 = new BTree<int>();
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

	//Tests for templates//

	BTree< BTree<int> > *b3 = NULL;

	try {
        b3 = new BTree<BTree<int>>();
    } catch (...) {
        cout << "Test_12\t->\tFAILED" << endl;
    }
	cout << "Test_12\t->\tPASSED" << endl;

	try {
        b3->key_insert(*b1);
    } catch (...) {
        cout << "Test_13\t->\tFAILED" << endl;
    }
	cout << "Test_13\t->\tPASSED" << endl;

	try {
        b3->key_insert(*b2);
    } catch (...) {
        cout << "Test_14\t->\tFAILED" << endl;
    }
	cout << "Test_14\t->\tPASSED" << endl;

	check_copy_constructor_2(*b3);

	try {
        b3->search(*b1);
    } catch (...) {
        cout << "Test_15\t->\tFAILED" << endl;
    }
	cout << "Test_15\t->\tPASSED" << endl;

	try {
        b3->search(*b2);
    } catch (...) {
        cout << "Test_16\t->\tFAILED" << endl;
    }
	cout << "Test_16\t->\tPASSED" << endl;

	/*try {
        b3->delete_from_btree(*b1);
    } catch (...) {
        cout << "Test_17\t->\tFAILED" << endl;
    }
	cout << "Test_17\t->\tPASSED" << endl;

	try {
        b3->delete_from_btree(*b2);
    } catch (...) {
        cout << "Test_18\t->\tFAILED" << endl;
    }
	cout << "Test_18\t->\tPASSED" << endl;*/

    delete b1;
	delete b2;
	delete b3;
    return 0;
}