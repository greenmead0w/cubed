#include "cubed.h"


/*

*/
static char wall_side_hit(int x, int y, t_vars *vars, t_ray *ray)
{
	if (x == 0)
		return 'E';
	if (y == 0)
		return 'S';
	if (x == vars->map_cols)
		return 'W';
	if (y == vars->map_rows -1)
		return 'N';
	if (ray->border == 'H')
	{
		if (ray->angle >0 && ray->angle < M_PI) //ray going bottom (graphically)
			return 'N';
		else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
			return 'S';
	}
	if (ray->border == 'V')
	{
		if ((ray->angle > 3 * M_PI / 2 && ray->angle <= 2 * M_PI) 
			|| (ray->angle >= 0 && ray->angle < M_PI / 2) ) //ray going east
			return 'W';
		else if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
			return 'E';
	}
	return 0;
}

/*
** function called in update_player_position() and when casting rays
** in the first case ray is passed as null, in the second one we prevent the ray
** from being chosen by setting its value high
*/
int ray_is_wall(int x, int y, t_vars *vars, t_ray *ray)
{
	if (x > vars->map_cols || x < 0 || y < 0 || y > vars->map_rows)
	{
		ray->distance = INT_MAX;
		return 1;
	}
	if (y == vars->map_rows) // last row of char ** is null, if doing game_map[last_row] then seg fault
	{
		ray->hit_side = 'N';
		return 1;
	}
	if (vars->game_map[y][x] == '1' )
	{
		ray->hit_side = wall_side_hit(x, y, vars, ray);
		return 1;
	}
	else
		return 0;

}

int pos_is_wall(double x, double y, t_vars *vars)
{
	int ix;
	int iy;

	ix = (int)x;
	iy = (int)y;
	if (ix > vars->map_cols || ix < 0 || iy < 0 || iy > vars->map_rows)
		return 1;
	if (vars->game_map[iy][ix] == '1' )
		return 1;
	else
		return 0;
}

/*
**	Without this function only checking the center of the rectangle, not the edges
**	or sides, and in many cases the center is not in the wall, but the edges / sides
**	are.
**	
**	collision_margin explanation:
**	1 - x and y params are grid indexes, player->display_size is 8 pixels, so dividing by
**		TILE_SIZE makes everything comparable in grid units
**	2 - Dividing by 2 because it's a square and we get the corners / sides of the square
**		
**	Important note: MINI_TILE scale is only used for displaying purposes, the wall collision
**	detection needs to work at the full TILE_SIZE scale, that's why we harmonize grid values
**	by dividing by TILE_SIZE
**
*/
int is_collision(double x, double y, t_player *player, t_vars *vars)
{
	//square sides
	double left;
	double right;
	double top;
	double base;
	double collision_margin;

	collision_margin = (player->display_size / TILE_SIZE) / 2;
	left = x - collision_margin;
	right = x + collision_margin;
	top = y - collision_margin;
	base = y + collision_margin;

	if (pos_is_wall(left, top, vars) || pos_is_wall(left, base, vars)
		|| pos_is_wall(right, top, vars) || pos_is_wall(right, base, vars)
		|| pos_is_wall(left, y, vars) || pos_is_wall(right, y, vars)
		|| pos_is_wall(x, top, vars) || pos_is_wall(x, base, vars))
			return 1;
	return 0;
}


static void update_play_pos(t_vars *vars, t_player *player)
{
	//printf("old position is: map[%f][%f]\n", player->play_pos[0], player->play_pos[1]);
	double new_x;
	double new_y;
	double angle;

	angle = player->rotation_angle;
	new_x = player->play_pos[1];
	new_y = player->play_pos[0];
	if (player->walk_direction == 'w')
	{
		new_x += cos(angle) * player->speed;
		new_y += sin(angle) * player->speed;
	}
	else if (player->walk_direction == 'a')
	{
		angle -= 90 * (M_PI/180); 
		new_x += cos(angle) * player->speed;
		new_y += sin(angle) * player->speed;
	}
	else if (player->walk_direction == 's')
	{
		new_x += cos(angle) * (player->speed * -1);
		new_y += sin(angle) * (player->speed * -1);
	}
	else if (player->walk_direction == 'd')
	{
		angle += 90 * (M_PI/180); 
		new_x += cos(angle) * player->speed;
		new_y += sin(angle) * player->speed;
	}
	//check for walls
	if (is_collision(new_x, new_y, player, vars))
		return;
	//printf("not a wall\n");
	player->play_pos[0] = new_y; //check for cartesian confusion (lineas*columnas vs (x,y))
	player->play_pos[1] = new_x;

	//printf("new position is: map[%f][%f]\n", player->play_pos[0], player->play_pos[1]);

}

/*
**  cap rotations to 1 full circle, so radian between 0 and 2 pi
**  fmod is "%" but for floating point numbers
*/
static double standardize_angle(double angle)
{
   double circle_in_rad;

   circle_in_rad =  2 * M_PI;
   angle = fmod(angle, circle_in_rad);
   if (angle < 0)
        angle +=circle_in_rad;

   return angle;
}

/*
**  get horizontal and vertical hit wall distance and compare both to store 
**  smallest distance
*/
void ray_cast(t_ray *ray, t_player * player, t_vars *vars)
{
    t_ray vert_ray;
    t_ray horz_ray;
    double angle;

    angle = standardize_angle(ray->angle);
    vert_ray.angle = angle;
    horz_ray.angle = angle;
	vert_ray.border = 'V';
	horz_ray.border = 'H';
    vertical_border(&vert_ray, player, vars);
    horizontal_border(&horz_ray, player, vars);
	if (vert_ray.distance < horz_ray.distance)
		*ray = vert_ray;
	else
		*ray = horz_ray;
}

void cast_all_rays(t_game *game)
{
	double angle; 
	int i;
	//initial angle for ray 0
	angle = game->player->rotation_angle - (game->player->field_of_view / 2);
	i = 0;
	while (i < game->vars->num_rays)
	{
		game->rays[i].angle = angle;
		//printf("ray[%d].angle: %f\n", i, (game->rays[i].angle* 180 / M_PI));
		ray_cast(&(game->rays[i]), game->player, game->vars);
		angle += game->player->field_of_view / game->vars->screen_width;
		//printf("ray[%d].distance: %f\n", i, (game->rays[i].distance));
		i++;
		
	}
}

/*
**	if user pressed a key then:
** 	1 - find new player position
**	2 - find new player orientation
**	3 - cast all rays
**	
*/
void update(t_game *game)
{
	update_play_pos(game->vars, game->player);
	if (game->player->turn_direction != 0) //updates player angle
		game->player->rotation_angle += 
		game->player->speed * game->player->turn_direction;
	cast_all_rays(game);

}


