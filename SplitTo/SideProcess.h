#pragma once
#include"SplitToDoc.h"
#include"MainFrm.h"
// CSideProcess �Ի���

/*
ͨ����ȡ����ȡ���ļ�����Ϣ���б���X\Y��������Сֵ�����Դ���ȡ���ݾ��ε����ĵ�����꣬
���Դ����ĵ���������ó�picture�ؼ������ĵ�������ٸ�����Ӧ�ı����任��ȡ�����ı仯
�Ӷ�ʵ����pictureͼ�οؼ�����ʾҪ�ӹ�ͼֽ��ʾ��ͼ��ʹ������Ľ����Ը�ǿ
*/
/*
�ſؼ��м䣬���������ø���ť��������ʾ��ͼ�ξ��е��ڣ�ʹ���ڶԻ����ڣ���ratio�������в�����
��Ҫ����ʾͼ�εı���д�ϳ���ȵı�ʶ�����ڲ���ӹ������ڸ߶ȷ����ϵ�ͼ��Ҳ����ʾ���˶�ά
ͼ���У���Ҫ�Ա���߶ȷ�������ݵ���д洢����������Ӧ�İ�Χ���䣬��������ʾ��ҲҪ����߶�
�����ϵ�h��
*/

class CSideProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CSideProcess)

public:
	CPtrArray m_TempArray;//�洢�Ķ��ǿ�ָ��
	vector<string> m_TempData;
	CRect BoundingBox(CPtrArray& Array);//���ڷ���ƽ���άͼ�ε���С��Χ���ο�
	void  SortDraw(CDC* dc,CPtrArray& m_Array);//����X Y��Z�����ϵ�����
	void DrawaLabel(CDC* m_pDC, CRect Rect);//���Ʊ�ע�ߣ������
	void DrawaLabelHeigth(CDC* m_pDC, CRect Rect);//ֻ���Ƹ߶�
	void DrawArrow(CDC* m_pDC, CPoint p1, CPoint p2, double theta, int length);//����ͷ
private:
	BOOL m_IsShow;
	CRect rec;//picture�ߴ�tagRECT = {top=0 bottom=208 left=0 right=253},������ʾ����Ŵ�20������5060����4160
	CRect PieceSize;//��������Ĺ�����rect
	CRect PieceSizeXY;
	CRect PieceSizeXZ;
	POINT m_CorCenter;//��ͼ����ʾ������picture�ؼ�������λ��
	float ratio;
	CRect m_BoundingBox_2D;
	
public:
	CSideProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSideProcess();

// �Ի�������
	enum { IDD = IDD_SIDEPROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedSideOpenFile();
	afx_msg void OnPaint();
	// �����ĳ���	// �����ĳ���
	double m_PieceLong;
	// �����Ŀ��
	double m_PieceWidth;
	// �����ӹ�����ͼ�εĸ߶�
	double m_PieceHeigth;
	afx_msg void OnBnClickedAmphsize();
	afx_msg void OnBnClickedShrink();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedShowTip();
	// ������ʾ����������ĳߴ�
	double m_PieceExtend;
	// �����ٶ�F
	float m_Feed;
	// ��������T
	float m_Time;
	// ë���ߴ糤������
	float m_LongSet;
	// ë���������
	float m_WidthSet;
	// ë���߶�����
	float m_HeigthSet;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ������
	float m_Load;
	float m_Feed_VX;
	// ��ֱ��Ĳ岹����
	float m_Time_VX;
	// ������
	float m_Load_VX;
	virtual BOOL OnInitDialog();
	// ���ڱ�ʾ�������
	float m_DeapthOfCut;
	// �洢�ּӹ�����
	float m_RoughLeft;
	// ���ӹ������ٶ�
	float m_Speed_Finish;
	// ���ӹ��岹����
	float m_Time_Finish;
	// ���ӹ���ֱ������ٶ�
	float m_Speed_Finish_VX;
	// ���ӹ��岹����
	float m_Time_Finish_VX;
	// ���ӹ��ϳɽ�����
	float m_Load_Finish;
	// ��ֱ��ϳɽ�����
	float m_Load_Finish_VX;
	// ���ӹ�ˮƽ��ÿ�εĽ������
	float m_DepthOfCut_Finish;
	// ��ע�ּӹ�����
	int m_Rough_Plies;
};
