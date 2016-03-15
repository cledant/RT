/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_getlight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 13:06:52 by cledant           #+#    #+#             */
/*   Updated: 2016/03/11 19:36:44 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_init_color(t_plane *obj, int (*ambiant_color)[4],
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

static void		ft_do_diff(t_plane *obj, int (*diff_color)[4],
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

static void		ft_do_spec(t_plane *obj, int (*spec_color)[4],
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

static void		ft_sinus_norm_type1(double (*norm)[3], double int_coord[3])
{
	/* damier avec gros point */
	(*norm)[0] = (1 + sin(10 * int_coord[0])) / 2.0f;
	(*norm)[1] = (1 + sin(10 * int_coord[1])) / 2.0f;
	(*norm)[2] = (1 + sin(10 * int_coord[2])) / 2.0f;
}

static void		ft_sinus_norm_type_verti(double (*norm)[3], double int_coord[3])
{
	/*tole vertical*/
	(*norm)[0] = (1 + sin(10 * int_coord[0])) / 2.0f;
	(*norm)[1] = (1 + sin(10 * int_coord[1])) / 2.0f;
}

static void		ft_sinus_norm_type_hori(double (*norm)[3], double int_coord[3])
{
	/*tole horizontal*/
	(*norm)[1] = (1 + sin(10 * int_coord[1])) / 2.0f;
	(*norm)[2] = (1 + sin(10 * int_coord[2])) / 2.0f;
}

static int		ft_checker_xy(double int_coord[3])
{
	double	x;
	double	y;
	double	size;
	int		color_1;
	int		color_2;

	color_1 = 0x00FF0000;
	color_2 = 0x00FFFFFF;
	size = 2;
	if (int_coord[0] < 0)
		int_coord[0] = -int_coord[0] + size / 2;
	if (int_coord[1] < 0)
		int_coord[1] = -int_coord[1] + size / 2;
	x = fmod(int_coord[0], size);
	y = fmod(int_coord[1], size);
	if ((x >= 0 && x <= size / 2) && (y >= 0 && y <= size / 2))
		return (color_1);
	else if ((x > size / 2  && x <= size) && (y >= 0 && y <= size / 2))
		return (color_2);
	else if ((x >= 0 && x <= size / 2) && (y > size / 2 && y <= size))
		return (color_2);
	else
		return (color_1);
}

static void		ft_display_perlin(double noise, double (*norm_vec)[3])
{
	double norm;

	(*norm_vec)[0] = (*norm_vec)[0] * -noise;
	(*norm_vec)[1] = (*norm_vec)[1] * -noise;
	(*norm_vec)[2] = (*norm_vec)[2] * -noise;
	norm = 	(*norm_vec)[0] * (*norm_vec)[0] + (*norm_vec)[1] *
		(*norm_vec)[1] + (*norm_vec)[2] * (*norm_vec)[2];
	(*norm_vec)[0] = (*norm_vec)[0] / norm;
	(*norm_vec)[1] = (*norm_vec)[1] / norm;
	(*norm_vec)[2] = (*norm_vec)[2] / norm;
}

int				ft_plane_getlight(t_plane *obj, t_light *light,
					double int_coord[3], double cam_vector[3], t_mlx *e)
{
	double	norm_vec[2][3];
	double	angle[2];
	int		color[3][4];
	double	noise;

	norm_vec[0][0] = int_coord[0] - light->coord[0];
	norm_vec[0][1] = int_coord[1] - light->coord[1];
	norm_vec[0][2] = int_coord[2] - light->coord[2];
	ft_normalize_vec(&norm_vec[0]);
	ft_calc_norm_vec_plane(obj, &norm_vec[1]);
	noise = ft_perlin_noise(int_coord[0], int_coord[1], 0.5, 32);
//	printf("noise = %f\n", noise);
	ft_display_perlin(noise, &norm_vec[1]);
//	ft_sinus_norm_type_verti(&norm_vec[1], int_coord);
	angle[0] = -norm_vec[1][0] * norm_vec[0][0] + -norm_vec[1][1] *
		norm_vec[0][1] + -norm_vec[1][2] * norm_vec[0][2];
	ft_init_color(obj, &color[0], &color[1], &color[2]);
//	obj->color = ft_checker_xy(obj, int_coord);
	angle[1] = ft_calc_spec_angle(cam_vector, norm_vec, angle[0]);
//	ft_do_spec(obj, &color[2], angle[1]);
	if (angle[0] < 0)
		angle[0] = -angle[0];
	if (angle[0] > 0)
		ft_do_diff(obj, &color[1], angle[0]);
	return (ft_ret_color(color[0], color[1], color[2]));
}
