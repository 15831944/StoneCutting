// SawSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplitTo.h"
#include "SawSetDlg.h"
#include "afxdialogex.h"


// CSawSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSawSetDlg, CDialogEx)

CSawSetDlg::CSawSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSawSetDlg::IDD, pParent)
	, m_Diamond(0)
	, m_SawThickness(0)
	, m_SawExtend(0)
{

}

CSawSetDlg::~CSawSetDlg()
{
}

void CSawSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Diamond);
	DDX_Text(pDX, IDC_EDIT2, m_SawThickness);
	DDX_Text(pDX, IDC_EDIT3, m_SawExtend);
}


BEGIN_MESSAGE_MAP(CSawSetDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSawSetDlg ��Ϣ�������


void CSawSetDlg::PostNcDestroy()
{
	delete this;

	CDialogEx::PostNcDestroy();
}


void CSawSetDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()



	CDC* pDC;
	pDC = GetDlgItem(IDC_SAW_PICTURE)->GetDC();

	GetDlgItem(IDC_SAW_PICTURE)->Invalidate();
	GetDlgItem(IDC_SAW_PICTURE)->UpdateWindow();

	CFont font;
	font.CreateFont(15,                                          //   nHeight     
		0,                                                   //   nWidth     
		0,                                                   //   nEscapement   
		0,                                                   //   nOrientation     
		FW_NORMAL,                                   //   nWeight     
		FALSE,                                           //   bItalic     
		FALSE,                                           //   bUnderline     
		0,                                                   //   cStrikeOut     
		ANSI_CHARSET,                             //   nCharSet     
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision     
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision     
		DEFAULT_QUALITY,                       //   nQuality     
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily       
		_T("����"));


	CRect rec;
	GetDlgItem(IDC_SAW_PICTURE)->GetClientRect(rec);//top=0,bottom=165,left=0,right=174


	CPen RedPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* OldPen=pDC->SelectObject(&RedPen);
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//�ջ�ˢ
	CBrush* pOldBrush = pDC->SelectObject(pBrush);

	pDC->Ellipse(20, 40, 100, 120);
	pDC->SetPixel(60, 80,RGB(255,0,0));
	pDC->Rectangle(130, 40, 140, 120);

	CPen GreenPen(PS_SOLID, 1, RGB(0, 255, 0));
	pDC->SelectObject(&GreenPen);
	pDC->MoveTo(20, 80);
	pDC->LineTo(20, 140);
	pDC->MoveTo(99, 80);
	pDC->LineTo(99, 140);

	pDC->MoveTo(130, 120);
	pDC->LineTo(130, 135);
	pDC->MoveTo(139, 120);
	pDC->LineTo(139, 135);

	DrawArrow(pDC, CPoint(20, 140), CPoint(99, 140),45,5);

	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(50, 150, 200));
	pDC->TextOutW(55, 145, _T("D"));

	DrawArrow(pDC, CPoint(130, 135), CPoint(139, 135), 45, 5);
	pDC->TextOutW(134, 140, _T("W"));

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(OldPen);

}

void CSawSetDlg::DrawArrow(CDC* m_pDC, CPoint p1, CPoint p2, double theta, int length)
{
	theta = 3.1415926*theta / 180;//ת��Ϊ����
	double Px, Py, P1x, P1y, P2x, P2y;
	//��P2Ϊԭ��õ�����P2P1��P��
	Px = p1.x - p2.x;
	Py = p1.y - p2.y;
	//����P��תtheta�ǵõ�����P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//�����������ƶ�����
	double x1, x2;
	x1 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x1;
	P1y = P1y*length / x1;
	x2 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x2;
	P2y = P2y*length / x2;
	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x = P1x + p2.x;
	P1y = P1y + p2.y;
	P2x = P2x + p2.x;
	P2y = P2y + p2.y;

	CPen pen, pen1, *oldpen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	pen1.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldpen = m_pDC->SelectObject(&pen);
	m_pDC->MoveTo(p1.x, p1.y);
	m_pDC->LineTo(p2.x, p2.y);
	m_pDC->SelectObject(&pen1);
	m_pDC->MoveTo(p2.x, p2.y);
	m_pDC->LineTo(P1x, P1y);
	m_pDC->MoveTo(p2.x, p2.y);
	m_pDC->LineTo(P2x, P2y);
	m_pDC->SelectObject(oldpen);


	//��P1Ϊԭ��õ�����P1P2��P��
	Px = p2.x - p1.x;
	Py = p2.y - p1.y;
	//����P��תtheta�ǵõ�����P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//�����������ƶ�����
	x1 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x1;
	P1y = P1y*length / x1;
	x2 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x2;
	P2y = P2y*length / x2;
	//ƽ�Ʊ�����ֱ�ߵ��׶�
	P1x = P1x + p1.x;
	P1y = P1y + p1.y;
	P2x = P2x + p1.x;
	P2y = P2y + p1.y;


	oldpen = m_pDC->SelectObject(&pen1);
	m_pDC->MoveTo(p1.x, p1.y);
	m_pDC->LineTo(P1x, P1y);
	m_pDC->MoveTo(p1.x, p1.y);
	m_pDC->LineTo(P2x, P2y);
	m_pDC->SelectObject(oldpen);


}

BOOL CSawSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Diamond = 600.00;
	m_SawThickness = 8.00;
	m_SawExtend = 400.00;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
