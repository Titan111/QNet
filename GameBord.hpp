#ifndef __GAME_BORD__
#define __GAME_BORD__
#include<iostream>
#include<vector>

#define GAME_SIZE 9
#define LINE_MAX 8
#define LINE_LEN 3
using namespace std;

using  PID = unsigned char;

class GameBord
{
	private:
		vector<PID> cells_;
	public:	
		GameBord();
		void init();
		int set_next(PID p,int n);
		vector<PID> get_state(){return cells_;};
		PID get_winner();
		void show();
		bool is_end();
};
#endif
