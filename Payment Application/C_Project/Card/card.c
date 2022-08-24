#include <stdio.h>
#include <ctype.h>      // This library to get isdigit function to check if number or not
#include "card.h"
#include "string.h"     // This library to get strlen function to know the length of the string

/* This function asks the user for
   the card holder name and returns
   the status of the card name which will be WRONG or OK
    --------------------
        Function Test
    --------------------
    ST_cardData_t card1;
    EN_cardError_t result = getCardHolderName(&card1);
    printf("Result is : %d\n" , result);
*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
    printf("Enter Card Name: ");
    gets(cardData -> cardHolderName);
    if((strlen(cardData -> cardHolderName) > 24) || (strlen(cardData -> cardHolderName) < 20 || (cardData -> cardHolderName) == NULL)){
        printf("WRONG_NAME\n");
        return WRONG_NAME;
    }else{
        printf("CARD_OK\n");
        return CARD_OK;
    }
}

/* This function asks the user for the expiration date
   and then returns the status of the card expiration date
   which will be WRONG if the date isn't valid or OK 
    --------------------
        Function Test
    --------------------
    ST_cardData_t card1;
    EN_cardError_t result = getCardExpiryDate(&card1);
    printf("Result is : %d\n" , result);
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    printf("Enter Card Expiry Date in format (MM/YY): ");
    gets(cardData -> cardExpirationDate);
    if(strlen(cardData -> cardExpirationDate) != 5){
        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    }
    if(!isdigit(cardData -> cardExpirationDate[0])){
        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    }
    if(!isdigit(cardData -> cardExpirationDate[1])){
        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    }
    if(cardData -> cardExpirationDate[2] != '/'){
        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    }
    if(!isdigit(cardData -> cardExpirationDate[3])){
        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    }
    if(!isdigit(cardData -> cardExpirationDate[4])){
        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    }
    if(cardData -> cardExpirationDate == NULL){
        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    }
    printf("CARD_OK\n");
    return CARD_OK;
}

/* This function asks for the card's Primary Account Number and store it in card data. 
    --------------------
        Function Test
    --------------------
    ST_cardData_t card1;
    EN_cardError_t result = getCardPAN(&card1);
    printf("Result is : %d\n" , result);
*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    printf("Enter Primary Account Number: ");
    gets(cardData -> primaryAccountNumber);
    if((strlen(cardData -> primaryAccountNumber) > 19) || (strlen(cardData -> primaryAccountNumber) < 16) || cardData -> primaryAccountNumber == NULL){
        printf("WRONG_PAN\n");
        return WRONG_PAN;
    }else{
        printf("CARD_OK\n");
        return CARD_OK;
    }
}