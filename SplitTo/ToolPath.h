#pragma once
/*
��ÿ���ӹ����͵�·�����ɶ�д�ڸ�toolpath����
*/
/*
Ӧ�ð���Ӧ�ӹ���·������д����Ӧ�����У���ctoolpath����ʵ������Ӧ�Ķ��󣿣�
*/
#include"OPENGL\CadBase.h"
#include"OPENGL\OpenGLDC.h"
#include<vector>
#include"Arc.h"
#include"Line.h"
#include"Circle.h"

using namespace std;
typedef struct tagOffsetPoint
{
	CPoint3D begin;
	CPoint3D end;
}OffsetPoint;

class CToolPath
{
public:
	CToolPath();
	~CToolPath();

	//��������ּӹ�ģʽ�ĳ�ʼ����
	void DeleteAllKindData();
	
	//���ĺ���ҲӦ�÷���������151207
	// �����ƫ�ò���

public:
	CVector3D slope(CPoint3D PtBegin, CPoint3D PtEnd);
	vector<CPoint3D> LineIntersection;//�洢ƫ�ƺ󽻵������
	vector<OffsetPoint> LineOffsetPoint;//�洢ƫ�ƺ�ֱ�����������
	vector<OffsetPoint> ExtendLine;//�洢��һ��ƫ���쳤��ĵ�λ��
	vector<vector<OffsetPoint>> Line;//�洢��������������
	void Polygeon(CPtrArray& Array, float distance, int number, float depth);
	CPoint3D TwoLineNot(OffsetPoint One, OffsetPoint Another);

	//������и�ӹ�****20160607*****
	void RenderPolygeonInit();//��ʾ����μӹ���״ʾ��ͼ�ĳ�ʼ������
	void RenderPolygeon(COpenGLDC* pDC);//��ʾ����μӹ���״ʾ��ͼ

	vector<OffsetPoint> m_PolygeonLines;//�洢���ߵ�ֱ��
	vector<vector<OffsetPoint>> m_OffsetPolygeonLines;//�洢ƫ�ú��ֱ�ߵ�λ�ã����ﲻ���Ǿ�Ƭ�ĺ�����⣬��������������ʱ����Ҫ����

	void RenderPolygeonCuttingPathInit();//����μӹ��켣��ʼ��
	void RenderPolygeonCuttingPath(COpenGLDC* pDC);//��ʾ�ӹ��켣
	vector<vector<OffsetPoint>> m_PolygeonCuttingLines;//�洢�����ӳ����Լ���Ƭ��Ⱥ�ľ�Ƭ���е�Ĺ켣��
	vector<vector<OffsetPoint>> m_PolygeonSequentialLines;//�洢�켣�߰��ձߴ洢�Ĺ켣��

	vector<vector<vector<CPoint3D>>> m_tempPolygeonSimulationPts;//�洢������ɢ��ķ����
    public://һЩ����
		float m_EveryAngelOfSide;
		float m_PolygeonPiles;
		
   public:
	   void SetPolygeonNumber(int NUMBER)
	   {
		   this->m_NumberOfPolygeon = NUMBER;
	   }
	   int GetPolygeonNumber()
	   {
		   return this->m_NumberOfPolygeon;
	   }
	   void SetPolygeonCenter(float CenterX, float CenterY, float CenterZ)
	   {
		   this->m_PolygeonCenter.x = CenterX;
		   this->m_PolygeonCenter.y = CenterY;
		   this->m_PolygeonCenter.z = CenterZ;
	   }
	   CPoint3D GetPolygeonCenter()
	   {
		   return this->m_PolygeonCenter;
	   }
	   void SetRadiusOfPolygeon(float Radius)
	   {
		   this->m_RadiusOfPolygeon = Radius;
	   }
	   float GetRadiusOfPolygeon()
	   {
		   return this->m_RadiusOfPolygeon;
	   }
	   void SetPolygeonBottomHigh(float BottomHigh)
	   {
		   this->m_PolygeonBottomHigh = BottomHigh;
	   }
	   float GetPolygeonBottomHigh()
	   {
		   return this->m_PolygeonBottomHigh;
	   }
	   void SetPolygeonBottomAngel(float angel)
	   {
		   this->m_PolygeonBottomAngel = angel;
	   }
	   float GetPolygeonBottomAngel()
	   {
		   return this->m_PolygeonBottomAngel;
	   }


	   void SetPolygeonFeedLoad(float PolygeonFeedLoad)
	   {
		   this->m_PolygeonFeedLoad = PolygeonFeedLoad;
	   }
	   float GetPolygeonFeedLoad()
	   {
		   return this->m_PolygeonFeedLoad;
	   }
	   void SetPolygeonFeedSpeed(float PolygeonFeedSpeed)
	   {
		   this->m_PolygeonFeedSpeed = PolygeonFeedSpeed;
	   }
	   float GetPolygeonFeedSpeed()
	   {
		   return this->m_PolygeonFeedSpeed;
	   }
	   void SetPolygeonFeedTime(float PolygeonFeedTime)
	   {
		   this->m_PolygeonFeedTime = PolygeonFeedTime;
	   }
	   float GetPolygeonFeedTime()
	   {
		   return this->m_PolygeonFeedTime;
	   }

	   void SetPolygeonCutDirection(int CutDirection)
	   {
		   this->m_PolygeonCuttingDirection = CutDirection;
	   }
	   int GetPolygeonCutDirection()
	   {
		   return this->m_PolygeonCuttingDirection;
	   }
	   void SetPolygeonExtention(float Extention)
	   {
		   this->m_PolygeonExtendDistance = Extention;
	   }
	   float GetPolygeonExtention()
	   {
		   return this->m_PolygeonExtendDistance;
	   }

	   void SetPolygeonSawWidth(float SawWidth)
	   {
		   this->m_PolygeonSawWidth = SawWidth;
	   }
	   float GetPolygeonSawWidth()
	   {
		   return this->m_PolygeonSawWidth;
	   }

