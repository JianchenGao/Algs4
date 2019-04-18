#pragma once
#pragma once
#ifndef STACKITERATOR_H
#define STACKITERATOR_H

#include<iterator>
#include"Stack.h"

template<class>struct Node;


template<class T>
class StackIterator :public std::iterator<std::input_iterator_tag, T> {
public:
	StackIterator(Node<T>* p) :curNode(p) {}
	StackIterator() {}
	StackIterator& operator=(const StackIterator &iter) {
		curNode = iter.curNode;
	}

	bool operator != (const StackIterator &iter) {
		return curNode != iter.curNode;
	}

	bool operator == (const StackIterator &iter) {
		return curNode == iter.curNode;
	}

	StackIterator operator ++() {
		curNode = curNode->next;
		return *this;
	}

	StackIterator operator ++(int) {
		StackIterator tmp = *this;
		curNode = curNode->next;
		return tmp;
	}

	T& operator * () {
		return curNode->item;
	}

private:
	Node<T> *curNode;
};

#endif
