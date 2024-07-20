/*
BOP_ATM is an automated teller machine simulator.
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


short int active = 1; //global ���������, � ����� ������� �� 1, ����� ��� �� � ������� ������� ��� ��������� ����������� "%%%", ����� ������� 0


/*��������� welcome: ���������� ��� ������ ��� ��� ���������� ��
������� ��� ��������� '%%%' ����������� ������ ����� �� ���������� �� ���������.
� ��������� ��� ������� ����������� ��� ��� ���������� ����.*/
void welcome(void)
{
    system("cls");
    SetColor(PURPLE);
    printf("\t\t\t\t\tWELCOME MENU\n\n");
    SetColor(WHITE);

    puts("Welcome to the official ATM of BOP (Bank Of Programmers)."
         "\nIf at any moment you want to terminate the session, enter %%%.\n\n");
}

/*��������� register_or_login: ���������� ��� ������ �� �������� �� ����� ��
������������ ���������� ���������� � �� �������� �� ��� ������� ��� ���� ��� ���������� ������, ���������� ��� ������� ���.
� ��������� ������� ��� ��������� ���� ������ ���� ������� ��� ������ ��� ��� ���������� ����.*/
void register_or_login(char *choice_r_l)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("Would you like to register or login? [r: register, l: login]");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //������� ��� �������� �������� ��� ���� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_r_l = tolower(input[0]); //��������� ��� ��������� �� ���� ��� ���������� ���

        switch (*choice_r_l) //������� ��� �������� ��������� �������� ��� 'r' ��� 'l'
        {
        case 'r':
            break;
        case 'l':
            break;
        default:
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter r or l.\n\n");
            SetColor(WHITE);
            break;
        }
    }
    while (*choice_r_l != 'r' && *choice_r_l != 'l');
}

/*��������� yes_or_no: ���������� ��� ������ �� �������� �� ����� ��
����� ��� ��������� � �� ���������� ��� ���� ��� ���������� ������, ���������� ��� ������� ���.
� ��������� ������� ��� ��������� ���� ������ ���� ������� ��� ������ ��� ��� ���������� ����.*/
void yes_or_no(char *choice_y_n)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("\n\nWould you like to make another transaction? [y: yes, n: no]");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //������� ��� �������� �������� ��� ���� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_y_n = tolower(input[0]); //��������� ��� ��������� �� ���� ��� ���������� ���

        switch (*choice_y_n) //������� ��� �������� ��������� �������� ��� 'r' ��� 'l'
        {
        case 'y':
            break;
        case 'n':
            break;
        default:
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter y or n.\n\n");
            SetColor(WHITE);
            break;
        }
    }
    while (*choice_y_n != 'y' && *choice_y_n != 'n');
}

/*��������� select_history: ���������� ��� ������ �� �������� �� �����
�� ��� �� �������� ��� ����������, ��� ��������� � ��� ��������� ��� ���� ��� ���������� ������, ���������� ��� ������� ���.
� ��������� ������� ��� ��������� ���� ������ ���� ������� ��� ������ ��� ��� ���������� ����.*/
void select_history(char *choice_d_w_t)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("Would you like to view your deposits, withdrawals or transfers history?");
        printf("[d: deposits history, w: withdrawals history, t: transfers history]\n");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //������� ��� �������� �������� ��� ���� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_d_w_t = tolower(input[0]); //��������� ��� ��������� �� ���� ��� ���������� ���

        switch (*choice_d_w_t) //������� ��� �������� ��������� �������� ��� 'd', 'w' ��� ��� 't'
        {
        case 'd':
            break;
        case 'w':
            break;
        case 't':
            break;
        default:
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter d, w or t.\n\n");
            SetColor(WHITE);
            break;
        }
    }
    while (*choice_d_w_t != 'd' && *choice_d_w_t != 'w' && *choice_d_w_t != 't');
}

