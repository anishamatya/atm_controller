#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank_function.h"

struct TestCaseStruct{
    char testAtmCard[MAX_STR_SIZE];
    int testPinNumber;
    int testAccType;
    int testAccOp;
    int testDepWdrawAmt;
    char testComment[50];
};

int fn_atm_function(int iModeVal, struct TestCaseStruct testCase){

    int i, iAtmRecordFound = 0, iAccType, iAccOp, iPinNumUsrInput;
    long lDepositAmount, lWithdrawAmount;
    long lTemp;
    char charTemp[20];
    char charTemp2[20];
    int iErrorAtm;
    // 0: no error
    // 1: ATM mismatch
    // 2: PIN mismatch
    // 100: miscellaneous

    iErrorAtm = 0;
    printf("(Enter an 8 character alphanumeric string to simulate am ATM card)\n");
    printf("Insert ATM card >> ");
    if(iModeVal == 0)
        scanf("%s", charTemp);
    else if(iModeVal == 1){
        strcpy(charTemp, testCase.testAtmCard);
        printf("%s\n", charTemp);
    }

    for(i = 0; i<bankGetTotalRecordNum(); i++){
        bankReadOneRecord();
        if(bankVerifyAtmCard(charTemp) == 1){
            iAtmRecordFound = 1;
            break;
        }
    }

    if(iAtmRecordFound == 1){
        // get pin number from user
        fflush(stdin);
        printf("Enter 4 digit pin number >> ");
        if(iModeVal == 0){
            scanf("%s", charTemp);
            iPinNumUsrInput = atoi(charTemp);
        }
        else if(iModeVal == 1){
            iPinNumUsrInput = testCase.testPinNumber;
            printf("%04d\n", iPinNumUsrInput);
        }
        charTemp[4] = '\0';
        if( bankVerifyPinNumber(iPinNumUsrInput) == 1){
            // proceed to next banking operations
            bankGetFirstName(charTemp);
            bankGetLastName(charTemp2);
            printf("Welcome %s %s \n", charTemp, charTemp2);
            printf("Select your account type [0: checking, 1: savings] >> ");
            if(iModeVal == 0){
                scanf("%d", &iAccType);
            }
            else if(iModeVal == 1){
                iAccType = testCase.testAccType;
                printf("%d\n", iAccType);
            }

            if(iAccType == 0){
                // checking account selected
                printf("Enter desired operation:\n0: Balance\n1:Deposit\n2:Withdraw\n3:Exit\n>> ");
                if(iModeVal == 0){
                    scanf("%d", &iAccOp);
                }
                else if(iModeVal == 1){
                    iAccOp = testCase.testAccOp;
                    printf("%d\n", iAccOp);
                }
                switch(iAccOp){
                case 0:
                    // balance
                    printf("Checking account number: %ld\n", bankGetAccountNumberChecking() );
                    printf("Your balance >> %ld\n", bankGetTotalBalanceChecking() );
                    break;

                case 1:
                    printf("Enter the amount to deposit >> ");
                    if(iModeVal == 0){
                        scanf("%ld", &lDepositAmount);
                    }
                    else if(iModeVal == 1){
                        lDepositAmount = testCase.testDepWdrawAmt;
                        printf("%ld\n", lDepositAmount);
                    }
                    lTemp = bankGetTotalBalanceChecking() + lDepositAmount;
                    bankSetTotalBalanceChecking(lTemp);
                    bankUpdateCurrentRecord();
                    break;

                case 2:
                    printf("Enter the amount to withdraw >> ");
                    if(iModeVal == 0){
                        scanf("%ld", &lWithdrawAmount);
                    }
                    else if(iModeVal == 1){
                        lWithdrawAmount = testCase.testDepWdrawAmt;
                        printf("%ld\n", lWithdrawAmount);
                    }
                    lTemp = bankGetTotalBalanceChecking() - lWithdrawAmount;
                    if(lTemp < 0){
                        printf("Insufficient funds. Please remove your card and try again\n");
                    }
                    else{
                        bankSetTotalBalanceChecking(lTemp);
                        bankUpdateCurrentRecord();
                    }
                    break;

                default:
                    break;
                }
            }
            else if(iAccType == 1){
                // savings account selected
                // only allow balance and deposit
                printf("Enter desired operation:\n0: Balance\n1:Deposit\n2:Exit\n>> ");
                if(iModeVal == 0){
                    scanf("%d", &iAccOp);
                }
                else if(iModeVal == 1){
                    iAccOp = testCase.testAccOp;
                    printf("%d\n", iAccOp);
                }
                switch(iAccOp){
                case 0:
                    // balance
                    printf("Savings account number: %ld\n", bankGetAccountNumberSavings() );
                    printf("Your balance >> %ld\n", bankGetTotalBalanceSavings() );
                    break;

                case 1:
                    printf("Enter the amount to deposit >> ");
                    if(iModeVal == 0){
                        scanf("%ld", &lDepositAmount);
                    }
                    else if(iModeVal == 1){
                        lDepositAmount = testCase.testDepWdrawAmt;
                        printf("%ld\n", lDepositAmount);
                    }
                    lTemp = bankGetTotalBalanceSavings() + lDepositAmount;
                    bankSetTotalBalanceSavings(lTemp);
                    bankUpdateCurrentRecord();
                    break;

                default:
                    break;
                }
            }
            else{
                iErrorAtm = 100;       // misc: invalid account type selected
            }
        }
        else{   // if( bankVerifyPinNumber(atoi(charTemp) == 1){
            iErrorAtm = 2;
        }
    }
    else {  // if(iAtmRecordFound == 1){

        iErrorAtm = 1;
    }

    bankResetRecordPointer();

    return iErrorAtm;
}

