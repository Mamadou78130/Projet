#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




//Fonction pour supprimer le "\n" dans mes recuperations de texte

void supp_enter(char* text){
                    char *positionEntree = NULL;
                    positionEntree = strchr(text, '\n'); // On recherche l'"Entrée"
                    if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
                    {
                        *positionEntree = '\0'; // On remplace ce caractère par \0
                    }
}




// Cette verifie le nombre de contact deja enregistre, et determine une indice pour  le nouveau
int indice_new_contact(){
    int n = 0; 
    while(1){

// On chaque chaque fichier un a un, j'ai le fichier 0.txt, si il existe, je ferme le fichier 
// et j'incremente n += 1, j'ouvre le fichier 1.txt, ainsi de suite, jusqu'a ce que le fichier 
// n.txt n'existe pas, je retourne n, n : nombre de fichier contact dans la base et 
// indice pour le nouveau fichier de contact !

            char fileName[50];
            sprintf(fileName, "%d.txt", n);

            FILE *fichier = fopen(fileName, "r");

            if (fichier == NULL){
                break;
                exit(0);
            }

            if (fichier != NULL){
            fclose(fichier);
            }

           n += 1;
    }

    return n;
}
// Cette verifie le nombre de contact deja enregistre, et determine une indice pour  le nouveau



/*Ma structure de donnees*/
typedef struct
{   
    GtkWidget *frame1;
    GtkWidget *frame2;
    GtkWidget *frame3;
    GtkWidget *hboxMain;
    GtkWidget *hboxMS;
    GtkWidget *vbox1;
    GtkWidget *vbox2;
    GtkWidget *vboxdetail;
    GtkWidget *hbox1;
    GtkWidget *bt_Ajouter_Contact;
    GtkWidget *bt_Modifier_Contact;
    GtkWidget *bt_Supprimer_Contact;
    GtkWidget *bt_contact[20];
    GtkWidget *grille;
    GtkWidget *win;
    GtkWidget *scrolled_window;
    GtkWidget *label_liste_contact;
    GtkWidget *label_nombre_contact;
    GtkWidget *label_select;
    GtkWidget *labelNom;
    GtkWidget *labelPrenom;
    GtkWidget *labelAdresse;
    GtkWidget *labelCp;
    GtkWidget *labelType;
    GtkWidget *labelMail;
    GtkWidget *labelNum;
    GtkWidget *label__Nom;
    GtkWidget *label__Prenom;
    GtkWidget *label__Adresse;
    GtkWidget *label__Cp;
    GtkWidget *label__Type;
    GtkWidget *label__Mail;
    GtkWidget *label__Num;
} WinData;
/*Ma structure de donnees*/






// RECHERCHE


        // Liste des types de contact
        enum {COL_IDD=0, COL_VALL=1};

        gchar* lst_recherche[] = {0};



        // Liste des types de contact

        typedef struct{
            gint    idd;
            gchar*  recherche;
        }DataRecherche;

        typedef struct{
        GtkWidget *combo2;
        }WinDataa;

        WinDataa  wdataa;

// RECHERCHE




/* Fontion qui genere la boite de dialogue*/
    void get_value_dialog(gpointer uData){



// Variables pour recuperer mes entrys
const char* nom;
char nom2[100] = {0};

const char* prenom;
char prenom2[100] = {0};

const char* adresse;
char adresse2[100] = {0};

const char* cp;
char cp2[100] = {0};

gchar* type;
char type2[100] = {0};

const char* mail;
char mail2[100] = {0};

const char* num;
char num2[100] = {0};
// Variables pour recuperer mes entrys




       

        WinData* uWData = uData;
        GtkWidget *lab_pre;
        GtkWidget *entry_pre;
        GtkWidget *lab_nom;
        GtkWidget *entry_nom;
        GtkWidget *lab_adresse;
        GtkWidget *entry_adresse;
        GtkWidget *lab_cp;
        GtkWidget *entry_cp;
        GtkWidget *lab_mail;
        GtkWidget *entry_mail;
        GtkWidget *lab_num;
        GtkWidget *entry_num;
        GtkWidget* diagArea;

        GtkWidget *lab_type;
        GtkWidget *lab_esp;


        // Liste des types de contact
        enum {COL_ID=0, COL_VAL=1};
        gchar* lst_type[] = {"Autre","Pro","Perso"};
        // Liste des types de contact

        typedef struct{
            gint    id;
            gchar*  typec;
        }DataTypec;

        typedef struct{
        GtkWidget *combo;
        }WinData;

        WinData  wdata;
        


// Fonction pour recuperer la valeur selectionnee dans le combo box
void on_get_value(gpointer ptrUserData){
  WinData *uData = ptrUserData;
  GtkTreeIter  iter;
  GtkTreeModel* tmpLst;
  DataTypec selectedData;


  tmpLst = gtk_combo_box_get_model (GTK_COMBO_BOX(uData->combo));
  
  gboolean is_active = gtk_combo_box_get_active_iter (GTK_COMBO_BOX(uData->combo), & iter);
  if(is_active){
    gtk_tree_model_get (tmpLst, &iter, COL_ID , &selectedData.id, COL_VAL, &selectedData.typec, -1);
    gchar print_data[20];
    g_snprintf(print_data, 20, "%s", selectedData.typec);
    type = print_data;
  }
}
// Fonction pour recuperer la valeur selectionnee dans le combo box




  /* ------------------------------------------------------------------------------------*/

  /***************************************
   * Création du modèle pour le combobox 
   ***************************************/
  GtkTreeIter iter;
  GtkListStore *lst = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  
  for (gint i = 0; i< 3 ; i ++){
    DataTypec dTypec;
    dTypec.id = i;
    dTypec.typec = lst_type[i];
    gtk_list_store_append (lst, &iter);
    gtk_list_store_set(lst, &iter, COL_ID, dTypec.id , COL_VAL, dTypec.typec, -1);
  }

  /************************
   * Création du combobox 
   ************************/
  //création du combo
  wdata.combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(lst));


  //création de la seconde colonne 
  GtkCellRenderer * rcell2 = NULL;
  rcell2 = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (wdata.combo), rcell2, FALSE);
  gtk_cell_layout_set_attributes ( GTK_CELL_LAYOUT (wdata.combo), rcell2, "text", 1, NULL);

    gtk_combo_box_set_active (GTK_COMBO_BOX (wdata.combo), 0);

