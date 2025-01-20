/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:03:52 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/17 17:38:16 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

time_t	get_current_time(void)
{
	struct timeval	*s_tp;
	time_t		current_time;

	gettimeofday(s_tp, 0);
	current_time = s_tp->tv_sec;
//	current_time = s_tp->tv_sec * 1000 + s_tp->tv_usec / 1000;
	return (current_time);
}


void	texture_to_display(t_game *game)
{
	time_t	time;

	time = get_current_time() - reference_time;
	if (time < delay_1)
		//load_img_1(empty)
	if (delay_1 <= time < delay_2)
		//load_img_2(public)
	if (delay_2 <= time < delay_3)
		//load_img_3(public_up)
	if (current_time - reference_time < delay_4)  
		//load_img_2(public)
	if (delay_4 <= time)
		reference_time = current_time;
}

typedef struct s_delay
{
	time_t	delay_1;
	time_t	delay_2;
	time_t	delay_3;
	time_t	delay_4;
}	t_delay;

# define DELAY_1 2
# define DELAY_2 3
# define DELAY_3 1
# define DELAY_4 3
