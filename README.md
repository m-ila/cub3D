# cub3D

# to do
- [ ] Dans game_multi_ray.c, fonction ft_malloc_rays(t_data *cub) protéger si malloc fail
- [ ] makefile : remettre Werror
- [ ] enlever la 2d map avec les rayons de partout
- [ ] separer les files en bonus et pas bonus
- [ ] enlever les wildcards dans le makefile
- [ ] Norme
- [ ] tests leaks
- [ ] pourquoi map2 ne fonctionne pas ?
- [ ] mettre plus de map jouables
- [ ] lorsque lit ligne par ligne une fois arrivee fin de map peut avoir des lignes empty
- [x] textures sud et est pb pixel x_max y_max
- [x] leak (invalid free sur map) si char pas bon dans la map
- [x] `   1  00001` renvoie faux map
- [x] strocc delimitersS
- [x] strocc base from
- [x] ??? leak GNL quand color est faux ???
- [x] -> quand lecture du fichier par GNL est finie avant la fin, ca cree leak (expecte), retravailler GNL
- [x] if player outside the walls ?
- [x] Free imgs quand fin partout
- [x] Angles texture
- [x] Faire en sorte que quand on reste appuyé ça avance
- [x] quand on appuie sur gauche, ça va vers la gauche etc
- [x] faire en sorte que la minimap soit sur le même écran et faire en sorte qu'elle soit en petit
- [x] parsing : régler le x_max
- [x] vérifier que le jeu ne crash pas si on lance sans env
- [x] des fois on peut rentrer dans les murs (angles et en allant en arrière)

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