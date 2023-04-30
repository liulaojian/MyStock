#include "BaseIndicator.h"
#include <math.h>
#include <stdint.h>
#include <limits.h>
/**
 ����maֵ

 @param value ��ʼ��������
 @param length ��ʼ�������鳤��
 @param m ����mֵ
 @param ma �洢maֵ������
 */
void calMa(const double value[], int length, int m, double ma[])
{
    double sum = 0;
    for (int idx = length - 1; idx >= 0; idx--)
    {
        if (idx >= m)
        {
            for (int jdx = 0; jdx < m; jdx++)
            {
                sum += value[idx - jdx];
            }
            ma[idx] = sum / m;
            sum = 0;
        }
        else
        {
            ma[idx] = value[idx];
        }
    }
}


/**
 ����emaֵ

 @param value ��ʼ��������
 @param length ��ʼ�������鳤��
 @param n ����nֵ
 @param ema �洢emaֵ������
 */
void calEma(const double value[], int length, int n, double ema[])
{
    ema[0] = 50;
    for (int idx = 1; idx < length; idx++)
    {
        ema[idx] = (value[idx] * 2 + ema[idx - 1] * (n - 1)) / (n + 1);
    }
}


/**
 ����smaֵ

 @param value ��ʼ��������
 @param length ��ʼ�������鳤��
 @param n ����nֵ
 @param m ����mֵ
 @param sma �洢smaֵ������
 */
void calSma(const double value[], int length, int n, int m, double sma[])
{
    sma[0] = 50;
    for (int idx = 1; idx < length; idx++)
    {
        sma[idx] = (value[idx] * m + sma[idx - 1] * (n - m)) / n;
    }
}

/**
 ����hhvֵ

 @param value HLOC��ά����
 @param length ���鳤��
 @param n ����ֵ
 @param index HLOC��ά���鵱ǰ������ֵ
 @param x 0��߼�-1��ͼ�-2���̼�-3���̼�
 @return ����hhvֵ
 */
double calHhv(const double value[][4], int length, int n, int index, int x)
{
    double hhv = (double)INT32_MIN;
    if (index > n)
    {
        for (int idx = n; idx > 0; idx--)
        {
            if (hhv < value[index - idx][x])
            {
                hhv = value[index - idx][x];
            }
        }
    }
    else
    {
        for (int idx = index; idx >= 0; idx--)
        {
            if (hhv < value[idx][x])
            {
                hhv = value[idx][x];
            }
        }
    }

    return hhv;
}

/**
 ����llvֵ

 @param value HLOC��ά����
 @param length ���鳤��
 @param n ����ֵ
 @param index HLOC��ά���鵱ǰ������ֵ
 @param x 0��߼�-1��ͼ�-2���̼�-3���̼�
 @return ����llvֵ
 */
double calLlv(const double value[][4], int length, int n, int index, int x)
{
    double llv = (double)INT32_MAX;
    if (index > n)
    {
        for (int idx = n; idx > 0; idx--)
        {
            if (llv > value[index - idx][x])
            {
                llv = value[index - idx][x];
            }
        }
    }
    else
    {
        for (int idx = index; idx >= 0; idx--)
        {
            if (llv > value[idx][x])
            {
                llv = value[idx][x];
            }
        }
    }

    return llv;
}

/**
 ����REFֵ

 @param value ԭʼ����
 @param length ���鳤��
 @param index ��ǰ�����±�ֵ
 @param n ȡǰn�����ڵ�ֵ
 @return ����refֵ
 */
double calRef(const double value[], int length, int index, int n)
{
    if (n > 0 && n < length && index >= 0 && index < length)
    {
        if (index == 0)
        {
            return value[index];
        }
        else
        {
            return value[index - n];
        }
    }

    return 0;
}

/**
 ����STDֵ

 @param x ��һ����ֵ����
 @param n �ڶ�����ֵ
 @param length ���鳤��
 @param index ��һ����ֵ���鵱ǰ������
 @return ���ؼ���ֵ
 */
double calStd(double x[], double n, int length, int index)
{
    double sum = 0;

    for (int idx = 0; idx <= index; idx++)
    {
        sum += pow(x[idx] - n, 2);
    }

    if (0 == index)
    {
        return sqrt(sum);
    }
    else
    {
        return sqrt(sum / length);
    }
}

/**
 ����ƽ������ƫ��

 @param X ��һ������
 @param U �ڶ�������
 @param count N
 @return ���ؼ�����ֵ
 */
double calAVEDEV(const double X[], const double U[], const int count)
{
    double sum = 0.f;
    for (int i = 0; i <= count; i++)
    {
        sum += fabs(X[i] - U[i]);
    }
    if (count == 0)
    {
        return sum;
    }
    else
    {
        return sum / count;
    }
}

/**
 ����ƽ��ָ���ƶ�ƽ��

 @param dataX ��������
 @param countX �����С
 @param N expmema(N)�е�N��ֵ
 @param smooth ƽ��ֵ
 @param expmema �洢������ֵ������
 */
void calEXPMEMA(const double dataX[],
    const int countX,
    const int N,
    const double smooth,
    double expmema[])
{
    expmema[0] = smooth;
    calEma(dataX, countX, N, expmema);
}

/**
 �����ܺ�

 @param data ��������
 @param N ����ֵ
 @param I ����ֵ
 @return �ܺ�ֵ
 */
double calSum(const double data[], const int N, const int I)
{
    if (I == 0)
    {
        return data[0];
    }

    double sum = 0.f;
    int idx = 0;

    if (I >= N)
    {
        idx = N;
    }
    else {
        idx = I;
    }
    for (int i = 0; i < idx; i++)
    {
        sum += data[I - i];
    }

    return sum;
}