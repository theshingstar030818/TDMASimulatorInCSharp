
// TDMASystem3SimulatorDlg.h : header file
//

#pragma once
#include "afxwin.h"

#define TDMA_STATUS_N 8
#define TDMA_STATUS_Li 4
#define TDMA_STATUS_W 4
#define TDMA_STATUS_PACKET_DATA_RANGE 100

struct PACKET {
    int data;
	int nodeNOFrom;
	int nodeNOTo;
	int slotNOCreated;
	int slotNOTranslated;
};

class TDMANode
{
public:
	TDMANode() {

	}

	CList<PACKET, PACKET &> m_PacketsToSend;
	CList<PACKET, PACKET &> m_PacketsReceived;

};

class TDMASimulator {
public:
	TDMANode m_Nodes[TDMA_STATUS_N];
	int m_SlotIndex = 0;
	int m_SlotTIndex = 0;
	int m_totalPacketsReceived = 0;
	int m_totalPacketsDelayed = 0;

	TDMASimulator() {

	}

	void initialize() {
		m_SlotIndex = 0;
		m_SlotTIndex = 0;
		m_totalPacketsReceived = 0;
		m_totalPacketsDelayed = 0;

		for (int j = 0; j < TDMA_STATUS_N; j++) {
			m_Nodes[j].m_PacketsToSend.RemoveAll();
			m_Nodes[j].m_PacketsReceived.RemoveAll();
		}
	}

	int GenerateAPacket() {
		int nNodeNO = rand() % TDMA_STATUS_N;
		if (m_Nodes[nNodeNO].m_PacketsToSend.GetCount() < TDMA_STATUS_Li)
		{ // Return if a node has packets equal or greater than Li
			PACKET pack;
			pack.data = rand() % TDMA_STATUS_PACKET_DATA_RANGE;
			pack.nodeNOFrom = nNodeNO;
			pack.nodeNOTo = rand() % (TDMA_STATUS_N - 1);
			if (pack.nodeNOTo >= pack.nodeNOFrom)
			{ // don't sent to the same node from a node.
				pack.nodeNOTo += 1;
			}
			pack.slotNOCreated = m_SlotIndex;
			pack.slotNOTranslated = -1;
			m_Nodes[nNodeNO].m_PacketsToSend.AddTail(pack);
		}
		else
		{
			return -1;
		}

		return nNodeNO;
	}

	int GetNodeNoToSendBasedOnTindex(int slotTIndex) {
		int nodeNOFrom = slotTIndex * 2;
		int nodeNOTo = slotTIndex * 2 + 1;
		CArray<int, int> nodes;

 		for (int i = 0; i < TDMA_STATUS_N; i++)
		{
			if (m_Nodes[i].m_PacketsToSend.GetCount() > 0)
			{
				PACKET pack = m_Nodes[i].m_PacketsToSend.GetHead();
				if (pack.nodeNOTo >= nodeNOFrom && pack.nodeNOTo <= nodeNOTo)
				{
					nodes.Add(pack.nodeNOTo);
				}
			}
		}

		if (nodes.GetCount() < 1)
			return -1;
		int nodeNoSelected = nodes.GetAt(rand() % nodes.GetCount());
		
		return nodeNoSelected;
	}

