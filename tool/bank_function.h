#ifndef BANK_FUNCTION_H_INCLUDED
#define BANK_FUNCTION_H_INCLUDED

#define MAX_STR_SIZE     15

// extern struct BankAccStructure;
struct BankAccStructure{
    char atmCard[MAX_STR_SIZE];       // 8 character alphanumeric identifier, simulate an ATM card
    char firstName[MAX_STR_SIZE];
    char lastName[MAX_STR_SIZE];
    long lAccountNumberChecking;    //  account number, no dashes
    long lTotalBalanceChecking;
    long lAccountNumberSavings;    //  account number, no dashes
    long lTotalBalanceSavings;
    int iPinNumber;         // 4 digit pin number
};


void bankConnect(char *bankRecFile);

void bankClose();

int bankGetTotalRecordNum();

void bankGetAtmCardNumber(char *retAtmCardNum);

void bankGetFirstName(char *retFirstname);


void bankGetLastName(char *retLastname);

long bankGetAccountNumberChecking();

long bankGetTotalBalanceChecking();

void bankSetTotalBalanceChecking(long i);

long bankGetAccountNumberSavings();

long bankGetTotalBalanceSavings();

void bankSetTotalBalanceSavings(long i);

// remove later
int bankGetPinNumber();

void bankResetRecordPointer();

void bankGotoRecordPointer(int i);

void bankReadOneRecord();

void bankWriteOneRecord();

void bankUpdateCurrentRecord();




#endif // BANK_FUNCTION_H_INCLUDED
