/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:11:48 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:40:55 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mat	*rec_mat_addr(char *str, t_mat *lst_mat)
{
	int		i;
	t_mat	*cpy;

	i = rec_int_value(str);
	cpy = lst_mat;
	while (cpy != NULL && cpy->id != i)
		cpy = cpy->next;
	if (cpy == NULL)
		xml_error_texture(1, 1, i);
	return (cpy);
}

void	rec_image_file(t_img **image, char *ret, void *mlx)
{
	char	*name;
	int		endian;
	int		bpp;
	int		sizeline;

	name = rec_name(ret);
	if (((*image)->img = mlx_xpm_file_to_image(mlx, name, &(*image)->img_width,
					&(*image)->img_height)) != NULL)
	{
		(*image)->data = mlx_get_data_addr((*image)->img, &bpp, \
		&sizeline, &endian);
	}
	else
		(*image)->data = NULL;
	if (name != NULL)
		free(name);
}

int		rec_sign(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '"') && (str[i] != '\0'))
		i++;
	if ((str[i] != '\0') && (str[i + 1] == '-'))
		return (-1);
	return (1);
}
