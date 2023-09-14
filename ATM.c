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


/*Κύρια συνάρτηση main: διαχειρίζεται όλες τις υπάρχουσες συναρτήσεις.
Πιο συγκεκριμένα, ενημερώνει τον χρήστη σχετικά με την εγγύηση του προγράμματος, δηλώνει και αρχικοποιεί όλες
τις απαραίτητες μεταβλητές και δημιουργεί έναν ατέρμονο βρόχο while. Μέσα σε αυτόν, ο χρήστης επιλέγει τις ενέργειες
που θέλει να κάνει και οι αντίστοιχες συναρτήσεις καλούνται. Όταν ένας χρήστης τερματίσει το "session" του,
έχει ολοκληρωθεί μία επανάληψη του ατέρμονου βρόχου και στην οθόνη εμφανίζεται εκ νέου η αρχική οθόνη,
εν αναμονή νέου χρήστη. Η συνάρτηση δεν δέχεται παραμέτρους και επιστρέφει 0 με την επιτυχή εκτέλεσή της,
αν και στην πραγματικότητα ποτέ δεν τερματίζεται, λόγω του ατέρμονου βρόχου while.*/
int main()
{
    system("cls");

    printf("BOP_ATM Copyright 2023 Spanoudakis Stavros, Filippidis Christos\n\n"
           "This program comes with ABSOLUTELY NO WARRANTY; for more information, enter 'w'.\n"
           "This is free software and you are welcome to redistribute it\n"
           "under certain conditions; for full list of conditions, see LICENSE.txt\n\n"
           "To initiate the main program, enter 'i'\n"); //Copyright Claim

    char choice_info;
    select_info(&choice_info); //w για warranty, i για συνέχεια στο κύριο μέρος του προγράμματος

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

    //δήλωση όλων των μεταβλητών
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

    while(1) //έναρξη ατέρμονου βρόχου
    {
        //αρχικοιποίηση όλων των μεταβλητών
        active = 1;
        requested_iban = 2; //τιμή για χειρισμό σφαλμάτων
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

        //έναρξη αλληλεπίδρασης με τον χρήστη
        system("cls");
        welcome();

        register_or_login(&choice_r_l); //r για εγγραφή, l για σύνδεση

        if (choice_r_l == 'l' && active)
        {
            system("cls");
            SetColor(PURPLE);
            printf("\t\t\t\t\tLOGIN");
            SetColor(WHITE);

            while (is_logged_in == 0)
            {
                get_creds_login(current_user.username, &current_user.id, &current_user.pin); //λήψη των απαραίτητων στοιχείων για σύνδεση
                if (!active) break;

                if (current_user.id == 0) //αν έγινε σύνδεση μέσω ονόματος χρήστη
                {
                    if (get_user_from_username(current_user.username).pin == current_user.pin) //αν το pin αντιστοιχεί στο εισαχθέν όνομα χρήστη
                    {
                        success_sound();
                        SetColor(GREEN);
                        printf("\n\nYou have successfully logged in.\n");
                        SetColor(WHITE);
                        Sleep(SHORT_SLEEP_TIME);
                        system("cls");
                        current_user = get_user_from_username(current_user.username); //μεταβίβαση όλων των στοιχείων του χρήστη που μόλις συνδέθηκε στη δομή current_user
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
                else //αν έγινε σύνδεση μέσω αριθμού λογαριασμού
                {
                    if (get_user_from_id(current_user.id).pin == current_user.pin) //αν το pin αντιστοιχεί στον εισαχθέντα αριθμό λογαριασμού
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

                if (cooldown(&invalid_input) == 1) //αν ο χρήστης έκανε πάνω απο τρεις αποτυχημένες προσπάθειες σύνδεσης
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
            get_creds_register(current_user.name, current_user.surname, current_user.username, &current_user.pin, &current_user.tin); //λήψη των απαραίτητων στοιχείων για εγγραφή
            current_user.id = create_new_user(current_user.name, current_user.surname, current_user.username, current_user.pin, current_user.tin); //δημιουργία νέου χρήστη και αποθήκευση του αριθμού λογαριασμού του στο μέλος δομής current_user.id
            is_logged_in = 1;
            system("cls");
        }

        while (is_logged_in && active)
        {
            if (choice_y_n == 'n' || !active) //αν ο χρήστης επέλεξε ότι δεν θέλει να κάνει άλλη συναλαγή
            {
                SetColor(ORANGE);
                print_message_slowly("\n\nTerminating session...Thank you for choosing BOP!");
                SetColor(WHITE);
                Sleep(LONG_SLEEP_TIME);
                break;
            }
            else if (choice_y_n == 'y') //αν ο χρήστης επέλεξε ότι θέλει να κάνει και άλλη συναλαγή
            {
                system("cls");
            }

            //Αρχικοποίηση των μεταβλητών επιλογής
            choice_d_w_t_b_c_h = '0';
            choice_d_w_t = '0';

            SetColor(PURPLE);
            printf("\t\t\t\t\tMAIN MENU\n\n");
            SetColor(WHITE);

            current_user = get_user_from_id(current_user.id); //μεταβίβαση όλων των στοιχείων του συνδεδεμένου χρήστη στη δομή current_user

            select_mode(&choice_d_w_t_b_c_h); //d για κατάθεση, w για ανάληψη, t για μεταφορά, b για έλεγχο υπολοίπου, c για έλεγχο στοιχείων, h για έλεγχο ιστορικού συναλλαγών

            switch(choice_d_w_t_b_c_h)
            {
            case 'd':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tNEW DEPOSIT");
                SetColor(WHITE);
                get_amount_description(&current_amount, current_description); //λήψη στοιχείων κατάθεσης
                if (!active) break;
                new_deposit(current_user.id, current_amount, current_description); //αποθήκευση στοιχείων κατάθεσης
                current_user = get_user_from_id(current_user.id); //μεταβίβαση όλων των στοιχείων του συνδεδεμένου χρήστη στη δομή current_user
                success_sound();
                SetColor(GREEN);
                printf("\nYour balance has been updated.\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //εμφάνιση νέου υπολοίπου
                Sleep(SHORT_SLEEP_TIME);
                yes_or_no(&choice_y_n); //y για νέα συναλλαγή, n για αποχώρηση
                break;

            case 'w':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tNEW WITHDRAWAL");
                SetColor(WHITE);
                get_amount_description(&current_amount, current_description); //λήψη στοιχείων ανάληψης
                if (!active) break;

                while (current_amount > current_user.balance && active) //όσο η προς ανάληψη ποσότητα υπερβαίνει το υπόλοιπο
                {
                    error_sound();
                    SetColor(RED);
                    printf("\nThe entered amount surpasses your current balance. Please try again.\n");
                    SetColor(WHITE);
                    get_amount_description(&current_amount, current_description); //λήψη στοιχείων ανάληψης
                }

                if (!active) break;
                new_withdrawal(current_user.id, current_amount, current_description); //αποθήκευση στοιχείων ανάληψης
                current_user = get_user_from_id(current_user.id); //μεταβίβαση όλων των στοιχείων του συνδεδεμένου χρήστη στη δομή current_user
                success_sound();
                SetColor(GREEN);
                printf("\nYour balance has been updated.\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //εμφάνιση νέου υπολοίπου
                Sleep(SHORT_SLEEP_TIME);
                yes_or_no(&choice_y_n); //y για νέα συναλλαγή, n για αποχώρηση
                break;

            case 't':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tNEW TRANSFER");
                SetColor(WHITE);
                get_user_to_transfer(&requested_iban); //λήψη iban παραλήπτη
                if (!active) break;

                while (get_user_from_iban(requested_iban).iban != requested_iban) //όσο το εισαχθέν iban δεν αντισοιχεί σε υπάρχον iban
                {
                    error_sound();
                    SetColor(RED);
                    printf("\nThe entered IBAN does not exist. Please try again.\n");
                    SetColor(WHITE);
                    get_user_to_transfer(&requested_iban); //λήψη iban παραλήπτη
                    if (!active) break;
                }

                if (!active) break;
                get_amount_description(&current_amount, current_description); //λήψη στοιχείων μεταφοράς
                if (!active) break;

                while (current_amount > current_user.balance && active) //όσο η προς μεταφορά ποσότητα υπερβαίνει το υπόλοιπο
                {
                    error_sound();
                    SetColor(RED);
                    printf("\nThe entered amount surpasses your current balance. Please try again.\n");
                    SetColor(WHITE);
                    get_amount_description(&current_amount, current_description); //λήψη στοιχείων μεταφοράς
                }

                if (!active) break;
                new_transfer(current_user.id, get_user_from_iban(requested_iban).id, current_amount, current_description); //αποθήκευση στοιχείων μεταφοράς
                current_user = get_user_from_id(current_user.id); //μεταβίβαση όλων των στοιχείων του συνδεδεμένου χρήστη στη δομή current_user
                success_sound();
                SetColor(GREEN);
                printf("\nTransfer is complete.\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //εμφάνιση νέου υπολοίπου
                Sleep(SHORT_SLEEP_TIME);
                yes_or_no(&choice_y_n); //y για νέα συναλλαγή, n για αποχώρηση
                break;

            case 'b':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tBALANCE\n");
                SetColor(WHITE);
                print_balance(current_user.balance); //εμφάνιση υπολοίπου
                if (!active) break;
                yes_or_no(&choice_y_n); //y για νέα συναλλαγή, n για αποχώρηση
                break;

            case 'c':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tCREDENTIALS\n");
                SetColor(WHITE);
                current_user = get_user_from_id(current_user.id); //μεταβίβαση όλων των στοιχείων του συνδεδεμένου χρήστη στη δομή current_user
                print_creds(current_user.name, current_user.surname, current_user.username, current_user.pin, current_user.tin, current_user.iban, current_user.id); //εμφάνιση όλων των στοιχείων του χρήστη
                yes_or_no(&choice_y_n); //y για νέα συναλλαγή, n για αποχώρηση
                break;

            case 'h':
                system("cls");
                SetColor(PURPLE);
                printf("\t\t\t\t\tTRANSACTION HISTORY MENU\n\n");
                SetColor(WHITE);

                select_history(&choice_d_w_t); //d για ιστορικό καταθέσεων, w για ιστορικό αναλήψεων, t για ιστορικό μεταφορών

                system("cls");

                switch(choice_d_w_t)
                {
                case 'd':
                    SetColor(PURPLE);
                    printf("\t\t\t\t\tDEPOSITS HISTORY\n\n");
                    SetColor(WHITE);
                    load_deposits_history(current_user.id); //εύρεση των καταθέσεων του χρήστη με αριθμό λογαριασμού "current_user.id"
                    print_deposits_history(deposits_history); //εμφάνιση του ιστορικού καταθέσεων
                    break;

                case 'w':
                    SetColor(PURPLE);
                    printf("\t\t\t\t\tWITHDRAWALS HISTORY\n\n");
                    SetColor(WHITE);
                    load_withdrawals_history(current_user.id); //εύρεση των αναλήψεων του χρήστη με αριθμό λογαριασμού "current_user.id"
                    print_withdrawals_history(withdrawals_history); //εμφάνιση του ιστορικού αναλήψεων
                    break;

                case 't':
                    SetColor(PURPLE);
                    printf("\t\t\t\t\tTRANSFERS HISTORY\n\n");
                    SetColor(WHITE);
                    load_transfers_rec_history(current_user.id); //εύρεση των ληφθέντων μεταφορών του χρήστη με αριθμό λογαριασμού "current_user.id"
                    load_transfers_send_history(current_user.id); //εύρεση των αποσταλέντων μεταφορών του χρήστη με αριθμό λογαριασμού "current_user.id"
                    print_transfers_rec_history(transfers_rec_history); //εμφάνιση του ιστορικού ληφθέντων μεταφορών
                    print_transfers_send_history(transfers_send_history); //εμφάνιση του ιστορικού αποσταλέντων μεταφορών
                    break;
                }

                yes_or_no(&choice_y_n); //y για νέα συναλλαγή, n για αποχώρηση
                break;
            }
        }
    }
    return 0;
}
