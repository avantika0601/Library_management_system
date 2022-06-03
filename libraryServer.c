#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "libraryHeader.h"

char uname[20];
char catagories[][15]={"Computer","Electronics","Electrical","Civil","Mechnnical","Architecture"};
COORD coord = {0, 0};

void selectCategories(){
    system("cls");
    gotoxy(20,5);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SELECT CATEGOIES \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,7);
	printf("\xDB\xDB\xDB\xDB\xB2 1. Computer");
	gotoxy(20,9);
	printf("\xDB\xDB\xDB\xDB\xB2 2. Electronics");
	gotoxy(20,11);
	printf("\xDB\xDB\xDB\xDB\xB2 3. Electrical");
	gotoxy(20,13);
	printf("\xDB\xDB\xDB\xDB\xB2 4. Civil");
	gotoxy(20,15);
	printf("\xDB\xDB\xDB\xDB\xB2 5. Mechanical");
	gotoxy(20,17);
	printf("\xDB\xDB\xDB\xDB\xB2 6. Architecture");
	gotoxy(20,19);
	printf("\xDB\xDB\xDB\xDB\xB2 7. Back to main menu");
	gotoxy(20,21);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

}
void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void readData(book* newBook,int edit)
{
system("cls");
gotoxy(20,3);
if(edit==0)
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Enter the book information \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
else
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Update Book information \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
char bookName[100];
char authorName[100];
gotoxy(20, 7);
printf("\xDB\xDB\xDB\xDB\xB2  Enter the Book name: ");
scanf("%[^\n]%*c",bookName);
strcpy(newBook->name,bookName);
gotoxy(20, 9);
printf("\xDB\xDB\xDB\xDB\xB2  Enter the Author name: ");
scanf("%[^\n]%*c",authorName);
strcpy(newBook->Author,authorName);
gotoxy(20, 11);
printf("\xDB\xDB\xDB\xDB\xB2  Enter the Book id: ");
scanf("%s",newBook->id);
gotoxy(20, 13);
printf("\xDB\xDB\xDB\xDB\xB2  Enter the Book price: ");
scanf("%f",&newBook->price);
gotoxy(20, 15);
printf("\xDB\xDB\xDB\xDB\xB2  Enter the Book quantity: ");
scanf("%d",&newBook->quantity);
gotoxy(20, 17);
printf("\xDB\xDB\xDB\xDB\xB2  Enter the Book rack no.: ");
scanf("%d%*c",&newBook->rackno);
//strcpy(newBook->stname,"--");

//printf("%s",newBook->name);
//printf("%s\n",newBook->name);
//printf("%s\n",newBook->Author);
//printf("%d\n",newBook->id);
//printf("%.2f\n",newBook->price);
//printf("%d\n",newBook->quantity);
//printf("%d",newBook->rackno);

}
void addBook()
{
FILE* books = fopen("books_data.csv","a");
if(books == NULL)
{
    printf("Error: Database could not be accessed!\n");
}
else
{book *newBook = (book*)malloc(sizeof(book));
selectCategories();
gotoxy(20,22);
printf("Enter your choice: ");
int choice;
scanf("%d%*c", &choice);
if(choice==7)
    mainMenu() ;
system("cls");
strcpy(newBook->category,catagories[choice-1]);
readData(newBook,0);
fprintf(books,"%s,%s,%s,%s,%.2f,%d,%d,\n",newBook->id,newBook->category,newBook->name,newBook->Author,newBook->price,newBook->quantity,newBook->rackno);
gotoxy(24, 20);
printf("Book successfully added!");
free(newBook);
newBook=NULL;
gotoxy(24, 22);
printf("Press any key to go back to main menu..");
getc(stdin);
mainMenu();
}
fclose(books);
}

