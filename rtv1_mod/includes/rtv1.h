/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 12:30:45 by cledant           #+#    #+#             */
/*   Updated: 2016/03/11 19:32:52 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <math.h>
# include "libft.h"
# include <stdio.h>
# define MLX_KEY_ESC 53
# define MLX_KEY_UP 126
# define MLX_KEY_DOWN 125
# define MLX_KEY_RIGHT 124
# define MLX_KEY_LEFT 123
# define MLX_KEY_PLUS 69
# define MLX_KEY_MINUS 78
# define MLX_KEY_W 13
# define MLX_KEY_A 0
# define MLX_KEY_S 1
# define MLX_KEY_D 2
# define MLX_KEY_Q 12
# define MLX_KEY_E 14
# define MLX_KEY_1 18
# define MLX_KEY_2 19
# define MLX_KEY_U 32
# define MLX_KEY_I 34
# define MLX_KEY_O 31
# define MLX_KEY_P 35
# define MLX_CAM_STEP 1
# define WIN_X 1000
# define WIN_Y 1000

typedef struct	s_sphere
{
	int		color;
	double	coord[3];
	double	north_vec[3];
	double	equ_vec[3];
	double	radius;
	double	diffuse;
	double	ambiant;
	double	specular;
	double	shiny;
}				t_sphere;

typedef struct	s_plane
{
	int		color;
	double	coord[3];
	double	factor[3];
	double	diffuse;
	double	ambiant;
	double	specular;
	double	shiny;
}				t_plane;

typedef struct	s_cylinder
{
	int		color;
	double	coord[3];
	double	dir[3];
	double	radius;
	double	diffuse;
	double	ambiant;
	double	specular;
	double	shiny;
}				t_cylinder;

typedef struct	s_cone
{
	int		color;
	double	coord[3];
	double	dir[3];
	double	angle;
	double	k;
	double	radius;
	double	diffuse;
	double	ambiant;
	double	specular;
	double	shiny;
}				t_cone;

typedef struct	s_light
{
	int		color;
	double	coord[3];
}				t_light;

typedef struct	s_camera
{
	double	coord[3];
	double	camera_size[3];
	double	camera_look_at[3];
	double	dir_vec[3];
	double	norm;
	double	norm_dir_vec[3];
	double	up_vec[3];
	double	right_vec[3];
	double	x_inc;
	double	y_inc;
	double	up_left_win[3];
}				t_camera;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*c_img;
	int			render;
	t_camera	*cam;
	t_list		*obj_list;
	t_list		*light_list;
	void		*i_globe;
	char		*c_globe;
	int			globe_width;
	int			globe_length;
	int			x;
	int			y;
}				t_mlx;

int				expose_hook(t_mlx *e);
int				key_hook(int keycode, t_mlx *e);
void			key_hook_12(int keycode, t_camera *camera, t_mlx *e);
void			key_hook_13(int keycode, t_camera *camera, t_mlx *e);
void			key_hook_14(int keycode, t_camera *camera, t_mlx *e);
void			key_hook_2(int keycode, t_camera *camera, t_mlx *e);
void			key_hook_21(int keycode, t_camera *camera, t_mlx *e);
void			key_hook_22(int keycode, t_camera *camera, t_mlx *e);
void			key_hook_23(int keycode, t_mlx *e);
void			key_hook_24(int keycode, t_mlx *e);
void			ft_draw_image(t_mlx *e);
void			ft_init_scene(t_mlx *e);
void			ft_add_obj_11(t_mlx *e, double tmp_coord[3], double tmp_vec[3]);
void			ft_add_obj_12(t_mlx *e, double tmp_coord[3], double tmp_vec[3]);
void			ft_add_obj_13(t_mlx *e, double tmp_coord[3], double tmp_vec[3]);
void			ft_add_obj_14(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl);
void			ft_add_obj_15(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cone *cone);
void			ft_init_scene_2(t_mlx *e);
void			ft_init_scene_21(t_mlx *e);
void			ft_init_scene_22(t_mlx *e);
void			ft_add_obj_21(t_mlx *e, double tmp_coord[3], double tmp_vec[3]);
void			ft_add_obj_22(t_mlx *e, double tmp_coord[3], double tmp_vec[3]);
void			ft_add_obj_23(t_mlx *e, double tmp_coord[3], double tmp_vec[3]);
void			ft_add_obj_24(t_mlx *e, double tmp_coord[3], double tmp_vec[3]);
void			ft_add_obj_25(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl);
void			ft_add_obj_26(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl);
void			ft_add_obj_27(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl);
void			ft_add_obj_28(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl);
void			ft_add_obj_29(t_mlx *e);
void			ft_add_obj_210(t_mlx *e);
void			ft_add_obj_211(t_mlx *e);
void			ft_add_obj_212(t_mlx *e);
void			ft_add_obj_213(t_mlx *e);
void			ft_add_obj_214(t_mlx *e);
void			ft_add_obj_215(t_mlx *e);
void			ft_camera_init(t_camera *cam);
void			ft_calc_int_pos(double dist, double cur_vec[3],
					double coord_cam[3], double (*int_coord)[3]);
double			ft_calc_spec_angle(double cam_vector[3], double norm_vec[2][3],
					double angle);
void			ft_scalar_product(double v1[3], double v2[3], double (*res)[3]);
void			ft_normalize_vec(double (*vec)[3]);
int				ft_add_color(int color1, int color2);
t_light			*ft_light_new(double loc[3], int color);
int				ft_is_light_interrupt(t_light *light, t_list *list,
					double int_coord[3]);
int				ft_getlight(t_list *obj, t_light *light, double int_coord[3],
					double norm_cur_dir[3], t_mlx *e);
int				ft_getambiant_light(t_list *obj);
t_sphere		*ft_sphere_new(int coloration, double origin[3], double size);
void			ft_sphere_material(double amb, double diff, double spec,
					t_sphere *sph);
int				ft_sphere_getlight(t_sphere *obj, t_light *light,
					double int_coord[3], double cam_vector[3]);
int				ft_calc_int_sphere(t_sphere *sphere, t_camera *camera,
					double cur_dir[3], double *dist);
int				ft_calc_int_sphere_light(t_sphere *sphere, t_light *light,
					double cur_dir[3], double *dist);
int				ft_sphere_ambiant(t_sphere *obj);
t_cylinder		*ft_cylinder_new(int coloration, double origin[3], double size,
					double dir[3]);
void			ft_cylinder_material(double amb, double diff, double spec,
					t_cylinder *cyl);
void			ft_calc_norm_vec_cylinder(t_cylinder *obj,
					double (*norm_vec)[2][3], double int_coord[3],
					t_light *light);
int				ft_cylinder_getlight(t_cylinder *obj, t_light *light,
					double int_coord[3], double cam_vector[3]);
int				ft_calc_int_cylinder(t_cylinder *cyl, t_camera *camera,
					double cur_dir[3], double *dist);
int				ft_calc_int_cylinder_light(t_cylinder *cyl, t_light *light,
					double cur_dir[3], double *dist);
int				ft_cylinder_ambiant(t_cylinder *obj);
t_cone			*ft_cone_new(int coloration, double origin[3], double size,
					double dir[3]);
void			ft_cone_angle(double c_angle, t_cone *cone);
void			ft_cone_material(double amb, double diff, double spec,
					t_cone *cone);
void			ft_calc_norm_vec_cone(t_cone *obj,
					double (*norm_vec)[2][3], double int_coord[3],
					t_light *light);
int				ft_cone_getlight(t_cone *obj, t_light *light,
					double int_coord[3], double cam_vector[3]);
int				ft_calc_int_cone(t_cone *cone, t_camera *camera,
					double cur_dir[3], double *dist);
int				ft_calc_int_cone_light(t_cone *cone, t_light *light,
					double cur_dir[3], double *dist);
int				ft_cone_ambiant(t_cone *obj);
t_plane			*ft_plane_new(int coloration, double origin[3], double vec[3]);
void			ft_plane_material(double amb, double diff, double spec,
					t_plane *plane);
void			ft_calc_norm_vec_plane(t_plane *obj,
					double (*norm_vec_normal)[3]);
int				ft_plane_getlight(t_plane *obj, t_light *light,
					double int_coord[3], double cam_vector[3], t_mlx *e);
int				ft_calc_int_plane(t_plane *plane, t_camera *camera,
					double cur_dir[3], double *dist);
int				ft_calc_int_plane_light(t_plane *plane, t_light *camera,
					double cur_dir[3], double *dist);
int				ft_plane_ambiant(t_plane *obj);
void			ft_lstfree_malloc(void *content, size_t size);
void			ft_write_in_image(int counter[5], t_mlx *e);
t_list			*ft_seek_int_obj(t_list *lst, t_camera *camera, double *dist,
					double dir[3]);

double			ft_dot_product(double v1[3], double v2[3]);
int				ft_get_texcolor_sphere(t_mlx *e, t_sphere *obj, double *norm_vec);
int				ft_sphere_getlight_texture(t_sphere *obj, t_light *light,
					double int_coord[3], double cam_vector[3], t_mlx *e);
void			ft_load_texture(t_mlx *e);
double			ft_perlin_noise(double x, double y, double p, int n);
double			ft_noise(int x, int y);

#endif
