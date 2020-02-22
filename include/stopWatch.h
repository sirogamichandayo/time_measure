/*
Copyright © 2020 Cota Tomooka

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <memory>
#include <regex>
#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <list>
#include <numeric>
#include <fstream>
#include <map>
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

#ifndef LOG
#define LOG(msg) std::cout << "[LOG] (" __FILE__ ":" << __LINE__ << ") from " << __func__ << "()\n    " << msg << "\n";
#endif

namespace stopwatch
{
	unsigned const int PLOT = (1<<0);
	unsigned const int BAR  = (1<<1);
}

//---
class stopWatch
{
public:
	explicit stopWatch(const string& t_) 
		: _is_start(0), _title{t_} {};
	void start();
	void lap();
	inline void    set_title(const string& t_);
	inline void    get_title(string* output_t_);
	inline void    get_rap_list(vector<double>* vec_);
	inline int 	   get_rap_list_size();

private:
	chrono::system_clock::time_point _start;
	string _title;
	double _rap_time;
	vector<double> _rap_list;
	bool _is_start;
};
//---


//---
class stopWatchController
{
public:
	stopWatchController() : _is_save(false) 
	{
		_plot_style_list = move(vector<string>
					{".:b", ".:g", ".:r", ".:c", ".:m", ".:y", ".:k",
					".-b", ".-g", ".-r", ".-c", ".-m", ".-y", ".-k"});
	} 
	~stopWatchController();
	int new_timer(const string& t_);
	void start(const int timer_index);
	void lap(const int timer_index);

	void create_bar();
	void create_plot();

template <class Iterator>	
	void set_plot_style(Iterator begin, Iterator end);
	void set_file_name(const string& t_);
	void set_title_name(const string& t_);
	void set_format(const int& w_);
	void save_file();

private:
	vector<stopWatch> _timer_list;
	vector<string>    _plot_style_list;
	string _file_name;
	string _title;
	bool _is_save;
	int _format;
};
//---


void stopWatch::start()
{
	if (_is_start)
	{
		LOG("start()もしくはlap()が適切に呼び出されてない可能性があります。");
		exit(-1);
	}
	this->_start = chrono::system_clock::now();
	_is_start ^= true;
	return;
}

void stopWatch::lap()
{
	if (!_is_start)	
	{
		LOG("start()もしくはlap()が適切に呼び出されていない可能性があります。");
		exit(-1);
	}
	chrono::system_clock::time_point end = chrono::system_clock::now();
	this->_rap_time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - this->_start).count() / 1000.0);
	_rap_list.push_back(_rap_time);
	_is_start ^= true;
	return;
}
inline void stopWatch::set_title(const string& t_)
{
	_title = t_;
}
inline void stopWatch::get_title(string *const  output_t)
{                                
	*output_t = _title;
}
inline void stopWatch::get_rap_list(vector<double>* vec_)
{
	move(_rap_list.begin(), _rap_list.end(), back_inserter(*vec_));
}

inline int stopWatch::get_rap_list_size()
{
	return _rap_list.size();
}
//======================================================
//=================stopWatchController==================
//======================================================
stopWatchController::~stopWatchController()
{
	if (_plot_style_list.size() < _timer_list.size() )
	{
		LOG("_plot_style_listの数が足りません。set_plot_style()を用いてスタイルを追加する、もしくは、その引数を確認してください。");
		exit(-1);
	}

	switch (_format)
	{
		case stopwatch::BAR:  create_bar(); break;
		case stopwatch::PLOT: create_plot(); break;
		default: LOG("表示形式が指定されていません。"); exit(-1); 
	}

	if (_is_save) save_file();
	else		  plt::show();
}

void stopWatchController::save_file()
{
	LOG("save in " + static_cast<string>(_file_name) + ".png");
	plt::save(_file_name);
}

void stopWatchController::create_bar()
{
	std::vector<double> xlist(_timer_list.size());
	std::vector<double> ylist(_timer_list.size());
	std::vector<string> titles(_timer_list.size());
	int i = 0;
	for (auto& timer : _timer_list)
	{
		std::vector<double> rap_list;
		timer.get_rap_list(&rap_list);
		double average = std::accumulate(rap_list.begin(), rap_list.end(), 0.0) 
							/ rap_list.size();

		xlist[i] = i;
		ylist[i] = average;
		string s;
		timer.get_title(&s);
		titles[i] = move(s);
		++i;
	}

	plt::bar(xlist, ylist);
	plt::title(_title);
	plt::ylabel("Process time[ms]");
	plt::xticks(xlist, titles);
	for (size_t i = 0; i < xlist.size(); i++)
	{
		plt::text(xlist[i], ylist[i], ylist[i]);
	}
}
void stopWatchController::create_plot()
{
	for (int timer_i = 0; timer_i < _timer_list.size(); ++timer_i)
	{
		int rap_time_size = _timer_list[timer_i].get_rap_list_size();		
		std::vector<double> x, y;
		x.reserve(rap_time_size);
		y.reserve(rap_time_size);

		for (int i = 0; i < rap_time_size; ++i) x.push_back(i);
		_timer_list[timer_i].get_rap_list(&y);
		std::string s;
		_timer_list[timer_i].get_title(&s);
		plt::named_plot(s ,x, y, _plot_style_list[timer_i]);
		plt::legend();
	}
	plt::title(_title);
	plt::ylabel("Process time[ms]");
}

int stopWatchController::new_timer(const string& t_)
{
	_timer_list.push_back(stopWatch(t_));
	return _timer_list.size() - 1;
}

void stopWatchController::start(const int timer_index)
{
	_timer_list[timer_index].start();
}

void stopWatchController::lap(const int timer_index)
{
	_timer_list[timer_index].lap();
}

template <class Iterator>
void stopWatchController::set_plot_style(Iterator begin, Iterator end)
{
	regex pat{R"(^([.,ov^<>12345sp*hH+xDd|_]?((--)|(-\.)|-|:)?[bgrcmykw]?)$)"};
	smatch matches;
	auto b = begin, e = end;
	for (;b != e; ++b)
	{
		// not match	
		if(!regex_search(*b, matches, pat))
		{
// !!!!!!!!!!!ONLY GOTO!!!!!!!!!!!!!!!!!			
			LOG("対応していないスタイルが渡されている可能性があります。<\"" + static_cast<string>(*b) + "\">");
		}
	}
	_plot_style_list.resize(distance(begin, end));
	move(begin, end, _plot_style_list.begin());
}

void stopWatchController::set_file_name(const string& t_)
{
	_file_name = move(t_);
	_is_save = true;
}

void stopWatchController::set_title_name(const string& t_)
{
	_title = move(t_);
}

void stopWatchController::set_format(const int& w_)
{
	_format = w_;
}
#endif	// TIME
