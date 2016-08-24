#pragma once
#include "ToolPath.h"



//�Ի�����ȡ�����ݵ������н��б��桢����

typedef struct tagelements
{
	CPoint3D begin;
	CPoint3D end;
	int flag=1;//��¼����

	CPoint3D center = CPoint3D(0, 0, 0);
	float radius = 0;
	float start_angle = 0.0;
	float end_angle = 0.0;
	float tudu ;//��ͨԲ��Ϊ0�����߶�Բ����Ϊ0
	BOOL arc_direction = false;//Բ���ķ���Ĭ��Ϊfalse,˳ʱ�룬trueΪ��ʱ��
}elements;

class CTableBoardProcess :
	public CToolPath
{

public:
	static CTableBoardProcess* GetTableProcessInstance();
private:
	static CTableBoardProcess* m_TableProcess;

	//˽����Ƕ�࣬��Ψһ�ĺô�����ɽ��CTableBoardDlgʵ��
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (CTableBoardProcess::m_TableProcess)
				delete CTableBoardProcess::m_TableProcess;
		}
	};
	//�����ڽ�����ʱ��ϵͳ���Զ��������е�ȫ�ֱ�����
	//��ʵ�ϣ�ϵͳҲ���������е���ľ�̬��Ա������������Щ��̬��ԱҲ��ȫ�ֱ���һ����
	//����һ����̬���������������ʱ���Զ�����������������
	//����д��ֱ�ӷ���������������Ҫ�ã�������ִ���
	static CGarbo Garbo;


private:
	CTableBoardProcess();
	~CTableBoardProcess();

public:

	//��ʼ������
	void InitData(CPtrArray* input);
	//��ԭ�ȵ������������
	void ClearData();

	void ClearBoardArray();

	//���ݸ߶��Լ���������ݽ��д���ģ��
	vector<CPtrArray*>  InitTableModel(CPtrArray* data,float high,float depth);
	
	//����ԭʼ����
	vector<elements> CalculateData(CPtrArray* input);
	vector<elements> New_CalculateData(CPtrArray* input);
	//�������input�����ֱ�ߵ����ݸ���������߰뾶����ֱ�߽��д�ϴ��������������´洢����
	vector<elements> ChangeSegments(vector<elements> data);
	
	//���ֱ�߽�һ��ֱ�߽ضϳ����Σ�������
	vector<elements> SeperateToThreeParts(elements LineData,float Diamand,float CutDepth);
	//ʶ�������������������������������ݽ������
	vector<vector<elements>> RegonizeProfile(vector<elements> data);

	//��vector<elements>��Ԫ��תΪCPtrArray�������ݵ���ɢ���Լ���ʾ
	CPtrArray* Change_To_Array(vector<elements> data);
	elements Copy_Elements(elements data);
	vector<CPtrArray*> Copy_CPtrArrays(vector<CPtrArray*> data);
private:	
	//�洢ԭʼ��ָ�����ݣ����е�����
	CPtrArray* m_ptBoardArray;//CPtrArray*->vector<elements>------->CPtrArray*���㻭ͼ��洢
	
	CPtrArray* m_innerArray;//��

	CPtrArray* m_outArray;//��

	CPtrArray* m_outOnlyLineArray;//ֻ�洢��������ֱ��Ԫ��
	CPtrArray* m_inOnlyLineArray;//ֻ�洢��������ֱ��Ԫ��

	vector<CPtrArray*> m_ArrayList;
	vector<CPtrArray*> m_InArrayList;
	vector<CPtrArray*> m_OutArrayList;

	
	
	//�洢ԭʼ����,ֻ��¼��ʼ�㣬��ֹ�㣬�뾶��Բ�ġ�
	vector<elements> m_SourceData;
	//�洢�ü�������ݣ�ֻ��¼��ʼ�㣬��ֹ�㣬�뾶��Բ�ġ�
	vector<elements> m_CutData;
	//�洢�ڡ������������ݣ�ֻ��¼��ʼ�㣬��ֹ�㣬�뾶��Բ�ġ�
	vector<vector<elements>> m_ProfileData;


