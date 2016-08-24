#pragma once


// CSawSetDlg �Ի���

class CSawSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSawSetDlg)

public:
	CSawSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSawSetDlg();
	void DrawArrow(CDC* m_pDC, CPoint p1, CPoint p2, double theta, int length);

// �Ի�������
	enum { IDD = IDD_SAWSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnPaint();

	// �洢��Ƭ��ֱ��(mm)
	float m_Diamond;
	// �洢��Ƭ�ĺ��
	float m_SawThickness;
	// �洢��Ƭ�и�ʱ�����쳤��
	float m_SawExtend;
	virtual BOOL OnInitDialog();
};
