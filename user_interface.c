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


short int active = 1; //global μεταβλητή, η οποία ισούται με 1, εκτός και αν ο χρήστης εισάγει τον συνδυασμο τερματισμού "%%%", οπότε γίνεται 0


/*Συνάρτηση welcome: υποδέχεται τον χρήστη και τον παροτρύνει να
εισάγει τον συνδυασμό '%%%' οποιαδήποτε στιγμή θέλει να τερματίσει το πρόγραμμα.
Η συνάρτηση δεν δέχεται παραμέτρους και δεν επιστρέφει τιμή.*/
void welcome(void)
{
    system("cls");
    SetColor(PURPLE);
    printf("\t\t\t\t\tWELCOME MENU\n\n");
    SetColor(WHITE);

    puts("Welcome to the official ATM of BOP (Bank Of Programmers)."
         "\nIf at any moment you want to terminate the session, enter %%%.\n\n");
}

/*Συνάρτηση register_or_login: παροτρύνει τον χρήστη να επιλεξει αν θελει να
δημιουργήσει καινουργιο λογαριασμο ή να συνδεθει σε ήδη υπάρχον και μετά τον απαραίτητο έλεγχο, αποθηκέυει την επιλογή του.
Η συνάρτηση δέχεται σαν παράμετρο έναν δείκτη στην επιλογή του χρήστη και δεν επιστρέφει τιμή.*/
void register_or_login(char *choice_r_l)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("Would you like to register or login? [r: register, l: login]");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //έλεγχος για εισαγωγή παραπάνω απο έναν χαρακτήρα
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_r_l = tolower(input[0]); //μετατροπή της εισαγωγής σε πεζά και αποθήκευσή της

        switch (*choice_r_l) //έλεγχος για εισαγωγή χαρακτήρα διάφορου του 'r' και 'l'
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

/*Συνάρτηση yes_or_no: παροτρύνει τον χρήστη να επιλεξει αν θελει να
κάνει νέα συναλλαγή ή να αποχωρήσει και μετά τον απαραίτητο έλεγχο, αποθηκέυει την επιλογή του.
Η συνάρτηση δέχεται σαν παράμετρο έναν δείκτη στην επιλογή του χρήστη και δεν επιστρέφει τιμή.*/
void yes_or_no(char *choice_y_n)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("\n\nWould you like to make another transaction? [y: yes, n: no]");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //έλεγχος για εισαγωγή παραπάνω απο έναν χαρακτήρα
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_y_n = tolower(input[0]); //μετατροπή της εισαγωγής σε πεζά και αποθήκευσή της

        switch (*choice_y_n) //έλεγχος για εισαγωγή χαρακτήρα διάφορου του 'r' και 'l'
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

/*Συνάρτηση select_history: παροτρύνει τον χρήστη να επιλεξει αν θέλει
να δει το ιστορικό των καταθέσεων, των αναλήψεων ή των μεταφορών και μετά τον απαραίτητο έλεγχο, αποθηκέυει την επιλογή του.
Η συνάρτηση δέχεται σαν παράμετρο έναν δείκτη στην επιλογή του χρήστη και δεν επιστρέφει τιμή.*/
void select_history(char *choice_d_w_t)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("Would you like to view your deposits, withdrawals or transfers history?");
        printf("[d: deposits history, w: withdrawals history, t: transfers history]\n");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //έλεγχος για εισαγωγή παραπάνω απο έναν χαρακτήρα
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_d_w_t = tolower(input[0]); //μετατροπή της εισαγωγής σε πεζά και αποθήκευσή της

        switch (*choice_d_w_t) //έλεγχος για εισαγωγή χαρακτήρα διάφορου του 'd', 'w' και του 't'
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

