#include "stdafx.h"
#include "CMqlx.h"


CMqlx::CMqlx(CString strIniFileName)
{
	cout<<"This is CMqlx Construction Fuction."<<endl;
	cout<<"IniFileName = "<<strIniFileName<<endl;
	int TOTALCONTRACT ;

		// 读入初始化文件的数据

	FILE *fpIni=fopen(strIniFileName,"rt") ;
	if (fpIni==NULL){
		cout<<"Open Ini file "<<strIniFileName<<" Error."<<endl;
		return ;
	}

	char buf[128] ;
	CString strContractFile ;
	typedef pair <CString,CPtrArray*> StrPtr_Pair;

	fscanf ( fpIni,"%s",buf ) ;
	m_strDestFile = CString("\\txtday\\")+buf ;
	fscanf ( fpIni,"%s",buf ) ;
	m_strCvtFile = buf ;

	fscanf ( fpIni,"%d", &TOTALCONTRACT) ;
	cout << "TOTALCONTRACT = "<<TOTALCONTRACT<<endl ;

	map<CString,CPtrArray*> &cb = CodeBook ;

	for ( int i=0; i<TOTALCONTRACT; i++ )
	{
		fscanf ( fpIni,"%s",buf ) ;
        strContractFile =  CString("\\txtday\\")+buf+".txt" ;
		CPtrArray *pAQ1= new CPtrArray() ;
		ReadQuotes(strContractFile,*pAQ1);
		cb.insert(StrPtr_Pair(buf,pAQ1)) ;
		cout <<"合约 = "<<buf<<endl ;
	}

	ReadCvtDate(m_strCvtFile,m_pCvt);

	return ;
}

int CMqlx::PrintQuotes()
{
	cout<<"This is PrintQuotes Fuction."<<endl;

	return 0;
}

int CMqlx::ReadCvtDate( CString strFilename, CPtrArray &pCvt ) 
{
	FILE *fpcvtin = fopen ( strFilename, "rt" ) ;
	if (fpcvtin==NULL){
		cout<<"Open CVT file "<<m_strCvtFile<<" Error."<<endl;
		return 1;
	}

	CvtDate *pQuote ;

	while ( !feof( fpcvtin ) ) 

	{
		pQuote = new CvtDate() ;

		fscanf ( fpcvtin, "%s %s %s", pQuote->BeginDate,
			pQuote->EndDate, pQuote->ContractName ) ;

		if (strcmp (pQuote->EndDate, pQuote->BeginDate ) != 0)
		{
			//printf ( "%s %s %s \n", pQuote->BeginDate, pQuote->EndDate, pQuote->ContractName ) ;
			//ChangeDateFormat ( pQuote ) ;
			pCvt.Add ( pQuote ) ;
		}
	}
	return 0 ;
}

int CMqlx::ReadQuotes ( CString strFilename, CPtrArray &pArrayQuote )
{

	FILE *fpin ;
	QUOTE *pQuote ;

	fpin = fopen ( strFilename, "rt" ) ;

	if (fpin==NULL){
		cout<<"Open file "<<strFilename<<" Error."<<endl;
		return 1;
	}

	while ( ! feof ( fpin ) )
	{
		pQuote = new QUOTE() ;

		fscanf( fpin, "%s %f %f %f %f %lf %lf",
			pQuote->CurrentDate, /*pQuote->CurrentTime, */
			&pQuote->Open, &pQuote->High, &pQuote->Low, &pQuote->Close,
			&pQuote->Volume, &pQuote->Amount ) ;

		if (strcmp ("", pQuote->CurrentDate ) != 0)
		{
			//ChangeDateFormat ( pQuote ) ;
			pArrayQuote.Add ( pQuote ) ;
		}
	}

	fclose ( fpin ) ;
	return 0 ;
}


int CMqlx::PrintQuotes ( CPtrArray &pArrayQuote )
{

	INT_PTR nCount ;

	nCount = pArrayQuote.GetCount ( ) ;
	for ( int i=0; i<nCount; i++ )
	{
		printf ( "%s %.4f %.4f %.4f %.4f %.4lf %.4lf\n",
			((QUOTE *)pArrayQuote[i])->CurrentDate, 
			/*((QUOTE *)pArrayQuote[i])->CurrentTime, */
			((QUOTE *)pArrayQuote[i])->Open, ((QUOTE *)pArrayQuote[i])->High, 
			((QUOTE *)pArrayQuote[i])->Low, ((QUOTE *)pArrayQuote[i])->Close,
			((QUOTE *)pArrayQuote[i])->Volume, ((QUOTE *)pArrayQuote[i])->Amount ) ;
	}
	return 0 ;
}

