/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perlin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:23:16 by cledant           #+#    #+#             */
/*   Updated: 2016/03/11 19:27:34 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h" 

double		ft_noise(int x, int y)
{
	int		value;
	int		noise;

	value = x + y * 57;
	value = pow((value << 13),value);
	noise = (value * (value * value * 15731 + 789221) + 1376312589);
	noise = noise & 0x7FFFFFFF;
	return ( 1 - noise / 1073741824.0f);
}

static double		ft_smooth_noise(double x, double y)
{
	double	u;
	double	v;
	double	w;

	u = (ft_noise(x - 1, y - 1) + ft_noise(x + 1, y - 1) +
			ft_noise(x - 1, y + 1) + ft_noise(x + 1, y + 1)) / 16.0f;
	v = (ft_noise(x - 1, y) + ft_noise(x + 1, y) +
			ft_noise(x, y - 1) + ft_noise(x, y + 1)) / 8.0f;
	w = ft_noise(x, y) / 4.0f;
	return (u + v + w);
}

static double		ft_cos_interpolate(double coeff_1, double coeff_2,
						double x)
{
	double	x_rad;
	double	coeff_3;
	double	ret_value;

	x_rad = x * M_PI;
	coeff_3 = (1 - cos(x_rad)) * 0.5f;
	ret_value = coeff_1 * (1 - coeff_3) + coeff_2 * coeff_3;
	return (ret_value);
}

static double		ft_noise_interpolation(double x, double y)
{
	double	rest_x;
	double	rest_y;
	double	value[4];
	double	inter[2];
	double	ret_value;

	rest_x = (int)x - x;
	rest_y = (int)y - y;
	value[0] = ft_smooth_noise(rest_x, rest_y);
	value[1] = ft_smooth_noise(rest_x + 1, rest_y);
	value[2] = ft_smooth_noise(rest_x, rest_y + 1);
	value[3] = ft_smooth_noise(rest_x + 1, rest_y + 1);
	inter[0] = ft_cos_interpolate(value[0], value[1], rest_x);
	inter[1] = ft_cos_interpolate(value[2], value[3], rest_x);
	ret_value = ft_cos_interpolate(inter[0], inter[1], rest_y);
	return (ret_value);
}

double				ft_perlin_noise(double x, double y, double p, int n)
{
	double	ret_val;
	int		i;
	double	freq;
	double	amp;

	i = 0;
	ret_val = 0;
	while (i < n)
	{
		freq = pow(2, i);
		amp = pow(p, i);
		ret_val = ret_val + ft_noise_interpolation(x * freq, y * freq) * amp;
		i++;
	}
	return (ret_val);
}