/*Συνάρτηση select_info: δέχεται εισαγωγή χαρακτήρα από τον χρήστη σχετικά με την άδεια χρήσης
και μετά τον απαραίτητο έλεγχο, αποθηκέυει την επιλογή του.
Η συνάρτηση δέχεται σαν παράμετρο έναν δείκτη στην επιλογή του χρήστη και δεν επιστρέφει τιμή.*/
void select_info(char *choice_info)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //έλεγχος για εισαγωγή παραπάνω απο έναν χαρακτήρα
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n\n");
            SetColor(WHITE);
            continue;
        }

        *choice_info = tolower(input[0]); //μετατροπή της εισαγωγής σε πεζά και αποθήκευσή της

        switch (*choice_info) //έλεγχος για εισαγωγή χαρακτήρα διάφορου του 'w' και του 'i'
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


/*Συνάρτηση get_creds_login: παροτρύνει τον χρήστη να εισάγει τα στοιχεία του, ώστε να συνδεθεί
στον λογαριασμό του και μετά τον απαραίτητο έλεγχο, τα αποθηκεύει.
Η συνάρτηση δέχεται σαν παραμέτρους δεικτη στο όνομα χρήστη, δείκτη στον αριθμό λογαριασμού
και δείκτη στον προσωπικό αριθμό ταυτοποίησης του χρήστη, ενώ δεν επιστρέφει τιμή.*/
void get_creds_login(char username[], unsigned long long int *id, short int *pin)
{
    char cleaner, input[MAX_USERNAME_SIZE + 1]; //== input[ID_DIGITS + 2];
    short int only_digits, only_word;;;

    //λήψη ονόματος χρήστη ή αριθμού λογαριασμού:
    while (1)
    {
        puts("\n\nEnter your username or your ID:");
        scanf("%18[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_number(input, &only_digits); //έλεγχος για εισαγωγή μόνο ψηφίων, το οποίο συνεπάγεται εισαγωγή αριθμού λογαριασμού

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) < ID_DIGITS) //έλεγχος μήκους αριθμού λογαριασμού
        {
            error_sound();
            SetColor(RED);
            printf("\nYour id cannot be less than %d digits short. Please try again.\n\n", ID_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) > ID_DIGITS) //έλεγχος μήκους αριθμού λογαριασμού
        {
            error_sound();
            SetColor(RED);
            printf("\nYour id cannot be more than %d digits long. Please try again.\n\n", ID_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) > MAX_USERNAME_SIZE - 1) //έλεγχος μήκους ονόματος χρήστη
        {
            error_sound();
            SetColor(RED);
            printf("\nYour username cannot be more than %d characters long. Please try again.\n\n", MAX_USERNAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) < MIN_USERNAME_SIZE) //έλεγχος μήκους ονόματος χρήστη
        {
            error_sound();
            SetColor(RED);
            printf("\nYour username cannot be less than %d characters short. Please try again.\n\n", MIN_USERNAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (only_digits) //αν η εισαγωγή ήταν ο αριθμός λογαριασμού
        {
            *id = strtoull(input, NULL, 10);
            break; //τερματισμός βρόχου while
        }
        else //αν η εισαγωγή ήταν το όνομα χρήστη
        {
            strncpy(username, input, MAX_USERNAME_SIZE); //αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }

    //λήψη προσωπικού αριθμού ταυτοποιήσης:
    while (active)
    {
        puts("\n\nEnter your pin:");
        scanf("%6[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_number(input, &only_digits); //έλεγχος για εισαγωγή μόνο ψηφίων, το οποίο συνεπάγεται εισαγωγή αριθμού λογαριασμού

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //έλεγχος για εισαγωγή γράμματος
        {
            error_sound();
            SetColor(RED);
            puts("\nYour pin cannot contain any letters. Please try again.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > PIN_DIGITS) //έλεγχος μήκους προσωπικού αριθμού ταυτοποιήσης
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be more than %d digits long. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) < PIN_DIGITS) //έλεγχος μήκους προσωπικού αριθμού ταυτοποιήσης
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be less than %d digits short. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == PIN_DIGITS) //αν η εισαγωγή ήταν πράγματι ο προσωπικός αριθμός ταυτοποίησης
        {
            *pin = (short int)atoi(input); //μετατροπή και αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }
}

/*Συνάρτηση get_creds_register: παροτρύνει τον χρήστη να εισάγει τα στοιχεία του, ώστε να δημιουργήσει
εναν καινούργιο λογαριασμό και μετά τον απαραίτητο έλεγχο, τα αποθηκεύει.
Η συνάρτηση δεχεται σαν παραμέτρους δεικτη στο όνομα, δεικτη στο επίθετο,
δεικτη στο όνομα χρήστη, δείκτη στον προσωπικό αριθμό ταυτοποίησης και δείκτη
στο ΑΦΜ του χρήστη, ενώ δεν επιστρέφει τιμή.*/
void get_creds_register(char name[], char surname[], char username[], short int *pin, unsigned int *tin)
{
    char cleaner, input[MAX_SURNAME_SIZE + 1];
    short int contains_digits, only_digits, only_word;

    //λήψη ονόματος:
    while (1)
    {
        puts("\n\nEnter your name:");
        scanf("%18[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_contains_digits(input, &contains_digits); //έλεγχος εισαγωγης για ύπαρξη ψηφίου

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (contains_digits) //έλεγχος εισαγωγης για ύπαρξη ψηφίου
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your name cannot contain any digits. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) > MAX_NAME_SIZE - 1) //έλεγχος μήκους ονόματος
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your name cannot be more than %d characters long. Please try again.\n\n", MAX_NAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MIN_NAME_SIZE) //έλεγχος μήκους ονόματος
        {
            error_sound();
            SetColor(RED);
            printf("Invalid input. Your name cannot be less than %d characters short. Please try again.\n\n", MIN_NAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MAX_NAME_SIZE && strlen(input) > MIN_NAME_SIZE - 1) //αν η εισαγωγή ήταν επιτρεπτό όνομα
        {
            strncpy(name, input, MAX_NAME_SIZE); //αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }

    //λήψη επιθέτου:
    while (active)
    {
        puts("\n\nEnter your surname:");
        fgets(input, 26, stdin);

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0'; //αλλαγή του '\n' σε '\0'

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        if (strcmp("", input) == 0) //έλεγχος για εισαγωγή αποκλειστικά <ENTER>
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter your surname before pressing <ENTER>.\n");
            SetColor(WHITE);
            continue;
        }

        string_contains_digits(input, &contains_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (contains_digits) //έλεγχος εισαγωγης για ύπαρξη ψηφίου
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your surname cannot contain any digits. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) > MAX_SURNAME_SIZE - 1) //έλεγχος μήκους επιθέτου
        {
            while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your surname cannot be more than %d characters long. Please try again.\n\n", MAX_SURNAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MIN_SURNAME_SIZE) //έλεγχος μήκους επιθέτου
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your surname cannot be less than %d characters short. Please try again.\n\n", MIN_SURNAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (!contains_digits && strlen(input) < MAX_SURNAME_SIZE && strlen(input) > MIN_SURNAME_SIZE - 1) //αν η εισαγωγή ήταν επιτρεπτό επίθετο
        {
            strncpy(surname, input, MAX_SURNAME_SIZE); //αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }

    //λήψη ονόματος χρήστη:
    while (active)
    {
        puts("\n\nCreate a username. Your username should not be more than 16 characters long or less"
             " than 4 characters short and should not contain digits only:");
        fgets(input, 18, stdin);

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0'; //αλλαγή του '\n' σε '\0'

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        if (strcmp("", input) == 0) //έλεγχος για εισαγωγή αποκλειστικά <ENTER>
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter your username before pressing <ENTER>.\n");
            SetColor(WHITE);
            continue;
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits) //έλεγχος για εισαγωγή μόνο ψηφίων
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your username cannot contain only digits. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) > MAX_USERNAME_SIZE - 1) //έλεγχος μήκους ονόματος χρήστη
        {
            while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your username cannot be more than %d characters long. Please try again.\n\n", MAX_USERNAME_SIZE - 1);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) < MIN_USERNAME_SIZE) //έλεγχος μήκους ονόματος χρήστη
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your username cannot be less than %d characters short. Please try again.\n\n", MIN_USERNAME_SIZE);
            SetColor(WHITE);
            continue;
        }

        if (!only_digits && strlen(input) < MAX_USERNAME_SIZE && strlen(input) > MIN_USERNAME_SIZE - 1) //αν η εισαγωγή ήταν επιτρεπτό όνομα χρήστη
        {
            if (get_user_from_username(input).id == 0) //αν δεν υπάρχει χρήστης με αυτό το όνομα χρήστη
            {
                strncpy(username, input, MAX_USERNAME_SIZE); //αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
                break; //τερματισμός βρόχου while //τερματισμός βρόχου while
            }
            else //αν υπάρχει χρήστης με αυτό το όνομα χρήστη
            {
                error_sound();
                SetColor(RED);
                printf("\nInvalid input. The entered username already exists. Please choose a different one.\n\n");
                SetColor(WHITE);
            }

        }
    }

    //λήψη προσωπικού αριθμού ταυτοποίησης:
    while (active)
    {
        puts("\n\nCreate a pin. Your pin should be exactly 4 digits long. Do not share your pin:");
        scanf("%6[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //έλεγχος για εισαγωγή γραμμάτων
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your pin cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) > PIN_DIGITS) //έλεγχος μήκος προσωπικού αριθμού ταυτοποίησης
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be more than %d characters long. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) < PIN_DIGITS) //έλεγχος μήκος προσωπικού αριθμού ταυτοποίησης
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your pin cannot be less than %d characters short. Please try again.\n\n", PIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == PIN_DIGITS) //αν η εισαγωγή ήταν επιτρεπτός προσωπικός αριθμός ταυτοποποίησης
        {
            *pin = (short int)atoi(input); //μετατροπή και αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }

    //λήψη ΑΦΜ:
    while (active)
    {
        puts("\n\nEnter your Tax Identification Number:");
        scanf("%11[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //έλεγχος για εισαγωγή γραμμάτων
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Your Tax Identification Number cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) > TIN_DIGITS) //έλεγχος μήκους ΑΦΜ
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your Tax Identification Number cannot be more than %d characters long. Please try again.\n\n", TIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) < TIN_DIGITS) //έλεγχος μήκους ΑΦΜ
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. Your Tax Identification Number cannot be less than %d characters short. Please try again.\n\n", TIN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == TIN_DIGITS) //αν η εισαγωγή ήταν επιτρεπτό ΑΦΜ
        {
            *tin = (unsigned int)strtoul(input, NULL, 10); //μετατροπή και αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }
}

/*Συνάρτηση select_mode: παροτρύνει τον χρήστη να επιλέξει αν θέλει να κάνει κατάθεση,
ανάληψη ή μεταφορά χρημάτων ή αν θέλει να ελέγξει το χρηματικό
υπόλοιπο του λογαριασμού του και μετά τον απαραίτητο έλεγχο, αποθηκεύει την επιλογή του.
Η συνάρτηση δέχεται σαν παράμετρο δείκτη στην επιλογή του χρήστη
και δεν επιστρέφει τιμη.*/
void select_mode(char *choice_d_w_t_b_c_h)
{
    char cleaner, input[MAX_CHOICE_INPUT];
    short int only_word;

    do
    {
        puts("Would you like to deposit, withdraw or transfer money?"
             " Alternatively,\nyou can check your balance, your transaction history or your credentials.\n[d: deposit, w: withdraw, t: transfer, b: check balance, h: transaction history, c: check credentials]");
        scanf("%4[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > 1) //έλεγχος για εισαγωγή παραπάνω απο έναν χαρακτήρα
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter only one letter.\n");
            SetColor(WHITE);
            continue;
        }

        *choice_d_w_t_b_c_h = tolower(input[0]); //μετατροπή της εισαγωγής σε πεζά και αποθήκευσή της

        switch (*choice_d_w_t_b_c_h) //έλεγχος για εισαγωγή χαρακτήρα διάφορου του 'd', του 'w',του 't', του 'b', του 'c' και του 'h'
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

/*Συνάρτηση get_amount_description: παροτρύνει τον χρήστη να εισάγει την ποσότητα των χρημάτων
που αφορούν τη συναλλαγή και μετά τον απαραίτητο έλεγχο,
την αποθηκεύει. Επίσης, παροτρύνει τον χρήστη να εισάγει μία περιγραφή για την συναλλαγή
και μετά τον απαραίτητο έλεγχο, την αποθηκεύει. Η συνάρτηση δέχεται σαν παραμέτρους δείκτη στην
ποσότητα των χρημάτων και δείκτη στην περιγραφή της συναλλαγής, ενώ δεν επιστρέφει τιμή.*/
void get_amount_description(float *amount, char description[])
{
    char cleaner, input[MAX_AMOUNT_SIZE + 2], input_des[MAX_DESCRIPTION_SIZE + 1] = {'\0'};
    short int only_float, amount_error, only_word;

    //λήψη ποσότητας:
    while (1)
    {
        amount_error = 0;

        puts("\n\nEnter desirable amount:");
        fgets(input, 11, stdin);

        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0'; //αλλαγή του '\n' σε '\0'

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        if (strcmp("", input) == 0) //έλεγχος για εισαγωγή αποκλειστικά <ENTER>
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Please enter an amount before pressing <ENTER>.\n");
            SetColor(WHITE);
            continue;
        }

        string_is_float_number(input, &only_float);

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > MAX_AMOUNT_SIZE) //έλεγχος μήκους ποσότητας
        {
            while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες
            amount_error = 1;
        }

        if (!only_float) //έλεγχος εισαγωγής για ύπαρξη γραμμάτων
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Amount cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (only_float) //αν η εισαγωγή ήταν επιτρεπτή ποσότητα
        {
            *amount =  atof(input); //μετατροπή και αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης

            if (*amount > MAX_AMOUNT || amount_error == 1) //έλεγχος μεγέθους ποσότητας
            {
                error_sound();
                SetColor(RED);
                printf("\nInvalid input. Amount cannot be greater than %.2f Euros. Please try again.\n\n", MAX_AMOUNT);
                SetColor(WHITE);
                continue;
            }

            if (*amount == 0.0) //έλεγχος εισαγωγής μηδενικής ποσότητας
            {
                error_sound();
                SetColor(RED);
                puts("\nInvalid input. Amount cannot be zero Euros. Please try again.\n");
                SetColor(WHITE);
                continue;
            }

            break; //τερματισμός βρόχου while
        }
    }

    //λήψη περιγραφής:
    while (active)
    {
        puts("\n\nEnter a description for the transaction. The description should not be more than 256"
             " characters long.\nPress <ENTER> for no description:");
        scanf("%258[^\n]", input_des); //διάβασμα εώς ότου εισαχθεί ο χαρακτήρας '\n'

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        if (strlen(input_des) > MAX_DESCRIPTION_SIZE - 1) //έλεγχος μηκους περιγραφής
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. The description cannot be more than 256 characters long. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input_des) < MAX_DESCRIPTION_SIZE) //έλεγχος μηκους περιγραφής
        {
            strncpy(description, input_des, MAX_DESCRIPTION_SIZE); //αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }
}

/*Συνάρτηση get_user_to_transfer: παροτρύνει τον χρήστη να εισάγει το IBAN του
χρήστη στον οποίο θέλει να μεταφέρει χρήματα και μετά τον απαραίτητο έλεγχο,
το αποθηκεύει. Η συνάρτηση δέχεται σαν παράμετρο δείκτη στο IBAN του χρήστη στον οποίο
θα μεταφερθούν τα χρήματα και δεν επιστρέφει τιμή.*/
void get_user_to_transfer(unsigned long long int *iban)
{
    char cleaner, input[IBAN_DIGITS + 2];
    short int only_digits, only_word;

    //λήψη IBAN:
    while (1)
    {
        puts("\n\nEnter the IBAN of the user you want to transfer money to:");
        scanf("%18[^\n]", input);

        while ((cleaner = getchar()) != '\n' && cleaner != EOF); //καθαρισμός της ροής stdin από περίσσιους χαρακτήρες

        if (terminate_transaction(input)) //τερματισμός προγράμματος με την εισαγωγη '%%%'
        {
            break; //τερματισμός βρόχου while
        }

        string_is_number(input, &only_digits);

        string_is_one_word(input, &only_word);

        if (!only_word) //έλεγχος για ειαγωγή παραπάνω από μίας λέξης
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. Input cannot consist of more than one words.\n\n");
            SetColor(WHITE);
            continue;
        }

        if (!only_digits) //έλεγχος για εισαγωγή γραμμάτων
        {
            error_sound();
            SetColor(RED);
            puts("\nInvalid input. IBAN cannot contain any letters. Please try again.\n");
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) > IBAN_DIGITS) //έλεγχος μήκους iban
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. IBAN cannot be more than %d digits long. Please try again.\n\n", IBAN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (strlen(input) < IBAN_DIGITS) //έλεγχος μήκους iban
        {
            error_sound();
            SetColor(RED);
            printf("\nInvalid input. IBAN cannot be less than %d digits short. Please try again.\n\n", IBAN_DIGITS);
            SetColor(WHITE);
            continue;
        }

        if (only_digits && strlen(input) == IBAN_DIGITS) //αν το iban ήταν επιτρεπτό
        {
            *iban = strtoull(input, NULL, 10); //μετατροπή και αποθήκευση της εισαγωγής σε παράμετρο της συνάρτησης
            break; //τερματισμός βρόχου while
        }
    }
}

/*Συνάρτηση print_balance: τυπώνει στην οθόνη του χρήστη το χρηματικό υπόλοιπο του λογαριασμού του.
Η συνάρτηση δέχεται σαν παράμετρο το χρηματικό υπόλοιπο του χρήστη και δεν επιστρέφει τιμή.*/
void print_balance(float balance)
{
    SetColor(BLUE);
    printf("\nCurrent balance: ");
    SetColor(WHITE);
    printf("%.2f Euros.", balance);
}

/*Συνάρτηση print_creds: τυπώνει στην οθόνη του χρήστη στοιχισμένα όλα του τα στοιχεία.
Η συνάρτηση δέχεται σαν παράμετρο δείκτη στο ονομα, δείκτη στο επίθετο, δείκτη στο όνομα χρήστη,
τον προσωπικό αριθμό ταυτοποίησης, το ΑΦΜ, το IBAN και τον αριθμό λογαριασμού του χρήστη, ενώ δεν επιστρέφει τιμή.*/
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

/*Συνάρτηση print_deposits_history: τυπώνει στην οθόνη του χρήστη στοιχισμένα το ιστορικό των καταθέσεών του.
Η συνάρτηση δέχεται σαν παράμετρο έναν πίνακα τύπου "Deposit", ο οποιος περιέχει τα στοιχεία κάθε κατάθεσης του χρήστη
και δεν επιστρέφει τιμή.*/
void print_deposits_history(struct Deposit deposits_history[])
{
    if (deposits_history[0].id == 0) //αν δεν έχουν γίνει καταθέσεις με αυτόν τον λογαριασμό
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

/*Συνάρτηση print_withdrawals_history: τυπώνει στην οθόνη του χρήστη στοιχισμένα το ιστορικό των αναλήψεών του.
Η συνάρτηση δέχεται σαν παράμετρο έναν πίνακα τύπου "Withdrawal", ο οποιος περιέχει τα στοιχεία κάθε ανάληψης του χρήστη
και δεν επιστρέφει τιμή.*/
void print_withdrawals_history(struct Withdrawal withdrawals_history[])
{
    if (withdrawals_history[0].id == 0) //αν δεν έχουν γίνει αναλήψεις με αυτόν τον λογαριασμό
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

/*Συνάρτηση print_transfers_rec_history: τυπώνει στην οθόνη του χρήστη στοιχισμένα το ιστορικό των μεταφορών που έχει λάβει.
Η συνάρτηση δέχεται σαν παράμετρο έναν πίνακα τύπου "Transfer", ο οποιος περιέχει τα στοιχεία κάθε μεταφοράς που έχει λάβει
και δεν επιστρέφει τιμή.*/
void print_transfers_rec_history(struct Transfer transfers_rec_history[])
{
    if (transfers_rec_history[0].id_receiver == 0) //αν δεν έχουν γίνει μεταφορές προς αυτόν τον λογαριασμό
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

/*Συνάρτηση print_transfers_send_history: τυπώνει στην οθόνη του χρήστη στοιχισμένα το ιστορικό των μεταφορών που έχει αποστείλει.
Η συνάρτηση δέχεται σαν παράμετρο έναν πίνακα τύπου "Transfer", ο οποιος περιέχει τα στοιχεία κάθε μεταφοράς που έχει αποστείλει
και δεν επιστρέφει τιμή.*/
void print_transfers_send_history(struct Transfer transfers_send_history[])
{
    if (transfers_send_history[0].id_sender == 0) //αν δεν έχουν γίνει μεταφορές από αυτόν τον λογαριασμό
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

/*Συνάρτηση string_is_number: έλεγχει αν στην εισαγωγή περιέχεται τουλάχιστον ένα γράμμα,
οπότε δεν είναι αριθμός. Η συνάρτηση δέχεται σαν παραμέτρους δείκτη στην εισαγωγή και
δείκτη στη μεταβλητή only_digits, ενώ δεν επιστρέφει τιμή.*/
void string_is_number(char input[], short int *only_digits)
{
    int i;

    *only_digits = 1;

    for (i = 0; i < (int)strlen(input); i++) //έλεγχος για εισαγωγή μόνο ψηφίων
    {
        if (!isdigit(input[i]))
        {
            *only_digits = 0;
        }
    }
}

/*Συνάρτηση string_is_float_number: έλεγχει αν στην εισαγωγή περιέχεται παραπάνω από μία υποδιαστολή
ή αν περιέχονται γάμματα, οπότε δεν είναι αριθμός κινητής υποδιαστολής.
Η συνάρτηση δέχεται σαν παραμέτρους δείκτη στην εισαγωγή και
δείκτη στη μεταβλητή only_float, ενώ δεν επιστρέφει τιμή.*/
void string_is_float_number(char input[], short int *only_float)
{
    int i, number_of_points = 0;

    *only_float = 1;

    for (i = 0; i < (int)strlen(input); i++)
    {
        if (input[i] == '.') //καταμέτρηση υποδιαστολών στην εισαγωγή
        {
            number_of_points++;
        }

        if (!isdigit(input[i]) && input[i] != '.') //έλεγχος για ύπαρξη γραμμάτων στην εισαγωγή
        {
            *only_float = 0;
        }
    }

    if (number_of_points > 1) //έλεγχος για ύπαρξη παραπάνω απο μίας υποδιαστολής
    {
        *only_float = 0;
    }
}

/*Συνάρτηση string_contains_digits: έλεγχει αν στην εισαγωγή περιέχεται τουλάχιστον ένα ψηφίο,
οπότε δεν είναι λέξη. Η συνάρτηση δέχεται σαν παραμέτρους δείκτη στην εισαγωγή και
δείκτη στη μεταβλητή contains_digits, ενώ δεν επιστρέφει τιμή.*/
void string_contains_digits(char input[], short int *contains_digits)
{
    int i;

    *contains_digits = 0;

    for (i = 0; i < (int)strlen(input); i++) //έλεγχος εισαγωγης για ύπαρξη ψηφίου
    {
        if (isdigit(input[i]))
        {
            *contains_digits = 1;
        }
    }
}

/*Συνάρτηση string_is_one_word: έλεγχει αν στην εισαγωγή περιέχεται τουλάχιστον ένας χαρακτήρας κενού,
οπότε αποτελείται από παραπάνω από μία λέξεις. Η συνάρτηση δέχεται σαν παραμέτρους δείκτη στην εισαγωγή και
δείκτη στη μεταβλητή only_word, ενώ δεν επιστρέφει τιμή.*/
void string_is_one_word(char input[], short int *only_word)
{
    int i;

    *only_word = 1;

    for (i = 0; i < (int)strlen(input); i++) //έλεγχος εισαγωγης για ύπαρξη ψηφίου
    {
        if (input[i] == ' ')
        {
            *only_word = 0;
        }
    }
}

/*Συνάρτηση terminate_transaction: ελέγχει αν η εισαγωγή είναι ο συνδυασμός εξόδου '%%%' και τυπώνει το
αντίστοιχο μύνημα. Η συνάρτηση δέχεται σαν παράμετρο δείκτη στην εισαγωγή και επιστρέφει
1, αν η ειασγωγή ηταν ο συνδυασμός εξόδου, ενώ σε διαφορετική περίπτωση επιστρέφει 0.*/
short int terminate_transaction(char input[])
{
    if (strcmp("%%%", input) == 0)
    {
        SetColor(ORANGE); //μπλε χρώμα ή μηπως 6?
        print_message_slowly("\n\nTerminating session...Thank you for choosing BOP!");
        SetColor(WHITE); //μαύρο χρώμα
        Sleep(LONG_SLEEP_TIME);
        active = 0;

        return 1;
    }

    return 0;
}

/*Συνάρτηση SetColor: αλλάζει το χρώμα του κειμένου στην ροή stdout.
Η συνάρτηση δέχεται σαν παράμετρο τον κωδικό του χρώματος και δεν επιστρέφει τιμή.
Πηγή: https://stackoverflow.com/a/29578507*/
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

/*Συνάρτηση print_message_slowly: τυπώνει γράμμα προς γράμμα μια συμβολοσειρά,
με μία μικρή καθυστέρηση ανάμεσα στην τύπωση των γραμμάτων. Η συνάρτηση δέχεται
σαν παράμετρο δείκτη στη συμβολοσειρά και δεν επιστρέφει τιμή.*/
void print_message_slowly(char message[])
{
    for (int i = 0; i < (int)strlen(message); i++)
    {
        putchar(message[i]);
        Sleep(VERY_SHORT_SLEEP_TIME);
    }

    putchar('\n');
}

/*Συνάρτηση cooldown: ελέγχει αν η παράμετρός της είναι ίση ή μεγαλύτερη
του τρια, οπότε ο χρήστης έχει κάνει τρεις ή παραπάνω αποτυχημένες προσπάθειες σύνδεσης
και του απαγορεύει να κάνει νέα προσπάθεια για 10 δευτερόλεπτα. Η συνάρτηση δέχεται
σαν παράμετρο δείκτη στη μεταβλητή invalid_input και επιστρέφει 1, αν ο χρήστης έκανε τρεις ή
περισσότερες αποτυχημένες προσπάθειες, ενώ σε διαφορετική περίπτωση επιστρέφει 0.*/
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

/*Συνάρτηση error_sound: παράγει ήχο αποτυχίας.
Η συνάρτηση δεν δέχεται παραμέτρους και δεν επιστρέφει τιμή.*/
void error_sound(void)
{
    Beep(E, SOUND_DURATION);
    Beep(D, SOUND_DURATION);
}

/*Συνάρτηση success_sound: παράγει ήχο επιτυχίας.
Η συνάρτηση δεν δέχεται παραμέτρους και δεν επιστρέφει τιμή.*/
void success_sound(void)
{
    Beep(D, SOUND_DURATION);
    Beep(CH, SOUND_DURATION);
}
