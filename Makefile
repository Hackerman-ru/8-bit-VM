all:
	gcc -g -fsanitize=address -m32 main.c interpretator.c cmd_processing/* builder/builder.c builder/file_manager.c builder/instruction_parser.c -o vm