	   void SetPolygeonWorkBlankLength(float PolygeonWorkLong)
	   {
		   this->m_PolygeonWorkBlankLength = PolygeonWorkLong;
	   }
	   float GetPolygeonWorkBlankLength()
	   {
		   return this->m_PolygeonWorkBlankLength;
	   }
	   void SetPolygeonWorkBlankWidth(float PolygeonWorkWidth)
	   {
		   this->m_PolygeonWorkBlankWidth = PolygeonWorkWidth;
	   }
	   float GetPolygeonWorkBlankWidth()
	   {
		   return this->m_PolygeonWorkBlankWidth;
	   }
	   void SetPolygeonWorkBlankHigh(float PolygeonWorkHigh)
	   {
		   this->m_PolygeonWorkBlankHigh = PolygeonWorkHigh;
	   }
	   float GetPolygeonWorkBlankHigh()
	   {
		   return this->m_PolygeonWorkBlankHigh;
	   }

	   void SetPolygeonPolyLine(vector<OffsetPoint> PolyLine)
	   {
		   vector<OffsetPoint>().swap(m_PolygeonLines);
		   for (vector<OffsetPoint>::iterator it = PolyLine.begin(); it != PolyLine.end(); ++it)
		   {
			   OffsetPoint m_tempPolygeonLines;
			   m_tempPolygeonLines.begin = it->begin;
			   m_tempPolygeonLines.end = it->end;
			   m_PolygeonLines.push_back(m_tempPolygeonLines);
		   }
	   }
	   vector<OffsetPoint> GetPolygeonPolyLine()
	   {
		   return this->m_PolygeonLines;
	   }

	private:
		int m_NumberOfPolygeon;//��¼����εı���
		CPoint3D m_PolygeonCenter;//��¼��������ĵ������
		float m_RadiusOfPolygeon;//��¼����ε����Բ�뾶
		float m_PolygeonBottomHigh;//��¼����ĸ߶�
		float m_PolygeonBottomAngel;//��¼��������ļн�

		float m_PolygeonFeedLoad;
		float m_PolygeonFeedSpeed;
		float m_PolygeonFeedTime;

		int m_PolygeonCuttingDirection;//��¼�����ķ���
		float m_PolygeonExtendDistance;//��¼�������

		float m_PolygeonSawWidth;//��¼��Ƭ�Ŀ��

		float m_PolygeonWorkBlankLength;//��¼����μӹ�ë���ĳ���
		float m_PolygeonWorkBlankWidth;//��¼����μӹ�ë���Ŀ��
		float m_PolygeonWorkBlankHigh;//��¼����μӹ��ĸ߶�


	//�����и�orthgonal
public:
	int Calculate(float Long, float Gap, float PartLength);//ͨ������Ĳ����ж����ɶ��ٶ��ٸ������
	/*vector<vector<OffsetPoint>> HorizonPos;
	vector<vector<OffsetPoint>> VerticalPos;
	vector<vector<OffsetPoint>> HorizonPosRT;
	vector<vector<OffsetPoint>> VerticalPosRT;*/
	//����
	vector<vector<OffsetPoint>> Horizon(float ToolWidth, float Angle, float Depth, float Height, float Width
		, float Long, float Gap, float PartLength);//��Ƭ����X���������˶�����YOZƽ���ڼ����������
	vector<vector<OffsetPoint>> Vertical(float ToolWidth, float Angle, float Depth, float Height, float Width
		, float Long, float Gap, float PartLength);//��Ƭ����Y���������˶�����XOZƽ���ڼ����������
	//������
	vector<vector<OffsetPoint>> HorizonRT(float ToolWidth, float Angle, float Depth, float Height, float Width
		, float Long, float Gap, float PartLength);
	vector<vector<OffsetPoint>> VerticalRT(float ToolWidth, float Angle, float Depth, float Height, float Width
		, float Long, float Gap, float PartLength);
public:
	BOOL RenderOrthgonalInit();
	void RenderOrthgonal(COpenGLDC* pDC);//��ʾ�����ӹ�����ʾ��ͼ
	CPoint3D GetOrthgonalWorkBlankCenter(float Length, float Width, float High);

	void RenderOrthgonalCuttingPathInit();
	void RenderOrthgonalCuttingPath(COpenGLDC* pDC);//��ʾ�ӹ��켣ʾ��ͼ

	vector<vector<OffsetPoint>> NormalTrapezoid;//�洢�����ε�����ֱ��
	vector<vector<OffsetPoint>> ReverseTrapezoid;//�洢�����ε�����ֱ��


	vector<vector<OffsetPoint>> NormalTrapezoidCut;//�洢�����μӹ�����ֱ��(˳��ת��֮��)
	vector<vector<OffsetPoint>> ReverseTrapezoidCut;//�洢�����μӹ�����ֱ��

	//�洢���ֵľ��ӹ���ɢ��
	vector<vector<vector<CPoint3D>>> m_TempNormalFinish;
	vector<vector<vector<CPoint3D>>> m_TempReverseFinish;

	//ë���ߴ�����úͻ�ȡ
	void SetOrthgonalWorkBlankLength(float Length)
	{
		this->m_OrthgonalWorkBlankLength = Length;
	}
	float GetOrthgonalWorkBlankLength()
	{
		return this->m_OrthgonalWorkBlankLength;
	}
	void SetOrthgonalWorkBlankWidth(float Width)
	{
		this->m_OrthgonalWorkBlankWidth = Width;
	}
	float GetOrthgonalWorkBlankWidth()
	{
		return this->m_OrthgonalWorkBlankWidth;
	}
	void SetOrthgonalWorkBlankHigh(float high)
	{
		this->m_OrthgonalWorkBlankHigh = high;
	}
	float GetOrthgonalWorkBlankHigh()
	{
		return this->m_OrthgonalWorkBlankHigh;
	}
	void SetOrthgonalTrapezoidAngle(float TrapezoidAngle)
	{
		this->m_TrapezoidAngle = TrapezoidAngle;
	}
	float GetOrthgonalTrapezoidAngle()
	{
		return this->m_TrapezoidAngle;
	}
	void SetOrthgonalSawWidth(float SawWidth)
	{
		this->m_OrthgonalSawWidth = SawWidth;
	}
	float GetOrthgonalSawWidth()
	{
		return this->m_OrthgonalSawWidth;
	}
	//���ε���״�Ļ�ȡ
	void SetOrthgonalTrapezoidType(int Type)
	{
		this->m_TrapezoidType = Type;
	}
	int GetOrthgonalTrapezoidType()
	{
		return this->m_TrapezoidType;
	}
	void SetOrthgonalProcessStyle(int style)
	{
		this->m_OrthgonalProcessStyle = style;
	}
	int GetOrthgonalProcessStyle()
	{
		return this->m_OrthgonalProcessStyle;
	}

