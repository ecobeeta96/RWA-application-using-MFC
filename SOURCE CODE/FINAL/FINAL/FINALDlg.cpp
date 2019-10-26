
// FINALDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FINAL.h"
#include "FINALDlg.h"
#include "afxdialogex.h"


#include <ctime>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////
#define V 6

//variables for mfc
string abc; // "from to distance string "
string assignWv_11, assignWv_12, assignWv_13, assignWv_21, assignWv_22;
bool assign = false;
string shortestpathString = "Shortest Path :- 0";
bool programRunOnce = false;


//concatenate string
string conct(string a, int b)
{
	return a + std::to_string(b);
}


//edge
struct edge
{
	int startNode;
	int endNode;
	int wvlenghts[2] = { 0, 0 }; //5 Gbps bandwidth
	int weight;
};

//edges vector
vector<edge> edges;

//structure for path to save
struct path
{
	int srcNode = 0, destNode, distance;
	vector<int> interNodes;
};

//shortest paths array from source to destination nodes
path shortestPath[V];

//parent array for printing path
int parent[V];

//Utility function
int minDistance(int dist[], bool sptset[])
{
	//initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
	{
		if (sptset[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;
	}

	return min_index;
}

//print the constructed distance array
void solution(int dist[], int n, int parent[], int src)
{
	//cout << "Source Node " << src << endl;
	/*cout << "Node Distance from Source \n"
	<< endl;*/

	for (int i = 0; i < V; i++)
	{
		//to store the shortestPaths

		shortestPath[i].srcNode = 0;
		shortestPath[i].destNode = i;
		shortestPath[i].distance = dist[i];

		int j = i;
		while (parent[j] != -1)
		{
			// cout << j << " ";
			shortestPath[i].interNodes.push_back(j);
			j = parent[j];
		}
		reverse(shortestPath[i].interNodes.begin(), shortestPath[i].interNodes.end());
		//cout << endl;
	}
}

//Dijkstra's algo
void dijkstra(int graph[V][V], int src)
{
	//shortest path distance form src to i
	int dist[V];

	//sptSet array
	bool sptset[V];

	//Initialize all the distances as infinite and sptset[V] as false
	for (int i = 0; i < V; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX, sptset[i] = false;
	}

	//Distance of source node from itself is always 0
	dist[src] = 0;

	//Find shortest path for all verices
	for (int count = 0; count < V; count++)
	{
		//pick the minimum distance node
		int u = minDistance(dist, sptset);

		//markd the picked node as visited
		sptset[u] = true;

		//update dist value of the adjacent nodes of the visited node
		for (int v = 0; v < V; v++)
		{
			//update dist[v] only if is not in sptset, there is an edge from
			//u to v, and total weight of path from src to v through u is
			//smaller than curren value of dist[v]
			if (!sptset[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}

	//print the constructed distance array
	solution(dist, V, parent, src);
}

//check wavelenghts availability
bool checkAvailability(edge myEdge, int lamdaNum)
{

	if (myEdge.wvlenghts[lamdaNum - 1] == 0)
	{
		myEdge.wvlenghts[lamdaNum - 1] = 1;
		return true; //if wvlengt is available return 1/true
	}
	else
		return false; //Not return -1/false
}

//check availability and assign wavelengths
void assignWv(int lamdaNum, path shortestPath[], int src, int dest)
{
	bool waveLenth = false;
	cout << "\n";
	for (int i = 0; i < V; i++)
	{
		if (shortestPath[i].srcNode == src && shortestPath[i].destNode == dest)
		{

			for (int j = 0; j < shortestPath[i].interNodes.size(); j++)
			{

				for (int k = 0; i < edges.size(); k++)
				{
					if (edges[k].startNode == src && edges[k].endNode == shortestPath[i].interNodes[j])
					{
						if (checkAvailability(edges[k], lamdaNum))
						{

							edges[k].wvlenghts[lamdaNum - 1] = 1;
							src = shortestPath[i].interNodes[j];

							waveLenth = true;
						}
						else
						{
							waveLenth = false;
							cout << "\n*\tPath is already allocated!!!.\n*\tCANNOT ALLOCATE THIS PATH !!! . \n*\tRequest is BLOCKED! " << endl;
							assignWv_11 = "Path is already allocated!!!. ";
							assignWv_12 = "CANNOT ALLOCATE THIS PATH !!! .";
							assignWv_13 = "Request is BLOCKED!";

							cout << "-----------------------------------------------------------------------------" << endl;


							return;
						}
						break;
					}
					else
						continue;
				}
			}
		}
	}

	if (waveLenth == true)
	{
		assignWv_21 = "PATH CAN BE ALLOCATED and REQUEST IS ACCEPTED";
		cout << "\r\n*\tPATH CAN BE ALLOCATED\n*\tREQUEST IS ACCEPTED☻☻.";

		cout << "wavelenght " << lamdaNum << " is free on above path!!!" << endl;

		string a = conct("wavelenght ", lamdaNum);
		assignWv_22 = a + " is free on above path!!!";

		//string a = conct("\n*\twavelenght ",)
		assign = true;
		cout << "\n-----------------------------------------------------------------------------\n" << endl;
	}
}


//print given path
void printGivenPath(int srcIn, int destIn)
{
	cout << "-----------------------------------------------------------------------------" << endl;
	string breakLine = "------------------------------------------------------------------ \n\t";
	cout << "\n*\tFrom "
		<< shortestPath[destIn].srcNode << " to " << shortestPath[destIn].destNode << "    Min.Disntance " << shortestPath[destIn].distance << "   Shorterst Path : ";

	/*stringstream ss1,ss2,ss3;
	ss1 << shortestPath[destIn].srcNode;
	ss2 << shortestPath[destIn].destNode;
	ss3 << shortestPath[destIn].distance;
	string str_1 = ss1.str();
	string str_2 = ss2.str();
	string str_3 = ss3.str();*/

	string a = conct("From Node ", shortestPath[destIn].srcNode);
	string b = conct(" TO Node ", shortestPath[destIn].destNode);
	string c = conct(" Distance ", shortestPath[destIn].distance);
	abc = a + b + c;


	int sz = shortestPath[5].interNodes.size();
	cout << srcIn;
	//string shortestpathString = "Shortest Path :- 0";
	for (int i = 0; i < shortestPath[destIn].interNodes.size(); i++)
	{
		cout << " -> " << shortestPath[destIn].interNodes[i];
		shortestpathString = shortestpathString + conct(" -> ", shortestPath[destIn].interNodes[i]);
	}
}





//////////////////////////////////////////////////////////



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFINALDlg dialog



CFINALDlg::CFINALDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FINAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFINALDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFINALDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnRunAlgo, &CFINALDlg::OnBnClickedbtnrunalgo)
	ON_BN_CLICKED(btnRunAgain, &CFINALDlg::OnBnClickedbtnrunagain)
	ON_BN_CLICKED(btnExit, &CFINALDlg::OnBnClickedbtnexit)
END_MESSAGE_MAP()


// CFINALDlg message handlers

BOOL CFINALDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFINALDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFINALDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFINALDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFINALDlg::OnBnClickedbtnrunalgo()
{
	// TODO: Add your control notification handler code here
	CString textInput;
	//sorce Node
	GetDlgItemText(txtSrcNode, textInput);
	int srcNode = 0;

	//Dest Node
	GetDlgItemText(txtDestNode, textInput);
	int destNode = _ttoi(textInput);

	//wavelenght num
	GetDlgItemText(txtWvlnght, textInput);
	int wvlengthNum = _ttoi(textInput);

	/////////////////////////////////////////////////////////
	//our src = 0 & dest = 5;

	if (programRunOnce == false)
	{
		int graph[V][V];
		ifstream inGraphFile("graph.txt");
		if (!inGraphFile)
		{
			cout << "Error while reading graph file!!!" << endl;
			string fileNotReading = "ERROR IN FILE READING!!!\n";
			CString fileNotRd(fileNotReading.c_str());
			SetDlgItemText(txtFileRd, fileNotRd);
			return;
		}


		//assign wavelenghts for each edge and input graph from a text file
		for (int i = 0; i < V; i++)
		{
			//edges for wavelenghts
			edge myEdge;

			for (int j = 0; j < V; j++)
			{
				int input;
				inGraphFile >> input;
				graph[i][j] = input;

				if (input >= 1)
				{
					myEdge.startNode = i;
					myEdge.endNode = j;
					myEdge.weight = input;

					edges.push_back(myEdge);
				}
			}
		}


		string fileReading = "file reading successfully done\n";
		CString fileRd(fileReading.c_str());
		SetDlgItemText(txtFileRd, fileRd);
		

		dijkstra(graph, srcNode);
		programRunOnce = true;

	}

	printGivenPath(srcNode, destNode);
	assignWv(wvlengthNum, shortestPath, srcNode, destNode);

	//pathDetail_1 from to distance
	CString pathDetail_0(abc.c_str());
	CString pathDetail_11(assignWv_11.c_str());
	CString pathDetail_12(assignWv_12.c_str());
	CString pathDetail_13(assignWv_13.c_str());


	CString pathDetail_3(assignWv_21.c_str());
	CString pathDetail_4(assignWv_22.c_str());
	CString shrtPath(shortestpathString.c_str());




	if (assign == true)
	{
		SetDlgItemText(pathDetails_1, pathDetail_0);
		SetDlgItemText(pathDetails_2, shrtPath);
		SetDlgItemText(pathDetails_3, pathDetail_3);
		SetDlgItemText(pathDetails_4, pathDetail_4);
		assign = false;
	}
	else
	{
		SetDlgItemText(pathDetails_2, pathDetail_11);
		SetDlgItemText(pathDetails_3, pathDetail_12);
		SetDlgItemText(pathDetails_4, pathDetail_13);
	}
}


void CFINALDlg::OnBnClickedbtnrunagain()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(txtSrcNode)->SetWindowText(0);
	//GetDlgItem(txtFileRd)->SetWindowText(0);
	GetDlgItem(txtDestNode)->SetWindowText(0);
	GetDlgItem(txtWvlnght)->SetWindowText(0);
	GetDlgItem(pathDetails_1)->SetWindowText(0);
	GetDlgItem(pathDetails_2)->SetWindowText(0);
	GetDlgItem(pathDetails_3)->SetWindowText(0);
	GetDlgItem(pathDetails_4)->SetWindowText(0);
	GetDlgItem(pathDetails_5)->SetWindowText(0);

	shortestpathString = "Shortest Path :- 0";
}


void CFINALDlg::OnBnClickedbtnexit()
{
	// TODO: Add your control notification handler code here
	//CloseWindow();
	this->DestroyWindow();
	
	//SetWindowLong(this->m_hWnd, GWL_STYLE, GetWindowLong(this->m_hWnd, GWL_STYLE) | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
}
