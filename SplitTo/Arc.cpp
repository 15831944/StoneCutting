#include "StdAfx.h"
#include "Arc.h"
#include<math.h>
#include"Circle.h"
#include"Line.h"
#define PI 3.1415926

CArc::CArc(void)
{
	m_begin.x=0;
	m_begin.y=0;
	m_begin.z=0;
	m_end.x=0;
	m_end.y=0;
	m_end.z=0;
	m_center.x=0;
	m_center.y=0;
	m_center.z=0;
	m_begin_angle=0.0;
	m_end_angle=0.0;
	m_radio=0.0;
	flag=2;
	m_Tudu=0.0;
	m_Direction=FALSE;
	
}


CArc::~CArc(void)
{
}



//Բ������ʼ�����ֹ���������ȡ����������ж�����˳ʱ�뻹����ʱ�룿������NC��������
BOOL CArc::Calculate(CPoint3D& center,float radio,float beginAngle,float endAngle,CPtrArray& XFarray,int index)
{
	float m_beginAng=PI*beginAngle/180;
	float m_endAng=PI*endAngle/180;
	((CArc*)XFarray.GetAt(index))->m_begin.x=center.x+radio*cos(m_beginAng);
	((CArc*)XFarray.GetAt(index))->m_begin.y=center.y+radio*sin(m_beginAng);
	//((CArc*)XFarray.GetAt(index))->m_begin.z=0.0;
	((CArc*)XFarray.GetAt(index))->m_begin.z = center.z;
	((CArc*)XFarray.GetAt(index))->m_end.x=center.x+radio*cos(m_endAng);
	((CArc*)XFarray.GetAt(index))->m_end.y=center.y+radio*sin(m_endAng);
	//((CArc*)XFarray.GetAt(index))->m_end.z=0.0;
	((CArc*)XFarray.GetAt(index))->m_end.z = center.z;

	CPoint3D PTSS = ((CArc*)XFarray.GetAt(index))->m_begin;
	CPoint3D PTSE = ((CArc*)XFarray.GetAt(index))->m_end;

	if(index!=0)
	{

	if(
		(fabs(((CArc*)XFarray.GetAt(index))->m_begin.x-((CArc*)XFarray.GetAt(index-1))->m_end.x)<0.01&& fabs(((CArc*)XFarray.GetAt(index))->m_begin.y - ((CArc*)XFarray.GetAt(index - 1))->m_end.y)<0.01)
	||  (fabs(((CArc*)XFarray.GetAt(index))->m_begin.x-((CLine*)XFarray.GetAt(index - 1))->m_end.x)<0.01&&fabs(((CArc*)XFarray.GetAt(index))->m_begin.y - ((CLine*)XFarray.GetAt(index - 1))->m_end.y)<0.01)
		)//Բ�����ǰ��Ҫ��Ԫ��!!!?������д���
	{

	((CArc*)XFarray.GetAt(index))->m_begin.x=center.x+radio*cos(m_beginAng);
	((CArc*)XFarray.GetAt(index))->m_begin.y=center.y+radio*sin(m_beginAng);
	((CArc*)XFarray.GetAt(index))->m_end.x=center.x+radio*cos(m_endAng);
	((CArc*)XFarray.GetAt(index))->m_end.y=center.y+radio*sin(m_endAng);
	((CArc*)XFarray.GetAt(index)) ->m_Direction = TRUE;
	return TRUE;//��ʱ��Ϊtrue��˳ʱ���Ϊfalse

	}

	else
	{
		((CArc*)XFarray.GetAt(index))->m_begin.x=center.x+radio*cos(m_endAng);
		((CArc*)XFarray.GetAt(index))->m_begin.y=center.y+radio*sin(m_endAng);
		((CArc*)XFarray.GetAt(index))->m_end.x=center.x+radio*cos(m_beginAng);
		((CArc*)XFarray.GetAt(index))->m_end.y=center.y+radio*sin(m_beginAng);

		((CArc*)XFarray.GetAt(index))->m_Direction = FALSE;
		return FALSE;
	}

	}
	else//����ж�Բ��Ϊ��ʼԪ�ص�˳��
	{
		if (XFarray.GetSize() == 1)
		{
			((CArc*)XFarray.GetAt(index))->m_Direction = TRUE;

			return TRUE;//ֻ��һ��Ԫ�صĻ�Ĭ��Ϊ��ʱ��
		}
		else
		{
			if (
				(fabs(((CArc*)XFarray.GetAt(0))->m_end.x - ((CArc*)XFarray.GetAt(1))->m_begin.x)<0.01&& fabs(((CArc*)XFarray.GetAt(0))->m_end.y - ((CArc*)XFarray.GetAt(1))->m_begin.y)<0.01)
			||  (fabs(((CArc*)XFarray.GetAt(0))->m_end.x - ((CLine*)XFarray.GetAt(1))->m_begin.x)<0.01&& fabs(((CArc*)XFarray.GetAt(0))->m_end.y - ((CLine*)XFarray.GetAt(1))->m_begin.y)<0.01)
			   )
			{
				((CArc*)XFarray.GetAt(index))->m_begin.x = center.x + radio*cos(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_begin.y = center.y + radio*sin(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_end.x = center.x + radio*cos(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_end.y = center.y + radio*sin(m_endAng);

				((CArc*)XFarray.GetAt(index))->m_Direction = TRUE;

				return TRUE;//��ʱ��Ϊtrue��˳ʱ���Ϊfalse
			}
			else
			{
				((CArc*)XFarray.GetAt(index))->m_begin.x = center.x + radio*cos(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_begin.y = center.y + radio*sin(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_end.x = center.x + radio*cos(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_end.y = center.y + radio*sin(m_beginAng);

				((CArc*)XFarray.GetAt(index))->m_Direction = FALSE;

				return FALSE;
			}
		}
	}
}

//���߶�ͨ������ʼ������껹��͹����ȡ��Բ�������Լ��뾶
void CArc::PolyCalculate(CPoint3D begin,CPoint3D end,float TuduAngle)
{

	float m_DisBeEnd=sqrt(pow((begin.x-end.x),2)+pow((begin.y-end.y),2)+pow((begin.z-end.z),2));//�����ҳ�

	CPoint3D m_LineCenter;
	 m_LineCenter.x=(begin.x+end.x)/2;//���е�����
	  m_LineCenter.y=(begin.y+end.y)/2;//���е�����
	  m_LineCenter.z=(begin.z+end.z)/2;//���е�����

	float m_CenterAng=4*atan(fabs(TuduAngle));//�������

	m_radio=0.5*m_DisBeEnd/sin(0.5*m_CenterAng);//����뾶

	
    float h=sqrt(pow(m_radio,2)-pow(m_DisBeEnd*0.5,2));//���㽻�������ĵľ���

	if(TuduAngle<=0.0)//����������յ���ұߣ�˳ʱ��͹��ֵΪ��*******XY����ƽ��
	{
		if(TuduAngle>-1)
		{

			if((begin.x<end.x)&&(begin.y>end.y))//Բ�����Բ���ڵ�һ����
		{
			m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.x<end.x&&begin.y<end.y)//Բ�����Բ���ڵڶ�����
		{
			m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.x>end.x&&begin.y<end.y)//Բ�����Բ���ڵ�������
		{
			m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.x>end.x&&begin.y>end.y)//Բ�����Բ���ڵ�������
		{
			m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.y==end.y)//������������ȵ�ʱ��
		{
			if(begin.x<=end.x)//��ʼ���ڵڶ����ޣ���ֹ���ڵ�һ����
			{
				m_center.y=m_LineCenter.y-h;
				m_center.x=m_LineCenter.x;
				m_center.z=0;
			}
			else//��ʼ���ڵ������ޣ���ֹ���ڵ�������
			{
				m_center.y=m_LineCenter.y+h;
				m_center.x=m_LineCenter.x;
				m_center.z=0;
			}

		}
		else if(begin.x==end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
		{
			if(begin.y<=end.y)//��ʼ���ڵ�һ���ޣ���ֹ���ڵ�������
			{
				m_center.x=m_LineCenter.x+h;
				m_center.y=m_LineCenter.y;
				m_center.z=0;
			}
			else//��ʼ���ڵ������ޣ���ֹ���ڵڶ�����
			{
				m_center.x=m_LineCenter.x-h;
				m_center.y=m_LineCenter.y;
				m_center.z=0;
			}
		}
		
		
		}
		else if(TuduAngle==-1)
		{
			m_center.x=m_LineCenter.x;
			m_center.y=m_LineCenter.y;
			m_center.z=0;
		}
		else
		{
			if((begin.x<end.x)&&(begin.y>end.y))//Բ�����2���յ�4
			{
				m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			else if(begin.x<end.x&&begin.y<end.y)//Բ�����3���յ�1
			{
				m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			else if(begin.x>end.x&&begin.y<end.y)//Բ�����4���յ�2
			{
				m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			else if(begin.x>end.x&&begin.y>end.y)//Բ�����1���յ����
			{
				m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			
			else if(begin.y==end.y)//������������ȵ�ʱ��
			{
				if(begin.x<=end.x)
				{
					m_center.y=m_LineCenter.y+h;
					m_center.x=m_LineCenter.x;
					m_center.z=0;
				}
				else
				{
					m_center.y=m_LineCenter.y-h;
					m_center.x=m_LineCenter.x;
					m_center.z=0;
				}

			}
			else if(begin.x==end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if(begin.y<=end.y)
				{
					m_center.x=m_LineCenter.x-h;
					m_center.y=m_LineCenter.y;
					m_center.z=0;
				}
				else
				{
					m_center.x=m_LineCenter.x+h;
					m_center.y=m_LineCenter.y;
					m_center.z=0;
				}
			}
		}

	}

	else//������յ����ߣ���ʱ��
	{
		if(TuduAngle<1)
		{
			if((begin.x>end.x)&&(begin.y<end.y))//Բ�����Բ���ڵ�һ����
		{
			m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.x>end.x&&begin.y>end.y)//Բ�����Բ���ڵڶ�����
		{
			m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.x<end.x&&begin.y>end.y)//Բ�����Բ���ڵ�������
		{
			m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.x<end.x&&begin.y<end.y)//Բ�����Բ���ڵ�������
		{
			m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
			m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
			m_center.z=0;
		}
		else if(begin.y==end.y)//��ʼ�����ֹ�����������ȵ�ʱ��
		{
			if(begin.x<=end.x)
			{
				m_center.y=m_LineCenter.y+h;
				m_center.x=m_LineCenter.x;
				m_center.z=0;
			}
			else
			{
				m_center.y=m_LineCenter.y-h;
				m_center.x=m_LineCenter.x;
				m_center.z=0;
			}
		}
		else if(begin.x==end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
		{
			if(begin.y<=end.y)//��ʼ���ڵ�4���ޣ���ֹ���ڵ�1����
			{
				m_center.x=m_LineCenter.x-h;
				m_center.y=m_LineCenter.y;
				m_center.z=0;
			}
			else//��ʼ���ڵ�2���ޣ���ֹ���ڵ�3����
			{
				m_center.x=m_LineCenter.x+h;
				m_center.y=m_LineCenter.y;
				m_center.z=0;
			}
		}
		}
		else if(TuduAngle==1)
		{
			m_center.x=m_LineCenter.x;
			m_center.y=m_LineCenter.y;
			m_center.z=0;
		}
		else
		{
			if((begin.x<end.x)&&(begin.y>end.y))//Բ�����2���յ�4
			{
				m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			else if(begin.x<end.x&&begin.y<end.y)//Բ�����3���յ�1
			{
				m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y-h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			else if(begin.x>end.x&&begin.y<end.y)//Բ�����4���յ�2
			{
				m_center.x=m_LineCenter.x+h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			else if(begin.x>end.x&&begin.y>end.y)//Բ�����1���յ����
			{
				m_center.x=m_LineCenter.x-h*abs(m_begin.y-m_end.y)/m_DisBeEnd;
				m_center.y=m_LineCenter.y+h*abs(m_begin.x-m_end.x)/m_DisBeEnd;
				m_center.z=0;
			}
			else if(begin.y==end.y)//��ʼ�����ֹ�����������ȵ�ʱ��
			{
				if(begin.x<=end.x)
				{
					m_center.y=m_LineCenter.y-h;
					m_center.x=m_LineCenter.x;
					m_center.z=0;
				}
				else
				{
					m_center.y=m_LineCenter.y+h;
					m_center.x=m_LineCenter.x;
					m_center.z=0;
				}
			}
			else if(begin.x==end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if(begin.y<=end.y)
				{
					m_center.x=m_LineCenter.x+h;
					m_center.y=m_LineCenter.y;
					m_center.z=0;
				}
				else
				{
					m_center.x=m_LineCenter.x-h;
					m_center.y=m_LineCenter.y;
					m_center.z=0;
				}
			}
		}

	}
	
	CVector3D CCXY(1,0,0);
	CVector3D CS(begin.x-m_center.x,begin.y-m_center.y);
	CVector3D CE(end.x-m_center.x,end.y-m_center.y);

	m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
	m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;

	if((begin.x>m_center.x)&&(begin.y>m_center.y))//Բ��������Բ���ڵ�һ����
	{
		if((end.x>m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y<m_center.y))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
	}
	else if(begin.x<m_center.x&&begin.y>m_center.y)//Բ��������Բ���ڵڶ�����
	{
		if((end.x>m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y<m_center.y))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle=0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
	}
	else if(begin.x<m_center.x&&begin.y<m_center.y)//Բ��������Բ���ڵ�������
	{
		if((end.x>m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y<m_center.y))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
	}
	else if(begin.x>m_center.x&&begin.y<m_center.y)//Բ��������Բ���ڵ�������
	{
		if((end.x>m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y>m_center.y))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else if((end.x<m_center.x)&&(end.y<m_center.y))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle=360-0.5*acos((CS|CCXY)/(CS.GetLength()*CCXY.GetLength()))*360/PI;
			m_end_angle=360-0.5*acos((CE|CCXY)/(CE.GetLength()*CCXY.GetLength()))*360/PI;
		}
	}


}

void CArc::PolyDrawNArc(CPoint3D& center,float start_angle,float end_angle,float delta_angle,float radius)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f,0.5f,0.5f);
	float vx,vy;
	start_angle=2*PI*start_angle/360;
	end_angle=2*PI*end_angle/360;
	if(start_angle<end_angle)
	{
		for(float a=start_angle;a<=end_angle;a+=delta_angle)  
		{  
			vx=center.x+radius*cos(a);  
			vy=center.y+radius*sin(a);  
			glVertex3f(vx,vy,0.0f);  
		}
	}
	else
	{
		for(float a=start_angle-2*PI;a<=end_angle;a+=delta_angle)  
		{  
			vx=center.x+radius*cos(a);  
			vy=center.y+radius*sin(a);  
			glVertex3f(vx,vy,0.0f);  
		}
	}

	glEnd(); 
}


void CArc::PolyDrawSArc(CPoint3D& center,float start_angle,float end_angle,float delta_angle,float radius)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f,0.5f,0.5f);
	float vx,vy;
	start_angle=2*PI*start_angle/360;
	end_angle=2*PI*end_angle/360;
	if(end_angle<start_angle)
	{

		for (float a=start_angle;a>=end_angle;a-=delta_angle)  
		{  
			vx=center.x+radius*cos(a);  

			vy=center.y+radius*sin(a);  
			glVertex3f(vx,vy,0.0f);  
		}
	}
	else
	{
		for (float a=start_angle;a>=end_angle-2*PI;a-=delta_angle)  
		{  
			vx=center.x+radius*cos(a);  

			vy=center.y+radius*sin(a);  
			glVertex3f(vx,vy,0.0f);  
		}
	}
	glEnd(); 
}



void CArc::GLDrawArc(CPoint3D& center,float start_angle,float end_angle,float delta_angle,float radius,CPtrArray& XFarray,int index)
{
	BOOL Direction=Calculate(center,radius,start_angle,end_angle,XFarray,index);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f,0.5f,0.5f);
	float vx,vy;
	
	if(Direction)//��ʱ��
	{
		start_angle=2*PI*start_angle/360;
		end_angle=2*PI*end_angle/360;
		if(start_angle<end_angle)
	{
		for(float a=start_angle;a<=end_angle;a+=delta_angle)  
	  {  
		 vx=center.x+radius*cos(a);  
		 vy=center.y+radius*sin(a);  
		 glVertex3f(vx, vy, center.z);
	   }
	}
		else
	{
		for(float a=start_angle-2*PI;a<=end_angle;a+=delta_angle)  
	   {  
		 vx=center.x+radius*cos(a);  
		 vy=center.y+radius*sin(a);  
		 glVertex3f(vx, vy, center.z);
	    }
     }


	
	}
	else //˳ʱ��
	{
		
		start_angle=2*PI*start_angle/360;
		end_angle=2*PI*end_angle/360;
		if(end_angle<start_angle)
		{
		for (float a=end_angle;a>=start_angle-2*PI;a-=delta_angle)  
	{  
		 vx=center.x+radius*cos(a);  
		
		 vy=center.y+radius*sin(a);  
		 glVertex3f(vx, vy, center.z);
	}
		}
		else
		{
			for (float a=start_angle;a<=end_angle;a+=delta_angle)  
	{  
		 vx=center.x+radius*cos(a);  
		
		 vy=center.y+radius*sin(a);  
		 glVertex3f(vx, vy, center.z);
	}
		}

	}
	
	glEnd();  
}

//XOZƽ��***********1230XZ��YZƽ��ķ����ж�Ҫ��������ǰ��һ�������⣬��Ҫ��Ҫy����x���������
BOOL CArc::CalculateXZ(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray, int index)
{
	float m_beginAng = PI*beginAngle / 180;
	float m_endAng = PI*endAngle / 180;
	((CArc*)XFarray.GetAt(index))->m_begin.x = center.x + radio*cos(m_beginAng);
	((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_beginAng);
	((CArc*)XFarray.GetAt(index))->m_begin.y = center.y;
	((CArc*)XFarray.GetAt(index))->m_end.x = center.x + radio*cos(m_endAng);
	((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_endAng);
	((CArc*)XFarray.GetAt(index))->m_end.y = center.y;

	if (index != 0)
	{
		if (
			(fabs(((CArc*)XFarray.GetAt(index))->m_begin.x - ((CArc*)XFarray.GetAt(index - 1))->m_end.x)<0.01&& fabs(((CArc*)XFarray.GetAt(index))->m_begin.z - ((CArc*)XFarray.GetAt(index - 1))->m_end.z)<0.01)
			|| (fabs(((CArc*)XFarray.GetAt(index))->m_begin.x - ((CLine*)XFarray.GetAt(index - 1))->m_end.x)<0.01&&fabs(((CArc*)XFarray.GetAt(index))->m_begin.z - ((CLine*)XFarray.GetAt(index - 1))->m_end.z)<0.01)
			)
		{
			((CArc*)XFarray.GetAt(index))->m_begin.x = center.x + radio*cos(m_beginAng);
			((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_beginAng);
			((CArc*)XFarray.GetAt(index))->m_end.x = center.x + radio*cos(m_endAng);
			((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_endAng);
			return TRUE;//��ʱ��Ϊtrue��˳ʱ���Ϊfalse
		}
		else
		{
			((CArc*)XFarray.GetAt(index))->m_begin.x = center.x + radio*cos(m_endAng);
			((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_endAng);
			((CArc*)XFarray.GetAt(index))->m_end.x = center.x + radio*cos(m_beginAng);
			((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_beginAng);
			return FALSE;
		}

	}
	else
	{
			if (
				(fabs(((CArc*)XFarray.GetAt(0))->m_end.x - ((CArc*)XFarray.GetAt(1))->m_begin.x)<0.01&& fabs(((CArc*)XFarray.GetAt(0))->m_end.z - ((CArc*)XFarray.GetAt(1))->m_begin.z)<0.01)
				|| (fabs(((CArc*)XFarray.GetAt(0))->m_end.x - ((CLine*)XFarray.GetAt(1))->m_begin.x)<0.01&& fabs(((CArc*)XFarray.GetAt(0))->m_end.z - ((CLine*)XFarray.GetAt(1))->m_begin.z)<0.01)
				)
			{
				((CArc*)XFarray.GetAt(index))->m_begin.x = center.x + radio*cos(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_end.x = center.x + radio*cos(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_endAng);
				return TRUE;//��ʱ��Ϊtrue��˳ʱ���Ϊfalse
			}
			else
			{
				((CArc*)XFarray.GetAt(index))->m_begin.x = center.x + radio*cos(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_end.x = center.x + radio*cos(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_beginAng);
				return FALSE;
			}
	}
}

void CArc::GLDrawArcXZ(CPoint3D& center, float start_angle, float end_angle, float delta_angle, float radius, CPtrArray& XFarray, int index)
{
	BOOL Direction = CalculateXZ(center, radius, start_angle, end_angle, XFarray, index);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	float vx, vz;

	if (Direction)//��ʱ��
	{
		start_angle = 2 * PI*start_angle / 360;
		end_angle = 2 * PI*end_angle / 360;
		if (start_angle<end_angle)
		{
			for (float a = start_angle; a <= end_angle; a += delta_angle)
			{
				vx = center.x + radius*cos(a);
				vz = center.z + radius*sin(a);
				glVertex3f(vx, center.y, vz);
			}
		}
		else
		{
			for (float a = start_angle - 2 * PI; a <= end_angle; a += delta_angle)
			{
				vx = center.x + radius*cos(a);
				vz = center.z + radius*sin(a);
				glVertex3f(vx,center.y, vz);
			}
		}



	}
	else //˳ʱ��
	{

		start_angle = 2 * PI*start_angle / 360;
		end_angle = 2 * PI*end_angle / 360;
		if (end_angle<start_angle)
		{
			for (float a = end_angle; a >= start_angle - 2 * PI; a -= delta_angle)
			{
				vx = center.x + radius*cos(a);

				vz = center.z + radius*sin(a);
				glVertex3f(vx, center.y, vz);
			}
		}
		else
		{
			for (float a = start_angle; a <= end_angle; a += delta_angle)
			{
				vx = center.x + radius*cos(a);

				vz = center.z + radius*sin(a);
				glVertex3f(vx, center.y, vz);
			}
		}

	}

	glEnd();
}


void CArc::PolyCalculateXZ(CPoint3D begin, CPoint3D end, float TuduAngle)
{

	float m_DisBeEnd = sqrt(pow((begin.x - end.x), 2) + pow((begin.z - end.z), 2) + pow((begin.y - end.y), 2));//�����ҳ�

	CPoint3D m_LineCenter;
	m_LineCenter.x = (begin.x + end.x) / 2;//���е�����
	m_LineCenter.y = (begin.y + end.y) / 2;//���е�����
	m_LineCenter.z = (begin.z + end.z) / 2;//���е�����

	float m_CenterAng = 4 * atan(fabs(TuduAngle));//�������

	m_radio = 0.5*m_DisBeEnd / sin(0.5*m_CenterAng);//����뾶


	float h = sqrt(pow(m_radio, 2) - pow(m_DisBeEnd*0.5, 2));//���㽻�������ĵľ���

	if (TuduAngle <= 0.0)//����������յ���ұߣ�˳ʱ��͹��ֵΪ��*******XZ����ƽ��
	{
		if (TuduAngle>-1)
		{

			if ((begin.x<end.x) && (begin.z>end.z))//Բ�����Բ���ڵ�һ����
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x<end.x&&begin.z<end.z)//Բ�����Բ���ڵڶ�����
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x>end.x&&begin.z<end.z)//Բ�����Բ���ڵ�������
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x>end.x&&begin.z>end.z)//Բ�����Բ���ڵ�������
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.z == end.z)//������������ȵ�ʱ��
			{
				if (begin.x <= end.x)//��ʼ���ڵڶ����ޣ���ֹ���ڵ�һ����
				{
					m_center.z = m_LineCenter.z - h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}
				else//��ʼ���ڵ������ޣ���ֹ���ڵ�������
				{
					m_center.z = m_LineCenter.z + h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}

			}
			else if (begin.x == end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)//��ʼ���ڵ�һ���ޣ���ֹ���ڵ�������
				{
					m_center.x = m_LineCenter.x + h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
				else//��ʼ���ڵ������ޣ���ֹ���ڵڶ�����
				{
					m_center.x = m_LineCenter.x - h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
			}


		}
		else if (TuduAngle == -1)
		{
			m_center.x = m_LineCenter.x;
			m_center.z = m_LineCenter.z;
			m_center.y = 0;
		}
		else
		{
			if ((begin.x<end.x) && (begin.z>end.z))//Բ�����2���յ�4
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x<end.x&&begin.z<end.z)//Բ�����3���յ�1
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x>end.x&&begin.z<end.z)//Բ�����4���յ�2
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x>end.x&&begin.z>end.z)//Բ�����1���յ����
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}

			else if (begin.z == end.z)//������������ȵ�ʱ��
			{
				if (begin.x <= end.x)
				{
					m_center.z = m_LineCenter.z + h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}
				else
				{
					m_center.z = m_LineCenter.z - h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}

			}
			else if (begin.x == end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)
				{
					m_center.x = m_LineCenter.x - h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
				else
				{
					m_center.x = m_LineCenter.x + h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
			}
		}

	}

	else//������յ����ߣ���ʱ��
	{
		if (TuduAngle<1)
		{
			if ((begin.x>end.x) && (begin.z<end.z))//Բ�����Բ���ڵ�һ����
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x>end.x&&begin.z>end.z)//Բ�����Բ���ڵڶ�����
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x<end.x&&begin.z>end.z)//Բ�����Բ���ڵ�������
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x<end.x&&begin.z<end.z)//Բ�����Բ���ڵ�������
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.z == end.z)//��ʼ�����ֹ�����������ȵ�ʱ��
			{
				if (begin.x <= end.x)
				{
					m_center.z = m_LineCenter.z + h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}
				else
				{
					m_center.z = m_LineCenter.z - h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}
			}
			else if (begin.x == end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)//��ʼ���ڵ�4���ޣ���ֹ���ڵ�1����
				{
					m_center.x = m_LineCenter.x - h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
				else//��ʼ���ڵ�2���ޣ���ֹ���ڵ�3����
				{
					m_center.x = m_LineCenter.x + h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
			}
		}
		else if (TuduAngle == 1)
		{
			m_center.x = m_LineCenter.x;
			m_center.z = m_LineCenter.z;
			m_center.y = 0;
		}
		else
		{
			if ((begin.x<end.x) && (begin.z>end.z))//Բ�����2���յ�4
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x<end.x&&begin.z<end.z)//Բ�����3���յ�1
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x>end.x&&begin.z<end.z)//Բ�����4���յ�2
			{
				m_center.x = m_LineCenter.x + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.x>end.x&&begin.z>end.z)//Բ�����1���յ����
			{
				m_center.x = m_LineCenter.x - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.x - m_end.x) / m_DisBeEnd;
				m_center.y = 0;
			}
			else if (begin.z == end.z)//��ʼ�����ֹ�����������ȵ�ʱ��
			{
				if (begin.x <= end.x)
				{
					m_center.z = m_LineCenter.z - h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}
				else
				{
					m_center.z = m_LineCenter.z + h;
					m_center.x = m_LineCenter.x;
					m_center.y = 0;
				}
			}
			else if (begin.x == end.x)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)
				{
					m_center.x = m_LineCenter.x + h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
				else
				{
					m_center.x = m_LineCenter.x - h;
					m_center.z = m_LineCenter.z;
					m_center.y = 0;
				}
			}
		}

	}


	m_center.y = begin.y;//2016.1.5����ӵĶ��ڶ��߶�Բ��Բ�ĵ�Ĳ���

	CVector3D CCXZ(1, 0, 0);
	CVector3D CS(begin.x - m_center.x, begin.z - m_center.z);
	CVector3D CE(end.x - m_center.x, end.z - m_center.z);

	m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
	m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;

	if ((begin.x>m_center.x) && (begin.z>m_center.z))//Բ��������Բ���ڵ�һ����
	{
		if ((end.x>m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
	}
	else if (begin.x<m_center.x&&begin.z>m_center.z)//Բ��������Բ���ڵڶ�����
	{
		if ((end.x>m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
	}
	else if (begin.x<m_center.x&&begin.z<m_center.z)//Բ��������Բ���ڵ�������
	{
		if ((end.x>m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
	}
	else if (begin.x>m_center.x&&begin.z<m_center.z)//Բ��������Բ���ڵ�������
	{
		if ((end.x>m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else if ((end.x<m_center.x) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCXZ) / (CS.GetLength()*CCXZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCXZ) / (CE.GetLength()*CCXZ.GetLength())) * 360 / PI;
		}
	}




}



void CArc::PolyDrawNArcXZ(CPoint3D& center, float start_angle, float end_angle, float delta_angle, float radius)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	float vx, vz;
	start_angle = 2 * PI*start_angle / 360;
	end_angle = 2 * PI*end_angle / 360;
	if (start_angle<end_angle)
	{
		for (float a = start_angle; a <= end_angle; a += delta_angle)
		{
			vx = center.x + radius*cos(a);
			vz = center.z + radius*sin(a);
			glVertex3f(vx, center.y,vz);
		}
	}
	else
	{
		for (float a = start_angle - 2 * PI; a <= end_angle; a += delta_angle)
		{
			vx = center.x + radius*cos(a);
			vz = center.z + radius*sin(a);
			glVertex3f(vx,center.y, vz);
		}
	}

	glEnd();
}


void CArc::PolyDrawSArcXZ(CPoint3D& center, float start_angle, float end_angle, float delta_angle, float radius)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	float vx, vz;
	start_angle = 2 * PI*start_angle / 360;
	end_angle = 2 * PI*end_angle / 360;
	if (end_angle<start_angle)
	{

		for (float a = start_angle; a >= end_angle; a -= delta_angle)
		{
			vx = center.x + radius*cos(a);

			vz = center.z + radius*sin(a);
			glVertex3f(vx,center.y, vz);
		}
	}
	else
	{
		for (float a = start_angle; a >= end_angle - 2 * PI; a -= delta_angle)
		{
			vx = center.x + radius*cos(a);

			vz = center.z + radius*sin(a);
			glVertex3f(vx, center.y,vz);
		}
	}
	glEnd();
}


//YOZƽ��
BOOL CArc::CalculateYZ(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray, int index)
{
	float m_beginAng = PI*beginAngle / 180;
	float m_endAng = PI*endAngle / 180;
	((CArc*)XFarray.GetAt(index))->m_begin.y = center.y + radio*cos(m_beginAng);
	((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_beginAng);
	((CArc*)XFarray.GetAt(index))->m_begin.x = center.x;
	((CArc*)XFarray.GetAt(index))->m_end.y = center.y + radio*cos(m_endAng);
	((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_endAng);
	((CArc*)XFarray.GetAt(index))->m_end.x = center.x;

	if (index != 0)
	{

		if (
			(fabs(((CArc*)XFarray.GetAt(index))->m_begin.z - ((CArc*)XFarray.GetAt(index - 1))->m_end.z)<0.01&& fabs(((CArc*)XFarray.GetAt(index))->m_begin.y - ((CArc*)XFarray.GetAt(index - 1))->m_end.y)<0.01)
			|| (fabs(((CArc*)XFarray.GetAt(index))->m_begin.z - ((CLine*)XFarray.GetAt(index - 1))->m_end.z)<0.01&&fabs(((CArc*)XFarray.GetAt(index))->m_begin.y - ((CLine*)XFarray.GetAt(index - 1))->m_end.y)<0.01)
			)
		{
			((CArc*)XFarray.GetAt(index))->m_begin.y = center.y + radio*cos(m_beginAng);
			((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_beginAng);
			((CArc*)XFarray.GetAt(index))->m_end.y = center.y + radio*cos(m_endAng);
			((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_endAng);
			return TRUE;//��ʱ��Ϊtrue��˳ʱ���Ϊfalse
		}
		else
		{
			((CArc*)XFarray.GetAt(index))->m_begin.y = center.y + radio*cos(m_endAng);
			((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_endAng);
			((CArc*)XFarray.GetAt(index))->m_end.y = center.y + radio*cos(m_beginAng);
			((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_beginAng);
			return FALSE;
		}

	}
	else//����ж�Բ��Ϊ��ʼԪ�ص�˳��
	{
		if (XFarray.GetSize() == 1)
		{
			return TRUE;//ֻ��һ��Ԫ�صĻ�Ĭ��Ϊ��ʱ��
		}
		else
		{
			if (
				(fabs(((CArc*)XFarray.GetAt(0))->m_end.y - ((CArc*)XFarray.GetAt(1))->m_begin.y)<0.01&& fabs(((CArc*)XFarray.GetAt(0))->m_end.z - ((CArc*)XFarray.GetAt(1))->m_begin.z)<0.01)
				|| (fabs(((CArc*)XFarray.GetAt(0))->m_end.y - ((CLine*)XFarray.GetAt(1))->m_begin.y)<0.01&& fabs(((CArc*)XFarray.GetAt(0))->m_end.z - ((CLine*)XFarray.GetAt(1))->m_begin.z)<0.01)
				)
			{
				((CArc*)XFarray.GetAt(index))->m_begin.y = center.y + radio*cos(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_end.y = center.y + radio*cos(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_endAng);
				return TRUE;//��ʱ��Ϊtrue��˳ʱ���Ϊfalse
			}
			else
			{
				((CArc*)XFarray.GetAt(index))->m_begin.y = center.y + radio*cos(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_begin.z = center.z + radio*sin(m_endAng);
				((CArc*)XFarray.GetAt(index))->m_end.y = center.y + radio*cos(m_beginAng);
				((CArc*)XFarray.GetAt(index))->m_end.z = center.z + radio*sin(m_beginAng);
				return FALSE;
			}
		}

	}
}

void CArc::GLDrawArcYZ(CPoint3D& center, float start_angle, float end_angle, float delta_angle, float radius, CPtrArray& XFarray, int index)
{
	BOOL Direction = Calculate(center, radius, start_angle, end_angle, XFarray, index);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	float vy, vz;

	if (Direction)//��ʱ��
	{
		start_angle = 2 * PI*start_angle / 360;
		end_angle = 2 * PI*end_angle / 360;
		if (start_angle<end_angle)
		{
			for (float a = start_angle; a <= end_angle; a += delta_angle)
			{
				vy = center.y + radius*cos(a);
				vz = center.z + radius*sin(a);
				glVertex3f( center.x,vy, vz);
			}
		}
		else
		{
			for (float a = start_angle - 2 * PI; a <= end_angle; a += delta_angle)
			{
				vy = center.y + radius*cos(a);
				vz = center.z + radius*sin(a);
				glVertex3f(center.x,vy,  vz);
			}
		}



	}
	else //˳ʱ��
	{

		start_angle = 2 * PI*start_angle / 360;
		end_angle = 2 * PI*end_angle / 360;
		if (end_angle<start_angle)
		{
			for (float a = end_angle; a >= start_angle - 2 * PI; a -= delta_angle)
			{
				vy = center.y + radius*cos(a);

				vz = center.z + radius*sin(a);
				glVertex3f(center.x,vy, vz);
			}
		}
		else
		{
			for (float a = start_angle; a <= end_angle; a += delta_angle)
			{
				vy = center.y + radius*cos(a);

				vz = center.z + radius*sin(a);
				glVertex3f(center.x,vy, vz);
			}
		}

	}

	glEnd();
}


void CArc::PolyCalculateYZ(CPoint3D begin, CPoint3D end, float TuduAngle)
{

	float m_DisBeEnd = sqrt(pow((begin.x - end.x), 2) + pow((begin.z - end.z), 2) + pow((begin.y - end.y), 2));//�����ҳ�

	CPoint3D m_LineCenter;
	m_LineCenter.x = (begin.x + end.x) / 2;//���е�����
	m_LineCenter.y = (begin.y + end.y) / 2;//���е�����
	m_LineCenter.z = (begin.z + end.z) / 2;//���е�����

	float m_CenterAng = 4 * atan(fabs(TuduAngle));//�������

	m_radio = 0.5*m_DisBeEnd / sin(0.5*m_CenterAng);//����뾶


	float h = sqrt(pow(m_radio, 2) - pow(m_DisBeEnd*0.5, 2));//���㽻�������ĵľ���

	if (TuduAngle <= 0.0)//����������յ���ұߣ�˳ʱ��͹��ֵΪ��*******XZ����ƽ��
	{
		if (TuduAngle>-1)
		{

			if ((begin.y<end.y) && (begin.z>end.z))//Բ�����Բ���ڵ�һ����
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y<end.y&&begin.z<end.z)//Բ�����Բ���ڵڶ�����
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y>end.y&&begin.z<end.z)//Բ�����Բ���ڵ�������
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y>end.y&&begin.z>end.z)//Բ�����Բ���ڵ�������
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.z == end.z)//������������ȵ�ʱ��
			{
				if (begin.y <= end.y)//��ʼ���ڵڶ����ޣ���ֹ���ڵ�һ����
				{
					m_center.z = m_LineCenter.z - h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}
				else//��ʼ���ڵ������ޣ���ֹ���ڵ�������
				{
					m_center.z = m_LineCenter.z + h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}

			}
			else if (begin.y == end.y)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)//��ʼ���ڵ�һ���ޣ���ֹ���ڵ�������
				{
					m_center.y = m_LineCenter.y + h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
				else//��ʼ���ڵ������ޣ���ֹ���ڵڶ�����
				{
					m_center.y = m_LineCenter.y - h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
			}


		}
		else if (TuduAngle == -1)
		{
			m_center.y = m_LineCenter.y;
			m_center.z = m_LineCenter.z;
			m_center.x = 0;
		}
		else
		{
			if ((begin.y<end.y) && (begin.z>end.z))//Բ�����2���յ�4
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y<end.y&&begin.z<end.z)//Բ�����3���յ�1
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y>end.y&&begin.z<end.z)//Բ�����4���յ�2
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y>end.y&&begin.z>end.z)//Բ�����1���յ����
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}

			else if (begin.z == end.z)//������������ȵ�ʱ��
			{
				if (begin.y <= end.y)
				{
					m_center.z = m_LineCenter.z + h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}
				else
				{
					m_center.z = m_LineCenter.z - h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}

			}
			else if (begin.y == end.y)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)
				{
					m_center.y = m_LineCenter.y - h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
				else
				{
					m_center.y = m_LineCenter.y + h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
			}
		}

	}

	else//������յ����ߣ���ʱ��
	{
		if (TuduAngle<1)
		{
			if ((begin.y>end.y) && (begin.z<end.z))//Բ�����Բ���ڵ�һ����
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y>end.y&&begin.z>end.z)//Բ�����Բ���ڵڶ�����
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y<end.y&&begin.z>end.z)//Բ�����Բ���ڵ�������
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y<end.y&&begin.z<end.z)//Բ�����Բ���ڵ�������
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.z == end.z)//��ʼ�����ֹ�����������ȵ�ʱ��
			{
				if (begin.y <= end.y)
				{
					m_center.z = m_LineCenter.z + h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}
				else
				{
					m_center.z = m_LineCenter.z - h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}
			}
			else if (begin.y == end.y)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)//��ʼ���ڵ�4���ޣ���ֹ���ڵ�1����
				{
					m_center.y = m_LineCenter.y - h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
				else//��ʼ���ڵ�2���ޣ���ֹ���ڵ�3����
				{
					m_center.y = m_LineCenter.y + h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
			}
		}
		else if (TuduAngle == 1)
		{
			m_center.y = m_LineCenter.y;
			m_center.z = m_LineCenter.z;
			m_center.x = 0;
		}
		else
		{
			if ((begin.y<end.y) && (begin.z>end.z))//Բ�����2���յ�4
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y<end.y&&begin.z<end.z)//Բ�����3���յ�1
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z - h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y>end.y&&begin.z<end.z)//Բ�����4���յ�2
			{
				m_center.y = m_LineCenter.y + h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.y>end.y&&begin.z>end.z)//Բ�����1���յ����
			{
				m_center.y = m_LineCenter.y - h*abs(m_begin.z - m_end.z) / m_DisBeEnd;
				m_center.z = m_LineCenter.z + h*abs(m_begin.y - m_end.y) / m_DisBeEnd;
				m_center.x = 0;
			}
			else if (begin.z == end.z)//��ʼ�����ֹ�����������ȵ�ʱ��
			{
				if (begin.y <= end.y)
				{
					m_center.z = m_LineCenter.z - h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}
				else
				{
					m_center.z = m_LineCenter.z + h;
					m_center.y = m_LineCenter.y;
					m_center.x = 0;
				}
			}
			else if (begin.y == end.y)//��ʼ�����ֹ��ĺ�������ȵ�ʱ��
			{
				if (begin.z <= end.z)
				{
					m_center.y = m_LineCenter.y + h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
				else
				{
					m_center.y = m_LineCenter.y - h;
					m_center.z = m_LineCenter.z;
					m_center.x = 0;
				}
			}
		}

	}

	m_center.x = end.x;
	CVector3D CCYZ(0, 1, 0);
	CVector3D CS(0,begin.y - m_center.y, begin.z - m_center.z);
	CVector3D CE(0,end.y - m_center.y, end.z - m_center.z);

	m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
	m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;

	if ((begin.y>m_center.y) && (begin.z>m_center.z))//Բ��������Բ���ڵ�һ����
	{
		if ((end.y>m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
	}
	else if (begin.y<m_center.y&&begin.z>m_center.z)//Բ��������Բ���ڵڶ�����
	{
		if ((end.y>m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
	}
	else if (begin.y<m_center.y&&begin.z<m_center.z)//Բ��������Բ���ڵ�������
	{
		if ((end.y>m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
	}
	else if (begin.y>m_center.y&&begin.z<m_center.z)//Բ��������Բ���ڵ�������
	{
		if ((end.y>m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�һ����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z>m_center.z))//Բ���յ����Բ���ڵ�2����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else if ((end.y<m_center.y) && (end.z<m_center.z))//Բ���յ����Բ���ڵ�3����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
		else//Բ���յ����Բ���ڵ�4����
		{
			m_begin_angle = 360 - 0.5*acos((CS | CCYZ) / (CS.GetLength()*CCYZ.GetLength())) * 360 / PI;
			m_end_angle = 360 - 0.5*acos((CE | CCYZ) / (CE.GetLength()*CCYZ.GetLength())) * 360 / PI;
		}
	}


}



void CArc::PolyDrawNArcYZ(CPoint3D& center, float start_angle, float end_angle, float delta_angle, float radius)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	float vy, vz;
	start_angle = 2 * PI*start_angle / 360;
	end_angle = 2 * PI*end_angle / 360;
	if (start_angle<end_angle)
	{
		for (float a = start_angle; a <= end_angle; a += delta_angle)
		{
			vy = center.y + radius*cos(a);
			vz = center.z + radius*sin(a);
			glVertex3f(center.x,vy, vz);
		}
	}
	else
	{
		for (float a = start_angle - 2 * PI; a <= end_angle; a += delta_angle)
		{
			vy = center.y + radius*cos(a);
			vz = center.z + radius*sin(a);
			glVertex3f(center.x,vy, vz);
		}
	}

	glEnd();
}


void CArc::PolyDrawSArcYZ(CPoint3D& center, float start_angle, float end_angle, float delta_angle, float radius)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	float vy, vz;
	start_angle = 2 * PI*start_angle / 360;
	end_angle = 2 * PI*end_angle / 360;
	if (end_angle<start_angle)
	{

		for (float a = start_angle; a >= end_angle; a -= delta_angle)
		{
			vy = center.y + radius*cos(a);

			vz = center.z + radius*sin(a);
			glVertex3f(center.x,vy, vz);
		}
	}
	else
	{
		for (float a = start_angle; a >= end_angle - 2 * PI; a -= delta_angle)
		{
			vy = center.y + radius*cos(a);

			vz = center.z + radius*sin(a);
			glVertex3f(center.x,vy, vz);
		}
	}
	glEnd();
}


vector<CPoint3D> CArc::ArcTDMInterpolation(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray,
	                                 int index,  float Inter, float F)
{
	ofstream of("data.txt");

	CPoint3D temp;
	vector<CPoint3D> ArcTDMPos;
	CPoint3D ptBegin;
	CPoint3D ptEnd;

	float m_ptOffsetX;
	float m_ptOffsetY;
	
	float m_Juge;

	//float feed = F*Inter / 60;//��λ��΢�׼���
	float feed = 0.001*F*Inter / 60;//��λ��΢�׼���
	float data;

	BOOL Direction = CArc::Calculate(center, radio, beginAngle, endAngle, XFarray, index);

	if (!Direction)//��ʱ��ΪTRUE��˳ʱ��ΪFALSE
	{
		ptBegin.x = center.x + radio*cos(PI*endAngle / 180);
		ptBegin.y = center.y + radio*sin(PI*endAngle / 180);
		ptEnd.x = center.x + radio*cos(PI*beginAngle / 180);
		ptEnd.y = center.y + radio*sin(PI*beginAngle / 180);
		ptBegin.z = ptEnd.z = 0;

		m_ptOffsetX = ptBegin.x - center.x;
		m_ptOffsetY = ptBegin.y - center.y;
		/*m_ptEndCOffsetX = ptEnd.x - center.x;
		m_ptEndCOffsetY = ptEnd.y - center.y;*/
	}
	else
	{
		ptBegin.x = center.x + radio*cos(PI*beginAngle / 180);
		ptBegin.y = center.y + radio*sin(PI*beginAngle / 180);
		ptEnd.x = center.x + radio*cos(PI*endAngle / 180);
		ptEnd.y = center.y + radio*sin(PI*endAngle / 180);
		ptBegin.z = ptEnd.z = 0;

		m_ptOffsetX = ptBegin.x - center.x;
		m_ptOffsetY = ptBegin.y - center.y;
	}

	ArcTDMPos.push_back(ptBegin);

		if (!Direction)//DirecrtionΪFalseʱ����˳ʱ�룬��������˳ʱ��Ĳ岹Go2
		{    
			 float x0 = m_ptOffsetX;//�岹���X����
			 float y0 = m_ptOffsetY;//�岹���Y����
			 float zx = feed*y0 / radio;//��ʼ������
			 float zy = feed*x0 / radio;//��ʼ������

			do{
				if (m_ptOffsetX >= 0 && m_ptOffsetY >= 0)
					m_Juge = 1;
				else if (m_ptOffsetX <= 0 && m_ptOffsetY >= 0)
					m_Juge = 2;
				else if (m_ptOffsetX <= 0 && m_ptOffsetY <= 0)
					m_Juge = 3;
				else if (m_ptOffsetX >= 0 && m_ptOffsetY <= 0)
					m_Juge = 4;
			
				

				if (m_Juge == 1)//��һ������
				{

					if (fabs(m_ptOffsetX) <= fabs(m_ptOffsetY))//�õ�һ�ַ���A
					{
						float x1;
						float y1;
						
					    zx = 0.5*feed*(y0 - zy) / radio;
						x1 = x0 + zx;
						y1 = sqrt(fabs(radio*radio - x1*x1));
						zy = y0 - y1;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						CString str;
						of << "���X�� " << x0 + center.x << "���Y: " << y0 + center.y << "�յ�X: " << x1 + center.x << "�յ�Y�� " << y1 + center.y << endl;
						str.Format(_T("����֮��ľ����ǣ�%f "), sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
						of << str << endl;

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						/*m_ptOffsetX = x0 - center.x;
						m_ptOffsetY = y0 - center.y;*/
						m_ptOffsetX = x0 ;
						m_ptOffsetY = y0;


					}
					else//�õڶ��ַ���B
					{
						float x1;
						float y1;

						zy = 0.5*feed*(x0+ zx) / radio;
						y1 = y0 -zy;
						x1 = sqrt(fabs(radio*radio - y1*y1));
						zx = x1 - x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						CString str;
						of << "���X�� " << x0 + center.x << "���Y: " << y0 + center.y << "�յ�X: " << x1 + center.x << "�յ�Y�� " << y1 + center.y << endl;
						str.Format(_T("����֮��ľ����ǣ�%f "), sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
						of << str << endl;


						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						/*m_ptOffsetX = x0 - center.x;
						m_ptOffsetY = y0 - center.y;*/

						m_ptOffsetX = x0 ;
						m_ptOffsetY = y0;
					}
				}
				else if(m_Juge==2)
			   {
					if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���B
					{
						float x1;
						float y1;

						zy = -0.5*feed*(x0 + zx) / radio;
						y1 = y0 + zy;
						if (radio*radio > y1*y1)
						x1 = -sqrt(radio*radio - y1*y1);
						else
							x1 = sqrt(fabs(radio*radio - y1*y1));
						zx = x1 - x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0 ;
					}
					else//�õ�һ�ַ���A
					{
						float x1;
						float y1;

						zx = 0.5*feed*(y0 - zy) / radio;
						x1 = x0 + zx;
						y1 = sqrt(radio*radio - x1*x1);
						//zy = y0 - y1;
						zy =  y1-y0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0 ;
						m_ptOffsetY = y0 ;

					}
			    }
				else if (m_Juge == 3)
				{
					if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õ�һ�ַ���A
					{
						float x1;
						float y1;

						zx = 0.5*feed*(y0 - zy) / radio;
						x1 = x0 + zx;
						y1 = -sqrt(radio*radio - x1*x1);
						zy = y0 - y1;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0 ;
						m_ptOffsetY = y0;

					}
					else//�õڶ��ַ���B
					{
						float x1;
						float y1;

						zy = 0.5*feed*(x0 + zx) / radio;
						y1 = y0 - zy;
						x1 = -sqrt(radio*radio - y1*y1);
						zx = x1 - x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0 ;
						m_ptOffsetY = y0 ;
					}

				}
				else if (m_Juge == 4)
				{
					if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���B
					{
						float x1;
						float y1;

						
						zy = -0.5*feed*(x0 + zx) / radio;
						y1 = y0 + zy;
						//�ж��������������С�����
						if (radio*radio > y1*y1)
							x1 = sqrt(radio*radio - y1*y1);
						else
							x1 = -sqrt(fabs(radio*radio - y1*y1));
						//x1 = sqrt(fabs(radio*radio - y1*y1));
						zx = x1 - x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0 ;
					}
					else//�õ�һ�ַ���A
					{
						float x1;
						float y1;

						zx = 0.5*feed*(y0 - zy) / radio;
						x1 = x0 + zx;
						y1 = -sqrt(radio*radio - x1*x1);
						zy = y1-y0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0 ;
						m_ptOffsetY = y0 ;

					}
				}
		     
				data = sqrt(pow(zx, 2) + pow(zy, 2));
			} while (sqrt(pow(temp.x-ptEnd.x,2)+pow(temp.y-ptEnd.y,2))>data);
		}
		else//��ʱ��Ĳ岹G03
		{
			float x0 = m_ptOffsetX;//�岹���X����
			float y0 = m_ptOffsetY;//�岹���Y����
			float zx = feed*y0 / radio;//��ʼ������
			float zy = feed*x0 / radio;//��ʼ������

			do{
				if (m_ptOffsetX >= 0 && m_ptOffsetY >= 0)
					m_Juge = 1;
				else if (m_ptOffsetX <= 0 && m_ptOffsetY >= 0)
					m_Juge = 2;
				else if (m_ptOffsetX <= 0 && m_ptOffsetY <= 0)
					m_Juge = 3;
				else if (m_ptOffsetX >= 0 && m_ptOffsetY <= 0)
					m_Juge = 4;



				if (m_Juge == 1)//��һ������
				{

					if (fabs(m_ptOffsetX) <= fabs(m_ptOffsetY))//�õ�һ�ַ���B
					{
						float x1;
						float y1;

						zy = 0.5*feed*(x0 + zx) / radio;
						y1 = y0 +zy;
						if (radio*radio >y1*y1)
						    x1 = sqrt(radio*radio - y1*y1);
						else
							x1 = -sqrt(fabs(radio*radio - y1*y1));
						zx = x1-x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						CString str;
						of << "���X�� " << x0 + center.x << "���Y: " << y0 + center.y << "�յ�X: " << x1 + center.x << "�յ�Y�� " << y1 + center.y << endl;
						str.Format(_T("����֮��ľ����ǣ�%f "), sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
						of << str << endl;

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						/*m_ptOffsetX = x0 - center.x;
						m_ptOffsetY = y0 - center.y;*/
						m_ptOffsetX = x0;
						m_ptOffsetY = y0;


					}
					else//�õڶ��ַ���A
					{
						float x1;
						float y1;

						zx = 0.5*feed*(y0 - zy) / radio;
						x1 = x0 - zx;
						y1 = sqrt(fabs(radio*radio - x1*x1));
						zy = y1- y0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						CString str;
						of << "���X�� " << x0 + center.x << "���Y: " << y0 + center.y << "�յ�X: " << x1 + center.x << "�յ�Y�� " << y1 + center.y << endl;
						str.Format(_T("����֮��ľ����ǣ�%f "), sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
						of << str << endl;

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						/*m_ptOffsetX = x0 - center.x;
						m_ptOffsetY = y0 - center.y;*/

						m_ptOffsetX = x0;
						m_ptOffsetY = y0;
					}
				}
				else if (m_Juge == 2)
				{
					if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���A
					{
						float x1;
						float y1;

						zx = -0.5*feed*(y0 - zy) / radio;
						x1 = x0 + zx;
						y1 = sqrt(fabs(radio*radio - x1*x1));
						zy = y1 - y0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0;
					}
					else//�õ�һ�ַ���B
					{
						float x1;
						float y1;

						zy = 0.5*feed*(x0 + zx) / radio;
						y1 = y0 + zy;
						x1 = -sqrt(fabs(radio*radio - y1*y1));
						zx = x1 -x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0;

					}
				}
				else if (m_Juge == 3)
				{
					if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õ�һ�ַ���B
					{
						float x1;
						float y1;

						zy = 0.5*feed*(x0 + zx) / radio;
						y1 = y0 +zy;
						if (radio*radio >y1*y1)
						    x1 = -sqrt(fabs(radio*radio - y1*y1));
						else
							x1 = sqrt(fabs(radio*radio - y1*y1));
						zx = x1-x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0;

					}
					else//�õڶ��ַ���A
					{
						float x1;
						float y1;

						zx = 0.5*feed*(y0 - zy) / radio;
						x1 = x0 - zx;
						y1 = -sqrt(fabs(radio*radio - x1*x1));
						zy = y1-y0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0;
					}

				}
				else if (m_Juge == 4)
				{
					if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���A
					{
						float x1;
						float y1;

						zx = 0.5*feed*(y0 - zy) / radio;
						x1 = x0 - zx;
						y1 = -sqrt(fabs(radio*radio - x1*x1));
						zy = y1 - y0;
						

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0;
					}
					else//�õ�һ�ַ���B
					{
						float x1;
						float y1;

						zy = 0.5*feed*(x0 + zx) / radio;
						y1 = y0 +zy;
						x1 = sqrt(fabs(radio*radio - y1*y1));
						zx = x1 - x0;

						temp.x = x1 + center.x;
						temp.y = y1 + center.y;
						ArcTDMPos.push_back(temp);

						//�岹�����任
						y0 = y1;
						x0 = x1;

						//�ж����޵���б仯
						m_ptOffsetX = x0;
						m_ptOffsetY = y0;

					}
				}

				data = sqrt(pow(zx, 2) + pow(zy, 2));

			} while (sqrt(pow(temp.x - ptEnd.x, 2) + pow(temp.y - ptEnd.y, 2))>data);

		}
		
		ArcTDMPos.push_back(ptEnd);

		for (vector<CPoint3D>::iterator it = ArcTDMPos.begin(); it != ArcTDMPos.end(); ++it)
		{
			it->z = center.z;
		}


	   return ArcTDMPos;
}


vector<CPoint3D> CArc::ArcTDMInterpolation(CPoint3D& center, float radio, BOOL Direction, CPoint3D ptBegin, CPoint3D ptEnd, float Inter, float F)
{
	CPoint3D temp;
	vector<CPoint3D> ArcTDMPos;
	float m_ptOffsetX;
	float m_ptOffsetY;

	float m_Juge;

	//float feed = F*Inter / 60;//��λ��΢�׼���
	float feed = 0.001*F*Inter / 60;//��λ�Ǻ��׼���
	float data;

	ArcTDMPos.push_back(ptBegin);

	m_ptOffsetX = ptBegin.x - center.x;
	m_ptOffsetY = ptBegin.y - center.y;


	if (!Direction)//DirecrtionΪFalseʱ����˳ʱ�룬��������˳ʱ��Ĳ岹Go2
	{
		float x0 = m_ptOffsetX;//�岹���X����
		float y0 = m_ptOffsetY;//�岹���Y����
		float zx = feed*y0 / radio;//��ʼ������
		float zy = feed*x0 / radio;//��ʼ������

		do{
			if (m_ptOffsetX >= 0 && m_ptOffsetY >= 0)
				m_Juge = 1;
			else if (m_ptOffsetX <= 0 && m_ptOffsetY >= 0)
				m_Juge = 2;
			else if (m_ptOffsetX <= 0 && m_ptOffsetY <= 0)
				m_Juge = 3;
			else if (m_ptOffsetX >= 0 && m_ptOffsetY <= 0)
				m_Juge = 4;



			if (m_Juge == 1)//��һ������
			{

				if (fabs(m_ptOffsetX) <= fabs(m_ptOffsetY))//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y0 - y1;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);


					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;


				}
				else//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 - zy;
					x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);


					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/

					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}
			}
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = -0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio > y1*y1)
						x1 = -sqrt(radio*radio - y1*y1);
					else
						x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}
				else//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(radio*radio - x1*x1);
					//zy = y0 - y1;
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;

				}
			}
			else if (m_Juge == 3)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = -sqrt(radio*radio - x1*x1);
					zy = y0 - y1;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;

				}
				else//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 - zy;
					x1 = -sqrt(radio*radio - y1*y1);
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}

			}
			else if (m_Juge == 4)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���B
				{
					float x1;
					float y1;


					zy = -0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					//�ж��������������С�����
					if (radio*radio > y1*y1)
						x1 = sqrt(radio*radio - y1*y1);
					else
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					//x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}
				else//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = -sqrt(radio*radio - x1*x1);
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;

				}
			}

			data = sqrt(pow(zx, 2) + pow(zy, 2));
		} while (sqrt(pow(temp.x - ptEnd.x, 2) + pow(temp.y - ptEnd.y, 2))>data);
	}
	else//��ʱ��Ĳ岹G03
	{
		float x0 = m_ptOffsetX;//�岹���X����
		float y0 = m_ptOffsetY;//�岹���Y����
		float zx = feed*y0 / radio;//��ʼ������
		float zy = feed*x0 / radio;//��ʼ������

		do{
			if (m_ptOffsetX >= 0 && m_ptOffsetY >= 0)
				m_Juge = 1;
			else if (m_ptOffsetX <= 0 && m_ptOffsetY >= 0)
				m_Juge = 2;
			else if (m_ptOffsetX <= 0 && m_ptOffsetY <= 0)
				m_Juge = 3;
			else if (m_ptOffsetX >= 0 && m_ptOffsetY <= 0)
				m_Juge = 4;



			if (m_Juge == 1)//��һ������
			{

				if (fabs(m_ptOffsetX) <= fabs(m_ptOffsetY))//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio >y1*y1)
						x1 = sqrt(radio*radio - y1*y1);
					else
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

				
					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;


				}
				else//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/

					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}
			}
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = -0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}
				else//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					x1 = -sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;

				}
			}
			else if (m_Juge == 3)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio >y1*y1)
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					else
						x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;

				}
				else//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}

			}
			else if (m_Juge == 4)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;


					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;
				}
				else//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.y = y1 + center.y;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetY = y0;

				}
			}

			data = sqrt(pow(zx, 2) + pow(zy, 2));

		} while (sqrt(pow(temp.x - ptEnd.x, 2) + pow(temp.y - ptEnd.y, 2))>data);

	}
	

	ArcTDMPos.push_back(ptEnd);

	return ArcTDMPos;
}


