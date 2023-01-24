package com.example.projet;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button btn;
    private Button btn2;
    private Button btn3;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btn = findViewById(R.id.btn);
        btn2 = findViewById(R.id.btn2);
        btn3 = findViewById(R.id.btn3);
        btn.setOnClickListener(this);
        btn2.setOnClickListener(this);
        btn3.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        if (view == this.btn) {
            Toast.makeText(this, "LE JEUX DU MEMORY", Toast.LENGTH_SHORT).show();
            Intent Memory = new Intent(MainActivity.this, Memory.class);
            startActivity(Memory);

        } else if (view == this.btn2) {
            Toast.makeText(this, "LE JEUX DE TOUCH BOX", Toast.LENGTH_SHORT).show();
            Intent TouchBox = new Intent(MainActivity.this, RActivity.class);
            startActivity(TouchBox);
        } else if (view == this.btn3) {
            Toast.makeText(this, "LE JEUX D'ANAGRAMME", Toast.LENGTH_SHORT).show();
            Intent Anagramme = new Intent(MainActivity.this, Anagramme.class);
            startActivity(Anagramme);
        }
    }
}