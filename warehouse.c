#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20
struct product
{
    int p_id;
    char p_name[40];
    double price;
    char lastSold[30];
    int quantity;
    bool discount;
};

void backup_copying(char update[255])
{
    FILE *file;
    file = fopen("history.txt", "a"); // creating history.txt file
    fprintf(file, "%s\n", update);
    fclose(file);
}

void insert(struct product *product_list, int *purchased_amount, int pid, int amount, char date[30], char name[40], double price)
{
    struct product newproduct;
    newproduct.p_id = pid;
    strcpy(newproduct.p_name, name);
    newproduct.price = price;
    strcpy(newproduct.lastSold, "--/--/--");
    newproduct.quantity = amount;
    newproduct.discount = false;

    for (int i = 0; i < MAX; i++)
    {
        if (strlen(product_list[i].p_name) < 1)
        {
            product_list[i] = newproduct;
            char buf[255];
            purchased_amount[i] = 0;
            snprintf(buf, 255, "%s  %d  %s  (%d) inserted..", newproduct.lastSold, pid, name, amount);
            backup_copying(buf);
            break;
        }
    }
}

void discount(struct product *product_list, char date[30])
{
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(product_list[i].p_name) < 1)
        {
            break;
        }
        product_list[i].discount = true;
    }
    char buf[255];
    snprintf(buf, 255, "%s All products are discounted..", date);
    backup_copying(buf);
}

void sell(struct product *product_list, int *purchased_amount, int pid, int amount, char date[30])
{
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(product_list[i].p_name) < 1)
        {
            break;
        }
        if (product_list[i].p_id == pid)
        {
            product_list[i].quantity -= amount; // q = q - a
            purchased_amount[i] += amount;
            strcpy(product_list[i].lastSold, date);
            char buf[255];
            snprintf(buf, 255, "%s  %d  %s  (%d) have been sold..", date, pid, product_list[i].p_name, amount);
            backup_copying(buf);
        }
    }
}

void update(struct product *product_list, int pid, char date[30])
{
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(product_list[i].p_name) < 1)
        {
            break;
        }
        if (product_list[i].p_id == pid)
        {
            product_list[i].quantity += 15; // q = q + a
            product_list[i].price += 100;
            char buf[255];
            snprintf(buf, 255, "%s  %d  product  (%s)  has been updated..", date, pid, product_list[i].p_name);
            backup_copying(buf);
        }
    }
}

void search(struct product *product_list, int *purchased_amount, char operationCode[20], int pid, int amount, char date[30], char name[40], double price)
{
    if (strcmp(operationCode, "I") == 0)
    {
        insert(product_list, purchased_amount, pid, amount, date, name, price);
    }
    else if (strcmp(operationCode, "S") == 0)
    {
        sell(product_list, purchased_amount, pid, amount, date);
    }
    else if (strcmp(operationCode, "U") == 0)
    {
        update(product_list, pid, date);
    }
    else if (strcmp(operationCode, "D") == 0)
    {
        discount(product_list, date);
    }
}

int main()
{

    struct product product_data[MAX] = {
        {10001, "Scanner", 800, "11.10.19", 120, true},
        {10002, "Printer", 700, "25.02.20", 130, false},
        {10003, "PC", 3000, "23.01.20", 40, false},
        {10004, "Laptop", 3500, "11.10.19", 65, false},
        {10005, "Mouse", 50, "--/--/--", 120, false},
        {10006, "Phone", 5000, "30.01.20", 200, false},
        {10007, "Camera", 4500, "25.03.20", 125, false},
        {10008, "Paper", 35, "11.10.19", 1000, false},
        {10009, "Router", 150, "--/--/--", 340, false},
        {10010, "Hard Disk", 600, "21.05.20", 500, false}};

    struct product *product_list = product_data;

    int purchases[10] = {0};
    int *purchased_amount = purchases;

    char operationCode[20];
    int pid;
    int amount;
    char date[30];
    char name[40];
    double price;

    FILE *file;
    file = fopen("history.txt", "w");
    fclose(file);

    FILE *fptr;
    char line[255];
    fptr = fopen("request.txt", "r");
    if (fptr == NULL)
    {
        printf("Error!");
    }

    while (fgets(line, 100, fptr))
    {
        char *ptr = strtok(line, " "); // string tokenization

        for (int i = 0; i < 6; i++)
        {
            if (i == 0)
            {
                strcpy(operationCode, ptr);
            }
            else if (i == 1)
            {
                pid = atoi(ptr);
            }
            else if (i == 2)
            {
                amount = atoi(ptr);
            }
            else if (i == 3)
            {
                strcpy(date, ptr);
            }
            else if (i == 4)
            {
                strcpy(name, ptr);
            }
            else if (i == 5)
            {
                price = (double)atoi(ptr);
            }
            ptr = strtok(NULL, " ");
        }
        search(product_list, purchased_amount, operationCode, pid, amount, date, name, price);
    }
    FILE *file2;
    file2 = fopen("salesRecords.txt", "w");
    fprintf(file2, "PID         PNAME           PRICE           LAST_SOLD           QUANTITY        DISCOUNT        PURCHASED_AMOUNT  GAIN (TL)");
    char discountValue[10];
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(product_list[i].p_name) < 1)
        {
            break;
        }
        if (product_list[i].discount)
        {
            strcpy(discountValue, "Yes");
        }
        else
        {
            strcpy(discountValue, "No");
        }
        char buf[255];
        snprintf(buf, 255, "\n%d %13s %14.2f %18s %14d %16s %18d %16.2f", product_list[i].p_id, product_list[i].p_name, product_list[i].price,
                 product_list[i].lastSold, product_list[i].quantity, discountValue, purchased_amount[i],
                 (purchased_amount[i] * product_list[i].price));
        fprintf(file2, "%s", buf);
    }
    fclose(file2);

    return 1;
}