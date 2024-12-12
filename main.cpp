#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Stack structure definition
#define MAX_SIZE 100

typedef struct {
    double data[MAX_SIZE];
    int top;
} Stack;

// Function prototypes
void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, double value);
double pop(Stack *s);
double peek(Stack *s);
void printMenu();
void processIns(Stack *stack, char instruction);

int main() {
    Stack stack;
    initStack(&stack);

    printf("Welcome to the Reverse Polish Notation (RPN) Calculator!\n");
    printf("........................................................\n");
    printMenu();

    char instruction;
    while (1) {
        printf("\nEnter Instruction : ");
        scanf(" %c", &instruction);

        if (instruction == 'q') {
            printf("Thank you for using the RPN Calculator!.\n");
            break;
        }

        processIns(&stack, instruction);
    }

    return 0;
}

// Initializing  the stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check whether the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if the stack is full
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Push a value onto the stack
void push(Stack *s, double value) {
    if (isFull(s)) {
        printf("Error: Stack is Full! Cannot push more elements.\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// Pop a value from the stack
double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Stack underflow! No elements to pop.\n");
        return 0; // Default value if stack is empty
    }
    return s->data[(s->top)--];
}

// Peek the top value of the stack
double peek(Stack *s) {  
    if (isEmpty(s)) {
        printf("Error: Stack is empty! Nothing to peek.\n");
        return 0; // Default value if stack is empty
    }
    return s->data[s->top];
}

// Display user instructions
void printMenu() {
    printf("Instructions:\n");
    printf("  ? - Enter a number and push it onto the stack.\n");
    printf("  + - Add  two numbers.\n");//Add the top two numbers on the stack
    printf("  - - Subtract two numbers.\n");//Subtract the top two numbers on the stack
    printf("  * - Multiply two numbers.\n");//Multiply the top two numbers on the stack
    printf("  / - Divide two numbers.\n");//Divide the top two numbers on the stack
    printf("  = - Display the result.\n");//Display the top number on the stack (without removing it
    printf("  q - exit from the program\n");
    printf("-------------------------------------------------------\n");
}

// Perform operations and handle instructions
void processIns(Stack *stack, char instruction) {
    double a, b, result;

    switch (instruction) {
        case '?': // Push a number onto the stack
            printf("Enter a number: ");
            double value;
            if (scanf("%lf", &value) == 1) {
                push(stack, value);
                printf("Pushed %.2f onto the stack.\n", value);
            } else {
                printf("Invalid input! Please enter a valid number.\n");
                while (getchar() != '\n'); // Clear invalid input
            }
            break;

        case '+': // Add the top two numbers
            if (stack->top >= 1) {
                b = pop(stack);
                a = pop(stack);
                result = a + b;
                push(stack, result);
                printf("Result: %.2f + %.2f = %.2f\n", a, b, result);
            } else {
                printf("Error: Not enough operands for addition.\n");
            }
            break;

        case '-': // Subtract the top two numbers
            if (stack->top >= 1) {
                b = pop(stack);
                a = pop(stack);
                result = a - b;
                push(stack, result);
                printf("Result: %.2f - %.2f = %.2f\n", a, b, result);
            } else {
                printf("Error: Not enough operands for subtraction.\n");
            }
            break;

        case '*': // Multiply the top two numbers
            if (stack->top >= 1) {
                b = pop(stack);
                a = pop(stack);
                result = a * b;
                push(stack, result);
                printf("Result: %.2f * %.2f = %.2f\n", a, b, result);
            } else {
                printf("Error: Not enough operands for multiplication.\n");
            }
            break;

        case '/': // Divide the top two numbers
            if (stack->top >= 1) {
                b = pop(stack);
                a = pop(stack);
                if (b != 0) {
                    result = a / b;
                    push(stack, result);
                    printf("Result: %.2f / %.2f = %.2f\n", a, b, result);
                } else {
                    printf("Error: Division by zero is undefined.\n");
                    push(stack, a);
                    push(stack, b);
                }
            } else {
                printf("Error: Not enough operands for division.\n");
            }
            break;

        case '=': // Display the top value of the stack
            if (!isEmpty(stack)) {
                printf("Top of stack: %.2f\n", peek(stack));
            } else {
                printf("Error: Stack is empty! Nothing to display.\n");
            }
            break;

        default: // Invalid instruction
            printf("Error: Invalid instruction '%c'. Please try again.\n", instruction);
            break;
    }
}
