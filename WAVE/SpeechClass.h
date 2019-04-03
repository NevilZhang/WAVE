#ifndef _SPEECHCLASS_H_
#define _SPEECHCLASS_H_
#include <vector>
#include <iostream>
using namespace std;
class SpeechClass {
//属性
public:
	vector<vector<long double>> frame_data;

//默认函数
public:
	SpeechClass();
	SpeechClass(vector<vector<long double>> data);
//自定义函数
public:
	vector<long double> shortEnergy();	//短时能量
	vector<int> shortCrossZero();		//短时过零率
	void ConvertToFFT(
		vector<vector<long double>> pRealOut,           //输出的实部
		vector<vector<long double>> pImageOut           //输出的虚部
	);

};

#endif