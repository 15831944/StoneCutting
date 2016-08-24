
// SplitToDoc.h : CSplitToDoc ��Ľӿ�
//


#pragma once
#include"Arc.h"
#include"OPENGL\CadBase.h"
#include"Circle.h"
#include"Line.h"
#include"fstream"
#include<iostream>
#include<string>
//#include"ToolPath.h"//2016.8.10 TableBoardProcess.h������ToolPath.h
#include"TableBoardProcess.h"

//#include"Orthogonal.h"
//#include"Offset.h"
//#include"LineStone.h"
typedef struct SplineData
{
	const int flag = 4;//��ʾSpline�ı�־
	CVector3D m_NormalVector;//210 220 230����ʸ��
	int Type;//70��������
	int Degree;//71���߽״�
	int NodeCount;//72�ڵ���
	int CtrlPtCount;//73���Ƶ���
	int FitPtCount;//74��ϵ���
	vector<double> NodeValue;//40�ڵ�ֵ
	const double WeightFactor=1;//41Ȩ����ֵ
	double m_FitTolerence;//44��Ϲ���
	double m_CtrlTolerence;//43���Ƶ㹫��
	double m_NodeTolerence;//42�ڵ㹫��
	vector<CPoint3D> CtrlPtValue;//10 20 30���Ƶ�ֵ 
	vector<CPoint3D> FitPtValue;//11 21 31��ϵ�ֵ
	CVector3D m_BeginSlope;//���������12 22 32
	CVector3D m_EndSlope;//�յ������� 13 23 33

} Spline;



class CSplitToDoc : public CDocument
{
protected: // �������л�����
	CSplitToDoc();
	DECLARE_DYNCREATE(CSplitToDoc)

// ����
public:
	CPtrArray m_ptArray;//�洢�Ķ��ǿ�ָ��
	vector<string> data;
	BOOL juge;

	CToolPath tool;

	void MyDraw(COpenGLDC* pDC);//��ͼ��
	void DrawOffset(COpenGLDC* pDC);//��ƫ��
	void DrawOtho(COpenGLDC* pDC);//������


	void ChangeToXOZ();//���洢�ĵ㶼תΪXOZƽ���ϵĵ�
	void MyDrawXOZ(COpenGLDC* pDC);//��XOZͼ��
	void ChangeToYOZ();//���洢�ĵ㶼תΪYOZƽ���ϵĵ�
	void MyDrawYOZ(COpenGLDC* pDC);//��YOZͼ��

	void ClearFlags();

	//����μӹ�
public:
	BOOL m_ShowPolygeon;
	BOOL m_ShowPolygeonCuttingPath;
	BOOL m_ShowPolygeonWorkBlank;

	//�����ӹ�
public:
	BOOL m_ShowOrthgonal;
	BOOL m_ShowOrthgonalCutting;
	BOOL m_ShowOrthgonalWorkBlank;
	//void DrawLineProcess(COpenGLDC* pDC);//��ֱ������
	//void DrawArcLineProcess(COpenGLDC* pDC);//��Բ������
	//CPtrArray m_LineProcess;//�洢λ��ƫ�ƺ������
	//vector<CPtrArray*> m_LineProcessList;//�洢λ��ƫ�ƺ���ɢ��ĵ��γɵ�Բ��������
	//CPtrArray m_LinePocessArcArray;//�洢Բ��������Բ������
	//BOOL InitArcLineProcess();//�������õ�Բ����Բ�İ뾶��ʼ�Ǻ���ֹ��ֵ����ģ��

public://�����ӹ�
	BOOL m_ShowLine;//��ʾ����
	BOOL m_ShowLineRough;//��ʾ�ּӹ��켣
	BOOL m_ShowLineWorkBlank;//��ʾë��
	BOOL m_ShowLineRoughCut;//��ʾ�ü���ּӹ��켣
	BOOL m_ShowLineRoughLeft;//��ʾ�ּӹ�����
	BOOL m_ShowLineFinish;//��ʾ���ӹ��켣
	

public://��ת�ӹ�
	BOOL m_ShowRotate;//��ʾ����ʾ��ͼ
	BOOL m_ShowRotateRough;//��ʾ�ּӹ��켣ʾ��ͼ
	BOOL m_ShowRotateWorkBlank;//��ʾë��
	BOOL m_ShowRotateRoughCut;//��ʾ�ּӹ��켣�ü�ʾ��ͼ
	BOOL m_ShowRotateFinish;//��ʾ���ӹ��켣ʾ��ͼ
	//CPoint3D m_center;
	//void ChangePartToXOZ();//�����ֵ�ͼ�ص�����ת��ΪXOZƽ����
	//void DrawRotate(COpenGLDC* pDC);//����ת��
public://����ӹ�
	BOOL m_ShowSide;
	BOOL m_ShowSidePiece;
	BOOL m_ShowSideRough;
	BOOL m_ShowSideRoughCut;
	BOOL m_ShowSideRoughLeft;//�����ж���ʾ�ּӹ�����
	BOOL m_ShowSideFinish;//�����ж���ʾ����ӹ����ӹ�·��

