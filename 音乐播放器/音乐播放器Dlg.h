#pragma once
#include<mmsystem.h>//��ý���豸�ӿ�
#include<Digitalv.h>//��������
#include "afxcmn.h"
#pragma comment(lib,"Winmm.lib")//���Ӿ�̬���ļ�


// C���ֲ�����Dlg �Ի���
class C���ֲ�����Dlg : public CDialogEx
{
// ����
public:
	C���ֲ�����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	MCIDEVICEID m_DeviceID;//��¼����

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedStop();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	
	CSliderCtrl m_slider;
	int m_nVolume;
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
};
