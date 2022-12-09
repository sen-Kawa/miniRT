#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "structs.h"
#	include <fcntl.h> //open

# ifdef __APPLE__ // should work in linux and mac headers
#  include "../mlx/mlx.h"
#  include <OpenGL/gl.h>//OS x libs
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
# else
#  include <GL/glut.h>
#  include <mlx.h>
# endif

# define WIDTH			1400
# define HEIGHT 		1400
# define BUFFERSIZE 	1000

typedef struct s_elements	t_elements;
typedef struct s_counter	t_counter;

typedef	struct s_data {
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	t_counter	*counter;
	t_elements	*elements;
} t_data;

//free.c
void	freeing_dpointer(char **paths);

//main.c
int open_file(char **argv);

//init.c
int		init_elements(char **argv, t_data *data);
void	init(t_data *data);


#endif
