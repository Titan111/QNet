bandit: bandit_test.cpp
	g++ -pthread bandit_test.cpp -I./ -std=c++14 -o bandit
vs_random: qnet_vs_random.cpp GameBord.cpp random.cpp QNet.hpp
	g++ -o0 -I./ -pthread --std=c++14 qnet_vs_random.cpp GameBord.cpp random.cpp -o vs_random
bord_test: bord_test.cpp GameBord*
	g++ -o bord_test bord_test.cpp GameBord.cpp
ttt: ttt_test.cpp GameBord.cpp RndNPC.hpp TTTEnv.hpp
	g++ -pthread ttt_test.cpp GameBord.cpp -I./ -std=c++14 -o ttt
sin: sin.cpp
	g++ -pthread sin.cpp -I./ -std=c++14 -o sin
