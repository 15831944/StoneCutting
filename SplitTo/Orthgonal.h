#pragma once

#include"SplitToDoc.h"
#include"MainFrm.h"
// COrthgonal �Ի���

class COrthgonal : public CDialogEx
{
	DECLARE_DYNAMIC(COrthgonal)

public:
	COrthgonal(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COrthgonal();

// �Ի�������
	enum { IDD = IDD_ORTHGONAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	CSplitToDoc* pDoc;
public:
	// ��¼�����ӹ�����ĳ���
	float m_OrthgonalWorkBlankLength;
	// ��¼�����ӹ�����Ŀ��
	float m_OrthgonalWorkBlankWidth;
	// ��¼�����ӹ�����ĸ߶�
	float m_OrthgonalWorkBlankHeigh;
	// ��¼�ӹ����ε����
//	int m_TrapezoidType;
	// ��¼�ӹ����εĵ׽�
	float m_TrapezoidAngle;
	// ��¼��Ƭ�Ŀ��
	float m_OrthgonalSawWidth;
	// ��¼���ε���״0Ϊ����1Ϊ������
	int m_TrapezoidType;
	// ��ֱ�ӹ�ģʽ��ѡ��0Ϊ���мӹ�1Ϊ���мӹ�2Ϊ�����ӹ�
	int m_OrthgonalProcessStyle;
	// ��¼Y�����εĶ̱߳���
	float m_OrthgonalYShort;
	// ��¼Y�����γ��ߵĳ���
	float m_OrthgonalYLong;
	// ��¼Y�����μ���
	float m_OrthgonalYGap;
	// ��¼Y�����εĽ�����
	float m_OrthgonalYFeedLoad;
	// ��¼X�����ζ̱ߵĳ���
	float m_OrthgonalXShort;
	// ��¼X�����γ��ߵĳ���
	float m_OrthgonalXLong;
	// ��¼X�����μ�ļ��
	float m_OrthgonalXGap;
	// ��¼X�����εĺϳɽ�����
	float m_OrthgonalXFeedLoad;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
