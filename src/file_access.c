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
#include "file_access.h"


/*��������� check_files: ������� �� �������� ������ ��� �� ������ data, deposits,
withdrawals ��� transfers. �� ��� ��������, �� ����������. �� ��������, ������� �� ���������� ������
��������� ��� ���������� �� ���������. � ��������� ��� ������� ����������� ��� ��� ���������� ����.*/
void check_files(void)
{
    FILE *uf, *df, *wf, *tf; //Users, Deposits, Withdrawals, Transfers Files

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        if ((uf = fopen("data.bin", "wb")) == NULL)
        {
            perror("Error");
            exit(errno);
        }
    }
    fclose(uf);

    if ((df = fopen("deposits.bin", "rb")) == NULL)
    {
        if ((df = fopen("deposits.bin", "wb")) == NULL)
        {
            perror("Error");
            exit(errno);
        }
    }
    fclose(df);

    if ((wf = fopen("withdrawals.bin", "rb")) == NULL)
    {
        if ((wf = fopen("withdrawals.bin", "wb")) == NULL)
        {
            perror("Error");
            exit(errno);
        }
    }
    fclose(wf);

    if ((tf = fopen("transfers.bin", "rb")) == NULL)
    {
        if ((tf = fopen("transfers.bin", "wb")) == NULL)
        {
            perror("Error");
            exit(errno);
        }
    }
    fclose(tf);
}

/*��������� get_user_from_username: �������� �� ������ "data.bin" ��� ����
��������� ��� ������ � ������ ���� ����� ������ ��� ���������. � ���������
������� ��� ��������� ������ ��� ����� ������ ��� ���������� ��� ����
����� User, users, � ����� �������� �� �������� ��� ������.*/
struct User get_user_from_username(char *username)
{
    FILE *uf; //Users File

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    static int i;

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //�������� ��� ������� "data.bin"
    {
        fread(&users[i], sizeof(struct User), 1, uf); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"

        if (strcmp(username, users[i].username) == 0) //�� �� ����� ������ ��� ������ ��� ����� ���������� ���������� �� ���� ��� ����������
            break;
    }

    fclose(uf);
    return users[i];
}

/*��������� get_user_from_id: �������� �� ������ "data.bin" ��� ����
��������� ��� ������ � ������ ���� ������ ����������� ��� ���������. � ���������
������� ��� ��������� ��� ������ ����������� ��� ���������� ��� ����
����� User, users, � ����� �������� �� �������� ��� ������.*/
struct User get_user_from_id(unsigned long long int id)
{
    FILE *up;

