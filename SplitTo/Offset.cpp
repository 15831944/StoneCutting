#include "stdafx.h"
#include "Offset.h"

#define PI 3.1415926
COffset::COffset()
{
}


COffset::~COffset()
{
}

CVector3D COffset::slope(CPoint3D PtBegin, CPoint3D PtEnd)//����������Ҫ�õ���XYƽ���ϵ�б��
{
	CVector3D LineSlope;
	LineSlope.dx = PtEnd.x - PtBegin.x;
	LineSlope.dy = PtEnd.y - PtBegin.y;
	LineSlope.dz = PtEnd.z - PtBegin.z;
	return LineSlope;

}
void  COffset::Polygeon(CPtrArray& Array, float distance, int number, float depth)
{
	LineOffsetPoint.clear();//�������
	LineIntersection.clear();//�������
	ExtendLine.clear();
	Line.clear();

	for (int i = 0; i < Array.GetSize(); ++i)//���趼�ߵ����󵶲��������״˳ʱ��ӹ�������û��ȥ��������ƫ����
	{
		CVector3D Slope = slope(((CLine*)Array.GetAt(i))->m_begin, ((CLine*)Array.GetAt(i))->m_end);
		OffsetPoint NewPt;
		double length = ((CLine*)Array.GetAt(i))->Length(((CLine*)Array.GetAt(i))->m_begin, ((CLine*)Array.GetAt(i))->m_end);//ֱ�ߵĳ���
		double cosXY = fabs(Slope.dx) / sqrt(pow(Slope.dx, 2) + pow(Slope.dy, 2) + pow(Slope.dz, 2));//����ֵ,����ֱ�ߵķ���������X��ĵ�λ�����ļн����
		double sinXY = sqrt(1 - pow(cosXY, 2));//����ֵ
		OffsetPoint point;

		if (Slope.dx < 0.000001&&Slope.dx>-0.000001)
		{
			if (((CLine*)Array.GetAt(i))->m_begin.y>((CLine*)Array.GetAt(i))->m_end.y)
			{
				point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x + distance;
				point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y;
				point.begin.z = 0;
				point.end.x = ((CLine*)Array.GetAt(i))->m_end.x + distance;
				point.end.y = ((CLine*)Array.GetAt(i))->m_end.y;
				point.end.z = 0;

				NewPt.begin = point.begin - Slope.GetNormal() * 50;// ����
				NewPt.end = point.end + Slope.GetNormal() * 50;// ����

			}
			else
			{
				point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x - distance;
				point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y;
				point.begin.z = 0;
				point.end.x = ((CLine*)Array.GetAt(i))->m_end.x - distance;
				point.end.y = ((CLine*)Array.GetAt(i))->m_end.y;
				point.end.z = 0;

				NewPt.begin = point.begin + Slope.GetNormal() * 50;// ����
				NewPt.end = point.end - Slope.GetNormal() * 50;// ����

			}
		}
		else
		{
			double ratio = Slope.dy / Slope.dx;

			if (ratio > 0)//б��Ϊ������б��Ϊ0
			{
				if (((CLine*)Array.GetAt(i))->m_begin.x <= ((CLine*)Array.GetAt(i))->m_end.x)
				{
					point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x - distance*sinXY;
					point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y + distance*cosXY;
					point.begin.z = 0;
					point.end.x = ((CLine*)Array.GetAt(i))->m_end.x - distance*sinXY;
					point.end.y = ((CLine*)Array.GetAt(i))->m_end.y + distance*cosXY;
					point.end.z = 0;


				}
				else
				{
					point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x + distance*sinXY;
					point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y - distance*cosXY;
					point.begin.z = 0;
					point.end.x = ((CLine*)Array.GetAt(i))->m_end.x + distance*sinXY;
					point.end.y = ((CLine*)Array.GetAt(i))->m_end.y - distance*cosXY;
					point.end.z = 0;


				}
			}
			else if (ratio<0)//б��Ϊ����ʱ��
			{
				if (((CLine*)Array.GetAt(i))->m_begin.x <= ((CLine*)Array.GetAt(i))->m_end.x)
				{
					point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x + distance*sinXY;
					point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y + distance*cosXY;
					point.begin.z = 0;
					point.end.x = ((CLine*)Array.GetAt(i))->m_end.x + distance*sinXY;
					point.end.y = ((CLine*)Array.GetAt(i))->m_end.y + distance*cosXY;
					point.end.z = 0;

				}
				else
				{
					point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x - distance*sinXY;
					point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y - distance*cosXY;
					point.begin.z = 0;
					point.end.x = ((CLine*)Array.GetAt(i))->m_end.x - distance*sinXY;
					point.end.y = ((CLine*)Array.GetAt(i))->m_end.y - distance*cosXY;
					point.end.z = 0;


				}

			}
			else
			{
				if (((CLine*)Array.GetAt(i))->m_begin.x <= ((CLine*)Array.GetAt(i))->m_end.x)
				{
					point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x;
					point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y + distance;
					point.begin.z = 0;
					point.end.x = ((CLine*)Array.GetAt(i))->m_end.x;
					point.end.y = ((CLine*)Array.GetAt(i))->m_end.y + distance;
					point.end.z = 0;

				}
				else
				{
					point.begin.x = ((CLine*)Array.GetAt(i))->m_begin.x;
					point.begin.y = ((CLine*)Array.GetAt(i))->m_begin.y - distance;
					point.begin.z = 0;
					point.end.x = ((CLine*)Array.GetAt(i))->m_end.x;
					point.end.y = ((CLine*)Array.GetAt(i))->m_end.y - distance;
					point.end.z = 0;


				}

			}

			NewPt.begin = point.begin - Slope.GetNormal() * 50;// ����
			NewPt.end = point.end + Slope.GetNormal() * 50;// ����
		}
		LineOffsetPoint.push_back(point);
		ExtendLine.push_back(NewPt);
	}
	for (int i = 0; i != number; ++i)
	{
		for (vector<OffsetPoint>::iterator it = ExtendLine.begin(); it != ExtendLine.end(); ++it)
		{
			CVector3D Dir = slope(it->end, it->begin);
			CVector3D Roat = CVector3D(Dir.dy, -1 * Dir.dx, 0);//ͶӰ��XYƽ���ϵ���������ʱ����ת90
			//CVector3D Roat = CVector3D(-1*Dir.dy, Dir.dx, 0);//ͶӰ��XYƽ���ϵ�������˳ʱ����ת90
			vector<OffsetPoint> Sum;
			OffsetPoint Pos;
			Pos.begin = it->begin + Roat.GetNormal()*distance*i;
			Pos.end = it->end + Roat.GetNormal()*distance*i;
			Pos.begin.z -= (i + 1)*depth;//z�����ϵľ����ƫ�þ���һ����45�Ƚ�
			Pos.end.z -= (i + 1)*depth;
			Sum.push_back(Pos);
			Line.push_back(Sum);
		}
	}


	//���������Ǹ����������ֱ�߷��̲��������ֱ�ߵĽ��㣬�ٽ�����洢��LineInteraction���棬��󽫵�ȡ������

	vector<CVector3D> Juge;
	CVector3D CloseGrap = CVector3D(0, 0, 0);
	for (vector<OffsetPoint>::iterator it = LineOffsetPoint.begin(); it != LineOffsetPoint.end(); ++it)//�ж��Ƿ��Ƿ��ͼ�Σ�ʸ����Ϊ0
	{
		Juge.push_back(slope(it->begin, it->end));
	}
	for (vector<CVector3D>::iterator it = Juge.begin(); it != Juge.end(); ++it)
	{
		CloseGrap += *it;
	}
	for (vector<OffsetPoint>::iterator it = LineOffsetPoint.begin(); it != LineOffsetPoint.end(); ++it)
	{


		if (CloseGrap.GetLength() == 0)//���ͼ����β����
		{

			if (it == LineOffsetPoint.begin())
			{
				LineIntersection.push_back(it->begin);
				CPoint3D  point = TwoLineNot(*it, *(it + 1));
				LineIntersection.push_back(point);
			}
			else if (it == LineOffsetPoint.end() - 1)
			{

				CPoint3D point;
				point = TwoLineNot(*it, *(LineOffsetPoint.begin()));
				LineIntersection.push_back(point);

			}

			else
			{
				CPoint3D  point = TwoLineNot(*it, *(it + 1));
				LineIntersection.push_back(point);
			}
		}
		else//����ͼ��
		{
			if (it == LineOffsetPoint.begin())
			{
				LineIntersection.push_back(it->begin);
			}
			if (it != LineOffsetPoint.end() - 1)
			{

				CPoint3D  point = TwoLineNot(*it, *(it + 1));
				LineIntersection.push_back(point);
			}
			if (it == LineOffsetPoint.end() - 1)
				LineIntersection.push_back(it->end);

		}

	}

}