	//���β���������,Y��ƽ��
	void SetOrthgonalYShort(float YShort)
	{
		this->m_OrthgonalYShort = YShort;
	}
	float GetOrthgonalYShort()
	{
		return this->m_OrthgonalYShort;
	}
	void SetOrthgonalYLong(float YLong)
	{
		this->m_OrthgonalYLong = YLong;
	}
	float GetOrthgonalYLong()
	{
		return this->m_OrthgonalYLong;
	}
	void SetOrthgonalYGap(float Gap)
	{
		this->m_OrthgonalYGap = Gap;
	}
	float GetOrthgonalYGap()
	{
		return this->m_OrthgonalYGap;
	}
	void SetOrthgonalYFeedLoad(float Load)
	{
		this->m_OrthgonalYFeedLoad = Load;
	}
	float GetOrthgonalYFeedLoad()
	{
		return this->m_OrthgonalYFeedLoad;
	}

	//���β���������,X��ƽ��
	void SetOrthgonalXShort(float XShort)
	{
		this->m_OrthgonalXShort = XShort;
	}
	float GetOrthgonalXShort()
	{
		return this->m_OrthgonalXShort;
	}
	void SetOrthgonalXLong(float XLong)
	{
		this->m_OrthgonalXLong = XLong;
	}
	float GetOrthgonalXLong()
	{
		return this->m_OrthgonalXLong;
	}
	void SetOrthgonalXGap(float Gap)
	{
		this->m_OrthgonalXGap = Gap;
	}
	float GetOrthgonalXGap()
	{
		return this->m_OrthgonalXGap;
	}
	void SetOrthgonalXFeedLoad(float Load)
	{
		this->m_OrthgonalXFeedLoad = Load;
	}
	float GetOrthgonalXFeedLoad()
	{
		return this->m_OrthgonalXFeedLoad;
	}

private:
	
private:
	float m_OrthgonalWorkBlankLength;
	float m_OrthgonalWorkBlankWidth;
	float m_OrthgonalWorkBlankHigh;
	float  m_TrapezoidAngle;
	float m_OrthgonalSawWidth;

	int m_TrapezoidType;//��������
	int m_OrthgonalProcessStyle;//�ӹ�ģʽ

	float m_OrthgonalYShort;
	float m_OrthgonalYLong;
	float m_OrthgonalYGap;
	float m_OrthgonalYFeedLoad;

	float m_OrthgonalXShort;
	float m_OrthgonalXLong;
	float m_OrthgonalXGap;
	float m_OrthgonalXFeedLoad;

	//�����ӹ� LineProcess
	//�岹�㷨ʵ����ɢ�������Ȼ����Ǻܹ�151207
public:
	vector<CPoint3D> LineDotPos;//�洢ֱ�ߵ���ɢ��
	vector<CPoint3D> ArcDotPos;//�洢Բ������ɢ��
	vector<CPoint3D> CircleDotPos;
	vector<LinePos> Opposite;//�洢��Ӧ������

	vector<CPoint3D> LineDiscrete(CPoint3D m_Begin, CPoint3D m_End, float Inter, float F);//ֱ�߲岹��ɢ������CLine�еĺ���
	vector<CPoint3D> ArcDiscrete(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray, int index, float Inter, float F);//��ͨԲ���岹��ɢ������CArc����ĺ���
	vector<CPoint3D> PolyArcDiscrete(CPoint3D begin, CPoint3D end, float TuduAngle, float Inter, float F);//���߶�Բ���岹��ɢ,���õ��ù�ֱ��д����������ȡCArcl��Ĳ��ִ���
	vector<CPoint3D> CircleDiscrete(CPoint3D center, float radius, CPoint3D EnterPoint, float Inter, float F);
	vector<LinePos> Reverse(vector<CPoint3D> start, double width);//������˰��֮����λ��
private:
	CPoint3D m_center;
	float m_radio;
	float m_begin_angle;
	float m_end_angle;
public:
	void ChangeToXOZ(CPtrArray& Array);//ת����XOZƽ��
	void ChangeToYOZ(CPtrArray& Array);//ת����YOZƽ��
	void LineRenerInit();
	void LineRender(COpenGLDC* pDC);

	//ֱ�������ּӹ���ʾ����ʼ��
	void LineRoughRenderInit();
	void LineRoughRender(COpenGLDC* pDC);

	//ֱ�������ּӹ�������ʾ
	void LineRoughLeftRenderInit();
	void LineRoughLeftRender(COpenGLDC* pDC);

	//ë���߿����ĵ�
	CPoint3D GetLineProcessWorkBlankCenter();
	BOOL BeInXZLineWorkBlank(CPoint3D point,  CPoint3D center,float Width, float High);

	//ֱ���������ӹ��켣�����ɼ���ʼ���������趨�ĳ��ӹ�������������ּӹ���������һ���ģ�
	//ֻ������ʱ�����ʹ�ֱ��岹�Ĳ���Ҫ�þ��ӹ��趨��ֵ
	void LineFinishRenderInit();
	void LineFinishRender(COpenGLDC* pDC);

public://��ŵ�������ʾ
	vector<LinePos> m_LineProcess;//���ֱ����������β��ļ���***L
	vector<vector<CPoint3D>> m_LineArcProcessPts;//�洢Բ�������������е��λ��
	vector<CPtrArray*> m_LineArrayArcList;//��¼Բ������XoZƽ����ɢ��ÿ��������Ӧ��Բ������

	CPtrArray m_LineRoughLeft;//�洢ֱ�������ӹ��ּӹ������Ľ�������Ϣ
	vector<CPoint3D> m_LineRoughLeftPts;//�洢ֱ�������ּӹ�������ɢ��ĵ㼯��
	vector<CPtrArray*> m_LineRoughLeftArc;//�洢�ּӹ�������ɢ��Ϊ���ҵ��Բ���ļ���
	vector<vector<CPoint3D>> m_LineRoughLeftArcDisPts;//�ּӹ�����Բ����ɢ��
	vector<LinePos> m_LineRoughLeftLines;//�洢ֱ�������ּӹ��������ߵļ���

