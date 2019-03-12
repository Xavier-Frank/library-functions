#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for Wiindows use #include <Windows.h>
#include <string.h>
#define RETURNTIME 15
struct Book
{
	int book_id;
	char Title[15];
	char Author[15];
	int quantity;
	int rack_no;	
};
struct login
{
    char firstname[12];
    char lastname[12];
    char username[25];
    char password[10];
};
void login(void)
{
	system("clear");//reserve for ubuntu ...for windows use system("clear")
	char username[25];
    char password[10];
    FILE *log;
	char correct = 'n';
    log=fopen("login.dat","r+");//opening file for reading
    printf("\nEnter your user name and password to login\n");
    printf("\t\nUsername:");
    scanf("%s",username);
    printf("\t\nPassword:");
    scanf("%s",password);
    while(!feof(log) && correct == 'n')
    {

		struct login a;
		int result = fread(&a, sizeof(struct login), 1, log);
        if(result != 0 && strcmp(username,a.username) == 0 && strcmp(password,a.password) == 0)//compares if username and password matches those in login file
        {

            printf("Successful login!");
            printf("\nWelcome! %s",username);
			correct = 'y';
            //call home function
        }
    }
    if(correct == 'n')
        {
            printf("Please Enter correct UserName and password");
            login();
        }
    fclose(log);
}
void registration(void)
{
	FILE *log; 
	log=fopen("login.dat","a+"); //open a login file for appending
	struct login a;

	if (log == NULL) {
		puts("ERROR! OPENING FILE!");
	}
	else
	{
		
		puts("\n\tEnter your firstname:"); //append data into the login file
		scanf("%s",a.firstname);
		puts("\n\tEnter your lastname:");
		scanf("%s",a.lastname);
		puts("\n\tEnter your username:");
		scanf("%s",a.username);
		puts("\n\tEnter your password not exceeding 10 characters:");
		scanf("%s",a.password);
		fseek(log,0,SEEK_END); // moving the file to the end allow appending of the next file
		fwrite(&a,sizeof(struct login),1,log);
		printf("Your username is:%s\n",a.username);
	
	
	sleep(2);
	}
	fclose(log);
 login();    //call login function to allow registerd user to login
}

