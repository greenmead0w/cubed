#include "cubed.h"


static void put_pixel_to_image(t_conn *conn, int x, int y, int color) {
    char *dst;

    dst = conn->image.addr + (y * conn->image.line_length + x * (conn->image.bpp / 8));
    *(unsigned int *)dst = color;
}



static void draw_row(int tmp_l, int col, char value, t_game *game, int line)
{
    int tmp_c;
    int size;

    tmp_c = col;
    size = TILE_SIZE;

    while (size > 0)
    {
		if (tmp_c == col || tmp_c == col + TILE_SIZE - 1 || tmp_l == line
			|| tmp_l == line + TILE_SIZE - 1) //border
			put_pixel_to_image(game->conn, tmp_c, tmp_l, 0xFFA500);
		else if (value == '1' || value == ' ')
        	put_pixel_to_image(game->conn, tmp_c, tmp_l, 0x000000);
    	else
        	put_pixel_to_image(game->conn, tmp_c, tmp_l, 0xFFFFFF);
        tmp_c++;
        size--;
    }
}

static void draw_tile(char value, t_game *game, int i, int j)
{
	int line;
    int col;
    int tmp_l;
    int size;

    line = i * TILE_SIZE;
    col = j * TILE_SIZE;
    tmp_l = line;
    size = TILE_SIZE;

    while (size > 0)
    {
        draw_row(tmp_l, col, value, game, line);
        tmp_l++;
        size--;
    }
}


void	draw_2d_map(t_game *game)
{
	
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
			draw_tile(map[i][j], game, i, j);
			j++;
		}
		i++;
	}
}


void fill_player_rect(t_conn *conn, int center_x, int center_y, int size, int color)
{
    int x_start;
	int x_end;
	int y_start;
	int y_end;
	int current_x;

    x_start = center_x - (size / 2);
    x_end = center_x + (size / 2);
	y_start = center_y - (size / 2);
	y_end = center_y + (size / 2);

	while (y_start <= y_end)
    {
		current_x = x_start;
		while(current_x <= x_end)
		{
			put_pixel_to_image(conn, current_x, y_start, color);
			current_x++;
		}
        y_start++;
    }
}


void draw_player(t_conn *conn, t_player *player)
{
    int center_x;
    int center_y;
    double size;

    center_x = player->play_pos[1] * TILE_SIZE;
    center_y = player->play_pos[0] * TILE_SIZE;
    size = TILE_SIZE / 3;

    fill_player_rect(conn, center_x, center_y, size, 0xFF0000);
}




void draw_direction_line(t_conn *conn, t_player *player)
{
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int line_length;

    line_length = TILE_SIZE / 2;  // Length of direction indicator
    start_x = player->play_pos[1] * TILE_SIZE;
    start_y = player->play_pos[0] * TILE_SIZE;
    end_x = start_x + (cos(player->rotation_angle) * line_length);
    end_y = start_y + (sin(player->rotation_angle) * line_length);

    // Drawing line pixel by pixel
    while (start_x != end_x || start_y != end_y)
    {
        put_pixel_to_image(conn, start_x, start_y, 0x00FF00);  // Green color for direction
        start_x += (start_x < end_x) ? 1 : (start_x > end_x ? -1 : 0);
        start_y += (start_y < end_y) ? 1 : (start_y > end_y ? -1 : 0);
    }
}