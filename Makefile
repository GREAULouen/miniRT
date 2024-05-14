CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = miniRT

SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes
LIB_DIR = ${INCLUDES_DIR}/lib

SRCS =	main.c
OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}

LIBFT_DIR = ${LIB_DIR}/libft
LIBFT = libft.a
INCLUDE_LIBFT = -L${LIBFT_DIR} -lft

MLX42_DIR = ${LIB_DIR}/MLX42
LIBMLX42 = libmlx42.a

LIBS = ${INCLUDE_LIBFT} -L. ${MLX42_DIR}/${LIBMLX42} -ldl -lglfw -pthread -lm

all : ${NAME}

${NAME} : ${OBJS} ${LIBFT} ${LIBMLX42}
	@$(CC) $(CFLAGS) ${LIBS} ${OBJS} -o ${NAME} -lreadline

${OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR}
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

${OBJ_DIR} :
	@mkdir -p ${OBJ_DIR}

${LIBFT} :
	@git submodule update --init
	@make -sC ${LIBFT_DIR} all

${LIBMLX42} :
	@git submodule update --init
	@cmake ${LIB_DIR}/MLX42 -B ${MLX42_DIR} && make -C ${MLX42_DIR} -j4

clean :
	@rm -f ${OBJS}
	@make -sC ${LIBFT_DIR} clean

fclean : clean
	@rm -f ${NAME}
	@make -sC ${LIBFT_DIR} fclean

re : fclean all

.PHONY: all clean fclean re
