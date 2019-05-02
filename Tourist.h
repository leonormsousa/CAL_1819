#include<algorithm>
#include"PoI.h"

using namespace std;

class Tourist{
    int id;
    string name;
    vector<PoI> poIs;
public:
	Tourist(int id, string name, vector<PoI> poIs = {});
    void addPoI(PoI n);
    void removePoI(PoI n);
    int getId(); 
    string getName();
    vector<PoI> getPoIs();
};