/*------------------------------------------------------------------------------*/




        
        //création de la boite de dialogue
        GtkWidget * diag = gtk_dialog_new_with_buttons("Nouveau contact",
                                GTK_WINDOW(uWData->win),
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                "OK", GTK_RESPONSE_ACCEPT,
                                "Annuler", GTK_RESPONSE_CANCEL,
                                NULL);

        gtk_container_set_border_width (GTK_CONTAINER (diag), 10);
        //récupérer le container de la boite de dialogue
        diagArea = gtk_dialog_get_content_area (GTK_DIALOG (diag));
        gtk_container_set_border_width (GTK_CONTAINER (diagArea), 10);
        
    




        //créeation de champs de saisie 
        lab_pre = gtk_label_new("Prénom *");
        entry_pre = gtk_entry_new();
        
        lab_nom = gtk_label_new("Nom *");
        entry_nom = gtk_entry_new();

        lab_adresse = gtk_label_new("Adresse");
        entry_adresse = gtk_entry_new();

        lab_cp = gtk_label_new("Code Postal");
        entry_cp = gtk_entry_new();
        
        lab_mail = gtk_label_new("E-mail");
        entry_mail = gtk_entry_new();

        lab_num = gtk_label_new("Numéro de téléphone *");
        entry_num = gtk_entry_new();


        lab_type = gtk_label_new("Type de contact");
        lab_esp = gtk_label_new("\nChamps obligatoires :\nNom (2 caracteres min), \nPrenom (2 caracteres min),\nNumero (6 chiffres min)\n\nCliquez sur ANNULER pour fermer la fenetre\n");
        
        


        //ajouter le champs de saisie à boite de dialogue
        gtk_container_add (GTK_CONTAINER (diagArea), lab_pre);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_pre);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_nom);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_nom);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_adresse);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_adresse);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_cp);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_cp);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_mail);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_mail);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_num);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_num);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_type);
        gtk_container_add (GTK_CONTAINER (diagArea), wdata.combo);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_esp);
        
        
        //aficher les éléments de la boite de dialogue
        gtk_widget_show_all (diag);


        // J'initialise les boutons du dial box
        // 1 - Si on clique sur OK et que les champs obligatoires de sont pas remplis,
        // On reboucle sur les bouton, on ne ferme pas la fenetre
        // Quand les champs sont remplis convenablement, on recupere les valeurs et on sort de la boucle
        // 2 - Si on cliquer sur Cancel, on arrete la boucle on ferme la fenetre du dial

        // Concusion

int quit = 1;  
while(quit) {
        // Affciher la boite de dialogue et récupérer la valeur du bouton 
        gint res = gtk_dialog_run(GTK_DIALOG(diag));

        char fileName_n[50];
        switch(res){
        case GTK_RESPONSE_ACCEPT:

            

        if ( strlen (  gtk_entry_get_text(GTK_ENTRY(entry_nom))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_pre))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_num))  ) > 5 ) {

            //récupérer la valeur sasise par l'utilisateur dans la boite de dialogue

            nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
            prenom = gtk_entry_get_text(GTK_ENTRY(entry_pre));
            adresse = gtk_entry_get_text(GTK_ENTRY(entry_adresse));
            cp = gtk_entry_get_text(GTK_ENTRY(entry_cp));
            mail = gtk_entry_get_text(GTK_ENTRY(entry_mail));
            num = gtk_entry_get_text(GTK_ENTRY(entry_num));


            strcpy(nom2, nom);
            strcpy(prenom2, prenom);
            strcpy(adresse2, adresse);
            strcpy(cp2, cp);

            on_get_value(&wdata);
            strcpy(type2, type);

            strcpy(mail2, mail);       
            strcpy(num2, num);  
            
            sprintf(fileName_n, "%d.txt", indice_new_contact());
            FILE *n_fichier = fopen(fileName_n, "w");

            fprintf(n_fichier, "%s\n%s\n%s\n%s\n%s\n%s\n%s", nom2, prenom2, adresse2, cp2, type2, mail2, num2);

            fclose(n_fichier);

            quit = 0;

            gtk_main_quit();
            
        }

        if ( strlen (  gtk_entry_get_text(GTK_ENTRY(entry_nom))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_pre))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_num))  ) > 5 ) {
            gtk_widget_destroy(diag);
            
        }

        break;
        

        case GTK_RESPONSE_CANCEL:
            quit = 0;
            gtk_widget_destroy(diag);
        case GTK_RESPONSE_NONE:
            quit = 0;
            gtk_widget_destroy(diag);
            break;
        }


	}


}
    
/* Fontion qui genere la boite de dialogue*/










