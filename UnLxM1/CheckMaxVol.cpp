// UnLxM1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CheckMaxVol.h"
#include "CMqlx.h"


// 唯一的应用程序对象

CWinApp theApp;


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
		return nRetCode;
	}
	// TODO: 在此处为应用程序的行为编写代码。
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
