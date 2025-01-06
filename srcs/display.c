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
    remaining = MINI_TILE;

    while (remaining > 0)
    {
        if (is_border_map(curr_x, y, start_x, start_y, MINI_TILE))
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

	char	**map;
	int		row;
	int		col;

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
******************DRAW PLAYER LAYER****************************
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
**  Multiplying by MINI_TILE to find the scaled down player position
**  Player is half the size of a mini map tile
*/
void draw_player(t_conn *conn, t_player *player)
{
    int center_x;
    int center_y;
    double size;

    center_x = player->play_pos[1] * MINI_TILE;
    center_y = player->play_pos[0] * MINI_TILE;
    size = MINI_TILE / 2;
    fill_player_rect(conn, center_x, center_y, size, 0xFF0000);
}


/*
******************************************************************
************************DRAW RAYS*********************************
******************************************************************
*/

/*
**  0 - initial "x" value; 1 - initial "y" value; 2 - final "x" value; 3 - final "y" value
**  Notice cartesian confusion (line, col == y, x)
*/
static void get_ray_coordinates(t_ray ray, t_player *player, int *line)
{

    line[0] = player->play_pos[1] * MINI_TILE;
    line[1] = player->play_pos[0] * MINI_TILE;
    line[2] = line[0] + (cos(ray.angle) * ray.distance * MINI_TILE);
    line[3] = line[1] + (sin(ray.angle) * ray.distance * MINI_TILE);

}

/*
**  the adjacent and opposite variables serve 2 purposes:
**  first they represent differences in x and y coordinates
**  and then are used as unit vectors
**  this is not clean code but capped by max number of variables per function
*/
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
    1 - get starting and ending position of ray(x,y) at the pixel level
    2 - calculate adjacent, opposite, hypotenuse
    4 - calculate increment in x and y position of line per pixel
    5 - store data on img, pixel by pixel, up to hypotenuse pixel
    */
void draw_all_rays(t_game *game)
{
    
    int line[4];
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

/*
**  Using bitwise operations to go from 3 independent color 1-char-ints 
**  to 1 0x00RRGGBB color
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

static t_texture get_ray_texture(t_game *game, t_ray ray)
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
    return *texture;
}

/*
**  multiplying ray->distance by TILE_SIZE to go from grid-values distance
**  to pixels
**
**  wall size is calculated via triangle similarity theorem
*/
static void adjusted_wall_height(t_ray *ray, t_player *player)
{
    double fisheye;
    double adjusted_distance;
    double wall_size;

    fisheye = cos(ray->angle - player->rotation_angle);
    adjusted_distance = ray->distance * fisheye * TILE_SIZE;
    wall_size = (TILE_SIZE / adjusted_distance) *player->dist_to_plane;
    ray->wall_height = wall_size;

}

/*
**  the if condition prevents from drawing out of screen bounds
**  it means that when wall_height > screen_height then start drawing
**  at top y coordinate
*/
static void x_y_wall_rendering_coords(t_ray *ray, t_vars *vars, int i)
{
    int x;
    int y;

    x = i * RAY_WIDTH;
    y = (vars->screen_height - ray->wall_height) / 2;
    if (y < 0)
        y = 0;
    ray->x = x;
    ray->y = y;

}

static double find_wall_hit_pos(t_ray ray)
{
    double wall_hit_pos;

    if (ray.border == 'H')
        wall_hit_pos = ray.pos[0] - floor(ray.pos[0]);
    else
        wall_hit_pos = ray.pos[1] - floor(ray.pos[1]);
    return wall_hit_pos;
}

/*
**  finds the byte at x,y position on the texture image
**  casting to (unsigned int *) makes it return next 4 bytes (1 pixel)
*/
static unsigned int get_tex_pixel(t_ray ray, int x, int y)
{
    char * pixel;
    unsigned int color;
    
    pixel = ray.tex.img.addr + (y * ray.tex.img.line_length + x * (ray.tex.img.bpp / 8));
    color = *(unsigned int *)pixel;

    return color;
}

/*
**  wall_offset -> if wall_height > screen_height we're only displaying part of the wall and 
**  therefore should be displaying part of the texture too. example: if we display 80% of
**  wall, we need to display 80% of texture. 
**  
**  step -> ratio to determine which texture pixel to sample for each wall pixel
**
**  without the second condition in the while loop program seg-faults when wall_height
**  > screen_height
**
**  tex_line is a double because when it was an int adding step < 1 made it stuck
**  at the same value all the time
*/
static void mapping_texture_pixels(t_vars *vars, t_ray ray, t_conn *conn, double wh_pos, int i)
{
    double step;
    double wall_offset;
    int tex_col;
    double tex_line;
    unsigned int tex_color;

    wall_offset = 0;
    if (ray.wall_height > vars->screen_height)
        wall_offset = (ray.wall_height - vars->screen_height) / 2.0;
    step = ray.tex.height / ray.wall_height;
    tex_line = wall_offset * step;
    tex_col = wh_pos * ray.tex.width;
    while (i < ray.wall_height && i < vars->screen_height)
    {
        tex_line = fmod(tex_line, ray.tex.height);
        tex_color = get_tex_pixel(ray, tex_col, tex_line);
        put_pixel_to_image(conn, ray.x, ray.y + i, tex_color);
        i++;
        tex_line += step;
    }
}

 /*
**  for every ray
**  1 - get wall height
**  2 - (x, y) coordinates where the strip will be rendered
**  3 - TEXTURES
**      3.1 - get texture to be rendered
**      3.2 - find where in the wall has the ray impacted
**      3.3 - find appropriate pixel in texture and write to appropriate pixel in screen image
*/
void draw_ray_cast(t_game *game, int i)
{
    double wall_hit_pos;
    while (i < game->vars->num_rays)
    {
        adjusted_wall_height(&game->rays[i], game->player);
        x_y_wall_rendering_coords(&game->rays[i], game->vars, i);
        game->rays[i].tex = get_ray_texture(game, game->rays[i]);
        wall_hit_pos = find_wall_hit_pos(game->rays[i]);
        mapping_texture_pixels(game->vars, game->rays[i], game->conn, wall_hit_pos, 0);
        i++;
    }
}