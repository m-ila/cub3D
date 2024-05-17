# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/06 14:38:55 by mbruyant          #+#    #+#              #
#    Updated: 2024/05/17 18:41:31 by yuewang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all bonus clean fclean re

all: bonus

bonus:
	@$(MAKE) -C bonus bonus

clean:
	@$(MAKE) -C bonus clean

fclean:
	@$(MAKE) -C bonus fclean

re:
	@$(MAKE) -C bonus re
