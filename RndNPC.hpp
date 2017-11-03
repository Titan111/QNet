#ifndef __RND_NPC__
#define __RND_NPC__

#include<stdlib.h>
#include<time.h>
#include<vector>

using namespace std;

typedef unsigned char PID;

class RndNPC{
	private:
		const int SIZE_;
		const int ID_;
	public:
		RndNPC(PID id):
			SIZE_(9),
			ID_(id)
	{
		srand((unsigned)time(NULL));
	}

	int count_0(vector<PID> now)
	{
		int ans=0;
		for(int i=0;i<SIZE_;i++){
			if(now[i]==(PID)0){
				ans++;
			}
		}
		return ans;
	}

#define LINE_MAX 8
#define LENE_KEN 3
	int get_next(vector<PID> now){

	static PID CHECK[LINE_MAX][LINE_LEN]={
		{0,1,2},
		{3,4,5},
		{6,7,8},
		{0,3,6},
		{1,4,7},
		{2,5,8},
		{0,4,8},
		{2,4,6}
	};
	for(int i=0;i<LINE_MAX;i++)
	{
		int a = now[CHECK[i][0]]==ID_?1:0;
		int b = now[CHECK[i][1]]==ID_?1:0;
		int c = now[CHECK[i][2]]==ID_?1:0;
		if((a+b+c)>=2)
		{
			for(int j=0;j<LINE_LEN;j++)
			{
				if(now[CHECK[i][j]] == 0)
				{
					//return CHECK[i][j];
				}
			}
		}
	}
		int zero_c=count_0(now);
		int select=rand()%zero_c;
		for(int i=0;i<SIZE_;i++){
			if(now[i]==(PID)0){
				if(true||select==0){
					return i;
				}
				select--;
			}
		}
	}
};

#endif
