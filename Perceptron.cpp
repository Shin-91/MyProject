/*
 Artificial Intelligence
 Project #1
<Perceptron Training Algorithm>

 - University of Seoul
 - Computer Science
 - 2011920031 신동주

 - Perceptron.cpp(16.09.14)
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;


ofstream outFile("output.txt", ios::app);       //txt파일 출력을 위해

class perceptron
{
public:
    perceptron(double c1, int x, int gate)      // constant c, X0, Gate Number(AND:0, OR:1, XOR:2)
    {

        this->w0 = rand() % 30;                 //make random number
        this->w1 = rand() % 30;
        this->w2 = rand() % 30;
        this->c = c1;
        this->x0 = x;
        this->gate_num = gate;
    }
    bool check()                                //Fnet 값과 원하는 게이트의 Output 값을 비교
    {
        for(int i=0;i<4;i++)
        {
            if(Fnet[i] != target[gate_num][i])
                return false;
        }
        return true;
    }
    void delta(int a, int b)                    //delta-rule
    {
        w0 = w0 + (c * (double)b * (double)x0);
        w1 = w1 + (c * (double)b * (double)x1[a]);
        w2 = w2 + (c * (double)b * (double)x2[a]);
    }
    void cal_Net(int index)                     // Calculate net value
    {
        Net[index] = (x0 * w0) + (x1[index] * w1) + (x2[index] * w2);
    }
    void set_Fnet(int index)                    // Compare Net with threshold (threshold는 0으로 고정)
    {                                           // threshold의 직접적인 값은 0 이지만 x0와 w0의 값을 이용하여 fnet의 임계값을 정함
        Net[index] <= threshold ? Fnet[index] = 0 : Fnet[index] = 1;
    }
    void cal_Error(int n)                       // Calculate Error
    {
        E[n] = target[gate_num][n] - Fnet[n];
        if(E[n] != 0)                           //Error가 0이 아니면 delta-rule 진행
            delta(n, E[n]);
    }
    void print_Data()                           //Round별로 값을 출력하기 위한 함수
    {

        cout.setf(ios::right);                  //오른쪽 정렬
        outFile.setf(ios::right);
        //간격에 맞춰 값 출력
        cout <<setw(3)<<"X0"<<setw(6)<<"X1"<<setw(6)<<"X2"<<setw(6)<<"W0"<<setw(6)<<"W1"<<setw(6)<<"W2"<<setw(9)<<"Net"<<setw(6)<<"Fnet"<<endl;
        outFile <<setw(3)<<"X0"<<setw(6)<<"X1"<<setw(6)<<"X2"<<setw(6)<<"W0"<<setw(6)<<"W1"<<setw(6)<<"W2"<<setw(9)<<"Net"<<setw(6)<<"Fnet"<<endl;
        for(int i=0;i<4;i++)
        {
            cout << "------------------------------------------------" << endl;
            cout <<setw(3)<<x0<<setw(6)<<x1[i]<<setw(6)<<x2[i]<<setw(6)<<w0<<setw(6)<<w1<<setw(6)<<w2<<setw(9)<<Net[i]<<setw(6)<<Fnet[i]<<endl;
            outFile << "------------------------------------------------" << endl;
            outFile <<setw(3)<<x0<<setw(6)<<x1[i]<<setw(6)<<x2[i]<<setw(6)<<w0<<setw(6)<<w1<<setw(6)<<w2<<setw(9)<<Net[i]<<setw(6)<<Fnet[i]<<endl;
        }
        cout << endl;
        outFile << endl;
    }

private:
    int threshold = 0;                          // 임계값
    double w0, w1, w2;
    int x1[4] = {0, 0, 1, 1};               // input value (0,0), (0,1), (1,0), (1,1)
    int x2[4] = {0, 1, 0, 1};
    int target[3][4] = {
        {0, 0, 0, 1}, // AND GATE
        {0, 1, 1, 1}, // OR GATE
        {0, 1, 1, 0}  // XOR GATE
        };
    int gate_num;
    double Net[4];
    int Fnet[4];
    int E[4];
    double c;
    int x0;
};


int main(void)
{

    int p = 1;          // Round cnt
    string str[3] = {"AND", "OR", "XOR"};
    srand((unsigned)time(NULL));
    double a, b;           // constant c, x0 value
    int q;                 // Gate_Number AND:0  OR:1  XOR:2

    cout << "C, X0, Gate_num을 입력하세요(Gate_num  AND:0, OR:1, XOR:2)\n";
    cin >> a >> b >> q;
    getchar();
    outFile << "C = " << a << "  X0 = " << b << "  Gate = " << str[q] << endl << endl;
    perceptron percep = perceptron(a, b, q);   // 객체 생성

    while(1)
    {
        if(p >100)                              //100 Round까지만 반복하며 delta_rule을 진행
        {                                       //100 Round를 진행하여도 정답을 못찾으면 입력값이 잘못되었거나 답이 나올 수 없는 경우라 판단(XOR의 경우)
            cout << endl <<  str[q] << "_Gate의 답을 찾지 못하였습니다.";
            outFile << endl <<  str[q] << "_Gate의 답을 찾지 못하였습니다.";
            break;
        }
        printf("ROUND #%d\n", p);
        outFile << "ROUND #" << p << endl;
        p++;
        for(int i=0;i<4;i++)
        {
            percep.cal_Net(i);                  //Calculate Net & Fnet
            percep.set_Fnet(i);
        }

        percep.print_Data();                    //현재 값 출력

        if(percep.check())                      //구한 Fnet을 이용하여 정답인지 확인
        {
            cout << "정답을 찾았습니다!!!!!\n";          //정답이면 반복문 탈출
            outFile << "정답을 찾았습니다!!!!!\n\n\n\n";
            getchar();
            break;
        }
        else
        {                                       //정답이 아니라면
            for(int i=0; i<4; i++)
            {
                percep.cal_Error(i);            //에러를 계산
            }
        }
    }
    return 0;
}
