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

static int is_border_map(int curr_x, int curr_y, int start_x, int start_y, int size)
{
    int is_vert_border;
    int is_horz_border;

    is_vert_border = (curr_x == start_x || curr_x == start_x + size -1);
    is_horz_border = (curr_y == start_y || curr_y == start_y + size -1 );

    return is_vert_border || is_horz_border;
}

static void draw_row(int y, int start_x, char value, t_game *game, int start_y)
{
    int curr_x;
    int remaining;

    curr_x = start_x;
    //remaining = TILE_SIZE;
    remaining = MINI_TILE;

    while (remaining > 0)
    {
        if (is_border_map(curr_x, y, start_x, start_y, /*TILE_SIZE*/MINI_TILE))
			put_pixel_to_image(game->conn, curr_x, y, 0xFFA500);
		else if (value == '1' || value == ' ')
        	put_pixel_to_image(game->conn, curr_x, y, 0x000000);
    	else
        	put_pixel_to_image(game->conn, curr_x, y, 0xFFFFFF);
        curr_x++;
        remaining--;
    }
}

static void draw_tile(char value, t_game *game, int row, int col)
{
    int curr_y;
    int remaining;
    int start_x;
    int start_y;

    /*start_y = row * TILE_SIZE;
    start_x = col * TILE_SIZE;
    curr_y = start_y;
    remaining = TILE_SIZE;*/
    start_y = row * MINI_TILE;
    start_x = col * MINI_TILE;
    curr_y = start_y;
    remaining = MINI_TILE;

    while (remaining > 0)
    {
        draw_row(curr_y, start_x, value, game, start_y);
        curr_y++;
        remaining--;
    }
}


