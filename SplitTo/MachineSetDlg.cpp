// MachineSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplitTo.h"
#include "MachineSetDlg.h"
#include "afxdialogex.h"


// CMachineSetDlg �Ի���

IMPLEMENT_DYNAMIC(CMachineSetDlg, CDialogEx)

CMachineSetDlg::CMachineSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMachineSetDlg::IDD, pParent)
{

}

CMachineSetDlg::~CMachineSetDlg()
{

}

void CMachineSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMachineSetDlg, CDialogEx)
END_MESSAGE_MAP()


// CMachineSetDlg ��Ϣ�������


void CMachineSetDlg::PostNcDestroy()
{
	delete this;

	CDialogEx::PostNcDestroy();
}
