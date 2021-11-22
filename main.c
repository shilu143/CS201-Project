//Shaurya PS Bisht -- 2020CSB1125
//Shilu Tudu --2020csb1126
//Tsering Wangzes -- 2020csb1136

/////CS201 Project - String Concatenation using Rope data structure


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len 2

struct Rope
{
    struct Rope* left;
    struct Rope* right;
    struct Rope* parent;
    char* text;
    int weight;
};

void create_rope(struct Rope **node, struct Rope *par, char a[], int l, int r)
{
    struct  Rope* temp = malloc(sizeof(struct Rope));
    temp->left=temp->right=NULL;
    temp->parent=par;
    if((r-l+1)>max_len)
    {
        temp->text=NULL;
        if((r-l)%2==0)
        {
            temp->weight=(r-l+2)/2;
            //printf("assigned weight %d\n", temp->weight);
        }
        else
        {
            temp->weight=(r-l+1)/2;
            //printf("assigned weight %d\n", temp->weight);
        }
        (*node)=temp;
        int m = (l+r)/2;
        create_rope(&((*node)->left), (*node), a, l, m);
        create_rope(&((*node)->right), (*node), a, m+1, r);
    }

    else
    {
        (*node)=temp;
        temp->weight=(r-l+1);
        //printf("\nassigned weight %d\n", temp->weight);
        int j =0;
        temp->text = (char*)malloc((r-l+1)*(sizeof(char)));
        //printf("---l and r are %d and %d\n", l,r);
        for(int i=l; i<=r; i++)
        {
            temp->text[j++]=a[i];
           // printf("%d", i);
        }
       // if(l==r){printf("%.1s", temp->text);}
       // else{printf("%.2s", temp->text);}
    }


}

void print(struct Rope* r)
{
    if(r==NULL)
    {
        return;
    }
    if(r->left==NULL && r->right==NULL)
        {
            if(r->weight==2)
            {
                printf("%.2s", r->text);
            }
            else if(r->weight==1)
            {
                printf("%.1s", r->text);
            }
        }
    print(r->left);
    print(r->right);

}

void concat(struct Rope **root3, struct Rope **root1, struct Rope **root2, int n1)
{
    struct Rope* tmp = malloc(sizeof(struct Rope));
    tmp->parent = NULL;
    tmp->left = (*root1);
    tmp->right = (*root2);

   (*root1)->parent= tmp;
   (*root2)->parent = tmp;

    tmp->weight = n1;

    tmp->text = NULL;
    (*root3 )= tmp;

}

char index_find(struct Rope* root, int i)
{
    if(root->left==NULL && root->right==NULL)
    {
        return root->text[i];
    }
    else
    {
        if(i>=root->weight)
        {
            i=i-(root->weight);
            index_find(root->right, i);
        }
        else if(i<root->weight)
        {
            index_find(root->left, i);
        }
    }
}

struct Rope* split(struct Rope **root, int i)
{
    struct Rope* temp= (*root);
    struct Rope* hold=NULL;
    int count=0;

