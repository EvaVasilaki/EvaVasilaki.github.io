#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_SIZE 1000000000 // Περιορισμός λογικού μεγέθους παραθύρου

void SMA(const double *data, int size, long long window_size) {//Συνάρτηση που υπολογίζει ως πρόβλεψη τον κινούμενο μέσο όρο

    double sum = 0.0;//Αρχικοποίηση του αθρίσματος

    for (int i = size - window_size; i < size; i++) { //Loop το οποίο εντοπίζει τα επιθυμητά στοιχεία του αρχείου απο την τιμή του παραθύρου για την εύρεση του μέσου όρου
        sum += data[i]; //Προσθήκη των στοιχείων στο άθροισμα
    }

    double average = sum / window_size;//Υπολογισμός του μέσου όρου
    printf("%.2f\n", average); //Εκτύπωση του αποτελέσματος 

}

int main(int argc, char *argv[]) {

    //Έλεγχος για την σωστή κλήση του προγράμματος
    if (argc < 2 || argc > 4) {

        fprintf(stderr, "Usage: %s <filename> [--window N (default: 50)]\n", argv[0]);
        return 1; // exit code 1 σε περίπτωση λάθους
    }

    const char *filename = argv[1]; //Αποθήκευση του ονόματος του αρχείου απο τα ορίσματα
    long long window_size = 50; // Default μέγεθος παραθύρου


    FILE *file = fopen(filename, "r"); //Ανοιγμα αρχείου

    if (file == NULL) { // Εαν για καποιο λόγο δεν ανοίγει το αρχείο, εμφανίζει error
        perror("Error opening file");
        return 1; // exit code 1 για σφάλμα
    }

    // Χρήση δυναμικής μνήμης για τον πίνακα δεδομένων
    double *data = malloc(MAX_DATA_SIZE * sizeof(double));

    //Αν δεν πραγματοποιηθεί η κατανομή μνήμης εμφανίζεται το παρακάτω error
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        fclose(file); //Κλείσιμο αρχείου
        return 1; // exit code 1
    }

    long long int size = 0;// Μεταβλητή για αποθηκευση του πλήθους των δεδομένων

    while (fscanf(file, "%lf", &data[size]) == 1) {
        size++; // Αυξηση του μεγέθους των δεδομένων κάθε φορά που γινεται ανάγνωση ενός
    }

    fclose(file); //Κλείσιμο αρχείου


    //Έλεγχος παραθύρου
    if (argc == 4) {
        if (strcmp(argv[2], "--window") == 0) {
            window_size = atoll(argv[3]);//Ανάγνωση του μεγέθους του παραθύρου
            if (window_size <= 0) {//Αν το μέγεθος του παραθύρου ειναι μικροτερο του 0 τοτε exit code 1 και error 
                fprintf(stderr, "Window too small!\n");
                return 1;
            }
            
        } 
        else {// Εαν υπάρχει μη έγκυρο όρισμα τοτε exit code 1 
            return 1;
        }
    }

    //Αν το μέγεθος του παραθύρου ειναι μεγαλύτερο απο αυτό του πίνακα των δεδομένων τότε εμφανίζεται error και exit code 1
    if (window_size > size) {
        fprintf(stderr, "Window too large!\n");
        free(data); // Απελευθέρωση μνλημης αφού τελειώνει το πρόγραμμα
        return 1;
    }

    //Κλήση της συνάρτησης υπολογισμου του Μ.Ο
    SMA(data, size, window_size);

    // Απελευθέρωση της μνήμης
    free(data);

    return 0;
}