void display(book* aBook)
{
    gotoxy(20, 5);
printf("Category: %s",aBook->category);
gotoxy(20,7);
printf("Book Name: %s\n",aBook->name);
gotoxy(20, 9);
printf("Author Name: %s\n",aBook->Author);
gotoxy(20, 11);
printf("Book id: %s\n",aBook->id);
gotoxy(20, 13);
printf("Price: %.2f\n",aBook->price);
gotoxy(20, 15);
printf("Quantity: %d\n",aBook->quantity);
gotoxy(20, 17);
printf("Rack no: %d\n",aBook->rackno);

}

int byId(char* bookId,char* id_num)
{
return strcmp(bookId,id_num)==0;
}

int byName(char* bookName,char* name)
{
return (strcmp(bookName, name)==0);
}

book* find(char* item,FILE* books)
{
book* foundBook = (book*)malloc(sizeof(book));
int found=0;
while((fscanf(books,"%[^,],%[^,],%[^,],%[^,],%f,%d,%d,%*c",foundBook->id,foundBook->category,foundBook->name,foundBook->Author,&foundBook->price,&foundBook->quantity,&foundBook->rackno))!=EOF)
{

if(byId(foundBook->name,item) || byName(foundBook->id,item))
{
found=1;
break;
}

}
if(found==0)
{
    return NULL;
}
else
{
    return foundBook;
}
}


