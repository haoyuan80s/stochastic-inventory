#include<vector>
#include<iostream>
#include"IC_ParameterData.h"
#include"IC_Policy.h"
#include"IC_Statistics.h"
using namespace std;

int main(int argc,char **argv){


	vector<double> v;
	v.push_back(0.22);
	v.push_back(0.22);
	v.push_back(0.22);
	v.push_back(0.22);
	v.push_back(0.22);
	
	Policy<double> p1(5,2,v,v,v);
	p1.output();
	p1.ParameterData::output();

	system("pause");
	return 0;
}

	
	/*
	ParameterData ic1;
	ic1.output();
	ic1.output_t(1);
	ParameterData ic2(5,2,0.5,0.3,0.2);
	ic2.output();

	Policy<double> db1;
	db1.output();
	db1.ParameterData::output();	
	
	
	vector<double> v;
	v.push_back(0.22);
	v.push_back(0.22);
	v.push_back(0.22);
	v.push_back(0.22);
	v.push_back(0.22);
	
	Policy<double> p1(5,2,v,v,v);
	p1.output();
	p1.ParameterData::output();
	*/