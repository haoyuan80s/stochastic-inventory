#ifndef IC_RANDOM_H
#define IC_RANDOM_H
#include "IC_Policy.h"
using namespace std;

template<class W>
vector<double> ConditionalExp(double y,Policy<W> &policy){
	//cout<<"Alert!!!!!!!!!!!!!!!! The ConditionalExp is called!!!!!!!!!!"<<endl;
	
	vector<double> temp;
	if(policy.alg==1){
		temp.push_back((y - 10.1)*(y-10.1));
		temp.push_back(1);
		temp.push_back(1);
	}
	if(policy.alg==2){
		temp.push_back((y - 10.1)*(y-10.1));
		temp.push_back(1);
		temp.push_back(1);
	}
	if(policy.alg==3){
		temp.push_back(y-10.1);
		temp.push_back(1);
		temp.push_back(1);
	}
	
	return temp;
}


template<class W>
int RandomDemand(Policy<W> &policy){
	//cout<<"Alert!!!!!!!!!!!!!!!! The RandomDemand is called!!!!!!!!!!"<<endl;
	policy.d[policy.cur]=1;
	return 1;
}

#endif