void search(int stu)
{
system("cls");
gotoxy(20,3);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCH \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
book* foundBook = NULL;
FILE* books = fopen("books_data.csv","r");
if(books == NULL)
{
    printf("Error: Database could not be accessed!\n");
}
else
{
gotoxy(20, 5);
printf("Enter the id or book name: ");
char detail[10];
scanf("%s%*c",detail);
foundBook = find(detail,books);
if(foundBook)
{
    system("cls");

    gotoxy(20, 3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 %s \xB2\xB2\xB2\xB2\xB2\xB2\xB2",foundBook->name);
    display(foundBook);
}
else
{
    gotoxy(20, 7);
    printf("Book not found.\n");
}
fclose(books);
gotoxy(20,20);
printf("Press any key to go back to main menu..");
getc(stdin);
if(stu==1)
    studentMenu();
else
    mainMenu();
}}


void deleteRecord(char* detail,FILE* books,int issuebook,int edit)
{
rewind(books);
book* foundBook = (book*)malloc(sizeof(book));
FILE* newFile = fopen("tmp.csv","w");
while((fscanf(books,"%[^,],%[^,],%[^,],%[^,],%f,%d,%d,%*c",foundBook->id,foundBook->category,foundBook->name,foundBook->Author,&foundBook->price,&foundBook->quantity,&foundBook->rackno))!=EOF)
{
    if(issuebook==1)
    {
    if((strcmp(detail,foundBook->id)==0) || (strcmp(detail,foundBook->name)==0))
    {
        foundBook->quantity=foundBook->quantity-1;
        fprintf(newFile,"%s,%s,%s,%s,%.2f,%d,%d,\n",foundBook->id,foundBook->category,foundBook->name,foundBook->Author,foundBook->price,foundBook->quantity,foundBook->rackno);

    }
    else
    {
        fprintf(newFile,"%s,%s,%s,%s,%.2f,%d,%d,\n",foundBook->id,foundBook->category,foundBook->name,foundBook->Author,foundBook->price,foundBook->quantity,foundBook->rackno);
    }
    }
    else if(edit==1)
    {
        if((strcmp(detail,foundBook->id)==0))
        {

            readData(foundBook,1);

        }
        fprintf(newFile,"%s,%s,%s,%s,%.2f,%d,%d,\n",foundBook->id,foundBook->category,foundBook->name,foundBook->Author,foundBook->price,foundBook->quantity,foundBook->rackno);
    }
    else
    {
        if(!(strcmp(detail,foundBook->id)==0) || (strcmp(detail,foundBook->name)==0))
            fprintf(newFile,"%s,%s,%s,%s,%.2f,%d,%d,\n",foundBook->id,foundBook->category,foundBook->name,foundBook->Author,foundBook->price,foundBook->quantity,foundBook->rackno);
    }



}
fclose(books);
fclose(newFile);
remove("books_data.csv");
rename("tmp.csv","books_data.csv");

}
void deleteBook()
{
system("cls");
gotoxy(20, 3);
printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 DELETE BOOK \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
book* foundBook = NULL;
FILE* books = fopen("books_data.csv","r");
if(books == NULL)
{
    printf("Error: Database could not be accessed.\n");
}
else
{
gotoxy(20, 7);
printf("\xDB\xDB\xDB\xDB\xB2 Enter the id or book name: ");
char detail[10];
scanf("%s%*c",detail);
foundBook = find(detail,books);
if(foundBook)
{
    system("cls");
    gotoxy(20, 3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2 %s \xB2\xB2\xB2\xB2\xB2\xB2\xB2",foundBook->name);
    gotoxy(20, 5);
    printf("Book Found.\n");
    display(foundBook);
    gotoxy(20,19);
    printf("Press y to delete n to go back to mainmenu..");
    char ch = getc(stdin);
    if(ch=='y')
    {deleteRecord(detail,books,0,0);
    gotoxy(20, 21);
    printf("Book deleted successfully!\n");}
    else{
        mainMenu();
    }
    //read();
}
else
{
    gotoxy(20,15);
    printf("Book not found.\n");
}
}
gotoxy(20,20);
fflush(stdin);
printf("Press any key to go back to main menu..");
getc(stdin);
mainMenu();
fclose(books);
}

void issue()
{
    system("cls");
    FILE* books = fopen("books_data.csv","r+");
    gotoxy(20,1);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  ISSUE \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,2);
    printf("Enter the id or the book name: ");
    char input[20];
    scanf("%[^\n]%*c",input);
    book* foundBook = find(input,books);
    if(foundBook)
    {
       FILE* borrowed = fopen("borrowed_books.csv","a");
       gotoxy(20,4);
       printf("Book Available.");
       display(foundBook);
       // printf("Issue date: %s",ctime(&issueDate));
        gotoxy(20,20);
        printf("Press y to issue the book or n to go to main menu..");
        char ch = getc(stdin);
        if (ch=='y')
        {
        gotoxy(20,22);
        printf("Enter the member id of the borrower: ");
        char id[10];
        scanf("%s%*c",id);
        deleteRecord(input,books,1,0);
        time_t t;
        time(&t);
        fprintf(borrowed,"%s,%s,%s,%s",foundBook->id,foundBook->name,id,ctime(&t));
        gotoxy(20,23);
        printf("Book Successfully issued.");
        fclose(borrowed);
        }
        else
        {
            mainMenu();
        }
    }
    else
    {
        gotoxy(20, 5);
        printf("Book not available/not found.\n");
    }
fclose(books);
gotoxy(20, 24);
printf("Press any key to go back to main menu..");
getc(stdin);
mainMenu();
}

void editbooks()  //edit information about book
{
	system("cls");
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Edit book information \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
	FILE* books = fopen("books_data.csv","r+");
	printf("\xDB\xDB\xDB\xDB\xB2 Enter the id of the book: ");
	char id[10];
	scanf("%s%*c",id);
	char* bookId;
	book* aBook = (book*)malloc(sizeof(book));
	char line[200];
	int found=0;
	while((fgets(line,200,books))!=NULL)
    {

        bookId = strtok(line,",");
        if(byId(bookId,id))
        {
            found=1;
            gotoxy(20,7);
            printf("Book Found.");
            gotoxy(20,9);
            printf("Book id: %s",bookId);
            gotoxy(20,11);
            strtok(NULL,",");
            printf("Book name: %s",strtok(NULL,","));
            gotoxy(20,13);
            printf("Press any key to enter new information..");
            getc(stdin);
            system("cls");
            break;
        }
    }
    gotoxy(20,20);
    if(found==1)
    {
    rewind(books);
    deleteRecord(id,books,0,1);
    gotoxy(20,20);
    printf("Data successfully updated!\n");
    }
    else
    {
        printf("Book not found.");
    }
    gotoxy(20,22);
    printf("Press any key to go back to main menu..");
    getc(stdin);
    mainMenu();
    fclose(books);


}

void logout(){
    system("cls");

    for(int i=3;i>=0;i--)
    {
        gotoxy(16, 5);
        printf("logging out in %d second...........>",i);
        Sleep(1000);
    }

    exit(0);
}

void viewbooks()  //show the list of book persists in library
{
    FILE *books = fopen("books_data.csv","r");
    book* foundBook = (book*)malloc(sizeof(book));
    book aBook;
    system("cls");
    gotoxy(25,1);
    printf("-------Book List-------");
    gotoxy(2,3);
    printf(" CATEGORY     ID      BOOK NAME         AUTHOR       QTY     PRICE     RackNo ");
    int j=4;
    while((fscanf(books,"%[^,],%[^,],%[^,],%[^,],%f,%d,%d,%*c",aBook.id,aBook.category,aBook.name,aBook.Author,&aBook.price,&aBook.quantity,&aBook.rackno))!=EOF){
        gotoxy(3,j);
        printf("%s",aBook.category);
        gotoxy(16,j);
        printf("%s",aBook.id);
        gotoxy(24,j);
        printf("%s",aBook.name);
        gotoxy(43,j);
        printf("%s",aBook.Author);
        gotoxy(55,j);
        printf("%d",aBook.quantity);
        gotoxy(62,j);
        printf("%.2f",aBook.price);
        gotoxy(75,j);
        printf("%d",aBook.rackno);
        printf("\n\n");
        j++;
    }
    fclose(books);
    gotoxy(20,22);
    printf("Press any key to go back to main menu..");
    getc(stdin);
    mainMenu();

}

void mainMenu()
{
    system("cls");
        gotoxy(20,3);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,5);
        printf("\xDB\xDB\xDB\xDB\xB2 1. Add Books   ");
        gotoxy(20,7);
        printf("\xDB\xDB\xDB\xDB\xB2 2. Delete Book");
        gotoxy(20,9);
        printf("\xDB\xDB\xDB\xDB\xB2 3. Search Book");
        gotoxy(20,11);
        printf("\xDB\xDB\xDB\xDB\xB2 4. View Book List");
        gotoxy(20,13);
        printf("\xDB\xDB\xDB\xDB\xB2 5. Edit Book Record ");
        gotoxy(20,15);
        printf("\xDB\xDB\xDB\xDB\xB2 6. Issue");
        gotoxy(20,17);
        printf("\xDB\xDB\xDB\xDB\xB2 7. Logout");
        gotoxy(20,19);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,21);
        printf("Enter your choice: ");
        char ch = getch();
        switch(ch){
            case '1':
                addBook();
                break;
            case '2':
                deleteBook();
                break;
            case '3':
                search(0);
                break;
            case '4':
                viewbooks();
                break;
            case '5':
                editbooks();
                break;
            case '6':
                issue();
                break;
            case '7':
                logout();

            default:
                gotoxy(10,23);
                printf("\aWrong Entry!!Please re-enter the correct option");
                Sleep(2000);
                mainMenu();

        }
}

