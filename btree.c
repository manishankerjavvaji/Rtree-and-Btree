#include<stdio.h>
#include<stdlib.h>
struct node{
	char a[3];
	struct node *ptr[4];
};
struct node *get_node()
{
	struct node *temp;
	temp = (struct node *) malloc(sizeof(struct node));
	int i;
	for(i = 0; i < 3; i++){
		temp->a[i] = 0;
		temp->ptr[i] = NULL;
	}
	temp->ptr[3] = NULL;
	return temp;
}
void push(struct node **stack, struct node *temp, struct node ***stackptr){
	if(*stackptr){
		(*stackptr)++;
		printf("pushed more than 1");
	} else {
		*stackptr = stack;
	}
	**stackptr = temp;
}
struct node *pop(struct node **stack, struct node ***stackptr){
	struct node *temp;
	if(*stackptr == NULL){
		temp = NULL;
	} else {
		temp = **stackptr;
		if(stack == *stackptr){
			*stackptr = NULL;
		} else {
			(*stackptr)--;
		}
	}
	return temp;
}

void insert_node(struct node **btree, char data){
	int i;
	int k;
	int j;
	struct node *splitnode;
	struct node *splitold;
	struct node **stack;
	stack = (struct node **) malloc(sizeof(struct node *) * 20);
	for(i=0; i < 20; i++){
		*(stack + i) = NULL;
	}
	struct node **stackptr;
	struct node *temp;
	stackptr = NULL;
	splitnode = NULL;
	splitold = NULL;
	if(*btree==NULL){
		*btree = get_node();
		(*btree)->a[0] = data;
	} else {
		temp = *btree;
		while(temp){
			for(i = 0; i < 3; i++){
				if(temp->a[i] == 0 || temp->a[i] > data){
					break;
				}
			}
			push(stack, temp, &stackptr);
			temp = temp->ptr[i];
		}
		while (data != 0){
			if(stackptr == NULL){
				splitnode = get_node();
				splitnode->a[0] = data;
				splitnode->ptr[0] = *btree;
				splitnode->ptr[1] = splitold;
				*btree = splitnode;
				data = 0;
				break;
			}
			temp = pop(stack, &stackptr);
			for(i = 2; i >= 0; i--){
				if(temp->a[i] != 0 && temp->a[i] < data){
					break;
				}
			}
			if(temp->a[2] == 0){
				for(j = 1; j > i; j--){
					temp->a[j+1] = temp->a[j];
				}
				temp->a[j+1] = data;
				temp->ptr[j+1] = splitold;
				data = 0;
			} else {
				splitnode = get_node();
				if(i<1){
					for(k=1; k<3; k++){
						splitnode->a[k-1] = temp->a[k];
						splitnode->ptr[k-1] = temp->ptr[k];

						temp->a[k] = 0;
						temp->ptr[k] = NULL;
					}
					splitnode->ptr[k-1] = temp->ptr[k];
					temp->ptr[k] = NULL;
					for(j=i+1; j < 1; j++){
						temp->a[j+1] = temp->a[j];
					}
					temp->a[i+1] = data;
					temp->ptr[i+2] = splitold;
				} else{
					k=0;
					i++;
					for(j = 2; j <= 3; j++){
						if( i == j){
							splitnode->a[j-2] = data;
							splitnode->ptr[j-2+1] = splitold;
							k++;
						}else {
							splitnode->a[j-2] = temp->a[j-k];
							splitnode->ptr[j-2+1] = temp->ptr[j-k+1];
						}
						temp->a[j-k] = 0;
						temp->ptr[j-k] = NULL;
					}
					splitnode->ptr[0] = temp->ptr[2];
					temp->ptr[2] = NULL;
				}
				data = temp->a[1];
				temp->a[1] = 0;
				splitold = splitnode;
			}
		}
	}
	splitnode = NULL;
	splitold = NULL;
	stackptr =NULL;
	free(stack);
}
void search(struct node *btree, char data){
	int i;
	if(btree == NULL){
		printf("no data");
		return;
	}
	for(i=0; i<3; i++){
		if(btree->a[i] == data){
			printf("%c_", data);
			return;
		} else if(btree->a[i] == 0 || btree->a[i] > data){
			printf("%c-",btree->a[0]);
		       	search(btree->ptr[i], data);
			return;
		}
	}
	search(btree->ptr[3], data);
}

int main(void)
{
	int n;
	char data;
	struct node *btree;
	btree = NULL;
	scanf("%d", &n);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%c", &data);
		insert_node(&btree, data);
	}
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%c", &data);
		search(btree, data);
	}
	return 0;
}