int CMqlx::fPrintQuotes ( CPtrArray &pArrayQuote )
{
	FILE *fpout ;

	fpout = fopen ( m_strDestFile, "wt" ) ;

	if (fpout==NULL){
		cout<<"Open file "<<m_strDestFile<<" Error."<<endl;
		return 1;
	}

	INT_PTR nCount ;

	nCount = pArrayQuote.GetCount ( ) ;
	for ( int i=0; i<nCount; i++ )
	{
		fprintf (fpout, "%s %.4f %.4f %.4f %.4f %.4lf %.4lf\n",
			((QUOTE *)pArrayQuote[i])->CurrentDate, 
			/*((QUOTE *)pArrayQuote[i])->CurrentTime, */
			((QUOTE *)pArrayQuote[i])->Open, ((QUOTE *)pArrayQuote[i])->High, 
			((QUOTE *)pArrayQuote[i])->Low, ((QUOTE *)pArrayQuote[i])->Close,
			((QUOTE *)pArrayQuote[i])->Volume, ((QUOTE *)pArrayQuote[i])->Amount ) ;
	}
	fclose ( fpout ) ;

	return 0 ;
}


int CMqlx::fPrintQuotesGMT ( CPtrArray &pArrayQuote )
{
	FILE *fpout ;

	fpout = fopen ( m_strDestFile, "wt" ) ;

	if (fpout==NULL){
		cout<<"Open file "<<m_strDestFile<<" Error."<<endl;
		return 1;
	}

	INT_PTR nCount ;
	CTime time1 ;
	CTimeSpan ts(8*3600);			//60秒的时间片
	CString strDate, strTime;

	nCount = pArrayQuote.GetCount ( ) ;
	for ( int i=0; i<nCount; i++ )
	{
		strTime = ((QUOTE *)pArrayQuote[i])->CurrentTime;
		time1 =  CTime::CTime(2009,4,15,atoi(strTime.Left(2)),atoi(strTime.Right(2)),0) - ts; 

		fprintf (fpout, "%s %s %.4f %.4f %.4f %.4f %.4lf %.4lf\n",
			((QUOTE *)pArrayQuote[i])->CurrentDate, 
			//((QUOTE *)pArrayQuote[i])->CurrentTime, 
			time1.Format("%H:%M:%S"),
			((QUOTE *)pArrayQuote[i])->Open, ((QUOTE *)pArrayQuote[i])->High, 
			((QUOTE *)pArrayQuote[i])->Low, ((QUOTE *)pArrayQuote[i])->Close,
			((QUOTE *)pArrayQuote[i])->Volume, ((QUOTE *)pArrayQuote[i])->Amount ) ;
	}
	fclose ( fpout ) ;

	return 0 ;
}


int CMqlx::GenLxQuotes(CPtrArray &pArrayQuote)
{
	INT_PTR nCount ;

	nCount = m_pCvt.GetCount ( ) ;
	for ( int i=0; i<nCount; i++ )
	{
		CPtrArray pAQ2;

		if (0==i){
			GetQuotes((CvtDate *)m_pCvt[i], pAQ2 );
			pArrayQuote.Append( pAQ2 );
			m_AdjustValue = 0.0 ;
			m_AdjustValue1 = 0.0 ;
			GetLowestClose(pArrayQuote);
		}
		else {
			GetAdjustValue((CvtDate *)m_pCvt[i-1],(CvtDate *)m_pCvt[i]);
			GetQuotes((CvtDate *)m_pCvt[i], pAQ2 );
			AdjustQuotes(pAQ2);
			pArrayQuote.Append( pAQ2 );
		
		}
	}
	EndAdjustQuotes(pArrayQuote);

	return 0 ;

}