void profile(char* usn)
{
    system("cls");
    FILE* students = fopen("students_data.csv","r");
    student aStudent;
    int found=0;
    while((fscanf(students,"%[^,],%[^,],%[^,],%[^,],%*c",aStudent.username,aStudent.password,aStudent.name,aStudent.srn))!=EOF)
    {
        //printf("%s %s %s %s\n",aStudent.username,aStudent.password,aStudent.name,aStudent.srn);
        if(strcmp(usn,aStudent.username)==0)
        {
            found=1;
            gotoxy(28,1);
            printf("My Card");
            gotoxy(20,3);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(20,4);printf("\xB2");gotoxy(45,4);printf("\xB2");
            gotoxy(20,5);printf("\xB2");gotoxy(45,5);printf("\xB2");
            gotoxy(20,6);printf("\xB2");gotoxy(45,6);printf("\xB2");
            gotoxy(20,7);printf("\xB2");gotoxy(45,7);printf("\xB2");
            gotoxy(20,8);printf("\xB2");gotoxy(45,8);printf("\xB2");
            gotoxy(20,9);printf("\xB2");gotoxy(45,9);printf("\xB2");
            gotoxy(20,10);printf("\xB2");gotoxy(45,10);printf("\xB2");
            gotoxy(20,11);printf("\xB2");gotoxy(45,11);printf("\xB2");
            gotoxy(20,12);printf("\xB2");gotoxy(45,12);printf("\xB2");
            gotoxy(20,13);printf("\xB2");gotoxy(45,13);printf("\xB2");
            gotoxy(20,14);printf("\xB2");gotoxy(45,14);printf("\xB2");
            gotoxy(20,15);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(22,5);
            printf("Name: %s",aStudent.name);
            gotoxy(22, 7);
            printf("Srn: %s",aStudent.srn);
            gotoxy(22,9);
            printf("Username: %s",aStudent.username);

            break;

            //printf("Name: %s",aStudent.name);
        }


    }
    gotoxy(20,20);
    if(found==0)
        printf("Not found");
    gotoxy(20,22);
    printf("Press any key to go back to main menu..");
            fflush(stdin);
            getc(stdin);
            studentMenu();
    fclose(students);
}
void updateFile(char* usn, char* newpassword)
{
    FILE* students = fopen("students_data.csv","r");
    student *aStudent = (student*)calloc(1,sizeof(student));
    FILE* newFile = fopen("tmp.csv","w");
    while((fscanf(students,"%[^,],%[^,],%[^,],%[^,],%*c",aStudent->username,aStudent->password,aStudent->name,aStudent->srn))!=EOF)
    {
        if(strcmp(aStudent->username,usn)==0)
        {
            strcpy(aStudent->password,newpassword);
        }
        fprintf(newFile,"%s,%s,%s,%s,\n",aStudent->username,aStudent->password,aStudent->name,aStudent->srn);
    }

fclose(students);
fclose(newFile);
remove("students_data.csv");
rename("tmp.csv","students_data.csv");

}
void changePasswordStudent(char* usn)
{
    system("cls");
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 CHANGE PASSWORD \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    char oldpassword[10];
    char newpassword[10];
    student aStudent;
    gotoxy(20, 5);
    printf("Enter old password: ");
    scanf("%s%*c",oldpassword);
    int found=0;
    FILE* students = fopen("students_data.csv","r+");
    while((fscanf(students,"%[^,],%[^,],%[^,],%[^,],%*c",aStudent.username,aStudent.password,aStudent.name,aStudent.srn))!=EOF)
    {
        //printf("%s %s\n",oldpassword,aStudent.password);
        //printf("%s %s\n",aStudent.username,usn);
        if(strcmp(aStudent.username,usn)==0 && strcmp(oldpassword,aStudent.password)==0)
        {
            gotoxy(20,7);
                found=1;

                printf("Enter new password: ");
                scanf("%s%*c",newpassword);
                strcpy(aStudent.password,newpassword);
                fclose(students);
                updateFile(usn,newpassword);
                gotoxy(20,9);
                printf("Password updated successfully.");
                break;


        }
    }
    gotoxy(20,20);
    if(found==0)
        printf("Incorrect password or username!");
    gotoxy(20,22);
        printf("Press any key to go back to main menu..");
            getc(stdin);
            studentMenu();
}

