#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
using namespace std;

// 參數設定:
// Runs: 51
// Dimension: 10, 30, 100 維度
// Evaluation times: Dimension × 10^4  最高評估次數
// Population size: 30, 100, 400 指NP(5*D - 10*D間，至少需4)
// F (Scaling Factor): 自行設定或參考論文 0.5
// CR (Crossover Rate): 自行設定或參考論文 0.1||0.9



double ackyle_fun(const vector<double>& x, int D){
    double a=20, b=0.2, c=2 * M_PI ; //d維度
    double sum1 = 0.0, sum2 = 0.0;
    for(int i=0;i<D;++i){
        sum1 += x[i] * x[i];
        sum2 += cos(c * x[i]);
    }
    //  [-32.768, 32.768]
    return -a*exp(-b*sqrt(sum1/D)) - exp(sum2/D) + a +exp(1);
    // f(0) = 0;
}

//單一run求最佳解 
double DE(int D,int NP,double F ,double CR){
    int evals = 0;
    //1. initialize
    double L=-32.768,R =32.768;//[-32.768, 32.768]
    //uniform probability distribution
    random_device rd;//接近隨機的亂數
    mt19937 gen(rd());
    uniform_real_distribution<float> unif(L, R);
    //NP個random vector
    vector<vector<double>> vector_populationis(NP, vector<double>(D));
    //放NP個向量進ack後的計算結果
    vector<double> cost(NP);
    for (int i = 0; i < NP; ++i) {//NP個D維向量
        for (int j = 0; j < D; ++j) {           
            vector_populationis[i][j] = unif(gen);
        }
        cost[i] = ackyle_fun(vector_populationis[i], D);//將最初向量接用ackyle_fun計算後，記錄初始值
        // evals++;//算一次ackyle_fun
    }
    evals = NP;
    
    //2.DE
    uniform_int_distribution<int> dist_rx(0, NP-1 );//0~ NP-1
    uniform_int_distribution<int> dist_j(0, D-1);
    while (evals < D*10000)//不可超過Evaluation times
    {
        for(int i=0;i<NP;++i){
            //1.Mutation
            int r1,r2,r3;
            //r1 r2 r3 i互不相等
            do{r1 = dist_rx(gen);} while(r1 == i);
            do{r2 = dist_rx(gen);} while (r2 == i || r2 == r1);
            do{r3 = dist_rx(gen);} while (r3 == i || r3 == r1 || r3 == r2);

            //2.Crossover
            vector<double> trial(D);//紀錄Crossover後的新變化向量，D維度
            uniform_real_distribution<double> dis(0.0, 1.0);

            int rnbr = dist_j(gen);//每向量有一rnbr(i)，確保至少有一個會是vi(突變)
            for(int j=0;j<D;++j){
                //新變化向量[j]=r1向量[j]+F*(r2向量[j]-r3向量[j])
                if(dis(gen)<=CR ||j == rnbr)
                    trial[j] = vector_populationis[r1][j]+F*(vector_populationis[r2][j]-vector_populationis[r3][j]);
                //仍是原向量不變化
                else 
                    trial[j] = vector_populationis[i][j];
            }
            //3.Selection(選新舊誰好)
            double score = ackyle_fun(trial,D);
            // evals++;
            if(score <= cost[i]){
                vector_populationis[i] = trial;
                cost[i] = score;
            }
        }
        evals +=NP;
    }
    //3.找本次最佳解
    double this_run_best = cost[0];
    for(int i=1;i<NP;++i){
        if(this_run_best > cost[i])
            this_run_best = cost[i];
    }
    return this_run_best;
}
int main(){
    int Runs,D,NP;
    double F ,CR;
    cout <<"input：";
    if(!(cin >> Runs >> D >> NP >> F >> CR)) 
        return 0;

    double Best_fitness , Average_run = 0;
    for(int i =0;i<Runs;++i){
        double now_fitness = DE(D,NP,F ,CR);
        Average_run += now_fitness;
        if(i == 0) Best_fitness = now_fitness;
        else if(Best_fitness > now_fitness)
            Best_fitness = now_fitness;
    }
    Average_run = Average_run / Runs;

    cout << "Best fitness of "<<Runs<<" runs:"<< Best_fitness <<endl;
    cout << "Average of " <<Runs<<" Runs’ best fitness:"<< Average_run <<endl;
}