	BOOL m_IsBeginSimulation;//�ּӹ����濪ʼ�жϱ�־
	BOOL m_IsBeginFinishSimulation;//���ӹ����濪ʼ�жϱ�־
	//void ChangeSideProcess();
	//void DrawSide(COpenGLDC* pDC);
	//int mark;//���ڴ洢���ͼ���м���Ԫ��
	//CPoint3D XMax;//���ڴ洢X���귽����ֵ���ĵ�����꣬һ��Ϊ���
public://˫����ӹ�
	BOOL m_ShowArc;
	BOOL m_ShowArcRough;
	BOOL m_ShowArcWorkBlank;
	BOOL m_ShowArcRoughAfterCut;
	BOOL m_ShowArcRoughLeft;
	BOOL m_ShowArcFinish;
	//void ChangeCoordinate();//ת��Ϊƽ����YOZ��YOZƽ��
	//void DrawSurface(COpenGLDC* pDC);

	//̨���ӹ�
public:
	BOOL m_ShowBoard;
	BOOL m_ShowBoardWorkBlank;
	
	BOOL m_ShowBoardInSawPath;
	BOOL m_ShowBoardInMillPath;

	BOOL m_ShowBoardOutPath;
	BOOL m_ShowBoardOutCutPath;

public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CSplitToDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnShowRoughCut();
	afx_msg void OnShowPiece();
	afx_msg void OnShowRough();
	afx_msg void OnShowSide();
	afx_msg void OnShowFinish();
	afx_msg void OnShowRoughLeft();
//	afx_msg void OnBnClickedBeginSimulation();
	afx_msg void OnBnClickedBeginSimulation();
	afx_msg void OnBnClickedBeginFinishSimulation();
	afx_msg void OnShowRotate();
	afx_msg void OnRoughRotate();
	afx_msg void OnShowRotateWorkBlank();
	afx_msg void OnShowRotateCutRough();
	afx_msg void OnShowRotateFinish();
	afx_msg void OnShowArc();
	afx_msg void OnShowArcRough();
	afx_msg void OnShowArcWorkBlank();
	afx_msg void OnShowArcRoughAfterDelete();
	afx_msg void OnShowArcRoughLeft();
	afx_msg void On32830();
	afx_msg void OnShowLineProcess();
	afx_msg void OnShowLineRough();
	afx_msg void OnShowLineWorkBlank();
//	afx_msg void OnShowLineRoughCut();
	afx_msg void OnShowLineRoughLeft();
	afx_msg void OnShowLineFinish();
	afx_msg void OnShowOrthgonal();
	afx_msg void OnShowOrthgonalCutting();
	afx_msg void OnShowOrthgonalWorkBlank();
	afx_msg void OnShowPolygeon();
	afx_msg void OnShowPolygeonWorkBlank();
	afx_msg void OnShowPolygeonCutting();
	afx_msg void OnShowBoard();
	afx_msg void OnShowBoardWorkBlank();
	afx_msg void OnShowBoardInSawPath();
	afx_msg void OnShowBoardInMillPath();
	afx_msg void OnShowBoardOutOffset();
	afx_msg void OnShowBoardOutCutting();
	afx_msg void OnDelData();
};