int main()
{
    int iMode, iBreak = 0, i;
    int iNumOfRecords;
    long lTemp;
    int iError = 0;
    // 0: no error
    // 1: ATM mismatch
    // 2: PIN mismatch
    // 100: miscellaneous
    FILE* fptrTestInputFile;
    char charTemp[50];

    struct TestCaseStruct testCaseData;
    int iNumberofTestCases;

    bankConnect("bank_rec_bin.dat");

    printf("Enter Mode [0: use ATM, 1: run test cases] >> ");
    scanf("%d", &iMode);
    if(iMode == 0){
        // run ATM
        do{
            iError = fn_atm_function(iMode, testCaseData);

            if(iError == 1){
                printf("Error (%d): ATM card mismatch or account does not exist. Please try again \n", iError);
            }
            else if(iError == 2){
                printf("Error (%d): Invalid PIN. Please reinsert your card and try again \n", iError);
            }
            else if(iError == 100){
                printf("Error (%d): Invalid option entry, please try again \n", iError);
            }
            else if(iError == 0){
                printf("Thank you for using our service\n -------- \n\n");
            }

        }while(iBreak != 1);

    }
    else if(iMode == 1){
        // run test cases
        printf("Enter choice [0: view entire bank record, 1: run test cases, 2: exit] >> ");
        scanf("%d", &iMode);
        switch(iMode){
        case 0:
            iNumOfRecords = bankGetTotalRecordNum();
            printf("Total records: %d\n", iNumOfRecords);
            for(i = 0; i<iNumOfRecords; i++){
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

                printf("----- \n");
            }
            break;

        case 1:
            fptrTestInputFile = fopen("atm_test_input.txt", "r");
            fscanf(fptrTestInputFile, "%s", charTemp);
            iNumberofTestCases = atoi(charTemp);
            printf("Number of Test cases >> %d\n", iNumberofTestCases);

            for(int i = 0; i<iNumberofTestCases; i++){
                printf("i = %d\n", i);
                fscanf(fptrTestInputFile, "%s", charTemp);
                strcpy(testCaseData.testAtmCard, charTemp);
                fscanf(fptrTestInputFile, "%s", charTemp);
                testCaseData.testPinNumber = atoi(charTemp);
                fscanf(fptrTestInputFile, "%s", charTemp);
                testCaseData.testAccType = atoi(charTemp);
                fscanf(fptrTestInputFile, "%s", charTemp);
                testCaseData.testAccOp = atoi(charTemp);
                fscanf(fptrTestInputFile, "%s", charTemp);
                testCaseData.testDepWdrawAmt = atoi(charTemp);
                fscanf(fptrTestInputFile, "%s", charTemp);
                strcpy(testCaseData.testComment, charTemp);

                iError = fn_atm_function(iMode, testCaseData);

                printf("--- test #%d completed ----\n", i);
                printf("Expected Output : %s\n", testCaseData.testComment);

                if(iError == 1){
                    printf("Error (%d): ATM card mismatch or account does not exist. Please try again \n -------- \n\n", iError);
                }
                else if(iError == 2){
                    printf("Error (%d): Invalid PIN. Please reinsert your card and try again \n -------- \n\n", iError);
                }
                else if(iError == 100){
                    printf("Error (%d): Invalid option entry, please try again \n", iError);
                }
                else if(iError == 0){
                    printf("Thank you for using our service\n -------- \n\n");
                }
            }
            break;
        }
    }
    else{
        printf("Invalid entry; please restart");
    }

    bankClose();
    return 0;
}
