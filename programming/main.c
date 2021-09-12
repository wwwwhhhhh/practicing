//
//  main.c
//  程序设计
//
//  Created by 甘蔗 on 2021/7/12.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "MyStock.h"
#define PD (p->days)

void Switch(int * f);
void CreatStock(void);
void CreatBank(void);
void FprintStock(void);
void FprintBank(void);
void FprintTransaction(void);

Stock * StoHead, * sto;
Bank bank;
Transaction * TraHead, * tra;

int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    
    sto = StoHead;
    tra = TraHead;
    
    // creat a Stock linked list
    // type 0 to use the formal one, 1 to creat a random one
    //CreatStock();
    CreatStock();
    
    // creat a bank
    // type 0 to use the formal one, 1 to creat a random one
    CreatBank();
    
    // start the game
    int f = 1;
    printf("现在正式开始");
    while (f){
        printf("\n\n\n");
        printf("*********************************************\n");
        printf("打印数据请输1，                处理数据请输2\n"); // ask for what to do
        printf("查找数据请输3，                进入下一天请输4\n");
        printf("更改账户信息请输5，             退出程序请输0:\n");
        scanf ("%d", & f);
        Switch(& f);
    }
    
    FprintStock();
    FprintBank();
    if (TraHead)
        FprintTransaction();
    
    return 0;
}

void FprintStock(void){
    FILE * f = fopen("Stock.txt", "w");
    Stock *p = StoHead;
    while (p){
        fprintf(f, "%-16s %-7.2f %-7d\n", p->company, p->share_pri[(PD)%10], p->shares_tot);
        p = p->next;
    }
    fclose(f);
}

void FprintBank(void){
    FILE * f = fopen("Bank.txt", "w");
    fprintf(f, "%-16s\n%-7.3lf\n", bank.username, bank.money);
    if (bank.money){
        Stock * p = StoHead;
        while(p){
            if (p->shares){
                fprintf(f, "%-16s\n股价：%-7.2f\n 股市：%-7d", p->company, p->share_pri[PD%10], p->shares_tot); // the data in this company
            }
            p = p->next;
        }
    }
    fclose(f);
}

void FprintTransaction(void){
    FILE * f = fopen("Transaction.txt", "w");
    Transaction * p = TraHead;
    char trans[5];
    while (p){
        if (p->trans == 0)
             strcpy(trans, "sell");
        else if (p->trans == 1)
            strcpy(trans, "buy");
        else if (p->trans == 2)
            strcpy(trans, "lost");
        fprintf(f, "%-16s 交易日期: %-3d %-5s 股数: %-3d 股价: %-7.2lf 总金额: %-7.2lf\n", p->bank, p->day, trans, p->shares_T, p->share_pri_T, p->total_val_T);
        p = p->next;
    
    }
}

// creat a Stock linked list from the formal file
void CreatStock0(void){
    Stock *p, *p1;
    FILE * f = fopen("Stock0.txt", "r");
    p1 = p = (Stock *) malloc (LENS);
    StoHead = p;
    fscanf(f, "%s", p->company);
    fscanf(f, "%f", &p->share_pri[0]);
    for (int i = 1; i < 10; i ++)
        p->share_pri[i] = 0;
    fscanf(f, "%d", &p->shares_tot);
    p->shares = p->total_sha = 0;
    for (int i = 0; i < 10; i ++)
        p->change[i] = 0;
    PD = 0;
    while(!feof(f)){
        p = (Stock *) malloc (LENS);
        fscanf(f, "%s", p->company);
        fscanf(f, "%f", & p->share_pri[0]);
        for (int i = 1; i < 10; i ++)
            p->share_pri[i] = 0;
        fscanf(f, "%d", & p->shares_tot);
        p->shares = p->total_sha = 0;
        for (int i = 0; i < 10; i ++)
            p->change[i] = 0;
        PD = 0;
        p1->next = p;
        p1 = p;
    }
    p->next = NULL;
    sto = p;
    fclose(f);
}

