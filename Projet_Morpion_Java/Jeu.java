import java.util.*;

public class Jeu {

	static Scanner sc = new Scanner(System.in);
	public String joueur1;
	public String joueur2;
	// Joueur1 si 1 et Joueur2 si 2
	public int pion;
	public String player;
	public String[][] plateau;
	public boolean gagner = false;

	public Jeu(String joueur1, String joueur2, int n) {
		plateau = new String[3][3];
	
		this.player = this.joueur1 = joueur1;
		this.joueur2 = joueur2;
		this.pion = n;
		
		this.jeu();
	}

	public void jeu() {
		for(int i = 0; i < this.plateau.length; i++)
			for(int j = 0; j < this.plateau[0].length; j++)
				plateau[i][j] = "0";
      
      this.gagner = false;
	}
	// 	Fonction pour placer un pion
	public void tabpion(int X, int Y) {
		if(plateau[X][Y].equals("0")) {
			plateau[X][Y] = Integer.toString(this.pion); 
			this.gagner = this.gagner();
			if(this.gagner != true) 
			this.moveplayer();
		}

		if (this.gagner == true) {
			if(pion == 1) {
				this.player = joueur1; 
				System.out.println("[JOUEUR 1 A GAGNE]");
			} else {
				System.out.println("[JOUEUR 2 A GAGNE]");
			}
		}
	}

	// Fonction pour changer de joueur
	public void moveplayer() {
		if(pion == 1) {
			this.player = joueur2; 
			pion = 2;
		} else {
			this.player = joueur1; 
			pion = 1;
		}
	}
	
	public boolean gagner() {
		int i, j;
		i = 0;
		j = 0;
	
		// Test horizontal
		for(i = 0; i < this.plateau.length; i++) {
			if(plateau[i][j].equals("1") && plateau[i][j+1].equals("1") && plateau[i][j+2].equals("1")) return true;
			if(plateau[i][j].equals("2") && plateau[i][j+1].equals("2") && plateau[i][j+2].equals("2")) return true;
		}
		
		i = 0;
		j = 0;
		//Test vertical
		for(j = 0; j < this.plateau[0].length; j++) {
			if(plateau[i][j].equals("1") && plateau[i+1][j].equals("1") && plateau[i+2][j].equals("1") ) return true;
			if(plateau[i][j].equals("2") && plateau[i+1][j].equals("2") && plateau[i+2][j].equals("2") ) return true;
		}
		
		i = 0;
		j = 0;
		//Test diagonal droit
		if(plateau[i][j].equals("1") && plateau[i+1][j+1].equals("1") && plateau[i+2][j+2].equals("1") ) return true;
		if(plateau[i][j].equals("2") && plateau[i+1][j+1].equals("2") && plateau[i+2][j+2].equals("2") ) return true;
	
		i = 0;
		j = 2;
		//Test diagonal gauche
		if(plateau[i][j].equals("1") && plateau[i+1][j-1].equals("1") && plateau[i+2][j-2].equals("1") ) return true;
		if(plateau[i][j].equals("2") && plateau[i+1][j-1].equals("2") && plateau[i+2][j-2].equals("2") ) return true;
		
		return false;
	}
	
	public boolean remplie() {
		int nb = 0;
		
		for(int i = 0; i < this.plateau.length; i++)
			for(int j = 0;j < this.plateau[0].length; j++)
				if(!plateau[i][j].equals("0")) 
				nb++;
	
		if(nb == 9) 
		return true;
		return false;
	}
	// Méthode toString
	public String toString() {
		String str = this.player + " ---> " + (this.pion == 1 ? "Le joueur 1 doit jouer ":"Le joueur 2 doit jouer ") + "\n";
		
		for(int i = 0; i < this.plateau.length; i++) {	
			str += "\n" + "";
		
			for(int j = 0; j < this.plateau[0].length; j++) {
				str += " [ ";
				if(!plateau[i][j].equals("0"))
					str += plateau[i][j] + " ] ";
				else
					str += " " + " ] ";
			}
		}
		
		str += "\n";
	
		return str;
	}
}