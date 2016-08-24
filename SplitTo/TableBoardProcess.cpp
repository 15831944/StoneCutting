#include "stdafx.h"
#include "TableBoardProcess.h"
//����̨���ӹ���C++��
#include"Utils.h"

CTableBoardProcess* CTableBoardProcess::m_TableProcess = NULL;

CTableBoardProcess::CTableBoardProcess()
{
	//����git
	m_ptBoardArray = NULL;
	m_innerArray = NULL;
	m_outArray = NULL;
	m_ExtendLength = 200;
	m_TotalSize = 0;
	m_PerDownDis = 0.0;

}


CTableBoardProcess::~CTableBoardProcess()
{
	if (m_ptBoardArray != NULL)
		delete m_ptBoardArray;
	if (m_innerArray != NULL)
		delete m_innerArray;
	if (m_outArray != NULL)
		delete m_outArray;
}


void CTableBoardProcess::RenderTableBoard(COpenGLDC* pDC)
{
	/*
	pDC->SetMaterialColor(RGB(255, 0, 0));
	DrawDIY(m_innerArray, pDC);
	pDC->SetMaterialColor(RGB(100, 100, 100));
	DrawDIY(m_outArray, pDC);
	pDC->SetMaterialColor(RGB(200,100,150));
	DrawDIY(Change_To_Array(m_CutData), pDC);
	*/

	/*
	for (elements it : m_CutData)
	{
		//��ֱ�߽��в���
		if (it.flag == 1)
		{
			glPointSize(5);
			pDC->DrawPoint(it.begin);
			pDC->DrawPoint(it.end);
		}
	}*/

	DrawDIYFromPt(m_InnerModelPoints, pDC);
	DrawDIYFromPt(m_OuterModelPoints, pDC);
	//RenderTableBlank(pDC);
	
}


void CTableBoardProcess::DrawDIY(CPtrArray* array, COpenGLDC* pDC)
{
	if (array != NULL)
	{
		for (int i = 0; i != array->GetSize(); i++)
		{
			if (((CLine*)array->GetAt(i))->flag == 1)
			{
				pDC->DrawLine(((CLine*)array->GetAt(i))->m_begin, ((CLine*)array->GetAt(i))->m_end);
			}
			else if (((CArc*)array->GetAt(i))->flag == 2)
			{
				if (((CArc*)array->GetAt(i))->m_Tudu == 0)//��ͨԲ��
				{
					((CArc*)array->GetAt(i))->GLDrawArc(((CArc*)array->GetAt(i))->m_center, ((CArc*)array->GetAt(i))->m_begin_angle,
						((CArc*)array->GetAt(i))->m_end_angle, 0.0001, ((CArc*)array->GetAt(i))->m_radio, *array, i);
				}
				else//���߶�Բ��
				{
					((CArc*)array->GetAt(i))->PolyCalculate(((CArc*)array->GetAt(i))->m_begin, ((CArc*)array->GetAt(i))->m_end,
						((CArc*)array->GetAt(i))->m_Tudu);
					if (((CArc*)array->GetAt(i))->m_Tudu > 0)//��ʱ��
					{
						((CArc*)array->GetAt(i))->PolyDrawNArc(((CArc*)array->GetAt(i))->m_center, ((CArc*)array->GetAt(i))->m_begin_angle,
							((CArc*)array->GetAt(i))->m_end_angle, 0.0001, ((CArc*)array->GetAt(i))->m_radio);
					}
					else//˳ʱ��
					{
						((CArc*)array->GetAt(i))->PolyDrawSArc(((CArc*)array->GetAt(i))->m_center, ((CArc*)array->GetAt(i))->m_begin_angle,
							((CArc*)array->GetAt(i))->m_end_angle, 0.0001, ((CArc*)array->GetAt(i))->m_radio);
					}

				}
			}
			else if (((CCircle*)array->GetAt(i))->flag == 3)
			{
				((CCircle*)array->GetAt(i))->GLDrawCircle(((CCircle*)array->GetAt(i))->m_center, ((CCircle*)array->GetAt(i))->m_radio);
			}

		}
	}
}

void CTableBoardProcess::DrawDIYFromPt(vector<vector<CPoint3D>> data, COpenGLDC* pDC)
{
	for (vector<vector<CPoint3D>>::iterator it = data.begin(); it != data.end(); ++it)
	{
		for (vector<CPoint3D>::iterator its = it->begin(); its != it->end() - 1; ++its)
		{
			pDC->DrawLine(*its, *(its + 1));
		}
	}
}

void CTableBoardProcess::DrawDIYFromPt(vector<vector<vector<vector<CPoint3D>>>> data, COpenGLDC* pDC)
{
	for (vector<vector<vector<vector<CPoint3D>>>>::iterator it = data.begin(); it != data.end(); ++it)
	{
		for (vector<vector<vector<CPoint3D>>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			for (vector<vector<CPoint3D>>::iterator itss = its->begin(); itss != its->end(); ++itss)
			{
				for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end() - 1; ++itsss)
				{
					pDC->DrawLine(*itsss, *(itsss + 1));
				}
			}
		}
	}
}
void CTableBoardProcess::DrawDIYFromOffset(vector<OffsetPoint> data, COpenGLDC* pDC)
{
	for (OffsetPoint it : data)
	{
		pDC->DrawLine(it.begin, it.end);
	}
}

void CTableBoardProcess::DrawOutRetractLine(vector<vector<vector<CPoint3D>>> data, COpenGLDC* pDC)
{
	pDC->SetMaterialColor(RGB(72, 61,139));//�������
	/*�����Ϸŵ�һ�������﷽�����*/
	vector<vector<vector<elements>>> m_SumRetractLines;

	vector<vector<elements>> m_RetractBLines;//��ʼ����˵��߼���
	vector<vector<elements>> m_RetractELines;//��ֹ�㴦�˵��߼���

	for (vector<vector<vector<CPoint3D>>>::iterator it = data.begin(); it != data.end(); ++it)
	{
		vector<elements> mm_RetractBLines;
		vector<elements> mm_RetractELines;
		for (vector<vector<CPoint3D>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			elements e1, e2;

			CVector3D m_LineDirection =*(its->begin()+1)-*(its->begin());
			CPoint3D m_RetractBegin = *(its->begin()) - m_LineDirection.GetNormal() * m_ExtendLength;//��������200mm
			e1.flag = 1;
			e1.begin = m_RetractBegin;
			e1.end = *(its->begin());
			mm_RetractBLines.push_back(e1);
			pDC->DrawLine(m_RetractBegin, *(its->begin()));

			m_LineDirection = *(its->end()-1) - *(its->end()-2);
			CPoint3D m_RetractEnd = *(its->end() - 1) + m_LineDirection.GetNormal() * m_ExtendLength;
			e2.flag = 2;
			e2.begin = *(its->end() - 1);
			e2.end = m_RetractEnd;
			mm_RetractELines.push_back(e2);

			pDC->DrawLine(m_RetractEnd, *(its->end()-1));
		}
		m_RetractBLines.push_back(mm_RetractBLines);
		m_RetractELines.push_back(mm_RetractELines);
	}

	m_SumRetractLines.push_back(m_RetractBLines);
	m_SumRetractLines.push_back(m_RetractELines);

	/*
	for (vector<vector<elements>>::iterator it = m_RetractBLines.begin(); it != m_RetractBLines.end(); ++it)
	{
		for (int i = 0; i != it->size(); ++i)
		{
			if (i% 2 == 1)//�����㣬����������
			{
				if (i != it->size() - 1)
				{
					pDC->DrawLine(((*it)[i]).begin, ((*it)[i + 1]).begin);
				}
			}
		}
	}
	for (vector<vector<elements>>::iterator it = m_RetractELines.begin(); it != m_RetractELines.end(); ++it)
	{
		for (int i = 0; i != it->size(); ++i)
		{
			if (i % 2 == 0)//ż���㣬�յ������յ�
			{
				if (i != it->size() - 1)
				{
					pDC->DrawLine(((*it)[i]).end, ((*it)[i + 1]).end);
				}
			}
		}
	}*/
	for (vector<vector<vector<elements>>>::iterator it = m_SumRetractLines.begin(); it != m_SumRetractLines.end(); ++it)
	{
		if (it == m_SumRetractLines.begin())//���������߲���
		{
			for (vector<vector<elements>>::iterator its = it->begin(); its != it->end(); ++its)
			{
				for (int i = 0; i != its->size(); ++i)
				{
					if (i % 2 == 1)//�����㣬����������
					{
						if (i != its->size() - 1)
						{
							pDC->SetMaterialColor(RGB(72, 61, 139));//�������
							pDC->DrawLine(((*its)[i]).begin, ((*its)[i + 1]).begin);
						}
						else//���һ���������������ʼ�����
						{
							//��������
							//�����һ�㣬��������һ�����
							pDC->SetMaterialColor(RGB(255, 255, 255));
							if (its != it->end()-1)
							{
								pDC->DrawStippleLine(((*its)[i]).begin, ((*(its+1))[0]).begin);
							}
							else
							{
								//���û����һ��
								pDC->DrawStippleLine(((*its)[i]).begin, CPoint3D(((*its)[i]).begin.x, 
									                 ((*its)[i]).begin.y, m_Board_Heigh*2));
							}
						}
					}
					
				}
			}
		}
		else if (it == m_SumRetractLines.end() - 1)//�յ�������߲���
		{
			//��¼����
			int m_ZCount = 0;
			for (vector<vector<elements>>::iterator its = it->begin(); its != it->end(); ++its)
			{	
				for (int i = 0; i != its->size(); ++i)
				{
					if (i % 2 == 0)//ż���㣬�յ������յ�
					{
						if (i != its->size() - 1)
						{
							pDC->SetMaterialColor(RGB(72, 61, 139));//�������
							pDC->DrawLine(((*its)[i]).end, ((*its)[i + 1]).end);
						}
						else//���һ����ż���㣬������һ������������
						{
							pDC->SetMaterialColor(RGB(255, 255, 255));
							if (its != it->end() - 1)
							{
								//pDC->DrawStippleLine(((*its)[i]).end, ((*(its + 1))[0]).end);
								pDC->DrawStippleLine(((*its)[i]).end, (*(it-1))[m_ZCount+1].begin()->begin);
							}
							else
							{

								pDC->DrawStippleLine(((*its)[i]).end, CPoint3D(((*its)[i]).end.x,
									((*its)[i]).end.y, m_Board_Heigh * 2));
							}
						}
					}
				}
				m_ZCount += 1;
			}

		}
		
	}

}
void CTableBoardProcess::DrawInSawRetractLine(vector<vector<vector<vector<CPoint3D>>>> data, COpenGLDC* pDC)
{
	vector<vector<vector<vector<elements>>>> m_InSawRetractElements;

	for (vector<vector<vector<vector<CPoint3D>>>>::iterator it = data.begin(); it != data.end(); ++it)//��һ��ľ�Ƭ�켣
	{
		vector<vector<vector<elements>>> m_SawElements;

		vector<vector<elements>> mm_SawCutElements;//��
		vector<vector<elements>> mm_SawLeaveElements;//��

		for (vector<vector<vector<CPoint3D>>>::iterator its = it->begin(); its != it->end(); ++its)//��һ�����һ��ľ�Ƭ�켣
		{
			

			//vector<vector<elements>> mm_SawCutElements;//��
			//vector<vector<elements>> mm_SawLeaveElements;//��
			CVector3D m_Linedirection = *(its->begin()->end() - 1) - *(its->begin()->begin());//ֱ�ߵķ���
			CVector3D m_NRotateLine = CVector3D(m_Linedirection.dy, -m_Linedirection.dx, 0).GetNormal();//��ʱ����ת��ĵ�λ����
			
			vector<elements> mmm_SawCutElements;
			vector<elements> mmm_SawLeaveElements;
			for (vector<vector<CPoint3D>>::iterator itss = its->begin(); itss != its->end(); ++itss)
			{
				elements e1,e2;
				e1.flag = 1;
				e1.begin = *(itss->begin()) + m_NRotateLine*m_ExtendLength;//��Ȼ200mm
				e1.end = *(itss->begin());
				e2.flag = 1;
				e2.begin = *(itss->end()-1);
				e2.end = *(itss->end() - 1) + m_NRotateLine * m_ExtendLength;
				mmm_SawCutElements.push_back(e1);
				mmm_SawLeaveElements.push_back(e2);
			}

			mm_SawCutElements.push_back(mmm_SawCutElements);
			mm_SawLeaveElements.push_back(mmm_SawLeaveElements);

			//m_SawElements.push_back(mm_SawCutElements);
			//m_SawElements.push_back(mm_SawLeaveElements);

			
		}

		m_SawElements.push_back(mm_SawCutElements);
		m_SawElements.push_back(mm_SawLeaveElements);

		m_InSawRetractElements.push_back(m_SawElements);
	}
	int j = 0;
	for (vector<vector<vector<vector<elements>>>>::iterator it = m_InSawRetractElements.begin(); it != m_InSawRetractElements.end(); ++it)//��һ�����ֵ�������
	{
		for (vector<vector<vector<elements>>>::iterator its = it->begin(); its != it->end(); ++its)//�������˵�
		{
			int i = 0;
			for (vector<vector<elements>>::iterator itss = its->begin(); itss != its->end(); ++itss)//��һ��
			{
				BOOL m_LineDirection = TRUE;
				
				for (vector<elements>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)//��һ�߶�
				{
					pDC->SetMaterialColor(RGB(72, 61, 139));//�������
					pDC->DrawLine(itsss->begin, itsss->end);
					if (its == it->begin())
					{
						if (!m_LineDirection)//��������
						{
							if (itsss != itss->end() - 1)//�����һ���߶�
							{
								pDC->DrawLine(itsss->begin, (itsss + 1)->begin);
							}
							else//���һ���߶Σ���Ҫ���ӵ���һ���ֵĽ������ֵĵ�һ����ʼ��
							{
								pDC->SetMaterialColor(RGB(255, 255, 255));
								if (itss == its->end() - 1)//���һ��Ľ�����
								{
									if (it != m_InSawRetractElements.end() - 1)//�����һ���ֵĽ�����
									{
										pDC->DrawStippleLine(itsss->begin, (it + 1)->begin()->begin()->begin()->begin);
									}
									else//���һ���ֵ����һ��
									{
										pDC->DrawStippleLine(itsss->begin, CPoint3D(itsss->begin.x,itsss->begin.y,m_Board_Heigh*2));
									}
								}
								else
								{
									pDC->DrawStippleLine(itsss->begin, (itss + 1)->begin()->begin);
								}
								
							}
						}
					}
					else
					{
						if (m_LineDirection)//�˵�����
						{
							if (itsss != itss->end() - 1)
							{
								pDC->DrawLine(itsss->end, (itsss + 1)->end);
							}
							else
							{
								pDC->SetMaterialColor(RGB(255, 255, 255));
								if (itss == its->end() - 1)
								{		
									if (it != m_InSawRetractElements.end() - 1)
									{
										pDC->DrawStippleLine(itsss->end, (it + 1)->begin()->begin()->begin()->begin);
									}
									else//���һ���ֵ����һ��
									{
										pDC->DrawStippleLine(itsss->end, CPoint3D(itsss->end.x, itsss->end.y, m_Board_Heigh * 2));
									}
								}
								else
								{
									pDC->DrawStippleLine(itsss->end, ((m_InSawRetractElements.begin()+j)->begin()->begin()+i+1)->begin()->begin);
								}
								
							}
						}
					}
					m_LineDirection = !m_LineDirection;
				}
				i = i + 1;
			}
			
		}
		j += 1;
	}

}
void CTableBoardProcess::DrawInMillRetractLine(vector<vector<vector<vector<CPoint3D>>>> data, COpenGLDC* pDC)
{
	for (vector<vector<vector<vector<CPoint3D>>>>::iterator it = data.begin(); it != data.end(); ++it)//��һ����
	{
		for (vector<vector<vector<CPoint3D>>>::iterator its = it->begin(); its != it->end(); ++its)//��һ��
		{
			for (vector<vector<CPoint3D>>::iterator itss = its->begin(); itss != its->end(); ++itss)//��һ�߶�
			{
				pDC->SetMaterialColor(RGB(255, 255, 255));
				if (its == it->begin())//ÿһ���һ���߶�
				{
					pDC->DrawStippleLine(CPoint3D(itss->begin()->x, itss->begin()->y, m_Board_Heigh * 2), 
						CPoint3D(itss->begin()->x, itss->begin()->y, m_Board_Heigh));

				}
				if (itss == its->end() - 1)//ÿһ������һ���߶�,������һ��ĵ�һ���߶�
				{
					if (its !=it->end() - 1)
					{
						pDC->DrawStippleLine(*(itss->begin()),*((its+1)->begin()->begin()));
					}
					else
					{
						if (it != data.end() - 1)//�����һ��
						{
							pDC->DrawStippleLine(*(itss->begin()),
								CPoint3D((it + 1)->begin()->begin()->begin()->x, (it + 1)->begin()->begin()->begin()->y, m_Board_Heigh * 2));
						}
						else//���һ��
						{
							pDC->DrawStippleLine(*(itss->begin()),
								CPoint3D((itss->begin())->x, (itss->begin())->y, m_Board_Heigh * 2));
						}
					}
					
				}
			}
		}
	}
}
CTableBoardProcess* CTableBoardProcess::GetTableProcessInstance()
{
	if (m_TableProcess == NULL)//�жϵ�һ�ε���
	{
		m_TableProcess = new CTableBoardProcess();
	}
	return m_TableProcess;
}


