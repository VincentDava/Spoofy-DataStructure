#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
struct data{
	char name[50];
	char title[50];
	int hour;
	int min;
	int sec;
	data *left,*right;
};
struct datac{
	char name[50];
	char title[50];
	int hour;
	int min;
	int sec;
};
data *createdata(char name[],char title[],int hour,int min,int sec){
	data *newdata = (data *)malloc(sizeof(data));
	newdata->hour=hour;
	newdata->min=min;
	newdata->sec=sec;
	strcpy(newdata->name,name);
	strcpy(newdata->title,title);
	newdata->left=newdata->right=NULL;
	return newdata;
}
data *insert(data *curr,char name[],char title[],int hour,int min, int sec){

	if(curr==NULL){
		return createdata(name,title,hour,min,sec);
	}else{
		if(strcmp(title,curr->title)<=0){
			curr->left=insert(curr->left,name,title,hour,min,sec);
		}else if(strcmp(title,curr->title)>0){
			curr->right= insert(curr->right,name,title,hour,min,sec);
		}
		return curr;
	}
}
int search(data *curr,char todel[]){
	if(curr == NULL){
		return 0;
	}else{
		if(strcmp(todel,curr->title)<0){
			return search(curr->left,todel);
		}else if(strcmp(todel,curr->title)>0){
			return search(curr->right,todel);
		}else{
			return 1;
		}
	}
}
void inorder(data *curr){
	if(curr==NULL){
		return;
	}else{
		inorder(curr->left);
		printf("|%s      |%s      |%d:%d:%d|\n",curr->title,curr->name,curr->hour,curr->min,curr->sec);
		inorder(curr->right);
	}
}
void nonnorder(data *curr){
	if(curr==NULL){
		return;
	}else{
		nonnorder(curr->right);
		printf("|%s      |%s      |%d:%d:%d|\n",curr->title,curr->name,curr->hour,curr->min,curr->sec);
		nonnorder(curr->left);
	}
}
data *findpredecessor(data *curr){
	data *temp = curr->left;
	while(temp->right!= NULL){
		temp=temp->right;
	}
	return temp;
}
data *remove(data *curr,char todel[]){
		if(curr==NULL){
		return NULL;
		}else{
		if(strcmp(todel,curr->title)<0){
			curr->left=remove(curr->left,todel);
		}else if(strcmp(todel,curr->title)>0){
			curr->right= remove(curr->right,todel);
		}else{

			if(curr->right == NULL && curr->left ==NULL){
			free(curr);
			curr=NULL;
			return NULL;
		}else if(curr->right ==NULL && curr->left !=NULL || curr->right !=NULL && curr->left ==NULL ){

			data *childpengganti;
			if(curr->right !=NULL){
				childpengganti = curr->right;
			}else if(curr->left !=NULL){
				//jika ada di kiri
				childpengganti = curr->left;
			}
			free(curr);
			curr = NULL;
			return childpengganti;
		}else{
			data *predecessor = findpredecessor(curr);
			curr->hour = predecessor->hour;
			curr->min=predecessor->min;
			curr->sec=predecessor->sec;
			strcpy(curr->name,predecessor->name);
			strcpy(curr->title,predecessor->title);
			curr->left=remove(curr->left,predecessor->title);
			return curr;
		}

		return curr;
	}
}
}
void menu(){
	printf("========================\n");
	printf("         Spoofy        \n");
	printf("========================\n");
	printf("1. Insert New Music !\n");
	printf("2. View My Music List !\n");
	printf("3. Delete Music !\n");
	printf("4. Exit!\n");
	printf("========================\n");
	printf("Input [1-4]:");
}
int main(){
	data *root=NULL;
	do{
	char name[30];
	char title[35];
	int hour;
	int min;
	int sec;
	int a=0;
	int cari=0;
	menu();
	int digit=0;
	scanf("%d",&a);
	getchar();
	if(a==1){
		do{
			digit=0;
		printf("Insert Artist [3-20 characters | not contains number]: ");
		scanf("%s",name);
		getchar();
		for(int i=0;i<strlen(name);i++){
			if(isdigit(name[i])){
				digit=1;
			}
		}
		}while((strlen(name)<3||strlen(name)>25)||digit==1);
		do{
			printf("Insert Title [3-25 characters | unique]: ");
			scanf("%[^\n]",title);
			getchar();
		}while(strlen(title)<3||strlen(title)>25);
		do{
			printf("Input Duration Hour [0-24]:");
			scanf("%d",&hour);
			getchar();
		}while(hour<0||hour>24);
		do{
			printf("Input Duration Minute [0-58]:");
			scanf("%d",&min);
			getchar();
		}while(min<0||min>59);
		int minsec=0;
			do{
				minsec=0;
			printf("Input Duration Second [0-59]:");
			scanf("%d",&sec);
			getchar();
			if(hour==0&&min==0&&sec==0){
				printf("The duration min. 1 second\n");
				minsec=1;
			}
		}while((sec<1||sec>59)||minsec==1);
		root=insert(root,name,title,hour,min,sec);
	}else if(a==2){
		int back=0;
		int c=0;
		do{
		printf("View Music\n");
		printf("1. Sort By Ascending\n");
		printf("2. Sort By Descending\n");
		printf("3. Exit\n");
		scanf("%d",&c);
		getchar();
		if(c==1){
			if(root==NULL){
				printf("NO DATA!\n");
			}
			if(root!=NULL){
		printf("|Title          | Artist             |Duration |\n");
		printf("===================================================\n");
		}
			inorder(root);
		}else if (c==2){
			if(root==NULL){
				printf("NO DATA!\n");
			}
		if(root!=NULL){
			printf("|Title          | Artist             |Duration |\n");
			printf("===================================================\n");

		}
		nonnorder(root);
		}else if(c==3){
			back=1;
		}	
	}while(back==0);
	}else if(a==3){
			char todel[50];
		do{
		inorder(root);
		printf("Input Music Title to be deleted [0 to cancel]: ");
		scanf("%s",todel);
		if(todel[0]=='0'){
			break;
		}
		}while(search(root,todel)==0);
		root=remove(root,todel);
	}else if(a==4){
		return 0;
	}
	}while(true);
}
