all:
	gcc -m32 -g -fsanitize=address main.c cmd_processing/* builder/builder.c builder/file_manager.c builder/instruction_parser.c interpretator/interpretator.c interpretator/file_manager.c -o vm