#include <stdio.h> 
#include <ctype.h>
#include <string.h> 

#define STACK_SIZE 32

/*
 * Step 1 − scan the expression from left to right 
 * Step 2 − if it is an operand push it to stack 
 * Step 3 − if it is an operator pull operand from stack and perform operation 
 * Step 4 − store the output of step 3, back to stack 
 * Step 5 − scan the expression until all operands are consumed 
 * Step 6 − pop the stack and perform operation
 */

char cstack[STACK_SIZE]; 
int ctop = -1; 

float fstack[STACK_SIZE]; 
int ftop = -1; 

void cpush(char item)
{
	cstack[++ctop] = item; 
} 

char cpop()
{
	return cstack[ctop--]; 
} 

void fpush(float item)
{
	if(ftop < STACK_SIZE) {
		fstack[++ftop] = item; 
	}
}

float fpop()
{
	float ret = 0;
	if(ftop >= 0) {
		ret = fstack[ftop--];
	}
	else {
		puts("stack is empty");
	}
	return ret;
}


/* returns precedence of operators */
int precedence(char symbol)
{
	int retval = 0;
	switch(symbol) {
		case '+': 
		case '-':
			retval = 2; 
			break; 
		case '*': 
		case '/':
			retval = 3; 
			break; 
		case '^': 
			retval = 4; 
			break; 
		case '(': 
		case ')': 
		case '#':
			retval = 1; 
			break; 
		default:
			retval = 0;
	} 
	return retval;
}

/* check whether the symbol is operator? */
int isOperator(char symbol)
{

	switch(symbol) {
		case '+': 
		case '-': 
		case '*': 
		case '/': 
		case '^': 
		case '(': 
		case ')':
			return 1; 
			break; 
		default:
			return 0; 
	} 
}

/* converts infix expression to postfix */
void convert(char infix[],char postfix[])
{
	int i,j = 0;
	cstack[++ctop] = '#';

	for( i=0; i<strlen(infix); i++ ) {
		if(isdigit(infix[i])) {
			postfix[j] = infix[i];
			j++;
		}
		else {
			if( i!=0 && isdigit(infix[i-1])) {
				postfix[j] = ' ';
				j++;
			}
			if(infix[i] == '(') {
				cpush(infix[i]);
			}
			else {
				if(infix[i] == ')') {
					while(cstack[ctop] != '(') {
						postfix[j] = cpop();
						j++;
					}
					cpop(); /* pop out (. */
				}
				else {
					if(precedence(infix[i]) > precedence(cstack[ctop])) {
						cpush(infix[i]);
					}
					else {
						while( precedence(infix[i]) <= precedence(cstack[ctop]) ) {
							postfix[j] = cpop();
							j++;
						}
						cpush(infix[i]);
					}
				}
			}
		}
	}

	while(cstack[ctop] != '#') {
		postfix[j] = cpop();
		j++;
	}

	postfix[j]='\0';
}

/* 
 * evaluates postfix expression
 */
float evaluate(char *postfix)
{
	int i = 0;
	float operand1, operand2, value = 0;

	for( i=0; postfix[i] != '\0'; i++) {
		if(isdigit(postfix[i])) {
			value = value*10 + postfix[i] - '0';
		}
		else if( postfix[i] == ' ' && isdigit(postfix[i-1])) {
			fpush(value);
			value = 0;
		}
		else {
			operand2 = fpop();
			operand1 = fpop();

			switch( postfix[i] ) {
				case '+':
					fpush(operand1+operand2);
					break;
				case '-':
					fpush(operand1-operand2);
					break;
				case '*':
					fpush(operand1*operand2);
					break;
				case '/':
					fpush(operand1/operand2);
					break;
				default:
					printf("unkonw operand %c\n", postfix[i]);
			}
		}
	}
	return fstack[ftop];
}


int main(int argc, char** argv)
{ 
	char infix[128] = "1*(2+3)";
	char postfix[256]; 
	if(argc > 1) {
		strcpy(infix, argv[1]);
	}
	convert(infix, postfix); 

	printf("Infix expression is  : %s\n" , infix);
	printf("Postfix expression is: %s\n" , postfix);
	printf("Evaluation is        : %f\n" , evaluate(postfix));
}

