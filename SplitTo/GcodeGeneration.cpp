#include "stdafx.h"
#include "GcodeGeneration.h"


CGcodeGeneration::CGcodeGeneration(CToolPath* tool)
{
	pTool=tool;
	FLAG = "";
}


CGcodeGeneration::~CGcodeGeneration()
{
}

void CGcodeGeneration::Init()
{
	if (pTool->GetRotateArray().IsEmpty()==0)//��ת�ӹ�
	{
		FLAG = _T("Rotate");
	}
	if (pTool->GetArray().IsEmpty() == 0)//����ӹ�
	{
		FLAG = _T("Side");
	}
	if (pTool->GetArcArray().IsEmpty()== 0)//˫����ӹ�
	{
		FLAG = _T("ARC");
	}
	if (pTool->GetLineArray().IsEmpty() == 0)//�����ӹ�
	{
		FLAG = _T("LineProcess");
	}
	if (pTool->RenderOrthgonalInit())
	{
		FLAG = _T("Orthgonal");
	}
	if (pTool->GetPolygeonPolyLine().size()!=0)
	{
		FLAG = _T("Polygon");
	}
	if (CTableBoardProcess::GetTableProcessInstance()->GetBoardArray() != NULL)
	{
		FLAG = _T("TableBoard");
	}
}

