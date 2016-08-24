#pragma once

#include"OPENGL\GLView.h"
#include"OPENGL\OpenGLDC.h"
#include"SplitToDoc.h"
#include"MainFrm.h"
#include"SplitToView.h"
#include"Polygeon.h"
#include"HighResolutionTimer.h"
#include"TableBoardProcess.h"
// CGraphic ��ͼ

class CGraphic : public CGLView
{
	DECLARE_DYNCREATE(CGraphic)


//��ý�嶨ʱ��
public:
	CHighResolutionTimer mm_Timer;
	CHighResolutionTimer mm_TimerFinish;
	static void TimerCallback(DWORD dwUser);
	static void TimerCallbackFinish(DWORD dwUser);
	CSplitToView* pSplitView;
	void SetRoughCordValue(CSplitToDoc* pDoc,int index);//���ôּӹ��������ʾ
	void SetFinishCordValue(CSplitToDoc* pDoc, int index);//���þ��ӹ��������ʾ
public:
	LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
protected:
	short account;

protected:
	CGraphic();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CGraphic();

public:
	CSplitToDoc* GetDocument() const;
public:
	
	void initRotate();
	CPoint3D      m_MidButtionPos;
	CPoint     m_LeftDownPos;
	float m_xRotate;
	float m_yRotate;
	bool m_LeftButtonDown;
	virtual void RenderScene(COpenGLDC* pDC);
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnFrontView();
	afx_msg void OnRightView();
	afx_msg void OnTopView();
//	afx_msg void OnUpdateFrontView(CCmdUI *pCmdUI);
	afx_msg void OnBackView();
	afx_msg void OnLeftView();
	afx_msg void OnBottomView();
//	afx_msg void OnBnClickedPolygeon();
	virtual void OnInitialUpdate();
//	afx_msg void OnBnClickedBeginSimulation();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