    if ((up = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    static int i;

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //�������� ��� ������� "data.bin"
    {
        fread(&users[i],sizeof(struct User), 1, up); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"

        if (id == users[i].id) //�� � ������� ����������� ��� ������ ��� ����� ���������� ���������� �� ����� ��� ����������
            break;
    }

    fclose(up);
    return users[i];
}

/*��������� get_user_from_iban: �������� �� ������ "data.bin" ��� ����
��������� ��� ������ � ������ ���� IBAN ��� ���������. � ���������
������� ��� ��������� �� IBAN ��� ���������� ��� ����
����� User, users, � ����� �������� �� �������� ��� ������.*/
struct User get_user_from_iban(unsigned long long int iban)
{
    FILE *up;

    if ((up = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    static int i;

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //�������� ��� ������� "data.bin"
    {
        fread(&users[i], sizeof(struct User), 1, up); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"

        if (iban == users[i].iban) //�� �� iban ��� ������ ��� ����� ���������� ���������� �� ���� ��� ����������
            break;
    }

    fclose(up);
    return users[i];
}

/*��������� load_deposits_history: �������� �� ������ "deposits.bin" ��� ����
��������� �������� ��� ��� ������ �� ������ ����������� ����� ��� ����������.
����, ���������� �� �������� ��� ������������� ��������� ���� ������ "deposits_history"
��� ������������� �� ���������� ����� ���� �� ���������� ��� �������� ������ �� �����
����������� ���� ������ "deposits_history". � ��������� ������� ��� ��������� ��� ���������
������ ����������� ��� ������ ��� ��� ���������� ����.*/
void load_deposits_history(unsigned long long int id)
{
    FILE *df; //Deposits File

    if ((df = fopen("deposits.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int dn = 0; //Number of found deposits

    for (int x = 0; x < MAX_NUMBER_OF_DEPOSITS; x++) //�������� ��� ������� "deposits.bin"
    {
        fread(&deposits[x], sizeof(struct Deposit), 1, df); //���������� ��� ��������� ��� ���������� ���� ������ �� �������� ��� ������ "deposits"

        if (id == deposits[x].id) //�� � ������� ����������� ��� ��������� ��� ����� ���������� ������� �� ��� ���������
        {
            deposits_history[dn] = deposits[x]; //���������� ��� ������������� ��������� ���� ������ "deposits_history"
            dn++;
        }
    }
    fclose(df);
}

/*��������� load_withdrawals_history: �������� �� ������ "withdrawals.bin" ��� ����
��������� �������� ��� ��� ������ �� ������ ����������� ����� ��� ����������.
����, ���������� �� �������� ��� ������������� �������� ���� ������ "withdrawals_history"
��� ������������� �� ���������� ����� ���� �� ��������� ��� �������� ������ �� �����
����������� ���� ������ "withdrawals_history". � ��������� ������� ��� ��������� ��� ���������
������ ����������� ��� ������ ��� ��� ���������� ����.*/
void load_withdrawals_history(unsigned long long int id)
{
    FILE *wf; //Withdrawals File

    if ((wf = fopen("withdrawals.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int wn = 0; //Number of found withdrawals

    for (int x = 0; x < MAX_NUMBER_OF_WITHDRAWALS; x++) //�������� ��� ������� "withdrawals.bin"
    {
        fread(&withdrawals[x], sizeof(struct Withdrawal), 1, wf); //���������� ��� ��������� ��� ��������� ���� ������ �� �������� ��� ������ "withdrawals"

        if (id == withdrawals[x].id) //�� � ������� ����������� ��� �������� ��� ����� ���������� ������� �� ��� ���������
        {
            withdrawals_history[wn] = withdrawals[x]; //���������� ��� ������������� �������� ���� ������ "withdrawals_history"
            wn++;
        }
    }
    fclose(wf);
}

/*��������� load_transfers_rec_history: �������� �� ������ "transfers.bin" ��� ����
��������� �������� ���� ��� ������ �� ������ ����������� ����� ��� ����������.
����, ���������� �� �������� ��� ������������� ��������� ���� ������ "transfers_rec_history"
��� ������������� �� ���������� ����� ���� �� ��������� ��� ��� �������� ������ �� �����
����������� ���� ������ "transfers_rec_history". � ��������� ������� ��� ��������� ��� ���������
������ ����������� ��� ������ ��� ��� ���������� ����.*/
void load_transfers_rec_history(unsigned long long int id)
{
    FILE *tf; //Transfers File

    if ((tf = fopen("transfers.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int tn = 0; //Number of found transfers

    for (int x = 0; x < MAX_NUMBER_OF_TRANSFERS; x++) //�������� ��� ������� "transfers.bin"
    {
        fread(&transfers[x], sizeof(struct Transfer), 1, tf); //���������� ��� ��������� ��� ��������� ���� ������ �� �������� ��� ������ "transfers"

        if (id == transfers[x].id_receiver) //�� � ������� ����������� ��������� ��� ��������� ��� ����� ���������� ������� �� ��� ���������
        {
            transfers_rec_history[tn] = transfers[x]; //���������� ��� ������������� ��������� ���� ������ "transfers_rec_history"
            tn++;
        }
    }
    fclose(tf);
}

/*��������� load_transfers_send_history: �������� �� ������ "transfers.bin" ��� ����
��������� �������� ��� ��� ������ �� ������ ����������� ����� ��� ����������.
����, ���������� �� �������� ��� ������������� ��������� ���� ������ "transfers_send_history"
��� ������������� �� ���������� ����� ���� �� ��������� ���� ��� �������� ������ �� �����
����������� ���� ������ "transfers_send_history". � ��������� ������� ��� ��������� ��� ���������
������ ����������� ��� ������ ��� ��� ���������� ����.*/
void load_transfers_send_history(unsigned long long int id)
{
    FILE *tf; //Transfers File

    if ((tf = fopen("transfers.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int tn = 0; //Number of found transfers

    for (int x = 0; x < MAX_NUMBER_OF_TRANSFERS; x++) //�������� ��� ������� "transfers.bin"
    {
        fread(&transfers[x], sizeof(struct Transfer), 1, tf); //���������� ��� ��������� ��� ��������� ���� ������ �� �������� ��� ������ "transfers"

        if (id == transfers[x].id_sender) //�� � ������� ����������� ��������� ��� ��������� ��� ����� ���������� ������� �� ��� ���������
        {
            transfers_send_history[tn] = transfers[x]; //���������� ��� ������������� ��������� ���� ������ "transfers_send_history"
            tn++;
        }
    }
    fclose(tf);
}


/*��������� random_id: ���������� ���� ������ ������ �����������
��� ���� ��� ������, ������������ ��� ��� �� seed ��� ��������� srand().
� ��������� ������� ��� ��������� ������ ���� ������ ����������� ��� ��� ���������� ����.*/
void random_id(unsigned long long int *id)
{
    time_t curtime;

    srand((unsigned)time(&curtime));

    for (int p = 0; p < ID_DIGITS; p++)
    {
        *id += (rand() % 10) * pow(10, p);
    }

    while (*id < pow(10, ID_DIGITS - 1))
    {
        *id += (rand() % 10) * pow(10, ID_DIGITS - 1);
    }
}

/*��������� random_iban: ���������� ��� ������ iban
��� ���� ��� ������, ������������ ��� ��� �� seed ��� ��������� srand().
� ��������� ������� ��� ��������� ������ ��� iban ��� ��� ���������� ����.*/
void random_iban(unsigned long long int *iban)
{
    time_t curtime;

    srand((unsigned)time(&curtime));

    for (int p = 0; p < IBAN_DIGITS; p++)
    {
       *iban += ((rand() % 10) + p % 10) % 10 * pow(10, p);
    }

    while (*iban < pow(10, IBAN_DIGITS - 1))
    {
        *iban += (rand() % 10) * pow(10, IBAN_DIGITS - 1);
    }
}

/*��������� create_new_user: �������� �� ������ "data.bin" ��� ���� ��������� ��� ���� ��������
��� ��������� users ��� ����� ����� User. ��� ��������, ���������� �� ���� �� �������� ���� ����������
������, ������� �� ��� ����������� �����������, ��� ���������� �� �������� ��� ��� ������ "data.bin".
� ��������� ������� ��� ����������� �� �����, �� �������, �� ����� ������, ��� ���������
������ ������������ ��� �� ��� ��� ������, ��� ���������� ��� ������ ����������� ��� ������.*/
unsigned long long int create_new_user(char *name, char *surname, char *username, short int pin, unsigned int tin)
{
    FILE *uf; //Users File
    static int i;

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //�������� ��� ������� "data.bin"
    {
        fread(&users[i], sizeof(struct User), 1, uf); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"

        if (users[i].id == 0) //�� � ������� ����������� ��� ������ ��� ����� ���������� ����� �����, ������ �� ���������� ��� � ���������� �������
            break;
    }

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    //���������� ���� ��� ���������� ��� �������� ��� ������ "users" ��� ����� ����������� ���� ��� ������
    random_id(&users[i].id);
    users[i].pin = pin;
    strcpy(users[i].name, name);
    strcpy(users[i].surname, surname);
    strcpy(users[i].username, username);
    random_iban(&users[i].iban);
    users[i].tin = tin;
    users[i].balance = 0;

    for (int k = 0; k < i + 1; k++)
    {
        fwrite(&users[k], sizeof(struct User), 1, uf); //������� ��� ������ "data.bin" ���� ��� �������, ������������������� ��� ����������� ������
    }

    fclose(uf);
    return users[i].id;
}

/*��������� new_deposit: �������� �� ������ "deposits.bin" ��� ����
��������� ��� ������ � ������ ���� ������ ����������� ��� ���������� ���������. ��� ��������,
��������� �������� �������� ���� ���������� ���� ��� ��������� ��� ��������� ��� �� ���������.
�� �������� ��� ��������� ������������� ��� ������ "deposits.bin". � ��������� ������� ��� �����������
��� ������ �����������, ��� �������� ��� �������� ��� ��� ���������, ��� ��� ���������� ����.*/
void new_deposit(unsigned long long int id, float amount, char *description)
{
    FILE *df; //Deposits File
    static int i;
    static int a;
    time_t current_time;


    if ((df = fopen("deposits.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (i = 0; i < MAX_NUMBER_OF_DEPOSITS; i++) //�������� ��� ������� "deposits.bin"
    {
        fread(&deposits[i], sizeof(struct Deposit), 1, df); //���������� ��� ��������� ���� ��������� �� �������� ��� ������ "deposits"

        if (deposits[i].id == 0) //�� � ������� ����������� ��� ��������� ��� ����� ���������� ����� �����, ������ �� ���������� ��� � ��������� ��������
            break;
    }

    //���������� ���� ��� ���������� ��� �������� ��� ������ "deposits" ��� ����� ����������� ���� ��� ��������
    deposits[i].id = id;
    time(&current_time);
    strcpy(deposits[i].date,ctime(&current_time));
    deposits[i].amount = amount;
    strcpy(deposits[i].description, description);
    fwrite(&deposits[i], sizeof(struct Deposit), 1, df);

    fclose(df);

    FILE *uf; //Users File

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //�������� ��� ������� "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"
        if(users[a].id == id) //�� � ������� ����������� ��� ������ ��� ����� ���������� ������� �� ��� ���������� ���������, ������ ���������� � ������� � ������ ����� ��� ��������
            break;
    }

    users[a].balance += amount; //������ ��� ��������� ��� ������

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) ==NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //������� ��� ������ "data.bin" ���� ��� �������, ������������������� ��� ������ �� ��� ���������� ��������

    fclose(uf);
}

/*��������� new_withdrawal: �������� �� ������ "withdrawals.bin" ��� ����
��������� ��� ������ � ������ ���� ������ ����������� ��� ���������� ���������. ��� ��������,
��������� �������� �������� ��� ��� ���������� ���� ��� ��������� ��� ��������� ��� �� ���������.
�� �������� ��� �������� ������������� ��� ������ "withdrawals.bin". � ��������� ������� ��� �����������
��� ������ �����������, ��� �������� ��� �������� ��� ��� ���������, ��� ��� ���������� ����.*/
void new_withdrawal(unsigned long long int id, float amount, char *description)
{
    FILE *wf; //Withdrawals File
    time_t current_time;
    static int i;
    static int a;

    if ((wf = fopen("withdrawals.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (i = 0; i < MAX_NUMBER_OF_DEPOSITS; i++) //�������� ��� ������� "withdrawals.bin"
    {
        fread(&withdrawals[i], sizeof(struct Withdrawal), 1, wf); //���������� ��� ��������� ���� �������� �� �������� ��� ������ "withdrawals"

        if(withdrawals[i].id == 0) //�� � ������� ����������� ��� �������� ��� ����� ���������� ����� �����, ������ �� ���������� ��� � ��������� �������
            break;
    }

    //���������� ���� ��� ���������� ��� �������� ��� ������ "withdrawals" ��� ����� ����������� ���� ��� �������
    withdrawals[i].id = id;
    time(&current_time);
    strcpy(withdrawals[i].date, ctime(&current_time));
    withdrawals[i].amount = amount;
    strcpy(withdrawals[i].description, description);
    fwrite(&withdrawals[i], sizeof(struct Withdrawal), 1, wf);

    fclose(wf);

    FILE *uf; //Users File

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //�������� ��� ������� "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"
        if(users[a].id == id) //�� � ������� ����������� ��� ������ ��� ����� ���������� ������� �� ��� ���������� ���������, ������ ���������� � ������� � ������ ����� ��� �������
            break;
    }

    users[a].balance -= amount; //������ ��� ��������� ��� ������

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //������� ��� ������ "data.bin" ���� ��� �������, ������������������� ��� ������ �� ��� ���������� �������

    fclose(uf);
}

/*��������� new_transfer: �������� �� ������ "transfers.bin" ��� ����
��������� ��� ������ � ������ ���� ������ ����������� ��� ���������� ��������� ��� ���������. ��� ��������,
��������� �������� �������� ��� ��� ���������� ��� ��������� ���� ���������� ��� ���������
��� ��������� ��� ��������� ��� �� ���������. �� �������� ��� �������� ������������� ��� ������ "transfers.bin".
� ��������� ������� ��� ����������� ��� ������ ����������� ��� ���������, ��� ������ ����������� ��� ���������,
��� �������� ��� �������� ��� ��� ���������, ��� ��� ���������� ����.*/
void new_transfer(unsigned long long int id_sender, unsigned long long int id_receiver, float amount, char *description)
{
    FILE *tf; //Transfers File
    static int i;
    static int a;
    time_t current_time;

    if ((tf = fopen("transfers.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (i = 0; i < MAX_NUMBER_OF_TRANSFERS; i++) //�������� ��� ������� "transfers.bin"
    {
        fread(&transfers[i], sizeof(struct Transfer), 1, tf); //���������� ��� ��������� ���� ��������� �� �������� ��� ������ "transfers"

        if (transfers[i].id_sender == 0) //�� � ������� ����������� ��� ��������� ��� ����� ���������� ����� �����, ������ �� ���������� ��� � ��������� ��������
            break;
    }

    //���������� ���� ��� ���������� ��� �������� ��� ������ "transfers" ��� ����� ����������� ���� ��� ��������
    transfers[i].id_sender = id_sender;
    transfers[i].id_receiver = id_receiver;
    time(&current_time);
    strcpy(transfers[i].date, ctime(&current_time));
    transfers[i].amount = amount;
    strcpy(transfers[i].description, description);
    fwrite(&transfers[i], sizeof(struct Transfer), 1, tf);

    fclose(tf);

    FILE *uf; //Users File

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //�������� ��� ������� "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"
        if (users[a].id == id_sender) //�� � ������� ����������� ��� ������ ��� ����� ���������� ������� �� ��� ���������� ��������� ��� ���������, ������ ���������� � ������� � ������ ������� ��� ��������
            break;
    }

    users[a].balance -= amount; //������ ��� ��������� ��� ���������

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //������� ��� ������ "data.bin" ���� ��� �������, ������������������� ��� ��������� �� ��� ���������� ��������

    fclose(uf);


    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //�������� ��� ������� "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //���������� ��� ��������� ���� ������ �� �������� ��� ������ "users"
        if (users[a].id == id_receiver) //�� � ������� ����������� ��� ������ ��� ����� ���������� ������� �� ��� ���������� ��������� ��� ���������, ������ ���������� � ������� � ������ ����� ��� ��������
            break;
    }

    users[a].balance += amount; //������ ��� ��������� ��� ���������

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //������� ��� ������ "data.bin" ���� ��� �������, ������������������� ��� ��������� �� ��� ���������� ��������

    fclose(uf);
}
