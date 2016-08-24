#pragma once
#include"SplitToDoc.h"
#include"MainFrm.h"
// CArcSurface �Ի���

class CArcSurface : public CDialogEx
{
	DECLARE_DYNAMIC(CArcSurface)

public:
	CArcSurface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CArcSurface();

// �Ի�������
	enum { IDD = IDD_ARCSURFACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedArcOpenfile();
public:
	void SortDraw(CDC* dc, CPtrArray& m_Array);
	CRect BoundingBox(CPtrArray& Array);//���ڷ���ƽ���άͼ�ε���С��Χ���ο�
	void DrawaLabel(CDC* m_pDC, CRect Rect);
	void DrawYLabel(CDC* m_pDC, CRect Rect);
	void DrawArrow(CDC* m_pDC, CPoint p1, CPoint p2, double theta, int length);
private:
	CPtrArray m_TempArray;//�洢�Ķ��ǿ�ָ��
	vector<string> m_TempData;
	CRect rec;//�洢��ʾ����ķ�Χ tagRECT = {top=0 bottom=216 left=0 right=232}
	float ratio;
	CRect PieceSize;//��������Ĺ�����rect
	POINT m_CorCenter;//��ͼ����ʾ������picture�ؼ�������λ��
	CRect m_BoundingBox_2D;
	BOOL m_ShowTips;
	//�洢���������Բ���İ뾶��X�����Բ����뾶�����
	float XRadius, YRadius;
	//
	CSplitToDoc* pDoc;
public:

public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedExtendBtn();
	afx_msg void OnBnClickedShrinkBtn();
	// ��¼����ĳ���
	float m_ArcPieceLong;
	// ��¼����Ŀ��
	float m_ArcPieceWidth;
	// ��¼����ĸ߶�
	float m_ArcPieceHigth;
	// Y�����Բ���뾶
	float m_ArcYSideRadius;
	// ��¼X����Բ���뾶
	float m_ArcXSideRadius;
	afx_msg void OnBnClickedTipsBtn();
	// ��¼���õ�ë���ĳ���
	float m_WorkBlankLong;
	// ��¼���õ�ë���Ŀ��
	float m_WorkBlankWidth;
	// ��¼���õ�ë���ĸ߶�
	float m_WorkBlankHeigth;
	// ��¼Y��Բ���Ĵּӹ������ٶ�
	float m_Rough_YArcFeedSpeed;
	// ��¼Y����ּӹ���������
	float m_Rough_YArcFeedTime;
	// ��¼Y����ּӹ��ϳɽ�����
	float m_Rough_YArcFeedLoad;
	// ��¼X����Բ���ּӹ������ٶ�
	float m_Rough_XArcFeedSpeed;
	// ��¼X����Բ���ּӹ���������
	float m_Rough_XArcFeedTime;
	// ��¼�ּӹ�X����ϳɽ�����
	float m_Rough_XArcFeedLoad;
	// ��¼�ּӹ���ֱ�µ�����
	float m_Rough_VerticalDown;
	// ��¼�ּӹ��ӹ�����
	float m_Rough_NumberOfPiles;
	// ��¼�ּӹ�����
	float m_Rough_Left;
	// ��¼Y����Բ�����ӹ������ٶ�
	float m_Finish_YArcFeedSpeed;
	// ��¼Y���澫�ӹ���������
	float m_Finish_YArcFeedTime;
	// ��¼Y����Բ�����ӹ��ϳɽ�����
	float m_Finish_YArcFeedLoad;
	// ��¼X���澫�ӹ������ٶ�
	float m_Finish_XArcFeedSpeed;
	// ��¼X���澫�ӹ���������
	float m_Finish_XArcFeedTime;
	// ��¼X����Բ�����ӹ��ϳɽ�����
	float m_Finish_XArcFeedLoad;
	// ��¼���ӹ���ֱ�µ�����
	float m_Finish_VerticalDistance;
	// ��¼���ӹ��ӹ�����
	float m_Finish_NumberOfPile;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
