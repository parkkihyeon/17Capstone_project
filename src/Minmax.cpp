/////////////////////////////////////////////////////////////////////////////
// JKStage.cpp: implementation of the CJKStage class.
//
//////////////////////////////////////////////////////////////////////
//#include "stdafx.h"
#include "Minmax.h"

#define BEGINING_DEPTH_LEVEL 1
#define MIDDLE_DEPTH_LEVEL 2
#define END_DEPTH_LEVEL 2

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;

//#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int CJKStage::sm_nTotalNode;
// Heuristic flags
int CJKStage::sm_nCutOffDepth;
int CJKStage::sm_nFeedOverDepth;
bool CJKStage::sm_bPoBeforeJang;
bool CJKStage::sm_bGatherJol;
bool CJKStage::sm_bAggressivePO;
bool CJKStage::sm_bAggressiveCHA;
bool CJKStage::sm_bAggressiveJOL;
bool CJKStage::sm_bAggressiveSANG;
bool CJKStage::sm_bAggressiveMA;
bool CJKStage::sm_bOnlyJangCenter;
CHistoryStack CJKStage::sm_cHistoryStack;

void CJKStage::testprint() {
	for (int i = 0; i < DF_PANEL_HEIGHT; i++) {
		for (int j = 0; j < DF_PANEL_WIDTH; j++) {

			//std::cout << m_enPanel[i][j] << "   ";
			switch (m_enPanel[i][j])
			{
			case PS_CHO_JANG:
				std::cout << "CK" << " " << j << i << "  ";
				break;
			case PS_CHO_CHA:
				std::cout << "CC" << " " << j << i << "  ";
				break;
			case PS_CHO_MA:
				std::cout << "CM" << " " << j << i << "  ";
				break;
			case PS_CHO_SANG:
				std::cout << "CX" << " " << j << i << "  ";
				break;
			case PS_CHO_PO:
				std::cout << "CP" << " " << j << i << "  ";
				break;
			case PS_CHO_SA:
				std::cout << "CS" << " " << j << i << "  ";
				break;
			case PS_CHO_JOL:
				std::cout << "CJ" << " " << j << i << "  ";
				break;
			case PS_HAN_JANG:
				std::cout << "HK" << " " << j << i << "  ";
				break;
			case PS_HAN_CHA:
				std::cout << "HC" << " " << j << i << "  ";
				break;
			case PS_HAN_MA:
				std::cout << "HM" << " " << j << i << "  ";
				break;
			case PS_HAN_SANG:
				std::cout << "HX" << " " << j << i << "  ";
				break;
			case PS_HAN_PO:
				std::cout << "HP" << " " << j << i << "  ";
				break;
			case PS_HAN_SA:
				std::cout << "HS" << " " << j << i << "  ";
				break;
			case PS_HAN_JOL:
				std::cout << "HJ" << " " << j << i << "  ";
				break;
			case PS_NOTHING:
				std::cout << "--" << " " << j << i << "  ";
				break;

			default:
				break;
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}


CJKStage::CJKStage()
{
	//fprintf(fp1, "%s", "CJKStage()\n");
	//printf("CJKSTAGE\n");
	Initialize();
	//fprintf(fp, "%s", "CJKStage()end\n");
}

CJKStage::CJKStage(CJKStage * pParentStage)
{
	//fprintf(fp1, "%s", "CJKStage(CJKStage....)\n");
	//printf("CJKStage(CJKStage)\n");
	m_pParent = pParentStage;
	m_nNodeCount = 0;
	m_pFirst = NULL;
	m_pLast = NULL;
	m_nDepth = pParentStage->m_nDepth + 1;
	m_enTeam = pParentStage->m_enTeam == TM_HAN ? TM_CHO : TM_HAN;
	m_bAmIMax = !pParentStage->IsMaxTurn();
	::memcpy(m_enPanel, pParentStage->m_enPanel, sizeof(m_enPanel));
}

CJKStage::~CJKStage()
{
	//fprintf(fp1, "%s", "~SJKStage()\n");
	//printf("~SJKStage()\n");
	ClearList();


}

void CJKStage::Initialize()
{
	//std::cout << "Ƚ��" << std::endl;
	//fprintf(fp1, "%s", "CJKStage::Initialize()\n");
	//printf ("CJKStage::Initialize()\n");
	m_pParent = NULL;
	m_nNodeCount = 0;
	m_pFirst = NULL;

	ClearList();

	::memset(m_enPanel, PS_NOTHING, sizeof(m_enPanel));
	
	/*switch (select)
	{
	case 1:
		m_enPanel[0][0] = PS_HAN_CHA;
		m_enPanel[0][1] = PS_HAN_SANG;
		m_enPanel[0][2] = PS_HAN_MA;
		m_enPanel[0][3] = PS_HAN_SA;
		m_enPanel[0][5] = PS_HAN_SA;
		m_enPanel[0][6] = PS_HAN_SANG;
		m_enPanel[0][7] = PS_HAN_MA;
		m_enPanel[0][8] = PS_HAN_CHA;
		m_enPanel[1][4] = PS_HAN_JANG;
		m_enPanel[2][1] = PS_HAN_PO;
		m_enPanel[2][7] = PS_HAN_PO;
		m_enPanel[3][0] = PS_HAN_JOL;
		m_enPanel[3][2] = PS_HAN_JOL;
		m_enPanel[3][4] = PS_HAN_JOL;
		m_enPanel[3][6] = PS_HAN_JOL;
		m_enPanel[3][8] = PS_HAN_JOL;
		break;
	case 2:
		m_enPanel[0][0] = PS_HAN_CHA;
		m_enPanel[0][1] = PS_HAN_MA;
		m_enPanel[0][2] = PS_HAN_SANG;
		m_enPanel[0][3] = PS_HAN_SA;
		m_enPanel[0][5] = PS_HAN_SA;
		m_enPanel[0][6] = PS_HAN_SANG;
		m_enPanel[0][7] = PS_HAN_MA;
		m_enPanel[0][8] = PS_HAN_CHA;
		m_enPanel[1][4] = PS_HAN_JANG;
		m_enPanel[2][1] = PS_HAN_PO;
		m_enPanel[2][7] = PS_HAN_PO;
		m_enPanel[3][0] = PS_HAN_JOL;
		m_enPanel[3][2] = PS_HAN_JOL;
		m_enPanel[3][4] = PS_HAN_JOL;
		m_enPanel[3][6] = PS_HAN_JOL;
		m_enPanel[3][8] = PS_HAN_JOL;
		break;
	case 3:
		m_enPanel[0][0] = PS_HAN_CHA;
		m_enPanel[0][1] = PS_HAN_SANG;
		m_enPanel[0][2] = PS_HAN_MA;
		m_enPanel[0][3] = PS_HAN_SA;
		m_enPanel[0][5] = PS_HAN_SA;
		m_enPanel[0][6] = PS_HAN_MA;
		m_enPanel[0][7] = PS_HAN_SANG;
		m_enPanel[0][8] = PS_HAN_CHA;
		m_enPanel[1][4] = PS_HAN_JANG;
		m_enPanel[2][1] = PS_HAN_PO;
		m_enPanel[2][7] = PS_HAN_PO;
		m_enPanel[3][0] = PS_HAN_JOL;
		m_enPanel[3][2] = PS_HAN_JOL;
		m_enPanel[3][4] = PS_HAN_JOL;
		m_enPanel[3][6] = PS_HAN_JOL;
		m_enPanel[3][8] = PS_HAN_JOL;
		break;
	case 4:
		m_enPanel[0][0] = PS_HAN_CHA;
		m_enPanel[0][1] = PS_HAN_MA;
		m_enPanel[0][2] = PS_HAN_SANG;
		m_enPanel[0][3] = PS_HAN_SA;
		m_enPanel[0][5] = PS_HAN_SA;
		m_enPanel[0][6] = PS_HAN_MA;
		m_enPanel[0][7] = PS_HAN_SANG;
		m_enPanel[0][8] = PS_HAN_CHA;
		m_enPanel[1][4] = PS_HAN_JANG;
		m_enPanel[2][1] = PS_HAN_PO;
		m_enPanel[2][7] = PS_HAN_PO;
		m_enPanel[3][0] = PS_HAN_JOL;
		m_enPanel[3][2] = PS_HAN_JOL;
		m_enPanel[3][4] = PS_HAN_JOL;
		m_enPanel[3][6] = PS_HAN_JOL;
		m_enPanel[3][8] = PS_HAN_JOL;
		break;

	}
	if (select2 == 0) {
		std::cout << "������ " << std::endl;
		std::cout << "1 . �󸶻�  ";
		std::cout << "2 . �����  ";
		std::cout << "3 . �󸶸���  ";
		std::cout << "4 . ���󸶻� \n ";
		std::cin >> select2;
	}
	switch (select2) {
	case 1:
		m_enPanel[9][0] = PS_CHO_CHA;
		m_enPanel[9][1] = PS_CHO_SANG;
		m_enPanel[9][2] = PS_CHO_MA;
		m_enPanel[9][3] = PS_CHO_SA;
		m_enPanel[9][5] = PS_CHO_SA;
		m_enPanel[9][6] = PS_CHO_SANG;
		m_enPanel[9][7] = PS_CHO_MA;
		m_enPanel[9][8] = PS_CHO_CHA;
		m_enPanel[8][4] = PS_CHO_JANG;
		m_enPanel[7][1] = PS_CHO_PO;
		m_enPanel[7][7] = PS_CHO_PO;
		m_enPanel[6][0] = PS_CHO_JOL;
		m_enPanel[6][2] = PS_CHO_JOL;
		m_enPanel[6][4] = PS_CHO_JOL;
		m_enPanel[6][6] = PS_CHO_JOL;
		m_enPanel[6][8] = PS_CHO_JOL;
		break;
	case 2:
		m_enPanel[9][0] = PS_CHO_CHA;
		m_enPanel[9][1] = PS_CHO_MA;
		m_enPanel[9][2] = PS_CHO_SANG;
		m_enPanel[9][3] = PS_CHO_SA;
		m_enPanel[9][5] = PS_CHO_SA;
		m_enPanel[9][6] = PS_CHO_SANG;
		m_enPanel[9][7] = PS_CHO_MA;
		m_enPanel[9][8] = PS_CHO_CHA;
		m_enPanel[8][4] = PS_CHO_JANG;
		m_enPanel[7][1] = PS_CHO_PO;
		m_enPanel[7][7] = PS_CHO_PO;
		m_enPanel[6][0] = PS_CHO_JOL;
		m_enPanel[6][2] = PS_CHO_JOL;
		m_enPanel[6][4] = PS_CHO_JOL;
		m_enPanel[6][6] = PS_CHO_JOL;
		m_enPanel[6][8] = PS_CHO_JOL;
		break;
	case 3:
		m_enPanel[9][0] = PS_CHO_CHA;
		m_enPanel[9][1] = PS_CHO_SANG;
		m_enPanel[9][2] = PS_CHO_MA;
		m_enPanel[9][3] = PS_CHO_SA;
		m_enPanel[9][5] = PS_CHO_SA;
		m_enPanel[9][6] = PS_CHO_MA;
		m_enPanel[9][7] = PS_CHO_SANG;
		m_enPanel[9][8] = PS_CHO_CHA;
		m_enPanel[8][4] = PS_CHO_JANG;
		m_enPanel[7][1] = PS_CHO_PO;
		m_enPanel[7][7] = PS_CHO_PO;
		m_enPanel[6][0] = PS_CHO_JOL;
		m_enPanel[6][2] = PS_CHO_JOL;
		m_enPanel[6][4] = PS_CHO_JOL;
		m_enPanel[6][6] = PS_CHO_JOL;
		m_enPanel[6][8] = PS_CHO_JOL;
		break;
	case 4:
		m_enPanel[9][0] = PS_CHO_CHA;
		m_enPanel[9][1] = PS_CHO_MA;
		m_enPanel[9][2] = PS_CHO_SANG;
		m_enPanel[9][3] = PS_CHO_SA;
		m_enPanel[9][5] = PS_CHO_SA;
		m_enPanel[9][6] = PS_CHO_MA;
		m_enPanel[9][7] = PS_CHO_SANG;
		m_enPanel[9][8] = PS_CHO_CHA;
		m_enPanel[8][4] = PS_CHO_JANG;
		m_enPanel[7][1] = PS_CHO_PO;
		m_enPanel[7][7] = PS_CHO_PO;
		m_enPanel[6][0] = PS_CHO_JOL;
		m_enPanel[6][2] = PS_CHO_JOL;
		m_enPanel[6][4] = PS_CHO_JOL;
		m_enPanel[6][6] = PS_CHO_JOL;
		m_enPanel[6][8] = PS_CHO_JOL;
		break;

	}

	*/


	sm_bPoBeforeJang = true;
	sm_bGatherJol = true;
	sm_bAggressivePO = true;
	sm_bAggressiveCHA = true;
	sm_bAggressiveJOL = true;
	sm_bAggressiveSANG = true;
	sm_bAggressiveMA = true;
	sm_bOnlyJangCenter = true;


}

/////////////////////////////////////////////////
// Check whether piece can pass the place located
bool CJKStage::IsPassable(int nX, int nY)
{
	//fprintf(fp1, "%s", "IsPassable()\n");
	//printf( "IsPassable()\n");
	if (nX < 0) return false;
	if (nY < 0) return false;
	if (nX >= DF_PANEL_WIDTH) return false;
	if (nY >= DF_PANEL_HEIGHT) return false;

	if (m_enPanel[nY][nX] == PS_NOTHING)
		return true;
	else
		return false;

}

void CJKStage::ClearList()
{
	//fprintf(fp1, "%s", "ClearList()\n");
	//printf( "ClearList()\n");
	if (m_pFirst)
	{
		CJKStage *pNode = m_pFirst;
		CJKStage *pTmp;
		do
		{
			pTmp = pNode->m_pNext;
			delete pNode;
			pNode = pTmp;
		} while (pNode != NULL);
		m_pFirst = NULL;
		m_pLast = NULL;
		m_nNodeCount = 0;
	}
}

void CJKStage::AddNextStageEffectively(CJKStage *pNewStage)
{
	//fprintf(fp1, "%s", "AddNextStageEffectively()\n");
	//printf("AddNextStageEffectively()\n");
	int nNewScore = pNewStage->Evaluate();

	///////////////////////////////////////////////////////
	// Nodes which are placed in same level must be sorted
	// to make Alpha-Beta algorithm effeciently.
	// When it's in Max turn, it must be sorted ascendently
	// in case of Min,Decendently.
	if (m_bAmIMax)
	{
		if (m_pFirst)
		{
			CJKStage *pNode = m_pFirst;
			do
			{
				if (nNewScore >= pNode->m_nScore) break;
				pNode = pNode->m_pNext;
			} while (pNode != NULL);
			if (pNode == NULL)
			{
				m_pLast->m_pNext = pNewStage;
				pNewStage->m_pPrev = m_pLast;
				pNewStage->m_pNext = NULL;
				m_pLast = pNewStage;
			}
			else
			{
				CJKStage * pTmp = pNode->m_pPrev;
				pNode->m_pPrev = pNewStage;
				pNewStage->m_pNext = pNode;
				pNewStage->m_pPrev = pTmp;
				if (pTmp)
				{
					pTmp->m_pNext = pNewStage;
				}
				else
				{
					m_pFirst = pNewStage;
				}
			}
		}
		else
		{
			m_pFirst = pNewStage;
			m_pLast = pNewStage;
			pNewStage->m_pPrev = NULL;
			pNewStage->m_pNext = NULL;
		}
	}
	else
	{
		if (m_pFirst)
		{
			CJKStage *pNode = m_pFirst;
			do
			{
				if (nNewScore <= pNode->m_nScore) break;
				pNode = pNode->m_pNext;
			} while (pNode != NULL);
			if (pNode == NULL)
			{
				m_pLast->m_pNext = pNewStage;
				pNewStage->m_pPrev = m_pLast;
				pNewStage->m_pNext = NULL;
				m_pLast = pNewStage;

			}
			else
			{
				CJKStage * pTmp = pNode->m_pPrev;
				pNode->m_pPrev = pNewStage;
				pNewStage->m_pNext = pNode;
				pNewStage->m_pPrev = pTmp;
				if (pTmp)
				{
					pTmp->m_pNext = pNewStage;
				}
				else
				{
					m_pFirst = pNewStage;
				}
			}
		}
		else
		{
			m_pFirst = pNewStage;
			m_pLast = pNewStage;
			pNewStage->m_pPrev = NULL;
			pNewStage->m_pNext = NULL;
		}
	}
	++m_nNodeCount;
}

//////////////////////////////////////////////
// Add possible movable location to the list 
bool CJKStage::TryToAddMovableXY(int nFromX, int nFromY, int nToX, int nToY)
{
	//fprintf(fp1, "%s", "TryAddMovableXY()\n");
	//printf( "TryAddMovableXY()\n");
	if (nToX < 0) return false;
	if (nToY < 0) return false;
	if (nToX >= DF_PANEL_WIDTH) return false;
	if (nToY >= DF_PANEL_HEIGHT) return false;

	// Impossible to move to a location where other piece of 
	// same team exist.
	if (GetTeamAt(nToX, nToY) == GetTeamAt(nFromX, nFromY)) return false;

	CJKStage *pNewStage = new CJKStage(this);
	pNewStage->MovePiece(nFromX, nFromY, nToX, nToY);

	pNewStage->m_nFromX = nFromX;
	pNewStage->m_nFromY = nFromY;
	pNewStage->m_nToX = nToX;
	pNewStage->m_nToY = nToY;
	pNewStage->m_enEatenPiece = m_enPanel[nToY][nToX];

	++sm_nTotalNode;

	AddNextStageEffectively(pNewStage);

	return true;
}

TEAM CJKStage::GetTeamAt(int nX, int nY) //���� ���������� �Ǵ�
{
	//fprintf(fp1, "%s", "GetTeamAT()\n");
	//printf("GetTeamAT()\n");
	if (m_enPanel[nY][nX] == PS_NOTHING) return TM_NOTHING;
	if (m_enPanel[nY][nX] < PS_BOUNDARY) return TM_CHO;

	return TM_HAN;
}

void CJKStage::GetMovableSaAndJang(int nFromX, int nFromY)
{
	//fprintf(fp1, "%s", "GetMovableSaAndJang()\n");
	//printf( "GetMovableSaAndJang()\n");
	switch (nFromY)
	{
	case 0:
	case 7:
		switch (nFromX)
		{
		case 3:
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY + 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY + 1);
			break;
		case 4:
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY + 1);
			break;
		case 5:
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY + 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY + 1);
			break;
		}
		break;
	case 1:
	case 8:
		switch (nFromX)
		{
		case 3:
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY + 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY);
			break;
		case 4:
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY + 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY + 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY + 1);
			break;
		case 5:
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY + 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY);
			break;
		}
		break;
	case 2:
	case 9:
		switch (nFromX)
		{
		case 3:
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY);
			break;
		case 4:
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY - 1);
			break;
		case 5:
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY);
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY - 1);
			break;
		}
		break;
	}
}

