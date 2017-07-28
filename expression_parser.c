#include<stdio.h> 
#include<string.h> 

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

int istack[STACK_SIZE]; 
int itop = -1; 

void push(char item)
{
	cstack[++ctop] = item; 
} 

char pop()
{
	return cstack[ctop--]; 
} 

/* returns precedence of operators */
int precedence(char symbol)
{

	switch(symbol) {
		case '+': 
		case '-':
			return 2; 
			break; 
		case '*': 
		case '/':
			return 3; 
			break; 
		case '^': 
			return 4; 
			break; 
		case '(': 
		case ')': 
		case '#':
			return 1; 
			break; 
	} 
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
	int i,symbol,j = 0;
	cstack[++ctop] = '#';

	for(i = 0;i<strlen(infix);i++) {
		symbol = infix[i]; 
		if(isOperator(symbol) == 0) {
			postfix[j] = symbol;
			j++;
		}
		else {
			if(symbol == '(') {
				push(symbol);
			}
			else {
				if(symbol == ')') {
					while(cstack[ctop] != '(') {
						postfix[j] = pop();
						j++;
					}
					pop();//pop out (. 
				}
				else {
					if(precedence(symbol) > precedence(cstack[ctop])) {
						push(symbol);
					}
					else {
						while( precedence(symbol) <= precedence(cstack[ctop]) ) {
							postfix[j] = pop();
							j++;
						}
						push(symbol);
					}
				}
			}
		}
	}

	while(cstack[ctop] != '#') {
		postfix[j] = pop();
		j++;
	}

	postfix[j]='\0';//null terminate string. 
}

void push_int(int item)
{
	if(itop < STACK_SIZE) {
		istack[++itop] = item; 
	}
}

char pop_int()
{
	if(itop >= 0) {
		return istack[itop--];
	}
}

//evaluates postfix expression
int evaluate(char *postfix){

	char ch;
	int i = 0,operand1,operand2;

	while( (ch = postfix[i++]) != '\0') {
		if(isdigit(ch)) {
			push_int(ch-'0');
		}
		else {
			operand2 = pop_int();
			operand1 = pop_int();

			switch(ch) {
				case '+':
					push_int(operand1+operand2);
					break;
				case '-':
					push_int(operand1-operand2);
					break;
				case '*':
					push_int(operand1*operand2);
					break;
				case '/':
					push_int(operand1/operand2);
					break;
				default:
					printf("unkonw operand %c\n", ch);
			}
		}
	}
	return istack[itop];
}


int main(int argc, char** argv)
{ 
	char infix[128] = "1*(2+3)";
	char postfix[256]; 
	if(argc > 1) {
		strcpy(infix, argv[1]);
	}
	convert(infix, postfix); 

	printf("Infix expression is: %s\n" , infix);
	printf("Postfix expression is: %s\n" , postfix);
	printf("Evaluated expression is: %d\n" , evaluate(postfix));
}

