//
// Created by kishore on 19/6/16. queue using two stacks
//
#include<iostream>
#include<stdio.h>
#include<conio.h>

class Stack {
private:
	int top;
	int arr[10];

public:
	Stack(){
		top = -1;
	}
	void push(int value){
		top++;
		arr[top] = value;
		printf("arr[%d] = %d\n ", top, arr[top]);
	}
	int pop(){
		top--;
		return arr[top + 1];
	}
};

class Queue {
private:
	Stack stack1;
	Stack stack2;
	int flag = 0;
public:
	
	void enQueue(int value){
		stack1.push(value);
	}
	int deQueue(){
		int i = 0;
		if (flag == 0){
			while (i < 10)
			{
				stack2.push(stack1.pop());
				i++;
			}
			flag = 1;
		}
		return stack2.pop();
	}
};

void main(){

	Queue q;// = new Queue();
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int i = 0;
	while (i < 10){
		printf("----");
		q.enQueue(arr[i++]);		
	}
	while (i > 0){
		printf("\nq.dequeue = %d", q.deQueue());
		i--;
	}
	
	_getch();
}