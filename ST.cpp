#include"ST.h"

using namespace std;

template<typename Key,typename Value>
ST<Key, Value>::ST()
{
	init();
}

template<typename Key, typename Value>
void ST<Key, Value>::put(Key key,Value val)
{	//�Լ�key��ֵ���и���
	KeyValNode<Key, Value> *curNode;
	for ( curNode = head; curNode != nullptr; curNode = curNode->next)
	{
		if (curNode->key == key)
		{
			curNode->val = val;
			return;
		}
	}
	//����key������ʱ��������ͷ���½�һ���ڵ�
	head = new KeyValNode<Key, Value>(key,val,head);
	N++;
}

template<typename Key, typename Value>
Value ST<Key, Value>::get(Key key)
{	//��ȡ��key��Ӧ��ֵ
	for (KeyValNode<Key, Value> *curNode = head; curNode != NULL; curNode = curNode->next)
	{
		if (curNode->key == key)
		{
			return curNode->val;
		}
	}
	return nullptr;
}

template<typename Key, typename Value>
void ST<Key, Value>::stDelete(Key key)
{
	KeyValNode<Key, Value> *preNode, *curNode;
	for (preNode = head, curNode = head; curNode != nullptr; curNode = curNode->next)
	{
		if (curNode->key == key)
		{
			if (curNode == head)
			{	//�����Ҫɾ������ͷ���
				head = curNode->next;
				delete curNode;
				N--;
				return;
			}
			else {
				preNode->next = curNode->next;
				delete curNode;
				N--;
				return;
			}
		}
	}
}

template<typename Key, typename Value>
bool ST<Key, Value>::contains(Key key)
{
	return get(key) != nullptr;
}

template<typename Key, typename Value>
bool ST<Key, Value>::isEmpty()
{
	return size() == 0;
}

template<typename Key, typename Value>
int ST<Key, Value>::size()
{
	return N;
}

/**********************
template<typename Key, typename Value>
ST<Key, Value>::iterator  ST<Key, Value>::keys()
{

}

template<typename Key, typename Value>
ST<Key, Value>::iterator  ST<Key, Value>::begin()
{
	return iterator(head);
}

template<typename Key, typename Value>
ST<Key, Value>::iterator  ST<Key, Value>::end()
{
	return iterator(tail);
}

*******************************/


