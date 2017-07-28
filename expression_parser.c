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

float istack[STACK_SIZE]; 
int itop = -1; 

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
	if(itop < STACK_SIZE) {
		istack[++itop] = item; 
	}
}

float fpop()
{
	if(itop >= 0) {
		return istack[itop--];
	}
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
	int i,j = 0;
	cstack[++ctop] = '#';

	for(i = 0;i<strlen(infix);i++) {
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
					cpop();//pop out (. 
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

	postfix[j++] = ' ';
	while(cstack[ctop] != '#') {
		postfix[j] = cpop();
		j++;
	}

	postfix[j]='\0';//null terminate string. 
}

//evaluates postfix expression
float evaluate(char *postfix){

	char ch;
	float operand1, operand2, value = 0;
	int i = 0;

	while( (ch = postfix[i++]) != '\0') {
		if(isdigit(ch)) {
			value = value*10 + ch - '0';
		}
		else if( ch == ' ') {
			fpush(value);
			value = 0;
		}
		else {
			operand2 = fpop();
			operand1 = fpop();

			switch(ch) {
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
	printf("Evaluated expression is: %f\n" , evaluate(postfix));
}

