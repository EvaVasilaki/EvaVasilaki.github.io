#include <stdio.h>
#include <stdlib.h>


long long int gcd(long long int x, long long int y) { //Συνάρτηση που υπολογίζει τον μέγιστο κοινό διαιρέτη 

    long long int k = x % y; //Με βάση τον αλγόριθμο του Ευκλείδη, ορίζω τη μεταβλητή k ως x mod y 
    //για να ελέγχω κάθε φορά το υπόλοιπο της διαίρεσης x/y μεχρι αυτο να γίνει 0

    if (k == 0) { //Στην περίπτωση που γίνει 0 τοτε:

        if (y<0) {//Άν ο αριθμός y είναι μικρότερος του 0 τοτε επιστρέφει τον αντίθετό του 
        //(καθώς ψάχνω τον ΜΚΔ, το προσιμο δεν παίζει ρόλο στη διαίρεση και επομένως εάν ενας αριθμος διαιρείται με το -y τοτε θα διαιρείται και με το y) 
        return (-1)*y; //Φροντίζοντας έτσι ο ΜΚΔ να είναι πάντα θετικός
        }
        else {//Aν είναι θετικός
            return y;//Επιστροφή του y
        }
    }

    else return gcd(y,k);//Εαν το k δεν ισουται με 0, τοτε μεσω της αναδρομής, επαναλαμβάνεται η συνάρτηση ως gcd(y,k) οπου k το υπόλοιπο που υπολογίζεται

}

int main(int argc, char ** argv) {
    //Έλεγχος για τον σωστό αριθμό arguments
    if (argc != 3) {
    printf("Usage: ./gcd <num1> <num2>\n");
    return 1;
    }
    //Μετατροπή των command line arguments σε long long int data type
    long long int num1 = atoll(argv[1]);
    long long int num2 = atoll(argv[2]);

    //έλεγχος για στη περίπτωση που οι αριθμοί ισούται με το 0
    if (num1 == 0 || num2 == 0) {
      return 1;
    }
    //Εκτυπωση του αποτελέσματος
    printf("gcd(%lld, %lld) = %lld\n" ,num1, num2, gcd(num1,num2));
    return 0;

  }
