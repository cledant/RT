/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perlin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:23:16 by cledant           #+#    #+#             */
/*   Updated: 2016/03/30 13:35:51 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double				ft_noise_3d(int x, int y, int z)
{
	int		value;
	int		noise;

	noise = 0;
	value = x + y * 57 + z * 157;
	noise = (value * (value * value * 161411 + 789221) + 1376312589);
	noise = noise & 0x7FFFFFFF;
	return (1 - noise / 1073741824.0f);
}

static void			zero_case(t_vector3 *vec, t_vector3 *cpy)
{
	if (vec->x == 0)
		cpy->x = 0.001;
	else
		cpy->x = vec->x;
	if (vec->y == 0)
		cpy->y = 0.001;
	else
		cpy->y = vec->y;
	if (vec->z == 0)
		cpy->z = 0.001;
	else
		cpy->z = vec->z;
}

double				perlin_noise_3d(t_vector3 *vec, double p, int n)
{
	double		ret_val;
	int			i;
	double		freq;
	double		amp;
	t_vector3	cpy;

	i = 0;
	ret_val = 0;
	while (i < n)
	{
		amp = pow(2, i);
		freq = pow(p, i);
		zero_case(vec, &cpy);
		ret_val = ret_val + ft_noise_interpolation_3d(cpy.x * freq,
						cpy.y * freq, cpy.z * freq) * amp;
		i++;
	}
	return (ret_val);
}
