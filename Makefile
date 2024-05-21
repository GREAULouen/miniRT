CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = miniRT

SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes
LIB_DIR = ${INCLUDES_DIR}/lib

LIBFT_DIR = ${LIB_DIR}/libft
LIBFT = libft.a
INCLUDE_LIBFT = -L${LIBFT_DIR} -lft

MLX42_DIR = ${LIB_DIR}/MLX42
LIBMLX42 = libmlx42.a

LIBS = ${INCLUDE_LIBFT} -L. ${MLX42_DIR}/${LIBMLX42} -ldl -lglfw -pthread -lm




UTILS_SRCS =	quit_utils.c				\
				object_type_utils.c			\
				object_type_misc.c			\
				parsing_utils.c
UTILS_OBJS =	${addprefix ${OBJ_DIR}/, ${notdir ${UTILS_SRCS:.c=.o}}}

PARSER_SRCS =	parser.c							\
				create_ambient_light.c				\
				create_camera.c						\
				create_spot_light.c					\
				create_plane.c						\
				create_sphere.c						\
				create_cylinder.c
PARSER_OBJS =	${addprefix ${OBJ_DIR}/, ${notdir ${PARSER_SRCS:.c=.o}}}

MAIN_SRCS =	main.c				\
			program_utils.c
MAIN_OBJS =	${addprefix ${OBJ_DIR}/, ${notdir ${MAIN_SRCS:.c=.o}}}


SRCS =	${MAIN_SRCS}			\
		${PARSER_SRCS}			\
		${UTILS_SRCS}
OBJS = ${addprefix ${OBJ_DIR}/, ${notdir ${SRCS:.c=.o}}}




all : ${NAME}

${NAME} : ${OBJS} ${LIBFT} ${LIBMLX42}
	@$(CC) $(CFLAGS) ${LIBS} ${OBJS} -o ${NAME} -lreadline



${MAIN_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR}
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

${PARSER_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/parsing/%.c | ${OBJ_DIR}
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@

${UTILS_OBJS}: ${OBJ_DIR}/%.o: ${SRC_DIR}/utils/%.c | ${OBJ_DIR}
	@$(CC) $(CFLAGS) -I$(INCLUDES_DIR) -c $< -o $@



${OBJ_DIR} :
	@mkdir -p ${OBJ_DIR}

${LIBFT} :
	@git submodule update --init --remote
	@make -sC ${LIBFT_DIR} all

${LIBMLX42} :
	@git submodule update --init --remote
	@cmake ${LIB_DIR}/MLX42 -B ${MLX42_DIR} && make -C ${MLX42_DIR} -j4

clean :
	@rm -f ${OBJS}
	@make -sC ${LIBFT_DIR} clean

fclean : clean
	@rm -f ${NAME}
	@make -sC ${LIBFT_DIR} fclean
	@git submodule update --init --remote

update_modules :
	@git submodule update --init --remote

re : fclean all

.PHONY: all clean fclean re
