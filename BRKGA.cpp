//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<stdlib.h>
//#include<cmath>
//#include<vector>
//#include<unordered_map>
//#include<iomanip>
//#include<fstream>
//#include<string>
//using namespace std;
//int pop;//种群数(5*n)
//int pope;//精英种群的数目(30%)
//int popm;//交叉个体的数目(25%)
//#define Pe 0.7//偏向于精英个体的概率
//int m;//机器数
//int n;//工件数
//int CS;//记录成本
//#define Pr 0.7
//#define Max_Nmach 30//最大机器数
//#define Max_Njob 300//最大工件数
//#define Max_pop 3000//最大种群数
//#define min_pt 1 //最小加工时间
//#define max_pt 99//最大加工时间
//int Max_st;//（9，49，99，124）
//double Rf;//（0.2，0.6，1.0，1.4，1.8）
//double alpha;//（0.05，0.5）
//#define Min_st 1
//#define NNM 3//机器类型数
//#define NNN 4//工件类型数
//#define NNMN 6
//#define NNS 4//设置时间类型数
//#define NNR 5//到达时间类型数
//#define NNa 2
//#define NNA 10//案例数
//#define Time 5
//double TL;
//int budget;
//double gen;
//double genBest;
//double BXCPUT;
//class Job_information
//{
//public:
//	int p[Max_Nmach];
//	int r;
//};
//Job_information Job[Max_Njob];
//class setuptime
//{
//public:
//	int s[Max_Njob][Max_Njob];
//};
//setuptime st[Max_Nmach];
//class machine_information
//{
//public:
//	int price;
//};
//machine_information machine[Max_Nmach];
//void f_ReadData(FILE* infile);
//class individual
//{
//public:
//	double a[Max_Njob];
//	vector<vector<int>> b;//解决方案
//	int truefit;
//	int C;
//};
//individual group[Max_pop];
//individual ngroup[Max_pop];
//individual gbest;
//void Initgroup()
//{
//	for (int i = 0;i < pop;i++)
//	{
//		for (int j = 0;j < n;j++)
//		{
//			group[i].a[j] = 1 + rand() / (RAND_MAX + 1.0) * m;
//		}
//	}
//}
//int getfitness(int k)
//{
//	for (int i = 0;i < m;i++)
//	{
//		group[k].b.push_back({});
//	}
//	//候选工件列表
//	vector<int> U(n);
//	for (int i = 0;i < n;i++)
//	{
//		U[i] = i + 1;
//	}
//	//对编码进行排序
//	vector<double> a(n);
//	for (int i = 0;i < n;i++)
//	{
//		a[i] = group[k].a[i];
//	}
//	for (int i = 0;i < n;i++)
//	{
//		for (int j = 0;j < n - 1 - i;j++)
//		{
//			if (a[j] > a[j + 1])
//			{
//				swap(a[j], a[j + 1]);
//				swap(U[j], U[j + 1]);
//			}
//		}
//	}
//	vector<int> num(m);//记录每个机器加工工件的个数
//	for (int i = 0;i < m;i++)
//	{
//		for (int j = 0;j < n;j++)
//		{
//			if (a[j] >= i + 1 && a[j] < i + 2)
//			{
//				num[i]++;
//			}
//		}
//	}
//	vector<int> SM(m);
//	for (int i = 0;i < m;i++)
//	{
//		if (num[i] == 0) {
//			continue;
//		}
//		else {
//			//[num[0]+num[1]+num[i-1],num[0]+num[1]+num[i-1]+num[i])
//			int sum = 0;
//			for (int j = 0;j < i;j++)
//			{
//				sum += num[j];
//			}
//			if (sum < n) {
//				SM[i] = Job[U[sum] - 1].r + st[i].s[U[sum] - 1][U[sum] - 1] + Job[U[sum] - 1].p[i];
//				group[k].b[i].push_back(U[sum]);
//				for (int j = sum + 1;j < sum + num[i];j++)
//				{
//					if (Job[U[j] - 1].r <= SM[i]) {
//						SM[i] += st[i].s[U[j - 1] - 1][U[j] - 1] + Job[U[j] - 1].p[i];
//					}
//					else {
//						SM[i] = Job[U[j] - 1].r + st[i].s[U[j - 1] - 1][U[j] - 1] + Job[U[j] - 1].p[i];
//					}
//					group[k].b[i].push_back(U[j]);
//				}
//			}
//		}
//	}
//	int max = 0;
//	for (int i = 0;i < m;i++)
//	{
//		if (SM[max] < SM[i])
//		{
//			max = i;
//		}
//	}
//	return SM[max];
//}
//int getSM(vector<vector<int>> TABU, int i)
//{
//	int sum = 0;
//	if (TABU[i].size() != 0) {
//		sum = st[i].s[TABU[i][0] - 1][TABU[i][0] - 1] + Job[TABU[i][0] - 1].r + Job[TABU[i][0] - 1].p[i];
//		for (int j = 1;j < TABU[i].size();j++) {
//			if (Job[TABU[i][j] - 1].r <= sum) {
//				sum += st[i].s[TABU[i][j - 1] - 1][TABU[i][j] - 1] + Job[TABU[i][j] - 1].p[i];
//			}
//			else {
//				sum = Job[TABU[i][j] - 1].r + st[i].s[TABU[i][j - 1] - 1][TABU[i][j] - 1] + Job[TABU[i][j] - 1].p[i];
//			}
//		}
//	}
//	return sum;
//}
//int getCmax(vector<vector<int>> a)
//{
//	vector<int> SM(m);
//	for (int i = 0;i < m;i++) {
//		if (a[i].size() != 0) {
//			SM[i] = Job[a[i][0] - 1].r + st[i].s[a[i][0] - 1][a[i][0] - 1] + Job[a[i][0] - 1].p[i];
//			for (int j = 1;j < a[i].size();j++) {
//				if (Job[a[i][j] - 1].r <= SM[i]) {
//					SM[i] += st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
//				}
//				else {
//					SM[i] = Job[a[i][j] - 1].r + st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
//				}
//			}
//		}
//	}
//	int max = 0;
//	for (int i = 0;i < m;i++) {
//		if (SM[max] < SM[i]) {
//			max = i;
//		}
//	}
//	return SM[max];
//}
//int getC(vector<vector<int>> a)
//{
//	int C = 0;
//	for (int i = 0;i < m;i++) {
//		for (int j = 0;j < a[i].size();j++) {
//			C += Job[a[i][j] - 1].p[i] * machine[i].price;
//		}
//	}
//	return C;
//}
//void dl(int o, int i, int j)
//{
//	for (int k = j + 1;k < group[o].b[i].size();k++) {
//		group[o].b[i][k - 1] = group[o].b[i][k];
//	}
//	group[o].b[i].pop_back();
//}
//void Insert(int o, int M, int W, int J)
//{
//	if (group[o].b[M - 1].size() == 0) {
//		group[o].b[M - 1].push_back(J);
//	}
//	else {
//		group[o].b[M - 1].push_back({});
//		for (int j = group[o].b[M - 1].size() - 2;j >= W - 1;j--) {
//			group[o].b[M - 1][j + 1] = group[o].b[M - 1][j];
//		}
//		group[o].b[M - 1][W - 1] = J;
//	}
//}
//void repair(int o,int P)
//{
//	int cost = CS;
//	while (cost > budget) {
//		//每次迭代将存在比原来成本低的工件插入到最好的位置
//		vector<vector<int>> JM;
//		for (int i = 0;i < n;i++) {
//			JM.push_back({});
//		}
//		for (int i = 0;i < m;i++) {
//			for (int j = 0;j < group[o].b[i].size();j++) {
//				for (int k = 1;k <= m;k++) {
//					if (machine[i].price * Job[group[o].b[i][j] - 1].p[i] > machine[k - 1].price * Job[group[o].b[i][j] - 1].p[k - 1]) {
//						JM[group[o].b[i][j] - 1].push_back(k);
//					}
//				}
//			}
//		}
//		if (P == 0) {
//			int r = rand() % n;
//			while (JM[r].size() == 0) {
//				r = rand() % n;
//			}
//			int r1 = rand() % JM[r].size();
//			int mindex = -1;
//			int windex = -1;
//			for (int i = 0;i < m;i++) {
//				for (int j = 0;j < group[o].b[i].size();j++) {
//					if (group[o].b[i][j] == r + 1) {
//						mindex = i;
//						windex = j;
//						break;
//					}
//				}
//				if (mindex != -1) {
//					break;
//				}
//			}
//			dl(o, mindex, windex);
//			int w = 1 + rand() % (1 + group[o].b[JM[r][r1] - 1].size());
//			Insert(o, JM[r][r1], w, r + 1);
//		}
//		else {
//			int mindex = 0;//记录选择工件的位置
//			int windex = 0;
//			int M = 1;//记录插入的机器
//			int W = 1;//记录插入的位置
//			int J;
//			int Cmax = 0;//记录插入后的最大完工时间
//			for (int i = 0;i < m;i++) {
//				if (group[o].b[i].size() == 0) {
//					continue;
//				}
//				else {
//					for (int j = 0;j < group[o].b[i].size();j++) {
//						if (JM[group[o].b[i][j] - 1].size() == 0) {
//							continue;
//						}
//						else {
//							J = group[o].b[i][j];
//							dl(o, i, j);
//							for (int k = 0;k < JM[J - 1].size();k++) {
//								for (int l = 1;l <= 1 + group[o].b[JM[J - 1][k] - 1].size();l++) {
//									Insert(o, JM[J - 1][k], l, J);
//									int C = getCmax(group[o].b);
//									if (Cmax == 0) {
//										mindex = i;
//										windex = j;
//										M = JM[J - 1][k];
//										W = l;
//										Cmax = C;
//									}
//									else {
//										if (Cmax > C) {
//											mindex = i;
//											windex = j;
//											M = JM[J - 1][k];
//											W = l;
//											Cmax = C;
//										}
//									}
//									dl(o, JM[J - 1][k] - 1, l - 1);
//								}
//							}
//							Insert(o, i + 1, j + 1, J);
//						}
//					}
//				}
//			}
//			J = group[o].b[mindex][windex];
//			dl(o, mindex, windex);
//			Insert(o, M, W, J);
//		}
//		cost = getC(group[o].b);
//	}
//	CS = cost;
//}
//int getmaxM(vector<vector<int>> a)
//{
//	vector<int> SM(m);
//	for (int i = 0;i < m;i++) {
//		if (a[i].size() != 0) {
//			SM[i] = Job[a[i][0] - 1].r + st[i].s[a[i][0] - 1][a[i][0] - 1] + Job[a[i][0] - 1].p[i];
//			for (int j = 1;j < a[i].size();j++) {
//				if (Job[a[i][j] - 1].r <= SM[i]) {
//					SM[i] += st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
//				}
//				else {
//					SM[i] = Job[a[i][j] - 1].r + st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
//				}
//			}
//		}
//	}
//	int max = 0;
//	for (int i = 0;i < m;i++) {
//		if (SM[max] < SM[i]) {
//			max = i;
//		}
//	}
//	return max + 1;
//}
//int getminM(vector<vector<int>> a)
//{
//	vector<int> SM(m);
//	for (int i = 0;i < m;i++) {
//		if (a[i].size() != 0) {
//			SM[i] = Job[a[i][0] - 1].r + st[i].s[a[i][0] - 1][a[i][0] - 1] + Job[a[i][0] - 1].p[i];
//			for (int j = 1;j < a[i].size();j++) {
//				if (Job[a[i][j] - 1].r <= SM[i]) {
//					SM[i] += st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
//				}
//				else {
//					SM[i] = Job[a[i][j] - 1].r + st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
//				}
//			}
//		}
//	}
//	int min = 0;
//	for (int i = 0;i < m;i++) {
//		if (SM[min] > SM[i]) {
//			min = i;
//		}
//	}
//	return min + 1;
//}
//void VND()
//{
//	for (int o = 0;o < pope;o++) {
//		vector<vector<int>> S;
//		S = group[o].b;
//		int t = 1;
//		vector<vector<int>> SM(2, vector<int>(m));
//		for (int i = 0;i < m;i++) {
//			SM[0][i] = i + 1;
//			SM[1][i] = getSM(S, i);
//		}
//		while (t != 3) {
//			if (t == 1) {//将最大完工时间机器上的工件随机选择放入最低完工时间上，直到达到局部最优
//				while (true) {
//					//对机器的完工时间进行非递减排列
//					for (int i = 0;i < m;i++) {
//						for (int j = 0;j < m - 1 - i;j++) {
//							if (SM[1][j] > SM[1][j + 1]) {
//								swap(SM[0][j], SM[0][j + 1]);
//								swap(SM[1][j], SM[1][j + 1]);
//							}
//						}
//					}
//					vector<int> U;//记录最大完工时间上的机器
//					for (int i = 0;i < S[SM[0][m - 1] - 1].size();i++) {
//						U.push_back(S[SM[0][m - 1] - 1][i]);
//					}
//					int num = U.size();
//					while (num > 0) {
//						int r = rand() % U.size();
//						while (U[r] == 0) {
//							r = rand() % U.size();
//						}
//						if (SM[1][m - 1] - SM[1][0] < Job[U[r] - 1].p[SM[0][0] - 1]) {
//							U[r] = 0;
//							num--;
//						}
//						else {
//							//分配到使得机器完工时间最小的位置
//							for (int i = r + 1;i < S[SM[0][m - 1] - 1].size();i++) {
//								S[SM[0][m - 1] - 1][i - 1] = S[SM[0][m - 1] - 1][i];
//							}
//							S[SM[0][m - 1] - 1].pop_back();
//							int W = 1;//记录最佳位置
//							int CM = 0;//记录最佳位置的完工时间
//							for (int i = 1;i <= S[SM[0][0] - 1].size() + 1;i++) {
//								if (S[SM[0][0] - 1].size() == 0) {
//									S[SM[0][0] - 1].push_back(U[r]);
//								}
//								else {
//									S[SM[0][0] - 1].push_back({});
//									for (int j = S[SM[0][0] - 1].size() - 2;j >= i - 1;j--) {
//										S[SM[0][0] - 1][j + 1] = S[SM[0][0] - 1][j];
//									}
//									S[SM[0][0] - 1][i - 1] = U[r];
//								}
//								int Cm = getSM(S, SM[0][0] - 1);
//								if (CM == 0) {
//									W = i;
//									CM = Cm;
//								}
//								else {
//									if (Cm < CM) {
//										W = i;
//										CM = Cm;
//									}
//								}
//								for (int j = i;j < S[SM[0][0] - 1].size();j++) {
//									S[SM[0][0] - 1][j - 1] = S[SM[0][0] - 1][j];
//								}
//								S[SM[0][0] - 1].pop_back();
//							}
//							int CM1 = getSM(S, SM[0][m - 1] - 1);
//							if (CM < SM[1][m - 1] && CM1 < SM[1][m - 1]) {
//								if (S[SM[0][0] - 1].size() == 0) {
//									S[SM[0][0] - 1].push_back(U[r]);
//								}
//								else {
//									S[SM[0][0] - 1].push_back({});
//									for (int j = S[SM[0][0] - 1].size() - 2;j >= W - 1;j--) {
//										S[SM[0][0] - 1][j + 1] = S[SM[0][0] - 1][j];
//									}
//									S[SM[0][0] - 1][W - 1] = U[r];
//								}
//								SM[1][m - 1] = CM1;
//								SM[1][0] = CM;
//								break;
//							}
//							else {
//								if (S[SM[0][m - 1] - 1].size() == 0) {
//									S[SM[0][m - 1] - 1].push_back(U[r]);
//								}
//								else {
//									S[SM[0][m - 1] - 1].push_back({});
//									for (int j = S[SM[0][m - 1] - 1].size() - 2;j >= r;j--) {
//										S[SM[0][m - 1] - 1][j + 1] = S[SM[0][m - 1] - 1][j];
//									}
//									S[SM[0][m - 1] - 1][r] = U[r];
//								}
//								U[r] = 0;
//								num--;
//							}
//						}
//					}
//					if (num == 0) {
//						break;
//					}
//				}
//			}
//			if (t == 2) {
//				while (true) {
//					//对机器的完工时间进行非递减排列
//					for (int i = 0;i < m;i++) {
//						for (int j = 0;j < m - 1 - i;j++) {
//							if (SM[1][j] > SM[1][j + 1]) {
//								swap(SM[0][j], SM[0][j + 1]);
//								swap(SM[1][j], SM[1][j + 1]);
//							}
//						}
//					}
//					//将最大完工时间机器上的每个工件与最小完工时间机器上的随机一个工件交换
//					int i = 0;
//					for (i = 0;i < S[SM[0][m - 1] - 1].size();i++) {
//						vector<int> U;
//						for (int j = 0;j < S[SM[0][0] - 1].size();j++) {
//							U.push_back(S[SM[0][0] - 1][j]);
//						}
//						int num = U.size();//记录不为0的个数
//						while (num > 0) {
//							int r = rand() % U.size();
//							while (U[r] == 0) {
//								r = rand() % U.size();
//							}
//							swap(S[SM[0][m - 1] - 1][i], S[SM[0][0] - 1][r]);
//							int CM1 = getSM(S, SM[0][m - 1] - 1);
//							int CM2 = getSM(S, SM[0][0] - 1);
//							if (CM1 < SM[1][m - 1] && CM2 < SM[1][m - 1]) {
//								SM[1][m - 1] = CM1;
//								SM[1][0] = CM2;
//								break;
//							}
//							else {
//								swap(S[SM[0][m - 1] - 1][i], S[SM[0][0] - 1][r]);
//								U[r] = 0;
//								num--;
//							}
//						}
//						if (num != 0) {
//							break;
//						}
//					}
//					if (i == S[SM[0][m - 1] - 1].size()) {
//						break;
//					}
//				}
//			}
//			if (getCmax(S) < group[o].truefit) {
//				group[o].b = S;
//				group[o].truefit = getCmax(S);
//				group[o].C = getC(group[o].b);
//				t = 1;
//			}
//			else {
//				t++;
//			}
//		}
//		for (int i = 0;i < m;i++) {
//			int s = S[i].size();
//			for (int j = 0;j < s;j++) {
//				S[i].pop_back();
//			}
//		}
//		for (int i = 0;i < m;i++) {
//			S.pop_back();
//		}
//	}
//}
//int main()
//{
// 	srand((unsigned)time(NULL));
//	for (int NM = 1;NM <= NNMN;NM++) {
//		switch (NM) {
//		case 1:m = 2;n = 6;break;
//		case 2:m = 2;n = 8;break;
//		case 3:m = 3;n = 8;break;
//		case 4:m = 3;n = 10;break;
//		case 5:m = 5;n = 10;break;
//		case 6:m = 5;n = 12;break;
//		}
//		m = 5;n = 12;
//	//for (int NM = 1;NM <= NNM;NM++) {
//	//	switch (NM) {
//	//	case 1:m = 10;break;
//	//	case 2:m = 15;break;
//	//	case 3:m = 20;break;
//	//	}
//	//	for (int NN = 1;NN <= NNN;NN++) {
//	//		switch (NN) {
//	//		case 1:n = 150;break;
//	//		case 2:n = 200;break;
//	//		case 3:n = 250;break;
//	//		case 4:n = 300;break;
//	//		}
//			for (int NS = 1;NS <= NNS;NS++) {
//				switch (NS) {
//				case 1:Max_st = 9;break;
//				case 2:Max_st = 49;break;
//				case 3:Max_st = 99;break;;
//				case 4:Max_st = 124;break;
//				}
//				for (int Na = 1;Na <= NNa;Na++) {
//					switch (Na)
//					{
//					case 1:alpha = 0.05;break;
//					case 2:alpha = 0.5;break;
//					}
//					alpha = 0.05;
//					//// 记录每个案例的平均最大完工时间，最优最大完工时间，平均取得最优解的时间
//					//string A = "C:\\Users\\Lenovo\\Desktop\\Rm rj sijk C Cmax\\Experimental-results\\Small-sized-instances\\BRKGA";
//					//char Excel[100];
//					//sprintf_s(Excel, "M%d_N%d_P%d_P%d_S%d_S%d_alpha%0.2f.xls", m, n, min_pt, max_pt, Min_st, Max_st, alpha);
//					//string fileName = A + Excel;
//					//ofstream OutFile(fileName, ios::out | ios::app);
//
//					//OutFile << "ID" << "\t";
//					//OutFile << "BX_Cmax" << "\t";
//					//OutFile << "AVG_Cmax" << "\t";
//					//OutFile << "AVG_genBest" << "\t";
//					//OutFile << "TimeLimit" << "\t";
//					//OutFile << "AVG_CUPTime" << "\t";
//					//OutFile << "Rf" << "\t";
//					//OutFile << endl;
//					//OutFile.precision(10);
//
//					for (int NA = 0;NA < NNA;NA++) {
//						TL = 1;
//						//TL = (double)10 * m * n / 1000;
//						cout << "*********************the results of instance- " << NA + 1 << "*******************************" << endl;
//						int na = ceil((double(NA + 1) / 2));
//						switch (na) {
//						case 1:Rf = 0.2;break;
//						case 2:Rf = 0.6;break;
//						case 3:Rf = 1.0;break;
//						case 4:Rf = 1.4;break;
//						case 5:Rf = 1.8;break;
//						}
//						pop = 120;
//						pope = ceil(0.25 * pop);
//						popm = ceil(0.3 * pop);
//						cout << "Max_st：" << Max_st << " " << "m：" << m << " " << "n：" << n << " " << "alpha：" << alpha << " " << "Rf：" << Rf << endl;
//						FILE* infile = nullptr;
//						char filename[500];
//						sprintf_s(filename, "C:\\Users\\Lenovo\\Desktop\\Rm rj sijk C Cmax\\Benchmark-instances\\Small-sized-instances\\M%d_N%d_P%d_P%d_S%d_S%d_alpha%0.2f_Rf%0.2f_%d.txt",
//							m, n, min_pt, max_pt, Min_st, Max_st, alpha, Rf, NA + 1);
//
//
//						if ((infile = fopen(filename, "r")) == NULL) {
//							printf("could not open file %s\n", filename);
//						}
//						f_ReadData(infile);
//						fclose(infile);
//						int sum_Cmax = 0;//记录最大完工时间之和
//						int sum_C = 0;//记录成本之和
//						double sumtime = 0;//记录求得最优解的时间之和
//						int sumgen = 0;//记录求得最优解的迭代次数之和
//						int BestCmax = 0;//记录求解到的最优最大完工时间
//						int BestC = 0;//记录求解到最优最大完工时间的成本
//						for (int T = 0;T < Time;T++) {
//							gen = 0;//记录迭代数
//							genBest = 0;//记录找到最优解的代数
//							double CPUT;
//							time_t GA_start_it, GA_finish_it, BXCPUT_it;
//							BXCPUT = 0;
//							GA_start_it = clock();
//							//初始化种群
//							Initgroup();
//							//解码，求适应度
//							for (int i = 0;i < pop;i++)
//							{
//								group[i].truefit = getfitness(i);
//								group[i].C = getC(group[i].b);
//							}
//							//如果种群中不存在满足成本的解则对最好的解进行修复
//							int num = 0;
//							for (int i = 0;i < pop;i++) {
//								if (group[i].C <= budget) {
//									num++;
//								}
//							}
//							if (num == 0) {
//								int min = 0;
//								for (int i = 0;i < pop;i++) {
//									if (group[i].truefit < group[min].truefit) {
//										min = i;
//									}
//								}
//								CS = group[min].C;
//								repair(min, 1);
//								group[min].C = CS;
//								group[min].truefit = getCmax(group[min].b);
//								for (int i = 0;i < m;i++) {
//									if (group[min].b[i].size() == 0) {
//										continue;
//									}
//									else {
//										vector<double> dn(group[min].b[i].size());
//										for (int j = 0;j < group[min].b[i].size();j++) {
//											dn[j] = i + 1 + rand() / (RAND_MAX + 1.0);
//										}
//										for (int j = 0;j < group[min].b[i].size();j++) {
//											for (int k = 0;k < group[min].b[i].size() - 1 - j;k++) {
//												if (dn[k] > dn[k + 1]) {
//													swap(dn[k], dn[k + 1]);
//												}
//											}
//										}
//										for (int j = 0;j < group[min].b[i].size();j++) {
//											group[min].a[group[min].b[i][j] - 1] = dn[j];
//										}
//									}
//								}
//							}
//							//更新全局最优解（满足成本的最优解）
//							for (int i = 0;i < pop;i++) {
//								if (group[i].C <= budget) {
//									if (gbest.b.size() == 0) {
//										for (int j = 0;j < n;j++) {
//											gbest.a[j] = group[i].a[j];
//										}
//										for (int j = 0;j < m;j++) {
//											gbest.b.push_back({});
//										}
//										for (int j = 0;j < m;j++) {
//											for (int k = 0;k < group[i].b[j].size();k++) {
//												gbest.b[j].push_back(group[i].b[j][k]);
//											}
//										}
//										gbest.truefit = group[i].truefit;
//										gbest.C = group[i].C;
//										genBest = gen;
//										BXCPUT_it = clock();
//										BXCPUT = (double)(BXCPUT_it - GA_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
//									}
//									else {
//										if (gbest.truefit > group[i].truefit) {
//											for (int j = 0;j < n;j++) {
//												gbest.a[j] = group[i].a[j];
//											}
//											for (int j = 0;j < m;j++) {
//												int s = gbest.b[j].size();
//												for (int k = 0;k < s;k++) {
//													gbest.b[j].pop_back();
//												}
//											}
//											for (int j = 0;j < m;j++) {
//												for (int k = 0;k < group[i].b[j].size();k++) {
//													gbest.b[j].push_back(group[i].b[j][k]);
//												}
//											}
//											gbest.truefit = group[i].truefit;
//											gbest.C = group[i].C;
//											genBest = gen;
//											BXCPUT_it = clock();
//											BXCPUT = (double)(BXCPUT_it - GA_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
//										}
//									}
//								}
//							}
//							cout << "初始最优解：" << endl;
//							for (int i = 0;i < m;i++) {
//								for (int j = 0;j < gbest.b[i].size();j++) {
//									cout << gbest.b[i][j] << " ";
//								}
//								cout << endl;
//							}
//							cout << gbest.truefit << " " << gbest.C << endl;
//							//cout << BXCPUT << endl;
//							do
//							{
//								gen++;
//								//对所有的精英个体采用VND
//								for (int i = 0;i < pop;i++)
//								{
//									for (int j = 0;j < pop - 1 - i;j++)
//									{
//										if (group[j].truefit > group[j + 1].truefit)
//										{
//											swap(group[j], group[j + 1]);
//										}
//									}
//								}
//								VND();
//								//对精英个体重新编码，并且更新适应度
//								for (int o = 0;o < pope;o++) {
//									for (int i = 0;i < m;i++) {
//										if (group[o].b[i].size() == 0) {
//											continue;
//										}
//										else {
//											vector<double> dn(group[o].b[i].size());
//											for (int j = 0;j < group[o].b[i].size();j++) {
//												dn[j] = i + 1 + rand() / (RAND_MAX + 1.0);
//											}
//											for (int j = 0;j < group[o].b[i].size();j++) {
//												for (int k = 0;k < group[o].b[i].size() - 1 - j;k++) {
//													if (dn[k] > dn[k + 1]) {
//														swap(dn[k], dn[k + 1]);
//													}
//												}
//											}
//											for (int j = 0;j < group[o].b[i].size();j++) {
//												group[o].a[group[o].b[i][j] - 1] = dn[j];
//											}
//										}
//									}
//								}
//								//对个体进行非递减排序
//								for (int i = 0;i < pop;i++)
//								{
//									for (int j = 0;j < pop - i - 1;j++)
//									{
//										if (group[j].truefit > group[j + 1].truefit)
//										{
//											swap(group[j], group[j + 1]);
//										}
//									}
//								}
//								//产生子代
//								for (int i = 0;i < pope;i++) {
//									ngroup[i] = group[i];
//								}
//								//产生popm个变异的个体
//								//for (int i = pope;i < pope + popm;i++) {
//								//	int r = rand() % pop;
//								//	ngroup[i] = group[r];
//								//	int w = rand() % n;
//								//	ngroup[i].a[w] = 1 + m * rand() / (RAND_MAX + 1.0);
//								//}
//								//随机产生popm个新的个体
//								for (int i = pope;i < pope + popm;i++) {
//									for (int w = 0;w < n;w++) {
//										ngroup[i].a[w] = 1 + m * rand() / (RAND_MAX + 1.0);
//									}
//								}
//								for (int i = pope + popm;i < pop;i++) {
//									int r1 = rand() % pope;
//									int r2 = pope + rand() % (pop - pope);
//									for (int j = 0;j < n;j++) {
//										double P = rand() / (RAND_MAX + 1.0);
//										if (P < Pe)
//										{
//											ngroup[i].a[j] = group[r1].a[j];
//										}
//										else
//										{
//											ngroup[i].a[j] = group[r2].a[j];
//										}
//									}
//								}
//								for (int i = 0;i < pop;i++) {
//									for (int j = 0;j < n;j++) {
//										group[i].a[j] = ngroup[i].a[j];
//									}
//									for (int j = 0;j < m;j++) {
//										int s = group[i].b[j].size();
//										for (int k = 0;k < s;k++) {
//											group[i].b[j].pop_back();
//										}
//									}
//									for (int j = 0;j < m;j++) {
//										group[i].b.pop_back();
//									}
//								}
//								for (int i = 0;i < pop;i++) {
//									group[i].truefit = getfitness(i);
//									group[i].C = getC(group[i].b);
//								}
//								////如果种群中不存在满足成本的解则对最好的解进行修复
//								//for (int i = 0;i < pop;i++) {
//								//	for (int j = 0;j < m;j++) {
//								//		for (int k = 0;k < group[i].b[j].size();k++) {
//								//			cout << group[i].b[j][k] << " ";
//								//		}
//								//		cout << endl;
//								//	}
//								//	cout << group[i].truefit << " " << group[i].C << endl;
//								//}
//								int num = 0;
//								for (int i = 0;i < pop;i++) {
//									if (group[i].C <= budget) {
//										num++;
//									}
//								}
//								if (num == 0) {
//									int min = 0;
//									for (int i = 0;i < pop;i++) {
//										if (group[i].truefit < group[min].truefit) {
//											min = i;
//										}
//									}
//									CS = group[min].C;
//									if (rand() / (RAND_MAX + 1.0) < Pr) {
//										repair(min, 1);
//									}
//									else {
//										repair(min, 0);
//									}
//									group[min].C = CS;
//									group[min].truefit = getCmax(group[min].b);
//									for (int i = 0;i < m;i++) {
//										if (group[min].b[i].size() == 0) {
//											continue;
//										}
//										else {
//											vector<double> dn(group[min].b[i].size());
//											for (int j = 0;j < group[min].b[i].size();j++) {
//												dn[j] = i + 1 + rand() / (RAND_MAX + 1.0);
//											}
//											for (int j = 0;j < group[min].b[i].size();j++) {
//												for (int k = 0;k < group[min].b[i].size() - 1 - j;k++) {
//													if (dn[k] > dn[k + 1]) {
//														swap(dn[k], dn[k + 1]);
//													}
//												}
//											}
//											for (int j = 0;j < group[min].b[i].size();j++) {
//												group[min].a[group[min].b[i][j] - 1] = dn[j];
//											}
//										}
//									}
//								}
//								//更新全局最优解（满足成本的最优解）
//								for (int i = 0;i < pop;i++) {
//									if (group[i].C <= budget) {
//										if (gbest.truefit > group[i].truefit) {
//											for (int j = 0;j < n;j++) {
//												gbest.a[j] = group[i].a[j];
//											}
//											for (int j = 0;j < m;j++) {
//												int s = gbest.b[j].size();
//												for (int k = 0;k < s;k++) {
//													gbest.b[j].pop_back();
//												}
//											}
//											for (int j = 0;j < m;j++) {
//												for (int k = 0;k < group[i].b[j].size();k++) {
//													gbest.b[j].push_back(group[i].b[j][k]);
//												}
//											}
//											gbest.truefit = group[i].truefit;
//											gbest.C = group[i].C;
//											genBest = gen;
//											BXCPUT_it = clock();
//											BXCPUT = (double)(BXCPUT_it - GA_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
//										}
//									}
//								}
//								GA_finish_it = clock();
//								CPUT = (double)(GA_finish_it - GA_start_it) / CLOCKS_PER_SEC;
//							} while (CPUT < TL);
//							cout << "全局最优解：" << endl;
//							for (int i = 0;i < n;i++) {
//								cout << gbest.a[i] << " ";
//							}
//							cout << endl;
//							for (int i = 0;i < m;i++) {
//								for (int j = 0;j < gbest.b[i].size();j++) {
//									cout << gbest.b[i][j] << " ";
//								}
//								cout << endl;
//							}
//							cout << "BestObjectiveValue=" << gbest.truefit << "  MachineUsageCost=" << gbest.C << endl;
//							cout << "genBest=" << genBest << "  BXCPUT=" << BXCPUT << endl;
//							if (BestCmax == 0) {
//								BestCmax = gbest.truefit;
//								BestC = gbest.C;
//							}
//							else {
//								if (BestCmax > gbest.truefit) {
//									BestCmax = gbest.truefit;
//									BestC = gbest.C;
//								}
//							}
//							sum_Cmax += gbest.truefit;
//							sum_C += gbest.C;
//							sumgen += genBest;
//							sumtime += BXCPUT;
//							for (int i = 0;i < m;i++) {
//								int s = gbest.b[i].size();
//								for (int j = 0;j < s;j++) {
//									gbest.b[i].pop_back();
//								}
//							}
//							for (int i = 0;i < m;i++)
//							{
//								gbest.b.pop_back();
//							}
//							for (int i = 0;i < pop;i++) {
//								for (int j = 0;j < m;j++) {
//									int s = group[i].b[j].size();
//									for (int k = 0;k < s;k++) {
//										group[i].b[j].pop_back();
//									}
//								}
//								for (int j = 0;j < m;j++) {
//									group[i].b.pop_back();
//								}
//							}
//						}
//						cout << "AvgObjectiveValue=" << (double)sum_Cmax / Time << " AvgMachineUsageCost=" << (double)sum_C / Time << endl;
//						cout << "BestObjectiveValue=" << BestCmax << " MachineUsageCost=" << BestC << endl;
//						cout << "genBest=" << (double)sumgen / Time << " BXCPUT=" << (double)sumtime / Time << endl;
//						//OutFile << NA + 1 << "\t";
//						//OutFile << BestCmax << "\t";
//						//OutFile << (double)sum_Cmax / Time << "\t";
//						//OutFile << (double)sumgen / Time << "\t";
//						//OutFile << TL << "\t";
//						//OutFile << (double)sumtime / Time << "\t";
//						//OutFile << Rf << "\t" << endl;
//					}
//					//OutFile.close();
//				}
//			}
//		//}
//	}
//	system("pause");
//}
//void f_ReadData(FILE* infile)
//{
//	char tmp[100];
//	fscanf(infile, "%s", tmp);
//	int bg;
//	fscanf(infile, "%d", &bg);
//	budget = bg;
//	cout << budget << endl;
//	fscanf(infile, "%s", tmp);
//	int cost;
//	for (int i = 0;i < m;i++) {
//		fscanf(infile, "%d", &cost);
//		machine[i].price = cost;
//		//cout << machine[i].price << " ";
//	}
//	//cout << endl;
//	fscanf(infile, "%s", tmp);
//	int pt;
//	for (int i = 0;i < n;i++) {
//		for (int j = 0;j < m;j++) {
//			fscanf(infile, "%d", &pt);
//			Job[i].p[j] = pt;
//		}
//	}
//	fscanf(infile, "%s", tmp);
//	int r;
//	for (int i = 0;i < n;i++) {
//		fscanf(infile, "%d", &r);
//		Job[i].r = r;
//	}
//	fscanf(infile, "%s", tmp);
//	for (int i = 0;i < m;i++) {
//		int s;
//		for (int j = 0;j < n;j++) {
//			for (int k = 0;k < n;k++) {
//				fscanf(infile, "%d", &s);
//				st[i].s[j][k] = s;
//			}
//		}
//	}
//	//for (int i = 0;i < n;i++) {
//	//	for (int j = 0;j < m;j++) {
//	//		cout << Job[i].p[j] << " ";
//	//	}
//	//	cout << endl;
//	//}
//	//for (int i = 0;i < n;i++) {
//	//	cout << Job[i].r << endl;
//	//}
//	//cout << endl;
//	//for (int i = 0;i < m;i++) {
//	//	for (int j = 0;j < n;j++) {
//	//		for (int k = 0;k < n;k++) {
//	//			cout << st[i].s[j][k] << " ";
//	//		}
//	//		cout << endl;
//	//	}
//	//	cout << endl;
//	//}
//}
