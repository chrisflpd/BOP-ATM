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


/*Συνάρτηση check_files: ελέγχει αν υπάρχουν καθένα από τα αρχεία data, deposits,
withdrawals και transfers. Αν δεν υπάρχουν, τα δημιουργεί. Αν αποτύχει, τυπώνει το αντίστοιχο μήνυμα
σφάλματος και τερματίζει το πρόγραμμα. Η συνάρτηση δεν δέχεται παραμέτρους και δεν επιστρέφει τιμή.*/
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

/*Συνάρτηση get_user_from_username: διαβάζει το αρχείο "data.bin" εώς ότου
εντοπίσει τον χρήστη ο οποίος έχει όνομα χρήστη την παράμετρο. Η συνάρτηση
δέχεται σαν παράμετρο δείκτη στο όνομα χρήστη και επιστρέφει την δομή
τύπου User, users, η οποία περιέχει τα στοιχεία του χρήστη.*/
struct User get_user_from_username(char *username)
{
    FILE *uf; //Users File

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    static int i;

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[i], sizeof(struct User), 1, uf); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"

        if (strcmp(username, users[i].username) == 0) //αν το όνομα χρήστη του χρήστη που μόλις διαβάστηκε ταυτίζεται με αυτό της παραμέτρου
            break;
    }

    fclose(uf);
    return users[i];
}

/*Συνάρτηση get_user_from_id: διαβάζει το αρχείο "data.bin" εώς ότου
εντοπίσει τον χρήστη ο οποίος έχει αριθμό λογαριασμού την παράμετρο. Η συνάρτηση
δέχεται σαν παράμετρο τον αριθμό λογαριασμού και επιστρέφει την δομή
τύπου User, users, η οποία περιέχει τα στοιχεία του χρήστη.*/
struct User get_user_from_id(unsigned long long int id)
{
    FILE *up;

    if ((up = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    static int i;

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[i],sizeof(struct User), 1, up); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"

        if (id == users[i].id) //αν ο αριθμός λογαριασμού του χρήστη που μόλις διαβάστηκε ταυτίζεται με αυτόν της παραμέτρου
            break;
    }

    fclose(up);
    return users[i];
}

/*Συνάρτηση get_user_from_iban: διαβάζει το αρχείο "data.bin" εώς ότου
εντοπίσει τον χρήστη ο οποίος έχει IBAN την παράμετρο. Η συνάρτηση
δέχεται σαν παράμετρο το IBAN και επιστρέφει την δομή
τύπου User, users, η οποία περιέχει τα στοιχεία του χρήστη.*/
struct User get_user_from_iban(unsigned long long int iban)
{
    FILE *up;

    if ((up = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    static int i;

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[i], sizeof(struct User), 1, up); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"

        if (iban == users[i].iban) //αν το iban του χρήστη που μόλις διαβάστηκε ταυτίζεται με αυτό της παραμέτρου
            break;
    }

    fclose(up);
    return users[i];
}

