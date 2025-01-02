#include "cubed.h"


static void put_pixel_to_image(t_conn *conn, int x, int y, int color)
{
    char *dst;

    dst = conn->image.addr + (y * conn->image.line_length + x * (conn->image.bpp / 8));
    *(unsigned int *)dst = color;
}


/*
************************** 2D MAP LAYER ********************
************************************************************
*/

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


/*
**********************************************************
******************PLAYER LAYER****************************
**********************************************************/
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



/*
*******************************************************
**************DIRECTION LINE LAYER*********************
*******************************************************
*/
/*
** temporal  function to debug if rotation working correctly
*/

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
        put_pixel_to_image(conn, start_x, start_y, 0x00FF00);
        if (start_x < end_x)
            start_x++;
        else if (start_x > end_x)
            start_x--;
        if(start_y < end_y)
            start_y++;
        else if (start_y > end_y)
            start_y--;
    }
}

/*
******************************************************************
************************DRAW RAYS*********************************
******************************************************************
*/


static void get_ray_coordinates(t_ray ray, t_player *player, int *line)
{

    line[0] = player->play_pos[1] * TILE_SIZE;
    line[1] = player->play_pos[0] * TILE_SIZE;
    line[2] = line[0] + (cos(ray.angle) * ray.distance * TILE_SIZE);
    line[3] = line[1] + (sin(ray.angle) * ray.distance * TILE_SIZE);

}

static void draw_ray(int *line, t_conn *conn)
{
    double adjacent;
    double opposite;
    int hypotenuse;
    double curr_x;
    double curr_y;

    adjacent = line[2] - line[0];
    opposite = line[3] - line[1];
    hypotenuse = sqrt(pow(adjacent, 2) + pow(opposite, 2));
    adjacent = adjacent / hypotenuse;
    opposite = opposite / hypotenuse;
    curr_x = line[0];
    curr_y = line[1];
    while (hypotenuse)
    {
        put_pixel_to_image(conn, curr_x, curr_y, 0xFF0000);
		curr_x += adjacent;
		curr_y += opposite;
		hypotenuse--;
    }

}


/* for each ray:
    1 - get starting position of ray(x,y) at the pixel level
    2 - get ending position of ray(x, y)
    3 - calculate adjacent, opposite, hypotenuse
    4 - calculate increment in x and y position of line per pixel
    5 - store data on img, pixel by pixel, up to hypotenuse pixel
    */
void draw_all_rays(t_game *game)
{
    
    int line[4]; //x_0, y_0, x_1, y_1
    int i;

    i = 0;
    while (i < game->vars->screen_width)
    {
        get_ray_coordinates(game->rays[i], game->player, line);
        draw_ray(line, game->conn);
        i++;
    }
}


/*
******************************************************************
*********************DRAW 3D  WALLS******************************
******************************************************************
*/
/*double wall_3d_size(t_game *game, t_ray ray)
{
    double size;
    double fisheye;
    double adjusted_distance;

    fisheye = cos(ray.angle - game->player->rotation_angle);
    adjusted_distance = ray.distance * fisheye * TILE_SIZE;
    size = (TILE_SIZE / adjusted_distance) *game->player->dist_to_plane;
    return size;

}*/

static int color_to_hex(t_color *color, char flag)
{
    t_color *current;
    int hex_color;

    current = color;
    while(current && current->cf != flag)
        current = current->next;
        //understanding the bitwise or operation!!

    return hex_color;
}

void draw_floor(t_game *game)
{

}

void draw_ceiling(t_game *game)
{
    int x;
    int y;
    int color;

    x = 0;
    //function to get color from rgb linked list to hex
    color = color_to_hex(game->color_root, 'C');
    while (x < game->vars->screen_width)
    {
        y = 0;
        while (y < game->vars->screen_height / 2)
        {

            put_pixel_to_image();
            y++;
        }
        x++;
    }

}

/*
**  if conditions protect code from writing pixels outside
**  the window boundary
*/
static void draw_3d_wall(int x, int y, double wall_size, t_game *game )
{
    double end_y;
    int curr_x;
    int tmp_y;

    end_y = y + wall_size;
    if (y < 0)
        y = 0;
    if (end_y > game->vars->screen_height)
        end_y = game->vars->screen_height - 1;
    curr_x = x;
    while (curr_x < x + RAY_WIDTH && curr_x < game->vars->screen_width)
    {
        tmp_y = y;
        while (tmp_y < end_y)
        {
            put_pixel_to_image(game->conn, curr_x, y, 0xFFFFFF);
            tmp_y++;
        }
        curr_x++;
    }
}

/*
**  up until now ray.distance was measured in 2d_map tiles, 
**  here we convert it to pixels by multiplying by TILE_SIZE
**   and adjust it to avoid the fisheye distortion
**
**  Triangle similarity theorem applied to get the projected wall size 
**  in pixels
*/
void draw_ray_cast(t_game *game, int i)
{
    double wall_size;
    double fisheye;
    double adjusted_distance;
    int x;
    int y;

    while (i < (game->vars->num_rays))
    {
        fisheye = cos(game->rays[i].angle - game->player->rotation_angle);
        adjusted_distance = game->rays[i].distance * fisheye * TILE_SIZE;
        wall_size = (TILE_SIZE / adjusted_distance) *game->player->dist_to_plane;
        x = i * RAY_WIDTH;
        y = (game->vars->screen_height - wall_size) / 2; //what happens if wall_size == screen_height or wall_size > screen_height?
        //texture for this ray / wall?
        draw_3d_wall(x, y, wall_size, game);
        i++;
    }
}