vector<CPoint3D> CArc::ArcTDMInterpolationXZ(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray,
	int index, float Inter, float F)
{
	

	CPoint3D temp;
	vector<CPoint3D> ArcTDMPos;
	CPoint3D ptBegin;
	CPoint3D ptEnd;

	float m_ptOffsetX;
	float m_ptOffsetZ;

	float m_Juge;

	//float feed = F*Inter / 60;//��λ��΢�׼���
	float feed =0.001* F*Inter / 60;//��λ�Ǻ��׼���

	float data;

	BOOL Direction = CArc::CalculateXZ(center, radio, beginAngle, endAngle, XFarray, index);

	if (!Direction)//��ʱ��ΪTRUE��˳ʱ��ΪFALSE
	{
		ptBegin.x = center.x + radio*cos(PI*endAngle / 180);
		ptBegin.z = center.z + radio*sin(PI*endAngle / 180);
		ptEnd.x = center.x + radio*cos(PI*beginAngle / 180);
		ptEnd.z = center.z + radio*sin(PI*beginAngle / 180);
		ptBegin.y = ptEnd.y = center.y;

		m_ptOffsetX = ptBegin.x - center.x;
		m_ptOffsetZ = ptBegin.z - center.z;
		/*m_ptEndCOffsetX = ptEnd.x - center.x;
		m_ptEndCOffsetY = ptEnd.y - center.y;*/
	}
	else
	{
		ptBegin.x = center.x + radio*cos(PI*beginAngle / 180);
		ptBegin.z = center.z + radio*sin(PI*beginAngle / 180);
		ptEnd.x = center.x + radio*cos(PI*endAngle / 180);
		ptEnd.z = center.z + radio*sin(PI*endAngle / 180);
		ptBegin.y = ptEnd.y = center.y;

		m_ptOffsetX = ptBegin.x - center.x;
		m_ptOffsetZ = ptBegin.z - center.z;
	}

	ArcTDMPos.push_back(ptBegin);

	if (!Direction)//DirecrtionΪFalseʱ����˳ʱ�룬��������˳ʱ��Ĳ岹Go2
	{
		float x0 = m_ptOffsetX;//�岹���X����
		float y0 = m_ptOffsetZ;//�岹���Y����
		float zx = feed*y0 / radio;//��ʼ������
		float zy = feed*x0 / radio;//��ʼ������

		do{
			if (m_ptOffsetX >= 0 && m_ptOffsetZ>= 0)
				m_Juge = 1;
			else if (m_ptOffsetX <= 0 && m_ptOffsetZ >= 0)
				m_Juge = 2;
			else if (m_ptOffsetX <= 0 && m_ptOffsetZ <= 0)
				m_Juge = 3;
			else if (m_ptOffsetX >= 0 && m_ptOffsetZ <= 0)
				m_Juge = 4;



			if (m_Juge == 1)//��һ������
			{

				if (fabs(m_ptOffsetX) <= fabs(m_ptOffsetZ))//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y0 - y1;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);


					//�岹�����任
					y0 = y1;
					x0 = x1;

					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;


				}
				else//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 - zy;
					x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);


					//�岹�����任
					y0 = y1;
					x0 = x1;

					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}
			}
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetZ))//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = -0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio > y1*y1)
						x1 = -sqrt(radio*radio - y1*y1);
					else
						x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(radio*radio - x1*x1);
					//zy = y0 - y1;
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;

				}
			}
			else if (m_Juge == 3)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetZ))//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = -sqrt(radio*radio - x1*x1);
					zy = y0 - y1;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;

				}
				else//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 - zy;
					x1 = -sqrt(radio*radio - y1*y1);
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}

			}
			else if (m_Juge == 4)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetZ))//�õڶ��ַ���B
				{
					float x1;
					float y1;


					zy = -0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					//�ж��������������С�����
					if (radio*radio > y1*y1)
						x1 = sqrt(radio*radio - y1*y1);
					else
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					//x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = -sqrt(radio*radio - x1*x1);
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;

				}
			}

			data = sqrt(pow(zx, 2) + pow(zy, 2));
		} while (sqrt(pow(temp.x - ptEnd.x, 2) + pow(temp.z - ptEnd.z, 2))>data);
	}
	else//��ʱ��Ĳ岹G03
	{
		float x0 = m_ptOffsetX;//�岹���X����
		float y0 = m_ptOffsetZ;//�岹���Y����
		float zx = feed*y0 / radio;//��ʼ������
		float zy = feed*x0 / radio;//��ʼ������

		do{
			if (m_ptOffsetX >= 0 && m_ptOffsetZ >= 0)
				m_Juge = 1;
			else if (m_ptOffsetX <= 0 && m_ptOffsetZ >= 0)
				m_Juge = 2;
			else if (m_ptOffsetX <= 0 && m_ptOffsetZ <= 0)
				m_Juge = 3;
			else if (m_ptOffsetX >= 0 && m_ptOffsetZ <= 0)
				m_Juge = 4;



			if (m_Juge == 1)//��һ������
			{

				if (fabs(m_ptOffsetX) <= fabs(m_ptOffsetZ))//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio >y1*y1)
						x1 = sqrt(radio*radio - y1*y1);
					else
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;


				}
				else//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/

					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}
			}
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetZ))//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = -0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					x1 = -sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;

				}
			}
			else if (m_Juge == 3)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetZ))//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio >y1*y1)
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					else
						x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;

				}
				else//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}

			}
			else if (m_Juge == 4)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetZ))//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;


					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.x = x1 + center.x;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetX = x0;
					m_ptOffsetZ = y0;

				}
			}

			data = sqrt(pow(zx, 2) + pow(zy, 2));

		} while (sqrt(pow(temp.x - ptEnd.x, 2) + pow(temp.z - ptEnd.z, 2))>data);

	}




	ArcTDMPos.push_back(ptEnd);

	for (vector<CPoint3D>::iterator it = ArcTDMPos.begin(); it != ArcTDMPos.end(); ++it)
	{
		it->y = center.y;
	}

	return ArcTDMPos;
}