//�ڶԻ������Ѿ��ж�input�������Ƿ�Ϊ�գ��������������ж�
void CTableBoardProcess::InitData(CPtrArray* input)
{
	m_ptBoardArray = input;

	ClearData();

	m_ArrayList = InitTableModel(m_ptBoardArray, m_Board_Heigh,2);

	m_ModelPoints = GetPoints(m_ArrayList, m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);

	if (m_SourceData.size())
		m_SourceData.clear();
	m_SourceData = CalculateData(input);
	if (m_SourceData.size())
	{
		m_ProfileData = RegonizeProfile(m_SourceData);

		//��Ҫ��vector<elements>ת��CPtrArray*�ĺ���
		m_InArrayList = InitTableModel(Change_To_Array(m_ProfileData[1]), m_Board_Heigh,2);
		m_OutArrayList = InitTableModel(Change_To_Array(m_ProfileData[0]), m_Board_Heigh,2);

		m_InnerModelPoints = GetPoints(m_InArrayList, m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
		m_OuterModelPoints = GetPoints(m_OutArrayList, m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
		//��ȡƫ�ú���ɢ����
		m_OuterBlankPoints = CoverOutsideProfToPoints(m_OutArrayList, 20, m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);

		//ֻ��Ҫ�����������д���
		m_CutData = ChangeSegments(m_ProfileData[1]);
	}

	InitTableBlank();
	InitTableOutPath();
	InitTableInPath();
	InitTableSimulationPoints(m_OutOffsetPoints, m_InOffsetSawPoints, m_InOffsetMillPoints);
	//��ʼ��NC����
	m_TableOutNCElements=InitTableOutNC(m_OutOffsetProfile);
	m_TableInSawNCElements=InitTableInSawNC(m_InOffsetSawProfile);
	m_TableInMillNCElements=InitTableInMillNC(m_InOffsetMillProfile);
}

void CTableBoardProcess::ClearData()
{
	vector<CPtrArray*>().swap(m_ArrayList);
	vector<CPtrArray*>().swap(m_InArrayList);
	vector<CPtrArray*>().swap(m_OutArrayList);

	vector<vector<CPoint3D>>().swap(m_ModelPoints);
	vector<vector<CPoint3D>>().swap(m_InnerModelPoints);
	vector<vector<CPoint3D>>().swap(m_OuterModelPoints);

	vector<vector<elements>>().swap(m_ProfileData);

	vector<elements>().swap(m_CutData);

	vector<vector<CPoint3D>>().swap(m_OuterBlankPoints);

	//�����������ë������
	vector<OffsetPoint>().swap(m_OuterBlankOffset);
	vector<OffsetPoint>().swap(m_InBlankOffset);
	vector<OffsetPoint>().swap(m_OuterBlankTopOffset);
	vector<OffsetPoint>().swap(m_InBlankTopOffset);

	//�����������ɢ��
	vector<vector<vector<CPoint3D>>>().swap(m_OutOffsetPoints);
	vector<vector<CPtrArray*>>().swap(m_OutOffsetProfile);

	//�����������ɢ��
	vector<vector<CPtrArray*>>().swap(m_inOffsetProfile);
	vector<vector<vector<CPoint3D>>>().swap(m_inOffsetPoints);

	vector<vector<vector<CPtrArray*>>>().swap(m_InOffsetSawProfile);
	vector<vector<vector<vector<CPoint3D>>>>().swap(m_InOffsetSawPoints);

	vector<vector<vector<CPtrArray*>>>().swap(m_InOffsetMillProfile);
	vector<vector<vector<vector<CPoint3D>>>>().swap(m_InOffsetMillPoints);

	//���NC����Ԫ��
	vector<vector<vector<elements>>>().swap(m_TableOutNCElements);
	vector<vector<vector<vector<elements>>>>().swap(m_TableInSawNCElements);
	vector<vector<vector<vector<elements>>>>().swap(m_TableInMillNCElements);
}

void CTableBoardProcess::ClearBoardArray()
{
	//��Ϊ��
	m_ptBoardArray = NULL;
}

vector<CPtrArray*> CTableBoardProcess::InitTableModel(CPtrArray* data,float high,float depth)
{
	vector<CPtrArray*> s;

	//ÿ���2mm
	//int fild =2;

	vector<float> PilesHeigh;
	while (high>0)
	{
		PilesHeigh.push_back(high);
		if (high <= depth)
		{
			PilesHeigh.push_back(0.0);
		}
		high -= depth;
	}
	
	/*
	for (float it : PilesHeigh)
	{
		//ָ�����ݸ��ƣ�
		CPtrArray& datas=*data;

		for (int i = 0; i < datas.GetSize(); ++i)
		{
			if (((CLine*)datas.GetAt(i))->flag == 1)
			{
				((CLine*)datas.GetAt(i))->m_begin.z = it;
				((CLine*)datas.GetAt(i))->m_end.z = it;
			}
			else if (((CArc*)datas.GetAt(i))->flag == 2)
			{
				((CArc*)datas.GetAt(i))->m_center.z = it;
				((CArc*)datas.GetAt(i))->m_begin.z = it;
				((CArc*)datas.GetAt(i))->m_end.z = it;
				
			}
		}
		s.push_back(&datas);
	}*/

	for (float it : PilesHeigh)
	{
		CPtrArray* newArray = new CPtrArray();
		for (int i = 0; i < data->GetSize(); ++i)
		{
			if (((CLine*)data->GetAt(i))->flag == 1)
			{
				CLine* pLine = new CLine();
				pLine->flag = ((CLine*)data->GetAt(i))->flag;
				pLine->m_begin = ((CLine*)data->GetAt(i))->m_begin;
				pLine->m_end = ((CLine*)data->GetAt(i))->m_end;
				pLine->m_end.z = it;
				pLine->m_begin.z = it;
				newArray->Add(pLine);
			}
			else if (((CArc*)data->GetAt(i))->flag == 2)
			{
				CArc* pArc = new CArc();
				pArc->m_center = ((CArc*)data->GetAt(i))->m_center;
				pArc->m_begin = ((CArc*)data->GetAt(i))->m_begin;
				pArc->m_end = ((CArc*)data->GetAt(i))->m_end;
				pArc->m_radio = ((CArc*)data->GetAt(i))->m_radio;
				pArc->m_begin_angle = ((CArc*)data->GetAt(i))->m_begin_angle;
				pArc->m_end_angle = ((CArc*)data->GetAt(i))->m_end_angle;

				pArc->m_Tudu = ((CArc*)data->GetAt(i))->m_Tudu;
				pArc->flag = ((CArc*)data->GetAt(i))->flag;
				pArc->m_Direction = ((CArc*)data->GetAt(i))->m_Direction;

				pArc->m_begin.z = it;
				pArc->m_center.z = it;
				pArc->m_end.z = it;

				newArray->Add(pArc);
			}
		}
		s.push_back(newArray);
	}
	return s;
}


vector<elements> CTableBoardProcess::CalculateData(CPtrArray* input)
{
	vector<elements> m_TempElements;

	if (input != NULL)
	{
		for (int i = 0; i != input->GetSize(); i++)
		{
			if (((CLine*)input->GetAt(i))->flag == 1)
			{
				elements e;
				e.begin = ((CLine*)input->GetAt(i))->m_begin;
				e.end = ((CLine*)input->GetAt(i))->m_end;
				m_TempElements.push_back(e);
			}
			else if (((CArc*)input->GetAt(i))->flag == 2)
			{
				elements e;
				if (((CArc*)input->GetAt(i))->m_Tudu == 0)//��ͨԲ��
				{
					((CArc*)input->GetAt(i))->Calculate(((CArc*)input->GetAt(i))->m_center, ((CArc*)input->GetAt(i))->m_radio,
						((CArc*)input->GetAt(i))->m_begin_angle, ((CArc*)input->GetAt(i))->m_end_angle, *input, i);
					e.tudu = 0;
				}
				else//���߶�Բ��
				{
					((CArc*)input->GetAt(i))->PolyCalculate(((CArc*)input->GetAt(i))->m_begin, ((CArc*)input->GetAt(i))->m_end,
						((CArc*)input->GetAt(i))->m_Tudu);
					e.tudu = ((CArc*)input->GetAt(i))->m_Tudu;
				}

				e.flag = 2;
				e.begin = ((CArc*)input->GetAt(i))->m_begin;
				e.end = ((CArc*)input->GetAt(i))->m_end;
				e.center = ((CArc*)input->GetAt(i))->m_center;
				e.radius = ((CArc*)input->GetAt(i))->m_radio;
				e.start_angle = ((CArc*)input->GetAt(i))->m_begin_angle;
				e.end_angle = ((CArc*)input->GetAt(i))->m_end_angle;
				m_TempElements.push_back(e);
			}
		

		}
	}

	return m_TempElements;
	
}

//�µĲ��������㼴��ת����ת����
vector<elements> CTableBoardProcess::New_CalculateData(CPtrArray* input)
{
	vector<elements> m_TempElements;

	if (input != NULL)
	{
		for (int i = 0; i != input->GetSize(); i++)
		{
			if (((CLine*)input->GetAt(i))->flag == 1)
			{
				elements e;
				e.begin = ((CLine*)input->GetAt(i))->m_begin;
				e.end = ((CLine*)input->GetAt(i))->m_end;
				m_TempElements.push_back(e);
			}
			else if (((CArc*)input->GetAt(i))->flag == 2)
			{
				elements e;
			
				e.tudu = ((CArc*)input->GetAt(i))->m_Tudu;

				e.flag = 2;
				e.begin = ((CArc*)input->GetAt(i))->m_begin;
				e.end = ((CArc*)input->GetAt(i))->m_end;
				e.center = ((CArc*)input->GetAt(i))->m_center;
				e.radius = ((CArc*)input->GetAt(i))->m_radio;
				e.start_angle = ((CArc*)input->GetAt(i))->m_begin_angle;
				e.end_angle = ((CArc*)input->GetAt(i))->m_end_angle;
				m_TempElements.push_back(e);
			}


		}
	}

	return m_TempElements;

}


//�ı��߶εĶ�����ֻ�ı�ֱ��
vector<elements> CTableBoardProcess::ChangeSegments(vector<elements> data)
{
	vector<elements> s;
	float d = 200;//������ǰ����ͼ��С������ߵ��ߵ�ֱ��������С��
	float ap = 10;

	for (elements it : data)
	{
		if (it.flag == 1)
		{
			//it.begin.x += 1200;
			//it.end.x += 1200;

			//vector<elements> temps = SeperateToThreeParts(it, d / 2, ap);
			//��ϳ���İ뾶��ʾ��Ƭ�İ뾶������10.
			vector<elements> temps = SeperateToThreeParts(it,10*m_MillToolDiamand/2, m_MillCutDepth_Vertical);
			for (elements its : temps)
			{
				s.push_back(its);
			}
		}
		else
		{
			//it.begin.x += 1200;
			//it.end.x += 1200;
			//it.center.x += 1200;
			s.push_back(it);
		}
	}

	return s;
}

//��ֱ�߸��ݾ�Ƭ�뾶��������Ƚ�ֱ�߷ֳ�����
vector<elements> CTableBoardProcess::SeperateToThreeParts(elements LineData , float Radius, float CutDepth)
{
	//ֻҪֱ�ߵ��������а뾶��С���������ɣ�
	vector<elements> s;

	//R-sqrt(R*R-(R-cut)*(R-cut))
	float LeftDis = Radius - sqrtf(pow(Radius, 2) - pow(Radius - CutDepth, 2));

	//ȷ��ֱ�ߵķ���
	CVector3D dir = CVector3D(LineData.end.x - LineData.begin.x, LineData.end.y - LineData.begin.y, 0);
	//��λ����
	CVector3D normal = dir.GetNormal();

	elements e1, e2, e3;
	e1.begin = LineData.begin;
	//e1.end = LineData.begin + normal*LeftDis;
	e1.end = LineData.begin + normal*Radius;
	s.push_back(e1);

	//e2.begin = LineData.begin + normal*LeftDis;
	//e2.end = LineData.end - normal*LeftDis;
	e2.begin = LineData.begin + normal*Radius;
	e2.end = LineData.end - normal*Radius;
	s.push_back(e2);

	//e3.begin = LineData.end - normal*LeftDis;
	e3.begin = LineData.end - normal*Radius;
	e3.end = LineData.end;
	s.push_back(e3);

	return s; 
}

//ʶ����������
vector<vector<elements>> CTableBoardProcess::RegonizeProfile(vector<elements> data)
{
	vector<vector<elements>> s;
	//���ֻ����ֻ��һ����������һ��������,����Ƕ���Ļ�������ͨ����������ĸ���������Ӧ�ĵ���.
	//Ĭ�����Ȼ����������ٻ��������������Ҫ���⻭�������Ҫ�����жϳߴ磬�ߴ�С�����ڣ��ߴ������⡣
	//�˴�δ�ӡ�
	vector<elements> tempS[2];
	int i = 0;

	if (data.size())
	{
		CVector3D dir = CVector3D(0, 0, 0);
	
		for (elements it : data)
		{
			dir += it.end - it.begin;
			if (dir.GetLength() <0.001)
			{
				tempS[i].push_back(it);

				//��ӵ�������
				s.push_back(tempS[i]);

				if (i<1)
					++i;
				//��������
				dir = CVector3D(0, 0, 0);

			}
			else
			{
				tempS[i].push_back(it);
			}

		}
	}

	//��Ϊ����Ҫ����Ҫ�ȼӹ��������ټӹ����������������洢��0λ�ã��������洢��1λ�á�
	for (int i = 0; i < s.size(); ++i)
	{
		if (i == 1)
		{
			m_innerArray = Change_To_Array(s[i]);

		}
		if (i == 0)
		{
			m_outArray = Change_To_Array(s[i]);
		}
	}


	return s;
}


CPtrArray* CTableBoardProcess::Change_To_Array(vector<elements> data)
{
	CPtrArray* tempArray = new CPtrArray();
	for (elements it : data)
	{
		if (it.flag == 1)
		{
			CLine* pLine = new CLine();
			pLine->flag = 1;
			pLine->m_begin = it.begin;
			pLine->m_end = it.end;
			tempArray->Add(pLine);

		}
		else if (it.flag == 2)
		{
			CArc* pArc = new CArc();

			it.flag = 2;
			pArc->m_center = it.center;
			pArc->m_radio = it.radius;
			pArc->m_begin_angle = it.start_angle;
			pArc->m_end_angle = it.end_angle;
			pArc->m_begin = it.begin;
			pArc->m_end = it.end;
			pArc->m_Tudu = it.tudu;//0�����ж�����ͨԲ�����Ƕ��߶�Բ�������߶�Բ�����������������ж�Բ����˳�档
			pArc->m_Direction = it.arc_direction;

			tempArray->Add(pArc);

		}
	}

	return tempArray;
}

elements CTableBoardProcess::Copy_Elements(elements data)
{
	elements tempElements;

	tempElements.begin = data.begin;
	tempElements.center = data.center;
	tempElements.end = data.end;
	tempElements.end_angle = data.end_angle;
	tempElements.flag = data.flag;
	tempElements.radius = data.radius;
	tempElements.start_angle = data.start_angle;
	tempElements.tudu = data.tudu;


	return tempElements;
}

vector<CPtrArray*> CTableBoardProcess::Copy_CPtrArrays(vector<CPtrArray*> data)
{
	vector<CPtrArray*> m_tempNewArrays;
	for (CPtrArray* it : data)
	{
		CPtrArray* m_tempNewArray = new CPtrArray();
		for (int i = 0; i != it->GetSize(); ++i)
		{
			if (((CLine*)it->GetAt(i))->flag == 1)
			{
				CLine* pLine = new CLine();
				pLine->flag = 1;
				pLine->m_begin = ((CLine*)it->GetAt(i))->m_begin;
				pLine->m_end = ((CLine*)it->GetAt(i))->m_end;

				m_tempNewArray->Add(pLine);

			}
			else if (((CArc*)it->GetAt(i))->flag == 2)
			{
				CArc* pArc = new CArc();

				pArc->flag = 2;
				pArc->m_center = ((CArc*)it->GetAt(i))->m_center;
				pArc->m_radio= ((CArc*)it->GetAt(i))->m_radio;
				pArc->m_begin_angle = ((CArc*)it->GetAt(i))->m_begin_angle;
				pArc->m_end_angle = ((CArc*)it->GetAt(i))->m_end_angle;
				pArc->m_begin = ((CArc*)it->GetAt(i))->m_begin;
				pArc->m_end = ((CArc*)it->GetAt(i))->m_end;
				pArc->m_Tudu = ((CArc*)it->GetAt(i))->m_Tudu;
				pArc->m_Direction = ((CArc*)it->GetAt(i))->m_Direction;

				m_tempNewArray->Add(pArc);

			}
		}
		m_tempNewArrays.push_back(m_tempNewArray);
	}
	return m_tempNewArrays;
}

//��ɢ��
vector<CPoint3D> CTableBoardProcess::ConverToPoints(CPtrArray* data, float F, float T)
{
	vector<CPoint3D> s;

	for (int i = 0; i != data->GetSize(); ++i)
	{
		if (((CLine*)data->GetAt(i))->flag == 1)
		{
			vector<CPoint3D> temps = this->LineDiscrete(((CLine*)data->GetAt(i))->m_begin,
												((CLine*)data->GetAt(i))->m_end,T, F);
			for (CPoint3D it : temps)
			{
				s.push_back(it);
			}
		}
		else if (((CArc*)data->GetAt(i))->flag == 2)
		{
			vector<CPoint3D> temps;

			if (((CArc*)data->GetAt(i))->m_Tudu == 0)
			{
				temps = this->ArcDiscrete(((CArc*)data->GetAt(i))->m_center, ((CArc*)data->GetAt(i))->m_radio,
					((CArc*)data->GetAt(i))->m_begin_angle, ((CArc*)data->GetAt(i))->m_end_angle, *data,i, T, F);
			}
			else
			{
				temps = this->PolyArcDiscrete(((CArc*)data->GetAt(i))->m_begin, ((CArc*)data->GetAt(i))->m_end, 
					                             ((CArc*)data->GetAt(i))->m_Tudu, T, F);
			}
			for (CPoint3D it : temps)
			{
				s.push_back(it);
			}
		}
	}



	return s;
}

vector<vector<CPoint3D>> CTableBoardProcess::GetPoints(vector<CPtrArray*> data, float F, float T)
{
	vector<vector<CPoint3D>> s;
	if (data.size())
	{
		for (CPtrArray* it : data)
		{
			vector<CPoint3D> temp = ConverToPoints(it,F,T);
			s.push_back(temp);
		}
	}
	return s;
}

vector<CPoint3D> CTableBoardProcess::GetPoints(CPtrArray* data, float F, float T)
{
	return ConverToPoints(data, F, T);
}

vector<vector<CPoint3D>> CTableBoardProcess::CoverOutsideProfToPoints(vector<CPtrArray*> data,float offset, float F, float T)
{
	vector<vector<CPoint3D>> s;
	this->SetFeedspeed(F);
	this->SetTime(T);
	for (CPtrArray* it : data)
	{
		vector<CPoint3D> ss;
		ss = OffsetAlgorithm(*it, it->GetSize() - 1, offset);
		for (CPoint3D& its : ss)
		{
			if (((CLine*)it->GetAt(0))->flag == 1)
			{
				its.z = ((CLine*)it->GetAt(0))->m_begin.z;
			}
			else if (((CArc*)it->GetAt(0))->flag ==2)
			{
				its.z = ((CArc*)it->GetAt(0))->m_center.z;
			}
		}
		s.push_back(ss);
	}
	return s;
}

vector<vector<CPoint3D>> CTableBoardProcess::CoverOutsideProfToPoints(vector<CPtrArray*> data, float F, float T)
{
	vector<vector<CPoint3D>> s;
	for (CPtrArray* it : data)
	{
		vector<CPoint3D> ss;
		//ss = OffsetAlgorithm(*it, it->GetSize() - 1, offset);
		for (int i = 0; i!=it->GetSize(); ++i)
		{
			vector<CPoint3D> sss;
			if (((CLine*)it->GetAt(i))->flag == 1)
			{
				sss = LineDiscrete(((CLine*)it->GetAt(i))->m_begin, ((CLine*)it->GetAt(i))->m_end, T, F);
			}
			else if (((CArc*)it->GetAt(i))->flag == 2)
			{
				sss = ((CArc*)it->GetAt(i))->ArcTDMInterpolation(((CArc*)it->GetAt(i))->m_center, ((CArc*)it->GetAt(i))->m_radio,
					((CArc*)it->GetAt(i))->m_Direction, ((CArc*)it->GetAt(i))->m_begin, ((CArc*)it->GetAt(i))->m_end, T, F);
			}
			for (CPoint3D its : sss)
			{
				ss.push_back(its);
			}
		}

		for (CPoint3D& its : ss)
		{
			if (((CLine*)it->GetAt(0))->flag == 1)
			{
				its.z = ((CLine*)it->GetAt(0))->m_begin.z;
			}
			else if (((CArc*)it->GetAt(0))->flag == 2)
			{
				its.z = ((CArc*)it->GetAt(0))->m_center.z;
			}
		}
		s.push_back(ss);
	}
	return s;
}

//ë����ʾ
void CTableBoardProcess::InitTableBlank()
{
	if (m_ProfileData.size())
	{
		vector<elements> m_tempElements;//��ȡ��������Ԫ����Ϣ
		for (elements it : m_ProfileData[0])
		{
			if (it.flag == 1)
			{
				m_tempElements.push_back(it);
			}
		}

		vector<elements> m_tempElementss;//��ȡ��������Ԫ����Ϣ
		for (elements it : m_ProfileData[1])
		{
			if (it.flag == 1)
			{
				m_tempElementss.push_back(it);
			}
		}


		m_outOnlyLineArray = Change_To_Array(m_tempElements);
		m_inOnlyLineArray = Change_To_Array(m_tempElementss);

		/*
		vector<vector<CPoint3D>>().swap(m_OuterBlankPoints);
		m_OuterBlankPoints.push_back(OffsetAlgorithm(*m_outOnlyLineArray, m_outOnlyLineArray->GetSize() - 1, 30));*/
		m_OuterBlankOffset = OffsetShapeAlgorithm(*m_outOnlyLineArray, m_outOnlyLineArray->GetSize() - 1, m_OutLeft);
		m_InBlankOffset = OffsetShapeAlgorithm(*m_inOnlyLineArray, m_inOnlyLineArray->GetSize() - 1, -m_InLeft);
		for (OffsetPoint it : m_OuterBlankOffset)
		{
			OffsetPoint its = it;
			its.begin.z = m_Board_Heigh;
			its.end.z = m_Board_Heigh;
			m_OuterBlankTopOffset.push_back(its);
		}
		for (OffsetPoint it : m_InBlankOffset)
		{
			OffsetPoint its = it;
			its.begin.z = m_Board_Heigh;
			its.end.z = m_Board_Heigh;
			m_InBlankTopOffset.push_back(its);
		}

	}
}

vector<OffsetPoint> CTableBoardProcess::OffsetShapeAlgorithm(CPtrArray& XFarray, int mark, double offset)
{
	vector<OffsetPoint> points;//�洢ÿ��ͼ��ƫ�ƺ����ʼ����յ�
	for (int i = 0; i != mark + 1; ++i)
	{
		if (((CLine*)XFarray.GetAt(i))->flag == 1)
		{
			OffsetPoint temp;
			CPoint3D Not;

			if (i == 0)//���ǵ�һ��Ԫ�ص����
			{
				CVector3D vec1;
				CVector3D vec2;
				CVector3D Roat1;
				CVector3D Roat2;


				if (((CLine*)XFarray.GetAt(mark))->flag == 1)//���һ��Ԫ��Ϊֱ��
				{

					vec1 = ((CLine*)XFarray.GetAt(0))->m_end - ((CLine*)XFarray.GetAt(0))->m_begin;
					vec2 = ((CLine*)XFarray.GetAt(mark))->m_end - ((CLine*)XFarray.GetAt(mark))->m_begin;
					Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);
					Roat2 = CVector3D(-1 * vec2.dy, vec2.dx, vec2.dz);
					Not = CLine::IntersectOfLine(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset, vec1,
						((CLine*)XFarray.GetAt(mark))->m_begin + Roat2.GetNormal()*offset, vec2);

					temp.begin = Not;

				}

				else if (((CArc*)XFarray.GetAt(mark))->flag == 2)//���һ��Ԫ��ΪԲ��
				{
					vec1 = ((CLine*)XFarray.GetAt(0))->m_end - ((CLine*)XFarray.GetAt(0))->m_begin;
					Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);
					CPoint3D tempBegin;
					CPoint3D tempEnd;
					tempBegin = ((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset;
					tempEnd = ((CLine*)XFarray.GetAt(0))->m_end + Roat1.GetNormal()*offset;


					if (((CArc*)XFarray.GetAt(mark))->m_Tudu == 0)//��ͨԲ��
					{
						Not = CLine::IntersectOfArc(tempBegin, tempEnd, ((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
					}
					else//���߶�Բ��
					{
						((CArc*)XFarray.GetAt(mark))->PolyCalculate(((CArc*)XFarray.GetAt(mark))->m_begin, ((CArc*)XFarray.GetAt(mark))->m_end, ((CArc*)XFarray.GetAt(mark))->m_Tudu);

						Not = CLine::IntersectOfArc(tempBegin, tempEnd, ((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
					}
					temp.begin = Not;
				}


				if (((CLine*)XFarray.GetAt(1))->flag == 1)//�ڶ���Ԫ��Ϊֱ��
				{
					vec1 = ((CLine*)XFarray.GetAt(0))->m_end - ((CLine*)XFarray.GetAt(0))->m_begin;
					vec2 = ((CLine*)XFarray.GetAt(1))->m_end - ((CLine*)XFarray.GetAt(1))->m_begin;
					Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);
					Roat2 = CVector3D(-1 * vec2.dy, vec2.dx, vec2.dz);
					Not = CLine::IntersectOfLine(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset, vec1, ((CLine*)XFarray.GetAt(1))->m_begin + Roat2.GetNormal()*offset, vec2);
				}
				else if (((CArc*)XFarray.GetAt(1))->flag == 2)//�ڶ���Ԫ��ΪԲ��
				{
					if (((CArc*)XFarray.GetAt(1))->m_Tudu == 0)//��ͨԲ��
					{
						Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset,
							((CLine*)XFarray.GetAt(0))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
					}
					else//���߶�Բ��
					{
						((CArc*)XFarray.GetAt(1))->PolyCalculate(((CArc*)XFarray.GetAt(1))->m_begin, ((CArc*)XFarray.GetAt(1))->m_end, ((CArc*)XFarray.GetAt(1))->m_Tudu);

						Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset,
							((CLine*)XFarray.GetAt(0))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
					}


				}


				temp.end = Not;



				points.push_back(temp);

			}
			else if (i == mark)//�������һ��Ԫ�ص����
			{

				if (((CLine*)XFarray.GetAt(mark))->flag == 1 && ((CLine*)XFarray.GetAt(0))->flag == 1)//���һ��Ԫ�غ͵�һ��Ԫ�ض���ֱ��
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;
				}
				else if (((CLine*)XFarray.GetAt(mark))->flag == 1 && ((CArc*)XFarray.GetAt(0))->flag == 2)//���һ��Ԫ��Ϊֱ�ߣ���һ��Ԫ��ΪԲ��
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;
				}

				points.push_back(temp);
			}
			else
			{
				CVector3D vec1;
				vec1 = ((CLine*)XFarray.GetAt(i))->m_end - ((CLine*)XFarray.GetAt(i))->m_begin;
				CVector3D Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);


				if (((CLine*)XFarray.GetAt(i + 1))->flag == 1)//ֱ�ߵ���һ��Ԫ����ֱ��
				{
					CVector3D vec2;
					vec2 = ((CLine*)XFarray.GetAt(i + 1))->m_end - ((CLine*)XFarray.GetAt(i + 1))->m_begin;
					CVector3D Roat2 = CVector3D(-1 * vec2.dy, vec2.dx, vec2.dz);

					Not = CLine::IntersectOfLine(((CLine*)XFarray.GetAt(i))->m_begin + Roat1.GetNormal()*offset, vec1,
						((CLine*)XFarray.GetAt(i + 1))->m_begin + Roat2.GetNormal()*offset, vec2);
					temp.begin = points[i - 1].end;
					temp.end = Not;

					points.push_back(temp);
				}

				else if (((CArc*)XFarray.GetAt(i + 1))->flag == 2) //ֱ�ߵ���һ��Ԫ����Բ��
				{
					if (((CArc*)XFarray.GetAt(i + 1))->m_Tudu == 0)//��ͨԲ��
					{
						Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(i))->m_begin + Roat1.GetNormal()*offset,
							((CLine*)XFarray.GetAt(i))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
					}
					else//���߶�Բ��
					{
						((CArc*)XFarray.GetAt(i + 1))->PolyCalculate(((CArc*)XFarray.GetAt(i + 1))->m_begin, ((CArc*)XFarray.GetAt(i + 1))->m_end, ((CArc*)XFarray.GetAt(i + 1))->m_Tudu);

						Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(i))->m_begin + Roat1.GetNormal()*offset,
							((CLine*)XFarray.GetAt(i))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
					}
					temp.begin = points[i - 1].end;
					temp.end = Not;
					points.push_back(temp);
				}

			}


		}
		else if (((CArc*)XFarray.GetAt(i))->flag == 2)
		{
			OffsetPoint temp;
			CPoint3D Not;

			if (((CArc*)XFarray.GetAt(i))->m_Tudu == 0)
			{
				((CArc*)XFarray.GetAt(i))->Calculate(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio,
					((CArc*)XFarray.GetAt(i))->m_begin_angle, ((CArc*)XFarray.GetAt(i))->m_end_angle, XFarray, i);//������ʼ�㼰��ֹ��

				if (i == 0)
				{
					if (((CLine*)XFarray.GetAt(mark))->flag == 1)//���һ��Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(mark))->m_end - ((CLine*)XFarray.GetAt(mark))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(mark))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(mark))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(mark))->flag == 2)//���һ��Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(mark))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(mark))->PolyCalculate(((CArc*)XFarray.GetAt(mark))->m_begin,
								((CArc*)XFarray.GetAt(mark))->m_end, ((CArc*)XFarray.GetAt(mark))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = Not;

					if (((CLine*)XFarray.GetAt(1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(1))->m_end - ((CLine*)XFarray.GetAt(1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(1))->PolyCalculate(((CArc*)XFarray.GetAt(1))->m_begin,
								((CArc*)XFarray.GetAt(1))->m_end, ((CArc*)XFarray.GetAt(1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.end = Not;

					points.push_back(temp);

				}
				else if (i == mark)
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;

					points.push_back(temp);
				}
				else
				{


					if (((CLine*)XFarray.GetAt(i + 1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(i + 1))->m_end - ((CLine*)XFarray.GetAt(i + 1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);


						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
							((CLine*)XFarray.GetAt(i + 1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(i + 1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(i + 1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(i + 1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(i + 1))->PolyCalculate(((CArc*)XFarray.GetAt(i + 1))->m_begin,
								((CArc*)XFarray.GetAt(i + 1))->m_end, ((CArc*)XFarray.GetAt(i + 1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = points[i - 1].end;
					temp.end = Not;
					points.push_back(temp);

				}
			}
			else//���߶�Բ��
			{

				((CArc*)XFarray.GetAt(i))->PolyCalculate(((CArc*)XFarray.GetAt(i))->m_begin, ((CArc*)XFarray.GetAt(i))->m_end,
					((CArc*)XFarray.GetAt(i))->m_Tudu);


				if (i == 0)
				{
					if (((CLine*)XFarray.GetAt(mark))->flag == 1)//���һ��Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(mark))->m_end - ((CLine*)XFarray.GetAt(mark))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(mark))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(mark))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(mark))->flag == 2)//���һ��Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(mark))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(mark))->PolyCalculate(((CArc*)XFarray.GetAt(mark))->m_begin,
								((CArc*)XFarray.GetAt(mark))->m_end, ((CArc*)XFarray.GetAt(mark))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = Not;

					if (((CLine*)XFarray.GetAt(1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(1))->m_end - ((CLine*)XFarray.GetAt(1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(1))->PolyCalculate(((CArc*)XFarray.GetAt(1))->m_begin,
								((CArc*)XFarray.GetAt(1))->m_end, ((CArc*)XFarray.GetAt(1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.end = Not;

					points.push_back(temp);

				}
				else if (i == mark)
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;

					points.push_back(temp);
				}
				else
				{


					if (((CLine*)XFarray.GetAt(i + 1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(i + 1))->m_end - ((CLine*)XFarray.GetAt(i + 1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);


						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
							((CLine*)XFarray.GetAt(i + 1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(i + 1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(i + 1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(i + 1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(i + 1))->PolyCalculate(((CArc*)XFarray.GetAt(i + 1))->m_begin,
								((CArc*)XFarray.GetAt(i + 1))->m_end, ((CArc*)XFarray.GetAt(i + 1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = points[i - 1].end;
					temp.end = Not;
					points.push_back(temp);

				}

			}



		}

	}

	return points;
}

void CTableBoardProcess::RenderTableBlank(COpenGLDC* pDC)
{
	//DrawDIYFromPt(m_OuterBlankPoints, pDC);
	//�ж����������ݲŻ���
	if (m_OuterBlankOffset.size() && m_InBlankOffset.size())
	{
		//pDC->SetMaterialColor(RGB(0,255,0));
		DrawDIYFromOffset(m_OuterBlankOffset, pDC);
		DrawDIYFromOffset(m_InBlankOffset, pDC);
		for (OffsetPoint it : m_OuterBlankOffset)
		{
			pDC->DrawLine(it.begin, CPoint3D(it.begin.x, it.begin.y, m_Board_Heigh));

		}
		for (OffsetPoint it : m_InBlankOffset)
		{
			pDC->DrawLine(it.begin, CPoint3D(it.begin.x, it.begin.y, m_Board_Heigh));

		}
		DrawDIYFromOffset(m_OuterBlankTopOffset, pDC);
		DrawDIYFromOffset(m_InBlankTopOffset, pDC);
	}
}

//��൶·�켣
void CTableBoardProcess::InitTableOutPath()
{
	/*
	ͨ��������Χ�ľ�Ƭÿ���������ë���ĺ�ȣ�ȷ����Ҫ�ӹ��Ĳ�����
	������ǰ�������ӹ��ģ�����ë����һȦ�ķ�ʽ��
	ͨ��OffsetShapeAlgorithm��CptrArray*ƫ��ת�ɳ�vector<elements>���������ͣ�
	�ٽ�vector<elements>�е�Ԫ��ͨ��chang_To_Arrayת����CPtrArray*��
	ͨ����ȡƫ�õ�vector<vector<CPtrArray*>>�����÷���CoverOutsideProfToPoints��vector<CPtrArray*>תΪ�㣬
	�洢��vector<vector<vector<CPoint3D>>>��ȥ����󽫵���������ʾ���ɡ�
	*/
	int n =m_OutLeft/m_B_FeedDis_Horizon ;

	for (int i = n; i !=-1; i--)
	{
		vector<elements> m_tempElements = OffsetOutPathAlgorithm(*m_outArray, m_outArray->GetSize() - 1,m_B_FeedDis_Horizon*i);
		
		//m_tempElements = InsertExtendLineElements(m_tempElements, 400);


		CPtrArray* m_tempOut = Change_To_Array(m_tempElements);

		vector<CPtrArray*> m_tempOutArrays = this->InitTableModel(m_tempOut, m_Board_Heigh, m_B_FeedLoad_Vertical/1000);

		//�����������Ϊ��ָ�룬������Ӧ���������ż���ı���ı�
		vector<CPtrArray*> mm_tempOutArrays = Copy_CPtrArrays(m_tempOutArrays);
		//����������ƫ�ý��д洢
		m_OutOffsetProfile.push_back(m_tempOutArrays);

		vector<vector<CPoint3D>> m_tempPTS;
		if (i == 0)
		{
			m_tempPTS = GetPoints(InitTableModel(Change_To_Array(m_ProfileData[0]), m_Board_Heigh, m_B_FeedLoad_Vertical/1000),
				m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
		}
		else
		{
		
		//�˴�CoverOutsideProfToPoints���offset����Ҫ����Ϊ0��Ҫ��Ȼ���ظ�����ƫ��
		/* m_tempPTS = CoverOutsideProfToPoints(mm_tempOutArrays, 0, 
			                          m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);*///******0819*****
			m_tempPTS = CoverOutsideProfToPoints(mm_tempOutArrays,
				m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
		}
		m_OutOffsetPoints.push_back(m_tempPTS);
	}
}

vector<elements> CTableBoardProcess::InsertExtendLineElements(vector<elements> data, float extendDis)
{
	//�ж���β,������ֱ��
	if (data[0].flag == 1)
	{
		elements ee;
		ee.flag = 1;
		//��ȡ��һ��ֱ�ߵķ�������
		CVector3D bd = data[0].end - data[0].begin;

		ee.end = data[0].begin;
		ee.begin = ee.end - bd.GetNormal()*extendDis;

		data.insert(data.begin(), ee);

	}
	else if (data[0].flag == 2)
	{

	}

	int m_DataSize = data.size();

	if (data[m_DataSize - 1].flag == 1)
	{
		elements ee;
		ee.flag = 1;

		//��ȡ������һ�����ݵķ�������
		CVector3D bd = data[m_DataSize - 1].end - data[m_DataSize - 1].begin;

		ee.begin = data[m_DataSize - 1].end;

		ee.end = ee.begin + bd.GetNormal()*extendDis;

		data.insert(data.end(), ee);

	}
	else if (data[m_DataSize - 1].flag == 2)
	{

	}


	return data;
}

vector<elements> CTableBoardProcess::OffsetOutPathAlgorithm(CPtrArray& XFarray, int mark, double offset)
{
	vector<elements> points;//�洢ÿ��ͼ��ƫ�ƺ����ʼ����յ�
	for (int i = 0; i != mark + 1; ++i)
	{
		if (((CLine*)XFarray.GetAt(i))->flag == 1)
		{
			elements temp;
			temp.flag = 1;

			CPoint3D Not;

			if (i == 0)//���ǵ�һ��Ԫ�ص����
			{
				CVector3D vec1;
				CVector3D vec2;
				CVector3D Roat1;
				CVector3D Roat2;


				if (((CLine*)XFarray.GetAt(mark))->flag == 1)//���һ��Ԫ��Ϊֱ��
				{

					vec1 = ((CLine*)XFarray.GetAt(0))->m_end - ((CLine*)XFarray.GetAt(0))->m_begin;
					vec2 = ((CLine*)XFarray.GetAt(mark))->m_end - ((CLine*)XFarray.GetAt(mark))->m_begin;
					Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);
					Roat2 = CVector3D(-1 * vec2.dy, vec2.dx, vec2.dz);
					Not = CLine::IntersectOfLine(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset, vec1,
						((CLine*)XFarray.GetAt(mark))->m_begin + Roat2.GetNormal()*offset, vec2);

					temp.begin = Not;

				}

				else if (((CArc*)XFarray.GetAt(mark))->flag == 2)//���һ��Ԫ��ΪԲ��
				{
					vec1 = ((CLine*)XFarray.GetAt(0))->m_end - ((CLine*)XFarray.GetAt(0))->m_begin;
					Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);
					CPoint3D tempBegin;
					CPoint3D tempEnd;
					tempBegin = ((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset;
					tempEnd = ((CLine*)XFarray.GetAt(0))->m_end + Roat1.GetNormal()*offset;


					if (((CArc*)XFarray.GetAt(mark))->m_Tudu == 0)//��ͨԲ��
					{
						Not = CLine::IntersectOfArc(tempBegin, tempEnd, ((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
					}
					else//���߶�Բ��
					{
						((CArc*)XFarray.GetAt(mark))->PolyCalculate(((CArc*)XFarray.GetAt(mark))->m_begin, ((CArc*)XFarray.GetAt(mark))->m_end, ((CArc*)XFarray.GetAt(mark))->m_Tudu);

						Not = CLine::IntersectOfArc(tempBegin, tempEnd, ((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
					}
					temp.begin = Not;
				}


				if (((CLine*)XFarray.GetAt(1))->flag == 1)//�ڶ���Ԫ��Ϊֱ��
				{
					vec1 = ((CLine*)XFarray.GetAt(0))->m_end - ((CLine*)XFarray.GetAt(0))->m_begin;
					vec2 = ((CLine*)XFarray.GetAt(1))->m_end - ((CLine*)XFarray.GetAt(1))->m_begin;
					Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);
					Roat2 = CVector3D(-1 * vec2.dy, vec2.dx, vec2.dz);
					Not = CLine::IntersectOfLine(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset, vec1, ((CLine*)XFarray.GetAt(1))->m_begin + Roat2.GetNormal()*offset, vec2);
				}
				else if (((CArc*)XFarray.GetAt(1))->flag == 2)//�ڶ���Ԫ��ΪԲ��
				{
					if (((CArc*)XFarray.GetAt(1))->m_Tudu == 0)//��ͨԲ��
					{
						Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset,
							((CLine*)XFarray.GetAt(0))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
					}
					else//���߶�Բ��
					{
						((CArc*)XFarray.GetAt(1))->PolyCalculate(((CArc*)XFarray.GetAt(1))->m_begin, ((CArc*)XFarray.GetAt(1))->m_end, ((CArc*)XFarray.GetAt(1))->m_Tudu);

						Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(0))->m_begin + Roat1.GetNormal()*offset,
							((CLine*)XFarray.GetAt(0))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
					}


				}


				temp.end = Not;



				points.push_back(temp);

			}
			else if (i == mark)//�������һ��Ԫ�ص����
			{

				if (((CLine*)XFarray.GetAt(mark))->flag == 1 && ((CLine*)XFarray.GetAt(0))->flag == 1)//���һ��Ԫ�غ͵�һ��Ԫ�ض���ֱ��
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;
				}
				else if (((CLine*)XFarray.GetAt(mark))->flag == 1 && ((CArc*)XFarray.GetAt(0))->flag == 2)//���һ��Ԫ��Ϊֱ�ߣ���һ��Ԫ��ΪԲ��
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;
				}

				points.push_back(temp);
			}
			else
			{
				CVector3D vec1;
				vec1 = ((CLine*)XFarray.GetAt(i))->m_end - ((CLine*)XFarray.GetAt(i))->m_begin;
				CVector3D Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);


				if (((CLine*)XFarray.GetAt(i + 1))->flag == 1)//ֱ�ߵ���һ��Ԫ����ֱ��
				{
					CVector3D vec2;
					vec2 = ((CLine*)XFarray.GetAt(i + 1))->m_end - ((CLine*)XFarray.GetAt(i + 1))->m_begin;
					CVector3D Roat2 = CVector3D(-1 * vec2.dy, vec2.dx, vec2.dz);

					Not = CLine::IntersectOfLine(((CLine*)XFarray.GetAt(i))->m_begin + Roat1.GetNormal()*offset, vec1,
						((CLine*)XFarray.GetAt(i + 1))->m_begin + Roat2.GetNormal()*offset, vec2);
					temp.begin = points[i - 1].end;
					temp.end = Not;

					points.push_back(temp);
				}

				else if (((CArc*)XFarray.GetAt(i + 1))->flag == 2) //ֱ�ߵ���һ��Ԫ����Բ��
				{
					if (((CArc*)XFarray.GetAt(i + 1))->m_Tudu == 0)//��ͨԲ��
					{
						//************************0810**************************˳ʱ��
						if (!((CArc*)XFarray.GetAt(i + 1))->Calculate(((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio,
							((CArc*)XFarray.GetAt(i + 1))->m_begin_angle, ((CArc*)XFarray.GetAt(i + 1))->m_end_angle, XFarray, i + 1))
						{
							Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(i))->m_begin + Roat1.GetNormal()*offset,
								((CLine*)XFarray.GetAt(i))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);

						}
						else//*********0810************��ʱ��
						{
							Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(i))->m_begin + Roat1.GetNormal()*offset,
								((CLine*)XFarray.GetAt(i))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio - offset, mark, XFarray, i);
						}
					}
					else//���߶�Բ��
					{
						((CArc*)XFarray.GetAt(i + 1))->PolyCalculate(((CArc*)XFarray.GetAt(i + 1))->m_begin, ((CArc*)XFarray.GetAt(i + 1))->m_end, ((CArc*)XFarray.GetAt(i + 1))->m_Tudu);

						Not = CLine::IntersectOfArc(((CLine*)XFarray.GetAt(i))->m_begin + Roat1.GetNormal()*offset,
							((CLine*)XFarray.GetAt(i))->m_end + Roat1.GetNormal()*offset, ((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
					}
					temp.begin = points[i - 1].end;
					temp.end = Not;
					points.push_back(temp);
				}

			}


		}
		else if (((CArc*)XFarray.GetAt(i))->flag == 2)
		{
			elements temp;
			temp.flag = 2;

			CPoint3D Not;

			if (((CArc*)XFarray.GetAt(i))->m_Tudu == 0)
			{
				BOOL dddd=((CArc*)XFarray.GetAt(i))->Calculate(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio,
					((CArc*)XFarray.GetAt(i))->m_begin_angle, ((CArc*)XFarray.GetAt(i))->m_end_angle, XFarray, i);//������ʼ�㼰��ֹ��

				temp.center = ((CArc*)XFarray.GetAt(i))->m_center;
				temp.start_angle = ((CArc*)XFarray.GetAt(i))->m_begin_angle;
				temp.end_angle = ((CArc*)XFarray.GetAt(i))->m_end_angle;
				//temp.radius = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
				temp.tudu = 0;
				temp.arc_direction = ((CArc*)XFarray.GetAt(i))->m_Direction;

				//************************0810**************************
				if (!dddd)
				{
					temp.radius = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
				}
				else
				{
					temp.radius = ((CArc*)XFarray.GetAt(i))->m_radio - offset;
				}
				/*
				if (dddd)
				{
					offset = -offset;//*********0818************
				}	
				temp.radius = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
				*/
				if (i == 0)
				{
					if (((CLine*)XFarray.GetAt(mark))->flag == 1)//���һ��Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(mark))->m_end - ((CLine*)XFarray.GetAt(mark))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(mark))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(mark))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(mark))->flag == 2)//���һ��Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(mark))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(mark))->PolyCalculate(((CArc*)XFarray.GetAt(mark))->m_begin,
								((CArc*)XFarray.GetAt(mark))->m_end, ((CArc*)XFarray.GetAt(mark))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = Not;

					if (((CLine*)XFarray.GetAt(1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(1))->m_end - ((CLine*)XFarray.GetAt(1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(1))->PolyCalculate(((CArc*)XFarray.GetAt(1))->m_begin,
								((CArc*)XFarray.GetAt(1))->m_end, ((CArc*)XFarray.GetAt(1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.end = Not;

					points.push_back(temp);

				}
				else if (i == mark)
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;

					points.push_back(temp);
				}
				else
				{


					if (((CLine*)XFarray.GetAt(i + 1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(i + 1))->m_end - ((CLine*)XFarray.GetAt(i + 1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						if (dddd)//��ʱ��*****0818*******
						{//��ʱ��*****0818*******
							Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio - offset,
								((CLine*)XFarray.GetAt(i + 1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(i + 1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
						}//��ʱ��*****0818*******
						else//*****0818*******
						{//*****0818*******
							Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CLine*)XFarray.GetAt(i + 1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(i + 1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
						}//*****0818*******
						
					}
					else if (((CArc*)XFarray.GetAt(i + 1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(i + 1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(i + 1))->PolyCalculate(((CArc*)XFarray.GetAt(i + 1))->m_begin,
								((CArc*)XFarray.GetAt(i + 1))->m_end, ((CArc*)XFarray.GetAt(i + 1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = points[i - 1].end;
					temp.end = Not;
					points.push_back(temp);

				}

			}
			else//���߶�Բ��
			{

				((CArc*)XFarray.GetAt(i))->PolyCalculate(((CArc*)XFarray.GetAt(i))->m_begin, ((CArc*)XFarray.GetAt(i))->m_end,
					((CArc*)XFarray.GetAt(i))->m_Tudu);

				temp.center = ((CArc*)XFarray.GetAt(i))->m_center;
				temp.radius = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
				temp.tudu = ((CArc*)XFarray.GetAt(i))->m_Tudu;
				temp.start_angle = ((CArc*)XFarray.GetAt(i))->m_begin_angle;
				temp.end_angle = ((CArc*)XFarray.GetAt(i))->m_end_angle;
			

				if (i == 0)
				{
					if (((CLine*)XFarray.GetAt(mark))->flag == 1)//���һ��Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(mark))->m_end - ((CLine*)XFarray.GetAt(mark))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(mark))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(mark))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(mark))->flag == 2)//���һ��Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(mark))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(mark))->PolyCalculate(((CArc*)XFarray.GetAt(mark))->m_begin,
								((CArc*)XFarray.GetAt(mark))->m_end, ((CArc*)XFarray.GetAt(mark))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(mark))->m_center, ((CArc*)XFarray.GetAt(mark))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = Not;

					if (((CLine*)XFarray.GetAt(1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(1))->m_end - ((CLine*)XFarray.GetAt(1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);

						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
							((CLine*)XFarray.GetAt(1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(1))->PolyCalculate(((CArc*)XFarray.GetAt(1))->m_begin,
								((CArc*)XFarray.GetAt(1))->m_end, ((CArc*)XFarray.GetAt(1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(0))->m_center, ((CArc*)XFarray.GetAt(0))->m_radio + offset,
								((CArc*)XFarray.GetAt(1))->m_center, ((CArc*)XFarray.GetAt(1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.end = Not;

					points.push_back(temp);

				}
				else if (i == mark)
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;

					points.push_back(temp);
				}
				else
				{


					if (((CLine*)XFarray.GetAt(i + 1))->flag == 1)//�ڶ���Ԫ����ֱ��
					{
						CVector3D vec1;
						CVector3D Roat1;
						vec1 = ((CLine*)XFarray.GetAt(i + 1))->m_end - ((CLine*)XFarray.GetAt(i + 1))->m_begin;
						Roat1 = CVector3D(-1 * vec1.dy, vec1.dx, vec1.dz);


						Not = CArc::IntersectOfLine(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
							((CLine*)XFarray.GetAt(i + 1))->m_begin + Roat1.GetNormal()*offset, ((CLine*)XFarray.GetAt(i + 1))->m_end + Roat1.GetNormal()*offset, mark, XFarray, i);
					}
					else if (((CArc*)XFarray.GetAt(i + 1))->flag == 2)//�ڶ���Ԫ����Բ��
					{
						if (((CArc*)XFarray.GetAt(i + 1))->m_Tudu == 0)//��ͨԲ��
						{
							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
						else//���߶�Բ��*****��Ҫ����Բ�İ뾶********
						{
							((CArc*)XFarray.GetAt(i + 1))->PolyCalculate(((CArc*)XFarray.GetAt(i + 1))->m_begin,
								((CArc*)XFarray.GetAt(i + 1))->m_end, ((CArc*)XFarray.GetAt(i + 1))->m_Tudu);

							Not = CArc::IntersectOfArc(((CArc*)XFarray.GetAt(i))->m_center, ((CArc*)XFarray.GetAt(i))->m_radio + offset,
								((CArc*)XFarray.GetAt(i + 1))->m_center, ((CArc*)XFarray.GetAt(i + 1))->m_radio + offset, mark, XFarray, i);
						}
					}

					temp.begin = points[i - 1].end;
					temp.end = Not;
					points.push_back(temp);

				}

			}



		}

	}

	return points;
}


void CTableBoardProcess::RenderTableOutPath(COpenGLDC* pDC)
{
	

	for (vector<vector<vector<CPoint3D>>>::iterator it = m_OutOffsetPoints.begin(); it != m_OutOffsetPoints.end(); ++it)
	{
		for (vector<vector<CPoint3D>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			for (vector<CPoint3D>::iterator itss = its->begin(); itss != its->end()-1; ++itss)
			{
				pDC->DrawLine(*itss, *(itss + 1));
			}
		}
	}
	
	
	DrawOutRetractLine(m_OutOffsetPoints, pDC);

}

//�ڲ൶·�켣
void CTableBoardProcess::InitTableInPath()
{
	int n = m_InLeft / m_B_FeedDis_Horizon;

	for (int i = n; i != -1; i--)
	{
		//��ȡ����Ԫ�غ��������Ϣ
		vector<elements> m_tempElements = NewInsertElement(OffsetOutPathAlgorithm(*m_innerArray, m_innerArray->GetSize() - 1, -1 * m_B_FeedDis_Horizon*i));
		
		CPtrArray* m_tempIn = Change_To_Array(m_tempElements);

		vector<CPtrArray*> m_tempInArrays = this->InitTableModel(m_tempIn, m_Board_Heigh, m_B_FeedLoad_Vertical / 1000);
		//�õ�������ƫ������
		m_inOffsetProfile.push_back(m_tempInArrays);

		/*
		vector<vector<CPoint3D>> m_tempPTS;
		if (i == 0)
		{
			m_tempPTS = GetPoints(InitTableModel(Change_To_Array(m_ProfileData[1]), m_Board_Heigh, m_B_FeedLoad_Vertical / 1000),
				m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
		}
		else
		{

			//�˴�CoverOutsideProfToPoints���offset����Ҫ����Ϊ0��Ҫ��Ȼ���ظ�����ƫ��
			m_tempPTS = CoverOutsideProfToPoints(m_tempInArrays, 0,
				m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
		}
		m_inOffsetPoints.push_back(m_tempPTS);*/
	}

	InitInArray();

	//��Ƭ�����ɢ��,��ָ���ǵ����
	for (vector<vector<vector<CPtrArray*>>>::iterator it = m_InOffsetSawProfile.begin(); it != m_InOffsetSawProfile.end(); ++it)
	{
		vector<vector<vector<CPoint3D>>> mmm_tempBoardPts;
		for (vector<vector<CPtrArray*>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			vector<vector<CPoint3D>> mm_tempBoardPts;
			for (vector<CPtrArray*>::iterator itss = its->begin(); itss != its->end(); ++itss)
			{
				vector<CPoint3D> m_tempBoardPts = this->GetPoints(*itss, m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
				mm_tempBoardPts.push_back(m_tempBoardPts);
			}
			mmm_tempBoardPts.push_back(mm_tempBoardPts);
		}
		m_InOffsetSawPoints.push_back(mmm_tempBoardPts);

	}
	/*��Ҫ����ϳ�����õ�ÿ��������Ƚ��зֲ㣬Ҳ����Ҫ�������õ�ֵ����m_InOffsetMillProfile�е�Z������������µķ��䡣
	��Ϊϳ���ӹ���Ҫ��������Ƚ��������½��ӹ������̵�ʱ��ֱ����ԭ�ȵĹ켣���мӹ�����*/
	
	vector<vector<vector<vector<CPoint3D>>>> m_tempInOffsetMillPoints;
	//ϳ�������ɢ��
	for (vector<vector<vector<CPtrArray*>>>::iterator it = m_InOffsetMillProfile.begin(); it != m_InOffsetMillProfile.end(); ++it)
	{
		vector<vector<vector<CPoint3D>>> mmm_tempBoardPts;
		for (vector<vector<CPtrArray*>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			vector<vector<CPoint3D>> mm_tempBoardPts;
			for (vector<CPtrArray*>::iterator itss = its->begin(); itss != its->end(); ++itss)
			{
				vector<CPoint3D> m_tempBoardPts = this->GetPoints(*itss, m_B_FeedSpeed_Horizon, m_B_FeedTime_Horizon);
				mm_tempBoardPts.push_back(m_tempBoardPts);
			}
			mmm_tempBoardPts.push_back(mm_tempBoardPts);
		}

		m_tempInOffsetMillPoints.push_back(mmm_tempBoardPts);
	}

	//����ϳ��ÿ����10mm,����ʱ�洢������޸�
	m_InOffsetMillPoints = ChangesToMillPoints(m_tempInOffsetMillPoints, m_MillCutDepth_Vertical);

}

vector<vector<vector<CPtrArray*>>> CTableBoardProcess::ChangesToMillProfiles(vector<vector<vector<CPtrArray*>>> data, float high, float depth)
{
	vector<vector<vector<CPtrArray*>>> datas;

	for (vector<vector<vector<CPtrArray*>>>::iterator it = data.begin(); it != data.end(); ++it)
	{
		vector < vector<CPtrArray*>> m_tempDATA;
		for (vector<vector<CPtrArray*>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			vector<CPtrArray*> mm_tempDATA = InitTableModel(*(its->begin()), high, depth);
			m_tempDATA.push_back(mm_tempDATA);
		}
		datas.push_back(m_tempDATA);
	}

	return datas;
}
vector<vector<vector<vector<CPoint3D>>>> CTableBoardProcess::ChangesToMillPoints(vector<vector<vector<vector<CPoint3D>>>> data, float m_MillDepth)
{
	vector<vector<vector<vector<CPoint3D>>>> s;
	for (vector<vector<vector<vector<CPoint3D>>>>::iterator it = data.begin(); it != data.end(); ++it)//��һ����
	{

		vector<vector<vector<CPoint3D>>> ss;
		for (vector<vector<vector<CPoint3D>>>::iterator its = it->begin(); its != it->end(); ++its)//��һ��
		{
			vector<vector<CPoint3D>> sss;
			BOOL DIRECTION = TRUE;//True��ʾ��Ҫ����ת��
			for (vector<vector<CPoint3D>>::iterator itss = its->begin(); itss != its->end(); ++itss)//��һ���߶�
			{
				/*��Ҫ�����޸ģ�11������10�Σ���Ҫ�������ж�ʮ��*/
				/*
				vector<CPoint3D> ssss;
				if (!DIRECTION)//����ת��
				{
					for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)//��һ��ֱ��
					{
						ssss.push_back(*itsss);//��ӵ㼴��
					}
				}
				else//��ת��
				{
					//��ȡ�������
					int m_TotalSize=itss->size();
					float m_PerDownDis = m_MillDepth / m_TotalSize;
					int m_COUNT = 0;
					if (itss==its->begin())//��һ��
					{
						for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)
						{
							itsss->z -= m_COUNT*m_PerDownDis;
							ssss.push_back(*itsss);
							m_COUNT += 1;
						}
					}
					else//�м估���һ��
					{
						for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)
						{
							itsss->z = itsss->z-m_COUNT*m_PerDownDis+m_MillDepth;
							ssss.push_back(*itsss);
							m_COUNT+=1;
						}
					}
				}
				sss.push_back(ssss);
				DIRECTION = !DIRECTION;*/
				vector<CPoint3D> ssss;
				vector<CPoint3D> ssss_s;
				m_TotalSize = itss->size();
				m_PerDownDis = m_MillDepth / m_TotalSize;
				int m_COUNT = 1;
				if (itss != its->begin())//����ߵ���һ��
				{
					for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)
					{
						CPoint3D m_tempPTTS = *itsss;
						m_tempPTTS.z= m_tempPTTS.z-m_COUNT*m_PerDownDis + m_MillDepth;
						ssss.push_back(m_tempPTTS);//��ӵ㼴��
						m_COUNT += 1;
					}
					for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)//���ֱ�ߵ㼴��
					{
						ssss_s.push_back(*itsss);//��ӵ㼴��
					}
				sss.push_back(ssss);
				sss.push_back(ssss_s);
				}
				
			}
			ss.push_back(sss);
		}
		s.push_back(ss);
	}


	return s;
}

void CTableBoardProcess::InitInArray()
{
	//��ȡ������ƫ�ú��CPtrArray*����
	//��Ƭ�ӹ��������£���������
	//��Ƭ
	vector<vector<CPtrArray*>> m_S1;
	vector<vector<CPtrArray*>> m_S5;
	vector<vector<CPtrArray*>> m_S9;
	vector<vector<CPtrArray*>> m_S13;

	//ϳ��
	vector<vector<CPtrArray*>> m_S2_4;
	vector<vector<CPtrArray*>> m_S6_8;
	vector<vector<CPtrArray*>> m_S10_12;
	vector<vector<CPtrArray*>> m_S14_0;


	//�ݴ�����
	vector<vector<vector<CPtrArray*>>> m_tempInOffsetMillProfile;

	//��������
	//ÿһ������
	for (vector<vector<CPtrArray*>>::iterator it = m_inOffsetProfile.begin(); it != m_inOffsetProfile.end(); ++it)
	{
		//��������
		vector<CPtrArray*> mm_S1;
		vector<CPtrArray*> mm_S5;
		vector<CPtrArray*> mm_S9;
		vector<CPtrArray*> mm_S13;

		vector<CPtrArray*> mm_S2_4;
		vector<CPtrArray*> mm_S6_8;
		vector<CPtrArray*> mm_S10_12;
		vector<CPtrArray*> mm_S14_0;

		//vector<vector<vector<CPtrArray*>>> m_tempInOffsetSawProfile;
		//vector<vector<vector<CPtrArray*>>> m_tempInOffsetMillProfile;

		//ÿһ���߶��ϵ�����
		for (vector<CPtrArray*>::iterator its = it->begin(); its != it->end(); ++its)
		{

			//ÿһ������
			for (int i = 0; i != (*its)->GetSize(); ++i)
			{
				CPtrArray* m_testArray = new CPtrArray();
				vector<int> m_testCount;

				if (i == pos[0])
				{
					m_testCount.push_back(i);
					m_testArray = CopyData(*its, m_testCount);
					mm_S1.push_back(m_testArray);

				}
				else if (i == pos[1])
				{
					m_testCount.push_back(i);
					m_testArray = CopyData(*its, m_testCount);
					mm_S5.push_back(m_testArray);
				}
				else if (i == pos[2])
				{
					m_testCount.push_back(i);
					m_testArray = CopyData(*its, m_testCount);
					mm_S9.push_back(m_testArray);
				}
				else if (i == pos[3])
				{
					m_testCount.push_back(i);
					m_testArray = CopyData(*its, m_testCount);
					mm_S13.push_back(m_testArray);
				}
				else if (i > pos[0] && i < pos[1])
				{
					if (i == pos[0] + 1)
					{
						for (int j = pos[0] + 1; j != pos[1]; ++j)
						{
							m_testCount.push_back(j);
						}
						m_testArray = CopyData(*its, m_testCount);
						mm_S2_4.push_back(m_testArray);

					}
					else
						continue;
				}
				else if (i>pos[1] && i < pos[2])
				{
					if (i == pos[1] + 1)
					{
						for (int j = pos[1] + 1; j != pos[2]; ++j)
						{
							m_testCount.push_back(j);
						}
						m_testArray = CopyData(*its, m_testCount);
						mm_S6_8.push_back(m_testArray);
					}
					else
						continue;
				}
				else if (i>pos[2] && i < pos[3])
				{
					if (i == pos[2] + 1)
					{
						for (int j = pos[2] + 1; j != pos[3]; ++j)
						{
							m_testCount.push_back(j);
						}
						m_testArray = CopyData(*its, m_testCount);
						mm_S10_12.push_back(m_testArray);
					}
					else
						continue;
				}
				else if (i>pos[3])//���һ��Ҫ���ϵ�һ��Ϊ0������
				{
					if (i == pos[3] + 1)
					{
						for (int j = pos[3] + 1; j != (*its)->GetSize(); ++j)
						{
							m_testCount.push_back(j);
						}
						//�������һ��
						m_testCount.push_back(0);
						m_testArray = CopyData(*its, m_testCount);
						mm_S14_0.push_back(m_testArray);
					}
					else
						continue;
				}
			}

		}

		m_S1.push_back(mm_S1);
		m_S5.push_back(mm_S5);
		m_S9.push_back(mm_S9);
		m_S13.push_back(mm_S13);


		m_S2_4.push_back(mm_S2_4);
		m_S6_8.push_back(mm_S6_8);
		m_S10_12.push_back(mm_S10_12);
		m_S14_0.push_back(mm_S14_0);


	}
	m_InOffsetSawProfile.push_back(m_S1);
	m_InOffsetSawProfile.push_back(m_S5);
	m_InOffsetSawProfile.push_back(m_S9);
	m_InOffsetSawProfile.push_back(m_S13);


	m_tempInOffsetMillProfile.push_back(m_S2_4);
	m_tempInOffsetMillProfile.push_back(m_S6_8);
	m_tempInOffsetMillProfile.push_back(m_S10_12);
	m_tempInOffsetMillProfile.push_back(m_S14_0);
	//���Ҽ���ϳ������ÿ���µ�Ϊ10mm
	m_InOffsetMillProfile = ChangesToMillProfiles(m_tempInOffsetMillProfile,m_Board_Heigh,m_MillCutDepth_Vertical);
	/*
	m_InOffsetMillProfile.push_back(m_S2_4);
	m_InOffsetMillProfile.push_back(m_S6_8);
	m_InOffsetMillProfile.push_back(m_S10_12);
	m_InOffsetMillProfile.push_back(m_S14_0);*/
}

CPtrArray* CTableBoardProcess::CopyData(CPtrArray* data, vector<int> number)
{
	CPtrArray* s=new CPtrArray();
	for (int i : number)
	{	
		if (((CLine*)data->GetAt(i))->flag == 1)
		{
			CLine* pLine = new CLine();
			s->Add(pLine);
			pLine->flag = ((CLine*)data->GetAt(i))->flag;
			pLine->m_begin = ((CLine*)data->GetAt(i))->m_begin;
			pLine->m_end = ((CLine*)data->GetAt(i))->m_end;
		}
		else if (((CArc*)data->GetAt(i))->flag == 2)
		{
			CArc* pArc = new CArc();
			s->Add(pArc);

			pArc->flag = ((CArc*)data->GetAt(i))->flag;
			pArc->m_center = ((CArc*)data->GetAt(i))->m_center;
			pArc->m_radio = ((CArc*)data->GetAt(i))->m_radio;
			pArc->m_begin_angle = ((CArc*)data->GetAt(i))->m_begin_angle;
			pArc->m_end_angle = ((CArc*)data->GetAt(i))->m_end_angle;

			pArc->m_begin = ((CArc*)data->GetAt(i))->m_begin;
			pArc->m_end = ((CArc*)data->GetAt(i))->m_end;
			pArc->m_Tudu = ((CArc*)data->GetAt(i))->m_Tudu;


		}
	}
	return s;
}


vector<elements> CTableBoardProcess::NewInsertElement(vector<elements> data)
{
	vector<elements> s;

	for (vector<elements>::iterator it =data.begin(); it != data.end(); ++it)
	{

		if (it->flag == 1)
		{
			vector<elements> m_cutElements =SeperateToThreeParts(*it, 10*m_MillToolDiamand/2, m_MillCutDepth_Horizon);
			for (elements ss : m_cutElements)
			{
				s.push_back(ss);
			}
		}
		else
		{
			s.push_back(*it);
		}

	}
	int p = 0;
	for (int i = 0; i != s.size(); ++i)
	{
		
		if (i >= 1 && i <= s.size() -2)
		{
			if (s[i].flag == 1 && s[i + 1].flag == 1 && s[i - 1].flag == 1)
			{
				pos[p] = i;
				p++;
			}
		}
	}

	return s;
}
void CTableBoardProcess::RenderTableSawPath(COpenGLDC* pDC)
{
	DrawDIYFromPt(m_InOffsetSawPoints,pDC);
	DrawInSawRetractLine(m_InOffsetSawPoints, pDC);
}
void CTableBoardProcess::RenderTableMillPath(COpenGLDC* pDC)
{
	DrawDIYFromPt(m_InOffsetMillPoints, pDC);
	DrawInMillRetractLine(m_InOffsetMillPoints, pDC);
}

//��ʼ�������
void CTableBoardProcess::InitTableSimulationPoints(vector<vector<vector<CPoint3D>>> m_outPts,
	vector<vector<vector<vector<CPoint3D>>>> m_inSaw, vector<vector<vector<vector<CPoint3D>>>> m_inMill)
{
	/*
	�������ں���ļӹ�˳����мӹ�����
	�Ƚ��о�Ƭ�ӹ������ϳ�ӹ�
	*/
	//��������ķ������ݵ�
	vector<CPoint3D>().swap(m_BoardRoughSimulation);
	vector<CPoint3D>().swap(m_BoardFinishSimulation);
	
	//���ڲ��Ƭ
	for (vector<vector<vector<vector<CPoint3D>>>>::iterator it = m_inSaw.begin(); it != m_inSaw.end(); ++it)//�Ŀ�
	{
		for (vector<vector<vector<CPoint3D>>>::iterator its = it->begin(); its != it->end(); ++its)//�Ĳ�
		{
			BOOL m_Direction = TRUE;//trueΪĬ��˳ʱ�뷽��falseΪ��ʱ�뷽��
			for (vector<vector<CPoint3D>>::iterator itss = its->begin(); itss != its->end(); ++itss)//�ĸ߶�
			{
				//����������һ���㣬�յ����һ����
				CVector3D m_Linedirection = *(its->begin()->end() - 1) - *(its->begin()->begin());//ֱ�ߵķ���
				CVector3D m_NRotateLine = CVector3D(m_Linedirection.dy, -m_Linedirection.dx, 0).GetNormal();

				if (m_Direction)
				{
					m_BoardRoughSimulation.push_back(*(itss->begin()) + m_NRotateLine*m_ExtendLength);
					m_BoardFinishSimulation.push_back(*(itss->begin()) + m_NRotateLine*m_ExtendLength);
					for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)//�ĵ�
					{
						m_BoardRoughSimulation.push_back(*itsss);
						m_BoardFinishSimulation.push_back(*itsss);
					}
					m_BoardRoughSimulation.push_back(*(itss->end() - 1) + m_NRotateLine * m_ExtendLength);
					m_BoardFinishSimulation.push_back(*(itss->end() - 1) + m_NRotateLine * m_ExtendLength);
				}
				else
				{
					m_BoardRoughSimulation.push_back(*(itss->end() - 1) + m_NRotateLine * m_ExtendLength);
					m_BoardFinishSimulation.push_back(*(itss->end() - 1) + m_NRotateLine * m_ExtendLength);
					for (vector<CPoint3D>::reverse_iterator itsss = itss->rbegin(); itsss != itss->rend(); ++itsss)//�ĵ�
					{
						m_BoardRoughSimulation.push_back(*itsss);
						m_BoardFinishSimulation.push_back(*itsss);
					}
					m_BoardRoughSimulation.push_back(*(itss->begin()) + m_NRotateLine*m_ExtendLength);
					m_BoardFinishSimulation.push_back(*(itss->begin()) + m_NRotateLine*m_ExtendLength);
				}
				//���һ���������һ�����͸߶ȴ�
				if (it == m_inSaw.end() - 1 && its == it->end() - 1 && itss == its->end() - 1)
				{
					CPoint3D tempPTS = *(m_BoardRoughSimulation.end() - 1);
					m_BoardRoughSimulation.push_back(CPoint3D(tempPTS.x, tempPTS.y, 2 * m_Board_Heigh));
					m_BoardFinishSimulation.push_back(CPoint3D(tempPTS.x, tempPTS.y, 2 * m_Board_Heigh));
				}
				m_Direction = !m_Direction;
			}
		}
	}
	
	//���ڲ�ϳ��
	
	for (vector<vector<vector<vector<CPoint3D>>>>::iterator it = m_inMill.begin(); it != m_inMill.end(); ++it)//�Ŀ�
	{
		for (vector<vector<vector<CPoint3D>>>::iterator its = it->begin(); its != it->end(); ++its)//�Ĳ�
		{
			BOOL m_Direction = TRUE;
			if (its == it->begin())
			{
				m_BoardRoughSimulation.push_back(CPoint3D(its->begin()->begin()->x, its->begin()->begin() ->y,m_Board_Heigh*2));
				m_BoardFinishSimulation.push_back(CPoint3D(its->begin()->begin()->x, its->begin()->begin()->y, m_Board_Heigh * 2));
			}
			for (vector<vector<CPoint3D>>::iterator itss = its->begin(); itss != its->end(); ++itss)//�ĸ߶�
			{
				if (m_Direction)
				{
					for (vector<CPoint3D>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)//�ĵ�
					{
						m_BoardRoughSimulation.push_back(*itsss);
						m_BoardFinishSimulation.push_back(*itsss);
						//���һ������һ���߶ȵ����һ����,���һ����̧�ߵ�2*m_board_high�߶�
						if (its == it->end() - 1 && itss == its->end() - 1&&itsss==itss->end()-1)
						{
							m_BoardRoughSimulation.push_back(CPoint3D(itsss->x,itsss->y,2*m_Board_Heigh));
							m_BoardFinishSimulation.push_back( CPoint3D(itsss->x, itsss->y, 2 * m_Board_Heigh));
						}
					}
				}
				else
				{
					for (vector<CPoint3D>::reverse_iterator itsss = itss->rbegin(); itsss != itss->rend(); ++itsss)
					{
						m_BoardRoughSimulation.push_back(*itsss);
						m_BoardFinishSimulation.push_back(*itsss);
						//���һ������һ���߶ȵ����һ����
						if (its == it->end() - 1 && itss == its->end() - 1 && itsss==itss->rend() - 1)
						{
							m_BoardRoughSimulation.push_back(CPoint3D(itsss->x, itsss->y, 2 * m_Board_Heigh));
							m_BoardFinishSimulation.push_back(CPoint3D(itsss->x, itsss->y, 2 * m_Board_Heigh));
						}
					}
				}
				
				m_Direction = !m_Direction;
			}
			
		}
	}
	
	//������Ƭ
	for (vector<vector<vector<CPoint3D>>>::iterator it = m_outPts.begin(); it != m_outPts.end(); ++it)//�Ĳ�
	{
		BOOL m_Direction = TRUE;
		for (vector<vector<CPoint3D>>::iterator its = it->begin(); its != it->end(); ++its)//�ĸ߶�
		{
			if (m_Direction)
			{
				CVector3D m_LineDirection = *(its->begin() + 1) - *(its->begin());
				CPoint3D m_RetractBegin = *(its->begin()) - m_LineDirection.GetNormal() * m_ExtendLength;
				m_BoardRoughSimulation.push_back(m_RetractBegin);
				m_BoardFinishSimulation.push_back(m_RetractBegin);

				for (vector<CPoint3D>::iterator itss = its->begin(); itss != its->end(); ++itss)//�ĵ�
				{
					m_BoardRoughSimulation.push_back(*itss);
					m_BoardFinishSimulation.push_back(*itss);
				}
				m_LineDirection = *(its->end() - 1) - *(its->end() - 2);
				CPoint3D m_RetractEnd = *(its->end() - 1) + m_LineDirection.GetNormal() * m_ExtendLength;
				m_BoardRoughSimulation.push_back(m_RetractEnd);
				m_BoardFinishSimulation.push_back(m_RetractEnd);
			}
			else
			{
				CVector3D m_LineDirection = *(its->end() - 1) - *(its->end() - 2);
				CPoint3D m_RetractBegin = *(its->end() - 1)+m_LineDirection.GetNormal() * m_ExtendLength;
				m_BoardRoughSimulation.push_back(m_RetractBegin);
				m_BoardFinishSimulation.push_back(m_RetractBegin);
				for (vector<CPoint3D>::reverse_iterator itss = its->rbegin(); itss != its->rend(); ++itss)//�ĵ�
				{
					m_BoardRoughSimulation.push_back(*itss);
					m_BoardFinishSimulation.push_back(*itss);
				}
				m_LineDirection = *(its->begin() + 1) - *(its->begin());
				CPoint3D m_RetractEnd = *(its->begin())-m_LineDirection.GetNormal() * m_ExtendLength;
				m_BoardRoughSimulation.push_back(m_RetractEnd);
				m_BoardFinishSimulation.push_back(m_RetractEnd);
			}
			m_Direction = !m_Direction;
			
		}
	}
}


//NC�������ݵĳ�ʼ��
//�ڲ���Ƭ
vector<vector<vector<vector<elements>>>> CTableBoardProcess::InitTableInSawNC(vector<vector<vector<CPtrArray*>>> data)
{
	vector<vector<vector<vector<elements>>>> s;

	for (vector<vector<vector<CPtrArray*>>>::iterator it = data.begin(); it != data.end(); ++it)
	{
		vector<vector<vector<elements>>> ss;
		for (vector<vector<CPtrArray*>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			vector<vector<elements>> sss;
			for (vector<CPtrArray*>::iterator itss = its->begin(); itss != its->end(); ++itss)
			{
				vector<elements> ssss = CalculateData(*itss);
				//��Ҫ����β������˵���
				CVector3D m_DirectionLine = ssss.begin()->end-ssss.begin()->begin;
				CVector3D m_NRotateLine = CVector3D(m_DirectionLine.dy, -m_DirectionLine.dx, 0).GetNormal();

				elements e1, e2;
				e1.begin = ssss.begin()->begin + m_NRotateLine*m_ExtendLength;
				e1.end = ssss.begin()->begin;
				e2.begin = (ssss.end() - 1)->end;
				e2.end = (ssss.end() - 1)->end + m_NRotateLine*m_ExtendLength;

				//��β�����
				ssss.insert(ssss.begin(), e1);
				ssss.insert(ssss.end(), e2);

				sss.push_back(ssss);
			}
			ss.push_back(sss);
		}
		s.push_back(ss);
	}

	return s;
}
//�ڲ�ϳ��
vector<vector<vector<vector<elements>>>> CTableBoardProcess::InitTableInMillNC(vector<vector<vector<CPtrArray*>>> data)
{
	vector<vector<vector<vector<elements>>>> s;

	for (vector<vector<vector<CPtrArray*>>>::iterator it = data.begin(); it != data.end(); ++it)
	{
		vector<vector<vector<elements>>> ss;
		for (vector<vector<CPtrArray*>>::iterator its = it->begin(); its != it->end(); ++its)
		{
			vector<vector<elements>> sss;
			//��ȥ��һ����в���
			for (vector<CPtrArray*>::iterator itss = its->begin()+1; itss != its->end(); ++itss)
			{
				vector<elements> ssss = CalculateData(*itss);
				vector<elements> m_ssss;
				//��Z������иı�,���洢����
				for (vector<elements>::iterator itsss = ssss.begin(); itsss!= ssss.end(); ++itsss)
				{
					elements e;
					e = *itsss;
					if (itsss->flag == 1)//ֱ��
					{
						vector<CPoint3D> m_PointSum = LineDiscrete(itsss->begin, itsss->end, m_B_FeedTime_Horizon, m_B_FeedSpeed_Horizon);

						if (itsss != ssss.end()-1)//�����һ���ı�����յ�
						{	
							e.begin.z = e.begin.z + m_MillCutDepth_Vertical;
							e.end.z = e.end.z - m_PerDownDis*m_PointSum.size() + m_MillCutDepth_Vertical;
						}
						else//���һ���ı�������
						{
							e.begin.z = e.begin.z + m_PerDownDis*m_PointSum.size();
						}
					}
					else if (itsss->flag == 2)//Բ��
					{
						if (itsss != ssss.end() - 1)//�ǵ�����һ��
						{
							vector<CPoint3D> m_PointSum = LineDiscrete((itsss-1)->begin, (itsss-1)->end, m_B_FeedTime_Horizon, m_B_FeedSpeed_Horizon);
							e.begin = (itsss - 1)->end;//Բ��������Ϊ��һ��Ԫ�ص��յ�
							e.begin.z = (itsss - 1)->end.z - m_PerDownDis*m_PointSum.size() + m_MillCutDepth_Vertical;
							m_PointSum = LineDiscrete((itsss + 1)->begin, (itsss +1)->end, m_B_FeedTime_Horizon, m_B_FeedSpeed_Horizon);

							e.end = (itsss + 1)->begin;//Բ�����յ��Ϊ��һ��Ԫ�ص����
							e.end.z = (itsss+1)->begin.z+m_PerDownDis*m_PointSum.size();
						}
					}

					m_ssss.push_back(e);
				}

				sss.push_back(m_ssss);
				sss.push_back(ssss);

				
			}
			ss.push_back(sss);
		}
		s.push_back(ss);
	}

	return s;
}
//�ⲿ��Ƭ
vector<vector<vector<elements>>> CTableBoardProcess::InitTableOutNC(vector<vector<CPtrArray*>> data)
{
	vector<vector<vector<elements>>> s;

	for (vector<vector<CPtrArray*>>::iterator it = data.begin(); it != data.end(); ++it)
	{
		vector<vector<elements>> ss;
		for (vector<CPtrArray*>::iterator its = it->begin(); its != it->end(); ++its)
		{
			vector<elements> sss = New_CalculateData(*its);
			//��sss�е���ʱ��Բ�����б��
			for (int i = 0; i != (*its)->GetSize();++i)
			{
				//Բ��
				if (((CArc*)(*its)->GetAt(i))->flag == 2)
				{
					//BOOL temp = CArc::Calculate(((CArc*)(*its)->GetAt(i))->m_center, ((CArc*)(*its)->GetAt(i))->m_radio,
						//((CArc*)(*its)->GetAt(i))->m_begin_angle, ((CArc*)(*its)->GetAt(i))->m_end_angle, **its, i);
					//if (i==5)//�̶�5��λ��Ϊ���
					if(((CArc*)(*its)->GetAt(i)) ->m_Direction)
					{
						sss[i].arc_direction = TRUE;//��ʱ��Ϊtrue
					}
				}
				
			}

			//��ÿ�����β��������㣬�ӳ�m_ExtendLength�ĳ���
			sss = InsertExtendLineElements(sss, m_ExtendLength);

			ss.push_back(sss);
		}
		s.push_back(ss);
	}
	return s;
}