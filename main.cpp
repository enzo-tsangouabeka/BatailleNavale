/**
 * @file main.cpp
 * @brief Projet Bataille navale
 * @author Enzo Tsangouabeka
 * @version v1.0
 * @date 02/12/2024
 */

/* CONSIGNE :

    → 2 joueurs
    → 1 plateau à 2 tableaux

Tour à tour, les joueurs doivent trouver les positions des navires de l'autre joueur pour les couler.
La partie est terminée quand tout les navires de l'adversaire sont coulés. Pour simplifier, un plateau de 10x10 cases pourra suffir avec dans ce cas 1 bateau de 4, un autre de 3 et un bateau de 2.

Niveau 0 (fait et push):
Votre programme simule une partie en affichant le plateau de chaque joueur à tour de role sous la forme d'un tableau 2D.
Les cases sont choisies par les deux joueurs et la fin de partie déterminée visuellement.
Les navires sont positionnés dès le départ par le programme et ne peuvent être modifiés par les joueurs.

Niveau 1 (fait et push):
Les navires sont placés par les joueurs.

Niveau 2 (fait et push):
Un joueur joue contre l'ordinateur qui choisit aléatoirement ses tirs.
*/

#include "main.h"

int main() {
    int answer(0);
    bool isntGoodNumber(true);
    system("cls");
    srand(time(0));

    cout << "Choisissez un niveau de jeu :" << endl;
    cout << " - Niveau 0 = Generation automatique des bateaux + PvP" << endl;
    cout << " - Niveau 1 = Generation manuel des bateaux + PvP" << endl;
    cout << " - Niveau 2 = Generation manuel des bateaux + PvE (non disponible)" << endl;

    while (isntGoodNumber) {
        cout << "Votre reponse >";
        cheakTypeEntire(answer);
        isntGoodNumber = !(answer == 0 || answer == 1 || answer == 2);
    }
    system("cls");
    game(answer); // Lancement de la partie
    return 0;
}

string playRandomMove() {
    int randomIndex(0);
    string move;
    while (true) {
        randomIndex = rand() % 100;
        move = availableMoves[randomIndex];
        if (move != "N/A") {
            availableMoves[randomIndex] = "N/A";
            return move;
        }
    }
}

bool isEmptyPlacement(int _startPointX, int _startPointY, int _boatDirection, short _boatSize, int _matrixToSearch[10][10]) {
    for (int i = 0; i < _boatSize; i++) {
        if (_boatDirection == 1) { // vers le haut
            if (_matrixToSearch[_startPointY - i][_startPointX] != DEFAULT_VALUE) {
                return false;
            }
        }
        else if (_boatDirection == 2) { // vers le bas
            if (_matrixToSearch[_startPointY + i][_startPointX] != DEFAULT_VALUE) {
                return false;
            }
        }
        else if (_boatDirection == 3) { // vers la droite
            if (_matrixToSearch[_startPointY][_startPointX + i] != DEFAULT_VALUE) {
                return false;
            }
        }
        else if (_boatDirection == 4) { // vers la gauche
            if (_matrixToSearch[_startPointY][_startPointX - i] != DEFAULT_VALUE) {
                return false;
            }
        }
    }
    return true;
}

bool reachableFinalDestination(int row, int column, int direction, int shipSize) {
    switch (direction) {
        case 1: // Haut
            if (row - shipSize + 1 < 0) {
                setColor(4); cout << "Le bateau depasse des limites, veuiller rentrer de bonne valeur de direction." << endl; setColor(7);
                return false; // Le bateau dépasse vers le haut
            }break;

        case 2: // Bas
            if (row + shipSize > 10) {
                setColor(4); cout << "Le bateau depasse des limites, veuiller rentrer de bonne valeur de direction." << endl; setColor(7);
                return false; // Le bateau dépasse vers le bas
            }break;

        case 3: // Droite
            if (column + shipSize > 10) {
                setColor(4); cout << "Le bateau depasse des limites, veuiller rentrer de bonne valeur de direction." << endl; setColor(7);
                return false; // Le bateau dépasse vers la droite
            }break;

        case 4: // Gauche
            if (column - shipSize + 1 < 0) {
                setColor(4); cout << "Le bateau depasse des limites, veuiller rentrer de bonne valeur de direction." << endl; setColor(7);
                return false; // Le bateau dépasse vers la gauche
            }break;

        default:
            setColor(4); cout << "Erreur lors de la verification de la fonction : reachableFinalDestination()" << endl; setColor(7);
            return false; // Direction invalide
    }
    return true;
}

