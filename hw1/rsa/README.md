# Το συγκεκριμένο πρόγραμμα κρυπτογραφεί και αποκρυπτογραφεί μηνυματα με βάση τον αλγόριθμο RSA

## Οι παρακάτω είναι οι βιβλιοθήκες που χρησιμοποιήθηκαν:

1. stdio.h Για την χρήση της printf.
2. stdlib.h Για την χρήση της συνάρτησης atoll που μετατρέπει τα command line arguments σε long long int datatype
3. string.h Για την χρήση της συνάρτησης strcmp που συγκρίνει δύο string.

## Build

Το πρόγραμμα γίνεται compile με τη παρακάτω εντολή :

```bash
gcc -O3 -Wall -Wextra -Werror -pedantic -o rsa rsa.c
```
## Χρήση 

```bash
echo <message> | ./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>
```
## Demo 

```bash
echo 65  | ./rsa enc 17 2753 61 53
2790
```
## Συναρτήσεις 

gcd

```c
long long int gcd(long long int x, long long int y) {  

    long long int k = x % y; 
    

    if (k == 0) { 

        if (y<0) { 
         
        return (-1)*y; 
        }
        else {
            return y;
        }
    }

    else return gcd(y,k);

}
```
Η συνάρτηση gcd χρησιμοποιείται για την εύρεση του μέγιστου κοινού διαιρέτη δύο αριθμών. Στο πρόγραμμα αξιοποιείται για τον έλεγχο της σχετικής πρωταρχικότητας μεταξύ δύο αριθμών μέσω της συνάρτησης coprime.

phi

```c
long long int phi(long long int n)
{
    long long int result = n; 

    for (long long int p = 2; p * p <= n; ++p) {

        if (n % p == 0) {
            
            while (n % p == 0)
                n /= p;
            result *= (1.0 - (1.0 / (float)p));
        }
    }

    if (n > 1)
        result -= result / n;
 

    return result;
}
```

H συνάρτηση phi είναι απαραίτητη για τον υπολογισμό της τιμής φ(n) δηλαδή το πλήθος των φυσικών αριθμών που είναι μικρότεροι του n και comprime με το n

prime 

```c
int prime(long long int x) { 

    if (x <= 1) return 0; 
    if (x == 2) return 1;
    if (x % 2 == 0) return 0; 

    for (long long int j = 3; j * j <= x; j += 2) {
       
        if (x % j == 0) return 0;
    }
    return 1;
}
```
Συνάρτηση για τον έλεγχο πρωταρχικότητας

```c
coprime

long long int coprime(long long int x, long long int N) { 

    long long int k = phi(N);
    return gcd(x, k)==1; 
}
```
Συνάρτηση για έλεγχο co primarity μεταξυ αριθμών

reverseCheck
```c
long long int reverseCheck (long long int e, long long int d, long long int N) {

    long long int k = phi(N);
    return (e*d)%k==1;
}
```
Συνάρτηση για έλεγχο αντιστρόφων

exoinentMod
```c
long long int exponentMod(long long int x, long long int n, long long int m) {
 
    long long int result = 1;  
    x = x % m;                

    while (n > 0) {
      
        if (n % 2 == 1) {
            result = (result * x) % m;
        }

        x = (x * x) % m;
        n = n / 2;
    }

    return result; 
}
```

Συνάρτηση που πραγματοποιεί modular exponentiation υπολογίζοντας το (x^n)mody χρησιμοποιώντας exponentiation by squaring
encrypt
```c
long long int encrypt (long long int m, long long int e, long long int N) {
    return exponentMod(m, e, N);
}
```
Συνάρτηση κρυπτογράφησης του μηνύματος

decrypt
```c
long long int decrypt (long long int m, long long int d, long long int N) {
    return exponentMod(m, d, N);
}
```
Συνάρτηση αποκρυπτογράφησης του μηνύματος

