def nouveauJeu():
    return ('.','.','.','.','.','.','.','.','.')

def affiche(jeu):
    print(jeu[0],jeu[1],jeu[2])
    print(jeu[3],jeu[4],jeu[5])
    print(jeu[6],jeu[7],jeu[8])

def joueur(jeu):
    J1=0
    J2=0
    for i in jeu:
        if i=='X':
           J1+=1
        if i=='O':
           J2+=1
    if J1==J2:
        return 'X'
    return('O')

def coupPos(jeu):
    res=[]
    for i in range(9):
        if jeu[i]=='.':
            res+=[i]
    return res

def jouer(jeu,coup):
    if jeu[coup]!='.':
        print("Case occupée")
    else:
        liste=[]
        liste+=jeu
        liste[coup]=joueur(jeu)
        return(tuple(liste))

def gagner(jeu):
    res='.'
    if (jeu[0]!='.' and jeu[0]==jeu[3]==jeu[6]):
        res=jeu[0]
    if (jeu[1]!='.' and jeu[1]==jeu[4]==jeu[7]):
        res=jeu[1]
    if (jeu[2]!='.' and jeu[2]==jeu[5]==jeu[8]):
        res=jeu[2]
    if (jeu[0]!='.' and jeu[0]==jeu[1]==jeu[2]):
        res=jeu[0]
    if (jeu[4]!='.' and jeu[4]==jeu[5]==jeu[3]):
        res=jeu[3]
    if (jeu[7]!='.' and jeu[7]==jeu[8]==jeu[6]):
        res=jeu[6]
    if (jeu[0]!='.' and jeu[0]==jeu[4]==jeu[8]):
        res=jeu[0]
    if (jeu[2]!='.' and jeu[2]==jeu[4]==jeu[6]):
        res=jeu[2]
    if (res=='O'):
        return(-1)
    else:
        if res=='X':
            return(1)
    return(0)


print("**********************************")
print("Chargement de la partie")
print("**********************************")

print("\n \n")

def valMax(jeu,dic):
    coups=coupPos(jeu)

    if gagner(jeu)!=0 or len(coups)==0:
        dic[jeu]=gagner(jeu)
        return ([gagner(jeu),['f']])

    max=[-2,['.']]
    valeurMax='.'

    for coup in coups:
        njeu=jouer(jeu,coup)
        val=valMin(njeu,dic)
        if val[0]>max[0] :
            max=val
            valeurMax=coup
    dic[jeu]=max[0]
    max[1].append(valeurMax)
    return [max[0],max[1]]
    
def valMin(jeu,dic):
    coups=coupPos(jeu)
     
    if gagner(jeu)!=0 or len(coups)==0:
        dic[jeu]=gagner(jeu)
        return ([gagner(jeu),['f']])
    min=[2,['.']]
    valeurMin='.'

    for coup in coups:
        njeu=jouer(jeu,coup)
        val=valMax(njeu,dic)
        if val[0]<min[0] :
            min=val
            valeurMin=coup
    dic[jeu]=min[0]
    min[1].append(valeurMin)
    return [min[0],min[1]]

def MinMax(jeu,dic):
    coups=coupPos(jeu)
    if gagner(jeu)!=0 or len(coups)==0:
        dic[jeu]=gagner(jeu)
        return ([gagner(jeu),['f']])
    if joueur(jeu)=='X':
        return valMax(jeu,dic)
    else:
        return valMin(jeu,dic)

def valMaxG(jeu,dic):
    coups=coupPos(jeu)
     
    if gagner(jeu)!=0 or len(coups)==0:
        dic[jeu]=gagner(jeu)
        return ([gagner(jeu),['f']])
    max=[-2,['.']]
    valeurMax='.'
    for coup in coups:
        njeu=jouer(jeu,coup)
        val=valMinG(njeu,dic)
        if val[0]>max[0] :
            max=val
            valeurMax=coup

    dic[jeu]=max[0]
    max[1].append(valeurMax)
    return [max[0]*0.9,max[1]]

def valMinG(jeu,dic):
    coups=coupPos(jeu)
    if gagner(jeu)!=0 or len(coups)==0:
        dic[jeu]=gagner(jeu)
        return ([gagner(jeu),['f']])
    min=[2,['.']]
    valeurMin='.'
    for coup in coups:
        njeu=jouer(jeu,coup)
        val=valMaxG(njeu,dic)
        if val[0]<min[0] :
            min=val
            valeurMin=coup

    dic[jeu]=min[0]
    min[1].append(valeurMin)
    return [min[0]*0.9,min[1]]

def MinMaxG(jeu,dic):
    coups=coupPos(jeu)

    if gagner(jeu)!=0 or len(coups)==0:
        dic[jeu]=gagner(jeu)
        return ([gagner(jeu),['f']])
    if joueur(jeu)=='X':
        return valMaxG(jeu,dic)
    else:
        return valMinG(jeu,dic)	

def afficheM():
    print ("Les touches du jeu")
    print ("------")
    print ("0 1 2")
    print ("3 4 5")
    print ("6 7 8")
    print ("------")

def jouerPartie(depart,table,humain):
    jeu=depart
    print("----- Bonne Partie !!! -----")
    affiche(jeu)
    while (gagner(jeu)==0) and len(coupPos(jeu))!=0:
        if joueur(jeu)==humain :
            print("----- Vous devez jouer -----") 
            coup=-1
            coups=coupPos(jeu)
            afficheM()
            while(coup not in coups):
                coup=int(input("Jouer un coup : "))
            jeu=jouer(jeu,coup)
            affiche(jeu)
        else:
            print("----- L'ordinateur à jouer -----")
   
            if (jeu not in table):
                table=calcul(jeu)
            coup=coupMeilleur(jeu,table)
            jeu=jouer(jeu,coup)
            affiche(jeu)

import random
def coupMeilleur(jeu,table):
    coups=coupPos(jeu)
    valeur=table[jeu]
    fini=False
    while (not fini):
        coup=coups[random.randint(0,len(coups)-1)]
        njeu=jouer(jeu,coup)
        if (njeu in table):
            if (table[njeu]==valeur):
                return coup

dico={}
jeu=nouveauJeu()

res=(MinMaxG(jeu,dico))

print("**********************************")
print("Lancement de la Partie")
print("**********************************")
jouerPartie(jeu,dico,'X')