/* Fontion qui genere la boite de dialogue*/
    void get_value_dialog2(gpointer uData, int mon_index){


        
                


// Variables pour recuperer mes entrys
const char* nom;
char nom2[100] = {0};

const char* prenom;
char prenom2[100] = {0};

const char* adresse;
char adresse2[100] = {0};

const char* cp;
char cp2[100] = {0};

gchar* type;
char type2[100] = {0};

const char* mail;
char mail2[100] = {0};

const char* num;
char num2[100] = {0};
// Variables pour recuperer mes entrys




       

        WinData* uWData = uData;
        GtkWidget *lab_pre;
        GtkWidget *entry_pre;
        GtkWidget *lab_nom;
        GtkWidget *entry_nom;
        GtkWidget *lab_adresse;
        GtkWidget *entry_adresse;
        GtkWidget *lab_cp;
        GtkWidget *entry_cp;
        GtkWidget *lab_mail;
        GtkWidget *entry_mail;
        GtkWidget *lab_num;
        GtkWidget *entry_num;
        GtkWidget* diagArea;

        GtkWidget *lab_type;
        GtkWidget *lab_esp;


        // Liste des types de contact
        enum {COL_ID=0, COL_VAL=1};
        gchar* lst_type[] = {"Autre","Pro","Perso"};
        // Liste des types de contact

        typedef struct{
            gint    id;
            gchar*  typec;
        }DataTypec;

        typedef struct{
        GtkWidget *combo;
        }WinData;

        WinData  wdata;
        


// Fonction pour recuperer la valeur selectionnee dans le combo box
void on_get_value(gpointer ptrUserData){
  WinData *uData = ptrUserData;
  GtkTreeIter  iter;
  GtkTreeModel* tmpLst;
  DataTypec selectedData;


  tmpLst = gtk_combo_box_get_model (GTK_COMBO_BOX(uData->combo));
  
  gboolean is_active = gtk_combo_box_get_active_iter (GTK_COMBO_BOX(uData->combo), & iter);
  if(is_active){
    gtk_tree_model_get (tmpLst, &iter, COL_ID , &selectedData.id, COL_VAL, &selectedData.typec, -1);
    gchar print_data[20];
    g_snprintf(print_data, 20, "%s", selectedData.typec);
    type = print_data;
  }
}
// Fonction pour recuperer la valeur selectionnee dans le combo box




  /* ------------------------------------------------------------------------------------*/

  /***************************************
   * Création du modèle pour le combobox 
   ***************************************/
  GtkTreeIter iter;
  GtkListStore *lst = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  
  for (gint i = 0; i< 3 ; i ++){
    DataTypec dTypec;
    dTypec.id = i;
    dTypec.typec = lst_type[i];
    gtk_list_store_append (lst, &iter);
    gtk_list_store_set(lst, &iter, COL_ID, dTypec.id , COL_VAL, dTypec.typec, -1);
  }

  /************************
   * Création du combobox 
   ************************/
  //création du combo
  wdata.combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(lst));


  //création de la seconde colonne 
  GtkCellRenderer * rcell2 = NULL;
  rcell2 = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (wdata.combo), rcell2, FALSE);
  gtk_cell_layout_set_attributes ( GTK_CELL_LAYOUT (wdata.combo), rcell2, "text", 1, NULL);


    gtk_combo_box_set_active (GTK_COMBO_BOX (wdata.combo), 0);
/*------------------------------------------------------------------------------*/




        
        //création de la boite de dialogue
        GtkWidget * diag = gtk_dialog_new_with_buttons("Modifier contact",
                                GTK_WINDOW(uWData->win),
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                "OK", GTK_RESPONSE_ACCEPT,
                                "Annuler", GTK_RESPONSE_CANCEL,
                                NULL);

        gtk_container_set_border_width (GTK_CONTAINER (diag), 10);
        //récupérer le container de la boite de dialogue
        diagArea = gtk_dialog_get_content_area (GTK_DIALOG (diag));
        gtk_container_set_border_width (GTK_CONTAINER (diagArea), 10);
        

          

                    signed char Nom_b[256];
                    signed char Prenom_b[256];
                    signed char Adresse_b[256];
                    signed char Cp_b[256];
                    signed char Type_b[256];
                    signed char Mail_b[256];
                    signed char Num_b[256];



                char fileName_b[50];
                
                sprintf(fileName_b, "%d.txt", mon_index - 1);

                FILE *fichier_b = fopen(fileName_b, "r");


                    fgets(Nom_b, 255, fichier_b);
                    supp_enter(Nom_b);
                    fgets(Prenom_b, 255, fichier_b);
                    supp_enter(Prenom_b);
                    fgets(Adresse_b, 255, fichier_b);
                    supp_enter(Adresse_b);
                    fgets(Cp_b, 255, fichier_b);
                    supp_enter(Cp_b);
                    fgets(Type_b, 255, fichier_b);
                    supp_enter(Type_b);
                    fgets(Mail_b, 255, fichier_b);
                    supp_enter(Mail_b);
                    fgets(Num_b, 255, fichier_b);
                    supp_enter(Num_b);

                fclose(fichier_b);




// On recupere les donnes du fichier qui doit etre modifier et on pre-remplie les entry avec des buffers





        GtkEntryBuffer * buff_nom;
        buff_nom = gtk_entry_buffer_new (Nom_b, -1);

        GtkEntryBuffer * buff_prenom;
        buff_prenom = gtk_entry_buffer_new (Prenom_b, -1);

        GtkEntryBuffer * buff_adresse;
        buff_adresse = gtk_entry_buffer_new (Adresse_b, -1);

        GtkEntryBuffer * buff_cp;
        buff_cp = gtk_entry_buffer_new (Cp_b, -1);

        GtkEntryBuffer * buff_type;
        buff_type = gtk_entry_buffer_new (Type_b, -1);

        GtkEntryBuffer * buff_mail;
        buff_mail = gtk_entry_buffer_new (Mail_b, -1);

        GtkEntryBuffer * buff_num;
        buff_num = gtk_entry_buffer_new (Num_b, -1);



        //créeation de champs de saisie 
        lab_pre = gtk_label_new("Prénom *");
        entry_pre = gtk_entry_new_with_buffer (buff_prenom);
        
        lab_nom = gtk_label_new("Nom *");
        entry_nom = gtk_entry_new_with_buffer (buff_nom);

        lab_adresse = gtk_label_new("Adresse");
        entry_adresse = gtk_entry_new_with_buffer (buff_adresse);

        lab_cp = gtk_label_new("Code Postal");
        entry_cp = gtk_entry_new_with_buffer (buff_cp);
        
        lab_mail = gtk_label_new("E-mail");
        entry_mail = gtk_entry_new_with_buffer (buff_mail);

        lab_num = gtk_label_new("Numéro de téléphone *");
        entry_num = gtk_entry_new_with_buffer (buff_num);


        lab_type = gtk_label_new("Type de contact");
        lab_esp = gtk_label_new("       ");
        lab_esp = gtk_label_new("\nChamps obligatoires :\nNom (2 caracteres min), \nPrenom (2 caracteres min),\nNumero (6 chiffres min)\n\nCliquez sur ANNULER pour fermer la fenetre\n");
        
        


        //ajouter le champs de saisie à boite de dialogue
        gtk_container_add (GTK_CONTAINER (diagArea), lab_pre);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_pre);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_nom);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_nom);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_adresse);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_adresse);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_cp);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_cp);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_mail);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_mail);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_num);
        gtk_container_add (GTK_CONTAINER (diagArea), entry_num);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_type);
        gtk_container_add (GTK_CONTAINER (diagArea), wdata.combo);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_esp);
        
        
        //aficher les éléments de la boite de dialogue
        gtk_widget_show_all (diag);



        
   int quit = 1;  
