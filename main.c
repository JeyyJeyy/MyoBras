#include <MyoController.h>
#include <Braccio.h>
#include <Servo.h>

// ----- Declaration des variables globales -----

MyoController myo = MyoController(); //Initialisation du MYO
enum motor{rotationBase=0, inclunaisonBase=1, inclinaisonCoude=2, rotationPoignee=3, serragePince=4}; // Liste des moteurs utilisables
//Changer la categorie securite si le nombre de moteur change
char activeMotor=1; // Moteur en cours d'utilisation, nro 1 par defaut, peut etre change

// ----- Definition des moteurs -----

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// ----- Boucles -----

void setup(){
    Braccio.begin(); //position de sécurité
}

void loop(){
    myo.updatePose(); // verification des changements d'etat

    switch(myo.getCurrentPose()){ // Recuperation des poses
        case rest:
        //Aucune reception
        break;

// ----- Changement de moteur -----

        case waveIn: //Main a gauche
            activeMotor=motor(activeMotor++); //Passage au moteur suivant
            Serial.writeln("Moteur suivant : "+activeMotor);
        break;
        case waveOut: //Main a Droite
            activeMotor=motor(activeMotor--); // Passage au moteur precedent
            Serial.writeln("Moteur precedent : "+activeMotor);
        break;

// ----- Envoi des ordres (horaires/bas/serrage) -----

        case fist:
            switch(activeMotor){
                case 0:
            //Rotation horaire de la base
            Serial.writeln("Rotation horaire de la base");
                break;
                case 1:
            //Inclinaison basse de la base
            Serial.writeln("Inclinaison basse de la base");
                break;
                case 2:
            //Inclinaison horaire du coude
            Serial.writeln("Inclinaison horaire du coude");
                break;
                case 3:
            //Rotation horaire du poignet
            Serial.writeln("Rotation horaire du poignet");
                break;
                case 4:
            //Serrage de la pince
            Serial.writeln("Serrage de la pince");
                break;
            }
        break;

// ----- Envoi des ordres (antihoraires/haut/deserrage) -----

        case fingersSpread:
            switch(activeMotor){
                case 0:
            //Rotation antihoraire de la base
            Serial.writeln("Rotation antihoraire de la base");
                break;
                case 1:
            //Inclinaison haute de la base
            Serial.writeln("Inclinaison haute de la base");
                break;
                case 2:
            //Inclinaison haute du coude
            Serial.writeln("Inclinaison haute du coude");
                break;
                case 3:
            //Rotation antihoraire du poignet
            Serial.writeln("Rotation antihoraire du poignet");
                break;
                case 4:
            //Deserrage de la pince
            Serial.writeln("Déserrage de la pince");
                break;
            }
        break;
    }

// ----- Securite: en cas de tour complet des fonctions ----
        
    if(activeMotor<0){
        activeMotor=4;
        Serial.writeln("!DEPASSEMENT NEGATIF");
    }
    else if(activeMotor>4){
        activeMotor=0;
        Serial.writeln("!DEPASSEMENT POSITIF");
    }
}
