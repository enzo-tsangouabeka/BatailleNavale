/**
* @file main.h
 * @brief Projet Bataille navale
 * @author Enzo Tsangouabeka
 * @version v1.0
 * @date 02/12/2024
 */

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdlib> // Aléatoire
#include <string>
#include <array> // Pour les tableaux
#include <windows.h> // Pour la couleur
#include <limits> // Pour ignorer les mauvaises entrées (int)

using namespace std;

// ---- Variable globale ----
int matrixOfPlayerBoat[10][10] {}; // Matrice des bateaux du joueur
int matrixOfMachineBoat[10][10] {}; // Matrice des bateaux de la machine
int matrixOfPlayerMissile[10][10] {}; // Matrice des missiles envoyer par le joueur
int matrixOfMachineMissile[10][10] {}; // Matrice des missiles envoyer par la machine

// Etat des bateaux du joueur (Variable de stockage du nombre de compartiments encore en "vie" de chaque bateau)
int playerCarrier(5), playerBattleship(4), playerCruiser(3), playerSubmarine(3), playerDestroyer(2);

// Etat des bateaux de la machine (Variable de stockage du nombre de compartiments encore en "vie" de chaque bateau)
int machineCarrier(5), machineBattleship(4), machineCruiser(3), machineSubmarine(3), machineDestroyer(2);

