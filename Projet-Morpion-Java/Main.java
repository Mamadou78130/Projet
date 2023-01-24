import java.util.*;

public class Main {

    static Scanner sc = new Scanner(System.in);

    public static void main(String [] arg)  {
		int res;
        Mode mor = new Mode();
        do {
           res = menu();
        switch(res) {
        case 1:
            mor.jeu1();
            break; 
        case 2:
			mor.jeu2();
            break; 
        case 3:
			mor.jeu3();
            break;  
            }} while(res!=0);
        }

		static int menu() {
			System.out.println("");
			System.out.println("MENU");
			System.out.println("");
			System.out.println("1 - Joueur Contre Joueur");
			System.out.println("2 - Ordinateur Contre Ordinateur");
			System.out.println("3 - Joueur Contre Ordinateur");
			System.out.println("0 - Quitter");
			System.out.println();
			
			System.out.print("Veuillez entrer une touche : ");
			return(sc.nextInt());
		}
}