	vector<CPoint3D> m_LineRoughPts;
	vector<LinePos> m_LineRoughVSegment;//�洢ë�����ּӹ������Ĵ�ֱֱ�ߵ���β�㣬��������
	vector<vector<CPoint3D>> m_LineRoughVSegmentDisPts;//�洢�߶���ɢ��ĵ�
	vector<vector<LinePos>> m_LineRoughVSegmentDisLine;//����ɢ��ĵ����Y�����첢���ӳ�ֱ��****L
	vector<vector<CPtrArray*>> m_LineRoughVSegmentDisArc;//����ɢ��ĵ㰴�����õ�ֵ����Բ��������***A
	vector<vector<vector<CPoint3D>>> m_LineRoughVSegmentDisArcDisPts;//Բ����ɢ�����ɵĵ�

	vector<LinePos> m_LineFinishVSegment;//�洢�ּӹ��������ӹ��������Ĵ�ֱ�߶ε���β�㣬��������
	vector<vector<CPoint3D>> m_LineFinishVSegmentDisPts;//�洢��ֱ�߶���ɢ��ĵ�
	vector<vector<LinePos>> m_LineFinishVSegmentDisLine;//�洢��ɢ��ĵ㣬�����õ���Y���������ĵ�������ӳ�ֱ��***L
	vector<CPtrArray*> m_LineFinishVSegmentDisArc;//�洢������ɢ���λ�����ɵ�Բ��������****A
	vector<vector<CPoint3D>> m_LineFinishVSegmentDisArcDisPts;//�洢Բ����ɢ��ĵ�

	vector<CPoint3D> m_LineArcSurfacePts;//�洢Բ��������������水�վ��ӹ�������ɢ��ĵ�

public:
	//�������ݵĻ�ȡ������
	void SetLineArray(CPtrArray& Array)
	{
		this->m_LineArray.Copy(Array);
	}
	CPtrArray& GetLineArray()
	{
		return this->m_LineArray;
	}
	//�ּӹ����ݵĻ�ȡ������
	void SetLineRoughHFeedSpeed(float speed)
	{
		this->m_LineRough_H_FeedSpeed = speed;
	}
	float GetLineRoughHFeedSpeed()
	{
		return this->m_LineRough_H_FeedSpeed;
	}
	void SetLineRoughHFeedTime(float time)
	{
		this->m_LineRough_H_FeedTime = time;
	}
	float GetLineRoughHFeedTime()
	{
		return this->m_LineRough_H_FeedTime;
	}
	void SetLineRoughVFeedSpeed(float speed)
	{
		this->m_LineRough_V_FeedSpeed = speed;
	}
	float GetLineRoughVFeedSpeed()
	{
		return this->m_LineRough_V_FeedSpeed;
	}
	void SetLineRoughVFeedTime(float time)
	{
		this->m_LineRough_V_FeedTime = time;
	}
	float GetLineRoughVFeedTime()
	{
		return this->m_LineRough_V_FeedTime;
	}
	void SetLineRoughVerticalDistance(float distance)
	{
		this->m_LineRough_VerticalDistance = distance;
	}
	float GetLineRoughVerticalDistance()
	{
		return this->m_LineRough_VerticalDistance;
	}
	void SetLineRoughPiles(float piles)
	{
		this->m_LineRough_Piles = piles;
	}
	float GetLineRoughPiles()
	{
		return this->m_LineRough_Piles;
	}
	void SetLineRoughLeft(float left)
	{
		this->m_LineRough_Left = left;
	}
	float GetLineRoughLeft()
	{
		return this->m_LineRough_Left;
	}

	//���ӹ����ݵĻ�ȡ������
	void SetLineFinishHFeedSpeed(float speed)
	{
		this->m_LineFinish_H_FeedSpeed = speed;
	}
	float GetLineFinishHFeedSpeed()
	{
		return this->m_LineFinish_H_FeedSpeed;
	}
	void SetLineFinishHFeedTime(float time)
	{
		this->m_LineFinish_H_FeedTime = time;
	}
	float GetLineFinishHFeedTime()
	{
		return this->m_LineFinish_H_FeedTime;
	}
	void SetLineFinishVFeedSpeed(float speed)
	{
		this->m_LineFinish_V_FeedSpeed = speed;
	}
	float GetLineFinishVFeedSpeed()
	{
		return this->m_LineFinish_V_FeedSpeed;
	}
	void SetLineFinishVFeedTime(float time)
	{
		this->m_LineFinish_V_FeedTime = time;
	}
	float GetLineFinishVFeedTime()
	{
		return this->m_LineFinish_V_FeedTime;
	}
	void SetLineFinishVerticalDistance(float distance)
	{
		this->m_LineFinish_VerticalDistance = distance;
	}
	float GetLineFinishVerticalDistance()
	{
		return this->m_LineFinish_VerticalDistance;
	}
	void SetLineFinishPiles(float piles)
	{
		this->m_LineFinish_Piles = piles;
	}
	float GetLineFinishPiles()
	{
		return this->m_LineFinish_Piles;
	}

	//ʯ����������
	void SetLineStyle(BOOL style)
	{
		this->m_LineStyle = style;
	}
	BOOL GetLineStyle()
	{
		return this->m_LineStyle;
	}
	//����������״
	void SetLineArcShapeArray(CPtrArray& Array)
	{
		this->m_LineOfArc.Copy(Array);
	}
	CPtrArray& GetLineArcShapeArray()
	{
		return this->m_LineOfArc;
	}

	//ë���ߴ��ȡ������
	void SetLineWorkBlankLength(float length)
	{
		this->m_LineWorkBlank_Length = length;
	}
	float GetLineWorkBlankLength()
	{
		return this->m_LineWorkBlank_Length;
	}
	void SetLineWorkBlankWidth(float width)
	{
		this->m_LineWorkBlank_Width = width;
	}
	float GetLineWorkBlankWidth()
	{
		return this->m_LineWorkBlank_Width;
	}
	void SetLineWorkBlankHigh(float high)
	{
		this->m_LineWorkBlank_High = high;
	}
	float GetLineWorkBlankHigh()
	{
		return this->m_LineWorkBlank_High;
	}
private:
	//��������
	CPtrArray m_LineArray;
	//�ּӹ�������ȡ
	float m_LineRough_H_FeedSpeed;
	float m_LineRough_H_FeedTime;
	float m_LineRough_V_FeedSpeed;
	float m_LineRough_V_FeedTime;
	float m_LineRough_VerticalDistance;
	float m_LineRough_Piles;
	float m_LineRough_Left;

