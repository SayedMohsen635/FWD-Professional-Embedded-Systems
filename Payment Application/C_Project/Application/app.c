#include <stdio.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

extern ST_accountsDB_t database[255];
extern uint32_t myIndex;

/* This program illustrates the given flow chart */
void appStart(void){
    ST_transaction_t account;
    /* 
    -----------------------------------------------------------------------------------------
    ---------------------------------Happy Scenario------------------------------------------
    -----------------------------------------------------------------------------------------
    */
    // if(getCardHolderName(&account.cardHolderData) == WRONG_NAME){
    //     return;
    // }
    // if(getCardExpiryDate(&account.cardHolderData) == WRONG_EXP_DATE){
    //     return;
    // }
    // if(getCardPAN(&account.cardHolderData) == WRONG_PAN){
    //     return;
    // }
    // getTransactionDate(&account.terminalData);
    // if(isCardExpired(&account.cardHolderData , &account.terminalData) == EXPIRED_CARD){
    //     return;
    // }
    // if(getTransactionAmount(&account.terminalData) == INVALID_AMOUNT){
    //     return;
    // }
    // recieveTransactionData(&account);
/* ------------------------------------------------------------------------------------------------------- */
    /* 
                                    --------------------------
                                      Testing The Application
                                    --------------------------
                    Transaction approved user story       --> Approved Story
                    Exceed the maximum amount user story  --> Excedded Max Amount
                    Insufficient fund user story          --> Insufficient Fund
                    Expired card user story               --> Expired Card
                    Invalid card user story               --> Blocked Card
    */
    if(getCardHolderName(&account.cardHolderData) == WRONG_NAME){
        return;
    }
    if(getCardExpiryDate(&account.cardHolderData) == WRONG_EXP_DATE){
        return;
    }
    if(getCardPAN(&account.cardHolderData) == WRONG_PAN){
        return;
    }
    getTransactionDate(&account.terminalData);
    if(isCardExpired(&account.cardHolderData , &account.terminalData) == EXPIRED_CARD){
        return;
    }
    if(isValidAccount(&account.cardHolderData , database) == ACCOUNT_NOT_FOUND){
        return;
    }
    if(isBlockedAccount(&database[myIndex]) == BLOCKED_ACCOUNT){
        printf("You can't use it anymore");
        return;
    }
    if(isBelowMaxAmount(&account.terminalData) == TERMINAL_OK){
        if(account.terminalData.transAmount > database[myIndex].balance){
            printf("DECLINED_INSUFFECIENT_FUND");
            return;
        }
        if(account.terminalData.transAmount <= database[myIndex].balance){
            saveTransaction(&account);
            printf("APPROVED\n");
            printf("Balance before update = %f\n" , database[myIndex].balance);
            database[myIndex].balance -= account.terminalData.transAmount;
            printf("Balance after update = %f\n" , database[myIndex].balance);
        }
    }
}