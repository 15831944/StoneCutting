#pragma once

#include"SplitToDoc.h"
#include"MainFrm.h"

//�����࣬�ṩһЩ���߷����������趨���Ǿ�̬�ķ������ʿ��Բ���ʵ��������


class CUtils
{
public:
	CUtils();
	~CUtils();
private:
	//CSplitToDoc* pMyDoc = NULL;
	
public:
	//ָ������ĶԻ���ľ�������ô��ļ��Ի���ı��⣬�Լ���ʾ��·�����ı��ռ��ID
	static CPtrArray* OpenFile(HWND hwnd,CString DialogName,int nShowText);

public:
	//�������
	static void ClearAllData();
	

	
};