void borrowed(char* srn)
{
    system("cls");
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BORROWED BOOKS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    FILE* borrowed = fopen("borrowed_books.csv","r");
    char bookname[20];
    char bookId[10];
    char dateIssued[30];
    char studSrn[20];
    int found=0;
    int j=5;
    while((fscanf(borrowed,"%[^,],%[^,],%[^,],%[^\n]%*c",bookId,bookname,studSrn,dateIssued))!=EOF)
    {
        if(strcmp(studSrn,srn)==0)
        {
            gotoxy(20,j);
            found++;
            printf("Book NO.: %d\n",found);
            gotoxy(20,j+1);
            printf("Book Name: %s\n",bookname);
            gotoxy(20,j+2);
            printf("Book Id: %s\n",bookId);
            gotoxy(20,j+3);
            printf("Date Issued: %s\n\n",dateIssued);
            j=j+7;
        }
    }
    if(found==0)
    {
        gotoxy(20,7);
        printf("No book borrowed.\n");
    }
    fflush(stdin);
    gotoxy(20,j+2);
            printf("Press any key to go back to main menu..");
            getc(stdin);
            fclose(borrowed);
            studentMenu();


}
void studentMenu()
{
    system("cls");
        gotoxy(20,3);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,5);
        printf("\xDB\xDB\xDB\xDB\xB2 1. My Card");
        gotoxy(20,7);
        printf("\xDB\xDB\xDB\xDB\xB2 2. Borrowed books");
        gotoxy(20,9);
        printf("\xDB\xDB\xDB\xDB\xB2 3. Search Book");
        gotoxy(20,11);
        printf("\xDB\xDB\xDB\xDB\xB2 4. Change Password");
        gotoxy(20,13);
        printf("\xDB\xDB\xDB\xDB\xB2 5. Logout");
        gotoxy(20,15);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,21);
        printf("Enter your choice: ");
        char ch = getchar();
        switch(ch){
            case '1':
                profile(uname);
                break;
            case '2':
                borrowed("pes1ug20cs625");
                break;
            case '3':
                search(1);
                break;
            case '4':
                changePasswordStudent(uname);
                break;
            case '5':
                logout();
                break;
            default:
                gotoxy(10,23);
                printf("\aWrong Entry!!Please re-enter the correct option");
                Sleep(2000);
                studentMenu();

    }}

