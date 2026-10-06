
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
RED     = \033[0;31m
RESET   = \033[0m


NAME = philo


CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g 


SRCS = main.c \
	   source/init_table.c \
	   source/monitor.c \
	   source/parse.c \
	   source/routine.c \
	   source/utils.c  \
	   source/should_stop.c\
	   source/helper_routine.c


OBJS = $(SRCS:.c=.o)


all: $(NAME)
	@printf "$(GREEN)✅ Build complete!\n$(RESET)"

%.o : %.c include/philo.h
	@printf "$(BLUE)[Compiling] $<\n$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@printf "$(YELLOW)[Linking Target: $(NAME)]\n$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	@rm -f $(OBJS)
	@printf "$(RED)🧹 Object files cleaned.\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)🧹 Executable cleaned.\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
