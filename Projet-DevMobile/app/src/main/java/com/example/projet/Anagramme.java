package com.example.projet;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Anagramme extends AppCompatActivity implements View.OnClickListener {

    private Button btnAccueil;

    private TextView rp_info, mot;

    private EditText ecrit_mot;

    private Button btn_verifie, btn_mot;

    Random r;

    String Word;

    String[] dictionnaire = {
            "ordinateur",
            "écran",
            "souris",
            "clavier",
            "logiciel",
            "informatique",
            "google",
            "internet",
            "wifi",
            "connexion",
            "mail",
            "antivirus",
            "application",
            "bios",
            "mémoire",
            "curseur",
            "dossier",
            "fichier",
            "langage",
            "navigateur",
            "processeur",
            "ram",
            "réseau",
            "serveur",

    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_anagramme);

        rp_info = (TextView) findViewById(R.id.rp_info);
        mot = (TextView) findViewById(R.id.mot);

        ecrit_mot = (EditText) findViewById(R.id.ecrit_mot);

        btn_verifie = (Button) findViewById(R.id.btn_verifie);
        btn_mot = (Button) findViewById(R.id.btn_mot);

        btnAccueil = findViewById(R.id.btnAccueil);
        btnAccueil.setOnClickListener(this);

        r = new Random();

        nouveauJeu();

        btn_verifie.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (ecrit_mot.getText().toString().equalsIgnoreCase(Word)) {
                    rp_info.setText("Bien répondu !");
                    btn_verifie.setEnabled(false);
                    btn_mot.setEnabled(true);
                } else {
                    rp_info.setText("Essayez encore !");
                }

            }
        });

        btn_mot.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                nouveauJeu();
            }
        });
    }

    @Override
    public void onClick(View view) {
        if (view == this.btnAccueil) {
            Toast.makeText( this, "PAGE D'ACCUEIL", Toast.LENGTH_SHORT).show();
            Intent myAccueil = new Intent (Anagramme.this, MainActivity.class);
            startActivity(myAccueil);
        }
    }

    private String func_word(String word) {
        List<String> lettres = Arrays.asList(word.split(""));
        Collections.shuffle(lettres);
        String shuffled = "";
        for (String lettre : lettres) {
            shuffled += lettre;
        }
        return shuffled;
    }

    private void nouveauJeu() {
        Word = dictionnaire[r.nextInt(dictionnaire.length)];

        mot.setText(func_word(Word));

        ecrit_mot.setText("");

        btn_mot.setEnabled(false);
        btn_verifie.setEnabled(true);
    }
}