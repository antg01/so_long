NAME = so_long
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBC = ar rcs
SRCS = $(addprefix src/, main.c init.c utils.c utils_bis.c parser.c parser_bis.c key_events.c key_events_utils.c render.c animate.c animate_bis.c path_validity.c path_validity_bis.c path_validity_utils.c check_error.c)
OBJS = ${SRCS:.c=.o}
PRINTF_SRC = $(addprefix ft_printf/, ft_printf.c convert_base.c print_hex.c print_number.c print_str.c)
PRINTF_OBJ := $(PRINTF_SRC:%.c=%.o)
GNL_SRC = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
GNL_OBJ := $(GNL_SRC:%.c=%.o)

MLX_DIR = mlx

all: ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -I${MLX_DIR} -Iincludes -c $< -o $@

${NAME}: ${OBJS} ${GNL_OBJ} ${PRINTF_OBJ}
	${CC} ${CFLAGS} $^ -L${MLX_DIR} -lmlx -framework OpenGL -framework AppKit -o ${NAME}

debug: ${OBJS} ${GNL_OBJ} ${PRINTF_OBJ}
	${CC} ${CFLAGS} -fsanitize=address $^ -L${MLX_DIR} -lmlx -framework OpenGL -framework AppKit -o ${NAME}

clean:
	${RM} ${OBJS} ${GNL_OBJ} ${PRINTF_OBJ}

fclean: clean
	@if [ -f ${MLX_DIR}/Makefile ]; then \
		make -C ${MLX_DIR} clean; \
	fi
	${RM} ${NAME}

mlx:
	@if [ ! -f ${MLX_DIR}/Makefile.gen ]; then \
		cd ${MLX_DIR} && ./configure; \
	fi
	@if [ -f ${MLX_DIR}/Makefile.gen ]; then \
		make -C ${MLX_DIR}; \
	fi

re: fclean all

.PHONY : all clean fclean re mlx

