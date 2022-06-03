#include <stdio.h>
void login();
typedef struct book_details
{
char id[10];
char category[20];
char name[20];
char Author[20];
int quantity;
float price;
int rackno;
}book;

typedef struct adminDetails
{
    char name[100];
    char code[100];
}admin;

typedef struct student_details
{
char name[20];
char password[10];
char username[20];
char srn[15];
char dateJoined[25];
}student;


void mainMenu();
void studentMenu();
void logout();
void viewbooks();
void selectCategories();
void gotoxy (int x, int y);

void readData(book* newBook,int edit);
void addBook();
void display(book* aBook);
int byId(char* bookId,char* id_num);
int byName(char* bookName,char* name);
book* find(char* item,FILE* books);
void search();
void deleteRecord(char* detail,FILE* books,int issuebook,int edit);
void deleteBook();
void issue();
void editbooks();
void login();
void profile(char* usn);
void changePasswordStudent(char* usn);
void updateFile(char* usn, char* newpassword);
void adminLogin();
void studentLogin();
void new_user();
