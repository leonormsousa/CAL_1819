#include<algorithm>
#include"PoI.h"

using namespace std;

class Tourist{
    int id;
    string name;
    vector<PoI*> poIs;
public:
	Tourist(int id, string name, vector<PoI*> poIs = {});
    bool addPoI(PoI* n);
    bool removePoI(PoI* n);
    int getId(); 
    string getName();
    vector<PoI*>* getPoIs();
    bool operator==(Tourist t);
};
