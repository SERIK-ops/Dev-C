NAME = mst

RESULT = result.png

CC = gcc

RM = rm -rf

CFLAGS = -W -Wall -Wextra -O2 -g

CPPFLAGS = -I include/

LD_FLAGS = -lm

SRC = main.c			\
	  binary.c			\
	  binary_actions.c	\
	  cities.c			\
	  cities_actions.c	\
	  cities_load.c		\
	  pipes.c			\
	  solution.c
SRC := $(addprefix sources/, $(SRC))

OBJ = $(SRC:.c=.o)


$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LD_FLAGS)

draw:
	@ls output/output_cities.dat output/output_graph.dat > /dev/null
	@cp output/*.dat ./
	python resources/visualisation.py
	@$(RM) ./*.dat

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(RESULT)
	$(RM) output/*.dat

re: fclean all
