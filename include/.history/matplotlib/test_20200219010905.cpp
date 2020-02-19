#include "matplotlibcpp.h"

#include <vector>
#include <string>

namespace plt = matplotlibcpp;

int main()
{
	int n = 5;
	std::vector<int> xlist(n), ylist(n);
	std::vector<std::string> titles(n);

	std::string test = "test";
	for (int i = 0; i < n; i++)
	{
		xlist[i] = i;
		ylist[i] = i * 2;
		titles[i] = test;
	}

	plt::bar(xlist, ylist);
	// plt::plot(xlist, ylist, "--r");
	plt::title("Process time[ms]");
	plt::xticks(xlist, titles);
	for (int i = 0; i < n; i++)
	{
		plt::text(xlist[i], ylist[i], ylist[i]);
	}
	plt::show("./test.png");
}

