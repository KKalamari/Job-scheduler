#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <cstring>
#include<queue>
#include<vector>
using namespace std;

extern int concurrency;
extern int jobs;

struct triplet 
{
    string jobID;
    char* job[256];
    int queuePosition;
    pid_t pid_for_kill = 0;

};

triplet issueJob(char * args[]);
void setConcurrency(int num);
string stop(string job_id);
vector<triplet> poll(const char* situation);
void exit();
void resize();
string tripletconverte(triplet job);

extern queue<triplet> the_one;
extern vector<triplet> running;