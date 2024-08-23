/*
Copyright 2023 Spanoudakis Stavros, Filippidis Christos

This file is part of BOP_ATM which is released under GNU General Purpose License version 3.
See LICENSE.txt or go to <https://www.gnu.org/licenses/> for full license details.
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>


//macros σχετικά με το αρχείο "file_access"
#define MAX_NUMBER_OF_USERS 16
#define MAX_NUMBER_OF_DEPOSITS 1024
#define MAX_NUMBER_OF_WITHDRAWALS 1024
#define MAX_NUMBER_OF_TRANSFERS 512

//macros σχετικά με το αρχείο "user_interface"
#define MAX_CHOICE_INPUT 4
#define ID_DIGITS 16
#define MAX_USERNAME_SIZE 17
#define MIN_USERNAME_SIZE 4
#define PIN_DIGITS 4
#define MAX_NAME_SIZE 17
#define MIN_NAME_SIZE 2
#define MAX_SURNAME_SIZE 25
#define MIN_SURNAME_SIZE 2
#define TIN_DIGITS 9
#define MAX_AMOUNT 99999.9 //euros
#define MAX_AMOUNT_SIZE 9
#define MAX_DESCRIPTION_SIZE 257
#define IBAN_DIGITS 16
#define LONG_SLEEP_TIME 4000 //ms
#define SHORT_SLEEP_TIME 1000 //ms
#define VERY_SHORT_SLEEP_TIME 40 //ms
#define WHITE 15
#define GREEN 10
#define BLUE 9
#define RED 4
#define PURPLE 13
#define ORANGE 12
#define D 293.7 //hz
#define E 329.6 //hz
#define CH 523.25 //hz
#define SOUND_DURATION 70 //ms


/*Δομή User: περιέχει όλα τα στοιχεία που πρέπει να
είναι αποθηκευμένα για κάθε χρήστη.*/
struct User
{
    unsigned long long int id;
    short int pin;
    char name[MAX_NAME_SIZE];
    char surname[MAX_SURNAME_SIZE];
    char username[MAX_USERNAME_SIZE];
    unsigned long long int iban;
    unsigned int tin;
    float balance;
};

/*Ο "users" είναι ένας πίνακας από δομές "User".*/
struct User users[MAX_NUMBER_OF_USERS];

/*Ο "current_user" είναι μία δομη τύπου "User".*/
struct User current_user;

/*Δομή Deposit: περιέχει όλα τα στοιχεία που πρέπει να
είναι αποθηκευμένα για κάθε κατάθεση.*/
struct Deposit
{
    unsigned long long int id;
    char date[32];
    float amount;
    char description[MAX_DESCRIPTION_SIZE];

};

/*Ο "deposits" είναι ένας πίνακας από δομές "Deposit".*/
struct Deposit deposits[MAX_NUMBER_OF_DEPOSITS];

/*Ο "deposits_history" είναι ένας πίνακας από δομές "Deposit".*/
struct Deposit deposits_history[MAX_NUMBER_OF_DEPOSITS];

/*Δομή Withdrawal: περιέχει όλα τα στοιχεία που πρέπει να
είναι αποθηκευμένα για κάθε ανάληψη.*/
struct Withdrawal
{
    unsigned long long int id;
    char date[32];
    float amount;
    char description[MAX_DESCRIPTION_SIZE];

};

/*Ο "withdrawals" είναι ένας πίνακας από δομές "Withdrawal".*/
struct Withdrawal withdrawals[MAX_NUMBER_OF_WITHDRAWALS];

/*Ο "withdrawals_history" είναι ένας πίνακας από δομές "Withdrawal".*/
struct Withdrawal withdrawals_history[MAX_NUMBER_OF_WITHDRAWALS];

/*Δομή Transfer: περιέχει όλα τα στοιχεία που πρέπει να
είναι αποθηκευμένα για κάθε μεταφορά.*/
struct Transfer
{
    unsigned long long int id_sender;
    unsigned long long int id_receiver;
    char date[32];
    float amount;
    char description[MAX_DESCRIPTION_SIZE];
};

/*Ο "transfers" είναι ένας πίνακας από δομές "Transfer".*/
struct Transfer transfers[MAX_NUMBER_OF_TRANSFERS];

/*Ο "transfers_rec_history" είναι ένας πίνακας από δομές "Transfer".*/
struct Transfer transfers_rec_history[MAX_NUMBER_OF_TRANSFERS];

/*Ο "transfers_send_history" είναι ένας πίνακας από δομές "Transfer".*/
struct Transfer transfers_send_history[MAX_NUMBER_OF_TRANSFERS];
