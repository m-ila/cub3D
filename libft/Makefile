NAME = libft.a
CC = cc
FLAGS = -Wall -Werror -Wextra
INC = libft.h
SRC_DIR	= srcs/
OBJ_DIR = objs/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
SRCS = $(SRC_DIR)ft_2d_arrays.c \
$(SRC_DIR)ft_ai_to_ia.c \
$(SRC_DIR)ft_calloc.c \
$(SRC_DIR)ft_char_is.c \
$(SRC_DIR)ft_char_is_2.c \
$(SRC_DIR)ft_char_mod.c \
$(SRC_DIR)ft_lst_one.c \
$(SRC_DIR)ft_lst_two.c \
$(SRC_DIR)ft_mem.c \
$(SRC_DIR)ft_put_fd.c \
$(SRC_DIR)ft_scan_str.c \
$(SRC_DIR)ft_split_append.c \
$(SRC_DIR)ft_split.c \
$(SRC_DIR)ft_str_dup.c \
$(SRC_DIR)ft_str_is.c \
$(SRC_DIR)ft_str_l.c \
$(SRC_DIR)ft_strlen.c \
$(SRC_DIR)ft_str_misc.c \
$(SRC_DIR)ft_str_mod.c \
$(SRC_DIR)ft_str_n.c \
$(SRC_DIR)get_next_line.c \
$(SRC_DIR)ft_printf_fun.c \
$(SRC_DIR)ft_printf_hex.c \
$(SRC_DIR)ft_printf_nb.c \
$(SRC_DIR)ft_printf_ptr.c \
$(SRC_DIR)ft_printf_uns.c \
$(SRC_DIR)ft_printf_fd.c \
$(SRC_DIR)ft_split_base.c \
$(SRC_DIR)ft_split_unbase.c \
$(SRC_DIR)ft_split_utils.c \
$(SRC_DIR)ft_split_fun.c \
$(SRC_DIR)ft_split_fun2.c \
$(SRC_DIR)ft_epur.c \
$(SRC_DIR)ft_strlen_misc.c \
$(SRC_DIR)ft_str_occ.c \
$(SRC_DIR)ft_has_only.c \
$(SRC_DIR)ft_split_epured.c \
$(SRC_DIR)ft_free.c \
$(SRC_DIR)ft_fd.c \
$(SRC_DIR)ft_str_misc_2.c \
$(SRC_DIR)ft_strncpy.c \
$(SRC_DIR)ft_strlcpy.c \
$(SRC_DIR)ft_strcpy.c 

all : ${NAME}

${NAME} : ${OBJS} #${INC} ${SRCS}
	# ${CC} ${FLAGS} -c ${SRCS} -include ${INC}
	ar rc $@ ${OBJS}

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean :
	${RM} ${OBJS}
	$(RM) -r $(OBJ_DIR)


fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all fclean clean re