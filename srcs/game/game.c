
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
    render_3d_view(cub);

    mlx_key_hook(cub->win_2d, key_hook, cub);
    mlx_mouse_hook(cub->win_2d, ft_handle_clic, cub);  // Mouse interaction for 2D view
    mlx_loop(cub->mlx_ptr);
}