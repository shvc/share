#include <stdio.h> 
#include <ctype.h>
#include <assert.h>
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
	if(ctop < STACK_SIZE) {
		cstack[++ctop] = item; 
	}
	else {
		puts("stack overflow");
	}
} 

char cpop()
{
	char ret = 0;
	if(ctop >= 0) {
		ret = cstack[ctop--];
	}
	else {
		puts("stack is empty");
	}
	return ret;
} 

void fpush(float item)
{
	if(ftop < STACK_SIZE) {
		fstack[++ftop] = item; 
	}
	else {
		puts("stack overflow");
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

	for( i=0; infix[i]!='\0'; i++ ) {
		if(isdigit(infix[i])) {
			postfix[j++] = infix[i];
		}
		else {
			if( i!=0 && isdigit(infix[i-1])) {
				postfix[j++] = ' ';
			}
			if(infix[i] == '(') {
				cpush(infix[i]);
			}
			else {
				if(infix[i] == ')') {
					while(cstack[ctop] != '(') {
						postfix[j++] = cpop();
					}
					cpop(); /* pop out (. */
				}
				else {
					if(ctop == -1 || precedence(infix[i]) > precedence(cstack[ctop])) {
						cpush(infix[i]);
					}
					else {
						while( precedence(infix[i]) <= precedence(cstack[ctop]) ) {
							postfix[j++] = cpop();
						}
						cpush(infix[i]);
					}
				}
			}
		}
	}
	if(isdigit(postfix[j-1])) {
		postfix[j++] = ' ';
	}

	while(ctop != -1) {
		postfix[j++] = cpop();
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

void test(char* infix, char* postfix) 
{
	strcpy(infix, "2+2-1-1*2/2");
	convert(infix, postfix);
	assert(2 == evaluate(postfix));

	strcpy(infix, "(2+2)/2*2-1");
	convert(infix, postfix);
	assert(3 == evaluate(postfix));

	strcpy(infix, "2+2/2*2");
	convert(infix, postfix);
	assert(4 == evaluate(postfix));


	strcpy(infix, "2+2+2*(2-1)");
	convert(infix, postfix);
	assert(6 == evaluate(postfix));

}

int main(int argc, char** argv)
{ 
	char infix[128];
	char postfix[256]; 

	test(infix, postfix);

	if(argc > 1) {
		strcpy(infix, argv[1]);
	}
	convert(infix, postfix); 

	printf("Infix expression is   :[%s]\n" , infix);
	printf("Postfix expression is :[%s]\n" , postfix);
	printf("Evaluation is         :[%.2f]\n" , evaluate(postfix));
}

