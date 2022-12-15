#include	"../header/structs.h"
#include	"../header/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bit_per_pix / 8));
	*(unsigned int*)dst = color;
}

void	render(t_data *data)
{
	int pixel_x;
	int pixel_y;
	t_ray	ray;
	double	scale;
	double	**camtoworld;

	camtoworld = ft_calloc(4, sizeof(double) * 4);
	scale = tan(degtorad(data->elements->camera->fov_h * 0.5));
	pixel_y = 0;
	while (pixel_y < HEIGHT)
	{
		pixel_x = 0;
		while (pixel_x < WIDTH)
		{
			// ray_create(data, &ray, pixel_x, pixel_y);
			ray = ray_creation_plane_screen(pixel_x, pixel_y, data, scale);
			if (does_intersect_s(ray, data) == 1)
			{
				my_mlx_pixel_put(data, pixel_x, pixel_y, JUNGLE);
				// printf("1 ray direction pixel %i x/y/z: %f/%f/%f\n", pixel_x, ray.v_direct.x, ray.v_direct.y, ray.v_direct.z);
			}
				
			else
			{
				my_mlx_pixel_put(data, pixel_x, pixel_y, 0x00000000);
				// printf("0 ray direction pixel %i x/y/z: %f/%f/%f\n", pixel_x, ray.v_direct.x, ray.v_direct.y, ray.v_direct.z);
			}
				
			pixel_x++;
		}
		pixel_y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}