	//���ӹ�������ȡ
	float m_LineFinish_H_FeedSpeed;
	float m_LineFinish_H_FeedTime;
	float m_LineFinish_V_FeedSpeed;
	float m_LineFinish_V_FeedTime;
	float m_LineFinish_VerticalDistance;
	float m_LineFinish_Piles;

	//��������
	BOOL m_LineStyle;//FALSE��ʾֱ�ߣ�TRUE��ʾԲ��

	//��������������
	CPtrArray m_LineOfArc;

	//ë���ߴ��ȡ
	float m_LineWorkBlank_Length;
	float m_LineWorkBlank_Width;
	float m_LineWorkBlank_High;


	//��ת��ӹ�Rotate Process.*******���ָ�����µ���λX���������ĵ�λ�����2016.1.5
public:
	vector<CPoint3D> LineDiscreteXZ(CPoint3D m_Begin, CPoint3D m_End, float Inter, float F);
	vector<CPoint3D> ArcDiscreteXZ(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray, int index, float Inter, float F);
	vector<CPoint3D> PolyArcDiscreteXZ(CPoint3D begin, CPoint3D end, float TuduAngle, float Inter, float F);

	BOOL InitRotateRender();
	void RenderRotate(COpenGLDC* pDC);//��ͼ������ʾ��ͼ
	BOOL InitRotateRough();
	void RenderRoughRotate(COpenGLDC* pDC);//���ƴּӹ�·��
	BOOL InitRotateWorkBlank();
	void RenderRotateWorkBlank(COpenGLDC* pDC);//����ë��ʾ��ͼ
	string BeInRotateWorkBlank(CPoint3D pt);
	BOOL InitRotateRoughCut();
	void RenderRoughCutRotate(COpenGLDC* pDC);//���Ʋü���Ĵּӹ�·��
	BOOL InitRotateFinish();
	void RenderFinishRotate(COpenGLDC* pDC);//���ƾ��ӹ�·��
public:
	void SetRotateArray(CPtrArray& Array)
	{
		this->m_Rotate_Array.Copy(Array);
	}
	CPtrArray& GetRotateArray()
	{
		return this->m_Rotate_Array;
	}
	//�ּӹ�ˮƽ
	void SetRotateFeedSpeed(float speed)
	{
		this->m_Rotate_FeedSpeed = speed;
	}
	float GetRotateFeedSpeed()
	{
		return this->m_Rotate_FeedSpeed;
	}
	void SetRotateFeedTime(float Time)
	{
		this->m_Rotate_FeedTime = Time;
	}
	float GetRotateFeedTime()
	{
		return this->m_Rotate_FeedTime;
	}
	//�ּӹ���ֱ
	void SetRotateFeedSpeedVx(float speed)
	{
		this->m_Rotate_FeedSpeed_VX = speed;
	}
	float GetRotateFeedSpeedVx()
	{
		return this->m_Rotate_FeedSpeed_VX;
	}
	void SetRotateFeedTimeVx(float Time)
	{
		this->m_Rotate_FeedTime_VX = Time;
	}
	float GetRotateFeedTimeVx()
	{
		return this->m_Rotate_FeedTime_VX;
	}
	//���ӹ�ˮƽ
	void SetRotateFeedSpeedFinish(float speed)
	{
		this->m_Rotate_FeedSpeed_Finish = speed;
	}
	float GetRotateFeedSpeedFinsh()
	{
		return this->m_Rotate_FeedSpeed_Finish;
	}
	void SetRotateFeedTimeFinish(float Time)
	{
		this->m_Rotate_FeedTime_Finish = Time;
	}
	float GetRotateFeedTimeFinish()
	{
		return this->m_Rotate_FeedTime_Finish;
	}
	
	//���ӹ���ֱ
	void SetRotateFeedSpeedFinishVX(float speed)
	{
		this->m_Rotate_FeedSpeed_VX_Finish = speed;
	}
	float GetRotateFeedSpeedFinshVX()
	{
		return this->m_Rotate_FeedSpeed_VX_Finish;
	}
	void SetRotateFeedTimeFinishVX(float Time)
	{
		this->m_Rotate_FeedTime_VX_Finish = Time;
	}
	float GetRotateFeedTimeFinishVX()
	{
		return this->m_Rotate_FeedTime_VX_Finish;
	}
	//ë���ߴ�Ļ�ȡ������
	void SetRotateBlankLongth(float longth)
	{
		this->m_Rotate_WorkBlank_Longth = longth;
	}
	float GetRotateBlankLongth()
	{
		return this->m_Rotate_WorkBlank_Longth;
	}
	void SetRotateBlankWidth(float width)
	{
		this->m_Rotate_WorkBlank_Width = width;
	}
	float GetRotateBlankWidth()
	{
		return this->m_Rotate_WorkBlank_Width;
	}
	void SetRotateBlankHeighth(float higth)
	{
		this->m_Rotate_WorkBlank_Heighth = higth;
	}
	float GetRotateBlankHeighth()
	{
		return this->m_Rotate_WorkBlank_Heighth;
	}
	//��ȡ�ּӹ�����ּӹ�����
	void SetRotateRoughPlies(float plies)
	{
		this->m_Rotate_RoughPlies = plies;
	}
	float GetRotateRoughPlies()
	{
		return this->m_Rotate_RoughPlies;
	}
	void SetRotateRoughCutOfDepth(float depth)
	{
		this->m_Rotate_RoughCutOfDepth = depth;
	}
	float GetRotateRoughCutOfDepth()
	{
		return this->m_Rotate_RoughCutOfDepth;
	}
	//��ȡ�ּӹ����������ӹ�����
	void SetRotateRoughLeft(float left)
	{
		this->m_Rotate_RoughLeft = left;
	}
	float GetRotateRoughLeft()
	{
		return this->m_Rotate_RoughLeft;
	}
	void SetRotateFinishCutOfDepth(float depth)
	{
		this->m_Rotate_FinishCutOfDepth = depth;
	}
	float GetRotateFinishCutOfDepth()
	{
		return this->m_Rotate_FinishCutOfDepth;
	}
	//��ȡ�ּӹ������е�
	vector<vector<vector<CPoint3D>>> GetRotateRoughCutPoints()
	{
		return this->m_RotateRoughCutPoints;
	}
	vector<vector<vector<CPoint3D>>> GetRotateRoughPoints()
	{
		return this->m_RotateRoughPoints;
	}
	//��ȡ���ӹ������е�
	vector<vector<vector<CPoint3D>>> GetRotateFinishPoints()
	{
		return this->m_RotateFinishPoints;
	}

