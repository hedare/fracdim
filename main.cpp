#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <vector>
using namespace std;
class Cluster {
    public:
        string clusterName;
        string clusterPath;
        int dimension;
        int particleCount = 0;
        vector<vector<double>> particles;   //a list of all particles with their coordinates
        Cluster() {};
        ~Cluster() {};
        bool getPath(string input);
        bool load(string input);
        void tragheitsradius(int stepSize);
};
bool Cluster::getPath(string input){
    if (input == "old 02 1") {
        clusterName = "2d_50k"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 02 2") {
        clusterName = "2D_alt"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 02 3") {
        clusterName = "2D_normal"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 03 1") {
        clusterName = "3D_alt"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 03 2") {
        clusterName = "3D_altmodisch"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 03 3") {
        clusterName = "3D_normal"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 04 1") {
        clusterName = "4D_normal"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 04 2") {
        clusterName = "4DCluster"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 04 3") {
        clusterName = "4DCluster_klein"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 05 1") {
        clusterName = "D5_a"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 05 2") {
        clusterName = "D5_b"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 06 1") {
        clusterName = "D6"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 07 1") {
        clusterName = "7D_1"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 07 2") {
        clusterName = "7D_2"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 07 3") {
        clusterName = "D7"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 08 1") {
        clusterName = "D8"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 09 1") {
        clusterName = "D9"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 10 1") {
        clusterName = "D10"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 12 1") {
        clusterName = "D12"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "old 13 1") {
        clusterName = "D13"; clusterPath = "bismarks_DLA/" + clusterName;
    } else if (input == "new 07 1") {
        clusterName = "7D_1"; clusterPath = "dla_neu/7D/" + clusterName;
    } else if (input == "new 07 2") {
        clusterName = "7D_2"; clusterPath = "dla_neu/7D/" + clusterName;
    } else if (input == "new 07 3") {
        clusterName = "7D_3"; clusterPath = "dla_neu/7D/" + clusterName;
    } else if (input == "new 07 4") {
        clusterName = "7D_4"; clusterPath = "dla_neu/7D/" + clusterName;
    } else if (input == "new 08 1") {
        clusterName = "8D_1"; clusterPath = "dla_neu/8D/" + clusterName;
    } else if (input == "new 08 2") {
        clusterName = "8D_2"; clusterPath = "dla_neu/8D/" + clusterName;
    } else if (input == "new 08 3") {
        clusterName = "8D_3"; clusterPath = "dla_neu/8D/" + clusterName;
    } else if (input == "new 10 1") {
        clusterName = "10D_1"; clusterPath = "dla_neu/10D/" + clusterName;
    } else if (input == "new 10 2") {
        clusterName = "10D_2"; clusterPath = "dla_neu/10D/" + clusterName;
    } else {
        return false;
    }
    return true;
}
bool Cluster::load(string input) {
    if (input.size() != 8) {
        cout << "invalid input, please try again" << endl;
        return false;
    }
    if (!getPath(input)) {
        cout << "invalid input, please try again" << endl;
        return false;
    }
    ifstream reader("../" + clusterPath);
    if (!reader) {
        cout << "error opening cluster file" << endl;
        return false;
    }
    char letter;
    string word = "";
    int wordCount = 0;
    int totalParticles;
    do  {
        reader.get(letter);
        if (letter == ' ') {
            wordCount++;
            switch(wordCount) {
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
        } else {
            word+= letter;
        }
    } while (letter != '\n');
    word = "";
    while (particles.size() < (unsigned) totalParticles) {
        particles.push_back({});
    }
    while (!reader.eof()) {
        reader.get(letter);
        if (letter == ' ') {
            particles[particleCount].push_back(stod(word));
            word = "";
        } else if (letter == '\n') {
            particleCount++;
            if (particleCount % 10000 == 0) {
                cout << particleCount << " particles loaded" << endl;
            }
        } else {
            word+= letter;
        }
    }
    particleCount--;
    return true;
}
void Cluster::tragheitsradius(int stepSize) {
    ofstream traraWriter("../octave/" + clusterName + "trara" + to_string(stepSize) + ".txt");
    double RGsquared = 0;
    for (int i = 1; i <= particleCount; i++) {
        for (int j = 0; j < dimension; j++) {
            RGsquared+= particles[i - 1][j] * particles[i - 1][j];
        }
        if (i % stepSize == 0) {
            traraWriter << log(i) << "," << log(RGsquared / i) << endl;
        }
    }
    return;
}
int main() {
    Cluster cluster = Cluster();
    string input;
    int num;
    bool clusterLoaded = false;
    while(1){
        cout << "available clusters:" << endl << "old:" << endl <<
                " 2D: 3, 3D: 3, 4D: 3, 5D: 2, 6D: 1, 7D: 3, 8D: 1, 9D: 1, 10D: 1, 12D: 1, 13D: 1" << endl <<
                "new:" << endl << " 7D: 4, 8D: 3, 10D: 2" << endl << "pick a cluster in the form 'old 02 1' or 'new 10 2' or exit" << endl;
        while (!clusterLoaded) {
            getline(cin, input);
            if (input == "exit") {
                return 0;
            }
            clusterLoaded = cluster.load(input);
            if (clusterLoaded) {
                cout << "cluster '" << cluster.clusterName << "' loaded successfully" << endl;
            }
        }
        while (clusterLoaded) {
            cout << "available commands: 'trara' to run the tragheitsradius analysis, 'back' to load another cluster, or 'exit' to quit the program" << endl;
            getline(cin, input);
            if (input == "exit") {
                return 0;
            }
            if (input == "back") {
                clusterLoaded = false;
                cluster.particleCount = 0;
            } else if (input == "trara") {
                cout << "the current cluster contains of " << cluster.particleCount << " particles, please enter the step size" << endl;
                getline(cin, input);
                try {
                    num = stoi(input);
                    if (cluster.particleCount / num > 1000) {
                        cout << "those are " << (int) cluster.particleCount / num << " steps, are you sure? ('yes' to confirm, anything else to abort)" << endl;
                        getline(cin, input);
                        if (input == "yes") {
                            cluster.tragheitsradius(num);
                        }
                    } else {
                       cluster.tragheitsradius(num);
                    }
                }
                catch(...){
                    cout << "invalid input" << endl;
                }
                cout << "success!" << endl;
            }
        }
    }
}
