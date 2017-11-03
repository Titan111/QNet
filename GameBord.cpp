#include<iostream>
#include"GameBord.hpp"
#include"debug.hpp"

using namespace std;

GameBord::GameBord(){
	cells_.resize(GAME_SIZE);
	init();
}
void GameBord::init(){
	for(int i=0;i<GAME_SIZE;i++){
		cells_[i]=0;
	}
}

int GameBord::set_next(PID p,int n){
	if(cells_[n]==0)
	{
		cells_[n]=p;
		return 0;
	}else
	{
		return 1;
	}
}

PID GameBord::get_winner(){
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

	PID check_id;

	for(int i=0;i<LINE_MAX;i++){
		check_id=cells_[CHECK[i][0]];
		for(int j=1;j<LINE_LEN;j++){
			if(check_id!=cells_[CHECK[i][j]]||check_id==0){
				break;
			}
			if(j==(LINE_LEN-1)){
				return check_id;
			}
		}
	}
	return 0;
}

void GameBord::show(){
	for(int i=0;i<GAME_SIZE;i++){
		cout<<(int)cells_[i]<<" ";
		if((i+1)%3==0)
			cout<<endl;
	}
	cout<<endl;
}

bool GameBord::is_end()
{
	if(get_winner()!=(PID)0)
		return true;
	int count=0;
	for(int i=0;i<GAME_SIZE;i++)
	{
		if(cells_[i]==(PID)0)count++;
	}
	if(count==0)
		return true;
	else
		return false;
}
