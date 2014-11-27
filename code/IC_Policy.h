#ifndef IC_POLICY_H
#define IC_POLICY_H
#include"IC_ParameterData.h"
#include<fstream>
#include<string>
using namespace std;

//Policy is a class saving result and sample path for different algorithm approaches
template <class W>
class Policy:public ParameterData{
public:
	//The following are the datas we are going to generate while doing the optimization problem

	//alg include what algorithm we used to compute the policy
	//1 for DP, 2 for myopic, 3 for dual balancing
	int alg;
	//randomness is what kind of random process distribution we used to generat the demand
	int randomness;
	//rand_para include all the parameter for the distribution of the random process 
	vector<double> rand_para;

	//Current time period that we already know the inventory position, demand and ordering.
	int cur;
	//Cost Vector
	vector<double> C;
	//Holding Cost Vector
	vector<double> Ch;
	//Backlogging Cost Vector
	vector<double> Cp;
	//Inventory Position
	vector<W> x;
	//Net Inventory
	vector<W> NI;
	//Demand
	vector<W> d;
	//Order
	vector<W> q;
	//Accumulative Cost Vector
	vector<double> C_accum;
	//Accumulative Holding Cost Vector
	vector<double> Ch_accum;
	//Accumulative Backlogging Cost Vector
	vector<double> Cp_accum;
	//Accumulative Demand
	vector<W> d_accum;
	//Accumulative Order
	vector<W> q_accum;

	//Total Cost,Demand and Order
	double total_C;
	double total_Ch;
	double total_Cp;
	W total_d;
	W total_q;
	
	//Constructors
	//Default Constructor
	Policy();
	//Constructor assigning constant cost coefficient
	Policy(int vT,int vL,double vc,double vh,double vp,W x0=0);
	//general constructor
	Policy(int vT,int vL,vector<double> vc,vector<double> vh,vector<double> vpp,W x0=0);

	//Out put the sample path or the state set
	int output();
	//Output on screen
	int soutput();
	//Output to file
	int foutput();

	//This function update the sample path or the state after we get every demand and ordering in every 
	int update(int t,W y_t,W d_t);

	template<class X> friend class samples;
};

template <class W>
Policy<W>::Policy():ParameterData(){
	alg=0;
	randomness=0;
	rand_para.push_back(0);

	cur=0;
	total_C=0;
	total_Ch=0;
	total_Cp=0;
	total_d=0;
	total_q=0;

	C.push_back(0);
	Ch.push_back(0);
	Cp.push_back(0);
	x.push_back(0);
	NI.push_back(0);
	d.push_back(0);
	q.push_back(0);

	C_accum.push_back(0);
	Ch_accum.push_back(0);
	Cp_accum.push_back(0);
	d_accum.push_back(0);
	q_accum.push_back(0);
}

template <class W>
Policy<W>::Policy(int vT,int vL,double vc,double vh,double vp,W x0=0):ParameterData(vT,vL,vc,vh,vp){
	alg=0;
	randomness=0;
	rand_para.push_back(0);

	cur=0;
	total_C=0;
	total_Ch=0;
	total_Cp=0;
	total_d=0;
	total_q=0;

	vector<double> temp(vT+1,0);
	C=temp;
	Ch=temp;
	Cp=temp;
	C_accum=temp;
	Ch_accum=temp;
	Cp_accum=temp;

	vector<W> tempW(vT+1,0);
	x=tempW;
	d=tempW;
	q=tempW;
	NI=tempW;
	d_accum=tempW;
	q_accum=tempW;

	x[0]=x0;
	NI[0]=x0;
}

template <class W>
Policy<W>::Policy(int vT,int vL,vector<double> vc,vector<double> vh,vector<double> vp,W x0=0):ParameterData(vT,vL,vc,vh,vp){
	alg=0;
	randomness=0;
	rand_para.push_back(0);

	cur=0;
	total_C=0;
	total_Ch=0;
	total_Cp=0;
	total_d=0;
	total_q=0;

	vector<double> temp(vT+1,0);
	C=temp;
	Ch=temp;
	Cp=temp;
	C_accum=temp;
	Ch_accum=temp;
	Cp_accum=temp;

	vector<W> tempW(vT+1,0);
	x=tempW;
	d=tempW;
	q=tempW;
	NI=tempW;
	d_accum=tempW;
	q_accum=tempW;

	x[0]=x0;
	NI[0]=x0;
}


template <class W>
int Policy<W>::output(){
	int temp;
	cout<<"Type 1 if you want output to screen, 0 otherwise."<<endl;
	cin>>temp;
	if(temp==1)
		soutput();
	temp=0;
	cout<<"Type 1 if you want output to a file, 0 otherwise."<<endl;
	cin>>temp;
	if(temp==1)
		foutput();
	return 1;
}