public:
	//��ʾ���������ߴ�
	void RenderTableBoard(COpenGLDC* pDC);
	//����CPtrArray*����,���滹��Ҫ���㣬�Ƚ���
	void DrawDIY(CPtrArray* array, COpenGLDC* pDC);
	//
	void DrawDIYFromPt(vector<vector<CPoint3D>> data, COpenGLDC* pDC);
	void DrawDIYFromPt(vector<vector<vector<vector<CPoint3D>>>> data,COpenGLDC* pDC);
	void DrawDIYFromOffset(vector<OffsetPoint> data, COpenGLDC* pDC);
	void DrawOutRetractLine(vector<vector<vector<CPoint3D>>> data, COpenGLDC* pDC);/*�����ⲿ�����Ľ��˵���*/
	void DrawInSawRetractLine(vector<vector<vector<vector<CPoint3D>>>> data, COpenGLDC* pDC);/*�����ڲ���Ƭ�����Ľ��˵���*/
	void DrawInMillRetractLine(vector<vector<vector<vector<CPoint3D>>>> data, COpenGLDC* pDC);/*�����ڲ�ϳ�������Ľ��˵���*/

	//��ʾë��
	void InitTableBlank();
	vector<OffsetPoint> OffsetShapeAlgorithm(CPtrArray& XFarray, int mark, double offset);//��ȡƫ�ƺ�������ʼ����Ϣ
	void RenderTableBlank(COpenGLDC* pDC);
	//��ʾ�������켣
	void InitTableInPath();
	void InitInArray();
	void InitTableSimulationPoints(vector<vector<vector<CPoint3D>>> m_outPts, 
		                          vector<vector<vector<vector<CPoint3D>>>> m_inSaw, vector<vector<vector<vector<CPoint3D>>>> m_inMill);
	//���ز������µ�elements����
	vector<elements> NewInsertElement(vector<elements> data);
	CPtrArray* CopyData(CPtrArray* data,vector<int> number);//��������,����λ��,number����洢�����±��λ��
	vector<vector<vector<vector<CPoint3D>>>> ChangesToMillPoints(vector<vector<vector<vector<CPoint3D>>>> data,float m_MillDepth);//����ɢ���ϳ���ĵ���д���ʹ����ܹ�����ϳ���ļӹ�����ֲ�
	vector<vector<vector<CPtrArray*>>> ChangesToMillProfiles(vector<vector<vector<CPtrArray*>>> data, float high, float depth);//ת�ɷ���ϳ���ӹ���ƫ�ù켣����ԭ����ֱ��������״̬�¡�
	int pos[4];//��¼λ����Ϣ
	void RenderTableMillPath(COpenGLDC* pDC);//��ʾϳ���켣
	void RenderTableSawPath(COpenGLDC* pDC);//��ʾ��Ƭ�켣
	//��ʾ�������켣
	void InitTableOutPath();
	vector<elements> OffsetOutPathAlgorithm(CPtrArray& XFarray, int mark, double offset);//��ȡ�ⲿ����ƫ�ú����ϸ��Ϣ 
	vector<elements> InsertExtendLineElements(vector<elements> data,float extendDis);//����β������ֱ�ߣ������Ƭ������
	void RenderTableOutPath(COpenGLDC* pDC);

