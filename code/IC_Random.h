#ifndef IC_RANDOM_H
#define IC_RANDOM_H
#include"IC_Policy.h"
using namespace std;

template<class W>
vector<double> ConditionalExp(W y,Policy<W> &policy){
	cout<<"Alert!!!!!!!!!!!!!!!! The ConditionalExp is called!!!!!!!!!!"<<endl;
	
	vector<double> temp;
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	
	return temp;
}


template<class W>
int RandomDemand(Policy<W> &policy){
	cout<<"Alert!!!!!!!!!!!!!!!! The RandomDemand is called!!!!!!!!!!"<<endl;
	policy.d[policy.cur]=1;
	return 1;
}

#endif
