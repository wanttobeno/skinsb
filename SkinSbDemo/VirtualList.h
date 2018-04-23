#pragma once

#include <vector>

struct ListData
{
	long nOffset;
	char szAddress[10];
	char szThread[20];
	char szCom[60];
	char szReg[16];
	ListData()
	{
		memset(this, 0, sizeof(ListData));
	}
};

// CVirtualList

class CVirtualList : public CListCtrl
{
	DECLARE_DYNAMIC(CVirtualList)

public:
	CVirtualList();
	virtual ~CVirtualList();
	int InsertItemDataCallBack(NMHDR* pNMHDR,std::vector<ListData*>& pVec);
protected:
	DECLARE_MESSAGE_MAP()
};