void CGcodeGeneration::OutPutNcCode()//��G���������
{
	CFileDialog openfile(FALSE, NULL, _T("*.nc"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		NULL, NULL);
	openfile.m_ofn.lpstrTitle = _T("л��NC���뱣�洰��");

	openfile.m_ofn.lpstrFilter = _T("�ı��ļ�(.txt)\0*.txt\0dxf�ļ�(.dxf)\0*.dxf\0NC�ļ�(.nc)\0*.nc\0�����ļ�(*.*)\0*.*\0\0");

	if (IDOK == openfile.DoModal())
	{
		ofstream outfile;//����д��
		outfile.open(openfile.GetPathName()); //myfile.bat�Ǵ�����ݵ��ļ���  
		if (outfile.is_open())
		{
			
			if (FLAG == "Rotate")
			{
				//outfile << "Hello!" << endl;    //message�ǳ����д�������� 
				RotateNC(&outfile);
			}
			else if (FLAG == "Side")
			{
				SideNC(&outfile);
			}
			else if (FLAG == "ARC")
			{
				ArcNC(&outfile);
			}
			else if (FLAG == "LineProcess")
			{
				LineNC(&outfile);
			}
			else if (FLAG == "Orthgonal")
			{
				OrthgonalNC(&outfile);
			}
			else if (FLAG == "Polygon")
			{
				PolygonNC(&outfile);
			}
			else if (FLAG == "TableBoard")
			{
				TableBoardNC(&outfile);
			}
			outfile.close();
			
		}
		else
		{
			AfxMessageBox(_T("���ܱ����ļ�"));
		}
	}

}
//��ת�ӹ�NC���������
void CGcodeGeneration::RotateNC(ofstream* of)
{
	//(*of) << "Hello" << endl;
	(*of) << "��ת�ӹ��ּӹ�NC���룺" << endl;
	vector<vector<vector<CPoint3D>>> temp = pTool->GetRotateRoughCutPoints();//��ȡ�ּӹ��ü���ĵ�
	vector<vector<vector<CPoint3D>>> tempRoughPoints = pTool->GetRotateRoughPoints();//��ȡ�ּӹ�δ���ü���ĵ�
	vector<vector<vector<CPoint3D>>> tempFinishPoints = pTool->GetRotateFinishPoints();//��ȡ���ӹ���


	CPoint3D CircleCenter = ((CCircle*)pTool->GetRotateArray().GetAt(0))->m_center;//���Բ������

	vector<vector<vector<CPoint3D>>>::iterator itRough = tempRoughPoints.begin();
	for (vector<vector<vector<CPoint3D>>>::iterator it = temp.begin(); it != temp.end(); ++it)
	{
		
		vector<vector<CPoint3D>>::reverse_iterator itsRough = itRough->rbegin();
		BOOL Direction = TRUE;
		for (vector<vector<CPoint3D>>::reverse_iterator its = it->rbegin(); its != it->rend(); ++its)
		{
			vector<CPoint3D>::iterator itssRough = itsRough->begin();//�ּӹ�δ���ü��ĳ�ʼ��

			if (Direction)//����Ĭ����ʱ��
			{
				if (its == it->rbegin())//ÿһ��ĵ�һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						CircleCenter.z = itss->z;
						//���벻��
						//double tempRadius = CLine::Length(*itss, CircleCenter);
						double tempRadius = CLine::Length(*itssRough, CircleCenter);
						CString str;
						//�㶨λ��̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						//�㶨λ��Բ�岹�����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss ->x, itss->y, itss->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						CPtrArray* Array=new CPtrArray;
						for (int j = 0; j != RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetSize(); ++j)
						{
							if (((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 1)
							{
								CLine* pLine = new CLine;
								Array->Add(pLine);
								pLine->m_begin = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pLine->m_end = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
							}
							else if (((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 2)
							{
								CArc* pArc = new CArc;
								Array->Add(pArc);
								pArc->m_begin = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pArc->m_end = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
								pArc->m_center = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_center;
								pArc->m_radio = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_radio;
							}
						}
						if (Array->IsEmpty() == 0)//�ǿ�
						{
							for (int i = 0; i != Array->GetSize(); ++i)
							{
								if (((CLine*)Array->GetAt(i))->flag==1)//ֱ��
								{
									str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_end.x, ((CLine*)Array->GetAt(i)) ->m_end.y,
										                         ((CLine*)Array->GetAt(i))->m_end.z);
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else if (((CArc*)Array->GetAt(i))->flag == 2)//Բ��
								{
									str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_end.y,
										((CArc*)Array->GetAt(i))->m_end.z, ((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_begin.x,
										((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_begin.y);
									//����ʵ�����
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
							}
						}
						else//���˾ͽ�����Բ�岹
						{
							//����Բ�岹(��Ҫ�ֱ���ֱ�߻���Բ��Ȼ�����ֱ�߲岹������Բ���岹)
							str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
								CircleCenter.x - itss->x, CircleCenter.y - itss->y);
							//����ʵ�����
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;

					}
				}
				else//��ÿһ��ĵ�һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						CircleCenter.z = itss->z;
						//double tempRadius = CLine::Length(*itss, CircleCenter);
						double tempRadius = CLine::Length(*itssRough, CircleCenter);
						CString str;
						//�㶨λ��̧����
						str.Format(_T("G00 Z%0.3f"), (itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//�㶨λ��Բ�岹�����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss->x, itss->y, itss->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//CPtrArray* Array=RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth());
						CPtrArray* Array = new CPtrArray;
						//��CPtrArray���ֵŪ����
						for (int j = 0; j != RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetSize(); ++j)
						{
							if (((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 1)
							{
								CLine* pLine = new CLine;
								Array->Add(pLine);
								pLine->m_begin = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pLine->m_end = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
							}
							else if (((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 2)
							{
								CArc* pArc = new CArc;
								Array->Add(pArc);
								pArc->m_begin = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pArc->m_end = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
								pArc->m_center = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_center;
								pArc->m_radio = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_radio;
							}
						}

						if (Array->IsEmpty() == 0)//�ǿ�
						{
							for (int i = 0; i != Array->GetSize(); ++i)
							{
								if (((CLine*)Array->GetAt(i))->flag == 1)//ֱ��
								{
									str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_end.x, ((CLine*)Array->GetAt(i))->m_end.y,
										((CLine*)Array->GetAt(i))->m_end.z);
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else if (((CArc*)Array->GetAt(i))->flag == 2)//Բ��
								{
									str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_end.y,
										((CArc*)Array->GetAt(i))->m_end.z, ((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_begin.x,
										((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_begin.y);
									//����ʵ�����
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
							}
						}
						else
						{
							//��ʼ��Բ�岹
							str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
								CircleCenter.x - itss->x, CircleCenter.y - itss->y);
							//����ʵ�����
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
			}
			else//����
			{
				if (its == it->rbegin())//ÿһ��ĵ�һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						CircleCenter.z = itss->z;
						//double tempRadius = CLine::Length(*itss, CircleCenter);
						double tempRadius = CLine::Length(*itssRough, CircleCenter);
						CString str;
						//�㶨λ��̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//�㶨λ��Բ�岹�����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss->x, itss->y, itss->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;


						CPtrArray* Array = new CPtrArray;
						for (int j = 0; j != RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetSize(); ++j)
						{
							if (((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 1)
							{
								CLine* pLine = new CLine;
								Array->Add(pLine);
								pLine->m_begin = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pLine->m_end = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
							}
							else if (((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 2)
							{
								CArc* pArc = new CArc;
								Array->Add(pArc);
								pArc->m_begin = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pArc->m_end = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
								pArc->m_center = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_center;
								pArc->m_radio = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_radio;
							}
						}
						if (Array->IsEmpty() == 0)//�ǿ�
						{
							for (int i = Array->GetSize()-1; i != -1; --i)
							{
								if (((CLine*)Array->GetAt(i))->flag == 1)//ֱ��
								{
									str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.x, ((CLine*)Array->GetAt(i))->m_begin.y,
										((CLine*)Array->GetAt(i))->m_begin.z);
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else if (((CArc*)Array->GetAt(i))->flag == 2)//Բ��
								{
									str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_begin.y,
										((CArc*)Array->GetAt(i))->m_begin.z, ((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_end.x,
										((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_end.y);
									//����ʵ�����
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
							}
						}
				        else
				       {
					       //��ʼ��Բ�岹
					       str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
						    CircleCenter.x - itss->x, CircleCenter.y - itss->y);
					        //����ʵ�����
					        STR = CStringA(str);
					         (*of) << STR.c_str() << endl;
				        }

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
				else//��ÿһ��ĵ�һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						CircleCenter.z = itss->z;
						//double tempRadius = CLine::Length(*itss, CircleCenter);
						double tempRadius = CLine::Length(*itssRough, CircleCenter);

						CString str;
						//�㶨λ��̧����
						str.Format(_T("G00 Z%0.3f"), (itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//�㶨λ��Բ�岹�����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss->x, itss->y, itss->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;


						CPtrArray* Array = new CPtrArray;
						for (int j = 0; j != RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetSize(); ++j)
						{
							if (((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 1)
							{
								CLine* pLine = new CLine;
								Array->Add(pLine);
								pLine->m_begin = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pLine->m_end = ((CLine*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
							}
							else if (((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->flag == 2)
							{
								CArc* pArc = new CArc;
								Array->Add(pArc);
								pArc->m_begin = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_begin;
								pArc->m_end = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_end;
								pArc->m_center = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_center;
								pArc->m_radio = ((CArc*)RotateCalculate(CircleCenter, tempRadius, pTool->GetRotateBlankLongth(), pTool->GetRotateBlankWidth())->GetAt(j))->m_radio;
							}
						}
						if (Array->IsEmpty() == 0)//�ǿ�
						{
							for (int i = Array->GetSize() - 1; i != -1; --i)
							{
								if (((CLine*)Array->GetAt(i))->flag == 1)//ֱ��
								{
									str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.x, ((CLine*)Array->GetAt(i))->m_begin.y,
										((CLine*)Array->GetAt(i))->m_begin.z);
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else if (((CArc*)Array->GetAt(i))->flag == 2)//Բ��
								{
									str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_begin.y,
										((CArc*)Array->GetAt(i))->m_begin.z, ((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_end.x,
										((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_end.y);
									//����ʵ�����
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
							}
						}
						else
						{
							//��ʼ��Բ�岹
							str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
								CircleCenter.x - itss->x, CircleCenter.y - itss->y);
							//����ʵ�����
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
			}
			Direction = !Direction;

			++itsRough;//�ּӹ�ÿ����������ƶ�
		}

		++itRough;//�ּӹ����������ƶ�
	}

	(*of) << "��ת�ӹ����ӹ�NC���룺" << endl;
	for (vector<vector<vector<CPoint3D>>>::iterator it = tempFinishPoints.begin(); it != tempFinishPoints.end(); ++it)
	{
		BOOL Direction = TRUE;
		for (vector<vector<CPoint3D>>::reverse_iterator its = it->rbegin(); its != it->rend(); ++its)
		{
			if (Direction)//����ԭ�ȵķ���˳��
			{
				if (its == it->rbegin())//��һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						//�㶨λ��̧����
						CString str;
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						//�㶨λ�������
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss->x, itss->y, itss->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//��ʼ��Բ�岹
						str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
							CircleCenter.x - itss->x, CircleCenter.y - itss->y);
						//����ʵ�����
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
				else//���ǵ�һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						//�㶨λ��̧����
						CString str;
						str.Format(_T("G00 Z%0.3f"),(itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						//�㶨λ�������
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss->x, itss->y, itss->z);
						 STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//��ʼ��Բ�岹
						str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
							CircleCenter.x - itss->x, CircleCenter.y - itss->y);
						//����ʵ�����
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
			}
			else//����
			{
				if (its == it->rbegin())//����������ڵ�һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						//�㶨λ��̧����
						CString str;
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						//�㶨λ�������
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss->x, itss->y, itss->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//��ʼ��Բ�岹
						str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
							CircleCenter.x - itss->x, CircleCenter.y - itss->y);
						//����ʵ�����
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}

				}
				else//���ڵ�һȦ
				{
					for (vector<CPoint3D>::iterator itss = its->begin() + 1; itss != its->begin() + 2; ++itss)
					{
						//�㶨λ��̧����
						CString str;
						str.Format(_T("G00 Z%0.3f"), (itss - 1)->z);
						std::string STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						//�㶨λ�������
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), itss->x, itss->y, itss->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//��ʼ��Բ�岹
						str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), itss->x, itss->y, itss->z,
							CircleCenter.x - itss->x, CircleCenter.y - itss->y);
						//����ʵ�����
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						//�ص�̧����
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), (itss - 1)->x, (itss - 1)->y, (itss - 1)->z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
			}
			Direction = !Direction;
		}
	}
}

CPtrArray* CGcodeGeneration::RotateCalculate(CPoint3D circlecenter, float circleradius, float workBlankLong, float workBlankWidth)
{
	CPtrArray tempArray;
	CPoint3D EnterPoint;

	//��ȡ�������������ֵ
	CPoint3D CornerPointRT;//���ϽǵĶ���
	CornerPointRT.x = circlecenter.x + workBlankLong / 2;
	CornerPointRT.y = circlecenter.y + workBlankWidth / 2;
	CornerPointRT.z = circlecenter.z;

	CPoint3D CornerPointRB;//���½ǵĶ���
	CornerPointRB.x = circlecenter.x + workBlankLong / 2;
	CornerPointRB.y = circlecenter.y - workBlankWidth / 2;
	CornerPointRB.z = circlecenter.z;

	CPoint3D CornerPointLT;//���ϽǵĶ���
	CornerPointLT.x = circlecenter.x - workBlankLong / 2;
	CornerPointLT.y = circlecenter.y + workBlankWidth / 2;
	CornerPointLT.z = circlecenter.z;

	CPoint3D CornerPointLB;//���½ǵĶ���
	CornerPointLB.x = circlecenter.x - workBlankLong / 2;
	CornerPointLB.y = circlecenter.y - workBlankWidth / 2;
	CornerPointLB.z = circlecenter.z;

	float Distance = CLine::Length(circlecenter, CornerPointRT);//��ȡԲ�ĵ����ϽǵĶ���ľ���

	float min;//�Ƚϻ�ȡ��Сֵ���洢����
	float max;
	if (workBlankLong > workBlankWidth)
	{
		min = workBlankWidth/2;
		max = workBlankLong/2;
	}
	else
	{
		min = workBlankLong/2;
		max = workBlankWidth/2;
	}

	if (circleradius > min&&circleradius<max)//˵��Բ��������н����,����ֻ�г����߿���Բ�н���
	{
		if (min == workBlankLong/2)
		{
			float Juge1 = pow(circleradius, 2) - pow(CornerPointRT.x - circlecenter.x, 2);
			if (Juge1 >= 0)
			{
				vector<sort> pos;
				sort pts;
				//ֱ��
				pts.begin.x = CornerPointRB.x;
				pts.begin.y = circlecenter.y;
				pts.begin.z = CornerPointRB.z;
				pts.end.x = CornerPointRB.x;
				pts.end.y = circlecenter.y + sqrt(Juge1);
				pts.end.z = CornerPointRT.z;
				pts.flag = 1;
				pos.push_back(pts);

				//Բ��
				pts.begin.x = CornerPointRB.x;
				pts.begin.y = circlecenter.y + sqrt(Juge1);
				pts.begin.z = CornerPointRT.z;
				pts.end.x = CornerPointLT.x;
				pts.end.y = circlecenter.y + sqrt(Juge1);
				pts.end.z = CornerPointLT.z;
				pts.flag = 2;
				pos.push_back(pts);
				//ֱ��
				pts.begin.x = CornerPointLT.x;
				pts.begin.y = circlecenter.y + sqrt(Juge1);
				pts.begin.z = CornerPointLT.z;
				pts.end.x = CornerPointLB.x;
				pts.end.y = circlecenter.y - sqrt(Juge1);
				pts.end.z = CornerPointLB.z;
				pts.flag = 1;
				pos.push_back(pts);
				//Բ��
				pts.begin.x = CornerPointLB.x;
				pts.begin.y = circlecenter.y - sqrt(Juge1);
				pts.begin.z = CornerPointLB.z;
				pts.end.x = CornerPointRB.x;
				pts.end.y = circlecenter.y - sqrt(Juge1);
				pts.end.z = CornerPointRB.z;
				pts.flag = 2;
				pos.push_back(pts);
				//ֱ��
				pts.begin.x = CornerPointRB.x;
				pts.begin.y = circlecenter.y - sqrt(Juge1);
				pts.begin.z = CornerPointRB.z;
				pts.end.x = CornerPointRB.x;
				pts.end.y = circlecenter.y;
				pts.end.z = CornerPointRB.z;
				pts.flag = 1;
				pos.push_back(pts);

				for (vector<sort>::iterator it = pos.begin(); it != pos.end(); ++it)
				{
					if (it->flag == 1)
					{
						CLine* pLine = new CLine;
						tempArray.Add(pLine);
						pLine->m_begin = it->begin;
						pLine->m_end = it->end;

					}
					else
					{
						CArc* pArc = new CArc;
						tempArray.Add(pArc);
						pArc->m_begin = it->begin;
						pArc->m_end = it->end;
						pArc->m_center = circlecenter;
						pArc->m_radio = circleradius;
					}
				}
			}

		}
		else if (min==workBlankWidth/2)
		{
			float Juge2 = pow(circleradius, 2) - pow(CornerPointRT.y - circlecenter.y, 2);
			if (Juge2 >= 0)
			{
				vector<sort> pos;
				sort pts;
				//Բ��
				pts.begin.x = circlecenter.x + circleradius;
				pts.begin.y = circlecenter.y;
				pts.begin.z = circlecenter.z;
				pts.end.x = circlecenter.x + sqrt(Juge2);
				pts.end.y = CornerPointRT.y;
				pts.end.z = CornerPointRT.z;
				pts.flag = 2;
				pos.push_back(pts);
				//ֱ��
				pts.begin.x = circlecenter.x + sqrt(Juge2);
				pts.begin.y = CornerPointRT.y;
				pts.begin.z = CornerPointRT.z;
				pts.end.x = circlecenter.x - sqrt(Juge2);
				pts.end.y = CornerPointLT.y;
				pts.end.z = CornerPointLT.z;
				pts.flag = 1;
				pos.push_back(pts);
				//Բ��
				pts.begin.x = circlecenter.x - sqrt(Juge2);
				pts.begin.y = CornerPointLT.y;
				pts.begin.z = CornerPointLT.z;
				pts.end.x = circlecenter.x - sqrt(Juge2);
				pts.end.y = CornerPointLB.y;
				pts.end.z = CornerPointLB.z;
				pts.flag = 2;
				pos.push_back(pts);
				//ֱ��
				pts.begin.x = circlecenter.x - sqrt(Juge2);
				pts.begin.y = CornerPointLB.y;
				pts.begin.z = CornerPointLB.z;
				pts.end.x = circlecenter.x + sqrt(Juge2);
				pts.end.y = CornerPointRB.y;
				pts.end.z = CornerPointRB.z;
				pts.flag = 1;
				pos.push_back(pts);
				//Բ��
				pts.begin.x = circlecenter.x + sqrt(Juge2);
				pts.begin.y = CornerPointRB.y;
				pts.begin.z = CornerPointRB.z;
				pts.end.x = circlecenter.x + circleradius;
				pts.end.y = circlecenter.y;
				pts.end.z = circlecenter.z;
				pts.flag = 2;
				pos.push_back(pts);

				for (vector<sort>::iterator it = pos.begin(); it != pos.end(); ++it)
				{
					if (it->flag == 1)
					{
						CLine* pLine = new CLine;
						tempArray.Add(pLine);
						pLine->m_begin = it->begin;
						pLine->m_end = it->end;

					}
					else
					{
						CArc* pArc = new CArc;
						tempArray.Add(pArc);
						pArc->m_begin = it->begin;
						pArc->m_end = it->end;
						pArc->m_center = circlecenter;
						pArc->m_radio = circleradius;
					}
				}

			}
		}
	}
	else if (circleradius >= max&&circleradius<Distance)//�뾶�ĳ��Ȼ�δ���︲�Ƕ���ĳ��ȣ�������ȫ�����н���
	{
		vector<sort> pos;
		float Juge1 = pow(circleradius, 2) - pow(CornerPointRT.x - circlecenter.x, 2);//Ϊ�Ҳ������Ϊ�����㣬Բ��ֱ���󽻵㣬������봹ֱ��,�ɸ��ݶԳ���ȡ������������Բ����
		float Juge2 = pow(circleradius, 2) - pow(CornerPointRT.y - circlecenter.y, 2);//Բ��ֱ���󽻵㣬�������ˮƽ��
		if (Juge1 >= 0 && Juge2 >= 0)//�н���������ȡ
		{
			sort pts;
			//ֱ�߲���
			pts.begin.x = CornerPointRT.x;
			pts.begin.y = circlecenter.y;
			pts.begin.z = CornerPointRT.z;
			pts.end.x = CornerPointRT.x;
			pts.end.y = circlecenter.y + sqrt(Juge1);
			pts.end.z = CornerPointRT.z;
			pts.flag = 1;//��ʾֱ��
			pos.push_back(pts);
			//Բ����
			pts.begin.x = CornerPointRT.x;
			pts.begin.y = circlecenter.y + sqrt(Juge1);
			pts.begin.z = CornerPointRT.z;
			pts.end.x = circlecenter.x + sqrt(Juge2);
			pts.end.y = CornerPointRT.y;
			pts.end.z = CornerPointRT.z;
			pts.flag = 2;//��ʾԲ��
			pos.push_back(pts);

			//ֱ�߶ζ���
			pts.begin.x = circlecenter.x + sqrt(Juge2);
			pts.begin.y = CornerPointRT.y;
			pts.begin.z = CornerPointRT.z;
			pts.end.x = circlecenter.x -sqrt(Juge2);
			pts.end.y = CornerPointLT.y;
			pts.end.z = CornerPointLT.z;
			pts.flag = 1;//��ʾֱ��
			pos.push_back(pts);

			//Բ����
			pts.begin.x = circlecenter.x - sqrt(Juge2);
			pts.begin.y = CornerPointLT.y;
			pts.begin.z = CornerPointLT.z;
			pts.end.x = CornerPointLT.x;
			pts.end.y = circlecenter.y + sqrt(Juge1);
			pts.end.z = CornerPointLT.z;
			pts.flag = 2;//��ʾԲ��
			pos.push_back(pts);

			//ֱ�߶�
			pts.begin.x = CornerPointLT.x;
			pts.begin.y = circlecenter.y + sqrt(Juge1);
			pts.begin.z = CornerPointLT.z;
			pts.end.x = CornerPointLT.x;
			pts.end.y = circlecenter.y - sqrt(Juge1);
			pts.end.z = CornerPointLT.z;
			pts.flag = 1;//��ʾֱ��
			pos.push_back(pts);

			//Բ��
			pts.begin.x = CornerPointLT.x;
			pts.begin.y = circlecenter.y - sqrt(Juge1);
			pts.begin.z = CornerPointLT.z;
			pts.end.x = circlecenter.x - sqrt(Juge2);
			pts.end.y = CornerPointLB.y;
			pts.end.z = CornerPointLB.z;
			pts.flag = 2;//��ʾԲ��
			pos.push_back(pts);

			//ֱ��
			pts.begin.x = circlecenter.x - sqrt(Juge2);
			pts.begin.y = CornerPointLB.y;
			pts.begin.z = CornerPointLB.z;
			pts.end.x = circlecenter.x+ sqrt(Juge2);
			pts.end.y = CornerPointLB.y;
			pts.end.z = CornerPointLB.z;
			pts.flag = 1;//��ʾֱ��
			pos.push_back(pts);

			//Բ��
			pts.begin.x = circlecenter.x + sqrt(Juge2);
			pts.begin.y = CornerPointRB.y;
			pts.begin.z = CornerPointRB.z;
			pts.end.x = CornerPointRB.x;
			pts.end.y = circlecenter.y - sqrt(Juge1);
			pts.end.z = CornerPointRB.z;
			pts.flag = 2;//��ʾԲ��
			pos.push_back(pts);

			//ֱ��
			pts.begin.x = CornerPointRB.x;
			pts.begin.y = circlecenter.y - sqrt(Juge1);
			pts.begin.z = CornerPointRB.z;
			pts.end.x = CornerPointRB.x;
			pts.end.y = circlecenter.y;
			pts.end.z = CornerPointRB.z;
			pts.flag = 1;//��ʾֱ��
			pos.push_back(pts);

			for (vector<sort>::iterator it = pos.begin(); it != pos.end(); ++it)
			{
				if (it->flag == 1)//ֱ��
				{
					CLine* pLine = new CLine;
					tempArray.Add(pLine);
					pLine->m_begin = it->begin;
					pLine->m_end = it->end;
				}
				else if (it->flag==2)//Բ��
				{
					CArc* pArc = new CArc;
					tempArray.Add(pArc);
					pArc->m_begin = it->begin;
					pArc->m_end = it->end;
					pArc->m_center = circlecenter;
					pArc->m_radio = circleradius;
				}
			}

		}
	}
	else if (circleradius >= Distance)//Բ�뾶���ڵ������ĵ㵽����ľ��룬��ʱ���ž�����������,������ʱ��
	{
		CLine* Line1 = new CLine;
		tempArray.Add(Line1);
		Line1->m_begin.x = CornerPointRT.x;
		Line1->m_begin.y = circlecenter.y;
		Line1->m_begin.z = CornerPointRT.z;
		Line1->m_end = CornerPointRT;

		CLine* Line2 = new CLine;
		tempArray.Add(Line2);
		Line2->m_begin = CornerPointRT;
		Line2->m_end = CornerPointLT;

		CLine* Line3 = new CLine;
		tempArray.Add(Line3);
		Line3->m_begin = CornerPointLT;
		Line3->m_end = CornerPointLB;

		CLine* Line4 = new CLine;
		tempArray.Add(Line4);
		Line4->m_begin = CornerPointLB;
		Line4->m_end = CornerPointRB;

		CLine* Line5 = new CLine;
		tempArray.Add(Line5);
		Line5->m_begin = CornerPointRB;
		Line5->m_end.x = CornerPointRB.x;
		Line5->m_end.y = circlecenter.y;
		Line5->m_end.z = CornerPointRB.z;

		
	}
	else//�뾶С����Сֵ˵���ھ���������������֣�ֱ�ӽ���Բ�岹����
	{

	}

	return &tempArray;
}

//����ӹ�NC���������

BOOL CGcodeGeneration::SideNCInit()
{
		vector<vector<CPtrArray*>>().swap(m_EverySideRoughPile);
		vector<CPtrArray*> SideRoughArrayList = pTool->GetArrayRoughList();//��ȡ�ּӹ�����ƫ������

	    for (vector<CPtrArray*>::iterator it = SideRoughArrayList.begin(); it != SideRoughArrayList.end(); ++it)
		{
			vector<CPtrArray*> temp;

			for (int i = 0; i != (*it)->GetSize(); ++i)
			{
				if (i > pTool->mark)//Ԫ�ظ������ڵ���ĸ�����ʱ��ſ�ʼ��
				{

					if (((CLine*)(*it)->GetAt(i))->flag == 1)//ֱ��
					{
						//��ɢ
						vector<CPoint3D> offsetPoints = pTool->LineDiscreteXZ(((CLine*)(*it)->GetAt(i))->m_begin, ((CLine*)(*it)->GetAt(i))->m_end, 
							                                                              pTool->GetTime(),pTool->GetFeedspeed() );
						//��ȡÿ���߶��ϵ�Ԫ�ؼ���˳����Ϣ������
						for (vector<CPoint3D>::iterator its = offsetPoints.begin(); its != offsetPoints.end(); ++its)
						{
							CPoint3D m_XFPoint = *its;
							m_XFPoint.z = 0.0;
							double distance = CLine::Length(pTool->XMax, m_XFPoint);
							CPtrArray* Array =SideNCOffsetAlgorithm((**it),pTool->mark,distance);
							
							//��Z�߶�ֵ���и�ֵ
							for (int j = 0; j != Array->GetSize(); ++j)
							{
								if (((CLine*)Array->GetAt(j))->flag == 1)
								{
									((CLine*)Array->GetAt(j))->m_begin.z = its->z;
									((CLine*)Array->GetAt(j))->m_end.z = its->z;
									CPoint3D pt1 = ((CLine*)Array->GetAt(j))->m_begin;
									CPoint3D pt2 = ((CLine*)Array->GetAt(j))->m_end;
								}
								else if (((CArc*)Array->GetAt(j))->flag == 2)
								{
									if (((CArc*)Array->GetAt(j))->m_Tudu == 0)
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;
										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;
									}
									else
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;

										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;
									}
								}

							}

							temp.push_back(Array);
							//SideRoughArrayList.push_back(Array);

						}
					}
					else if (((CArc*)(*it)->GetAt(i))->flag == 2)//Բ��
					{
						vector<CPoint3D> offsetPoints;
						if (((CArc*)(*it)->GetAt(i))->m_Tudu == 0)//��ͨԲ��
						{
							offsetPoints = pTool->ArcDiscreteXZ(((CArc*)(*it)->GetAt(i))->m_center, ((CArc*)(*it)->GetAt(i))->m_radio, ((CArc*)(*it)->GetAt(i))->m_begin_angle,
								((CArc*)(*it)->GetAt(i))->m_end_angle, **it, i, pTool->GetTime(), pTool->GetFeedspeed());
						}
						else//���߶�Բ��
						{
							offsetPoints = pTool->PolyArcDiscreteXZ(((CArc*)(*it)->GetAt(i))->m_begin, ((CArc*)(*it)->GetAt(i))->m_end,
								((CArc*)(*it)->GetAt(i))->m_Tudu, pTool->GetTime(), pTool->GetFeedspeed());
						}

						for (vector<CPoint3D>::iterator its = offsetPoints.begin(); its != offsetPoints.end(); ++its)
						{
							CPoint3D m_XFPoint = *its;
							m_XFPoint.z = 0.0;
							double distance = CLine::Length(pTool->XMax, m_XFPoint);
							CPtrArray* Array = SideNCOffsetAlgorithm(**it, pTool->mark, distance);

							for (int j = 0; j != Array->GetSize(); ++j)
							{
								if (((CLine*)Array->GetAt(j))->flag == 1)
								{
									((CLine*)Array->GetAt(j))->m_begin.z = its->z;
									((CLine*)Array->GetAt(j))->m_end.z = its->z;
									CPoint3D pt1 = ((CLine*)Array->GetAt(j))->m_begin;
									CPoint3D pt2 = ((CLine*)Array->GetAt(j))->m_end;
								}
								else if (((CArc*)Array->GetAt(j))->flag == 2)
								{
									if (((CArc*)Array->GetAt(j))->m_Tudu == 0)
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;

										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;

									}
									else
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;

										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;
									}
								}

							}
							temp.push_back(Array);
							//SideRoughArrayList.push_back(Array);
						}

					}
				}

			}

			m_EverySideRoughPile.push_back(temp);
			vector<CPtrArray*>().swap(temp);
		}

		//�ּӹ��ֲ㣬�������ڣ���������
		//����ÿ������εĽ������½���ÿ��ĵ��ָ�뼯��
		vector<vector<vector<TypeSort>>>().swap(m_SideRough);//��� �洢���������е�
		vector<vector<vector<TypeSort>>> m_TempSideRough;//�洢��ɢ������е�
		vector<vector<vector<CPoint3D>>> m_SideRoughCutPoints = pTool->GetRoughCutPoints();//��ȡ�ü���ּӹ��ĵ�
		for (vector<vector<CPtrArray*>>::iterator it = m_EverySideRoughPile.begin(); it != m_EverySideRoughPile.end(); ++it)
		{
			vector<vector<TypeSort>> TempOnePile;
			for (vector<CPtrArray*>::reverse_iterator its = it->rbegin(); its != it->rend(); ++its)
			{
				//CPtrArray* Array = SideCalculate(**its, pTool->GetCenter(), pTool->GetLongth(), pTool->GetWidth());
				vector<TypeSort> Temp;
				for (int i = 0; i != (*its)->GetSize(); ++i)
				{
					if (((CLine*)(*its)->GetAt(i))->flag == 1)//��ֱ��
					{
						vector<CPoint3D> points = pTool->LineDiscrete(((CLine*)(*its)->GetAt(i))->m_begin, ((CLine*)(*its)->GetAt(i))->m_end,
							30, 1000);
						for (vector<CPoint3D>::iterator itss = points.begin(); itss != points.end(); ++itss)
						{
							TypeSort pt;
							itss->z = ((CLine*)(*its)->GetAt(i))->m_begin.z;
							pt.position = *itss;
							pt.flag = 1;
							pt.center = CPoint3D(0, 0, 0);
							Temp.push_back(pt);
						}

					}
					else if (((CArc*)(*its)->GetAt(i))->flag == 2)
					{//0510
						//����Բ��˳ʱ��
						vector<CPoint3D> points = CArc::ArcTDMInterpolation(((CArc*)(*its)->GetAt(i))->m_center, ((CArc*)(*its)->GetAt(i))->m_radio,
							0,((CArc*)(*its)->GetAt(i))->m_begin, ((CArc*)(*its)->GetAt(i))->m_end, 30, 1000);
						for (vector<CPoint3D>::iterator itss = points.begin(); itss != points.end(); ++itss)
						{
							TypeSort pt;
							itss->z = ((CArc*)(*its)->GetAt(i)) ->m_center.z;
							pt.position = *itss;
							pt.flag = 2;//��ʾԲ��
							pt.center = ((CArc*)(*its)->GetAt(i))->m_center;
							Temp.push_back(pt);
						}
					}

				}
				TempOnePile.push_back(Temp);
				vector<TypeSort>().swap(Temp);
			}
			m_TempSideRough.push_back(TempOnePile);
			vector<vector<TypeSort>>().swap(TempOnePile);
		}
		//2016.5.9����m_TempSideRough����ĵ���Ҫ�ֵ��ܵ㾫�ȲŻ���ߣ��ж��ھ����ڵĵ�ͱ�����������ĵ�Ͳ�Ҫ�ˣ�֮�������ӽضϵĵ㣬���ӿɵõ���Ӧ�ضϺ��ͼ�Ρ�
		for (vector<vector<vector<TypeSort>>>::iterator it = m_TempSideRough.begin(); it != m_TempSideRough.end(); ++it)
		{
			vector<vector<TypeSort>> TempOnePile;
			for (vector<vector<TypeSort>>::iterator its = it->begin(); its != it->end(); ++its)
			{
				vector<TypeSort> Temp;
				for (vector<TypeSort>::iterator itss = its->begin(); itss != its->end(); ++itss)
				{
					BOOL m_JUGE = JugeInSide(itss->position, pTool->GetCenter(), pTool->GetLongth(), pTool->GetWidth());
					//if (m_JUGE)//�ھ������򱣴�����
						
						if (!m_JUGE)//���ھ�����ĵ���Ϊֱ��
						{
							itss->flag = 1;
							itss->center = CPoint3D(0, 0, 0);
						}
						Temp.push_back(*itss);
				}
				TempOnePile.push_back(Temp);
				vector<TypeSort>().swap(Temp);
			}
			m_SideRough.push_back(TempOnePile);
			vector<vector<TypeSort>>().swap(TempOnePile);
		}

		//���ӹ�������ȡ2016.5.12
		vector<vector<CPtrArray*>>().swap(m_SideNCFinish);
		vector<CPtrArray*> SideFinishArrayList = pTool->GetArrayFinishList();//��ȡ���ӹ�����ƫ������
		for (vector<CPtrArray*>::iterator it = SideFinishArrayList.begin(); it != SideFinishArrayList.end(); ++it)
		{
			vector<CPtrArray*> temp;
			for (int i = 0; i != (*it)->GetSize(); ++i)
			{
				if (i > pTool->mark)//Ԫ�ظ������ڵ���ĸ�����ʱ��ſ�ʼ��
				{
					if (((CLine*)(*it)->GetAt(i))->flag == 1)//ֱ��
					{
						//��ɢ
						vector<CPoint3D> offsetPoints = pTool->LineDiscreteXZ(((CLine*)(*it)->GetAt(i))->m_begin, ((CLine*)(*it)->GetAt(i))->m_end,
							pTool->GetTime(), pTool->GetFeedspeed());
						//��ȡÿ���߶��ϵ�Ԫ�ؼ���˳����Ϣ������
						for (vector<CPoint3D>::iterator its = offsetPoints.begin(); its != offsetPoints.end(); ++its)
						{
							CPoint3D m_XFPoint = *its;
							m_XFPoint.z = 0.0;
							double distance = CLine::Length(pTool->XMax, m_XFPoint);
							CPtrArray* Array = SideNCOffsetAlgorithm((**it), pTool->mark, distance);

							//��Z�߶�ֵ���и�ֵ
							for (int j = 0; j != Array->GetSize(); ++j)
							{
								if (((CLine*)Array->GetAt(j))->flag == 1)
								{
									((CLine*)Array->GetAt(j))->m_begin.z = its->z;
									((CLine*)Array->GetAt(j))->m_end.z = its->z;
									CPoint3D pt1 = ((CLine*)Array->GetAt(j))->m_begin;
									CPoint3D pt2 = ((CLine*)Array->GetAt(j))->m_end;
								}
								else if (((CArc*)Array->GetAt(j))->flag == 2)
								{
									if (((CArc*)Array->GetAt(j))->m_Tudu == 0)
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;
										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;
									}
									else
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;

										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;
									}
								}

							}

							temp.push_back(Array);

						}
					}
					else if (((CArc*)(*it)->GetAt(i))->flag == 2)//Բ��
					{
						vector<CPoint3D> offsetPoints;
						if (((CArc*)(*it)->GetAt(i))->m_Tudu == 0)//��ͨԲ��
						{
							offsetPoints = pTool->ArcDiscreteXZ(((CArc*)(*it)->GetAt(i))->m_center, ((CArc*)(*it)->GetAt(i))->m_radio, ((CArc*)(*it)->GetAt(i))->m_begin_angle,
								((CArc*)(*it)->GetAt(i))->m_end_angle, **it, i, pTool->GetTime(), pTool->GetFeedspeed());
						}
						else//���߶�Բ��
						{
							offsetPoints = pTool->PolyArcDiscreteXZ(((CArc*)(*it)->GetAt(i))->m_begin, ((CArc*)(*it)->GetAt(i))->m_end,
								((CArc*)(*it)->GetAt(i))->m_Tudu, pTool->GetTime(), pTool->GetFeedspeed());
						}

						for (vector<CPoint3D>::iterator its = offsetPoints.begin(); its != offsetPoints.end(); ++its)
						{
							CPoint3D m_XFPoint = *its;
							m_XFPoint.z = 0.0;
							double distance = CLine::Length(pTool->XMax, m_XFPoint);
							CPtrArray* Array = SideNCOffsetAlgorithm(**it, pTool->mark, distance);

							for (int j = 0; j != Array->GetSize(); ++j)
							{
								if (((CLine*)Array->GetAt(j))->flag == 1)
								{
									((CLine*)Array->GetAt(j))->m_begin.z = its->z;
									((CLine*)Array->GetAt(j))->m_end.z = its->z;
									CPoint3D pt1 = ((CLine*)Array->GetAt(j))->m_begin;
									CPoint3D pt2 = ((CLine*)Array->GetAt(j))->m_end;
								}
								else if (((CArc*)Array->GetAt(j))->flag == 2)
								{
									if (((CArc*)Array->GetAt(j))->m_Tudu == 0)
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;

										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;

									}
									else
									{
										((CArc*)Array->GetAt(j))->m_center.z = its->z;
										((CArc*)Array->GetAt(j))->m_begin.z = its->z;
										((CArc*)Array->GetAt(j))->m_end.z = its->z;

										CPoint3D pt1 = ((CArc*)Array->GetAt(j))->m_begin;
										CPoint3D pt2 = ((CArc*)Array->GetAt(j))->m_end;
										CPoint3D pt3 = ((CArc*)Array->GetAt(j))->m_center;
										float RADIUS = ((CArc*)Array->GetAt(j))->m_radio;
									}
								}

							}
							temp.push_back(Array);
						}

					}
				}

			}

			m_SideNCFinish.push_back(temp);
			vector<CPtrArray*>().swap(temp);
		}

	if (m_SideRough.size() != 0&&m_SideNCFinish.size()!=0)//2016.5.12
		return TRUE;
	else
		return FALSE;
}
BOOL CGcodeGeneration::JugeInSide(CPoint3D& pos, CPoint3D center, float workBlankLong, float workBlankWidth)
{
		WorkBlankRect rec;
		//�������Ͻǵ�
		rec.LeftTop.x = center.x - workBlankLong*0.5;
		rec.LeftTop.y = center.y + workBlankWidth*0.5;
		rec.LeftTop.z = center.z;
		
		//�������½ǵ�
		rec.LeftBottom.x = center.x - workBlankLong*0.5;
		rec.LeftBottom.y = center.y - workBlankWidth*0.5;
		rec.LeftBottom.z = center.z;
	
		//�������Ͻǵ�
		rec.RightTop.x = center.x + workBlankLong*0.5;
		rec.RightTop.y = center.y + workBlankWidth*0.5;
		rec.RightTop.z = center.z;
	
		//�������½ǵ�
		rec.RightBottom.x = center.x + workBlankLong*0.5;
		rec.RightBottom.y = center.y - workBlankWidth*0.5;
		rec.RightBottom.z = center.z;

			if (pos.x <= rec.RightTop.x&&pos.x >= rec.LeftTop.x)//����X��������֮��
			{
				if (pos.y <= rec.RightTop.y&&pos.y >= rec.LeftBottom.y)//����Y���������Сֵ֮��
				{
					return TRUE;
				}
				else if (pos.y >=rec.RightTop.y)//��Y���ֵ�Ϸ�
				{
					pos.y = rec.RightTop.y;
					return FALSE;
				}
				else if (pos.y <= rec.LeftBottom.y)//��Y��Сֵ�·�
				{
					pos.y = rec.LeftBottom.y;
					return FALSE;
				}
			}
			else
			{
				if (pos.x >= rec.RightTop.x)//���ұ�
				{
					if (pos.y <= rec.RightTop.y&&pos.y >= rec.LeftBottom.y)//����Y���������Сֵ֮��
					{
						pos.x = rec.RightTop.x;
						return FALSE;
					}
					else if (pos.y >= rec.RightTop.y)//��Y���ֵ�Ϸ�
					{
						pos.x = rec.RightTop.x;
						pos.y = rec.RightTop.y;
						return FALSE;
					}
					else if (pos.y <= rec.LeftBottom.y)//��Y��Сֵ�·�
					{
						pos.x = rec.RightBottom.x;
						pos.y = rec.RightBottom.y;
						return FALSE;
					}
				}
				else if (pos.x <= rec.LeftTop.x)//�����
				{
					if (pos.y <= rec.RightTop.y&&pos.y >= rec.LeftBottom.y)//����Y���������Сֵ֮��
					{
						pos.x = rec.LeftTop.x;
						return FALSE;
					}
					else if (pos.y >= rec.RightTop.y)//��Y���ֵ�Ϸ�
					{
						pos.x = rec.LeftTop.x;
						pos.y = rec.LeftTop.y;
						return FALSE;
					}
					else if (pos.y <= rec.LeftBottom.y)//��Y��Сֵ�·�
					{
						pos.x = rec.LeftBottom.x;
						pos.y = rec.LeftBottom.y;
						return FALSE;
					}
				}
			}
}
CPtrArray* CGcodeGeneration::SideNCOffsetAlgorithm(CPtrArray& XFarray, int mark, double offset)
{
	CPtrArray* Array = new CPtrArray;
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

				//1.���µ��������д洢
				CLine* pLine = new CLine;
				Array->Add(pLine);
				pLine->m_begin = temp.begin;
				pLine->m_end = temp.end;

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

				//2.���µ��������д洢
				CLine* pLine = new CLine;
				Array->Add(pLine);
				pLine->m_begin = temp.begin;
				pLine->m_end = temp.end;

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

					//3.���µ��������д洢
					CLine* pLine = new CLine;
					Array->Add(pLine);
					pLine->m_begin = temp.begin;
					pLine->m_end = temp.end;

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

					//4.���µ��������д洢
					CLine* pLine = new CLine;
					Array->Add(pLine);
					pLine->m_begin = temp.begin;
					pLine->m_end = temp.end;

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

					//1.
					CArc* pArc = new CArc;
					Array->Add(pArc);
					pArc->m_center = ((CArc*)XFarray.GetAt(i))->m_center;
					pArc->m_radio = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
					pArc->m_begin_angle = ((CArc*)XFarray.GetAt(i))->m_begin_angle;
					pArc->m_end_angle = ((CArc*)XFarray.GetAt(i))->m_end_angle;
					pArc->m_begin = temp.begin;
					pArc->m_end = temp.end;

					points.push_back(temp);

				}
				else if (i == mark)
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;

					//2.
					CArc* pArc = new CArc;
					Array->Add(pArc);
					pArc->m_center = ((CArc*)XFarray.GetAt(i))->m_center;
					pArc->m_radio = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
					pArc->m_begin_angle = ((CArc*)XFarray.GetAt(i))->m_begin_angle;
					pArc->m_end_angle = ((CArc*)XFarray.GetAt(i))->m_end_angle;
					pArc->m_begin = temp.begin;
					pArc->m_end = temp.end;

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

					//3.
					CArc* pArc = new CArc;
					Array->Add(pArc);
					pArc->m_center = ((CArc*)XFarray.GetAt(i))->m_center;
					pArc->m_radio = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
					pArc->m_begin_angle = ((CArc*)XFarray.GetAt(i))->m_begin_angle;
					pArc->m_end_angle = ((CArc*)XFarray.GetAt(i))->m_end_angle;
					pArc->m_begin = temp.begin;
					pArc->m_end = temp.end;


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

					//1.
					CArc* pArc = new CArc;
					Array->Add(pArc);
					pArc->m_center = ((CArc*)XFarray.GetAt(i))->m_center;
					pArc->m_radio = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
					pArc->m_begin = temp.begin;
					pArc->m_end = temp.end;
					pArc->m_Tudu = ((CArc*)XFarray.GetAt(i))->m_Tudu;

					points.push_back(temp);

				}
				else if (i == mark)
				{
					temp.begin = points[mark - 1].end;
					temp.end = points[0].begin;

					//2.
					CArc* pArc = new CArc;
					Array->Add(pArc);
					pArc->m_center = ((CArc*)XFarray.GetAt(i))->m_center;
					pArc->m_radio = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
					pArc->m_begin = temp.begin;
					pArc->m_end = temp.end;
					pArc->m_Tudu = ((CArc*)XFarray.GetAt(i))->m_Tudu;

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

					//3.
					CArc* pArc = new CArc;
					Array->Add(pArc);
					pArc->m_center = ((CArc*)XFarray.GetAt(i))->m_center;
					pArc->m_radio = ((CArc*)XFarray.GetAt(i))->m_radio + offset;
					pArc->m_begin = temp.begin;
					pArc->m_end = temp.end;
					pArc->m_Tudu = ((CArc*)XFarray.GetAt(i))->m_Tudu;


					points.push_back(temp);
				}
			}
		}
	}
	return Array;
}
void CGcodeGeneration::SideNC(ofstream* of)
{
	//��m_EverySideRoughPile���м��㣬�����ÿ��Ԫ���Ƿ񱻾���ë������ȡ�����ҽ��佻�����������ӱ���ȡ���Ԫ����m_EverySideRoughPile �л��
	//���ھ��ӹ�����Ҫ�����жϽ�ȡ��ֱ�ӽ����������
	
	if (SideNCInit()==TRUE)
	{

		CString str;
		str = _T("����ӹ��ּӹ�NC���룺");
		std::string STR = CStringA(str);
		(*of) << STR.c_str() << endl;
		CPoint3D CENTER = pTool->GetCenter();
		CPoint3D m_CutLiftPt = CPoint3D(0, 0, 0);//����̧����
		

		for (vector<vector<vector<TypeSort>>>::iterator it = m_SideRough.begin(); it != m_SideRough.end(); ++it)
		{
			int count = 0;
			BOOL FeedDirection = FALSE;//Ĭ��˳ʱ��		
			for (vector<vector<TypeSort>>::iterator its = it->begin(); its != it->end(); ++its)//���������
			{
				CPtrArray* Array = new CPtrArray;
				int number = SideCalculate(*its)->GetSize();
				for (int j = 0; j != number; ++j)
				{
					if (((CLine*)SideCalculate(*its)->GetAt(j))->flag == 1)
					{
						CLine* pLine = new CLine;
						Array->Add(pLine);
						pLine->m_begin = ((CLine*)SideCalculate(*its)->GetAt(j))->m_begin;
						pLine->m_end = ((CLine*)SideCalculate(*its)->GetAt(j))->m_end;
						pLine->flag = 1;
					}
					else if (((CArc*)SideCalculate(*its)->GetAt(j))->flag == 2)
					{
						CArc* pArc = new CArc;
						Array->Add(pArc);
						pArc->m_begin = ((CArc*)SideCalculate(*its)->GetAt(j))->m_begin;
						pArc->m_end = ((CArc*)SideCalculate(*its)->GetAt(j))->m_end;
						pArc->m_center = ((CArc*)SideCalculate(*its)->GetAt(j))->m_center;
						pArc->flag = 2;
					}
				}
				//�������
				str.Format(_T("�� %d ��: "), count);
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;

				if (!FeedDirection)//˳ʱ���ʱ�򣬴Ӽ�¼�ĵ�һ��Ԫ�ؿ�ʼ����
				{
					for (int i = 0; i != Array->GetSize(); ++i)
					{
						if (((CLine*)Array->GetAt(i))->flag == 1)//ֱ��
						{
							if (i == 0)//ֱ��Ԫ��Ϊ��һ��Ԫ��
							{
								if (its == it->begin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)Array->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦��Z�᷽���½�
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.x,
									((CLine*)Array->GetAt(i))->m_begin.y, ((CLine*)Array->GetAt(i))->m_begin.z);//�㶨λ���ӹ���ʼ�㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_end.x,
									((CLine*)Array->GetAt(i))->m_end.y, ((CLine*)Array->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

							}
							else if (i == Array->GetSize() - 1)//ֱ��Ԫ��Ϊ���һ��Ԫ�ص�ʱ��
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_end.x,
									((CLine*)Array->GetAt(i))->m_end.y, ((CLine*)Array->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)Array->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

							}
							else//ֱ��Ԫ��Ϊ�м�Ԫ��
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_end.x,
									((CLine*)Array->GetAt(i))->m_end.y, ((CLine*)Array->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
						else if (((CArc*)Array->GetAt(i))->flag == 2)
						{
							if (i == 0)//Բ��Ԫ��Ϊ��һ����ͷ
							{
								if (its == it->begin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)Array->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else//�ǵ�һ��
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_begin.x,
									((CArc*)Array->GetAt(i))->m_begin.y, ((CArc*)Array->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
								str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_end.y, ((CArc*)Array->GetAt(i))->m_end.z,
									((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_begin.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (i == Array->GetSize() - 1)//Բ��Ԫ�������һ����β
							{
								str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_end.y, ((CArc*)Array->GetAt(i))->m_end.z,
									((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_begin.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)Array->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else//Բ��Ԫ�����м�
							{
								str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_end.y, ((CArc*)Array->GetAt(i))->m_end.z,
									((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_begin.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
					}
				}
				else//��ʱ���ʱ�򣬴Ӽ�¼�����һ��Ԫ�ؿ�ʼ����
				{
					for (int i = Array->GetSize() - 1; i != -1; --i)
					{
						if (((CLine*)Array->GetAt(i))->flag == 1)//ֱ��
						{
							if (i == Array->GetSize() - 1)//��һ��Ԫ����ֱ��
							{
								if (its == it->begin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)Array->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦��Z�᷽���½�
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_end.x,
									((CLine*)Array->GetAt(i))->m_end.y, ((CLine*)Array->GetAt(i))->m_end.z);//�㶨λ���ӹ���ʼ�㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.x,
									((CLine*)Array->GetAt(i))->m_begin.y, ((CLine*)Array->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

							}
							else if (i ==0)//���һ��Ԫ����ֱ��
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.x,
									((CLine*)Array->GetAt(i))->m_begin.y, ((CLine*)Array->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)Array->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else//�м�Ԫ����ֱ�߶�
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)Array->GetAt(i))->m_begin.x,
									((CLine*)Array->GetAt(i))->m_begin.y, ((CLine*)Array->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
						else if (((CArc*)Array->GetAt(i))->flag == 2)//Բ��
						{
							if (i == Array->GetSize() - 1)//��ʱ��ĵ�һ��Ԫ����Բ��
							{
								if (its == it->begin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)Array->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else//�ǵ�һ��
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_end.x,
									((CArc*)Array->GetAt(i))->m_end.y, ((CArc*)Array->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
								str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_begin.y, ((CArc*)Array->GetAt(i))->m_begin.z,
									((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_end.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

							}
							else if (i == 0)//��ʱ������һ��Ԫ����Բ��
							{
								str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_begin.y, ((CArc*)Array->GetAt(i))->m_begin.z,
									((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_end.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)Array->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else//�м��Ԫ����Բ����
							{
								str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)Array->GetAt(i))->m_begin.x, ((CArc*)Array->GetAt(i))->m_begin.y, ((CArc*)Array->GetAt(i))->m_begin.z,
									((CArc*)Array->GetAt(i))->m_center.x - ((CArc*)Array->GetAt(i))->m_end.x, ((CArc*)Array->GetAt(i))->m_center.y - ((CArc*)Array->GetAt(i))->m_end.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
					}

				}
				//�Ǻ�
				++count;
				FeedDirection=!FeedDirection;
			}
		}

		str = _T("����ӹ����ӹ�NC���룺");
		STR = CStringA(str);
		(*of) << STR.c_str() << endl;
		for (vector<vector<CPtrArray*>>::iterator it = m_SideNCFinish.begin(); it != m_SideNCFinish.end(); ++it)
		{
			BOOL FeedDirection = FALSE;//Ĭ��˳ʱ��
			int count = 0;
			for (vector<CPtrArray*>::reverse_iterator its = it->rbegin(); its != it->rend(); ++its)//����������������
			{
				str.Format(_T("�� %d ��: "), count);
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;

				if (!FeedDirection)//˳ʱ��
				{
					for (int i = 0; i != (*its)->GetSize(); ++i)
					{
						if (((CLine*)(*its)->GetAt(i))->flag == 1)
						{
							if (i == 0)
							{
								if (its == it->rbegin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦��Z�᷽���½�
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_begin.x,
									((CLine*)(*its)->GetAt(i))->m_begin.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);//�㶨λ���ӹ���ʼ�㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_end.x,
									((CLine*)(*its)->GetAt(i))->m_end.y, ((CLine*)(*its)->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (i == (*its)->GetSize()-1)
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_end.x,
									((CLine*)(*its)->GetAt(i))->m_end.y, ((CLine*)(*its)->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

							}
							else
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_end.x,
									((CLine*)(*its)->GetAt(i))->m_end.y, ((CLine*)(*its)->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
						else if (((CArc*)(*its)->GetAt(i))->flag == 2)
						{
							if (i == 0)
							{
								if (its == it->rbegin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)(*its)->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else//�ǵ�һ��
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_begin.x,
									((CArc*)(*its)->GetAt(i))->m_begin.y, ((CArc*)(*its)->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
								str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_end.x, ((CArc*)(*its)->GetAt(i))->m_end.y, ((CArc*)(*its)->GetAt(i))->m_end.z,
									((CArc*)(*its)->GetAt(i))->m_center.x - ((CArc*)(*its)->GetAt(i))->m_begin.x, ((CArc*)(*its)->GetAt(i))->m_center.y - ((CArc*)(*its)->GetAt(i))->m_begin.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (i == (*its)->GetSize() - 1)
							{
								str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_end.x, ((CArc*)(*its)->GetAt(i))->m_end.y, ((CArc*)(*its)->GetAt(i))->m_end.z,
									((CArc*)(*its)->GetAt(i))->m_center.x - ((CArc*)(*its)->GetAt(i))->m_begin.x, ((CArc*)(*its)->GetAt(i))->m_center.y - ((CArc*)(*its)->GetAt(i))->m_begin.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)(*its)->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else
							{
								str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_end.x, ((CArc*)(*its)->GetAt(i))->m_end.y, ((CArc*)(*its)->GetAt(i))->m_end.z,
									((CArc*)(*its)->GetAt(i))->m_center.x - ((CArc*)(*its)->GetAt(i))->m_begin.x, ((CArc*)(*its)->GetAt(i))->m_center.y - ((CArc*)(*its)->GetAt(i))->m_begin.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
					}
				}
				else//��ʱ�����ɣ���
				{
					for (int i = (*its)->GetSize() - 1; i != -1; --i)
					{
						if (((CLine*)(*its)->GetAt(i))->flag == 1)
						{
							if (i == (*its)->GetSize() - 1)
							{
								if (its == it->rbegin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦��Z�᷽���½�
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_end.x,
									((CLine*)(*its)->GetAt(i))->m_end.y, ((CLine*)(*its)->GetAt(i))->m_end.z);//�㶨λ���ӹ���ʼ�㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_begin.x,
									((CLine*)(*its)->GetAt(i))->m_begin.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (i == 0)
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_begin.x,
									((CLine*)(*its)->GetAt(i))->m_begin.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else
							{
								str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), ((CLine*)(*its)->GetAt(i))->m_begin.x,
									((CLine*)(*its)->GetAt(i))->m_begin.y, ((CLine*)(*its)->GetAt(i))->m_begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
						else if (((CArc*)(*its)->GetAt(i))->flag == 2)
						{
							if (i == (*its)->GetSize() - 1)
							{
								if (its == it->rbegin())//ÿƬ�ĵ�һ��
								{
									str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)(*its)->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}
								else//�ǵ�һ��
								{
									str.Format(_T("G00 Z%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
									STR = CStringA(str);
									(*of) << STR.c_str() << endl;
								}

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_end.x,
									((CArc*)(*its)->GetAt(i))->m_end.y, ((CArc*)(*its)->GetAt(i))->m_end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
								str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_begin.x, ((CArc*)(*its)->GetAt(i))->m_begin.y, ((CArc*)(*its)->GetAt(i))->m_begin.z,
									((CArc*)(*its)->GetAt(i))->m_center.x - ((CArc*)(*its)->GetAt(i))->m_end.x, ((CArc*)(*its)->GetAt(i))->m_center.y - ((CArc*)(*its)->GetAt(i))->m_end.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (i == 0)
							{
								str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_begin.x, ((CArc*)(*its)->GetAt(i))->m_begin.y, ((CArc*)(*its)->GetAt(i))->m_begin.z,
									((CArc*)(*its)->GetAt(i))->m_center.x - ((CArc*)(*its)->GetAt(i))->m_end.x, ((CArc*)(*its)->GetAt(i))->m_center.y - ((CArc*)(*its)->GetAt(i))->m_end.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;

								str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), m_CutLiftPt.x, m_CutLiftPt.y, ((CArc*)(*its)->GetAt(i))->m_center.z);//�㶨λ��̧���㴦
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else
							{
								str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), ((CArc*)(*its)->GetAt(i))->m_begin.x, ((CArc*)(*its)->GetAt(i))->m_begin.y, ((CArc*)(*its)->GetAt(i))->m_begin.z,
									((CArc*)(*its)->GetAt(i))->m_center.x - ((CArc*)(*its)->GetAt(i))->m_end.x, ((CArc*)(*its)->GetAt(i))->m_center.y - ((CArc*)(*its)->GetAt(i))->m_end.y);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
					}
				}

				FeedDirection = !FeedDirection;
				++count;
			}
		}
	}	
}
CPtrArray* CGcodeGeneration::SideCalculate(vector<TypeSort> pts)
{
	/*�ö��������⣬Ҫ��pts����ͬ�ĵ�ȥ��*/
	CPtrArray* temp=new CPtrArray;
	vector<sort> TempSort;
	vector<sort> DeleteSort;//�洢�����жϵ�sort���жϺ����TempSort
	vector<TypeSort> TempPts;
	//ɾ���ظ��ĵ��Ƶ����������
	for (vector<TypeSort>::iterator it = pts.begin()+1; it != pts.end(); ++it)
	{
		TypeSort m_TempSort;
		while (it->position.x == (it -1)->position.x&&it->position.y == (it -1)->position.y)
		{
			if (it != pts.end() - 1)
				++it;
			else
				break;
		}
		if (it == pts.begin() + 1)
		{
			m_TempSort.position = (it-1)->position;
			m_TempSort.center = (it-1)->center;
			m_TempSort.flag = (it-1)->flag;
			TempPts.push_back(m_TempSort);
		}
		m_TempSort.position =it->position;
		m_TempSort.center = it->center;
		m_TempSort.flag = it->flag;
		TempPts.push_back(m_TempSort);
		
	}
	//һС��С���߶�
	for (vector<TypeSort>::iterator it = TempPts.begin(); it != TempPts.end() - 1; ++it)
	{
		sort xf;
		if (it->flag == 1&&(it+1)->flag==1)//ǰ����������ֱ�ߵ�Ԫ��
		{
			xf.flag = 1;
			xf.begin = it->position;
			xf.end = (it + 1)->position;
		}
		else if (it->flag == 2&&(it+1)->flag==2)//ǰ����������Բ����Ԫ��
		{
			xf.flag = 2;
			//0510
			xf.begin = it->position;
			xf.center = it->center;
			xf.end = (it + 1)->position;
		}
		else if (it->flag == 1 && (it + 1)->flag == 2)//ǰֱ�ߵ�Ԫ�غ���Բ����Ԫ��
		{
			xf.flag = 2;
			xf.begin = it->position;
			xf.center = (it + 1)->center;
			xf.end = (it + 1)->position;
		}
		else if (it->flag == 2 && (it + 1)->flag == 1)//ǰԲ����Ԫ�غ���ֱ�ߵ�Ԫ��
		{
			xf.flag = 2;
			xf.begin = it->position;
			xf.center = it->center;
			xf.end = (it + 1)->position;
		}
		TempSort.push_back(xf);
		//DeleteSort.push_back(xf);
	}
	
	int i = 0;
	//����ɢ������ֱ�ߣ�����б��
	for (vector<sort>::iterator it = TempSort.begin(); it!=TempSort.end();++it)
	{	//0510
		if (it->flag == 1)
		{
			if ((float)it->begin.x == (float)it->end.x)//˵���ڴ�ֱX���ֱ���ϣ�б�������
			{
				CLine* pLine = new CLine;
				//temp.Add(pLine);
				temp->Add(pLine);
				pLine->flag = 1;
				pLine->m_begin = it->begin;
				BOOL JUGE = FALSE;
				do
				{
					if (it == TempSort.end() - 1)
					{
						JUGE = FALSE;
					}
					/*else if ( fabs(it->end.x-(it + 1)->end.x)<0.5 &&fabs(it->end.x-(it + 1)->begin.x)<0.5)*/
					else if (it->end.x == (it + 1)->end.x && it->end.x == (it + 1)->begin.x)
					{
						JUGE = TRUE;
						++it;
						++i;
					}
					else
						JUGE = FALSE;
				} while (JUGE);
				pLine->m_end = it->end;
			}
			else
			{
				CLine* pLine = new CLine;
				//temp.Add(pLine);
				temp->Add(pLine);
				pLine->flag = 1;
				pLine->m_begin = it->begin;
				BOOL JUGE = FALSE;
				do
				{
					if (it == TempSort.end() - 1)
						JUGE = FALSE;
					else if ((it + 1)->end.x != (it + 1)->begin.x)
					{
						double ratio1 = (it->end.y - it->begin.y) / (it->end.x - it->begin.x);
						double ratio2 = ((it + 1)->end.y - (it + 1)->begin.y) / ((it + 1)->end.x - (it + 1)->begin.x);

						if (fabs((it->end.y - it->begin.y) / (it->end.x - it->begin.x) -
							((it + 1)->end.y - (it + 1)->begin.y) / ((it + 1)->end.x - (it + 1)->begin.x)) < 0.1)//ԭ0.05
						{
							JUGE = TRUE;
							++it;
							++i;
						}
						else
							JUGE = FALSE;
					}
					else
						JUGE = FALSE;
				} while (JUGE);
				pLine->m_end = it->end;
			}
			++i;
		}
		else if (it->flag == 2)//0510
		{
			CArc* pNewArc = new CArc;
			temp->Add(pNewArc);
			pNewArc->flag = 2;
			pNewArc->m_begin = it->begin;
			pNewArc->m_center = it->center;
			BOOL JUGE = FALSE;
			do
			{
				if (it == TempSort.end() - 1)
					JUGE = FALSE;
				else if (it->center == (it + 1)->center)//Բ����ȱ�ʾͬһ��Բ��
				{
					JUGE =TRUE;
					++it;
				}
				else
					JUGE = FALSE;
			} while (JUGE);
			
			pNewArc->m_end = it->end;
			
		}
	}
	CPtrArray* NewTemp = new CPtrArray;//�洢�����������Ԫ��
	vector<TypeSort> NewTypeSort;//��ȡ�����������Ϣ
	for (int i = 0; i != temp->GetSize(); ++i)
	{
		if (((CLine*)temp->GetAt(i))->flag == 1)
		{
			TypeSort m_LocalTypeSort;
			if (i == 0)
			{
				m_LocalTypeSort.center = CPoint3D(0, 0, 0);
				m_LocalTypeSort.flag = 1;
				m_LocalTypeSort.position = ((CLine*)temp->GetAt(i))->m_begin;
				NewTypeSort.push_back(m_LocalTypeSort);
				m_LocalTypeSort.position = ((CLine*)temp->GetAt(i))->m_end;
				NewTypeSort.push_back(m_LocalTypeSort);
			}
			else
			{
				m_LocalTypeSort.center = CPoint3D(0, 0, 0);
				m_LocalTypeSort.flag = 1;
				m_LocalTypeSort.position = ((CLine*)temp->GetAt(i))->m_end;
				NewTypeSort.push_back(m_LocalTypeSort);
			}
		}
		else if (((CArc*)temp->GetAt(i))->flag == 2)
		{
			TypeSort m_LocalTypeSort;
			if (i == 0)
			{
				m_LocalTypeSort.center = ((CArc*)temp->GetAt(i)) ->m_center;
				m_LocalTypeSort.flag = 2;
				m_LocalTypeSort.position = ((CArc*)temp->GetAt(i))->m_begin;
				NewTypeSort.push_back(m_LocalTypeSort);
				m_LocalTypeSort.position = ((CArc*)temp->GetAt(i))->m_end;
				NewTypeSort.push_back(m_LocalTypeSort);
			}
			else
			{
				m_LocalTypeSort.center = ((CArc*)temp->GetAt(i))->m_center;
				m_LocalTypeSort.flag = 2;
				m_LocalTypeSort.position = ((CArc*)temp->GetAt(i))->m_end;
				NewTypeSort.push_back(m_LocalTypeSort);
			}
		}
	}

	//�����һ������д�������������յ㲻��������������ȣ�ʹ�䲻��ʾ����
	if (((CLine*)temp->GetAt(temp->GetSize() - 1))->flag == 1)
	{
		if (((CLine*)temp->GetAt(temp->GetSize() - 1))->m_begin == ((CLine*)temp->GetAt(temp->GetSize() - 1))->m_end)
		{
			((CLine*)temp->GetAt(temp->GetSize() - 1))->flag = 4;
		}
	}
	else if (((CArc*)temp->GetAt(temp->GetSize() - 1))->flag == 2)
	{
		if (((CArc*)temp->GetAt(temp->GetSize() - 1))->m_begin == ((CArc*)temp->GetAt(temp->GetSize() - 1))->m_end)
			((CArc*)temp->GetAt(temp->GetSize() - 1))->flag = 4;
	}
	//��¼ֱ�߶γ���С��һ������ļ���
	vector<int> countNumber;
	for (int i = 0; i != temp->GetSize(); ++i)
	{
		if (((CLine*)temp->GetAt(i))->flag == 1)
		{
			float JugeLength = CLine::Length(((CLine*)temp->GetAt(i))->m_begin, ((CLine*)temp->GetAt(i))->m_end);
			if (JugeLength < 1&&JugeLength!=0)
				countNumber.push_back(i);
		}
	}

	//�����볬��һ�������ֱ�߶ν������أ��������յ�ֵ������һ��Ԫ��
	for (vector<int>::iterator it = countNumber.begin(); it != countNumber.end();++it)
	{
		int total = temp->GetSize() - 1;
		if (*it == total)//���Ϊ���һ��Ԫ��
		{//��һ��Ԫ���뵹���ڶ���Ԫ��Ϊֱ�ߣ��򽫵����ڶ���Ԫ�ص��յ㸳ֵ��������ʼ�㣬�����һ��Ԫ������
			if (((CLine*)temp->GetAt(0))->flag == 1 && ((CLine*)temp->GetAt(*it-1))->flag == 1)
			{
				((CLine*)temp->GetAt(0))->m_begin = ((CLine*)temp->GetAt(*it - 1))->m_end;
				((CLine*)temp->GetAt(*it))->flag = 4;
			}
		}
		else//�������һ��Ԫ��(�ж������ε�ʱ����Ҫ�������㣿�������ﶥ��ֻ�ܼ�������)
		{
			if (((CLine*)temp->GetAt(*it))->flag == 1 && ((CLine*)temp->GetAt(*it + 1))->flag == 1)
			{
				((CLine*)temp->GetAt(*it))->m_end = ((CLine*)temp->GetAt(*it + 1))->m_end;
				
				if (CLine::Length(((CLine*)temp->GetAt(*it))->m_begin, ((CLine*)temp->GetAt(*it))->m_end) < 1)
				{
					if (((CLine*)temp->GetAt(*it-1))->flag == 1)
					{
						((CLine*)temp->GetAt(*it - 1))->m_end = ((CLine*)temp->GetAt(*it))->m_end;
						((CLine*)temp->GetAt(*it))->flag = 4;
					}
				}
				((CLine*)temp->GetAt(*it + 1))->flag = 4;
			}
		}
	}

	return temp;
}

//Բ��˫����ӹ�NC���������
BOOL CGcodeGeneration::ArcNCInit()
{
	vector<vector<vector<sort>>>().swap(m_ArcRough);//����
	vector<vector<vector<sort>>>().swap(m_ArcFinish);
	vector<vector<CPtrArray*>> m_ArcNCRoughList=pTool->m_ArcsYSide;
	vector<vector<CPtrArray*>> m_ArcNCFinishList = pTool->m_ArcFinishYSide;
	for (vector<vector<CPtrArray*>>::iterator it = m_ArcNCRoughList.begin(); it != m_ArcNCRoughList.end(); ++it)
	{
		vector<vector<sort>> m_tempArcRough;
		for (vector<CPtrArray*>::iterator its = it->begin(); its != it->end()/* - 1*/; ++its)
		{
			vector<sort> m_tempTempArcRough = ArcNCCalculate(**its, pTool->GetArcWorkBlankHeigth());
			m_tempArcRough.push_back(m_tempTempArcRough);
			vector<sort>().swap(m_tempTempArcRough);
		}

		//����̧����ͽ�����
		vector<sort> HeadSort;
		vector<sort> EndSort;
		sort InsertSort;
		InsertSort.flag = 1;
		InsertSort.begin = m_tempArcRough.begin()->begin()->begin;
		InsertSort.begin.z = 2500;
		InsertSort.end = m_tempArcRough.begin()->begin()->begin;
		HeadSort.push_back(InsertSort);
		m_tempArcRough.insert(m_tempArcRough.begin(), HeadSort);

		if (m_tempArcRough.size() % 2 == 0)//ż��
		{
			InsertSort.begin = ((m_tempArcRough.end() - 1)->end() - 1)->end;
			InsertSort.end = ((m_tempArcRough.end() - 1)->end() - 1)->end;
			InsertSort.end.z = 2500;
			EndSort.push_back(InsertSort);
		}
		else//����
		{
			InsertSort.begin = ((m_tempArcRough.end() - 1)->begin())->begin;
			InsertSort.end = ((m_tempArcRough.end() - 1)->begin())->begin;
			InsertSort.end.z = 2500;
			EndSort.push_back(InsertSort);
		}
		m_tempArcRough.push_back(EndSort);

		m_ArcRough.push_back(m_tempArcRough);
		vector<vector<sort>>().swap(m_tempArcRough);
	}
	//���ӹ��㴦��
	for (vector<vector<CPtrArray*>>::iterator it = m_ArcNCFinishList.begin(); it!= m_ArcNCFinishList.end(); ++it)
	{
		vector<vector<sort>> m_tempArcFinish;
		for (vector<CPtrArray*>::iterator its = it->begin(); its != it->end(); ++its)
		{
			vector<sort> m_tempTempArcFinish = ArcNCCalculate(**its, pTool->GetArcWorkBlankHeigth());
			m_tempArcFinish.push_back(m_tempTempArcFinish);
			vector<sort>().swap(m_tempTempArcFinish);
		}

		//����̧����ͽ�����
		vector<sort> HeadSort;
		vector<sort> EndSort;
		sort InsertSort;
		InsertSort.flag = 1;
		InsertSort.begin = m_tempArcFinish.begin()->begin()->begin;
		InsertSort.begin.z = 2500;
		InsertSort.end = m_tempArcFinish.begin()->begin()->begin;
		HeadSort.push_back(InsertSort);
		m_tempArcFinish.insert(m_tempArcFinish.begin(), HeadSort);

		if (m_tempArcFinish.size() % 2 == 0)//ż��
		{
			InsertSort.begin = ((m_tempArcFinish.end() - 1)->end() - 1)->end;
			InsertSort.end = ((m_tempArcFinish.end() - 1)->end() - 1)->end;
			InsertSort.end.z = 2500;
			EndSort.push_back(InsertSort);
		}
		else//����
		{
			InsertSort.begin = ((m_tempArcFinish.end() - 1)->begin())->begin;
			InsertSort.end = ((m_tempArcFinish.end() - 1)->begin())->begin;
			InsertSort.end.z = 2500;
			EndSort.push_back(InsertSort);
		}
		m_tempArcFinish.push_back(EndSort);

		m_ArcFinish.push_back(m_tempArcFinish);
		vector<vector<sort>>().swap(m_tempArcFinish);
	}

	if (m_ArcRough.size() != 0 && m_ArcFinish.size() != 0)
		return TRUE;
	else
		return FALSE;
}

vector<sort> CGcodeGeneration::ArcNCCalculate(CPtrArray& Array, float High)
{
	vector<sort> m_tempSort;
	for (int i = 0; i != Array.GetSize(); ++i)
	{
		if (((CArc*)Array.GetAt(i))->flag == 2)
		{
			if (((CArc*)Array.GetAt(i))->m_Tudu == 0)
			{
				BOOL direction = CArc::CalculateYZ(((CArc*)Array.GetAt(i))->m_center, ((CArc*)Array.GetAt(i))->m_radio, ((CArc*)Array.GetAt(i))->m_begin_angle - 270,
					((CArc*)Array.GetAt(i))->m_end_angle + 90, Array, i);
			}
			else
			{
				((CArc*)Array.GetAt(i))->PolyCalculateYZ(((CArc*)Array.GetAt(i))->m_begin, ((CArc*)Array.GetAt(i))->m_end, ((CArc*)Array.GetAt(i))->m_Tudu);
			}

			if (((CArc*)Array.GetAt(i))->m_center.z >= High)//Բ������֮�ϵ�ֱ�ӱ�ֱ��
			{
				sort m_LineSort;
				m_LineSort.flag = 1;
				m_LineSort.begin = ((CArc*)Array.GetAt(i))->m_begin;
				m_LineSort.end = ((CArc*)Array.GetAt(i))->m_end;
				m_LineSort.begin.z =m_LineSort.end.z= High;
				m_tempSort.push_back(m_LineSort);
			}
			else//Բ�����߶ε�����
			{
				float distance = High - ((CArc*)Array.GetAt(i))->m_center.z;//��ȡԲ�����߶εĴ�ֱ������뾶���Ƚ�
				if (distance >= ((CArc*)Array.GetAt(i))->m_radio)//˵��Բ����ֱ��û�н���
				{
					sort m_ArcSort;
					m_ArcSort.flag = 2;
					m_ArcSort.begin = ((CArc*)Array.GetAt(i))->m_begin;
					m_ArcSort.end = ((CArc*)Array.GetAt(i))->m_end;
					m_ArcSort.center = ((CArc*)Array.GetAt(i))->m_center;
					m_tempSort.push_back(m_ArcSort);
				}
				else//Բ����ֱ���н���
				{
					float y1, y2;
					y1 = ((CArc*)Array.GetAt(i))->m_center.y + sqrt(pow(((CArc*)Array.GetAt(i))->m_radio, 2) - pow(High - ((CArc*)Array.GetAt(i))->m_center.z, 2));
					y2 = ((CArc*)Array.GetAt(i))->m_center.y - sqrt(pow(((CArc*)Array.GetAt(i))->m_radio, 2) - pow(High - ((CArc*)Array.GetAt(i))->m_center.z, 2));
					if (y1 - y2 >= fabs(((CArc*)Array.GetAt(i))->m_end.y - ((CArc*)Array.GetAt(i))->m_begin.y))//����֮��ĳ��ȴ�����ʼ����ֹ��֮��ĳ��ȣ�Ϊһֱ��
					{
						sort m_LineSort;
						m_LineSort.flag = 1;
						m_LineSort.begin = ((CArc*)Array.GetAt(i))->m_begin;
						m_LineSort.end = ((CArc*)Array.GetAt(i))->m_end;
						m_LineSort.begin.z = m_LineSort.end.z = High;
						m_tempSort.push_back(m_LineSort);
					}
					else
					{
						sort m_ArcSort;
						m_ArcSort.flag = 2;
						m_ArcSort.begin = ((CArc*)Array.GetAt(i))->m_begin;
						m_ArcSort.end.x = ((CArc*)Array.GetAt(i))->m_end.x;
						/*m_ArcSort.end.y = y1;*/
						m_ArcSort.end.y = y2;
						m_ArcSort.end.z = High;
						m_ArcSort.center = ((CArc*)Array.GetAt(i))->m_center;
						m_tempSort.push_back(m_ArcSort);

						sort m_LineSort;
						m_LineSort.flag = 1;
						m_LineSort.begin.x = ((CArc*)Array.GetAt(i))->m_begin.x;
						/*m_LineSort.begin.y = y1;*/
						m_LineSort.begin.y = y2;
						m_LineSort.end.x = ((CArc*)Array.GetAt(i))->m_end.x;
						/*m_LineSort.end.y = y2;*/
						m_LineSort.end.y = y1;
						m_LineSort.begin.z = m_LineSort.end.z = High;
						m_tempSort.push_back(m_LineSort);

						m_ArcSort.begin.x = ((CArc*)Array.GetAt(i))->m_begin.x;
						/*m_ArcSort.begin.y = y2;*/
						m_ArcSort.begin.y = y1;
						m_ArcSort.begin.z = High;
						m_ArcSort.end = ((CArc*)Array.GetAt(i))->m_end;
						m_ArcSort.center = ((CArc*)Array.GetAt(i))->m_center;
						m_tempSort.push_back(m_ArcSort);


					}
				}

			}
		}
	}

	return m_tempSort;
}

void CGcodeGeneration::ArcNC(ofstream* of)
{
	if (ArcNCInit())
	{
		CString str;
		str = _T("˫����Բ���ּӹ�NC���룺");
		std::string STR = CStringA(str);
		(*of) << STR.c_str() << endl;
		str = _T("G90 G19 M03");//����ֵ��ʽ��YZƽ�棬������ת
		STR = CStringA(str);
		(*of) << STR.c_str() << endl;
		int number = 0;
	
		//�ּӹ�NC��������,Ĭ�ϵ�Բ�ķ���Ϊ��ʱ��
		for (vector<vector<vector<sort>>>::iterator it = m_ArcRough.begin(); it != m_ArcRough.end(); ++it)
		{
			BOOL direction = TRUE;
			str.Format(_T("��%d�㣺"), number);
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			for (vector<vector<sort>>::iterator its = it->begin(); its != it->end(); ++its)
			{
				if (its==it->begin())//��һ������ֻ��һ��ֱ��
				{
					str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin()->begin.x, its->begin()->begin.y, its->begin()->begin.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
					str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin()->end.x, its->begin()->end.y, its->begin()->end.z);
					STR = CStringA(str);
				    (*of) << STR.c_str() << endl;
					
				}
				else if (its==it->end()-1)//���һ��1��ֱ��
				{
					str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin()->end.x, its->begin()->end.y, its->begin()->end.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
				}
				else
				{
					if (direction)//ԭ�ȷ���
					{
						for (vector<sort>::iterator itss = its->begin(); itss != its->end(); ++itss)
						{
							if (itss->flag == 1)//ֱ��
							{
								str.Format(_T("G01 Y%0.3f Z%0.3f F1500"),itss->end.y, itss->end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (itss->flag == 2)
							{
								str.Format(_T("G02 Y%0.3f Z%0.3f J%0.3f K%0.3f F1500"),  itss->end.y, itss->end.z,
									itss->center.y - itss->begin.y, itss->center.z - itss->begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}

						}
						if (its != it->end() - 2)//�����ڶ���Ԫ�ز��ý��и��ε�����
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its + 1)->rbegin()->end.x, (its + 1)->rbegin()->end.y, (its + 1)->rbegin()->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}
					else//������
					{
						for (vector<sort>::reverse_iterator itss = its->rbegin(); itss != its->rend(); ++itss)
						{
							if (itss->flag == 1)
							{
								str.Format(_T("G01 Y%0.3f Z%0.3f F1500"), itss->begin.y, itss->begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (itss->flag == 2)
							{
								str.Format(_T("G03 Y%0.3f Z%0.3f J%0.3f K%0.3f F1500"),  itss->begin.y, itss->begin.z,
									itss->center.y - itss->end.y, itss->center.z - itss->end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
						//���ε�����
						if (its != it->end() - 2)//�����ڶ���Ԫ�ز��ý��и��ε�����
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its + 1)->begin()->begin.x, (its + 1)->begin()->begin.y, (its + 1)->begin()->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}

					direction = !direction;
				}

			}

			++number;
		}

		str = _T("˫����Բ�����ӹ�NC���룺");
		STR = CStringA(str);
		(*of) << STR.c_str() << endl;

		for (vector<vector<vector<sort>>>::iterator it = m_ArcFinish.begin(); it != m_ArcFinish.end(); ++it)
		{
			BOOL direction = TRUE;
			str.Format(_T("��%d�㣺"), number);
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			for (vector<vector<sort>>::iterator its = it->begin(); its != it->end(); ++its)
			{
				if (its == it->begin())//��һ������ֻ��һ��ֱ��
				{
					str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin()->begin.x, its->begin()->begin.y, its->begin()->begin.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
					str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin()->end.x, its->begin()->end.y, its->begin()->end.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
				}
				else if (its == it->end() - 1)//���һ��1��ֱ��
				{
					str.Format(_T("G00 X%0.3f Y%0.3f Z% 0.3f F1500"), its->begin()->end.x, its->begin()->end.y, its->begin()->end.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
				}
				else
				{
					if (direction)//ԭ�ȷ���
					{
						for (vector<sort>::iterator itss = its->begin(); itss != its->end(); ++itss)
						{
							if (itss->flag == 1)//ֱ��
							{
								str.Format(_T("G01 Y%0.3f Z%0.3f F1500"), itss->end.y, itss->end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (itss->flag == 2)
							{
								str.Format(_T("G02 Y%0.3f Z%0.3f J%0.3f K%0.3f F1600"), itss->end.y, itss->end.z,
									itss->center.y - itss->begin.y, itss->center.z - itss->begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}

						}
						if (its != it->end() - 2)//�����ڶ���Ԫ�ز��ý��и��ε�����
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z% 0.3f F1500"), (its + 1)->rbegin()->end.x, (its + 1)->rbegin()->end.y, (its + 1)->rbegin()->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}
					else//������
					{
						for (vector<sort>::reverse_iterator itss = its->rbegin(); itss != its->rend(); ++itss)
						{
							if (itss->flag == 1)
							{
								str.Format(_T("G01 Y%0.3f Z% 0.3f F1500"), itss->begin.y, itss->begin.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
							else if (itss->flag == 2)
							{
								str.Format(_T("G03 Y%0.3f Z%0.3f J%0.3f K%0.3f F1700"), itss->begin.y, itss->begin.z,
									itss->center.y - itss->end.y, itss->center.z - itss->end.z);
								STR = CStringA(str);
								(*of) << STR.c_str() << endl;
							}
						}
						//���ε�����
						if (its != it->end() - 2)//�����ڶ���Ԫ�ز��ý��и��ε�����
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z% 0.3f F1500"), (its + 1)->begin()->begin.x, (its + 1)->begin()->begin.y, (its + 1)->begin()->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}

					direction = !direction;
				}
			}
			++number;
		}

	}
}


//�����ӹ�NC���������
BOOL CGcodeGeneration::LineNCInit()//��ֱ�߻���Բ���ΰ���˳���ź�
{
	if (!pTool->GetLineStyle())//ֱ��
	{
		return TRUE;
	}
	else//Բ��
	{
		vector<vector<sort>>().swap(LineRoughArc);
		vector<sort>().swap(LineFinishArc);
		//�ּӹ�������ȡ
		for (vector<vector<CPtrArray*>>::iterator it = pTool->m_LineRoughVSegmentDisArc.begin();it != pTool->m_LineRoughVSegmentDisArc.end(); ++it)
		{
			vector<sort> m_tempLineRoughArc;
			for (vector<CPtrArray*>::iterator its = it->begin(); its != it->end(); ++its)
			{
				sort temp;
				for (int i = 0; i != (*its)->GetSize(); ++i)
				{
					if (((CArc*)(*its)->GetAt(i))->flag == 2)
					{
						if (((CArc*)(*its)->GetAt(i))->m_Tudu == 0)
						{
							((CArc*)(*its)->GetAt(i))->Calculate(((CArc*)(*its)->GetAt(i))->m_center, ((CArc*)(*its)->GetAt(i))->m_radio,
								((CArc*)(*its)->GetAt(i))->m_begin_angle, ((CArc*)(*its)->GetAt(i))->m_end_angle, **its, i);
							temp.begin = ((CArc*)(*its)->GetAt(i))->m_begin;
							temp.end = ((CArc*)(*its)->GetAt(i))->m_end;
							temp.center = ((CArc*)(*its)->GetAt(i))->m_center;
							temp.flag = 2;
						}
					}
				}
				m_tempLineRoughArc.push_back(temp);
			}
			LineRoughArc.push_back(m_tempLineRoughArc);
			vector<sort>().swap(m_tempLineRoughArc);
		}
		//���ӹ�������ȡ
		for (vector<CPtrArray*>::iterator it = pTool->m_LineFinishVSegmentDisArc.begin(); it != pTool->m_LineFinishVSegmentDisArc.end(); ++it)
		{
			sort temp;
			for (int i = 0; i != (*it)->GetSize(); ++i)
			{
				if (((CArc*)(*it)->GetAt(i))->flag == 2)
				{
					if (((CArc*)(*it)->GetAt(i))->m_Tudu == 0)
					{
						((CArc*)(*it)->GetAt(i))->Calculate(((CArc*)(*it)->GetAt(i))->m_center, ((CArc*)(*it)->GetAt(i))->m_radio,
							((CArc*)(*it)->GetAt(i))->m_begin_angle, ((CArc*)(*it)->GetAt(i))->m_end_angle, **it, i);
						temp.begin = ((CArc*)(*it)->GetAt(i))->m_begin;
						temp.end = ((CArc*)(*it)->GetAt(i))->m_end;
						temp.center = ((CArc*)(*it)->GetAt(i))->m_center;
						temp.flag = 2;
					}
				}
			}
			LineFinishArc.push_back(temp);
		}

		if (LineRoughArc.size() != 0 && LineFinishArc.size() != 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}


}
void CGcodeGeneration::LineNC(ofstream* of)
{
	if (LineNCInit())
	{
		CString str;
		str = _T("�����ӹ��ӹ�NC���룺");
		std::string STR = CStringA(str);
		(*of) << STR.c_str() << endl;
		if (!pTool->GetLineStyle())//ֱ��
		{
			str = _T("ֱ���������ּӹ���");
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), 0, 0, pTool->GetLineWorkBlankHigh());//�㶨λ��ĳ�߶�
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			for (vector<vector<LinePos>>::iterator it = pTool->m_LineRoughVSegmentDisLine.begin();
				it != pTool->m_LineRoughVSegmentDisLine.end(); ++it)
			{
				BOOL Direction = TRUE;
				for (vector<LinePos>::iterator its = it->begin(); its != it->end(); ++its)
				{
					if ( its == it->begin())//��һ������λ
					{
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);//�㶨λ��̧���㴦
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}

					if (its == it->end() - 1)//���һ��ֱ�ߣ�̧���������ë���߶�
					{
						if (Direction)//������Y������
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, its->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, pTool->GetLineWorkBlankHigh());
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
						else
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, pTool->GetLineWorkBlankHigh());
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}
					else
					{
						if (Direction)//������Y������
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, its->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its+1)->end.x, (its+1)->end.y, (its+1)->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
						else//������Y������
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its+1)->begin.x, (its+1)->begin.y, (its+1)->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}

					}

					Direction = !Direction;

				}
			}

			str = _T("ֱ�����������ӹ���");
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;
			str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"),pTool->m_LineRoughVSegmentDisLine.begin()->begin()->begin.x,
				    pTool->m_LineRoughVSegmentDisLine.begin()->begin()->begin.y, pTool->GetLineWorkBlankHigh());//�㶨λ��ԭ�ȴּӹ����
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), pTool->m_LineFinishVSegmentDisLine.begin()->begin()->begin.x,
				pTool->m_LineFinishVSegmentDisLine.begin()->begin()->begin.y, pTool->m_LineFinishVSegmentDisLine.begin()->begin()->begin.z);//�㶨λ�����ӹ����
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			for (vector<vector<LinePos>>::iterator it = pTool->m_LineFinishVSegmentDisLine.begin();
				it != pTool->m_LineFinishVSegmentDisLine.begin()+1; ++it)
			{
				BOOL Direction = TRUE;
				for (vector<LinePos>::iterator its = it->begin(); its != it->end(); ++its)
				{
					if (its == it->end()-1)//���һ��һ��ֱ����m_LineProcess�ĵ�һ���ص�
					{
						if (Direction)
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, its->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
							
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (pTool->m_LineProcess.begin()+1)->end.x, 
								            (pTool->m_LineProcess.begin()+1)->end.y,( pTool->m_LineProcess.begin()+1)->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							Direction = FALSE;
							for (vector<LinePos>::iterator itss = pTool->m_LineProcess.begin() + 1;
								itss != pTool->m_LineProcess.end(); ++itss)
							{
								if (itss == pTool->m_LineProcess.end() - 1)
								{
									if (Direction)
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->end.x, itss->end.y, itss->end.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), itss->end.x, itss->end.y, pTool->GetLineWorkBlankHigh());
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
									else
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->begin.x, itss->begin.y, itss->begin.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), itss->begin.x, itss->begin.y, pTool->GetLineWorkBlankHigh());
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
								}
								else
								{
									if (Direction)
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->end.x, itss->end.y, itss->end.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (itss + 1)->end.x, (itss + 1)->end.y, (itss + 1)->end.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
									else
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->begin.x, itss->begin.y, itss->begin.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (itss + 1)->begin.x, (itss + 1)->begin.y, (itss + 1)->begin.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
								}

								Direction = !Direction;
							}

						}
						else
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (pTool->m_LineProcess.begin()+1)->begin.x,
								(pTool->m_LineProcess.begin()+1)->begin.y, (pTool->m_LineProcess.begin()+1)->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							Direction = TRUE;
							for (vector<LinePos>::iterator itss = pTool->m_LineProcess.begin() + 1;
								itss != pTool->m_LineProcess.end(); ++itss)
							{
								if (itss == pTool->m_LineProcess.end() - 1)
								{
									if (Direction)
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->end.x, itss->end.y, itss->end.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), itss->end.x, itss->end.y, pTool->GetLineWorkBlankHigh());
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
									else
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->begin.x, itss->begin.y, itss->begin.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), itss->begin.x, itss->begin.y, pTool->GetLineWorkBlankHigh());
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
								}
								else
								{
									if (Direction)
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->end.x, itss->end.y, itss->end.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (itss + 1)->end.x, (itss + 1)->end.y, (itss + 1)->end.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
									else
									{
										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), itss->begin.x, itss->begin.y, itss->begin.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;

										str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (itss + 1)->begin.x, (itss + 1)->begin.y, (itss + 1)->begin.z);
										STR = CStringA(str);
										(*of) << STR.c_str() << endl;
									}
								}

								Direction = !Direction;
							}

						}
						

					}
					else
					{
						if (Direction)
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, its->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its + 1)->end.x, (its + 1)->end.y, (its + 1)->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
						else
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its + 1)->begin.x, (its + 1)->begin.y, (its + 1)->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}

					Direction = !Direction;
				}
			}




		}
		else//Բ��
		{
			str = _T("Բ���������ּӹ���");
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), 0, 0, pTool->GetLineWorkBlankHigh());//�㶨λ��ĳ�߶�
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			for (vector<vector<sort>>::iterator it = LineRoughArc.begin(); it != LineRoughArc.end(); ++it)
			{
				BOOL Direction=TRUE;
				for (vector<sort>::iterator its = it->begin(); its != it->end(); ++its)
				{
					if (its == it->begin())//��һ��
					{
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);//�㶨λ����ʼ��
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
					if (its == it->end() - 1)//���һ��
					{
						if (Direction)//��ʱ��
						{
							str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), its->end.x, its->end.y, its->end.z,
								its->center.x - its->begin.x, its->center.y - its->begin.y);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, pTool->GetLineWorkBlankHigh());//�㶨λ���������ë���߶�
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
						else
						{
							str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z,
								its->center.x - its->end.x, its->center.y - its->end.y);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, pTool->GetLineWorkBlankHigh());//�㶨λ���������ë���߶�
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

						}
					}
					else//�м�
					{
						if (Direction)//��ʱ��
						{
							str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), its->end.x, its->end.y, its->end.z,
								its->center.x - its->begin.x, its->center.y - its->begin.y);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its+1)->end.x, (its+1)->end.y, (its+1)->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
						else//˳ʱ��
						{
							str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z,
								its->center.x - its->end.x, its->center.y - its->end.y);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;

							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its + 1)->begin.x, (its + 1)->begin.y, (its + 1)->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}
					Direction = !Direction;
				}
			}

			str = _T("Բ�����������ӹ���");
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"),LineRoughArc.begin()->begin()->begin.x,LineRoughArc.begin()->begin()->begin.y, 
				                                            LineRoughArc.begin()->begin()->begin.z);//�㶨λ���ּӹ���ʼλ��
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), LineFinishArc.begin()->begin.x,LineFinishArc.begin()->begin.y,
				                                             LineFinishArc.begin()->begin.z);//�㶨λ�����ӹ���ʼλ��
			STR = CStringA(str);
			(*of) << STR.c_str() << endl;

			BOOL Direction = TRUE;
			for (vector<sort>::iterator it = LineFinishArc.begin(); it != LineFinishArc.end(); ++it)
			{
				if (it == LineFinishArc.begin())
				{
					str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin.x, it->begin.y, it->begin.z);//�㶨λ����ʼ��
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
				}
				if (it == LineFinishArc.end() - 1)
				{
					if (Direction)//��ʱ��
					{
						str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), it->end.x, it->end.y, it->end.z,
							it->center.x - it->begin.x, it->center.y - it->begin.y);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), it->end.x, it->end.y, pTool->GetLineWorkBlankHigh());//�㶨λ���յ��ë���߶�
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
					else
					{
						str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), it->begin.x, it->begin.y, it->begin.z,
							it->center.x - it->end.x, it->center.y - it->end.y);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin.x, it->begin.y, pTool->GetLineWorkBlankHigh());//�㶨λ���յ��ë���߶�
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
				else
				{
					if (Direction)//��ʱ��
					{
						str.Format(_T("G03 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), it->end.x, it->end.y, it->end.z,
							it->center.x - it->begin.x, it->center.y - it->begin.y);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (it + 1)->end.x, (it + 1)->end.y, (it + 1)->end.z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
					else
					{
						str.Format(_T("G02 X%0.3f Y%0.3f Z%0.3f I%0.3f J%0.3f F1500"), it->begin.x, it->begin.y, it->begin.z,
							it->center.x - it->end.x, it->center.y - it->end.y);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;

						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (it + 1)->begin.x, (it + 1)->begin.y, (it + 1)->begin.z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
				Direction = !Direction;
			}


		}
	}
}

//�����ӹ�NC���������
BOOL CGcodeGeneration::OrthgonalNCInit()
{
	if (pTool->GetOrthgonalTrapezoidType() == 0)//������
	{
		if (pTool->NormalTrapezoidCut.size() != 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else if (pTool->GetOrthgonalTrapezoidType() == 1)//������
	{
		if (pTool->ReverseTrapezoidCut.size() != 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}
void CGcodeGeneration::OrthgonalNC(ofstream* of)
{
	if (OrthgonalNCInit())
	{
		CString str;
		str = _T("�����ӹ��ӹ�NC���룺");
		std::string STR = CStringA(str);
		(*of) << STR.c_str() << endl;

		if (pTool->GetOrthgonalTrapezoidType() == 0)//������
		{
			if (pTool->GetOrthgonalProcessStyle() == 0)//����
			{
				str = _T("�����κ��мӹ��ӹ�NC���룺");
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;
			}
			else if (pTool->GetOrthgonalProcessStyle() == 1)//����
			{
				str = _T("���������мӹ��ӹ�NC���룺");
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;
			}
			else if (pTool->GetOrthgonalProcessStyle() == 2)//������
			{
				str = _T("�����������ӹ��ӹ�NC���룺");
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;
			}

			for (vector<vector<OffsetPoint>>::iterator it = pTool->NormalTrapezoidCut.begin(); it != pTool->NormalTrapezoidCut.end(); ++it)
			{
				for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
				{
					if (its == it->begin())
					{
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), its->begin.x, its->begin.y, its->begin.z+300);//�㶨λ��ĳ�߶�
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);//�㶨λ����ʼ��
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
					str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, its->end.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;

					if (its == it->end() - 1)
					{
						if (it->size() % 2 == 0)//ż������������Ե�һ�������
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin()->begin.x, it->begin()->begin.y, it->begin()->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), it->begin()->begin.x, it->begin()->begin.y, it->begin()->begin.z+300);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
						else//��������������Ե�һ�����յ�
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin()->end.x, it->begin()->end.y, it->begin()->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), it->begin()->end.x, it->begin()->end.y, it->begin()->end.z+300);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}
					else
					{
						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its+1)->begin.x, (its+1)->begin.y, (its+1)->begin.z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}

				}
			}

		}
		else if (pTool->GetOrthgonalTrapezoidType() == 1)//������
		{
			if (pTool->GetOrthgonalProcessStyle() == 0)//����
			{
				str = _T("�����κ��мӹ��ӹ�NC���룺");
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;
			}
			else if (pTool->GetOrthgonalProcessStyle() == 1)//����
			{
				str = _T("���������мӹ��ӹ�NC���룺");
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;
			}
			else if (pTool->GetOrthgonalProcessStyle() == 2)//������
			{
				str = _T("�����������ӹ��ӹ�NC���룺");
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;
			}

			for (vector<vector<OffsetPoint>>::iterator it = pTool->ReverseTrapezoidCut.begin(); it != pTool->ReverseTrapezoidCut.end(); ++it)
			{
				for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
				{
					if (its == it->begin())
					{
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), its->begin.x, its->begin.y, its->begin.z + 300);//�㶨λ��ĳ�߶�
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);//�㶨λ����ʼ��
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
					str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, its->end.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;

					if (its == it->end() - 1)
					{
						if (it->size() % 2 == 0)//ż������������Ե�һ�������
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin()->begin.x, it->begin()->begin.y, it->begin()->begin.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), it->begin()->begin.x, it->begin()->begin.y, it->begin()->begin.z + 300);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
						else//��������������Ե�һ�����յ�
						{
							str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin()->end.x, it->begin()->end.y, it->begin()->end.z);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
							str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), it->begin()->end.x, it->begin()->end.y, it->begin()->end.z + 300);
							STR = CStringA(str);
							(*of) << STR.c_str() << endl;
						}
					}
					else
					{
						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its + 1)->begin.x, (its + 1)->begin.y, (its + 1)->begin.z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}

				}
			}
		}
	}
}


//����μӹ�NC�������ʼ��
BOOL CGcodeGeneration::PolygonNCInit()
{
	return TRUE;
}
void CGcodeGeneration::PolygonNC(ofstream* of)
{
	if (PolygonNCInit())
	{
		CString str;
		str.Format(_T("%d ���������ӹ�NC���룺"), pTool->GetPolygeonNumber());
		std::string STR = CStringA(str);
		(*of) << STR.c_str() << endl;

		for (vector<vector<OffsetPoint>>::iterator it = pTool->m_PolygeonSequentialLines.begin(); it != pTool->m_PolygeonSequentialLines.end(); ++it)
		{
			for (vector<OffsetPoint>::iterator its = it->begin(); its != it->end(); ++its)
			{
				if (its == it->begin())
				{
					str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), its->begin.x, its->begin.y, its->begin.z + 300);//�㶨λ��ĳ�߶�
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
					str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->begin.x, its->begin.y, its->begin.z);//�㶨λ����ʼ��
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
				}
				str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), its->end.x, its->end.y, its->end.z);
				STR = CStringA(str);
				(*of) << STR.c_str() << endl;

				if (its == it->end() - 1)
				{
					if (it->size() % 2 == 0)//ż������������Ե�һ�������
					{
						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin()->begin.x, it->begin()->begin.y, it->begin()->begin.z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), it->begin()->begin.x, it->begin()->begin.y, it->begin()->begin.z + 300);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
					else//��������������Ե�һ�����յ�
					{
						str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), it->begin()->end.x, it->begin()->end.y, it->begin()->end.z);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
						str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"), it->begin()->end.x, it->begin()->end.y, it->begin()->end.z + 300);
						STR = CStringA(str);
						(*of) << STR.c_str() << endl;
					}
				}
				else
				{
					str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), (its + 1)->begin.x, (its + 1)->begin.y, (its + 1)->begin.z);
					STR = CStringA(str);
					(*of) << STR.c_str() << endl;
				}
			}
		}
	}
}
//NC�������ʾ
void CGcodeGeneration::ShowNcCode()//��G������ʾ��List�ؼ���
{

}

