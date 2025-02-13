
#include <stdio.h> //Συμπερίληψη της απαιτούμενης βιβλιοθήκης για τη χρήση printf, scanf


int main () {


    long double leftCost,rightCost; //Ορισμός των μεταβλητών τύπου long double ωστε να ανταποκρίνονται στο εύρος των τιμων 

    while (!feof(stdin)) { //Περιορισμός της λειτουργίας του loop για όσο η είσοδος δεν είναι ιση με EOF

        printf("Please enter the cost of going left:"); //Εκτύπωση της πρότασης "Please enter the cost of going left"

        if(scanf("%Lf" , &leftCost)!= 1) { //Ελεγχος της πρώτης scanf να διαβάζει σωστη είσοδο
            printf("Terminating\n"); //(τύπου long double) και οταν φτάσει σε EOF να τελειώσει το πρόγραμμα με exit code 0
            return 0; // εκτυπώνοντας τη λέξη terminating 
        }

        printf("\n"); // Αλλαγή γραμμής 
        printf("Please enter the cost of going right:"); //Εκτύπωση της πρότασης "Please enter the cost of going right"


        if(scanf("%Lf",&rightCost)!= 1){ //Έλεγχος της δευτερης scanf να διαβάζει σωστή είσοδο 
            printf("No right cost provided\n"); //(τύπου float) αλλιώς εάν διαβάσει κατι λαθος η φτάσει σε EOF να τελειώσει το προγραμμα
            return 1;// με exit code 1 εκτυπώνοντας τη φράση No right cost provided
        }

        printf("\n"); //Αλλαγη γραμμης

        if (leftCost>rightCost) { //Έλεγχος των τιμων leftCost , rightCost για τις οποίες 
            printf("Go right\n");//αν η αριστερη ειναι μικρότερη η ιση τοτε εκτυπώνεται το Go left , αλλιως εμφανίζεται το Go right
        }
        else
        {
            printf("Go left\n");
        }

    }

        return 0;

}
