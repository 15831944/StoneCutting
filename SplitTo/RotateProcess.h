#pragma once

#include"SplitToDoc.h"
#include"MainFrm.h"
// CRotateProcess �Ի���

class CRotateProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CRotateProcess)

public:
	CRect BoundingBox(CPtrArray& Array);//���ڷ���ƽ���άͼ�ε���С��Χ���ο�
	void  SortDraw(CDC* dc, CPtrArray& m_Array);//����Բ���Բ������
	void DrawaLabel(CDC* m_pDC, CRect Rect);//���Ʋ����ע��
	void DrawCircleLabel(CDC* m_pDC, CRect Rect);//���Ƶ���Բ�α�ע��
	void DrawArrow(CDC* m_pDC, CPoint p1, CPoint p2, double theta, int length);//����ͷ
private:
	CPtrArray m_TempArray;//�洢�Ķ��ǿ�ָ��
	vector<string> m_TempData;
	CRect rec;//{top=0 bottom=219 left=0 right=228}	�洢��ʾ����ĳߴ�
	float ratio;
	CRect PieceSize;//��������Ĺ�����rect
	POINT m_CorCenter;//��ͼ����ʾ������picture�ؼ�������λ��
	CRect m_BoundingBox_2D;
	BOOL m_ShowTips;

public:
	CRotateProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRotateProcess();

// �Ի�������
	enum { IDD = IDD_ROTATEPROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedRotateOpenFile();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedShowBigeer();
	afx_msg void OnBnClickedShowSmaller();
	afx_msg void OnBnClickedTips();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ��¼����ĳ���(��Բ��ֱ��)
	float m_underside_Long;
	// ��¼����Ŀ��(��Բ��ֱ��)
	float m_underside_Width;
	// ��¼������״�ĸ߶�
	float m_Highth;
	// ��¼����͹���ĳ���(����ڵ���͹���Ĳ���)
	float m_raised;
	// ��¼ë���ĳ���
	float m_workBlank_Long;
	// ��¼������ë���Ŀ��
	float m_workBlank_Width;
	// ��¼������ë���ĸ߶�
	float m_workBlank_Heighth;
	// ��¼�������ٶ�
	float m_FeedSpeed;
	// ��¼����������
	float m_FeedTime;
	// ��¼�ϳɽ�����
	float m_FeedLoad;
	// ��¼ÿ������ľ���
	float m_FeedDistance;
	// ��¼�ּӹ���������
	float m_RoughPlies;
	// ��¼�ּӹ�����
	float m_RoughLeft;
	// ��¼��ֱ����Ľ����ٶ�
	float m_FeedSpeed_VX;
	// ��¼��ֱ�����ϵĲ岹����
	float m_FeedTime_VX;
	// ��¼��ֱ����Ĵּӹ��ϳɽ�����
	float m_FeedLoad_VX;
	// ��¼���ӹ�ˮƽ�����ٶ�
	float m_FeedSpeed_Finish;
	// ��¼���ӹ���������
	float m_FeedTime_Finish;
	// ��¼���ӹ�ˮƽ�����ϵĺϳɽ�����
	float m_FeedLoad_Finish;
	// ��¼���ӹ�ˮƽ������ÿ����и���
	float m_FeedDistance_Finish;
	// ��¼���ӹ���ֱ�����ϵĽ����ٶ�
	float m_FeedSpeed_VX_Finish;
	// ��¼���ӹ���ֱ�����ϵĽ�������
	float m_FeedTime_VX_Finish;
	// ��¼���ӹ���ֱ�����ϵĺϳɽ�����
	float m_FeedLoad_VX_Finish;
	virtual BOOL OnInitDialog();
};
