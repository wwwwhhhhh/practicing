#ifndef MYSTOCK_H_
#define MYSTOCK_H_
#define LENS sizeof(Stock)
#define LENT sizeof(Transaction)
int CompanyNum = 100; // the number of the companies
int TraNum = 0; // the number of data int Transaction
int Day = 1; // the time in this game 


typedef struct S{
    char company[20];
    int shares; // the shares you have in this company
    int shares_tot; // the shares you can have most
    float share_pri[10]; // the shares' value in most recent 10 days
    double total_sha; // the money you have in this company
    float change[10]; // -1 - down, 0 - no change, 1 - up
    int days; // the day this company had formed
    struct S * next;
}Stock;

typedef struct{
    char username[20];
    double money; // the money you have in the bank
    double shares_val; // the money changed from all of your shares
}Bank;

typedef struct T{
    int day; // transaction day
    char bank[20]; // the company you transacted with
    int trans; // 0 - sell, 1 - buy, 2 - lost(the bank was broken)
    int shares_T; // the number of shares you buy, sell, or lost
    float share_pri_T; // the value of each shares
    double total_val_T; // the number of money in this transaction
    struct T * next;
}Transaction;

#endif
