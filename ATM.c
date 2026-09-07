#include<stdio.h>
// int pin=0;
// int deposite=0;
// int balance=0;
// void create_pin(){
    
//     printf("enter the new pin:");
//     scanf("%d",&pin);
//     printf("pin has been created successfully\n");
// }
// void change_pin(){
//     int p,enpin;
//     printf("enter the old pin:");
//     scanf("%d",&p);
//     if(p==pin){
//         printf("enter the new pin:");
//         scanf("%d",&enpin);
//         pin=enpin;
//         printf("pin is been updated successfully\n");
//     }
//     else{
//         printf("entered old pin doesn't match with old pin\n");
//     }

// }
// void check_balance(){
//     int enter_pin;
//     printf("enter the pin:");
//     scanf("%d",&enter_pin);
//     if(enter_pin==pin){
//       printf("your balance: %d\n",balance);
//     }
//     else{
//         printf("your entered pin doesn't match \n");
//     }
// }
// void deposite_amount(){
//     int enter_pin;
//     printf("enter the pin:");
//     scanf("%d",&enter_pin);
//     if(enter_pin==pin){
//         printf("enter the amount to deposite:");
//         scanf("%d",&deposite);
//         if(deposite<=0){
//             printf("the amount must be greater the 0\n");
//             printf("enter the valid amount\n");
//         }
//         else{
//          printf("your %d is been deposited successfully\n",deposite);
//          balance=balance+deposite;
//         }
//     }
//     else{
//         printf("invalid pin!");
//     }
// }
// void withdraw_balance(){
//     int enter_pin,withdraw;
//     printf("enter the pin:");
//     scanf("%d",&enter_pin);
//     if(enter_pin==pin){
//        printf("enter the amount to withdraw: ");
//        scanf("%d",&withdraw);
//        if(withdraw<=balance){
//          balance=balance-withdraw;
//          printf("the amount u withdrawed is %d\n",withdraw);

//        }
//        else{
//          printf("invalid balance!\n");
//        }
      
//     }
//     else{
//         printf("invalid pin!\n");
//     }
// }
// void main(){
//     int choice;
//     while (1)
//     {
//         printf("enter 1 to create pin\n");
//         printf("enter 2 to change pin\n");
//         printf("enter 3 to check balance\n");
//         printf("enter 4 to deposite amount\n");
//         printf("enter 5 to withdraw balance\n");
//         printf("enter 6 to exit\n");
//         printf("enter your choice:");
//         scanf("%d",&choice);
//         if(choice==1){
//              create_pin();
//         }
//         else if(choice==2){
//              change_pin();
//         }
//         else if(choice==3){
//             check_balance();
//         }
//         else if(choice==4){
//             deposite_amount();
//         }
//         else if(choice==5){
//             withdraw_balance();
//         }
//         else if(choice==6){
//             printf("----Thank you for banking with us-----");
//             break;
//         }
//         else{
//             printf("invalid choice!");
//         }
//     }
    
// }



#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACCOUNTS 100
#define FILE_NAME "bank_accounts.txt"

struct Account {
    char accountNumber[12];
    int pin;
    float balance;
};

struct Account accounts[MAX_ACCOUNTS];
int accountCount = 0;


/* Clear input buffer */
void clearBuffer() {
    while (getchar() != '\n');
}


/* Check 11-digit account number */
int validAccountNumber(char accNum[]) {

    if (strlen(accNum) != 11) {
        return 0;
    }

    for (int i = 0; i < 11; i++) {

        if (!isdigit((unsigned char)accNum[i])) {
            return 0;
        }
    }

    return 1;
}


/* Check 4-digit PIN */
int validPIN(int pin) {

    return (pin >= 1000 && pin <= 9999);
}


/* Find account */
int findAccount(char accNum[]) {

    for (int i = 0; i < accountCount; i++) {

        if (strcmp(accounts[i].accountNumber, accNum) == 0) {
            return i;
        }
    }

    return -1;
}


