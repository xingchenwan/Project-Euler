// Problem 59

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

struct AnalyzedNum {
    int num; // decimal number
    char bin [32]; // binary number
    int PasswordIndex; // the password char corresponding to this encrypted char. Index is 0,1 or 2. The password index is recycled periodically
};
int PasswordASCII [3];
char *PasswordBinary [3];
void converter (char *, struct AnalyzedNum *);
void FindPasscode (struct AnalyzedNum *, int);
long decryption (struct AnalyzedNum *);
int main()
{
    char buf [3203];
    struct AnalyzedNum CipherText [1201];
    FILE *fp;
    
    // Legal ASCII code range for the 3-digited password: 97 - 122 ("a" to "z")
    
    fp = fopen ("/Users/Stellar/Desktop/ProjectEuler/InputDocs/p059_cipher.txt","r");
    if (fp == NULL) {
        printf ("Error opening the file.\n");
        return 1;
    }fgets(buf, 3203, fp);
    
    converter(buf, CipherText);
    FindPasscode(CipherText, 0); // Passcodes in ASCII are "103, 111, 100" (god)
    printf ("Passcode: %c%c%c\n\n", PasswordASCII[0], PasswordASCII[1], PasswordASCII[2]);
    printf ("\n\nASCII Value Count: %ld", decryption(CipherText));
    return 0;
}

    
int btoi (char *);
void itob (int, char*);

long decryption (struct AnalyzedNum *Cipher)
{
    int i, j;
    char DecryptedBinary [32];
    int DecryptedASCII;
    long sum = 0;
    
    printf ("Decrypted Text: \n\n");
    for (i = 0; i < 1201; i++) {
        for (j = 0; j < 32; j++) {
            DecryptedBinary[j] = PasswordBinary[Cipher[i].PasswordIndex][j] ^ Cipher[i].bin[j];
        }
            // XOR password and encrypted to get decrypted message
            sum += (DecryptedASCII = btoi(DecryptedBinary));
            printf ("%c", DecryptedASCII);
        }
    return sum;
}

void FindPasscode (struct AnalyzedNum * Cipher, int k)
// For the current try, test whether XORing the trial and the cipher returns a value within the legal range
{
    char CurrentTryBinary [32];
    char PlainBinary [32];
    int ProbablePlain;
    int j, i, p = k;
    
    for (j=97; j<=122; j++) { // 'a' = 97; 'z' = 122
    itob (j, CurrentTryBinary);
        // Try possible passwords ('a' to 'z'). Convert the ASCII of that char to binary num
        for ( ; p < 1201; p += 3) {
            if (p > 1190) {// If the current attempt is valid for all chars. It has to be the key
                PasswordASCII[Cipher[k].PasswordIndex] = j;
                PasswordBinary[k] = strdup (CurrentTryBinary);
                goto nextpassworddigit;
            }
            for (i = 0; i < 32; i++)
                PlainBinary[i] = CurrentTryBinary[i] ^ Cipher[p].bin[i]; // XOR the possible password with the ciphered text
            ProbablePlain = btoi(PlainBinary);
            if ( (ProbablePlain >= 32 && ProbablePlain <= 34) ||// SPACE, " and !
                 (ProbablePlain >= 38 && ProbablePlain <= 41) || // &,',( and )
                 (ProbablePlain >= 44 && ProbablePlain <= 59) || // 0 - 9, : and ;
                 (ProbablePlain >= 63 && ProbablePlain <= 90) || // A - Z
                 (ProbablePlain >= 97 && ProbablePlain <= 122) ) // a - z
                 ;
            else break;
        }
    }
    nextpassworddigit:
    if (k == 0)
        FindPasscode(Cipher, 1); //Find next digit of the passcode
    else if (k == 1)
        FindPasscode(Cipher, 2);
    else return;
}


int btoi (char *BinaryList) // Convert binary to decimal
{
    int i = 31, j = 0;
    int temp = 0;
    
    for (;i >= 0; i--, j++)
        if (BinaryList[i])
            temp += pow (2,j);
    return temp;
}

void converter (char *buff, struct AnalyzedNum * text)
{
    int i, PassIndex = 0, tempindex = 0, afterdigit = 0;
    int k = 0;
    
    char temp[3];
    for (i = 0; (buff[i] != EOF) && (k <= 1200); i++) {
        if (isdigit(buff[i])) {
            temp[tempindex++] = buff[i];
            afterdigit = 1;
        } else if (afterdigit) {
            text[k].num = atoi (temp);
            itob (text[k].num, text[k].bin);
            if (PassIndex <= 2)
                text[k].PasswordIndex = PassIndex++;
            else {
                text[k].PasswordIndex = 0;
                PassIndex = 1;
            } afterdigit = tempindex = temp[0] = temp[1] = 0; // Flush mem
            k++;
        }
    }
}

void itob (int num, char *BinaryList) // Convert decimal to binary
{
    int j; // Size of BinaryList - 1
    for (j = 0; j < 32; j++)
        BinaryList[j] = '0';
    j--;
    while (num > 0) {
        if (num % 2)
            BinaryList [j--] = '1';
        else BinaryList [j--] = '0';
        num /= 2;
    }
}

// Passcode is "god"
// Decrypted text is "The Gospel of John, chapter 1" : 1 In the beginning the Word... ... the glory of the only Son of the Father.
// ASCII count is 107359
// Runtime: 2.0ms