vector<CPoint3D> CArc::ArcTDMInterpolationYZ(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray,
	int index, float Inter, float F)
{
	CPoint3D temp;
	vector<CPoint3D> ArcTDMPos;
	CPoint3D ptBegin;
	CPoint3D ptEnd;

	float m_ptOffsetY;
	float m_ptOffsetZ;

	float m_Juge;

	//float feed = F*Inter / 60;//��λ��΢�׼���
	float feed =0.001* F*Inter / 60;//��λ�Ǻ��׼���

	float data;

	BOOL Direction = CArc::CalculateYZ(center, radio, beginAngle, endAngle, XFarray, index);

	if (!Direction)//��ʱ��ΪTRUE��˳ʱ��ΪFALSE
	{
		ptBegin.y = center.y + radio*cos(PI*endAngle / 180);
		ptBegin.z = center.z + radio*sin(PI*endAngle / 180);
		ptEnd.y = center.y + radio*cos(PI*beginAngle / 180);
		ptEnd.z = center.z + radio*sin(PI*beginAngle / 180);
		ptBegin.x = ptEnd.x = center.x;

		m_ptOffsetY = ptBegin.y - center.y;
		m_ptOffsetZ = ptBegin.z - center.z;
		/*m_ptEndCOffsetX = ptEnd.x - center.x;
		m_ptEndCOffsetY = ptEnd.y - center.y;*/
	}
	else
	{
		ptBegin.y = center.y + radio*cos(PI*beginAngle / 180);
		ptBegin.z = center.z + radio*sin(PI*beginAngle / 180);
		ptEnd.y = center.y + radio*cos(PI*endAngle / 180);
		ptEnd.z = center.z + radio*sin(PI*endAngle / 180);
		ptBegin.x = ptEnd.x = center.x;

		m_ptOffsetY = ptBegin.y - center.y;
		m_ptOffsetZ = ptBegin.z - center.z;
	}

	ArcTDMPos.push_back(ptBegin);

	if (!Direction)//DirecrtionΪFalseʱ����˳ʱ�룬��������˳ʱ��Ĳ岹Go2
	{
		float x0 = m_ptOffsetY;//�岹���X����
		float y0 = m_ptOffsetZ;//�岹���Y����
		float zx = feed*y0 / radio;//��ʼ������
		float zy = feed*x0 / radio;//��ʼ������

		do{
			if (m_ptOffsetY >= 0 && m_ptOffsetZ >= 0)
				m_Juge = 1;
			else if (m_ptOffsetY <= 0 && m_ptOffsetZ >= 0)
				m_Juge = 2;
			else if (m_ptOffsetY <= 0 && m_ptOffsetZ <= 0)
				m_Juge = 3;
			else if (m_ptOffsetY >= 0 && m_ptOffsetZ <= 0)
				m_Juge = 4;



			if (m_Juge == 1)//��һ������
			{

				if (fabs(m_ptOffsetY) <= fabs(m_ptOffsetZ))//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y0 - y1;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);


					//�岹�����任
					y0 = y1;
					x0 = x1;

					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;


				}
				else//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 - zy;
					x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);


					//�岹�����任
					y0 = y1;
					x0 = x1;

					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}
			}
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetY) < fabs(m_ptOffsetZ))//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = -0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio > y1*y1)
						x1 = -sqrt(radio*radio - y1*y1);
					else
						x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(radio*radio - x1*x1);
					//zy = y0 - y1;
					zy = y1 - y0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;

				}
			}
			else if (m_Juge == 3)
			{
				if (fabs(m_ptOffsetY) < fabs(m_ptOffsetZ))//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = -sqrt(radio*radio - x1*x1);
					zy = y0 - y1;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;

				}
				else//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 - zy;
					x1 = -sqrt(radio*radio - y1*y1);
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}

			}
			else if (m_Juge == 4)
			{
				if (fabs(m_ptOffsetY) < fabs(m_ptOffsetZ))//�õڶ��ַ���B
				{
					float x1;
					float y1;


					zy = -0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					//�ж��������������С�����
					if (radio*radio > y1*y1)
						x1 = sqrt(radio*radio - y1*y1);
					else
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					//x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = -sqrt(radio*radio - x1*x1);
					zy = y1 - y0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;

				}
			}

			data = sqrt(pow(zx, 2) + pow(zy, 2));
		} while (sqrt(pow(temp.y - ptEnd.y, 2) + pow(temp.z - ptEnd.z, 2))>data);
	}
	else//��ʱ��Ĳ岹G03
	{
		float x0 = m_ptOffsetY;//�岹���X����
		float y0 = m_ptOffsetZ;//�岹���Y����
		float zx = feed*y0 / radio;//��ʼ������
		float zy = feed*x0 / radio;//��ʼ������

		do{
			if (m_ptOffsetY >= 0 && m_ptOffsetZ >= 0)
				m_Juge = 1;
			else if (m_ptOffsetY <= 0 && m_ptOffsetZ >= 0)
				m_Juge = 2;
			else if (m_ptOffsetY <= 0 && m_ptOffsetZ <= 0)
				m_Juge = 3;
			else if (m_ptOffsetY >= 0 && m_ptOffsetZ <= 0)
				m_Juge = 4;



			if (m_Juge == 1)//��һ������
			{

				if (fabs(m_ptOffsetY) <= fabs(m_ptOffsetZ))//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio >y1*y1)
						x1 = sqrt(radio*radio - y1*y1);
					else
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);



					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;


				}
				else//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);



					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					/*m_ptOffsetX = x0 - center.x;
					m_ptOffsetY = y0 - center.y;*/

					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}
			}
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetY) < fabs(m_ptOffsetZ))//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = -0.5*feed*(y0 - zy) / radio;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					x1 = -sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;

				}
			}
			else if (m_Juge == 3)
			{
				if (fabs(m_ptOffsetY) < fabs(m_ptOffsetZ))//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					if (radio*radio >y1*y1)
						x1 = -sqrt(fabs(radio*radio - y1*y1));
					else
						x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;

				}
				else//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}

			}
			else if (m_Juge == 4)
			{
				if (fabs(m_ptOffsetY) < fabs(m_ptOffsetZ))//�õڶ��ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radio;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radio*radio - x1*x1));
					zy = y1 - y0;


					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;
				}
				else//�õ�һ�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radio;
					y1 = y0 + zy;
					x1 = sqrt(fabs(radio*radio - y1*y1));
					zx = x1 - x0;

					temp.y = x1 + center.y;
					temp.z = y1 + center.z;
					ArcTDMPos.push_back(temp);

					//�岹�����任
					y0 = y1;
					x0 = x1;

					//�ж����޵���б仯
					m_ptOffsetY = x0;
					m_ptOffsetZ = y0;

				}
			}

			data = sqrt(pow(zx, 2) + pow(zy, 2));

		} while (sqrt(pow(temp.y - ptEnd.y, 2) + pow(temp.z - ptEnd.z, 2))>data);

	}




	ArcTDMPos.push_back(ptEnd);

	for (vector<CPoint3D>::iterator it = ArcTDMPos.begin(); it != ArcTDMPos.end(); ++it)
	{
		it->x = center.x;
	}

	return ArcTDMPos;

}


