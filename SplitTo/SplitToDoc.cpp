
// SplitToDoc.cpp : CSplitToDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SplitTo.h"
#endif

#include "SplitToDoc.h"
#include"Graphic.h"
#include <propkey.h>
#include"Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSplitToDoc

IMPLEMENT_DYNCREATE(CSplitToDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplitToDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CSplitToDoc::OnFileOpen)
	ON_COMMAND(ID_SHOW_ROUGH_CUT, &CSplitToDoc::OnShowRoughCut)
	ON_COMMAND(ID_SHOW_PIECE, &CSplitToDoc::OnShowPiece)
	ON_COMMAND(ID_SHOW_ROUGH, &CSplitToDoc::OnShowRough)
	ON_COMMAND(ID_SHOW_SIDE, &CSplitToDoc::OnShowSide)
	ON_COMMAND(ID_32808, &CSplitToDoc::OnShowFinish)
	ON_COMMAND(ID_SHOW_ROUGH_LEFT, &CSplitToDoc::OnShowRoughLeft)
	ON_BN_CLICKED(IDC_BUTTON8, &CSplitToDoc::OnBnClickedBeginSimulation)
	ON_BN_CLICKED(IDC_BUTTON14, &CSplitToDoc::OnBnClickedBeginFinishSimulation)
	ON_COMMAND(ID_32820, &CSplitToDoc::OnShowRotate)
	ON_COMMAND(ID_32821, &CSplitToDoc::OnRoughRotate)
	ON_COMMAND(ID_32823, &CSplitToDoc::OnShowRotateWorkBlank)
	ON_COMMAND(ID_32822, &CSplitToDoc::OnShowRotateCutRough)
	ON_COMMAND(ID_32824, &CSplitToDoc::OnShowRotateFinish)
	ON_COMMAND(ID_32825, &CSplitToDoc::OnShowArc)
	ON_COMMAND(ID_32826, &CSplitToDoc::OnShowArcRough)
	ON_COMMAND(ID_32827, &CSplitToDoc::OnShowArcWorkBlank)
	ON_COMMAND(ID_32828, &CSplitToDoc::OnShowArcRoughAfterDelete)
	ON_COMMAND(ID_32829, &CSplitToDoc::OnShowArcRoughLeft)
	ON_COMMAND(ID_32830, &CSplitToDoc::On32830)
	ON_COMMAND(ID_32831, &CSplitToDoc::OnShowLineProcess)
	ON_COMMAND(ID_32832, &CSplitToDoc::OnShowLineRough)
	ON_COMMAND(ID_32833, &CSplitToDoc::OnShowLineWorkBlank)
	//ON_COMMAND(ID_32834, &CSplitToDoc::OnShowLineRoughCut)
	ON_COMMAND(ID_32835, &CSplitToDoc::OnShowLineRoughLeft)
	ON_COMMAND(ID_32836, &CSplitToDoc::OnShowLineFinish)
	ON_COMMAND(ID_32839, &CSplitToDoc::OnShowOrthgonal)
	ON_COMMAND(ID_32837, &CSplitToDoc::OnShowOrthgonalCutting)
	ON_COMMAND(ID_32838, &CSplitToDoc::OnShowOrthgonalWorkBlank)
	ON_COMMAND(ID_32840, &CSplitToDoc::OnShowPolygeon)
	ON_COMMAND(ID_32843, &CSplitToDoc::OnShowPolygeonWorkBlank)
	ON_COMMAND(ID_32842, &CSplitToDoc::OnShowPolygeonCutting)
	ON_COMMAND(ID_32845, &CSplitToDoc::OnShowBoard)
	ON_COMMAND(ID_32846, &CSplitToDoc::OnShowBoardWorkBlank)
	ON_COMMAND(ID_32849, &CSplitToDoc::OnShowBoardInSawPath)
	ON_COMMAND(ID_32850, &CSplitToDoc::OnShowBoardInMillPath)
	ON_COMMAND(ID_32851, &CSplitToDoc::OnShowBoardOutOffset)
	ON_COMMAND(ID_32852, &CSplitToDoc::OnShowBoardOutCutting)
	ON_COMMAND(ID_DEL_DATA, &CSplitToDoc::OnDelData)
END_MESSAGE_MAP()


// CSplitToDoc ����/����

CSplitToDoc::CSplitToDoc()
{
	juge = FALSE;
	// mark = 0;
	//����ӹ�
	m_ShowSide = TRUE;
	m_ShowSidePiece = FALSE;
	m_ShowSideRough = FALSE;
	m_ShowSideRoughCut = FALSE;
	m_ShowSideRoughLeft = FALSE;
	m_ShowSideFinish = FALSE;
	m_IsBeginSimulation = FALSE;
	m_IsBeginFinishSimulation = FALSE;

	//��ת�ӹ�
	m_ShowRotate = TRUE;
	m_ShowRotateRough = FALSE;
	m_ShowRotateWorkBlank = FALSE;
	m_ShowRotateRoughCut = FALSE;
	m_ShowRotateFinish = FALSE;

	//˫����ӹ�
	m_ShowArc = TRUE;
	m_ShowArcRough=FALSE;
	m_ShowArcWorkBlank = FALSE;
	m_ShowArcRoughAfterCut = FALSE;
	m_ShowArcRoughLeft = FALSE;
	m_ShowArcFinish = FALSE;

	//�����ӹ�
	m_ShowLine =TRUE;
	m_ShowLineRough = FALSE;
	m_ShowLineWorkBlank = FALSE;
	m_ShowLineRoughCut = FALSE;
	m_ShowLineRoughLeft = FALSE;
	m_ShowLineFinish = FALSE;

	//�����ӹ�
	m_ShowOrthgonal = TRUE;
	m_ShowOrthgonalCutting = FALSE;
	m_ShowOrthgonalWorkBlank = FALSE;

	//����μӹ�
	m_ShowPolygeon = TRUE;
	m_ShowPolygeonCuttingPath = FALSE;
	m_ShowPolygeonWorkBlank = FALSE;

	//̨���ӹ�
	m_ShowBoard = TRUE;
	m_ShowBoardWorkBlank = FALSE;
	m_ShowBoardInMillPath = FALSE;
	m_ShowBoardInSawPath = FALSE;
	m_ShowBoardOutPath = FALSE;
	m_ShowBoardOutCutPath = FALSE;

}

CSplitToDoc::~CSplitToDoc()
{
}

BOOL CSplitToDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CSplitToDoc ���л�

void CSplitToDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CSplitToDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CSplitToDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CSplitToDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSplitToDoc ���

#ifdef _DEBUG
void CSplitToDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSplitToDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSplitToDoc ����


