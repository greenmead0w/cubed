/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:40:06 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/10 12:42:55 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	se llama a esta función desde:
**	1- examine_color -> check_floor_ceiling -> revise_digit
**	2 - parse->fill_colors_list -> take_partial_color
**	En 1) hace falta q los chars de line vayan corriendo (char ** como param),
**	pero en 2) no tienen que correr (char *), si no da problemas.
**	Lo que he hecho de manera temporal es crear 2 funciones casi idénticas,
**	pero habría que cambiar por una función para los 2 casos. 
**	Igual usando un flag como parámetro?
*/

/*
** ejemplo: line = "200, 100, 55" --> count_digits devuelve 3
** ejemplo: line = "123456, " --> count_digits devuelve 6 (error)
*/
int	count_digits(char *line)
{
	int	digit_number;

	digit_number = 0;
	while ('0' <= *line && *line <= '9')
	{
		line++;
		digit_number++;
	}
	return (digit_number);
}

//necesario el tipo de parametro en examine_colors -> revise_digit
int	count_digits_2(char **line)
{
	int	digit_number;

	digit_number = 0;
	while ('0' <= **line && **line <= '9')
	{
		(*line)++;
		digit_number++;
	}
	return (digit_number);
}