int CMqlx::GetAdjustValue(CvtDate *pCvtDate1,CvtDate *pCvtDate2)
{
	char (&n1)[15]=pCvtDate1->ContractName ;
	char (&n2)[15]=pCvtDate2->ContractName ;
	cout<<" Name1 = "<<n1  ; 
	cout<<" Name2 = "<<n2 <<endl ; 
	map<CString,CPtrArray*> &b = CodeBook ;
	CPtrArray &pAQ1=*(b[n1]) ;
	CPtrArray &pAQ2=*(b[n2]) ;

	bool IsFound1=false;
	bool IsFound2=false;
	INT_PTR i,j,nCount1,nCount2 ;
	nCount1 = pAQ1.GetCount ( ) ;
	cout<<" Count1 = "<< nCount1 ; 
	for ( i=0; i<nCount1; i++ )
	{
		char (&dt)[11]=((QUOTE *)pAQ1[i])->CurrentDate ;
		if ((strcmp( dt, pCvtDate1->EndDate )==0)){
			IsFound1 = true ;
			break ;
		}
	}
	nCount2 = pAQ2.GetCount ( ) ;
	cout<<" Count2 = "<< nCount2<<endl ; 
	for ( j=0; j<nCount2; j++ )
	{
		char (&dt)[11]=((QUOTE *)pAQ2[j])->CurrentDate ;
		if ((strcmp( dt, pCvtDate2->BeginDate )==0)){
			IsFound2 = true ;
			break ;
		}
	}
	if (IsFound1 && IsFound2 && (strcmp( pCvtDate2->BeginDate, pCvtDate1->EndDate )==0))
	{
		m_AdjustValue += ((QUOTE *)pAQ1[i])->Close - ((QUOTE *)pAQ2[j])->Close ;
		cout<<" m_AdjustValue = "<< m_AdjustValue<<endl ; 
	}
	else {
		cout<<" Can't found equal point\a "<< endl ;
		char c=getchar();
	}
	return 0 ;
}

int CMqlx::GetQuotes(CvtDate *pCvtDate, CPtrArray &pArrayQuote )
{
	cout<<"BeginDate = "<<pCvtDate->BeginDate ; 
	cout<<" EndDate = "<<pCvtDate->EndDate <<endl; 
	//cout<<" Name = "<<pCvtDate->ContractName  ; 

	char (&n)[15]=pCvtDate->ContractName ;
	cout<<" Name = "<<n ; 
	map<CString,CPtrArray*> &b = CodeBook ;
	CPtrArray &pAQ=*(b[n]) ;

	INT_PTR nCount ;
	nCount = pAQ.GetCount ( ) ;
	cout<<" Count = "<< nCount<<endl ; 
	for ( int i=0; i<nCount; i++ )
	{
/*
		QUOTE* q=((QUOTE *)pAQ[i]);
		QUOTE* &q1=q;
		cout<<q1->CurrentDate <<endl;
*/
		char (&dt)[11]=((QUOTE *)pAQ[i])->CurrentDate ;
		if ((strcmp( dt, pCvtDate->BeginDate )>=0) &&
			(strcmp( dt, pCvtDate->EndDate )<0))
			pArrayQuote.Add (pAQ[i]);
		else if (strcmp( dt, pCvtDate->EndDate )>=0)
			break ;

	}

	return 0 ;
}

int CMqlx::GetLowestClose(CPtrArray &pArrayQuote )
{
	INT_PTR nCount ;
	
	nCount = pArrayQuote.GetCount ( ) ;
	if (nCount>0){
		m_LowestClose = ((QUOTE *)pArrayQuote[0])->Close ;

		for ( int i=0; i<nCount; i++ )
		{
			if(((QUOTE *)pArrayQuote[i])->Close<m_LowestClose){
				m_LowestClose = ((QUOTE *)pArrayQuote[i])->Close ;
			}
		}
	}
	else
		m_LowestClose = 0.0 ;

	cout<<" m_LowestClose = "<< m_LowestClose<<endl ; 
	return 0 ;
}

int CMqlx::AdjustQuotes( CPtrArray &pArrayQuote )
{
	INT_PTR nCount ;
	
	nCount = pArrayQuote.GetCount ( ) ;

	for ( int i=0; i<nCount; i++ )
	{
		((QUOTE *)pArrayQuote[i])->Open	 += m_AdjustValue;
		((QUOTE *)pArrayQuote[i])->High  += m_AdjustValue;
		((QUOTE *)pArrayQuote[i])->Low   += m_AdjustValue;
		((QUOTE *)pArrayQuote[i])->Close += m_AdjustValue;

		if(((QUOTE *)pArrayQuote[i])->Close<m_LowestClose){
			m_LowestClose = ((QUOTE *)pArrayQuote[i])->Close ;
			m_AdjustValue1 = m_AdjustValue ;
		}
	}

	cout<<" m_LowestClose = "<< m_LowestClose ; 
	cout<<" m_AdjustValue1 = "<< m_AdjustValue1<<endl ; 

	return 0 ;
}

