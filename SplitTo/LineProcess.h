#pragma once
#include"SplitToDoc.h"
#include"MainFrm.h"
#include "afxwin.h"

// CLineProcess �Ի���

class CLineProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CLineProcess)

public:
	CLineProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLineProcess();

// �Ի�������
	enum { IDD = IDD_LINEPROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedLineProcessOpenFile();
public://ͼ����ʾ����
	CRect BoundingBox(CPtrArray& Array);//���ڷ���ƽ���άͼ�ε���С��Χ���ο�
	void SortDraw(CDC* dc, CPtrArray& m_Array);
	void DrawaLabel(CDC* m_pDC, CRect Rect);
	void DrawH2Label(CDC* m_pDC, CRect Rect);
	void DrawArrow(CDC* m_pDC, CPoint p1, CPoint p2, double theta, int length);

private://ͼ����ʾ
	int m_AddDistance;//ͼ��̫�����ˣ����Ӹ�����ʹ��λ���м�
	CPtrArray m_TempArray;//�洢�Ķ��ǿ�ָ��
	vector<string> m_TempData;
	CRect rec;//�洢��ʾ����ķ�Χ
	float ratio;
	CRect PieceSize;//��������Ĺ�����rect
	POINT m_CorCenter;//��ͼ����ʾ������picture�ؼ�������λ��
	CRect m_BoundingBox_2D;
	BOOL m_ShowTips;
	CSplitToDoc* pDoc;
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedShowBigger();
	afx_msg void OnBnClickedShowSmaller();
	afx_msg void OnBnClickedShowTips();
	// �����ĳ���
	float m_PierceLong;
	// �����Ŀ��
	float m_PierceWidth;
	// �������ĸ�
	float m_PierceTopHigh;
	// ��������ĸ߶�
	float m_PierceBottomHigh;
	// ��¼���õ�ë���ĳ���
	float m_WorkBlankLength;
	// ��¼�����Ŀ��
	float m_WorkBlankWidth;
	// ��¼���õ�ë���ĸ߶�
	float m_WorkBlankHigh;
	// ��¼�ּӹ�ˮƽ�и�����ٶ�
	float m_Rough_H_FeedSpeed;
	// ��¼ˮƽ�ּӹ��и��������
	float m_Rough_H_FeedTime;
	// ��¼ˮƽ�ּӹ��ϳɽ�����
	float m_Rough_H_FeedLoad;
	// ��¼�ּӹ���ֱ��ӹ������ٶ�
	float m_Rough_V_FeedSpeed;
	// ��¼�ּӹ���ֱ���и��������
	float m_Rough_V_FeedTime;
	// ��¼�ּӹ���ֱ��ӹ��ϳɽ�����
	float m_Rough_V_FeedLoad;
	// ��¼�ּӹ���ֱ�µ�����
//	float m_Rough_VerticalDistance;
	// ��¼�ּӹ�����
//	float m_Rough_Piles;
	// ��¼�ּӹ�����
	float m_Rough_Left;
	// ��¼���ӹ�ˮƽ���и��ٶ�
	float m_Finish_H_FeedSpeed;
	// ��¼���ӹ�ˮƽ���и��������
	float m_Finish_H_FeedTime;
	// ��¼ˮƽ�澫�ӹ��ϳɽ�����
	float m_Finish_H_FeedLoad;
	// ��¼���ӹ���ֱ���и�����ٶ�
	float m_Finish_V_FeedSpeed;
	// ��¼���ӹ���ֱ��ӹ���������
	float m_Finish_V_FeedTime;
	// ��¼���ӹ���ֱ��ϳɽ�����
	float m_Finish_V_FeedLoad;
	// ��¼���ӹ���ֱ�µ�����
//	float m_Finish_VerticalDistance;
	// ��¼ ���ӹ�����
//	float m_Finish_Piles;
	// ��¼����ʯ�������ĳ���
	float m_Line_Length;
	// ��¼Բ��������Բ�ĺ�����
	float m_Arc_CenterX;
	// ��¼Բ��������Բ��������
	float m_Arc_CenterY;
	// ��¼Բ��������Բ��Z����
	float m_Arc_CenterZ;
	// ��¼Բ���������뾶,��ͼ�ε�����˵�����İ뾶
	float m_Arc_Radius;
	// ��¼Բ����������ʼ��(����ʱ��н�)
	float m_Arc_BeginAngle;
	// ��¼Բ����������ֹ��(����ʱ��н�)
	float m_Arc_EndAngle;
//	CButton m_LineRadio;
	int m_LineRadio;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedArcRadio();
	afx_msg void OnBnClickedLineRadio();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// �����и��
//	int m_LineDirection;
	afx_msg void OnEnChangeEdit17();
};
