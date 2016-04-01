/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin3d_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:24:53 by cledant           #+#    #+#             */
/*   Updated: 2016/03/30 13:24:56 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double		ft_smooth_noise(double x, double y, double z)
{
	double	u;
	double	v;
	double	w;

	u = (ft_noise_3d(x - 1, y - 1, z) + ft_noise_3d(x + 1, y - 1, z) +
		ft_noise_3d(x - 1, y + 1, z) + ft_noise_3d(x + 1, y + 1, z) +
		ft_noise_3d(x - 1, y - 1, z + 1) + ft_noise_3d(x + 1, y - 1, z + 1) +
		ft_noise_3d(x - 1, y + 1, z + 1) + ft_noise_3d(x + 1, y + 1, z + 1) +
		ft_noise_3d(x - 1, y - 1, z - 1) + ft_noise_3d(x + 1, y - 1, z - 1) +
		ft_noise_3d(x - 1, y + 1, z - 1) + ft_noise_3d(x + 1, y + 1, z - 1)) /
		64.0f;
	v = (ft_noise_3d(x - 1, y, z) + ft_noise_3d(x + 1, y, z) +
		ft_noise_3d(x, y - 1, z) + ft_noise_3d(x, y + 1, z) +
		ft_noise_3d(x - 1, y, z - 1) + ft_noise_3d(x + 1, y, z - 1) +
		ft_noise_3d(x, y - 1, z - 1) + ft_noise_3d(x, y + 1, z - 1) +
		ft_noise_3d(x - 1, y, z + 1) + ft_noise_3d(x + 1, y, z + 1) +
		ft_noise_3d(x, y - 1, z + 1) + ft_noise_3d(x, y + 1, z + 1)) / 32.0f;
	w = ft_noise_3d(x, y, z) / 16.0f;
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

static void			ft_op_noise_inter_1(double (*value)[8], double x,
						double y, double z)
{
	(*value)[0] = ft_smooth_noise(x, y, z);
	(*value)[1] = ft_smooth_noise(x + 1, y, z);
	(*value)[2] = ft_smooth_noise(x, y + 1, z);
	(*value)[3] = ft_smooth_noise(x + 1, y + 1, z);
	(*value)[4] = ft_smooth_noise(x, y, z + 1);
	(*value)[5] = ft_smooth_noise(x + 1, y, z + 1);
	(*value)[6] = ft_smooth_noise(x, y + 1, z + 1);
	(*value)[7] = ft_smooth_noise(x + 1, y + 1, z + 1);
}

static void			ft_op_noise_inter_2(double *value, double *rest,
						double (*inter)[4], double (*inter_bis)[2])
{
	(*inter)[0] = ft_cos_interpolate(value[0], value[1], rest[0]);
	(*inter)[1] = ft_cos_interpolate(value[2], value[3], rest[0]);
	(*inter)[2] = ft_cos_interpolate(value[4], value[5], rest[0]);
	(*inter)[3] = ft_cos_interpolate(value[6], value[7], rest[0]);
	(*inter_bis)[0] = ft_cos_interpolate((*inter)[0], (*inter)[1], rest[1]);
	(*inter_bis)[1] = ft_cos_interpolate((*inter)[2], (*inter)[3], rest[1]);
}

double				ft_noise_interpolation_3d(double x, double y, double z)
{
	double	rest[3];
	double	value[8];
	double	inter[4];
	double	inter_bis[2];
	double	ret_value;

	if (x >= 0)
		rest[0] = x - (int)x;
	else
		rest[0] = x - ((int)x - 1);
	if (y >= 0)
		rest[1] = y - (int)y;
	else
		rest[1] = y - ((int)y - 1);
	if (z >= 0)
		rest[2] = z - (int)z;
	else
		rest[2] = z - ((int)z - 1);
	ft_op_noise_inter_1(&value, x, y, z);
	ft_op_noise_inter_2(value, rest, &inter, &inter_bis);
	ret_value = ft_cos_interpolate(inter_bis[0], inter_bis[1], rest[2]);
	return (ret_value);
}
