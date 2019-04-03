#include "StdAfx.h"
#include"SpeechClass.h"
#include"mathlib.h"
#include <vector>
#include <complex>
using namespace std;
/*=====================================默认函数=================================================*/
SpeechClass::SpeechClass(void) {

}
SpeechClass::SpeechClass(vector<vector<long double>> data) {
	frame_data.assign(data.begin(), data.end());
}

/*=====================================自定义函数===============================================*/
vector<long double> SpeechClass::shortEnergy()
{
	/*
	function:短时能量
	*/
	vector<long double> En;
	for (int i = 0; i < frame_data.size(); i++) {
		En.push_back(0.0);
		for (int j = 0; j < frame_data[i].size(); j++)
			En[i] += frame_data[i][j];
	}

	return En;
}


vector<int> SpeechClass::shortCrossZero()
{
	/*
	function:短时过零率
	*/
	vector<int> Zn;
	for (int i = 0; i < frame_data.size(); i++) {
		Zn.push_back(0);
		for (int j = 1; j < frame_data[i].size(); j++) {
			Zn[i] = Zn[i] + abs(sgn(frame_data[i][j]) - sgn(frame_data[i][j - 1])) * 0.5;
		}
	}
	return Zn;
}

void SpeechClass::ConvertToFFT(vector<vector<long double>> pRealOut, vector<vector<long double>> pImageOut)
{
	unsigned int nCount = frame_data.size(), nShorts = frame_data[0].size();
	vector<vector<complex<long double>>> pDataout;
	vector<complex<long double>> temp;
	for (int k = 0; k < nCount; k++) {
		for (int i = 0; i < nShorts; i++) {
			temp.push_back(complex<long double>(frame_data[k][i],0));
		}
		FFT(temp, nShorts);
		pDataout.push_back(temp);

	}
}
