#include "stopWatch.h"
#define LOG(msg) std::cout << "[LOG] (" __FILE__ ":" << __LINE__ << ") from " << __func__ << "()\n    " << msg << "\n"
int main()
{
	shared_ptr<stopWatchController> timer_con;
	timer_con = make_shared<stopWatchController>();
	string title1 = "range_for";
	string title2 = "iterator";
	string title3 = "pointer";
	string title4 = "index";
	string filename = "text.csv";
	timer_con->set_file_name(filename);
	const int RANGE_FOR = timer_con->new_timer(title1);
	const int ITERATOR  = timer_con->new_timer(title2);
	const int POINTER   = timer_con->new_timer(title3);
	const int INDEX     = timer_con->new_timer(title4);

	// initialize vector.
	vector<int> range;
	for (int i = 0; i < 1000; i++)
		range.push_back(i);

	int a = 0;
	for (int k = 0; k < 10; k++)
	{
		timer_con->start(RANGE_FOR);
		for (const auto& elem : range)
			a = (a + elem) % 17;
		timer_con->lap(RANGE_FOR);
	}

	a = 0;
	for (int k = 0; k < 10; k++)
	{
		timer_con->start(ITERATOR);
		for (vector<int>::const_iterator it = range.begin(), e = range.end(); it != e; it++)
			a = (a + *it) % 17;
		timer_con->lap(ITERATOR);
	}

	a = 0;
	for (int k = 0; k < 10; k++)
	{
		timer_con->start(POINTER);
		int *p = &range[0];
		for (size_t i = 0; i < range.size(); i++)
			a = (a + *(p+i)) % 17;
		timer_con->lap(POINTER);
	}

	a = 0;
	for (int k = 0; k < 10; k++)
	{
		timer_con->start(INDEX);
		for (size_t i = 0; i < range.size(); i++)
			a = (a + range[i]) % 17;
		timer_con->lap(INDEX);
		timer_con->wait(INDEX, 100000);
	}

}
