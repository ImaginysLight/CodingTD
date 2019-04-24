#pragma once
#include<iostream>
using namespace std;

class Question{
public:
	int id = 0;
	int type = 1;
	string content = "";
	string dapAnA = "A. ";
	string dapAnB = "B. ";
	string dapAnC = "C. ";
	string dapAnD = "D. ";
	string dapAn = "";
	float time = 0;
	int level = 0;
};