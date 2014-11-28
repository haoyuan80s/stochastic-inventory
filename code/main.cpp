#include<vector>
#include<iostream>
#include"IC_ParameterData.h"
#include"IC_Policy.h"
#include"IC_Random.h"
#include"IC_DualBalancing.h"
#include"IC_DP.h"
#include"IC_Myopic.h"
#include"IC_Statistics.h"
#include"IC_Support.h"
using namespace std;

int main(int argc,char **argv){

	Policy<double> P;
	DualBalancing(P);

	vector<double> v;
	v.push_back(0.5);
	v.push_back(0.5);
	v.push_back(0.5);
	v.push_back(0.5);
	v.push_back(0.5);
	
	Policy<double> p1(5,2,v,v,v,0.99,10,0);
	RandomDemand(p1);
	
	vector<double> u;
	double y=10;

	u=ConditionalExp(y,p1);
	
	cout<<u[0]<<endl;
	cout<<u[1]<<endl;
	cout<<u[2]<<endl;

	p1.output();

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