int CMqlx::EndAdjustQuotes( CPtrArray &pArrayQuote )
{
	INT_PTR nCount ;
	
	nCount = pArrayQuote.GetCount ( ) ;

	for ( int i=0; i<nCount; i++ )
	{
		((QUOTE *)pArrayQuote[i])->Open	 -= m_AdjustValue1;
		((QUOTE *)pArrayQuote[i])->High  -= m_AdjustValue1;
		((QUOTE *)pArrayQuote[i])->Low   -= m_AdjustValue1;
		((QUOTE *)pArrayQuote[i])->Close -= m_AdjustValue1;
	}

	cout<<" Total nCount = "<< nCount <<endl; 
	cout<<" Genrate End." <<endl; 

	return 0 ;
}

int	CMqlx::ChangeDateFormat ( QUOTE *pQuote ) 
{
	pQuote->CurrentDate[4] = pQuote->CurrentDate[7] = '-' ;

	return 0 ;
}



/*
int MergeItop30 ( CPtrArray &pa1, CPtrArray &pa2 )
{

	int nFirst = 0 ;

	INT_PTR nCount1, nCount2 ;

	nCount1 = pa1.GetCount ( ) ;
	nCount2 = pa2.GetCount ( ) ;

	for ( int i=0; i<nCount2; i++ )
	{
		for ( int j=nFirst; j<nCount1; j++ ) 
			if ( strcmp ( ((QUOTE *)pa1[j])->CurrentDate, ((ITOP30 *)pa2[i])->CurrentDate ) == 0 )
			{
				((QUOTE *)pa1[j])->Loi += ((ITOP30 *)pa2[i])->Loi;
				((QUOTE *)pa1[j])->Soi += ((ITOP30 *)pa2[i])->Soi ;
				nFirst = j ;

				//cout << "i="<<i<<"j="<<j<<" "<<((ITOP30 *)pa2[i])->CurrentDate <<" "<< ((QUOTE *)pa1[j])->Soi<< endl ;
				break ;
			}		
		
	}
	return 0 ;

}

int fPrintQuotes ( CString strFilename, CPtrArray &pArrayQuote )
{
	FILE *fpout ;

	fpout = fopen ( strFilename, "wt" ) ;

	INT_PTR nCount = pArrayQuote.GetCount ( ) ;

	for ( int i=0; i<nCount; i++ )
	{
		fprintf ( fpout, "%s %u %u %u %u %.2lf %.2lf\n", ((QUOTE *)pArrayQuote[i])->CurrentDate, 
			((QUOTE *)pArrayQuote[i])->Open, ((QUOTE *)pArrayQuote[i])->High, 
			((QUOTE *)pArrayQuote[i])->Low, ((QUOTE *)pArrayQuote[i])->Close,
			((QUOTE *)pArrayQuote[i])->Volume, ((QUOTE *)pArrayQuote[i])->Amount ) ;
	}
	fclose ( fpout ) ;
	return 0 ;
}

int ReadItop30 ( CString strFilename, CPtrArray &pArrayItop30 )
{

	FILE *fpin ;
	ITOP30 *pItop30 ;

	fpin = fopen ( strFilename, "rt" ) ;

	while ( ! feof ( fpin ) )
	{
		pItop30 = new ITOP30() ;

		fscanf( fpin, "%10s,%u,%u", pItop30->CurrentDate, 
			&pItop30->Loi, &pItop30->Soi ) ;

		if (strcmp ("", pItop30->CurrentDate ) != 0)
			pArrayItop30.Add ( pItop30 ) ;

	}

	fclose ( fpin ) ;
	return 0 ;
}

int PrintItop30 ( CPtrArray &pArrayItop30 )
{

	INT_PTR nCount ;

	nCount = pArrayItop30.GetCount ( ) ;
	for ( int i=0; i<nCount; i++ )
	{
		printf ( "%s,%u,%u\n", ((ITOP30 *)pArrayItop30[i])->CurrentDate, 
			((ITOP30 *)pArrayItop30[i])->Loi, ((ITOP30 *)pArrayItop30[i])->Soi ) ;
	}
	return 0 ;
}

int fPrintItop30 ( CString strFilename, CPtrArray &pArrayQuote )
{
	FILE *fpout ;

	fpout = fopen ( strFilename, "wt" ) ;

	INT_PTR nCount ;

	nCount = pArrayQuote.GetCount ( ) ;
	for ( int i=0; i<nCount; i++ )
	{
		fprintf ( fpout, "%s,%u,%u\n", ((QUOTE *)pArrayQuote[i])->CurrentDate, 
			((QUOTE *)pArrayQuote[i])->Loi, ((QUOTE *)pArrayQuote[i])->Soi ) ;
	}
	fclose ( fpout ) ;
	return 0 ;
}
*/
int CMqlx::PrintCvt()
{
	INT_PTR nCount ;

	nCount = m_pCvt.GetCount ( ) ;
	for ( int i=0; i<nCount; i++ )
	{


		cout<<((CvtDate *)m_pCvt[i])->BeginDate<<" ";
		cout<<((CvtDate *)m_pCvt[i])->EndDate<<" ";

		cout<<((CvtDate *)m_pCvt[i])->ContractName<<endl;
	}

	return 0;
}