while(quit) {
        // Affciher la boite de dialogue et récupérer la valeur du bouton 
        gint res = gtk_dialog_run(GTK_DIALOG(diag));

        char fileName_n[50];
        switch(res){
        case GTK_RESPONSE_ACCEPT:

            

        if ( strlen (  gtk_entry_get_text(GTK_ENTRY(entry_nom))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_pre))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_num))  ) > 5 ) {

            //récupérer la valeur sasise par l'utilisateur dans la boite de dialogue

            nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
            prenom = gtk_entry_get_text(GTK_ENTRY(entry_pre));
            adresse = gtk_entry_get_text(GTK_ENTRY(entry_adresse));
            cp = gtk_entry_get_text(GTK_ENTRY(entry_cp));
            mail = gtk_entry_get_text(GTK_ENTRY(entry_mail));
            num = gtk_entry_get_text(GTK_ENTRY(entry_num));


            strcpy(nom2, nom);
            strcpy(prenom2, prenom);
            strcpy(adresse2, adresse);
            strcpy(cp2, cp);

            on_get_value(&wdata);
            strcpy(type2, type);

            strcpy(mail2, mail);       
            strcpy(num2, num);  

            remove(fileName_b);
            
            sprintf(fileName_n, "%d.txt", mon_index - 1);
            FILE *n_fichier = fopen(fileName_n, "w");

            fprintf(n_fichier, "%s\n%s\n%s\n%s\n%s\n%s\n%s", nom2, prenom2, adresse2, cp2, type2, mail2, num2);

            fclose(n_fichier);

            quit = 0;

            gtk_main_quit();
            
        }

        if ( strlen (  gtk_entry_get_text(GTK_ENTRY(entry_nom))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_pre))  ) > 1 && strlen(  gtk_entry_get_text(GTK_ENTRY(entry_num))  ) > 5 ) {
            gtk_widget_destroy(diag);
            
        }

        break;
        

        case GTK_RESPONSE_CANCEL:
            quit = 0;
            gtk_widget_destroy(diag);
        case GTK_RESPONSE_NONE:
            quit = 0;
            gtk_widget_destroy(diag);
            break;
        }


	}


}
    
/* Fontion qui genere la boite de dialogue*/









// Fonction pour replacer mes fichiers apres suppression

void replacer_fichier(int mon_index) {

    // Je lis le fichier qui se trouve apres le fichier qui vient d'etre supprimer
    // Je recupere les donnees de cette derniere, je le supprime et je recree un nouveau fichier avec les donnes
    // du fichier que je viens de supprimer dans la place du fichier supprimer bien avant

    const int quantite_contact = indice_new_contact();

    for(mon_index; mon_index < quantite_contact; mon_index++) {

                    char Nom_rec[256];
                    char Prenom_rec[256];
                    char Adresse_rec[256];
                    char Cp_rec[256];
                    char Type_rec[256];
                    char Mail_rec[256];
                    char Num_rec[256];



                char fileName_rec[50];
                
                sprintf(fileName_rec, "%d.txt", mon_index);

                FILE *fichier_rec = fopen(fileName_rec, "r");

                    fgets(Nom_rec, 255, fichier_rec);
                    supp_enter(Nom_rec);
                    fgets(Prenom_rec, 255, fichier_rec);
                    supp_enter(Prenom_rec);
                    fgets(Adresse_rec, 255, fichier_rec);
                    supp_enter(Adresse_rec);
                    fgets(Cp_rec, 255, fichier_rec);
                    supp_enter(Cp_rec);
                    fgets(Type_rec, 255, fichier_rec);
                    supp_enter(Type_rec);
                    fgets(Mail_rec, 255, fichier_rec);
                    supp_enter(Mail_rec);
                    fgets(Num_rec, 255, fichier_rec);
                    supp_enter(Num_rec);


                fclose(fichier_rec);

        if ( remove(fileName_rec) == 0) {
                char fileName_print[50];

                sprintf(fileName_print, "%d.txt", mon_index - 1);
                FILE *print_fichier = fopen(fileName_print, "w");

                fprintf(print_fichier, "%s\n%s\n%s\n%s\n%s\n%s\n%s", Nom_rec, Prenom_rec, Adresse_rec, Cp_rec, Type_rec, Mail_rec, Num_rec);

                fclose(print_fichier);
        }


    }



}

// Fonction pour replacer mes fichiers apres suppression







