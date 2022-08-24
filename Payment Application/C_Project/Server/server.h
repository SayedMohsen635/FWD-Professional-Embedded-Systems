#ifndef SERVER_H_
#define SERVER_H_
#include "../Card/card.h"
#include "../Terminal/terminal.h"

typedef unsigned int uint32_t;
extern uint32_t sequenceNumber;

/* This enum has the possible return values of the status of transaction operation of the card */
typedef enum EN_transState_t{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

/* This structure has some data of the card module,
   terminal module and also some specific elements for the server module  */
typedef struct ST_transaction_t{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

/* This enum has the possible return values of the server erros */
typedef enum EN_serverError_t{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

/* This enum has the possible return values of the account status */
typedef enum EN_accountState_t{
    RUNNING,
    BLOCKED
}EN_accountState_t;

/* This structure has the database of the card */
typedef struct ST_accountsDB_t{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/* Functions Prototypes */
EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData , ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);

#endif /* SERVER_H_ */