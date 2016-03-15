/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_getlight.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 19:22:09 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:38:14 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_init_color(t_cylinder *obj, int (*ambiant_color)[4],
					int (*diff_color)[4], int (*spec_color)[4])
{
	(*ambiant_color)[0] = (obj->color & 0xFF000000);
	(*ambiant_color)[0] = (*ambiant_color)[0] >> (4 * 6);
	(*ambiant_color)[0] = (*ambiant_color)[0] * obj->ambiant;
	(*ambiant_color)[1] = (obj->color & 0x00FF0000);
	(*ambiant_color)[1] = (*ambiant_color)[1] >> (4 * 4);
	(*ambiant_color)[1] = (*ambiant_color)[1] * obj->ambiant;
	(*ambiant_color)[2] = (obj->color & 0x0000FF00);
	(*ambiant_color)[2] = (*ambiant_color)[2] >> (4 * 2);
	(*ambiant_color)[2] = (*ambiant_color)[2] * obj->ambiant;
	(*ambiant_color)[3] = (obj->color & 0x000000FF);
	(*ambiant_color)[3] = (*ambiant_color)[3] * obj->ambiant;
	(*diff_color)[0] = 0;
	(*diff_color)[1] = 0;
	(*diff_color)[2] = 0;
	(*diff_color)[3] = 0;
	(*spec_color)[0] = 0;
	(*spec_color)[1] = 0;
	(*spec_color)[2] = 0;
	(*spec_color)[3] = 0;
}

static void		ft_do_diff(t_cylinder *obj, int (*diff_color)[4],
					double angle)
{
	(*diff_color)[0] = (obj->color & 0xFF000000);
	(*diff_color)[0] = (*diff_color)[0] >> (4 * 6);
	(*diff_color)[0] = (*diff_color)[0] * obj->diffuse * angle;
	(*diff_color)[1] = (obj->color & 0x00FF0000);
	(*diff_color)[1] = (*diff_color)[1] >> (4 * 4);
	(*diff_color)[1] = (*diff_color)[1] * obj->diffuse * angle;
	(*diff_color)[2] = (obj->color & 0x0000FF00);
	(*diff_color)[2] = (*diff_color)[2] >> (4 * 2);
	(*diff_color)[2] = (*diff_color)[2] * obj->diffuse * angle;
	(*diff_color)[3] = (obj->color & 0x000000FF);
	(*diff_color)[3] = (*diff_color)[3] * obj->diffuse * angle;
}

static void		ft_do_spec(t_cylinder *obj, int (*spec_color)[4],
					double spec_angle)
{
	(*spec_color)[0] = (obj->color & 0xFF000000);
	(*spec_color)[0] = (*spec_color)[0] >> (4 * 6);
	(*spec_color)[0] = (*spec_color)[0] * obj->specular *
		pow(spec_angle, obj->shiny);
	(*spec_color)[1] = (obj->color & 0x00FF0000);
	(*spec_color)[1] = (*spec_color)[1] >> (4 * 4);
	(*spec_color)[1] = (*spec_color)[1] * obj->specular *
		pow(spec_angle, obj->shiny);
	(*spec_color)[2] = (obj->color & 0x0000FF00);
	(*spec_color)[2] = (*spec_color)[2] >> (4 * 2);
	(*spec_color)[2] = (*spec_color)[2] * obj->specular *
		pow(spec_angle, obj->shiny);
	(*spec_color)[3] = (obj->color & 0x000000FF);
	(*spec_color)[3] = (*spec_color)[3] * obj->specular *
		pow(spec_angle, obj->shiny);
}

static int		ft_ret_color(int ambiant_color[4], int diff_color[4],
					int spec_color[4])
{
	int		ret_color[5];

	ret_color[0] = ambiant_color[0] + diff_color[0] + spec_color[0];
	if (ret_color[0] > 0xFF)
		ret_color[0] = 0xFF;
	ret_color[1] = ambiant_color[1] + diff_color[1] + spec_color[1];
	if (ret_color[1] > 0xFF)
		ret_color[1] = 0xFF;
	ret_color[2] = ambiant_color[2] + diff_color[2] + spec_color[2];
	if (ret_color[2] > 0xFF)
		ret_color[2] = 0xFF;
	ret_color[3] = ambiant_color[3] + diff_color[3] + spec_color[3];
	if (ret_color[3] > 0xFF)
		ret_color[3] = 0xFF;
	ret_color[0] = ret_color[0] << (4 * 6);
	ret_color[1] = ret_color[1] << (4 * 4);
	ret_color[2] = ret_color[2] << (4 * 2);
	ret_color[4] = ret_color[0] + ret_color[1] + ret_color[2] + ret_color[3];
	return (ret_color[4]);
}

int				ft_cylinder_getlight(t_cylinder *obj, t_light *light,
					double int_coord[3], double cam_vector[3])
{
	double	norm_vec[2][3];
	double	angle[2];
	int		color[3][4];

	ft_calc_norm_vec_cylinder(obj, &norm_vec, int_coord, light);
	angle[0] = -norm_vec[1][0] * norm_vec[0][0] + -norm_vec[1][1] *
		norm_vec[0][1] + -norm_vec[1][2] * norm_vec[0][2];
	ft_init_color(obj, &color[0], &color[1], &color[2]);
	if (angle[0] < 0)
		angle[0] = 0;
	if (angle[0] > 0)
	{
		ft_do_diff(obj, &color[1], angle[0]);
		angle[1] = ft_calc_spec_angle(cam_vector, norm_vec, angle[0]);
		ft_do_spec(obj, &color[2], angle[1]);
	}
	return (ft_ret_color(color[0], color[1], color[2]));
}