void adminLogin()
{
    int found=0;
    while(found==0)
    {
    system("cls");
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADMIN \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
        printf("\xDB\xDB\xB2 USERNAME: ");
        gotoxy(20,7);
        printf("\xDB\xDB\xB2 PASSWORD: ");
FILE*fp=fopen("admin_account.csv","r");
char get_data[1000];
char *user_name;
char password[100];
char my_user_name[100];
char my_password[100];
    gotoxy(35,5);
    scanf("%s",my_user_name);
    fflush(stdin);
    gotoxy(35,7);
    scanf("%s",my_password);
    admin* anAdmin = (admin*)calloc(1,sizeof(admin));


    fflush(stdin);
    int i=0;

    while(fgets(get_data,1000,fp)!=NULL)
    {
        user_name=strtok(get_data,",");
        strcpy(anAdmin->name,user_name);
        user_name=strtok(NULL,",");
        strcpy(anAdmin->code,user_name);



        if (strcmp(anAdmin->name,my_user_name)==0 && strcmp(anAdmin->code,my_password)==0)
        {
            found=1;
            mainMenu();
        }


    }
    if(found==0)
    {
        gotoxy(20,9);
            printf("inavalid user name or password\n");
            Sleep(2000);


    }
}}


void studentLogin()
        {
            int success=0;
            while(success==0)
            {
            system("cls");
            gotoxy(20,3);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
        printf("\xDB\xDB\xB2 USERNAME: ");
        gotoxy(20,7);
        printf("\xDB\xDB\xB2 PASSWORD: ");
            int i=0;
            char name[100];
            char SRN[100];
            char password[100];
            char *details;
            char fetch[1000];
            FILE *fp=fopen("students_data.csv","r");
            gotoxy(35,5);
            scanf("%s",uname);
            fflush(stdin);
            gotoxy(35,7);
            scanf("%s",password);
            fflush(stdin);
            student* s = (student*)calloc(1,sizeof(student));
            while (fgets(fetch,1000,fp)!=NULL)
            {
                details=strtok(fetch,",");
                strcpy(s->username,details);
                details=strtok(NULL,",");
                strcpy(s->password,details);
                details=strtok(NULL,",");
                (s->name,details);
                details=strtok(NULL,",");
                strcpy(s->srn,details);
                if(strcmp(s->username,uname)==0 && strcmp(s->password,password)==0)
                {
                    success=1;
                    fclose(fp);
                    studentMenu();
                }
                else
                {
                    success=0;
                    gotoxy(20, 11);
                    printf("Invalid information\n");
                    fclose(fp);
                    Sleep(2000);
                }
            }
            fclose(fp);

        }}
