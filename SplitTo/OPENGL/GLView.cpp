
// GLView.cpp : CGLView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "gl\GL.h"
#endif

#include "GLView.h"
#include "OpenGLDC.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CGLView

IMPLEMENT_DYNCREATE(CGLView, CView)

BEGIN_MESSAGE_MAP(CGLView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGLView::OnFilePrintPreview)
//	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CGLView ����/����

CGLView::CGLView()
{
	m_pGLDC = NULL;
}

CGLView::~CGLView()
{
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	//λOpenGl���Ӵ��ڷ������
	//cs.style |= WS_MAXIMIZE;
	cs.style|=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CGLView ����
//�Ժ��������⺯��RenderScene()������д����Ҫ����ʾ���ע�͵���������ͼ���е����⺯��OnDraw()����������ͻ����CGLView�е�OnDraw
void CGLView::OnDraw(CDC* /*pDC*/)
{
	

	if(m_pGLDC){
		m_pGLDC->Ready();
		RenderScene(m_pGLDC);
		m_pGLDC->Finish();
	}
}


// CGLView ��ӡ


void CGLView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}



void CGLView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}



// CGLView ���

#ifdef _DEBUG
void CGLView::AssertValid() const
{
	CView::AssertValid();
}

void CGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


#endif //_DEBUG


// CGLView ��Ϣ�������


int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pGLDC=new COpenGLDC(this->GetSafeHwnd());
	m_pGLDC->InitDC();
	return 0;
}




void CGLView::OnDestroy()
{
	CView::OnDestroy();
	if(m_pGLDC)	delete m_pGLDC;
}



void CGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);


	if(m_pGLDC)	
		m_pGLDC->GLResize(cx,cy);
}




BOOL CGLView::OnEraseBkgnd(CDC* pDC)
{
	

   //return CView::OnEraseBkgnd(pDC);

	return TRUE;

}


void CGLView::RenderScene(COpenGLDC* pDC)
{
	pDC->DrawCoord(); 

}

void CGLView::OnViewType(UINT type)
{
	ASSERT(type >= VIEW_FRONT && type <= VIEW_NW_ISOMETRIC);
	m_pGLDC->m_Camera.set_view_type(type);
	Invalidate();
}

BOOL CGLView::GetBox(double& x0,double& y0,double& z0,double& x1,double& y1,double& z1)
{
	return FALSE;
}

void CGLView::ZoomAll()
{
	double x0,y0,z0,x1,y1,z1;
	if(GetBox(x0,y0,z0,x1,y1,z1)){
		m_pGLDC->m_Camera.zoom_all(x0,y0,z0,x1,y1,z1);
		Invalidate();
	}
}

void CGLView::Zoom(double dScale)
{
	m_pGLDC->m_Camera.zoom(dScale);
	Invalidate();
}

void CGLView::MoveView(double dpx,double dpy)
{
	m_pGLDC->m_Camera.move_view(dpx,dpy);
	Invalidate();
}

COpenGLDC* CGLView::GetGLDc()
{
	return this->m_pGLDC;
}