// creat a new Stock linked list
void CreatStock1(void){
    Stock *p1, *p;
    float t;
    printf("请输入公司数量：\n"); // ask for the number of companys
    scanf("%d", & CompanyNum);
    p1 = p = (Stock *)malloc(LENS);
    StoHead = p;
    int com = rand()%10 + 4;
    p->company[0] = rand()%26 + 'A';
    for (int i = 1; i < com; i ++){
        p->company[i] = rand()%26 + 'a';
    }
    p->shares = 0;
    p->shares_tot = rand()%10000;
    t = 1.0 / (rand()%10 + 1);
    p->share_pri[0] = rand()%100 + t;
    for (int i = 1; i < 10; i ++)
        p->share_pri[i] = 0;
    p->total_sha = 0;
    for (int i = 0; i < 10; i ++)
        p->change[i] = 0;
    PD = 0;
    for (int i = 1; i < CompanyNum; i ++){
        p = (Stock *)malloc(LENS);
        p1->next = p;
        p1 = p;
        com = rand()%10 + 4;
        p->company[0] = rand()%26 + 'A';
        for (int i = 1; i < com; i ++){
            p->company[i] = rand()%26 + 'a';
        }
        p->company[com] = '\0';
        p->shares = 0;
        p->shares_tot = rand()%10000 + 100;
        t = 1.0 / (rand()%10 + 1) + 0.1;
        p->share_pri[0] = rand()%100 + t;
        for (int i = 1; i < 10; i ++)
            p->share_pri[i] = 0;
        p->total_sha = 0;
        for (int i = 0; i < 10; i ++)
            p->change[i] = 0;
        PD = 0;
    }
    p->next = NULL;
    sto = p;
}

void CreatStock(void){
    int f;
    while (1){
        printf("首先建立您的股市。\n"); // ask for the choice
        printf("请输入建立方式:(从已有文件读取请输入0，建立随机股市请输入1)\n");
        scanf("%d", &f);
        if (f == 0){
            CreatStock0();
            break;
        }
        else if (f == 1){
            CreatStock1();
            break;
        }
        else
            printf("请输入0或1\n"); // enter wrong
    }
}

// creat a random bank
void CreatBank0(void){
    int num = rand() % 10 + 4;
    bank.username[0] = rand() % 26 + 'A';
    for (int i = 1; i < num; i ++)
        bank.username[i] = rand() % 26 + 'a';
    bank.money = rand() % 100000 + 10000;
    bank.shares_val = 0;
}

// creat a new bank by the user
void CreatBank1(int * flag){
    printf("请输入您的账户名：（输入0返回上一步）\n"); // ask for the usetname, 0 to return to the last step
    scanf("%s", bank.username);
    if (strcmp(bank.username, "0")){
        * flag = 0;
        printf("请输入您的初始金额：\n"); // ask for the money
        scanf("%lf", & bank.money);
        bank.shares_val = 0;
    }
}

void CreatBank(void){
    int f = 1;
    while (f){
        printf("现在建立您的账户：(随机建立请输入0，自定义请输入1)\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0){
            CreatBank0();
            break;
        }
        else if (f == 1){
            CreatBank1(&f);
        }
        else
            printf("请输入0或1\n"); // enter error
    }
}

void PrintStock(void){
    int n = 0;
    if (StoHead){
        Stock * p;
        p = StoHead;
        while (p){
            // print the data
            printf("%-16s\n", p->company);
            printf("             您持有的股票数量: %-7d        您的最大持有量: %-7d \n", p->shares, p->shares_tot);
            printf("             股价: %-7.3lf       您的总股值: %-7.3lf    较前日变化: %-.3lf\n", p->share_pri[PD%10], p->total_sha, p->change[(PD - 1)%10]);
            p = p->next;
            if (!n % 30)
                getchar();
            n ++;
        }
    }
    else
        printf("暂无数据。\n");
}

void PrintBank(void){
    // print the data
    printf("账户名：%-16s 持有金额: %-9.3lf 持有总股值: %-9.3lf\n", bank.username, bank.money, bank.shares_val);
    // print the data of the user's shares
    if (bank.money){
        Stock * p = StoHead;
        while(p){
            if (p->shares){
                printf("%-16s\n", p->company);
                printf("             您持有的股票数量: %-7d        您的最大持有量: %-7d \n", p->shares, p->shares_tot);
                printf("             股价: %-7.3lf       您的总股值: %-7.3lf    较前日变化: %-.3lf\n", p->share_pri[PD%10], p->total_sha, p->change[(PD - 1)%10]);
            }
            p = p->next;
        }
    }
}

