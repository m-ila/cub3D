# cub3D

# to do
- [x] `   1  00001` renvoie faux map
- [x] strocc delimitersS
- [x] strocc base from
- [ ] ??? leak GNL quand color est faux ???
- [ ] -> quand lecture du fichier par GNL est finie avant la fin, ca cree leak (expecte), retravailler GNL
- [x] if player outside the walls ?
- [ ] Dans game_multi_ray.c, fonction ft_malloc_rays(t_data *cub) protéger si malloc fail


## Ressources
* [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
* [Scratch a pixel](https://www.scratchapixel.com/)
* [MiniRT tips (42 stud from slack)](https://github.com/RubenNijhuis/Mini-Ray-Tracer/blob/main/minirt_tips.md)
* [42 docs - cub3d](https://harm-smits.github.io/42docs/projects/cub3d)
* [cub3d tutorial](https://hackmd.io/@nszl/H1LXByIE2)
* [cub3d tutorial medium](https://medium.com/@afatir.ahmedfatir/cub3d-tutorial-af5dd31d2fcf)
* [map tester : error map ressources](https://github.com/DevJ2K/cub3d_map_tester.git)
* [raycast](https://www.permadi.com/tutorial/raycast/rayc7.html)
* [img mlx](https://github.com/keuhdall/images_example)

### Perso
* Alias git : ```git config --add alias.wip '!f() { git add -A && git commit -m "$@" && git push; }; f'```
* ```alias cub='valgrind -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./cub3d'```