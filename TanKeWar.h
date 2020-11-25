// TanKeWar.h: interface for the CTanKeWar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TANKEWAR_H__E3D8AC84_899B_4FC9_831B_D2690371FF58__INCLUDED_)
#define AFX_TANKEWAR_H__E3D8AC84_899B_4FC9_831B_D2690371FF58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef struct
{
	int x;//�л�����x
	int y;//�л�����y
	int v;//�л��ٶ�
	int Size;//�л���С
	int FS;//�л�����
}DiJi;
typedef struct
{
	int x;//�ӵ�����x
	int y;//�ӵ�����y
	int v;//�ӵ��ٶ�
	int Size;//�ӵ���С
	int Colr;//�ӵ���ɫ
}ZiDan;
class CTanKeWar  
{
public:
	int PengZhuangDiJiTanKe();
	void PengZhuangDiJiZiDan();
	void Draw(CDC *p);
	void ChangeDire(int n);
	void MoveTanKe();
	void DrawTanKe();
	void DeleteZiDan(int n);
	void MoveZiDan();
	void DrawZiDan();
	void CreateZiDan();
	void DeleteDiJi(int xz,int n);
	void MoveDiJi();
	void DrawDiJi();
	void CreateDiJi();
	CTanKeWar();
	virtual ~CTanKeWar();
	CDC *pDC;//����pDCָ��CDC������ָ��

	DiJi m_JX[100];//���εл�
	DiJi m_SJX[100];//�����εл�
	DiJi m_YX[100];//Բ�εл�
	int m_nJX;//���εл���
	int m_nSJX;//�����εл���
	int m_nYX;//Բ�εл���

	ZiDan m_ZD[100];//�ӵ�
	int m_nZD;//�ӵ���
	
	int m_r;//̹��Բ�뾶
	int m_x;//̹������x
	int m_y;//̹������y
	int m_L1,m_L2;//̹�˳�
	int m_LPT;//̹����Ͳ��
	int m_Dire;//̹�˷���
	int m_V;//̹���ƶ��ٶ�

	int m_ZongFen;//�ܷ�
	int m_CiShu;//����

};

#endif // !defined(AFX_TANKEWAR_H__E3D8AC84_899B_4FC9_831B_D2690371FF58__INCLUDED_)
