#include <stdio.h>
#include <cs50.h>
#include <string.h>
int main(void)
{
    int firstDigit;
    int secondDigit;
    long n = 0;       //number from user input
    int checksum = 0; //checksum of card
    int f;            // for first number of checksum
    int i;            //loop
    int s1, s2;        //digits of the F for checksum
    int r2;           //r2 //second variable for checksum
    int rp=0;         //r1
    int r;

 //Prompt User to INPUT A NUMBER

    do
    {
    n = get_long("Number: ");
    }
    while (n < 0);
    long ni = n;




   // for 13 DIGITS (VISA)
   if ( n>=1000000000000  && n <=9999999999999 ) {

        for (i = 0; i < 7; i++)
        {
            firstDigit = rp;
            secondDigit = r2;
                r = n%10;
                n= n/10;
            if (n<=100)
            {
                rp = n / 10;
                r2 = n % 10;
            }
            f = n % 10;
            f = f * 2 ;

            if (f >= 10)
            {
                 s1 = f / 10;
                 s2 = f % 10;

                 f = s1 + s2;
            }

        n = n / 10;




            checksum = checksum + (f + r);

        }

    checksum = checksum % 10;
   }
   //--------------------------

   //FOR 15 DIGITS (AMEX)
   if (n >= 100000000000000 && n <= 999999999999999)
   {
        for (i = 0; i<8; i++)
        {

            firstDigit = rp;
            secondDigit = r2;
              r = n%10;
              n = n/10;
    if (n <= 100)
    {
        rp = n/10;
        r2 = n%10;

    }

            f = n%10;
            f = f*2 ;

            if (f >= 10)
            {
                s1 = f/10;
                s2 = f%10;
                f = s1+s2;
            }

        n = n/10;
        checksum = checksum + (f + r);

        }

 checksum = checksum%10;

   }
   //-----------------------------

   //FOR 16 DIGITS (VISA & MASTERCARD)
   if (n >= 1000000000000000 && n <= 9999999999999999)
   {
    for (i = 0; i<8; i++){

        if (n <= 100)
        {
         rp = n/10;
         r2 = n%10;
        }

    firstDigit = rp;
    secondDigit = r2;
    r = n % 10;
    n = n/10;

    f = n%10;
    f = f*2 ;

    if (f >= 10)
    {
     s1 = f/10;
     s2 = f%10;
     f = s1+s2;
    }
        n = n / 10;
        checksum = checksum + (f + r);

        }

     checksum = checksum%10;


    }


  //-----------------------------








    // CHECK FOR CARDS STATS

    if (ni >= 1000000000000 && ni <= 10000000000000000){
        if (checksum == 0)
        {
            // GET FIRST TWO DIGITS

           if ((firstDigit == 3 && secondDigit == 4) || (firstDigit == 3 &&secondDigit==7) )
           {
               printf("AMEX\n");
           }
           else if ((firstDigit == 5 && secondDigit == 1) ||( firstDigit == 5 && secondDigit == 2) || (firstDigit == 5 && secondDigit == 3 )|| (firstDigit == 5 && secondDigit==4) ||( firstDigit == 5 && secondDigit==5))
           {
               printf("MASTERCARD\n");
           }
           else if (secondDigit == 4 || firstDigit == 4)
           {
               printf("VISA\n");
           }
           else
           {
               printf("INVALID\n");
           }
        }
        else {
            printf("INVALID\n") ;
        }


    }
    else {
        printf("INVALID\n");
    }

}
