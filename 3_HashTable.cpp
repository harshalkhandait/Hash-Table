#include<stdio.h>
#include<stdlib.h>
#define MAX 10

struct node{
    int data;
    struct node *next;
};
struct hashset{
    struct node *arr[MAX];
};
int hashFunction(int value);
int isEmpty(struct node *head[]);
int isElementOf(struct node *head[], int x);
void displayData(struct node *head[]);
int getSize(struct node *head[]);
void doInsert(struct node *head[],int data);
void build(int arr[],int n,struct node *head[]);
void getUnion(struct node *Set1[],struct node *Set2[],struct node *head[]);
void getIntersection(struct node* Set1[],struct node * Set2[],struct node *head[]);
void getDifference(struct node* Set1[],struct node * Set2[],struct node *head[]);
int checkSubset(struct node *Set1[],struct node *Set2[]);
int main(){
    struct hashset S,P,unionS,intersectionS,differenceS;//making 5 sets.
    for(int i=0;i<MAX;i++){//starting node of every set hashed value to NULL
      S.arr[i]=NULL;
      P.arr[i]=NULL;
      unionS.arr[i]=NULL;
      intersectionS.arr[i]=NULL;
      differenceS.arr[i]=NULL;
    }
    displayData(S.arr);
    printf("\n");
    //make set S
    doInsert(S.arr,5);
    doInsert(S.arr,2);
    doInsert(S.arr,5);
    doInsert(S.arr,7);
    doInsert(S.arr,11);
    doInsert(S.arr,14);
    doInsert(S.arr,24);
    displayData(S.arr);
    printf("\n");
    int arr[] = {11,22,33,33,44,55,44};
    build(arr,7,P.arr);//make set P
    displayData(P.arr);
    printf("\n");
    getUnion(S.arr,P.arr,unionS.arr);//argument passed set1 and set2 return set3
    displayData(unionS.arr);
    printf("\n");
    getDifference(S.arr,P.arr,differenceS.arr);//argument passed set1 and set2 return set3
    displayData(differenceS.arr);
    printf("\n");
    if(checkSubset(S.arr,P.arr))//argument passed set1 and set2 return int value
        printf("Second Hash is subset \n");
    else
        printf("Second Hash is not subset \n");

}
int hashFunction(int value){
    return (value % MAX);
}
int isEmpty(struct node *head[]){
    for(int i=0;i<MAX;i++){
        if(head[i]!=NULL){
            return 1;
        }
    }
    return 0;
}
int isElementOf(struct node *head[], int x){
    int index = hashFunction(x);
    struct node *temp = head[index];
    while(temp != NULL){
        if(temp->data == x)
            return 1;
        temp =temp->next;
    }
    return 0;
}
void displayData(struct node *head[]){
    for(int i=0;i<MAX;i++){
        if(head[i] != NULL){
            struct node * temp = head[i];
            while(temp != NULL){
                printf("%d ", temp->data);
                temp = temp->next;
            }
        }
    }
}
int getSize(struct node *head[]){
    int sizeofHash = 0;
    for(int i=0;i<MAX;i++){
        if(head[i] != NULL){
            struct node * temp = head[i];
            while(temp != NULL){
                sizeofHash++;
                temp=temp->next;
        }
    }
}
return sizeofHash;
}
void doInsert(struct node *head[],int data){
    if(isElementOf(head,data)){
        return;
    }
    struct node *newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    struct node *temp;
    temp = head[(hashFunction(data))];
    if(temp!=NULL){
        while(temp->next!=NULL){
        temp=temp->next;
        }
        temp->next=newnode;
    }else{
        head[(hashFunction(data))]=newnode;
    }
}
void build(int arr[],int n,struct node *head[]){
    int i=0;
    for(i=0;i<n;i++){
        doInsert(head,arr[i]);
    }
}
void getUnion(struct node *Set1[],struct node *Set2[],struct node *head[]){
    int size_set1 = getSize(Set1);
    int size_set2 = getSize(Set2);
    for(int i=0;i<MAX;i++){
        if(Set1[i]==NULL){
            continue;
        }else{
            struct node *temp = Set1[i];
            while(temp!=NULL){
              doInsert(head,temp->data);
              temp = temp->next;
            }
        }
    }
    for(int i=0;i<MAX;i++){
        if(Set2[i]==NULL){
            continue;
        }else{
            struct node *temp=Set2[i];
            while(temp!=NULL){
              doInsert(head,temp->data);
              temp = temp->next;
            }
        }
    }
}
void getIntersection(struct node* Set1[],struct node * Set2[],struct node *head[]){
    for(int i=0;i<MAX;i++){
        if(Set1[i]==NULL){
            continue;
        }else{
            struct node * temp=Set1[i];
            while(temp!=NULL){
                if(isElementOf(Set2,temp->data)){
                    doInsert(head,temp->data);
                }
                temp=temp->next;
            }
        }
    }
}
void getDifference(struct node* Set1[],struct node * Set2[],struct node *head[]){
    for(int i=0;i<MAX;i++){
        if(Set1[i]==NULL){
            continue;
        }else{
            struct node * temp=Set1[i];
            while(temp!=NULL){
                if(!isElementOf(Set2,temp->data)){
                    doInsert(head,temp->data);
                }
                temp=temp->next;
            }
        }
    }
}
int checkSubset(struct node *Set1[],struct node *Set2[]){
    for(int i=0;i<MAX;i++){
        if(Set1[i]==NULL){
            continue;
        }else{
            struct node *temp=Set1[i];
            while(temp!=NULL){
               if(!isElementOf(Set2,temp->data)){
                return 0;
                }
                temp = temp->next;
            }
        }
    }
    return 1;
}
