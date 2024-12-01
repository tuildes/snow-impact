# Definindo variáveis
SRCS	= src
OBJS	= obj
OUT		= SNOW_IMPACT
CC	 	= gcc

# Flags de compilação e link
CFLAGS	= -g -c -Wall -Wextra -Werror -Wpedantic -Walloc-zero -Wduplicated-branches -Wduplicated-cond -Wformat=2 -Wshadow
LFLAGS	= -lm
AFLAGS 	= -lallegro -lallegro_font -lallegro_image -lallegro_ttf -lallegro_audio -lallegro_acodec -lallegro_primitives

# Encontrando os arquivos .c na pasta src
SRC_FILES = $(wildcard $(SRCS)/*.c)
# Gerando a lista de arquivos .o correspondentes
OBJ_FILES = $(SRC_FILES:$(SRCS)/%.c=$(OBJS)/%.o)

# Regra para compilar o programa final (executável)
$(OUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS) $(AFLAGS) -o $(OUT)

# Regra para compilar os arquivos .c em .o
$(OBJS)/%.o: $(SRCS)/%.c
	@mkdir -p $(OBJS) # Cria o diretório obj se não existir
	$(CC) $(CFLAGS) $< -o $@ # Compila os arquivos .c em .o

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(OBJS) $(OUT)

# Regra padrão para compilar tudo
all: $(OUT)