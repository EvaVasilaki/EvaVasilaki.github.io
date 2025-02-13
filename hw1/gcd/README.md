# Το συγκεκριμένο πρόγραμμα υπολογίζει τον Μεγιστο Κοινό Διαιρέτη με βάση τον Αλγόριθμο του Ευκλείδη

## Οι παρακάτω είναι οι βιβλιοθήκες που χρησιμοποιήθηκαν:

1. stdio.h Για την χρήση της printf.
2. stdlib.h Για την χρήση της συνάρτησης atoll που μετατρέπει τα command line arguments σε long long int datatype


## Build

Το πρόγραμμα γίνεται compile με τη παρακάτω εντολή :

```bash
gcc -O3 -Wall -Wextra -Werror -pedantic -o gcd gcd.c
```
## Χρήση 

```bash
./gcd <num1> <num2>
```
## Demo 

```bash
./gcd 129 6235
43
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
Η συνάρτηση gcd χρησιμοποιείται για την εύρεση του μέγιστου κοινού διαιρέτη δύο αριθμών.

main 
```c
int main(int argc, char ** argv) {

  if (argc != 3) {
	printf("Usage: ./gcd <num1> <num2>\n");
	return 1;
  }

  long long int num1 = atoll(argv[1]);
  long long int num2 = atoll(argv[2]);

  if (num1 == 0 || num2 == 0) {
    return 1;
  }

  printf("gcd(%lld, %lld) = %lld\n" ,num1, num2, gcd(num1,num2));
  return 0;

 }
```
Στην συνάρτηση main: 
1. Γίνεται έλεγχος για τον σωστό αριθμό arguments
2. Μετατρέπονται τα command line arguments σε long long int data type
3. Γίνεται έλεγχος για στη περίπτωση που οι αριθμοί ισούται με το 0
4. Εκτυπώνεται το αποτέλεσμα

Exit code 0 : Ομαλός τερματισμός προγράμματος
Exit code 1 : Εσφαλμένος τερματισμός προγράμματος