public:
	//תΪ��
	vector<CPoint3D> ConverToPoints(CPtrArray* data, float F, float T);
	vector<vector<CPoint3D>> GetPoints(vector<CPtrArray*> data,float F,float T);
	vector<CPoint3D> GetPoints(CPtrArray* data, float F, float T);

	//�����������ƫ��offset����
	vector<vector<CPoint3D>> CoverOutsideProfToPoints(vector<CPtrArray*> data,float offset,float F, float T);
	//������ƫ����ȡ�㣬���ݴ洢��CPtrArray*
	vector<vector<CPoint3D>> CoverOutsideProfToPoints(vector<CPtrArray*> data, float F, float T);
	//���ڲ�������ƫ��offset����
	vector<vector<CPoint3D>> CoverInsideProfToPoints(vector<CPtrArray*> data, float offset, float F, float T);

	//���÷����
	vector<CPoint3D> m_BoardRoughSimulation;
	vector<CPoint3D> m_BoardFinishSimulation;

private:
	vector<vector<CPoint3D>> m_ModelPoints;//��ģ�͵���ɢ��
	vector<vector<CPoint3D>> m_InnerModelPoints;
	vector<vector<CPoint3D>> m_OuterModelPoints;

	vector<vector<CPoint3D>> m_OuterBlankPoints;

	//����Ͷ����ƫ������
	vector<OffsetPoint> m_OuterBlankOffset;
	vector<OffsetPoint> m_InBlankOffset;
	vector<OffsetPoint> m_OuterBlankTopOffset;
	vector<OffsetPoint> m_InBlankTopOffset;

	//���ƫ�ù켣�õ�
	vector<vector<CPtrArray*>> m_OutOffsetProfile;
	vector<vector<vector<CPoint3D>>> m_OutOffsetPoints;
	//���ü��켣�õ�

	//�ڲ��Ƭƫ�ù켣
	vector<vector<CPtrArray*>> m_inOffsetProfile;
	vector<vector<vector<CPoint3D>>> m_inOffsetPoints;

	vector<vector<vector<CPtrArray*>>> m_InOffsetSawProfile;
	vector<vector<vector<vector<CPoint3D>>>> m_InOffsetSawPoints;
	//�ڲ�ϳ��ƫ�ù켣
	vector<vector<vector<CPtrArray*>>> m_InOffsetMillProfile;
	vector<vector<vector<vector<CPoint3D>>>> m_InOffsetMillPoints;

	//��ʼ������NC��������Ҫ�����ݣ���Ҫ������Ӧ�ĵ�
	//�ú���calculate(CPtrArray* )����ɵ�vector<elements>
	public:
		vector<vector<vector<elements>>> InitTableOutNC(vector<vector<CPtrArray*>> data);
		vector<vector<vector<vector<elements>>>> InitTableInSawNC(vector<vector<vector<CPtrArray*>>> data);
		vector<vector<vector<vector<elements>>>> InitTableInMillNC(vector<vector<vector<CPtrArray*>>> data);
private:
	vector<vector<vector<elements>>> m_TableOutNCElements;
	vector<vector<vector<vector<elements>>>> m_TableInSawNCElements;
	vector<vector<vector<vector<elements>>>> m_TableInMillNCElements;
	public:
		vector<vector<vector<elements>>> GetTableOutNCElements()
		{
			return this->m_TableOutNCElements;
		}
		vector<vector<vector<vector<elements>>>> GetTableInSawNCElements()
		{
			return this->m_TableInSawNCElements;
		}
		vector<vector<vector<vector<elements>>>> GetTableInMillNCElements()
		{
			return this->m_TableInMillNCElements;
		}
	//�Ի������ݴ洢
private:
	int m_TotalSize;//�洢ϳ��ÿһС�εĵ�����
	float m_PerDownDis;//�洢ÿһС���½��ĸ߶�


	float m_ExtendLength;
	float m_Board_Heigh;
	float m_Board_Length;
	float m_Board_Width;

	float m_OutLeft;
	float m_InLeft;

	float m_B_FeedSpeed_Horizon;
	float m_B_FeedTime_Horizon;
	float m_B_FeedLoad_Horizon;
	//ˮƽÿ���е����
	float m_B_FeedDis_Horizon;

	float m_B_FeedSpeed_Vertical;
	float m_B_FeedTime_Vertical;
	//��ֱ�µ�ÿ�������
	float m_B_FeedLoad_Vertical;


	//ϳ������
	float m_MillToolDiamand;
	float m_MillCutDepth_Vertical;
	float m_MillCutDepth_Horizon;
	//�������������ȡ
