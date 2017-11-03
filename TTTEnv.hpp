#ifndef __TTTENV__
#define __TTTENV__

#include "GameBord.hpp"
#include "RndNPC.hpp"
class TTTEnv
{
	public:
		TTTEnv()
		{
			PLAYER1 = 1;PLAYER2 = 2;
			bord = new GameBord();
			npc = new RndNPC(PLAYER2);
		}
		double play(int act_id)
		{
			if(bord->set_next(PLAYER1,act_id))
			{
				if(bord->get_winner()==PLAYER1)
					return 1;
				if(bord->is_end())
					return -1;

				int rand_act = npc->get_next(bord->get_state());
				bord->set_next(PLAYER2,rand_act);
				if(bord->get_winner()==PLAYER2)
					return -1;
				if(bord->is_end())
					return -1;
				return 0;
			}else
			{
				return -1;
			}
		}
		vec_t get_state()
		{
			return get_sig(bord->get_state());
		}

		bool is_end()
		{
			return bord->is_end();
		}
		void show()
		{
			bord->show();
		}

		PID get_winner()
		{
			return bord->get_winner();
		}
	private:
		GameBord* bord;
		RndNPC* npc;
		unsigned char PLAYER1,PLAYER2;
		vec_t get_sig(vector<PID> x)
		{
			int size = x.size();
			vec_t y(size);
			for(int i=0;i<size;i++)
			{
				if(x[i]==(PID)0)
					y[i]=0.0;
				else if(x[i]==PLAYER1)
					y[i]=1.0;
				else
					y[i]=-1.0;
			}
			return y;
		}
};
#endif
