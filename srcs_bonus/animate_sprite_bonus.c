/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:03:52 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 22:06:18 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static time_t	get_time_diff(time_t *reference_time)
{
	struct timeval	s_tp;
	time_t		current_time;
	time_t		time_diff;
	
	gettimeofday(&s_tp, 0);
	current_time = s_tp.tv_sec;
	time_diff = current_time - *reference_time;
	if (DELAY_4 <= time_diff)
		*reference_time = current_time;	
	return (time_diff);
}

void	init_textures(t_texture **tex, t_texture **type, enum e_mode mode)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	if (mode == animate_empty_stadium)
	{
		while (i < 4)
			tex[i++] = type[j++];
	}
	else if (mode == animate_spectators_up)
	{
		while (i < 4)
			tex[i++] = type[j++];
	}	
	else if (mode == spectators_relaxed)
	{
		while (i < 4)
			tex[i++] = type[j++];
	}
}

void	set_texture_to_display(t_vars *vars)
{
	time_t	time;

	time = get_time_diff(&vars->reference_time);
	if (time < DELAY_1)
		init_textures(vars->textures, vars->animate_empty, animate_empty_stadium);
	else if (time < DELAY_2)
		init_textures(vars->textures, vars->walls, spectators_relaxed);
	else if (time < DELAY_3)
		init_textures(vars->textures, vars->animate_cheer, animate_spectators_up);
	else if (time < DELAY_4)  
		init_textures(vars->textures, vars->walls, spectators_relaxed);
	else
		init_textures(vars->textures, vars->animate_empty, animate_empty_stadium);
}