public:
	void SetBoardToolDiamnd(float data)
	{
		this->m_MillToolDiamand = data;
	}
	float GetBoardToolDiamand()
	{
		return this->m_MillToolDiamand;
	}
	void SetBoardMillCutDepthVertical(float data)
	{
		this->m_MillCutDepth_Vertical = data;
	}
	float GetBoardMillCutDepthVertical()
	{
		return this->m_MillCutDepth_Vertical;
	}
	void SetBoardMillCutDepthHorizon(float data)
	{
		this->m_MillCutDepth_Horizon = data;
	}
	float GetBoardMillCutDepthHorizon()
	{
		return this->m_MillCutDepth_Horizon;
	}

	CPtrArray* GetBoardArray()
	{
		//�������ݵķ�װ�ԣ�����m_ptBoardArrayֻ�ܷ��ʣ����ܸ�����ָ���ַ�����ǿ���ͨ��ָ�����ָ����ָ���ֵ��
		return this->m_ptBoardArray;
	}

	void SetBoardHeigh(float data)
	{
		this->m_Board_Heigh = data;
	}
	float GetBoardHeigh()
	{
		return  this->m_Board_Heigh;
	}

	void SetBoardWidth(float data)
	{
		this->m_Board_Width = data;
	}
	float GetBoardWidth()
	{
		return this->m_Board_Width;
	}

	void SetBoardLength(float data)
	{
		this->m_Board_Length = data;
	}
	float GetBoardLength()
	{
		return this->m_Board_Length;
	}

	void SetBoardInLeft(float data)
	{
		this->m_InLeft = data;
	}
	float GetBoardInLeft()
	{
		return this->m_InLeft;
	}
	void SetBoardOutLeft(float data)
	{
		this->m_OutLeft = data;
	}
	float GetBoardOutLeft()
	{
		return this->m_OutLeft;
	}

	void SetBoardFeedSpeedHorizon(float data)
	{
		this->m_B_FeedSpeed_Horizon = data;
	}
	float GetBoardFeedSpeedHorizon()
	{
		return this->m_B_FeedSpeed_Horizon;
	}

	void SetBoardFeedTimeHorizon(float data)
	{
		this->m_B_FeedTime_Horizon = data;
	}
	float GetBoardFeedTimeHorizon()
	{
		return this->m_B_FeedTime_Horizon;
	}

	void SetBoardFeedLoadHorizon(float data)
	{
		this->m_B_FeedLoad_Horizon = data;
	}
	float GetBoardFeedLoadHorizon()
	{
		return this->m_B_FeedLoad_Horizon;
	}

	void SetBoardFeedDisHorizon(float data)
	{
		this->m_B_FeedDis_Horizon = data;
	}
	float GetBoardFeedDisHorizon()
	{
		return this->m_B_FeedDis_Horizon;
	}

	void SetBoardFeedSpeedVertical(float data)
	{
		this->m_B_FeedSpeed_Vertical = data;
	}
	float GetBoardFeedSpeedVertical()
	{
		return this->m_B_FeedSpeed_Vertical;

	}
	void SetBoardFeedTimeVertical(float data)
	{
		this->m_B_FeedTime_Vertical = data;
	}
	float GetBoardFeedTimeVertical()
	{
		return this->m_B_FeedTime_Vertical;
	}
	void SetBoardFeedLoadVertical(float data)
	{
		this->m_B_FeedLoad_Vertical = data;
	}
	float GetBoardFeedLoadVertical()
	{
		return this->m_B_FeedLoad_Vertical;
	}
};

