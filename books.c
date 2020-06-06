#include <stdio.h>
#include <string.h>
#define MAX 100

struct writer_info
{
    char name[15];
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

void search_book(struct book_info *book_list, struct book_info searchedBook)
{
    int ifNotExist = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            break;
        }
        if (strcmp(book_list[i].book_name, searchedBook.book_name) == 0 || strcmp(book_list[i].writer.name, searchedBook.writer.name) == 0 || strcmp(book_list[i].writer.surname, searchedBook.writer.surname) == 0 || book_list[i].first_publication_year == searchedBook.first_publication_year)
        {
            printf("Number of book is %d.\n", i + 1);
            ifNotExist = 1;
        }
    }
    if (ifNotExist == 0)
    {
        printf("Please note that one writer can have more than one book, or first publication year can be the same for different books");
    }
}

void find_writer_info(struct book_info *book_list, char *book_name)
{
    int ifNotExist = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            break;
        }
        if (strcmp(book_list[i].book_name, book_name) == 0)
        {
            printf("\n%s has found in the list. \n", book_name);
            printf("Writer name    : %s %s.\n", book_list[i].writer.name, book_list[i].writer.surname);
            printf("Number of writer's book   : %d.\n", book_list[i].writer.number_of_book);
            ifNotExist = 1;
        }
    }
    if (ifNotExist == 0)
    {
        printf("%s is not found in the list.\n", book_name);
    }
}

struct book_info create_new_book(char *bName, struct writer_info writer, int pubYear)
{
    struct book_info newbook;
    strcpy(newbook.book_name, bName);
    newbook.writer = writer;
    newbook.first_publication_year = pubYear;
    return newbook;
}

void add_new_book(struct book_info *book_list, struct book_info newbook)
{
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            book_list[i] = newbook;
            break;
        }
    }
}

void remove_book(struct book_info *book_list, int index)
{

    for (int i = index-1; i < MAX; i++)
    {
        if (strlen(book_list[i].book_name) < 1)
        {
            break;
        }
        book_list[i]=book_list[i+1];
    }
    print_book_info(book_list);
}
int main(void)
{

    struct writer_info writer_list[MAX] = {
        {"anas", "badawi", 3},
        {"abdelwahab", "ali", 5},
        {"kinan", "dori", 1},
        {"eda", "ulu", 8},
        {"ahmet", "korkmaz", 11},
        {"khaled", "mehmet", 13},
        {"seif", "ashoush", 20},
        {"ragab", "shwki", 1},
        {"john", "dori", 9},
        {"ramy", "tawfik", 2}};

    struct book_info book_data[MAX] = {
        {"book1", writer_list[0], 1990},
        {"book2", writer_list[1], 1991},
        {"book3", writer_list[2], 1993},
        {"book4", writer_list[3], 1999},
        {"book5", writer_list[4], 2000},
        {"book6", writer_list[5], 1980},
        {"book7", writer_list[6], 2001},
        {"book8", writer_list[7], 2011},
        {"book9", writer_list[8], 2019},
        {"book10", writer_list[9], 2011}};

    struct book_info *book_list = book_data;

    int option;
    while (option != 6)
    {
        printf("Option number :\n\n");
        printf("1. print \n");
        printf("2. search book \n");
        printf("3. search writer \n");
        printf("4. add book \n");
        printf("5. remove book \n");
        printf("6. quit \n\n");
        printf("Your Choice: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            print_book_info(book_list);
            break;
        }
        case 2:
        {
            printf("\nchoose one of searching options\n\n");
            printf("1. book name \n");
            printf("2. writer name \n");
            printf("3. writer surname \n");
            printf("4. publication date \n");
            printf("\nYour choice: ");
            int searchOption;
            scanf("%d", &searchOption);
            char temp[20];
            struct book_info searchedBook;
            switch (searchOption)
            {
            case 1:
                printf("\nEnter book name > ");
                scanf("%s", temp);
                strcpy(searchedBook.book_name, temp);
                search_book(book_list, searchedBook);
                break;

            case 2:
                printf("\nEnter writer name > ");
                scanf("%s", temp);
                strcpy(searchedBook.writer.name, temp);
                search_book(book_list, searchedBook);
                break;

            case 3:
                printf("\nEnter writer surname > ");
                scanf("%s", temp);
                strcpy(searchedBook.writer.surname, temp);
                search_book(book_list, searchedBook);
                break;

            case 4:
                printf("\nEnter publication date > ");
                int pubDate;
                scanf("%d", &pubDate);
                searchedBook.first_publication_year = pubDate;
                search_book(book_list, searchedBook);
                break;
            }
            break;
        }
        case 3:
        {
            printf("\nEnter book name to find book's writer info : ");
            char bookName[20];
            scanf("%s", bookName);
            char *bookNampPtr;
            bookNampPtr = bookName;
            find_writer_info(book_list, bookNampPtr);
            break;
        }
        case 4:
        {
            char bookName2[20];
            char writerName[20];
            char writerSurname[20];
            int pubDate, bookNum;
            printf("\nPlease enter new book information>\n\n");
            printf("Book Name                         :");
            scanf("%s", bookName2);
            printf("Writer Name                       :");
            scanf("%s", writerName);
            printf("Writer Surname                    :");
            scanf("%s", writerSurname);
            printf("First Publication year             :");
            scanf("%d", &pubDate);
            printf("Number of writer's books           :");
            scanf("%d", &bookNum);
            struct writer_info writer;
            strcpy(writer.name, writerName);
            strcpy(writer.surname, writerSurname);
            writer.number_of_book = bookNum;
            char *bookNampPtr2 = bookName2;
            struct book_info newbook = create_new_book(bookNampPtr2, writer, pubDate);
            add_new_book(book_list, newbook);
            break;
        }
        case 5:
        {
            printf("\nEnter position of book you want to remove: ");
            int removedIndex;
            scanf("%d", &removedIndex);
            remove_book(book_list, removedIndex);

            break;
        }
        }
    }

    return 0;
}
