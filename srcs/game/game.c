
#include "../../inc/cub3d.h"

void ft_game(t_data *cub)
{
    init_mlx(cub);
    init_windows(cub);
    cub->position.x = cub->map->spawn.x * TILE_SIZE + 32;
    cub->position.y = cub->map->spawn.y * TILE_SIZE + 32;
    ft_get_starting_angle(cub);
    ft_malloc_rays(cub);

    render_2d_map(cub);
    render_3d(cub);

    //mlx_hook(win_ptr, 2, 1L << 0, key_pressed, &keycode);
    mlx_hook(cub->win_3d, 2, 1L << 0 ,key_hook, cub);
    mlx_hook(cub->win_3d, 3, 1L << 1 ,key_hook, cub);
    mlx_mouse_hook(cub->win_3d, ft_handle_clic, cub);  // Mouse interaction for 2D view
    mlx_loop(cub->mlx_ptr);
}