main 
```c
int main(int argc, char ** argv) {

    //Έλεγχος : ο αριθμός των argument στο τερματικό πρέπει να ισούται με 6
    if (argc != 6) {
        printf("Usage: ./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>\n");//Σωστή κλήση του προγράμματος
        return 1;//Exit code 1 για λανθασμενη κλήση του προγράμματος
    }

    //Ορισμός των μεταβλητών ως τα ορίσματα που δίνονται στην ανάλογη θέση απο το terminal
    long long int e = atoll(argv[2]);
    long long int d = atoll(argv[3]);
    long long int p = atoll(argv[4]);
    long long int q = atoll(argv[5]);
    //Ορισμός της μεταβλητής N ως το γινόμενο των p και q
    long long int N = p*q;
        

    //Περιορισμός : το πρώτο argument πρεπει να είναι είτε "enc" είτε "dec"
    if(strcmp(argv[1], "dec") != 0 && strcmp(argv[1], "enc") != 0) {//Χρήση της συνάρτησης strcmp για τη σύγκρηση μεταξύ δύο συμβολοσειρών
        printf("First argument must be 'enc' or 'dec'\n");//Μήνυμα σε περιπτώση λανθασμένης εισόδου
        return 1;//Exit code 1
    }

    //Περιορισμός: όλοι οι ακέραιοι πρέπει να είναι θετικοί.
    if(e<0 || d<0 || p<0 || q<0) {
        printf("Negative numbers are not allowed\n");//Μήνυμα λανθασμένης εισόδου
        return 1;//Exit code 1
    }
        
    //Περιορισμός: οι ακέραιοι p και q είναι πρώτοι
    if (!prime(p) || !prime(q)) {//Αν οι συναρτήσεις δεν ισχύουν τότε 
        printf("p and q must be prime\n");//Μήνυμα λανθασμένης εισόδου
        return 1;//Exit code 1
    }

    // Περιορισμός: ο ακέραιος e είναι coprime με το ϕ(N).
    if (!coprime(e, N)) {
        printf("e is not coprime with phi(N)\n");//Μήνυμα λανθασμένης εισόδου
        return 1;//Exit code 1
    }
        
    //Περιορισμός: οι ακέραιοι e και d είναι αντίστροφοι
    if(!reverseCheck(e, d, N)) {
        printf("e * d mod phi(N) is not 1\n");//Μήνυμα λανθασμένης εισόδου
        return 1;//Exit code 1
    }

    //Ορισμός μυστικού μηνύματος m
    long long int m = 0;

    //Έλεγχος: Αν η είσοδος της scanf είναι λανθασμένη το πρόγραμμα τερματίζει με exit code 1
    if(scanf("%lld" , &m)!= 1) { //Ανάγνωση της τιμής του m από το τερματικό 
        return 1; //Exit code 1
    }
        
    //Περιορισμός: το μήνυμα m πρέπει να είναι θετικό
    if(m<0){ 
        printf("Negative numbers are not allowed\n");//Μήνυμα λανθασμένης εισόδου
        return 1;//Exit code 1
    }
    //Περιορισμός: το μήνυμα m πρέπει να είναι μικρότερο του Ν
    if (N < m) {
        printf("Message is larger than N\n");//Μήνυμα λανθασμένης εισόδου
        return 1;//Exit code 1
    }


    //Ορισμός μεταβλητής εξόδου
    long long int output;
    //Επιλογή του προγράμματος ανάλογα του πρώτου argument απο το τερματικό για κρυπτογράφηση ή αποκρυπτογράφηση
    //Εάν το argument στη θεση 1 ισούται με enc τότε το πρόγραμμα χρησιμοποιεί τη συναρτηση encrypt και αποθηκεύει το αποτέλεσμά της στη μεταβλητή output
    if (strcmp(argv[1], "enc") == 0) {
        output = encrypt(m, e, N);
    //Εάν το argument στη θεση 1 ισούται με dec τότε το πρόγραμμα χρησιμοποιεί τη συναρτηση decrypt και αποθηκεύει το αποτέλεσμά της στη μεταβλητή output 
    } else if (strcmp(argv[1], "dec") == 0) {
        output = decrypt(m, d, N);
    }

    //Εκτύπωση του αποτελέσματος
    printf("%lld\n" ,output);
        
    //Exit code 0 σωστή έξοδος του προγράμματος
    return 0;

    }  

```

Exit code 0 : Ομαλός τερματισμός προγράμματος
Exit code 1 : Εσφαλμένος τερματισμός προγράμματος