bool isGoodMove(int _startPointX, int _startPointY, int _matrixToSearch[10][10]) {
    if (_startPointX < 10 && _startPointY < 10 && _startPointX >= 0 && _startPointY >= 0) {
        if (_matrixToSearch[_startPointX][_startPointY] < MISSILE_VALUE) {
            return true;
        }
        setColor(4); cout << "Attention, vous devez tirer vos missiles dans des cases ou vous n'avez pas encore tire !" << endl; setColor(7);
        return false;
    }
    setColor(4); cout << "Attention, vos coup doivent etre compris enter A1 et J10 !" << endl; setColor(7); // Plus atteignable par le code (inutile)
    return false;
}

bool isEndGameCondition() {
    scoreMAJ();

    if (playerScore == 0) {
        setColor(10); cout << "La joueur 1 a gagner" << endl; setColor(7);
    }
    if (machineScore == 0) {
        setColor(10); cout << "Le joueur 2 a gagner" << endl; setColor(7);
    }
    return (playerScore == 0 || machineScore == 0 ) ;
}

int cheakTypeEntire(int& _entire) {
    while (!(cin >> _entire)) {
        cin.clear();  // Efface le message d'erreur de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore la dernière mauvaise entrées
        cout << "Erreur : Veuillez entrer un nombre entier :";
    }
    return _entire;  // Retourner l'entier validé
}

void printMatrix(int _matrixToPrint[10][10]) {
    cout << "   ";
    for(const string& letters : tableOfLetters) {
        cout << letters << "  ";
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << ((i == 9) ? (" ") : ("  ")); // Pour la mise en forme
        for (int j = 0; j < 10; j++) {
            switch (_matrixToPrint[i][j]) {
                case 0b00000: // Mer (~)
                    cout << "~  ";
                    break;
                case 0b00001: // Carrier (C)
                    setColor(3); cout << "C  "; setColor(7);
                    break;
                case 0b00010: // Battleship (B)
                    setColor(3); cout << "B  "; setColor(7);
                    break;
                case 0b000100: // Cruiser (K)
                    setColor(3); cout << "K  "; setColor(7);
                    break;
                case 0b001000: // Submarine (S)
                    setColor(3); cout << "S  "; setColor(7);
                    break;
                case 0b010000: // Destroyer (D)
                    setColor(3); cout << "D  "; setColor(7);
                    break;
                case 0b100000: // Missile dans la mer (X)
                    cout << "X  ";
                    break;
                default: // Erreur
                    if (_matrixToPrint[i][j] > MISSILE_VALUE) { // Missile ayant touché un bateau
                        setColor(4); cout << "X  "; setColor(7);
                    }
                    else {
                        cout << "F  "; // Fusion de bateau (Impossible thériquement)
                    }
                break;
            }
        }
        cout << endl;
    }
}

void generateBoards(bool _isForPlayer, bool _isntManual) {
    if(_isntManual) {
        if(_isForPlayer) {
            AddBoat(1, matrixOfPlayerBoat);
            AddBoat(2, matrixOfPlayerBoat);
            AddBoat(3, matrixOfPlayerBoat);
            AddBoat(4, matrixOfPlayerBoat);
            AddBoat(5, matrixOfPlayerBoat);
        }
        else {
            AddBoat(1, matrixOfMachineBoat);
            AddBoat(2, matrixOfMachineBoat);
            AddBoat(3, matrixOfMachineBoat);
            AddBoat(4, matrixOfMachineBoat);
            AddBoat(5, matrixOfMachineBoat);
        }
    }
    else {
        if(_isForPlayer) {
            AddBoat(1, matrixOfPlayerBoat, false);
            AddBoat(2, matrixOfPlayerBoat, false);
            AddBoat(3, matrixOfPlayerBoat, false);
            AddBoat(4, matrixOfPlayerBoat, false);
            AddBoat(5, matrixOfPlayerBoat ,false);
            cout << "Voici votre plateau : " << endl;
            printMatrix(matrixOfPlayerBoat);
            system("pause");
        }
        else {
            AddBoat(1, matrixOfMachineBoat, false);
            AddBoat(2, matrixOfMachineBoat, false);
            AddBoat(3, matrixOfMachineBoat, false);
            AddBoat(4, matrixOfMachineBoat, false);
            AddBoat(5, matrixOfMachineBoat, false);
            cout << "Voici votre plateau : " << endl;
            printMatrix(matrixOfMachineBoat);
            system("pause");
        }
    }
}

