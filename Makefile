# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcollet <gcollet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 15:31:26 by sfournie          #+#    #+#              #
#    Updated: 2022/01/20 19:07:43 by gcollet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
# INCS_FLAGS has all the -I that are needed. (-Imlx, -Ilibft, etc.)
CC				= gcc
CFLAGS			= -Wall -Wextra
C_ALL			= $(CC) $(CFLAGS) $(INCS_FLAGS) $(INC_MLX)
C_OBJS			= $(C_ALL) -g
C_MAIN			= $(C_ALL) -g $(MAIN) $(OBJS) -lmlx $(C_FWRK) $(LIB_LFT) -o $(NAME)
C_LINUX_OBJS	= $(C_ALL) -O3 -g
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
MAIN		= $(DIR_MAINS)/main.c
#

# Headers
_HEADS	=	cub3d.h cub3d_struct.h
HEADS		= $(patsubst %,$(DIR_INCS)/%,$(_HEADS))
#

# Sources and Objects
SRCS	= 	game.c map.c map_utils.c interface.c\
			parse.c parse_map.c parse_utils.c parse_wall.c\
			parse_map_id.c parse_cub_id.c\
			position.c rotation.c size.c\
			vector3d.c math_utils.c math_angles.c\
			image.c mlx.c textures.c\
			color.c color_trgb.c color_utils.c\
			draw.c minimap.c\
			background.c\
			animation.c time.c\
			collision.c intersection.c intersection_utils.c\
			raycast.c\
			object.c init_object.c\
			door.c door_utils.c animation_door.c\
			player.c gun.c enemy.c\
			input.c

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
		$(eval INC_MLX=$(INC_MLX))

color	: _color _linux $(NAME)

_color	:
		$(eval MAIN=$(MAIN_COLOR))

re		: fclean all

re_linux : fclean linux

bonus	: $(NAME)

signature : 
	@echo "                        								"
	@echo "                        .@@@@@@@@@@@@@@@@@@@@@@@@&."
	@echo "                      (@@@@@@@@POUTINE-STJEAN@@@@@@@@/"
	@echo "                   .&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*"
	@echo "                  .&../@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%"
	@echo "                  %%@#%@@@@@@@@@@@@@@@@@@@@@@@@@@#&. ./%*   ,&(@@&,*&/"
	@echo "     #(  &*       ##@/ %@@@@@@@(/&@@@@@@@@@@@&@@@@@*  *&  /%*@@@@@@@@.%,"
	@echo "   (#.&@@@//&/     @. @@#/.   .%@%@&@@@@@,       ,,/  &##.*@@@@@@@%.*@/@"
	@echo "  ,# .#@@@@@@( *&@&@, .#*        (&%@@@@& /@@%. *@@* ,   (@@@@@@,,%,   &*"
	@echo "   & @*(/./&@@@/      *@@(  , .%@@%@@@@@@@@#.%&@@@&       %@@( (.    .&*"
	@echo "   .@,        *%.  *@@@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@#    ,/       .#%."
	@echo "     %#            ,.%@@@@@@@@@@@@@&/& @@@@@@@@@@@@@.          ,&("
	@echo "       *&(,           /(&@@@@@@@@@@@&@( &@@@@(/(/,          /&*"
	@echo "           ,#&/        /.  /&%%@@@@@@@@@@@@&,%           /@,"
	@echo "                /@(*      %@@@@@@@@@@@@@@@@@(@        .*&."
	@echo "                   /%&*     .@@@@@@@@@@@@@@@@&       ,&,"
	@echo "                    .%(      (((@@@@@@@@@@@@/&          .*%%(,"
	@echo "                *%#.         .  .,.(*,   ..              ,(%%%%#%&%#(*."
	@echo "            *&(*.      .,.                            /&@@@@@@@@@@@@@&%*#("
	@echo "     ##%&/*#&@@@@@&*                                    ..  ,#@@@@@@@@@@#.#"
	@echo "   /# (@@@@@@/. ,%/.         .#&&&#&       ((.              .*#/  .*%@*   &"
	@echo "   .@.     *&@#.        #@(.       ,#%&#* (/     ,@%(, *(.        .#,    &*"
	@echo "    .&.   &%       *&%.                *@@/          ,.    .#@&(       %#" 
	@echo "      ,@/ *   *%@*                                                .,#,"
	@echo "                        								"

.PHONY	: all re clean fclean bonus linux color