/* Load accounts from TXT file */
void loadAccounts() {

    FILE *file;

    file = fopen(FILE_NAME, "r");

    if (file == NULL) {

        accountCount = 0;
        return;
    }

    accountCount = 0;

    /*
       Skip the header lines
    */
    char line[200];

    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);


    /*
       Read accounts
    */
    while (accountCount < MAX_ACCOUNTS) {

        if (fscanf(file, "%11s %d %f",
                   accounts[accountCount].accountNumber,
                   &accounts[accountCount].pin,
                   &accounts[accountCount].balance) != 3) {

            break;
        }

        accountCount++;
    }

    fclose(file);
}


/* Save accounts to TXT file */
void saveAccounts() {

    FILE *file;

    file = fopen(FILE_NAME, "w");

    if (file == NULL) {

        printf("Error: Could not save account data.\n");
        return;
    }


    fprintf(file, "ACCOUNT NUMBER\tPIN\tBALANCE\n");
    fprintf(file, "--------------------------------------\n");


    for (int i = 0; i < accountCount; i++) {

        fprintf(file, "%s\t\t%d\t%.2f\n",
                accounts[i].accountNumber,
                accounts[i].pin,
                accounts[i].balance);
    }

    fclose(file);
}


/* Create account */
void createAccount() {

    if (accountCount >= MAX_ACCOUNTS) {

        printf("\nBank system is full!\n");
        return;
    }

    struct Account newAcc;


    printf("\n================================\n");
    printf("        CREATE ACCOUNT\n");
    printf("================================\n");


    /* Account number */

    while (1) {

        printf("Enter 11-digit account number: ");
        scanf("%11s", newAcc.accountNumber);


        if (!validAccountNumber(newAcc.accountNumber)) {

            printf("\nAccount number must contain exactly 11 digits.\n");

        }
        else if (findAccount(newAcc.accountNumber) != -1) {

            printf("\nAccount number already exists!\n");

        }
        else {

            break;
        }
    }


    /* PIN */

    while (1) {

        printf("Create 4-digit PIN: ");
        scanf("%d", &newAcc.pin);


        if (validPIN(newAcc.pin)) {
            break;
        }

        printf("PIN must contain exactly 4 digits.\n");
    }


    /* Balance */

    while (1) {

        printf("Enter initial balance: ");
        scanf("%f", &newAcc.balance);


        if (newAcc.balance >= 0) {
            break;
        }

        printf("Balance cannot be negative.\n");
    }


    /* Add account */

    accounts[accountCount] = newAcc;

    accountCount++;


    /* Save all accounts */

    saveAccounts();


    printf("\n================================\n");
    printf("Account created successfully!\n");
    printf("Account Number : %s\n", newAcc.accountNumber);
    printf("Initial Balance: %.2f\n", newAcc.balance);
    printf("================================\n");
}


/* Verify PIN */
int verifyPIN(int index) {

    int enteredPin;

    printf("Enter your PIN: ");
    scanf("%d", &enteredPin);


    if (enteredPin == accounts[index].pin) {

        return 1;
    }


    printf("Incorrect PIN!\n");

    return 0;
}


/* Deposit */
void deposit(int index) {

    float amount;

    printf("\nEnter amount to deposit: ");
    scanf("%f", &amount);


    if (amount <= 0) {

        printf("Invalid amount.\n");
        return;
    }


    accounts[index].balance += amount;

    saveAccounts();


    printf("\nAmount deposited successfully!\n");
    printf("New Balance: %.2f\n",
           accounts[index].balance);
}


/* Withdraw */
void withdraw(int index) {

    float amount;

    printf("\nEnter amount to withdraw: ");
    scanf("%f", &amount);


    if (amount <= 0) {

        printf("Invalid amount.\n");
    }

    else if (amount > accounts[index].balance) {

        printf("Insufficient balance!\n");
        printf("Available Balance: %.2f\n",
               accounts[index].balance);
    }

    else {

        accounts[index].balance -= amount;

        saveAccounts();


        printf("\nAmount withdrawn successfully!\n");
        printf("Remaining Balance: %.2f\n",
               accounts[index].balance);
    }
}


