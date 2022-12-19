#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
# include <fcntl.h> //open

# ifdef __APPLE__ // should work in linux and mac headers
#  include "../mlx/mlx.h"
#  include <OpenGL/gl.h>//OS x libs
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
#  include <mlx.h>
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# define WIDTH			1000
# define HEIGHT			1000
# define ASPECT_RATIO	HEIGHT / WIDTH
# define RAY_T_MAX		1.0e30f
# define RAY_T_MIN		0.0001f
# define INFO_AL		3
# define INFO_C			4
# define INFO_L			4
# define INFO_PL		4
# define INFO_SP		4
# define INFO_CY		6
# define INFO_COLOR		3
# define INFO_V			3

//color
# define JUNGLE			0x00A7CBD0
# define CORIANDER		0x00BDCCAC
# define BLACK			0x00000000
# define SHADOW			0x00306000

//events
# define RED_CROSS		17
# define KEY_PRESS		2
# define ESC			65307

typedef struct s_coordenates	t_coord;
typedef struct s_elements		t_elements;
typedef struct s_counter		t_counter;
typedef struct s_elements		t_elements;
typedef struct s_amb_light		t_amb_light;
typedef struct s_light			t_light;
typedef struct s_cam			t_cam;
typedef struct s_obj			t_obj;
typedef struct s_vec			t_vec;
typedef struct s_ray			t_ray;
typedef struct s_color			t_color;
typedef struct s_matrix			t_mat;

typedef struct s_data
{
	int			bit_per_pix;
	int			line_len;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	t_counter	*counter;
	t_elements	*elements;
}	t_data;

//free.c
void	freeing_dpointer(char **paths);
void	free_allocation(t_data *data);
void	free_allocation_objects(t_data *data);

//alloc.c
int		struct_allocation(t_data *data);
void	object_allocation(t_data *data);

//utils.c
int		expected_words(int expected, char **words);
int		open_file(char **argv);
int		isaldigit(char **value);
int		check_colors(char *rgb, t_color *location);
int		char_to_double(char *value, double *dst);

//main.c

//parsing.c
int		parse_line(char *line, t_data *data, char **splitted);
int		check_arguments(int argc, char **argv);
int		check_counter(t_data *data, char **argv);
void	parsing(int argc, char **argv, t_data *data);

//init.c
int		init_elements(char **argv, t_data *data);
void	init_counter(t_data *data);

//count_input.c
int		counting_elements(char **argv, t_data *data);
int		increase_count(t_data *data, char **splitted);
int		count_elements(char *line, t_data *data);
int		assign_info(char **splitted);
int		check_count(t_data *data);

//controls.c
void	controls(t_data *data);

//elements_single.c
int		init_a(t_data *data, char **splitted);
int		init_l(t_data *data, char **splitted);
int		init_camera(t_data *data, char **splitted);
int		init_camera_fov(t_cam *cam, char **splitted);
t_coord	conversion(int px, int py);

//objects.c
int		init_s(t_data *data, char **splitted);
int		init_cylinder(t_data *data, char **splitted);
int		init_plane(t_data *data, char **splitted);
t_vec	init_vector(char *xyz);
int		check_boundries_vector(t_vec *vector, int min, int max);

//vector_operations.c
t_vec	normalise(t_vec vector);
double	dot_prod(t_vec v1, t_vec v2);
t_vec	cross_prod(t_vec v1, t_vec v2);
double	vector_lensqr(t_vec v);
double	vector_len(t_vec v);

//render.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	render(t_data *data);
void	intersections(t_data *data, t_ray *ray, int pixel_x, int pixel_y);

//vector_operations_2.c
t_vec	make_vector(double x, double y, double z);
t_vec	vector_dev(t_vec u, t_vec v);
t_vec	vector_rot_x(t_vec v, double alpha);
t_vec	vector_rot_y(t_vec v, double alpha);
t_vec	vector_rot_z(t_vec v, double alpha);


//vector_operations_3.c
double	degtorad(double deg);
t_vec	mult_vec_mat(t_vec vec, double **mat);
t_vec	make_opposite_vector(t_vec vec);

//rays.c
int		ray_create(t_data *data, t_ray *ray, int px, int py);
int		does_intersect_p(t_ray ray, t_data *data);
int		intersect_p(t_ray ray, t_data *data);
int		does_intersect_s(t_ray *ray, t_data *data, int id, int *objid);
int		does_intersect_s_shadow(t_ray *ray, t_data *data);

//plane_screen.c
t_ray	ray_creation_plane_screen(int px, int py, t_data *data, double scale);
void	cam_to_world_mat(t_vec c_orient, double ***mat, t_data *data);
double	**make_mat44(t_vec forward, t_vec up, t_vec right, t_data *data);
int		shadow_rays(t_ray *ray, t_data *data);

#endif
