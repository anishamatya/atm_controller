#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "bank_function.h"

int main()
{
    int iNumOfRecordsWrite;
    char charTemp[20];
    long lTemp;
    int i;
    struct BankAccStructure bankNewEntry;
    FILE *fptrBankRecFile;
    fptrBankRecFile = fopen("bank_rec_bin.dat", "w+b");
    printf("Enter number of records to write >> ");
    scanf("%d", &iNumOfRecordsWrite);
    fwrite(&iNumOfRecordsWrite, sizeof(int), 1, fptrBankRecFile);

    for(i = 0; i<iNumOfRecordsWrite; i++){
        printf("ATM card number >> ");
        scanf("%s", bankNewEntry.atmCard);

        printf("First >> ");
        scanf("%s", bankNewEntry.firstName);

        printf("Last >> ");
        scanf("%s", bankNewEntry.lastName);

        printf("Acc No (checking) >> ");
        scanf("%ld", &bankNewEntry.lAccountNumberChecking);
        printf("Total Balance (checking) >> ");
        scanf("%ld", &bankNewEntry.lTotalBalanceChecking);

        printf("Acc No (savings) >> ");
        scanf("%ld", &bankNewEntry.lAccountNumberSavings);
        printf("Total Balance (savings) >> ");
        scanf("%ld", &bankNewEntry.lTotalBalanceSavings);

        printf("Pin No >> ");
        scanf("%d", &bankNewEntry.iPinNumber);
        fwrite(&bankNewEntry, sizeof(bankNewEntry), 1, fptrBankRecFile);
    }

    printf("Written %d records\n", i);
    fclose(fptrBankRecFile);

    printf("Press any key to read from the file >> \n\n");
    getch();
    bankConnect("bank_rec_bin.dat");
    iNumOfRecordsWrite = bankGetTotalRecordNum();   // use same variable as above for temporary test

    for(i = 0; i<iNumOfRecordsWrite; i++){
        bankReadOneRecord();
        bankGetAtmCardNumber(charTemp);
        printf("ATM card number >> %s\n", charTemp);

        bankGetFirstName(charTemp);
        printf("First >> %s\n", charTemp);

        bankGetLastName(charTemp);
        printf("Last >> %s\n", charTemp);

        lTemp = bankGetAccountNumberChecking();
        printf("Acc no (checking) >> %ld\n", lTemp);
        lTemp = bankGetTotalBalanceChecking();
        printf("Balance (checking) >> %ld\n", lTemp);

        lTemp = bankGetAccountNumberSavings();
        printf("Acc no (savings) >> %ld\n", lTemp);
        lTemp = bankGetTotalBalanceSavings();
        printf("Balance (savings) >> %ld\n", lTemp);

        lTemp = bankGetPinNumber();
        printf("Pin No >> %d\n", (int)lTemp);
        printf("----- \n\n");
    }

#if 0
    printf("\nEnter the record number to edit (First  = 0) >> ");
    scanf("%d", &i);
    bankResetRecordPointer();
    bankGotoRecordPointer(i);
    bankReadOneRecord();
    bankSetTotalBalanceChecking(2222);
    bankSetTotalBalanceSavings(22220000);

    bankGetAtmCardNumber(charTemp);
    printf("Current ATM >> %s\n", charTemp);
    bankGetFirstName(charTemp);
    printf("Current First >> %s\n", charTemp);
    bankGetLastName(charTemp);
    printf("Current Last >> %s\n", charTemp);
    lTemp = bankGetAccountNumberChecking();
    printf("Current Acc no (checking) >> %ld\n", lTemp);
    lTemp = bankGetTotalBalanceChecking();
    printf("Current Balance (checking) >> %ld\n", lTemp);
    lTemp = bankGetAccountNumberSavings();
    printf("Current Acc no (savings) >> %ld\n", lTemp);
    lTemp = bankGetTotalBalanceSavings();
    printf("Current Balance (savings) >> %ld\n", lTemp);
    lTemp = bankGetPinNumber();
    printf("Current Pin No >> %d\n", (int)lTemp);

    printf("Going to update record ...\n");
    getch();

    bankUpdateCurrentRecord();

    printf("Press any key to read from the file >> \n\n");
    getch();
    // bankConnect("bank_rec_bin.dat");
    bankResetRecordPointer();
    iNumOfRecordsWrite = bankGetTotalRecordNum();   // use same variable as above for temporary test

    for(i = 0; i<iNumOfRecordsWrite; i++){
        bankReadOneRecord();
        bankGetAtmCardNumber(charTemp);
        printf("ATM card number >> %s\n", charTemp);

        bankGetFirstName(charTemp);
        printf("First >> %s\n", charTemp);

        bankGetLastName(charTemp);
        printf("Last >> %s\n", charTemp);

        lTemp = bankGetAccountNumberChecking();
        printf("Acc no (checking) >> %ld\n", lTemp);
        lTemp = bankGetTotalBalanceChecking();
        printf("Balance (checking) >> %ld\n", lTemp);

        lTemp = bankGetAccountNumberSavings();
        printf("Acc no (savings) >> %ld\n", lTemp);
        lTemp = bankGetTotalBalanceSavings();
        printf("Balance (savings) >> %ld\n", lTemp);

        lTemp = bankGetPinNumber();
        printf("Pin No >> %d\n", (int)lTemp);
        printf("----- \n");
    }
#endif



    bankClose();
    return 0;
}
