#ifndef CARD_H_
#define CARD_H_

typedef unsigned char uint8_t;

/* This structure has the data of the payment card
   which are the holder_name, primary_number and also the expiration date */
typedef struct ST_cardData_t{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

/* This enum has the status of every possible return value of the functions */
typedef enum EN_cardError_t{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/* Functions Prototypes */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* CARD_H_ */