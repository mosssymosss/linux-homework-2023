#include <iostream>
#include <string>
#include <climits>


int main(int argc, char** argv )
{
	int maximum = INT_MIN, minimum = INT_MAX;
	for(int i = 1; i < argc; ++i)
	{
		int tmp = std::stoi(argv[i]);
		if(tmp > maximum)
		{
			maximum = tmp;
		}
		if(tmp < minimum)
		{
			minimum = tmp;
		}
	}
	std::cout<<"minimum is " << minimum <<" maximum is " << maximum<<std::endl;
	return 0;
}
