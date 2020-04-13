#pragma once
#include <afxwin.h>
class CChildWnd :
	public CWnd
{
public:
	CChildWnd();
	~CChildWnd();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