void CJKStage::GetMovableJol(int nFromX, int nFromY)
{
	//fprintf(fp1, "%s", "GetMovableJol()\n");
	//printf( "GetMovableJol()\n");
	int nDirection = GetTeamAt(nFromX, nFromY) == TM_CHO ? -1 : 1;

	//////////////////////////////////////////////////
	// JOL also can move diagonaly in the area of King
	switch (nFromY)
	{
	case 1:
	case 8:
		switch (nFromX)
		{
		case 4:
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY + nDirection);
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY + nDirection);
			break;
		}
		break;
	case 2:
	case 7:
		switch (nFromX)
		{
		case 3:
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY + nDirection);
			break;
		case 5:
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY + nDirection);
			break;
		}
		break;
	}

	// Tru to move to left
	TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY);
	// Try to move to right	
	TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY);
	// Try to move forward
	TryToAddMovableXY(nFromX, nFromY, nFromX, nFromY + nDirection);
}


void CJKStage::GetMovablePo(int nFromX, int nFromY)
{
	//fprintf(fp1, "%s", "GetMovablePo()\n");
	//printf( "GetMovablePo()\n");
	int k;

	bool bMovable = false;
	// Try Right side line
	for (int k = nFromX + 1; k < DF_PANEL_WIDTH; ++k)
	{
		if (bMovable)
		{
			if (m_enPanel[nFromY][k] != PS_CHO_PO &&
				m_enPanel[nFromY][k] != PS_HAN_PO)
			{
				TryToAddMovableXY(nFromX, nFromY, k, nFromY);
				if (m_enPanel[nFromY][k] != PS_NOTHING)
					break;
			}
			else
			{
				break;
			}
		}
		else
		{
			////////////////////////////////////////////////////////
			// PO only can move over the other piece except other PO
			if (m_enPanel[nFromY][k] == PS_HAN_PO)
				break;
			if (m_enPanel[nFromY][k] == PS_CHO_PO)
				break;
			if (m_enPanel[nFromY][k] != PS_NOTHING)
				bMovable = true;
		}
	}

	bMovable = false;
	// Try left side line
	for (k = nFromX - 1; k >= 0; --k)
	{
		if (bMovable)
		{
			if (m_enPanel[nFromY][k] != PS_CHO_PO &&
				m_enPanel[nFromY][k] != PS_HAN_PO)
			{
				TryToAddMovableXY(nFromX, nFromY, k, nFromY);
				if (m_enPanel[nFromY][k] != PS_NOTHING)
					break;
			}
			else
			{
				break;
			}
		}
		else
		{
			////////////////////////////////////////////////////////
			// PO only can move over the other piece except other PO
			if (m_enPanel[nFromY][k] == PS_HAN_PO)
				break;
			if (m_enPanel[nFromY][k] == PS_CHO_PO)
				break;
			if (m_enPanel[nFromY][k] != PS_NOTHING)
				bMovable = true;
		}
	}
	bMovable = false;
	// Try upper line
	for (k = nFromY - 1; k >= 0; --k)
	{
		if (bMovable)
		{
			if (m_enPanel[k][nFromX] != PS_CHO_PO &&
				m_enPanel[k][nFromX] != PS_HAN_PO)
			{
				TryToAddMovableXY(nFromX, nFromY, nFromX, k);
				if (m_enPanel[k][nFromX] != PS_NOTHING)
					break;
			}
			else
			{
				break;
			}
		}
		else
		{
			////////////////////////////////////////////////////////
			// PO only can move over the other piece except other PO
			if (m_enPanel[k][nFromX] == PS_HAN_PO)
				break;
			if (m_enPanel[k][nFromX] == PS_CHO_PO)
				break;
			if (m_enPanel[k][nFromX] != PS_NOTHING)
				bMovable = true;
		}
	}
	bMovable = false;
	// Try under line
	for (k = nFromY + 1; k < DF_PANEL_HEIGHT; ++k)
	{
		if (bMovable)
		{
			if (m_enPanel[k][nFromX] != PS_CHO_PO &&
				m_enPanel[k][nFromX] != PS_HAN_PO)
			{
				TryToAddMovableXY(nFromX, nFromY, nFromX, k);
				if (m_enPanel[k][nFromX] != PS_NOTHING)
					break;
			}
			else
			{
				break;
			}
		}
		else
		{
			////////////////////////////////////////////////////////
			// PO only can move over the other piece except other PO
			if (m_enPanel[k][nFromX] == PS_HAN_PO)
				break;
			if (m_enPanel[k][nFromX] == PS_CHO_PO)
				break;
			if (m_enPanel[k][nFromX] != PS_NOTHING)
				bMovable = true;
		}
	}
}


