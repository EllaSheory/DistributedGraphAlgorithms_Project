#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
//#define NUM_VERTEX 256
#define TIME 3

static int C;
static int NUM_VERTEX;
vector<vector<int>> graph;
bool massage[8193][8193];
int source_contractor[8193][8193];
int contractor_target[8193][8193];

void init_graph(){
    graph.clear();
    graph.resize(NUM_VERTEX);
    for(int i=0; i<NUM_VERTEX/C; i++){
        for(int j=0; j<NUM_VERTEX/C; j++){
            if(i==j) continue;
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
    }
    for(int i= NUM_VERTEX/C; i<NUM_VERTEX; i++){
        for(int j=0; j<NUM_VERTEX/C; j++){
            graph[i].push_back(j);
            graph[j].push_back(i);
        }
    }
}
void init_massage(){
    for(int i=0; i<NUM_VERTEX; i++){
        for(int j=0; j<NUM_VERTEX; j++){
            if(i==j) massage[i][j]=true;
            else massage[i][j]=false;
            source_contractor[i][j]=0;
            contractor_target[i][j]=0;
        }
    }
}
bool check_work(){
    double sum = 0;
    for(int i=0; i<NUM_VERTEX; i++){
        for(int j=0; j<NUM_VERTEX; j++){
            //if(massage[i][j]) sum++;
            if(!massage[i][j]) return false;
        }
    }
    //if(sum/(NUM_VERTEX*NUM_VERTEX)==1) return true;
    return true;
}

int can_send_massage(pair<int,pair<int,int>> m){
    if(source_contractor[m.second.first][m.first]>C) return 0;
    if(contractor_target[m.first][m.second.second]>C) return 0;
    if( massage[m.second.first][m.second.second]) return 0;
    massage[m.second.first][m.second.second]=true;
    return 1;
}

void send_massage(){

    vector<pair<int,pair<int,int>>> all_massage_in_round;
    for(int i=0; i<NUM_VERTEX; i++){
        for(int j=0; j<NUM_VERTEX; j++){
            contractor_target[i][j]=0;
            source_contractor[i][j]=0;
        }
    }
    for(int i=0; i<NUM_VERTEX; i++){
        for(int j=0; j<NUM_VERTEX; j++){
            if(!massage[i][j]){
                int x = (rand()%(NUM_VERTEX));
                if(x<NUM_VERTEX/C) {
                    all_massage_in_round.push_back(make_pair(x, make_pair(i,j)));
                }
            }
        }
    }
    for(auto a: all_massage_in_round){
        source_contractor[a.second.first][a.first]++;
        contractor_target[a.first][a.second.second]++;
    }
    int counter=0;
    for(auto a: all_massage_in_round){
        can_send_massage(a);
    }
}
int run_once(){
    init_massage();
    int round=0;
    while(!check_work()){
        round++;
    }
    return round;
}

int main(){
    srand(time(0));
//    NUM_VERTEX=X;
//     C=y;
//count num of round with run once

    return 0;
}