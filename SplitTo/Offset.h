#pragma once
#include"Finish.h"
class COffset : public CFinish
{
public:
	COffset();
	~COffset();

	// �����ƫ�ò���
public:
	CVector3D slope(CPoint3D PtBegin, CPoint3D PtEnd);
	vector<CPoint3D> LineIntersection;//�洢ƫ�ƺ󽻵������
	vector<OffsetPoint> LineOffsetPoint;//�洢ƫ�ƺ�ֱ�����������
	vector<OffsetPoint> ExtendLine;//�洢��һ��ƫ���쳤��ĵ�λ��
	vector<vector<OffsetPoint>> Line;//�洢��������������
	void Polygeon(CPtrArray& Array, float distance, int number, float depth);
	CPoint3D TwoLineNot(OffsetPoint One, OffsetPoint Another);

	static void DrawOffset(COpenGLDC* pDC, CPtrArray m_ptArray);
};

