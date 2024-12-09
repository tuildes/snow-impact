# [VARS] Varias de compilacao
SRCS	= src
OBJS	= obj
INCL	= includes
OUT		= SNOW_IMPACT
CC	 	= gcc

# [VARS] Arquivos aldo de compilacao
SRC_FILES = $(wildcard $(SRCS)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRCS)/%.c=$(OBJS)/%.o)

# [FLAGS] Flags de compilação
CFLAGS	= -g -c -Wall -Wextra -Werror -Wpedantic -Walloc-zero -Wduplicated-branches -Wduplicated-cond -Wformat=2 -Wshadow -I$(INCL)
LFLAGS	= -lm
AFLAGS 	= -lallegro -lallegro_font -lallegro_image -lallegro_ttf -lallegro_primitives

$(OUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS) $(AFLAGS) -o $(OUT)

$(OBJS)/%.o: $(SRCS)/%.c
	@mkdir -p $(OBJS) # Cria o diretório obj se não existir
	$(CC) $(CFLAGS) $< -o $@ # Compila os arquivos .c em .o

# [Regra] Limpar os arquivos gerados
clean:
	rm -rf $(OBJS) $(OUT)

# [Regra] Compilar tudo
all: $(OUT)