void CJKStage::GetMovableCha(int nFromX, int nFromY)
{
	//fprintf(fp1, "%s", "GetMovableCha()\n");
	//////////////////////////////////////////////////
	// CHA also can move diagonaly in the area of King
	switch (nFromY)
	{
	case 0:
	case 7:
		switch (nFromX)
		{
		case 3:
			if (GetTeamAt(4, nFromY) != GetTeamAt(nFromX, nFromY))
				TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY + 1);
			if (GetTeamAt(4, nFromY + 1) == PS_NOTHING)
				TryToAddMovableXY(nFromX, nFromY, nFromX + 2, nFromY + 2);
			break;
		case 5:
			if (GetTeamAt(4, nFromY) != GetTeamAt(nFromX, nFromY))
				TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY + 1);
			if (GetTeamAt(4, nFromY + 1) == PS_NOTHING)
				TryToAddMovableXY(nFromX, nFromY, nFromX - 2, nFromY + 2);
			break;
		}
		break;
	case 1:
	case 8:
		switch (nFromX)
		{
		case 4:
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY - 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY + 1);
			TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY + 1);
			break;
		}
		break;
	case 2:
	case 9:
		switch (nFromX)
		{
		case 3:
			if (GetTeamAt(4, nFromY) != GetTeamAt(nFromX, nFromY))
				TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY - 1);
			if (GetTeamAt(4, nFromY - 1) == PS_NOTHING)
				TryToAddMovableXY(nFromX, nFromY, nFromX + 2, nFromY - 2);
			break;
		case 5:
			if (GetTeamAt(4, nFromY) != GetTeamAt(nFromX, nFromY))
				TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY - 1);
			if (GetTeamAt(4, nFromY - 1) == PS_NOTHING)
				TryToAddMovableXY(nFromX, nFromY, nFromX - 2, nFromY - 2);
			break;
		}
		break;
	}
	// try Right line
	for (int k = nFromX + 1; k < DF_PANEL_WIDTH; ++k)
	{
		// Stop if other piece of same team exist
		if (GetTeamAt(k, nFromY) == GetTeamAt(nFromX, nFromY))
			break;
		TryToAddMovableXY(nFromX, nFromY, k, nFromY);
		if (GetTeamAt(k, nFromY) != PS_NOTHING)
			break;
	}
	// try Left line 
	for (int k = nFromX - 1; k >= 0; --k)
	{
		if (GetTeamAt(k, nFromY) == GetTeamAt(nFromX, nFromY))
			break;
		TryToAddMovableXY(nFromX, nFromY, k, nFromY);
		if (GetTeamAt(k, nFromY) != PS_NOTHING)
			break;
	}

	// try Upper line
	for (int k = nFromY - 1; k >= 0; --k)
	{
		if (GetTeamAt(nFromX, k) == GetTeamAt(nFromX, nFromY))
			break;
		TryToAddMovableXY(nFromX, nFromY, nFromX, k);
		if (GetTeamAt(nFromX, k) != PS_NOTHING)
			break;
	}

	// Try under line 
	for (int k = nFromY + 1; k < DF_PANEL_HEIGHT; ++k)
	{
		if (GetTeamAt(nFromX, k) == GetTeamAt(nFromX, nFromY))
			break;
		TryToAddMovableXY(nFromX, nFromY, nFromX, k);
		if (GetTeamAt(nFromX, k) != PS_NOTHING)
			break;
	}
}