void PrintTransaction(void){
    if (TraHead){
        Transaction * p;
        p = TraHead;
        char trans[5];
        while (p){
            // print the data
            if (p->trans == 0)
                 strcpy(trans, "sell");
            else
                strcpy(trans, "buy");
            printf("%-16s 交易日期: %-3d %-5s 股数 %-3d 股价: %-7.2lf 总金额: %-7.2lf\n", p->bank, Day, trans, p->shares_T, p->share_pri_T, p->total_val_T);
            p = p->next;
        }
    }
    else
        printf("暂无数据\n");
}

void Print(void){
    int f = 1;
    while (f){
        printf("输入0返回上一步，输入1打印股市，输入2打印账户，输入3打印交易明细\n"); // what to find
        scanf("%d", &f);
        switch(f){
            case 0:
                break;
            case 1:
                PrintStock();
                f = 0;
                break;
            case 2:
                PrintBank();
                f = 0;
                break;
            case 3:
                PrintTransaction();
                f = 0;
                break;
            default:
                printf("请输入0～3\n"); // enter error
                break;
        }
    }
}

void BuyShares(int * flag){
    Stock * p = StoHead;
    char CompanyBuy[20];
    while(1){
        printf("请输入公司名字(输入0返回上一步)\n"); // ask for the company name
        scanf("%s", CompanyBuy);
        if (!strcmp(CompanyBuy, "0"))
            break;
        else{
            p = StoHead;
            while (p){
                if (!strcmp(CompanyBuy, p->company)){
                    // print the data of that company
                    printf("%-16s\n", p->company);
                    printf("             您持有的股票数量: %-7d        您的最大持有量: %-7d \n", p->shares, p->shares_tot);
                    printf("             股价: %-7.3lf       您的总股值: %-7.3lf    较前日变化: %-.3lf\n", p->share_pri[PD%10], p->total_sha, p->change[(PD - 1)%10]);
                    printf("账户剩余金额：%-9.3lf\n", bank.money);
                    int BuyNum;
                    printf("请输入交易数量\n"); // ask for the number to buy
                    scanf("%d", & BuyNum);
                    if (BuyNum + p->shares > p->shares_tot)
                        printf("超过您所能购买上限\n"); // more than you can buy
                    else if ((double)BuyNum * (p->share_pri[PD%10]) > (bank.money))
                        printf("金额不足\n"); // don't hsve that much money
                    else{
                        // update this company
                        p->shares += BuyNum;
                        p->total_sha += BuyNum * p->share_pri[PD%10];
                        // update your bank
                        bank.money -= BuyNum * p->share_pri[PD%10];
                        bank.shares_val += BuyNum * p->share_pri[PD%10];
                        // update Transaction
                        Transaction * p1 = (Transaction *)malloc(LENT);
                        if(TraHead)
                            tra->next = p1;
                        else
                            TraHead = tra = p1;
                        p1->next = NULL;
                        tra = p1;
                        // add data into p1
                        strcpy(p1->bank, p->company);
                        p1->day = Day;
                        p1->trans = 1;
                        p1->shares_T = BuyNum;
                        p1->share_pri_T = p->share_pri[PD%10];
                        p1->total_val_T = BuyNum * p->share_pri[PD%10];
                    }
                    *flag = 0;
                    break;
                }
                else
                    p = p->next;
            }
            if (p)
                break;
            else
                printf("未能找到\n"); // search error
        }
    }
}

