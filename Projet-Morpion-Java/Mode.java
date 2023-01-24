import java.util.*;

public class Mode {
    static Scanner sc = new Scanner(System.in);
	public int pion;
	public String player;
	public String joueur1;
	public String joueur2;
	
    // Fonction du mode jeu Joueur Contre Joueur
	public void jeu1() {
		int X = 0;
		int Y = 0;
		
		System.out.print("---------------- \n");
        System.out.print("JEU DU MORPION \n");
        System.out.print("---------------- \n");
        System.out.print("JOUEUR 1 : 1 \n");
        System.out.print("JOUEUR 2 : 2 \n");
        System.out.print("---------------- \n");
		Jeu JeuMorpion = new Jeu("Joueur 1", "Joueur 2", 1);
        
        System.out.print("PLATEAU DE JEU \n");
        System.out.print("---------------- \n");

		System.out.println(JeuMorpion);
		
		while(!JeuMorpion.gagner()) {

			System.out.print("Donner la position X : ");
			X = sc.nextInt();
			System.out.print("Donner la position Y : ");
			Y = sc.nextInt();
			System.out.print("\n");

			JeuMorpion.tabpion(X,Y);
			System.out.println(JeuMorpion);
		}

		if (JeuMorpion.gagner())
			System.out.print("[FIN DE LA PARTIE] \n");
	}

	// Fonction du mode jeu Ordinateur Contre Ordinateur
	public void jeu2() {
		int X = 0;
		int Y = 0;
		
		System.out.print("---------------- \n");
        System.out.print("JEU DU MORPION \n");
        System.out.print("---------------- \n");
        System.out.print("JOUEUR 1 : 1 \n");
        System.out.print("JOUEUR 2 : 2 \n");
        System.out.print("---------------- \n");
		Jeu JeuMorpion = new Jeu("Joueur 1", "Joueur 2", 1);
        
        System.out.print("PLATEAU DE JEU \n");
        System.out.print("---------------- \n");

		System.out.println(JeuMorpion);

		Random random = new Random();
		
		while(!JeuMorpion.gagner()) {

			X = random.nextInt(3);
			Y = random.nextInt(3);

			JeuMorpion.tabpion(X,Y);
			System.out.println(JeuMorpion);
		}

		if (JeuMorpion.gagner())
			System.out.print("[FIN DE LA PARTIE] \n");
	}

	// Fonction du mode jeu Joueur Contre Ordinateur
	public void jeu3() {
		int X = 0;
		int Y = 0;
		
		System.out.print("---------------- \n");
        System.out.print("JEU DU MORPION \n");
        System.out.print("---------------- \n");
        System.out.print("JOUEUR 1 : 1 \n");
        System.out.print("JOUEUR 2 : 2 \n");
        System.out.print("---------------- \n");
		Jeu JeuMorpion = new Jeu("Joueur 1", "Joueur 2", 1);
        
        System.out.print("PLATEAU DE JEU \n");
        System.out.print("---------------- \n");

		System.out.println(JeuMorpion);

		Random random = new Random();
		
		while(!JeuMorpion.gagner()) {

			if (pion == 1) {
				this.player = joueur1;

				System.out.print("Donner la position X : ");
				X = sc.nextInt();
				System.out.print("Donner la position Y : ");
				Y = sc.nextInt();
				System.out.print("\n");

			} else {

				X = random.nextInt(3);
				Y = random.nextInt(3);

				JeuMorpion.tabpion(X,Y);
				System.out.println(JeuMorpion);

			}

			if (JeuMorpion.gagner())
				System.out.print("[FIN DE LA PARTIE] \n");
		}
	}
}
