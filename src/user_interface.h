/*
Copyright 2023 Spanoudakis Stavros, Filippidis Christos

This file is part of BOP_ATM which is released under GNU General Purpose License version 3.
See LICENSE.txt or go to <https://www.gnu.org/licenses/> for full license details.
*/


void welcome(void);

void register_or_login(char *choice_r_l);

void yes_or_no(char *choice_y_n);

void select_history(char *choice_d_w_t);

void select_info(char *choice_info);

void get_creds_login(char username[], unsigned long long int *id, short int *pin);

void get_creds_register(char name[], char surname[], char username[], short int *pin, unsigned int *tin);

void select_mode(char *choice_d_w_t_b_c_h);

void get_amount_description(float *amount, char description[]);

void get_user_to_transfer(unsigned long long int *iban);

void print_balance(float balance);

void print_creds(char name[], char surname[], char username[], short int pin, unsigned int tin, unsigned long long int iban, unsigned long long int id);

void print_deposits_history(struct Deposit deposits_history[]);

void print_withdrawals_history(struct Withdrawal withdrawals_history[]);

void print_transfers_rec_history(struct Transfer transfers_rec_history[]);

void print_transfers_send_history(struct Transfer transfers_send_history[]);

void string_is_number(char input[], short int *only_digits);

void string_is_float_number(char input[], short int *only_float);

void string_contains_digits(char input[], short int *contains_digits);

void string_is_one_word(char input[], short int *only_word);

short int terminate_transaction(char input[]);

void SetColor(int ForgC);

void print_message_slowly(char message[]);

short int cooldown(short int *invalid_input);

void error_sound(void);

void success_sound(void);
