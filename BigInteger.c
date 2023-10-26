#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"

void display2(struct BigInteger b1) 
{ 
    struct node *temp=b1.list;
    if (b1.sign==0)
    {
        printf("-");
    }
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

struct BigInteger allocate(int cap) {
    struct BigInteger b ;
    b.size = 0;
    b.sign = 1;
    b.cap = cap;
    b.list = NULL;
    return b;
}

int length (struct node *b)
{
    int l=0;
    while (b)
    {
        l++;
        b=b->next;
    }
    return l;
}

struct node* NewNode(int val)
{
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=val;
    newnode->next=NULL;
    return newnode;
}

struct BigInteger initialize(char *str) 
{ 
    struct BigInteger b = allocate (strlen(str));
    int len = strlen(str);
    b.size = len;
    if (str[0] == '-') 
    {
        b.sign = 0;
        b.size--; // Decrease size if the number is negative
    }
    
    for (int i = 0; i < len; i++) 
    {
        char c = str[len - i -1];
        if (c >= '0' && c <= '9') 
        {
            int d = c - '0';
            struct node *temp = (struct node*)malloc(sizeof(struct node));
            temp->data = d;
            temp->next = b.list;
            b.list = temp; // Update the linked list
        }
    }
    return b;
}

struct node* reverse(struct node *head) 
{
    struct node *curr = head;
    struct node *nxt = NULL;
    struct node *prev = NULL;
    
    while (curr) {
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    
    return prev;
}

struct BigInteger dupl(struct BigInteger b1) 
{
    struct BigInteger ret;
    ret.cap = b1.cap;
    ret.size = b1.size;
    ret.sign = b1.sign;
    ret.list = NULL; 
    struct node *current = b1.list;
    struct node *prev = NULL;
    struct node *newDigits = NULL;

    while (current) 
    {
        struct node *newNode = NewNode(current->data);
        if (!prev) 
        {
            ret.list = newNode;  
        } 
        else 
        {
            prev->next = newNode; 
        }
        prev = newNode;
        current = current->next;
    }

    return ret;
}

int is_null(struct BigInteger a)
{
    struct node *n = duplicate(a.list);
    while (n)
    {
        if (n->data != 0)
        {
            return 1;
        }
        n=n->next;
    }
    return 0;
}

int comp(struct BigInteger b1,struct BigInteger b2)
{
    struct node *head1=reverse(duplicate(b1.list));
    struct node *head2=reverse(duplicate(b2.list));
    while (head1->data == 0)
    {
        head1=head1->next;
    }
    while (head2->data == 0)
    {
        head2=head2->next;
    }
    while (head1)
    {
        if (head1->data > head2->data)
        {
            return 1;
        }
        else if (head1->data < head2->data)
        {
            return 2;
        }
        else 
        {
            return 0;
        }
        head1=head1->next;
        head2=head2->next;
    }
}

struct node* duplicate(struct node *b1) 
{
    struct node *list = NULL; 
    struct node *current = b1;
    struct node *prev = NULL;
    struct node *newDigits = NULL;

    while (current) 
    {
        struct node *newNode = NULL;
        newNode = NewNode(current->data);
        if (!prev) 
        {
            list= newNode;  
        }
        else 
        {
            prev->next = newNode; 
        }
        prev = newNode;
        current = current->next;
    }

    return list;
}

void push(struct node** head, int data)
{
    struct node* new_node = NewNode(data);
    new_node->next = (*head);
    (*head) = new_node;
}

struct node* empty_list(int size)
{
    struct node* head = NULL;
    while (size--)
        push(&head, 0);
    return head;
}

struct BigInteger add(struct BigInteger b1,struct BigInteger b2)
{
    if (!b1.size || (is_null(b1)==0))
    {
        return b2;
    }
    if (!b2.size || (is_null(b2)==0))
    {
        return b1;
    }
    
    struct BigInteger res;
    struct node *itr=NULL; 
    struct node *resnode=NULL;
    res.size=0;
    res.sign=1;
    res.list=NULL;
    if (b1.sign == 0 && b2.sign == 1)
    {
        b1.sign=1;
        res=sub(b2,b1);
        return res;
    }
    if (b1.sign == 1 && b2.sign== 0)
    {
        b2.sign=1;
        res=sub(b1,b2);
        return res;
    }
    int l1=length(b1.list);
    int l2=length(b2.list);
    struct node *n1=NULL,*n2=NULL;
    if (l1>l2)
    {
        n1=duplicate(reverse(b1.list));
        n2=duplicate(reverse(b2.list));
    }
    else
    {
        n1=duplicate(reverse (b2.list));
        n2=duplicate(reverse (b1.list));
    }
    while ((n1!=NULL) && (n2!=NULL))
    {
        res.size++;
        int d=n1->data+n2->data;
        if (d>9)
        {
            d-=10;
            if (!n1->next)
            {
                n1->next=NewNode(1);
            }
            else
            {
                n1->next->data++;
            }    
        }
        if (!(resnode))
        {
            resnode=NewNode(d);
            itr=resnode;
            n1=n1->next;
            n2=n2->next;

        }
        else
        {
            itr->next=NewNode(d);
            itr=itr->next;
            n1=n1->next;
            n2=n2->next;
        }
    }
    while (n1)
    {
        res.size++;
        itr->next=NewNode(n1->data);
        itr=itr->next;
        n1=n1->next;
    }
    while (n2)
    {
        res.size++;
        itr->next=NewNode(n2->data);
        itr=itr->next;
        n2=n2->next;
    }
    res.cap=res.size;
    if (b1.sign == 0 && b2.sign == 0)
    {
        res.sign=0;
    }
    res.list=reverse(resnode);
    return res;
}

struct BigInteger sub(struct BigInteger b1,struct BigInteger b2)
{
    if (!b1.size || (is_null(b1)==0))
    {
        b2.sign = 0;
        return b2;
    }
    if (!b2.size || (is_null(b2)==0))
    {
        return b1;
    }
    struct BigInteger res;
    struct node *resnode=NULL;
    res.size=0;
    res.sign=1;
    res.list=NULL;
    if (b1.sign == 0 && b2.sign == 1)
    {
        b1.sign=1;
        res=add(b2,b1);
        res.sign=0;
        return res;
    }
    if (b2.sign == 0)
    {
        b2.sign=1;
        res=add(b1,b2);
        return res;
    }
    int l1=length(b1.list);
    int l2=length(b2.list);
    struct node *h1=NULL;
    struct node *h2=NULL;
    if (l1<l2)
    {
        h1=reverse(b2.list);
        h2=reverse (b1.list);
    }
    else if (l1==l2)
    {
        if (comp(b1,b2)==2)
        {
            h1=reverse (b2.list);
            h2=reverse(b1.list);
            res.sign=0;
        }
        else
        {
            h1=reverse (b1.list);
            h2= reverse ( b2.list);
        } 
    }
    else
    {
        h1=  reverse ( b1.list);
        h2= reverse( b2.list);
    }
    struct node *itr = NULL; //(struct node)malloc(sizeof(struct node));
    while ((h1!=NULL) && (h2!=NULL))
    {
        res.size++;
        int d=h1->data-h2->data;
        if (d<0)
        {
            if (!h1->next)
            {
                res.sign=0;
                d=0;
            }
            else
            {
                if (h1->next->data <= 0)
                {
                    h1->next->data +=10;
                    h1->next->next->data --;
                }
                h1->next->data--;
                d+=10;
            }
        }
        if (!(resnode))
        {
            resnode=NewNode(d);
            itr=resnode;
            h1=h1->next;
            h2=h2->next;

        }
        else
        {
            itr->next=NewNode(d);
            itr=itr->next;
            h1=h1->next;
            h2=h2->next;
        }
    }
    while (h1)
    {
        res.size++;
        itr->next=NewNode(h1->data);
        itr=itr->next;
        h1=h1->next;
    }
    while (h2)
    {
        res.size++;
        itr->next=NewNode(h2->data);
        itr=itr->next;
        h2=h2->next;
    }
    res.cap=res.size;
    if (l1<l2)
    {
        res.sign=0;
    }
    struct node *s=duplicate(resnode);
    struct node *x=s;
    while (s->next)
    {
        if (s->data < 0)
        {
            s->data+=10;
            s->next->data --;
        }
        s=s->next;
    }
    resnode=duplicate(x);
    res.list=reverse(resnode);
    return res;
}

int compare(struct BigInteger d,struct BigInteger b)
{
    struct BigInteger s = sub(dupl(d),dupl(b));
    //display(s);
    if (s.sign == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

struct BigInteger mul(struct BigInteger b1, struct BigInteger b2)
{
    if (!b1.size || (is_null(dupl(b1))==0))
    {
        return b1;
    }
    if (!b2.size || (is_null(dupl(b2))==0))
    {
        return b2;
    }
    struct node *first =b1.list;
    struct node *second =b2.list;
    int m =length (first) , n = length(second);
    struct BigInteger result = allocate (m + n + 1);
    struct node* res= empty_list(m + n + 1);
 
    struct node *second_ptr = second,*result_ptr1 = res, *result_ptr2, *first_ptr;
 
    while (second_ptr) 
    {
 
        int carry = 0;
 
        result_ptr2 = result_ptr1;
 
        first_ptr = first;
 
        while (first_ptr) 
        {
            int multi = first_ptr->data * second_ptr->data + carry;
            result_ptr2->data += multi % 10;
            carry = multi / 10 + result_ptr2->data / 10;
            result_ptr2->data = result_ptr2->data % 10;
 
            first_ptr = first_ptr->next;
            result_ptr2 = result_ptr2->next;
        }
        if (carry > 0) 
        {
            result_ptr2->data += carry;
        }
 
        result_ptr1 = result_ptr1->next;
        second_ptr = second_ptr->next;
        result.size++;
    }

    res=reverse(res);
    int s = res->data;
    s = s / 100;
    while (res->data == 0) 
    {
        struct node* temp = res;
        res = res->next;
        free(temp);
        result.size--;
    }
    res=reverse(res);
    result.list=res;

    if ((b1.sign == 0  && b2.sign == 1)) 
    {
        result.sign=0;
    }
    if ((b2.sign == 0  && b1.sign == 1))
    {
        result.sign=0;
    }
    return result;
}

struct BigInteger div1(struct BigInteger b1,struct BigInteger b2)
{
    struct BigInteger a1=dupl(b1);
    a1.sign=1;
    struct BigInteger a2=dupl(b2);
    a2.sign=1;
    long long int quotient=0;
    struct BigInteger q;
    if (!b1.size || (is_null(dupl(a1))==0))
    {
        q.list=NewNode(0);
        return q;
    }
    if (compare(dupl(a1),dupl(a2))==0)
    {
        q.list=NewNode(0);
        return q;
    }
    if (!b2.size || (is_null(dupl(a2))==0))
    {
        printf ("Division doesn't exist.\n");
        q.list=NewNode(0);
        return q;
    }
    struct BigInteger a=sub(dupl(a1),dupl(a2));
    int l=is_null(a);
    if (l==0)
    {
        q.list=NewNode(1);
        return q;
    }
    while (compare(dupl(a1),dupl(a2)))
    {
        quotient++;
        a1=sub(dupl(a1),dupl(a2));
    }      
    struct node *list= NewNode(quotient);
    q.list = duplicate(list);
    if ((b1.sign == 0  && b2.sign == 1)) 
    {
        q.sign=0;
    }
    if ((b2.sign == 0  && b1.sign == 1))
    {
        q.sign=0;
    }
    return q;
}

struct BigInteger mod(struct BigInteger b1,struct BigInteger b2)
{
    struct BigInteger m;
    if (!b1.size || (is_null(dupl(b1))==0))
    {
        m.list=NewNode(0);
        return m;
    }
    if (compare(dupl(b1),dupl(b2))==0)
    {
        return b2;
    }
    if (!b2.size || (is_null(dupl(b2))==0))
    {
        m.list=NewNode(0);
        return m;
    }
    struct BigInteger a1=dupl(b1);
    a1.sign=1;
    struct BigInteger a2=dupl(b2);
    a2.sign=1;
    struct BigInteger a=sub(dupl(a1),dupl(a2));
    int l=is_null(a);
    if (l==0)
    {
        m.list=NewNode(0);
        return m;
    }
    while (compare(dupl(a1),dupl(a2)))
    {
        a1=sub(dupl(a1),dupl(a2));
    }
    if (a1.list==NULL)
    {
        m.list=NewNode(0);
        return m;
    }
    m=dupl(a1);
    if (b1.sign == 0) 
    {
        m.sign=0;
    }
    return m;
}
