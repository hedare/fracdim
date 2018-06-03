#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm> //implementiert die sort()-funktion
using namespace std;
class Cluster {
public:
    string input;
    string clusterName;
    string clusterPath;
    string folderPath = "../"; //Pfad von dem Ausführungsort des Programms zum Ordner 'dla'
    bool clusterLoaded = false; //gibt an, ob ein Cluster, bzw. seine Teilchenkoordinaten (particles), geladen wurde
    double maxRadius = 0;
    int dimension; //Raumdimension d
    int particleCount = 0; //Anzahl N der Teilchen
    vector<vector<double>> particles; // Nxd-Matrix aller Teilchenkoordinaten
    vector<double> centerOfMass; //d-Vektor, Schwerpunktkoordinaten
    vector<double> radii; //N-Vektor, Schwerpunktsabstände aller Teilchen
    vector<double> sortedRadii; //N-Vektor, sortierte radii
    vector<vector<double>> range = { {},{},{} }; //3xd-Vektor, kleinste und größte Koordinate in jeder Dimension und ihre Differenz
    vector<unsigned long long int> boxes;
    Cluster() {};
    bool getClusterPath(); //setzt den Namen und den Pfad zu dem  jeweiligen Cluster (hart gecodet)
    bool load(); //lädt die Koordinaten aller Teilchen des eingegebenen Clusters
    void checkCommands(); //überprüft den Input auf die eingebauten Befehle
    void getCenterOfMass(); //berechnet den Schwerpunkt des Clusters
    void getRadii(); //berechnet die quadratischen Abstände aller Teilchen zum Schwerpunkt des Clusters
    void sortRadii(); //sortiert die in in getRadii berechneten Abstände aufsteigend
    void getMaxRadius(); //berechnet den Abstand des am weitesten vom Schwerpunkt des Clusters entfernten Teilchens
    void getRange(); //bestimmt die kleinsten und größten Teilchenkoordinaten in jeder Dimension, sowie ihre Differenz
    void getBoxes(double boxlength); //bestimmt die Anzahl an Boxen (Hyperwürfeln), mit denen der Cluster überdeckt werden kann, in Abhängigkeit von deren Kantenlänge
    void trara(int stepSize); //berechnet den Trägheitsradius in Abhängigkeit von der Teilchenzahl
    void kugvol(int stepNumber); //bestimmt die Anzahl der Teilchen innerhalb einer Hyperkugel um den Schwerpunkt in Abhängigkeit von deren Radius
    void kugschal(int stepNumber); //bestimmt die Anzahl der Teilchen innerhalb einer Hyperkugelschale fester Dicke in Abhängigkeit von deren Radius
    void boxcount(int stepNumber); //bestimmt die fraktale Dimension nach der Boxcountingmethode
    void information(int stepNumber);
    void correlation();
    void renyi();
};
bool Cluster::getClusterPath() {
    if (input == "old 02 1") {
        clusterName = "2d_50k"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 02 2") {
        clusterName = "2D_alt"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 02 3") {
        clusterName = "2D_normal"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 03 1") {
        clusterName = "3D_alt"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 03 2") {
        clusterName = "3D_altmodisch"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 03 3") {
        clusterName = "3D_normal"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 04 1") {
        clusterName = "4D_normal"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 04 2") {
        clusterName = "4DCluster"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 04 3") {
        clusterName = "4DCluster_klein"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 05 1") {
        clusterName = "D5_a"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 05 2") {
        clusterName = "D5_b"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 06 1") {
        clusterName = "D6"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 07 1") {
        clusterName = "7D_1"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 07 2") {
        clusterName = "7D_2"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 07 3") {
        clusterName = "D7"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 08 1") {
        clusterName = "D8"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 09 1") {
        clusterName = "D9"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 10 1") {
        clusterName = "D10"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 12 1") {
        clusterName = "D12"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "old 13 1") {
        clusterName = "D13"; clusterPath = "bismarks_DLA/" + clusterName;
    }
    else if (input == "new 07 1") {
        clusterName = "7D_1"; clusterPath = "dla_neu/7D/" + clusterName;
    }
    else if (input == "new 07 2") {
        clusterName = "7D_2"; clusterPath = "dla_neu/7D/" + clusterName;
    }
    else if (input == "new 07 3") {
        clusterName = "7D_3"; clusterPath = "dla_neu/7D/" + clusterName;
    }
    else if (input == "new 07 4") {
        clusterName = "7D_4"; clusterPath = "dla_neu/7D/" + clusterName;
    }
    else if (input == "new 08 1") {
        clusterName = "8D_1"; clusterPath = "dla_neu/8D/" + clusterName;
    }
    else if (input == "new 08 2") {
        clusterName = "8D_2"; clusterPath = "dla_neu/8D/" + clusterName;
    }
    else if (input == "new 08 3") {
        clusterName = "8D_3"; clusterPath = "dla_neu/8D/" + clusterName;
    }
    else if (input == "new 10 1") {
        clusterName = "10D_1"; clusterPath = "dla_neu/10D/" + clusterName;
    }
    else if (input == "new 10 2") {
        clusterName = "10D_2"; clusterPath = "dla_neu/10D/" + clusterName;
    }
    else {
        cout << "cluster not found, please check your input" << endl;
        return false;
    }
    return true;
}
bool Cluster::load() {
    if (input.size() != 8) { //korrekter input besteht immer aus 8 zeichen
        cout << "invalid input, please try again" << endl;
        return false;
    }
    if (!getClusterPath()) { //wendet getClusterPath, welches false ausgibt, wenn der input nicht korrekt ist
        cout << "invalid input, please try again" << endl;
        return false;
    }
    ifstream reader(folderPath + clusterPath);
    if (!reader) { //gibt false aus, wenn die datei nicht gefunden wurde
        cout << "error opening cluster file" << endl;
        return false;
    }
    char letter;
    string word = "";
    int wordCount = 0;
    int totalParticles;
    do {
        reader.get(letter);
        if (letter == ' ') {
            wordCount++;
            switch (wordCount) { //liest die raumdimension und die teilchenzahl aus der ersten zeile der datei
            case 1:
                dimension = stoi(word);
                break;
            case 2:
                totalParticles = stoi(word);
                cout << "about to load " << totalParticles << " particles..." << endl;
            default:
                break;
            }
            word = "";
        }
        else {
            word += letter;
        }
    } while (letter != '\n');
    word = "";
    particles.resize(totalParticles);
    while (!reader.eof()) {
        reader.get(letter);
        if (letter == ' ') {
            particles[particleCount].push_back(stod(word)); //schreibt die korrdinaten in particles
            word = "";
        }
        else if (letter == '\n') {
            particleCount++;
            if (particleCount % 100000 == 0) {
                cout << particleCount << " particles loaded" << endl;
            }
        }
        else {
            word += letter;
        }
    }
    particleCount--;
    cout << "cluster " << clusterName << " loaded successfully" << endl;
    return true;
}
void Cluster::checkCommands() {
    try {
        if (input == "back") { //löscht bestimmte variablen, damit ein neuer cluster geladen werden kann
            particles.clear();
            centerOfMass.clear();
            radii.clear();
            sortedRadii.clear();
            particleCount = 0;
            clusterLoaded = false;
        }
        else if (input == "help") {
            cout << "'back' to load another cluster" << endl <<
                "'exit' to quit the program" << endl <<
                "'trara [stepSize]' to run the tragheitsradius method" << endl <<
                "'kugvol [stepNumber]' for the kugelvolumen method" << endl <<
                "'kugschal [stepNumber]' for the kugelschalen method" << endl <<
                "'boxcount [stepNumber]' for the boxcounting method" << endl <<
                "'info [stepNumber' to derive the information dimension" << endl <<
                "'corr' to get the correlation dimension (not yet implemented)" << endl <<
                "`renyi' to get the renyi dimension (not yet implemented)" << endl <<
                "[stepSize] and [stepNumber] are integers" << endl;
        }
        else if (input.substr(0, 5) == "trara") {
            trara(stoi(input.substr(6, input.size() - 6)));
        }
        else if (input.substr(0, 6) == "kugvol") {
            kugvol(stoi(input.substr(7, input.size() - 7)));
        }
        else if (input.substr(0, 8) == "kugschal") {
            kugschal(stoi(input.substr(9, input.size() - 9)));
        }
        else if (input.substr(0, 8) == "boxcount") {
            boxcount(stoi(input.substr(9, input.size() - 9)));
        }
        else if (input.substr(0, 4) == "info") {
            information(stoi(input.substr(5, input.size() - 5)));
        }
        else {
            cout << "invalid command" << endl;
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl; //outputtet den error text
    }
    return;
}
void Cluster::getCenterOfMass() {
    if (centerOfMass.empty()) {
        centerOfMass.resize(dimension);
        for (int j = 0; j < dimension; j++) {
           for (int i = 0; i < particleCount; i++) {
                centerOfMass[j] += particles[i][j]; //mittelt die koordinatenwerte für alle teilchen in jeder dimension
           }
           centerOfMass[j] = centerOfMass[j] / particleCount;
        }
    }
    return;
}
void Cluster::getRadii() {
    getCenterOfMass();
    if (radii.empty()) {
        double rSquared;
        radii.resize(particleCount);
        for (int i = 0; i < particleCount; i++) {
            rSquared = 0;
            for (int j = 0; j < dimension; j++) {
                rSquared += (particles[i][j] - centerOfMass[j]) * (particles[i][j] - centerOfMass[j]); //berechnet den quadratischen abstand zum schwerpunkt für jedes teilchen
            }
            radii[i] = rSquared;
        }
    }
    return;
}
void Cluster::sortRadii() {
    getRadii();
    if (sortedRadii.empty()) {
        sortedRadii = radii;
        sort(sortedRadii.begin(), sortedRadii.end()); //eingebaute funktion aus der algorithm bibliothek
    }
    return;
}
void Cluster::getMaxRadius() {
    if (maxRadius == 0) {
        if (sortedRadii.empty()) {
            double rmax = 0;
            getRadii();
            for (int i = 0; i < particleCount; i++) { //durchsucht alle abstände nach dem größten unter ihnen
                if (radii[i] > rmax) {
                    rmax = radii[i];
                }
            }
            maxRadius = sqrt(rmax);
        }
        else {
            maxRadius = sqrt(sortedRadii[particleCount - 1]); //wenn die abstände schon sortiert sind, ist die letzte komponente von sortedRadii der größte abstand
        }
    }
    return;
}
void Cluster::getRange() {
    if (range[0].empty()) {
        range[0].resize(dimension);
        range[1].resize(dimension);
        range[2].resize(dimension);
        for (int j = 0; j < dimension; j++) {
            for (int i = 0; i < particleCount; i++) {
                if (particles[i][j] < range[0][j]) { //sucht nach der kleinsten koordinate unter allen teilchen in jeder dimension
                    range[0][j] = particles[i][j];
                }
                else if (particles[i][j] > range [1][j]) { //sucht nach der größten koordinate unter allen teilchen in jeder dimension
                    range[1][j] = particles[i][j];
                }
            }
            range[2][j] = range[1][j] - range[0][j]; //berechnet die ausdehnung des clusters in jeder dimension
        }
    }
    return;
}
void Cluster::getBoxes(double boxlength) {
    unsigned long long int box; //N-Vektor, enthält für jedes teilchen die nummer dessen zugeordneter boxmaxBox = 1;
    unsigned long long int maxBox = 1; //höchstmöglicher Boxindex
    double invertedBoxlength = 1 / boxlength;
    vector<int> boxRange(dimension + 1);
    boxRange[dimension] = 1;
    for (int j = 0; j < dimension; j++) {
        boxRange[j] = (int)(range[2][j] * invertedBoxlength + 1); //rundet die koordinaten des teilchens auf den nächsten gitterpunkt
        maxBox = maxBox * boxRange[j];
    }
    cout << " maxbox " << maxBox;
    for (int i = 0; i < particleCount; i++) {
        box = 0;
        for (int j = 0; j < dimension; j++) {
            box += (int)((particles[i][j] - range[0][j]) * invertedBoxlength + 0.5);
            box = box * boxRange[j + 1];
        }
        boxes[i] = box; //jede den teilchen zugeordnete box bekommt einen int zugewiesen, der eindeutig die position der box beschreibt
    }
    sort(boxes.begin(), boxes.end()); //sortiert die zugeordneten boxen
}
void Cluster::trara(int stepSize) {
    string filePath = "octave/trara/" + clusterName + "trara" + to_string(stepSize) + ".txt"; //dateiname enthält die methode und die schrittweite
    ofstream traraWriter(folderPath + filePath);
    double RGsquared = 0;
    getRadii();
    for (int i = 1; i <= particleCount; i++) {
        RGsquared += radii[i - 1];
        if (i % stepSize == 0) {
            traraWriter << log(i) << "," << log(RGsquared / i) << endl; //schreibt die daten log(teilchenzahl),log(mittlerer quadratischer abstand dieser teilchen) in die datei
        }
    }
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::kugvol(int stepNumber) {
    string filePath = "octave/kugvol/" + clusterName + "kugvol" + to_string(stepNumber) + ".txt"; //datei enthält die methode und die schrittzahl
    ofstream kugvolWriter(folderPath + filePath);
    sortRadii();
    getMaxRadius();
    int counter = 0;
    double stepSize = maxRadius / stepNumber;
    for (int i = 1; i < stepNumber; i++) {
        while (sortedRadii[counter] < i * i * stepSize * stepSize) {
            counter++;
        }
        kugvolWriter << log(counter) << "," << log(i * stepSize) << endl; //schreibt die daten log(anzahl der teilchen in einer kugel um den schwerpunkt),log(radius der kugel) in die datei
    }
    kugvolWriter << log(particleCount) << "," << log(maxRadius) << endl;
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::kugschal(int stepNumber) {
    string filePath = "octave/kugschal/" + clusterName + "kugschal" + to_string(stepNumber) + ".txt"; //datei enthält die methode und die schrittzahl
    ofstream kugschalWriter(folderPath + filePath);
    sortRadii();
    getMaxRadius();
    int counter;
    double stepSize = maxRadius / stepNumber;
    double dimLogStepSize = dimension * log(stepSize);
    for (int i = 1; i < stepNumber; i++) {
        counter = 0;
        while (sortedRadii[counter] < i * i * stepSize * stepSize) {
            counter++;
        }
        kugschalWriter << log(counter / (pow(i, dimension) - pow(i - 1, dimension))) - dimLogStepSize << "," << log(i * stepSize) << endl; //schreibt die daten log(anzahl der teilchen in einer kugelschale um den schwerpunkt),log(radius der äußeren kugel) in die datei
    }
    kugschalWriter << log(particleCount / (pow(stepNumber, dimension) - pow(stepNumber - 1, dimension))) - dimLogStepSize  << "," << log(maxRadius) << endl;
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::boxcount(int stepNumber) {
    string filePath = "octave/boxcount/" + clusterName + "boxcount" + to_string(stepNumber) + ".txt"; //dateiname enthält die methode und die schrittzahl
    ofstream boxcountWriter(folderPath + filePath);
    getMaxRadius();
    getRange();
    double stepSize = maxRadius / stepNumber;
    double boxlength;
    boxes.resize(particleCount);
    int counter = 0;
    for (int k = 1; k <= stepNumber; k++) {
        cout << "k " << k;
        boxlength = stepSize * k;
        getBoxes(boxlength);
        counter = 1;
        for (int i = 0; i < particleCount - 1; i++) { //bestimmt die anzahl verschiedener boxen
            if (boxes[i] != boxes[i + 1]) {
                counter++;
            }
        }
        cout << " boxes " << counter << endl;
        boxcountWriter << log(counter) << "," << log(boxlength) << endl;
    }
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::information(int stepNumber) {
    string filePath = "octave/info/" + clusterName + "info" + to_string(stepNumber) + ".txt"; //dateiname enthält die methode und die schrittzahl
    ofstream infoWriter(folderPath + filePath);
    getMaxRadius();
    getRange();
    double stepSize = 0.1 * maxRadius / stepNumber;
    double boxlength;
    double infoFunction;
    boxes.resize(particleCount);
    int counter = 0;
    double logCounter;
    for (int k = 1; k <= stepNumber; k++) {
        cout << "k " << k;
        boxlength = stepSize * k;
        getBoxes(boxlength);
        counter = 1;
        for (int i = 0; i < particleCount - 1; i++) { //bestimmt die anzahl verschiedener boxen
            if (boxes[i] != boxes[i + 1]) {
                counter++;
            }
        }
        logCounter = log(counter);
        infoFunction = 0;
        int counter2 = 0;
        for (int i = 0; i < particleCount - 1; i++) {
            if (boxes[i] != boxes[i + 1]) { //bestimmt die anzahl der teilchen in jeder box
                infoFunction += (log(counter2)-logCounter)*counter2/counter;
                counter2 = 1;
            }
            else {
                counter2++;
            }
        }
        infoFunction += (log(counter2)-logCounter)*counter2/counter;
        cout << " boxes " << counter << endl;
        infoWriter << -infoFunction/log(boxlength) << "," << boxlength << endl;
    }
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::correlation() { //nicht implementiert

    return;
}
void Cluster::renyi() { //nicht implementiert

    return;
}
int main() { //Benutzerschnittstelle, von der aus Cluster geladen und Befehle zur Dimensionsbestimmung eingegeben werden können
    Cluster cluster = Cluster();
    while (1) {
        if (!cluster.clusterLoaded) {
            cout << "available clusters:" << endl << "old:" << endl <<
                " 2D: 3, 3D: 3, 4D: 3, 5D: 2, 6D: 1, 7D: 3, 8D: 1, 9D: 1, 10D: 1, 12D: 1, 13D: 1" << endl <<
                "new:" << endl << " 7D: 4, 8D: 3, 10D: 2" << endl <<
                "pick a cluster in the form 'old 02 1' or 'new 10 2' or exit" << endl;
            getline(cin, cluster.input);
            if (cluster.input == "exit") {
                return 0;
            }
            cluster.clusterLoaded = cluster.load();
        }
        else {
            cout << "available commands: help, back, exit, trara [stepSize], kugvol [stepNumber], kugschal [stepNumber]" << endl;
            getline(cin, cluster.input);
            if (cluster.input == "exit") {
                return 0;
            }
            cluster.checkCommands();
        }
    }
}
