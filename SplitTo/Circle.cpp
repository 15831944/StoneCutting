#include "StdAfx.h"
#include "Circle.h"
#include<math.h>
#define PI 3.1415926
CCircle::CCircle(void)
{
	m_center.x=0;
	m_center.y=0;
	m_center.z=0;
	m_radio=0.0;
	flag=3;
}


CCircle::~CCircle(void)
{
}
void CCircle::GLDrawCircle(CPoint3D center,float radius)
{

	glBegin(GL_LINE_STRIP);//OpenGLҪ��ָ�������������������glBegin����֮��  
	//glEnd����֮ǰ������ָ���Ķ��㽫�����ԣ�������glBegin��ָ�����ʹ����Щ��  
	//GL_POLYGON��ʾ������Σ��ɵ����ӳɶ���Σ�  
	glColor3f(0.0f,0.0f,1.0f);
	for(float a=0; a<2*PI; a+=0.01)  
		glVertex3f(center.x+radius*cos(a), center.y+radius*sin(a),center.z);  
	glEnd();
}

void CCircle::GLDrawCircleXZ(CPoint3D center, float radius)
{

	glBegin(GL_LINE_STRIP);//OpenGLҪ��ָ�������������������glBegin����֮��  
	//glEnd����֮ǰ������ָ���Ķ��㽫�����ԣ�������glBegin��ָ�����ʹ����Щ��  
	//GL_POLYGON��ʾ������Σ��ɵ����ӳɶ���Σ�  
	glColor3f(0.0f, 0.0f, 1.0f);
	for (float a = 0; a<2 * PI; a += 0.01)
		glVertex3f(center.x + radius*cos(a),center.y,center.z + radius*sin(a));
	glEnd();
}
void CCircle::GLDrawCircleYZ(CPoint3D center, float radius)
{

	glBegin(GL_LINE_STRIP);//OpenGLҪ��ָ�������������������glBegin����֮��  
	//glEnd����֮ǰ������ָ���Ķ��㽫�����ԣ�������glBegin��ָ�����ʹ����Щ��  
	//GL_POLYGON��ʾ������Σ��ɵ����ӳɶ���Σ�  
	glColor3f(0.0f, 0.0f, 1.0f);
	for (float a = 0; a<2 * PI; a += 0.01)
		glVertex3f(center.x,center.y + radius*cos(a),  center.z + radius*sin(a));
	glEnd();
}

