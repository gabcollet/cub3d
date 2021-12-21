# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fousse <fousse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2021/12/21 16:23:25 by fousse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
# INCS_FLAGS has all the -I that are needed. (-Imlx, -Ilibft, etc.)
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
C_ALL			= $(CC) $(CFLAGS) $(INCS_FLAGS) $(INC_MLX)
C_OBJS			= $(C_ALL)
C_MAIN			= $(C_ALL) -g $(MAIN) $(OBJS) -lmlx $(C_FWRK) $(LIB_ALL) -o $(NAME)
C_LINUX_OBJS	= $(C_ALL) -O3
C_LINUX_MAIN	= $(C_ALL) -g $(MAIN) $(OBJS) -Lmlx_linux -lmlx_linux -lXext -lX11 -lm -lz $(LIB_LFT) -o $(NAME)
C_FWRK			= -framework OpenGL -framework AppKit
#

# Program
NAME	= cub3D 
#

# Directories
DIR_SRCS	= srcs
DIR_OBJS	= objs
DIR_INCS	= includes
DIR_MAINS	= mains
DIR_LFT		= libft
#

# Libraries and Includes
LIB_LFT		= $(DIR_LFT)/libft.a
INC_MLX		= -Imlx

INCS_ALL	= $(DIR_LFT) $(DIR_INCS)
INCS_FLAGS	= $(patsubst %,-I%,$(INCS_ALL))
#

# Makefiles
MK_LFT		= make -C $(DIR_LFT)
#

# Mains
MAIN		= $(DIR_MAINS)/cub3d.c
MAIN_PRAC	= $(DIR_MAINS)/main.c

# Headers
_HEADS	=	cub3d.h
HEADS		= $(patsubst %,$(DIR_INCS)/%,$(_HEADS))
#

# Sources and Objects
SRCS	= 	position.c size.c vector3d.c

_OBJS	= $(SRCS:.c=.o)
OBJS	= $(patsubst %,$(DIR_OBJS)/%,$(_OBJS))

$(DIR_OBJS)/%.o :  %.c
		$(C_OBJS) -c $< -o $@

vpath %.c $(DIR_SRCS)
#

all		: $(NAME)

$(NAME)	: $(HEADS) $(DIR_INCS) $(LIB_LFT) $(SRCS) $(MAIN) $(DIR_OBJS) $(OBJS)
		 $(C_MAIN)
		# $(shell echo "Compiling cub3d done!")
		# $(shell echo "Executable is : $(NAME)")

$(DIR_OBJS)	: 
		@ mkdir objs

$(LIB_LFT)	:
		@ $(MK_LFT) all

clean	: 
		@ rm -rf $(DIR_OBJS)
		@ $(MK_LFT) clean
		# $(shell echo "cub3d cleaned!")

fclean	: clean
		@ $(MK_LFT) fclean
		@ rm -rf $(NAME)

linux	: _linux $(NAME)

_linux	:
		$(eval C_OBJS=$(C_LINUX_OBJS))
		$(eval C_MAIN=$(C_LINUX_MAIN))
		$(eval INC_MLX=$(INC_MLX)_linux)

re		: fclean all

bonus	: $(NAME)

.PHONY	: all re clean fclean bonus linux