void viewbooks(void)
{
    system("clear");
    FILE *fb;	
    fb = fopen("booksinfo.dat", "rb+");
	if (fb == NULL)
	{
		puts("Error opening the file");
	}
	else
	{
        puts("\t\t\t*********************** BOOK LIST **************************************");
        puts("\n\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************\n");

        printf("\t\t\t%6s %6s %6s %14s %23s\n", "BOOK ID","QUANTITY", "RACK No.","TITLE", "AUTHOR");
        struct Book sample;
        while(!feof(fb))
        {   
	        int results=fread(&sample,sizeof(sample),1,fb);
            if (results!=0 && sample.book_id != 0)
            {
                printf("\t\t\t%6d %6d %6d \t%16s \t%16s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);
            }
            
        }
        puts("\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************");
   
        
    }
   
    fclose(fb);
}
void addbooks(void)
{
    system("clear");
    puts("\t********************** Add Books ********************");
    int n,Book_id;
    FILE *fp;
    fp=fopen("booksinfo.dat","a+"); //open sample login file for appending and updating

	if (fp == NULL)
        {
            puts("ERROR! OPENING FILE!");
        }
    else 
    {
		
        struct Book sample;
        Book_id=sample.book_id;
		printf("\n\tEnter Book ID:"); //append data into the login file
		scanf("%d",&Book_id);
        while(!feof(fp))
        {
            int results=fread(&sample,sizeof(struct Book),1,fp);
            if (Book_id==sample.book_id)
                {
                    puts("Book with similar Id exists");
                    sleep(1);
                    addbooks();
                }
        
        else
        { 
            
            printf("\n\tEnter Book Title:");
            scanf("%s",sample.Title);
            printf("\n\tEnter Book Author:");
            scanf("%s",sample.Author);
            printf("\n\tEnter Book rack no:");
            scanf("%d",&sample.rack_no);
            printf("\n\tEnter Quantity:");
            scanf("%d",&sample.quantity);
            // fseek(fp,0,SEEK_END); // moving the file to the end allow appending of the next file
            sleep(2);
            fwrite(&sample, sizeof(struct Book),1 , fp);
            fclose(fp);
            puts("\n\tBook succesfully added");
            puts("\n\tAdd another book?\t press 1.(Yes) or 2.(No)");
            scanf("%d",&n);
            
            

            if (n == 1)
                {
                    addbooks(); 
                }
            if (n == 2) 
                {
                    system("clear");
                    viewbooks();
                }
            else
            {
            // call a function to exit this function                        
                
            }
        }
            }
    }
}
void searchbook()
{
    FILE *fp;
    int Book_id,a;
    char Book_title[16];
    system("clear");
    
   
    fp = fopen("booksinfo.dat", "r");
    if(fp==NULL)
    puts("Error opening file!");
    else
    {   
        puts("\t\t*************************** Search Book ******************************");
        puts("\tsearch by:---> 1.Book Id \t\t---> 2.Book Title \t\t---> 2.Exit");
        printf("Enter your choice:");
        scanf("%d",&a);
        struct Book sample;
        if (a == 1)
        {
                    printf("\t\tEnter book id:");
                    scanf("%d",&Book_id);
                    while(!feof(fp))
                    {
                        int results=fread(&sample,sizeof(sample),1,fp);
                        if(results!=0 && Book_id==sample.book_id && sample.book_id!=0)
                        {
                            printf("\n\t\tThe Book Exists\n");
                            sleep(1);
                            printf("\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                            printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);
                                                  
                        }
                                        
                    }
                    fclose(fp);
        }
        if (a == 2)
         {

                    printf("\t\tEnter book title:");
                    scanf("%s",Book_title);
                    while(!feof(fp))
                    {
                        int results=fread(&sample,sizeof(sample),1,fp);
                        if(results!=0 && strcmp(Book_title,sample.Title)==0)
                        {
                            printf("\n\t\tThe Book Exists\n");
                            sleep(1);
                            printf("\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                            printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);
                            // findbook='t';                        
                        }
                        
                    }
                    fclose(fp);
         }
        if (a==2)
        {
            // call a function to exit this function                      
        }	
            
    }

}
void deletebooks(void)
{
    system("clear");
    FILE *fp;
    FILE *fd;
    int Book_Id;
    char findbook='n'; int option;
	system("clear");
    fp =fopen("booksinfo.dat", "r+");
	rewind(fp);	// for taking file pointer to the begining of the file
	if (fp == NULL)
        {
        puts("Error opening the file!");
        }
    else
    {  
        printf("\t\t Enter the Book ID to Delete :  ");
	    scanf("%d", &Book_Id);
	    
        struct Book sample;
        int count=0;        
		while(!feof(fp) && findbook=='n')
        { 
            int results=fread(&sample,sizeof(struct Book),1,fp);
            count += results;
			//finding if the user input matches book id in the system 
			if(results !=0 && sample.book_id==Book_Id && findbook=='n')
            {
				printf("\t\t The Books Record is available\n");
                sleep(1);
				printf("\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);				
				findbook = 'y';
			}
			
		}
		if(findbook =='n')
        {
			//if no book of such id is found
            printf("\t\t No book of such Id exist");
            deletebooks();
            sleep(2);
		}
        if (findbook =='y')
            {
                puts("\t\t\tAre you true to delete?-->Press 1.[Yes] -->2.[No]");
                sleep(1);
                scanf("%d",&option);
                switch (option)
                {
                    case 1:
                        fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                        struct Book blank = {0,"","",0,0};
                        fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                        fwrite(&blank,sizeof(struct Book),1,fp);
                        break;
                    case 2:
                    // call a function to exit this function                        
                
                    default:
                        puts("Invalid option try again");
                        deletebooks();
                        break;
                }


            }
            fclose(fp);
    }
}    
void editbooks(void)
{
    system("clear");
    FILE *fp=NULL;
    int n,Book_id,choice;
    char option='n';
    fp=fopen("booksinfo.dat","r+");
    rewind(fp);
    if (fp==NULL)
        {
            puts("Error opening File!!");
        }
    else
    {
        int count=0;
        struct Book sample;
        printf("\n\t\tEnter the Book id to edit:");
        scanf("%d",&Book_id);
       while(!feof(fp) && option=='n')
        {
            int results=fread(&sample,sizeof(struct Book),1,fp);
            count+=results;
            if (results!=0 && Book_id==sample.book_id && option=='n')
            {
                printf("\t\t The Books Record is available\n");
                sleep(1);
				printf("\n\n\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                printf("\n\n\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);				
				option = 'y';
            }
            
        }
       
        if (option=='n')
            {
                //if no book of such id is found
            printf("\t\t No book of such Id exist");
            editbooks();
            sleep(1);  
            }
        if (option=='y')
        {
            puts("\t\t\tAre you true to edit-->Press 1.[Yes] -->2.[No]");
            sleep(1);
            scanf("%d",&choice);
            switch (choice)
            {
                case 1:
                    fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                    printf("\n\tEnter New Book ID:"); //append data into the booksinfo file
                    scanf("%d",&sample.book_id);
                    printf("\n\tEnter New Book Title:");
                    scanf("%s",sample.Title);
                    printf("\n\tEnter New Book Author:");
                    scanf("%s",sample.Author);
                    printf("\n\tEnter New  Book rack no:");
                    scanf("%d",&sample.rack_no);
                    printf("\n\tEnter New Quantity:");
                    scanf("%d",&sample.quantity);
                    sleep(2);
                    fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                    fwrite(&sample, sizeof(struct Book),1 , fp);
                    fclose(fp);
                    puts("\n\tBook succesfully edited");
                    puts("\n\tEdit another book?\t press 1.(Yes) or 2.(No)");
                    scanf("%d",&n);
                    if (n == 1)
                        {
                            editbooks(); 
                        }
                        else 
                        {
                        puts("Invalid option try again");
                        //call a function e.g to return to home screen 
                        }
                    break;
                case 2:
                puts("Please wait...");
                sleep(2);
                //call a function e.g to return to home screen 
                break;         
            }
                        
                        
                                
        }
    }            
}

void issuebook(void)
{
    FILE *fp,*fissue,*fuser;
    system("clear");
    struct ISSUED
    {
        char username[20];
        int bookid;
        char booktitle[20];
    };
    struct ISSUED issued;
    int n,Book_id;
    int y;
    char option1='n',option2='n',username[12];
    fp = fopen("booksinfo.dat", "rb+");
    fissue = fopen("issue.dat", "a+");
    fuser=fopen("login.dat","r+");
    if (fp==NULL && fissue==NULL && fissue==NULL)
        {
            puts("Error opening the file");
        }
    else
    {
        struct Book sample;
        struct login a;
        puts("\n\t************************** ISSUE BOOK SECTION *******************************");
        puts("\n\n\t*****************************************************************************");
        puts("\t*****************************************************************************");
        printf("\n\n\t\t--> 1.Issue a Book \t\t--> 2.View Issued Books\n");
        printf("\n\t\t--> 3.Search Issued Books \t--> 4.Remove Issued book\n");
        printf("\n\t\t--> 5.Exit\n");
        puts("\n\n\t*****************************************************************************");
        puts("\t*****************************************************************************");
        printf("\n\t\t Enter your choice :  ");
        scanf("%d",&n);
        switch (n)
        {
            case 1: //issue a book
            system("clear");
            printf("\n\t\tEnter the Book id to be issued:");
            scanf("%d",&Book_id);
            printf("\n\t\tEnter the username of the user:");
            scanf("%s",username);
            char book_title[20];
            while(!feof(fp) && option1=='n' )
                {
                    int results=fread(&sample,sizeof(struct Book),1,fp);
                    if (results!=0 && Book_id==sample.book_id)
                    {
                        strcpy(book_title, sample.Title);
                        printf("\t\t The Books Record is available");
                        sleep(1);
                        printf("\tBeing Issued to:%s",username);
                        printf("\n\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                        printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);				
                        option1 = 'y';
                    }
                    
                    
                }
            while(!feof(fuser) && option2=='n')
            {
                int results=fread(&a,sizeof(struct login),1,fuser);
                if (results!=0 && strcmp(username,a.username)==0)
                {
                    puts("username available");
                    option2='y';
                }
                
                else 
                {
                    //if user not in the system
                    printf("No such user exists");
                }
            }
            
            

            
                if (option1=='n')
                    {
                        //if no book of such id is found
                        printf("\t\t No book of such Id exist or Not a user ");
                        sleep(1);  
                        issuebook();
                    }
                if (option1 == 'y'&& option2=='y')
                    {
                        struct ISSUED issued;
                        sleep(1);
                        strcpy(issued.username,username);
                        issued.bookid=Book_id;
                        strcpy(issued.booktitle,book_title);
                        printf("Book issued succesfully");
                        fwrite(&issued,sizeof(struct ISSUED),1,fissue);
                        fclose(fp);
                        fclose(fissue);
                        fclose(fuser);
                        printf("\n\t\t Issue More Book? --> Press 1[yes]\t\t--> Press 2[no]:");
				        scanf("%d",&y);
                        if (y==1)
                        {
                            sleep(1);
                            issuebook();
                        }
                        else
                        {
                            issuebook();
                        }
                    }
                break;
            case 2://view issued books
                system("clear");
                fissue=fopen("issue.dat","rb");
                if (fissue==NULL) 
                    {
                       puts("Error opening the file");
                    }
                else
                {
                    puts("\t\t\t***********************ISSUEDBOOK LIST **************************************");
                    puts("\n\n\t\t\t**********************************************************************");
                    puts("\t\t\t**********************************************************************\n");
                    printf("\t\t\t%6s %6s %14s\n", "Username", "Book Id","Book title");
                    struct ISSUED issued;
                    while(!feof(fissue))
                    {   
                        int results=fread(&issued,sizeof(struct ISSUED),1,fissue);
                        if (results!=0 && issued.bookid != 0)
                        {
                            printf("\t\t\t%6s %6d %14s\n",issued.username,issued.bookid,issued.booktitle);
                        }
                    }
                    
                    puts("\n\t\t\t**********************************************************************");
                    puts("\t\t\t**********************************************************************");
                }
                fclose(fissue);
                sleep(5);
                issuebook();
                break;
            case 3://search issued book
                system("clear");
                int option;
                fissue=fopen("issue.dat","rb+");
                if (fissue==NULL)
                    {
                        puts("Erro opening the file");
                    }
                else
                    {
                      printf("Enter the book id: ");
                      scanf("%d",&Book_id); 
                      while(!feof(fissue))
                    {
                        int results=fread(&issued,sizeof(issued),1,fissue);
                        if(results!=0 && Book_id==issued.bookid && issued.bookid!=0)
                        {
                            printf("\n\t\tThe Book Exists\n");
                            sleep(1);
                            printf("\t\t\t%6s %6s %14s\n", "Username", "Book Id","Book title");
                            printf("\t\t\t%6s %6d %14s\n",issued.username,issued.bookid,issued.booktitle);
                           
                        }
                                                  
                    }
                    fclose(fissue);
                    sleep(2);
                    issuebook();
                    }
                    break;
                case 4:// remove issued book
                    system("clear");
                    int Book_id;
                    char findbook='y';
                    fissue =fopen("issue.dat", "rb+");
	                rewind(fissue);	// for taking file pointer to the begining of the file
                        printf("\t\t Enter the Book ID to Delete :  ");
                        scanf("%d",& Book_id);
	    
                        struct Book sample;
                        int count=0;        
		                while(!feof(fissue) && findbook=='n')
                        { 
                            int results=fread(&sample,sizeof(struct Book),1,fissue);
                            count += results;
                            //finding if the user input matches book id in the system 
			                if(results !=0 && sample.book_id==Book_id && findbook=='n')
                            {
                            printf("\t\t The Books Record is available\n");
                            sleep(1);
                            printf("\t\t\t%6s %6s %14s\n", "Username", "Book Id","Book title");
                            printf("\t\t\t%6s %6d %14s\n",issued.username,issued.bookid,issued.booktitle);			
                            findbook = 'y';
                            }
		                }
                        if(findbook =='n')
                        {
                            //if no book of such id is found
                            printf("\t\t No book of such Id exist");
                            issuebook();
                            sleep(2);
                        }
                        if (findbook =='y')
                        {
                            puts("\t\t\tAre you true to remove?-->Press 1.[Yes] -->2.[No]");
                            sleep(1);
                            scanf("%d",&option);
                            switch (option)
                            {
                                case 1:
                                    fseek(fissue,(count-1)*sizeof(struct Book),SEEK_SET);
                                    struct Book blank = {0,"","",0,0};
                                    fseek(fissue,(count-1)*sizeof(struct Book),SEEK_SET);
                                    fwrite(&blank,sizeof(struct Book),1,fissue);
                                    sleep(1);
                                    issuebook();
                                    break;
                                case 2:
                                    issuebook();// call a function to exit this function                        
                                    break;
                                default:
                                    puts("Invalid option try again");
                                    issuebook();
                                    break;
                            }
                        }
                case 5:
                    system("clear");
                    sleep(1);
                    ;//call Home function
                    break;         
                default:
                puts("Invalid option");
                issuebook();
                break;
        }


    
        
    }
    fclose(fp);
    fclose(fuser);
    fclose(fissue);
}
void viewusers(void)
{
    FILE *Vw;
    Vw=fopen("login.dat","rb+");
    if (Vw==NULL)
        {
            puts("Error opening the file!");
        }
    else
    {
        puts("\t\t\t*********************** USERS' LIST **********************************");
        puts("\n\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************\n");
        printf("\t\t\t%14s %12s %12s\n","USERNAME","FIRSTNAME","LASTNAME");
        struct login a;
        while(!feof(Vw))
        {
        int results=fread(&a,sizeof(struct login),1,Vw);
        if (results !=0)
            {
        
                printf("\t\t\t%12s %12s %12s\n",a.username,a.firstname,a.lastname);
            }
        }
        puts("\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************");
    }
    fclose(Vw);
    int n;
    printf("\t\t\t --> Press 1. to continue:");
    scanf("%d",&n);
    switch (n)
    {
        case 1:
            system("clear");
            //call librarian home
            break;
    
        default:
            system("clear");
            puts("\n\t\t\tInvalid option\n");
            viewusers();
            break;
    }
    
   
}
void delete_users()
{
    system("clear");
    char stop='n',username[20];
    FILE *log;
    log=fopen("login.dat","rb+");
    if (log== NULL )
        {
            puts("Error opening the file!");
        }
    else
    {
        struct login a;
        int count=0;
        printf("\n\tEnter your username to edit:");
        scanf("%s",username);
        while(!feof(log) && stop == 'n')
            {
                int results=fread(&a,sizeof(struct login),1,log);
                count+=results;
                if (results!=0 && strcmp(username,a.username)==0)
                    {
                       printf("\n\tUser Available");
                       sleep(1);
                        printf("\n\t\t\t%14s %12s %12s\n","USERNAME","FIRSTNAME","LASTNAME");
                        printf("\t\t\t%12s %12s %12s\n",a.username,a.firstname,a.lastname);
                        stop='y';
                    }
                
            }
            if (stop=='n')
             {
                puts("User doesnt exist!");
                sleep(2);
                delete_users();    /* code */
            }
            if (stop=='y')
            {
               puts("Are you sure you want to delete?\t-->Press 1.[Yes] \t-->Press 2.[No]");
               printf("Enter your Choice:");
               int Choice;
               scanf("%d",&Choice);
               switch (Choice)
                {
                    case 1:
                        fseek(log,(count-1)*sizeof(struct login),SEEK_SET);
                        struct login blank = {"","","",""};
                        fseek(log,(count-1)*sizeof(struct login),SEEK_SET);
                        fwrite(&blank,sizeof(struct login),1,log);
                        puts("User Deleted...");
						sleep(2);
                        fclose(log);
						// Librarian_home();
                        delete_users();
                        break;
                    case 2:
						puts("Please wait...");
						sleep(1);
                        // Librarian_home();
                        delete_users();
                        break;                
                    default:
                        puts("Invalid stop try again");
                        delete_users();
                        break;
                }
            }
            
            

        
    }
    
    

}
int main(void)
{
    // login();
    // registration();
    // searchbook();
    // viewbooks();
    // editbooks();
    // addbooks();
    // deletebooks();
    // issuebook();
    //viewusers();
    // delete_users();
return 0;
}

	                
                    
                     
			

                    

