#pragma once
#include"SplitToDoc.h"
#include"MainFrm.h"

// CPolygeon �Ի���

class CPolygeon : public CDialogEx
{
	DECLARE_DYNAMIC(CPolygeon)

public:
	CPolygeon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPolygeon();

// �Ի�������
	enum { IDD = IDD_POLYGEON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	CSplitToDoc* pDoc;
	vector<OffsetPoint> PolygeonLine;//�洢����εı�
	float m_EveryAngelOfSide;//ÿ��������Ӧ��Բ�Ľ�
	CRect rec;//�洢ͼ��ؼ��ĳߴ���Ϣ
	float ratio;//���ñ���

public:
	// ��¼����α���
	int m_PolygeonSideNumber;
	// ��¼��������ĵ�X����
	float m_PolygeonCenterX;
	// ��¼��������ĵ��Y����
	float m_PolygeonCenterY;
	// ��¼��������ĵ��Z����
	float m_PolygeonCenterZ;
	// ��¼��������Բ�İ뾶
	float m_PolygeonCircleRadius;
	// ��¼����ε���ĸ߶�
	float m_PolygeonBottomHigh;
	// ��¼����β�������ļн�
	float m_PolygeonSideAngel;
	// ��¼����μӹ��еĽ����ٶ�
	float m_PolygeonFeedSpeed;
	// ��¼����μӹ��еĽ�������
	float m_PolygeonFeedTime;
	// ��¼����μӹ��еĺϳɽ�����
	float m_PolygeonFeedLoad;
	// ��¼����μӹ������ߵ����쳤��
	float m_PolygeonExtendDisatance;
	// ��¼����μӹ��еĵ�������
//	int m_PolygeonCutDirection;
	// ��¼����μӹ��о�Ƭ�Ŀ��
	float m_PolygeonSawWidth;
	// ��¼����μӹ��о�Ƭ��ֱ��
	float m_PolygeonSawDiamand;
	// ��¼����μӹ���ë���ĳ���
	float m_PolygeonWorkBlankLength;
	// ��¼����μӹ���ë���Ŀ��ֵ
	float m_PolygeonWorkBlankWidth;
	// ��¼����μӹ���ë���ĸ߶�
	float m_PolygeonWorkBlankHigh;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedShowBigger();
	afx_msg void OnBnClickedShowSmaller();
};
