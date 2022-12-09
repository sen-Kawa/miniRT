#include	"../header/structs.h"
#include	"../header/minirt.h"

void init_counter(t_data *data)
{
	t_counter *counter;

	data->counter = malloc(sizeof(t_counter));
	counter = data->counter;
	counter->ambient_light_count = 0;
	counter->light_count = 0;
	counter->camera_count = 0;
	counter->sphere_count = 0;
	counter->cylinder_count = 0;
	counter->plane_count = 0;
	counter->newline_count = 0;
}

int	init_elements(char **argv, t_data *data)
{
	char	*line;
	int		fd;

	fd = open_file(argv);
	allocating_elements(data);
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, data))
		{
			free(line);
			close(fd); 
			return (0);//TODO- Error message for parsing
		}
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

void allocating_elements(t_data *data)
{
	int obj_cont;

	obj_cont = data->counter->cylinder_count + data->counter->plane_count 
	+ data->counter->sphere_count;
	data->elements = malloc(sizeof(t_elements));
	data->elements->objects = malloc(sizeof(t_elements) * obj_cont);
}