void Buy(int * flag){
    int f = 1;
    while (f){
        printf("输入0退出，输入1打印数据，输入2进行交易\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0)
            break;
        else if (f == 1){
            Print();
        }
        else if (f == 2){
            // buy shares
            BuyShares(&f);
            *flag = 0;
            break;
        }
        else
            printf("请输入0~2\n"); // enter error
    }
}

void SellShares(int * flag){
    Stock * p = StoHead;
    char CompanyBuy[20];
    while(1){
        printf("请输入公司名字(输入0返回上一步)\n"); // ask for the company name
        scanf("%s", CompanyBuy);
        if (!strcmp(CompanyBuy, "0")){
            break;
        }
        else{
            p = StoHead;
            while (p){
                if (!strcmp(CompanyBuy, p->company)){
                    // print the data of that company
                    printf("%-16s\n", p->company);
                    printf("             您持有的股票数量: %-7d        您的最大持有量: %-7d \n", p->shares, p->shares_tot);
                    printf("             股价: %-7.3lf       您的总股值: %-7.3lf    较前日变化: %-.3lf\n", p->share_pri[PD%10], p->total_sha, p->change[(PD - 1)%10]);
                    int SellNum;
                    printf("请输入交易数量:\n"); // ask for the number you sell
                    scanf("%d", & SellNum);
                    if (SellNum > p->shares)
                        printf("超出交易上限。\n"); // more than you can sell
                    else{
                        // update this company
                        p->shares -= SellNum;
                        p->total_sha -= SellNum * p->share_pri[PD%10];
                        // update your bank
                        bank.money += SellNum * p->share_pri[PD%10];
                        bank.shares_val -= SellNum * p->share_pri[PD%10];
                        // update Transaction
                        Transaction * p1 = (Transaction *)malloc(LENT);
                        if(TraHead)
                            tra->next = p1;
                        else
                            TraHead = tra = p1;
                        p1->next = NULL;
                        tra = p1;
                        // add data into p1
                        strcpy(p1->bank, p->company);
                        p1->day = Day;
                        p1->trans = 0;
                        p1->shares_T = SellNum;
                        p1->share_pri_T = p->share_pri[PD%10];
                        p1->total_val_T = SellNum * p->share_pri[PD%10];
                    }
                    break;
                }
                else
                    p = p->next;
            }
            if (p)
                break;
            else
                printf("未能找到。\n"); // search error
        }
    }
}

void Sell(int * flag){
    int f = 1;
    while (f){
        printf("输入0返回上一步，输入1打印数据，输入2进行交易:\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0)
            break;
        else if (f == 1)
            Print();
        else if (f == 2){
            // sold shares
            *flag = 0;
            SellShares(&f);
            break;
        }
        else
            printf("请输入0～2:\n"); // enter error
    }
}

void AddCompany(int * flag){
    int f = 1;
    while (f){
        printf("输入0返回上一步，输入1添加随机公司，输入2添加自定义公司(默认从尾部添加):\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0)
            break;
        else if (f == 1){
            // creat a random one
            // update Stock
            Stock * p = (Stock *)malloc(LENS);
            sto->next = p;
            p->next = NULL;
            sto = p;
            // add data into p
            int comnum = rand()%10 + 4;
            p->company[0] = rand()%26 + 'A';
            for (int i = 1; i < comnum; i ++){
                p->company[i] = rand()%26 + 'a';
            }
            p->company[comnum] = '\0';
            p->shares = 0;
            p->shares_tot = rand()%10000;
            p->share_pri[0] = rand()%100 + 1 / (rand() % 10 + 1);
            for (int i = 1; i < 10; i ++)
                p->share_pri[i] = 0;
            p->total_sha = 0;
            for (int i = 0; i < 10; i ++)
                p->change[i] = 0;
            PD = 0;
            CompanyNum++;
            *flag = 0;
            break;
        }
        else if (f == 2){
            // creat by the player
            Stock * p = (Stock *)malloc(LENS);

            printf("请输入公司名字：(输入0返回上一步)\n"); // ask for the name of the company
            scanf("%s", p->company);
            if (!strcmp(p->company, "0"))
                break;
            printf("请输入股价:\n"); // ask for the value of the shares
            scanf("%f", & p->share_pri[0]);
            printf("请输入购买上限:\n"); // ask for the number of the shares you can buy
            scanf("%d", & p->shares_tot);
            p->shares = 0;
            for (int i = 0; i < 10; i ++)
                p->change[i] = 0;
            PD = 0;
            p->total_sha = 0;
            sto->next = p;
            p->next = NULL;
            sto = p;
            CompanyNum++;
            *flag = 0;
            break;
        }
        else
            printf("请输入0～2:\n"); // enter error
    }
}

void DeleteCompany1(void){
    Stock *p = StoHead, *p1 = p->next;
    if (StoHead){
        int location = rand() % CompanyNum;
        if (location){
            for (int i = 0; i < location - 1; i ++){
                p = p->next;
                p1 = p1->next;
            }
            p->next = p1->next;
            if(p1->shares){
                Transaction * p2 = (Transaction *)malloc(LENT);
                if (TraHead)
                    tra->next = p2;
                else
                    TraHead = tra = p2;
                p2->next = NULL;
                tra = p2;
                p2->day = Day;
                strcpy(p2->bank, p1->company);
                p2->trans = 2;
                p2->shares_T = p1->shares;
                p2->share_pri_T = p1->share_pri[p1->days%10];
                p2->total_val_T = p1->total_sha;
                bank.shares_val -= p1->total_sha;
            }
            free(p1);
            CompanyNum --;
        }
        else{
            StoHead = p1;
            if(p->shares){
                Transaction * p2 = (Transaction *)malloc(LENT);
                tra->next = p2;
                p2->next = NULL;
                tra = p2;
                p2->day = Day;
                strcpy(p2->bank, p->company);
                p2->trans = 2;
                p2->shares_T = p->shares;
                p2->share_pri_T = p->share_pri[PD%10];
                p2->total_val_T = p->total_sha;
                bank.shares_val -= p->total_sha;
            }
            free(p);
            CompanyNum --;
        }
    }
    else
        printf("暂无数据\n"); // no data yet
}

void DeleteCompany2(int * flag){
    printf("请输入公司名:\n"); // ask for the company name;
    char TargetName[20];
    scanf("%s", TargetName);
    Stock * p = StoHead, * p1 = p->next;
    if (StoHead){
        if (!strcmp(TargetName, StoHead->company)){
            printf("(二次确认)是否删除？(输入0返回上一步, 其他数字继续):\n"); // double sure, 0 to quit, 1 to continue
            scanf("%d", flag);
            if(*flag){
                StoHead = p1;
                if (p->shares){
                    Transaction * p2 = (Transaction *)malloc(LENT);
                    if (TraHead)
                        tra->next = p2;
                    else
                        TraHead = tra = p2;
                    p2->next = NULL;
                    tra = p2;
                    p2->day = Day;
                    strcpy(p2->bank, p->company);
                    p2->trans = 2;
                    p2->shares_T = p->shares;
                    p2->share_pri_T = p->share_pri[PD%10];
                    p2->total_val_T = p->total_sha;
                    bank.shares_val -= p->total_sha;
                }
                free(p);
                CompanyNum --;
            }
        }
        else{
            while(p1){
                if(strcmp(p1->company, TargetName)){
                    p = p->next;
                    p1 = p->next;
                }
                else
                    break;
            }
            if(p1){
                printf("(二次确认)是否删除？(输入0返回上一步,其他数字继续):\n"); // double sure
                scanf("%d", flag);
                if(flag){
                    p->next = p1->next;
                    if(p1->shares){
                        Transaction * p2 = (Transaction *)malloc(LENT);
                        if (TraHead)
                            tra->next = p2;
                        else
                            TraHead = tra = p2;
                        p2->next = NULL;
                        tra = p2;
                        p2->day = Day;
                        strcpy(p2->bank, p1->company);
                        p2->trans = 2;
                        p2->shares_T = p1->shares;
                        p2->share_pri_T = p1->share_pri[p1->days%10];
                        p2->total_val_T = p1->total_sha;
                        bank.shares_val -= p->total_sha;
                    }
                    printf("%s\n", p1->company);
                    free(p1);
                    CompanyNum --;
                }
            }
            else
                printf("未能找到\n"); // company not found
        }
    }
    else
        printf("暂无数据\n"); // no data yet
}

void DeleteCompany(int * flag){
    int f = 1;
    while (f){
        printf("输入0返回上一步，输入1删除随机数据，输入2删除指定公司：\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0)
            break;
        else if (f == 1){
            while(1){
                printf("(二次确认)是否删除？(输入0返回上一步,其他数字继续):\n"); // double sure, 0 to quit, 1 to continue
                scanf("%d", & f);
                if (f == 0)
                    break;
                else if (f == 1){
                    // delete a random one
                    DeleteCompany1();
                    break;
                }
                else
                    printf("请输入0或1"); // enter error
            }
            *flag = 0;
            break;
        }
        else if (f == 2){
            // delete by the player
            DeleteCompany2(&f);
            *flag = 0;
            break;
        }
        else
            printf("请输入0～2\n"); // enter error
    }
}

void SortName(void){
    Stock *p, *p1 = NULL, *p2 = NULL, *t;
    if (StoHead->next && StoHead){
        for (int i = 0; i < CompanyNum; i ++){
            if (strcmp(StoHead->company, StoHead->next->company) > 0){
                p1 = StoHead; p2 = StoHead->next;
                StoHead = p2;
                p1->next = p2->next;
                StoHead->next = p1;
            }
            p = StoHead; p1 = p->next; p2 = p1->next;
            while(p2){
                if (strcmp(p1->company, p2->company) > 0){
                    t = p1; p1 = p2; p2 = t;
                    p->next = p1; p2->next = p1->next; p1->next = p2;
                }
                p = p->next; p1 = p1->next; p2 = p2->next;
            }
        }
    }
}

void SortValue(void){
    Stock *p, *p1 = NULL, *p2 = NULL, *t;
    if (StoHead->next && StoHead){
        for (int i = 0; i < CompanyNum; i ++){
            p1 = StoHead; p2 = StoHead->next;
            if (p1->share_pri[p1->days%10] < p2->share_pri[p2->days%10]){
                p1 = StoHead; p2 = StoHead->next;
                StoHead = p2;
                p1->next = p2->next;
                StoHead->next = p1;
            }
            p = StoHead; p1 = p->next; p2 = p1->next;
            while(p2){
                if (p1->share_pri[p1->days%10] < p2->share_pri[p2->days%10]){
                    t = p1; p1 = p2; p2 = t;
                    p->next = p1; p2->next = p1->next; p1->next = p2;
                }
                p = p->next; p1 = p1->next; p2 = p2->next;
            }
        }
    }
}

void Sort(int * flag){
    int f = 1;
    while (f){
        printf("输入0返回上一步，输入1对名称排序，输入2对股价排序:\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0)
            break;
        else if (f == 1){
            SortName();
            *flag = 0;
            // sort by company name
            break;
        }
        else if (f == 2){
            SortValue();
            *flag = 0;
            // sort by share value
            break;
        }
        else
            printf("请输入0~2\n"); // enter error
    }
}

void Process(void){
    int f = 1;
    while (f){
//        printf("***********************************************************\n");
        printf("输入0返回上一步，             输入1购买股票\n"); // ask for the choice
        printf("输入2卖出股票，               输入3增加公司\n");
        printf("输入4删除公司，               输入5排序\n");
        scanf("%d", &f);
        switch(f){
            case 0:
                break;
            case 1:
                // buy some shares
                Buy(&f);
                break;
            case 2:
                // sold some shares
                Sell(&f);
                break;
            case 3:
                // creat a new company
                AddCompany(&f);
                break;
            case 4:
                // delete a company
                DeleteCompany(&f);
                break;
            case 5:
                // sort
                Sort(&f);
                break;
            default:
                break;
        }
    }
}

void Find(void){
    char TargetName[20];
    printf("请输入公司名(输入0返回上一步):\n"); // ask for the choice
    scanf("%s", TargetName);
    if (strcmp(TargetName, "0")){
        Stock * p = StoHead;
        while(p){
            if(!strcmp(TargetName, p->company)){
                printf("%-16s 您持有的股票数量: %-7d 您的最大持有量: %-7d 您的总股值: %-7.3lf \n", p->company, p->shares, p->shares_tot, p->total_sha);
                printf("近日股价变化：\n");
                if(PD > 10){
                    for (int i = 0; i < 10; i ++)
                        printf("%-.3f ", p->change[(PD + i)%10]);
                    printf("\n");
                }
                else{
                    for (int i = 0; i < PD - 1; i ++)
                        printf("%-.3f ", p->change[i]);
                    printf("\n");
                }
                printf("近日股价：\n");
                if(PD >= 10){
                    for (int i = 1; i <= 10; i ++)
                        printf("%-5.3f ", p->share_pri[(PD + i + 1)%10]);
                    printf("\n");
                }
                else{
                    for (int i = 0; i <= PD; i ++)
                        printf("%-5.3f ", p->share_pri[i]);
                    printf("\n");
                }
                break;
            }
            p = p->next;
        }
        if(!p)
            printf("未能找到\n"); // company not found
    }
}

void Update(void){
    float t;
    Stock * p = StoHead;
    while(p){
        PD ++;
        p->change[(PD - 1)%10] = rand()%3 - 1;
        t = 1.0 / (rand()%20 + 1);
        p->change[(PD - 1)%10] *= t;
        p->share_pri[(PD)%10] = p->share_pri[(PD - 1)%10] * (1 + p->change[(PD - 1)%10]);
        p->total_sha = p->share_pri[(PD)%10] * p->shares;
        if (p->shares)
            bank.shares_val += (p->share_pri[(PD)%10] - p->share_pri[(PD - 1) % 10]) * p->shares;

        p = p->next;
    }
    Day++;
}

// if CompanyNum > 10
void Delete(void){
    int DeleteNum = rand() % (CompanyNum/20 + 1), num = 0, t;
    int DeleteLa[DeleteNum];
    DeleteLa[0] = rand() % (CompanyNum - 2);
    for (int i = 0; i < DeleteNum; i ++){
        t = rand()%(CompanyNum - 2);
        for (int j = 0; j < i; j ++)
            if (t == DeleteLa[j]){
                t = rand()%(CompanyNum - 2);
                j = 0;
            }
        DeleteLa[i] = t;
        for (int j = i; j >= 0; j --){
            if (!j){
                DeleteLa[j] = t;
                break;
            }
            else if (DeleteLa[j - 1] > t)
                DeleteLa[j] = DeleteLa[j - 1];
            else{
                DeleteLa[j] = t;
                break;
            }
        }
    }
    int n = 0, i = 0;
    Stock * p = StoHead, *p_ = NULL, *p_1 = NULL;
    while(p && p->next){
        if(DeleteLa[i] == n || (p->share_pri[(PD)%10]) == 0){
            if (!i)
                p_ = p_1 = p->next;
            else{
                p_1->next = p->next;
                p_1 = p_1->next;
            }
            p->next = p_1->next;
            p_1->next = NULL;
            i ++;
            num ++;
            if(p_1->shares){
                Transaction * p2 = (Transaction *)malloc(LENT);
                if (TraHead)
                    tra->next = p2;
                else
                    TraHead = tra = p2;
                p2->next = NULL;
                tra = p2;
                p2->day = Day;
                strcpy(p2->bank, p_1->company);
                p2->trans = 2;
                p2->shares_T = p_1->shares;
                p2->share_pri_T = p_1->share_pri[PD%10];
                p2->total_val_T = p_1->total_sha;
                bank.shares_val -= p_1->total_sha;
            }
            CompanyNum --;
        }
        n ++;
        p = p->next;
    }

    if (p_){
        printf("%d 个公司被删除:\n", num); // the number of company deleted
        p_1 = p_;
        p_ = NULL;
        if (p_1->next)
            p_ = p_1->next;
        while(p_){
            printf("%-16s 您持有的股票数量: %-7d 股价: %-7.3lf 您的总股值: %-7.3lf 较前日变化: %-.3lf\n", p_1->company, p_1->shares, p_1->share_pri[p_1->days%10], p_1->total_sha, p_1->change[(p_1->days - 1)%10]);
            free(p_1);
            p_1 = p_;
            p_ = p_-> next;
            // free this list
        }
        if (p_1){
                printf("%-16s 您持有的股票数量: %-7d 股价: %-7.3lf 您的总股值: %-7.3lf 较前日变化: %-.3lf\n", p_1->company, p_1->shares, p_1->share_pri[p_1->days%10], p_1->total_sha, p_1->change[(p_1->days - 1)%10]);
                free(p_1);
            }
    }
}

void Add(void){
    int AddNum = rand() % 3 + 1;
    Stock * p = NULL;
    for (int i = 0; i < AddNum; i ++){
        p = (Stock *)malloc(LENS);
        int com = rand()%10 + 4;
        p->company[0] = rand()%26 + 'A';
        for (int i = 1; i < com; i ++){
            p->company[i] = rand()%26 + 'a';
        }
        p->company[com] = '\0';
        p->shares = 0;
        p->shares_tot = rand()%10000;
        p->share_pri[0] = rand()%100 + 1 / (rand() % 10 + 1);
        for (int i = 1; i < 10; i ++)
            p->share_pri[i] = 0;
        p->total_sha = 0;
        p->change[0] = 0;
        PD = 0;
        sto->next = p;
        sto = p;
        CompanyNum++;
    }
    p->next = NULL;
    printf("AddNum: %d\n", AddNum);
}

void Spend(void){
    bank.money -= 100;
    printf("日常花费：100\n");
}

void NextDay(int * flag){
    if (bank.money >0 || bank.shares_val > 0){
        double shares_val_t = bank.shares_val;
        // update the share_val, total_val, and move to the next day (Day ++)
        Update();
        // delete some companys
        if (CompanyNum > 10)
            Delete();
        // add some companys
        Add();
        // spend 100 money
        Spend();
        printf("CompanyNum: %d\n", CompanyNum);
        printf("您的金额变化: %.3lf\n", bank.shares_val - shares_val_t);// you lost or earn a number of money
    }
    else{
        // game over
        printf("\n\n\n\n\nYOU BROKE\n\n\n");
        printf("GAME OVER\n");
        *flag = 0;
    }
}

void ChangeShare_val(int * flag){
    char TargetName[20];
    float share_value;
    while(1){
        printf("请输入公司名字（输入0返回上一步）:\n"); // ask for the choice
        scanf("%s", TargetName);
        if(strcmp(TargetName, "0")){
            Stock * p = StoHead;
            while(p){
                if(strcmp(p->company, TargetName))
                    p = p->next;
                else{
                    printf("%-16s 您持有的股票数量: %-7d 您的最大持有量: %-7d 股价: %-7.3lf 您的总股值: %-7.3lf 较前日变化: %-.3lf\n", p->company, p->shares, p->shares_tot, p->share_pri[PD%10], p->total_sha, p->change[(PD - 1)%10]);
                    printf("请输入新股值：\n");// print the data of that company, ask for the value
                    scanf("%f", & share_value);
                    p->share_pri[PD % 10] = share_value;
                    p->change[(PD - 1) % 10] = 0;
                    break;
                }
            }
            if(p)
                break;
            else
                printf("未能找到\n"); // search error
        }
        else{
            * flag = 10;
            break;
        }
    }
}

void ChangeName(int * flag){
    int f = 1;
    while (f){
        printf("输入0返回上一步，输入1更改为随机名字，输入2更改为指定名字:\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0){
            *flag = 10;
            break;
        }
        else if (f == 1){
            // change a random one
            int num = rand() % 10 + 4;
            bank.username[0] = rand() % 26 + 'A';
            for (int i = 1; i < num; i ++)
                bank.username[i] = rand() % 26 + 'a';
            break;
        }
        else if (f == 2){
            // change by the player
            printf("请输入新用户名：\n"); // enter the name
            scanf("%s", bank.username);
            break;
        }
        else
            printf("请输入0～2\n"); // enter error
    }
}

void ChangeBankValue(int * flag){
    int f = 1;
    while (f){
        printf("输入0返回上一步，输入1更改为随机金额，输入2更改为指定金额:\n"); // ask for the choice
        scanf("%d", & f);
        if (f == 0){
            *flag = 10;
            break;
        }
        else if (f == 1){
            // change a random one
            int num = rand() % 10 + 4;
            bank.username[0] = rand() % 26 + 'A';
            for (int i = 1; i < num; i ++)
                bank.username[i] = rand() % 26 + 'a';
            bank.money = rand() % 100000 + 10000;
            bank.shares_val = 0;
        }
        else if (f == 2){
            // change by the player
            printf("请输入金额：\n"); // enter the name
            scanf("%lf", &bank.shares_val);
            break;
        }
        else
            printf("请输入0～2\n"); // enter error
    }
}

void ChangeBank(void){
    int f = 1;
    printf("账户名：%-16s 持有金额: %-9.3lf 持有总股值: %-9.3lf\n", bank.username, bank.money, bank.shares_val);
    while(f){
        printf("输入0返回上一步，输入1更改用户名，输入2更改金额:\n"); // ask for the choice
        scanf("%d", & f);
        if(f == 0){
            break;
        }
        else if (f == 1){
            ChangeName(&f);
            break;
        }
        else if (f == 2){
            printf("请输入新金额:\n"); // ask for the choice
            scanf("%lf", & bank.money);
            break;
        }
        else
            printf("请输入0～2\n"); // enter error
    }
}

void Switch(int * f){
    
    switch (*f){
        case 0:
            break;
        case 1:
            // print data
            Print();
            break;
        case 2:
            // process data
            Process();
            break;
        case 3:
            // find data
            Find();
            break;
        case 4:
            // next day
            NextDay(f);
            break;
        case 5:
            // change the name or money of your money
            ChangeBank();
            break;
        default:
            printf("请输入0～5\n"); // enter error
            break;
    }
}
