NAME= ft_containers
SRCS= main.cpp common.cpp test_list.cpp test_stack.cpp test_vector.cpp test_queue.cpp test_map.cpp
OBJS= $(addprefix srcs/, $(SRCS:.cpp=.o))
CC= clang++
CFLAGS= -Wall -Wextra -Werror -std=c++98
HEADER= -I includes

.cpp.o:
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.cpp=.o)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all	
.PHONY: all clean fclean re