/*Συνάρτηση load_deposits_history: διαβάζει το αρχείο "deposits.bin" εώς ότου
εντοπίσει κατάθεση από τον χρήστη με αριθμό λογαριασμού αυτόν της παραμέτρου.
Τότε, αποθηκεύει τα στοιχεία της συγκεκριμένης κατάθεσης στον πίνακα "deposits_history"
και επαναλαμβάνει τη διαδικασία μέχρι όλες οι καταθέσεις του εκάστοτε χρήστη να έχουν
αποθηκευτεί στον πίνακα "deposits_history". Η συνάρτηση δέχεται σαν παράμετρο τον προσωπικό
αριθμό λογαριασμού του χρήστη και δεν επιστρέφει τιμή.*/
void load_deposits_history(unsigned long long int id)
{
    FILE *df; //Deposits File

    if ((df = fopen("deposits.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int dn = 0; //Number of found deposits

    for (int x = 0; x < MAX_NUMBER_OF_DEPOSITS; x++) //διάβασμα του αρχείου "deposits.bin"
    {
        fread(&deposits[x], sizeof(struct Deposit), 1, df); //αποθήκευση των στοιχείων των καταθέσεων κάθε χρήστη σε στοιχείο του πίνακα "deposits"

        if (id == deposits[x].id) //αν ο αριθμός λογαριασμού της κατάθεσης που μόλις διαβάστηκε ισούται με την παράμετρο
        {
            deposits_history[dn] = deposits[x]; //αποθήκευση της συγκεκριμένης κατάθεσης στον πίνακα "deposits_history"
            dn++;
        }
    }
    fclose(df);
}

/*Συνάρτηση load_withdrawals_history: διαβάζει το αρχείο "withdrawals.bin" εώς ότου
εντοπίσει κατάθεση από τον χρήστη με αριθμό λογαριασμού αυτόν της παραμέτρου.
Τότε, αποθηκεύει τα στοιχεία της συγκεκριμένης ανάληψης στον πίνακα "withdrawals_history"
και επαναλαμβάνει τη διαδικασία μέχρι όλες οι αναλήψεις του εκάστοτε χρήστη να έχουν
αποθηκευτεί στον πίνακα "withdrawals_history". Η συνάρτηση δέχεται σαν παράμετρο τον προσωπικό
αριθμό λογαριασμού του χρήστη και δεν επιστρέφει τιμή.*/
void load_withdrawals_history(unsigned long long int id)
{
    FILE *wf; //Withdrawals File

    if ((wf = fopen("withdrawals.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int wn = 0; //Number of found withdrawals

    for (int x = 0; x < MAX_NUMBER_OF_WITHDRAWALS; x++) //διάβασμα του αρχείου "withdrawals.bin"
    {
        fread(&withdrawals[x], sizeof(struct Withdrawal), 1, wf); //αποθήκευση των στοιχείων των αναλήψεων κάθε χρήστη σε στοιχείο του πίνακα "withdrawals"

        if (id == withdrawals[x].id) //αν ο αριθμός λογαριασμού της ανάληψης που μόλις διαβάστηκε ισούται με την παράμετρο
        {
            withdrawals_history[wn] = withdrawals[x]; //αποθήκευση της συγκεκριμένης ανάληψης στον πίνακα "withdrawals_history"
            wn++;
        }
    }
    fclose(wf);
}

/*Συνάρτηση load_transfers_rec_history: διαβάζει το αρχείο "transfers.bin" εώς ότου
εντοπίσει μεταφορά προς τον χρήστη με αριθμό λογαριασμού αυτόν της παραμέτρου.
Τότε, αποθηκεύει τα στοιχεία της συγκεκριμένης μεταφοράς στον πίνακα "transfers_rec_history"
και επαναλαμβάνει τη διαδικασία μέχρι όλες οι μεταφορές από τον εκάστοτε χρήστη να έχουν
αποθηκευτεί στον πίνακα "transfers_rec_history". Η συνάρτηση δέχεται σαν παράμετρο τον προσωπικό
αριθμό λογαριασμού του χρήστη και δεν επιστρέφει τιμή.*/
void load_transfers_rec_history(unsigned long long int id)
{
    FILE *tf; //Transfers File

    if ((tf = fopen("transfers.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int tn = 0; //Number of found transfers

    for (int x = 0; x < MAX_NUMBER_OF_TRANSFERS; x++) //διάβασμα του αρχείου "transfers.bin"
    {
        fread(&transfers[x], sizeof(struct Transfer), 1, tf); //αποθήκευση των στοιχείων των μεταφορών κάθε χρήστη σε στοιχείο του πίνακα "transfers"

        if (id == transfers[x].id_receiver) //αν ο αριθμός λογαριασμού παραλήπτη της μεταφοράς που μόλις διαβάστηκε ισούται με την παράμετρο
        {
            transfers_rec_history[tn] = transfers[x]; //αποθήκευση της συγκεκριμένης μεταφοράς στον πίνακα "transfers_rec_history"
            tn++;
        }
    }
    fclose(tf);
}

/*Συνάρτηση load_transfers_send_history: διαβάζει το αρχείο "transfers.bin" εώς ότου
εντοπίσει μεταφορά από τον χρήστη με αριθμό λογαριασμού αυτόν της παραμέτρου.
Τότε, αποθηκεύει τα στοιχεία της συγκεκριμένης μεταφοράς στον πίνακα "transfers_send_history"
και επαναλαμβάνει τη διαδικασία μέχρι όλες οι μεταφορές προς τον εκάστοτε χρήστη να έχουν
αποθηκευτεί στον πίνακα "transfers_send_history". Η συνάρτηση δέχεται σαν παράμετρο τον προσωπικό
αριθμό λογαριασμού του χρήστη και δεν επιστρέφει τιμή.*/
void load_transfers_send_history(unsigned long long int id)
{
    FILE *tf; //Transfers File

    if ((tf = fopen("transfers.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    int tn = 0; //Number of found transfers

    for (int x = 0; x < MAX_NUMBER_OF_TRANSFERS; x++) //διάβασμα του αρχείου "transfers.bin"
    {
        fread(&transfers[x], sizeof(struct Transfer), 1, tf); //αποθήκευση των στοιχείων των μεταφορών κάθε χρήστη σε στοιχείο του πίνακα "transfers"

        if (id == transfers[x].id_sender) //αν ο αριθμός λογαριασμού αποστολέα της μεταφοράς που μόλις διαβάστηκε ισούται με την παράμετρο
        {
            transfers_send_history[tn] = transfers[x]; //αποθήκευση της συγκεκριμένης μεταφοράς στον πίνακα "transfers_send_history"
            tn++;
        }
    }
    fclose(tf);
}


/*Συνάρτηση random_id: δημιουργεί έναν τυχαίο αριθμό λογαριασμού
για κάθε νέο χρήστη, αξιοποιώντας την ώρα ως seed στη συνάρτηση srand().
Η συνάρτηση δέχεται σαν παράμετρο δείκτη στον αριθμό λογαριασμού και δεν επιστρέφει τιμη.*/
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

/*Συνάρτηση random_iban: δημιουργεί ένα τυχαίο iban
για κάθε νέο χρήστη, αξιοποιώντας την ώρα ως seed στη συνάρτηση srand().
Η συνάρτηση δέχεται σαν παράμετρο δείκτη στο iban και δεν επιστρέφει τιμη.*/
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

/*Συνάρτηση create_new_user: διαβάζει το αρχείο "data.bin" εώς ότου εντοπίσει ένα κενό στοιχείο
στη συστοιχία users των δομών τύπου User. Στη συνέχεια, δημιουργεί σε αυτό το στοιχείο έναν καινούργιο
χρήστη, σύμφωνα με τις αντίστοιχες παραμέτρους, και αποθηκεύει τα στοιχεία του στο αρχείο "data.bin".
Η συνάρτηση δέχεται σαν παραμέτρους το όνομα, το επώνυμο, το όνομα χρήστη, τον προσωπικό
αριθμό ταυτοποιήσης και το ΑΦΜ του χρήστη, ενώ επιστρέφει τον αριθμό λογαριασμού του χρήστη.*/
unsigned long long int create_new_user(char *name, char *surname, char *username, short int pin, unsigned int tin)
{
    FILE *uf; //Users File
    static int i;

    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (i = 0; i < MAX_NUMBER_OF_USERS; i++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[i], sizeof(struct User), 1, uf); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"

        if (users[i].id == 0) //αν ο αριθμός λογαριασμού του χρήστη που μόλις διαβάστηκε είναι μηδέν, δηλαδή αν διαβάστηκε και ο τελευταίος χρήστης
            break;
    }

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    //αποθήκευση όλων των παραμέτρων στο στοιχείο του πίνακα "users" που πλέον αντιστοιχεί στον νέο χρήστη
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
        fwrite(&users[k], sizeof(struct User), 1, uf); //γράψιμο στο αρχείο "data.bin" όλων των χρηστών, συμπεριλαμβανομένου του καινούργιου χρήστη
    }

    fclose(uf);
    return users[i].id;
}

/*Συνάρτηση new_deposit: διαβάζει το αρχείο "deposits.bin" εώς ότου
εντοπίσει τον χρήστη ο οποίος έχει αριθμό λογαριασμού την αντίστοιχη παράμετρο. Στη συνέχεια,
καταθέτει ποσότητα χρημάτων στον λογαριασμό αυτό και προσθέτει μία περιγραφή για τη συναλλαγή.
Τα στοιχεία της κατάθεσης αποθηκεύονται στο αρχείο "deposits.bin". Η συνάρτηση δέχεται σαν παραμέτρους
τον αριθμό λογαριασμού, την ποσότητα των χρημάτων και την περιγραφή, ενώ δεν επιστρέφει τιμή.*/
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

    for (i = 0; i < MAX_NUMBER_OF_DEPOSITS; i++) //διάβασμα του αρχείου "deposits.bin"
    {
        fread(&deposits[i], sizeof(struct Deposit), 1, df); //αποθήκευση των στοιχείων κάθε κατάθεσης σε στοιχείο του πίνακα "deposits"

        if (deposits[i].id == 0) //αν ο αριθμός λογαριασμού της κατάθεσης που μόλις διαβάστηκε είναι μηδέν, δηλαδή αν διαβάστηκε και η τελευταία κατάθεση
            break;
    }

    //αποθήκευση όλων των παραμέτρων στο στοιχείο του πίνακα "deposits" που πλέον αντιστοιχεί στην νέα κατάθεση
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

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"
        if(users[a].id == id) //αν ο αριθμός λογαριασμού του χρήστη που μόλις διαβάστηκε ισούται με την αντίστοιχη παράμετρο, δηλαδή διαβάστηκε ο χρήστης ο οποίος έκανε την κατάθεση
            break;
    }

    users[a].balance += amount; //αύξηση του υπολοίπου του χρήστη

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) ==NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //γράψιμο στο αρχείο "data.bin" όλων των χρηστών, συμπεριλαμβανομένου του χρήστη με την καινούργια κατάθεση

    fclose(uf);
}

/*Συνάρτηση new_withdrawal: διαβάζει το αρχείο "withdrawals.bin" εώς ότου
εντοπίσει τον χρήστη ο οποίος έχει αριθμό λογαριασμού την αντίστοιχη παράμετρο. Στη συνέχεια,
αναλήπτει ποσότητα χρημάτων από τον λογαριασμό αυτό και προσθέτει μία περιγραφή για τη συναλλαγή.
Τα στοιχεία της ανάληψης αποθηκεύονται στο αρχείο "withdrawals.bin". Η συνάρτηση δέχεται σαν παραμέτρους
τον αριθμό λογαριασμού, την ποσότητα των χρημάτων και την περιγραφή, ενώ δεν επιστρέφει τιμή.*/
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

    for (i = 0; i < MAX_NUMBER_OF_DEPOSITS; i++) //διάβασμα του αρχείου "withdrawals.bin"
    {
        fread(&withdrawals[i], sizeof(struct Withdrawal), 1, wf); //αποθήκευση των στοιχείων κάθε ανάληψης σε στοιχείο του πίνακα "withdrawals"

        if(withdrawals[i].id == 0) //αν ο αριθμός λογαριασμού της ανάληψης που μόλις διαβάστηκε είναι μηδέν, δηλαδή αν διαβάστηκε και η τελευταία ανάληψη
            break;
    }

    //αποθήκευση όλων των παραμέτρων στο στοιχείο του πίνακα "withdrawals" που πλέον αντιστοιχεί στην νέα ανάληψη
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

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"
        if(users[a].id == id) //αν ο αριθμός λογαριασμού του χρήστη που μόλις διαβάστηκε ισούται με την αντίστοιχη παράμετρο, δηλαδή διαβάστηκε ο χρήστης ο οποίος έκανε την ανάληψη
            break;
    }

    users[a].balance -= amount; //μείωση του υπολοίπου του χρήστη

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //γράψιμο στο αρχείο "data.bin" όλων των χρηστών, συμπεριλαμβανομένου του χρήστη με την καινούργια ανάληψη

    fclose(uf);
}

/*Συνάρτηση new_transfer: διαβάζει το αρχείο "transfers.bin" εώς ότου
εντοπίσει τον χρήστη ο οποίος έχει αριθμό λογαριασμού την αντίστοιχη παράμετρο του αποστολέα. Στη συνέχεια,
μεταφέρει ποσότητα χρημάτων από τον λογαριασμό του αποστολέα στον λογαριασμό του παραλήπτη
και προσθέτει μία περιγραφή για τη συναλλαγή. Τα στοιχεία της ανάληψης αποθηκεύονται στο αρχείο "transfers.bin".
Η συνάρτηση δέχεται σαν παραμέτρους τον αριθμό λογαριασμού του αποστολέα, τον αριθμό λογαριασμού του παραλήπτη,
την ποσότητα των χρημάτων και την περιγραφή, ενώ δεν επιστρέφει τιμή.*/
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

    for (i = 0; i < MAX_NUMBER_OF_TRANSFERS; i++) //διάβασμα του αρχείου "transfers.bin"
    {
        fread(&transfers[i], sizeof(struct Transfer), 1, tf); //αποθήκευση των στοιχείων κάθε μεταφοράς σε στοιχείο του πίνακα "transfers"

        if (transfers[i].id_sender == 0) //αν ο αριθμός λογαριασμού της μεταφοράς που μόλις διαβάστηκε είναι μηδέν, δηλαδή αν διαβάστηκε και η τελευταία μεταφορά
            break;
    }

    //αποθήκευση όλων των παραμέτρων στο στοιχείο του πίνακα "transfers" που πλέον αντιστοιχεί στην νέα μεταφορά
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

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"
        if (users[a].id == id_sender) //αν ο αριθμός λογαριασμού του χρήστη που μόλις διαβάστηκε ισούται με την αντίστοιχη παράμετρο του αποστολέα, δηλαδή διαβάστηκε ο χρήστης ο οποίος έστειλε την μεταφορά
            break;
    }

    users[a].balance -= amount; //μείωση του υπολοίπου του αποστολέα

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //γράψιμο στο αρχείο "data.bin" όλων των χρηστών, συμπεριλαμβανομένου του αποστολέα με την καινούργια μεταφορά

    fclose(uf);


    if ((uf = fopen("data.bin", "rb")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (a = 0; a < MAX_NUMBER_OF_USERS; a++) //διάβασμα του αρχείου "data.bin"
    {
        fread(&users[a],sizeof(struct User), 1, uf); //αποθήκευση των στοιχείων κάθε χρήστη σε στοιχείο του πίνακα "users"
        if (users[a].id == id_receiver) //αν ο αριθμός λογαριασμού του χρήστη που μόλις διαβάστηκε ισούται με την αντίστοιχη παράμετρο του παραλήπτη, δηλαδή διαβάστηκε ο χρήστης ο οποίος έλαβε την μεταφορά
            break;
    }

    users[a].balance += amount; //αύξηση του υπολοίπου του παραλήπτη

    fclose(uf);

    if ((uf = fopen("data.bin", "rb+")) == NULL)
    {
        perror("Error");
        exit(errno);
    }

    for (int k = 0; k < a + 1; k++)
        fwrite(&users[k], sizeof(struct User), 1, uf); //γράψιμο στο αρχείο "data.bin" όλων των χρηστών, συμπεριλαμβανομένου του παραλήπτη με την καινούργια μεταφορά

    fclose(uf);
}