	CPoint3D m_RotateRoughWorkBlankCenter;//�洢��ת�ӹ�ë�������ĵ�

private:
	CPtrArray m_Rotate_Array;//���ڴ洢�Ի�������ȡ������
	//�ּӹ�ʱ��Ĳ�������
	float m_Rotate_FeedSpeed;
	float m_Rotate_FeedTime;
	float m_Rotate_FeedSpeed_VX;
	float m_Rotate_FeedTime_VX;
	//���ӹ�ʱ��Ĳ�������
	float m_Rotate_FeedSpeed_Finish;
	float m_Rotate_FeedTime_Finish;
	float m_Rotate_FeedSpeed_VX_Finish;
	float m_Rotate_FeedTime_VX_Finish;
	//ë���ߴ������
	float m_Rotate_WorkBlank_Longth;
	float m_Rotate_WorkBlank_Width;
	float m_Rotate_WorkBlank_Heighth;
	//���ôּӹ��ӹ��������ּӹ�����
	float m_Rotate_RoughLeft;
	float m_Rotate_RoughPlies;
	float m_Rotate_RoughCutOfDepth;//�ּӹ�����
	float m_Rotate_FinishCutOfDepth;//���ӹ�����
	//���ÿ���߶�Բ��Բ������
	CPoint3D m_RotateCenter;

	//����ʾ��ͼ�����е�
	vector<vector<CPoint3D>> RotateWorkPiecePoints;

	//�ּӹ��켣�ֲ�Ĵ洢���ּӹ��ʹּӹ��ü���Ĵ洢
	vector<CPtrArray*> m_RotateRoughArrayList;
	vector<vector<vector<CPoint3D>>> m_RotateRoughPoints;
	vector<vector<vector<CPoint3D>>> m_RotateRoughCutPoints;

	//�洢��ת�ӹ����ӹ����е�
	vector<CPtrArray*> m_RotateFinsihArrayList;
	vector<vector<vector<CPoint3D>>> m_RotateFinishPoints;

	
	
	//�����ӹ� Side Process
public:	
	int mark;//���ڴ洢���ͼ���м���Ԫ��
	CPoint3D XMax;//���ڴ洢X���귽����ֵ���ĵ�����꣬һ��Ϊ���
	void ChangeSideProcess();
	vector<CPoint3D> OffsetAlgorithm(CPtrArray& XFarray, int mark, double offset);
	BOOL RenderSideInit();//����������������
	void RenderSide(COpenGLDC* pDC);//���Ƽӹ���״
	CPoint3D GetCenterPoint();
	string BeInBox(CPoint3D pt);//�����ж��Ƿ������趨��ë���ĳߴ緶Χ��
	
	void RoughInit();
	void RenderSideRough(COpenGLDC* pDC);//���ƴּӹ��ĵ���켣
	void DeletePointOutOfBox();//***ͨ���Ծ���������з�����ʹ����������Ĳ��ְ������ž��α߽���ֱ�ߵ�˼·���У����׵��Ƕ������ϡ����ϡ����¡������⼸�����������ߵ��ǹ�ͬ�ĵ���Ǽ��****
	void RenderSideRoughCut(COpenGLDC* pDC);//���ƾ���ѡ����ë��֮�ڵĴּӹ�·��
	
	void InitSideRoughLeft();//��ʼ������
	void RenderSideRoughLeft(COpenGLDC* pDC);//���ƴּӹ�������ʾ��ͼ

	vector<CPoint3D> FinishOffsetAlgorithm(CPtrArray& XFarray, int mark, double offset);
	void InitSideFinish();//��ʼ������
	void RenderSideFinish(COpenGLDC* pDC);//���ƾ��ӹ�·��

public:
	void SetArray(CPtrArray& Array)
	{
		this->m_ptArray.Copy(Array);	
	}
	CPtrArray& GetArray( )
	{
		return this->m_ptArray;
	}
	//���������ӹ��ּӹ�����������
	vector<CPtrArray*> GetArrayRoughList()
	{
		return this->NewArrayList;
	}
	vector<CPtrArray*> GetArrayFinishList()
	{
		return this->FinishArrayList;
	}
	void SetTime(float time)
	{
		this->m_FeedTime = time;
	}
	float GetTime()
	{
		return this->m_FeedTime;
	}
	void SetFeedspeed(float speed)
	{
		this->m_FeedSpeed = speed;
	}
	float GetFeedspeed()
	{
		return this->m_FeedSpeed;
	}
	void SetTimeVx(float time)
	{
		this->m_FeedTime_VX = time;
	}
	float GetTimeVx()
	{
		return this->m_FeedTime_VX;
	}
	void SetSpeedVx(float speed)
	{
		this->m_FeedSpeed_VX = speed;
	}
	float GetSpeedVx()
	{
		return this->m_FeedSpeed_VX;
	}
	void SetSpeedFinish(float speed)
	{
		this->m_FeedSpeed_Finish = speed;
	}
	float GetSpeedFinish()
	{
		return m_FeedSpeed_Finish;
	}
	void SetTimeFinish(float time)
	{
		this->m_FeedTime_Finish=time;
	}
	float GetTimeFinish()
	{
		return this->m_FeedTime_Finish;
	}
	void SetSpeedFinishVX(float speed)
	{
		this->m_FeedSpeed_VX_Finish = speed;
	}
	float GetSpeedFinishVX()
	{
		return this->m_FeedSpeed_VX_Finish;
	}
	void SetTimeFinishVX(float time)
	{
		this->m_FeedTime_VX_Finish = time;
	}
	float GetTimeFinishVX()
	{
		return this->m_FeedTime_VX_Finish;
	}
	