/*��������� select_info: ������� �������� ��������� ��� ��� ������ ������� �� ��� ����� ������
��� ���� ��� ���������� ������, ���������� ��� ������� ���.
� ��������� ������� ��� ��������� ���� ������ ���� ������� ��� ������ ��� ��� ���������� ����.*/
void select_info(char *choice_info)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //������� ��� �������� �������� ��� ���� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_info = tolower(input[0]); //��������� ��� ��������� �� ���� ��� ���������� ���

        switch (*choice_info) //������� ��� �������� ��������� �������� ��� 'w' ��� ��� 'i'
        {
        case 'w':
            break;
        case 'i':
            break;
        default:
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter w or i.\n\n");
            SetColor(WHITE);
            break;
        }
    }
    while (*choice_info != 'w' && *choice_info != 'i');
}


/*��������� get_creds_login: ���������� ��� ������ �� ������� �� �������� ���, ���� �� ��������
���� ���������� ��� ��� ���� ��� ���������� ������, �� ����������.
� ��������� ������� ��� ����������� ������ ��� ����� ������, ������ ���� ������ �����������
��� ������ ���� ��������� ������ ������������ ��� ������, ��� ��� ���������� ����.*/
void get_creds_login(char username[], unsigned long long int *id, short int *pin)
{
    char cleaner, input[MAX_USERNAME_SIZE + 1]; //== input[ID_DIGITS + 2];
    short int only_digits, only_word;;;

    //���� �������� ������ � ������� �����������:
    while (1)
    {
        puts("\n\nEnter your username or your ID:");
        scanf("%18[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_number(input, &only_digits); //������� ��� �������� ���� ������, �� ����� ����������� �������� ������� �����������

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) < ID_DIGITS) //������� ������ ������� �����������
        {
            error_sound();
            SetColor(RED);
            printf("\nYour id cannot be less than %d digits short. Please try again.\n\n", ID_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) > ID_DIGITS) //������� ������ ������� �����������
        {
            error_sound();
            SetColor(RED);
            printf("\nYour id cannot be more than %d digits long. Please try again.\n\n", ID_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) > MAX_USERNAME_SIZE - 1) //������� ������ �������� ������
        {
            error_sound();
            SetColor(RED);
            printf("\nYour username cannot be more than %d characters long. Please try again.\n\n", MAX_USERNAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) < MIN_USERNAME_SIZE) //������� ������ �������� ������
        {
            error_sound();
            SetColor(RED);
            printf("\nYour username cannot be less than %d characters short. Please try again.\n\n", MIN_USERNAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (only_digits) //�� � �������� ���� � ������� �����������
        {
            *id = strtoull(input, NULL, 10);
            break; //����������� ������ while
        }
        else //�� � �������� ���� �� ����� ������
        {
            strncpy(username, input, MAX_USERNAME_SIZE); //���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }

    //���� ���������� ������� ������������:
    while (active)
    {
        puts("\n\nEnter your pin:");
        scanf("%6[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_number(input, &only_digits); //������� ��� �������� ���� ������, �� ����� ����������� �������� ������� �����������

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //������� ��� �������� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nYour pin cannot contain any letters. Please try again.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > PIN_DIGITS) //������� ������ ���������� ������� ������������
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be more than %d digits long. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) < PIN_DIGITS) //������� ������ ���������� ������� ������������
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be less than %d digits short. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == PIN_DIGITS) //�� � �������� ���� �������� � ���������� ������� ������������
        {
            *pin = (short int)atoi(input); //��������� ��� ���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }
}

/*��������� get_creds_register: ���������� ��� ������ �� ������� �� �������� ���, ���� �� ������������
���� ���������� ���������� ��� ���� ��� ���������� ������, �� ����������.
� ��������� ������� ��� ����������� ������ ��� �����, ������ ��� �������,
������ ��� ����� ������, ������ ���� ��������� ������ ������������ ��� ������
��� ��� ��� ������, ��� ��� ���������� ����.*/
void get_creds_register(char name[], char surname[], char username[], short int *pin, unsigned int *tin)
{
    char cleaner, input[MAX_SURNAME_SIZE + 1];
    short int contains_digits, only_digits, only_word;

    //���� ��������:
    while (1)
    {
        puts("\n\nEnter your name:");
        scanf("%18[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_contains_digits(input, &contains_digits); //������� ��������� ��� ������ ������

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (contains_digits) //������� ��������� ��� ������ ������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your name cannot contain any digits. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) > MAX_NAME_SIZE - 1) //������� ������ ��������
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your name cannot be more than %d characters long. Please try again.\n\n", MAX_NAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MIN_NAME_SIZE) //������� ������ ��������
        {
            error_sound();
            SetColor(RED);
            printf("Invalid input. Your name cannot be less than %d characters short. Please try again.\n\n", MIN_NAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MAX_NAME_SIZE && strlen(input) > MIN_NAME_SIZE - 1) //�� � �������� ���� ��������� �����
        {
            strncpy(name, input, MAX_NAME_SIZE); //���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }

    //���� ��������:
    while (active)
    {
        puts("\n\nEnter your surname:");
        fgets(input, 26, stdin);

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0'; //������ ��� '\n' �� '\0'

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        if (strcmp("", input) == 0) //������� ��� �������� ������������ <ENTER>
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter your surname before pressing <ENTER>.\n");
            SetColor(WHITE);
            continue;
        }

        string_contains_digits(input, &contains_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (contains_digits) //������� ��������� ��� ������ ������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your surname cannot contain any digits. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) > MAX_SURNAME_SIZE - 1) //������� ������ ��������
        {
            while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your surname cannot be more than %d characters long. Please try again.\n\n", MAX_SURNAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MIN_SURNAME_SIZE) //������� ������ ��������
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your surname cannot be less than %d characters short. Please try again.\n\n", MIN_SURNAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MAX_SURNAME_SIZE && strlen(input) > MIN_SURNAME_SIZE - 1) //�� � �������� ���� ��������� �������
        {
            strncpy(surname, input, MAX_SURNAME_SIZE); //���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }

    //���� �������� ������:
    while (active)
    {
        puts("\n\nCreate a username. Your username should not be more than 16 characters long or less"
             " than 4 characters short and should not contain digits only:");
        fgets(input, 18, stdin);

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0'; //������ ��� '\n' �� '\0'

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        if (strcmp("", input) == 0) //������� ��� �������� ������������ <ENTER>
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter your username before pressing <ENTER>.\n");
            SetColor(WHITE);
            continue;
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits) //������� ��� �������� ���� ������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your username cannot contain only digits. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) > MAX_USERNAME_SIZE - 1) //������� ������ �������� ������
        {
            while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your username cannot be more than %d characters long. Please try again.\n\n", MAX_USERNAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) < MIN_USERNAME_SIZE) //������� ������ �������� ������
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your username cannot be less than %d characters short. Please try again.\n\n", MIN_USERNAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) < MAX_USERNAME_SIZE && strlen(input) > MIN_USERNAME_SIZE - 1) //�� � �������� ���� ��������� ����� ������
        {
            if (get_user_from_username(input).id == 0) //�� ��� ������� ������� �� ���� �� ����� ������
            {
                strncpy(username, input, MAX_USERNAME_SIZE); //���������� ��� ��������� �� ��������� ��� ����������
                break; //����������� ������ while //����������� ������ while
            }
            else //�� ������� ������� �� ���� �� ����� ������
            {
                error_sound();
                SetColor(RED);
                printf("\nInvalid input. The entered username already exists. Please choose a different one.\n\n");
                SetColor(WHITE);
            }

        }
    }

    //���� ���������� ������� ������������:
    while (active)
    {
        puts("\n\nCreate a pin. Your pin should be exactly 4 digits long. Do not share your pin:");
        scanf("%6[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //������� ��� �������� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your pin cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) > PIN_DIGITS) //������� ����� ���������� ������� ������������
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be more than %d characters long. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) < PIN_DIGITS) //������� ����� ���������� ������� ������������
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be less than %d characters short. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == PIN_DIGITS) //�� � �������� ���� ���������� ���������� ������� ��������������
        {
            *pin = (short int)atoi(input); //��������� ��� ���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }

    //���� ���:
    while (active)
    {
        puts("\n\nEnter your Tax Identification Number:");
        scanf("%11[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //������� ��� �������� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your Tax Identification Number cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) > TIN_DIGITS) //������� ������ ���
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your Tax Identification Number cannot be more than %d characters long. Please try again.\n\n", TIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) < TIN_DIGITS) //������� ������ ���
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your Tax Identification Number cannot be less than %d characters short. Please try again.\n\n", TIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == TIN_DIGITS) //�� � �������� ���� ��������� ���
        {
            *tin = (unsigned int)strtoul(input, NULL, 10); //��������� ��� ���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }
}

/*��������� select_mode: ���������� ��� ������ �� �������� �� ����� �� ����� ��������,
������� � �������� �������� � �� ����� �� ������� �� ���������
�������� ��� ����������� ��� ��� ���� ��� ���������� ������, ���������� ��� ������� ���.
� ��������� ������� ��� ��������� ������ ���� ������� ��� ������
��� ��� ���������� ����.*/
void select_mode(char *choice_d_w_t_b_c_h)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("Would you like to deposit, withdraw or transfer money?"
             " Alternatively,\nyou can check your balance, your transaction history or your credentials.\n[d: deposit, w: withdraw, t: transfer, b: check balance, h: transaction history, c: check credentials]");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //������� ��� �������� �������� ��� ���� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n");
            SetColor(WHITE);
            continue;
        }

        *choice_d_w_t_b_c_h = tolower(input[0]); //��������� ��� ��������� �� ���� ��� ���������� ���

        switch (*choice_d_w_t_b_c_h) //������� ��� �������� ��������� �������� ��� 'd', ��� 'w',��� 't', ��� 'b', ��� 'c' ��� ��� 'h'
        {
        case 'd':
            break;
        case 'w':
            break;
        case 't':
            break;
        case 'b':
            break;
        case 'c':
            break;
        case 'h':
            break;
        default:
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter d, w, t, b, c or h.\n");
            SetColor(WHITE);
            break;
        }
    }
    while (*choice_d_w_t_b_c_h != 'd' && *choice_d_w_t_b_c_h != 'w' && *choice_d_w_t_b_c_h != 't' && *choice_d_w_t_b_c_h != 'b' && *choice_d_w_t_b_c_h != 'c' && *choice_d_w_t_b_c_h != 'h');
}

/*��������� get_amount_description: ���������� ��� ������ �� ������� ��� �������� ��� ��������
��� ������� �� ��������� ��� ���� ��� ���������� ������,
��� ����������. ������, ���������� ��� ������ �� ������� ��� ��������� ��� ��� ���������
��� ���� ��� ���������� ������, ��� ����������. � ��������� ������� ��� ����������� ������ ����
�������� ��� �������� ��� ������ ���� ��������� ��� ����������, ��� ��� ���������� ����.*/
void get_amount_description(float *amount, char description[])
{
    char cleaner, input[MAX_AMOUNT_SIZE + 2], input_des[MAX_DESCRIPTION_SIZE + 1] = {'\0'};
    short int only_float, amount_error, only_word;

    //���� ���������:
    while (1)
    {
        amount_error = 0;

        puts("\n\nEnter desirable amount:");
        fgets(input, 11, stdin);

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0'; //������ ��� '\n' �� '\0'

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        if (strcmp("", input) == 0) //������� ��� �������� ������������ <ENTER>
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter an amount before pressing <ENTER>.\n");
            SetColor(WHITE);
            continue;
        }

        string_is_float_number(input, &only_float);

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > MAX_AMOUNT_SIZE) //������� ������ ���������
        {
            while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������
            amount_error = 1;
        }

        if (!only_float) //������� ��������� ��� ������ ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Amount cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (only_float) //�� � �������� ���� ��������� ��������
        {
            *amount =  atof(input); //��������� ��� ���������� ��� ��������� �� ��������� ��� ����������

            if (*amount > MAX_AMOUNT || amount_error == 1) //������� �������� ���������
            {
                error_sound();
                SetColor(RED);
                printf("\nInvalid input. Amount cannot be greater than %.2f Euros. Please try again.\n\n", MAX_AMOUNT);
                SetColor(WHITE);
                continue;
            }

            if (*amount == 0.0) //������� ��������� ��������� ���������
            {
                error_sound();
                SetColor(RED);
                puts("\nInvalid input. Amount cannot be zero Euros. Please try again.\n");
                SetColor(WHITE);
                continue;
            }

            break; //����������� ������ while
        }
    }

    //���� ����������:
    while (active)
    {
        puts("\n\nEnter a description for the transaction. The description should not be more than 256"
             " characters long.\nPress <ENTER> for no description:");
        scanf("%258[^\n]", input_des); //�������� ��� ���� �������� � ���������� '\n'

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        if (strlen(input_des) > MAX_DESCRIPTION_SIZE - 1) //������� ������ ����������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. The description cannot be more than 256 characters long. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input_des) < MAX_DESCRIPTION_SIZE) //������� ������ ����������
        {
            strncpy(description, input_des, MAX_DESCRIPTION_SIZE); //���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }
}

/*��������� get_user_to_transfer: ���������� ��� ������ �� ������� �� IBAN ���
������ ���� ����� ����� �� ��������� ������� ��� ���� ��� ���������� ������,
�� ����������. � ��������� ������� ��� ��������� ������ ��� IBAN ��� ������ ���� �����
�� ����������� �� ������� ��� ��� ���������� ����.*/
void get_user_to_transfer(unsigned long long int *iban)
{
    char cleaner, input[IBAN_DIGITS + 2];
    short int only_digits, only_word;

    //���� IBAN:
    while (1)
    {
        puts("\n\nEnter the IBAN of the user you want to transfer money to:");
        scanf("%18[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //���������� ��� ���� stdin ��� ���������� ����������

        if (terminate_transaction(input)) //����������� ������������ �� ��� �������� '%%%'
        {
            break; //����������� ������ while
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //������� ��� ������� �������� ��� ���� �����
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //������� ��� �������� ���������
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. IBAN cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > IBAN_DIGITS) //������� ������ iban
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. IBAN cannot be more than %d digits long. Please try again.\n\n", IBAN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) < IBAN_DIGITS) //������� ������ iban
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. IBAN cannot be less than %d digits short. Please try again.\n\n", IBAN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == IBAN_DIGITS) //�� �� iban ���� ���������
        {
            *iban = strtoull(input, NULL, 10); //��������� ��� ���������� ��� ��������� �� ��������� ��� ����������
            break; //����������� ������ while
        }
    }
}

/*��������� print_balance: ������� ���� ����� ��� ������ �� ��������� �������� ��� ����������� ���.
� ��������� ������� ��� ��������� �� ��������� �������� ��� ������ ��� ��� ���������� ����.*/
void print_balance(float balance)
{
    SetColor(BLUE);
    printf("\nCurrent balance: ");
    SetColor(WHITE);
    printf("%.2f Euros.", balance);
}

/*��������� print_creds: ������� ���� ����� ��� ������ ����������� ��� ��� �� ��������.
� ��������� ������� ��� ��������� ������ ��� �����, ������ ��� �������, ������ ��� ����� ������,
��� ��������� ������ ������������, �� ���, �� IBAN ��� ��� ������ ����������� ��� ������, ��� ��� ���������� ����.*/
void print_creds(char name[], char surname[], char username[], short int pin, unsigned int tin, unsigned long long int iban, unsigned long long int id)
{
    SetColor(BLUE);
    printf("\nName:      ");
    SetColor(WHITE);
    printf("%s", name);
    SetColor(BLUE);
    printf("\nSurname:   ");
    SetColor(WHITE);
    printf("%s", surname);
    SetColor(BLUE);
    printf("\nUsername:  ");
    SetColor(WHITE);
    printf("%s", username);
    SetColor(BLUE);
    printf("\nPin:       ");
    SetColor(WHITE);
    printf("%hi", pin);
    SetColor(BLUE);
    printf("\nTIN:       ");
    SetColor(WHITE);
    printf("%u", tin);
    SetColor(BLUE);
    printf("\nIBAN:      ");
    SetColor(WHITE);
    printf("%llu", iban);
    SetColor(BLUE);
    printf("\nID:        ");
    SetColor(WHITE);
    printf("%llu", id);
}

/*��������� print_deposits_history: ������� ���� ����� ��� ������ ����������� �� �������� ��� ���������� ���.
� ��������� ������� ��� ��������� ���� ������ ����� "Deposit", � ������ �������� �� �������� ���� ��������� ��� ������
��� ��� ���������� ����.*/
void print_deposits_history(struct Deposit deposits_history[])
{
    if (deposits_history[0].id == 0) //�� ��� ����� ����� ���������� �� ����� ��� ����������
    {
        error_sound();
        SetColor(RED);
        printf("No deposits have been made on this account.");
        SetColor(WHITE);
    }
    else
    {
        int dn = 0; //Number of deposit

        while (deposits_history[dn].id != 0)
        {
            SetColor(BLUE);
            printf("Deposit Number:    ");
            SetColor(WHITE);
            printf("%d\n", dn + 1);
            SetColor(BLUE);
            printf("Amount deposited:  ");
            SetColor(WHITE);
            printf("%.2f\n", deposits_history[dn].amount);
            SetColor(BLUE);
            printf("Time of deposit:   ");
            SetColor(WHITE);
            printf("%s", deposits_history[dn].date);
            SetColor(BLUE);
            printf("Description:       ");
            SetColor(WHITE);
            printf("%s\n\n\n", deposits_history[dn].description);
            dn++;
        }
    }
}

/*��������� print_withdrawals_history: ������� ���� ����� ��� ������ ����������� �� �������� ��� ��������� ���.
� ��������� ������� ��� ��������� ���� ������ ����� "Withdrawal", � ������ �������� �� �������� ���� �������� ��� ������
��� ��� ���������� ����.*/
void print_withdrawals_history(struct Withdrawal withdrawals_history[])
{
    if (withdrawals_history[0].id == 0) //�� ��� ����� ����� ��������� �� ����� ��� ����������
    {
        error_sound();
        SetColor(RED);
        printf("No withdrawals have been made on this account.");
        SetColor(WHITE);
    }
    else
    {
        int wn = 0; //Number of withdrawal

        while (withdrawals_history[wn].id != 0)
        {
            SetColor(BLUE);
            printf("Withdrawal Number:   ");
            SetColor(WHITE);
            printf("%d\n", wn + 1);
            SetColor(BLUE);
            printf("Amount withdrawn:    ");
            SetColor(WHITE);
            printf("%.2f\n", withdrawals_history[wn].amount);
            SetColor(BLUE);
            printf("Time of withdrawal:  ");
            SetColor(WHITE);
            printf("%s", withdrawals_history[wn].date);
            SetColor(BLUE);
            printf("Description:         ");
            SetColor(WHITE);
            printf("%f\n\n\n", withdrawals_history[wn].amount);
            wn++;
        }
    }
}

/*��������� print_transfers_rec_history: ������� ���� ����� ��� ������ ����������� �� �������� ��� ��������� ��� ���� �����.
� ��������� ������� ��� ��������� ���� ������ ����� "Transfer", � ������ �������� �� �������� ���� ��������� ��� ���� �����
��� ��� ���������� ����.*/
void print_transfers_rec_history(struct Transfer transfers_rec_history[])
{
    if (transfers_rec_history[0].id_receiver == 0) //�� ��� ����� ����� ��������� ���� ����� ��� ����������
    {
        error_sound();
        SetColor(RED);
        printf("No money has been received by this account.\n\n");
        SetColor(WHITE);
    }
    else
    {
        int tn = 0; //Number of transfer

        SetColor(PURPLE);
        printf("\n-Transfers received-\n");

        while (transfers_rec_history[tn].id_receiver != 0)
        {
            SetColor(BLUE);
            printf("Transfer Number:   ");
            SetColor(WHITE);
            printf("%d\n", tn + 1);
            SetColor(BLUE);
            printf("Sender IBAN:       ");
            SetColor(WHITE);
            printf("%llu\n", get_user_from_id(transfers_rec_history[tn].id_sender).iban);
            SetColor(BLUE);
            printf("Amount received:   ");
            SetColor(WHITE);
            printf("%.2f\n", transfers_rec_history[tn].amount);
            SetColor(BLUE);
            printf("Time of transfer:  ");
            SetColor(WHITE);
            printf("%s", transfers_rec_history[tn].date);
            SetColor(BLUE);
            printf("Description:       ");
            SetColor(WHITE);
            printf("%s\n\n", transfers_rec_history[tn].description);
            tn++;
        }
    }
}

/*��������� print_transfers_send_history: ������� ���� ����� ��� ������ ����������� �� �������� ��� ��������� ��� ���� ����������.
� ��������� ������� ��� ��������� ���� ������ ����� "Transfer", � ������ �������� �� �������� ���� ��������� ��� ���� ����������
��� ��� ���������� ����.*/
void print_transfers_send_history(struct Transfer transfers_send_history[])
{
    if (transfers_send_history[0].id_sender == 0) //�� ��� ����� ����� ��������� ��� ����� ��� ����������
    {
        error_sound();
        SetColor(RED);
        printf("No money has been sent by this account.\n");
        SetColor(WHITE);
    }
    else
    {
        int tn = 0; //Number of transfer

        SetColor(PURPLE);
        printf("\n-Transfers sent-\n");

        while (transfers_send_history[tn].id_sender != 0)
        {
            SetColor(BLUE);
            SetColor(BLUE);
            printf("Transfer Number:   ");
            SetColor(WHITE);
            printf("%d\n", tn + 1);
            SetColor(BLUE);
            printf("Receiver IBAN:     ");
            SetColor(WHITE);
            printf("%llu\n", get_user_from_id(transfers_send_history[tn].id_receiver).iban);
            SetColor(BLUE);
            printf("Amount sent:       ");
            SetColor(WHITE);
            printf("%.2f\n", transfers_send_history[tn].amount);
            SetColor(BLUE);
            printf("Time of transfer:  ");
            SetColor(WHITE);
            printf("%s", transfers_send_history[tn].date);
            SetColor(BLUE);
            printf("Description:       ");
            SetColor(WHITE);
            printf("%s\n\n", transfers_send_history[tn].description);
            tn++;
        }
    }
}

/*��������� string_is_number: ������� �� ���� �������� ���������� ����������� ��� ������,
����� ��� ����� �������. � ��������� ������� ��� ����������� ������ ���� �������� ���
������ ��� ��������� only_digits, ��� ��� ���������� ����.*/
void string_is_number(char input[], short int *only_digits)
{
    int i;

    *only_digits = 1;

    for (i = 0; i < (int)strlen(input); i++) //������� ��� �������� ���� ������
    {
        if (!isdigit(input[i]))
        {
            *only_digits = 0;
        }
    }
}

/*��������� string_is_float_number: ������� �� ���� �������� ���������� �������� ��� ��� �����������
� �� ����������� �������, ����� ��� ����� ������� ������� ������������.
� ��������� ������� ��� ����������� ������ ���� �������� ���
������ ��� ��������� only_float, ��� ��� ���������� ����.*/
void string_is_float_number(char input[], short int *only_float)
{
    int i, number_of_points = 0;

    *only_float = 1;

    for (i = 0; i < (int)strlen(input); i++)
    {
        if (input[i] == '.') //����������� ������������ ���� ��������
        {
            number_of_points++;
        }

        if (!isdigit(input[i]) && input[i] != '.') //������� ��� ������ ��������� ���� ��������
        {
            *only_float = 0;
        }
    }

    if (number_of_points > 1) //������� ��� ������ �������� ��� ���� ������������
    {
        *only_float = 0;
    }
}

/*��������� string_contains_digits: ������� �� ���� �������� ���������� ����������� ��� �����,
����� ��� ����� ����. � ��������� ������� ��� ����������� ������ ���� �������� ���
������ ��� ��������� contains_digits, ��� ��� ���������� ����.*/
void string_contains_digits(char input[], short int *contains_digits)
{
    int i;

    *contains_digits = 0;

    for (i = 0; i < (int)strlen(input); i++) //������� ��������� ��� ������ ������
    {
        if (isdigit(input[i]))
        {
            *contains_digits = 1;
        }
    }
}

/*��������� string_is_one_word: ������� �� ���� �������� ���������� ����������� ���� ���������� �����,
����� ����������� ��� �������� ��� ��� ������. � ��������� ������� ��� ����������� ������ ���� �������� ���
������ ��� ��������� only_word, ��� ��� ���������� ����.*/
void string_is_one_word(char input[], short int *only_word)
{
    int i;

    *only_word = 1;

    for (i = 0; i < (int)strlen(input); i++) //������� ��������� ��� ������ ������
    {
        if (input[i] == ' ')
        {
            *only_word = 0;
        }
    }
}

/*��������� terminate_transaction: ������� �� � �������� ����� � ���������� ������ '%%%' ��� ������� ��
���������� ������. � ��������� ������� ��� ��������� ������ ���� �������� ��� ����������
1, �� � �������� ���� � ���������� ������, ��� �� ����������� ��������� ���������� 0.*/
short int terminate_transaction(char input[])
{
    if (strcmp("%%%", input) == 0)
    {
        SetColor(ORANGE); //���� ����� � ����� 6?
        print_message_slowly("\n\nTerminating session...Thank you for choosing BOP!");
        SetColor(WHITE); //����� �����
        Sleep(LONG_SLEEP_TIME);
        active = 0;

        return 1;
    }

    return 0;
}

/*��������� SetColor: ������� �� ����� ��� �������� ���� ��� stdout.
� ��������� ������� ��� ��������� ��� ������ ��� �������� ��� ��� ���������� ����.
����: https://stackoverflow.com/a/29578507*/
void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forground color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

/*��������� print_message_slowly: ������� ������ ���� ������ ��� ������������,
�� ��� ����� ����������� ������� ���� ������ ��� ���������. � ��������� �������
��� ��������� ������ ��� ������������ ��� ��� ���������� ����.*/
void print_message_slowly(char message[])
{
    for (int i = 0; i < (int)strlen(message); i++)
    {
        putchar(message[i]);
        Sleep(VERY_SHORT_SLEEP_TIME);
    }

    putchar('\n');
}

/*��������� cooldown: ������� �� � ���������� ��� ����� ��� � ����������
��� ����, ����� � ������� ���� ����� ����� � �������� ������������ ����������� ��������
��� ��� ���������� �� ����� ��� ���������� ��� 10 ������������. � ��������� �������
��� ��������� ������ ��� ��������� invalid_input ��� ���������� 1, �� � ������� ����� ����� �
������������ ������������ �����������, ��� �� ����������� ��������� ���������� 0.*/
short int cooldown(short int *invalid_input)
{
    if (*invalid_input >= 3)
    {
        *invalid_input = 0;

        putchar('\n');

        error_sound();

        for (int seconds = 10; seconds >= 0; seconds--)
        {
            SetColor(RED);
            printf("Too many failed attempts. You can try again in %d seconds. \r", seconds);
            SetColor(WHITE);
            Sleep(1000);
        }

        putchar('\n');

        return 1;
    }

    return 0;
}

/*��������� error_sound: ������� ��� ���������.
� ��������� ��� ������� ����������� ��� ��� ���������� ����.*/
void error_sound(void)
{
    Beep(E, SOUND_DURATION);
    Beep(D, SOUND_DURATION);
}

/*��������� success_sound: ������� ��� ���������.
� ��������� ��� ������� ����������� ��� ��� ���������� ����.*/
void success_sound(void)
{
    Beep(D, SOUND_DURATION);
    Beep(CH, SOUND_DURATION);
}
