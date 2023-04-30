#pragma once
#include <stdio.h>

/**
 ����maֵ

 @param value ��ʼ��������
 @param length ��ʼ�������鳤��
 @param m ����mֵ
 @param ma �洢maֵ������
 */
void calMa(const double value[], int length, int m, double ma[]);

/**
 ����emaֵ

 @param value ��ʼ��������
 @param length ��ʼ�������鳤��
 @param n ����nֵ
 @param ema �洢emaֵ������
 */
void calEma(const double value[], int length, int n, double ema[]);

/**
 ����smaֵ

 @param value ��ʼ��������
 @param length ��ʼ�������鳤��
 @param n ����nֵ
 @param m ����mֵ
 @param sma �洢smaֵ������
 */
void calSma(const double value[], int length, int n, int m, double sma[]);

/**
 ����hhvֵ

 @param value HLOC��ά����
 @param length ���鳤��
 @param n ����ֵ
 @param index HLOC��ά���鵱ǰ������ֵ
 @param x 0��߼�-1��ͼ�-2���̼�-3���̼�
 @return ����hhvֵ
 */
double calHhv(const double value[][4], int length, int n, int index, int x);

/**
 ����llvֵ

 @param value HLOC��ά����
 @param length ���鳤��
 @param n ����ֵ
 @param index HLOC��ά���鵱ǰ������ֵ
 @param x 0��߼�-1��ͼ�-2���̼�-3���̼�
 @return ����llvֵ
 */
double calLlv(const double value[][4], int length, int n, int index, int x);

/**
 ����REFֵ

 @param value ԭʼ����
 @param length ���鳤��
 @param index ��ǰ�����±�ֵ
 @param n ȡǰn�����ڵ�ֵ
 @return ����refֵ
 */
double calRef(const double value[], int length, int index, int n);

/**
 ����STDֵ

 @param x ��һ����ֵ����
 @param n �ڶ�����ֵ
 @param length ���鳤��
 @param index ��һ����ֵ���鵱ǰ������
 @return ���ؼ���ֵ
 */
double calStd(double x[], double n, int length, int index);

/**
 ����ƽ������ƫ��

 @param X ��һ������
 @param U �ڶ�������
 @param count N
 @return ���ؼ�����ֵ
 */
double calAVEDEV(const double X[], const double U[], const int count);

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
    double expmema[]);


/**
 �����ۺ�

 @param data ��������
 @param N ����ֵ
 @param I ����ֵ
 @return �ܺ�ֵ
 */
double calSum(const double data[],
    const int N,
    const int I);