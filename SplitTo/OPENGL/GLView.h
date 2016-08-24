
// GLView.h : CGLView ��Ľӿ�
//

#pragma once
#include"gl\GL.h"
#include"gl\GLU.h"
#include"gl\GLAUX.H"
#include"gl\glut.h"
#include"Camera.h"
#include "CadBase.h"
#define BUFFER_LENGTH 64

class COpenGLDC;
class CGLView : public CView
{
protected: // �������л�����
	CGLView();
	DECLARE_DYNCREATE(CGLView)

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	virtual void RenderScene(COpenGLDC* pDC);//����OPENGL����ͼ��
	COpenGLDC* GetGLDc();
private:

	//device context
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	COpenGLDC*	m_pGLDC;

	virtual BOOL GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1);

	void	Zoom(double dScale);
	void	ZoomAll();
	void	OnViewType(UINT type);
	void	MoveView(double dpx,double dpy);
};

#ifndef _DEBUG  // GLView.cpp �еĵ��԰汾
//inline CGLDoc* CGLView::GetDocument() const
//   { return reinterpret_cast<CGLDoc*>(m_pDocument); }
#endif

