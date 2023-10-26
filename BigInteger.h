#ifndef BIGINTEGER_H
#define BIGINTEGER_H
struct node 
{
    int data;
    struct node *next;
};
struct BigInteger
{
    int size;
    struct node *list;
    int sign;
    int cap;
};
void display2(struct BigInteger b1);
struct node* NewNode(int val);
struct BigInteger allocate(int cap);
struct BigInteger initialize(char *str);
int length (struct node *b);
struct BigInteger dupl(struct BigInteger b1);
struct node* reverse(struct node *head);
int is_null(struct BigInteger a);
int comp(struct BigInteger b1,struct BigInteger b2);
struct node* duplicate(struct node *b1);
struct BigInteger add(struct BigInteger b1, struct BigInteger b2);
struct BigInteger sub(struct BigInteger b1,struct BigInteger b2);
int compare(struct BigInteger d,struct BigInteger b);
struct BigInteger div1(struct BigInteger b1,struct BigInteger b2);
struct BigInteger mod(struct BigInteger b1,struct BigInteger b2);
void push(struct node** head, int data);
struct node* empty_list(int size);
struct BigInteger mul(struct BigInteger b1, struct BigInteger b2);
#endif