// Tableau utilisé pour l'affichage des matrices
array<string, 10> tableOfLetters {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

// Tableau utiliser pour l'affichage des noms de bateau
array<string,6> boat {"Erreur", "Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};

// Tableau des coups disponibles
array<string,100> availableMoves;

// Coordonnées des missiles
int row(0), column(0);

// Scores et nombres de tours
int round(1);
int playerScore(playerCarrier + playerBattleship + playerCruiser + playerSubmarine + playerDestroyer);
int machineScore(machineCarrier + machineBattleship + machineCruiser + machineSubmarine + machineDestroyer);
const int MAX_SCORE(17);

// Différentes valeurs pour les emplacements des matrices
int DEFAULT_VALUE (0b00000);
int MISSILE_VALUE (0b100000);
int GOOD_MISSILE_VALUE (0b1000000);
int CARRIER_VALUE (0b00001);
int BATTLESHIP_VALUE (0b00010);
int CRUISER_VALUE (0b00100);
int SUBMARINE_VALUE (0b01000);
int DESTROYER_VALUE (0b10000);

// Sous-Programmes et Fonctions

/**
* @fn void printMatrix(int _matrixToPrint[10][10]);
* @brief Permet d'afficher une matrix de 10x10
* @param int _matrixToPrint[10][10] : Matrice selectionnée
*/
void printMatrix(int _matrixToPrint[10][10]);

/**
* @fn void generateBoard()
* @brief Géneration des 5 bateaux pour chaqun des 2 camps, 10 au total (horizontal ou vertical)
* @param bool _isForPlayer : Permet de choisir si le génération des bateau se fait pour le joueur ou la machine
* @param bool _isntManual : Permet de choisir si le génération des bateau se fait manuellement ou automatiquement
*/
void generateBoards(bool _isForPlayer, bool _isntManual = true);

/**
* @fn void AddBoat(int boatID, int _matrixToEdit[10][10]);
* @brief Permet d'ajouter un bateau dans une matrixe,
* @brief En trouvant aléatoirement l'orientation du bateau,
* @brief Puis en choisissant une position sur la matrix et en essayant de placer un bateau dans une direction,
* @brief Sinon en le placant dans l'autre direction,
* @param int boatID : Type du bateau
* @param int _matrixToEdit : Matrice à éditer
*/
void AddBoat(int _boatID, int _matrixToEdit[10][10], bool  _isntManual = true);

/**
* @fn void setColor(int _color);
* @brief Permet de modifier la couleur du text affichée après l'execution de la routine
* @param int _color : Couleur choisie
*/
void setColor(int _color = 7);

/**
* @fn void printMatrix(int _matrixToPrint[10][10]);
* @brief Routine principale permettant au jeu de marcher
* @param int _gameMode : Permet de savoir quel est le mode de jeu afin d'adapter le code en fonction
*/
void game(int _gameMode);

/**
* @fn prompt(bool _isForPlayer);
* @brief Permet d'afficher le promt de chaque joueur
* @param bool _isForPlayer : Es-ce le joueur 1 ou 2int
* @param_ int _gameMode : Permet de savoir quel est le mode de jeu afin d'adapter le code en fonction
*/
void prompt(bool _isForPlayer, int _gameMode);

/**
* @fn void shootMissile(int _row, int _column, int _matrixToEdit[10][10]);
* @brief Permet de modifier une case de la matrice _matrixToEdit[][] afin de lui ajouter MISSILE_VALUE (pour avoir un X)
* @param int _row : Variable de la ligne
* @param int _column : Variable de la colone
* @param int _matrixToEdit[10][10] : Matrice sur laquel on effectue les actions
* @param bool _isTouch : permet de savoir si la case doit être afficher avec une croix rouge ou grise
*/
void shootMissile(int _row, int _column, int _matrixToEdit[10][10], bool _isTouch = false);

/**
* @fn void positionToMatrix(string position);
* @param int _isntForBoatInit : Permet de savoir si la routine est appelée par la routine generateBoards() ou par la routine prompt()
* @param int _boatID : Utiliser pour afficher le nom du bateau
* @param string _externalMove : Utiliser par le code du niveau 2 pour transformer une entré de type "A1" en position type row = 0 column = 0
* @brief Permet de transformer une entré de type lettreChiffres en position sur la matrice
*/
void positionToMatrix(int _isntForBoatInit = true, int _boatID = 0, string _externalMove = "N/A");

/**
* @fn void scoreMAJ();
* @brief Permet de mettre à jour les variables playerScore et machineScore
*/
void scoreMAJ();

/**
* @fn void initAvalableMoves();
* @brief Permet d'initialiser le tableau availableMoves[]
*/
void initAvalableMoves();

/**
* @fn string playRandomMove();
* @brief Permet de retourner une position aléatoire dans le tabeau tabeau availableMoves[] différant de N/A (Afin de ne pas répéter 2 coups)
* @return string : Retourne une position aléatoire dans le tabeau availableMoves[] différant de N/A
*/
string playRandomMove();

/**
* @fn bool isEmptyPlacement(int _startPointX, int _startPointY, int _boatDirection, short _boatSize, int _matrixToSearch[10][10]);
* @brief Permet de verifier la validité d'un placement d'un bateau afin d'éviter la superposition sur une matrice
* @param int _startPointX : Position x de départ
* @param int _startPointY : Position y de départ
* @param int _boatDirection : Direction du bateau
* @param short _boatSize : Taille du bateau
* @param int _matrixToSearch[10][10] : Matrice selectionnée
* @return bool : Son rôle de permettre d'autoriser le placement d'un bateau sur une matrice si celle ci est bien vide à l'emplacement choisi
*/
bool isEmptyPlacement(int _startPointX, int _startPointY, int _boatDirection, short _boatSize, int _matrixToSearch[10][10]);

/**
* @fn bool reachableFinalDestination(int row, int column, int direction, int shipSize);
* @brief Permet de verifier le si un bateau depasse des limites
* @param int row : Position y de départ
* @param int column : Position x de départ
* @param int direction : Direction du bateau
* @param int shipSize : Taille du bateau (pour le nombre d'itération dans la boucle)
* @return bool : Son rôle de permettre d'autoriser le placement d'un bateau sur une matrice si celle ci est bien vide à l'emplacement choisi
*/
bool reachableFinalDestination(int row, int column, int direction, int shipSize);

/**
* @fn bool isGoodMove(int _startPointX, int _startPointY, int _matrixToSearch[10][10]);
* @brief Permet de verifier la validité de l'entré utilisateur
* @param int _startPointX : Position x de départ
* @param int _startPointY : Position y de départ
* @param int _matrixToSearch[10][10] : Matrice selectionnée
* @return bool : Son rôle de permettre d'autoriser un coup en verifiant ça validité
*/
bool isGoodMove(int _startPointX, int _startPointY, int _matrixToSearch[10][10]);

/**
* @fn bool isEndGameCondition();
* @brief Permet de verifier si la condition de fin de partie est validé ou non
* @return bool : Son rôle est de revoyer true si la condition de fin de partie est véridique
*/
bool isEndGameCondition();

/**
* @fn int cheakTypeEntire(int& _entire);
* @brief Fonction de vérification des entiers
* @return int : Retourne un entier valide
*/
int cheakTypeEntire(int& _entire);

#endif //MAIN_H
