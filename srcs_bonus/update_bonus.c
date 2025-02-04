/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:26:38 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/17 18:51:25 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	new_pos(t_player *player, double *new_x,
	double *new_y, double angle)
{
	if (player->walk_direction == 'w')
	{
		*new_x += cos(angle) * player->speed * USAIN;
		*new_y += sin(angle) * player->speed * USAIN;
	}
	else if (player->walk_direction == 'a')
	{
		angle -= 90 * (M_PI / 180);
		*new_x += cos(angle) * player->speed * USAIN;
		*new_y += sin(angle) * player->speed * USAIN;
	}
	else if (player->walk_direction == 's')
	{
		*new_x += cos(angle) * (player->speed * USAIN * -1);
		*new_y += sin(angle) * (player->speed * USAIN * -1);
	}
	else if (player->walk_direction == 'd')
	{
		angle += 90 * (M_PI / 180);
		*new_x += cos(angle) * player->speed * USAIN;
		*new_y += sin(angle) * player->speed * USAIN;
	}
}

/*
**	Beware of cartesian confusion (lineas*columnas vs (x,y))
*/
static void	update_play_pos(t_vars *vars, t_player *player)
{
	double	new_x;
	double	new_y;
	double	angle;

	angle = player->rotation_angle;
	new_x = player->play_pos[1];
	new_y = player->play_pos[0];
	new_pos(player, &new_x, &new_y, angle);
	if (is_collision(new_x, new_y, player, vars))
	{
		if (player->health)
			player->health -= 5;
		return ;
	}
	player->play_pos[0] = new_y;
	player->play_pos[1] = new_x;
}

/*
**  get horizontal and vertical hit wall distance and compare both to store 
**  smallest distance
*/
void	ray_cast(t_ray *ray, t_player *player, t_vars *vars)
{
	t_ray	vert_ray;
	t_ray	horz_ray;
	double	angle;

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

void	cast_all_rays_bonus(t_game *game)
{
	double	angle;
	int		i;

	angle = game->player->rotation_angle - (game->player->field_of_view / 2);
	i = 0;
	while (i < game->vars->num_rays)
	{
		game->rays[i].angle = angle;
		game->rays[i].purpose = 'W';
		ray_cast(&(game->rays[i]), game->player, game->vars);
		angle += game->player->field_of_view / game->vars->screen_width;
		i++;
	}
}

static void cast_door_ray_bonus(t_game *game)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	//check for malloc error
	ray->angle = game->player->rotation_angle;
	ray->purpose = 'D';
	ray_cast(ray, game->player, game->vars);
	printf("ray.door.distance is: %f\n ", ray->distance);
	//update to door open if distance to ray below threshold
	//when rendering if open is default then closed else render open texture

}

/*
**	if user pressed a key then:
** 	1 - find new player position
**	2 - find new player orientation
**	3 - cast all rays
**	
*/
void	update(t_game *game)
{
	if (game->player->health <= 0)
		ft_close_conn(game);
	update_play_pos(game->vars, game->player);
	if (game->player->turn_direction != 0)
		game->player->rotation_angle += \
		game->player->rotation_speed * game->player->turn_direction;
	cast_all_rays_bonus(game);
	if (game->vars->space_press)
	{
		cast_door_ray_bonus(game);
		game->vars->space_press = 0;
	}
	printf("exit\n");
	exit(1);
}
