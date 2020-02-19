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

class stopWatch
{
public:
	stopWatch() : is_start(0), is_end(true) {};
	void start();
	void lap();
	inline void    set_title(const string& t_);
	inline string  get_title();
	inline void get_rap_list(vector<double>* vec_);

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
	int new_timer(const string& t_);
	void start(const int timer_index);
	void lap(const int timer_index);
	void show_graph();
	void set_file_name(const string& t_);
	void set_title_name(const string& t_);
	void save_file();

private:
	vector<shared_ptr<stopWatch>> timer_list;
	string _file_name;
	string _title;
	bool _is_save;
};


#endif	// TIME
