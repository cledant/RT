/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 08:49:40 by cledant           #+#    #+#             */
/*   Updated: 2016/03/10 17:28:35 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_init_cur_dir(t_camera *camera, int i, int j,
					double (*norm_cur_dir)[3])
{
	double		cur_dir[3];
	double		val_cur_dir;

	cur_dir[0] = -(camera->up_left_win[0] + i * camera->x_inc *
		camera->right_vec[0] - j * camera->y_inc *
		camera->up_vec[0]) + camera->coord[0];
	cur_dir[1] = -(camera->up_left_win[1] + i * camera->x_inc *
		camera->right_vec[1] - j * camera->y_inc *
		camera->up_vec[1]) + camera->coord[1];
	cur_dir[2] = -(camera->up_left_win[2] + i * camera->x_inc *
		camera->right_vec[2] - j * camera->y_inc *
		camera->up_vec[2]) + camera->coord[2];
	val_cur_dir = sqrt(cur_dir[0] * cur_dir[0] + cur_dir[1] * cur_dir[1] +
		cur_dir[2] * cur_dir[2]);
	(*norm_cur_dir)[0] = cur_dir[0] / val_cur_dir;
	(*norm_cur_dir)[1] = cur_dir[1] / val_cur_dir;
	(*norm_cur_dir)[2] = cur_dir[2] / val_cur_dir;
}

static void		ft_reset_val(t_list **lst, t_list **light, int (*counter)[5],
					t_mlx *e)
{
	*lst = e->obj_list;
	*light = (*light)->next;
	(*counter)[3] = 0;
	(*counter)[2] = 0x00000000;
}

static void		ft_seek_light(t_mlx *e, t_list *obj, int (*counter)[5],
					double vec[2][3])
{
	t_list		*light;
	t_list		*lst;

	light = e->light_list;
	lst = e->obj_list;
	while (light != NULL)
	{
		while (lst != NULL)
		{
			if (lst != obj && ft_is_light_interrupt(light->content,
				lst, vec[1]) == 1)
			{
				(*counter)[3] = 1;
				break ;
			}
			lst = lst->next;
		}
		if ((*counter)[3] != 1)
			(*counter)[2] = ft_getlight(obj, light->content, vec[1], vec[0], e);
		else
			(*counter)[2] = ft_getlight(obj, light->content, vec[1], vec[0], e);
		ft_write_in_image(*counter, e);
		ft_reset_val(&lst, &light, counter, e);
	}
}

static void		ft_init_values(int (*counter)[5], t_mlx *e, double *dist)
{
	int		tmp;

	tmp = WIN_X * WIN_Y * 4;
	ft_bzero(e->c_img, tmp);
	(*counter)[0] = 0;
	(*counter)[1] = 0;
	(*counter)[2] = 0x00000000;
	(*counter)[3] = 0;
	(*counter)[4] = 0x00000000;
	*dist = 1000000;
}

void			ft_draw_image(t_mlx *e)
{
	int			counter[5];
	double		vector[2][3];
	t_list		*obj_int;
	double		dist;

	ft_init_values(&counter, e, &dist);
	while (counter[0] < WIN_Y)
	{
		e->y = counter[0];
		while (counter[1] < WIN_X)
		{
			e->x = counter[1];
			ft_init_cur_dir(e->cam, counter[1], counter[0], &vector[0]);
			obj_int = ft_seek_int_obj(e->obj_list, e->cam, &dist, vector[0]);
			if (obj_int != NULL)
			{
				ft_calc_int_pos(dist, vector[0], e->cam->coord, &vector[1]);
				ft_seek_light(e, obj_int, &counter, vector);
			}
			obj_int = NULL;
			dist = 1000000;
			counter[1]++;
		}
		counter[1] = 0;
		counter[0]++;
	}
}
