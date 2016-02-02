#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum { false, true } bool;
struct node{
    char *data;
    struct node *next;
};

void destructor(struct node **head){
    if (head != NULL){
        struct node *temp = *head;

        while (temp -> next != NULL){
          struct node *next_temp = temp -> next;
          free(temp -> data);
          free(temp);
          temp = next_temp;
        }
        if (temp -> next == NULL){
          free(temp->data);
          free(temp);
        }
    }
}

void insert(struct node **head, char *data){
    struct node *next;
    next = (struct node *) malloc(sizeof(struct node));
    next -> data = malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(next->data, data);
    struct node *traverse = *head;

    if (*head == NULL){
        *head = next;
        next -> next = NULL;
    }
    else{
        if (strcmp(traverse->data, data) > 0){
            next -> next = *head;
            *head = next;
        }
        else {
            while (traverse -> next && strcmp(traverse -> next -> data, data) < 0){
                traverse = traverse -> next;
            }
            if (traverse -> next == NULL){
                traverse -> next = next;
                next -> next = NULL;
            }
            else{
                next -> next = traverse -> next;
                traverse -> next = next;
            }
        }
    }
}

void deleteNode(struct node **head, char *data){
    if (*head != NULL){
        if (strcmp((*head) -> data, data) == 0){
            struct node *tempNode = *head;
            *head = (*head) -> next;
            free(tempNode->data);
            free(tempNode);
        }
        else {
            struct node *temp = *head;
            while (temp -> next != NULL && strcmp(temp -> next -> data, data) != 0){
                temp = temp -> next;
            }
            if( temp -> next != NULL){
              struct node *tempNode = temp -> next;
              temp -> next = temp -> next -> next;
              free(tempNode->data);
              free(tempNode);
            }

        }

    }
}

int main(int argc, const char * argv[]){
    if(argc != 4){
        printf("num of variable is wrong.. Try again later!");
        return 1;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");

    char line[256];
    struct node *head1;
    if (fp != NULL){
        head1 = NULL;
        while (fscanf(fp, "%s", line) == 1){
            insert(&head1, line);
        }
    }
    else {
        printf("File is invalid!\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    fp = fopen(argv[2], "r");
    struct node *head2;
    if(fp != NULL){
        head2 = NULL;
        while (fscanf(fp, "%s", line) == 1){
            insert(&head2, line);
        }
    }
    else{
        printf("File is invalid!");
        fclose(fp);
        return 1;
    }

    struct node *traverse = head2;

    while (traverse != NULL){
        deleteNode(&head1, traverse -> data);
        traverse = traverse -> next;
    }
    fclose(fp);
    fp = fopen(argv[3], "w");

    traverse = head1;
    while (traverse != NULL){
        fprintf(fp, "%s\n", traverse -> data);
        traverse  = traverse -> next;
    }

    fclose(fp);
    destructor(&head1);
    destructor(&head2);

    return 0;
}
