#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bank_function.h"

FILE* fptrBankRecord;
int iTotalRecordNum = 0;

struct BankAccStructure bankRecord;

int iCurrentRecordNumber = 0;      // internal variable to keep track of Nth record
long lAtmMachineBalance = 1000000;

void bankConnect(char *bankRecFile){
    fptrBankRecord = fopen(bankRecFile, "r+b");
    fread(&iTotalRecordNum, sizeof(int), 1, fptrBankRecord);
}

void bankClose(){
    if(fptrBankRecord != NULL){
        fclose(fptrBankRecord);
    }
    iCurrentRecordNumber = 0;  // reset
}

int bankGetTotalRecordNum(){
    return iTotalRecordNum;
}

void bankGetAtmCardNumber(char *retAtmCardNum){
    strcpy(retAtmCardNum, bankRecord.atmCard);
}

void bankGetFirstName(char *retFirstname){
    strcpy(retFirstname, bankRecord.firstName);
}

void bankGetLastName(char *retLastname){
    strcpy(retLastname, bankRecord.lastName);
}

long bankGetAccountNumberChecking(){
    return bankRecord.lAccountNumberChecking;
}

long bankGetTotalBalanceChecking(){
    return bankRecord.lTotalBalanceChecking;
}

void bankSetTotalBalanceChecking(long i){
    bankRecord.lTotalBalanceChecking = i;
}

long bankGetAccountNumberSavings(){
    return bankRecord.lAccountNumberSavings;
}

long bankGetTotalBalanceSavings(){
    return bankRecord.lTotalBalanceSavings;
}

void bankSetTotalBalanceSavings(long i){
    bankRecord.lTotalBalanceSavings = i;
}

// remove later
int bankGetPinNumber(){
    return bankRecord.iPinNumber;
}

void bankResetRecordPointer(){
    fseek(fptrBankRecord, 0, SEEK_SET);
    iCurrentRecordNumber = 0;  // reset
    fread(&iTotalRecordNum, sizeof(int), 1, fptrBankRecord);    // move pointer from initial "number of entries" record
}

void bankGotoRecordPointer(int i){
    fseek(fptrBankRecord, sizeof(bankRecord)*i, SEEK_CUR);
    iCurrentRecordNumber = i;  // reset
}


void bankReadOneRecord(){
    fread(&bankRecord, sizeof(bankRecord), 1, fptrBankRecord);
    iCurrentRecordNumber++;
}

void bankWriteOneRecord(){
    fwrite(&bankRecord, sizeof(bankRecord), 1, fptrBankRecord);
    // iCurrentRecordNumber++;
}

void bankUpdateCurrentRecord(){

    fseek(fptrBankRecord, -sizeof(bankRecord), SEEK_CUR);
    fwrite(&bankRecord, sizeof(bankRecord), 1, fptrBankRecord);
    // iCurrentRecordNumber++;
    fflush(fptrBankRecord);
}



