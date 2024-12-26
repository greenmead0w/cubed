#include "cubed.h"


//load pixel in image buffer
// static void put_pixel_to_image(t_image *img, int x, int y, int color)
// {
// 	char *dst;
// 	//formula for preventing misalignments between screen width and line width in memory
// 	dst = img.addr + (y * img.line_length + x * (img.bpp / 8));
// 	*(int*)dst = color;
// }

void put_pixel_to_image(t_conn *conn, int x, int y, int color) {
    char *dst;

    dst = conn->image.addr + (y * conn->image.line_length + x * (conn->image.bpp / 8));
    *(unsigned int *)dst = color;
}


/*static void	get_color(char value, t_game *p, int i, int j)
{
	int	x;
	int	y;

	x = j * 64;
	y = i * 64;
	if (value == '1')
	{
		//draw to buffer: entire tile color black
	}
	if (value == '0')
		//draw to buffer: entire tile color white;

	if (ft_strchr(SET_2, value))
		//draw to buffer: cube root of tile size (4 pixels) of red circle

}*/

static void get_color(char value, t_game *g, int i, int j) {
    int x = j * 64;
    int y = i * 64;
    int size = 64;


    for (int py = y; py < y + size; py++) {
        for (int px = x; px < x + size; px++) {
            // Draw orange borders
            if (py == y || py == y + size - 1 || px == x || px == x + size - 1) {
                put_pixel_to_image(g->conn, px, py, 0xFFA500);  // Orange
            }
            // Fill the rest of the tile
            else if (value == '1') {
                put_pixel_to_image(g->conn, px, py, 0x000000);  // Black
            } else if (value == '0') {
                put_pixel_to_image(g->conn, px, py, 0xFFFFFF);  // White
            } else if (ft_strchr(SET_2, value)) {
                put_pixel_to_image(g->conn, px, py, 0xFF00FF);  // Red
            }
        }
    }
}


void	load_background(t_game *game)
{
	//TODO: ADD MOVE_PLAYER LOGIC!! map is always the same otherwise!!
	int		i;
	int		j;
	char	**map;

	map = game->vars->game_map;
	i = 0;
	while (i < game->vars->map_rows)
	{
		j = 0;
		while (j < game->vars->map_cols)
		{
			get_color(map[i][j], game, i, j);
			j++;
		}
		i++;
	}
}