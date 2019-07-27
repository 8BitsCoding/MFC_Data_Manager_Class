
// MFCApplication3Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "MFCApplication3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3Dlg 대화 상자



CMFCApplication3Dlg::CMFCApplication3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCApplication3Dlg 메시지 처리기

BOOL CMFCApplication3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication3Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/* // CPtrArray 방식
		POINT * p;
		int count = m_pos_list.GetCount();

		for (int i = 0; i < count; i++) {
			p = (POINT*)m_pos_list.GetAt(i);
			if (p != NULL) {
				dc.Rectangle(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
			}
		}
		*/

		// CPtrList  방식
		POINT * p;
		POSITION pos = m_pos_list.GetHeadPosition();
		while (pos != NULL) {
			p = (POINT*)m_pos_list.GetNext(pos);
			dc.Rectangle(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
		}
		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT * p = new POINT;
	p->x = point.x;
	p->y = point.y;

	// CPtrList 방식
	m_pos_list.AddTail(p);

	// CPtrArray 방식
	// m_pos_list.Add(p);

	CClientDC dc(this);
	dc.Rectangle(point.x - 10, point.y - 10, point.x + 10, point.y + 10);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication3Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	/* // CPtrArray 방식
	POINT* p;
	int count = m_pos_list.GetCount();
	CRect r;

	for (int i = 0; i < count; i++) {
		p = (POINT*)m_pos_list.GetAt(i);
		if (p != NULL) {
			r.SetRect(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
			if (r.PtInRect(point)) {
				// 내부에 있음
				delete p;
				m_pos_list.SetAt(i, NULL);
				// delete를 해도 뒤에 주소가 앞으로 당겨지지 않기에 NULL을 넣어줘야함!
				Invalidate();
				break;
			}
		}
	}
	*/

	// CPtrList 방식
	POINT * p;
	POSITION pos = m_pos_list.GetHeadPosition(), check_pos;
	CRect r;
	while (pos != NULL) {
		check_pos = pos;
		p = (POINT*)m_pos_list.GetNext(pos);
		if (p != NULL) {
			r.SetRect(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
			if (r.PtInRect(point)) {
				delete p;
				m_pos_list.RemoveAt(check_pos);
				Invalidate();
				break;
			}
		}
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CMFCApplication3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	/*  // CPtrArray 방식
	POINT * p;
	int count = m_pos_list.GetCount();
	for (int i = 0; i < count; i++) {
		p = (POINT*)m_pos_list.GetAt(i);
		if(p!=NULL) delete p;
	}
	*/

	// CPtrList 방식
	POINT * p;
	POSITION pos = m_pos_list.GetHeadPosition();
	while (pos != NULL) {
		p = (POINT*)m_pos_list.GetNext(pos);
		delete p;
	}
}