	void SetLongth(float Long)
	{
		this->m_Piece_Long = Long;
	}
	float GetLongth()
	{
		return this->m_Piece_Long;
	}
	void SetWidth(float width)
	{
		this->m_Piece_Width = width;
	}
	float GetWidth()
	{
		return this->m_Piece_Width;
	}
	void SetHeigth(float heigth)
	{
		this->m_Piece_Heigth = heigth;
	}
	float GetHeigth()
	{
		return this->m_Piece_Heigth;
	}
	
	void SetDepthCut(float depth)
	{
		this->m_DepthOfCut = depth;
	}
	float GetDepthCut()
	{
		return this->m_DepthOfCut;
	}
	void SetDepthCutFinish(float depth)
	{
		this->m_DepthOfCut_Finish=depth;
	}
	float GetDepthCutFinish()
	{
		return this->m_DepthOfCut_Finish;
	}
	void SetRoughLeft(float rough)
	{
		this->m_RoughLeft = rough;
	}
	float GetRoughLeft()
	{
		return this->m_RoughLeft;
	}
	void SetRoughPlies(int plies)
	{
		this->m_Rough_Plies = plies;
	}
	int GetRoughPlies()
	{
		return this->m_Rough_Plies;
	}

	CPoint3D GetCenter()
	{
		return m_RectCenter;
	}
	vector<vector<vector<CPoint3D>>> GetRoughPoints()
	{
		return this->ArrayPoint;
	}
	vector<vector<vector<CPoint3D>>> GetRoughCutPoints()
	{
		return this->ADArrayPoint;
	}
	vector<vector<vector<CPoint3D>>> GetFinishPoints()
	{
		return this->FinishPoints;
	}
private:
	CPtrArray m_ptArray;
	CVector3D m_Translation;//���ڴ洢XYƽ����X���ֵ����XZ���ֵ������λ��
	float m_FeedSpeed;
	float m_FeedTime;
	float m_FeedSpeed_VX;
	float m_FeedTime_VX;
	float m_FeedSpeed_Finish;//���ӹ�ˮƽ������ٶ�
	float m_FeedTime_Finish;//���ӹ�ˮƽ��岹����
	float m_FeedSpeed_VX_Finish;//���ӹ���ֱ������ٶ�
	float m_FeedTime_VX_Finish;//���ӹ���ֱ��岹����
	float m_Piece_Long;
	float m_Piece_Width;
	float m_Piece_Heigth;
	float m_DepthOfCut;//�洢�ּӹ�ÿ�ε�ˮƽ������
	float m_DepthOfCut_Finish;//�洢���ӹ�ÿ�ε�ˮƽ������
	float m_RoughLeft;//�洢�ּӹ�����
	CPoint3D m_RectCenter;
	int m_Rough_Plies;//��Ŵּӹ�����

	//����CPtrArray���ִ��ָ����������ø��ƶ�����и��ƣ����Ը���ָ����ָ������ֵ
	
	vector<vector<CPoint3D>> SidePoint;//�洢��ȡ��׼ȷ��Ϣ�ĵ�
	
	vector<CPtrArray*> NewArrayList;//���ڴ洢�ּӹ�����켣ÿ���������λ��ָ��

	vector<vector<vector<CPoint3D>>> ArrayPoint;//�����洢�ӹ��켣ÿ��ĵ�λvector<CPoint3D>�洢ÿһ���߶��ϵ���ɢ�㣬
	                                            //vector<vector<CPoint3D>>�洢����һ��ƫ�ƵĲ���������������е�
	                                            //vector<vector<vector<CPoint3D>>>�洢��������ƫ�ƾ���Ĳ��������ϵ����е�
	vector<vector<vector<CPoint3D>>> ADArrayPoint;//�洢ArrayPoint�����жϺ�����е�

	vector<vector<CPoint3D>> RoughLeftPoints;//�洢�ּӹ������ϵĵ�

	vector<CPtrArray*> FinishArrayList;//�洢���ӹ�����ÿ���������λ��ָ��
	vector<vector<vector<CPoint3D>>> FinishPoints;//�洢���ӹ��ĵ�

	public://���õķ����
	vector<CPoint3D> RoughSimulationPoints;//�洢�ּӹ��ķ�����ٴּӹ���ʼ�������н��д�����������̧����
	vector<CPoint3D> FinishSimulationPoints;//�洢���ӹ��ķ���㣬����̧����
	


//����ӹ�Surface Process
public:
	vector<CPoint3D> ArcDiscreteYZ(CPoint3D& center, float radio, float beginAngle, float endAngle, CPtrArray& XFarray, int index, float Inter, float F);
	vector<CPoint3D> PolyArcDiscreteYZ(CPoint3D begin, CPoint3D end, float TuduAngle, float Inter, float F);
public:
	void RenderArcInit();
	void RenderArc(COpenGLDC* pDC);//����˫�������ʾ��ͼ
	
	vector<vector<CPoint3D>> ArcDiscrete(CPtrArray& m_Array);
	vector<vector<CPoint3D>> ArcFinishDiscrete(CPtrArray& m_Array);
	void RenderArcSection(CPtrArray& m_Array, COpenGLDC* pDC);
	void RenderRoughArcInit();
	void RenderRoughArc(COpenGLDC* pDC);//����˫����Բ���ּӹ�ƫ�ù켣

	CPoint3D GetArcWorkBlankCenter(float higth);//��ȡë�����ε����ĵ�

	//�ּӹ��켣�ض�,���üӹ�������ʱ����ֻ�ó���һ�㣬���ټӹ�ʱ��
	void RenderArcRoughCutInit();//��Y��������������X������������ȡ�����洢��vector<CArc*>�У�Ȼ����ȡ������ֱ�߱Ƚ��н��㣬��ȡ���㣬Բ����Ϊ����СԲ����һ���߶�
	void RenderArcRoughCut(COpenGLDC* pDC);

	//�ּӹ�����
	void RenderArcRoughLeftInit();
	void RenderArcRoughLeft(COpenGLDC* pDC);
	//���ӹ�
	void RenderArcFinishInit();
	void RenderArcFinish(COpenGLDC* pDC);
	
