#ifndef __QNET__
#define __QNET__

#include <vector>
#include <algorithm>
#include <functional>
#include "tiny_dnn/tiny_dnn.h"

using namespace std;
using namespace tiny_dnn;
using namespace tiny_dnn::layers;
using namespace tiny_dnn::activation;

class QNet
{
	public:
	QNet(network<sequential> nn)
	{
		Q=nn;
		
		input_data.resize(0);
		teach_data.resize(0);
		t = 0.1;//ボルツマン分布の温度
		gamma = 0.95;
	}
	private:
	network<sequential> Q;
	vec_t befor_x_;
	vec_t befor_q_out_;
	vector<vec_t> input_data;
	vector<vec_t> teach_data;
	gradient_descent opt;
	int befor_action_;
	double gamma;
	

	int max_id(vec_t x)
	{
		vec_t::iterator max_itr = std::max_element(x.begin(),x.end());
		return std::distance(x.begin(),max_itr);
	}
int roulet(vector<double> x)
{
	double random = (double)rand()/(double)RAND_MAX; 
	int i;
	double sum = 0.0;
	for(i=0;;i++)
	{
		sum+=x[i];
		if(sum>=random)
			break;
	}
	return i;
}

	int softmax(vec_t x)
	{
		double bunbo=0; 
		for(int i=0;i<x.size();i++)
		{
			bunbo += exp(x[i]/t);
		}
		vector<double> prob;
		prob.resize(x.size());
		for(int i=0;i<x.size();i++)
		{
			prob[i]=exp(x[i]/t)/bunbo;
		}
		return roulet(prob);
	} 

	public:
	double t;
	int action(vec_t x)
	{
		befor_x_ = x;
		befor_q_out_ = Q.predict(x);
		int act_id = softmax(befor_q_out_);
		befor_action_ = act_id;
		return act_id;
	}
	void make_data(vec_t x,double r)
	{
		vec_t q_out=Q.predict(x);
		int q_max=max_id(q_out);
		double teach = r;+gamma*q_out[q_max];
		int vec_dim = q_out.size();
		vec_t teach_vec(vec_dim);
		for(int i=0;i<vec_dim;i++)
		{
			if(i==befor_action_)
				teach_vec[i]=teach;
			else
				teach_vec[i]=q_out[i];
		}
		input_data.push_back(befor_x_);
		teach_data.push_back(teach_vec);;
	}
	void learn()
	{
		Q.fit<mse>(opt,input_data,teach_data,input_data.size(),1);
		input_data.resize(0);
		teach_data.resize(0);
	}
};
#endif


