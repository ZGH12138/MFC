// TankWarView.cpp : implementation of the CTankWarView class
//

#include "stdafx.h"
#include "TankWar.h"

#include "TankWarDoc.h"
#include "TankWarView.h"
#include "TanKeWar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTankWarView

IMPLEMENT_DYNCREATE(CTankWarView, CView)

BEGIN_MESSAGE_MAP(CTankWarView, CView)
	//{{AFX_MSG_MAP(CTankWarView)
	ON_COMMAND(ID_M_Start, OnMStart)
	ON_COMMAND(ID_M_Stop, OnMStop)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTankWarView construction/destruction

CTankWarView::CTankWarView()
{
	// TODO: add construction code here

}

CTankWarView::~CTankWarView()
{
}

BOOL CTankWarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTankWarView drawing

void CTankWarView::OnDraw(CDC* pDC)
{
	CTankWarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDC MemDc;
	int width,height;
	CRect rect;
	CBitmap MemBitmap;
	GetWindowRect(&rect);
	width = rect.Width();
	height = rect.Height();
	MemDc.CreateCompatibleDC(NULL);
	MemBitmap.CreateCompatibleBitmap(pDC,width,height);
    CBitmap *pOldBit = MemDc.SelectObject(&MemBitmap);
	MemDc.FillSolidRect(0,0,width,height,RGB(255,255,255));
	MemDc.SetBkMode(TRANSPARENT);

	//tw.Draw(pDC);
	tw.Draw(&MemDc);

	pDC->BitBlt(0,0,width,height,&MemDc,0,0,SRCCOPY);
	MemBitmap.DeleteObject();
	MemDc.DeleteDC();
}

/////////////////////////////////////////////////////////////////////////////
// CTankWarView printing

BOOL CTankWarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTankWarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTankWarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTankWarView diagnostics

#ifdef _DEBUG
void CTankWarView::AssertValid() const
{
	CView::AssertValid();
}

void CTankWarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTankWarDoc* CTankWarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTankWarDoc)));
	return (CTankWarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTankWarView message handlers

void CTankWarView::OnMStart() 
{
	// TODO: Add your command handler code here
	SetTimer(1,1000,NULL);
	SetTimer(2,100,NULL);
}

void CTankWarView::OnMStop() 
{
	// TODO: Add your command handler code here
	KillTimer(1);
	KillTimer(2);
}

void CTankWarView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		tw.CreateDiJi();
		tw.CreateZiDan();
		Invalidate(true);
	}
	if(nIDEvent == 2)
	{
		tw.MoveDiJi();
		tw.MoveZiDan();
		tw.MoveTanKe();
		tw.PengZhuangDiJiZiDan();
		if(tw.m_CiShu != 0)
		{
			if(tw.PengZhuangDiJiTanKe()==1)
			{
				CString str;
				str.Format("»¹Ê£%dÌõÃü£¡",tw.m_CiShu);
				AfxMessageBox(str);
				SetTimer(1,1000,NULL);
				SetTimer(2,100,NULL);
			}
		}
		else
		{
			KillTimer(1);
			KillTimer(2);
			AfxMessageBox("Game Over!");
		}
			
		Invalidate(true);
	}
	CView::OnTimer(nIDEvent);
}

void CTankWarView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	tw.ChangeDire(nChar);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CTankWarView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
	return CView::OnEraseBkgnd(pDC);
}
