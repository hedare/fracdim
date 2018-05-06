#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
class Cluster {
public:
    string input;
    string clusterName;
    string clusterPath;
    string folderPath = "../";
    bool clusterLoaded = false;
    bool radiiBool = false;
    bool radiiSorted = false;
    int dimension;
    int particleCount = 0;
    vector<vector<double>> particles;
    vector<double> radii;
    vector<double> sortedRadii;
    Cluster() {};
    bool getClusterPath();
    bool load();
    void checkCommands();
    void getRadii();
    void sortRadii();
    void trara(int stepSize);
    void kugvol(int stepNumber);
    void kugschal(int stepNumber);
    void boxcount();
    void renyi();
    void correlation();
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
    if (input.size() != 8) {
        cout << "invalid input, please try again" << endl;
        return false;
    }
    if (!getClusterPath()) {
        cout << "invalid input, please try again" << endl;
        return false;
    }
    ifstream reader(folderPath + clusterPath);
    if (!reader) {
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
            switch (wordCount) {
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
            particles[particleCount].push_back(stod(word));
            word = "";
        }
        else if (letter == '\n') {
            particleCount++;
            if (particleCount % 10000 == 0) {
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
        if (input == "back") {
            clusterLoaded = false;
            radiiBool = false;
            radiiSorted = false;
            particleCount = 0;
        }
        else if (input == "help") {
            cout << "'back' to load another cluster" << endl <<
                "'exit' to quit the program" << endl <<
                "'trara [stepSize]' to run the tragheitsradius method" << endl <<
                "'kugvol [stepNumber]' for the kugelvolumen method" << endl <<
                "'kugschal [stepNumber]' for the kugelschalen method" << endl <<
                "'boxcount' for the boxcounting method (not yet implemented)" << endl <<
                "'renyi' to derive the renyi dimension (not yet implemented)" << endl <<
                "'corr' to get the correlation dimension (not yet implemented)" << endl <<
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
        else if (input == "boxcount") {
            boxcount();
        }
        else {
            cout << "invalid command" << endl;
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
    return;
}
void Cluster::getRadii() {
    if (!radiiBool) {
        vector<double> coordSum(dimension);
        double rSquared = 0;
        radii.resize(particleCount);
        for (int i = 1; i <= particleCount; i++) {
            for (int j = 0; j < dimension; j++) {
                coordSum[j] += particles[i - 1][j];
                rSquared += (particles[i - 1][j] - coordSum[j] / i) * (particles[i - 1][j] - coordSum[j] / i);
            }
            radii[i - 1] = rSquared;
            rSquared = 0;
        }
        radiiBool = true;
    }
    return;
}
void Cluster::sortRadii() {
    getRadii();
    if (!radiiSorted) {
        sortedRadii = radii;
        sort(sortedRadii.begin(), sortedRadii.end());
        radiiSorted = true;
    }
    return;
}
void Cluster::trara(int stepSize) {
    string filePath = "octave/" + clusterName + "trara" + to_string(stepSize) + ".txt";
    ofstream traraWriter(folderPath + filePath);
    double RGsquared = 0;
    getRadii();
    for (int i = 1; i <= particleCount; i++) {
        RGsquared += radii[i - 1];
        if (i % stepSize == 0) {
            traraWriter << log(i) << "," << log(RGsquared / i) << endl;
        }
    }
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::kugvol(int stepNumber) {
    string filePath = "octave/" + clusterName + "kugvol" + to_string(stepNumber) + ".txt";
    ofstream kugvolWriter(folderPath + filePath);
    sortRadii();
    int counter = 0;
    double maxRadius = sortedRadii[particleCount - 1];
    double stepSize = maxRadius / stepNumber;
    for (int i = 1; i < stepNumber; i++) {
        while (sortedRadii[counter] < i * stepSize) {
            counter++;
        }
        kugvolWriter << log(counter) << "," << log(i * stepSize) << endl;
    }
    kugvolWriter << log(particleCount) << "," << log(maxRadius) << endl;
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::kugschal(int stepNumber) {
    string filePath = "octave/" + clusterName + "kugschal" + to_string(stepNumber) + ".txt";
    ofstream kugschalWriter(folderPath + filePath);
    sortRadii();
    int counter;
    double maxRadius = sortedRadii[particleCount - 1];
    double stepSize = maxRadius / stepNumber;
    for (int i = 1; i < stepNumber; i++) {
        counter = 0;
        while (sortedRadii[counter] < i * stepSize) {
            counter++;
        }
        kugschalWriter << log(counter / (pow(i, dimension) - pow(i - 1, dimension))) << "," << log(i * stepSize) << endl;
    }
    kugschalWriter << log(particleCount / (pow(stepNumber, dimension) - pow(stepNumber - 1, dimension))) << "," << log(maxRadius) << endl;
    cout << "data saved in " << filePath << endl;
    return;
}
void Cluster::boxcount() {

    return;
}
void Cluster::renyi() {

    return;
}
void Cluster::correlation() {

    return;
}
int main() {
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