void new_user()
            {

                system("cls");
            gotoxy(20,3);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 STUDENT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(20,5);
            printf("\xDB\xDB\xDB\xDB\xB2 Name: ");
        gotoxy(20,7);
        printf("\xDB\xDB\xDB\xDB\xB2 SRN: ");
        gotoxy(20,9);
        printf("\xDB\xDB\xDB\xDB\xB2 SET USERNAME: ");
        gotoxy(20,11);
        printf("\xDB\xDB\xDB\xDB\xB2 SET PASSWORD: ");
                char name[100];
                char SRN[100];
                char username[100];
                char password[100];
                FILE *fp=fopen("students_data.csv","a+");
                gotoxy(33,5);
                scanf("%[^\n]",name);
                fflush(stdin);
                gotoxy(32,7);
                scanf("%s",SRN);
                  fflush(stdin);
                  gotoxy(41,9);
                scanf("%s",username);
                  fflush(stdin);
                  gotoxy(41,11);
                scanf("%s",password);
                  fflush(stdin);



                fprintf(fp,"%s,%s,%s,%s,\n",username,password,name,SRN);

                /*
                fputs(strcat(name,","),fp);
                fseek(fp,-2,SEEK_END);
                fputs(strcat(SRN,","),fp);
                 fseek(fp,-2,SEEK_END);
                fputs(strcat(username,","),fp);
                fseek(fp,-2,SEEK_END);
                fputs(strcat(password,","),fp);
                 fseek(fp,-2,SEEK_END);*/
                 gotoxy(20,13);
                 printf("your credentials have been accepted\n");
                 fclose(fp);
                 Sleep(2000);
                 login();






        }

void login()
{


    int my_choice;

    char ch='y';
    gotoxy(20,3);


    while(ch=='y')
    {
        system("cls");
        gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 LIBRARY MANAGEMENT SYSTEM \xB2\xB2\xB2\xB2");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
            gotoxy(20,4);printf("\xB2");gotoxy(80,4);printf("\xB2");
            gotoxy(20,5);printf("\xB2");gotoxy(80,5);printf("\xB2");
            gotoxy(20,6);printf("\xB2");gotoxy(80,6);printf("\xB2");
            gotoxy(20,7);printf("\xB2");gotoxy(80,7);printf("\xB2");
            gotoxy(20,8);printf("\xB2");gotoxy(80,8);printf("\xB2");
            gotoxy(20,9);printf("\xB2");gotoxy(80,9);printf("\xB2");
            gotoxy(20,10);printf("\xB2");gotoxy(80,10);printf("\xB2");
            gotoxy(20,11);printf("\xB2");gotoxy(80,11);printf("\xB2");
            gotoxy(20,12);printf("\xB2");gotoxy(80,12);printf("\xB2");
            gotoxy(20,13);printf("\xB2");gotoxy(80,13);printf("\xB2");
            gotoxy(20,14);printf("\xB2");gotoxy(80,14);printf("\xB2");
            gotoxy(20,15);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(43,5);
   printf("LOGIN");
   gotoxy(22,7);
        printf("1. ADMIN");
        gotoxy(22,9);
        printf("2. STUDENT");
        gotoxy(22,11);
        printf("3. NEW USER");
    gotoxy(22,13);
    printf("4. EXIT");
    gotoxy(22,18);
    printf("Enter your choice: ");
    scanf("%d%*c",&my_choice);
    switch (my_choice)
    {
    case 1:adminLogin();
    ch='n';
    break;
    case 2:studentLogin();
    ch='n';
    break;
    case 3:new_user();
    ch='n';
    break;
    case 4:exit(0);
    break;
    default:
        gotoxy(20,16);
        printf("Enter a valid choice.");
        Sleep(2000);
        ch='y';
    }
 }   }