vector<CPoint3D> CCircle::CircleTDMInterpolation(CPoint3D center, float radius, CPoint3D EnterPoint, float Inter, float F)
{
	
	CPoint3D temp;
	vector<CPoint3D> ArcTDMPos;
	CPoint3D ptBegin;
	CPoint3D ptEnd;

	float m_ptOffsetX;
	float m_ptOffsetY;

	float m_Juge;

	//float feed = F*Inter / 60;//��λ��΢�׼���
	float feed =0.001*F*Inter / 60;//��λ�Ǻ��׼���
	float data;

	ptBegin = EnterPoint;
	ptEnd = EnterPoint;

	m_ptOffsetX = ptBegin.x - center.x;
	m_ptOffsetY = ptBegin.y - center.y;


	BOOL Direction = TRUE;//�����ж�˳ʱ�뻹����ʱ�룬����ǿ���趨Ϊ��ʱ��

	ArcTDMPos.push_back(ptBegin);
	
	
	if (!Direction)//DirecrtionΪFalseʱ����˳ʱ�룬��������˳ʱ��Ĳ岹Go2
	{
		float x0 = m_ptOffsetX;//�岹���X����
		float y0 = m_ptOffsetY;//�岹���Y����
		float zx = feed*y0 / radius;//��ʼ������
		float zy = feed*x0 / radius;//��ʼ������

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

					zx = 0.5*feed*(y0 - zy) / radius;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radius*radius - x1*x1));
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

					zy = 0.5*feed*(x0 + zx) / radius;
					y1 = y0 - zy;
					x1 = sqrt(fabs(radius*radius - y1*y1));
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
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õڶ��ַ���B
				{
					float x1;
					float y1;

					zy = -0.5*feed*(x0 + zx) / radius;
					y1 = y0 + zy;
					if (radius*radius > y1*y1)
						x1 = -sqrt(radius*radius - y1*y1);
					else
						x1 = sqrt(fabs(radius*radius - y1*y1));
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

					zx = 0.5*feed*(y0 - zy) / radius;
					x1 = x0 + zx;
					y1 = sqrt(radius*radius - x1*x1);
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

					zx = 0.5*feed*(y0 - zy) / radius;
					x1 = x0 + zx;
					y1 = -sqrt(radius*radius - x1*x1);
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

					zy = 0.5*feed*(x0 + zx) / radius;
					y1 = y0 - zy;
					x1 = -sqrt(radius*radius - y1*y1);
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


					zy = -0.5*feed*(x0 + zx) / radius;
					y1 = y0 + zy;
					//�ж��������������С�����
					if (radius*radius > y1*y1)
						x1 = sqrt(radius*radius - y1*y1);
					else
						x1 = -sqrt(fabs(radius*radius - y1*y1));
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

					zx = 0.5*feed*(y0 - zy) / radius;
					x1 = x0 + zx;
					y1 = -sqrt(radius*radius - x1*x1);
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
			data /= 2;//ԭ���ļ��̫С����������ѭ���ʱ�һ������
		} while (sqrt(pow(temp.x - ptEnd.x, 2) + pow(temp.y - ptEnd.y, 2))>=data);
	}

	else//��ʱ��Ĳ岹G03
	{
		float x0 = m_ptOffsetX;//�岹���X����
		float y0 = m_ptOffsetY;//�岹���Y����
		float zx = feed*y0 / radius;//��ʼ������
		float zy = feed*x0 / radius;//��ʼ������

		float distance;

		do{
			if (m_ptOffsetX >= 0 && m_ptOffsetY >= 0)
				m_Juge = 1;
			else if (m_ptOffsetX <= 0 && m_ptOffsetY >= 0)
				m_Juge = 2;
			else if (m_ptOffsetX <= 0 && m_ptOffsetY <= 0)
				m_Juge = 3;
			else if (m_ptOffsetX >= 0 && m_ptOffsetY <= 0)
				m_Juge = 4;



			if (m_Juge == 1)//��һ������******2016.1.1�ĵĵ�һ���޵�A��B�ķ�����B��A�ķ���******
			{

				if (fabs(m_ptOffsetX) <= fabs(m_ptOffsetY))//�õ�2�ַ���B
				{
					float x1;
					float y1;

					/*zy = 0.5*feed*(x0 + zx) / radius;
					y1 = y0 + zy;
					if (radius*radius >y1*y1)
						x1 = sqrt(radius*radius - y1*y1);
					else
						x1 = -sqrt(fabs(radius*radius - y1*y1));
					zx = x1 - x0;*/

					zx = 0.5*feed*(y0 - zy) / radius;
					x1 = x0 - zx;
					if (radius*radius >x1*x1)
						y1 = sqrt(fabs(radius*radius - x1*x1));
					else
						y1 = -sqrt(fabs(radius*radius - x1*x1));
					
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
				else//�õ�1�ַ���A
				{
					float x1;
					float y1;

					/*zx = 0.5*feed*(y0-zy) / radius;
					x1 = x0 - zx;
					y1 = sqrt(fabs(radius*radius - x1*x1));
					zy = y1 - y0;*/

					zy = 0.5*feed*(x0 + zx) / radius;
					y1 = y0 + zy;
					x1 = sqrt(radius*radius - y1*y1);
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
			else if (m_Juge == 2)
			{
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õ�1�ַ���A
				{
					float x1;
					float y1;

					zx = -0.5*feed*(y0 - zy) / radius;
					x1 = x0 + zx;
					y1 = sqrt(fabs(radius*radius - x1*x1));
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
				else//�õ�2�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radius;
					y1 = y0 + zy;
					x1 = -sqrt(fabs(radius*radius - y1*y1));
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
				if (fabs(m_ptOffsetX) < fabs(m_ptOffsetY))//�õ�2�ַ���B
				{
					float x1;
					float y1;

					zy = 0.5*feed*(x0 + zx) / radius;
					y1 = y0 + zy;
					if (radius*radius >y1*y1)
						x1 = -sqrt(fabs(radius*radius - y1*y1));
					else
						x1 = sqrt(fabs(radius*radius - y1*y1));
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
				else//�õ�1�ַ���A
				{
					float x1;
					float y1;

					zx = 0.5*feed*(y0 - zy) / radius;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radius*radius - x1*x1));
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

					zx = 0.5*feed*(y0 - zy) / radius;
					x1 = x0 - zx;
					y1 = -sqrt(fabs(radius*radius - x1*x1));
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

					zy = 0.5*feed*(x0 + zx) / radius;
					y1 = y0 + zy;
					x1 = sqrt(fabs(radius*radius - y1*y1));
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
			data /= 2;//ԭ���ļ��̫С����������ѭ���ʱ�һ������

			distance = sqrt(pow(temp.x - ptEnd.x, 2) + pow(temp.y - ptEnd.y, 2));
		} while (distance>=data);


	}




	ArcTDMPos.push_back(ptEnd);


	for (vector<CPoint3D>::iterator it = ArcTDMPos.begin(); it != ArcTDMPos.end(); ++it)
	{
		it->z = center.z;
	}


	return ArcTDMPos;
}