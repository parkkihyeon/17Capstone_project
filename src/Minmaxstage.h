//#ifndef _MINMAXSTAGE_H_
//#define _MINMAXSTAGE_H_
#ifndef _STAGE_
#define _STAGE_
/*
해당 클래스는  MICROSOFT FOUNDATION CLASS LIBRARY : Jangki 에서 CJKStage Class를 차용하여 제작하였습니다.
This class was created by borrowing CJKStage Class from MICROSOFT FOUNDATION CLASS LIBRARY: Jangki.
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <memory.h>
using namespace std;
//#include "Statenode.h"
#define WIDTH_SIZE            10
#define DF_PANEL_WIDTH        9
#define DF_PANEL_HEIGHT        10

#define DF_SCORE_JANG        500000
#define DF_SCORE_SA            10000
#define DF_SCORE_JOL        5000
#define DF_SCORE_PO            25000

#define DF_SCORE_CHA        32000
#define DF_SCORE_MA            15000
#define DF_SCORE_SANG        9000

#define DF_INFINITY            9999999


enum MOVERESULT { MR_HANDEAD, MR_CHODEAD, MR_UNMOVED, MR_MOVED };

enum TEAM { TM_NOTHING, TM_HAN, TM_CHO };
enum PIECES {
    PS_NOTHING,
    PS_CHO_JANG,
    PS_CHO_SA,
    PS_CHO_JOL,
    PS_CHO_PO,
    PS_CHO_CHA,
    PS_CHO_MA,
    PS_CHO_SANG,
    PS_BOUNDARY,
    PS_HAN_JANG,
    PS_HAN_SA,
    PS_HAN_JOL,
    PS_HAN_PO,
    PS_HAN_CHA,
    PS_HAN_MA,
    PS_HAN_SANG,
};


class Minmaxstage{
public:
    Minmaxstage();
    virtual ~Minmaxstage();
    
public:
    Minmaxstage(Minmaxstage * pParentStage);
    bool    IsPassable(int nX, int nY);
    void    GetMovableSaAndJang(int nFromX, int nFromY);
    void    GetMovableJol(int nFromX, int nFromY);
    void    GetMovablePo(int nFromX, int nFromY);
    void    GetMovableCha(int nFromX, int nFromY);
    void    GetMovableMa(int nFromX, int nFromY);
    void    GetMovableSang(int nFromX, int nFromY);
    bool    TryToAddMovableXY(int nFromX, int nFromY, int nToX, int nToY);
    void    ClearList();
    bool    MovePiece(int nFromX, int nFromY, int nToX, int nToY);
    int        GetDepth() { return m_nDepth; }
    bool    IsMaxTurn() { return m_bAmIMax; }
    int        MaxValue(int nAlpha, int nBeta);
    int        MinValue(int nAlpha, int nBeta);
    void    AddNextStageEffectively(Minmaxstage *pNewStage);
    int        Evaluate();
    bool    CutOffTest();
    void    GetNextStage();
    Minmaxstage * DeleteNode(Minmaxstage *pNode);
    
    
public:
    
    int getNumPiece();
    void    Initialize();
    TEAM    GetTeamAt(int nX, int nY);
    MOVERESULT Infer(int turn);
    MOVERESULT HumanMove(int nFromX, int nFromY, int nToX, int nToY);
    bool    GetNextPieceLoc(int nX, int nY);
    PIECES    GetPiece(int nIndexX, int nIndexY) { return m_enPanel[nIndexY][nIndexX]; }
   
    bool    SaveStage(const char * filename);
    bool    LoadStage(const char * filename);
    bool    MoveBack();
    int        GetCutOffDepth() { return sm_nCutOffDepth; }
    int        GetFeedOverDepth() { return sm_nFeedOverDepth; }
    void    testprint();
    void    boardChage(char board[][10]);
    void     getboard(char state_[11][10]);
    

private:
    PIECES    m_enPanel[DF_PANEL_HEIGHT][DF_PANEL_WIDTH];
    int        m_nDepth;
    int        m_nScore;
    bool    m_bAmIMax;
    PIECES    m_enEatenPiece;
    int        m_nFromX;
    int        m_nFromY;
    int        m_nToX;
    int        m_nToY;
    int        m_nNodeCount;
    
    static    int sm_nTotalNode;
    
    // Flags for heuristic
    static int sm_nCutOffDepth;
    static int sm_nFeedOverDepth;
    
    static bool sm_bPoBeforeJang;
    static bool sm_bGatherJol;
    static bool sm_bAggressivePO;
    static bool sm_bAggressiveCHA;
    static bool sm_bAggressiveJOL;
    static bool sm_bAggressiveSANG;
    static bool sm_bAggressiveMA;
    static bool sm_bOnlyJangCenter;
    
    TEAM    m_enTeam;
    
    Minmaxstage * m_pPrev;
    Minmaxstage * m_pNext;
    Minmaxstage * m_pFirst;
    Minmaxstage * m_pLast;
    Minmaxstage * m_pParent;
};

#endif _JKSTATE_// !defined(AFX_JKSTAGE_H__530CA6F7_6E30_11D3_B509_BEB3B0969997__INCLUDED_)

