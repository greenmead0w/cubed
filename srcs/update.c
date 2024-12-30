#include "cubed.h"



/*
** function called in update_player_position() and when casting rays
** in the first case ray is passed as null, in the second one we prevent the ray
** from being chosen by setting its value high
*/
int is_wall3(int x, int y, t_vars *vars, t_ray *ray)
{
	//printf("wall3(): x: %i, y: %i\n", x, y);
	if (x > vars->screen_width || x < 0 || y < 0 || y > vars->screen_height)
	{
		if (ray && ray->distance)
			ray->distance = INT_MAX;
		return 1;
	}
	if (vars->game_map[y][x] == '1' )
		return 1;
	else
		return 0;

}




/*
** function called in update_player_position() and when casting rays
** in the first case ray is passed as null, in the second one we prevent the ray
** from being chosen by setting its value high
*/
int is_wall2(int x, int y, t_vars *vars, t_ray *ray)
{
	//printf("wall2(): x: %i, y: %i\n", x, y);
	if (x > vars->screen_width || x < 0 || y < 0 || y > vars->screen_height)
	{
		if (ray && ray->distance)
			ray->distance = INT_MAX;
		return 1;
	}
	if (vars->game_map[y][x] == '1' )
		return 1;
	else
		return 0;

}





/*
** function called in update_player_position() and when casting rays
** in the first case ray is passed as null, in the second one we prevent the ray
** from being chosen by setting its value high
*/
int is_wall(int x, int y, t_vars *vars, t_ray *ray)
{
	if (x > vars->screen_width || x < 0 || y < 0 || y > vars->screen_height)
	{
		if (ray && ray->distance)
			ray->distance = INT_MAX;
		return 1;
	}
	if (vars->game_map[y][x] == '1' )
		return 1;
	else
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
	if (is_wall((int)new_x, (int)new_y, vars, 0))
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
	static int i = 0;
    double angle;

	//printf("before standard angle[%d] is: %d | ", i, (int)(ray->angle * 180 / M_PI));
    angle = standardize_angle(ray->angle);
	//printf("standard angle[%d] is: %d\n", i, (int)(angle * 180 / M_PI));
	//printf("-----------------------\n");
	i++;
    vert_ray.angle = angle;
    horz_ray.angle = angle;
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


