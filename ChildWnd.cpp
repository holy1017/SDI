#include "pch.h"
#include "ChildWnd.h"


CChildWnd::CChildWnd()
{
}


CChildWnd::~CChildWnd()
{
}
BEGIN_MESSAGE_MAP(CChildWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CChildWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CWnd::OnPaint()��(��) ȣ������ ���ʽÿ�.
	dc.TextOut(20, 20, _T(" ���ϵ� ������ �Դϴ�"));
}
