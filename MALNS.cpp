#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<vector>
#include<unordered_map>
#include<iomanip>
#include<fstream>
using namespace std;
int m;//机器数
int n;//工件数
#define yita1 0.6
#define yita2 10e-5
#define yita 50
#define p0 0.2
#define K 6
int CS;//记录成本
int d;//破坏工件个数
#define pu 30//更新迭代数
#define a1 0.2
#define a2 0.1
#define a3 0.05
#define b1 0.02
#define Pr 0.85
#define Dn 6//破坏操作的个数
#define Rn 5//修复操作的个数
#define Max_Nmach 30//最大机器数
#define Max_Njob 300//最大工件数
#define min_pt 1 //最小加工时间
#define max_pt 99//最大加工时间
double Rf;//（0.2，0.6，1.0，1.4，1.8）
double alpha;//（0.05，0.5）
int Max_st;//（9，49，99，124）
#define Min_st 1
#define NNM 3//机器类型数
#define NNN 4//工件类型数
#define NNS 4//设置时间类型数
#define NNa 2
#define NNMN 6
#define NNR 5//到达时间类型数
#define NNA 10//案例数
#define RND 4
#define Time 5
int wgsj;//最大完工时间所在机器完工时间变化值
int wgsj1;//其它机器完工时间变化值
int q = 0;//记录是否退出循环
int q1 = 0;//记录解决方案是否达到最优
double TL;
int budget;
double gen;
double genBest;
double BXCPUT;
class Job_information
{
public:
	int p[Max_Nmach];
	int r;
};
Job_information Job[Max_Njob];
class setuptime
{
public:
	int s[Max_Njob][Max_Njob];
};
setuptime st[Max_Nmach];
class machine_information
{
public:
	int price;
};
machine_information machine[Max_Nmach];
class Gbest
{
public:
	vector<vector<int>> a;
	int truefit;
	int C;
};
Gbest gbest;
void f_ReadData(FILE* infile);
vector<vector<int>> TABU;//记录初始解决方案
vector<vector<int>> S;//用于破坏和修复
vector<int> U;//记录破坏工件
vector<int> SM;//记录机器的完工时间
double W[Dn * Rn];//每一对操作的权重
int u[Dn * Rn];//每一对操作在一段迭代中使用的次数
int	s[Dn * Rn];//每一对操作在一段迭代中的得分
int getfitness(vector<vector<int>> a)//适应度
{
	vector<int> SM(m);
	for (int i = 0;i < m;i++) {
		if (a[i].size() != 0) {
			SM[i] = Job[a[i][0] - 1].r + st[i].s[a[i][0] - 1][a[i][0] - 1] + Job[a[i][0] - 1].p[i];
			for (int j = 1;j < a[i].size();j++) {
				if (Job[a[i][j] - 1].r <= SM[i]) {
					SM[i] += st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
				}
				else {
					SM[i] = Job[a[i][j] - 1].r + st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
				}
			}
		}
	}
	int max = 0;
	for (int i = 0;i < m;i++) {
		if (SM[max] < SM[i]) {
			max = i;
		}
	}
	return SM[max];
}
int getC(vector<vector<int>> a)//成本
{
	int C = 0;
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < a[i].size();j++) {
			C += Job[a[i][j] - 1].p[i] * machine[i].price;
		}
	}
	return C;
}
int getmaxM(vector<vector<int>> a)//最大完工时间的机器
{
	vector<int> SM(m);
	for (int i = 0;i < m;i++) {
		if (a[i].size() != 0) {
			SM[i] = Job[a[i][0] - 1].r + st[i].s[a[i][0] - 1][a[i][0] - 1] + Job[a[i][0] - 1].p[i];
			for (int j = 1;j < a[i].size();j++) {
				if (Job[a[i][j] - 1].r <= SM[i]) {
					SM[i] += st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
				}
				else {
					SM[i] = Job[a[i][j] - 1].r + st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
				}
			}
		}
	}
	int max = 0;
	for (int i = 0;i < m;i++) {
		if (SM[max] < SM[i]) {
			max = i;
		}
	}
	return max + 1;
}
int getSM(vector<vector<int>> a, int i)//机器的完工时间
{
	int sum = 0;
	if (a[i].size() != 0) {
		sum = Job[a[i][0] - 1].r + st[i].s[a[i][0] - 1][a[i][0] - 1] + Job[a[i][0] - 1].p[i];
		for (int j = 1;j < a[i].size();j++) {
			if (Job[a[i][j] - 1].r <= sum) {
				sum += st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
			}
			else {
				sum = Job[a[i][j] - 1].r + st[i].s[a[i][j - 1] - 1][a[i][j] - 1] + Job[a[i][j] - 1].p[i];
			}
		}
	}
	return sum;
}
void CP()
{
	for (int i = 0;i < m;i++) {
		TABU.push_back({});
	}
	vector<int> U(n);
	for (int i = 0;i < n;i++) {
		U[i] = i + 1;
	}
	//int Cmax = 0;
	//vector<int> SM(m);
	int num = n;
	while (num > 0) {
		//vector<vector<int>> Cij;//第一行记录工件位置，第二行记录机器，第三行记录工件放入机器最后一个位置的最大完工时间,第四行记录机器完工时间
		//for (int i = 0;i < 4;i++) {
		//	Cij.push_back({});
		//}
		//for (int i = 0;i < n;i++) {
		//	if (U[i] != 0) {
		//		for (int j = 0;j < m;j++) {
		//			int C = 0;
		//			if (TABU[j].size() == 0) {
		//				C = Job[U[i] - 1].r + st[j].s[U[i] - 1][U[i] - 1] + Job[U[i] - 1].p[j];
		//			}
		//			else {
		//				if (Job[U[i] - 1].r <= SM[j]) {
		//					C = SM[j] + st[j].s[TABU[j][TABU[j].size() - 1] - 1][U[i] - 1] + Job[U[i] - 1].p[j];
		//				}
		//				else {
		//					C = Job[U[i] - 1].r + st[j].s[TABU[j][TABU[j].size() - 1] - 1][U[i] - 1] + Job[U[i] - 1].p[j];
		//				}
		//			}
		//			Cij[0].push_back(i);
		//			Cij[1].push_back(j + 1);
		//			Cij[2].push_back(max(Cmax, C));
		//			Cij[3].push_back(C);
		//		}
		//	}
		//}
		//int min = 0;
		//for (int i = 0;i < Cij[0].size();i++) {
		//	if (Cij[2][min] > Cij[2][i]) {
		//		min = i;
		//	}
		//}
		//TABU[Cij[1][min] - 1].push_back(U[Cij[0][min]]);
		//Cmax = Cij[2][min];
		//SM[Cij[1][min] - 1] = Cij[3][min];
		//U[Cij[0][min]] = 0;
		int r = rand() % n;
		while (U[r] == 0) {
			r = rand() % n;
		}
		int r1 = rand() % m;
		TABU[r1].push_back(U[r]);
		U[r] = 0;
		num--;
	}

}
void dl(int i, int j)
{
	for (int k = j + 1;k < S[i].size();k++) {
		S[i][k - 1] = S[i][k];
	}
	S[i].pop_back();
}
void Insert(int M, int W, int J)
{
	if (S[M - 1].size() == 0) {
		S[M - 1].push_back(J);
	}
	else {
		S[M - 1].push_back({});
		for (int j = S[M - 1].size() - 2;j >= W - 1;j--) {
			S[M - 1][j + 1] = S[M - 1][j];
		}
		S[M - 1][W - 1] = J;
	}
}
void repair(int P)
{
	int cost = CS;
	while (cost > budget) {
		//每次迭代将存在比原来成本低的工件插入到最好的位置
		vector<vector<int>> JM;
		for (int i = 0;i < n;i++) {
			JM.push_back({});
		}
		for (int i = 0;i < m;i++) {
			for (int j = 0;j < S[i].size();j++) {
				for (int k = 1;k <= m;k++) {
					if (machine[i].price * Job[S[i][j] - 1].p[i] > machine[k - 1].price * Job[S[i][j] - 1].p[k - 1]) {
						JM[S[i][j] - 1].push_back(k);
					}
				}
			}
		}
		if (P == 0) {//随机修复
			int r = rand() % n;
			while (JM[r].size() == 0) {
				r = rand() % n;
			}
			int r1 = rand() % JM[r].size();
			int mindex = -1;
			int windex = -1;
			for (int i = 0;i < m;i++) {
				for (int j = 0;j < S[i].size();j++) {
					if (S[i][j] == r + 1) {
						mindex = i;
						windex = j;
						break;
					}
				}
				if (mindex != -1) {
					break;
				}
			}
			dl(mindex, windex);
			int w = 1 + rand() % (1 + S[JM[r][r1] - 1].size());
			Insert(JM[r][r1], w, r + 1);
		}
		else {
			int mindex = 0;//记录选择工件的位置
			int windex = 0;
			int M = 1;//记录插入的机器
			int W = 1;//记录插入的位置
			int J;
			int Cmax = 0;//记录插入后的最大完工时间
			for (int i = 0;i < m;i++) {
				if (S[i].size() == 0) {
					continue;
				}
				else {
					for (int j = 0;j < S[i].size();j++) {
						if (JM[S[i][j] - 1].size() == 0) {
							continue;
						}
						else {
							J = S[i][j];
							dl(i, j);
							for (int k = 0;k < JM[J - 1].size();k++) {
								for (int l = 1;l <= 1 + S[JM[J - 1][k] - 1].size();l++) {
									Insert(JM[J - 1][k], l, J);
									int C = getfitness(S);
									if (Cmax == 0) {
										mindex = i;
										windex = j;
										M = JM[J - 1][k];
										W = l;
										Cmax = C;
									}
									else {
										if (Cmax > C) {
											mindex = i;
											windex = j;
											M = JM[J - 1][k];
											W = l;
											Cmax = C;
										}
									}
									dl(JM[J - 1][k] - 1, l - 1);
								}
							}
							Insert(i + 1, j + 1, J);
						}
					}
				}
			}
			J = S[mindex][windex];
			dl(mindex, windex);
			Insert(M, W, J);
		}
		cost = getC(S);
	}
	CS = cost;
}
//随机破坏
void D1()
{
	while (U.size() < d) {
		int r = rand() % m;
		while (S[r].size() == 0) {
			r = rand() % m;
		}
		int r1 = rand() % S[r].size();
		U.push_back(S[r][r1]);
		dl(r, r1);
		SM[r] = getSM(S, r);
	}
}
//基本最差破坏（删除最大完工时间机器上使得删除后使得最大完工时间最小的工件）
void D2()
{
	while (U.size() < d) {
		int M = getmaxM(S);
		int J;
		int windex = 0;//记录删除工件的位置
		int Cmax = 0;//记录删除后的Cmax
		int Cm = 0;//记录删除后机器的完工时间
		for (int i = 0;i < S[M - 1].size();i++) {
			J = S[M - 1][i];
			dl(M - 1, i);
			int C = getSM(S, M - 1);
			int CM = SM[M - 1];
			SM[M - 1] = C;
			int max = 0;
			for (int j = 0;j < m;j++) {
				if (SM[max] < SM[j]) {
					max = j;
				}
			}
			if (Cmax == 0) {
				windex = i;
				Cmax = SM[max];
				Cm = SM[M - 1];
			}
			else {
				if (Cmax > SM[max]) {
					windex = i;
					Cmax = SM[max];
					Cm = SM[M - 1];
				}
			}
			Insert(M, i + 1, J);
			SM[M - 1] = CM;
		}
		U.push_back(S[M - 1][windex]);
		dl(M - 1, windex);
		SM[M - 1] = Cm;
	}
}
//深度最差破坏（每次删除使得工件所在机器完工时间减少最多的工件）
void D3()
{
	while (U.size() < d) {
		int fs = 0;//判断是否是第一个
		int J;
		int mindex = 0;//记录删除工件所在机器的位置
		int windex = 0;//记录删除工件所在的位置
		int Cm = 0;//记录删除后机器的完工时间
		int chaC = 0;//记录删除工件后机器完工时间的差额
		for (int i = 0;i < m;i++) {
			if (S[i].size() == 0) {
				continue;
			}
			else {
				for (int j = 0;j < S[i].size();j++) {
					J = S[i][j];
					dl(i, j);
					int C = getSM(S, i);
					if (fs == 0) {
						mindex = i;
						windex = j;
						Cm = C;
						chaC = SM[i] - C;
						fs = 1;
					}
					else {
						if (chaC < SM[i] - C) {
							mindex = i;
							windex = j;
							Cm = C;
							chaC = SM[i] - C;
						}
					}
					Insert(i + 1, j + 1, J);
				}
			}
		}
		U.push_back(S[mindex][windex]);
		dl(mindex, windex);
		SM[mindex] = Cm;
	}
}
//半贪婪删除（一半删除使得完工时间最小的，一半随机删除）
void D4()
{
	int d1 = d / 2;
	while (U.size() < d1) {
		int M = getmaxM(S);
		int J;
		int windex = 0;//记录删除工件的位置
		int Cmax = 0;//记录删除后的Cmax
		int Cm = 0;//记录删除后机器的完工时间
		for (int i = 0;i < S[M - 1].size();i++) {
			J = S[M - 1][i];
			dl(M - 1, i);
			int C = getSM(S, M - 1);
			int CM = SM[M - 1];
			SM[M - 1] = C;
			int max = 0;
			for (int j = 0;j < m;j++) {
				if (SM[max] < SM[j]) {
					max = j;
				}
			}
			if (Cmax == 0) {
				windex = i;
				Cmax = SM[max];
				Cm = SM[M - 1];
			}
			else {
				if (Cmax > SM[max]) {
					windex = i;
					Cmax = SM[max];
					Cm = SM[M - 1];
				}
			}
			Insert(M, i + 1, J);
			SM[M - 1] = CM;
		}
		U.push_back(S[M - 1][windex]);
		dl(M - 1, windex);
		SM[M - 1] = Cm;
	}
	while (U.size() < d) {
		int r = rand() % m;
		while (S[r].size() == 0) {
			r = rand() % m;
		}
		int r1 = rand() % S[r].size();
		U.push_back(S[r][r1]);
		dl(r, r1);
		SM[r] = getSM(S, r);
	}
}
//相关删除（每次删除最相近的工件，评价标准为机器完工时间的变化值）
void D5()
{
	int r = rand() % m;
	while (S[r].size() == 0) {
		r = rand() % m;
	}
	int r1 = rand() % S[r].size();//随机选择机器上的工件进行移除
	U.push_back(S[r][r1]);
	dl(r, r1);
	int CM = getSM(S, r);
	int R1 = SM[r] - CM;//计算移除后机器完工时间的差值
	SM[r] = CM;
	vector<vector<int>> J;//第一行记录工件所在机器，第二行记录工件所在位置，第三行记录机器完工时间，第四行记录变化值
	for (int i = 0;i < 4;i++) {
		J.push_back({});
	}
	for (int i = 0;i < m;i++) {
		for (int j = 0;j < S[i].size();j++) {
			int Jo = S[i][j];
			dl(i, j);
			CM = getSM(S, i);
			J[0].push_back(i + 1);
			J[1].push_back(j);
			J[2].push_back(CM);
			J[3].push_back(SM[i] - CM);
			Insert(i + 1, j + 1, Jo);
		}
	}
	while (U.size() < d) {
		int min = 0;
		for (int i = 0;i < J[0].size();i++) {
			if (abs(J[3][min] - R1) > abs(J[3][i] - R1)) {
				min = i;
			}
		}
		U.push_back(S[J[0][min] - 1][J[1][min]]);
		dl(J[0][min] - 1, J[1][min]);
		SM[J[0][min] - 1] = J[2][min];
		R1 = J[3][min];//更新差值
		int sum = 0;//计算之前机器上加工的作业之和
		for (int i = 0;i < J[0][min] - 1;i++) {
			sum += S[i].size();
		}
		int s = S[J[0][min] - 1].size();//计算此时机器上加工工件数
		for (int i = min + 1;i < J[0].size();i++) {
			J[0][i - 1] = J[0][i];
			J[1][i - 1] = J[1][i];
			J[2][i - 1] = J[2][i];
			J[3][i - 1] = J[3][i];
		}
		for (int i = 0;i < 4;i++) {
			J[i].pop_back();
		}
		//[sum,sum+s)
		if (s != 0) {
			for (int i = 0;i < S[J[0][sum] - 1].size();i++) {
				int Jo = S[J[0][sum] - 1][i];
				J[1][sum + i] = i;
				dl(J[0][sum] - 1, i);
				CM = getSM(S, J[0][sum] - 1);
				J[2][sum + i] = CM;
				J[3][sum + i] = SM[J[0][sum] - 1] - CM;
				Insert(J[0][sum], i + 1, Jo);
			}
		}
	}
}
//随机机器删除
void D6()
{
	int r = rand() % m;
	while (S[r].size() == 0) {
		r = rand() % m;
	}
	while (U.size() < d) {
		if (S[r].size() != 0) {
			int r1 = rand() % S[r].size();
			U.push_back(S[r][r1]);
			dl(r, r1);
			SM[r] = getSM(S, r);
		}
		else {
			r = rand() % m;
			while (S[r].size() == 0) {
				r = rand() % m;
			}
		}
	}
}
//贪婪插入
void R1()
{
	int num = d;
	while (num > 0) {
		int index = 0;//记录选择工件的位置
		int M = 0;//记录插入的机器
		int W = 0;//记录插入的位置
		int Cmax = 0;//记录最大完工时间
		int Cm = 0;//记录插入后机器的完工时间
		for (int i = 0;i < U.size();i++) {
			if (U[i] != 0) {
				for (int j = 0;j < m;j++) {
					for (int k = 1;k <= S[j].size() + 1;k++) {
						Insert(j + 1, k, U[i]);
						int CM = getSM(S, j);
						int C = SM[j];
						SM[j] = CM;
						int max = 0;
						for (int o = 0;o < m;o++) {
							if (SM[max] < SM[o]) {
								max = o;
							}
						}
						if (Cmax == 0) {
							index = i;
							M = j + 1;
							W = k;
							Cmax = SM[max];
							Cm = SM[j];
						}
						else {
							if (Cmax > SM[max]) {
								index = i;
								M = j + 1;
								W = k;
								Cmax = SM[max];
								Cm = SM[j];
							}
						}
						dl(j, k - 1);
						SM[j] = C;
					}
				}
			}
		}
		Insert(M, W, U[index]);
		SM[M - 1] = Cm;
		U[index] = 0;
		num--;
	}
}
//2-后悔插入
void R2()
{
	int num = d;
	while (num > 0) {
		vector<vector<int>> HHZ;//第一行记录工件所在位置，第二行记录工件的后悔值，第三行记录插入最佳位置对应机器，第四行记录插入最佳位置，第五行对应最大完工时间，第六行对应机器完工时间
		for (int i = 0;i < 6;i++) {
			HHZ.push_back({});
		}
		for (int i = 0;i < U.size();i++) {
			if (U[i] != 0) {
				vector<vector<int>> CW;//记录插入各个位置的完工时间
				for (int j = 0;j < 4;j++) {
					CW.push_back({});
				}
				for (int j = 0;j < m;j++) {
					for (int k = 1;k <= S[j].size() + 1;k++) {
						Insert(j + 1, k, U[i]);
						int CM = getSM(S, j);
						int C = SM[j];
						SM[j] = CM;
						int max = 0;
						for (int o = 0;o < m;o++) {
							if (SM[max] < SM[o]) {
								max = o;
							}
						}
						CW[0].push_back(j + 1);
						CW[1].push_back(k);
						CW[2].push_back(SM[max]);
						CW[3].push_back(SM[j]);
						dl(j, k - 1);
						SM[j] = C;
					}
				}
				for (int j = 0;j < CW[0].size();j++) {
					for (int k = 0;k < CW[0].size() - 1 - j;k++) {
						if (CW[2][k] > CW[2][k + 1]) {
							swap(CW[0][k], CW[0][k + 1]);
							swap(CW[1][k], CW[1][k + 1]);
							swap(CW[2][k], CW[2][k + 1]);
							swap(CW[3][k], CW[3][k + 1]);
						}
					}
				}
				HHZ[0].push_back(i);
				HHZ[1].push_back(CW[2][1] - CW[2][0]);
				HHZ[2].push_back(CW[0][0]);
				HHZ[3].push_back(CW[1][0]);
				HHZ[4].push_back(CW[2][0]);
				HHZ[5].push_back(CW[3][0]);
			}
		}
		int max = 0;
		for (int i = 0;i < HHZ[0].size();i++) {
			if (HHZ[1][max] < HHZ[1][i]) {
				max = i;
			}
		}
		Insert(HHZ[2][max], HHZ[3][max], U[HHZ[0][max]]);
		U[HHZ[0][max]] = 0;
		SM[HHZ[2][max] - 1] = HHZ[5][max];
		num--;
	}
}
//半贪婪插入（随机选择一半插入到最佳位置，另一半随机插入）
void R3()
{
	int d1 = d / 2;
	int num = d1;
	while (num > 0) {
		int r = rand() % U.size();
		while (U[r] == 0) {
			r = rand() % U.size();
		}
		int r1 = rand() % m;
		int w = rand() % (1 + S[r1].size()) + 1;
		Insert(r1 + 1, w, U[r]);
		U[r] = 0;
		SM[r1] = getSM(S, r1);
		num--;
	}
	num = d - d1;
	while (num > 0) {
		int index = 0;//记录选择工件的位置
		int M = 0;//记录插入的机器
		int W = 0;//记录插入的位置
		int Cmax = 0;//记录最大完工时间
		int Cm = 0;//记录插入后机器的完工时间
		for (int i = 0;i < U.size();i++) {
			if (U[i] != 0) {
				for (int j = 0;j < m;j++) {
					for (int k = 1;k <= S[j].size() + 1;k++) {
						Insert(j + 1, k, U[i]);
						int CM = getSM(S, j);
						int C = SM[j];
						SM[j] = CM;
						int max = 0;
						for (int o = 0;o < m;o++) {
							if (SM[max] < SM[o]) {
								max = o;
							}
						}
						if (Cmax == 0) {
							index = i;
							M = j + 1;
							W = k;
							Cmax = SM[max];
							Cm = SM[j];
						}
						else {
							if (Cmax > SM[max]) {
								index = i;
								M = j + 1;
								W = k;
								Cmax = SM[max];
								Cm = SM[j];
							}
						}
						dl(j, k - 1);
						SM[j] = C;
					}
				}
			}
		}
		Insert(M, W, U[index]);
		SM[M - 1] = Cm;
		U[index] = 0;
		num--;
	}
}
//最小机器修复（每次选择完工时间最小的机器加工）
void R4()
{
	int num = d;
	while (num > 0) {
		int min = 0;
		for (int i = 0;i < m;i++) {
			if (SM[i] < SM[min]) {
				min = i;
			}
		}
		int index = 0;//记录选择工件的位置
		int W = 1;//记录插入的位置
		int Cm = 0;//记录插入后机器的完工时间
		for (int i = 0;i < U.size();i++) {
			if (U[i] != 0) {
				for (int j = 1;j <= S[min].size() + 1;j++) {
					Insert(min + 1, j, U[i]);
					int CM = getSM(S, min);
					if (Cm == 0) {
						Cm = CM;
						index = i;
						W = j;
					}
					else {
						if (Cm > CM) {
							Cm = CM;
							index = i;
							W = j;
						}
					}
					dl(min, j - 1);
				}
			}
		}
		Insert(min + 1, W, U[index]);
		SM[min] = Cm;
		U[index] = 0;
		num--;
	}
}
//随机机器修复（每次随机选择机器进行加工）
void R5()
{
	int num = d;
	while (num > 0) {
		int min = rand() % m;
		int index = 0;//记录选择工件的位置
		int W = 1;//记录插入的位置
		int Cm = 0;//记录插入后机器的完工时间
		for (int i = 0;i < U.size();i++) {
			if (U[i] != 0) {
				for (int j = 1;j <= S[min].size() + 1;j++) {
					Insert(min + 1, j, U[i]);
					int CM = getSM(S, min);
					if (Cm == 0) {
						Cm = CM;
						index = i;
						W = j;
					}
					else {
						if (Cm > CM) {
							Cm = CM;
							index = i;
							W = j;
						}
					}
					dl(min, j - 1);
				}
			}
		}
		Insert(min + 1, W, U[index]);
		SM[min] = Cm;
		U[index] = 0;
		num--;
	}
}
void MMJob_swap(int max)
{
	//cout << "max：" << max + 1 << " " << getmaxM(S) << endl;
	for (int i = 0;i < S[max].size();i++) {
		for (int j = i + 1;j < S[max].size();j++) {
			swap(S[max][i], S[max][j]);
			wgsj = getSM(S, max);
			if (wgsj < SM[max]) {
				SM[max] = wgsj;
				q = 1;
				break;
			}
			else {
				swap(S[max][i], S[max][j]);
			}
		}
		if (q == 1) {
			break;
		}
	}
}
void IMJob_swap(int max)
{
	int C = getC(S);
	for (int k = 0;k < S[max].size();k++) {
		for (int i = 0;i < m;i++) {
			if (i == max || S[i].size() == 0) {
				continue;
			}
			else {
				for (int j = 0;j < S[i].size();j++) {
					if (C - machine[max].price * Job[S[max][k] - 1].p[max] - machine[i].price * Job[S[i][j] - 1].p[i] + machine[max].price * Job[S[i][j] - 1].p[max] + machine[i].price * Job[S[max][k] - 1].p[i] <= budget) {
						swap(S[max][k], S[i][j]);
						wgsj = getSM(S, max);
						wgsj1 = getSM(S, i);
						if (wgsj < SM[max] && wgsj1 < SM[max]) {
							SM[max] = wgsj;
							SM[i] = wgsj1;
							C = C - machine[max].price * Job[S[i][j] - 1].p[max] - machine[i].price * Job[S[max][k] - 1].p[i] + machine[max].price * Job[S[max][k] - 1].p[max] + machine[i].price * Job[S[i][j] - 1].p[i];
							q = 1;
							break;
						}
						else {
							swap(S[max][k], S[i][j]);
						}
					}
				}
			}
			if (q == 1) {
				break;
			}
		}
		if (q == 1) {
			break;
		}
	}
}
void MMJob_insert(int max)
{
	for (int i = 0;i < S[max].size();i++) {
		int J = S[max][i];
		dl(max, i);
		for (int j = 1;j <= S[max].size() + 1;j++) {
			Insert(max + 1, j, J);
			wgsj = getSM(S, max);
			if (wgsj < SM[max]) {
				SM[max] = wgsj;
				q = 1;
				break;
			}
			else {
				dl(max, j - 1);
			}
		}
		if (q == 1) {
			break;
		}
		else {
			Insert(max + 1, i + 1, J);
		}
	}
}
void IMJob_insert(int max)
{
	//for (int i = 0;i < m;i++) {
	//	for (int j = 0;j < S[i].size();j++) {
	//		cout << S[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	int C = getC(S);
	for (int i = 0;i < S[max].size();i++) {
		int J = S[max][i];
		dl(max, i);
		C = C - machine[max].price * Job[J - 1].p[max];
		wgsj = getSM(S, max);
		for (int j = 0;j < m;j++) {
			if (j == max || C + machine[j].price * Job[J - 1].p[j] > budget) {
				continue;
			}
			else {
				for (int k = 1;k <= S[j].size() + 1;k++) {
					Insert(j + 1, k, J);
					wgsj1 = getSM(S, j);
					if (wgsj < SM[max] && wgsj1 < SM[max]) {
						SM[max] = wgsj;
						SM[j] = wgsj1;
						C = C + machine[j].price * Job[J - 1].p[j];
						q = 1;
						break;
					}
					else {
						dl(j, k - 1);
					}
				}
			}
			if (q == 1) {
				break;
			}
		}
		if (q == 1) {
			break;
		}
		else {
			Insert(max + 1, i + 1, J);
			C = C + machine[max].price * Job[J - 1].p[max];
		}
	}
}
void CRVND()
{
	q = 0;
	int rvnd[RND];
	for (int i = 0;i < RND;i++) {
		rvnd[i] = 1;
	}
	int num = RND;
	while (num > 0) {
		int RD = rand() % RND;
		while (rvnd[RD] == 0) {
			RD = rand() % RND;
		}
		int max = 0;
		for (int i = 0;i < m;i++) {
			if (SM[max] < SM[i]) {
				max = i;
			}
		}
		if (RD == 0) {
			if (S[max].size() >= 2) {
				MMJob_swap(max);//将最大完工时间机器上的工件进行一一交换
			}
		}
		if (RD == 1) {
			IMJob_swap(max);//将最大完工时间机器上的工件与满足成本的机器上的工件进行交换
		}
		if (RD == 2) {
			MMJob_insert(max);//将最大完工时间机器上的工件插入到其它位置
		}
		if (RD == 3) {
			IMJob_insert(max);//将最大完工时间机器上的工件插入到满足成本的机器上的位置
		}
		if (q == 1) {
			for (int i = 0;i < RND;i++) {
				rvnd[i] = 1;
			}
			num = RND;
		}
		else {
			rvnd[RD] = 0;
			num--;
		}
		q = 0;
	}
}
int main()
{
	srand((unsigned)time(NULL));
	for (int NM = 1;NM <= NNMN;NM++) {
		switch (NM) {
		case 1:m = 2;n = 6;break;
		case 2:m = 2;n = 8;break;
		case 3:m = 3;n = 8;break;
		case 4:m = 3;n = 10;break;
		case 5:m = 5;n = 10;break;
		case 6:m = 5;n = 12;break;
		}
		//m = 5;n = 12;
		m = 10;n = 300;
	//for (int NM = 1;NM <= NNM;NM++) {
	//	switch (NM) {
	//	case 1:m = 10;break;
	//	case 2:m = 15;break;
	//	case 3:m = 20;break;
	//	}
	//	for (int NN = 1;NN <= NNN;NN++) {
	//		switch (NN) {
	//		case 1:n = 150;break;
	//		case 2:n = 200;break;
	//		case 3:n = 250;break;
	//		case 4:n = 300;break;
	//		}
			for (int NS = 1;NS <= NNS;NS++) {
				switch (NS) {
				case 1:Max_st = 9;break;
				case 2:Max_st = 49;break;
				case 3:Max_st = 99;break;;
				case 4:Max_st = 124;break;
				}
				Max_st = 9;
				for (int Na = 1;Na <= NNa;Na++) {
					switch (Na)
					{
					case 1:alpha = 0.05;break;
					case 2:alpha = 0.5;break;
					}
					alpha = 0.05;
					//// 记录每个案例的平均最大完工时间，最优最大完工时间，平均取得最优解的时间
					//string A = "C:\\Users\\Lenovo\\Desktop\\Rm online sijk TC Cmax\\Experimental-results\\Medium-sized-instances\\MSA";
					//char Excel[100];
					//sprintf_s(Excel, "M%d_N%d_P%d_P%d_S%d_S%d_alpha%0.2f.xls", m, n, min_pt, max_pt, Min_st, Max_st, alpha);
					//string fileName = A + Excel;
					//ofstream OutFile(fileName, ios::out | ios::app);

					//OutFile << "ID" << "\t";
					//OutFile << "BX_Cmax" << "\t";
					//OutFile << "AVG_Cmax" << "\t";
					//OutFile << "AVG_genBest" << "\t";
					//OutFile << "TimeLimit" << "\t";
					//OutFile << "AVG_CUPTime" << "\t";
					//OutFile << "Rf" << "\t";
					//OutFile << endl;
					//OutFile.precision(10);

					for (int NA = 0;NA < NNA;NA++) {
						int na = ceil((double(NA + 1) / 2));
						switch (na) {
						case 1:Rf = 0.2;break;
						case 2:Rf = 0.6;break;
						case 3:Rf = 1.0;break;
						case 4:Rf = 1.4;break;
						case 5:Rf = 1.8;break;
						}
						//TL = 1;
						TL = (double)10 * m * n / 1000;
						d = ceil(0.1 * n);
						cout << "*********************the results of instance- " << NA + 1 << "*******************************" << endl;
						cout << "Max_st：" << Max_st << " " << "m：" << m << " " << "n：" << n << " " << "alpha：" << alpha << " " << "Rf：" << Rf << endl;
						FILE* infile = nullptr;
						char filename[200];
						sprintf_s(filename, "D:\\Benchmark-instances\\Large-sized-instances\\M%d_N%d_P%d_P%d_S%d_S%d_alpha%0.2f_Rf%0.2f_%d.txt", m, n, min_pt, max_pt, Min_st, Max_st, alpha, Rf, NA + 1);

						if ((infile = fopen(filename, "r")) == NULL) {
							printf("could not open file %s\n", filename);
						}
						f_ReadData(infile);
						fclose(infile);
						int sum_Cmax = 0;//记录最大完工时间之和
						int sum_C = 0;//记录成本之和
						double sumtime = 0;//记录求得最优解的时间之和
						int sumgen = 0;//记录求得最优解的迭代次数之和
						int BestCmax = 0;//记录求解到的最优最大完工时间
						int BestC = 0;//记录求解到最优最大完工时间的成本
						for (int IT = 0;IT < Time;IT++) {
							gen = 0;//记录迭代数
							genBest = 0;//记录找到最优解的代数
							double CPUT;
							time_t IGAT_start_it, IGAT_finish_it, BXCPUT_it;
							BXCPUT = 0;
							IGAT_start_it = clock();
							int w = 0;
							//构造初始解
							CP();
							S = TABU;
							CS = getC(S);
							if (CS > budget) {
								repair(1);
							}
							for (int i = 0;i < m;i++) {
								SM.push_back(getSM(S, i));
							}
							CRVND();
							for (int i = 0;i < m;i++) {
								SM.pop_back();
							}
							TABU = S;
							for (int i = 0;i < m;i++) {
								int s = S[i].size();
								for (int j = 0;j < s;j++) {
									S[i].pop_back();
								}
							}
							for (int i = 0;i < m;i++) {
								S.pop_back();
							}
							gbest.a = TABU;
							gbest.truefit = getfitness(gbest.a);
							gbest.C = getC(gbest.a);
							genBest = gen;
							BXCPUT_it = clock();
							BXCPUT = (double)(BXCPUT_it - IGAT_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
							//cout << "初始最优解：" << endl;
							//for (int i = 0;i < m;i++) {
							//	for (int j = 0;j < gbest.a[i].size();j++) {
							//		cout << gbest.a[i][j] << " ";
							//	}
							//	cout << endl;
							//}
							//cout << gbest.truefit << " " << gbest.C << endl;
							double T0 = -(yita1 * getfitness(TABU)) / (log(0.5) / log(exp(1)));//初始温度
							double Tf = -(yita2 * getfitness(TABU)) / (log(0.5) / log(exp(1)));//最终温度
							double T = T0;
							double k = pow((double)Tf / T0, 1.0 / yita);
							vector<double> Dprobabilities(Dn);//破坏算子的概率
							vector<double> Rprobabilities(Rn);//修复算子的概率
							vector<double> Dprobabilities1(Dn);
							vector<double> Rprobabilities1(Rn);
							for (int i = 0;i < Dn;i++) {
								Dprobabilities[i] = 1.0 / Dn;
								Dprobabilities1[i] = 1.0 / Dn;
							}
							for (int i = 0;i < Rn;i++) {
								Rprobabilities[i] = 1.0 / Rn;
								Rprobabilities1[i] = 1.0 / Rn;
							}
							do {
								gen++;
								S = TABU;
								vector<double> Dlunpandu(Dn);//破坏算子的轮盘赌
								vector<double> Rlunpandu(Rn);//修复算子的轮盘赌
								Dlunpandu[0] = Dprobabilities[0];
								for (int i = 1;i < Dn;i++) {
									Dlunpandu[i] = Dlunpandu[i - 1] + Dprobabilities[i];
								}
								int Dindex = 0;
								double P = rand() / (RAND_MAX + 1.0);
								for (int i = 0;i < Dn;i++) {
									if (P <= Dlunpandu[i]) {
										Dindex = i;
										break;
									}
								}
								Rlunpandu[0] = Rprobabilities[0];
								for (int i = 1;i < Rn;i++) {
									Rlunpandu[i] = Rlunpandu[i - 1] + Rprobabilities[i];
								}
								int Rindex = 0;
								P = rand() / (RAND_MAX + 1.0);
								for (int i = 0;i < Rn;i++) {
									if (P <= Rlunpandu[i]) {
										Rindex = i;
										break;
									}
								}
								for (int i = 0;i < m;i++) {
									SM.push_back(getSM(S, i));
								}
								if (Dindex == 0) {
									D1();
								}
								if (Dindex == 1) {
									D2();
								}
								if (Dindex == 2) {
									D3();
								}
								if (Dindex == 3) {
									D4();
								}
								if (Dindex == 4) {
									D5();
								}
								if (Dindex == 5) {
									D6();
								}
								if (Rindex == 0) {
									R1();
								}
								if (Rindex == 1) {
									R2();
								}
								if (Rindex == 2) {
									R3();
								}
								if (Rindex == 3) {
									R4();
								}
								if (Rindex == 4) {
									R5();
								}
								CS = getC(S);
								if (CS > budget) {
									if (rand() / (RAND_MAX + 1.0) < Pr) {
										repair(1);
									}
									else {
										repair(0);
									}
								}
								for (int i = 0;i < m;i++) {
									SM[i] = getSM(S, i);
								}
								CRVND();
								//for (int i = 0;i < m;i++) {
								//	cout << SM[i] << " " << getSM(S, i) << endl;
								//}
								w++;
								int CmaxTABU = getfitness(TABU);//当前解
								int CmaxS = getfitness(S);//迭代解
								double a;
								double b;
								if (CmaxS < gbest.truefit) {
									TABU = S;
									gbest.a = S;
									gbest.truefit = getfitness(gbest.a);
									gbest.C = getC(gbest.a);
									genBest = gen;
									BXCPUT_it = clock();
									BXCPUT = (double)(BXCPUT_it - IGAT_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
									w = 0;
									a = a1;
									b = 0;
								}
								else if (CmaxS < CmaxTABU) {
									TABU = S;
									a = a2;
									b = 0;
								}
								else if (rand() / (RAND_MAX + 1.0) < exp(-(double)(CmaxS - CmaxTABU) / T)) {
									TABU = S;
									a = a3;
									b = 0;
								}
								else {
									a = 0;
									b = b1;
								}
								if (a != 0) {
									for (int i = 0;i < Dn;i++) {
										if (Dindex == i) {
											Dprobabilities1[i] += a * (1 - Dprobabilities1[i]);
										}
										else {
											Dprobabilities1[i] = Dprobabilities1[i] * (1 - a);
										}
									}
									for (int i = 0;i < Rn;i++) {
										if (Rindex == i) {
											Rprobabilities1[i] += a * (1 - Rprobabilities1[i]);
										}
										else {
											Rprobabilities1[i] = Rprobabilities1[i] * (1 - a);
										}
									}
								}
								else {
									for (int i = 0;i < Dn;i++) {
										if (Dindex == i) {
											Dprobabilities1[i] = (1 - b) * Dprobabilities1[i];
										}
										else {
											Dprobabilities1[i] = (double)b / (Dn - 1) + (1 - b) * Dprobabilities1[i];
										}
									}
									for (int i = 0;i < Rn;i++) {
										if (Rindex == i) {
											Rprobabilities1[i] = (1 - b) * Rprobabilities1[i];
										}
										else {
											Rprobabilities1[i] = (double)b / (Rn - 1) + (1 - b) * Rprobabilities1[i];
										}
									}
								}
								T = T * k;
								if (T < Tf) {
									T = Tf;
								}
								if ((int)gen % K == 0) {
									for (int i = 0;i < Dn;i++) {
										Dprobabilities[i] = Dprobabilities1[i];
									}
									for (int i = 0;i < Rn;i++) {
										Rprobabilities[i] = Rprobabilities1[i];
									}
								}
								if (w == pu) {
									TABU = gbest.a;
									w = 0;
								}
								IGAT_finish_it = clock();
								CPUT = (double)(IGAT_finish_it - IGAT_start_it) / CLOCKS_PER_SEC;
								for (int i = 0;i < m;i++) {
									SM.pop_back();
								}
								int s = U.size();
								for (int i = 0;i < s;i++) {
									U.pop_back();
								}
							} while (CPUT < TL);
							cout << "全局最优解：" << endl;
							for (int i = 0;i < m;i++) {
								for (int j = 0;j < gbest.a[i].size();j++) {
									cout << gbest.a[i][j] << " ";
								}
								cout << endl;
							}
							cout << "BestObjectiveValue=" << gbest.truefit << "  MachineUsageCost=" << gbest.C << endl;
							cout << "genBest=" << genBest << "  BXCPUT=" << BXCPUT << endl;
							if (BestCmax == 0) {
								BestCmax = gbest.truefit;
								BestC = gbest.C;
							}
							else {
								if (BestCmax > gbest.truefit) {
									BestCmax = gbest.truefit;
									BestC = gbest.C;
								}
							}
							sum_Cmax += gbest.truefit;
							sum_C += gbest.C;
							sumgen += genBest;
							sumtime += BXCPUT;
							for (int i = 0;i < m;i++) {
								int s = TABU[i].size();
								for (int j = 0;j < s;j++) {
									TABU[i].pop_back();
								}
							}
							for (int i = 0;i < m;i++) {
								TABU.pop_back();
							}
							for (int i = 0;i < m;i++) {
								int s = gbest.a[i].size();
								for (int j = 0;j < s;j++) {
									gbest.a[i].pop_back();
								}
							}
							for (int i = 0;i < m;i++) {
								gbest.a.pop_back();
							}
						}
						cout << "AvgObjectiveValue=" << (double)sum_Cmax / Time << " AvgMachineUsageCost=" << (double)sum_C / Time << endl;
						cout << "BestObjectiveValue=" << BestCmax << " MachineUsageCost=" << BestC << endl;
						cout << "genBest=" << (double)sumgen / Time << " BXCPUT=" << (double)sumtime / Time << endl;
						//OutFile << NA + 1 << "\t";
						//OutFile << BestCmax << "\t";
						//OutFile << (double)sum_Cmax / Time << "\t";
						//OutFile << (double)sumgen / Time << "\t";
						//OutFile << TL << "\t";
						//OutFile << (double)sumtime / Time << "\t";
						//OutFile << Rf << "\t" << endl;
					}
					//OutFile.close();
				}
			}
	    //}
	}
	system("pause");
}
void f_ReadData(FILE* infile)
{
	char tmp[100];
	fscanf(infile, "%s", tmp);
	int bg;
	fscanf(infile, "%d", &bg);
	budget = bg;
	cout << budget << endl;
	fscanf(infile, "%s", tmp);
	int cost;
	for (int i = 0;i < m;i++) {
		fscanf(infile, "%d", &cost);
		machine[i].price = cost;
		//cout << machine[i].price << " ";
	}
	//cout << endl;
	fscanf(infile, "%s", tmp);
	int pt;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			fscanf(infile, "%d", &pt);
			Job[i].p[j] = pt;
		}
	}
	fscanf(infile, "%s", tmp);
	int r;
	for (int i = 0;i < n;i++) {
		fscanf(infile, "%d", &r);
		Job[i].r = r;
	}
	fscanf(infile, "%s", tmp);
	for (int i = 0;i < m;i++) {
		int s;
		for (int j = 0;j < n;j++) {
			for (int k = 0;k < n;k++) {
				fscanf(infile, "%d", &s);
				st[i].s[j][k] = s;
			}
		}
	}
	//for (int i = 0;i < n;i++) {
	//	for (int j = 0;j < m;j++) {
	//		cout << Job[i].p[j] << " ";
	//	}
	//	cout << endl;
	//}
	//for (int i = 0;i < n;i++) {
	//	cout << Job[i].r << endl;
	//}
	//cout << endl;
	//for (int i = 0;i < m;i++) {
	//	for (int j = 0;j < n;j++) {
	//		for (int k = 0;k < n;k++) {
	//			cout << st[i].s[j][k] << " ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}
}