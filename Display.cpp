#include <cstdio>
#include <cassert>
#include <memory.h>
#include <iostream>
#include <fstream>

#include "Display.h"

using namespace std;

// ORIGINAL SIZE
#define W 16
#define H  9

//#define W 300
//#define H 300

static unsigned short frame_buffer[W*H];

Display::Display()
{
	// nice colors 0x2be1 0x1077 0xD375 0xFFFF
	set_edge_colors(0, 0, 0, 0);
}

Display::~Display()
{
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			if (x > 0)
			{
				cout << " ";
			}
			cout << hex << "0x" << ramp[{x, y}];
		}

		cout << endl;
	}

	// clear pixel container
	ramp.clear();
}

bool Display::connect(const char *display_name)
{
	return true;
}

void Display::get_size(int &width, int &height)
{
	width = W;
	height = H;
}

/* old version
void Display::draw_raster(int x, int y,
	const unsigned short *pixels, int width)
{
	memcpy(&frame_buffer[y*W + x], pixels, width*sizeof(unsigned short));
}
*/

void Display::draw_raster(int x, int y, int width)
{
	if (x+width > W)
	{
		throw string("ERROR! draw_raster(): width too long");
	}

	for (int i = 0; i < width; i++)
	{
		// better to use find instead of [], reinterpret is quite dangerous
		frame_buffer[y*W + i] = ramp[{x+i, y}];
	}
}

void Display::dump_ramp()
{
	ofstream myfile;
	myfile.open("ramp.raw", ios::out | ios::binary);

	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			// better to use find instead of [], reinterpret is quite dangerous
			unsigned short color_val = ramp[{x, y}];
			myfile.write(reinterpret_cast<char*>(&color_val), sizeof(short int));
		}
	}

	myfile.close();
}

void Display::set_edge_colors(unsigned short upper_left_col, unsigned short upper_right_col,
					unsigned short lower_left_col, unsigned short lower_right_col)
{
	m_upper_left_col = upper_left_col;
	m_upper_right_col = upper_right_col;
	m_lower_left_col = lower_left_col;
	m_lower_right_col = lower_right_col;
}
void Display::generate_ramp()
{
	for (int y = 0; y < H; y++)
	{
		ramp[{0, y}] = set_first_y_pixel_color(y);
		ramp[{W-1, y}] = set_last_y_pixel_color(y);

		for (int x = 1; x < W-1; x++)
		{
			ramp[{x, y}] = set_x_pixel_color(ramp[{0, y}], ramp[{W-1, y}], x);
		}
	}
}

unsigned short Display::set_first_y_pixel_color(unsigned int current_step)
{
	return set_pixel_color(m_upper_left_col, m_lower_left_col, current_step, H);
}

unsigned short Display::set_last_y_pixel_color(unsigned int current_step)
{
	return set_pixel_color(m_lower_right_col, m_lower_right_col, current_step, H);
}

unsigned short Display::set_x_pixel_color(unsigned short left_col, unsigned short right_col,
								unsigned int current_step)
{
	return set_pixel_color(left_col, right_col, current_step, W);
}

unsigned short Display::set_pixel_color(unsigned short first_color, unsigned short last_color,
								unsigned int current_step, int orientation)
{
	float n;
	unsigned char r, g, b;
	unsigned short ret = 0;

	n = (float)current_step / (float)(orientation-1);

	r = (float)((first_color & 0xF800)	>> 11)	* (1.0f-n) + (float)((last_color & 0xF800) >> 11) * n;
	g = (float)((first_color & 0x7E0)	>> 5)	* (1.0f-n) + (float)((last_color & 0x7E0) >> 5) * n;
	b = (float)(first_color & 0x1F) 			* (1.0f-n) + (float)(last_color & 0x1F) * n;

	ret = (r << 11) | (g << 5) | b;

	return ret;
}