CPoint3D CArc::IntersectOfArc(CPoint3D& BeginCenter, float BeginRadio, 
	                                CPoint3D& EndCenter, float EndRadio, int mark,CPtrArray& XFarray, int index)
{
	//((CArc*)XFarray.GetAt(index))->Calculate(BeginCenter, BeginRadio, beginAngle, endAngle, XFarray, index);//����ó�Բ������ʼ�����ֹ��
	
	CPoint3D pt;

	double CenterDistance;
	double k, t;
	double a, b, c;
	double m;

	CenterDistance = sqrt(pow(BeginCenter.x - EndCenter.x, 2) + pow(BeginCenter.y - EndCenter.y, 2));//����Բ�ľ�

	
	 if (CenterDistance<=BeginRadio + EndRadio)//����Բ�н���
	{
		//if (EndCenter.y != BeginCenter.y)//Բ�Ĳ���ͬһ���߶���
		//{

			k = -1 * (EndCenter.x - BeginCenter.x) / (EndCenter.y - BeginCenter.y);
			t = ((BeginRadio + EndRadio)*(BeginRadio - EndRadio) + (EndCenter.x - BeginCenter.x)*(EndCenter.x + BeginCenter.x)
				+ (EndCenter.y - BeginCenter.y)*(EndCenter.y + BeginCenter.y)) / (2 * (EndCenter.y - BeginCenter.y));

			a = 1 + pow(k, 2);
			b = 2 * k*(t - BeginCenter.y) - 2 * BeginCenter.x;
			c = pow(BeginCenter.x, 2) + pow(t - BeginCenter.y, 2) - pow(BeginRadio, 2);

			m = pow(b, 2) - 4 * a*c;

			if (m >= 0)
			{
				CPoint3D s1, s2;
				double dis1, dis2;

				s1.x = (-1 * b - sqrt(m)) / (2 * a);
				s2.x = (-1 * b + sqrt(m)) / (2 * a);
				
				s1.y = s1.x*k + t;
				s2.y = s2.x*k + t;

				if (index != mark)
				{
					dis1 = CLine::Length(s1, ((CArc*)XFarray.GetAt(index))->m_end);
					dis2 = CLine::Length(s2, ((CArc*)XFarray.GetAt(index))->m_end);
				}
				else if (index == mark)//************
				{
					dis1 = CLine::Length(s1, ((CArc*)XFarray.GetAt(0))->m_begin);
					dis2 = CLine::Length(s2, ((CArc*)XFarray.GetAt(0))->m_begin);
				}

				if (dis1 < dis2)
					pt = s1;
				else
					pt = s2;
			}
			else if (m == 0)
			{
				pt.x = (-1 * b - sqrt(m)) / (2 * a);
				pt.y = pt.x*k + t;

			}

		/*}
		else
		{

		}*/
	}
	else//����Բû�н���
	{
		return FALSE;
	}

	return pt;
}

