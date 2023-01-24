package com.example.projet;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import java.util.Arrays;
import java.util.Collections;

public class Memory extends AppCompatActivity implements View.OnClickListener {

    private Button btnAccueil;

    ImageView b_1, b_2, b_3, b_4, b_5, b_6, b_7, b_8, b_9, b_10, b_11, b_12,
            b_13, b_14, b_15, b_16, b_17, b_18, b_19, b_20, b_21, b_22, b_23, b_24;

    Integer[] tab_carte = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,
                            201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212};

    int carte1, carte2, carte3, carte4, carte5, carte6, carte7, carte8, carte9, carte10, carte11, carte12,
            carte13, carte14, carte15, carte16, carte17, carte18, carte19, carte20, carte21, carte22, carte23, carte24;

    int first_carte, second_carte;
    int clic_first, clic_second;
    int num_carte = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_memory);

        b_1 = (ImageView) findViewById(R.id.b_1);
        b_2 = (ImageView) findViewById(R.id.b_2);
        b_3 = (ImageView) findViewById(R.id.b_3);
        b_4 = (ImageView) findViewById(R.id.b_4);
        b_5 = (ImageView) findViewById(R.id.b_5);
        b_6 = (ImageView) findViewById(R.id.b_6);
        b_7 = (ImageView) findViewById(R.id.b_7);
        b_8 = (ImageView) findViewById(R.id.b_8);
        b_9 = (ImageView) findViewById(R.id.b_9);
        b_10 = (ImageView) findViewById(R.id.b_10);
        b_11 = (ImageView) findViewById(R.id.b_11);
        b_12 = (ImageView) findViewById(R.id.b_12);
        b_13 = (ImageView) findViewById(R.id.b_13);
        b_14 = (ImageView) findViewById(R.id.b_14);
        b_15 = (ImageView) findViewById(R.id.b_15);
        b_16 = (ImageView) findViewById(R.id.b_16);
        b_17 = (ImageView) findViewById(R.id.b_17);
        b_18 = (ImageView) findViewById(R.id.b_18);
        b_19 = (ImageView) findViewById(R.id.b_19);
        b_20 = (ImageView) findViewById(R.id.b_20);
        b_21 = (ImageView) findViewById(R.id.b_21);
        b_22 = (ImageView) findViewById(R.id.b_22);
        b_23 = (ImageView) findViewById(R.id.b_23);
        b_24 = (ImageView) findViewById(R.id.b_24);

        b_1.setTag("0");
        b_2.setTag("1");
        b_3.setTag("2");
        b_4.setTag("3");
        b_5.setTag("4");
        b_6.setTag("5");
        b_7.setTag("6");
        b_8.setTag("7");
        b_9.setTag("8");
        b_10.setTag("9");
        b_11.setTag("10");
        b_12.setTag("11");
        b_13.setTag("12");
        b_14.setTag("13");
        b_15.setTag("14");
        b_16.setTag("15");
        b_17.setTag("16");
        b_18.setTag("17");
        b_19.setTag("18");
        b_20.setTag("19");
        b_21.setTag("20");
        b_22.setTag("21");
        b_23.setTag("22");
        b_24.setTag("23");

        btnAccueil = findViewById(R.id.btnAccueil);
        btnAccueil.setOnClickListener(this);

        carte_ressource();

        Collections.shuffle(Arrays.asList(tab_carte));

        b_1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_1, carte);
            }
        });

        b_2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_2, carte);
            }
        });

        b_3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_3, carte);
            }
        });

        b_4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_4, carte);
            }
        });

        b_5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_5, carte);
            }
        });

        b_6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_6, carte);
            }
        });

        b_7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_7, carte);
            }
        });

        b_8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_8, carte);
            }
        });

        b_9.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_9, carte);
            }
        });

        b_10.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_10, carte);
            }
        });

        b_11.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_11, carte);
            }
        });

        b_12.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_12, carte);
            }
        });

        b_13.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_13, carte);
            }
        });

        b_14.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_14, carte);
            }
        });

        b_15.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_15, carte);
            }
        });

        b_16.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_16, carte);
            }
        });

        b_17.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_17, carte);
            }
        });

        b_18.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_18, carte);
            }
        });

        b_19.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_19, carte);
            }
        });

        b_20.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_20, carte);
            }
        });

        b_21.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_21, carte);
            }
        });

        b_22.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_22, carte);
            }
        });

        b_23.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_23, carte);
            }
        });

        b_24.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int carte = Integer.parseInt((String) view.getTag());
                set_carte(b_24, carte);
            }
        });

    }

    @Override
    public void onClick(View view) {
        if (view == this.btnAccueil) {
            Toast.makeText( this, "PAGE D'ACCUEIL", Toast.LENGTH_SHORT).show();
            Intent myAccueil = new Intent (Memory.this, MainActivity.class);
            startActivity(myAccueil);
        }
    }

    private void set_carte(ImageView i, int carte) {
        if (tab_carte[carte] == 101) {
            i.setImageResource(carte1);
        } else if (tab_carte[carte] == 102) {
            i.setImageResource(carte2);
        } else if (tab_carte[carte] == 103) {
            i.setImageResource(carte3);
        } else if (tab_carte[carte] == 104) {
            i.setImageResource(carte4);
        } else if (tab_carte[carte] == 105) {
            i.setImageResource(carte5);
        } else if (tab_carte[carte] == 106) {
            i.setImageResource(carte6);
        } else if (tab_carte[carte] == 107) {
            i.setImageResource(carte7);
        } else if (tab_carte[carte] == 108) {
            i.setImageResource(carte8);
        } else if (tab_carte[carte] == 109) {
            i.setImageResource(carte9);
        } else if (tab_carte[carte] == 110) {
            i.setImageResource(carte10);
        } else if (tab_carte[carte] == 111) {
            i.setImageResource(carte11);
        } else if (tab_carte[carte] == 112) {
            i.setImageResource(carte12);
        } else if (tab_carte[carte] == 201) {
            i.setImageResource(carte13);
        } else if (tab_carte[carte] == 202) {
            i.setImageResource(carte14);
        } else if (tab_carte[carte] == 203) {
            i.setImageResource(carte15);
        } else if (tab_carte[carte] == 204) {
            i.setImageResource(carte16);
        } else if (tab_carte[carte] == 205) {
            i.setImageResource(carte17);
        } else if (tab_carte[carte] == 206) {
            i.setImageResource(carte18);
        } else if (tab_carte[carte] == 207) {
            i.setImageResource(carte19);
        } else if (tab_carte[carte] == 208) {
            i.setImageResource(carte20);
        } else if (tab_carte[carte] == 209) {
            i.setImageResource(carte21);
        } else if (tab_carte[carte] == 210) {
            i.setImageResource(carte22);
        } else if (tab_carte[carte] == 211) {
            i.setImageResource(carte23);
        } else if (tab_carte[carte] == 212) {
            i.setImageResource(carte24);
        }

        if (num_carte ==  1) {
            first_carte = tab_carte[carte];
            if (first_carte > 200) {
                first_carte = first_carte - 100;
            }
            num_carte = 2;
            clic_first = carte;

            i.setEnabled(false);
        } else if (num_carte == 2) {
            second_carte = tab_carte[carte];
            if (second_carte > 200) {
                second_carte = second_carte - 100;
            }
            num_carte = 1;
            clic_second = carte;

            b_1.setEnabled(false);
            b_2.setEnabled(false);
            b_3.setEnabled(false);
            b_4.setEnabled(false);
            b_5.setEnabled(false);
            b_6.setEnabled(false);
            b_7.setEnabled(false);
            b_8.setEnabled(false);
            b_9.setEnabled(false);
            b_10.setEnabled(false);
            b_11.setEnabled(false);
            b_12.setEnabled(false);
            b_13.setEnabled(false);
            b_14.setEnabled(false);
            b_15.setEnabled(false);
            b_16.setEnabled(false);
            b_17.setEnabled(false);
            b_18.setEnabled(false);
            b_19.setEnabled(false);
            b_20.setEnabled(false);
            b_21.setEnabled(false);
            b_22.setEnabled(false);
            b_23.setEnabled(false);
            b_24.setEnabled(false);

            Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    calculate();
                }
            }, 1000);
        }
    }

    private void calculate () {
        if(first_carte == second_carte) {
            if (clic_first == 0) {
                b_1.setVisibility(View.INVISIBLE);
            } else if (clic_first == 1) {
                b_2.setVisibility(View.INVISIBLE);
            } else if (clic_first == 2) {
                b_3.setVisibility(View.INVISIBLE);
            } else if (clic_first == 3) {
                b_4.setVisibility(View.INVISIBLE);
            } else if (clic_first == 4) {
                b_5.setVisibility(View.INVISIBLE);
            } else if (clic_first == 5) {
                b_6.setVisibility(View.INVISIBLE);
            } else if (clic_first == 6) {
                b_7.setVisibility(View.INVISIBLE);
            } else if (clic_first == 7) {
                b_8.setVisibility(View.INVISIBLE);
            } else if (clic_first == 8) {
                b_9.setVisibility(View.INVISIBLE);
            } else if (clic_first == 9) {
                b_10.setVisibility(View.INVISIBLE);
            } else if (clic_first == 10) {
                b_11.setVisibility(View.INVISIBLE);
            } else if (clic_first == 11) {
                b_12.setVisibility(View.INVISIBLE);
            } else if (clic_first == 12) {
                b_13.setVisibility(View.INVISIBLE);
            } else if (clic_first == 13) {
                b_14.setVisibility(View.INVISIBLE);
            } else if (clic_first == 14) {
                b_15.setVisibility(View.INVISIBLE);
            } else if (clic_first == 15) {
                b_16.setVisibility(View.INVISIBLE);
            } else if (clic_first == 16) {
                b_17.setVisibility(View.INVISIBLE);
            } else if (clic_first == 17) {
                b_18.setVisibility(View.INVISIBLE);
            } else if (clic_first == 18) {
                b_19.setVisibility(View.INVISIBLE);
            } else if (clic_first == 19) {
                b_20.setVisibility(View.INVISIBLE);
            } else if (clic_first == 20) {
                b_21.setVisibility(View.INVISIBLE);
            } else if (clic_first == 21) {
                b_22.setVisibility(View.INVISIBLE);
            } else if (clic_first == 22) {
                b_23.setVisibility(View.INVISIBLE);
            } else if (clic_first == 23) {
                b_24.setVisibility(View.INVISIBLE);
            }

            if (clic_second == 0) {
                b_1.setVisibility(View.INVISIBLE);
            } else if (clic_second == 1) {
                b_2.setVisibility(View.INVISIBLE);
            } else if (clic_second == 2) {
                b_3.setVisibility(View.INVISIBLE);
            } else if (clic_second == 3) {
                b_4.setVisibility(View.INVISIBLE);
            } else if (clic_second == 4) {
                b_5.setVisibility(View.INVISIBLE);
            } else if (clic_second == 5) {
                b_6.setVisibility(View.INVISIBLE);
            } else if (clic_second == 6) {
                b_7.setVisibility(View.INVISIBLE);
            } else if (clic_second == 7) {
                b_8.setVisibility(View.INVISIBLE);
            } else if (clic_second == 8) {
                b_9.setVisibility(View.INVISIBLE);
            } else if (clic_second == 9) {
                b_10.setVisibility(View.INVISIBLE);
            } else if (clic_second == 10) {
                b_11.setVisibility(View.INVISIBLE);
            } else if (clic_second == 11) {
                b_12.setVisibility(View.INVISIBLE);
            } else if (clic_second == 12) {
                b_13.setVisibility(View.INVISIBLE);
            } else if (clic_second == 13) {
                b_14.setVisibility(View.INVISIBLE);
            } else if (clic_second == 14) {
                b_15.setVisibility(View.INVISIBLE);
            } else if (clic_second == 15) {
                b_16.setVisibility(View.INVISIBLE);
            } else if (clic_second == 16) {
                b_17.setVisibility(View.INVISIBLE);
            } else if (clic_second == 17) {
                b_18.setVisibility(View.INVISIBLE);
            } else if (clic_second == 18) {
                b_19.setVisibility(View.INVISIBLE);
            } else if (clic_second == 19) {
                b_20.setVisibility(View.INVISIBLE);
            } else if (clic_second == 20) {
                b_21.setVisibility(View.INVISIBLE);
            } else if (clic_second == 21) {
                b_22.setVisibility(View.INVISIBLE);
            } else if (clic_second == 22) {
                b_23.setVisibility(View.INVISIBLE);
            } else if (clic_second == 23) {
                b_24.setVisibility(View.INVISIBLE);
            }

        } else {
            b_1.setImageResource(R.drawable.empty);
            b_2.setImageResource(R.drawable.empty);
            b_3.setImageResource(R.drawable.empty);
            b_4.setImageResource(R.drawable.empty);
            b_5.setImageResource(R.drawable.empty);
            b_6.setImageResource(R.drawable.empty);
            b_7.setImageResource(R.drawable.empty);
            b_8.setImageResource(R.drawable.empty);
            b_9.setImageResource(R.drawable.empty);
            b_10.setImageResource(R.drawable.empty);
            b_11.setImageResource(R.drawable.empty);
            b_12.setImageResource(R.drawable.empty);
            b_13.setImageResource(R.drawable.empty);
            b_14.setImageResource(R.drawable.empty);
            b_15.setImageResource(R.drawable.empty);
            b_16.setImageResource(R.drawable.empty);
            b_17.setImageResource(R.drawable.empty);
            b_18.setImageResource(R.drawable.empty);
            b_19.setImageResource(R.drawable.empty);
            b_20.setImageResource(R.drawable.empty);
            b_21.setImageResource(R.drawable.empty);
            b_22.setImageResource(R.drawable.empty);
            b_23.setImageResource(R.drawable.empty);
            b_24.setImageResource(R.drawable.empty);

        }

        b_1.setEnabled(true);
        b_2.setEnabled(true);
        b_3.setEnabled(true);
        b_4.setEnabled(true);
        b_5.setEnabled(true);
        b_6.setEnabled(true);
        b_7.setEnabled(true);
        b_8.setEnabled(true);
        b_9.setEnabled(true);
        b_10.setEnabled(true);
        b_11.setEnabled(true);
        b_12.setEnabled(true);
        b_13.setEnabled(true);
        b_14.setEnabled(true);
        b_15.setEnabled(true);
        b_16.setEnabled(true);
        b_17.setEnabled(true);
        b_18.setEnabled(true);
        b_19.setEnabled(true);
        b_20.setEnabled(true);
        b_21.setEnabled(true);
        b_22.setEnabled(true);
        b_23.setEnabled(true);
        b_24.setEnabled(true);

        verifier();
    }

    private void verifier() {
        if (b_1.getVisibility() == View.INVISIBLE &&
                b_2.getVisibility() == View.INVISIBLE &&
                b_3.getVisibility() == View.INVISIBLE &&
                b_4.getVisibility() == View.INVISIBLE &&
                b_5.getVisibility() == View.INVISIBLE &&
                b_6.getVisibility() == View.INVISIBLE &&
                b_7.getVisibility() == View.INVISIBLE &&
                b_8.getVisibility() == View.INVISIBLE &&
                b_9.getVisibility() == View.INVISIBLE &&
                b_10.getVisibility() == View.INVISIBLE &&
                b_11.getVisibility() == View.INVISIBLE &&
                b_12.getVisibility() == View.INVISIBLE &&
                b_13.getVisibility() == View.INVISIBLE &&
                b_14.getVisibility() == View.INVISIBLE &&
                b_15.getVisibility() == View.INVISIBLE &&
                b_16.getVisibility() == View.INVISIBLE &&
                b_17.getVisibility() == View.INVISIBLE &&
                b_18.getVisibility() == View.INVISIBLE &&
                b_19.getVisibility() == View.INVISIBLE &&
                b_20.getVisibility() == View.INVISIBLE &&
                b_21.getVisibility() == View.INVISIBLE &&
                b_22.getVisibility() == View.INVISIBLE &&
                b_23.getVisibility() == View.INVISIBLE &&
                b_24.getVisibility() == View.INVISIBLE) {

            AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(Memory.this);
            alertDialogBuilder
                    //.setMessage("GAME OVER!\nP1: " + playerPoints + "\nP2: " + cpuPoints)
                    .setMessage("LA PARTIE EST FINI!\nVOULEZ-VOUS REJOUER ?")
                    .setCancelable(false)
                    .setPositiveButton("OUI", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick (DialogInterface dialogInterface, int i) {
                            Intent intent = new Intent(getApplicationContext(), Memory.class);
                            startActivity(intent);
                            finish();
                        }
                    })
                    .setNegativeButton("NON", new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                            finish();
                        }
                    });
            AlertDialog alertDialog = alertDialogBuilder.create();
            alertDialog.show();
        }
    }

    private void carte_ressource() {
        carte1 = R.drawable.image1;
        carte2 = R.drawable.image2;
        carte3 = R.drawable.image3;
        carte4 = R.drawable.image4;
        carte5 = R.drawable.image5;
        carte6 = R.drawable.image6;
        carte7 = R.drawable.image7;
        carte8 = R.drawable.image8;
        carte9 = R.drawable.image9;
        carte10 = R.drawable.image10;
        carte11 = R.drawable.image11;
        carte12 = R.drawable.image12;
        carte13 = R.drawable.image13;
        carte14 = R.drawable.image14;
        carte15 = R.drawable.image15;
        carte16 = R.drawable.image16;
        carte17 = R.drawable.image17;
        carte18 = R.drawable.image18;
        carte19 = R.drawable.image19;
        carte20 = R.drawable.image20;
        carte21 = R.drawable.image21;
        carte22 = R.drawable.image22;
        carte23 = R.drawable.image23;
        carte24 = R.drawable.image24;


    }
}