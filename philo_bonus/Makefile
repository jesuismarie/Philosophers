NAME = philo_bonus

BUILD = ./objs_bonus

SRC = ./srcs_bonus

SRCS  = $(shell find $(SRC) -name '*.c')

OBJS  = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

INCS = -I./includes_bonus

HEADER = ./includes_bonus/philo_bonus.h

FLAGS = -Wall -Wextra -Werror  #-g -fsanitize=address

CC = cc

all: $(BUILD) $(NAME)

$(BUILD)/%.o: $(SRC)/%.c $(HEADER) Makefile
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

${NAME}: ${OBJS}
	$(CC) $(FLAGS) $(OBJS) $(INCS) -o ${NAME}
	@echo "Philo bonus created 😇"

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re