template <class W>
int Policy<W>::soutput(){
	int i;
	cout.precision(4);
	cout<<"Planning Horizon is: "<<T<<endl;
	cout<<"The Current Step is at time: "<<cur<<endl;
	cout<<"Leading Time is: "<<L<<endl;
	cout<<"Discount Rate is: "<<alpha<<endl;
	cout<<"The Algorithm is: "<<alg<<endl;
	cout<<"The Distribution Type is: "<<randomness<<endl;
	cout<<"The Distribution Parameters are: ";
	for(i=0;i<rand_para.size();i++)
		cout<<setw(10)<<rand_para[i];
	cout<<endl;
	cout<<"Total Cost is: "<<total_C<<endl;
	cout<<"Total Demand is: "<<total_d<<endl;
	cout<<"Total Order is: "<<total_q<<endl;
	cout<<"Total Holding Cost is: "<<total_Ch<<endl;
	cout<<"Total Backlogging Cost is: "<<total_Cp<<endl;
	cout<<endl;

	cout<<setw(6)<<"Period"<<setw(10)<<"Inv Pos"<<setw(10)<<"Net Inv"<<setw(10)<<"Cost"<<setw(10)<<"Demand"<<setw(10)<<"Ordering"<<setw(10)<<"H Cost"<<setw(10)<<"B Cost";
	cout<<setw(10)<<"Cost Ac"<<setw(10)<<"Demand Ac"<<setw(10)<<"Order Ac"<<setw(10)<<"H Cost Ac"<<setw(10)<<"B Cost Ac"<<endl;
	for(i=0;i<=T;i++){
		cout<<setw(6)<<i<<setw(10)<<x[i]<<setw(10)<<NI[i]<<setw(10)<<C[i]<<setw(10)<<d[i]<<setw(10)<<q[i]<<setw(10)<<Ch[i]<<setw(10)<<Cp[i];
		cout<<setw(10)<<C_accum[i]<<setw(10)<<d_accum[i]<<setw(10)<<q_accum[i]<<setw(10)<<Ch_accum[i]<<setw(10)<<Cp_accum[i]<<endl;
	}
	cout<<endl;

	return 1;
}

template <class W>
int Policy<W>::foutput(){
	char filename[200];
	cout<<"Please type a file name for output. (.txt)"<<endl;
	while(1){
		cin>>filename;
		ofstream fout;
		fout.open(filename,ios::out);
		if(fout){
			fout.seekp(0);
			cout<<"File is openned successfully, outputting data..."<<endl;
			
			int i;
			fout.precision(4);
			fout<<"Planning Horizon is: "<<T<<endl;
			fout<<"The Current Step is at time: "<<cur<<endl;
			fout<<"Leading Time is: "<<L<<endl;
			fout<<"Discount Rate is: "<<alpha<<endl;
			fout<<"The Algorithm is: "<<alg<<endl;
			fout<<"The Distribution Type is: "<<randomness<<endl;
			fout<<"The Distribution Parameters are: ";
			for(i=0;i<rand_para.size();i++)
				fout<<setw(10)<<rand_para[i];
			fout<<endl;
			fout<<"Total Cost is: "<<total_C<<endl;
			fout<<"Total Demand is: "<<total_d<<endl;
			fout<<"Total Order is: "<<total_q<<endl;
			fout<<"Total Holding Cost is: "<<total_Ch<<endl;
			fout<<"Total Backlogging Cost is: "<<total_Cp<<endl;
			fout<<endl;

			fout<<setw(6)<<"Period"<<setw(10)<<"Inv Pos"<<setw(10)<<"Net Inv"<<setw(10)<<"Cost"<<setw(10)<<"Demand"<<setw(10)<<"Ordering"<<setw(10)<<"H Cost"<<setw(10)<<"B Cost";
			fout<<setw(10)<<"Cost Ac"<<setw(10)<<"Demand Ac"<<setw(10)<<"Order Ac"<<setw(10)<<"H Cost Ac"<<setw(10)<<"B Cost Ac"<<endl;
			for(i=0;i<=T;i++){
				fout<<setw(6)<<i<<setw(10)<<x[i]<<setw(10)<<NI[i]<<setw(10)<<C[i]<<setw(10)<<d[i]<<setw(10)<<q[i]<<setw(10)<<Ch[i]<<setw(10)<<Cp[i];
				fout<<setw(10)<<C_accum[i]<<setw(10)<<d_accum[i]<<setw(10)<<q_accum[i]<<setw(10)<<Ch_accum[i]<<setw(10)<<Cp_accum[i]<<endl;
			}
			fout<<endl;

			fout.close();
			cout<<"Data output finished."<<endl<<endl;
			break;
		}
	}
	return 1;
}

template<class W>
int Policy<W>::update(int t, W y_t, W d_t){
	cur=t;

	
}



#endif