	CString ProcessASlot()
	{
		CString strRTN = _T("");
		//Pick a random Node to send based on T index
		int nNodeNO = GetNodeNoToSendBasedOnTindex(m_SlotTIndex);
		if (nNodeNO < 0)
		{//nothing to process
			strRTN.Format(_T("T%d -- Null -> Null: Null"),
				m_SlotTIndex + 1);
		}
		else if (m_Nodes[nNodeNO].m_PacketsToSend.GetCount() <= 0)
		{ // nothing to send
			strRTN.Format(_T("T%d -- N%d -> Null: Null"),
				m_SlotTIndex + 1,
				nNodeNO + 1);
		}
		else
		{
			//PACKET pack = m_Nodes[nNodeNO].m_PacketsToSend.GetHead();
			PACKET pack = m_Nodes[nNodeNO].m_PacketsToSend.RemoveHead();

			strRTN.Format(_T("T%d -- N%d -> R%d: %d"),
				m_SlotTIndex + 1,
				nNodeNO + 1,
				pack.nodeNOTo + 1,
				pack.data);

			//Process received Packet
			pack.slotNOTranslated = m_SlotIndex;
			m_Nodes[nNodeNO].m_PacketsReceived.AddHead(pack);

			if (m_Nodes[nNodeNO].m_PacketsReceived.GetCount() > TDMA_STATUS_Li)
			{
				m_Nodes[nNodeNO].m_PacketsReceived.RemoveTail();
			}

			//Calc delay
			m_totalPacketsReceived++;
			m_totalPacketsDelayed += (pack.slotNOTranslated - pack.slotNOCreated);
		}
		
		m_SlotIndex++;
		m_SlotTIndex = (m_SlotTIndex + 1) % TDMA_STATUS_W;

		return strRTN;
	}

	CString GetAverageDelay()
	{
		CString strRTN = _T("");
		if(m_totalPacketsReceived > 0)
			strRTN.Format(_T("%f slots -- total packets received: %d, total slots consumed: %d"),
				(1.0 * m_totalPacketsDelayed) / m_totalPacketsReceived,
				m_totalPacketsReceived,
				m_totalPacketsDelayed);
		return strRTN;
	}

	CString GetNodeToSendString(int nNodeNO) {
		CString strRTN = _T("");
		POSITION pos = m_Nodes[nNodeNO].m_PacketsToSend.GetHeadPosition();

		for (int i = 0; i < m_Nodes[nNodeNO].m_PacketsToSend.GetCount(); i++)
		{
			if (strRTN.GetLength() > 0)
				strRTN += ", ";
			PACKET pack = m_Nodes[nNodeNO].m_PacketsToSend.GetNext(pos);
			CString str;
			str.Format(_T("%d"), pack.data);
			strRTN += str;
		}

		strRTN = _T("[") + strRTN + _T("]");
		return strRTN;
	}

	CString GetNodeReceivedString(int nNodeNO) {
		CString strRTN = _T("");
		POSITION pos = m_Nodes[nNodeNO].m_PacketsReceived.GetHeadPosition();

		for (int i = 0; i < m_Nodes[nNodeNO].m_PacketsReceived.GetCount(); i++)
		{
			if (strRTN.GetLength() > 0)
				strRTN += ", ";
			PACKET pack = m_Nodes[nNodeNO].m_PacketsReceived.GetNext(pos);
			CString str;
			str.Format(_T("%d"), pack.data);
			strRTN += str;
		}

		strRTN = _T("[") + strRTN + _T("]");
		return strRTN;
	}
};


// CTDMASystem3SimulatorDlg dialog
class CTDMASystem3SimulatorDlg : public CDialogEx
{
// Construction
public:
	CTDMASystem3SimulatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TDMASYSTEM3SIMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLbnSelchangeList1();
	int status_N;
	int status_W;
	int status_Li;
	int status_SlotLen;
	CString m_sSrcN1;
	CString m_sSrcN2;
	CString m_sSrcN3;
	CString m_sSrcN4;
	CString m_sSrcN5;
	CString m_sSrcN6;
	CString m_sSrcN7;
	CString m_sSrcN8;
	CString m_sDstN1;
	CString m_sDstN2;
	CString m_sDstN3;
	CString m_sDstN4;
	CString m_sDstN5;
	CString m_sDstN6;
	CString m_sDstN7;
	CString m_sDstN8;
	CListBox m_ctrlLstSlotLog;
	afx_msg void OnBnClickedBtnStart();
	int status_bVal;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	//TDAM simulator object
	TDMASimulator m_objTDMASimulator;
	bool m_fMutex = false;
	bool m_isPaused = false;
	void UpdateDlgContentOfSendParty(int nNodeNO);
	void UpdateDlgContentOfReceiveParty(int nNodeNO);
	CString m_strAnalyze;
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnPause();
};