    while(temp->left!=NULL)
    {
        //printf("\nloop and i is %d", i);
        if(i==0 && temp->left->left==NULL && temp->left->right==NULL)
        {

            //printf("\ncase0  case we are on %d and i is %d", temp->weight, i);
            struct Rope* new_par= NULL;
            if(count>0)
            {
                temp->right->parent=NULL;
                concat((&new_par),(&temp->right),(&hold), (temp->right->weight));
                temp->right=NULL;
                hold=new_par;
            }
            else
            {
                hold = temp->right;
                temp->right=NULL;
                hold->parent=hold->left=hold->right=NULL;
            }



            struct Rope* l = malloc(sizeof(struct Rope));
            struct Rope* r = malloc(sizeof(struct Rope));
            l->left=l->right=r->left=r->right=NULL;

            l->text= (char*)malloc((1)*(sizeof(char)));
            r->text= (char*)malloc((1)*(sizeof(char)));

            l->text[0]=temp->left->text[0];
           // printf("\nyoo %c\n", temp->left->text[0]);
            r->text[0]=temp->left->text[1];
            //printf("\nyoo %s\n", temp->left->text[1]);

            l->weight=r->weight=1;
            temp->left->text=NULL;
            //printf("\nyoo %s\n", temp->left->text);
            temp->left->weight=1;

            temp->left->left=l;
            temp->left->right=NULL;
            l->parent=temp->left;

            temp->left->left->parent=temp->parent;
            if(temp->parent->right==temp){temp->parent->right=temp->left->left;}
            else{temp->parent->left=temp->left->left;}

            struct Rope* new_par2= NULL;
            concat((&new_par2),(&r),(&hold), (1));
            return new_par2;
        }

        else if(i+1<temp->weight && i+1!=temp->weight)
        {
           // printf("\ncase1  case we are on %d and i is %d", temp->weight, i);
           // printf("\nfirst %d", temp->weight);
            while(temp->left!=NULL &&  i+1<temp->weight)
                {


                    //printf("\nsecond %d %d", temp->weight, i+1);
                    if(i==0 && temp->left->left==NULL && temp->left->right==NULL)
                    {
                        break;
                    }
                    else if(count==0)
                    {
                        if(temp->right!=NULL)
                        {
                            //printf("\nthird a %d", temp->weight);
                            temp->weight = i+1;
                            hold = temp->right;
                            temp->right=NULL;
                            hold->parent=NULL;
                            temp=temp->left;
                            (count)++;
                        }
                        else
                        {
                            temp->weight = i+1;
                            temp=temp->left;
                        }


                    }
                    else
                    {
                       // printf("\nthird b %d", temp->weight);
                        struct Rope* new_par= NULL;
                        struct Rope* temp22= NULL;

                        concat((&new_par),(&temp->right),(&hold), (temp->right->weight));
                        temp->right=NULL;
                        hold = new_par;
                      //  if(temp->parent->weight>temp->weight){temp->parent->weight=temp->weight;}

                        temp22= temp;
                        temp=temp->left;

                        temp22->parent->left=temp22->left;
                        temp22->left->parent= temp22->parent;

                        temp22->left=temp22->parent=NULL;
                        free(temp22);
                        (count)++;


                    }


                }
        }
        else if(i+1==temp->weight)
        {
            //printf("\ncase2  case we are on %d and i is %d", temp->weight, i);
            if(count==0)
            {
                hold = temp->right;
                temp->right=NULL;
                hold->parent=NULL;
                return hold;
            }
            else if(count>0)
            {
                //printf("correct");
                struct Rope* new_par= NULL;
                temp->right->parent=NULL;
                concat((&new_par),(&temp->right),(&hold), (temp->right->weight));
                temp->right=NULL;

                temp->parent->left=temp->left;
                temp->left->parent=temp->parent;

                temp->parent=temp->left=NULL;
                free(temp);
                return new_par;
            }

        }
        else if(i>=temp->weight && temp->right->left!=NULL)
        {
           // printf("\ncase3  case we are on %d and i is %d", temp->weight, i);
            i=i-(temp->weight);
            temp=temp->right;

        }
        else if(i>=temp->weight && temp->right->left==NULL)
        {

           // printf("\ncase4 case we are on %d and i is %d", temp->weight, i);
            struct Rope* l = malloc(sizeof(struct Rope));
            struct Rope* r = malloc(sizeof(struct Rope));
            l->left=l->right=r->left=r->right=NULL;

            l->text= (char*)malloc((1)*(sizeof(char)));
            r->text= (char*)malloc((1)*(sizeof(char)));

            l->text[0]=temp->right->text[0];
           // printf("\nyoo %c\n", temp->left->text[0]);
            r->text[0]=temp->right->text[1];
           // printf("\nyoo %c\n", temp->left->text[1]);

            l->weight=r->weight=1;
            temp->right->text=NULL;
            //printf("\nyoo %s\n", temp->right->text);
            temp->right->weight=1;

            temp->right->left=l;
            temp->right->right=NULL;
            l->parent=temp->right;

            struct Rope* new_par2= NULL;
            concat((&new_par2),(&r),(&hold), (1));
            return new_par2;
        }

    }
}


