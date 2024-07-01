#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void addModel();
void modelList();
void del();
void carBooking();
void bookedList();
void cdel();
struct cars
{
    int modelId;
    char carName[50];
    char date[12];
} b;
struct customer
{
    int modelId;
    char cName[50];
    char cAddress[50];
    char cPhno[11];
    char carName[50];
    char date[12];
} s;
FILE *fp;
int main()
{
    int ch;
    while (1)
    {
        system("cls");
        printf("<== Car Booking System ==>\n");
        printf("1.Add New Model\n");
        printf("2. Car Model List\n");
        printf("3.Remove Car Model\n");
        printf("4.Book Car\n");
        printf("5.Car Booked List\n");
        printf("6.Remove booking\n");
        printf("0.Exit\n\n");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            exit(0);
        case 1:
            addModel();
            break;
        case 2:
            modelList();
            break;
        case 3:
            del();
            break;
        case 4:
            carBooking();
            break;
        case 5:
            bookedList();
            break;
        case 6:
            cdel();
            break;
        default:
            printf("Invalid Choice...\n\n");
        }
        printf("Press Any Key To Continue...");
        getch();
    }
    return 0;
}
void addModel()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1,
            tm.tm_year + 1900);
    strcpy(b.date, myDate);
    fp = fopen("cars.txt", "ab");
    printf("Enter model id: ");
    scanf("%d", &b.modelId);
    printf("Enter car name: ");
    fflush(stdin);
    gets(b.carName);
    printf("Car Added Successfully");
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}
void modelList()
{
    system("cls");
    printf("<== Available Car Models ==>\n\n");
    printf("%-10s %-30s %s\n\n", "Model id", "Car Name", "Date");
    fp = fopen("cars.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        printf("%-10d %-30s %s\n", b.modelId, b.carName, b.date);
    }
    fclose(fp);
}
void del()
{
    int id, f = 0;
    system("cls");
    printf("<== Remove Car Model ==>\n\n");
    printf("Enter Model id to remove: ");
    scanf("%d", &id);
    FILE *ft;
    fp = fopen("cars.txt", "rb");
    ft = fopen("temp.txt", "wb");
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (id == b.modelId)
        {
            f = 1;
        }
        else
        {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }
    if (f == 1)
    {
        printf("\n\nDeleted Successfully.");
    }
    else
    {
        printf("\n\nRecord Not Found !");
    }
    fclose(fp);
    fclose(ft);
    remove("cars.txt");
    rename("temp.txt", "cars.txt");
}
void carBooking()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1,
            tm.tm_year + 1900);
    strcpy(s.date, myDate);
    int f = 0;
    system("cls");
    printf("<== Car Booking ==>\n\n");
    printf("Enter Model id to issue: ");
    scanf("%d", &s.modelId);
    // Check if we have model of given id
    fp = fopen("cars.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (b.modelId == s.modelId)
        {
            strcpy(s.carName, b.carName);
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        printf("No model found with this id\n");
        printf("Please try again...\n\n");
        return;
    }
    fp = fopen("issue.txt", "ab");
    printf("Enter Customer Name: ");
    fflush(stdin);
    gets(s.cName);
    printf("Enter Customer Address: ");
    fflush(stdin);
    gets(s.cAddress);
    printf("Enter Customer Phone no.: ");
    fflush(stdin);
    gets(s.cPhno);
    printf("Booked Successfully\n\n");
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}
void bookedList()
{
    system("cls");
    printf("<== Booked Car List ==>\n\n");
    printf("%-10s %-30s %-30s %-15s %-30s %s\n\n", "modelId",
           "Name", "Address", "Phone no.", "Car Name", "Date");
    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("%-10d %-30s %-30s %-15s %-30s %s\n", s.modelId,
               s.cName, s.cAddress, s.cPhno, s.carName, s.date);
    }
    fclose(fp);
}
void cdel()
{
    struct delc
    {
        char name1[50];
    } p;
    int f = 0;
    system("cls");
    printf("<== Remove Car Model ==>\n\n");
    printf("Enter Customer Name to remove: ");
    fflush(stdin);
    scanf("%s", p.name1);
    FILE *ft;
    fp = fopen("issue.txt", "rb");
    ft = fopen("temp1.txt", "wb");
    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (strcmp(s.cName, p.name1) == 0)
        {
            f = 0;
            continue;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, ft);
        }
    }
    if (f == 0)
    {
        printf("\n\nDeleted Successfully.\n");
    }
    else
    {
        printf("\n\nRecord Not Found !");
    }
    fclose(fp);
    fclose(ft);
    remove("issue.txt");
    rename("temp1.txt", "issue.txt");
}
