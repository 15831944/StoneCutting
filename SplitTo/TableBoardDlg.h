#pragma once
//***2016.08.20***#include"TableBoardProcess.h"
#include"SplitToDoc.h"
#include"MainFrm.h"
// CTableBoardDlg �Ի���



class CTableBoardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTableBoardDlg)
//������
	public:
		static CTableBoardDlg* GetTableBoardInstance();
	private:
		static CTableBoardDlg* m_TableBoard;
		
		//˽����Ƕ�࣬��Ψһ�ĺô�����ɽ��CTableBoardDlgʵ��
		class CGarbo
		{
		public:
			~CGarbo()
			{
				if (CTableBoardDlg::m_TableBoard)
					delete CTableBoardDlg::m_TableBoard;
			}
		};
		//�����ڽ�����ʱ��ϵͳ���Զ��������е�ȫ�ֱ�����
		//��ʵ�ϣ�ϵͳҲ���������е���ľ�̬��Ա������������Щ��̬��ԱҲ��ȫ�ֱ���һ����
		//����һ����̬���������������ʱ���Զ�����������������
		//����д��ֱ�ӷ���������������Ҫ�ã�������ִ���
		static CGarbo Garbo;

private:
	CTableBoardDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTableBoardDlg();

// �Ի�������
	enum { IDD = IDD_TABLE_BOARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	//�洢ͼƬ�ռ��λ����Ϣ
	CRect rec;//tagRECT = {top=0 bottom=240 left=0 right=259}
	//���ڿؼ��л�ͼ
	void MyDraw(CDC* pDC);

	//���ڻ�ȡ����ĳߴ��
	CRect BoundingBox(CPtrArray* Array);
	CRect m_BoundingBox_2D;
	float ratio;
	POINT m_center;
	//�������
	BOOL m_ShowTips;
	void SortDraw(CDC* dc, CPtrArray* m_Array);
	void DrawaLabel(CDC* m_pDC, CRect Rect);
	void DrawArrow(CDC* m_pDC, CPoint p1, CPoint p2, double theta, int length);

private:
	CSplitToDoc* pDoc;

	//�洢����
	CPtrArray* m_TempArray;
	CPtrArray* m_BackupArray;//����
	CPtrArray m_Array;
public:
	afx_msg void OnBnClickedTbOpenfile();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedExtend();
	afx_msg void OnBnClickedShrink();
	afx_msg void OnBnClickedTips();
	int m_BoardPieceLength;
	int m_BoardPieceWidth;
	// ̨���߶�����
	int m_BoardPieceHighth;
	// ̨������ë��
	float m_BoardOutLeft;
	// ̨����ڲ�ë��
	float m_BoardInLeft;
	float m_FeedSpeed_Horizon;
	float m_FeedTime_Horizon;
	float m_FeedLoad_Horizon;
	// ˮƽ��������
	float m_FeedDis_Horizon;
	float m_FeedSpeed_Vertical;
	float m_FeedTime_Vertical;
	float m_FeedLoad_Vertical;
	float m_ToolDiamand;
	// ϳ���ٶ�vc
	float m_MillCutSpeed;
	// ϳ��ת��n
	float m_MillRotation;
	// ÿ�ݽ�����fz
	float m_MillLoadPerTooth;
	// ÿ���ӽ�����vf
	float m_FeedLoadPerMin;
	// ˮƽ�Ե���
	float m_MillCutLoad_Horizon;
	// �������
	float m_MillCutDepth;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