void AddBoat(int _boatID, int _matrixToEdit[10][10], bool _isntManual) {
    int boatDirection(0);
    int xPositionToStart(rand() % 10), yPositionToStart(rand() % 10), BOX_VALUE(DEFAULT_VALUE);
    short shipSize(0);

    if (_boatID == 1) { // Mise en place du Carrier
        BOX_VALUE = CARRIER_VALUE;
        shipSize = 5;
    }
    else if (_boatID == 2) { // Mise en place du Battleship
        BOX_VALUE = BATTLESHIP_VALUE;
        shipSize = 4;
    }
    else if (_boatID == 3) { // Mise en place du Cruiser
        BOX_VALUE = CRUISER_VALUE;
        shipSize = 3;
    }
    else if (_boatID == 4) { // Mise en place du Submarine
        BOX_VALUE = SUBMARINE_VALUE;
        shipSize = 3;
    }
    else if (_boatID == 5) { // Mise en place du Destroyer
        BOX_VALUE = DESTROYER_VALUE;
        shipSize = 2;
    }

    if (_isntManual) {
        // Permet de générer l'emplacement d'un bateau
        do {
            boatDirection = (rand() % 4 + 1);
            if (boatDirection == 1) { // haut
                xPositionToStart = (rand() % 10);
                yPositionToStart = rand() % (10 - shipSize) + shipSize;
            }
            else if (boatDirection == 2) { // bas
                xPositionToStart = rand() % 10;
                yPositionToStart = rand() % (10 - shipSize);
            }
            else if (boatDirection == 3) { // droite
                xPositionToStart = rand() % (10 - shipSize);
                yPositionToStart = rand() % 10;
            }
            else if (boatDirection == 4) { // gauche
                xPositionToStart = rand() % (10 - shipSize) + shipSize;
                yPositionToStart = rand() % 10;
            }
        } while (!isEmptyPlacement(xPositionToStart, yPositionToStart, boatDirection, shipSize, _matrixToEdit));
    }
    else {
        do {
            boatDirection = 0;
            positionToMatrix(false, _boatID);
            while (boatDirection < 1 || boatDirection > 4){
                cout << "Quel est votre la direction (1=Haut, 2=Bas, 3=Droite, 4=Gauche) > " ;
                cheakTypeEntire(boatDirection); // Vérifier la validité de l'entré
            }
            yPositionToStart = row;
            xPositionToStart = column;

        } while (!isEmptyPlacement(column, row, boatDirection, shipSize, _matrixToEdit) || !reachableFinalDestination(yPositionToStart, xPositionToStart, boatDirection, shipSize));
    }

    if (boatDirection == 1) { // Génerer un bateau vers le haut
        for (int i(0); i < shipSize; i++) {
            _matrixToEdit[yPositionToStart - i][xPositionToStart] += BOX_VALUE;
        }
    }
    else if (boatDirection == 2) { // Génerer un bateau vers le bas
        for (int i(0); i < shipSize; i++) {
            _matrixToEdit[yPositionToStart + i][xPositionToStart] += BOX_VALUE;
        }
    }
    else if (boatDirection == 3) { // Génerer un bateau vers la droite
        for (int i(0); i < shipSize; i++) {
            _matrixToEdit[yPositionToStart][xPositionToStart + i] += BOX_VALUE;
        }
    }
    else if (boatDirection == 4) { // Génerer un bateau vers la gauche
        for (int i(0); i < shipSize; i++) {
            _matrixToEdit[yPositionToStart][xPositionToStart - i] += BOX_VALUE;
        }
    }
    else {
        cout << "Erreur" << endl;
    }
}

