// UnLxM1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CheckMaxVol.h"
#include "CMqlx.h"


// Ψһ��Ӧ�ó������

CWinApp theApp;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
		nRetCode = 1;
		return nRetCode;
	}
	// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
    if ( argc<2 ) {cout<<"Usage: CheckMaxVol file.ini"<<endl;return 1;}

	CMqlx Mqlx(argv[1]);
	//CPtrArray *pAQ1= new CPtrArray() ;
	CPtrArray pAQ2;
	//Mqlx.ReadQuotes("\\txtmin1\\DQAX01.TXT",*pAQ1);
	//Mqlx.PrintQuotes (*(Mqlx.CodeBook["DQAX09"])) ;
	//pAQ2.Append(*(Mqlx.CodeBook["DQAX01"]));
	//pAQ2.Append(*(Mqlx.CodeBook["DQAX03"]));
	//Mqlx.GenLxQuotes(pAQ2);
	//Mqlx.fPrintQuotes (pAQ2) ;
	//Mqlx.PrintCvt () ;

	Mqlx.FindMaxVol();

	return nRetCode;
	//
}
