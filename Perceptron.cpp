/*
 Artificial Intelligence
 Project #1
<Perceptron Training Algorithm>

 - University of Seoul
 - Computer Science
 - 2011920031 �ŵ���

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


ofstream outFile("output.txt", ios::app);       //txt���� ����� ����

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
    bool check()                                //Fnet ���� ���ϴ� ����Ʈ�� Output ���� ��
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
    void set_Fnet(int index)                    // Compare Net with threshold (threshold�� 0���� ����)
    {                                           // threshold�� �������� ���� 0 ������ x0�� w0�� ���� �̿��Ͽ� fnet�� �Ӱ谪�� ����
        Net[index] <= threshold ? Fnet[index] = 0 : Fnet[index] = 1;
    }
    void cal_Error(int n)                       // Calculate Error
    {
        E[n] = target[gate_num][n] - Fnet[n];
        if(E[n] != 0)                           //Error�� 0�� �ƴϸ� delta-rule ����
            delta(n, E[n]);
    }
    void print_Data()                           //Round���� ���� ����ϱ� ���� �Լ�
    {

        cout.setf(ios::right);                  //������ ����
        outFile.setf(ios::right);
        //���ݿ� ���� �� ���
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
    int threshold = 0;                          // �Ӱ谪
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

    cout << "C, X0, Gate_num�� �Է��ϼ���(Gate_num  AND:0, OR:1, XOR:2)\n";
    cin >> a >> b >> q;
    getchar();
    outFile << "C = " << a << "  X0 = " << b << "  Gate = " << str[q] << endl << endl;
    perceptron percep = perceptron(a, b, q);   // ��ü ����

    while(1)
    {
        if(p >100)                              //100 Round������ �ݺ��ϸ� delta_rule�� ����
        {                                       //100 Round�� �����Ͽ��� ������ ��ã���� �Է°��� �߸��Ǿ��ų� ���� ���� �� ���� ���� �Ǵ�(XOR�� ���)
            cout << endl <<  str[q] << "_Gate�� ���� ã�� ���Ͽ����ϴ�.";
            outFile << endl <<  str[q] << "_Gate�� ���� ã�� ���Ͽ����ϴ�.";
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

        percep.print_Data();                    //���� �� ���

        if(percep.check())                      //���� Fnet�� �̿��Ͽ� �������� Ȯ��
        {
            cout << "������ ã�ҽ��ϴ�!!!!!\n";          //�����̸� �ݺ��� Ż��
            outFile << "������ ã�ҽ��ϴ�!!!!!\n\n\n\n";
            getchar();
            break;
        }
        else
        {                                       //������ �ƴ϶��
            for(int i=0; i<4; i++)
            {
                percep.cal_Error(i);            //������ ���
            }
        }
    }
    return 0;
}
