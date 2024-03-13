#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 5
long int state_count=1; //  arithmos state 
long int parent_count=0;//  arithmos epektasewn

struct status
{   int A[N];
    int g_n;//  g(n) cost katastasis
    struct status *next_srch_set;//epomeni katastasi sto metopo anazitisis
    struct status *next_cl_set;//epomeni katastasi kleistou sinolou
    struct status *parent;
    struct status *path;	                       
};
struct status *first_srch_set=NULL;//proti katastasi sto metopo anazitisis
struct status *last_srch_set=NULL;//teleutaia latastasi sto metopo anazitisis
struct status *first_cl_set=NULL;//proti katastasi kleistoy sinolou
struct status *last_cl_set=NULL;//teleutaia katastasi kleistoy sinolou

//ektupwsi katastasewn - apotelesmatwn
void print_res(struct status *st)
{   
    printf("<=========|RESULTS|=========>\n");
    struct status *tmp,*st1;
    int counter=1; // counter katastasewn
    int j;
    tmp=st;
    st1=st;
    while(tmp->parent!=NULL)
    {    tmp->parent->path=tmp;
        tmp=tmp->parent;
    }
    while(tmp!=st1)
    {   printf("H %d katastasi me kostos %d einai i eksis:",counter,tmp->g_n);
        for(j=0;j<N;j++)
        {   printf("%d ",tmp->A[j]);
        }
        printf("\n");
        tmp=tmp->path;
	counter++;
    }
    printf("H %d kai teliki katastasi me kostos %d einai i eksis:",counter,tmp->g_n);
    for(j=0;j<N;j++)
    {   printf("%d ",tmp->A[j]);
    }
    printf("\n");
}

//psaxnei to kleisto sunolo
int search_in_cl_set(int B[N])
{	 
    int flag=0,i;
    struct status *st;
    
    st=first_cl_set;
    while(st!=NULL)
    {   
	int flag2=1;
        for(i=0;i<N;i++)
        {   if (B[i]!=st->A[i])
            {   
                flag2=0;   
            }
        }
	if(flag2==1)
	{
		flag=1;
		break;
        }
        
        st=st->next_cl_set;
    } 
    return flag;   
}

//kanoume epektasi twn katastasewn-paidiwn
void children(struct status *st)
{   struct status *tmp;
    int i,j;

    for(i=1;i<N;i++)
    {   	tmp=(struct status *)malloc(sizeof(struct status));
		state_count++;
		
		tmp->g_n= st->g_n+ 1;

		tmp->parent=st;
		tmp->next_srch_set=NULL;
		tmp->next_cl_set=NULL;

		for(j=0;j<=i;j++)
			tmp->A[j]=st->A[i-j];
		for(j=i+1;j<N;j++)
			tmp->A[j]=st->A[j];
		
		if (first_srch_set==NULL)
		{   
			first_srch_set=tmp;
			last_srch_set=tmp;
		}
		else
		{   
			last_srch_set->next_srch_set=tmp;
			last_srch_set=tmp;
		}

    }
    if (first_cl_set==NULL)
    {   
        first_cl_set=st;
        last_cl_set=st;
    }
    else
    {   
        last_cl_set->next_cl_set=st;
        last_cl_set=st;
    }
    
}  

//briskei thn kaluterh pros epektash katastash
struct status *get_best_op(void)
{
	struct status *prev,*current,*st,*best_op;
    	int less_cost;
    	prev=NULL;
    	st=first_srch_set;
    	less_cost=st->g_n;
    	best_op=st;	

	while(st->next_srch_set!=NULL)
        {   current=st;
            st=st->next_srch_set;
            if (st->g_n < less_cost)
            {   less_cost=st->g_n;
                best_op=st;
                prev=current;
            }
        }
    
        if (prev!=NULL)
        {   prev->next_srch_set=best_op->next_srch_set;
            if (best_op->next_srch_set==NULL)
            {
                last_srch_set=prev;
            }
            best_op->next_srch_set=NULL;
        }
        else
        {   first_srch_set=best_op->next_srch_set;
            if (best_op->next_srch_set==NULL)
            {
                last_srch_set=NULL;
            }
            best_op->next_srch_set=NULL;
        }   
	return best_op;
}

//elegxos telikis katastasis
int check_end(struct status *st)
{   
    int i,k=1;
    for(i=0;i<N;i++)
    {   if (st->A[i]!=(i+1))
           k=0;
    }
    return(k);
}

//algorithmos UCS
void UCS(void)
{   
    struct status *tmp,*best_op,*st,*st1;
    int i,num;

    tmp=(struct status *)malloc(sizeof(struct status));// tmp = ARXIKI katastasi
    tmp->g_n=0;
    tmp->parent=NULL;
    tmp->next_srch_set=NULL;
    tmp->next_cl_set=NULL;
    tmp->path=NULL;
    
    for(i=0;i<N;i++)
    {    printf("Dwse enan arithmo kathe fora apo to 1 ews to 5:\n");
         scanf("%d",&num);
         tmp->A[i]=num;
    }
    first_srch_set=tmp;
    last_srch_set=tmp;
    printf("Given Sequence:");
    for(i=0;i<N;i++)
    {
        printf(" | %d",first_srch_set->A[i]);
    }
    printf("\n");
    int succ=0,end,flag;
    
    
    
    
    while(succ==0)
    {    
        if (first_srch_set==NULL)//elegxo an exei adiasei to metopo anazitisis
        {   printf("<======|SOLUTION NOT FOUND|======>\n");
            exit(-1);
        }
	 		        
        st1=get_best_op();
        if (search_in_cl_set(st1->A)==0)
        {     
            end=check_end(st1);
            if (end==1)
            {
		succ=1; 
                print_res(st1);
		    
	    }
	 
	    else 
	    {
		parent_count++;
                children(st1);
	    }
                    
            		          
        }
    }
}


int main()
{   
    
    UCS();
    
    printf("O arithmos twn epektasewn einai: %ld.\n",parent_count);
    printf("To sunoliko kostos twn epektasewn einai: %ld.\n",state_count);
}

