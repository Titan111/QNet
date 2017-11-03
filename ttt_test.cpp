#include<iostream>
#include"QNet.hpp"
#include"TTTEnv.hpp"

using namespace std;

int main()
{
	network<sequential> nn;
	int units_nums[] = {9,50,50,9};
	nn = make_mlp<tanh_layer>(units_nums,units_nums+4);
	QNet agent(nn);
	agent.t = 0.5;

	int one_cycle = 10000;
	for(int epoch=0;epoch<2;epoch++)
	{
		int win=0;
		for(int i=0;i<one_cycle;i++)
		{
			TTTEnv env;
			while(!env.is_end())
			{
				int act = agent.action(env.get_state());
				double r = env.play(act);
				agent.make_data(env.get_state(),r);
			}
			if(env.get_winner()==1)
				win++;
			agent.learn();
		}
		cout<<win<<endl;
	}
}
