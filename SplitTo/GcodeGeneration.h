#pragma once
#include"SplitToDoc.h"

//�����������ǰ�ô����������ĵ�λ����Ϣ���д��������ô���
//ʹ������NC����
//��ͳ��Ҫͨ�����ɵ�λ�ļ������ɣ�����λ��͵���ʸ���������ɣ����ҵ�λ�ļ�ΪAPT���ԣ����ﲻ�����ɵ�λ�ļ�
//ֱ�Ӿ�����NC���룬���ҽ�NC������б������������ʾ��CSplitToView����ϵ�List�ؼ��У�ʹ�����ܹ����Ŷ�ʱ������ʵʱ����ʾ

/*˼·���Ƕ��ڸ��ּӹ����ͽ����жϣ�����/��ת��/Բ��/�����������жϣ����ݲ�ͬ�ļӹ����ͽ�����Ӧ��
  NC��������ɣ����Ǹ����߶�����˳�ŵ������״���мӹ�������������Ӧ��G����
*/
typedef struct tagsort
{
	CPoint3D begin;
	CPoint3D end;
	int flag;//��¼����
	CPoint3D center = CPoint3D(0, 0, 0);
}sort;
typedef struct tagTyeSort
{
	CPoint3D position;
	int flag;//��¼����
	CPoint3D center; //�洢Բ������
}TypeSort;
typedef struct tagWorkBlankRect
{
	CPoint3D LeftTop;
	CPoint3D LeftBottom;
	CPoint3D RightTop;
	CPoint3D RightBottom;
}WorkBlankRect;
class CGcodeGeneration
{
public:
	//CGcodeGeneration(CPtrArray& Array);
	CGcodeGeneration(CToolPath* tool);
	~CGcodeGeneration();
public:
	void Init();//��ʼ��
	void OutPutNcCode();//�������������
	void ShowNcCode();//��ʾNC����
	
	//��ͬģ��NC������
	//��ת��ӹ�NC����
	void RotateNC(ofstream* of);//��ת�ӹ��ּӹ�NC��������
	CPtrArray* RotateCalculate(CPoint3D circlecenter,float circleradius,float workBlankLong,float workBlankWidth);//�����Բ�ֳɼ���Բ����ֱ��
	
	//����ӹ�NC����
	BOOL SideNCInit();//��ʼ����ؼ���
	BOOL JugeInSide(CPoint3D& pos, CPoint3D center, float workBlankLong, float workBlankWidth);
	CPtrArray* SideNCOffsetAlgorithm(CPtrArray& XFarray, int mark, double offset);//ƫ���㷨
	void SideNC(ofstream* of);//����ӹ�NC��������
	CPtrArray* SideCalculate(vector<TypeSort> pts);
	vector<vector<vector<TypeSort>>> m_SideRough;//�洢����ӹ�δ�ü���ɢ���ĵ�ļ��ϣ������ֱ��1Բ��2��Բ��Բ�ķ���
	vector<vector<CPtrArray*>> m_SideNCFinish;

	//Բ������ӹ�NC����
	BOOL ArcNCInit();//��ʼ��
	void ArcNC(ofstream* of);//��������
	vector<sort> ArcNCCalculate(CPtrArray& Array, float High);//����Բ����ˮƽ�ߵĽ������⣬��������Բ��һ���߶Σ�����һ��Բ��
	vector<vector<vector<sort>>> m_ArcRough;//�洢˫����ּӹ��ü���ĸ��εı�ǣ�ֱ��1Բ��2
	vector<vector<vector<sort>>> m_ArcFinish;//�洢˫���澫�ӹ����εı�ǣ�ֱ��1Բ��2

	//�����ӹ�NC����
	BOOL LineNCInit();
	void LineNC(ofstream* of);
	vector<vector<sort>> LineRoughArc;//�洢�ּӹ�Բ����
	vector<sort> LineFinishArc;//�洢���ӹ�Բ����

	//�����ӹ�NC����
	BOOL OrthgonalNCInit();
	void OrthgonalNC(ofstream* of);


	//����μӹ�NC����
	BOOL PolygonNCInit();
	void PolygonNC(ofstream* of);

	//̨���ӹ�
	void TableBoardNC(ofstream* of);
	void TableBoardOutNC(vector<vector<vector<elements>>> data, ofstream* of);
	void TableBoardInSawNC(vector<vector<vector<vector<elements>>>> data, ofstream* of);
	void TableBoardInMillNC(vector<vector<vector<vector<elements>>>> data, ofstream* of);

public:
	void Input_G00(float posx, float posy, float posz, ofstream* of);
	void Input_G01(float posx, float posy, float posz, ofstream* of);
	void Input_G02(float posx, float posy, float posz, float posi, float posj, ofstream* of);
	void Input_G03(float posx, float posy, float posz, float posi, float posj, ofstream* of);

private:
	//CPtrArray m_CodeArray;//��¼ԭʼͼԪ��Ϣ
	CToolPath* pTool;
	int m_Number;//��¼����

	//��¼�����ּӹ�ÿ�����״˳����Ϣ,��������
	vector<vector<CPtrArray*>> m_EverySideRoughPile;

	//���
	CString FLAG;
};

