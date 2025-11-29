#include "io.h"
#include "simulation_state.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

bool loadLevelFile(const char* filename)
{
    ifstream in(filename);
    if (!in) return false;

    string token;
    while (in >> token)
    {
        if (token=="ROWS:") in >> rows;
        else if (token=="COLS:") in >> cols;
        else if (token=="MAP:")
        {
            string line;
            getline(in,line);
            for(int r=0;r<rows;r++)
            {
                getline(in,line);
                for(int c=0;c<cols;c++)
                    grid[r][c]=line[c];
            }
        }
    }
    return true;
}

void initializeLogFiles()
{
    system("mkdir -p out");

    ofstream t("out/trace.csv");
    t << "tick,r1,c1,r2,c2,...\n";

    ofstream s("out/switches.csv");
    s << "tick,id,state\n";
}

void logTrainTrace()
{
    ofstream out("out/trace.csv", ios::app);
    out<<currentTick<<",";
    for(int i=0;i<trainCount;i++)
        out<<trainRow[i]<<":"<<trainCol[i]<<",";
    out<<"\n";
}

void logSwitchState()
{
    ofstream out("out/switches.csv",ios::app);
    for(int i=0;i<switchCount;i++)
        out<<currentTick<<","<<switchId[i]<<","<<switchState[i]<<"\n";
}

void writeMetrics()
{
    ofstream out("out/metrics.txt");
    out<<"Total trains: "<<trainCount<<"\n";
    out<<"Ticks: "<<currentTick<<"\n";
    out<<"Complete: "<<simulationComplete<<"\n";
}

void printGrid()
{
    cout<<"\n";
    for(int r=0;r<rows;r++)
    {
        for(int c=0;c<cols;c++)
        {
            bool placed=false;
            for(int t=0;t<trainCount;t++)
            {
                if(trainActive[t] && trainRow[t]==r && trainCol[t]==c)
                {
                    cout<<t;
                    placed=true;
                    break;
                }
            }
            if(!placed) cout<<grid[r][c];
        }
        cout<<"\n";
    }
    cout<<"\n";
}
