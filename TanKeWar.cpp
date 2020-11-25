// TanKeWar.cpp: implementation of the CTanKeWar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TankWar.h"
#include "TanKeWar.h"
#include "math.h"
#define PI 3.1415926

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//初始化
CTanKeWar::CTanKeWar()
{	
	m_nJX = 0;
	m_nSJX = 0;
	m_nYX = 0;
	m_nZD = 0;
	m_x = 500;
	m_y = 500;
	m_r = 15;
	m_L1 = 50;
	m_L2 = 60;
	m_LPT = 50;
	m_ZongFen = 0;
	m_Dire = 1;//1表示向左，2表示向上，3表示向右，4表示向下
	m_V = 5;
	m_CiShu = 3;

}

CTanKeWar::~CTanKeWar()
{

}
//创造敌机
void CTanKeWar::CreateDiJi()
{
	int sjs;//随机数
	sjs = rand()%3;//对3求余，即0,1,2
	switch(sjs)
	{
	case 0:
		m_JX[m_nJX].x = rand()%700 + 50;
		m_JX[m_nJX].y = 0;
		m_JX[m_nJX].v = rand()%50 + 10;
		m_JX[m_nJX].Size = rand()%20 + 10;
		m_JX[m_nJX].FS = m_JX[m_nJX].v + 100/m_JX[m_nJX].Size;
		m_nJX++;
		break;
	case 1:
		m_SJX[m_nSJX].x = rand()%700 + 50;
		m_SJX[m_nSJX].y = 0;
		m_SJX[m_nSJX].v = rand()%30 + 10;
		m_SJX[m_nSJX].Size = rand()%60 + 30;
		m_SJX[m_nSJX].FS = m_SJX[m_nSJX].v + 300/m_SJX[m_nSJX].Size;
		m_nSJX++;
		break;
	case 2:
		m_YX[m_nYX].x = rand()%700 + 50;
		m_YX[m_nYX].y = 0;
		m_YX[m_nYX].v = rand()%40 + 10;
		m_YX[m_nYX].Size = rand()%40 + 20;
		m_YX[m_nYX].FS = m_YX[m_nYX].v + 200/m_YX[m_nYX].Size;
		m_nYX++;
		break;
	}

}
//画敌机
void CTanKeWar::DrawDiJi()
{
	int i;
	int x,y,r;
	for(i=0;i<m_nJX;i++)
	{
		x = m_JX[i].x;
		y = m_JX[i].y;
		r = m_JX[i].Size/2;
		pDC->Rectangle(x,y,x + r,y + r);
	}
	for(i=0;i<m_nSJX;i++)
	{
		x = m_SJX[i].x;
		y = m_SJX[i].y;
		r = m_SJX[i].Size/2;
		pDC->MoveTo(x,y);
		x -= r;
		y += r*2*cos(PI/6);
		pDC->LineTo(x,y);
		x += 2*r;
		pDC->LineTo(x,y);
		x = m_SJX[i].x;
		y = m_SJX[i].y;
		pDC->LineTo(x,y);
	}	
	for(i=0;i<m_nYX;i++)
	{
		x = m_YX[i].x;
		y = m_YX[i].y;
		r = m_YX[i].Size/2;
		pDC->Ellipse(x - r,y - r,x + r,y + r);
	}


}
//移动敌机
void CTanKeWar::MoveDiJi()
{
	int i;
	for(i=0;i<m_nJX;i++)
	{
		m_JX[i].y += m_JX[i].v * 0.1;
		if(m_JX[i].y>750)
			DeleteDiJi(0,i);
	}
	for(i=0;i<m_nSJX;i++)
	{
		m_SJX[i].y += m_SJX[i].v * 0.3;
		if(m_SJX[i].y>750)
			DeleteDiJi(1,i);
	
	}	
	for(i=0;i<m_nYX;i++)
	{
		m_YX[i].y += m_YX[i].v * 0.2;
		if(m_YX[i].y>750)
			DeleteDiJi(2,i);
	}


}
//消除敌机
void CTanKeWar::DeleteDiJi(int xz, int n)
{
	switch(xz)
	{
	case 0:
		m_JX[n] = m_JX[m_nJX-1];
		m_nJX--;
		break;
	case 1:
		m_SJX[n] = m_SJX[m_nSJX-1];
		m_nSJX--;
		break;
	case 2:
		m_YX[n] = m_YX[m_nYX-1];
		m_nYX--;
		break;
	}

}
//创造子弹
void CTanKeWar::CreateZiDan()
{
	m_ZD[m_nZD].x = m_x;
	m_ZD[m_nZD].v = rand()%50 + 25;
	m_ZD[m_nZD].Size = rand()%20 + 10;
	m_ZD[m_nZD].y = m_y - m_r*sqrt(3)/2 - m_LPT - m_ZD[m_nZD].Size/2;
	m_ZD[m_nZD].Colr = RGB(120,160,200);
	m_nZD++;
	
}
//画子弹
void CTanKeWar::DrawZiDan()
{
	int i;
	int x,y,r;
	for(i=0;i<m_nZD;i++)
	{
		x = m_ZD[i].x;
		y = m_ZD[i].y;
		r = m_ZD[i].Size/2;
		CBrush brush;
		brush.CreateSolidBrush(m_ZD[i].Colr);
		pDC->SelectObject(&brush);
		pDC->BeginPath();
		pDC->Ellipse(x - r,y - r,x + r,y + r);
		pDC->EndPath();
		pDC->FillPath();
	}

}
//移动子弹
void CTanKeWar::MoveZiDan()
{
	int i;
	for(i=0;i<m_nZD;i++)
	{
		m_ZD[i].y -= m_ZD[i].v * 0.2;
		if(m_ZD[i].y < 75)
			DeleteZiDan(i);
	}

}
//消除子弹
void CTanKeWar::DeleteZiDan(int n)
{
	m_ZD[n] = m_ZD[m_nZD-1];
	m_nZD--;
}
//画坦克
void CTanKeWar::DrawTanKe()
{
	int x1,x2,y1,y2,z1,z2;
	x1 = m_L1/2;
	x2 = m_L2/2;
	y1 = 2*m_r;
	y2 = 3*m_r;
	pDC->Rectangle(m_x - x2,m_y - y2,m_x + x2,m_y + y2);
	pDC->Rectangle(m_x - x1,m_y - y1,m_x + x1,m_y + y1);
	pDC->Ellipse(m_x - m_r,m_y - m_r,m_x + m_r,m_y + m_r);
	z1 = m_r/2;
	z2 = m_r*sqrt(3)/2;
	pDC->MoveTo(m_x + z1,m_y - z2);
	pDC->LineTo(m_x + z1,m_y - z2 - m_LPT);
	pDC->LineTo(m_x - z1,m_y - z2 - m_LPT);
	pDC->LineTo(m_x - z1,m_y - z2);

}
//移动坦克
void CTanKeWar::MoveTanKe()
{
	if(m_Dire == 1) m_x -= m_V;
	if(m_Dire == 2) m_y -= m_V;
	if(m_Dire == 3) m_x += m_V;
	if(m_Dire == 4) m_y += m_V;
}
//方向变化
void CTanKeWar::ChangeDire(int n)
{
	switch(n)
	{
	case 37:
		m_Dire = 1;//向左
		break;
	case 38:
		m_Dire = 2;//向上
		break;
	case 39:
		m_Dire = 3;//向右
		break;
	case 40:
		m_Dire = 4;//向下
		break;
	}

}
//画图
void CTanKeWar::Draw(CDC *p)
{
	CString str,str1;
	pDC=p;
	DrawDiJi();
	DrawTanKe();
	DrawZiDan();
	str.Format("总分：%d",m_ZongFen);
	str1.Format("您有%d条命！",m_CiShu);
	pDC->TextOut(50,50,str1);
	pDC->TextOut(100,100,str);

}
//子弹敌机碰撞
void CTanKeWar::PengZhuangDiJiZiDan()
{
	int i,j;
	int d;
	for(i=0;i<m_nZD;i++)
	{	
		for(j=0;j<m_nJX;j++)
		{
			d = sqrt((m_ZD[i].x - m_JX[j].x)*(m_ZD[i].x - m_JX[j].x)+(m_ZD[i].y - m_JX[j].y)*(m_ZD[i].y - m_JX[j].y));
			if(d<m_ZD[i].Size/2 + m_JX[j].Size/2)
			{
				m_ZongFen += m_JX[j].FS;
				DeleteDiJi(0,j);
				DeleteZiDan(i);
				break;
			}
		}
		if(j<m_nJX)
			continue;
		for(j=0;j<m_nSJX;j++)
		{
			d = sqrt((m_ZD[i].x - m_SJX[j].x)*(m_ZD[i].x - m_SJX[j].x)+(m_ZD[i].y - m_SJX[j].y)*(m_ZD[i].y - m_SJX[j].y));
			if(d<m_ZD[i].Size/2 + m_SJX[j].Size/2)
			{
				m_ZongFen += m_SJX[j].FS;
				DeleteDiJi(1,j);
				DeleteZiDan(i);
				break;
			}
		}
		if(j<m_nSJX)
			continue;
		for(j=0;j<m_nYX;j++)
		{
			d = sqrt((m_ZD[i].x - m_YX[j].x)*(m_ZD[i].x - m_YX[j].x)+(m_ZD[i].y - m_YX[j].y)*(m_ZD[i].y - m_YX[j].y));
			if(d<m_ZD[i].Size/2 + m_YX[j].Size/2)
			{
				m_ZongFen += m_YX[j].FS;
				DeleteDiJi(2,j);
				DeleteZiDan(i);
				break;
			}
		}
		if(j<m_nYX)
			continue;
	}

}
//敌机坦克碰撞
int CTanKeWar::PengZhuangDiJiTanKe()
{
	int i,d;
	int flag=0;
	for(i=0;i<m_nJX;i++)
	{
		d = sqrt((m_JX[i].x - m_x)*(m_JX[i].x - m_x)+(m_JX[i].y - m_y)*(m_JX[i].y - m_y));
		if(d<m_JX[i].Size/2+m_r*sqrt(3)/2+m_LPT)
		{
			flag=1;
			DeleteDiJi(0,i);
			m_CiShu--;
			return flag;
		}
	}
	for(i=0;i<m_nSJX;i++)
	{
		d = sqrt((m_SJX[i].x - m_x)*(m_SJX[i].x - m_x)+(m_SJX[i].y - m_y)*(m_SJX[i].y - m_y));
		if(d<m_SJX[i].Size/2+m_r*sqrt(3)/2+m_LPT)
		{	
			flag=1;
			DeleteDiJi(1,i);
			m_CiShu--;
			return flag;
		}
	}
	for(i=0;i<m_nYX;i++)
	{
		d = sqrt((m_YX[i].x - m_x)*(m_YX[i].x - m_x)+(m_YX[i].y - m_y)*(m_YX[i].y - m_y));
		if(d<m_YX[i].Size/2+m_r*sqrt(3)/2+m_LPT)
		{	
			flag=1;
			DeleteDiJi(2,i);
			m_CiShu--;
			return flag;
		}
	}

}