/* Balance enquiry */
void balanceEnquiry(int index) {

    printf("\n================================\n");
    printf("        BALANCE ENQUIRY\n");
    printf("================================\n");

    printf("Account Number : %s\n",
           accounts[index].accountNumber);

    printf("Current Balance: %.2f\n",
           accounts[index].balance);

    printf("================================\n");
}


/* Update PIN */
void updatePIN(int index) {

    int oldPin;
    int newPin;


    printf("\nEnter old PIN: ");
    scanf("%d", &oldPin);


    if (oldPin != accounts[index].pin) {

        printf("Incorrect old PIN!\n");
        return;
    }


    while (1) {

        printf("Enter new 4-digit PIN: ");
        scanf("%d", &newPin);


        if (validPIN(newPin)) {
            break;
        }

        printf("PIN must contain exactly 4 digits.\n");
    }


    accounts[index].pin = newPin;

    saveAccounts();


    printf("PIN updated successfully!\n");
}


/* Login */
int login() {

    char accNum[12];

    printf("\n================================\n");
    printf("             LOGIN\n");
    printf("================================\n");


    printf("Enter 11-digit account number: ");
    scanf("%11s", accNum);


    if (!validAccountNumber(accNum)) {

        printf("Invalid account number!\n");
        return -1;
    }


    int index = findAccount(accNum);


    if (index == -1) {

        printf("Account not found!\n");
        return -1;
    }


    if (verifyPIN(index)) {

        printf("\nLogin successful!\n");

        return index;
    }


    return -1;
}


/* ATM menu */
void atmMenu(int index) {

    int choice;


    do {

        printf("\n================================\n");
        printf("            ATM MENU\n");
        printf("================================\n");

        printf("Account Number: %s\n\n",
               accounts[index].accountNumber);


        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Balance Enquiry\n");
        printf("4. Update PIN\n");
        printf("5. Logout\n");


        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice) {

            case 1:
                deposit(index);
                break;


            case 2:
                withdraw(index);
                break;


            case 3:
                balanceEnquiry(index);
                break;


            case 4:
                updatePIN(index);
                break;


            case 5:
                printf("\nLogged out successfully.\n");
                break;


            default:
                printf("Invalid choice!\n");
        }


    } while (choice != 5);
}


/* Main */
int main() {

    int choice;
    int index;


    /*
       IMPORTANT:
       Load existing accounts FIRST.
    */
    loadAccounts();


    /*
       If accounts already exist,
       directly show normal menu.
    */

    if (accountCount == 0) {

        printf("\n========================================\n");
        printf("       WELCOME TO ATM BANKING SYSTEM\n");
        printf("========================================\n");

        printf("\nNo account exists.\n");
        printf("Please create your first account.\n");


        createAccount();


        /*
           Automatically login after creation
        */

        printf("\nPlease login to continue.\n");


        index = login();


        if (index != -1) {

            atmMenu(index);
        }
    }


    /*
       Normal menu
    */

    do {

        printf("\n========================================\n");
        printf("          ATM BANKING SYSTEM\n");
        printf("========================================\n");


        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");


        printf("Enter your choice: ");


        if (scanf("%d", &choice) != 1) {

            clearBuffer();

            printf("Invalid input! Please enter a number.\n");

            continue;
        }


        switch (choice) {


            case 1:

                createAccount();

                break;


            case 2:

                index = login();


                if (index != -1) {

                    atmMenu(index);
                }

                break;


            case 3:

                printf("\nThank you for using ATM Banking System!\n");

                break;


            default:

                printf("Invalid choice!\n");
        }


    } while (choice != 3);


    return 0;
}