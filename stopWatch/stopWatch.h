#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <fstream>
#include <map>

using namespace std;

const string DIRNAME = "timedata/";

class stopWatch
{
public:
	stopWatch();
	void start();
	void lap();
	void show();
	void wait(const int time);
	inline void   set_title(string t_);
	inline string get_title();
	inline vector<double> get_rap_list();

private:
	chrono::system_clock::time_point _start;
	string _title;
	double _rap_time;
	vector<double> _rap_list;
	bool is_start;
	bool is_end;
};

class stopWatchController
{
public:
	stopWatchController();
	~stopWatchController();
	int new_timer(string title_);
	void start(const int timer_index);
	void lap(const int timer_index);
	void show(const int timer_index);
	void wait(const int timer_index, const int time);
	inline static void wait(const int time) {usleep(time);};
	void show_all();
	void show_graph();
	void set_file_name(string& t_);
	void save_file();

private:
	vector<shared_ptr<stopWatch>> timer_list;
	// std::map<string, vector<double>> _rap_list_all;
	string file_name;
	bool is_save;
};


#endif	// TIME
