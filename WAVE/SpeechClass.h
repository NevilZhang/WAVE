#ifndef _SPEECHCLASS_H_
#define _SPEECHCLASS_H_
#include <vector>
#include <iostream>
using namespace std;
class SpeechClass {
//����
public:
	vector<vector<long double>> frame_data;

//Ĭ�Ϻ���
public:
	SpeechClass();
	SpeechClass(vector<vector<long double>> data);
//�Զ��庯��
public:
	vector<long double> shortEnergy();	//��ʱ����
	vector<int> shortCrossZero();		//��ʱ������
	void ConvertToFFT(
		vector<vector<long double>> pRealOut,           //�����ʵ��
		vector<vector<long double>> pImageOut           //������鲿
	);

};

#endif