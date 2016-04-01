/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_func_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:11:25 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:03:24 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rec_angle(double nbr, double *angle, int deg)
{
	if (!angle)
		return ;
	angle[0] = nbr;
	if (deg)
		angle[0] *= RADIAN;
	angle[1] = cos(angle[0]);
	angle[2] = sin(angle[0]);
}

int		xml_cmp(char *str, char *ref)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] && ref[j] && str[i] != ref[j])
		i++;
	while (str[i] && ref[j] && str[i] == ref[j])
	{
		if (ref[j] == '\0')
			return (0);
		i++;
		j++;
	}
	if (ref[j] == '\0')
		return (0);
	return (1);
}

void	rec_cam(int fd, char *ret, t_env *e)
{
	if (!(e->cam = (t_cam *)malloc(sizeof(t_cam))))
		malloc_error();
	while (get_next_line(fd, &ret))
	{
		if (xml_cmp(ret, "<crd") == 0)
			e->cam->crd = rec_vec(ret);
		if (xml_cmp(ret, "<rotation") == 0)
			rec_rot_cam(ret, e->cam);
		if (xml_cmp(ret, "</camera") == 0)
			break ;
	}
}

t_mat	*rec_mat(char *str, t_mat *mat_lst)
{
	int		i;
	t_mat	*tmp_lst;

	i = rec_int_value(str);
	tmp_lst = mat_lst;
	while (tmp_lst)
	{
		if (tmp_lst->id == i)
			return (tmp_lst);
		tmp_lst = tmp_lst->next;
	}
	ft_putendl("Erreur: un materiau n'existe pas.");
	return (NULL);
}

int		rec_int_value(char *str)
{
	int i;

	i = 0;
	while (str[i] != '"')
		i++;
	i++;
	return (ft_atoi(&str[i]));
}
