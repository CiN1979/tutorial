#ifndef DISPLAY_H
#define DISPLAY_H

#include <map>

class Display
{
private:
	// stores all pixels displayed in framebuffer
	std::map<std::pair<int, int>, short int> ramp;

	unsigned short m_upper_left_col;
	unsigned short m_upper_right_col;
	unsigned short m_lower_left_col;
	unsigned short m_lower_right_col;

	/** \brief set first pixel in the specified height
	 *
	 * \param current y position
	 * \return new pixel color
	 *
	 */
	unsigned short set_first_y_pixel_color(unsigned int current_step);

	/** \brief set last pixel in the specified height
	 *
	 * \param current y position
	 * \return new pixel color
	 *
	 */
	unsigned short set_last_y_pixel_color(unsigned int current_step);

	/** \brief set pixel color in the specified width
	 *
	 * \param first pixel color value
	 * \param last pixel color value
	 * \param current x position
	 * \return new pixel color
	 *
	 */
	unsigned short set_x_pixel_color(unsigned short first_color, unsigned short last_color,
									unsigned int current_step);

	/** \brief set pixel color in the specified width
	 *
	 * \param first pixel color value
	 * \param last pixel color value
	 * \param current pixel position
	 * \param orientation
	 * \return new pixel color
	 *
	 */
	unsigned short set_pixel_color(unsigned short first_color, unsigned short last_color,
									unsigned int current_step, int orientation);

public:
	Display();
	virtual ~Display();

	/** \brief connect to video device
	 *
	 * \param display_name of the video device
	 * \return true when connected
	 *
	 */
	bool connect(const char *display_name);

	/** \brief get size of the framebuffer
	 *
	 * \param framebuffer width
	 * \param framebuffer height
	 *
	 */
	void get_size(int &width, int &height);

	/** \brief draw raster with specified width
	 *
	 * \param framebuffer width
	 * \param framebuffer height
	 *
	 */
	void draw_raster(int x, int y, int width);

	/// \brief generates color ramp based on edge pixels
	void generate_ramp();

	/// \brief dump pixel container to file
	void dump_ramp();

	/** \brief set edge colors
	 *
	 * \param upper left color value
	 * \param upper right color value
	 * \param lower left color value
	 * \param lower right color value
	 *
	 */
	void set_edge_colors(unsigned short upper_left_col, unsigned short upper_right_col,
					unsigned short lower_left_col, unsigned short lower_right_col);
};

#endif
