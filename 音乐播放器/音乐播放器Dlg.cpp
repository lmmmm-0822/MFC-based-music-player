#include "stdafx.h"
#include "���ֲ�����.h"
#include "���ֲ�����Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C���ֲ�����Dlg �Ի���
C���ֲ�����Dlg::C���ֲ�����Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C���ֲ�����Dlg::IDD, pParent)
	, m_nVolume(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C���ֲ�����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_EDIT1, m_nVolume);
}

BEGIN_MESSAGE_MAP(C���ֲ�����Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &C���ֲ�����Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_PLAY, &C���ֲ�����Dlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_PAUSE, &C���ֲ�����Dlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_STOP, &C���ֲ�����Dlg::OnBnClickedStop)
	ON_WM_DROPFILES()
	
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &C���ֲ�����Dlg::OnCustomdrawSlider1)
END_MESSAGE_MAP()


// C���ֲ�����Dlg ��Ϣ�������

BOOL C���ֲ�����Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	m_slider.SetRange(0,1000);
	m_slider.SetPos(500);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C���ֲ�����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CPaintDC dc(this);
		//��ȡ�ͻ��˿��
		CRect rect;
		GetClientRect(&rect);

		//����һ��ͼƬ
		CBitmap bmp;
		bmp.LoadBitmap(IDB_MAIN_BJ);
		

		//��ȡͼƬ��С
		BITMAP logBmp;
		bmp.GetBitmap(&logBmp);

		//�����ڴ�DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject(&bmp);
		//���Ƶ�����
		//dc.BitBlt(0, 0, rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
		dc.SetStretchBltMode(HALFTONE);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0,
			logBmp.bmWidth, logBmp.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C���ֲ�����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



////��
void C���ֲ�����Dlg::OnBnClickedOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);
	dlg.DoModal();

	//��ȡѡ����ļ���·��
	CString strmusicPath = dlg.GetPathName();

	//��ʾ�ļ���
	CString strFilename = dlg.GetFileName();
	SetDlgItemText(IDC_FILENAME, strFilename);


	//1. �ر���һ������
	//��ý���豸�ӿڣ�MCI��
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);


	//2. �������ļ�
	MCI_OPEN_PARMS mciopenparms;
	mciopenparms.lpstrElementName = strmusicPath;
	MCIERROR mciError;
	mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&mciopenparms);
	if (mciError)//mciErrorΪ��ʱ��˵����ʧ��
	{
		wchar_t szErrorMsg[256];
		mciGetErrorString(mciError, szErrorMsg, 256);//��ȡ������Ϣ
		AfxMessageBox(szErrorMsg);//����������Ϣ
		return;
	}
	m_DeviceID = mciopenparms.wDeviceID;//
}


////����
void C���ֲ�����Dlg::OnBnClickedPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MCI_PLAY_PARMS mcipalyparms;
	mcipalyparms.dwCallback = NULL;
	mcipalyparms.dwFrom = 0;//��ͷ��ʼ����
	mciSendCommand(m_DeviceID, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)&mcipalyparms);
}


////��ͣ/����
void C���ֲ�����Dlg::OnBnClickedPause()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_PAUSE, str);
	if (str == L"��ͣ")
	{
		mciSendCommand(m_DeviceID, MCI_PAUSE, 0, 0);
		SetDlgItemText(IDC_PAUSE, L"����");
	}
	else if (str == L"����")
	{
		mciSendCommand(m_DeviceID, MCI_RESUME, 0, 0);
		SetDlgItemText(IDC_PAUSE, L"��ͣ");
	}
}


////ֹͣ
void C���ֲ�����Dlg::OnBnClickedStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	mciSendCommand(m_DeviceID, MCI_STOP, 0, 0);
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);
}



void C���ֲ�����Dlg::OnDropFiles(HDROP hDropInfo)
{
	// ��ȡ��ק�ļ���·��
	wchar_t szMusicPath[256];
	DragQueryFile(hDropInfo, 0, szMusicPath, 256);
	//AfxMessageBox(szMusicPath);


	//1. �ر���һ������
	//��ý���豸�ӿڣ�MCI��
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);


	//2. �������ļ�
	MCI_OPEN_PARMS mciopenparms;
	mciopenparms.lpstrElementName = szMusicPath;
	MCIERROR mciError;
	mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&mciopenparms);
	if (mciError)//mciErrorΪ��ʱ��˵����ʧ��
	{
		wchar_t szErrorMsg[256];
		mciGetErrorString(mciError, szErrorMsg, 256);//��ȡ������Ϣ
		AfxMessageBox(szErrorMsg);//����������Ϣ
		return;
	}
	m_DeviceID = mciopenparms.wDeviceID;

	//��ʾ�ļ���
	CString strFilename = szMusicPath;
	strFilename = strFilename.Mid(strFilename.ReverseFind('\\') + 1, ((strFilename.ReverseFind('.') - strFilename.ReverseFind('\\')) - 1));
	DragFinish(hDropInfo);
	SetDlgItemText(IDC_FILENAME, strFilename);


	CDialogEx::OnDropFiles(hDropInfo);
}




void C���ֲ�����Dlg::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�����ռ䵱ǰֵ
	m_nVolume =0.1* m_slider.GetPos();
	UpdateData(FALSE);
	
	MCI_DGV_SETAUDIO_PARMS mciSetvolume;
	mciSetvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetvolume.dwValue = m_nVolume;

	mciSendCommand(m_DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)&mciSetvolume);

	*pResult = 0;
}
