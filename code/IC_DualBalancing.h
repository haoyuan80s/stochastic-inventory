#ifndef IC_DUALBALANCING_H
#define IC_DUALBALANCING_H
#include "IC_Policy.h"
#include "IC_Random.h"
#include <cmath>
using namespace std;

template <class W>
int DualBalancing (Policy<W>& P) {
	if(P.cur<P.T){
		P.cur =P.cur+1;
		if (P.cur > P.T - P.L) {
			P.q[P.cur] = 0;
		} 
		else {
			vector<double> v;
			double min = 0;
			double max = 1000;
			while(true) {
				v = ConditionalExp(max,P);
				if (v[0] - v[1] < 0) 
					max *= 2;
				else
					break;
			}
			double eps = 0.00001;
			double q = (min + max) / 2;
			while (true) {
				v = ConditionalExp(q,P);
				if (abs(v[0] - v[1]) < eps) break;
				else if(v[0] - v[1] > 0) {
					max = q;
					q = (min + q)/2;
				} else {
					min = q;
					q = (max+q)/2;
				}
			}
			P.q[P.cur] = q;
		}
		RandomDemand(P);
	}
	return 1;
}

#endif