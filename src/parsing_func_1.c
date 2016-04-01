/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:07:55 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:40:32 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rec_rot_cam(char *str, t_cam *cam)
{
	int i;

	i = 0;
	while (str[i] != '"')
		i++;
	cam->rx[0] = ft_atoi(&str[++i]) * RADIAN;
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	cam->ry[0] = ft_atoi(&str[i]) * RADIAN;
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	cam->rz[0] = ft_atoi(&str[++i]) * RADIAN;
	cam->rx[1] = cos(cam->rx[0]);
	cam->ry[1] = cos(cam->ry[0]);
	cam->rz[1] = cos(cam->rz[0]);
	cam->rx[2] = sin(cam->rx[0]);
	cam->ry[2] = sin(cam->ry[0]);
	cam->rz[2] = sin(cam->rz[0]);
}

t_vector3	*rec_vec(char *str)
{
	int			i;
	t_vector3	*res;

	i = 0;
	if (!(res = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	while (str[i] != '"')
		i++;
	i++;
	res->x = ft_atoi(&str[i]);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	res->y = ft_atoi(&str[i]);
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	res->z = ft_atoi(&str[i]);
	return (res);
}

void		rec_rot(char *str, t_obj *obj)
{
	int i;

	i = 0;
	while (str[i] != '"')
		i++;
	obj->rx[0] = ft_atoi(&str[++i]) * RADIAN;
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	obj->ry[0] = ft_atoi(&str[++i]) * RADIAN;
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	obj->rz[0] = ft_atoi(&str[++i]) * RADIAN;
	obj->rx[1] = cos(obj->rx[0]);
	obj->ry[1] = cos(obj->ry[0]);
	obj->rz[1] = cos(obj->rz[0]);
	obj->rx[2] = sin(obj->rx[0]);
	obj->ry[2] = sin(obj->ry[0]);
	obj->rz[2] = sin(obj->rz[0]);
}

void		rec_coef(t_obj *obj, char *str)
{
	int i;

	obj->a = rec_int_value(str) / 100.0;
	i = 0;
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	obj->b = rec_int_value(&str[i]) / 100.0;
	while (str[i] != '"')
		i++;
	i++;
	while (str[i] != '"')
		i++;
	i++;
	obj->c = rec_int_value(&str[i]) / 100.0;
	obj->a2 = obj->a * obj->a;
	obj->b2 = obj->b * obj->b;
	obj->c2 = obj->c * obj->c;
	obj->r2 = obj->r * obj->r;
}
