#pragma once


// CMachineSetDlg �Ի���

class CMachineSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMachineSetDlg)

public:
	CMachineSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMachineSetDlg();

// �Ի�������
	enum { IDD = IDD_MACHINESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
