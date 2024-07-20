/*
BOP ATM is an automated teller machine simulator.
Copyright 2023 Spanoudakis Stavros, Filippidis Christos

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "initialization.h"
#include "user_interface.h"
#include "file_access.h"


/*����� ��������� main: ������������� ���� ��� ���������� �����������.
��� ������������, ���������� ��� ������ ������� �� ��� ������� ��� ������������, ������� ��� ����������� ����
��� ����������� ���������� ��� ���������� ���� �������� ����� while. ���� �� �����, � ������� �������� ��� ���������
��� ����� �� ����� ��� �� ����������� ����������� ���������. ���� ���� ������� ���������� �� "session" ���,
���� ����������� ��� ��������� ��� ��������� ������ ��� ���� ����� ����������� �� ���� � ������ �����,
�� ������� ���� ������. � ��������� ��� ������� ����������� ��� ���������� 0 �� ��� ������� �������� ���,
�� ��� ���� �������������� ���� ��� ������������, ���� ��� ��������� ������ while.*/
int main()
{
    system("cls");

    printf("BOP_ATM Copyright 2023 Spanoudakis Stavros, Filippidis Christos\n\n"
           "This program comes with ABSOLUTELY NO WARRANTY; for more information, enter 'w'.\n"
           "This is free software and you are welcome to redistribute it\n"
           "under certain conditions; for full list of conditions, see LICENSE.txt\n\n"
           "To initiate the main program, enter 'i'\n"); //Copyright Claim

    char choice_info;
    select_info(&choice_info); //w ��� warranty, i ��� �������� ��� ����� ����� ��� ������������

    switch(choice_info)
    {
    case 'w':
        printf("\nDisclaimer of Warranty\n\nTHERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTEND PERMITTED BY\n"
               "APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n"
               "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM ""AS IS"" WITHOUT WARRANTY\n"
               "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INLCUDING, BUT NOT LIMITED TO,\n"
               "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n"
               "PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n"
               "IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n"
               "ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\n"
               "Enter 'i' to initiate the main program:\n");
        select_info(&choice_info);
    case 'i':
        break;
    }

    //������ ���� ��� ����������
    char choice_r_l;
    char choice_d_w_t_b_c_h;
    char choice_y_n;
    char choice_d_w_t;
    short int is_logged_in, invalid_input;
    extern short int active;
    float current_amount;
    char current_description[MAX_DESCRIPTION_SIZE];
    unsigned long long int requested_iban;

    check_files();

    while(1) //������ ��������� ������
    {
        //������������� ���� ��� ����������
        active = 1;
        requested_iban = 2; //���� ��� �������� ���������
        is_logged_in = 0;
        choice_r_l = '0';
        choice_y_n = '0';
        invalid_input = 0;
        strcpy(current_user.username, " ");
        current_user.id = 0;
        current_user.pin = 0;

        for (int r = 0; r < MAX_NUMBER_OF_DEPOSITS; r++)
        {
            deposits_history[r].id = 0;
        }

        for (int r = 0; r < MAX_NUMBER_OF_WITHDRAWALS; r++)
        {
            withdrawals_history[r].id = 0;
        }

        for (int r = 0; r < MAX_NUMBER_OF_TRANSFERS; r++)
        {
            transfers_rec_history[r].id_receiver = 0;
            transfers_send_history[r].id_sender = 0;
        }

        //������ �������������� �� ��� ������
        system("cls");
        welcome();

        register_or_login(&choice_r_l); //r ��� �������, l ��� �������

        if (choice_r_l == 'l' && active)
        {
            system("cls");
            SetColor(PURPLE);
            printf("\t\t\t\t\tLOGIN");
            SetColor(WHITE);

            while (is_logged_in == 0)
            {
                get_creds_login(current_user.username, &current_user.id, &current_user.pin); //���� ��� ����������� ��������� ��� �������
                if (!active) break;

                if (current_user.id == 0) //�� ����� ������� ���� �������� ������
                {
                    if (get_user_from_username(current_user.username).pin == current_user.pin) //�� �� pin ����������� ��� �������� ����� ������
                    {
                        success_sound();
                        SetColor(GREEN);
                        printf("\n\nYou have successfully logged in.\n");
                        SetColor(WHITE);
                        Sleep(SHORT_SLEEP_TIME);
                        system("cls");
                        current_user = get_user_from_username(current_user.username); //���������� ���� ��� ��������� ��� ������ ��� ����� ��������� ��� ���� current_user
                        is_logged_in = 1;
                    }
                    else
                    {
                        invalid_input++;
                        error_sound();
                        SetColor(RED);
                        printf("\nThe combination of the username and PIN you entered is incorrect. Please try again.\n");
                        SetColor(WHITE);
                    }
                }
                else //�� ����� ������� ���� ������� �����������
                {
                    if (get_user_from_id(current_user.id).pin == current_user.pin) //�� �� pin ����������� ���� ���������� ������ �����������
                    {
                        success_sound();
                        SetColor(GREEN);
                        printf("\n\nYou have successfully logged in.\n");
                        SetColor(WHITE);
                        Sleep(SHORT_SLEEP_TIME);
                        system("cls");
                        is_logged_in = 1;
                    }
                    else
                    {
                        invalid_input++;
                        error_sound();
                        SetColor(RED);
                        printf("\nThe combination of the ID and PIN you entered is incorrect. Please try again.\n");
                        SetColor(WHITE);
                    }
                }

                if (cooldown(&invalid_input) == 1) //�� � ������� ����� ���� ��� ����� ������������ ����������� ��������
                {
                    continue;
                }
            }
        }
        else if (choice_r_l == 'r' && active)
        {
            system("cls");
            SetColor(PURPLE);
            printf("\t\t\t\t\tREGISTRATION");
            SetColor(WHITE);
            get_creds_register(current_user.name, current_user.surname, current_user.username, &current_user.pin, &current_user.tin); //���� ��� ����������� ��������� ��� �������
            current_user.id = create_new_user(current_user.name, current_user.surname, current_user.username, current_user.pin, current_user.tin); //���������� ���� ������ ��� ���������� ��� ������� ����������� ��� ��� ����� ����� current_user.id
            is_logged_in = 1;
            system("cls");
        }

        while (is_logged_in && active)
        {
            if (choice_y_n == 'n' || !active) //�� � ������� ������� ��� ��� ����� �� ����� ���� ��������
            {
                SetColor(ORANGE);
                print_message_slowly("\n\nTerminating session...Thank you for choosing BOP!");
                SetColor(WHITE);
                Sleep(LONG_SLEEP_TIME);
                break;
            }
            else if (choice_y_n == 'y') //�� � ������� ������� ��� ����� �� ����� ��� ���� ��������
            {
                system("cls");
            }

            //������������ ��� ���������� ��������
            choice_d_w_t_b_c_h = '0';
            choice_d_w_t = '0';

            SetColor(PURPLE);
            printf("\t\t\t\t\tMAIN MENU\n\n");
            SetColor(WHITE);

            current_user = get_user_from_id(current_user.id); //���������� ���� ��� ��������� ��� ������������ ������ ��� ���� current_user

            select_mode(&choice_d_w_t_b_c_h); //d ��� ��������, w ��� �������, t ��� ��������, b ��� ������ ���������, c ��� ������ ���������, h ��� ������ ��������� ����������

            switch(choice_d_w_t_b_c_h)
            {
            case 'd':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tNEW DEPOSIT");
                SetColor(WHITE);
                get_amount_description(&current_amount, current_description); //���� ��������� ���������
                if (!active) break;
                new_deposit(current_user.id, current_amount, current_description); //���������� ��������� ���������
                current_user = get_user_from_id(current_user.id); //���������� ���� ��� ��������� ��� ������������ ������ ��� ���� current_user
                success_sound();
                SetColor(GREEN);
                printf("\nYour balance has been updated.\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //�������� ���� ���������
                Sleep(SHORT_SLEEP_TIME);
                yes_or_no(&choice_y_n); //y ��� ��� ���������, n ��� ���������
                break;

            case 'w':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tNEW WITHDRAWAL");
                SetColor(WHITE);
                get_amount_description(&current_amount, current_description); //���� ��������� ��������
                if (!active) break;

                while (current_amount > current_user.balance && active) //��� � ���� ������� �������� ���������� �� ��������
                {
                    error_sound();
                    SetColor(RED);
                    printf("\nThe entered amount surpasses your current balance. Please try again.\n");
                    SetColor(WHITE);
                    get_amount_description(&current_amount, current_description); //���� ��������� ��������
                }

                if (!active) break;
                new_withdrawal(current_user.id, current_amount, current_description); //���������� ��������� ��������
                current_user = get_user_from_id(current_user.id); //���������� ���� ��� ��������� ��� ������������ ������ ��� ���� current_user
                success_sound();
                SetColor(GREEN);
                printf("\nYour balance has been updated.\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //�������� ���� ���������
                Sleep(SHORT_SLEEP_TIME);
                yes_or_no(&choice_y_n); //y ��� ��� ���������, n ��� ���������
                break;

            case 't':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tNEW TRANSFER");
                SetColor(WHITE);
                get_user_to_transfer(&requested_iban); //���� iban ���������
                if (!active) break;

                while (get_user_from_iban(requested_iban).iban != requested_iban) //��� �� �������� iban ��� ���������� �� ������� iban
                {
                    error_sound();
                    SetColor(RED);
                    printf("\nThe entered IBAN does not exist. Please try again.\n");
                    SetColor(WHITE);
                    get_user_to_transfer(&requested_iban); //���� iban ���������
                    if (!active) break;
                }

                if (!active) break;
                get_amount_description(&current_amount, current_description); //���� ��������� ���������
                if (!active) break;

                while (current_amount > current_user.balance && active) //��� � ���� �������� �������� ���������� �� ��������
                {
                    error_sound();
                    SetColor(RED);
                    printf("\nThe entered amount surpasses your current balance. Please try again.\n");
                    SetColor(WHITE);
                    get_amount_description(&current_amount, current_description); //���� ��������� ���������
                }

                if (!active) break;
                new_transfer(current_user.id, get_user_from_iban(requested_iban).id, current_amount, current_description); //���������� ��������� ���������
                current_user = get_user_from_id(current_user.id); //���������� ���� ��� ��������� ��� ������������ ������ ��� ���� current_user
                success_sound();
                SetColor(GREEN);
                printf("\nTransfer is complete.\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //�������� ���� ���������
                Sleep(SHORT_SLEEP_TIME);
                yes_or_no(&choice_y_n); //y ��� ��� ���������, n ��� ���������
                break;

            case 'b':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tBALANCE\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //�������� ���������
                if (!active) break;
                yes_or_no(&choice_y_n); //y ��� ��� ���������, n ��� ���������
                break;

            case 'c':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tCREDENTIALS\n");
                SetColor(WHITE);
                current_user = get_user_from_id(current_user.id); //���������� ���� ��� ��������� ��� ������������ ������ ��� ���� current_user
                print_creds(current_user.name, current_user.surname, current_user.username, current_user.pin, current_user.tin, current_user.iban, current_user.id); //�������� ���� ��� ��������� ��� ������
                yes_or_no(&choice_y_n); //y ��� ��� ���������, n ��� ���������
                break;

            case 'h':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tTRANSACTION HISTORY MENU\n\n");
                SetColor(WHITE);

                select_history(&choice_d_w_t); //d ��� �������� ����������, w ��� �������� ���������, t ��� �������� ���������

                system("cls");

                switch(choice_d_w_t)
                {
                case 'd':
                    SetColor(PURPLE);
                    printf("\t\t\t\t\tDEPOSITS HISTORY\n\n");
                    SetColor(WHITE);
                    load_deposits_history(current_user.id); //������ ��� ���������� ��� ������ �� ������ ����������� "current_user.id"
                    print_deposits_history(deposits_history); //�������� ��� ��������� ����������
                    break;

                case 'w':
                    SetColor(PURPLE);
                    printf("\t\t\t\t\tWITHDRAWALS HISTORY\n\n");
                    SetColor(WHITE);
                    load_withdrawals_history(current_user.id); //������ ��� ��������� ��� ������ �� ������ ����������� "current_user.id"
                    print_withdrawals_history(withdrawals_history); //�������� ��� ��������� ���������
                    break;

                case 't':
                    SetColor(PURPLE);
                    printf("\t\t\t\t\tTRANSFERS HISTORY\n\n");
                    SetColor(WHITE);
                    load_transfers_rec_history(current_user.id); //������ ��� ��������� ��������� ��� ������ �� ������ ����������� "current_user.id"
                    load_transfers_send_history(current_user.id); //������ ��� ������������ ��������� ��� ������ �� ������ ����������� "current_user.id"
                    print_transfers_rec_history(transfers_rec_history); //�������� ��� ��������� ��������� ���������
                    print_transfers_send_history(transfers_send_history); //�������� ��� ��������� ������������ ���������
                    break;
                }

                yes_or_no(&choice_y_n); //y ��� ��� ���������, n ��� ���������
                break;
            }
        }
    }
    return 0;
}
