//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<stdlib.h>
//#include<cmath>
//#include<vector>
//#include<unordered_map>
//#include<iomanip>
//#include<fstream>
//using namespace std;
//int m;//机器数
//int n;//工件数
//#define f 0.1//阿尔法
//#define Pr 0.7
//int CS;
//#define Kmax 8//扰动次数
//#define Max_Nmach 30//最大机器数
//#define Max_Njob 300/*最大工件数*/
//#define min_pt 1 //最小加工时间
//#define max_pt 99//最大加工时间
//double Rf;//（0.2，0.6，1.0，1.4，1.8）
//double alpha;//（0.05，0.5）
//int Max_st;//（9，49，99，124）
//#define Min_st 1
//#define NNM 3//机器类型数
//#define NNN 4//工件类型数
//#define NNS 4//设置时间类型数
//#define NNa 2
//#define NNMN 6
//#define NNR 5//到达时间类型数
//#define NNA 10//案例数
//#define NLS 4
//#define Time 5//案例运行次数
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
//class Gbest
//{
//public:
//	vector<vector<int>> a;
//	int truefit;
//	int C;
//};
//Gbest gbest;
//vector<vector<int>> TABU;
//vector<vector<int>> TABU1;
//int getfitness(vector<vector<int>> TABU)
//{
//	vector<int> SM(m);
//	for (int i = 0;i < m;i++) {
//		if (TABU[i].size() != 0) {
//			SM[i] = st[i].s[TABU[i][0] - 1][TABU[i][0] - 1] + Job[TABU[i][0] - 1].r + Job[TABU[i][0] - 1].p[i];
//			for (int j = 1;j < TABU[i].size();j++) {
//				if (Job[TABU[i][j] - 1].r <= SM[i]) {
//					SM[i] += st[i].s[TABU[i][j - 1] - 1][TABU[i][j] - 1] + Job[TABU[i][j] - 1].p[i];
//				}
//				else {
//					SM[i] = Job[TABU[i][j] - 1].r + st[i].s[TABU[i][j - 1] - 1][TABU[i][j] - 1] + Job[TABU[i][j] - 1].p[i];
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
//void CP() {
//	vector<int> U(n);
//	for (int i = 0;i < n;i++) {
//		U[i] = i + 1;
//	}
//	vector<int> SM(m);
//	//每个机器先安排在这个机器上加工时间最小的工件进行加工
//	for (int i = 0;i < m;i++) {
//		//在未调度的工件中选择在这个机器上加工后使得机器加工时间最小的
//		int J = 1;
//		int index = 0;
//		for (int j = 0;j < n;j++) {
//			if (U[j] != 0) {
//				J = U[j];
//				index = j;
//				break;
//			}
//		}
//		for (int j = 0;j < n;j++) {
//			if (U[j] != 0) {
//				if (st[i].s[J - 1][J - 1] + Job[J - 1].r + Job[J - 1].p[i] > st[i].s[U[j] - 1][U[j] - 1] + Job[U[j] - 1].r + Job[U[j] - 1].p[i]) {
//					J = U[j];
//					index = j;
//				}
//			}
//		}
//		TABU[i].push_back(J);
//		SM[i] = st[i].s[J - 1][J - 1] + Job[J - 1].r + Job[J - 1].p[i];
//		U[index] = 0;
//	}
//	int num = 0;
//	for (int i = 0;i < n;i++) {
//		if (U[i] != 0) {
//			num++;
//		}
//	}
//	while (num > 0) {
//		//选择具有最小完工时间的机器
//		int minm = 0;
//		for (int i = 0;i < m;i++) {
//			if (SM[minm] > SM[i]) {
//				minm = i;
//			}
//		}
//		//计算每一个候选工件集中工件插入的最佳位置以及变化值
//		vector<vector<int>> bw;//记录未调度工件的最佳位置和变化值，第一行是未调度的工件，第二行是最佳位置，第三行是变化值
//		for (int i = 0;i < 3;i++) {
//			bw.push_back({});
//		}
//		for (int i = 0;i < n;i++) {
//			if (U[i] != 0) {
//				//判断第U[i]个工件的最佳位置和变化值
//				//找最佳位置(插入这个工件后使得机器完工时间变化最小的)
//				int w = 1;//记录插入的最佳位置
//				int CM = 0;//记录插入最佳位置机器的完工时间
//				for (int j = 1;j <= TABU[minm].size() + 1;j++) {
//					//cout << "U[i]：" << U[i]<<" " << "j：" << j << endl;
//					TABU[minm].push_back({});
//					for (int k = TABU[minm].size() - 2;k >= j - 1;k--) {
//						TABU[minm][k + 1] = TABU[minm][k];
//					}
//					TABU[minm][j - 1] = U[i];
//					if (CM == 0) {
//						CM = getSM(TABU, minm);
//						w = j;
//					}
//					else {
//						if (CM > getSM(TABU, minm)) {
//							CM = getSM(TABU, minm);
//							w = j;
//						}
//					}
//					for (int k = j;k < TABU[minm].size();k++) {
//						TABU[minm][k - 1] = TABU[minm][k];
//					}
//					TABU[minm].pop_back();
//				}
//				bw[0].push_back(U[i]);
//				bw[1].push_back(w);
//				bw[2].push_back(CM);
//			}
//		}
//		//计算机器完工时间变化的最大和最小值
//		int max = 0;
//		int min = 0;
//		for (int i = 0;i < bw[2].size();i++) {
//			if (bw[2][max] < bw[2][i]) {
//				max = i;
//			}
//			if (bw[2][min] > bw[2][i]) {
//				min = i;
//			}
//		}
//		int chamax = bw[2][max] - SM[minm];
//		int chamin = bw[2][min] - SM[minm];
//		//创建限制候选列表
//		vector<int> RCL;
//		for (int i = 0;i < bw[0].size();i++) {
//			if (bw[2][i] - SM[minm] <= chamin + f * (chamax - chamin)) {
//				RCL.push_back(bw[0][i]);
//			}
//		}
//		//随机从限制列表中选择工件进行调度
//		int l = rand() % RCL.size();
//		//插入对应的最佳位置
//		int index = 0;
//		for (int i = 0;i < bw[0].size();i++) {
//			if (bw[0][i] == RCL[l]) {
//				index = i;
//				break;
//			}
//		}
//		//将第RCL[l]个工件插入到第bw[1][index]个位置
//		TABU[minm].push_back({});
//		for (int i = TABU[minm].size() - 2;i >= bw[1][index] - 1;i--) {
//			TABU[minm][i + 1] = TABU[minm][i];
//		}
//		TABU[minm][bw[1][index] - 1] = RCL[l];
//		SM[minm] = bw[2][index];
//		int index1 = 0;
//		for (int i = 0;i < n;i++) {
//			if (U[i] == RCL[l]) {
//				index1 = i;
//				break;
//			}
//		}
//		U[index1] = 0;
//		num = 0;
//		for (int i = 0;i < n;i++) {
//			if (U[i] != 0) {
//				num++;
//			}
//		}
//	}
//}
//void RVND()
//{
//	//随机选择局部搜索进行操作
//	vector<int> LS(NLS);
//	for (int i = 0;i < NLS;i++) {
//		LS[i] = 1;
//	}
//	int num = 0;
//	for (int i = 0;i < NLS;i++) {
//		if (LS[i] != 0) {
//			num++;
//		}
//	}
//	while (num > 0) {
//		int r = rand() % NLS;
//		while (LS[r] == 0) {
//			r = rand() % NLS;
//		}
//		if (r == 0) {
//			//交换最大完工机器上的工件（固定机器上的一个工件，交换工件之后的每个工件选择最好的
//			int M = getmaxM(TABU1);
//			int w = rand() % TABU1[M - 1].size();
//			int w1 = 0;//记录选择交换的位置
//			int Cmax = 0;//记录交换后的最大完工时间
//			for (int i = w + 2;i < TABU1[M - 1].size();i++) {
//				swap(TABU1[M - 1][w], TABU1[M - 1][i]);
//				int CM = getfitness(TABU1);
//				if (Cmax == 0) {
//					w1 = i;
//					Cmax = CM;
//				}
//				else {
//					if (CM < Cmax) {
//						w1 = i;
//						Cmax = CM;
//					}
//				}
//				swap(TABU1[M - 1][w], TABU1[M - 1][i]);
//			}
//			swap(TABU1[M - 1][w], TABU1[M - 1][w1]);
//		}
//		if (r == 1) {
//			//将最大完工机器上的工件插入到机器上的其它位置，选择最好的
//			int M = getmaxM(TABU1);
//			int w = rand() % TABU1[M - 1].size();
//			int J = TABU1[M - 1][w];
//			int W = 0;//记录最好的插入位置
//			int Cmax = 0;//记录插入最好位置的最大完工时间
//			for (int i = 1;i <= TABU1[M - 1].size() + 1;i++) {
//				if (i < w + 1) {
//					for (int j = w - 1;j >= i - 1;j--) {
//						TABU1[M - 1][j + 1] = TABU1[M - 1][j];
//					}
//					TABU1[M - 1][i - 1] = J;
//					int CM = getfitness(TABU1);
//					if (Cmax == 0) {
//						W = i;
//						Cmax = CM;
//					}
//					else {
//						if (Cmax > CM) {
//							W = i;
//							Cmax = CM;
//						}
//					}
//					for (int j = i;j <= w;j++) {
//						TABU1[M - 1][j - 1] = TABU1[M - 1][j];
//					}
//					TABU1[M - 1][w] = J;
//				}
//				if (i > w + 2) {
//					for (int j = w + 1;j <= i - 2;j++) {
//						TABU1[M - 1][j - 1] = TABU1[M - 1][j];
//					}
//					TABU1[M - 1][i - 2] = J;
//					int CM = getfitness(TABU1);
//					if (Cmax == 0) {
//						W = i;
//						Cmax = CM;
//					}
//					else {
//						if (Cmax > CM) {
//							W = i;
//							Cmax = CM;
//						}
//					}
//					for (int j = i - 3;j >= w;j--) {
//						TABU1[M - 1][j + 1] = TABU1[M - 1][j];
//					}
//					TABU1[M - 1][w] = J;
//				}
//				if (i == w + 1 || i == w + 2) {
//					int CM = getfitness(TABU1);
//					if (Cmax == 0) {
//						W = i;
//						Cmax = CM;
//					}
//					else {
//						if (Cmax > CM) {
//							W = i;
//							Cmax = CM;
//						}
//					}
//				}
//			}
//			if (W < w + 1) {
//				for (int j = w - 1;j >= W - 1;j--) {
//					TABU1[M - 1][j + 1] = TABU1[M - 1][j];
//				}
//				TABU1[M - 1][W - 1] = J;
//			}
//			if (W > w + 2) {
//				for (int j = w + 1;j <= W - 2;j++) {
//					TABU1[M - 1][j - 1] = TABU1[M - 1][j];
//				}
//				TABU1[M - 1][W - 2] = J;
//			}
//		}
//		if (r == 2) {
//			//将具有最大完工时间机器上的工件与其它机器上的工件进行交换（固定最大完工时间机器上的工件，与其它机器上的工件进行一一交换）
//			int M = getmaxM(TABU1);
//			int w = rand() % TABU1[M - 1].size();
//			int num = 0;
//			for (int i = 0;i < m;i++) {
//				if (TABU1[i].size() != 0) {
//					num++;
//				}
//			}
//			if (num >= 2) {
//				int M1 = rand() % m;
//				while (M == M1 + 1 || TABU1[M1].size() == 0) {
//					M1 = rand() % m;
//				}
//				int w1 = 0;//记录交换的最佳工件
//				int Cmax = 0;//记录交换后的最大完工时间
//				for (int i = 0;i < TABU1[M1].size();i++) {
//					swap(TABU1[M1][i], TABU1[M - 1][w]);
//					int CM = getfitness(TABU1);
//					if (Cmax == 0) {
//						w1 = i;
//						Cmax = CM;
//					}
//					else {
//						if (Cmax > CM) {
//							w1 = i;
//							Cmax = CM;
//						}
//					}
//					swap(TABU1[M1][i], TABU1[M - 1][w]);
//				}
//				swap(TABU1[M1][w1], TABU1[M - 1][w]);
//			}
//		}
//		if (r == 3) {
//			//将最大完工机器上的工件插入到其它机器上（固定最大完工机器上的工件，插入到其它机器上的各个位置选择最优的）
//			int M = getmaxM(TABU1);
//			int w = rand() % TABU1[M - 1].size();
//			int J = TABU1[M - 1][w];
//			int M1 = rand() % m;
//			while (M == M1 + 1) {
//				M1 = rand() % m;
//			}
//			int W = 0;//记录插入的位置
//			int Cmax = 0;//记录插入后的最大完工时间
//			for (int i = 1;i <= TABU1[M1].size() + 1;i++) {
//				if (TABU1[M1].size() == 0) {
//					TABU1[M1].push_back(TABU1[M - 1][w]);
//				}
//				else {
//					TABU1[M1].push_back({});
//					for (int j = TABU1[M1].size() - 2;j >= i - 1;j--) {
//						TABU1[M1][j + 1] = TABU1[M1][j];
//					}
//					TABU1[M1][i - 1] = TABU1[M - 1][w];
//				}
//				for (int j = w + 1;j < TABU1[M - 1].size();j++) {
//					TABU1[M - 1][j - 1] = TABU1[M - 1][j];
//				}
//				TABU1[M - 1].pop_back();
//				int CM = getfitness(TABU1);
//				if (Cmax == 0) {
//					W = i;
//					Cmax = CM;
//				}
//				else {
//					if (Cmax > CM) {
//						W = i;
//						Cmax = CM;
//					}
//				}
//				if (TABU1[M - 1].size() == 0) {
//					TABU1[M - 1].push_back(J);
//				}
//				else {
//					TABU1[M - 1].push_back({});
//					for (int j = TABU1[M - 1].size() - 2;j >= w;j--) {
//						TABU1[M - 1][j + 1] = TABU1[M - 1][j];
//					}
//					TABU1[M - 1][w] = J;
//				}
//				for (int j = i;j < TABU1[M1].size();j++)
//				{
//					TABU1[M1][j - 1] = TABU1[M1][j];
//				}
//				TABU1[M1].pop_back();
//			}
//			if (TABU1[M1].size() == 0) {
//				TABU1[M1].push_back(TABU1[M - 1][w]);
//			}
//			else {
//				TABU1[M1].push_back({});
//				for (int j = TABU1[M1].size() - 2;j >= W - 1;j--) {
//					TABU1[M1][j + 1] = TABU1[M1][j];
//				}
//				TABU1[M1][W - 1] = TABU1[M - 1][w];
//			}
//			for (int j = w + 1;j < TABU1[M - 1].size();j++) {
//				TABU1[M - 1][j - 1] = TABU1[M - 1][j];
//			}
//			TABU1[M - 1].pop_back();
//		}
//		if (getfitness(TABU1) < getfitness(TABU)) {
//			for (int i = 0;i < m;i++) {
//				int s = TABU[i].size();
//				for (int j = 0;j < s;j++) {
//					TABU[i].pop_back();
//				}
//			}
//			for (int i = 0;i < m;i++) {
//				for (int j = 0;j < TABU1[i].size();j++) {
//					TABU[i].push_back(TABU1[i][j]);
//				}
//			}
//			for (int i = 0;i < NLS;i++) {
//				LS[i] = 1;
//			}
//		}
//		else {
//			for (int i = 0;i < m;i++) {
//				int s = TABU1[i].size();
//				for (int j = 0;j < s;j++) {
//					TABU1[i].pop_back();
//				}
//			}
//			for (int i = 0;i < m;i++) {
//				for (int j = 0;j < TABU[i].size();j++) {
//					TABU1[i].push_back(TABU[i][j]);
//				}
//			}
//			LS[r] = 0;
//		}
//		num = 0;
//		for (int i = 0;i < NLS;i++) {
//			if (LS[i] != 0) {
//				num++;
//			}
//		}
//	}
//}
//void IP()
//{
//	//先对初始解用局部搜索进行改进
//	for (int i = 0;i < m;i++) {
//		TABU1.push_back({});
//	}
//	for (int i = 0;i < m;i++) {
//		for (int j = 0;j < TABU[i].size();j++) {
//			TABU1[i].push_back(TABU[i][j]);
//		}
//	}
//	RVND();
//	for (int i = 0;i < m;i++) {
//		int s = TABU1[i].size();
//		for (int j = 0;j < s;j++) {
//			TABU1[i].pop_back();
//		}
//	}
//	for (int i = 0;i < m;i++) {
//		for (int j = 0;j < TABU[i].size();j++) {
//			TABU1[i].push_back(TABU[i][j]);
//		}
//	}
//	int k = 1;
//	while (k <= Kmax) {
//		//对解决方案进行部分破坏然后进行重构
//		//破坏
//		vector<int> U;//候选工件列表
//		int r = floor(0.1 * n * k);
//		while (r > 0) {
//			//从有工件的机器中随机选择选择一个工件放回候选工件中
//			int M = rand() % m;
//			while (TABU1[M].size() == 0) {
//				M = rand() % m;
//			}
//			int j = rand() % TABU1[M].size();
//			U.push_back(TABU1[M][j]);
//			for (int i = j + 1;i < TABU1[M].size();i++) {
//				TABU1[M][i - 1] = TABU1[M][i];
//			}
//			TABU1[M].pop_back();
//			r--;
//		}
//		//修复
//		//将候选工件中的工件重新在机器上加工（选择加工时间最小的机器，选择在这个机器上加工时间最短的工件插入到最佳位置）
//		//计算机器的完工时间
//		vector<int> SM(m);
//		for (int i = 0;i < m;i++) {
//			SM[i] = getSM(TABU1, i);
//		}
//		int num = 0;
//		for (int i = 0;i < U.size();i++) {
//			if (U[i] != 0) {
//				num++;
//			}
//		}
//		while (num > 0) {
//			int minm = 0;
//			for (int i = 0;i < m;i++) {
//				if (SM[minm] > SM[i]) {
//					minm = i;
//				}
//			}
//			//记录候选工件插入机器中最佳位置的完工时间，选择使得机器完工时间最小的
//			vector<vector<int>> bw;
//			for (int i = 0;i < 3;i++) {
//				bw.push_back({});
//			}
//			for (int i = 0;i < U.size();i++) {
//				if (U[i] != 0) {
//					//将第U[i]个工件插入到机器上的最佳位置
//					int w = 1;//记录插入的最佳位置
//					int CM = 0;//记录插入最佳位置的时间
//					for (int j = 1;j <= TABU1[minm].size() + 1;j++) {
//						if (TABU1[minm].size() == 0) {
//							TABU1[minm].push_back(U[i]);
//						}
//						else {
//							TABU1[minm].push_back({});
//							for (int k = TABU1[minm].size() - 2;k >= j - 1;k--) {
//								TABU1[minm][k + 1] = TABU1[minm][k];
//							}
//							TABU1[minm][j - 1] = U[i];
//						}
//						if (CM == 0) {
//							CM = getSM(TABU1, minm);
//							w = j;
//						}
//						else {
//							if (CM > getSM(TABU1, minm)) {
//								CM = getSM(TABU1, minm);
//								w = j;
//							}
//						}
//						for (int k = j;k < TABU1[minm].size();k++) {
//							TABU1[minm][k - 1] = TABU1[minm][k];
//						}
//						TABU1[minm].pop_back();
//					}
//					bw[0].push_back(U[i]);
//					bw[1].push_back(w);
//					bw[2].push_back(CM);
//				}
//			}
//			int min = 0;
//			for (int i = 0;i < bw[0].size();i++) {
//				if (bw[2][min] > bw[2][i]) {
//					min = i;
//				}
//			}
//			//将第bw[0][min]个工件插入第bw[1][min]个位置
//			SM[minm] = bw[2][min];
//			if (TABU1[minm].size() == 0) {
//				TABU1[minm].push_back(bw[0][min]);
//			}
//			else {
//				TABU1[minm].push_back({});
//				for (int i = TABU1[minm].size() - 2;i >= bw[1][min] - 1;i--) {
//					TABU1[minm][i + 1] = TABU1[minm][i];
//				}
//				TABU1[minm][bw[1][min] - 1] = bw[0][min];
//			}
//			int index = 0;
//			for (int i = 0;i < U.size();i++) {
//				if (U[i] == bw[0][min]) {
//					index = i;
//				}
//			}
//			U[index] = 0;
//			num = 0;
//			for (int i = 0;i < U.size();i++) {
//				if (U[i] != 0) {
//					num++;
//				}
//			}
//		}
//		vector<vector<int>> TABU2;
//		TABU2 = TABU;
//		TABU = TABU1;
//		//局部搜索
//		RVND();
//		TABU = TABU2;
//		if (getfitness(TABU1) < getfitness(TABU)) {
//			for (int i = 0;i < m;i++) {
//				int s = TABU[i].size();
//				for (int j = 0;j < s;j++) {
//					TABU[i].pop_back();
//				}
//			}
//			for (int i = 0;i < m;i++) {
//				for (int j = 0;j < TABU1[i].size();j++) {
//					TABU[i].push_back(TABU1[i][j]);
//				}
//			}
//			k = 1;
//		}
//		else {
//			TABU1 = TABU;
//			k++;
//		}
//	}
//	for (int i = 0;i < m;i++) {
//		int s = TABU1[i].size();
//		for (int j = 0;j < s;j++) {
//			TABU1[i].pop_back();
//		}
//	}
//	for (int i = 0;i < m;i++) {
//		TABU1.pop_back();
//	}
//}
//void dl(int i, int j)
//{
//	for (int k = j + 1;k < TABU[i].size();k++) {
//		TABU[i][k - 1] = TABU[i][k];
//	}
//	TABU[i].pop_back();
//}
//void Insert(int M, int W, int J)
//{
//	if (TABU[M - 1].size() == 0) {
//		TABU[M - 1].push_back(J);
//	}
//	else {
//		TABU[M - 1].push_back({});
//		for (int j = TABU[M - 1].size() - 2;j >= W - 1;j--) {
//			TABU[M - 1][j + 1] = TABU[M - 1][j];
//		}
//		TABU[M - 1][W - 1] = J;
//	}
//}
//void repair(int P)
//{
//	int cost = CS;
//	while (cost > budget) {
//		//每次迭代将存在比原来成本低的工件插入到最好的位置
//		vector<vector<int>> JM;
//		for (int i = 0;i < n;i++) {
//			JM.push_back({});
//		}
//		for (int i = 0;i < m;i++) {
//			for (int j = 0;j < TABU[i].size();j++) {
//				for (int k = 1;k <= m;k++) {
//					if (machine[i].price * Job[TABU[i][j] - 1].p[i] > machine[k - 1].price * Job[TABU[i][j] - 1].p[k - 1]) {
//						JM[TABU[i][j] - 1].push_back(k);
//					}
//				}
//			}
//		}
//		if (P == 0) {//随机修复
//			int r = rand() % n;
//			while (JM[r].size() == 0) {
//				r = rand() % n;
//			}
//			int r1 = rand() % JM[r].size();
//			int mindex = -1;
//			int windex = -1;
//			for (int i = 0;i < m;i++) {
//				for (int j = 0;j < TABU[i].size();j++) {
//					if (TABU[i][j] == r + 1) {
//						mindex = i;
//						windex = j;
//						break;
//					}
//				}
//				if (mindex != -1) {
//					break;
//				}
//			}
//			dl(mindex, windex);
//			int w = 1 + rand() % (1 + TABU[JM[r][r1] - 1].size());
//			Insert(JM[r][r1], w, r + 1);
//		}
//		else {
//			int mindex = 0;//记录选择工件的位置
//			int windex = 0;
//			int M = 1;//记录插入的机器
//			int W = 1;//记录插入的位置
//			int J;
//			int Cmax = 0;//记录插入后的最大完工时间
//			for (int i = 0;i < m;i++) {
//				if (TABU[i].size() == 0) {
//					continue;
//				}
//				else {
//					for (int j = 0;j < TABU[i].size();j++) {
//						if (JM[TABU[i][j] - 1].size() == 0) {
//							continue;
//						}
//						else {
//							J = TABU[i][j];
//							dl(i, j);
//							for (int k = 0;k < JM[J - 1].size();k++) {
//								for (int l = 1;l <= 1 + TABU[JM[J - 1][k] - 1].size();l++) {
//									Insert(JM[J - 1][k], l, J);
//									int C = getfitness(TABU);
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
//									dl(JM[J - 1][k] - 1, l - 1);
//								}
//							}
//							Insert(i + 1, j + 1, J);
//						}
//					}
//				}
//			}
//			J = TABU[mindex][windex];
//			dl(mindex, windex);
//			Insert(M, W, J);
//		}
//		cost = getC(TABU);
//	}
//	CS = cost;
//}
//int main()
//{
//	srand((unsigned)time(NULL));
//	//for (int NM = 1;NM <= NNMN;NM++) {
//	//	switch (NM) {
//	//	case 1:m = 2;n = 6;break;
//	//	case 2:m = 2;n = 8;break;
//	//	case 3:m = 3;n = 8;break;
//	//	case 4:m = 3;n = 10;break;
//	//	case 5:m = 5;n = 10;break;
//	//	case 6:m = 5;n = 12;break;
//	//	}
//	for (int NM = 1;NM <= NNM;NM++) {
//		switch (NM) {
//		case 1:m = 10;break;
//		case 2:m = 15;break;
//		case 3:m = 20;break;
//		}
//		for (int NN = 1;NN <= NNN;NN++) {
//			switch (NN) {
//			case 1:n = 150;break;
//			case 2:n = 200;break;
//			case 3:n = 250;break;
//			case 4:n = 300;break;
//			}
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
//
//					//// 记录每个案例的平均最大完工时间，最优最大完工时间，平均取得最优解的时间
//					//string A = "C:\\Users\\Lenovo\\Desktop\\Rm rj sijk C Cmax\\Experimental-results\\Small-sized-instances\\GRASP";
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
//						int na = ceil((double(NA + 1) / 2));
//						switch (na) {
//						case 1:Rf = 0.2;break;
//						case 2:Rf = 0.6;break;
//						case 3:Rf = 1.0;break;
//						case 4:Rf = 1.4;break;
//						case 5:Rf = 1.8;break;
//						}
//						TL = (double)10 * m * n / 1000;
//						//TL = 1;
//						cout << "*********************the results of instance- " << NA + 1 << "*******************************" << endl;
//						cout << "Max_st：" << Max_st << " " << "m：" << m << " " << "n：" << n << " " << "alpha：" << alpha << " " << "Rf：" << Rf << endl;
//						FILE* infile = nullptr;
//						char filename[200];
//						sprintf_s(filename, "C:\\Users\\Lenovo\\Desktop\\Rm rj sijk C Cmax\\Benchmark-instances\\Large-sized-instances\\M%d_N%d_P%d_P%d_S%d_S%d_alpha%0.2f_Rf%0.2f_%d.txt", m, n, min_pt, max_pt, Min_st, Max_st, alpha, Rf, NA + 1);
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
//							for (int i = 0;i < m;i++) {
//								gbest.a.push_back({});
//							}
//							double CPUT;
//							time_t GRASP_start_it, GRASP_finish_it, BXCPUT_it;
//							BXCPUT = 0;
//							GRASP_start_it = clock();
//							do {
//								//构造解
//								for (int i = 0;i < m;i++) {
//									TABU.push_back({});
//								}
//								CP();
//								IP();
//								CS = getC(TABU);
//								if (CS > budget) {
//									if (gen == 0) {
//										repair(1);
//									}
//									else {
//										if (rand() / (RAND_MAX + 1.0) < Pr) {
//											repair(1);
//										}
//										else {
//											repair(0);
//										}
//									}
//								}
//								if (gen == 0) {
//									gbest.a = TABU;
//									gbest.truefit = getfitness(gbest.a);
//									gbest.C = getC(gbest.a);
//									genBest = gen;
//									BXCPUT_it = clock();
//									BXCPUT = (double)(BXCPUT_it - GRASP_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
//									//cout << "初始最优解：" << endl;
//									//for (int i = 0;i < m;i++) {
//									//	for (int j = 0;j < gbest.a[i].size();j++) {
//									//		cout << gbest.a[i][j] << " ";
//									//	}
//									//	cout << endl;
//									//}
//									//cout << gbest.truefit << " " << gbest.C << endl;
//								}
//								else {
//									if (getC(TABU) <= budget) {
//										if (getfitness(TABU) < gbest.truefit) {
//											gbest.a = TABU;
//											gbest.truefit = getfitness(gbest.a);
//											gbest.C = getC(gbest.a);
//											genBest = gen;
//											BXCPUT_it = clock();
//											BXCPUT = (double)(BXCPUT_it - GRASP_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
//										}
//									}
//								}
//								for (int i = 0;i < m;i++) {
//									int s = TABU[i].size();
//									for (int j = 0;j < s;j++) {
//										TABU[i].pop_back();
//									}
//								}
//								for (int i = 0;i < m;i++) {
//									TABU.pop_back();
//								}
//								gen++;
//								GRASP_finish_it = clock();
//								CPUT = (double)(GRASP_finish_it - GRASP_start_it) / CLOCKS_PER_SEC;
//							} while (CPUT < TL);
//							cout << "全局最优解：" << endl;
//							for (int i = 0;i < m;i++) {
//								for (int j = 0;j < gbest.a[i].size();j++) {
//									cout << gbest.a[i][j] << " ";
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
//								int s = gbest.a[i].size();
//								for (int j = 0;j < s;j++) {
//									gbest.a[i].pop_back();
//								}
//							}
//							for (int i = 0;i < m;i++) {
//								gbest.a.pop_back();
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
//		}
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