void CJKStage::GetMovableMa(int nFromX, int nFromY)
{
	//fprintf(fp1, "%s", "GetMovableMa()\n");
	// Left Upper 
	if (IsPassable(nFromX, nFromY - 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY - 2);
	// Right Upper
	if (IsPassable(nFromX, nFromY - 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY - 2);
	// Left under
	if (IsPassable(nFromX, nFromY + 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 1, nFromY + 2);
	// Right under
	if (IsPassable(nFromX, nFromY + 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 1, nFromY + 2);
	// Left Upper 
	if (IsPassable(nFromX - 1, nFromY))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 2, nFromY - 1);
	// Left under
	if (IsPassable(nFromX - 1, nFromY))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 2, nFromY + 1);
	// Right upper
	if (IsPassable(nFromX + 1, nFromY))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 2, nFromY - 1);
	// right under
	if (IsPassable(nFromX + 1, nFromY))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 2, nFromY + 1);
}

void CJKStage::GetMovableSang(int nFromX, int nFromY)
{
	//fprintf(fp1, "%s", "GetMovalvleSang()\n");
	// Upper & Left
	if (IsPassable(nFromX, nFromY - 1) && IsPassable(nFromX - 1, nFromY - 2))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 2, nFromY - 3);

	// Upper & Right
	if (IsPassable(nFromX, nFromY - 1) && IsPassable(nFromX + 1, nFromY - 2))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 2, nFromY - 3);

	// Under & Left
	if (IsPassable(nFromX, nFromY + 1) && IsPassable(nFromX - 1, nFromY + 2))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 2, nFromY + 3);

	// Under & Right
	if (IsPassable(nFromX, nFromY + 1) && IsPassable(nFromX + 1, nFromY + 2))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 2, nFromY + 3);

	// Left & Upper
	if (IsPassable(nFromX - 1, nFromY) && IsPassable(nFromX - 2, nFromY - 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 3, nFromY - 2);

	// Left & Under
	if (IsPassable(nFromX - 1, nFromY) && IsPassable(nFromX - 2, nFromY + 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX - 3, nFromY + 2);

	// Right & Upper
	if (IsPassable(nFromX + 1, nFromY) && IsPassable(nFromX + 2, nFromY - 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 3, nFromY - 2);

	// Right & Under
	if (IsPassable(nFromX + 1, nFromY) && IsPassable(nFromX + 2, nFromY + 1))
		TryToAddMovableXY(nFromX, nFromY, nFromX + 3, nFromY + 2);
}
/////////////////////////////////////////////////
// HAN : Plus score
// CHO : Minus score
int CJKStage::Evaluate()
{
	//printf("EVALUATE()\n");
	m_nScore = 0;
	for (int i, j = 0; j < DF_PANEL_HEIGHT; ++j)
		for (i = 0; i < DF_PANEL_WIDTH; ++i)
		{
			switch (m_enPanel[j][i])
			{
			case PS_CHO_JANG:
			{
				m_nScore -= DF_SCORE_JANG;
				// An inclination to place PO in front of JANG
				if (sm_bPoBeforeJang)
				{
					if (m_enPanel[j - 1][i] == PS_CHO_PO)
						m_nScore -= 50;
				}
				break;
			}
			case PS_CHO_SA: m_nScore -= DF_SCORE_SA; break;
			case PS_CHO_JOL:
			{
				m_nScore -= DF_SCORE_JOL;
				// Gather JOL to center
				if (sm_bGatherJol)
				{
					if (m_enPanel[j][i - 1] == PS_CHO_JOL)
						m_nScore -= 1;
					if (m_enPanel[j][i + 1] == PS_CHO_JOL)
						m_nScore -= 1;
				}
				// Make JOL aggressive
				if (sm_bAggressiveJOL)
				{
					if (j < 7)
						m_nScore -= 1;
				}
				break;
			}
			case PS_CHO_PO:
			{
				m_nScore -= DF_SCORE_PO;
				// Make PO aggressive
				if (sm_bAggressivePO)
				{
					if (j < 7)
						m_nScore -= 1;
				}
				break;
			}
			case PS_CHO_CHA:
			{
				m_nScore -= DF_SCORE_CHA;
				// Make CHA Aggressive
				if (sm_bAggressiveCHA)
				{
					if (j < 7)
						m_nScore -= 2;
				}
				break;
			}
			case PS_CHO_MA:
			{
				m_nScore -= DF_SCORE_MA;
				// Make MA aggressive
				if (sm_bAggressiveMA)
				{
					if (j < 7)
						m_nScore -= 1;
				}
				break;
			}
			case PS_CHO_SANG:
			{
				m_nScore -= DF_SCORE_SANG;
				// Make SANG aggressive
				if (sm_bAggressiveSANG)
				{
					if (j < 7)
						m_nScore -= 1;
				}
				break;
			}
			case PS_HAN_JANG:
			{
				m_nScore += DF_SCORE_JANG;
				// An inclination to place PO in front of JANG
				if (sm_bPoBeforeJang)
				{
					if (m_enPanel[j + 1][i] == PS_HAN_PO)
						m_nScore += 50;
				}
				break;
			}
			case PS_HAN_SA: m_nScore += DF_SCORE_SA; break;
			case PS_HAN_JOL:
			{
				m_nScore += DF_SCORE_JOL;
				// Gather JOL to center
				if (sm_bGatherJol)
				{
					if (m_enPanel[j][i - 1] == PS_HAN_JOL)
						m_nScore += 1;
					if (m_enPanel[j][i + 1] == PS_HAN_JOL)
						m_nScore += 1;
				}
				// Aggressive JOL
				if (sm_bAggressiveJOL)
				{
					if (j > 3)
						m_nScore += 1;
				}
				break;
			}
			case PS_HAN_PO:
			{
				m_nScore += DF_SCORE_PO;
				// Aggressive PO
				if (sm_bAggressivePO)
				{
					if (j > 3)
						m_nScore += 1;
				}
				break;
			}
			case PS_HAN_CHA:
			{
				m_nScore += DF_SCORE_CHA;
				// Aggressive CHA
				if (sm_bAggressiveCHA)
				{
					if (j > 3)
						m_nScore += 2;
				}
				break;
			}
			case PS_HAN_MA:
			{
				m_nScore += DF_SCORE_MA;
				// Aggressive MA
				if (sm_bAggressiveMA)
				{
					if (j > 3)
						m_nScore += 1;
				}
				break;
			}
			case PS_HAN_SANG:
			{
				m_nScore += DF_SCORE_SANG;
				// Aggressive SANG
				if (sm_bAggressiveSANG)
				{
					if (j > 3)
						m_nScore += 1;
				}
				break;
			}
			}
		}
	// Block up other pieces except SA and MA to come to the center of the area of JANG
	if (sm_bOnlyJangCenter)
	{
		if (m_enPanel[1][4] != PS_NOTHING && m_enPanel[1][4] != PS_HAN_JANG && m_enPanel[1][5] != PS_HAN_SA)
			m_nScore -= 10;
		if (m_enPanel[8][4] != PS_NOTHING && m_enPanel[8][4] != PS_CHO_JANG && m_enPanel[8][4] != PS_CHO_SA)
			m_nScore += 10;
	}
	return m_nScore;
}

bool CJKStage::SaveStage(const char * filename)
{
	//fprintf(fp1, "%s", "SaveStage\n");
	//printf("SaveStage\n");
	//FILE *fp = fopen(filename, "w+b");
	//if (fp == NULL) return false;

	//	fwrite(m_enPanel, 1, sizeof(m_enPanel), fp);
	//sm_cHistoryStack.SaveHistory(fp);
	//
	//fclose(fp);

	return true;
}

bool CJKStage::LoadStage(const char * filename)
{
	//fprintf(fp1, "%s", "LoadStage\n");
	//printf("LoadStage\n");
	//	FILE *fp = fopen(filename, "r+b");
	//if (fp == NULL) return false;

	//	fread(m_enPanel, 1, sizeof(m_enPanel), fp);
	//sm_cHistoryStack.LoadHistory(fp);
	//	fclose(fp);

	return true;
}

bool CJKStage::MovePiece(int nFromX, int nFromY, int nToX, int nToY)
{
	//	//fprintf(fp1, "%s", "MovePiece\n");
	//printf("MovePiece\n");
	if (nFromX < 0 || nFromX >= DF_PANEL_WIDTH) return false;
	if (nFromY < 0 || nFromY >= DF_PANEL_HEIGHT) return false;
	if (nToX < 0 || nToX >= DF_PANEL_WIDTH) return false;
	if (nToY < 0 || nToY >= DF_PANEL_HEIGHT) return false;

	m_enPanel[nToY][nToX] = m_enPanel[nFromY][nFromX];
	m_enPanel[nFromY][nFromX] = PS_NOTHING;

	return true;
}

MOVERESULT CJKStage::HumanMove(int nFromX, int nFromY, int nToX, int nToY)
{
	//	printf( "HumanMove\n");
	//	fprintf(fp1, "%s", "HumanMove\n");
	PIECES enEatenPiece = m_enPanel[nToY][nToX];

	bool bResult = MovePiece(nFromX, nFromY, nToX, nToY);

	if (!bResult)	return MR_UNMOVED;
	// Save History
	sm_cHistoryStack.Push(nFromX, nFromY, nToX, nToY, enEatenPiece);

	if (enEatenPiece == PS_HAN_JANG) return MR_HANDEAD;
	if (enEatenPiece == PS_CHO_JANG) return MR_CHODEAD;

	return MR_MOVED;
}

///////////////////////////////////////////////
// Makes another CJKStage object,and get
// the information of movable location.
bool CJKStage::GetNextPieceLoc(int nFromX, int nFromY, CMoveData & cMD)
{
	//fprintf(fp1, "%s", "GetNextPieceLoc\n");
	//printf( "GetNextPieceLoc\n");
	CJKStage cStage;
	::memcpy(cStage.m_enPanel, m_enPanel, sizeof(m_enPanel));

	cMD.Reset();
	/////////////////////////////////////////////////////
	// �� �� ���� ������ �� �ִ� ������ ���Ѵ�.
	std::cout << nFromX << "  " << nFromY << std::endl;
	switch (cStage.m_enPanel[nFromY][nFromX])
	{
	case PS_CHO_JANG:
	case PS_CHO_SA: cStage.GetMovableSaAndJang(nFromX, nFromY); std::cout << "CHO SA" << std::endl; break;
	case PS_CHO_JOL: cStage.GetMovableJol(nFromX, nFromY);  std::cout << "CHO JOL" << std::endl; break;
	case PS_CHO_PO: cStage.GetMovablePo(nFromX, nFromY);  std::cout << "CHO PO" << std::endl; break;
	case PS_CHO_CHA: cStage.GetMovableCha(nFromX, nFromY);  std::cout << "CHO CHA" << std::endl; break;
	case PS_CHO_MA: cStage.GetMovableMa(nFromX, nFromY); std::cout << "CHO MA" << std::endl; break;
	case PS_CHO_SANG: cStage.GetMovableSang(nFromX, nFromY); std::cout << "CHO SANG" << std::endl; break;
	case PS_HAN_JANG:
	case PS_HAN_SA: cStage.GetMovableSaAndJang(nFromX, nFromY);  std::cout << "HAN SA" << std::endl; break;
	case PS_HAN_JOL: cStage.GetMovableJol(nFromX, nFromY);  std::cout << "HAN JOOL" << std::endl; break;
	case PS_HAN_PO: cStage.GetMovablePo(nFromX, nFromY);  std::cout << "HAN PO" << std::endl; break;
	case PS_HAN_CHA: cStage.GetMovableCha(nFromX, nFromY);  std::cout << "HNA CHA" << std::endl; break;
	case PS_HAN_MA: cStage.GetMovableMa(nFromX, nFromY);  std::cout << "HAN MA" << std::endl; break;
	case PS_HAN_SANG: cStage.GetMovableSang(nFromX, nFromY); std::cout << "HAN SANG" << std::endl;  break;
	}

	cMD.SetFromXY(nFromX, nFromY);

	if (cStage.m_pFirst)
	{
		CJKStage * pNode = cStage.m_pFirst;
		do
		{
			cMD.AddToXY(pNode->m_nToX, pNode->m_nToY);
			pNode = pNode->m_pNext;
		} while (pNode != NULL);

		return true;
	}

	return true;
}

void CJKStage::GetNextStage()
{
	//fprintf(fp1, "%s", "GetNextStage\n");
	//printf( "GetNextStage\n");

	if (m_enTeam == TM_HAN)
	{
		for (int j, i = 0; i < DF_PANEL_HEIGHT; ++i)
		{
			for (j = 0; j < DF_PANEL_WIDTH; ++j)
			{
				switch (m_enPanel[i][j])
				{
				case PS_HAN_JANG:
				case PS_HAN_SA: GetMovableSaAndJang(j, i); break;
				case PS_HAN_JOL: GetMovableJol(j, i); break;
				case PS_HAN_PO: GetMovablePo(j, i); break;
				case PS_HAN_CHA: GetMovableCha(j, i); break;
				case PS_HAN_MA: GetMovableMa(j, i); break;
				case PS_HAN_SANG: GetMovableSang(j, i); break;
				}
			}
		}
	}
	else
	{
		for (int j, i = 0; i < DF_PANEL_HEIGHT; ++i)
		{
			for (j = 0; j < DF_PANEL_WIDTH; ++j)
			{
				switch (m_enPanel[i][j])
				{
				case PS_CHO_JANG:
				case PS_CHO_SA: GetMovableSaAndJang(j, i); break;
				case PS_CHO_JOL: GetMovableJol(j, i); break;
				case PS_CHO_PO: GetMovablePo(j, i); break;
				case PS_CHO_CHA: GetMovableCha(j, i); break;
				case PS_CHO_MA: GetMovableMa(j, i); break;
				case PS_CHO_SANG: GetMovableSang(j, i); break;
				}
			}
		}
	}
}

bool CJKStage::CutOffTest()
{
	//fprintf(fp1, "%s", "CutOffTest\n");
	//printf( "CutOffTest\n");
	if (m_enEatenPiece == PS_CHO_JANG)
		return true;
	if (m_enEatenPiece == PS_HAN_JANG)
		return true;

	if (m_nDepth < sm_nCutOffDepth) return false;

	if (m_enEatenPiece == PS_NOTHING)
		return true;

	if (m_nDepth >= sm_nFeedOverDepth) return true;

	return false;
}

int CJKStage::MaxValue(int nAlpha, int nBeta)
{
	//fprintf(fp1, "%s", "MaxValue]n");
	//printf( "MaxValue]n");
	// CUTOFF test
	if (CutOffTest()) return m_nScore;

	GetNextStage();

	if (m_pFirst)
	{
		CJKStage * pNode = m_pFirst;
		int nValue;
		do
		{
			nValue = pNode->MinValue(nAlpha, nBeta);

			if (nValue > nAlpha)
			{
				nAlpha = nValue;
			}
			if (nAlpha >= nBeta)
			{
				ClearList();
				return nBeta;
			}
			pNode = pNode->m_pNext;
		} while (pNode != NULL);
	}
	ClearList();
	return nAlpha;
}
int CJKStage::getNumPiece() {
	int count = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (m_enPanel[i][j] != PS_NOTHING)
				count++;
		}
	}


	if (count > 25) //BEGINNING
		return BEGINING_DEPTH_LEVEL;
	if (count > 15) //MIDDLE
		return MIDDLE_DEPTH_LEVEL;
	
	return END_DEPTH_LEVEL; //END

	
}
int CJKStage::MinValue(int nAlpha, int nBeta)
{
	//fprintf(fp1, "%s", "MinValue\n");
	//printf("MinValue\n");
	// CUTOFF test
	if (CutOffTest()) return m_nScore;

	GetNextStage();
	if (m_pFirst)
	{
		CJKStage * pNode = m_pFirst;

		int nValue;
		do
		{
			nValue = pNode->MaxValue(nAlpha, nBeta);
			if (nValue < nBeta)
			{
				nBeta = nValue;
			}
			if (nBeta <= nAlpha)
			{
				ClearList();
				return nAlpha;
			}
			pNode = pNode->m_pNext;
		} while (pNode != NULL);
	}
	ClearList();
	return nBeta;
}

