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

	//如果p和q已经在相同的分量之中则不需要采取任何行动
	if (pID == qID) return;

	//将p的分量重命名为q的名称
	for (int i = 0; i < id.size(); i++)
	{
		if (id.at(i) == pID)
			id.at(i) = qID;
	}
	_count--;
}