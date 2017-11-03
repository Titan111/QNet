#include<iostream>
#include"QNet.hpp"

using namespace std;

class Bandit
{
	public:
		double play(int act_id)
		{
			if(act_id == 7)
				return 1.0;
			else
				return 0.0;
		}
};
int main()
{
	Bandit env;

	network<sequential> nn;
	int units_nums[] = {1,10,9};
	nn = make_mlp<tanh_layer>(units_nums,units_nums+3);
	QNet agent(nn);
	agent.t = 0.2;

	vec_t x(1);
	x[0]=1;

	int action_num = 9;
	for(int epoch=0;epoch<100;epoch++)
	{
		agent.t -= 0.0015;
		double result[action_num] = {0,0,0,0,0,0,0,0,0};
		int n = 100;
		double sum_r = 0.0;
		for(int i=0;i<n;i++)
		{
			int act_id = agent.action(x);
			result[act_id]++;
			double r = env.play(act_id);
			sum_r += r;
			agent.make_data(x,r);
			agent.learn();
		}
		for(int i=0;i<action_num;i++)
		{
			cout<<result[i]/n<<" ";
		}
		cout<<sum_r;
		cout<<endl;
	}
}
