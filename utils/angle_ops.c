/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:26:26 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/22 21:40:07 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

/*
**  cap rotations to 1 full circle, so radian between 0 and 2 pi
**  fmod is "%" but for floating point numbers
*/
double	standardize_angle(double angle)
{
	double	circle_in_rad;

	circle_in_rad = 2 * M_PI;
	angle = fmod(angle, circle_in_rad);
	if (angle < 0)
		angle += circle_in_rad;
	return (angle);
}