	//���÷����
	vector<CPoint3D> SetArcRoughSimulationPoints(vector<vector<vector<CPoint3D>>> ArcRoughPoints);
	vector<CPoint3D> SetArcFinishSimulationPoints(vector<vector<vector<CPoint3D>>> ArcFinishPoints);

	public://�洢�������
		vector<vector<CPoint3D>> m_ArcPiecePoints;//�洢˫����Բ��ʾ��ͼ��
		vector<CPtrArray*> m_ArcRoughArrayList;
		
		vector<vector<vector<CPoint3D>>> m_ArcRoughPoints;//�洢�ּӹ���ɢ��

		vector<vector<CPtrArray*>> m_ArcsYSide;//�洢Y��Բ���ļ���
		vector<vector<vector<CPoint3D>>> m_ArcRoughCutPoints;//�洢�ּӹ��ü���ĵ�

		CPtrArray m_ArcRoughLeftArray;
		vector<vector<CPoint3D>> m_ArcRoughLeftPoints;//�洢�ּӹ�������ɢ��

		vector<CPtrArray*> m_ArcFinishArrayList;
		vector<vector<CPtrArray*>> m_ArcFinishYSide;//�洢���ӹ�Y��Բ���ļ���
		vector<vector<vector<CPoint3D>>> m_ArcFinishPoints;//�洢�����ӹ���ɢ��

	public:
		void SetArcArray(CPtrArray& Array)
		{
			this->m_ArcArray.Copy(Array);
		}
		CPtrArray& GetArcArray()
		{
			return this->m_ArcArray;
		}
		void SetArcWorkBlank(float length, float width, float heigth)
		{
			this->m_Arc_WorkBlankLong = length;
			this->m_Arc_WorkBlankWidth = width;
			this->m_Arc_WorkBlankHeigth = heigth;
		}
		float GetArcWorkBlankLongth()
		{
			return this->m_Arc_WorkBlankLong;
		}
		float GetArcWorkBlankWidth()
		{
			return this->m_Arc_WorkBlankWidth;
		}
		float GetArcWorkBlankHeigth()
		{
			return this->m_Arc_WorkBlankHeigth;
		}
		//�ּӹ�����
		void SetYArcRoughFeedSpeed(float speed)
		{
			this->m_Rough_YArcFeedSpeed = speed;
		}
		float GetYArcRoughFeedSpeed()
		{
			return this->m_Rough_YArcFeedSpeed;
		}
		void SetYArcRoughFeedTime(float time)
		{
			this->m_Rough_YArcFeedTime = time;
		}
		float GetYArcRoughFeedTime()
		{
			return this->m_Rough_YArcFeedTime;
		}
		void SetXArcRoughFeedSpeed(float speed)
		{
			this->m_Rough_XArcFeedSpeed = speed;
		}
		float GetXArcRoughFeedSpeed()
		{
			return this->m_Rough_XArcFeedSpeed;
		}
		void SetXArcRoughFeedTime(float time)
		{
			this->m_Rough_XArcFeedTime = time;
		}
		float GetXArcRoughFeedTime()
		{
			return this->m_Rough_XArcFeedTime;
		}
		void SetArcRoughVerticalDistance(float distance)
		{
			this->m_Rough_VerticalDistance = distance;
		}
		float GetArcRoughVerticalDistance()
		{
			return this->m_Rough_VerticalDistance;
		}
		void SetArcRoughPiles(float piles)
		{
			this->m_ArcRough_NumberOfPiles = piles;
		}
		float GetArcRoughPiles()
		{
			return m_ArcRough_NumberOfPiles;
		}
		void SetArcRoughLeft(float left)
		{
			this->m_ArcRough_Left = left;
		}
		float GetArcRoughLeft()
		{
			return this->m_ArcRough_Left;
		}

		//���ӹ�����
		void SetYArcFinishFeedSpeed(float speed)
		{
			this->m_Finish_YArcFeedSpeed = speed;
		}
		float GetYArcFinishFeedSpeed()
		{
			return this->m_Finish_YArcFeedSpeed;
		}
		void SetYArcFinishFeedTime(float time)
		{
			this->m_Finish_YArcFeedTime = time;
		}
		float GetYArcFinishFeedTime()
		{
			return this->m_Finish_YArcFeedTime;
		}

		void SetXArcFinishFeedSpeed(float speed)
		{
			this->m_Finish_XArcFeedSpeed=speed;
		}
		float GetXArcFinishFeedSpeed()
		{
			return m_Finish_XArcFeedSpeed;
		}
		void SetXArcFinishFeedTime(float time)
		{
			this->m_Finish_XArcFeedTime = time;
		}
		float GetXArcFinishFeedTime()
		{
			return this->m_Finish_XArcFeedTime;
		}
		void SetArcFinishVerticalDistance(float distance)
		{
			this->m_Finish_VerticalDistance = distance;
		}
		float GetArcFinishVerticalDistance()
		{
			return this->m_Finish_VerticalDistance;
		}
		void SetArcFinishPiles(float piles)
		{
			this->m_ArcFinish_NumberOfPiles = piles;
		}
		float GetArcFinishPiles()
		{
			return this->m_ArcFinish_NumberOfPiles;
		}
	private:
		//�������ݵĻ�ȡ
		CPtrArray m_ArcArray;
		//ë�����ò���
		float m_Arc_WorkBlankLong;
		float m_Arc_WorkBlankWidth;
		float m_Arc_WorkBlankHeigth;
		//�ּӹ�����
		float m_Rough_YArcFeedSpeed;//Y��Բ��
		float m_Rough_YArcFeedTime;
		float m_Rough_XArcFeedSpeed;//X��Բ��
		float m_Rough_XArcFeedTime;
		float m_Rough_VerticalDistance;//��ֱ�µ�����
		float m_ArcRough_NumberOfPiles;//�ּӹ�����
		float m_ArcRough_Left;//�ּӹ�����

		//���ӹ�����
		float m_Finish_YArcFeedSpeed;//Y��Բ��
		float m_Finish_YArcFeedTime;
		float m_Finish_XArcFeedSpeed;//X��Բ��
		float m_Finish_XArcFeedTime;
		float m_Finish_VerticalDistance;//��ֱ�µ�����
		float m_ArcFinish_NumberOfPiles;//���ӹ�����

};

