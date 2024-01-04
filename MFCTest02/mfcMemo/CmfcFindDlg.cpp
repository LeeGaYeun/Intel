#include "pch.h"
#include "framework.h"
#include "mfcMemo.h"
#include "mfcMemoDlg.h"
#include "afxdialogex.h"
#include "CmfcFindDlg.h"

BEGIN_MESSAGE_MAP(CmfcFindDlg, CDialogEx)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CmfcFindDlg::CmfcFindDlg() : CDialogEx(IDD_FND_DIALOG) //"mfcMemo.h"�� resource.h�� ���� / IDD_FND_DIALOG(resource.h)�ʿ�
{

}

void CmfcFindDlg::DoDataExchange(CDataExchange* pDX) //���������� ������
{
	CDialogEx::DoDataExchange(pDX);
}

void CmfcFindDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //����Ű ������ �Է� ����
{
	switch (nChar) 
	{
	case VK_RETURN:
		GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr); //ã�� ���� �Է� �� ���͸� ���� �� mstr�� ����
		GetDlgItem(ID_EDIT_REPLACE)->GetWindowText(mStr2);
		break; //switch�� ����

	case VK_ESCAPE:
		mStr = "";
		mStr2 = "";
		break;

	default:
		break;
	}

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CmfcFindDlg::OnInitDialog() //�ʱ�ȭ �Լ�
{
	CDialogEx::OnInitDialog();

	mStr = "";
	mStr2 = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CmfcFindDlg::PreTranslateMessage(MSG* pMsg) //��� �޽��� ���޵� 
{
	switch (pMsg->message) {

	case WM_KEYDOWN: //OnKeyDown�� ���� ����
		switch (pMsg->wParam) {
		case VK_RETURN: //����Ű
			GetDlgItem(ID_EDIT_FIND)->GetWindowText(mStr);
			GetDlgItem(ID_EDIT_REPLACE)->GetWindowText(mStr2);
			EndDialog(IDOK); //dialog�� return �� ����(IDOK)��
			break;

		case VK_ESCAPE:
			mStr = ""; //��� ���ڿ� �����
			mStr2 = "";
			EndDialog(IDCANCEL);
			break;

		default:
			break;

		}
		break;

	default: //keydown ���� �����
		break;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