void	draw_2d_map(t_game *game)
{
	
	int		row;
	int		col;
	char	**map;
    //int map_size;

    // map_size = MINI_TILE * game->vars->map_rows;
    // if (map_size > game->vars->screen_height)
    //     return;
    map = game->vars->game_map;
	row = 0;
	while (row < game->vars->map_rows)
	{
		col = 0;
		while (col < game->vars->map_cols)
		{
			draw_tile(map[row][col], game, row, col);
			col++;
		}
		row++;
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

/*
**  Player is half the size of a mini map tile
*/
void draw_player(t_conn *conn, t_player *player)
{
    int center_x;
    int center_y;
    double size;

    //center_x = player->play_pos[1] * TILE_SIZE;
    //center_y = player->play_pos[0] * TILE_SIZE;
    //size = TILE_SIZE / 4;
    center_x = player->play_pos[1] * MINI_TILE;
    center_y = player->play_pos[0] * MINI_TILE;
    size = MINI_TILE / 2;
    //player->display_size = (double)size;

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

/*void draw_direction_line(t_conn *conn, t_player *player)
{
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int line_length;

    // line_length = TILE_SIZE / 2;  // Length of direction indicator
    // start_x = player->play_pos[1] * TILE_SIZE;
    // start_y = player->play_pos[0] * TILE_SIZE;

    line_length = MINI_TILE / 2;
    start_x = player->play_pos[1] * MINI_TILE;
    start_y = player->play_pos[0] * MINI_TILE;

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
}*/

/*
******************************************************************
************************DRAW RAYS*********************************
******************************************************************
*/


static void get_ray_coordinates(t_ray ray, t_player *player, int *line)
{

    // line[0] = player->play_pos[1] * TILE_SIZE;
    // line[1] = player->play_pos[0] * TILE_SIZE;
    // line[2] = line[0] + (cos(ray.angle) * ray.distance * TILE_SIZE);
    // line[3] = line[1] + (sin(ray.angle) * ray.distance * TILE_SIZE);

    line[0] = player->play_pos[1] * MINI_TILE;
    line[1] = player->play_pos[0] * MINI_TILE;
    line[2] = line[0] + (cos(ray.angle) * ray.distance * MINI_TILE);
    line[3] = line[1] + (sin(ray.angle) * ray.distance * MINI_TILE);

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

/*
**  Understanding bitwise operations:
**  Translating to hex or decimal, it doesn't matter. But hex is more intuitive because
**  hex is base 16, enabling each byte to be represented by 2 digits.
**
**  We start with three independent color ints, each one with 32 bits / 4 bytes. But each
**  component only uses the least significant 8 bits (we could have used the char data
**  type to hold the numbers?). First step is to switch those 8 bits to their appropriate
**  position in our 0xRRGGBB number representation. Our pixel color will consist of 3 bytes,
**  so it will be 0x00RRGGBB. Our red number needs to occupy the second byte in our
**  new hex number, so it will have to switch its least significant byte with it's second 
**  most significant byte "<< 16", green <<8 and blue as it is. 

** Now that we have transformed our independent color all we need to do is combine
**  their values via bitwise OR operator, discarding the NULL bytes and effectively creating
**  a new int of type 0x00RRGGBB
*/
static int combine_rgb(t_color *color, char flag)
{
    t_color *current;
    int res_color;

    current = color;
    res_color = 0;
    while(current && current->cf != flag)
        current = current->next;
    if (current)
        res_color = current->r_color << 16 | current->g_color <<8 
            | current->b_color;
    return res_color;
}

void draw_floor(t_game *game)
{
    int x;
    int y;
    int color;

    x = 0;
    color = combine_rgb(game->color_root, 'F');
    while (x < game->vars->screen_width)
    {
        y = game->vars->screen_height / 2;
        while (y < game->vars->screen_height)
        {
            put_pixel_to_image(game->conn, x, y, color);
            y++;
        }
        x++;
    }
}

void draw_ceiling(t_game *game)
{
    int x;
    int y;
    int color;

    x = 0;
    color = combine_rgb(game->color_root, 'C');
    while (x < game->vars->screen_width)
    {
        y = 0;
        while (y < game->vars->screen_height / 2)
        {
            put_pixel_to_image(game->conn, x, y, color);
            y++;
        }
        x++;
    }
}

/*static void everything_texture()
{
    //TODO
    0 - get texture value for this ray (is it 'N', 'S', 'W' or 'E')
    1 - Find wall_hit_position (as a fraction, as a pixel)
    2 - Find that fractions equivalence in the texture image
            it could be a rule of three (if 0.4 in wall, what col is at 0.4 width in texture)
    3 - step and stuff
    this_ray_texture();


}*/

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
            put_pixel_to_image(game->conn, curr_x, tmp_y, 0x00fdf0d5);
            tmp_y++;
        }
        curr_x++;
    }
}

static double solve_fisheye(t_ray ray, t_player *player)
{
    double fisheye;
    double adjusted_distance;
    double wall_size;

    fisheye = cos(ray.angle - player->rotation_angle);
    adjusted_distance = ray.distance * fisheye * TILE_SIZE;
    wall_size = (TILE_SIZE / adjusted_distance) *player->dist_to_plane;
    return wall_size;
}

static t_texture *get_ray_texture(t_game *game, t_ray ray)
{
    t_texture *texture;

    if (ray.hit_side == 'N')
            texture = game->vars->textures[NORTH];
        else if (ray.hit_side == 'S')
            texture = game->vars->textures[SOUTH];
        else if (ray.hit_side == 'E')
            texture = game->vars->textures[EAST];
        else if (ray.hit_side == 'W')
            texture = game->vars->textures[WEST];
    return texture;
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
    t_texture *texture;
    double wall_hit_pos;
    int x;
    int y;

    while (i < (game->vars->num_rays))
    {
        wall_size = solve_fisheye(game->rays[i], game->player);
        x = i * RAY_WIDTH;
        y = (game->vars->screen_height - wall_size) / 2; //what happens if wall_size == screen_height or wall_size > screen_height?
        texture = get_ray_texture(game, game->rays[i]);
        (void)texture;
        if (game->rays[i].border == 'H')
            wall_hit_pos = game->rays[i].pos[0] - floor(game->rays[i].pos[0]);
        else
            wall_hit_pos = game->rays[i].pos[1] - floor(game->rays[i].pos[1]);      
        (void)wall_hit_pos;  
        draw_3d_wall(x, y, wall_size, game);
        i++;
    }
}
