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

	unsigned const int P1 = timer_con.new_timer("process1");
	unsigned const int P2 = timer_con.new_timer("process2");
	unsigned const int P3 = timer_con.new_timer("process3");
	unsigned const int P4 = timer_con.new_timer("process4");

	int times = 30;

	for (int i = 0; i < times+1; ++i)	
	{
		timer_con.start(P1);
		if (i == 0) usleep(times * 1000);
		timer_con.lap(P1);

		timer_con.start(P2);
		int t;
		if (i == times) t = 0;
		else		 t = times*1000;
		usleep(t);
		timer_con.lap(P2);

		timer_con.start(P3);
		usleep(i * 1000);
		timer_con.lap(P3);

		timer_con.start(P4);
		usleep((times - i) * 1000);
		timer_con.lap(P4);

	}
}