//̨���ӹ�
void CGcodeGeneration::TableBoardNC(ofstream* of)
{
	TableBoardInSawNC(CTableBoardProcess::GetTableProcessInstance()->GetTableInSawNCElements(), of);
	TableBoardInMillNC(CTableBoardProcess::GetTableProcessInstance()->GetTableInMillNCElements(), of);
	TableBoardOutNC(CTableBoardProcess::GetTableProcessInstance()->GetTableOutNCElements(), of);
}


void CGcodeGeneration::TableBoardInSawNC(vector<vector<vector<vector<elements>>>> data, ofstream* of)
{
	CString str = _T("̨���ӹ��ڲ��Ƭ�ӹ�NC���룺");
	std::string STR = CStringA(str);
	(*of) << STR.c_str() << endl;

	str = _T("G90 G17 M03");//����ֵ��ʽ��XYƽ�棬������ת
	STR = CStringA(str);
	(*of) << STR.c_str() << endl;

	//��ʼ���ƶ���2�������ߵĵط�
	Input_G00(0, 0, 2*CTableBoardProcess::GetTableProcessInstance()->GetBoardHeigh(),of);

	for (vector<vector<vector<vector<elements>>>>::iterator it = data.begin(); it != data.end(); ++it)//��һ����
	{
		for (vector<vector<vector<elements>>>::iterator its = it->begin(); its != it->end(); ++its)//�Ĳ�
		{
			BOOL m_Direction = TRUE;//TRUE��˳��������������������

			for (vector<vector<elements>>::iterator itss = its->begin(); itss != its->end(); ++itss)//�ĸ߶�
			{
				if (m_Direction)//����
				{
					for (vector<elements>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)
					{
						if (itsss->flag == 1)
						{
							//ÿһ���߶�
							if (itsss == itss->begin())
							{
								//��λ�����
								Input_G00(itsss->begin.x, itsss->begin.y, itsss->begin.z, of);
								Input_G01(itsss->end.x, itsss->end.y, itsss->end.z, of);
							}
							else
							{
								Input_G01(itsss->end.x, itsss->end.y, itsss->end.z, of);
							}
							//���һ���ֵ����һ�����͸߶ȵ����һ��
							if (it == data.end() - 1 && its == it->end() - 1 && itss == its->end() - 1 && itsss == itss->end() - 1)
							{
								Input_G00(itsss->end.x, itsss->end.y, 
									            2 * CTableBoardProcess::GetTableProcessInstance()->GetBoardHeigh(), of);
							}
						}
					}
				}
				else//����
				{
					for (vector<elements>::reverse_iterator itsss = itss->rbegin(); itsss != itss->rend(); ++itsss)
					{
						if (itsss->flag == 1)
						{
							if (itsss == itss->rbegin())
							{
								Input_G00(itsss->end.x, itsss->end.y, itsss->end.z, of);
								Input_G01(itsss->begin.x, itsss->begin.y, itsss->begin.z, of);
							}
							else
							{
								Input_G01(itsss->begin.x, itsss->begin.y, itsss->begin.z, of);
							}
							//���һ���ֵ����һ�����͸߶ȵ����һ��
							if (it == data.end() - 1 && its == it->end() - 1 && itss == its->end() - 1 && itsss == itss->rend() - 1)
							{
								Input_G00(itsss->begin.x, itsss->begin.y,
									2 * CTableBoardProcess::GetTableProcessInstance()->GetBoardHeigh(), of);
							}
						}
					}
				}
				
				m_Direction = !m_Direction;
			}
		}
	}

}
void CGcodeGeneration::TableBoardInMillNC(vector<vector<vector<vector<elements>>>> data, ofstream* of)
{
	CString str = _T("G28 Z0 T01 M06");//��T01ϳ��
	std::string STR = CStringA(str);
	(*of) << STR.c_str() << endl;

	for (vector<vector<vector<vector<elements>>>>::iterator it = data.begin(); it != data.end(); ++it)//�Ŀ�
	{
		for (vector<vector<vector<elements>>>::iterator its = it->begin(); its != it->end(); ++its)//�Ĳ�
		{
			BOOL m_ArcDirection = TRUE;

			for (vector<vector<elements>>::iterator itss = its->begin(); itss != its->end(); ++itss)//�ĸ߶�
			{
				if (m_ArcDirection)//����,ֻ�е�һ����û�����һ��
				{
					for (vector<elements>::iterator itsss = itss->begin(); itsss != itss->end(); ++itsss)//�Ķ�
					{
						if (itsss->flag == 1)//ֱ�߶�
						{
							if (its==it->begin()&&itss == its->begin() && itsss == itss->begin())//ÿ���һ������λ�õĵ�һ���߶�
							{
								Input_G00(itsss->begin.x, itsss->begin.y,
									2 * CTableBoardProcess::GetTableProcessInstance()->GetBoardHeigh(), of);
								Input_G00(itsss->begin.x, itsss->begin.y, itsss->begin.z, of);
							}
							else if (itss == its->begin()&&itsss==itss->begin())//ÿ������λ�õĵ�һ���߶�
							{
								Input_G00(itsss->begin.x, itsss->begin.y, itsss->begin.z,of);
							}
							Input_G01(itsss->end.x, itsss->end.y, itsss->end.z, of);
						
						}
						else if (itsss->flag == 2)//Բ����
						{
							//���zΪ0�����������
							Input_G02(itsss->end.x, itsss->end.y, itsss->end.z,
								itsss->center.x - itsss->begin.x, itsss->center.y - itsss->begin.y, of);
						}
					}
				}
				else//����ֻ�����һ��û�е�һ��
				{
					for (vector<elements>::reverse_iterator itsss = itss->rbegin(); itsss != itss->rend(); ++itsss)//�Ķ�
					{
						if (itsss->flag == 1)
						{
							Input_G01(itsss->begin.x, itsss->begin.y, itsss->begin.z, of);

							//���һ���ֵ����һ�����λ�õ����һ��Ԫ��
							if (it == data.end() - 1 && its == it->end() - 1 && itss == its->end() - 1 && itsss == itss->rend() - 1)
							{
								Input_G00(itsss->begin.x, itsss->begin.y,
									2 * CTableBoardProcess::GetTableProcessInstance()->GetBoardHeigh(), of);
							}
						}
						else if (itsss->flag == 2)
						{
							Input_G03(itsss->begin.x, itsss->begin.y, itsss->begin.z,
								itsss->center.x - itsss->end.x, itsss->center.y - itsss->end.y, of);
						}
					}
				}
				m_ArcDirection = !m_ArcDirection;
			}
		}
	}


}
void CGcodeGeneration::TableBoardOutNC(vector<vector<vector<elements>>> data, ofstream* of)
{
	CString str = _T("G28 Z0 T02 M06");//��T02��Ƭ
	std::string STR = CStringA(str);
	(*of) << STR.c_str() << endl;
	for (vector<vector<vector<elements>>>::iterator it = data.begin(); it != data.end(); ++it)//��һ��
	{
		BOOL m_Direction = TRUE;
		for (vector<vector<elements>>::iterator its = it->begin(); its != it->end(); ++its)//�ĸ߶�
		{
			if (m_Direction)//����˳ʱ��
			{
				for (vector<elements>::iterator itss = its->begin(); itss != its->end(); ++itss)//���߶�
				{
					if (itss->flag == 1)
					{
						if (itss == its->begin())//ÿ�θ߶���ߵĵ�һ��Ԫ��
						{
							//��λ�����
							Input_G00(itss->begin.x, itss->begin.y, itss->begin.z, of);
						}

						Input_G01(itss->end.x, itss->end.y, itss->end.z, of);

					}
					else if (itss->flag==2)
					{
						if (itss == its->begin())//ÿ�θ߶���ߵĵ�һ��Ԫ��
						{
							//��λ�����
							Input_G00(itss->begin.x, itss->begin.y, itss->begin.z, of);
						}
						if (itss->arc_direction == 0)//˳ʱ��ʱ��
						{
							Input_G02(itss->end.x, itss->end.y, itss->end.z,
								itss->center.x - itss->begin.x, itss->center.y - itss->begin.y, of);
						}
						else if (itss->arc_direction==1)//��ʱ��
						{
							Input_G03(itss->end.x,itss->end.y,itss->end.z,
								itss->center.x - itss->begin.x, itss->center.y - itss->begin.y, of);
						}
						
					}

					//���һ�����͸߶����һ��Ԫ��
					if (it == data.end() - 1 && its == it->end() - 1 && itss==its->end() - 1)
					{
						Input_G00(itss->end.x, itss->end.y, 2*CTableBoardProcess::GetTableProcessInstance()->GetBoardHeigh(), of);
					}

				}
			}
			else//������ʱ��
			{
				for (vector<elements>::reverse_iterator itss = its->rbegin(); itss != its->rend(); ++itss)//���߶�
				{
					if (itss == its->rbegin())//ÿ�θ߶���ߵĵ�һ��Ԫ��
					{
						Input_G00(itss->end.x, itss->end.y, itss->end.z, of);
					}

					if (itss->flag == 1)
					{		
						Input_G01(itss->begin.x, itss->begin.y, itss->begin.z, of);
					}
					else  if (itss->flag == 2)
					{
						if (itss->arc_direction == 1)//ԭ��������ʱ�룬��������Ӧ����˳ʱ��
						{
							Input_G02(itss->begin.x, itss->begin.y, itss->begin.z,
								itss->center.x - itss->end.x, itss->center.y - itss->end.y, of);
						}
						else if (itss->arc_direction == 0)//ԭ����˳ʱ��ģ�������������ʱ��
						{
							Input_G03(itss->begin.x, itss->begin.y, itss->begin.z,
								itss->center.x - itss->end.x, itss->center.y - itss->end.y, of);
						}
						
					}

					//���һ�����͸߶����һ��Ԫ��
					if (it == data.end() - 1 && its == it->end() - 1 && itss == its->rend() - 1)
					{
						Input_G00(itss->begin.x, itss->begin.y,
							       2 * CTableBoardProcess::GetTableProcessInstance()->GetBoardHeigh(), of);
					}
				}
			}
			

			m_Direction = !m_Direction;
		}
	}
}

