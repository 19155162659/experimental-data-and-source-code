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
//int CS;
//#define Popsize 120//种群数
//#define Pc 0.5//交叉概率
//#define Pm 0.2//变异概率
//#define Pr 0.85
//#define Max_Nmach 30//最大机器数
//#define Max_Njob 300//最大工件数
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
//class individual
//{
//public:
//	vector<double> a;
//	vector<vector<int>> TABU;//记录解决方案
//	int truefit;
//	int C;
//};
//individual group[Popsize];
//individual s_group[Popsize];
//individual c_group[Popsize];
//individual gbest;
//void Initgroup()
//{
//	for (int i = 0;i < Popsize;i++) {
//		for (int j = 0;j < n * m;j++) {
//			group[i].a.push_back(rand() / (RAND_MAX + 1.0));
//		}
//	}
//}
//void jiema()
//{
//	//对个体进行解码
//	for (int i = 0;i < Popsize;i++) {
//		for (int j = 0;j < m;j++) {
//			group[i].TABU.push_back({});
//		}
//		//先将工件放入机器上加工再排序
//		for (int j = 1;j <= n;j++) {
//			//找到[(j-1)*m,j*m-1]最小的数
//			int index = (j - 1) * m;
//			for (int k = (j - 1) * m;k <= j * m - 1;k++) {
//				if (group[i].a[k] < group[i].a[index]) {
//					index = k;
//				}
//			}
//			group[i].TABU[index - (j - 1) * m].push_back(j);
//		}
//		for (int j = 0;j < m;j++) {
//			if (group[i].TABU[j].size() <= 1) {
//				continue;
//			}
//			else {
//				for (int k = 0;k < group[i].TABU[j].size();k++) {
//					for (int l = 0;l < group[i].TABU[j].size() - k - 1;l++) {
//						if (group[i].a[(group[i].TABU[j][l] - 1) * m + j] > group[i].a[(group[i].TABU[j][l + 1] - 1) * m + j])
//						{
//							swap(group[i].TABU[j][l], group[i].TABU[j][l + 1]);
//						}
//					}
//				}
//			}
//		}
//	}
//}
//int getfitness(vector<vector<int>> TABU)
//{
//	vector<int> SM(m);
//	for (int i = 0;i < m;i++) {
//		if (TABU[i].size() == 0) {
//			continue;
//		}
//		else {
//			SM[i] = Job[TABU[i][0] - 1].r + st[i].s[TABU[i][0] - 1][TABU[i][0] - 1] + Job[TABU[i][0] - 1].p[i];
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
//int getC(vector<vector<int>> TABU) {
//	int sum = 0;
//	for (int i = 0;i < m;i++) {
//		for (int j = 0;j < TABU[i].size();j++) {
//			sum += Job[TABU[i][j] - 1].p[i] * machine[i].price;
//		}
//	}
//	return sum;
//}
//int getSM(vector<vector<int>> TABU, int i)
//{
//	vector<int> SM(m);
//	for (int i = 0;i < m;i++) {
//		if (TABU[i].size() == 0) {
//			continue;
//		}
//		else {
//			SM[i] = Job[TABU[i][0] - 1].r + st[i].s[TABU[i][0] - 1][TABU[i][0] - 1] + Job[TABU[i][0] - 1].p[i];
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
//	return SM[i];
//}
//void dl(int o, int i, int j)
//{
//	for (int k = j + 1;k < group[o].TABU[i].size();k++) {
//		group[o].TABU[i][k - 1] = group[o].TABU[i][k];
//	}
//	group[o].TABU[i].pop_back();
//}
//void Insert(int o, int M, int W, int J)
//{
//	if (group[o].TABU[M - 1].size() == 0) {
//		group[o].TABU[M - 1].push_back(J);
//	}
//	else {
//		group[o].TABU[M - 1].push_back({});
//		for (int j = group[o].TABU[M - 1].size() - 2;j >= W - 1;j--) {
//			group[o].TABU[M - 1][j + 1] = group[o].TABU[M - 1][j];
//		}
//		group[o].TABU[M - 1][W - 1] = J;
//	}
//}
//void repair(int o, int P)
//{
//	int cost = CS;
//	while (cost > budget) {
//		//每次迭代将存在比原来成本低的工件插入到最好的位置
//		vector<vector<int>> JM;
//		for (int i = 0;i < n;i++) {
//			JM.push_back({});
//		}
//		for (int i = 0;i < m;i++) {
//			for (int j = 0;j < group[o].TABU[i].size();j++) {
//				for (int k = 1;k <= m;k++) {
//					if (machine[i].price * Job[group[o].TABU[i][j] - 1].p[i] > machine[k - 1].price * Job[group[o].TABU[i][j] - 1].p[k - 1]) {
//						JM[group[o].TABU[i][j] - 1].push_back(k);
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
//				for (int j = 0;j < group[o].TABU[i].size();j++) {
//					if (group[o].TABU[i][j] == r + 1) {
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
//			int w = 1 + rand() % (1 + group[o].TABU[JM[r][r1] - 1].size());
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
//				if (group[o].TABU[i].size() == 0) {
//					continue;
//				}
//				else {
//					for (int j = 0;j < group[o].TABU[i].size();j++) {
//						if (JM[group[o].TABU[i][j] - 1].size() == 0) {
//							continue;
//						}
//						else {
//							J = group[o].TABU[i][j];
//							dl(o, i, j);
//							for (int k = 0;k < JM[J - 1].size();k++) {
//								for (int l = 1;l <= 1 + group[o].TABU[JM[J - 1][k] - 1].size();l++) {
//									Insert(o, JM[J - 1][k], l, J);
//									int C = getfitness(group[o].TABU);
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
//			J = group[o].TABU[mindex][windex];
//			dl(o, mindex, windex);
//			Insert(o, M, W, J);
//		}
//		cost = getC(group[o].TABU);
//	}
//	CS = cost;
//}
//void select()
//{
//	//随机从父本选择个体
//	for (int i = 0;i < Popsize;i++) {
//		int r = rand() % Popsize;
//		for (int j = 0;j < n * m;j++) {
//			s_group[i].a.push_back(group[r].a[j]);
//		}
//	}
//}
//void cross()
//{
//	for (int i = 0;i < Popsize - 1;i = i + 2) {
//		int r1 = rand() % Popsize;
//		int r2 = rand() % Popsize;
//		while (r1 == r2) {
//			r2 = rand() % Popsize;
//		}
//		if (rand() / (RAND_MAX + 1.0) < Pm) {
//			int point = rand() % n * m;
//			//cout << "point：" << point << endl;
//			for (int j = 0;j < point;j++) {
//				c_group[i].a.push_back(s_group[r1].a[j]);
//				c_group[i + 1].a.push_back(s_group[r2].a[j]);
//			}
//			for (int j = point;j < n * m;j++) {
//				c_group[i].a.push_back(s_group[r2].a[j]);
//				c_group[i + 1].a.push_back(s_group[r1].a[j]);
//			}
//		}
//		else {
//			for (int j = 0;j < n * m;j++) {
//				c_group[i].a.push_back(group[r1].a[j]);
//				c_group[i + 1].a.push_back(group[r2].a[j]);
//			}
//		}
//	}
//}
//void mutate()
//{
//	for (int i = 0;i < Popsize;i++) {
//		if (rand() / (RAND_MAX + 1.0) < Pm) {
//			int r = rand() % n * m;
//			double num = c_group[i].a[r];
//			double nnum = rand() / (RAND_MAX + 1.0);
//			while (nnum == num) {
//				nnum = rand() / (RAND_MAX + 1.0);
//			}
//			c_group[i].a[r] = nnum;
//		}
//	}
//}
//void LS()
//{
//	for (int i = 0;i < Popsize;i++) {
//		vector<vector<int>> Gene(2, vector<int>(n));
//		for (int j = 0;j < m;j++) {
//			if (group[i].TABU[j].size() != 0) {
//				int sum = 0;
//				for (int k = 0;k < j;k++) {
//					sum += group[i].TABU[k].size();
//				}
//				for (int k = sum;k < sum + group[i].TABU[j].size();k++) {
//					Gene[0][k] = j + 1;
//					Gene[1][k] = group[i].TABU[j][k - sum];
//				}
//			}
//		}
//		for (int j = 0;j < n;j++) {
//			for (int k = j + 1;k < n;k++) {
//				if (Gene[0][j] == Gene[0][k]) {
//					if (k == j + 1) {
//						int a = 0;
//						int b = 0;
//						int c = 0;
//						if (j > 0 && Gene[0][j] == Gene[0][j - 1]) {
//							a = st[Gene[0][j] - 1].s[Gene[1][j - 1] - 1][Gene[1][k] - 1] - st[Gene[0][j] - 1].s[Gene[1][j - 1] - 1][Gene[1][j] - 1] + st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][j] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][k] - 1];
//						}
//						if (j == 0 || Gene[0][j] != Gene[0][j - 1]) {
//							b = st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][k] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][j] - 1] + st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][j] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][k] - 1];
//						}
//						if (k < n - 1 && Gene[0][k] == Gene[0][k + 1]) {
//							c = st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][k + 1] - 1] - st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][k + 1] - 1];
//						}
//						if (a + b + c < 0) {
//							//将Gene[1][j]和Gene[1][k]工件进行交换
//							swap(group[i].a[(Gene[1][j] - 1) * m + Gene[0][j] - 1], group[i].a[(Gene[1][k] - 1) * m + Gene[0][k] - 1]);
//							//确保Gene[1][j]仍然在机器上加工
//							for (int l = (Gene[1][j] - 1) * m;l < Gene[1][j] * m;l++) {
//								if (l == (Gene[1][j] - 1) * m + Gene[0][j] - 1) {
//									continue;
//								}
//								else {
//									if (group[i].a[l] < group[i].a[(Gene[1][j] - 1) * m + Gene[0][j] - 1]) {
//										double num = rand() / (RAND_MAX + 1.0);
//										while (num < group[i].a[(Gene[1][j] - 1) * m + Gene[0][j] - 1]) {
//											num = rand() / (RAND_MAX + 1.0);
//										}
//										group[i].a[l] = num;
//									}
//								}
//							}
//							swap(Gene[1][j], Gene[1][k]);
//						}
//					}
//					if (k > j + 1) {
//						int a = 0;
//						int b = 0;
//						int c = 0;
//						if (j > 0 && Gene[0][j] == Gene[0][j - 1]) {
//							a = st[Gene[0][j] - 1].s[Gene[1][j - 1] - 1][Gene[1][k] - 1] - st[Gene[0][j] - 1].s[Gene[1][j - 1] - 1][Gene[1][j] - 1] + st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][j + 1] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][j + 1] - 1] + st[Gene[0][j] - 1].s[Gene[1][k - 1] - 1][Gene[1][j] - 1] - st[Gene[0][j] - 1].s[Gene[1][k - 1] - 1][Gene[1][k] - 1];
//						}
//						if (j == 0 || Gene[0][j] != Gene[0][j - 1]) {
//							b = st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][k] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][j] - 1] + st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][j + 1] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][j + 1] - 1] + st[Gene[0][j] - 1].s[Gene[1][k - 1] - 1][Gene[1][j] - 1] - st[Gene[0][j] - 1].s[Gene[1][k - 1] - 1][Gene[1][k] - 1];
//						}
//						if (k < n - 1 && Gene[0][k] == Gene[0][k + 1]) {
//							c = st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][k + 1] - 1] - st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][k + 1] - 1];
//						}
//						if (a + b + c < 0) {
//							//将Gene[1][j]和Gene[1][k]工件进行交换
//							swap(group[i].a[(Gene[1][j] - 1) * m + Gene[0][j] - 1], group[i].a[(Gene[1][k] - 1) * m + Gene[0][k] - 1]);
//							for (int l = (Gene[1][j] - 1) * m;l < Gene[1][j] * m;l++) {
//								if (l == (Gene[1][j] - 1) * m + Gene[0][j] - 1) {
//									continue;
//								}
//								else {
//									if (group[i].a[l] < group[i].a[(Gene[1][j] - 1) * m + Gene[0][j] - 1]) {
//										double num = rand() / (RAND_MAX + 1.0);
//										while (num < group[i].a[(Gene[1][j] - 1) * m + Gene[0][j] - 1]) {
//											num = rand() / (RAND_MAX + 1.0);
//										}
//										group[i].a[l] = num;
//									}
//								}
//							}
//							swap(Gene[1][j], Gene[1][k]);
//						}
//					}
//				}
//				if (Gene[0][j] != Gene[0][k]) {
//					int a = 0;
//					int a1 = 0;
//					int a2 = 0;
//					int b = 0;
//					int b1 = 0;
//					int b2 = 0;
//					int Cmax1 = 0;
//					int Cmax2 = 0;
//					int C1 = getSM(group[i].TABU, Gene[0][j] - 1);
//					a = C1 + Job[Gene[1][k] - 1].p[Gene[0][j] - 1] - Job[Gene[1][j] - 1].p[Gene[0][j] - 1];
//					if (j > 0 && Gene[0][j] == Gene[0][j - 1]) {
//						a1 = st[Gene[0][j] - 1].s[Gene[1][j - 1] - 1][Gene[1][k] - 1] - st[Gene[0][j] - 1].s[Gene[1][j - 1] - 1][Gene[1][j] - 1];
//					}
//					if (j == 0 || Gene[0][j] != Gene[0][j - 1]) {
//						a1 = st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][k] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][j] - 1];
//					}
//					if (Gene[0][j] == Gene[0][j + 1]) {
//						a2 = st[Gene[0][j] - 1].s[Gene[1][k] - 1][Gene[1][j + 1] - 1] - st[Gene[0][j] - 1].s[Gene[1][j] - 1][Gene[1][j + 1] - 1];
//					}
//					int C2 = getSM(group[i].TABU, Gene[0][k] - 1);
//					b = C2 + Job[Gene[1][j] - 1].p[Gene[0][k] - 1] - Job[Gene[1][k] - 1].p[Gene[0][k] - 1];
//					if (Gene[0][k] == Gene[0][k - 1]) {
//						b1 = st[Gene[0][k] - 1].s[Gene[1][k - 1] - 1][Gene[1][j] - 1] - st[Gene[0][k] - 1].s[Gene[1][k - 1] - 1][Gene[1][k] - 1];
//					}
//					if (Gene[0][k] != Gene[0][k - 1]) {
//						b1 = st[Gene[0][k] - 1].s[Gene[1][j] - 1][Gene[1][j] - 1] - st[Gene[0][k] - 1].s[Gene[1][k] - 1][Gene[1][k] - 1];
//					}
//					if (k < n - 1 && Gene[0][k] == Gene[0][k + 1]) {
//						b2 = st[Gene[0][k] - 1].s[Gene[1][j] - 1][Gene[1][k + 1] - 1] - st[Gene[0][k] - 1].s[Gene[1][k] - 1][Gene[1][k + 1] - 1];
//					}
//					a = a + a1 + a2;
//					b = b + b1 + b2;
//					Cmax1 = max(C1, C2);
//					Cmax2 = max(a, b);
//					if (C2 < C1) {
//						//将有关的机器的数进行互换
//						swap(group[i].a[(Gene[1][j] - 1) * m + Gene[0][j] - 1], group[i].a[(Gene[1][k] - 1) * m + Gene[0][j] - 1]);
//						swap(group[i].a[(Gene[1][j] - 1) * m + Gene[0][k] - 1], group[i].a[(Gene[1][k] - 1) * m + Gene[0][k] - 1]);
//						for (int l = (Gene[1][j] - 1) * m;l < Gene[1][j] * m;l++) {
//							if (l == (Gene[1][j] - 1) * m + Gene[0][k] - 1) {
//								continue;
//							}
//							else {
//								if (group[i].a[l] < group[i].a[(Gene[1][j] - 1) * m + Gene[0][k] - 1]) {
//									double num = rand() / (RAND_MAX + 1.0);
//									while (num < group[i].a[(Gene[1][j] - 1) * m + Gene[0][k] - 1]) {
//										num = rand() / (RAND_MAX + 1.0);
//									}
//									group[i].a[l] = num;
//								}
//							}
//						}
//						for (int l = (Gene[1][k] - 1) * m;l < Gene[1][k] * m;l++) {
//							if (l == (Gene[1][k] - 1) * m + Gene[0][j] - 1) {
//								continue;
//							}
//							else {
//								if (group[i].a[l] < group[i].a[(Gene[1][k] - 1) * m + Gene[0][j] - 1]) {
//									double num = rand() / (RAND_MAX + 1.0);
//									while (num < group[i].a[(Gene[1][k] - 1) * m + Gene[0][j] - 1]) {
//										num = rand() / (RAND_MAX + 1.0);
//									}
//									group[i].a[l] = num;
//								}
//							}
//						}
//						swap(Gene[1][j], Gene[1][k]);
//					}
//				}
//			}
//		}
//		for (int j = 0;j < m;j++) {
//			int s = group[i].TABU[j].size();
//			for (int k = 0;k < s;k++) {
//				group[i].TABU[j].pop_back();
//			}
//		}
//		for (int j = 0;j < n;j++) {
//			group[i].TABU[Gene[0][j] - 1].push_back(Gene[1][j]);
//		}
//	}
//}
//int main()
//{
//	srand((unsigned)time(NULL));
//	for (int NM = 1;NM <= NNMN;NM++) {
//		switch (NM) {
//		case 1:m = 2;n = 6;break;
//		case 2:m = 2;n = 8;break;
//		case 3:m = 3;n = 8;break;
//		case 4:m = 3;n = 10;break;
//		case 5:m = 5;n = 10;break;
//		case 6:m = 5;n = 12;break;
//		}
//		//m = 10;n = 150;
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
//
//					//// 记录每个案例的平均最大完工时间，最优最大完工时间，平均取得最优解的时间
//					//string A = "C:\\Users\\Lenovo\\Desktop\\Rm rj sijk C Cmax\\Experimental-results\\Large-sized-instances\\GA";
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
//						//TL = (double)10 * m * n / 1000;
//						TL = 1;
//						cout << "*********************the results of instance- " << NA + 1 << "*******************************" << endl;
//						cout << "Max_st：" << Max_st << " " << "m：" << m << " " << "n：" << n << " " << "alpha：" << alpha << " " << "Rf：" << Rf << endl;
//						FILE* infile = nullptr;
//						char filename[200];
//						sprintf_s(filename, "D:\\Small-sized-instances\\M%d_N%d_P%d_P%d_S%d_S%d_alpha%0.2f_Rf%0.2f_%d.txt", m, n, min_pt, max_pt, Min_st, Max_st, alpha, Rf, NA + 1);
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
//							//解码
//							jiema();
//							for (int i = 0;i < Popsize;i++) {
//								group[i].truefit = getfitness(group[i].TABU);
//								group[i].C = getC(group[i].TABU);
//							}
//							//存在满足成本的解就不修复，不存在则对最好的解进行修复
//							int num = 0;
//							for (int i = 0;i < Popsize;i++) {
//								if (group[i].C <= budget) {
//									num++;
//								}
//							}
//							if (num == 0) {
//								//对最好的解进行修复
//								int index = 0;
//								for (int i = 0;i < Popsize;i++) {
//									if (group[index].truefit > group[i].truefit) {
//										index = i;
//									}
//								}
//								CS = group[index].C;
//								repair(index, 1);
//								group[index].truefit = getfitness(group[index].TABU);
//								group[index].C = CS;
//								for (int i = 0;i < m;i++) {
//									for (int j = 0;j < group[index].TABU[i].size();j++) {
//										for (int k = (group[index].TABU[i][j] - 1) * m;k < group[index].TABU[i][j] * m;k++) {
//											group[index].a[k] = rand() / (RAND_MAX + 1.0);
//										}
//										int index1 = (group[index].TABU[i][j] - 1) * m;
//										for (int k = (group[index].TABU[i][j] - 1) * m;k < group[index].TABU[i][j] * m;k++) {
//											if (group[index].a[k] < group[index].a[index1]) {
//												index1 = k;
//											}
//										}
//										swap(group[index].a[index1], group[index].a[(group[index].TABU[i][j] - 1) * m + i]);
//									}
//									for (int j = 0;j < group[index].TABU[i].size();j++) {
//										for (int k = 0;k < group[index].TABU[i].size() - 1 - j;k++) {
//											if (group[index].a[(group[index].TABU[i][k] - 1) * m + i] > group[index].a[(group[index].TABU[i][k + 1] - 1) * m + i]) {
//												for (int l = 0;l < m;l++) {
//													swap(group[index].a[(group[index].TABU[i][k] - 1) * m + l], group[index].a[(group[index].TABU[i][k + 1] - 1) * m + l]);
//												}
//											}
//										}
//									}
//								}
//							}
//							//更新全局最优解
//							int min = 0;
//							for (int i = 0;i < Popsize;i++) {
//								if (group[i].C <= budget) {
//									min = i;
//								}
//							}
//							//cout << "min：" << min << " " << getC(group[min].TABU) << endl;
//							for (int i = 0;i < Popsize;i++) {
//								if (group[i].C <= budget) {
//									if (group[i].truefit < group[min].truefit) {
//										min = i;
//									}
//								}
//							}
//							for (int i = 0;i < m;i++) {
//								gbest.TABU.push_back({});
//							}
//							for (int i = 0;i < n * m;i++) {
//								gbest.a.push_back(group[min].a[i]);
//							}
//							for (int i = 0;i < m;i++) {
//								for (int j = 0;j < group[min].TABU[i].size();j++) {
//									gbest.TABU[i].push_back(group[min].TABU[i][j]);
//								}
//							}
//							gbest.truefit = group[min].truefit;
//							gbest.C = group[min].C;
//							genBest = gen;
//							BXCPUT_it = clock();
//							BXCPUT = (double)(BXCPUT_it - GA_start_it) / CLOCKS_PER_SEC;//update the CPU time when the best solution is found
//							//cout << "初始最优解：" << endl;
//							//for (int j = 0;j < m;j++) {
//							//	for (int k = 0;k < gbest.TABU[j].size();k++) {
//							//		cout << gbest.TABU[j][k] << " ";
//							//	}
//							//	cout << endl;
//							//}
//							//cout << gbest.truefit << " " << gbest.C << endl;
//							do {
//								gen++;
//								//选择
//								select();
//								//交叉
//								cross();
//								//变异
//								mutate();
//								for (int i = 0;i < Popsize;i++) {
//									for (int j = 0;j < n * m;j++) {
//										group[i].a[j] = c_group[i].a[j];
//									}
//									for (int j = 0;j < m;j++) {
//										int s = group[i].TABU[j].size();
//										for (int k = 0;k < s;k++) {
//											group[i].TABU[j].pop_back();
//										}
//									}
//									for (int j = 0;j < m;j++) {
//										group[i].TABU.pop_back();
//									}
//								}
//								//cout << "LS前：" << endl;
//								//for (int i = 0;i < Popsize;i++) {
//								//	cout << group[i].truefit << " ";
//								//}
//								//cout << endl;
//								jiema();
//								//局部搜索
//								LS();
//								//cout << "LS：" << endl;
//								//for (int j = 0;j < m;j++) {
//								//	for (int k = 0;k < gbest.TABU[j].size();k++) {
//								//		cout << gbest.TABU[j][k] << " ";
//								//	}
//								//	cout << endl;
//								//}
//								//cout << gbest.truefit << " " << gbest.C << endl;
//								for (int i = 0;i < Popsize;i++) {
//									group[i].truefit = getfitness(group[i].TABU);
//									group[i].C = getC(group[i].TABU);
//								}
//								//cout << "LS后：" << endl;
//								//for (int i = 0;i < Popsize;i++) {
//								//	cout << group[i].truefit << " ";
//								//}
//								//cout << endl;
//								//存在满足成本的解就不修复，不存在则对最好的解进行修复
//								int num = 0;
//								for (int i = 0;i < Popsize;i++) {
//									if (group[i].C <= budget) {
//										num++;
//									}
//								}
//								if (num == 0) {
//									int index = 0;
//									for (int i = 0;i < Popsize;i++) {
//										if (group[index].truefit > group[i].truefit) {
//											index = i;
//										}
//									}
//									CS = group[index].C;
//									if (rand() / (RAND_MAX + 1.0) < Pr) {
//										repair(index, 1);
//									}
//									else {
//										repair(index, 0);
//									}
//									group[index].truefit = getfitness(group[index].TABU);
//									group[index].C = CS;
//									//重新编码
//									for (int i = 0;i < m;i++) {
//										for (int j = 0;j < group[index].TABU[i].size();j++) {
//											//随机生成小数
//											for (int k = (group[index].TABU[i][j] - 1) * m;k < group[index].TABU[i][j] * m;k++) {
//												group[index].a[k] = rand() / (RAND_MAX + 1.0);
//											}
//											//找到最小的数
//											int index1 = (group[index].TABU[i][j] - 1) * m;
//											for (int k = (group[index].TABU[i][j] - 1) * m;k < group[index].TABU[i][j] * m;k++) {
//												if (group[index].a[k] < group[index].a[index1]) {
//													index1 = k;
//												}
//											}
//											swap(group[index].a[index1], group[index].a[(group[index].TABU[i][j] - 1) * m + i]);
//										}
//										//重新排序决定加工顺序
//										for (int j = 0;j < group[index].TABU[i].size();j++) {
//											for (int k = 0;k < group[index].TABU[i].size() - 1 - j;k++) {
//												if (group[index].a[(group[index].TABU[i][k] - 1) * m + i] > group[index].a[(group[index].TABU[i][k + 1] - 1) * m + i]) {
//													for (int l = 0;l < m;l++) {
//														swap(group[index].a[(group[index].TABU[i][k] - 1) * m + l], group[index].a[(group[index].TABU[i][k + 1] - 1) * m + l]);
//													}
//												}
//											}
//										}
//									}
//								}
//								for (int i = 0;i < Popsize;i++) {
//									if (group[i].C <= budget) {
//										if (group[i].truefit < gbest.truefit) {
//											for (int j = 0;j < m * n;j++) {
//												gbest.a[j] = group[i].a[j];
//											}
//											for (int j = 0;j < m;j++) {
//												int s = gbest.TABU[j].size();
//												for (int k = 0;k < s;k++) {
//													gbest.TABU[j].pop_back();
//												}
//											}
//											for (int j = 0;j < m;j++) {
//												for (int k = 0;k < group[i].TABU[j].size();k++) {
//													gbest.TABU[j].push_back(group[i].TABU[j][k]);
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
//								for (int i = 0;i < Popsize;i++) {
//									int s = c_group[i].a.size();
//									for (int j = 0;j < s;j++) {
//										c_group[i].a.pop_back();
//									}
//								}
//								for (int i = 0;i < Popsize;i++) {
//									int s = s_group[i].a.size();
//									for (int j = 0;j < s;j++) {
//										s_group[i].a.pop_back();
//									}
//								}
//								GA_finish_it = clock();
//								CPUT = (double)(GA_finish_it - GA_start_it) / CLOCKS_PER_SEC;
//							} while (CPUT < TL);
//							cout << "全局最优解：" << endl;
//							for (int i = 0;i < n * m;i++) {
//								cout << gbest.a[i] << " ";
//							}
//							cout << endl;
//							for (int j = 0;j < m;j++) {
//								for (int k = 0;k < gbest.TABU[j].size();k++) {
//									cout << gbest.TABU[j][k] << " ";
//								}
//								cout << endl;
//							}
//							cout << "BestObjectiveValue=" << gbest.truefit << " MachineUsageCost=" << gbest.C << endl;
//							cout << "genBest=" << genBest << " BXCPUT=" << BXCPUT << endl;
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
//							for (int i = 0;i < Popsize;i++) {
//								int s = group[i].a.size();
//								for (int j = 0;j < s;j++) {
//									group[i].a.pop_back();
//								}
//								for (int j = 0;j < m;j++) {
//									int s1 = group[i].TABU[j].size();
//									for (int k = 0;k < s1;k++) {
//										group[i].TABU[j].pop_back();
//									}
//								}
//								for (int j = 0;j < m;j++) {
//									group[i].TABU.pop_back();
//								}
//							}
//							int s = gbest.a.size();
//							for (int j = 0;j < s;j++) {
//								gbest.a.pop_back();
//							}
//							for (int j = 0;j < m;j++) {
//								int s1 = gbest.TABU[j].size();
//								for (int k = 0;k < s1;k++) {
//									gbest.TABU[j].pop_back();
//								}
//							}
//							for (int j = 0;j < m;j++) {
//								gbest.TABU.pop_back();
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