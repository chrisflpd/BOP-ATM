/*
Copyright 2023 Spanoudakis Stavros, Filippidis Christos

This file is part of BOP_ATM which is released under GNU General Purpose License version 3.
See LICENSE.txt or go to <https://www.gnu.org/licenses/> for full license details.
*/


void check_files(void);

struct User get_user_from_username(char *username);

struct User get_user_from_id(unsigned long long int id);

struct User get_user_from_iban(unsigned long long int iban);

void load_deposits_history(unsigned long long int id);

void load_withdrawals_history(unsigned long long int id);

void load_transfers_rec_history(unsigned long long int id);

void load_transfers_send_history(unsigned long long int id);

void random_id(unsigned long long int *id);

void random_iban(unsigned long long int *iban);

unsigned long long int create_new_user(char *name, char *surname, char *username, short int pin, unsigned int tin);

void new_deposit(unsigned long long int id, float amount, char *description);

void new_withdrawal(unsigned long long int id, float amount, char *description);

void new_transfer(unsigned long long int id_sender, unsigned long long int id_receiver, float amount, char *description);