CPoint3D  COffset::TwoLineNot(OffsetPoint One, OffsetPoint Another)//��֪����ֱ�����佻�����굫��ȱ��ˮƽ����ֱ��ֱ�ߵĽ�������
{
	CPoint3D point;//�洢����
	double X, Y, x, y;
	double A, B, a, b;
	if (slope(One.begin, One.end).dx != 0 && slope(Another.begin, Another.end).dx != 0)//����ֱ�߶���б��
	{
		A = slope(One.begin, One.end).dy / slope(One.begin, One.end).dx;
		a = slope(Another.begin, Another.end).dy / slope(Another.begin, Another.end).dx;
		B = (One.end.x*One.begin.y - One.begin.x*One.end.y) / (One.end.x - One.begin.x);
		b = (Another.end.x*Another.begin.y - Another.begin.x * Another.end.y) / (Another.end.x - Another.begin.x);
		point.x = (b - B) / (A - a);
		point.y = (A*b - a*B) / (A - a);
		point.z = 0;
	}
	else if (slope(One.begin, One.end).dx == 0 && slope(Another.begin, Another.end).dx != 0)//�ڶ���ֱ��б�������
	{
		point.x = One.begin.x;
		a = slope(Another.begin, Another.end).dy / slope(Another.begin, Another.end).dx;
		b = (Another.end.x*Another.begin.y - Another.begin.x * Another.end.y) / (Another.end.x - Another.begin.x);
		point.y = a*One.begin.x + b;

	}
	else if (slope(One.begin, One.end).dx != 0 && slope(Another.begin, Another.end).dx == 0)//��һ��ֱ��б�������
	{
		point.x = Another.begin.x;
		A = slope(One.begin, One.end).dy / slope(One.begin, One.end).dx;
		B = (One.end.x*One.begin.y - One.begin.x*One.end.y) / (One.end.x - One.begin.x);
		point.y = A*Another.begin.x + B;
	}
	else
	{
		AfxMessageBox(_T("����ֱ��ƽ�У�"));
	}
	return point;
}

