#pragma once
#ifndef STITERATOR_H
#define STITERATOR_H

#include<iterator>
#include"ST.h"

//template<class>struct Node;

template<typename Key, typename Value>struct KeyValNode;

template<typename Key, typename Value>
class STIterator :public std::iterator<std::input_iterator_tag, Key> {
public:
	STIterator(KeyValNode<Key, Value>* p) :curNode(p) {}
	STIterator() {}
	STIterator& operator=(const STIterator &iter) {
		curNode = iter.curNode;
		return *this;
	}

	bool operator != (const STIterator &iter) {
		return curNode != iter.curNode;
	}

	bool operator == (const STIterator &iter) {
		return curNode == iter.curNode;
	}

	STIterator operator ++() {
		curNode = curNode->next;
		return *this;
	}

	STIterator operator ++(int) {
		STIterator tmp = *this;
		curNode = curNode->next;
		return tmp;
	}

	Value& operator * () {
		return curNode->val;
	}
	Value& frist() {
		return curNode->val;
	}
	Key& second() {
		return curNode->key;
	}

private:
	KeyValNode<Key,Value> *curNode;
};


#endif
