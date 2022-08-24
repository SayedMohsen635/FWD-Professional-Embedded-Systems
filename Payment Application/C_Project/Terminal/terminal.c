#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "terminal.h"

/* This function asks the user for the date and
   store it in the transactionDate element of the structure
    ---------------------
        Function Test
    ---------------------
    ST_terminalData_t card1;
    EN_terminalError_t result = getTransactionDate(&card1);
    printf("Result is : %d\n" , result);
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    printf("Enter Transaction Date In Format (DD/MM/YYYY): ");
    gets(termData -> transactionDate);
    if(strlen(termData -> transactionDate) != 10){
        printf("WRONG_DATE\n");
        return WRONG_DATE;
    }
    if(termData -> transactionDate == NULL){
        printf("WRONG_DATE\n");
        return WRONG_DATE;
    }
    for(int i = 0; i < 2; i++){
        if(!isdigit(termData -> transactionDate[i])){
            printf("WRONG_DATE\n");
            return WRONG_DATE;
        }
    }
    if(termData -> transactionDate[2] != '/'){
        printf("WRONG_DATE\n");
        return WRONG_DATE;
    }
    for(int i = 3; i < 5; i++){
        if(!isdigit(termData -> transactionDate[i])){
            printf("WRONG_DATE\n");
            return WRONG_DATE;
        }
    }
    if(termData -> transactionDate[5] != '/'){
        printf("WRONG_DATE\n");
        return WRONG_DATE;
    }
    for(int i = 6; i < 10; i++){
        if(!isdigit(termData -> transactionDate[i])){
            printf("WRONG_DATE\n");
            return WRONG_DATE;
        }
    }
    printf("TERMINAL_OK\n");
    return TERMINAL_OK;
}

/* This function checks if the card is expired or not
    ---------------------
        Function Test
    ---------------------
    ST_cardData_t card1;
    ST_terminalData_t terminal1;
    EN_terminalError_t result = isCardExpired(&card1 , &terminal1);
    printf("Result is : %d\n" , result);
    ---------------------
        Test Cases
    ---------------------
    transYear < expYear     : 01/12/2020 , 12/23   --> TERMINAL_OK  (0)
    transYear > expYear     : 01/12/2022 , 12/20   --> EXPIRED_CARD (2)
    transMonth < expMonth   : 01/06/2023 , 10/23   --> TERMINAL_OK  (0)
    transMonth > expMonth   : 01/11/2023 , 09/23   --> EXPIRED_CARD (2)
*/
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
    int expirMonth , expirYear , transMonth , transYear;
    expirMonth = (cardData -> cardExpirationDate[0] - '0') * 10 + (cardData -> cardExpirationDate[1] - '0') * 1;
    printf("expirMonth = %d\t" , expirMonth);
    expirYear = (cardData -> cardExpirationDate[3] - '0') * 10 + (cardData -> cardExpirationDate[4] - '0') * 1;
    printf("expirYear = %d\t" , expirYear);
    transMonth = (termData -> transactionDate[3] - '0') * 10 + (termData -> transactionDate[4] - '0') * 1;
    printf("transMonth = %d\t" , transMonth);
    transYear = (termData -> transactionDate[8] - '0') * 10 + (termData -> transactionDate[9] - '0') * 1;
    printf("transYear = %d\t" , transYear);
    if(transYear < expirYear){
        printf("TERMINAL_OK\n");
        return TERMINAL_OK;
    }else if(transYear > expirYear){
        printf("EXPIRED_CARD\n");
        return EXPIRED_CARD;
    }else if(transYear == expirYear){
        if(transMonth < expirMonth){
            printf("TERMINAL_OK\n");
            return TERMINAL_OK;
        }else{
            printf("EXPIRED_CARD\n");
            return EXPIRED_CARD;
        }
    }
}

/* This function asks for the transaction amount and saves it into terminal data
    ---------------------
        Function Test
    ---------------------
    ST_terminalData_t card1;
    EN_terminalError_t result = getTransactionAmount(&card1);
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    printf("Enter Transaction Amount: ");
    scanf("%f" , &(termData -> transAmount));
    if((termData -> transAmount) <= 0){
        printf("INVALID_AMOUNT\n");
        return INVALID_AMOUNT;
    }else{
        printf("TERMINAL_OK\n");
        return TERMINAL_OK;
    }
}

/* This functions checks if the transaction amount is below the maximum amount or not
    ---------------------
        Function Test
    ---------------------
    ST_terminalData_t card1;
    EN_terminalError_t result = isBelowMaxAmount(&card1);
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    printf("Enter Transaction Amount: ");
    scanf("%f" , &(termData -> transAmount));
    printf("Enter Maximum Transaction Amount: ");
    scanf("%f" , &(termData -> maxTransAmount));
    if(termData -> transAmount > termData -> maxTransAmount){
        printf("EXCEED_MAX_AMOUNT\n");
        return EXCEED_MAX_AMOUNT;
    }else{
        printf("TERMINAL_OK\n");
        return TERMINAL_OK;
    }
}

/* This function asks the user to enter the maximum transaction amount
   to store it in the structure maxTransAmount element and checks if it's invalid or not
    ---------------------
        Function Test
    ---------------------
    ST_terminalData_t card1;
    EN_terminalError_t result = setMaxAmount(&card1);
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    printf("Enter Maximum Transaction Amount: ");
    scanf("%f" , &(termData -> maxTransAmount));
    if(termData -> maxTransAmount <= 0){
        printf("INVALID_MAX_AMOUNT\n");
        return INVALID_MAX_AMOUNT;
    }else{
        printf("TERMINAL_OK\n");
        return TERMINAL_OK;
    }
}