CPoint3D CArc::IntersectOfLine(CPoint3D& center, float radio,  CPoint3D& LineBegin, CPoint3D& LineEnd, int mark, CPtrArray& XFarray, int index)
{
	CPoint3D pt1;
	double a, b, c, m;//Բ����ax2+bx+c=0
	double k, t;//ֱ��y=kx+t
	//BOOL Direction=((CArc*)XFarray.GetAt(index))->Calculate(center, radio, beginAngle, endAngle, XFarray, index);
	int flag = 0;;
	//if (LineBegin.y == LineEnd.y)
	if (fabs(LineBegin.y- LineEnd.y)<0.000001)
	{
		flag = 3;
		pt1.y = LineBegin.y;

	}
	//else if (LineBegin.x == LineEnd.x)
	else if (fabs(LineBegin.x- LineEnd.x)<0.000001)
	{
		flag = 2;
		pt1.x = LineBegin.x;
	}
	else
	{
		flag = 1;
		k = (LineBegin.y - LineEnd.y) / (LineBegin.x - LineEnd.x);
		t = LineBegin.y - k*LineBegin.x;
	}

	if (flag == 1)
	{

		a = pow(k, 2) + 1;
		b = -2 * center.x + 2 * k*t - 2 * k*center.y;
		c = pow(center.x, 2) + pow(t, 2) - 2 * t*center.y + pow(center.y, 2) - pow(radio, 2);

		m = pow(b, 2) - 4 * a*c;

		if (m == 0)
		{
			pt1.x = -1 * b / (2 * a);
			pt1.y = k*pt1.x + t;
		}
		else if (m > 0)
		{
			CPoint3D s1, s2;//�洢���ĵ�
			double dis1, dis2;
			s1.x = (-1 * b + sqrt(m)) / (2 * a);
			s1.y = k*s1.x + t;
			s2.x = (-1 * b - sqrt(m)) / (2 * a);
			s2.y = k*s2.x + t;

			if (index != mark)//���Բ���������һ��Ԫ��
			{

				dis1 = CLine::Length(s1, LineBegin);
				dis2 = CLine::Length(s2, LineBegin);
				if (dis1 < dis2)
					pt1 = s1;
				else
					pt1 = s2;
			}
			else if (index == mark)
			{
				dis1 = CLine::Length(s1, LineEnd);
				dis2 = CLine::Length(s2, LineEnd);
				if (dis1 < dis2)
					pt1 = s1;
				else
					pt1 = s2;
			}


		}
		else
		{
			return FALSE;
		}
	}
	else if (flag == 2)//ֱ����X�ᴹֱ
	{
		CPoint3D s1, s2;//�洢���ĵ�
		double dis1, dis2;
		s1.x = s2.x = LineBegin.x;

		if (sqrt(pow(radio, 2) - pow(pt1.x - center.x, 2)) >= 0)
		{

			s1.y = center.y + sqrt(pow(radio, 2) - pow(pt1.x - center.x, 2));
			s2.y = center.y - sqrt(pow(radio, 2) - pow(pt1.x - center.x, 2));

			if (index != mark)//���Բ���������һ��Ԫ��
			{

				dis1 = CLine::Length(s1, LineBegin);
				dis2 = CLine::Length(s2, LineBegin);
				if (dis1 < dis2)
					pt1 = s1;
				else
					pt1 = s2;
			}
			else if (index == mark)
			{
				dis1 = CLine::Length(s1, LineEnd);
				dis2 = CLine::Length(s2, LineEnd);
				if (dis1 < dis2)
					pt1 = s1;
				else
					pt1 = s2;
			}

		}
		else
		{
			return FALSE;
		}

	}
	else//��Y�ᴹֱ
	{

		CPoint3D s1, s2;//�洢���ĵ�
		double dis1, dis2;
		s1.y = s2.y = LineBegin.y;

		if (sqrt(pow(radio, 2) - pow(pt1.y - center.y, 2)) >= 0)
		{

			s1.x = center.x + sqrt(pow(radio, 2) - pow(pt1.y - center.y, 2));
			s2.x = center.x - sqrt(pow(radio, 2) - pow(pt1.y - center.y, 2));

			if (index != mark)//���Բ���������һ��Ԫ��
			{

				dis1 = CLine::Length(s1, LineBegin);
				dis2 = CLine::Length(s2, LineBegin);
				if (dis1 < dis2)
					pt1 = s1;
				else
					pt1 = s2;
			}
			else if (index == mark)
			{
				dis1 = CLine::Length(s1, LineEnd);
				dis2 = CLine::Length(s2, LineEnd);
				if (dis1 < dis2)
					pt1 = s1;
				else
					pt1 = s2;
			}

		}
		else
		{
			return FALSE;
		}
	}

	return pt1;
}