void setColor(int _color) {
    /*
    0	Noir
    1	Bleu
    2	Vert
    3	Cyan
    4	Rouge
    5	Magenta
    6	Jaune
    7	Gris clair (couleur par défaut)
    8	Gris foncé
    9	Bleu clair
    10	Vert clair
    11	Cyan clair
    12	Rouge clair
    13	Magenta clair
    14	Jaune clair
    15	Blanc
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, _color);
}

void game(int _gameMode) {
    system("cls");
    bool _isntEndGameCondition(true) ;

    if(_gameMode == 0) {
        // Génère les positions des bateaux pour le joueur et la machine automatiquement
        generateBoards(true); // Joueur
        generateBoards(false); // Machine
    }
    else if (_gameMode == 1) {
        // Génère les positions des bateaux pour le joueur et la machine manuellement
        generateBoards(true, false);
        system("cls");
        setColor(5); cout << "Changement, Joueur 2 a vous" << endl; setColor(7);
        system("pause");
        system("cls");
        generateBoards(false, false);
        system("cls");
    }
    else if (_gameMode == 2) {
        // Génère les positions des bateaux pour le joueur et la machine manuellement
        generateBoards(true, false);
        system("cls");
        generateBoards(false); // Machine
        initAvalableMoves(); // Initialisation du tableau availableMoves[]

    }

    // Boucle se jouant jusqu'à la victoire d'un des 2 joueurs en affichant les prompts à tour de rôle
    while (_isntEndGameCondition) {
        if (!isEndGameCondition() && _isntEndGameCondition) {// Tour du joueur 1
            prompt(true, _gameMode);
        }
        else {
            _isntEndGameCondition = false;
        }
        if (!isEndGameCondition() && _isntEndGameCondition) {
            // Tour du joueur 2
            prompt(false, _gameMode);
        }
        else {
            _isntEndGameCondition = false;
        }
    }
}

void prompt(bool _isForPlayer, int _gameMode) {
    bool isntGoodMove(true);
    system("cls");

    // Joueur 1
    if (_isForPlayer) {
        system("cls");
        cout << "----- Tour du JOUEUR 1 -----\n" << endl;
        cout << "Tour : " << round << endl;
        cout << "joueur 1 (" << MAX_SCORE - playerScore << "), joueur 2 (" << MAX_SCORE - machineScore << ")" << endl;
        cout << "Plateau joueur 1 : " << endl;
        printMatrix(matrixOfPlayerBoat);
        cout << endl;
        cout << "Missiles envoyer par joueur 1 : " << endl;
        printMatrix(matrixOfPlayerMissile);
        cout << endl;

        // Obtenire les coordonées du tir
        while (isntGoodMove) {
            positionToMatrix();
            if (isGoodMove(row, column, matrixOfMachineBoat)) {
                isntGoodMove = false;
            }
        }

        // Effectuer le tir de missile

        if (matrixOfMachineBoat[row][column] != DEFAULT_VALUE) {
            shootMissile(row, column, matrixOfPlayerMissile, true);
        }
        else {
            shootMissile(row, column, matrixOfPlayerMissile);
        }
        shootMissile(row, column, matrixOfMachineBoat);

        if(matrixOfMachineBoat[row][column] - MISSILE_VALUE == CARRIER_VALUE) {
            cout << "Touche" << endl;
            playerCarrier--;
            if (playerCarrier == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfMachineBoat[row][column] - MISSILE_VALUE == BATTLESHIP_VALUE) {
            cout << "Touche" << endl;
            playerBattleship--;
            if (playerBattleship == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfMachineBoat[row][column] - MISSILE_VALUE == CRUISER_VALUE) {
            cout << "Touche" << endl;
            playerCruiser--;
            if (playerCruiser == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfMachineBoat[row][column] - MISSILE_VALUE == SUBMARINE_VALUE) {
            cout << "Touche" << endl;
            playerSubmarine--;
            if (playerSubmarine == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfMachineBoat[row][column] - MISSILE_VALUE == DESTROYER_VALUE) {
            cout << "Touche" << endl;
            playerDestroyer--;
            if (playerDestroyer == 0) {
                cout << "Coule" << endl;
            }
        }
        if(_gameMode == 2) {
            setColor(5); cout << "Tour suivant" << endl; setColor(7);
            system("pause");
            system("cls");
            round++;
        }
        else {
            system("pause"); system("cls");
            setColor(5); cout << "Changement de sens" << endl; setColor(7);
            system("pause");
        }
    }

    // Joueur 2
    else if (!_isForPlayer && _gameMode != 2) {
        system("cls");
        cout << "----- Tour du JOUEUR 2 -----\n" << endl;
        cout << "Tour : " << round++ << endl;
        cout << "joueur 1 (" << MAX_SCORE - playerScore << "), joueur 2 (" << MAX_SCORE - machineScore << ")" << endl;
        cout << "Plateau joueur 2 : " << endl;
        printMatrix(matrixOfMachineBoat);
        cout << endl;
        cout << "Missiles envoyer par joueur 2 : " << endl;
        printMatrix(matrixOfMachineMissile);
        cout << endl;

        // Obtenire les coordonées du tir
        while (isntGoodMove) {
            positionToMatrix();
            if (isGoodMove(row, column, matrixOfPlayerBoat)) {
                isntGoodMove = false;
            }
        }

        // Effectuer le tir de missile
        if(matrixOfPlayerBoat[row][column] != DEFAULT_VALUE) {
            shootMissile(row, column, matrixOfMachineMissile, true);
        }
        else {
            shootMissile(row, column, matrixOfMachineMissile);
        }
        shootMissile(row, column, matrixOfPlayerBoat);

        if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == CARRIER_VALUE) {
            cout << "Touche" << endl;
            machineCarrier--;
            if (machineCarrier == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == BATTLESHIP_VALUE) {
            cout << "Touche" << endl;
            machineBattleship--;
            if (machineBattleship == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == CRUISER_VALUE) {
            cout << "Touche" << endl;
            machineCruiser--;
            if (machineCruiser == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == SUBMARINE_VALUE) {
            cout << "Touche" << endl;
            machineSubmarine--;
            if (machineSubmarine == 0) {
                cout << "Coule" << endl;
            }
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == DESTROYER_VALUE) {
            cout << "Touche" << endl;
            machineDestroyer--;
            if (machineDestroyer == 0) {
                cout << "Coule" << endl;
            }
        }
        system("pause"); system("cls");
        setColor(5); cout << "Changement de sens" << endl; setColor(7);
        system("pause");
    }

    // Machine
    else {
        // Obtenire les coordonées du tir
        positionToMatrix(true, 0, playRandomMove());

        // Effectuer le tir de missile
        if(matrixOfPlayerBoat[row][column] != DEFAULT_VALUE) {
            shootMissile(row, column, matrixOfMachineMissile, true);
        }
        else {
            shootMissile(row, column, matrixOfMachineMissile);
        }
        shootMissile(row, column, matrixOfPlayerBoat);

        if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == CARRIER_VALUE) {
            machineCarrier--;
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == BATTLESHIP_VALUE) {
            machineBattleship--;
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == CRUISER_VALUE) {
            machineCruiser--;
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == SUBMARINE_VALUE) {
            machineSubmarine--;
        }
        else if(matrixOfPlayerBoat[row][column] - MISSILE_VALUE == DESTROYER_VALUE) {
            machineDestroyer--;
        }
    }

    scoreMAJ(); // Mets à jour les varibles de score
}

void shootMissile(int _row, int _column, int _matrixToEdit[10][10], bool _isTouch) {
    if (_isTouch) {
        _matrixToEdit[_row][_column] += GOOD_MISSILE_VALUE;
    }
    else {
        _matrixToEdit[_row][_column] += MISSILE_VALUE;
    }
}

void scoreMAJ() {
    playerScore = playerCarrier + playerBattleship + playerCruiser + playerSubmarine + playerDestroyer;
    machineScore = machineCarrier + machineBattleship + machineCruiser + machineSubmarine +  machineDestroyer;
}

void positionToMatrix(int _isntForBoatInit, int _boatID, string _externalMove) {
    string move;
    bool isntGoodEntry(true);

    if(_externalMove != "N/A") {
        char letter = toupper(_externalMove[0]);
        int number = stoi(_externalMove.substr(1));
        column = letter - 'A';
        row = number - 1;
        return;
    }

    while (isntGoodEntry) {
        if (_isntForBoatInit) {
            cout << "Quel sera votre prochain mouvement > ";
            cin >> move;
        }
        else {
            cout << "Quel est la position du votre " << boat[_boatID] << " > ";
            cin >> move;
        }
        // Vérification que l'entrée est valide (format lettreChiffre, ex : A1)
        if (move.length() >= 2 && isalpha(move[0]) && isdigit(move[1])) {
            char letter = toupper(move[0]); // Convertir la lettre en majuscule et l'extrait
            try {
                int number = stoi(move.substr(1)); // Supprime le premier caractère

                // Vérification : (lettre A-J, chiffre 1-10)
                if (letter >= 'A' && letter <= 'J' && number >= 1 && number <= 10) {
                    column = letter - 'A';      // Convertir la lettre en colonne (0 à 9)
                    row = number - 1;           // Convertir le chiffre en ligne (0 à 9)
                    isntGoodEntry = false;      // Sortir de la boucle
                } else {
                    setColor(4); cout << "Entrez une position valide (ex: A1, B5... J10).\n"; setColor(7);
                }
            } catch (const invalid_argument &) { // Permet d'éviter le crash du programe
                setColor(4); cout << "Erreur : entrée invalide. Entrez une position comme A1 ou J10.\n"; setColor(7);
            }
        } else {
            setColor(4); cout << "Entrez une position valide (ex: A1, B5... J10).\n"; setColor(7);
        }
    }
}

void initAvalableMoves() {
    int index(0);
    for (char col = 'A'; col <= 'J'; ++col) {
        for (int row = 1; row <= 10; ++row) {
            availableMoves[index] = string(1, col) + to_string(row);
            ++index;
        }
    }
}