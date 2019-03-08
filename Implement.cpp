#include "Implement.h"
#include <iostream>
#include <cstdio>
#include <cctype>
using namespace std;
#define SIZE 1000
char stack[SIZE];
int top= -1; // initial

// general for prefix and postfix
void push(int x)
{
	top++;
	stack[top]=x;
}
void pop()
{
	top--;
}
int int_top()
{
	return stack[top];
}
//======================================================================
	// some function for prefix
void pre_pushin(char c_element)
{
	top++;
	stack[top]= c_element;
}
char pre_popout()
{
	char x;
	x= stack[top];
	top--;
	return x;
}
int pre_priority(char c_element)
{
	switch(c_element){
		case '#':
		case ')': return 1;
		break;
		case '+': 
		case '-': return 2;
		break;
		case '*': 
		case '/': return 4;
		break;
	}
}
int isOp(char c_element)
{
	switch(c_element){
		case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
			return 1;
		break;
		default:return 0;
	}
}

void reverse(char array[SIZE*2])
{
	int i,j;
	char temp[1000];
	for(i=0,j=strlen(array)-1;j+1!=0;++i,--j){
		temp[i]=array[j];
	}
	temp[i]='\0';
	strcpy(array,temp);
}

// convert infix into prefix

void Implement::infix2Prefix(Expression &prefix, const Expression &infix)
{
	char pre_infix[SIZE]={}, pre_prefix[SIZE]={}, ch=' ';
	int i,j=0;
	// read
	for(i=0;i<infix.sz;i++) pre_infix[i]=infix.data[i];
	i=0;
	// prefix rules
	pre_pushin('#');
	reverse(pre_infix);
	while((ch=pre_infix[i++]) !='\0'){
		if(isOp(ch)==0) pre_prefix[j++]=ch; //運算元
		else {
			if(ch==')') pre_pushin(ch); // )  push
		    else if(ch=='('){ //pop stack中所有運算子直到遇到)
				while(stack[top] !=')') pre_prefix[j++]= pre_popout();
				pre_popout();
			}
			else{ // 運算子
				if(pre_priority(ch) > pre_priority(stack[top])) pre_pushin(ch);
				else{
					while(pre_priority(ch) < pre_priority(stack[top])) pre_prefix[j++]= pre_popout();
					pre_pushin(ch);
				}
			}
		}
	}
	
	while(stack[top] !='#'){
		pre_prefix[j]= pre_popout(); //pop until empty
		j++;
	}
	pre_prefix[j]= '\0'; //保持string型態
	
	reverse(pre_prefix);
	prefix= pre_prefix;
	// initial
	void clear();
	top= -1;
	stack[SIZE]={};
}
int Implement::evalPrefix(const Expression &prefix)
{
	char pre_prefix[SIZE];
    int i,a,b,ans;
    for(i=prefix.sz-1;i>=0;i--) pre_prefix[prefix.sz-1-i]= prefix.data[i]; 
    for(i=0;i<prefix.sz;i++){ 
        if((pre_prefix[i]>=48)&&(pre_prefix[i]<=57)){ //0-9
            push(pre_prefix[i]-48);
        }
		else if(pre_prefix[i]=='+'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(b+a);
        }
		else if(pre_prefix[i]=='-'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(b-a);
        }
		else if(pre_prefix[i]=='*'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(b*a);
        }
		else if(pre_prefix[i]=='/'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(b/a);
        }
		else{
			// do nothing
		}
    }
    ans= int_top();
    return ans;
}
//======================================================================
	// some function for postfix
void post_pushin(char c_element)
{
	stack[++top]= c_element;
}
char post_popout()
{
	return stack[top--]; 
}
int post_priority(char c_element)
{
	switch(c_element){
		case '#': return 0;
		case '(': return 1;
		case '+': return 2;
		case '-': return 2;
		case '*': return 3;
		case '/': return 3;
	}
}
// convert infix into postfix
void Implement::infix2Postfix(Expression &postfix, const Expression &infix)
{
	char post_infix[SIZE]={}, post_postfix[SIZE]={}, ch=' ';
	int i,j=0;
	// read
	for(i=0;i<infix.sz;i++) post_infix[i]=infix.data[i];
	i=0;
	// postfix rules
	post_pushin('#');
	while((ch=post_infix[i++]) !='\0'){
		if(isalnum(ch)) post_postfix[j++]=ch; //運算元
		else if(ch=='(') post_pushin(ch); // (  push
		else if(ch==')'){ //pop stack中所有運算子直到遇到(
			while(stack[top] !='(') post_postfix[j++]= post_popout();
			post_popout(); 
		}
		else{ // 運算子
			while(post_priority(ch) <= post_priority(stack[top])) post_postfix[j++]= post_popout();
			post_pushin(ch);
		}
	}
	
	while(stack[top] !='#'){
		post_postfix[j]= post_popout(); //pop until empty
		j++;
	}
	post_postfix[j]= '\0'; //保持string型態

	postfix= post_postfix;
	// initial state
	void clear();
	top= -1;
	stack[SIZE]={};
}
int Implement::evalPostfix(const Expression &postfix)
{
	char po_postfix[SIZE];
    int i,a,b,ans;
    for(i=0;i<postfix.sz;i++) po_postfix[i]= postfix.data[i];
    for(i=0;i<postfix.sz;i++){
        if((po_postfix[i]<=57)&&(po_postfix[i]>=48)){ //0-9
            push(po_postfix[i]-48);
        }
		else if(po_postfix[i]=='+'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(a+b);
        }
		else if(po_postfix[i]=='-'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(a-b);
        }
		else if(po_postfix[i]=='*'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(a*b);
        }
		else if(po_postfix[i]=='/'){
            b= int_top();
            pop();
            a= int_top();
            pop();
            push(a/b);
        }
		else{
			// do nothing
		}
    }
    ans= int_top();
    return ans;
}
