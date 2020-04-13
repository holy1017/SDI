// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해
// 추가적으로 제공되는 내용입니다.
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// SDIView.cpp: CSDIView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDI.h"
#endif

#include "SDIDoc.h"
#include "SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define ID_DECREASE_BUTTON	3000
#define ID_INCREASE_BUTTON	3100
#define ID_LISTBOX	        3200

#define ID_PROGBAR          3300

// CSDIView

IMPLEMENT_DYNCREATE(CSDIView, CView)

BEGIN_MESSAGE_MAP(CSDIView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_DECREASE_BUTTON, OnDecreaseButton)
	ON_COMMAND(ID_INCREASE_BUTTON, OnIncreaseButton)
END_MESSAGE_MAP()

// CSDIView 생성/소멸

CSDIView::CSDIView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSDIView::~CSDIView()
{
}

BOOL CSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIView 그리기

void CSDIView::OnDraw(CDC* /*pDC*/)
{
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSDIView 인쇄


void CSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSDIView 진단

#ifdef _DEBUG
void CSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIDoc* CSDIView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIView 메시지 처리기


int CSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TRACE0("CSDIView::OnCreate\n");
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.


	m_Wnd01.Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW),
		_T("첫번째 차일드윈도우"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
		CRect(40, 40, 250, 200),
		this,
		1010);
	ASSERT(m_Wnd01.m_hWnd != NULL);

	m_Wnd02.Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW),
		_T("두번째 차일드윈도우"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CHILD,
		CRect(350, 50, 540, 250),
		this,
		1020);
	m_ProgressBar.Create(WS_DLGFRAME | WS_VISIBLE, CRect(50, 230, 290, 270), this, ID_PROGBAR);
	m_ProgressBar.SetRange(0, 10);
	m_ProgressBar.SetPos(1);

	m_Increase_Btn.Create(_T("추가"), WS_VISIBLE, CRect(400, 300, 550, 330),
		this, ID_INCREASE_BUTTON);
	m_Decrease_Btn.Create(_T("감소"), WS_VISIBLE, CRect(400, 350, 550, 380),
		this, ID_DECREASE_BUTTON);
	m_ListBox.Create(WS_DLGFRAME | WS_VISIBLE, CRect(50, 300, 300, 500),
		this, ID_LISTBOX);
	m_ListBox.AddString(_T("윈도우 프로그래밍 !"));
	return 0;
}

void CSDIView::OnDecreaseButton()
{
	TRACE0("CSDIView::OnDecreaseButton\n");
	int count = m_ListBox.GetCount();

	if (count > 0)
	{
		m_ListBox.DeleteString(count - 1);
		m_ProgressBar.SetPos(count - 1);
	}
	else
	{
		AfxMessageBox(_T("지울 아이템이 없습니다"));
	}

}

void CSDIView::OnIncreaseButton()
{
	TRACE0("CSDIView::OnIncreaseButton\n");
	int count = m_ListBox.GetCount();

	if (count < 10)
	{
		CString s;
			s.Format( _T("윈도우 프로그래밍 ! %d"), count);
		m_ListBox.AddString(s);
		//m_ListBox.AddString(_T("윈도우 프로그래밍 !"));
		m_ProgressBar.SetPos(count + 1);
	}
	else
	{
		AfxMessageBox(_T("더이상 추가할 수 없습니다"));
	}
}