/* Fontion qui genere la boite de dialogue*/
    void get_value_dialog3(gpointer uData, int mon_index){




       

        WinData* uWData = uData;
        GtkWidget *lab_notice;
        GtkWidget *lab_contact;
        GtkWidget* diagArea;

        WinData  wdata;




        
        //création de la boite de dialogue
        GtkWidget * diag = gtk_dialog_new_with_buttons("Modifier contact",
                                GTK_WINDOW(uWData->win),
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                "SUPPRIMER", GTK_RESPONSE_ACCEPT,
                                "Annuler", GTK_RESPONSE_CANCEL,
                                NULL);

        gtk_container_set_border_width (GTK_CONTAINER (diag), 10);
        //récupérer le container de la boite de dialogue
        diagArea = gtk_dialog_get_content_area (GTK_DIALOG (diag));
        gtk_container_set_border_width (GTK_CONTAINER (diagArea), 10);
        

        // Je supprime le fichier avec l'indice du contact affiche dans le combo
          
                signed char Prenom_b[256];
                signed char Nom_b[256];



                char fileName_b[50];
                
                sprintf(fileName_b, "%d.txt", mon_index - 1);

                FILE *fichier_b = fopen(fileName_b, "r");


                    fgets(Nom_b, 255, fichier_b);
                    fgets(Prenom_b, 255, fichier_b);

                fclose(fichier_b);



        //créeation de champs de saisie 
        lab_notice = gtk_label_new("Confirmer la suppression de :\n");
        lab_contact = gtk_label_new(Prenom_b);
        


        //ajouter le champs de saisie à boite de dialogue
        gtk_container_add (GTK_CONTAINER (diagArea), lab_notice);
        gtk_container_add (GTK_CONTAINER (diagArea), lab_contact);
        
        //aficher les éléments de la boite de dialogue
        gtk_widget_show_all (diag);

        

        // Affciher la boite de dialogue et récupérer la valeur du bouton 
        gint res = gtk_dialog_run(GTK_DIALOG(diag));

        char fileName_supp[50];

        switch(res){
        case GTK_RESPONSE_ACCEPT:

            
            sprintf(fileName_supp, "%d.txt", mon_index - 1);
            replacer_fichier(mon_index);
            gtk_main_quit();
            

        break;
        

        case GTK_RESPONSE_CANCEL:
        case GTK_RESPONSE_NONE:
            break;
        }


	gtk_widget_destroy(diag);


}
    
/* Fontion qui genere la boite de dialogue*/










