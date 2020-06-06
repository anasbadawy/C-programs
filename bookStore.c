#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct writer_info
{
    char name[20];
    char surname[20];
    int number_of_book;
};
struct book_info
{
    char book_name[20];
    struct writer_info writer;
    int first_publication_year;
};
void print_book_info(struct book_info *book_list)
{
    printf("\nBook Name                    Writer name - surname                first publication year\n\n");
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            break;
        }
        printf("%d. %8s %27s %12s %30d\n", i + 1, book_list[i].book_name, book_list[i].writer.name, book_list[i].writer.surname, book_list[i].first_publication_year);
    }
}

void search_book(struct book_info searchedBook, struct book_info *book_list)
{
    int exist = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            break;
        }
        if (strcmp(book_list[i].book_name, searchedBook.book_name) == 0 ||
            book_list[i].first_publication_year == searchedBook.first_publication_year || strcmp(searchedBook.writer.name, book_list[i].writer.name) == 0 || strcmp(searchedBook.writer.surname, book_list[i].writer.surname) == 0)
        {
            printf("\n\nNumber of book is %d.\n\n", i + 1);
            exist = 1;
        }
    }
    if (exist == 0)
    {
        printf("\n\nPlease note that one writer can have more than one book, or first publication year can be the same for different books.\n\n");
    }
}

void find_writer_info(struct book_info *book_list, char bookName[20])
{
    int exist = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            break;
        }
        if (strcmp(book_list[i].book_name, bookName) == 0)
        {
            printf("\n%s has found in the list.\nWriter name is:  %s.\nNumber of writer's is: %d.\n\n", bookName, book_list[i].writer.name, book_list[i].writer.number_of_book);
            exist = 1;
        }
    }
    if (exist == 0)
    {
        printf("\n%s is not found on the list.\n", bookName);
    }
}

struct book_info create_new_book(char bName[20], struct writer_info writer, int pubYear)
{
    struct book_info newBook;
    strcpy(newBook.book_name, bName);
    newBook.writer = writer;
    newBook.first_publication_year = pubYear;
    return newBook;
}

void add_new_book(struct book_info *book_list, struct book_info newBook)
{
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) > 0)
        {
            continue;
        }
        else
        {
            strcpy(book_list[i].book_name, newBook.book_name);
            book_list[i].first_publication_year = newBook.first_publication_year;
            book_list[i].writer = newBook.writer;
            break;
        }
    }
}

void remove_book(struct book_info *book_list, int index)
{
    for (int i = index - 1; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            break;
        }
        book_list[i] = book_list[i + 1];
    }
    print_book_info(book_list);
}
int main(void)
{
    struct writer_info writer_list[] = {
        {"name1", "surname1", 6},
        {"name2", "surname2", 3},
        {"name3", "surname3", 23},
        {"name4", "surname4", 21},
        {"name5", "surname5", 6},
        {"name6", "surname6", 4},
        {"name7", "surname7", 1},
        {"name8", "surname8", 5},
        {"name9", "surname9", 3},
        {"name10", "surname10", 2},
    };
    struct book_info books_data[] = {
        {"book1", writer_list[0], 1990},
        {"book2", writer_list[1], 1880},
        {"book3", writer_list[2], 1992},
        {"book4", writer_list[3], 2011},
        {"book5", writer_list[4], 2015},
        {"book6", writer_list[5], 1924},
        {"book7", writer_list[6], 1954},
        {"book8", writer_list[7], 2010},
        {"book9", writer_list[8], 2001},
        {"book10", writer_list[9], 1983},
    };
    struct book_info *book_list = books_data;

    int choice = 0;
    while (choice != 6)
    {
        printf("Enter number of option that you want to do \n\n");
        printf("1- print book list\n");
        printf("2- search book\n");
        printf("3- search writer \n");
        printf("4- add new book\n");
        printf("5- remove book\n");
        printf("6- exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            print_book_info(book_list);
            break;
        }
        case 2:
        {
            int searchOption;
            printf("\n1. enter book name: ");
            printf("\n2. enter writer name: ");
            printf("\n3. enter writer surname: ");
            printf("\n4. enter publication date: ");

            printf("\nchoose searching book option: ");
            scanf("%d", &searchOption);
            char temp[20];
            struct book_info book_temp;

            switch (searchOption)
            {
            case 1:
            {
                printf("\nenter book name: ");
                scanf("%s", temp);
                strcpy(book_temp.book_name, temp);
                search_book(book_temp, book_list);
                break;
            }
            case 2:
            {
                printf("\nenter writer name: ");
                scanf("%s", temp);
                strcpy(book_temp.writer.name, temp);
                search_book(book_temp, book_list);
                break;
            }
            case 3:
            {
                printf("\nenter writer surname: ");
                scanf("%s", temp);
                strcpy(book_temp.writer.surname, temp);
                search_book(book_temp, book_list);
                break;
            }
            case 4:
            {
                int tempInt;
                scanf("%d", &tempInt);
                printf("\nenter publication date: ");
                book_temp.first_publication_year = tempInt;
                search_book(book_temp, book_list);
                break;
            }
            default:
                printf("\n\nYou entered a non exist option.\n\n");
            }
            break;
        }
        case 3:
        {
            printf("\nEnter book name to find book's writer info : ");
            char temp[20];
            scanf("%s", temp);
            find_writer_info(book_list, temp);
            break;
        }
        case 4:
        {
            char bName[20], wName[20], wSurname[20];
            int pubYear, bookNum;
            printf("\nPlease enter new book information > \n");
            printf("\nBook Name: ");
            scanf("%s", bName);
            printf("\nWriter Name: ");
            scanf("%s", wName);
            printf("\nWriter surname: ");
            scanf("%s", wSurname);
            printf("\nFirst PubicatiYear: ");
            scanf("%d", &pubYear);
            printf("\nNumber of writer's book: ");
            scanf("%d", &bookNum);
            struct writer_info newWriter;
            strcpy(newWriter.name, wName);
            strcpy(newWriter.surname, wSurname);
            newWriter.number_of_book = bookNum;
            struct book_info newBook = create_new_book(bName, newWriter, pubYear);
            add_new_book(book_list, newBook);
            break;
        }
        case 5:
        {
            int removedBook;
            printf("\nEnter Position of book you want to remove: ");
            scanf("%d", &removedBook);
            remove_book(book_list, removedBook);
            break;
        }
        }
    }
    return 0;
}