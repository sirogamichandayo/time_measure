#include "../matplotlib/matplotlibcpp.h"
namespace plt = matplotlibcpp;

#include "stopWatch.h"

#define LOG(msg) std::cout << "[LOG] (" __FILE__ ":" << __LINE__ << ") from " << __func__ << "()\n    " << msg << "\n";

void stopWatch::start()
{
	if (is_end && !is_start)
	{
		this->_start = chrono::system_clock::now();
		is_end = false;
		is_start = true;
		return;
	}
	LOG("stopWatch error.");
	exit(0);
}

void stopWatch::lap()
{
	if (!is_end && is_start)	
	{
		chrono::system_clock::time_point end = chrono::system_clock::now();
		this->_rap_time = static_cast<double>(chrono::duration_cast<chrono::microseconds>(end - this->_start).count() / 1000.0);
		_rap_list.push_back(_rap_time);
		is_end = true;
		is_start = false;
		return;
	}
	LOG("stopwatch error.")
	exit(0);
}

inline void stopWatch::set_title(const string& t_)
{
	_title = t_;
}

inline string stopWatch::get_title()
{
	return _title;
}

inline void stopWatch::get_rap_list(vector<double>* vec_)
{
	move(_rap_list.begin(), _rap_list.end(), back_inserter(*vec_));
}


//======================================================
stopWatchController::stopWatchController() : is_save(0) {}

stopWatchController::~stopWatchController()
{
	show_graph();
	if (is_save) save_file();
}

void stopWatchController::save_file()
{
	plt::save(file_name);
}

void stopWatchController::show_graph() 
{
	std::vector<double> xlist(timer_list.size());
	std::vector<double> ylist(timer_list.size());
	std::vector<string> titles(timer_list.size());
	int i = 0;
	for (const auto& timer : timer_list)
	{
		std::vector<double> rap_list;
		timer->get_rap_list(&rap_list);
		double average = std::accumulate(rap_list.begin(), rap_list.end(), 0.0) / rap_list.size();
		/////////

		xlist[i] = i;
		ylist[i] = average;
		titles[i] = timer->get_title();
		i++;
	}

	plt::bar(xlist, ylist);
	plt::title("Process time[ms]");
	plt::ylabel("Process time[ms]");
	plt::xticks(xlist, titles);
	for (size_t i = 0; i < xlist.size(); i++)
	{
		plt::text(xlist[i], ylist[i], ylist[i]);
	}
	if (!is_save)
		plt::show();	
}

int stopWatchController::new_timer(const string& t_)
{
	shared_ptr<stopWatch> timer = make_shared<stopWatch>();
	timer->set_title(t_);
	timer_list.push_back(timer);
	return timer_list.size() - 1;
}

void stopWatchController::start(const int timer_index)
{
	timer_list[timer_index]->start();
}

void stopWatchController::lap(const int timer_index)
{
	timer_list[timer_index]->lap();
}

void stopWatchController::set_file_name(const string& t_)
{
	file_name = t_;
	is_save = true;
}
