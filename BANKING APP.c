#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct Customer
{
    char Name[65];
    char Address[65];
    unsigned long long phoneNumber;
    char Gender[8];
    char username[65];
    char password[65];
    int accountNumber;
    char accountType[8];
    int Balance;
};

struct Transaction
{
    char username[65];
    int amount;
    char type[12];
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void admin();
void withdraw();
void customer();
void exitApplication();
void adminLogin();
void viewCustomersList();
void viewCustomersTransactions();
void removeCustomer();
void newCustomer();
void customerLogin();
void customerInfo();
void updateCustomer();
void viewAccount();
void transactions();
void deposit();
void withdraw();
void mainMenu();
void viewTransactions();
int main()
{
    mainMenu();
    return 0;
}
//This is the main menu which firstly display on the screen.
void mainMenu()
{
    system("cls");
    int selection;
    printf("\t\t\tMALAYSIAN URBAN BANK MANAGEMENT SYSTEM!!!!\n");
    printf("1. Admin\n");
    printf("2. Customer\n");
    printf("3. Exit\n");
    printf("\nYou are requested to select one option!!! Choose from (1-3)\n");
    scanf("%d", &selection);

    switch (selection)
    {
    case 1:
        admin(false);
        break;
    case 2:
        customer(NULL);
        break;
    case 3:
        exitApplication();
        break;
    default:
        system("cls");
        printf("Invalid Input. Please try again.\n\n");
        mainMenu();
        break;
    }
}
//This is admin menu where admin can perform the mentioned operations.
void admin(isLogged)
{
    int selection;
    system("cls");
    printf("\t\t\tADMIN MENU\n");
    printf("1. Login\n");
    printf("2. View Customers' list\n");
    printf("3. View Customers' Transactions\n");
    printf("4. Remove Existing Customer\n");
    printf("5. Go Back\n");
    printf("6. Exit\n");
    scanf("%d", &selection);
    switch (selection)
    {
    case 1:
        adminLogin();
        break;
    case 2:
        viewCustomersList(isLogged);
        break;
    case 3:
        viewCustomersTransactions(isLogged);
        break;
    case 4:
        removeCustomer(isLogged);
        break;
    case 5:
        mainMenu();
        break;
    case 6:
        exitApplication();
        break;
    default:
        system("cls");
        printf("Invalid Input. Please try again.\n\n");
        admin(isLogged);
        break;
    }
}
//This is customer menu where customer can signup and perform the following operations.
void customer(struct Customer *User)
{
    int selection;
    system("cls");

    printf("\t\t\tCUSTOMER MENU\n");
    printf("1. Register account\n");
    printf("2. Login\n");
    printf("3. View Personal Information\n");
    printf("4. Update Personal Information\n");
    printf("5. View Account Detail\n");
    printf("6. Manage Transactions\n");
    printf("7. View Transactions\n");
    printf("8. Go Back\n");
    printf("9. Exit\n");
    scanf("%d", &selection);

    switch (selection)
    {
    case 1:
        newCustomer();
        break;
    case 2:
        customerLogin();
        break;
    case 3:
        customerInfo(User);
        break;
    case 4:
        updateCustomer(User);
        break;
    case 5:
        viewAccount(User);
        break;
    case 6:
        transactions(User);
        break;
    case 7:
        viewTransactions(User);
        break;
    case 8:
    	mainMenu();
        break;
    case 9:
        exitApplication();
        break;
    }
}
//To exit from the application
void exitApplication()
{
    system("cls");
    printf("\nTHANKS FOR USING OUR APPLICATION.HAVE A NICE DAY!!!");
    exit(0);
}
//It compares the entered password and check whether it is true or false.
void adminLogin()
{
    system("cls");
    char password[16] = "MUMBS";
    char userInput[16];
    printf("Enter password: ");
    scanf("%s", userInput);

    if (strcmp(password, userInput) == 0)
    {
        printf("Authorized to use admin functionalities.\n");
        system("pause");
        admin(true);
    }
    else
    {
        printf("Incorrect admin password.\n");
        system("pause");
        admin(false);
    }
}
//To view the list of customer
void viewCustomersList(isLogged)
{
    system("cls");
    if(!isLogged) {
        printf("Not authorized. Please login.\n");
        adminLogin();
    } else {
        struct Customer getData;
        FILE *fp;
        fp = fopen("records.txt", "r");

        printf("\n%16s | %16s | %16s | %16s | %16s\n\n", "Name", "Address", "Phone Number", "Gender", "Username");

        while (fscanf(fp, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", getData.Name, getData.Address, &getData.phoneNumber, getData.Gender, getData.username, getData.password, &getData.accountNumber, getData.accountType, &getData.Balance) != EOF)
        {
            printf("%16s | %16s | %16llu | %16s | %16s\n", getData.Name, getData.Address, getData.phoneNumber, getData.Gender, getData.username);
        }
        fclose(fp);
        system("pause");
        admin(isLogged);
    }
}

void viewCustomersTransactions(isLogged)
{
    system("cls");
    if(!isLogged) {
        printf("Not authorized. Please login.\n");
        adminLogin();
    } else {
        struct Transaction transact;
        FILE* readFile;
        readFile = fopen("transactions.txt", "r");

        printf("\n%16s | %16s | %16s | %16s\n\n", "Username", "Amount", "Type", "Date/Time");

        while(fscanf(readFile, "%s\t%d\t%s\t%d/%d/%d %d:%d:%d\n", transact.username, &transact.amount, transact.type, &transact.year, &transact.month, &transact.day, &transact.hour, &transact.minute, &transact.second) != EOF) {
            printf("%16s | %16d | %16s | %d/%d/%d %d:%d:%d\n", transact.username, transact.amount, transact.type, transact.year, transact.month, transact.day, transact.hour, transact.minute, transact.second);
        }
        fclose(readFile);
        system("pause");
        admin(isLogged);
    }
}
//To remove the existing customer.
void removeCustomer(isLogged)
{
    system("cls");
    if(!isLogged) {
        printf("Not authorized. Please login.\n");
        adminLogin();
    } else {
        char username[16];
        struct Customer getData;
        FILE* readFile, *writeFile;
        readFile = fopen("records.txt", "r");
        writeFile = fopen("new.txt", "w");

        printf("Enter username of customer to remove: ");
        scanf("%s", username);

        while (fscanf(readFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", getData.Name, getData.Address, &getData.phoneNumber, getData.Gender, getData.username, getData.password, &getData.accountNumber, getData.accountType, &getData.Balance) != EOF)
        {
            if (strcasecmp(username, getData.username) != 0) {
                fprintf(writeFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", getData.Name, getData.Address, getData.phoneNumber, getData.Gender, getData.username, getData.password, getData.accountNumber, getData.accountType, getData.Balance);
            }
        }
        fclose(readFile);
        fclose(writeFile);
        remove("records.txt");
        rename("new.txt", "records.txt");
        printf("Specified customer removed.");
        system("pause");
        admin();
    }
}
//Menu for the registration of account for new customer.
void newCustomer()
{
    system("cls");
    struct Customer add;
    char retypePassword[32];
    int retypeNumber;

    FILE *fp;
    fp = fopen("records.txt", "a");

    printf("\t\t\tCustomer Registration\n");
    printf("Enter your name: ");
    scanf("%s", &add.Name);
    system("cls");
    printf("Enter your address: ");
    scanf("%s", &add.Address);
    system("cls");
    printf("Enter your phone number: ");
    scanf("%llu", &add.phoneNumber);
    system("cls");

    retryGender:
    printf("Enter Gender (Male/Female): ");
    scanf("%s", &add.Gender);
    system("cls");

    if (strcasecmp(add.Gender, "male") == 0 || strcasecmp(add.Gender, "m") == 0)
    {
        strcpy(add.Gender, "Male");
    }
    else if (strcasecmp(add.Gender, "female") == 0 || strcasecmp(add.Gender, "f") == 0)
    {
        strcpy(add.Gender, "Female");
    }
    else
    {
        printf("Invalid input.\n");
        goto retryGender;
    }

    printf("Enter username: ");
    scanf("%s", &add.username);
    system("cls");

    retryPassword:
    printf("Enter password: ");
    scanf("%s", &add.password);
    system("cls");
    printf("Retype password: ");
    scanf("%s", retypePassword);
    system("cls");

    if (strcmp(add.password, retypePassword) != 0)
    {
        printf("Error: Passwords didn't match.\n");
        goto retryPassword;
    }

    retryNumber:
    printf("Enter account number: ");
    scanf("%d", &add.accountNumber);
    system("cls");
    printf("Retype account number: ");
    scanf("%d", &retypeNumber);
    system("cls");

    if (add.accountNumber != retypeNumber)
    {
        printf("Account numbers didn't match.\n");
        goto retryNumber;
    }

    retryType:
    printf("Enter account type (Saving / Current): ");
    scanf("%s", &add.accountType);
    system("cls");

    if (strcasecmp(add.accountType, "saving") == 0 || strcasecmp(add.accountType, "s") == 0)////strcasecmp is used to compare two strings(ie.male and female)
    {
        strcpy(add.accountType, "SAVING");
    }
    else if (strcasecmp(add.accountType, "current") == 0 || strcasecmp(add.accountType, "c") == 0)
    {
        strcpy(add.accountType, "CURRENT");
    }
    else
    {
        printf("Invalid input.\n");
        goto retryType;
    }

    fprintf(fp, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", add.Name, add.Address, add.phoneNumber, add.Gender, add.username, add.password, add.accountNumber, add.accountType, 0);
    fclose(fp);
}
//Menu for login by customer. 
void customerLogin()
{
    struct Customer data;
    char username[16];
    char password[32];
    bool logged = false;//bool is a variable which can be either true or false
    system("cls");

    Login:
    printf("\t\t\tCUSTOMER LOGIN\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp;
    fp = fopen("records.txt", "r");
    if (fp == NULL)
    {
        printf("NO RECORDS FOUND.\n");
    }
    else
    {
        while (fscanf(fp, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, &data.phoneNumber, data.Gender, data.username, data.password, &data.accountNumber, data.accountType, &data.Balance) != EOF)
        {
            //printf("%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, data.phoneNumber, data.Gender, data.username, data.password, data.accountNumber, data.accountType, data.Balance);
            if (strcasecmp(username, data.username) == 0 && strcmp(password, data.password) == 0)
            {
                printf("CUSTOMER LOGGED IN.\n");
                logged = true;
                break;
            }
        }

        if (logged)
        {
            fclose(fp);
            system("pause");
            customer(&data);
        }
        else
        {
            fclose(fp);
            system("cls");
            printf("Invalid username or password.\n");
            goto Login;
        }
    }
}
//It helps to check the personal information by customer.
void customerInfo(struct Customer *User)
{
    system("cls");
    if (User == NULL)
    {
        printf("Customer not logged in.\n");
        system("pause");
        customer(NULL);
    }
    else
    {
        printf("Username: %s\n", User->username);//arrow is an operator used to access a member of structure
        printf("Name: %s\n", User->Name);
        printf("Address: %s\n", User->Address);
        printf("Phone Number: %llu\n", User->phoneNumber);
        printf("Gender: %s\n", User->Gender);
        system("pause");
        customer(User);
    }
}
// Menu to update the personal information.
void updateCustomer(struct Customer *User)
{
    int selection;
    char retypePassword[32];
    struct Customer getData;
    system("cls");
    FILE *readFile;
    FILE *writeFile;
    readFile = fopen("records.txt", "r");
    writeFile = fopen("new.txt", "w");

    if (readFile == NULL || writeFile == NULL)
    {
        printf("Error opening I/O files.\n");
        system("pause");
        exitApplication();
    }

    if (User == NULL)
    {
        printf("Customer not logged in.\n");
        system("pause");
        customer(NULL);
    }
    else
    {
        printf("1. Change name\n");
        printf("2. Change address\n");
        printf("3. Change phone number\n");
        printf("4. Change gender\n");
        printf("5. Change password\n");
        printf("6. Change account type\n");
        printf("7. Go Back\n");
        scanf("%d", &selection);

        while (fscanf(readFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", getData.Name, getData.Address, &getData.phoneNumber, getData.Gender, getData.username, getData.password, &getData.accountNumber, getData.accountType, &getData.Balance) != EOF)
        {
            if (strcmp(User->username, getData.username) == 0)
            {
                switch (selection)
                {
                case 1:
                    system("cls");
                    printf("Enter new name: ");
                    scanf("%s", User->Name);
                    printf("Customer's name changed.\n");
                    break;
                case 2:
                    system("cls");
                    printf("Enter new address: ");
                    scanf("%s", User->Address);
                    printf("Customer's address changed.\n");
                    break;
                case 3:
                    system("cls");
                    printf("Enter new phone number: ");
                    scanf("%llu", User->phoneNumber);
                    printf("Customer's phone number changed.\n");
                    break;
                case 4:
                    retryGender:
                    system("cls");
                    printf("Enter new gender: ");
                    scanf("%s", User->Gender);

                    if (strcasecmp(User->Gender, "male") == 0 || strcasecmp(User->Gender, "m") == 0)
                    {
                        strcpy(User->Gender, "MALE");
                    }
                    else if (strcasecmp(User->Gender, "female") == 0 || strcasecmp(User->Gender, "f") == 0)
                    {
                        strcpy(User->Gender, "FEMALE");
                    }
                    else
                    {
                        printf("Invalid input.\n");
                        system("pause");
                        goto retryGender;
                    }
                    printf("Customer's gender changed.\n");
                    break;
                case 5:
                    retryPassword:
                    system("cls");
                    printf("Enter password: ");
                    scanf("%s", User->password);
                    printf("Retype password: ");
                    scanf("%s", retypePassword);

                    if (strcmp(User->password, retypePassword) != 0)
                    {
                        printf("Error: Passwords didn't match.\n");
                        system("pause");
                        goto retryPassword;
                    }
                    printf("Password changed.\n");
                    break;
                case 6:
                    retryType:
                    system("cls");
                    printf("Enter account type (Saving / Current): ");
                    scanf("%s", User->accountType);

                    if (strcasecmp(User->accountType, "saving") == 0 || strcasecmp(User->accountType, "s") == 0)
                    {
                        strcpy(User->accountType, "SAVING");
                    }
                    else if (strcasecmp(User->accountType, "current") == 0 || strcasecmp(User->accountType, "c") == 0)
                    {
                        strcpy(User->accountType, "CURRENT");
                    }
                    else
                    {
                        printf("Invalid input.\n");
                        system("pause");
                        goto retryType;
                    }
                    printf("Account type changed to %s.\n", User->accountType);
                    break;
                case 7:
                    fclose(readFile);
                    fclose(writeFile);
                    remove("new.txt");
                    customer(User);
                    break;
                }
                fprintf(writeFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", User->Name, User->Address, User->phoneNumber, User->Gender, User->username, User->password, User->accountNumber, User->accountType, User->Balance);
            }
            else
            {
                fprintf(writeFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", getData.Name, getData.Address, getData.phoneNumber, getData.Gender, getData.username, getData.password, getData.accountNumber, getData.accountType, getData.Balance);
            }
        }
        fclose(readFile);
        fclose(writeFile);
        remove("records.txt");
        rename("new.txt", "records.txt");
        system("pause");
        updateCustomer(User);
    }
}
//Menu to view account details.
void viewAccount(struct Customer *User)
{
    system("cls");
    if (User == NULL)
    {
        printf("Customer not logged in.\n");
        system("pause");
        customer(NULL);
    }
    else
    {
        printf("Account Number: %d\n", User->accountNumber);
        printf("Account Type: %s\n", User->accountType);
        printf("Balance: %d\n", User->Balance);
        system("pause");
        customer(User);
    }
}
//Menu to choose deposit or withdraw amount.
void transactions(struct Customer *User)
{
    if (User == NULL)
    {
        printf("Customer not logged in.\n");
        system("pause");
        customer(NULL);
    } else {
        int selection;
        system("cls");
        printf("\t\t\tManage Transactions\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Go Back\n");
        scanf("%d", &selection);

        switch(selection) {
            case 1:
                deposit(User);
                break;
            case 2:
                withdraw(User);
                break;
            case 3:
                customer(User);
                break;
            default:
                printf("Invalid Input.\n");
                system("pause");
                transactions(User);
                break;
        }
    }
}
//Menu to deposit amount in the bank.
void deposit(struct Customer *User)
{
    system("cls");

    struct Customer data;
    int amount;

    FILE* readFile;
    FILE* writeFile;
    FILE* fp;

    readFile = fopen("records.txt", "r");
    writeFile = fopen("new.txt", "w");
    fp = fopen("transactions.txt", "a+");

    printf("Enter amount to deposit: ");
    scanf("%d", &amount);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    while (fscanf(readFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, &data.phoneNumber, data.Gender, data.username, data.password, &data.accountNumber, data.accountType, &data.Balance) != EOF)
    {
        if (strcmp(data.username, User->username) == 0) {
            User->Balance = data.Balance + amount;
            fprintf(writeFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, data.phoneNumber, data.Gender, data.username, data.password, data.accountNumber, data.accountType, User->Balance);
            fprintf(fp, "%s\t%d\t%s\t%d/%d/%d %d:%d:%d\n", data.username, amount, "Deposit", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        } else {
            fprintf(writeFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, data.phoneNumber, data.Gender, data.username, data.password, data.accountNumber, data.accountType, data.Balance);
        }
    }
    fclose(readFile);
    fclose(writeFile);
    fclose(fp);
    remove("records.txt");
    rename("new.txt", "records.txt");
    system("pause");
    customer(User);
}
//Menu to withdraw the amount from the bank.
void withdraw(struct Customer *User)
{
    system("cls");

    struct Customer data;
    int amount;

    FILE* readFile;
    FILE* writeFile;
    FILE* fp;

    readFile = fopen("records.txt", "r");
    writeFile = fopen("new.txt", "w");
    fp = fopen("transactions.txt", "a+");

    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    while (fscanf(readFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, &data.phoneNumber, data.Gender, data.username, data.password, &data.accountNumber, data.accountType, &data.Balance) != EOF)
    {
        if (strcmp(data.username, User->username) == 0) {
            User->Balance = data.Balance - amount;
            fprintf(writeFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, data.phoneNumber, data.Gender, data.username, data.password, data.accountNumber, data.accountType, User->Balance);
            fprintf(fp, "%s\t%d\t%s\t%d/%d/%d %d:%d:%d\n", data.username, amount, "Withdrawal", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        } else {
            fprintf(writeFile, "%s\t%s\t%llu\t%s\t%s\t%s\t%d\t%s\t%d\n", data.Name, data.Address, data.phoneNumber, data.Gender, data.username, data.password, data.accountNumber, data.accountType, data.Balance);
        }
    }
    fclose(readFile);
    fclose(writeFile);
    fclose(fp);
    remove("records.txt");
    rename("new.txt", "records.txt");
    system("pause");
    customer(User);
}
// to view details of deposit and withdraw with date and time. 
void viewTransactions(struct Customer* User)
{
    if(User == NULL) {
        printf("Customer isn't logged in.\n");
        system("pause");
        customer(NULL);
    } else {
        struct Transaction transact;
        FILE* readFile;
        readFile = fopen("transactions.txt", "r");

        printf("\n%16s | %16s | %16s | %16s\n\n", "Username", "Amount", "Type", "Date/Time");

        while(fscanf(readFile, "%s\t%d\t%s\t%d/%d/%d %d:%d:%d\n", transact.username, &transact.amount, transact.type, &transact.year, &transact.month, &transact.day, &transact.hour, &transact.minute, &transact.second) != EOF) {
            if(strcmp(User->username, transact.username) == 0) {
                printf("%16s | %16d | %16s | %d/%d/%d %d:%d:%d\n", transact.username, transact.amount, transact.type, transact.year, transact.month, transact.day, transact.hour, transact.minute, transact.second);
            }
        }
        fclose(readFile);
        system("pause");
        customer(User);
    }
}
