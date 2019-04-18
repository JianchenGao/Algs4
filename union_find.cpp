#include"union_find.h"

using namespace std;

int UF::find(int p)
{
	return id.at(p);
}

void UF::_union(int p, int q)
{
	int pID = find(p);
	int qID = find(q);

	//���p��q�Ѿ�����ͬ�ķ���֮������Ҫ��ȡ�κ��ж�
	if (pID == qID) return;

	//��p�ķ���������Ϊq������
	for (int i = 0; i < id.size(); i++)
	{
		if (id.at(i) == pID)
			id.at(i) = qID;
	}
	_count--;
}