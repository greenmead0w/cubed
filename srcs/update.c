#include "cubed.h"









static int is_wall(int x, int y, t_vars *vars)
{
	if (x > vars->screen_width || x < 0 || y < 0 || y > vars->screen_height)
		return 1;
	if (vars->game_map[y][x] == '1')
		return 1;
	else
		return 0;

}


static void update_play_pos(t_vars *vars, t_player *player)
{
	printf("old position is: map[%f][%f]\n", player->play_pos[0], player->play_pos[1]);
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
	if (is_wall((int)new_x, (int)new_y, vars))
		return;
	printf("not a wall\n");
	player->play_pos[0] = new_y; //check for cartesian confusion (lineas*columnas vs (x,y))
	player->play_pos[1] = new_x;

	printf("new position is: map[%f][%f]\n", player->play_pos[0], player->play_pos[1]);

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
	//TODO: update_player_angle()



}
