#include <stdio.h>
#include <stdlib.h>

void sieve_es(int nbr)
{
	
	int i,x;
	int* primes;
	//primes = malloc(sizeof(int)*nbr);
	primes = malloc(sizeof(*primes)*nbr);

    //on rempli notre liste d'entiers naturelle
    for(i = 2; i<=nbr; i++)
    {
		primes[i] = i;
	}
    
    
	/*
	cette boucle while vas mettre à zéro tous les multiples exemples on prend 2 on élimine tous les multiples de 2 
	on prend 3 on élimine tous les multiples de 3 etc..
	*/
	i = 2;
	while ((i*i) <= nbr)
    {
        if (primes[i] != 0)
        {
            for(x=2; x<nbr; x++)
            {
                if (primes[i]*x > nbr)
					{
					break;
					}else
				{
                    // on met les elements multiples a zero
					primes[primes[i]*x]=0;
				}
			}
			
        }
        i++;
    }
	printf("\nPrimes numbers from 2 to %d are: ", nbr);
	printf("\n");
    for(i = 2; i<=nbr; i++)
    {
        //si le nombre n'est pas zero c'est un nombre premier et on l'affiche
        if (primes[i]!=0)
            printf("%d\n",primes[i]);
    }
	//printf("size of primes array is %d \n", sizeof(primes));
}

//fonction principale 
int main()
{
   
	int nbr,max;
	max = 500001;
	
	printf("Enter a number: \n");
    scanf("%d",&nbr);
	//if(nbr < max)
	//{
	sieve_es(nbr);
	//}else
	//{
	//	printf("your number is too big");
	//}
}