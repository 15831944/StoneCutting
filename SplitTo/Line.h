#pragma once
#include<vector>
#include"OPENGL\CadBase.h"
#include"Arc.h"
#include<math.h>
using namespace std;
class CLine
{
public:
	CLine(void);
	~CLine(void);
	CPoint3D m_begin;
	CPoint3D m_end;
	UINT flag;
     float sum;
public:
	
	static double Length(CPoint3D m_begin, CPoint3D m_end);

//����
public:
	static CPoint3D IntersectOfLine(const CPoint3D& pt0, const CVector3D& vec0,const CPoint3D& pt1, const CVector3D& vec1);//ֱ����ֱ�ߵĽ���
	static CPoint3D IntersectOfArc(CPoint3D& LineBegin, CPoint3D& LineEnd, CPoint3D& center, float radio,int mark, /*float beginAngle, float endAngle,*/ 
		                       CPtrArray& XFarray, int index); //�����ж���ֱ������µ�ֱ����Բ���Ľ�������

public://ʱ��ָ�岹
	static vector<CPoint3D>  LineTDMInterpolation(CPoint3D ptBegin, CPoint3D ptEnd, float Inter, float F);//XOY��ʼ�㣬��ֹ�㣬�岹����ms�Լ������ٶ�mm/min
	static vector<CPoint3D>  LineTDMInterpolationXZ(CPoint3D ptBegin, CPoint3D ptEnd, float Inter, float F);
	static vector<CPoint3D>  LineTDMInterpolationYZ(CPoint3D ptBegin, CPoint3D ptEnd, float Inter, float F);
};