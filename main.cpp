#include<iostream>

#include"gtest/gtest.h"
#include"Counter.h"
#include"BinarySearch.h"
#include"StaticSETofInts.h"
#include"Bag.h"
#include"Queue.h"
#include"Stack.h"
#include"CreatRand.h"
#include"ThreeSum.h"
#include"union_find.h"
#include"Selection.h"
#include"Insertion.h"
#include"Shell.h"
#include"Merge.h"
#include"MergeBU.h"
#include"Quick.h"
#include"Quick3way.h"
#include"Quick_Ex.h"
#include"Date.h"
#include"Transaction.h"
#include"MaxPQ.h"
#include"PQsort.h"
#include"ST.h"
#include"BinarySearchST.h"
#include"BST.h"
#include"RedBlackBST.h"
#include"SeparateChainingHashST.h"
#include"LinearProbingHashST.h"

using namespace std;

using ::testing::InitGoogleTest;

int main(int argc, char **argv) {
	cout << "hello algs4!" << endl;
	InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}