int main (int argc, char* argv[]){




WinData windata;






// Fontion pour le design
void load_css (void) {

  GtkStyleContext *contextvbox2;
  contextvbox2 = gtk_widget_get_style_context (windata.vbox2);
  gtk_style_context_add_class(contextvbox2, "vbox2");
  GtkCssProvider *providervbox2 = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providervbox2, "style.css", NULL);
  gtk_style_context_add_provider (contextvbox2, GTK_STYLE_PROVIDER(providervbox2), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextbuttAC;
  contextbuttAC = gtk_widget_get_style_context (windata.bt_Ajouter_Contact);
  gtk_style_context_add_class(contextbuttAC, "bt_Ajouter_Contact");
  GtkCssProvider *providerbuttAC = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerbuttAC, "style.css", NULL);
  gtk_style_context_add_provider (contextbuttAC, GTK_STYLE_PROVIDER(providerbuttAC), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextbuttMC;
  contextbuttMC = gtk_widget_get_style_context (windata.bt_Modifier_Contact);
  gtk_style_context_add_class(contextbuttMC, "bt_Modifier_Contact");
  GtkCssProvider *providerbuttMC = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerbuttMC, "style.css", NULL);
  gtk_style_context_add_provider (contextbuttMC, GTK_STYLE_PROVIDER(providerbuttMC), GTK_STYLE_PROVIDER_PRIORITY_USER);


  GtkStyleContext *contextbuttSC;
  contextbuttSC = gtk_widget_get_style_context (windata.bt_Supprimer_Contact);
  gtk_style_context_add_class(contextbuttSC, "bt_Supprimer_Contact");
  GtkCssProvider *providerbuttSC = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerbuttSC, "style.css", NULL);
  gtk_style_context_add_provider (contextbuttSC, GTK_STYLE_PROVIDER(providerbuttSC), GTK_STYLE_PROVIDER_PRIORITY_USER);


  GtkStyleContext *contextlabelNom;
  contextlabelNom = gtk_widget_get_style_context (windata.labelNom);
  gtk_style_context_add_class(contextlabelNom, "labelNom");
  GtkCssProvider *providerlabelNom = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabelNom, "style.css", NULL);
  gtk_style_context_add_provider (contextlabelNom, GTK_STYLE_PROVIDER(providerlabelNom), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabelPrenom;
  contextlabelPrenom = gtk_widget_get_style_context (windata.labelPrenom);
  gtk_style_context_add_class(contextlabelPrenom, "labelPrenom");
  GtkCssProvider *providerlabelPrenom = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabelPrenom, "style.css", NULL);
  gtk_style_context_add_provider (contextlabelPrenom, GTK_STYLE_PROVIDER(providerlabelPrenom), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabelAdresse;
  contextlabelAdresse = gtk_widget_get_style_context (windata.labelAdresse);
  gtk_style_context_add_class(contextlabelAdresse, "labelAdresse");
  GtkCssProvider *providerlabelAdresse = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabelAdresse, "style.css", NULL);
  gtk_style_context_add_provider (contextlabelAdresse, GTK_STYLE_PROVIDER(providerlabelAdresse), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabelCp;
  contextlabelCp = gtk_widget_get_style_context (windata.labelCp);
  gtk_style_context_add_class(contextlabelCp, "labelCp");
  GtkCssProvider *providerlabelCp = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabelCp, "style.css", NULL);
  gtk_style_context_add_provider (contextlabelCp, GTK_STYLE_PROVIDER(providerlabelCp), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabelType;
  contextlabelType = gtk_widget_get_style_context (windata.labelType);
  gtk_style_context_add_class(contextlabelType, "labelType");
  GtkCssProvider *providerlabelType = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabelType, "style.css", NULL);
  gtk_style_context_add_provider (contextlabelType, GTK_STYLE_PROVIDER(providerlabelType), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabelMail;
  contextlabelMail = gtk_widget_get_style_context (windata.labelMail);
  gtk_style_context_add_class(contextlabelMail, "labelMail");
  GtkCssProvider *providerlabelMail = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabelMail, "style.css", NULL);
  gtk_style_context_add_provider (contextlabelMail, GTK_STYLE_PROVIDER(providerlabelMail), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabelNum;
  contextlabelNum = gtk_widget_get_style_context (windata.labelNum);
  gtk_style_context_add_class(contextlabelNum, "labelNum");
  GtkCssProvider *providerlabelNum = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabelNum, "style.css", NULL);
  gtk_style_context_add_provider (contextlabelNum, GTK_STYLE_PROVIDER(providerlabelNum), GTK_STYLE_PROVIDER_PRIORITY_USER);


  GtkStyleContext *contextlabel__Nom;
  contextlabel__Nom = gtk_widget_get_style_context (windata.label__Nom);
  gtk_style_context_add_class(contextlabel__Nom, "label__Nom");
  GtkCssProvider *providerlabel__Nom = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabel__Nom, "style.css", NULL);
  gtk_style_context_add_provider (contextlabel__Nom, GTK_STYLE_PROVIDER(providerlabel__Nom), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabel__Prenom;
  contextlabel__Prenom = gtk_widget_get_style_context (windata.label__Prenom);
  gtk_style_context_add_class(contextlabel__Prenom, "label__Prenom");
  GtkCssProvider *providerlabel__Prenom = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabel__Prenom, "style.css", NULL);
  gtk_style_context_add_provider (contextlabel__Prenom, GTK_STYLE_PROVIDER(providerlabel__Prenom), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabel__Adresse;
  contextlabel__Adresse = gtk_widget_get_style_context (windata.label__Adresse);
  gtk_style_context_add_class(contextlabel__Adresse, "label__Adresse");
  GtkCssProvider *providerlabel__Adresse = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabel__Adresse, "style.css", NULL);
  gtk_style_context_add_provider (contextlabel__Adresse, GTK_STYLE_PROVIDER(providerlabel__Adresse), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabel__Cp;
  contextlabel__Cp = gtk_widget_get_style_context (windata.label__Cp);
  gtk_style_context_add_class(contextlabel__Cp, "label__Cp");
  GtkCssProvider *providerlabel__Cp = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabel__Cp, "style.css", NULL);
  gtk_style_context_add_provider (contextlabel__Cp, GTK_STYLE_PROVIDER(providerlabel__Cp), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabel__Type;
  contextlabel__Type = gtk_widget_get_style_context (windata.label__Type);
  gtk_style_context_add_class(contextlabel__Type, "label__Type");
  GtkCssProvider *providerlabel__Type = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabel__Type, "style.css", NULL);
  gtk_style_context_add_provider (contextlabel__Type, GTK_STYLE_PROVIDER(providerlabel__Type), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabel__Mail;
  contextlabel__Mail = gtk_widget_get_style_context (windata.label__Mail);
  gtk_style_context_add_class(contextlabel__Mail, "label_Mail");
  GtkCssProvider *providerlabel__Mail = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabel__Mail, "style.css", NULL);
  gtk_style_context_add_provider (contextlabel__Mail, GTK_STYLE_PROVIDER(providerlabel__Mail), GTK_STYLE_PROVIDER_PRIORITY_USER);

  GtkStyleContext *contextlabel__Num;
  contextlabel__Num = gtk_widget_get_style_context (windata.label__Num);
  gtk_style_context_add_class(contextlabel__Num, "label__Num");
  GtkCssProvider *providerlabel__Num = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (providerlabel__Num, "style.css", NULL);
  gtk_style_context_add_provider (contextlabel__Num, GTK_STYLE_PROVIDER(providerlabel__Num), GTK_STYLE_PROVIDER_PRIORITY_USER);



}
// Fontion pour le design






// Fonction pour affichier les details de chaque contact 

    void afficher_contact(GtkWidget *pWidget, gpointer user_data)
    {

        int n = 0;
        while (n < indice_new_contact()) {
            if ( windata.bt_contact[n] == pWidget) {

                char fileName[50];
                
                sprintf(fileName, "%d.txt", n);

                FILE *fichier = fopen(fileName, "r");

                if (fichier == NULL){
                    exit(0);
                }

                    signed char Nom[256];
                    signed char Prenom[256];
                    signed char Adresse[256];
                    signed char Cp[256];
                    signed char Type[256];
                    signed char Mail[256];
                    signed char Num[256];

                    fgets(Nom, 255, fichier);
                    supp_enter(Nom);
                    fgets(Prenom, 255, fichier);
                    supp_enter(Prenom);
                    fgets(Adresse, 255, fichier);
                    supp_enter(Adresse);
                    fgets(Cp, 255, fichier);
                    supp_enter(Cp);
                    fgets(Type, 255, fichier);
                    supp_enter(Type);
                    fgets(Mail, 255, fichier);
                    supp_enter(Mail);
                    fgets(Num, 255, fichier);
                    supp_enter(Num);

                    gtk_label_set_text(GTK_LABEL(windata.label__Nom), Nom);
                    gtk_label_set_text(GTK_LABEL(windata.label__Prenom), Prenom);
                    gtk_label_set_text(GTK_LABEL(windata.label__Adresse), Adresse);
                    gtk_label_set_text(GTK_LABEL(windata.label__Cp), Cp);
                    gtk_label_set_text(GTK_LABEL(windata.label__Type), Type);
                    gtk_label_set_text(GTK_LABEL(windata.label__Mail), Mail);
                    gtk_label_set_text(GTK_LABEL(windata.label__Num), Num);

                    break;

                if (fichier != NULL){
                fclose(fichier);
                }                

            }
            else{
                n += 1;
            }
        }
    }
