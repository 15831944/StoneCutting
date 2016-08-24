
// SplitToView.cpp : CSplitToView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SplitTo.h"
#endif

#include "SplitToDoc.h"
#include "SplitToView.h"
#include"MainFrm.h"
#include"Line.h"
#include"Graphic.h"
#include"GcodeGeneration.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSplitToView

IMPLEMENT_DYNCREATE(CSplitToView, CFormView)

BEGIN_MESSAGE_MAP(CSplitToView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CSplitToView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_LINEPROCESS, &CSplitToView::OnBnClickedLineprocess)
	ON_BN_CLICKED(IDC_ORTHGONAL, &CSplitToView::OnBnClickedOrthgonal)
	ON_BN_CLICKED(IDC_ROTATE_SURFACE, &CSplitToView::OnBnClickedRotateSurface)
	ON_BN_CLICKED(IDC_SIDE_SURFACE, &CSplitToView::OnBnClickedSideSurface)
	ON_BN_CLICKED(IDC_ARC_SURFACE, &CSplitToView::OnBnClickedArcSurface)
	ON_WM_ERASEBKGND()
	/*ON_COMMAND(ID_SHOW_ROUGH, &CSplitToView::OnShowRough)*/
	ON_BN_CLICKED(IDC_MACHINE_SET, &CSplitToView::OnBnClickedMachineSet)
	ON_BN_CLICKED(IDC_SAW_SET, &CSplitToView::OnBnClickedSawSet)
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON13, &CSplitToView::OnBnClickedCodeGeneration)
	ON_BN_CLICKED(IDC_TABLE_BOARD, &CSplitToView::OnBnClickedTableBoard)
END_MESSAGE_MAP()

// CSplitToView ����/����

CSplitToView::CSplitToView()
	: CFormView(CSplitToView::IDD)
{
	JUGE = FALSE;
}

CSplitToView::~CSplitToView()
{
}

void CSplitToView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_HorizonScroll);
}

BOOL CSplitToView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//cs.style |= WS_MAXIMIZE;
	return CFormView::PreCreateWindow(cs);
}

void CSplitToView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	SetDlgItemInt(IDC_X_CORD, 0);
	SetDlgItemInt(IDC_Y_CORD, 0);
	SetDlgItemInt(IDC_Z_CORD, 0);
	SetDlgItemInt(IDC_A_AXIS, 0);
	SetDlgItemInt(IDC_C_AXIS, 0);

	m_HorizonScroll.SetScrollRange(1, 100);
	m_HorizonScroll.SetScrollPos(50);
	SetDlgItemInt(IDC_HSCROLL_EDIT, 50);


	//GetDlgItem(IDC_SCROLLBAR2)->EnableWindow(FALSE);//ʹ�ÿؼ�������

}

void CSplitToView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSplitToView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSplitToView ���

#ifdef _DEBUG
void CSplitToView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSplitToView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSplitToDoc* CSplitToView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitToDoc)));
	return (CSplitToDoc*)m_pDocument;
}
#endif //_DEBUG


// CSplitToView ��Ϣ�������


void CSplitToView::OnBnClickedButton1()
{
	CPolygeon* pPolygeon=new CPolygeon;
	pPolygeon->Create(IDD_POLYGEON, this);
	pPolygeon->ShowWindow(SW_SHOW);
	
}


void CSplitToView::OnBnClickedLineprocess()
{
	CLineProcess* pLineProcess = new CLineProcess;
	pLineProcess->Create(IDD_LINEPROCESS,this);
	pLineProcess->ShowWindow(SW_SHOW);
}


void CSplitToView::OnBnClickedOrthgonal()
{
	COrthgonal* pOrthgonal = new COrthgonal;
	pOrthgonal->Create(IDD_ORTHGONAL, this);
	pOrthgonal->ShowWindow(SW_SHOW);
}


void CSplitToView::OnBnClickedRotateSurface()
{
	CRotateProcess* rote = new CRotateProcess;
	rote->Create(IDD_ROTATEPROCESS);
	rote->ShowWindow(SW_SHOW);
}


void CSplitToView::OnBnClickedSideSurface()
{
	CSideProcess* pSide = new CSideProcess;
	pSide->Create(IDD_SIDEPROCESS);
	pSide->ShowWindow(SW_SHOW);
}


