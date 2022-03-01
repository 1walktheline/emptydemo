#include <iostream>
#include "connect.h"
#include "Precompute.h"
#include "secondary.h"
#include "tools.h"

using namespace std;
int partyNum=0;

int main(){
    cout<<"connect.h included"<<endl;
    voidConnectInit();
    emptyPrecomputeInit();
    emptySecondaryInit();
    emptyToolsInit();
    return 0;
}