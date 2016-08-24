
// SplitToView.h : CSplitToView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include"OPENGL\OpenGLDC.h"
#include"Polygeon.h"
#include"LineProcess.h"
#include"Orthgonal.h"
#include"RotateProcess.h"
#include"SideProcess.h"
#include"ArcSurface.h"
#include"SawSetDlg.h"
#include"TableBoardDlg.h"
#include"MachineSetDlg.h"
#include "afxwin.h"

class CSplitToView : public CFormView
{


protected: // �������л�����
	CSplitToView();
	DECLARE_DYNCREATE(CSplitToView)

public:
	enum{ IDD = IDD_SPLITTO_FORM };


// ����
public:
	CSplitToDoc* GetDocument() const;

	
// ����
public:
	BOOL JUGE;
	
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CSplitToView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClickedButton1();
//	afx_msg void OnBnClickedPolygeon();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedLineprocess();
	afx_msg void OnBnClickedOrthgonal();
	afx_msg void OnBnClickedRotateSurface();
	afx_msg void OnBnClickedSideSurface();
	afx_msg void OnBnClickedArcSurface();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnShowRough();
	afx_msg void OnBnClickedMachineSet();
	afx_msg void OnBnClickedSawSet();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// ˮƽ������
	CScrollBar m_HorizonScroll;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCodeGeneration();
	afx_msg void OnBnClickedTableBoard();
};

#ifndef _DEBUG  // SplitToView.cpp �еĵ��԰汾
inline CSplitToDoc* CSplitToView::GetDocument() const
   { return reinterpret_cast<CSplitToDoc*>(m_pDocument); }
#endif

