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
	int x;//敌机坐标x
	int y;//敌机坐标y
	int v;//敌机速度
	int Size;//敌机大小
	int FS;//敌机分数
}DiJi;
typedef struct
{
	int x;//子弹坐标x
	int y;//子弹坐标y
	int v;//子弹速度
	int Size;//子弹大小
	int Colr;//子弹颜色
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
	CDC *pDC;//定义pDC指向CDC类对象的指针

	DiJi m_JX[100];//矩形敌机
	DiJi m_SJX[100];//三角形敌机
	DiJi m_YX[100];//圆形敌机
	int m_nJX;//矩形敌机数
	int m_nSJX;//三角形敌机数
	int m_nYX;//圆形敌机数

	ZiDan m_ZD[100];//子弹
	int m_nZD;//子弹数
	
	int m_r;//坦克圆半径
	int m_x;//坦克坐标x
	int m_y;//坦克坐标y
	int m_L1,m_L2;//坦克长
	int m_LPT;//坦克炮筒长
	int m_Dire;//坦克方向
	int m_V;//坦克移动速度

	int m_ZongFen;//总分
	int m_CiShu;//次数

};

#endif // !defined(AFX_TANKEWAR_H__E3D8AC84_899B_4FC9_831B_D2690371FF58__INCLUDED_)
