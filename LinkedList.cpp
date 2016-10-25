/*

A linked list implementation using smart pointers

Program handles 5 types of queries (for linked list of size N) :
1.	Insert at beginning of list	- O(1) complexity
2.	Insert at end of list - O(N) complexity
3.	Delete at beginning of list - O(1) complexity
4.	Delete at end of list - O(N) complexity
5.	Print linked list - O(N) complexity

*/	

#include <memory>
#include <iostream>
#include <algorithm>


struct node{
	int data;
	std::shared_ptr<node> next;

	node():next(nullptr),data(0){}
	node(int val):next(nullptr),data(val){}
	node(int val, std::shared_ptr<node> Next):next(Next),data(val){}
};


void insertAtBeg(std::shared_ptr<node>& head){
	int val;
	std::cout<<"\nEnter value:";
	std::cin>>val;
	std::shared_ptr<node> newHead = std::make_shared<node>(val,head);
	head = newHead;
}

void insertAtEnd(std::shared_ptr<node>& head){
	int val;
	std::cout<<"\nEnter value:";
	std::cin>>val;

	std::shared_ptr<node> newRear = std::make_shared<node>(val);
	std::shared_ptr<node> headCopy = head;
	std::weak_ptr<node> tracker = headCopy;

	if(tracker.expired()){
		head = newRear;
	}
	else{
		headCopy = head;
		tracker = (headCopy->next);

		while(!tracker.expired()){
			headCopy = headCopy->next;
			tracker = headCopy->next;
		}

		headCopy->next = newRear;		
	}

}


void deleteAtBeg(std::shared_ptr<node>& head){
	std::weak_ptr<node> tracker = head;

	if(!tracker.expired()){
		head = head->next;
	}
	
}


void deleteAtEnd(std::shared_ptr<node>& head){
	std::weak_ptr<node> tracker = head;
	std::shared_ptr<node> headCopy;

	if(!tracker.expired()){
		tracker = head->next;

		if(!tracker.expired()){
			headCopy = head;
			tracker = (headCopy->next->next);

			while(!tracker.expired()){
				headCopy = headCopy->next;
				tracker = headCopy->next->next;
			}

			headCopy->next = nullptr;
		}
		else{
			head = nullptr;
		}
	}
}


void print(std::shared_ptr<node> head){
	std::weak_ptr<node> tracker = head;
	std::cout<<"\nLinked list contents are: ";

	while(!tracker.expired()){
		std::cout<<(head->data)<<" -> ";
		head = head->next;
		tracker = head;
	}

	std::cout<<"NULL\n";
	return ;
}


void processQuery(int queryType){
	static std::shared_ptr<node> head;
	if(queryType == 1){
		insertAtBeg(head);
	}
	else if(queryType == 2){
		insertAtEnd(head);
	}
	else if(queryType == 3){
		deleteAtBeg(head);
	}
	else if(queryType == 4){
		deleteAtEnd(head);
	}
	else if(queryType == 5){
		print(head);
	}
}


void input(){
	int queryType,queries;
	bool interactive = false;
	std::cout<<"\nEnter number of queries(0 for interactive session): ";
	std::cin>>queries;
	queries = std::max(queries,0);
	interactive = (queries==0);

	if(interactive)std::cout<<"\nInteractive mode. Press Ctrl + C to quit \n\n";

	while(interactive || queries>0){
		std::cout<<"\nEnter query type: ";
		std::cin>>queryType;
		processQuery(queryType);
		queries--;
	}

}


int main(){
	input();
	return 0;
}