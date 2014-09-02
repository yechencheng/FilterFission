#include "pin.H"
#include <iostream>
#include <fstream>
#include <set>

using namespace std;


INT32 Usage()
{
    cerr <<
        "This tool prints out the number of dynamic instructions executed to stderr.\n"
        "\n";
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}



UINT64 insCount = 0;
set<ADDRINT> addrSet;
VOID ProcessAddr(ADDRINT a){
    insCount++;
    addrSet.insert(a);
}
VOID Instruction(INS i, VOID *v)
{
    if(INS_IsMemoryRead(i)){
        INS_InsertCall(i, IPOINT_BEFORE, (AFUNPTR)ProcessAddr, IARG_MEMORYREAD_EA, IARG_END);
           if(INS_HasMemoryRead2(i))
            INS_InsertCall(i, IPOINT_BEFORE, (AFUNPTR)ProcessAddr, IARG_MEMORYREAD2_EA, IARG_END);
        }
            if(INS_IsMemoryWrite(i)){
        INS_InsertCall(i, IPOINT_BEFORE, (AFUNPTR)ProcessAddr, IARG_MEMORYWRITE_EA, IARG_END);
    }
}

int numRTN = 0;
char fileList[128];
string rtnName[128];

UINT64 ioInsCount = 0;
set<ADDRINT> ioAddrSet;

VOID ProcessIOAddr(ADDRINT a){
    ioInsCount++;
    ioAddrSet.insert(a);
}

VOID Image(IMG img, VOID *v){
    for(int i = 0; i < numRTN; i++){
        RTN myRTN = RTN_FindByName(img, rtnName[i].c_str());
        if(!RTN_Valid(myRTN)){
            //cout << "RTN is not valid or found: " << rtnName[i] << endl;
            continue;
        }
        else
            cout << "RTN is found : " << rtnName[i] << endl;

        RTN_Open(myRTN);
        INS head = RTN_InsHead(myRTN);
        INS tail = RTN_InsTail(myRTN);
        for(INS i = head; i != tail; i = INS_Next(i)){

            if(INS_IsMemoryRead(i)){
                INS_InsertCall(i, IPOINT_BEFORE, (AFUNPTR)ProcessIOAddr, IARG_MEMORYREAD_EA, IARG_END);
                if(INS_HasMemoryRead2(i))
                    INS_InsertCall(i, IPOINT_BEFORE, (AFUNPTR)ProcessIOAddr, IARG_MEMORYREAD2_EA, IARG_END);
            }
            if(INS_IsMemoryWrite(i)){
                INS_InsertCall(i, IPOINT_BEFORE, (AFUNPTR)ProcessIOAddr, IARG_MEMORYWRITE_EA, IARG_END);
            }
        }
        RTN_Close(myRTN);
    }
}

VOID Fini(INT32 code, VOID *v)
{
    cout << "io inst count : " << insCount << endl;
    cout << "Address Access : " << addrSet.size() << endl;
    cout << "target IO inst count : " << ioInsCount << endl;
    cout << "target Address Access : " << ioAddrSet.size() << endl;
}

KNOB<string> KnobInputFile(KNOB_MODE_WRITEONCE, "pintool", "i", "list.in", "input functions");
KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "rt.out", "output files");
std::ifstream InputFile;
std::ofstream OutputFile;

VOID InitInput(){
    InputFile.open(KnobInputFile.Value().c_str());

    while(InputFile >> rtnName[numRTN++])
        ;
    while(rtnName[numRTN-1].size() == 0 && numRTN > 0){
        numRTN--;
    }
}

int main(int argc, char *argv[])
{
    if( PIN_Init(argc,argv) )
    {
        return Usage();
    }
    PIN_InitSymbols();
    InitInput();    
    IMG_AddInstrumentFunction(Image, 0);
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();
    
    return 0;
}