//����
void CGcodeGeneration::Input_G00(float posx, float posy, float posz,ofstream* of)
{
	CString str;
	str.Format(_T("G00 X%0.3f Y%0.3f Z%0.3f"),posx,posy,posz);
	std::string STR = CStringA(str);
	(*of) << STR.c_str() << endl;
}
void CGcodeGeneration::Input_G01(float posx, float posy, float posz, ofstream* of)
{
	CString str;
	str.Format(_T("G01 X%0.3f Y%0.3f Z%0.3f F1500"), posx, posy, posz);
	std::string STR = CStringA(str);
	(*of) << STR.c_str() << endl;
}
void CGcodeGeneration::Input_G02(float posx, float posy, float posz,float posi,float posj, ofstream* of)
{
	CString str;
	str.Format(_T("G02 X%0.3f Y%0.3f I%0.3f J%0.3f Z%0.3f F1500"), posx, posy, posi, posj, posz);
	
	std::string STR = CStringA(str);
	(*of) << STR.c_str() << endl;
}
void CGcodeGeneration::Input_G03(float posx, float posy, float posz, float posi, float posj, ofstream* of)
{
	CString str;
	
	str.Format(_T("G03 X%0.3f Y%0.3f I%0.3f J%0.3f Z%0.3f F1500"), posx, posy, posi, posj, posz);


	std::string STR = CStringA(str);
	(*of) << STR.c_str() << endl;
}