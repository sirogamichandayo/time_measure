#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include "../include/stopWatch.h"

#ifndef LOG
#define LOG(msg) std::cout << "[LOG] (" __FILE__ ":" << __LINE__ << ") from " << __func__ << "()\n    " << msg << "\n";
#endif

int main(int argc, char** argv)
{
	// make timer.
	stopWatchController timer_con;
	timer_con.set_title_name("compare");

	if (argc < 2)
	{
		LOG("コマンドライン引数の数が少ないです。");
		exit(-1);
	} 
	if (static_cast<string>(argv[1]) == static_cast<string>("each"))	
		timer_con.set_what_plot(stopwatch::PLOT);
	else if (static_cast<string>(argv[1]) == static_cast<string>("ave"))
		timer_con.set_what_plot(stopwatch::BAR);
	if (argc == 3)
		timer_con.set_file_name(argv[2]);
	if (argc >= 4)
	{
		LOG("コマンドライン引数の数が多すぎます。");
		exit(-1);
	}

	std::string title1 = "for_each";
	std::string title2 = "range_for";
	std::string title3 = "counter";
	std::string title4 = "at";
	
	unsigned const int FOR_EACH  = timer_con.new_timer(title1);
	unsigned const int RANGE_FOR = timer_con.new_timer(title2);
	unsigned const int COUNTER   = timer_con.new_timer(title3);
	unsigned const int AT		 = timer_con.new_timer(title4);


	std::vector<std::vector<int>> vecvec(1000, std::vector<int>(1000, 0));
	unsigned const int times = 50;

	for (int k = 0; k < times; ++k)
	{
		timer_con.start(FOR_EACH);
		for_each(vecvec.begin(), vecvec.end(), [](vector<int>& vec)
		{
			for_each(vec.begin(), vec.end(), [](int& elem)
			{
				++elem;	
			});
		});
		timer_con.lap(FOR_EACH);
	}

	for (int k = 0; k < times; ++k)
	{
		timer_con.start(RANGE_FOR);
		for (vector<int>& vec : vecvec)
		{
			for (int& elem : vec)
			{
				++elem;	
			}
		}
		timer_con.lap(RANGE_FOR);
	}

	for (int k = 0; k < times; ++k)
	{
		timer_con.start(COUNTER);
		int n = vecvec.size();
		for (int i = 0; i < n; ++i) 
			{
			for (int j = 0; j < vecvec[i].size(); ++j) 
			{
				++vecvec[i][j];
			}		
		}
		timer_con.lap(COUNTER);
	}

	for (int k = 0; k < times; ++k)
	{
		timer_con.start(AT);
		int n = vecvec.size();
		for (int i = 0; i < n; ++i) 
			{
			for (int j = 0; j < vecvec[i].size(); ++j) 
			{
				++vecvec.at(i).at(j);
			}		
		}
		timer_con.lap(AT);
	}

}
