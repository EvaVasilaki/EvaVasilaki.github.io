# Το συγκεκριμένο πρόγραμμα υπολογίζει τον κινούμενο μέσο όρο για μια σειρά από δεδομένα και να τον εκτυπώνει ως πρόβλεψη

## Οι παρακάτω είναι οι βιβλιοθήκες που χρησιμοποιήθηκαν:

1. <stdio.h> Για την χρήση της printf, fprintf(stderr..)
2. <stdlib.h> Για την χρήση της συνάρτησης atoll, malloc και free
3. <string.h> Για την κλήση της συνάρτησης strcmp

## Build

Το πρόγραμμα γίνεται compile με τη παρακάτω εντολή :

```bash
gcc -O3 -Wall -Wextra -Werror -pedantic -o future future.c
```
## Χρήση 

```bash
./future <filename> [--window N (default: 50)]

```
## Demo 

```bash
./future
Usage: ./future <filename> [--window N (default: 50)]
$ cat values.txt
9 7 7 1 4 4 4 38 8 4
$ ./future values.txt --window 10
8.60
$ echo $?
0
```
## Συναρτήσεις 

SMA

```c

void SMA(const double *data, int size, long long window_size) {//Συνάρτηση που υπολογίζει ως πρόβλεψη τον κινούμενο μέσο όρο

    double sum = 0.0;//Αρχικοποίηση του αθρίσματος

    for (int i = size - window_size; i < size; i++) { //Loop το οποίο εντοπίζει τα επιθυμητά στοιχεία του αρχείου απο την τιμή του παραθύρου για την εύρεση του μέσου όρου
        sum += data[i]; //Προσθήκη των στοιχείων στο άθροισμα
    }

    double average = sum / window_size;//Υπολογισμός του μέσου όρου
    printf("%.2f\n", average); //Εκτύπωση του αποτελέσματος 

}


```
Η παραπάνω συνάρτηση, είναι αυτή που υπολογίζει τον κινούμενο μέσο όρο. Πρώτα, αρχικοποιεί το άθρισμα για τον ορθο υπολογισμό του στη συνέχεια. Προχωρά με μια for loop η οποία βρίσκει τα τελευταία X στοιχεία του αρχείου τα οποία ορίζονται απο το τερματικό με τη μεταβλητη window_size. Με το sum += data[i] προσθέτει όλα τα απαιτούμενα στοιχεία μεταξύ τους και στην average βρίσκει τον μέσο όρο.

main 

```c
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

```
Στην συνάρτηση main: 

Κάνει ελέγχους για:

1. Τη δυνατότητα κατανομής μνήμης για τα δεδομένα.
```c
//Αν δεν πραγματοποιηθεί η κατανομή μνήμης εμφανίζεται το παρακάτω error
    if (data == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        fclose(file); //Κλείσιμο αρχείου
        return 1; // exit code 1
    }
```

2. Εγκυρότητα του μεγέθους του παραθύρου (πρέπει να είναι θετικός αριθμός και μικρότερος ή ίσος με το μέγεθος των δεδομένων).
```c
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

```

Εκτός από τους ελέγχους, στη main ανοίγει και γίνεται ανάγνωση αρχείου και πραγματοποιείται δέσμευση μνήμης για τους πίνακες άγνωστων μεγεθών που θα 
αποθηκεύσουν τα στοιχεία των αρχείων: 
```c
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
```

Τέλος, σε αυτο το πρόγραμμα όλα τα errors γράφονται στο stderr

Exit code 0 : Ομαλός τερματισμός προγράμματος
Exit code 1 : Εσφαλμένος τερματισμός προγράμματος