CJKStage * CJKStage::DeleteNode(CJKStage *pNode)
{
	if (pNode)
	{
		if (pNode->m_pPrev)
			pNode->m_pPrev->m_pNext = pNode->m_pNext;
		else
			m_pFirst = pNode->m_pNext;

		if (pNode->m_pNext)
			pNode->m_pNext->m_pPrev = pNode->m_pPrev;
		else
			m_pLast = pNode->m_pPrev;

		--m_nNodeCount;
	}
	return pNode;
}

MOVERESULT CJKStage::Infer(int turn)
{
	/////////////////////////////////////////////////////
	// ALPHA - maximum value of child for max
	// BETA	 - minimum value of child for min
	/////////////////////////////////////////////////////
	// Team HAN gets plus score,so HAN must be Max

	TEAM enTeam;
	if (turn == 0)
		enTeam = TM_CHO;
	else
		enTeam = TM_HAN;
	m_bAmIMax = (enTeam == TM_HAN);
	m_enTeam = enTeam;

	m_nDepth = 0;
	sm_nTotalNode = 0;

	int nAlpha = -DF_INFINITY;
	int nBeta = +DF_INFINITY;
	int nScore;
	CJKStage *pSelected = NULL;

	ClearList();
	GetNextStage();
	//TODO
	sm_nCutOffDepth = 6 - (m_nNodeCount / 10) + getNumPiece();
	sm_nFeedOverDepth = 10 - (m_nNodeCount / 10);

	if (sm_nCutOffDepth < 4) sm_nCutOffDepth = 4;
	if (sm_nFeedOverDepth < 8) sm_nFeedOverDepth = 8;

	if (m_pFirst == NULL) return MR_UNMOVED;
	////////////////////////////////////////
	// In case of team HAN
	if (m_bAmIMax)
	{
		CJKStage * pNode = m_pFirst;
		int snCount = 0;
		do
		{
			nScore = pNode->MinValue(nAlpha, nBeta);

			if (nScore > nAlpha)
			{
				nAlpha = nScore;
				pSelected = pNode;
			}
			pNode->m_nScore = nScore;
			pNode = pNode->m_pNext;
		} while (pNode != NULL);
	}
	else
	{
		////////////////////////////////////////
		// In case of team JO
		CJKStage * pNode = m_pFirst;
		int snCount = 0;
		do
		{
			nScore = pNode->MaxValue(nAlpha, nBeta);

			if (nScore < nBeta)
			{
				nBeta = nScore;
				pSelected = pNode;
			}
			pNode->m_nScore = nScore;
			pNode = pNode->m_pNext;
		} while (pNode != NULL);
	}
	if (pSelected == NULL) return MR_UNMOVED;

	m_nFromX = pSelected->m_nFromX;
	m_nFromY = pSelected->m_nFromY;
	m_nToX = pSelected->m_nToX;
	m_nToY = pSelected->m_nToY;
	m_enEatenPiece = m_enPanel[m_nToY][m_nToX];

	MovePiece(m_nFromX, m_nFromY, m_nToX, m_nToY);
	// Save History
	sm_cHistoryStack.Push(m_nFromX, m_nFromY, m_nToX, m_nToY, m_enEatenPiece);

	m_enEatenPiece = pSelected->m_enEatenPiece;
	/*std::cout << "Computer Moved : ";
	std::cout << m_nFromX << m_nFromY << "   ";
	std::cout << m_nToX << m_nToY << std::endl;*/
	if (m_enEatenPiece == PS_HAN_JANG) return MR_HANDEAD;
	if (m_enEatenPiece == PS_CHO_JANG) return MR_CHODEAD;

	return MR_MOVED;
}