// Fonction pour affichier les details de chaque contact 



 

while (1){

    int quitter = 0;

    void main_quitter() {
        quitter = 1;
    }

    // Creation de la Fenetre
    gtk_init(&argc, &argv);
    windata.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(windata.win), "Contact");
    gtk_window_resize(GTK_WINDOW(windata.win), 1200,800);
    gtk_window_set_position(GTK_WINDOW(windata.win), GTK_WIN_POS_CENTER);
    // Fenetre


  //vscrollbar
  windata.scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(windata.scrolled_window), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
  gtk_widget_set_size_request(windata.scrolled_window, 100, 430);
  

    /*Creation des widgets*/
        windata.label_liste_contact = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(windata.label_liste_contact), "<b>La liste des contacts</b>");

        windata.label_nombre_contact = gtk_label_new(NULL);
        char lab_nb_ct[50];
        sprintf(lab_nb_ct, "<b>Nombre de contact : %d</b>", indice_new_contact());
        gtk_label_set_markup(GTK_LABEL(windata.label_nombre_contact), lab_nb_ct);

        windata.hboxMain = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20); /* Hbox principal*/
        windata.frame1 = gtk_frame_new("   MES CONTACTS  ");  /*Frame pour gerer les contacts*/
        windata.frame2 = gtk_frame_new("   DETAILS   "); /*Frame pour afficher les details des contacts*/
        windata.frame3 = gtk_frame_new(NULL);
        windata.vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); /*Vbox principal du frame1*/
        windata.vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
        windata.vboxdetail = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
        windata.hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        windata.hboxMS = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
        
        char *labelo = "Ajouter un contact";
        windata.bt_Ajouter_Contact  = gtk_button_new_with_label (labelo); /*Le bouton pour ajouter un contact*/

        windata.bt_Modifier_Contact  = gtk_button_new_with_label ("Modifer"); /*Le bouton pour Modifier un contact*/

        windata.bt_Supprimer_Contact  = gtk_button_new_with_label ("Supprimer"); /*Le bouton pour Supp un contact*/

        windata.label_select = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(windata.label_select), "<b>Selectionner un contact pour le Modifier/Supprimer</b>");










        int b = 0;
        while (b < indice_new_contact() + 2) {
            
            if (b == 0){

                lst_recherche[b] = "Rechercher un contact";

            }

            else {

                int c = b - 1;

                char fileName[50];
                sprintf(fileName, "%d.txt", c);
                FILE *fichier = fopen(fileName, "r");

                if (fichier == NULL){
                    break;
                    exit(0);
                }

                signed char texte[256];
                signed char texte2[256];

                fscanf(fichier, "%s\n%s", texte2, texte);

                gchar *labc = g_strdup_printf("%s %s", texte, texte2);

                lst_recherche[b] = labc;

                if (fichier != NULL){
                fclose(fichier);

                }

                
            } 

            b += 1;
        }



  /* ------------------------------------------------------------------------------------*/

  /***************************************
   * Création du modèle pour le combobox RECHERCHE 
   ***************************************/
  GtkTreeIter iterr;
  GtkListStore *lstt = gtk_list_store_new(2, G_TYPE_INT, G_TYPE_STRING);
  
  for (gint i = 0; i< indice_new_contact() + 1 ; i ++){
    DataRecherche dRecherche;
    dRecherche.idd = i;
    dRecherche.recherche = lst_recherche[i];
    gtk_list_store_append (lstt, &iterr);
    gtk_list_store_set(lstt, &iterr, COL_IDD, dRecherche.idd , COL_VALL, dRecherche.recherche, -1);
  }

  /************************
   * Création du combobox RECHERCHE
   ************************/
  //création du combo
  wdataa.combo2 = gtk_combo_box_new_with_model(GTK_TREE_MODEL(lstt));


  //création de la seconde colonne 
  GtkCellRenderer * rcell22 = NULL;
  rcell22 = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (wdataa.combo2), rcell22, FALSE);
  gtk_cell_layout_set_attributes ( GTK_CELL_LAYOUT (wdataa.combo2), rcell22, "text", 1, NULL);

  gtk_combo_box_set_active (GTK_COMBO_BOX (wdataa.combo2), 0);


/*------------------------------------------------------------------------------*/







// Fonction pour recuperer la valeur selectionnee dans le combo box
int on_get_value2(gpointer ptrUserData){

          typedef struct{
            gint    id;
            gchar*  typec;
        }DataTypec;
  WinData *uData = ptrUserData;
  GtkTreeIter  iter;
  GtkTreeModel* tmpLst;
  DataTypec selectedData;


  tmpLst = gtk_combo_box_get_model (GTK_COMBO_BOX(wdataa.combo2));
  
  gboolean is_active = gtk_combo_box_get_active_iter (GTK_COMBO_BOX(wdataa.combo2), & iter);
  if(is_active){
    gtk_tree_model_get (tmpLst, &iter, COL_IDD , &selectedData.id, COL_VALL, &selectedData.typec, -1);

  }

  return selectedData.id;
  
}
// Fonction pour recuperer la valeur selectionnee dans le combo box











void dialg_mod(void){

    if (on_get_value2(&wdataa) != 0) {
        get_value_dialog2(&windata, on_get_value2(&wdataa) ); 
    }

}