void CSplitToDoc::OnFileOpen()
{
	CFileDialog openfile(TRUE, NULL, _T("*.dxf"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		NULL, NULL);
	openfile.m_ofn.lpstrTitle = _T("л��DXF�򿪴���");

	openfile.m_ofn.lpstrFilter = _T("�ı��ļ�(.txt)\0*.txt\0dxf�ļ�(.dxf)\0*.dxf\0NC�ļ�(.nc)\0�����ļ�(*.*)\0*.*\0\0");


	if (IDOK == openfile.DoModal())//����ȷ������ť��ʱ����Զ����ݽ��д洢������Ҫ����������Ϊpublic
	{
		vector<string>().swap(data);
		vector<OffsetPoint>().swap(tool.LineOffsetPoint);
		vector<CPoint3D>().swap(tool.LineIntersection);
		m_ptArray.RemoveAll();
		CString FilePath;
		FilePath = openfile.GetPathName();
		ifstream ifs(FilePath);
		if (ifs.is_open())
		{
			string s;
			if (!ifs)exit(EXIT_FAILURE);
			while (getline(ifs, s))
			{
				cout << s << endl;
				data.push_back(s);
			}
			ifs.close();
			ifs.clear();

		}
		for (vector<string>::iterator it = data.begin(); it != data.end(); ++it)
		{
			static int i = 0;
			if ((*it) == "LINE")
			{
				CLine* pline = new CLine;
				m_ptArray.Add(pline);
				//pline->m_begin.x = (atof)((it + 12)->c_str());//��string���͵�����ת��Ϊfloat����
				//pline->m_begin.y = (atof)((it + 14)->c_str());
				//pline->m_begin.z = (atof)((it + 16)->c_str());
				//pline->m_end.x = (atof)((it + 18)->c_str());
				//pline->m_end.y = (atof)((it + 20)->c_str());
				//pline->m_end.z = (atof)((it + 22)->c_str());
				//++i;
				for (it; *(it+1)!="LINE";++it)
				{
					if (*it==" 10")
						pline->m_begin.x = (atof)((it + 1)->c_str());
					if (*it == " 20")
						pline->m_begin.y = (atof)((it + 1)->c_str());
					if (*it == " 30")
						pline->m_begin.z = (atof)((it + 1)->c_str());
					if (*it == " 11")
						pline->m_end.x = (atof)((it + 1)->c_str());
					if (*it == " 21")
						pline->m_end.y = (atof)((it + 1)->c_str());
					if (*it == " 31")
					{
						pline->m_end.z = (atof)((it + 1)->c_str());
						break;
					}
						
				}
				
				++i;
			}
			else if ((*it) == "ARC")
			{
				CArc* parc = new CArc;
				m_ptArray.Add(parc);
				/*parc->m_center.x = (atof)((it + 12)->c_str());
				parc->m_center.y = (atof)((it + 14)->c_str());
				parc->m_center.z = (atof)((it + 16)->c_str());
				parc->m_radio = (float)(atof)((it + 18)->c_str());
				parc->m_begin_angle = (float)(atof)((it + 22)->c_str());
				parc->m_end_angle = (float)(atof)((it + 24)->c_str());*/
				for (it; *(it + 1) != "LINE"; ++it)
				{
					if ((*it) == " 10")
						parc->m_center.x = (atof)((it + 1)->c_str());
					else if ((*it) == " 20")
						parc->m_center.y = (atof)((it + 1)->c_str());
					else if ((*it) == " 30")
						parc->m_center.z = (atof)((it + 1)->c_str());
					else if ((*it) == " 40")
						parc->m_radio = (float)(atof)((it + 1)->c_str());
					else if ((*it) == " 50")
						parc->m_begin_angle = (float)(atof)((it + 1)->c_str());
					else if ((*it) == " 51")
					{
						parc->m_end_angle = (float)(atof)((it + 1)->c_str());
						break;
					}
				}
				++i;
			}
			else if ((*it) == "CIRCLE")
			{
				CCircle* pcircle = new CCircle;
				m_ptArray.Add(pcircle);
				/*pcircle->m_center.x = (atof)((it + 12)->c_str());
				pcircle->m_center.y = (atof)((it + 14)->c_str());
				pcircle->m_center.z = (atof)((it + 16)->c_str());
				pcircle->m_radio = (float)(atof)((it + 18)->c_str());
				++i;*/
				for (it; *(it+1)!= "LINE";++it)
				{
					if((*it) == " 10")
						pcircle->m_center.x = (atof)((it + 1)->c_str());
					else if((*it) == " 20")
						pcircle->m_center.y = (atof)((it + 1)->c_str());
					else if((*it) == " 30")
						pcircle->m_center.z= (atof)((it + 1)->c_str());
					else if((*it) == " 40")
					{
						pcircle->m_radio = (float)(atof)((it+1)->c_str());
						break;
					}
						
				}
				++i;
			}
			else if ((*it) == "LWPOLYLINE")//͹��Ϊ0��ֱ�ߣ�͹��Ϊ��ֵΪԲ��˳ʱ�룬͹��Ϊ��ֵΪԲ����ʱ��
				//͹�Ⱦ���ֵ����1��ʾ���Ǵ���180�ȵĽǣ�����ֵС��1��ʾ����С��180�ȵĽ�
			{
				do
				{

					if ((*it) == " 10" && (*(it + 2)) == " 20" && (*(it + 4)) != "  0" && (*(it + 4)) != " 42")//��ȡֱ��
					{
						CLine* pline = new CLine;
						m_ptArray.Add(pline);
						pline->m_begin.x = (atof)((it + 1)->c_str());
						pline->m_begin.y = (atof)((it + 3)->c_str());
						pline->m_begin.z = 0.0;//��άpolyline
						pline->m_end.x = (atof)((it + 5)->c_str());
						pline->m_end.y = (atof)((it + 7)->c_str());
						pline->m_end.z = 0.0;//��άpolyline
						++i;
						it = it + 3;
					}
					else if ((*it) == " 10" && (*(it + 2)) == " 20" && (*(it + 4)) == " 42" && (*(it + 6) != "  0"))//��ȡԲ��
					{
						CArc* parc = new CArc;
						m_ptArray.Add(parc);
						parc->m_begin.x = (atof)((it + 1)->c_str());
						parc->m_begin.y = (atof)((it + 3)->c_str());
						parc->m_begin.z = 0.0;
						parc->m_Tudu = (atof)((it + 5)->c_str());
						parc->m_end.x = (atof)((it + 7)->c_str());
						parc->m_end.y = (atof)((it + 9)->c_str());
						parc->m_end.z = 0.0;
						++i;
						it = it + 5;
					}

					++it;
				} while ((*it) != "ENDSEC");
				++i;
			}

			else if ((*it) == ("SPLINE"))
			{
				Spline* s = new Spline;
				m_ptArray.Add(s);
				do
				{
					if (*it == "210")
						s->m_NormalVector.dx =(atof)( (it+1)->c_str());
					else if (*it == "220")
						s->m_NormalVector.dy = (atof)((it + 1)->c_str());
					else if (*it == "230")
						s->m_NormalVector.dz = (atof)((it + 1)->c_str());
					else if (*it == " 70")
						s->Type = (atof)((it + 1)->c_str());
					else if (*it == " 71")
						s->Degree = (atof)((it + 1)->c_str());
					else if (*it == " 72")
						s->NodeCount = (atof)((it + 1)->c_str());
					else if (*it == " 73")
						s->CtrlPtCount = (atof)((it + 1)->c_str());
					else if (*it == " 74")
						s->FitPtCount = (atof)((it + 1)->c_str());
					else if (*it == " 42")
						s->m_NodeTolerence = (atof)((it + 1)->c_str());
					else if (*it == " 43")
						s->m_CtrlTolerence = (atof)((it + 1)->c_str());
					else if (*it == " 44")
						s->m_FitTolerence = (atof)((it + 1)->c_str());
					else if (*it == " 12")
						s->m_BeginSlope.dx = (atof)((it + 1)->c_str());
					else if (*it == " 22")
						s->m_BeginSlope.dy = (atof)((it + 1)->c_str());
					else if (*it == " 32")
						s->m_BeginSlope.dz = (atof)((it + 1)->c_str());
					else if (*it == " 13")
						s->m_EndSlope.dx = (atof)((it + 1)->c_str());
					else if (*it == " 23")
						s->m_EndSlope.dy = (atof)((it + 1)->c_str());
					else if (*it == " 33")
						s->m_EndSlope.dz = (atof)((it + 1)->c_str());
					else if (*it == " 40")
						s->NodeValue.push_back((atof)((it + 1)->c_str()));
					/*else if (*it == " 41")
						s->WeightFactor = (atof)((it + 1)->c_str());*/
					else if (*it == " 10")
					{
						CPoint3D pt;
						pt.x =atof((it + 1)->c_str());
						pt.y = atof((it + 3)->c_str());
						pt.z = atof((it + 5)->c_str());
						s->CtrlPtValue.push_back(pt);
						it = it + 5;
					}
					else if (*it == " 11")
					{
						CPoint3D pt;
						pt.x = atof((it + 1)->c_str());
						pt.y = atof((it + 3)->c_str());
						pt.z = atof((it + 5)->c_str());
						s->FitPtValue.push_back(pt);
						it = it + 5;
					}

					++it;
				} while ((*it) != "  0");


				++i;
			}
		}

	}
	
	//ChangeToXOZ();
	//ChangeToYOZ();
	//ChangePartToXOZ();//������ת�ӹ���ʱ��������Բ�����ͼ������ı任2016.1.5
	//ChangeSideProcess();//���ڲ���ӹ�ʱ����ת��
	//ChangeCoordinate();//��������ӹ�ʱ����ת��
}



//void CSplitToDoc::ChangePartToXOZ()
//{
//	
//	CVector3D Translation;
//	CPoint3D EnterPoint;//Բ�뾶�ϵĴ�ֵ��
//
//	for (int i = 0; i != m_ptArray.GetSize(); ++i)
//	{
//		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
//		{
//			CPoint3D temp;
//			CPoint3D temp1;
//			temp.x = ((CLine*)m_ptArray.GetAt(i))->m_begin.x;
//			temp.y = 0;
//			temp.z = ((CLine*)m_ptArray.GetAt(i))->m_begin.y;
//			((CLine*)m_ptArray.GetAt(i))->m_begin = temp;
//
//			if (i == 1)
//			{
//
//				Translation.dx = EnterPoint.x - ((CLine*)m_ptArray.GetAt(i))->m_begin.x;
//				Translation.dy = EnterPoint.y - ((CLine*)m_ptArray.GetAt(i))->m_begin.y;
//				Translation.dz = EnterPoint.z - ((CLine*)m_ptArray.GetAt(i))->m_begin.z;
//			}
//
//			temp1.x = ((CLine*)m_ptArray.GetAt(i))->m_end.x;
//			temp1.y = 0;
//			temp1.z = ((CLine*)m_ptArray.GetAt(i))->m_end.y;
//			((CLine*)m_ptArray.GetAt(i))->m_end = temp1;
//
//
//		}
//		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
//			{
//
//				CPoint3D center;
//				center.x = ((CArc*)m_ptArray.GetAt(i))->m_center.x;
//				center.y = 0;
//				center.z = ((CArc*)m_ptArray.GetAt(i))->m_center.y;
//				((CArc*)m_ptArray.GetAt(i))->m_center = center;
//			}
//			else
//			{
//				CPoint3D temp;
//				CPoint3D temp1;
//				temp.x = ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//				temp.y = 0;
//				temp.z = ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//				((CArc*)m_ptArray.GetAt(i))->m_begin = temp;
//
//				temp1.x = ((CArc*)m_ptArray.GetAt(i))->m_end.x;
//				temp1.y = 0;
//				temp1.z = ((CArc*)m_ptArray.GetAt(i))->m_end.y;
//				((CArc*)m_ptArray.GetAt(i))->m_end = temp1;
//			}
//		}
//		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
//		{
//			CPoint3D center;
//			center.x = ((CCircle*)m_ptArray.GetAt(i))->m_center.x;
//			center.z = 0;
//			center.y = ((CCircle*)m_ptArray.GetAt(i))->m_center.y;
//			((CCircle*)m_ptArray.GetAt(i))->m_center = center;
//
//			EnterPoint.x = center.x + ((CCircle*)m_ptArray.GetAt(i))->m_radio;
//			EnterPoint.y = center.y;
//			EnterPoint.z = 0;
//
//			m_center = center;
//		}
//
//	}
//
//	for (int i = 0; i != m_ptArray.GetSize(); ++i)
//	{
//		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
//		{
//			((CLine*)m_ptArray.GetAt(i))->m_begin += Translation;
//			((CLine*)m_ptArray.GetAt(i))->m_end += Translation;
//
//		}
//		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)
//			{
//				((CArc*)m_ptArray.GetAt(i))->m_center += Translation;
//			}
//			else
//			{
//				((CArc*)m_ptArray.GetAt(i))->m_begin += Translation;
//				((CArc*)m_ptArray.GetAt(i))->m_end += Translation;
//
//			}
//		}
//		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
//		{
//
//		}
//	}
//
//}

void CSplitToDoc::ChangeToXOZ()//����ת��
{
	for (int i = 0; i != m_ptArray.GetSize(); ++i)
	{
		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
		{
			CPoint3D temp;
			CPoint3D temp1;
			temp.x=((CLine*)m_ptArray.GetAt(i))->m_begin.x;
			temp.y = 0;
			temp.z = ((CLine*)m_ptArray.GetAt(i))->m_begin.y;
			((CLine*)m_ptArray.GetAt(i))->m_begin = temp;

			temp1.x = ((CLine*)m_ptArray.GetAt(i))->m_end.x;
			temp1.y = 0;
			temp1.z = ((CLine*)m_ptArray.GetAt(i))->m_end.y;
			((CLine*)m_ptArray.GetAt(i))->m_end = temp1;
			
			
		}
		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
		{
			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
			{

				CPoint3D center;
				center.x = ((CArc*)m_ptArray.GetAt(i))->m_center.x;
				center.y = 0;
				center.z = ((CArc*)m_ptArray.GetAt(i))->m_center.y;
				((CArc*)m_ptArray.GetAt(i))->m_center = center;
			}
			else
			{
				CPoint3D temp;
				CPoint3D temp1;
				temp.x = ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
				temp.y = 0;
				temp.z = ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
				((CArc*)m_ptArray.GetAt(i))->m_begin = temp;

				temp1.x = ((CArc*)m_ptArray.GetAt(i))->m_end.x;
				temp1.y = 0;
				temp1.z = ((CArc*)m_ptArray.GetAt(i))->m_end.y;
				((CArc*)m_ptArray.GetAt(i))->m_end = temp1;
			}
		}
		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
		{
			CPoint3D center;
			center.x = ((CCircle*)m_ptArray.GetAt(i))->m_center.x;
			center.y = 0;
			center.z = ((CCircle*)m_ptArray.GetAt(i))->m_center.y;
			((CCircle*)m_ptArray.GetAt(i))->m_center = center;
		}

	}
}

void CSplitToDoc::ChangeToYOZ()//ת��ΪYOZƽ���ϵ�����
{
	for (int i = 0; i != m_ptArray.GetSize(); ++i)
	{
		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
		{
			CPoint3D temp;
			CPoint3D temp1;
			temp.y = ((CLine*)m_ptArray.GetAt(i))->m_begin.x;
			temp.x = 0;
			temp.z = ((CLine*)m_ptArray.GetAt(i))->m_begin.y;
			((CLine*)m_ptArray.GetAt(i))->m_begin = temp;

			temp1.y = ((CLine*)m_ptArray.GetAt(i))->m_end.x;
			temp1.x = 0;
			temp1.z = ((CLine*)m_ptArray.GetAt(i))->m_end.y;
			((CLine*)m_ptArray.GetAt(i))->m_end = temp1;


		}
		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
		{
			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
			{

				CPoint3D center;
				center.y = ((CArc*)m_ptArray.GetAt(i))->m_center.x;
				center.x = 0;
				center.z = ((CArc*)m_ptArray.GetAt(i))->m_center.y;
				((CArc*)m_ptArray.GetAt(i))->m_center = center;
			}
			else
			{
				CPoint3D temp;
				CPoint3D temp1;
				temp.y = ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
				temp.x = 0;
				temp.z = ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
				((CArc*)m_ptArray.GetAt(i))->m_begin = temp;

				temp1.y = ((CArc*)m_ptArray.GetAt(i))->m_end.x;
				temp1.x = 0;
				temp1.z = ((CArc*)m_ptArray.GetAt(i))->m_end.y;
				((CArc*)m_ptArray.GetAt(i))->m_end = temp1;
			}
		}
		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
		{
			CPoint3D center;
			center.y = ((CCircle*)m_ptArray.GetAt(i))->m_center.x;
			center.x = 0;
			center.z = ((CCircle*)m_ptArray.GetAt(i))->m_center.y;
			((CCircle*)m_ptArray.GetAt(i))->m_center = center;
		}

	}
}
void CSplitToDoc::MyDrawXOZ(COpenGLDC* pDC)
{
	//XOZƽ���ϻ�ͼ��
	for (int i = 0; i != m_ptArray.GetSize(); i++)
	{
		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
		{
			pDC->DrawLine(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end);
		}
		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
		{
			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
			{
				((CArc*)m_ptArray.GetAt(i))->GLDrawArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
					((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);
			}
			else//���߶�Բ��
			{
				((CArc*)m_ptArray.GetAt(i))->PolyCalculateXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
					((CArc*)m_ptArray.GetAt(i))->m_Tudu);
				if (((CArc*)m_ptArray.GetAt(i))->m_Tudu>0)//��ʱ��
				{
					((CArc*)m_ptArray.GetAt(i))->PolyDrawNArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
				}
				else//˳ʱ��
				{
					((CArc*)m_ptArray.GetAt(i))->PolyDrawSArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
				}

			}
		}
		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
		{
			((CCircle*)m_ptArray.GetAt(i))->GLDrawCircleXZ(((CCircle*)m_ptArray.GetAt(i))->m_center, ((CCircle*)m_ptArray.GetAt(i))->m_radio);
		}

	}
}

void CSplitToDoc::MyDrawYOZ(COpenGLDC* pDC)
{//YOZƽ�滭ͼ
	for (int i = 0; i != m_ptArray.GetSize(); i++)
	{
		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
		{
			pDC->DrawLine(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end);
		}
		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
		{
			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
			{
				((CArc*)m_ptArray.GetAt(i))->GLDrawArcYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
					((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);
			}
			else//���߶�Բ��
			{
				((CArc*)m_ptArray.GetAt(i))->PolyCalculateYZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
					((CArc*)m_ptArray.GetAt(i))->m_Tudu);
				if (((CArc*)m_ptArray.GetAt(i))->m_Tudu>0)//��ʱ��
				{
					((CArc*)m_ptArray.GetAt(i))->PolyDrawNArcYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
				}
				else//˳ʱ��
				{
					((CArc*)m_ptArray.GetAt(i))->PolyDrawSArcYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
				}

			}
		}
		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
		{
			((CCircle*)m_ptArray.GetAt(i))->GLDrawCircleYZ(((CCircle*)m_ptArray.GetAt(i))->m_center, ((CCircle*)m_ptArray.GetAt(i))->m_radio);
		}

	}
}
void CSplitToDoc::MyDraw(COpenGLDC* pDC)
{
	//��XOYƽ���ϻ�
	for (int i = 0; i != m_ptArray.GetSize(); i++)
	{
		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
		{
			pDC->DrawLine(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end);
		}
		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
		{
			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
			{
				((CArc*)m_ptArray.GetAt(i))->GLDrawArc(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
					((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);
			}
			else//���߶�Բ��
			{
				((CArc*)m_ptArray.GetAt(i))->PolyCalculate(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
					((CArc*)m_ptArray.GetAt(i))->m_Tudu);
				if (((CArc*)m_ptArray.GetAt(i))->m_Tudu>0)//��ʱ��
				{
					((CArc*)m_ptArray.GetAt(i))->PolyDrawNArc(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
				}
				else//˳ʱ��
				{
					((CArc*)m_ptArray.GetAt(i))->PolyDrawSArc(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
				}

			}
		}
		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
		{
			((CCircle*)m_ptArray.GetAt(i))->GLDrawCircle(((CCircle*)m_ptArray.GetAt(i))->m_center, ((CCircle*)m_ptArray.GetAt(i))->m_radio);
		}

	}
	
}

void CSplitToDoc::DrawOffset(COpenGLDC* pDC)
{
	//tool.Polygeon(m_ptArray, 10, 10, 10);

	//
	//for (vector<vector<OffsetPoint>>::iterator it = tool.Line.begin(); it != tool.Line.end(); ++it)
	//{
	//	for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
	//	{

	//		pDC->DrawLine(its->begin, its->end);
	//	}
	//}

	tool.RenderPolygeon(pDC);
	/*for (vector<OffsetPoint>::iterator it = tool.LineOffsetPoint.begin(); it != tool.LineOffsetPoint.end(); ++it)
	{
		pDC->SetMaterialColor(RGB(0, 255, 0));
		pDC->DrawLine(it->begin, it->end);
	}*/
	/*for (vector<OffsetPoint>::iterator it = tool.ExtendLine.begin(); it != tool.ExtendLine.end(); ++it)
	{
		pDC->SetMaterialColor(RGB(255, 0, 0));
		pDC->DrawLine(it->begin, it->end);
	}*/

}

void CSplitToDoc::DrawOtho(COpenGLDC* pDC)
{
	//  tool.Horizon(0.5, 45, 3, 20, 500, 500, 10, 50);
	//for (vector<vector<OffsetPoint> >::iterator it =tool.HorizonPos.begin(); it != tool.HorizonPos.end(); ++it)
	//{
	//	for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
	//	{

	//		pDC->DrawLine(its->begin, its->end);
	//	}

	//}

	//tool.Vertical(0.5, 45, 3, 20, 500, 500, 10, 50);
	//for (vector<vector<OffsetPoint> >::iterator it = tool.VerticalPos.begin(); it != tool.VerticalPos.end(); ++it)
	//{
	//	for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
	//	{

	//		pDC->DrawLine(its->begin, its->end);
	//	}

	//}

	////tool.HorizonRT(0.5, 45, 3, 20, 1000, 1000, 50, 50);
	//for (vector<vector<OffsetPoint> >::iterator it = tool.HorizonPosRT.begin(); it != tool.HorizonPosRT.end(); ++it)
	//{
	//	for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
	//	{

	//		pDC->DrawLine(its->begin, its->end);
	//	}

	//}

	////tool.VerticalRT(0.5, 45, 3, 20, 1000, 1000, 50, 50);
	//for (vector<vector<OffsetPoint> >::iterator it = tool.VerticalPosRT.begin(); it != tool.VerticalPosRT.end(); ++it)
	//{
	//	for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
	//	{

	//		pDC->DrawLine(its->begin, its->end);
	//	}

	//}


}

//void CSplitToDoc::DrawLineProcess(COpenGLDC* pDC)//�岹�ľ��Ȳ���,ʱ��ָ
//{
//
//	for (int i = 0; i != m_ptArray.GetSize(); i++)
//	{
//		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
//		{
//			vector<CPoint3D> point = tool.LineDiscrete(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end, 80,600);
//			
//			for (vector<CPoint3D>::iterator it = point.begin(); it != point.end()-1; ++it)
//			{
//				CPoint3D tempPt = *it;
//				tempPt.z = 200;
//				pDC->DrawLine(*it, tempPt);
//				pDC->DrawLine(*it, *(it + 1));
//			}
//			
//
//		}
//		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
//			{
//				
//				vector<CPoint3D> point =tool.ArcDiscrete(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//					((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i, 80, 600);
//				for (vector<CPoint3D>::iterator it = point.begin(); it != point.end() - 1; ++it)
//				{
//					CPoint3D tempPt = *it;
//					tempPt.z = 200;
//					pDC->DrawLine(*it, tempPt);
//					pDC->DrawLine(*it, *(it + 1));
//					
//				}
//			}
//			else//���߶�Բ��
//			{
//				vector<CPoint3D> point = tool.PolyArcDiscrete(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//					((CArc*)m_ptArray.GetAt(i))->m_Tudu, 80, 600);
//				for (vector<CPoint3D>::iterator it = point.begin(); it != point.end() - 1; ++it)
//				{
//					CPoint3D tempPt = *it;
//					tempPt.z = 200;
//					pDC->DrawLine(*it, tempPt);
//					pDC->DrawLine(*it, *(it + 1));
//					
//				}
//			}
//		}
//		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
//		{
//			CPoint3D place;//�洢��һ�����յ�
//			if (((CLine*)m_ptArray.GetAt(i-1))->flag == 1)
//				place = ((CLine*)m_ptArray.GetAt(i-1))->m_end;
//			else if (((CArc*)m_ptArray.GetAt(i-1))->flag == 2)
//			{
//				if (((CArc*)m_ptArray.GetAt(i - 1))->m_Tudu == 0)
//					place = ((CArc*)m_ptArray.GetAt(i - 1))->m_end;
//				else
//					place = ((CArc*)m_ptArray.GetAt(i - 1))->m_end;
//			}
//			vector<CPoint3D> point = tool.CircleDiscrete(((CCircle*)m_ptArray.GetAt(i))->m_center, ((CCircle*)m_ptArray.GetAt(i))->m_radio, place,80, 600);
//			for (vector<CPoint3D>::iterator it = point.begin(); it != point.end() - 1; ++it)
//			{
//				CPoint3D tempPt = *it;
//				tempPt.z = 200;
//				pDC->DrawLine(*it, tempPt);
//				pDC->DrawLine(*it, *(it + 1));
//				
//			}
//
//		}
//
//	}
//
//}
//
//BOOL CSplitToDoc::InitArcLineProcess()
//{
//	CPoint3D m_ArcCenter = CPoint3D(500, 500, 0);
//	float m_ArcRadius = 500;
//	float m_ArcBeginAngle = -45;
//	float m_ArcEndAngle = 45;
//	m_LinePocessArcArray.RemoveAll();
//	CArc* pArc = new CArc;
//	m_LinePocessArcArray.Add(pArc);
//	pArc->m_center = m_ArcCenter;
//	pArc->m_radio = m_ArcRadius;
//	pArc->m_begin_angle = m_ArcBeginAngle;
//	pArc->m_end_angle = m_ArcEndAngle;
//	pArc->m_begin.x = pArc->m_center.x + pArc->m_radio*cos(pArc->m_begin_angle*PI/180);
//	pArc->m_begin.y = pArc->m_center.y + pArc->m_radio*sin(pArc->m_begin_angle*PI/180);
//	pArc->m_end.x = pArc->m_center.x + pArc->m_radio*cos(pArc->m_end_angle*PI / 180);
//	pArc->m_end.y = pArc->m_center.y + pArc->m_radio*sin(pArc->m_end_angle*PI / 180);
//	pArc->m_begin.z = pArc->m_end.z = pArc->m_center.z;
//	pArc->m_Tudu = 0;
//
//	//��¼Բ�Ĵ�+X�뾶�������
//	CPoint3D m_MidlePt;
//	m_MidlePt.x = ((CArc*)m_LinePocessArcArray.GetAt(0))->m_center.x + ((CArc*)m_LinePocessArcArray.GetAt(0))->m_radio;
//	m_MidlePt.y = ((CArc*)m_LinePocessArcArray.GetAt(0))->m_center.y;
//	m_MidlePt.z = ((CArc*)m_LinePocessArcArray.GetAt(0))->m_center.z;
//
//	//��m_ptArray���������ת��XOZƽ���ٽ���ת�������m_MidlePt��λ��
//	m_LineProcess.RemoveAll();
//	for (int i = 0; i != m_ptArray.GetSize(); ++i)
//	{
//		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
//		{
//			CLine* pLine = new CLine;
//			m_LineProcess.Add(pLine);
//			pLine->m_begin.x =((CLine*)m_ptArray.GetAt(i))->m_begin.x;
//			pLine->m_begin.y = 0;
//			pLine->m_begin.z = ((CLine*)m_ptArray.GetAt(i))->m_begin.y;
//
//			pLine->m_end.x = ((CLine*)m_ptArray.GetAt(i))->m_end.x;
//			pLine->m_end.y =0 ;
//			pLine->m_end.z = ((CLine*)m_ptArray.GetAt(i))->m_end.y;
//		}
//		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)
//			{
//				CArc* pArc = new CArc;
//				m_LineProcess.Add(pArc);
//				pArc->m_center.x = ((CArc*)m_ptArray.GetAt(i))->m_center.x;
//				pArc->m_center.y = 0;
//				pArc->m_center.z = ((CArc*)m_ptArray.GetAt(i))->m_center.y;
//
//				pArc->m_radio = ((CArc*)m_ptArray.GetAt(i))->m_radio;
//				pArc->m_begin_angle = ((CArc*)m_ptArray.GetAt(i))->m_begin_angle;
//				pArc->m_end_angle = ((CArc*)m_ptArray.GetAt(i))->m_end_angle;
//				pArc->m_Tudu = 0;
//
//			}
//			else
//			{
//				CArc* pArc = new CArc;
//				m_LineProcess.Add(pArc);
//				pArc->m_begin.x = ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//				pArc->m_begin.y =0;
//				pArc->m_begin.z = ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//
//				pArc->m_end.x = ((CArc*)m_ptArray.GetAt(i))->m_end.x;
//				pArc->m_end.y = 0;
//				pArc->m_end.z = ((CArc*)m_ptArray.GetAt(i))->m_end.y;
//			}
//		}
//	}
//	//ƽ��
//	CVector3D m_OffsetDirection;
//	for (int i = 0; i != m_LineProcess.GetSize(); ++i)
//	{
//		if (i == 0)
//		{
//			if (((CLine*)m_LineProcess.GetAt(i))->flag == 1)
//			{
//				m_OffsetDirection.dx = m_MidlePt.x - ((CLine*)m_LineProcess.GetAt(i))->m_begin.x;
//				m_OffsetDirection.dy = m_MidlePt.y - ((CLine*)m_LineProcess.GetAt(i))->m_begin.y;
//				m_OffsetDirection.dz = 0;
//
//			}
//			else if (((CArc*)m_LineProcess.GetAt(i))->flag == 2)
//			{
//
//			}
//		}
//
//		if (((CLine*)m_LineProcess.GetAt(i))->flag == 1)
//		{
//			((CLine*)m_LineProcess.GetAt(i))->m_begin += m_OffsetDirection;
//			((CLine*)m_LineProcess.GetAt(i))->m_end += m_OffsetDirection;
//		}
//		else if (((CArc*)m_LineProcess.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_LineProcess.GetAt(i))->m_Tudu == 0)
//			{
//				((CArc*)m_LineProcess.GetAt(i))->m_center += m_OffsetDirection;
//			}
//			else
//			{
//				((CArc*)m_LineProcess.GetAt(i))->m_begin += m_OffsetDirection;
//				((CArc*)m_LineProcess.GetAt(i))->m_end += m_OffsetDirection;
//			}
//		}
//
//		
//	}
//	//��ɢ
//	vector<CPtrArray*>().swap(m_LineProcessList);//�������
//	for (int i = 0; i != m_LineProcess.GetSize(); ++i)
//	{
//		if (((CLine*)m_LineProcess.GetAt(i))->flag == 1)
//		{
//			vector<CPoint3D> m_tempPt = CLine::LineTDMInterpolationXZ(((CLine*)m_LineProcess.GetAt(i))->m_begin, ((CLine*)m_LineProcess.GetAt(i))->m_end, 60, 3000);
//			for (vector<CPoint3D>::iterator it = m_tempPt.begin(); it != m_tempPt.end(); ++it)
//			{
//				float m_tempRadius = CLine::Length(*it, CPoint3D(m_ArcCenter.x, m_ArcCenter.y, it->z));
//
//				CPtrArray* m_tempArray = new CPtrArray;
//				CArc* pArc = new CArc;
//				m_tempArray->Add(pArc);
//				pArc->m_radio = m_tempRadius;
//				pArc->m_center = CPoint3D(m_ArcCenter.x, m_ArcCenter.y, it->z);
//				pArc->m_begin_angle = m_ArcBeginAngle;
//				pArc->m_end_angle = m_ArcEndAngle;
//				pArc->m_Tudu = 0;
//
//				m_LineProcessList.push_back(m_tempArray);		
//			}
//		}
//		else if (((CArc*)m_LineProcess.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_LineProcess.GetAt(i))->m_Tudu == 0)//��ͨԲ��
//			{
//				vector<CPoint3D> m_tempPt = CArc::ArcTDMInterpolationXZ(((CArc*)m_LineProcess.GetAt(i))->m_center, ((CArc*)m_LineProcess.GetAt(i))->m_radio,
//					((CArc*)m_LineProcess.GetAt(i))->m_begin_angle, ((CArc*)m_LineProcess.GetAt(i))->m_end_angle, m_LineProcess, i,60,1000);
//				for (vector<CPoint3D>::iterator it = m_tempPt.begin(); it != m_tempPt.end(); ++it)
//				{
//					float m_tempRadius = CLine::Length(*it, CPoint3D(m_ArcCenter.x, m_ArcCenter.y, it->z));
//
//					CPtrArray* m_tempArray = new CPtrArray;
//					CArc* pArc = new CArc;
//					m_tempArray->Add(pArc);
//					pArc->m_radio = m_tempRadius;
//					pArc->m_center = CPoint3D(m_ArcCenter.x, m_ArcCenter.y, it->z);
//					pArc->m_begin_angle = m_ArcBeginAngle;
//					pArc->m_end_angle = m_ArcEndAngle;
//					pArc->m_Tudu = 0;
//
//					m_LineProcessList.push_back(m_tempArray);
//				}
//			}
//			else
//			{
//				vector<CPoint3D> m_tempPt = tool.PolyArcDiscreteXZ(((CArc*)m_LineProcess.GetAt(i))->m_begin, ((CArc*)m_LineProcess.GetAt(i))->m_end, 
//					((CArc*)m_LineProcess.GetAt(i))->m_Tudu, 60, 3000);
//				for (vector<CPoint3D>::iterator it = m_tempPt.begin(); it != m_tempPt.end(); ++it)
//				{
//					float m_tempRadius = CLine::Length(*it, CPoint3D(m_ArcCenter.x, m_ArcCenter.y, it->z));
//
//					CPtrArray* m_tempArray = new CPtrArray;
//					CArc* pArc = new CArc;
//					m_tempArray->Add(pArc);
//					pArc->m_radio = m_tempRadius;
//					pArc->m_center = CPoint3D(m_ArcCenter.x, m_ArcCenter.y, it->z);
//					pArc->m_begin_angle = m_ArcBeginAngle;
//					pArc->m_end_angle = m_ArcEndAngle;
//					pArc->m_Tudu = 0;
//
//					m_LineProcessList.push_back(m_tempArray);
//				}
//			}
//		}
//	}
//
//	return TRUE;
//}
//void CSplitToDoc::DrawArcLineProcess(COpenGLDC* pDC)
//{
//	if (InitArcLineProcess())
//	{
//		for (int i = 0; i != m_LinePocessArcArray.GetSize(); ++i)
//		{
//			if (((CArc*)m_LinePocessArcArray.GetAt(i))->flag == 2)
//			{
//				if (((CArc*)m_LinePocessArcArray.GetAt(i))->m_Tudu == 0)
//				{
//					((CArc*)m_LinePocessArcArray.GetAt(i))->GLDrawArc(((CArc*)m_LinePocessArcArray.GetAt(i))->m_center, ((CArc*)m_LinePocessArcArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_LinePocessArcArray.GetAt(i))->m_end_angle, 0.001, ((CArc*)m_LinePocessArcArray.GetAt(i))->m_radio, m_LinePocessArcArray, i);
//				}
//			}
//		}
//		for (int i = 0; i != m_LineProcess.GetSize(); ++i)
//		{
//			if (((CLine*)m_LineProcess.GetAt(i))->flag == 1)
//			{
//				pDC->DrawLine(((CLine*)m_LineProcess.GetAt(i))->m_begin, ((CLine*)m_LineProcess.GetAt(i))->m_end);
//			}
//			else if (((CArc*)m_LineProcess.GetAt(i))->flag == 2)
//			{
//				if (((CArc*)m_LineProcess.GetAt(i))->m_Tudu == 0)
//				{
//					((CArc*)m_LineProcess.GetAt(i))->GLDrawArcXZ(((CArc*)m_LineProcess.GetAt(i))->m_center, ((CArc*)m_LineProcess.GetAt(i))->m_begin_angle,
//						((CArc*)m_LineProcess.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_LineProcess.GetAt(i))->m_radio, m_LineProcess, i);
//				}
//				else
//				{
//					((CArc*)m_LineProcess.GetAt(i))->PolyCalculateXZ(((CArc*)m_LineProcess.GetAt(i))->m_begin, ((CArc*)m_LineProcess.GetAt(i))->m_end, 
//						                                             ((CArc*)m_LineProcess.GetAt(i))->m_Tudu);
//					if (((CArc*)m_LineProcess.GetAt(i))->m_Tudu > 0)
//					{
//						((CArc*)m_LineProcess.GetAt(i))->PolyDrawNArcXZ(((CArc*)m_LineProcess.GetAt(i))->m_center, ((CArc*)m_LineProcess.GetAt(i))->m_begin_angle,
//							((CArc*)m_LineProcess.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_LineProcess.GetAt(i))->m_radio);
//					}
//					else
//					{
//						((CArc*)m_LineProcess.GetAt(i))->PolyDrawSArcXZ(((CArc*)m_LineProcess.GetAt(i))->m_center, ((CArc*)m_LineProcess.GetAt(i))->m_begin_angle,
//							((CArc*)m_LineProcess.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_LineProcess.GetAt(i))->m_radio);
//					}
//				}
//			}
//		}
//		
//		for (vector<CPtrArray*>::iterator it = m_LineProcessList.begin(); it != m_LineProcessList.end(); ++it)
//		{
//			for (int i = 0; i != (*it)->GetSize(); ++i)
//			{
//				if (((CArc*)(*it)->GetAt(i))->flag == 2)
//				{
//					if (((CArc*)(*it)->GetAt(i))->m_Tudu == 0)
//					{
//						((CArc*)(*it)->GetAt(i))->GLDrawArc(((CArc*)(*it)->GetAt(i))->m_center, ((CArc*)(*it)->GetAt(i))->m_begin_angle, ((CArc*)(*it)->GetAt(i))->m_end_angle,
//							0.001, ((CArc*)(*it)->GetAt(i))->m_radio, **it, i);
//					}
//				}
//			}
//		}
//
//	}
//}

//void CSplitToDoc::DrawRotate(COpenGLDC* pDC)
//{
	////��XOZƽ���ϻ�ֱ�ߺ�Բ������XOYƽ���ϻ�Բ
	//for (int i = 0; i != m_ptArray.GetSize(); i++)
	//{
	//	if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
	//	{
	//		pDC->DrawLine(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end);
	//		//vector<CPoint3D> point = CLine::LineTDMInterpolationXZ(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end, 8, 120);
	//		vector<CPoint3D> point = tool.LineDiscreteXZ(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end, 8, 30);

	//		for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
	//		{
	//			m_center.z = it->z;
	//			float radius = sqrt(pow(it->x - m_center.x, 2) + pow(it->y - m_center.y, 2));
	//			//vector<CPoint3D> Cpoint = CCircle::CircleTDMInterpolation(m_center, radius, *it, 8, 120);
	//			vector<CPoint3D> Cpoint = tool.CircleDiscrete(m_center, radius, *it, 8, 300);

	//			/*glBegin(GL_POINTS);
	//			for (int j = 0;j!=Cpoint.size();++j)
	//			{
	//				glVertex3f(Cpoint[j].x, Cpoint[j].y, Cpoint[j].z);
	//			}
	//			glEnd();*/

	//			for (int j = 0; j != Cpoint.size()-1; ++j)
	//			{
	//				pDC->DrawLine(Cpoint[j], Cpoint[j + 1]);
	//			}
	//		}
	//		
	//	}
	//	else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
	//	{
	//		if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
	//		{
	//			((CArc*)m_ptArray.GetAt(i))->GLDrawArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
	//				((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);

	//			/*vector<CPoint3D> point = CArc::ArcTDMInterpolationXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
	//				((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i, 8, 120);*/
	//			vector<CPoint3D> point = tool.ArcDiscreteXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
	//				((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i, 8, 300);
	//			
	//			for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
	//			{
	//				m_center.z = it->z;
	//				float radius = sqrt(pow(it->x - m_center.x, 2) + pow(it->y - m_center.y, 2));
	//				//vector<CPoint3D> Cpoint = CCircle::CircleTDMInterpolation(m_center, radius, *it, 8, 120);
	//				vector<CPoint3D> Cpoint = tool.CircleDiscrete(m_center, radius, *it, 8, 300);

	//				glBegin(GL_POINTS);
	//				for (int j = 0; j != Cpoint.size(); ++j)
	//				{
	//					glVertex3f(Cpoint[j].x, Cpoint[j].y, Cpoint[j].z);
	//				}
	//				glEnd();
	//			}
	//			
	//			
	//		}
	//		else//���߶�Բ��********2016.1.1������߶ε�Բ�������Ҫ��ʾ����Ҫ��toolpath�����polyarcediscrete����XOZƽ���ϵı仯*************
	//		{
	//			((CArc*)m_ptArray.GetAt(i))->PolyCalculateXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
	//				((CArc*)m_ptArray.GetAt(i))->m_Tudu);

	//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu>0)//��ʱ��
	//			{
	//				((CArc*)m_ptArray.GetAt(i))->PolyDrawNArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
	//					((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);

	//				vector<CPoint3D> point = tool.PolyArcDiscreteXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
	//					((CArc*)m_ptArray.GetAt(i))->m_Tudu, 8, 120);

	//				for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
	//				{
	//					m_center.z = it->z;
	//					float radius = sqrt(pow(it->x - m_center.x, 2) + pow(it->y - m_center.y, 2));
	//					vector<CPoint3D> Cpoint = tool.CircleDiscrete(m_center, radius, *it, 8, 120);

	//					glBegin(GL_POINTS);
	//					for (int j = 0; j != Cpoint.size(); ++j)
	//					{
	//						glVertex3f(Cpoint[j].x, Cpoint[j].y, Cpoint[j].z);
	//					}
	//					glEnd();
	//				}


	//			}
	//			else//˳ʱ��
	//			{
	//				((CArc*)m_ptArray.GetAt(i))->PolyDrawSArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
	//					((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);


	//				vector<CPoint3D> point = tool.PolyArcDiscreteXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
	//					((CArc*)m_ptArray.GetAt(i))->m_Tudu, 8, 120);

	//				for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
	//				{
	//					m_center.z = it->z;
	//					float radius = sqrt(pow(it->x - m_center.x, 2) + pow(it->y - m_center.y, 2));
	//					vector<CPoint3D> Cpoint = tool.CircleDiscrete(m_center, radius, *it, 8, 120);

	//					glBegin(GL_POINTS);
	//					for (int j = 0; j != Cpoint.size(); ++j)
	//					{
	//						glVertex3f(Cpoint[j].x, Cpoint[j].y, Cpoint[j].z);
	//					}
	//					glEnd();
	//				}


	//			}

	//		}
	//	}
	//	else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
	//	{
	//		((CCircle*)m_ptArray.GetAt(i))->GLDrawCircle(((CCircle*)m_ptArray.GetAt(i))->m_center, ((CCircle*)m_ptArray.GetAt(i))->m_radio);
	//	}

	//}
//}

//
//void CSplitToDoc::ChangeSideProcess()//�����ж��Ƿ�պϲ����ñպϵ�����λ��XOYƽ�棬û�бպϵ��߶�λ�������***���������Ȼ���������ٻ��Ƿ������*****
//{
//	if (m_ptArray.GetSize() !=0 )//�����������ݵ�ʱ��Ž��м���
//	{
//		CVector3D IsSealing;//�ж��Ƿ�պ�
//		CVector3D Translation;//���ڴ洢ƫ����
//		//int mark=0;//���ڴ洢���ͼ���м���Ԫ��
//		//CPoint3D XMax;//���ڴ洢X���귽����ֵ���ĵ�����꣬һ��Ϊ���
//
//		for (int i = 0; i != m_ptArray.GetSize(); ++i)
//		{
//			if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
//			{
//				CVector3D temp;
//				CPoint3D  tempMax;
//				temp.dx = ((CLine*)m_ptArray.GetAt(i))->m_end.x - ((CLine*)m_ptArray.GetAt(i))->m_begin.x;
//				temp.dy = ((CLine*)m_ptArray.GetAt(i))->m_end.y - ((CLine*)m_ptArray.GetAt(i))->m_begin.y;
//				temp.dz = ((CLine*)m_ptArray.GetAt(i))->m_end.z - ((CLine*)m_ptArray.GetAt(i))->m_begin.z;
//
//				IsSealing += temp;
//
//				if (((CLine*)m_ptArray.GetAt(i))->m_end.x >= ((CLine*)m_ptArray.GetAt(i))->m_begin.x)
//					tempMax = ((CLine*)m_ptArray.GetAt(i))->m_end;
//				else
//					tempMax = ((CLine*)m_ptArray.GetAt(i))->m_begin;
//
//				if (tempMax.x >= XMax.x)
//					XMax = tempMax;
//
//			}
//			else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//			{
//				CVector3D temp;
//				CPoint3D  tempMax;
//				if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)
//				{
//
//					((CArc*)m_ptArray.GetAt(i))->Calculate(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i);
//
//					temp.dx = ((CArc*)m_ptArray.GetAt(i))->m_end.x - ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//					temp.dy = ((CArc*)m_ptArray.GetAt(i))->m_end.y - ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//					temp.dz = ((CArc*)m_ptArray.GetAt(i))->m_end.z - ((CArc*)m_ptArray.GetAt(i))->m_begin.z;
//				}
//				else
//				{
//					temp.dx = ((CArc*)m_ptArray.GetAt(i))->m_end.x - ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//					temp.dy = ((CArc*)m_ptArray.GetAt(i))->m_end.y - ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//					temp.dz = ((CArc*)m_ptArray.GetAt(i))->m_end.z - ((CArc*)m_ptArray.GetAt(i))->m_begin.z;
//				}
//
//				IsSealing += temp;
//
//
//				if (((CArc*)m_ptArray.GetAt(i))->m_end.x >= ((CArc*)m_ptArray.GetAt(i))->m_begin.x)
//					tempMax = ((CArc*)m_ptArray.GetAt(i))->m_end;
//				else
//					tempMax = ((CArc*)m_ptArray.GetAt(i))->m_begin;
//
//				if (tempMax.x >= XMax.x)
//					XMax = tempMax;
//			}
//			else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)//Բ�Ļ������뿼�ǣ�����Ĳ���ӹ����ǵ��治��Բ�ε�ʱ��ļӹ�
//			{
//
//			}
//
//			if (IsSealing.GetLength() < 1.0)//����������ĳ��ȵ���0���ʾ���Ǳպϵ�
//			{
//				mark = i;
//				break;//�������ʱ��������ѭ��
//			}
//
//		}
//
//
//
//		for (int number = mark + 1; number != m_ptArray.GetSize(); ++number)
//		{
//			if (((CLine*)m_ptArray.GetAt(number))->flag == 1)
//			{
//				CPoint3D temp;
//				temp.x = ((CLine*)m_ptArray.GetAt(number))->m_begin.x;
//				temp.y = 0;
//				temp.z = ((CLine*)m_ptArray.GetAt(number))->m_begin.y;
//				((CLine*)m_ptArray.GetAt(number))->m_begin = temp;
//
//				temp.x = ((CLine*)m_ptArray.GetAt(number))->m_end.x;
//				temp.y = 0;
//				temp.z = ((CLine*)m_ptArray.GetAt(number))->m_end.y;
//				((CLine*)m_ptArray.GetAt(number))->m_end = temp;
//
//				if (number == mark + 1)
//				{
//					Translation.dx = XMax.x - ((CLine*)m_ptArray.GetAt(number))->m_begin.x;
//					Translation.dy = XMax.y - ((CLine*)m_ptArray.GetAt(number))->m_begin.y;
//					Translation.dz = XMax.z - ((CLine*)m_ptArray.GetAt(number))->m_begin.z;
//
//				}
//
//			}
//			else if (((CArc*)m_ptArray.GetAt(number))->flag == 2)
//			{
//				if (((CArc*)m_ptArray.GetAt(number))->m_Tudu == 0)//��ͨԲ��
//				{
//					((CArc*)m_ptArray.GetAt(number))->Calculate(((CArc*)m_ptArray.GetAt(number))->m_center, ((CArc*)m_ptArray.GetAt(number))->m_radio, ((CArc*)m_ptArray.GetAt(number))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(number))->m_end_angle, m_ptArray, number);
//
//					CPoint3D center;
//					center.x = ((CArc*)m_ptArray.GetAt(number))->m_center.x;
//					center.y = 0;
//					center.z = ((CArc*)m_ptArray.GetAt(number))->m_center.y;
//					((CArc*)m_ptArray.GetAt(number))->m_center = center;
//
//
//					if (number == mark + 1)
//					{
//						Translation.dx = XMax.x - ((CArc*)m_ptArray.GetAt(number))->m_begin.x;
//						Translation.dy = XMax.y - ((CArc*)m_ptArray.GetAt(number))->m_begin.y;
//						Translation.dz = XMax.z - ((CArc*)m_ptArray.GetAt(number))->m_begin.z;
//
//					}
//				}
//				else
//				{
//					CPoint3D temp;
//					CPoint3D temp1;
//					temp.x = ((CArc*)m_ptArray.GetAt(number))->m_begin.x;
//					temp.y = 0;
//					temp.z = ((CArc*)m_ptArray.GetAt(number))->m_begin.y;
//					((CArc*)m_ptArray.GetAt(number))->m_begin = temp;
//
//					temp1.x = ((CArc*)m_ptArray.GetAt(number))->m_end.x;
//					temp1.y = 0;
//					temp1.z = ((CArc*)m_ptArray.GetAt(number))->m_end.y;
//					((CArc*)m_ptArray.GetAt(number))->m_end = temp1;
//
//					if (number == mark + 1)
//					{
//						Translation.dx = XMax.x - ((CArc*)m_ptArray.GetAt(number))->m_begin.x;
//						Translation.dy = XMax.y - ((CArc*)m_ptArray.GetAt(number))->m_begin.y;
//						Translation.dz = XMax.z - ((CArc*)m_ptArray.GetAt(number))->m_begin.z;
//
//					}
//
//				}
//			}
//			else if (((CCircle*)m_ptArray.GetAt(number))->flag == 3)
//			{
//
//			}
//		}
//
//
//		for (int i = mark + 1; i != m_ptArray.GetSize(); ++i)
//		{
//			if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
//			{
//				((CLine*)m_ptArray.GetAt(i))->m_begin += Translation;
//				((CLine*)m_ptArray.GetAt(i))->m_end += Translation;
//
//			}
//			else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//			{
//				if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)
//				{
//					((CArc*)m_ptArray.GetAt(i))->m_center += Translation;
//				}
//				else
//				{
//					((CArc*)m_ptArray.GetAt(i))->m_begin += Translation;
//					((CArc*)m_ptArray.GetAt(i))->m_end += Translation;
//
//				}
//			}
//			else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
//			{
//
//			}
//		}
//
//	}
//}
//
////������ӹ�
//void CSplitToDoc::DrawSide(COpenGLDC* pDC)//�ı�ÿ����岹������CToolPath���棬��bain����Ĳ岹���ȿ������������
//{
//	//ChangeSideProcess();//���ڲ���ӹ�ʱ����ת��
//
//	for (int i = 0; i != m_ptArray.GetSize(); ++i)
//	{
//		if (((CLine*)m_ptArray.GetAt(i))->flag == 1)
//		{
//			pDC->DrawLine(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end);
//
//			if (((CLine*)m_ptArray.GetAt(i))->m_begin.z == 0.0 && ((CLine*)m_ptArray.GetAt(i))->m_end.z == 0.0)
//			{
//				vector<CPoint3D> point = tool.LineDiscrete(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end, 8, 200);
//
//				glBegin(GL_POINTS);
//				for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//				{
//					glVertex3f(it->x, it->y, it->z);
//				}
//				glEnd();
//
//			}
//			else
//			{
//				vector<CPoint3D> point = tool.LineDiscreteXZ(((CLine*)m_ptArray.GetAt(i))->m_begin, ((CLine*)m_ptArray.GetAt(i))->m_end, 8, 200);
//
//				
//				for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//				{
//					/*glPointSize(5);
//					glBegin(GL_POINTS);
//					glVertex3f(it->x, it->y, it->z);
//					glEnd();*/
//
//					double offset;
//					offset = sqrt(pow(it->x - XMax.x, 2) + pow(it->y - XMax.y, 2));
//					vector<CPoint3D> OffsetPoint=tool.OffsetAlgorithm(m_ptArray, mark, offset);
//					
//				    for (vector<CPoint3D>::iterator its = OffsetPoint.begin(); its != OffsetPoint.end()-1; ++its)
//					{
//						its->z = it->z;
//						(its + 1)->z = it->z;
//						pDC->DrawLine(*its, *(its + 1));
//					}
//
//				}
//				
//
//
//			}
//			
//		}
//		else if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
//			{
//				if (((CArc*)m_ptArray.GetAt(i))->m_center.z == 0.0)//�ж��Ƿ�����XOYƽ���ϻ��ǲ�����XOYƽ����
//				{
//					((CArc*)m_ptArray.GetAt(i))->GLDrawArc(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);
//
//					vector<CPoint3D> point = tool.ArcDiscrete(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i, 8, 600);
//					glBegin(GL_POINTS);
//					for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//					{
//						glVertex3f(it->x, it->y, it->z);
//					}
//					glEnd();
//
//
//				}
//				else
//				{
//					((CArc*)m_ptArray.GetAt(i))->GLDrawArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);
//
//
//					vector<CPoint3D> point = tool.ArcDiscreteXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i, 8, 600);
//					
//					for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//					{
//						/*glBegin(GL_POINTS);
//						glVertex3f(it->x, it->y, it->z);
//						glEnd();*/
//
//						double offset;
//						offset = sqrt(pow(it->x - XMax.x, 2) + pow(it->y - XMax.y, 2));
//						vector<CPoint3D> OffsetPoint = tool.OffsetAlgorithm(m_ptArray, mark, offset);
//						for (vector<CPoint3D>::iterator its = OffsetPoint.begin(); its != OffsetPoint.end() - 1; ++its)
//						{
//							its->z = it->z;
//							(its + 1)->z = it->z;
//							pDC->DrawLine(*its, *(its + 1));
//						}
//					}
//					
//
//					
//
//
//				}
//			}
//			else//���߶�Բ��
//			{
//				if (((CArc*)m_ptArray.GetAt(i))->m_begin.z == 0.0 && ((CArc*)m_ptArray.GetAt(i))->m_end.z == 0.0)
//				{
//					((CArc*)m_ptArray.GetAt(i))->PolyCalculate(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//						((CArc*)m_ptArray.GetAt(i))->m_Tudu);
//
//					if (((CArc*)m_ptArray.GetAt(i))->m_Tudu>0)//��ʱ��
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawNArc(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//					else//˳ʱ��
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawSArc(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//
//
//					vector<CPoint3D> point = tool.PolyArcDiscrete(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//						((CArc*)m_ptArray.GetAt(i))->m_Tudu, 8, 600);
//					glBegin(GL_POINTS);
//					for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//					{
//						glVertex3f(it->x, it->y, it->z);
//					}
//					glEnd();
//
//
//				}
//				else
//				{
//					((CArc*)m_ptArray.GetAt(i))->PolyCalculateXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//						((CArc*)m_ptArray.GetAt(i))->m_Tudu);
//
//					if (((CArc*)m_ptArray.GetAt(i))->m_Tudu > 0)//��ʱ��
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawNArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//					else
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawSArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//
//					vector<CPoint3D> point = tool.PolyArcDiscreteXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//						((CArc*)m_ptArray.GetAt(i))->m_Tudu, 8, 600);
//					
//					for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//					{
//						/*glBegin(GL_POINTS);
//						glVertex3f(it->x, it->y, it->z);
//						glEnd();
//                        */
//						double offset;
//						offset = sqrt(pow(it->x - XMax.x, 2) + pow(it->y - XMax.y, 2));
//						vector<CPoint3D> OffsetPoint = tool.OffsetAlgorithm(m_ptArray, mark, offset);
//						for (vector<CPoint3D>::iterator its = OffsetPoint.begin(); its != OffsetPoint.end() - 1; ++its)
//						{
//							its->z = it->z;
//							(its + 1)->z = it->z;
//							pDC->DrawLine(*its, *(its + 1));
//						}
//
//					}
//					
//
//				}
//			}
//		}
//		else if (((CCircle*)m_ptArray.GetAt(i))->flag == 3)
//		{
//
//		}
//	}
//}


//����ӹ�����ת��
//void CSplitToDoc::ChangeCoordinate()//�̶�������Ԫ��Ϊ����
//{
//
//	for (int i = 0; i != m_ptArray.GetSize(); ++i)
//	{
//		if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//		{
//			
//
//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
//			{
//
//				/*((CArc*)m_ptArray.GetAt(i))->Calculate(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//					((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i);*/
//
//				if (i != m_ptArray.GetSize()-1)
//				{
//					CPoint3D center;
//					center.x = ((CArc*)m_ptArray.GetAt(i))->m_center.x;
//					center.y = 0;
//					center.z = ((CArc*)m_ptArray.GetAt(i))->m_center.y;
//					((CArc*)m_ptArray.GetAt(i))->m_center = center;
//				}
//				else if (i == m_ptArray.GetSize() - 1)
//				{
//					CPoint3D center;
//					CVector3D Direction;
//
//					center.y = ((CArc*)m_ptArray.GetAt(i))->m_center.x;
//					center.x = 0;
//					center.z = ((CArc*)m_ptArray.GetAt(i))->m_center.y;
//					((CArc*)m_ptArray.GetAt(i))->m_center = center;
//
//					((CArc*)m_ptArray.GetAt(i))->CalculateYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle-270,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle+90, m_ptArray, i);
//
//					if (((CArc*)m_ptArray.GetAt(0))->m_Tudu == 0)
//					{
//						((CArc*)m_ptArray.GetAt(0))->CalculateXZ(((CArc*)m_ptArray.GetAt(0))->m_center, ((CArc*)m_ptArray.GetAt(0))->m_radio, ((CArc*)m_ptArray.GetAt(0))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(0))->m_end_angle, m_ptArray, 0);
//					}
//
//					
//					Direction.dx = ((CArc*)m_ptArray.GetAt(0))->m_begin.x - ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//					Direction.dy = ((CArc*)m_ptArray.GetAt(0))->m_begin.y - ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//					Direction.dz = ((CArc*)m_ptArray.GetAt(0))->m_begin.z - ((CArc*)m_ptArray.GetAt(i))->m_begin.z;
//
//					((CArc*)m_ptArray.GetAt(i))->m_center += Direction;
//				}
//			}
//			else//���߶�Բ��
//			{
//				if (i != m_ptArray.GetSize() - 1)//ת����XOZƽ��
//				{
//					CPoint3D temp;
//					temp.x = ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//					temp.y= 0;
//					temp.z = ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//
//					((CArc*)m_ptArray.GetAt(i))->m_begin = temp;
//
//					temp.x = ((CArc*)m_ptArray.GetAt(i))->m_end.x;
//					temp.y = 0;
//					temp.z = ((CArc*)m_ptArray.GetAt(i))->m_end.y;
//
//					((CArc*)m_ptArray.GetAt(i))->m_end = temp;
//
//				}
//				else if (i == m_ptArray.GetSize() - 1)//ת������YOZƽ��ƽ�е�����
//				{
//					CPoint3D temp1,temp2;
//					CVector3D Direction, vec1, vec2;
//					CVector3D Rotate1, Rotate2;
//
//
//					temp1.x =0 ;
//					temp1.y =((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//					temp1.z = ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//
//					((CArc*)m_ptArray.GetAt(i))->m_begin = temp1;
//
//					temp2.x = 0;
//					temp2.y = ((CArc*)m_ptArray.GetAt(i))->m_end.x;
//					temp2.z = ((CArc*)m_ptArray.GetAt(i))->m_end.y;
//
//					((CArc*)m_ptArray.GetAt(i))->m_end = temp2;
//
//					if (((CArc*)m_ptArray.GetAt(0))->m_Tudu == 0)
//					{
//						((CArc*)m_ptArray.GetAt(0))->CalculateXZ(((CArc*)m_ptArray.GetAt(0))->m_center, ((CArc*)m_ptArray.GetAt(0))->m_radio, ((CArc*)m_ptArray.GetAt(0))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(0))->m_end_angle, m_ptArray, 0);
//					}
//
//					((CArc*)m_ptArray.GetAt(i))->PolyCalculateYZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end, ((CArc*)m_ptArray.GetAt(i))->m_Tudu);
//
//					vec1 = ((CArc*)m_ptArray.GetAt(i))->m_begin - ((CArc*)m_ptArray.GetAt(i))->m_center;
//					vec2 = ((CArc*)m_ptArray.GetAt(i))->m_end - ((CArc*)m_ptArray.GetAt(i))->m_center;
//					Rotate1 = CVector3D(vec1.dx, -1 * vec1.dz, vec1.dy);//�����ʱ����ת90��
//					Rotate2 = CVector3D(vec2.dx, -1 * vec2.dz, vec2.dy);//�յ���ʱ����ת90��
//
//					((CArc*)m_ptArray.GetAt(i))->m_begin = ((CArc*)m_ptArray.GetAt(i))->m_center + Rotate1;//��ת90�Ⱥ������λ������
//					((CArc*)m_ptArray.GetAt(i))->m_end = ((CArc*)m_ptArray.GetAt(i))->m_center + Rotate2;//��ת90�Ⱥ���յ��λ������
//
//					//��ת����������ڵ�һ��Ԫ�ص�ƫ����
//					Direction.dx = ((CArc*)m_ptArray.GetAt(0))->m_begin.x - ((CArc*)m_ptArray.GetAt(i))->m_begin.x;
//					Direction.dy = ((CArc*)m_ptArray.GetAt(0))->m_begin.y - ((CArc*)m_ptArray.GetAt(i))->m_begin.y;
//					Direction.dz = ((CArc*)m_ptArray.GetAt(0))->m_begin.z - ((CArc*)m_ptArray.GetAt(i))->m_begin.z;
//
//					//ʹ���һ��Ԫ�ص�������һ��Ԫ�ص����������
//					((CArc*)m_ptArray.GetAt(i))->m_begin += Direction;
//					((CArc*)m_ptArray.GetAt(i))->m_end += Direction;
//
//				}
//
//			}
//		}
//	}
//
//}



//������ӹ�
//void CSplitToDoc::DrawSurface(COpenGLDC* pDC)
//{
//	for (int i = 0; i != m_ptArray.GetSize(); ++i)
//	{
//		if (((CArc*)m_ptArray.GetAt(i))->flag == 2)
//		{
//			if (((CArc*)m_ptArray.GetAt(i))->m_Tudu == 0)//��ͨԲ��
//			{
//				if (((CArc*)m_ptArray.GetAt(i))->m_center.y == 0)//XOZƽ��
//				{
//					((CArc*)m_ptArray.GetAt(i))->GLDrawArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);
//
//					vector<CPoint3D> point = tool.ArcDiscreteXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle, m_ptArray, i,60,6000/* 8, 100*/);
//
//					
//					
//					for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//					{
//						glBegin(GL_POINTS);
//						glVertex3f(it->x, it->y, it->z);
//					    glEnd();
//
//						CVector3D Direction;
//						if (((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_Tudu == 0)
//						{
//							((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->CalculateYZ(((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_center, ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_radio,
//								((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_begin_angle - 270, ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_end_angle + 90, m_ptArray, m_ptArray.GetSize() - 1);
//						}
//
//						Direction = *it - ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_begin;
//
//						vector<CPoint3D> point2 = tool.ArcDiscreteYZ(((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_center + Direction, ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_radio, ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_begin_angle - 270,
//							((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_end_angle + 90, m_ptArray, m_ptArray.GetSize() - 1,60,3000/* 8, 250*/);
//
//						for (vector<CPoint3D>::iterator its = point2.begin(); its != point2.end()-1; ++its)
//						{
//							pDC->DrawLine(*its, *(its + 1));
//						}
//					}
//					
//				}
//				else //ƽ����YOZƽ��
//				{
//					((CArc*)m_ptArray.GetAt(i))->GLDrawArcYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle-270,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle+90, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio, m_ptArray, i);
//
//					vector<CPoint3D> point = tool.ArcDiscreteYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_radio, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle-270,
//						((CArc*)m_ptArray.GetAt(i))->m_end_angle+90, m_ptArray, i, 60,6000/*8, 100*/);
//
//					
//					glBegin(GL_POINTS);
//					for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//					{
//						glVertex3f(it->x, it->y, it->z);
//					}
//					glEnd();
//
//				}
//			}
//			else//���߶�Բ��
//			{
//			
//				if (((CArc*)m_ptArray.GetAt(i))->m_begin.y == 0 && ((CArc*)m_ptArray.GetAt(i))->m_end.y == 0)//XOZƽ��
//				{
//					((CArc*)m_ptArray.GetAt(i))->PolyCalculateXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//						((CArc*)m_ptArray.GetAt(i))->m_Tudu);
//
//					if (((CArc*)m_ptArray.GetAt(i))->m_Tudu < 0)//˳ʱ��
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawSArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//					else//��ʱ��
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawNArcXZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//
//					vector<CPoint3D> point = tool.PolyArcDiscreteXZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//						((CArc*)m_ptArray.GetAt(i))->m_Tudu, 60,6000/*8, 300*/);
//					
//					for (vector<CPoint3D>::iterator it = point.begin(); it != point.end(); ++it)
//					{
//						glBegin(GL_POINTS);
//						glVertex3f(it->x, it->y, it->z);
//                        glEnd();
//
//
//						CVector3D Direction;
//						if (((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_Tudu == 0)
//						{
//							((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->CalculateYZ(((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_center, ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_radio, ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_begin_angle - 270,
//								((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_end_angle + 90, m_ptArray, m_ptArray.GetSize() - 1);
//						}
//
//						Direction = *it - ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_begin;
//
//						vector<CPoint3D> point2 = tool.PolyArcDiscreteYZ(((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_begin + Direction, ((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_end + Direction,
//							((CArc*)m_ptArray.GetAt(m_ptArray.GetSize() - 1))->m_Tudu, 60,6000/*8, 150*/);
//
//						for (vector<CPoint3D>::iterator its = point2.begin(); its != point2.end() - 1; ++its)
//						{
//							pDC->DrawLine(*its, *(its + 1));
//						}
//
//					}
//					
//
//				}
//				else /* if (((CArc*)m_ptArray.GetAt(i))->m_begin.x == 0 && ((CArc*)m_ptArray.GetAt(i))->m_end.x == 0)*///YOZƽ��
//				{
//					((CArc*)m_ptArray.GetAt(i))->PolyCalculateYZ(((CArc*)m_ptArray.GetAt(i))->m_begin, ((CArc*)m_ptArray.GetAt(i))->m_end,
//						((CArc*)m_ptArray.GetAt(i))->m_Tudu);
//					
//
//					if (((CArc*)m_ptArray.GetAt(i))->m_Tudu < 0)//˳ʱ��
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawSArcYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//					else//��ʱ��
//					{
//						((CArc*)m_ptArray.GetAt(i))->PolyDrawNArcYZ(((CArc*)m_ptArray.GetAt(i))->m_center, ((CArc*)m_ptArray.GetAt(i))->m_begin_angle,
//							((CArc*)m_ptArray.GetAt(i))->m_end_angle, 0.0001, ((CArc*)m_ptArray.GetAt(i))->m_radio);
//					}
//				}
//			}
//		}
//	}
//}

//void CSplitToDoc::OnBnClickedButton1()
//{
//	polygeon.DoModal();
//}

//����ӹ�����Ӧ
void CSplitToDoc::OnShowRoughCut()
{
	if (m_ShowSideRoughCut)
		m_ShowSideRoughCut = FALSE;
	else
	{
		m_ShowSideRoughCut = TRUE;
		tool.DeletePointOutOfBox();
	}
}


void CSplitToDoc::OnShowPiece()
{
	if (m_ShowSidePiece)
		m_ShowSidePiece = FALSE;
	else
		m_ShowSidePiece = TRUE;
       // UpdateAllViews(NULL);
}


void CSplitToDoc::OnShowRough()
{
	    if (m_ShowSideRough)
	        m_ShowSideRough = FALSE;
		else
	    {
	       m_ShowSideRough = TRUE;
			tool.RoughInit();
		}
	//UpdateAllViews(NULL);
}


void CSplitToDoc::OnShowSide()
{
	if (m_ShowSide)
		m_ShowSide = FALSE;
	else
		m_ShowSide = TRUE;
}


void CSplitToDoc::OnShowFinish()
{
	if (m_ShowSideFinish)
		m_ShowSideFinish = FALSE;
	else
	{
		m_ShowSideFinish = TRUE;
		tool.InitSideFinish();
	}
}

void CSplitToDoc::OnShowRoughLeft()
{
	if (m_ShowSideRoughLeft)
		m_ShowSideRoughLeft = FALSE;
	else
	{
		m_ShowSideRoughLeft = TRUE;
		tool.InitSideRoughLeft();
	}
}

void CSplitToDoc::OnBnClickedBeginSimulation()//���ڿ��ƴּӹ��ķ���
{


	CView* pView;
	POSITION pos =GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		if (!pView->IsKindOf(RUNTIME_CLASS(CGraphic)));
		break;
	}
	CGraphic* pGraphicView = (CGraphic*)GetNextView(pos);


	if (m_IsBeginSimulation)
	{
		m_IsBeginSimulation = FALSE;
		pGraphicView->mm_Timer.KillTimer();
		pGraphicView->pSplitView->m_HorizonScroll.SetScrollPos(50);//���½��ؼ���Ϊ50
		
	}
	else
	{
		m_IsBeginSimulation = TRUE;
		pGraphicView->mm_Timer.CreateTimer((DWORD)pGraphicView,20, pGraphicView->TimerCallback);
		
	}
	UpdateAllViews(NULL);
}


void CSplitToDoc::OnBnClickedBeginFinishSimulation()//���ڿ��ƾ��ӹ��ķ���
{
	
	CView* pView;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		if (!pView->IsKindOf(RUNTIME_CLASS(CGraphic)));
		break;
	}
	CGraphic* pGraphicView = (CGraphic*)GetNextView(pos);

	if (m_IsBeginFinishSimulation)
	{
		m_IsBeginFinishSimulation = FALSE;
		pGraphicView->mm_TimerFinish.KillTimer();
		pGraphicView->pSplitView->m_HorizonScroll.SetScrollPos(50);//���½��ؼ���Ϊ50

	}
	else
	{
		m_IsBeginFinishSimulation = TRUE;
		pGraphicView->mm_TimerFinish.CreateTimer((DWORD)pGraphicView, 10, pGraphicView->TimerCallbackFinish);

	}
	UpdateAllViews(NULL);
}

//��ת�ӹ�
void CSplitToDoc::OnShowRotate()
{
	if (m_ShowRotate)
		m_ShowRotate = FALSE;
	else
		m_ShowRotate = TRUE;
}


void CSplitToDoc::OnRoughRotate()
{
	if (m_ShowRotateRough)
		m_ShowRotateRough = FALSE;
	else
	{
		m_ShowRotateRough = TRUE;
		tool.InitRotateRough();
	}
}


void CSplitToDoc::OnShowRotateWorkBlank()
{
	if (m_ShowRotateWorkBlank)
		m_ShowRotateWorkBlank = FALSE;
	else
	{
		m_ShowRotateWorkBlank = TRUE;
		tool.InitRotateWorkBlank();
	}
}


void CSplitToDoc::OnShowRotateCutRough()
{
	if (m_ShowRotateRoughCut)
		m_ShowRotateRoughCut = FALSE;
	else
	{
		m_ShowRotateRoughCut = TRUE;
		tool.InitRotateRoughCut();
	}
}


void CSplitToDoc::OnShowRotateFinish()
{
	if (m_ShowRotateFinish)
		m_ShowRotateFinish = FALSE;
	else
	{
		m_ShowRotateFinish = TRUE;
		tool.InitRotateFinish();
	}
}

//˫����ӹ���Ӧ
void CSplitToDoc::OnShowArc()
{
	if (m_ShowArc)
		m_ShowArc = FALSE;
	else
		m_ShowArc = TRUE;
}


void CSplitToDoc::OnShowArcRough()
{
	if (m_ShowArcRough)
		m_ShowArcRough = FALSE;
	else
	{
		m_ShowArcRough = TRUE;
		tool.RenderRoughArcInit();
	}
}


void CSplitToDoc::OnShowArcWorkBlank()
{
	if (m_ShowArcWorkBlank)
		m_ShowArcWorkBlank = FALSE;
	else
	{
		m_ShowArcWorkBlank = TRUE;
		
	}
}


void CSplitToDoc::OnShowArcRoughAfterDelete()
{
	if (m_ShowArcRoughAfterCut)
		m_ShowArcRoughAfterCut = FALSE;
	else
	{
		m_ShowArcRoughAfterCut = TRUE;
		tool.RenderArcRoughCutInit();
	}
}


void CSplitToDoc::OnShowArcRoughLeft()
{
	if (m_ShowArcRoughLeft)
		m_ShowArcRoughLeft = FALSE;
	else
	{
		m_ShowArcRoughLeft = TRUE;
		tool.RenderArcRoughLeftInit();
	}
}


void CSplitToDoc::On32830()//��ʾ˫���澫�ӹ�·��ʾ��ͼ
{
	if (m_ShowArcFinish)
		m_ShowArcFinish = FALSE;
	else
	{
		m_ShowArcFinish = TRUE;
		tool.RenderArcFinishInit();
	}
}

//�����ӹ���Ӧ
void CSplitToDoc::OnShowLineProcess()
{
	if (m_ShowLine)
	{
		m_ShowLine = FALSE;
	}
	else
	{
		m_ShowLine = TRUE;
	}
}


void CSplitToDoc::OnShowLineRough()
{
	if (m_ShowLineRough)
	{
		m_ShowLineRough = FALSE;
	}
	else
	{
		m_ShowLineRough = TRUE;
		tool.LineRoughRenderInit();

	}
}


void CSplitToDoc::OnShowLineWorkBlank()
{
	if (m_ShowLineWorkBlank)
		m_ShowLineWorkBlank = FALSE;
	else
	{
		m_ShowLineWorkBlank = TRUE;
	}
}


//void CSplitToDoc::OnShowLineRoughCut()
//{
//	
//}


void CSplitToDoc::OnShowLineRoughLeft()
{
	if (m_ShowLineRoughLeft)
	{
		m_ShowLineRoughLeft = FALSE;
	}
	else
	{
		m_ShowLineRoughLeft = TRUE;
		tool.LineRoughLeftRenderInit();
	}
}


void CSplitToDoc::OnShowLineFinish()
{
	if (m_ShowLineFinish)
	{
		m_ShowLineFinish = FALSE;
	}
	else
	{
		m_ShowLineFinish = TRUE;
		tool.LineFinishRenderInit();
	}
}


void CSplitToDoc::OnShowOrthgonal()
{
	if (m_ShowOrthgonal)
		m_ShowOrthgonal = FALSE;
	else
		m_ShowOrthgonal = TRUE;
}


void CSplitToDoc::OnShowOrthgonalCutting()
{
	if (m_ShowOrthgonalCutting)
	{
		m_ShowOrthgonalCutting = FALSE;
	}
	else
	{
		m_ShowOrthgonalCutting = TRUE;
		tool.RenderOrthgonalCuttingPathInit();
	}
}


void CSplitToDoc::OnShowOrthgonalWorkBlank()
{
	if (m_ShowOrthgonalWorkBlank)
		m_ShowOrthgonalWorkBlank = FALSE;
	else
		m_ShowOrthgonalWorkBlank = TRUE;
}


void CSplitToDoc::OnShowPolygeon()
{
	if (m_ShowPolygeon)
		m_ShowPolygeon = FALSE;
	else
		m_ShowPolygeon = TRUE;
	
}


void CSplitToDoc::OnShowPolygeonWorkBlank()
{
	if (m_ShowPolygeonWorkBlank)
		m_ShowPolygeonWorkBlank = FALSE;
	else
		m_ShowPolygeonWorkBlank = TRUE;
}


void CSplitToDoc::OnShowPolygeonCutting()
{
	if (m_ShowPolygeonCuttingPath)
	{
		m_ShowPolygeonCuttingPath = FALSE;
	}
	else
	{
		m_ShowPolygeonCuttingPath = TRUE;
		tool.RenderPolygeonCuttingPathInit();
	}
}

//̨���ӹ�
//��ʾ����ʾ��ͼ
void CSplitToDoc::OnShowBoard()
{
	if (m_ShowBoard)
	{
		m_ShowBoard = FALSE;
	}
	else
	{
		m_ShowBoard = TRUE;
	}
}


//��ʾë��ʾ��ͼ
void CSplitToDoc::OnShowBoardWorkBlank()
{
	
	if (m_ShowBoardWorkBlank)
	{
		m_ShowBoardWorkBlank = FALSE;
	}
	else
	{
		m_ShowBoardWorkBlank = TRUE;
	}
}

//��ʾ�ڲ��Ƭ��·�켣
void CSplitToDoc::OnShowBoardInSawPath()
{
	if (m_ShowBoardInSawPath)
	{
		m_ShowBoardInSawPath = FALSE;
	}
	else
	{
		m_ShowBoardInSawPath = TRUE;
	}
}

//��ʾ�ڲ�ϳ����·�켣
void CSplitToDoc::OnShowBoardInMillPath()
{
	if (m_ShowBoardInMillPath)
	{
		m_ShowBoardInMillPath = FALSE;
	}
	else
	{
		m_ShowBoardInMillPath = TRUE;
	}
}


//��ʾ��൶·�켣ƫ��ʾ��ͼ
void CSplitToDoc::OnShowBoardOutOffset()
{
	if (m_ShowBoardOutPath)
	{
		m_ShowBoardOutPath = FALSE;
	}
	else
	{
		m_ShowBoardOutPath = TRUE;
	}
	
}

//��ʾ��൶·�켣�ü���ʾ��ͼ
void CSplitToDoc::OnShowBoardOutCutting()
{
	if (m_ShowBoardOutCutPath)
	{
		m_ShowBoardOutCutPath = FALSE;
	}
	else
	{
		m_ShowBoardOutCutPath = TRUE;
	}
}

//�������
void CSplitToDoc::OnDelData()
{
	CUtils::ClearAllData();
	ClearFlags();
	UpdateAllViews(NULL);
}

//��ձ��
void CSplitToDoc::ClearFlags()
{
	//CSplitToDoc();
	
	//����μӹ�
	m_ShowPolygeon = TRUE;;
	m_ShowPolygeonCuttingPath=FALSE;
	m_ShowPolygeonWorkBlank=FALSE;

	//�����ӹ�
	m_ShowOrthgonal=TRUE;
	m_ShowOrthgonalCutting=FALSE;
	m_ShowOrthgonalWorkBlank=FALSE;

	//�����ӹ�
	m_ShowLine=TRUE;//��ʾ����
	m_ShowLineRough=FALSE;//��ʾ�ּӹ��켣
	m_ShowLineWorkBlank = FALSE;//��ʾë��
	m_ShowLineRoughCut = FALSE;//��ʾ�ü���ּӹ��켣
	m_ShowLineRoughLeft = FALSE;//��ʾ�ּӹ�����
	m_ShowLineFinish = FALSE;//��ʾ���ӹ��켣

	//��ת�ӹ�
	m_ShowRotate=TRUE;//��ʾ����ʾ��ͼ
	m_ShowRotateRough=FALSE;//��ʾ�ּӹ��켣ʾ��ͼ
	m_ShowRotateWorkBlank = FALSE;//��ʾë��
	m_ShowRotateRoughCut = FALSE;//��ʾ�ּӹ��켣�ü�ʾ��ͼ
	m_ShowRotateFinish = FALSE;//��ʾ���ӹ��켣ʾ��ͼ

	//����ӹ�
	m_ShowSide=TRUE;
	m_ShowSidePiece=FALSE;
	m_ShowSideRough = FALSE;
	m_ShowSideRoughCut = FALSE;
	m_ShowSideRoughLeft = FALSE;//�����ж���ʾ�ּӹ�����
	m_ShowSideFinish = FALSE;//�����ж���ʾ����ӹ����ӹ�·��

	//˫����ӹ�
	m_ShowArc=TRUE;
	m_ShowArcRough=FALSE;
	m_ShowArcWorkBlank = FALSE;
	m_ShowArcRoughAfterCut = FALSE;
	m_ShowArcRoughLeft = FALSE;
	m_ShowArcFinish = FALSE;

	//̨���ӹ�
	m_ShowBoard=TRUE;
	m_ShowBoardWorkBlank=FALSE;

	m_ShowBoardInSawPath = FALSE;
	m_ShowBoardInMillPath = FALSE;

	m_ShowBoardOutPath = FALSE;
	m_ShowBoardOutCutPath = FALSE;

}