void CSplitToView::OnBnClickedArcSurface()
{
	CArcSurface* pArc = new CArcSurface;
	pArc->Create(IDD_ARCSURFACE);
	pArc->ShowWindow(SW_SHOW);
	
}


BOOL CSplitToView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CFormView::OnEraseBkgnd(pDC);

}





void CSplitToView::OnBnClickedMachineSet()
{
	CMachineSetDlg* pMachine = new CMachineSetDlg;
	pMachine->Create(IDD_MACHINESET);
	pMachine->ShowWindow(SW_SHOW);
}


void CSplitToView::OnBnClickedSawSet()
{
	CSawSetDlg* pSaw = new CSawSetDlg;
	pSaw->Create(IDD_SAWSET);
	pSaw->ShowWindow(SW_SHOW);
}


void CSplitToView::OnMouseMove(UINT nFlags, CPoint point)
{
	

	CFormView::OnMouseMove(nFlags, point);
}


void CSplitToView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSplitToDoc* pDoc = GetDocument();
	CView* pView;
	POSITION POS = pDoc->GetFirstViewPosition();
	while (POS != NULL)
	{
		pView = pDoc->GetNextView(POS);
		if (!pView->IsKindOf(RUNTIME_CLASS(CGraphic)));
		break;
	}
	CGraphic* pGraphicView = (CGraphic*)pDoc->GetNextView(POS);


	int pos = m_HorizonScroll.GetScrollPos();    // ��ȡˮƽ��������ǰλ��   

	switch (nSBCode)
	{
		// ����������һ�У���pos��1   
	case SB_LINEUP:
		pos -= 1;
		break;
		// ������ҹ���һ�У���pos��1   
	case SB_LINEDOWN:
		pos += 1;
		break;
		// ����������һҳ����pos��10   
	case SB_PAGEUP:
		pos -= 10;
		break;
		// ������ҹ���һҳ����pos��10   
	case SB_PAGEDOWN:
		pos += 10;
		break;
		// �������������ˣ���posΪ1   
	case SB_TOP:
		pos = 1;
		break;
		// ������������Ҷˣ���posΪ100   
	case SB_BOTTOM:
		pos = 100;
		break;
		// ����϶������������ָ��λ�ã���pos��ֵΪnPos��ֵ   
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
		// �����m_horiScrollbar.SetScrollPos(pos);ִ��ʱ��ڶ��ν���˺���������ȷ��������λ�ã����һ�ֱ�ӵ�default��֧�������ڴ˴����ñ༭������ʾ��ֵ   
	default:
		SetDlgItemInt(IDC_HSCROLL_EDIT,pos);
		return;
	}

	// ���ù�����λ��   
	m_HorizonScroll.SetScrollPos(pos);

	//�����ٶȵı仯��ͨ�����¶��嶨ʱ������
	if (pDoc->m_IsBeginSimulation)
	{
		pGraphicView->mm_Timer.CreateTimer((DWORD)pGraphicView, 20 * 50 / pos, pGraphicView->TimerCallback);
		
	}
	
	if (pDoc->m_IsBeginFinishSimulation)
	{	
		pGraphicView->mm_TimerFinish.CreateTimer((DWORD)pGraphicView, 10 * 50 / pos, pGraphicView->TimerCallbackFinish);
	}
	
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CSplitToView::OnTimer(UINT_PTR nIDEvent)//�����϶�ý�嶨ʱ�����ٶ�
{
	

	CFormView::OnTimer(nIDEvent);
}


void CSplitToView::OnBnClickedCodeGeneration()
{
	CSplitToDoc* pDoc = GetDocument();
	CGcodeGeneration Gcode(&pDoc->tool);
	Gcode.Init();
	Gcode.OutPutNcCode();
}


void CSplitToView::OnBnClickedTableBoard()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CTableBoardDlg* pTable = new CTableBoardDlg();
	CTableBoardDlg* pTable = CTableBoardDlg::GetTableBoardInstance();

	//�ж϶Ի���ľ���Ƿ�Ϊ�գ����򴴽��Ի���
	//�ǿ��򲻴����Ի�����֤�˶Ի���ֻ��һ����ʵ�ֵ�һ��
	
	if (!pTable->m_hWnd)
	{
		pTable->Create(IDD_TABLE_BOARD);
		pTable->ShowWindow(SW_SHOW);
	}
	else
	{
		pTable->ShowWindow(SW_SHOW);
	}
}
