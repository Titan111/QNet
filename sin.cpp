#include<iostream>
#include<vector>
#include<math.h>
#include"tiny_dnn/tiny_dnn.h"

using namespace std;
using namespace tiny_dnn;
using namespace tiny_dnn::layers;
using namespace tiny_dnn::activation;

#define PI 3.14159265358979323846264338

int main()
{
	adagrad opt;
	network<sequential> nn;
	int units_nums[] = {1,30,30,1};
	nn = make_mlp<tanh_layer>(units_nums,units_nums+4);
	vec_t x(1);
	vec_t y(1);

	for(int epoch=0;epoch<100;epoch++)
	{
		for(int i = 0;i<100;i++)
		{
			vector<vec_t> input_data;
			vector<vec_t> teach_data;
			x[0]=(double)i/100;
			y[0]=sin((double)i/100*2*PI);
			input_data.push_back(x);
			teach_data.push_back(y);
			nn.fit<mse>(opt,input_data,teach_data,1,1);
		}
	}

	for(int i = 0;i<100;i++)
	{
		vec_t a(1);
		a[0]=(double)i/100;
		cout<<nn.predict(a)[0]<<endl;
	}

}
