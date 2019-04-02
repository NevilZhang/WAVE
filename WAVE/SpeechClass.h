#pragma once
#include <vector>
#include <iostream>
using namespace std;
class SpeechClass {
public:
	vector<vector<long double>> frame_data;
	SpeechClass();
	SpeechClass(vector<vector<long double>> data);

};
SpeechClass::SpeechClass() {

}

SpeechClass::SpeechClass(vector<vector<long double>> data) {
	frame_data.assign(data.begin(), data.end());
}