bool CJKStage::GetLastMove(SHistory & LMStore)
{
	//fprintf(fp1, "%s", "GetLastMove\n");
	//printf("GetLastMove\n");
	return sm_cHistoryStack.GetLastMove(LMStore);
}


void CJKStage::getboard(char state_[11][10]) {
	 
	for (int i = 0; i < 11; i++) {
		state_[i][0] = '-';
	}
	for (int i = 0; i < 10; i++) {
		state_[0][i] = '-';
	}
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 10; j++) {
			switch (m_enPanel[i-1][j-1])
			{
			case PS_NOTHING:
				state_[i][j] = '-';
				break;
			case PS_CHO_CHA:
				state_[i][j] = 'c';
				break;
			case PS_CHO_JANG:
				state_[i][j] = 'k';
				break;
			case PS_CHO_JOL:
				state_[i][j] = 'j';
				break;
			case PS_CHO_MA:
				state_[i][j] = 'h';
				break;
			case PS_CHO_PO:
				state_[i][j] = 'p';
				break;
			case PS_CHO_SANG:
				state_[i][j] = 'x';
				break;
			case PS_CHO_SA:
				state_[i][j] = 's';
				break;
		
			case PS_HAN_CHA:
				state_[i][j] = 'C';
				break;
			case PS_HAN_JANG:
				state_[i][j] = 'K';
				break;
			case PS_HAN_JOL:
				state_[i][j] = 'J';
				break;
			case PS_HAN_MA:
				state_[i][j] = 'H';
				break;
			case PS_HAN_PO:
				state_[i][j] = 'P';
				break;
			case PS_HAN_SANG:
				state_[i][j] = 'X';
				break;
			case PS_HAN_SA:
				state_[i][j] = 'S';
				break;
				
			default:
				break;
			}
		}
	}

}