struct Rope* delete_rope(struct Rope **root, int i, int j)
{
    struct Rope* temp = (*root);
    int n = j-(i+1);
   // printf("\n %d", n);
    //printf("\n split");
    struct Rope* temp1 = split((root),i);

   // printf("\n");
    //print(temp1);

    //printf("\n\n\n split2");
    struct Rope* temp2 = split((&temp1),n);
    //printf("\n");
    //print(temp2);

    struct Rope* final= NULL;
    concat((&final), (root), (&temp2), ((temp1)->weight));

    return final;

}

void insert(struct Rope **root, struct Rope** to_add, int i)
{
    struct Rope* right_side = split(root, i);
    struct Rope* new_parent1=NULL;

    concat((&new_parent1), root, (to_add), (*root)->weight);

    struct Rope* new_parent2=NULL;
    concat((root), (&new_parent1), (&right_side), new_parent1->weight);

}


int main()
{
   char temp;
   printf("Enter a string: ");
   char str[100];
   scanf("%[^\n]s",str);
   scanf("%c", &temp);
   int length = strlen(str);
   struct Rope* main=NULL;

   create_rope((&main), NULL, str, 0 , length-1);

   int choice;
   printf("\nEnter the respective number to perform that function\n1: Concatenate other string at its end\n2: Enter index to find corresponding character");
   printf("\n3: Insert a string at a particular index of current string\n4: Delete characters in string after index i till j\n5: Quit\n-->");

   scanf("%d", &choice);
   while(choice!=5 && choice<5)
   {
       if(choice==2)
       {
           printf("Enter the index to get character (0 to %d): ", length-1);
           int x;
           scanf("%d", &x);
           char c = index_find(main, x);
           printf("\nCharacter is %c", c);
       }
       else if(choice==1)
       {
           char buffer;
           printf("Enter a string: ");
           char str420[100];
           scanf("%c", &buffer);
           scanf("%[^\n]s",str420);
           scanf("%c", &buffer);
           int length420 = strlen(str420);
           struct Rope* to_concat=NULL;
           create_rope((&to_concat), NULL, str420, 0 , length420 - 1);

           struct Rope* parent_for_concat=NULL;

           concat((&parent_for_concat), (&main), (&to_concat), length);
           (main) = (parent_for_concat);
           print(main);
           length = length + length420;

       }

       else if(choice==3)
       {
           char buffer;
           printf("Enter a string: ");
           char str420[100];
           scanf("%c", &buffer);
           scanf("%[^\n]s",str420);
           scanf("%c", &buffer);
           int length420 = strlen(str420);
           struct Rope* to_insert=NULL;
           create_rope((&to_insert), NULL, str420, 0 , length420 - 1);

           printf("Enter the index you want it to be inserted at: ");
           int x;
           scanf("%d", &x);
           insert((&main), (&to_insert), x);
           length = length + length420;

           print(main);
       }

       else if(choice==4)
       {
           printf("Enter the index i and j for deletion: ");
           int x,y;
           scanf("%d %d", &x, &y);
           struct Rope* justhold = delete_rope((&main), x,y);
           print(justhold);


       }




       printf("\n\nEnter the respective number to perform that function\n1: Concatenate other string at its end\n2: Enter index to find corresponding character");
       printf("\n3: Insert a string at a particular index of current string\n4: Delete characters in string after index i till j\n5: Quit\n-->");
       scanf("%d", &choice);

   }







}
