#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Display.h"

using namespace std;

int main(int argc, char **argv)
{
	vector<string> params;
	Display d;

	for (int i = 1; i < argc; i++)
	{
		if ((string(argv[i]).find('x') == string::npos) && (string(argv[i]).find('X') == string::npos))
		{
			cout << "ERROR! Please provide hexadecimal values i.e. 0xFFFF" << endl;
			return 0;
		}

		params.push_back(argv[i]);
	}

	if ((params.size() < 2) | (params.size() > 4) | (params.size() == 3))
	{
		cout << "ERROR! Wrong parameters quantity, please provide 2 or 4 parameters." << endl;
		return 0;
	}

	// set edge pixel values
	if (params.size() == 2)
	{
		// lower left pixel color is has the same value that upper left pixel value
		// lower right pixel color is has the same value that upper right pixel value
		// conversion from text hex to int can be easily achieved by BOOST lexical_cast, this time another solution
		d.set_edge_colors((int)strtol(params.at(0).c_str(), NULL, 0), (int)strtol(params.at(1).c_str(), NULL, 0), (int)strtol(params.at(0).c_str(), NULL, 0), (int)strtol(params.at(1).c_str(), NULL, 0));
	}
	else
	{
		d.set_edge_colors((int)strtol(params.at(0).c_str(), NULL, 0), (int)strtol(params.at(1).c_str(), NULL, 0), (int)strtol(params.at(2).c_str(), NULL, 0), (int)strtol(params.at(3).c_str(), NULL, 0));
	}

	// generate ramp based on specified edge pixel values
	d.generate_ramp();

/*
	// write a line of pixels to framebuffer
	try
	{
		d.draw_raster(200, 0, 114);
	}
	catch (string &e)
	{
		cout << e << endl;
	}
*/

	// dump ramp to file
	d.dump_ramp();

    return 0;
}
