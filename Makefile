# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:45:50 by cabouzir          #+#    #+#              #
#    Updated: 2023/05/24 14:57:52 by cabouzir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

LIBFT			=	libft.a

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c utils.c utils2.c

OBJS		=	${SRCS_NAMES:.c=.o}

# OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

# HEAD			=	-Ilibft/includes -Iincludes

CC				=	cc

CFLAGS			=	-g3 -Wall -Werror -Wextra

# MAKEFLAGS		=	--no-print-directory

all				:	${NAME}

$(NAME): $(OBJS)
#	make -C libft
#	mv libft/libft.a .
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[34;5mpipex\033[0m"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEAD)

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

bonus:
	make -C libft
	mv libft/libft.a .
	$(CC) $(CFLAGS) $(SRCS_B) ${LIBFT} ${HEAD} -o $(NAME)
	@echo "\033[39;5mpipex bonus\033[0m"

clean:
#	make clean -C libft
	rm -rf ${DIR_OBJS}
	rm -rf ${OBJS}

fclean:	clean
#	make fclean -C libft
	rm -rf ${LIBFT}
	rm -rf ${NAME}

re:	fclean all

stop:
	rm -f ${NAME}

.PHONY:	all clean fclean re bonus
# .SILENT: