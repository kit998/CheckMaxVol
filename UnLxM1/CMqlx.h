#pragma once

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef _LK_QUOTE
#define _LK_QUOTE
struct QUOTE
{
	char CurrentDate[11];
	char CurrentTime[11];
	float Open ;
	float High ;
	float Low ;
	float Close;
	double Volume ;
	double Amount ;
} ;
struct CvtDate
{
	char BeginDate[11];
	char EndDate[11];
	char ContractName[15];
} ;

#endif 

#ifndef _LK_CMqlx
#define _LK_CMqlx
class CMqlx
{
public:
	//QUOTE m_Quote;
	CString m_strDestFile, m_strCvtFile ;

	map<CString,CPtrArray*> CodeBook ;
	CPtrArray m_pCvt;
	CPtrArray m_pDest;
	CMqlx(CString strIniFileName);

	float m_AdjustValue, m_AdjustValue1 ;
	float m_LowestClose ;

	int PrintQuotes();
	int PrintQuotes ( CPtrArray &pArrayQuote ) ;
	int fPrintQuotes ( CPtrArray &pArrayQuote ) ;
	int fPrintQuotesGMT ( CPtrArray &pArrayQuote ) ;
	int ReadQuotes( CString strFilename, CPtrArray &pArrayQuote ) ;
	int ReadCvtDate( CString strFilename, CPtrArray &pCvt ) ;
	int	ChangeDateFormat ( QUOTE *pQuote ) ;

	int GenLxQuotes( CPtrArray &pArrayQuote );
	int GetAdjustValue(CvtDate *pCvtDate1,CvtDate *pCvtDate2);
	int GetQuotes(CvtDate *pCvtDate, CPtrArray &pArrayQuote );
	int AdjustQuotes( CPtrArray &pArrayQuote );
	int EndAdjustQuotes( CPtrArray &pArrayQuote );
	int GetLowestClose(CPtrArray &pArrayQuote ) ;


	int PrintCvt();
	int FindMaxVol(void);
	int GetDateQuotes(QUOTE* q1, CString ContractName);
};

#endif 