bool CJKStage::MoveBack()
{
	//fprintf(fp1, "%s", "MoveBack\n");
	//printf( "MoveBack\n");
	SHistory sH;
	if (sm_cHistoryStack.Pop(sH))
	{
		m_enPanel[sH.nFromY][sH.nFromX] = m_enPanel[sH.nToY][sH.nToX];
		m_enPanel[sH.nToY][sH.nToX] = sH.enEatenPiece;
		return true;
	}

	return false;
}
void CJKStage::boardChage(char board[][10]) {

	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 10; j++) {
			switch (board[i][j])
			{
			case 'C':
				m_enPanel[i - 1][j - 1] = PS_HAN_CHA;
				break;
			case 'X':
				m_enPanel[i - 1][j - 1] = PS_HAN_SANG;
				break;
			case 'H':
				m_enPanel[i - 1][j - 1] = PS_HAN_MA;
				break;
			case 'J':
				m_enPanel[i - 1][j - 1] = PS_HAN_JOL;
				break;
			case 'K':
				m_enPanel[i - 1][j - 1] = PS_HAN_JANG;
				break;
			case 'S':
				m_enPanel[i - 1][j - 1] = PS_HAN_SA;
				break;
			case 'P':
				m_enPanel[i - 1][j - 1] = PS_HAN_PO;
				break;
			case '-':
				m_enPanel[i - 1][j - 1] = PS_NOTHING;
				break;
			case 'c':
				m_enPanel[i - 1][j - 1] = PS_CHO_CHA;
				break;
			case 'x':
				m_enPanel[i - 1][j - 1] = PS_CHO_SANG;
				break;
			case 'h':
				m_enPanel[i - 1][j - 1] = PS_CHO_MA;
				break;
			case 'j':
				m_enPanel[i - 1][j - 1] = PS_CHO_JOL;
				break;
			case 'k':
				m_enPanel[i - 1][j - 1] = PS_CHO_JANG;
				break;
			case 's':
				m_enPanel[i - 1][j - 1] = PS_CHO_SA;
				break;
			case 'p':
				m_enPanel[i - 1][j - 1] = PS_CHO_PO;
				break;

			}
		}
	}

}
