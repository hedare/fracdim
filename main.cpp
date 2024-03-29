#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm> //implementiert die sort()-funktion
#include <time.h>
using namespace std;
class Cluster {
public:
	string input;
	string clusterName;
	string clusterPath;
    string folderPath = "../"; //Pfad von dem Ausf�hrungsort des Programms zum Ordner 'dla'
	bool clusterLoaded = false; //gibt an, ob ein Cluster, bzw. seine Teilchenkoordinaten (particles), geladen wurde
	double maxRadius = 0;
	int dimension; //Raumdimension d
    int particleCount = 0; //Anzahl N der Teilchen
    vector<vector<double>> particles; // Nxd-Matrix aller Teilchenkoordinaten
	vector<double> centerOfMass; //d-Vektor, Schwerpunktkoordinaten
	vector<double> radii; //N-Vektor, Schwerpunktsabst�nde aller Teilchen
	vector<double> sortedRadii; //N-Vektor, sortierte radii
	vector<vector<double>> range = { {},{},{} }; //3xd-Vektor, kleinste und gr��te Koordinate in jeder Dimension und ihre Differenz
	vector<unsigned long long int> boxes;
    Cluster() {}
    bool getClusterPath(); //setzt den Namen und den Pfad zu dem  jeweiligen Cluster (hart gecodet)
	bool load(); //l�dt die Koordinaten aller Teilchen des eingegebenen Clusters
	void checkCommands(); //�berpr�ft den Input auf die eingebauten Befehle
	void getCenterOfMass(); //berechnet den Schwerpunkt des Clusters
	void getRadii(); //berechnet die quadratischen Abst�nde aller Teilchen zum Schwerpunkt des Clusters
	void sortRadii(); //sortiert die in in getRadii berechneten Abst�nde aufsteigend
	void getMaxRadius(); //berechnet den Abstand des am weitesten vom Schwerpunkt des Clusters entfernten Teilchens
	void getRange(); //bestimmt die kleinsten und gr��ten Teilchenkoordinaten in jeder Dimension, sowie ihre Differenz
	void getBoxes(double boxlength); //bestimmt die Anzahl an Boxen (Hyperw�rfeln), mit denen der Cluster �berdeckt werden kann, in Abh�ngigkeit von deren Kantenl�nge
	void trara1(int stepNumber); //berechnet den Tr�gheitsradius in Abh�ngigkeit von der Teilchenzahl, Teilchen nach Abstand zum Schwerpunkt sortiert
	void trara2(int stepNumber); //berechnet den Tr�gheitsradius in Abh�ngigkeit von der Teilchenzahl, Teilchen in zeitlicher Reihenfolge
	void kugvol(int stepNumber); //bestimmt die Anzahl der Teilchen innerhalb einer Hyperkugel um den Schwerpunkt in Abh�ngigkeit von deren Radius
	void kugschal(int stepNumber); //bestimmt die Anzahl der Teilchen innerhalb einer Hyperkugelschale fester Dicke in Abh�ngigkeit von deren Radius
	void boxcount(int stepNumber); //bestimmt die fraktale Dimension nach der Boxcountingmethode
	void info(int stepNumber);
	void renyi(double q);
	void correl(int stepNumber);
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
    if (input.substr(0, 4) == "test") {
        try {
            dimension = stoi(input.substr(5, input.size() - 5));
            particleCount = 10000000;
            particles.resize(particleCount);
            clusterName = "test" + to_string(dimension);
            for (int i = 0; i < particleCount; i++) {
                for (int j = 0; j < dimension; j++) {
                    particles[i].push_back(rand());
                }
                if ((i + 1) % 1000000 == 0) {
                    cout << i + 1 << " particles created" << endl;
                }
            }
            cout << "cluster " << clusterName << " created successfully" << endl;
            return true;
        }
        catch (...) {
            cout << "please pick an integer from 2 to 10" << endl;
            return false;
        }
    }
	if (!getClusterPath()) { //wendet getClusterPath an, welches false ausgibt, wenn der input nicht korrekt ist
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
            particles[particleCount].push_back(stod(word)); //schreibt die koordinaten in particles
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
		if (input == "back") { //l�scht bestimmte variablen, damit ein neuer cluster geladen werden kann
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
				"'trara1 [stepNumber]' to run the tragheitsradius method (radial)" << endl <<
				"'trara2 [stepNumber]' to run the alternative tragheitsradius method (chronological)" << endl <<
				"'kugvol [stepNumber]' for the kugelvolumen method" << endl <<
				"'kugschal [stepNumber]' for the kugelschalen method" << endl <<
				"'boxcount [stepNumber]' for the boxcounting method" << endl <<
				"'info [stepNumber]' to derive the information dimension" << endl <<
				"`renyi [q]' to get the renyi dimension" << endl <<
				"'correl [stepNumber]' to get the correlation dimension (not yet implemented)" << endl <<
				"[stepNumber] is an integer, [q] is a double" << endl;
		}
		else if (input.substr(0, 6) == "trara1") {
			trara1(stoi(input.substr(7, input.size() - 7)));
		}
		else if (input.substr(0, 6) == "trara2") {
			trara2(stoi(input.substr(7, input.size() - 7)));
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
			info(stoi(input.substr(5, input.size() - 5)));
		}
		else if (input.substr(0, 5) == "renyi") {
			renyi(stod(input.substr(6, input.size() - 6)));
		}
		else if (input.substr(0, 6) == "correl") {
			correl(stoi(input.substr(7, input.size() - 7)));
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
				centerOfMass[j] += particles[i][j]; //mittelt die koordinatenwerte f�r alle teilchen in jeder dimension
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
				rSquared += (particles[i][j] - centerOfMass[j]) * (particles[i][j] - centerOfMass[j]); //berechnet den quadratischen abstand zum schwerpunkt f�r jedes teilchen
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
			for (int i = 0; i < particleCount; i++) { //durchsucht alle abst�nde nach dem gr��ten unter ihnen
				if (radii[i] > rmax) {
					rmax = radii[i];
				}
			}
			maxRadius = sqrt(rmax);
		}
		else {
			maxRadius = sqrt(sortedRadii[particleCount - 1]); //wenn die abst�nde schon sortiert sind, ist die letzte komponente von sortedRadii der gr��te abstand
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
				else if (particles[i][j] > range[1][j]) { //sucht nach der gr��ten koordinate unter allen teilchen in jeder dimension
					range[1][j] = particles[i][j];
				}
			}
			range[2][j] = range[1][j] - range[0][j]; //berechnet die ausdehnung des clusters in jeder dimension
		}
	}
	return;
}
void Cluster::getBoxes(double boxlength) {
	unsigned long long int box; //N-Vektor, enth�lt f�r jedes teilchen die nummer dessen zugeordneter boxmaxBox = 1;
	unsigned long long int maxBox = 1; //h�chstm�glicher Boxindex
	double invertedBoxlength = 1 / boxlength;
	vector<int> boxRange(dimension + 1);
	boxRange[dimension] = 1;
	for (int j = 0; j < dimension; j++) {
		boxRange[j] = (int)(range[2][j] * invertedBoxlength + 1); //rundet die koordinaten des teilchens auf den n�chsten gitterpunkt
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
void Cluster::trara1(int stepNumber) {
	string filePath = "octave/trara/" + clusterName + "trara1_" + to_string(stepNumber) + ".txt"; //dateiname enth�lt die methode und die schrittweite
	ofstream traraWriter(folderPath + filePath);
	double RGsquared = 0;
	sortRadii();
	double currentStep = 1;
	double stepSize = pow(particleCount / currentStep, 1.0 / stepNumber);
	for (int i = 1; i <= particleCount; i++) {
		RGsquared += sortedRadii[i - 1];
		if (i % (int)currentStep == 0) {
			traraWriter << log(i) << "," << log(RGsquared / i) << endl; //schreibt die daten log(teilchenzahl),log(mittlerer quadratischer abstand dieser teilchen) in die datei
			currentStep = currentStep * stepSize + 1;
		}
	}
	traraWriter << log(particleCount) << "," << log(RGsquared / particleCount) << endl;
	cout << "data saved in " << filePath << endl;
	return;
}
void Cluster::trara2(int stepNumber) {
	string filePath = "octave/trara/" + clusterName + "trara2_" + to_string(stepNumber) + ".txt"; //dateiname enth�lt die methode und die schrittweite
	ofstream traraWriter(folderPath + filePath);
	double RGsquared = 0;
	getRadii();
	double currentStep = 1;
	double stepSize = pow(particleCount / currentStep, 1.0 / stepNumber);
	for (int i = 1; i <= particleCount; i++) {
		RGsquared += radii[i - 1];
		if (i % (int)currentStep == 0) {
			traraWriter << log(i) << "," << log(RGsquared / i) << endl; //schreibt die daten log(teilchenzahl),log(mittlerer quadratischer abstand dieser teilchen) in die datei
			currentStep = currentStep * stepSize + 1;
		}
	}
	traraWriter << log(particleCount) << "," << log(RGsquared / particleCount) << endl;
	cout << "data saved in " << filePath << endl;
	return;
}
void Cluster::kugvol(int stepNumber) {
	string filePath = "octave/kugvol/" + clusterName + "kugvol" + to_string(stepNumber) + ".txt"; //datei enth�lt die methode und die schrittzahl
	ofstream kugvolWriter(folderPath + filePath);
	sortRadii();
	getMaxRadius();
	int counter = 0;
	double currentStep = 0.5;
	double stepSize = pow(maxRadius / currentStep, 1.0 / stepNumber);
	while (currentStep < maxRadius) {
		while (sortedRadii[counter] < currentStep * currentStep) {
			counter++;
		}
		kugvolWriter << log(counter) << "," << log(currentStep) << endl; //schreibt die daten log(anzahl der teilchen in einer kugel um den schwerpunkt),log(radius der kugel) in die datei
		currentStep = currentStep * stepSize;
	}
	kugvolWriter << log(particleCount) << "," << log(maxRadius) << endl;
	cout << "data saved in " << filePath << endl;
	return;
}
void Cluster::kugschal(int stepNumber) {
	string filePath = "octave/kugschal/" + clusterName + "kugschal" + to_string(stepNumber) + ".txt"; //datei enth�lt die methode und die schrittzahl
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
		kugschalWriter << log(counter / (pow(i, dimension) - pow(i - 1, dimension))) - dimLogStepSize << "," << log(i * stepSize) << endl; //schreibt die daten log(anzahl der teilchen in einer kugelschale um den schwerpunkt),log(radius der �u�eren kugel) in die datei
	}
	kugschalWriter << log(particleCount / (pow(stepNumber, dimension) - pow(stepNumber - 1, dimension))) - dimLogStepSize << "," << log(maxRadius) << endl;
	cout << "data saved in " << filePath << endl;
	return;
}
void Cluster::boxcount(int stepNumber) {
	string filePath = "octave/boxcount/" + clusterName + "boxcount" + to_string(stepNumber) + ".txt"; //dateiname enth�lt die methode und die schrittzahl
	ofstream boxcountWriter(folderPath + filePath);
	getMaxRadius();
	getRange();
	double boxlength = 1;
	double stepSize = pow (maxRadius / boxlength, 1.0 / stepNumber);
	boxes.resize(particleCount);
	int counter = 0;
	int k = 0;
	while (boxlength < maxRadius) {
		k++;
		cout << "k " << k;
		getBoxes(boxlength);
		counter = 1;
		for (int i = 0; i < particleCount - 1; i++) { //bestimmt die anzahl verschiedener boxen
			if (boxes[i] != boxes[i + 1]) {
				counter++;
			}
		}
		cout << " boxes " << counter << endl;
		boxcountWriter << log(counter) << "," << log(boxlength) << endl;
		boxlength = boxlength * stepSize;
	}
	cout << "data saved in " << filePath << endl;
	return;
}
void Cluster::info(int stepNumber) {
	string filePath = "octave/info/" + clusterName + "info" + to_string(stepNumber) + ".txt"; //dateiname enth�lt die methode und die schrittzahl
	ofstream infoWriter(folderPath + filePath);
	getMaxRadius();
	getRange();
	double boxlength = 0.1;
	double maxBoxlength = 0.1 * maxRadius;
	double stepSize = pow(maxBoxlength / boxlength, 1.0 / stepNumber);
	double infoFunction;
	boxes.resize(particleCount);
	int counter = 0;
	double logCounter;
	int k = 1;
	while (boxlength < maxBoxlength) {
		cout << "k " << k;
		getBoxes(boxlength);
		counter = 1;
		for (int i = 0; i < particleCount - 1; i++) { //bestimmt die anzahl verschiedener boxen
			if (boxes[i] != boxes[i + 1]) {
				counter++;
			}
		}
		logCounter = log(counter);
		infoFunction = 0;
		int counter2 = 1;
		for (int i = 0; i < particleCount - 1; i++) {
			if (boxes[i] != boxes[i + 1]) { //bestimmt die anzahl der teilchen in jeder box
				infoFunction -= (log(counter2) - logCounter) * counter2 / counter;
				counter2 = 1;
			}
			else {
				counter2++;
			}
		}
		infoFunction -= (log(counter2) - logCounter) * counter2 / counter;
		cout << " boxes " << counter << endl;
		infoWriter << log(boxlength) << "," << infoFunction << endl;
		boxlength = boxlength * stepSize;
		k++;
	}
	cout << "data saved in " << filePath << endl;
	return;
}
void Cluster::renyi(double q) {
	string filePath = "octave/renyi/" + clusterName + "renyi" + to_string(q) + ".txt"; //dateiname enth�lt die methode und die schrittzahl
	ofstream infoWriter(folderPath + filePath);
	getMaxRadius();
	getRange();
	int stepNumber = 100;
	double stepSize = 0.1 * maxRadius / stepNumber;
	double boxlength;
	double pSum;
	boxes.resize(particleCount);
	int counter = 0;
	double invPowCounter;
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
		invPowCounter = pow(counter, -q);
		pSum = 0;
		int counter2 = 0;
		for (int i = 0; i < particleCount - 1; i++) {
			if (boxes[i] != boxes[i + 1]) { //bestimmt die anzahl der teilchen in jeder box
				pSum += pow(counter2, q) * invPowCounter;
				counter2 = 1;
			}
			else {
				counter2++;
			}
		}
		pSum = log(pSum + pow(counter2, q) * invPowCounter) / (q - 1);
		cout << " boxes " << counter << endl;
		infoWriter << log(boxlength) << "," << pSum << endl;
	}
	cout << "data saved in " << filePath << endl;
	return;
}
void Cluster::correl(int stepNumber) {
	string filePath = "octave/correl/" + clusterName + "correl" + to_string(stepNumber) + ".txt"; //datei enth�lt die methode und die schrittzahl
	ofstream correlWriter(folderPath + filePath);
    int dotNumber = 1000;
    double rmin = 0.5;//2
    double rmax = 20;//7.5
	double rcur = rmin;
	double dotStepSize = pow(rmax / rmin, 1.0 / dotNumber);
	vector<double> steps(dotNumber);
	vector<int> counterVec(dotNumber);
	for (int i = 0; i < dotNumber; i++) {
		counterVec[i] = 0;
		steps[i] = rcur * rcur;
		rcur = rcur * dotStepSize;
	}
	int stepSize = (int)(sqrt(particleCount) / 100);
	vector<double> currentParticle(dimension);
	vector<double> currentRadii(particleCount - 1);
	double rSquared;
	int counter;
	for (int k = 0; k < stepNumber; k++) {
		currentParticle = particles[k * stepSize];
		for (int i = 0; i < particleCount; i++) {
			rSquared = 0;
			for (int j = 0; j < dimension; j++) {
				rSquared += (particles[i][j] - currentParticle[j]) * (particles[i][j] - currentParticle[j]); //berechnet den quadratischen abstand zum aktuellen Teilchen f�r jedes teilchen
			}
			if (i < k * stepSize) {
				currentRadii[i] = rSquared;
			}
			else if (i > k * stepSize) {
				currentRadii[i - 1] = rSquared;
			}
		}
		sort(currentRadii.begin(), currentRadii.end());
		counter = 0;
		for (int i = 0; i < dotNumber; i++) {
			while (currentRadii[counter] < steps[i]) {
				counter++;
			}
			counterVec[i] += counter;
		}
		cout << "k " << k + 1 << endl;
	}
	for (int i = 0; i < dotNumber; i++) {
		correlWriter << log(steps[i]) << "," << log(counterVec[i]) << endl;
	}
	cout << "data saved in " << filePath << endl;
	return;
}
int main() { //Benutzerschnittstelle, von der aus Cluster geladen und Befehle zur Dimensionsbestimmung eingegeben werden k�nnen
	Cluster cluster = Cluster();
    srand (time(NULL));
	while (1) {
		if (!cluster.clusterLoaded) {
			cout << "available clusters:" << endl << "old:" << endl <<
				" 2D: 3, 3D: 3, 4D: 3, 5D: 2, 6D: 1, 7D: 3, 8D: 1, 9D: 1, 10D: 1, 12D: 1, 13D: 1" << endl <<
				"new:" << endl << " 7D: 4, 8D: 3, 10D: 2" << endl <<
                "test 02 - 10" << endl <<
                "pick a cluster in the form 'old 02 1' or 'new 10 2' or 'test 2' or exit" << endl;
			getline(cin, cluster.input);
			if (cluster.input == "exit") {
				return 0;
			}
			cluster.clusterLoaded = cluster.load();
		}
		else {
			cout << "available commands: help, back, exit, trara1 [N], trara2 [N] kugvol [N], kugschal [N], boxcount [N], info [N], renyi [q], correl [N]" << endl;
			getline(cin, cluster.input);
			if (cluster.input == "exit") {
				return 0;
			}
			cluster.checkCommands();
		}
	}
}
