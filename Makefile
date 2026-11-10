CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = includes

LIBDIR = libs
LIBS = -lGL -lglfw -lGLEW

LIBSTRDIR = $(LIBDIR)/libstr
LIBSTR = $(LIBSTRDIR)/libstr.h

VPATH = sources:sources/callbacks:sources/utils
SRCS =	main.c ftsglWindow.c ftsglRenderer.c ftsglQuad.c ftsglVertex.c ftsglVector.c ftsglShader.c ftsglBufferObject.c ftsglVao.c utils.c \
		error_callback.c key_callback.c window_callback.c

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

NAME = libftsgl

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o : %.c | $(OBJDIR) $(LIBSTR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES) -I $(LIBSTRDIR)

$(LIBSTR) : | $(LIBSTRDIR)
	git clone https://github.com/julienPR86/libstr.git $(LIBSTRDIR)

$(LIBDIR) :
	mkdir -p $@

$(LIBSTRDIR) : | $(LIBDIR)
	mkdir -p $@

$(OBJDIR) :
	mkdir -p $@

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