void dialg_mod2(void){

    if (on_get_value2(&wdataa) != 0) {
        get_value_dialog3(&windata, on_get_value2(&wdataa) ); 
    }

}












        g_signal_connect (G_OBJECT(windata.bt_Ajouter_Contact),"clicked",G_CALLBACK(get_value_dialog) ,&windata);

        g_signal_connect (G_OBJECT(windata.bt_Modifier_Contact),"clicked",G_CALLBACK(dialg_mod), NULL);

        g_signal_connect (G_OBJECT(windata.bt_Supprimer_Contact),"clicked",G_CALLBACK(dialg_mod2), NULL);


        windata.grille = gtk_grid_new(); /*Grille qui affiche les contacts*/
        
        windata.labelNom = gtk_label_new("Nom");
        windata.labelPrenom = gtk_label_new("Prenom");
        windata.labelAdresse = gtk_label_new("Adresse");
        windata.labelCp = gtk_label_new("Code postal");
        windata.labelType = gtk_label_new("Type de contact");
        windata.labelMail = gtk_label_new("email");
        windata.labelNum = gtk_label_new("Numero");

        windata.label__Nom = gtk_label_new("--");
        windata.label__Prenom = gtk_label_new("--");
        windata.label__Adresse = gtk_label_new("--");
        windata.label__Cp = gtk_label_new("--");
        windata.label__Type = gtk_label_new("--");
        windata.label__Mail = gtk_label_new("--");
        windata.label__Num = gtk_label_new("--");


        /*Cretion des boutons des contacts*/

        int m = 0;
        while (1) {

            char fileName[50];
            sprintf(fileName, "%d.txt", m);
            FILE *fichier = fopen(fileName, "r");

            if (fichier == NULL){
                break;
                exit(0);
            }

            signed char texte[256];
            signed char texte2[256];

            fscanf(fichier, "%s\n%s", texte, texte2);

            supp_enter(texte);
            supp_enter(texte2);

            gchar *lab = g_strdup_printf("%s %s", texte, texte2);
            windata.bt_contact[m] = gtk_button_new_with_label (lab);
            gtk_widget_set_size_request(windata.bt_contact[m], 450, 100);            

            if (fichier != NULL){
            fclose(fichier);
            }

           m += 1;
        }

        /*Cretion des boutons des contacts*/
    /*Creation des widgets*/

load_css();

    // Inclusion de Widgets dans Widgets
        gtk_container_add(GTK_CONTAINER(windata.win), windata.hboxMain);
        gtk_container_add(GTK_CONTAINER(windata.hboxMain), windata.frame1);
        gtk_container_add(GTK_CONTAINER(windata.hboxMain), windata.frame2);
        gtk_container_add(GTK_CONTAINER(windata.frame1), windata.vbox1);
        gtk_container_add(GTK_CONTAINER(windata.hbox1), windata.label_nombre_contact);  
        gtk_container_add(GTK_CONTAINER(windata.hbox1), windata.bt_Ajouter_Contact);
        gtk_container_add(GTK_CONTAINER(windata.vbox1), windata.hbox1);
        gtk_container_add(GTK_CONTAINER(windata.vbox1), windata.label_liste_contact);
        gtk_container_add(GTK_CONTAINER(windata.vbox1), windata.vbox2);
        gtk_container_add(GTK_CONTAINER(windata.vbox1), wdataa.combo2);
        gtk_container_add(GTK_CONTAINER(windata.vbox1), windata.hboxMS);
        gtk_container_add(GTK_CONTAINER(windata.vbox1), windata.label_select);
        gtk_container_add(GTK_CONTAINER(windata.vbox2), windata.frame3);
        gtk_container_add(GTK_CONTAINER(windata.frame3), windata.scrolled_window);
        gtk_container_add(GTK_CONTAINER(windata.scrolled_window), windata.grille);
        gtk_container_add(GTK_CONTAINER(windata.frame2), windata.vboxdetail);
        gtk_container_add(GTK_CONTAINER(windata.hboxMS), windata.bt_Modifier_Contact);
        gtk_container_add(GTK_CONTAINER(windata.hboxMS), windata.bt_Supprimer_Contact);

        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.labelNom);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.label__Nom);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.labelPrenom);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.label__Prenom);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.labelAdresse);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.label__Adresse);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.labelCp);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.label__Cp);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.labelType);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.label__Type);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.labelMail);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.label__Mail);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.labelNum);
        gtk_container_add(GTK_CONTAINER(windata.vboxdetail), windata.label__Num);


        int n = 0;
        while (1) {

            char fileName[50];
            
            sprintf(fileName, "%d.txt", n);

            FILE *fichier = fopen(fileName, "r");

            if (fichier == NULL){
                break;
                exit(0);
            }

            gtk_grid_attach (GTK_GRID(windata.grille), windata.bt_contact[n] , 0, n, 1, 1);

           g_signal_connect (G_OBJECT (windata.bt_contact[n]), "clicked", G_CALLBACK (afficher_contact), NULL);

            if (fichier != NULL){
            fclose(fichier);
            }

           n += 1;
        }


    // Inclusion Widgets


    // Margin all
        gtk_widget_set_margin_top (windata.hboxMain,10);
        gtk_widget_set_margin_start (windata.hboxMain,10);
        gtk_widget_set_margin_end (windata.hboxMain,10);
        gtk_widget_set_margin_bottom (windata.hboxMain,10);
        gtk_widget_set_margin_end (windata.label_nombre_contact,20);
        gtk_widget_set_margin_start (windata.label_nombre_contact,50);
        gtk_widget_set_margin_start (windata.bt_Modifier_Contact,120);
        gtk_widget_set_margin_start (wdataa.combo2,60);
        gtk_widget_set_margin_end (wdataa.combo2,60);
        gtk_widget_set_margin_top (wdataa.combo2,20);
        gtk_widget_set_margin_top (windata.hbox1,20);
        gtk_widget_set_margin_top (windata.vboxdetail,30);
    // Margin all


    gtk_widget_set_size_request(windata.frame2, 720, 750);

    gtk_widget_set_size_request(windata.frame1, 450, 750);

    g_signal_connect (G_OBJECT (windata.win), "clicked", G_CALLBACK (main_quitter), NULL);
    
    

    if (quitter == 1) {
        break;
        gtk_main_quit();
    }
    
    gtk_widget_show_all(windata.win);
    gtk_main();

    }
    
    
    return EXIT_SUCCESS;
    
  }
