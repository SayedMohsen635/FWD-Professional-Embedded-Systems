#include "server.h"
#include <string.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include <stdio.h>

/* This is the account database */
ST_accountsDB_t database[255] = {{100000 , RUNNING , "37828205246310005"} 
                               , {200000 , BLOCKED , "56105910810182508"}
                               , {300000 , RUNNING , "20987261987198489"} 
                               , {400000 , BLOCKED , "98094984526018746"} 
                               , {500000 , RUNNING , "32109849849874997"} 
                               , {600000 , BLOCKED , "65106784931479832"} 
                               , {700000 , RUNNING , "47892312356411845"} 
                               , {800000 , BLOCKED , "24241858498494892"} 
                               , {900000 , RUNNING , "32198489795423339"} 
                               , {999999 , BLOCKED , "10245641122467983"}};

/* This is the transaction database */
ST_transaction_t transaction[255] = {0};

/* Global Variable for transactionSequenceNumber */
uint32_t sequenceNumber = 0;

uint32_t myIndex;

/* This function will search for the element we need */
//if(search(&(transData -> cardHolderData) , database) == -1){
uint32_t search(ST_cardData_t *cardData , ST_accountsDB_t *accountRefrence){
    for(uint32_t i = 0; i < 255; i++){
        if(strcmp(cardData -> primaryAccountNumber , accountRefrence[i].primaryAccountNumber) == 0){
            myIndex = i;
            printf("myIndex = %d\n" , myIndex);
            return myIndex;
        }
    }
    return -1;
}

/* This function will take card data and validate if the account related to this card exists or not
    --------------------
        Function Test
    --------------------    
    ST_cardData_t card1;
    printf("Enter Primary Account Number: ");
    gets(card1.primaryAccountNumber);
    isValidAccount(&card1 , database);
*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence){
    myIndex = search(cardData , accountRefrence);
    if(myIndex == -1){
        printf("ACCOUNT_NOT_FOUND\n");
        return ACCOUNT_NOT_FOUND;
    }else{
        printf("SERVER_OK\n");
        return SERVER_OK;
    }
}

/* This function checks if the account is blocked or not
    --------------------
        Function Test
    --------------------    
    isBlockedAccount(&database[0]);
*/
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence){
    if(accountRefrence -> state == BLOCKED){
        printf("BLOCKED_ACCOUNT\n");
        return BLOCKED_ACCOUNT;
    }else{
        printf("SERVER_OK\n");
        return SERVER_OK;
    }
}

/* This function will take terminal data and
   checks if the transaction amount is greater than balance or not
   ----------------------
        Function Test
   ----------------------  
    ST_terminalData_t terminal;
    terminal.transAmount = 1500;
    isAmountAvailable(&terminal , &database[0]);
*/
/* EN_serverError_t amountAvailable = isAmountAvailable(&transData -> terminalData , &database[vadlidmyIndex]); */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData , ST_accountsDB_t *accountRefrence){
    if((termData -> transAmount) > (accountRefrence -> balance)){
        printf("LOW_BALANCE\n");
        return LOW_BALANCE;
    }else{
        printf("SERVER_OK\n");
        return SERVER_OK;
    }
}

/* This function will store all transaction data in the transactions database */
EN_serverError_t saveTransaction(ST_transaction_t *transData){
    transData -> transactionSequenceNumber = sequenceNumber;
    if(transData -> transactionSequenceNumber > 255){
        printf("SAVING_FAILED\n");
        return SAVING_FAILED;
    }
    transaction[sequenceNumber] = *transData;
    sequenceNumber++;
    printf("SERVER_OK\n");
    return SERVER_OK;
}

/* This function takes the sequence number of a transaction and returns the transaction data if found in the transactions DB */
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData){
    for(int i = 0; i < 255; i++){
        if(transaction[i].transactionSequenceNumber == transData -> transactionSequenceNumber){
            printf("SERVER_OK\n");
            return SERVER_OK;
        }
    }
    printf("TRANSACTION_NOT_FOUND\n");
    return TRANSACTION_NOT_FOUND;
}

/* This function will take all transaction data and validate its data
    ----------------------
        Function Test
    ----------------------  
    ST_transaction_t testAcc;
    strcpy(testAcc.cardHolderData.primaryAccountNumber, "56105910810182508");
    testAcc.terminalData.transAmount = 50000;
    recieveTransactionData(&testAcc);
*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
    if(isValidAccount(&(transData -> cardHolderData) , database) == ACCOUNT_NOT_FOUND){
        printf("FRAUD_CARD");
        return FRAUD_CARD;
    }else{
        EN_serverError_t amountAvailable = isAmountAvailable(&(transData -> terminalData) , &database[myIndex]);
        if(amountAvailable == LOW_BALANCE){
            printf("DECLINED_INSUFFECIENT_FUND\n");
            return DECLINED_INSUFFECIENT_FUND;
        }else{
            EN_serverError_t accountStatus = isBlockedAccount(database);
            if(accountStatus == BLOCKED_ACCOUNT){
                printf("DECLINED_STOLEN_CARD\n");
                return DECLINED_STOLEN_CARD;
            }else{
                if(saveTransaction(transData) == SAVING_FAILED){
                    printf("INTERNAL_SERVER_ERROR\n");
                    return INTERNAL_SERVER_ERROR;
                }else{
                    printf("Balance before update = %f\n" , database[myIndex].balance);
                    database[myIndex].balance -= transData -> terminalData.transAmount;
                    printf("APPROVED\n");
                    printf("Balance after update = %f\n" , database[myIndex].balance);
                    return APPROVED;
                }
            }
        }
    }
}