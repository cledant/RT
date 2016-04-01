/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:12:19 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 17:05:19 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	write_size(int size, unsigned char *head, int begin)
{
	int	ret;

	ret = 4 - size % 4;
	size += 4 - size % 4;
	head[begin++] = size % 256;
	size -= size % 256;
	size /= 256;
	head[begin++] = size % 256;
	size -= size % 256;
	head[begin++] = size / 256;
	head[begin] = 0;
	return (ret);
}

static int	write_bmp_header(int fd, t_env *e)
{
	unsigned char	head[54];
	int				ret;
	int				i;

	i = 0;
	while (i < 54)
		head[i++] = 0;
	head[0] = 'B';
	head[1] = 'M';
	ret = write_size(54 + (e->height * e->width * 3), head, 2);
	head[10] = 54;
	head[14] = 40;
	head[18] = e->width % 256;
	head[19] = e->width / 256;
	head[22] = e->height % 256;
	head[23] = e->height / 256;
	head[26] = 1;
	head[28] = 24;
	write_size((e->height * e->width * 3), head, 34);
	write(fd, head, 54);
	return (ret);
}

static int	get_pic_nbr(void)
{
	DIR				*dir;
	struct dirent	*dp;
	int				nbr;

	dir = opendir("./save");
	nbr = -1;
	while ((dp = readdir(dir)) != NULL)
	{
		if (ft_atoi(&(dp->d_name[4])) > nbr)
			nbr = ft_atoi(&(dp->d_name[4]));
	}
	closedir(dir);
	return (nbr + 1);
}

static char	*create_file(void)
{
	char	*name;
	int		tmp;
	int		nbc;
	int		nbr;

	nbr = get_pic_nbr();
	tmp = nbr;
	nbc = 1;
	while (tmp > 0)
	{
		tmp /= 10;
		nbc++;
	}
	if (!(name = (char*)malloc(sizeof(char) * (14 + nbc))))
		malloc_error();
	ft_strcat(name, "save/pic_");
	ft_strcat(name, ft_itoa(nbr));
	ft_strcat(name, ".bmp");
	ft_putendl(name);
	nbr++;
	return (name);
}

void		save_image(char *img, t_env *e)
{
	int				v[5];
	unsigned char	*save;
	char			*file;

	file = create_file();
	v[3] = 0;
	if (!(save = (unsigned char *)malloc(sizeof(unsigned char) *
					e->height * e->width * 3 + 60)))
		malloc_error();
	v[0] = open(file, O_RDWR | O_CREAT | O_APPEND);
	v[4] = write_bmp_header(v[0], e);
	v[2] = e->height;
	put_color(e, img, v, save);
	v[2] = -1;
	while (++v[2] < v[4])
		save[v[3] + v[2]] = 0;
	write(v[0], save, e->height * e->width * 3);
	close(v[0]);
	chmod(file, 777);
	free(save);
}
