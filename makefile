C_FILES = 					 \
	bounded-buffer.c 	 \
	co-editor.c				 \
	dispatcher.c			 \
	main.c						 \
	producer.c				 \
	read-config.c			 \
	screen-manager.c   \
	unbounded-buffer.c \

FLAGS = -Wall -g -lpthread -std=gnu99

OUT_FILE = ex3.out

RUN_ARGS = conf.txt

O_FILES = $(C_FILES:.c=.o)

all: $(OUT_FILE)

$(OUT_FILE): $(O_FILES) 
	gcc $(FLAGS) $(O_FILES) -o $(OUT_FILE)

.c.o:
	gcc $(FLAGS) -c $< -o $@

run: $(OUT_FILE)
	./$(OUT_FILE) $(RUN_ARGS)

clean:
	$(RM) *.o *~ $(OUT_FILE)