int CMqlx::FindMaxVol(void)
{
	INT_PTR nCvtCount ;

	nCvtCount = m_pCvt.GetCount ( ) ;

	CvtDate * pCvtDate ;

	pCvtDate = (CvtDate *)m_pCvt[nCvtCount-1] ;

	cout<<"BeginDate = "<<pCvtDate->BeginDate ; 
	cout<<" EndDate = "<<pCvtDate->EndDate <<endl; 
	//cout<<" Name = "<<pCvtDate->ContractName  ; 

	char (&n)[15]=pCvtDate->ContractName ;
	cout<<" Name = "<<n<<endl ; 
	map<CString,CPtrArray*> &b = CodeBook ;
	map<CString,CPtrArray*> :: iterator pIter;

	CPtrArray &pAQ=*(b[n]) ;
	INT_PTR nCount ;
	nCount = pAQ.GetCount ( ) ;
	cout<<" Count = "<< nCount<<endl ; 
	for ( int i=0; i<nCount; i++ )
	{
		char (&dt)[11]=((QUOTE *)pAQ[i])->CurrentDate ;
		if ((strcmp( dt, pCvtDate->BeginDate )>0) )
			for ( pIter = b.begin( ); pIter != b.end( ); pIter++ )
				if (1==GetDateQuotes((QUOTE *)pAQ[i],pIter->first))
				{
					//cout<<"有新的主力合约= "<<pIter->first<<endl;
					i = nCount ;
					break ;
				}
	}

	return 0;
}

int CMqlx::GetDateQuotes(QUOTE* q1, CString ContractName)
{
	//cout<<"In GetDateQuotes,"<<"QueryDate= "<<q1->CurrentDate;
	//cout<<" ContractName= "<<ContractName<<endl;

	map<CString,CPtrArray*> &b = CodeBook ;
	CPtrArray &pAQ=*(b[ContractName]) ;

	int nRetCode=0 ;
	INT_PTR nCount ;
	nCount = pAQ.GetCount ( ) ;
	//cout<<" Count = "<< nCount<<endl ; 
	for ( int i=0; i<nCount; i++ )
	{

//		QUOTE* q=((QUOTE *)pAQ[i]);
//		QUOTE* &q1=q;
//		cout<<q1->CurrentDate <<endl;

		char (&dt)[11]=((QUOTE *)pAQ[i])->CurrentDate ;
		if ((strcmp( dt, q1->CurrentDate )==0) &&
			((QUOTE *)pAQ[i])->Volume > q1->Volume)
			//pArrayQuote.Add (pAQ[i]);
		{
			cout<<"新主力合约= "<<ContractName;

			cout<<" Date= "<<q1->CurrentDate;

			cout<<" Find OldVol="<<q1->Volume
				<<" NewVol="<<((QUOTE *)pAQ[i])->Volume <<endl;
			nRetCode = 1 ;
			break ;
		}

	}

return nRetCode;
}
