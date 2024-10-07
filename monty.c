#include "monty.h"

/**
 * execute_opcode - executes the appropriate function for the given opcode
 * @opcode: the operation code to be executed
 * @stack: double pointer to the top of the stack
 * @line_number: current line number in the script
 *
 * This function matches the provided opcode with the correct function
 * and executes it. If the opcode is not recognized, an error is printed
 * and the program exits with failure.
 */
void execute_opcode(char *opcode, stack_t **stack, unsigned int line_number)
{
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
	{"pint", pint},
	{"pop", pop},
	{"swap", swap},
	{"add", add},
	{"nop", nop},
	{"sub", sub},
        {NULL, NULL}
    };

    int i;
    for (i = 0; instructions[i].opcode != NULL; i++)
    {
        if (strcmp(opcode, instructions[i].opcode) == 0)
        {
            instructions[i].f(stack, line_number);
            return;
        }
    }
    fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}

/**
 * main - entry point of the Monty interpreter
 * @argc: argument count
 * @argv: argument vector
 *
 * This function opens the provided file, reads each line, and processes
 * the opcodes one by one. If the number of arguments is incorrect, or if
 * there's an issue opening the file, it prints an error and exits with failure.
 * It also frees allocated memory before exiting.
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
    FILE *file;  /* Declare all variables at the beginning */
    char *line;  
    stack_t *stack = NULL;  
    unsigned int line_number = 0;
    char *opcode;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Allocate a buffer for reading the line */
    line = malloc(1024);
    if (!line)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 1024, file) != NULL)
    {
        line_number++;
        opcode = strtok(line, " \n");
        if (opcode)
        {
            execute_opcode(opcode, &stack, line_number);
        }
    }

    /* Free allocated memory and close the file */
    fclose(file);
    free(line);
    while (stack)  /* Free the stack */
    {
        stack_t *temp = stack;
        stack = stack->next;
        free(temp);
    }

    return 0;
}

