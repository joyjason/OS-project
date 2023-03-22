#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Process{
	int ID;
	int cpu_burst;
	int arrival_time;
	int priority;
	bool already;
};

class ProcessScheduling {
	public:
		void test();
		void readfile( string FileName );
		void writefile();
		void execute();
		void PP();
		void RR();
		void FCFS();
		void PSJF();
		void NSJF();
		bool Done();
		void Sort();
		void Sort_by_SJF( vector<Process> & queue , bool Preeable );
		void Sort_by_PP( vector<Process> & queue, bool Preeable );
		void Slice( int ID );
		Process WhatProcess( int ID );
	private:
		int command;
		int slice;
		vector<Process> process_list;
		vector<int> gantt_chart;
		
		
};

int main(int argc, char** argv) {
	ProcessScheduling scheduling;
	scheduling.readfile( "input999.txt" );
	scheduling.Sort();
	scheduling.execute();
	//scheduling.writefile();
}

void ProcessScheduling::test(){
		for( int i = 0; i < process_list.size() ; i++ ){
			cout << process_list[i].ID << " ";
		}
}

void ProcessScheduling::execute(){
	if ( command == 1 ) FCFS();
	else if ( command == 2 ) RR();
	else if ( command == 3 ) PSJF();
	else if ( command == 4 ) NSJF();
	else if ( command == 5 ) PP();
	//else if ( command == 6 ) ALL();
}

Process ProcessScheduling::WhatProcess( int ID ) {
	Process temp;
	for( int i = 0; i < process_list.size() ; i++ ){
		if ( process_list[i].ID == ID ) {
			temp = process_list[i];
			return temp;
		}
	}
} 

void ProcessScheduling::Slice( int ID ) {
	for (int i = 0; i < process_list.size() ; i++ ){
		if ( process_list[i].ID == ID ) process_list[i].cpu_burst = process_list[i].cpu_burst - 1;
	}
}


void ProcessScheduling::Sort(){
	for (int i = process_list.size() - 1; i > 0; i-- ){
		for (int j = 0; j < i; j++ ){
			if ( process_list[j + 1].arrival_time < process_list[j].arrival_time ) swap(process_list[j + 1],process_list[j] );
			else if ( process_list[j + 1].arrival_time == process_list[j].arrival_time ) {
				if ( process_list[j + 1].ID < process_list[j].ID )	swap(process_list[j + 1],process_list[j] );
			} 
		}
	}
	
}

void ProcessScheduling::Sort_by_SJF( vector<Process> & queue, bool Preeable ){
	for (int i = queue.size() - 1; i > 0; i-- ){
		for (int j = 0; j < i; j++ ){
			if ( queue[j + 1].cpu_burst < queue[j].cpu_burst ) {
				if ( j == 0 && Preeable ) swap(queue[j + 1],queue[j] );
				else if ( j == 0 && !Preeable && !queue[j].already ) swap(queue[j + 1],queue[j] );
				else if ( !Preeable && !queue[j].already ) swap(queue[j + 1],queue[j] );
				else if ( !Preeable && queue[j].already );
				else swap(queue[j + 1],queue[j] );
			}
			else if ( queue[j + 1].cpu_burst == queue[j].cpu_burst ) {
				//if ( queue[j + 1].already && !queue[j].already ) swap(queue[j + 1],queue[j] );
				if ( Preeable && queue[j].already ) swap(queue[j + 1],queue[j] );
			} 
		}
	}
	
}

void ProcessScheduling::Sort_by_PP( vector<Process> & queue, bool Preeable ){
	for (int i = queue.size() - 1; i > 0; i-- ){
		for (int j = 0; j < i; j++ ){
			if ( queue[j + 1].priority < queue[j].priority ) {
				if ( j == 0 && Preeable ) swap(queue[j + 1],queue[j] );
				else if ( j == 0 && !Preeable && !queue[j].already ) swap(queue[j + 1],queue[j] );
				else if ( !Preeable && !queue[j].already ) swap(queue[j + 1],queue[j] );
				else if ( !Preeable && queue[j].already );
				else swap(queue[j + 1],queue[j] );
			}
			else if ( queue[j + 1].priority == queue[j].priority ) {
				//if ( queue[j + 1].already && !queue[j].already ) swap(queue[j + 1],queue[j] );
				if ( Preeable && queue[j].already ) swap(queue[j + 1],queue[j] );
			} 
		}
	}
	
}

bool ProcessScheduling::Done(){
	for (int i = 0; i < process_list.size() ; i++ ){
		if ( process_list[i].cpu_burst > 0 ) return false;
	}
	
	return true;
}

void ProcessScheduling::FCFS(){
	for (int i = 0; i < process_list.size() ; i++ ){
		while ( process_list[i].cpu_burst > 0 ) {
			gantt_chart.push_back( process_list[i].ID );
			
			if ( process_list[i].cpu_burst - slice < 0 ) {
				process_list[i].cpu_burst = process_list[i].cpu_burst - slice;
			}
			else process_list[i].cpu_burst = process_list[i].cpu_burst - slice;;
			
		}
		fstream file;
		file.open( "output1-1.txt", ios::out );
		for (int i = 0; i < gantt_chart.size() ; i++ ){
			if ( gantt_chart[i] < 10 ) file << gantt_chart[i];
			else if ( gantt_chart[i] == 10 ) file << "A" ;
			else if ( gantt_chart[i] == 11 ) file << "B" ;
			else if ( gantt_chart[i] == 12 ) file << "C" ;
			else if ( gantt_chart[i] == 13 ) file << "D" ;
			else if ( gantt_chart[i] == 14 ) file << "E" ;
			else if ( gantt_chart[i] == 15 ) file << "F" ;
			else if ( gantt_chart[i] == 16 ) file << "G" ;
			else if ( gantt_chart[i] == 17 ) file << "H" ;
			else if ( gantt_chart[i] == 18 ) file << "I" ;
			else if ( gantt_chart[i] == 19 ) file << "J" ;
			else if ( gantt_chart[i] == 20 ) file << "K" ;
			else if ( gantt_chart[i] == 21 ) file << "L" ;
			else if ( gantt_chart[i] == 22 ) file << "M" ;
			else if ( gantt_chart[i] == 23 ) file << "N" ;
			else if ( gantt_chart[i] == 24 ) file << "O" ;
			else if ( gantt_chart[i] == 25 ) file << "P" ;
			else if ( gantt_chart[i] == 26 ) file << "Q" ;
			else if ( gantt_chart[i] == 27 ) file << "R" ;
			else if ( gantt_chart[i] == 28 ) file << "S" ;
			else if ( gantt_chart[i] == 29 ) file << "T" ;
			else if ( gantt_chart[i] == 30 ) file << "U" ;
			else if ( gantt_chart[i] == 31 ) file << "V" ;
			else if ( gantt_chart[i] == 32 ) file << "W" ;
			else if ( gantt_chart[i] == 33 ) file << "X" ;
			else if ( gantt_chart[i] == 34 ) file << "Y" ;
			else if ( gantt_chart[i] == 35 ) file << "Z" ;
		}
	}
}

void ProcessScheduling::RR(){
	int now = 1, temp = 0, i = 0; 
	vector<Process> queue;
	int MaxSlice = 0;
	now = process_list[i].arrival_time;
	while( now >= process_list[i].arrival_time && i < process_list.size() ) {
		if ( WhatProcess( process_list[i].ID ).cpu_burst > 0 ) 
			queue.push_back( process_list[i] );
			i++;	
	}
	while( !Done() ) { // ┮Τprocess常暗Чㄓ 
		if ( queue.size() != 0 ) {
			gantt_chart.push_back( queue[0].ID );
			Slice ( queue[0].ID );
			queue[0].cpu_burst--;
			temp = queue[0].ID;
			MaxSlice++;
			if ( MaxSlice == slice ||  queue[0].cpu_burst == 0 ) {	
				queue.erase( queue.begin() );
				MaxSlice = 0;
			}	
		}
		else gantt_chart.push_back( -1 );
		now++;// this second Done
		while( now >= process_list[i].arrival_time && i < process_list.size() ) {
			if ( process_list[i].cpu_burst > 0 ) 
				queue.push_back( process_list[i] );
			i++;	
		}
		if ( WhatProcess(temp).cpu_burst > 0 && MaxSlice == 0 ) queue.push_back( WhatProcess(temp));
		
	}
	
	
	
	
	fstream file;
	file.open( "outputRRRRR.txt", ios::out );
	for (int i = 0; i < gantt_chart.size() ; i++ ){
		if ( gantt_chart[i] == -1 ) file << "-" ;
		else if ( gantt_chart[i] < 10 ) file << gantt_chart[i];
		else if ( gantt_chart[i] == 10 ) file << "A" ;
		else if ( gantt_chart[i] == 11 ) file << "B" ;
		else if ( gantt_chart[i] == 12 ) file << "C" ;
		else if ( gantt_chart[i] == 13 ) file << "D" ;
		else if ( gantt_chart[i] == 14 ) file << "E" ;
		else if ( gantt_chart[i] == 15 ) file << "F" ;
		else if ( gantt_chart[i] == 16 ) file << "G" ;
		else if ( gantt_chart[i] == 17 ) file << "H" ;
		else if ( gantt_chart[i] == 18 ) file << "I" ;
		else if ( gantt_chart[i] == 19 ) file << "J" ;
		else if ( gantt_chart[i] == 20 ) file << "K" ;
		else if ( gantt_chart[i] == 21 ) file << "L" ;
		else if ( gantt_chart[i] == 22 ) file << "M" ;
		else if ( gantt_chart[i] == 23 ) file << "N" ;
		else if ( gantt_chart[i] == 24 ) file << "O" ;
		else if ( gantt_chart[i] == 25 ) file << "P" ;
		else if ( gantt_chart[i] == 26 ) file << "Q" ;
		else if ( gantt_chart[i] == 27 ) file << "R" ;
		else if ( gantt_chart[i] == 28 ) file << "S" ;
		else if ( gantt_chart[i] == 29 ) file << "T" ;
		else if ( gantt_chart[i] == 30 ) file << "U" ;
		else if ( gantt_chart[i] == 31 ) file << "V" ;
		else if ( gantt_chart[i] == 32 ) file << "W" ;
		else if ( gantt_chart[i] == 33 ) file << "X" ;
		else if ( gantt_chart[i] == 34 ) file << "Y" ;
		else if ( gantt_chart[i] == 35 ) file << "Z" ;
	}
}



void ProcessScheduling::PSJF(){
	int now = 1, temp = 0, i = 0; 
	vector<Process> queue;
	int MaxSlice = 0;
	now = process_list[i].arrival_time;
	while( now >= process_list[i].arrival_time && i < process_list.size() ) {
		if ( WhatProcess( process_list[i].ID ).cpu_burst > 0 ) 
			queue.push_back( process_list[i] );
			Sort_by_SJF( queue , true );//穖 
			i++;	
	}
	while( !Done() ) { // ┮Τprocess常暗Чㄓ 
		if ( queue.size() != 0 ) {
			gantt_chart.push_back( queue[0].ID );
			Slice ( queue[0].ID );
			queue[0].cpu_burst--;
			temp = queue[0].ID;
			queue[0].already = true;
			MaxSlice++;
			if ( queue[0].cpu_burst == 0 ) {	
				queue.erase( queue.begin() );
				MaxSlice = 0;
			}	
		}
		else gantt_chart.push_back( -1 );
		now++;// this second Done
		while( now >= process_list[i].arrival_time && i < process_list.size() ) {
			if ( process_list[i].cpu_burst > 0 ){
				queue.push_back( process_list[i] );
				Sort_by_SJF( queue , true );
			}
			i++;	
		}
		
	}
	
	
	
	
	fstream file;
	file.open( "outputRRRRR6.txt", ios::out );
	for (int i = 0; i < gantt_chart.size() ; i++ ){
		if ( gantt_chart[i] == -1 ) file << "-" ;
		else if ( gantt_chart[i] < 10 ) file << gantt_chart[i];
		else if ( gantt_chart[i] == 10 ) file << "A" ;
		else if ( gantt_chart[i] == 11 ) file << "B" ;
		else if ( gantt_chart[i] == 12 ) file << "C" ;
		else if ( gantt_chart[i] == 13 ) file << "D" ;
		else if ( gantt_chart[i] == 14 ) file << "E" ;
		else if ( gantt_chart[i] == 15 ) file << "F" ;
		else if ( gantt_chart[i] == 16 ) file << "G" ;
		else if ( gantt_chart[i] == 17 ) file << "H" ;
		else if ( gantt_chart[i] == 18 ) file << "I" ;
		else if ( gantt_chart[i] == 19 ) file << "J" ;
		else if ( gantt_chart[i] == 20 ) file << "K" ;
		else if ( gantt_chart[i] == 21 ) file << "L" ;
		else if ( gantt_chart[i] == 22 ) file << "M" ;
		else if ( gantt_chart[i] == 23 ) file << "N" ;
		else if ( gantt_chart[i] == 24 ) file << "O" ;
		else if ( gantt_chart[i] == 25 ) file << "P" ;
		else if ( gantt_chart[i] == 26 ) file << "Q" ;
		else if ( gantt_chart[i] == 27 ) file << "R" ;
		else if ( gantt_chart[i] == 28 ) file << "S" ;
		else if ( gantt_chart[i] == 29 ) file << "T" ;
		else if ( gantt_chart[i] == 30 ) file << "U" ;
		else if ( gantt_chart[i] == 31 ) file << "V" ;
		else if ( gantt_chart[i] == 32 ) file << "W" ;
		else if ( gantt_chart[i] == 33 ) file << "X" ;
		else if ( gantt_chart[i] == 34 ) file << "Y" ;
		else if ( gantt_chart[i] == 35 ) file << "Z" ;
	}
}

void ProcessScheduling::NSJF(){
	int now = 1, temp = 0, i = 0; 
	vector<Process> queue;
	int MaxSlice = 0;
	now = process_list[i].arrival_time;
	while( now >= process_list[i].arrival_time && i < process_list.size() ) {
		if ( WhatProcess( process_list[i].ID ).cpu_burst > 0 ) 
			queue.push_back( process_list[i] );
			Sort_by_SJF( queue , false );
			i++;	
	}
	while( !Done() ) { // ┮Τprocess常暗Чㄓ 
		if ( queue.size() != 0 ) {
			gantt_chart.push_back( queue[0].ID );
			Slice ( queue[0].ID );
			queue[0].cpu_burst--;
			temp = queue[0].ID;
			queue[0].already = true;
			MaxSlice++;
			if ( queue[0].cpu_burst == 0 ) {	
				queue.erase( queue.begin() );
				MaxSlice = 0;
			}	
		}
		else gantt_chart.push_back( -1 );
		now++;// this second Done
		while( now >= process_list[i].arrival_time && i < process_list.size() ) {
			if ( process_list[i].cpu_burst > 0 ){
				queue.push_back( process_list[i] );
				Sort_by_SJF( queue , false );
			}
			i++;	
		}
		
	}
	
	
	
	
	fstream file;
	file.open( "outputRRRRR6.txt", ios::out );
	for (int i = 0; i < gantt_chart.size() ; i++ ){
		if ( gantt_chart[i] == -1 ) file << "-" ;
		else if ( gantt_chart[i] < 10 ) file << gantt_chart[i];
		else if ( gantt_chart[i] == 10 ) file << "A" ;
		else if ( gantt_chart[i] == 11 ) file << "B" ;
		else if ( gantt_chart[i] == 12 ) file << "C" ;
		else if ( gantt_chart[i] == 13 ) file << "D" ;
		else if ( gantt_chart[i] == 14 ) file << "E" ;
		else if ( gantt_chart[i] == 15 ) file << "F" ;
		else if ( gantt_chart[i] == 16 ) file << "G" ;
		else if ( gantt_chart[i] == 17 ) file << "H" ;
		else if ( gantt_chart[i] == 18 ) file << "I" ;
		else if ( gantt_chart[i] == 19 ) file << "J" ;
		else if ( gantt_chart[i] == 20 ) file << "K" ;
		else if ( gantt_chart[i] == 21 ) file << "L" ;
		else if ( gantt_chart[i] == 22 ) file << "M" ;
		else if ( gantt_chart[i] == 23 ) file << "N" ;
		else if ( gantt_chart[i] == 24 ) file << "O" ;
		else if ( gantt_chart[i] == 25 ) file << "P" ;
		else if ( gantt_chart[i] == 26 ) file << "Q" ;
		else if ( gantt_chart[i] == 27 ) file << "R" ;
		else if ( gantt_chart[i] == 28 ) file << "S" ;
		else if ( gantt_chart[i] == 29 ) file << "T" ;
		else if ( gantt_chart[i] == 30 ) file << "U" ;
		else if ( gantt_chart[i] == 31 ) file << "V" ;
		else if ( gantt_chart[i] == 32 ) file << "W" ;
		else if ( gantt_chart[i] == 33 ) file << "X" ;
		else if ( gantt_chart[i] == 34 ) file << "Y" ;
		else if ( gantt_chart[i] == 35 ) file << "Z" ;
	}

}

void ProcessScheduling::PP(){
	int now = 1, temp = 0, i = 0; 
	vector<Process> queue;
	int MaxSlice = 0;
	now = process_list[i].arrival_time;
	while( now >= process_list[i].arrival_time && i < process_list.size() ) {
		if ( WhatProcess( process_list[i].ID ).cpu_burst > 0 ) 
			queue.push_back( process_list[i] );
			Sort_by_PP( queue , true );//穖 
			i++;	
	}
	while( !Done() ) { // ┮Τprocess常暗Чㄓ 
		if ( queue.size() != 0 ) {
			gantt_chart.push_back( queue[0].ID );
			Slice ( queue[0].ID );
			queue[0].cpu_burst--;
			temp = queue[0].ID;
			queue[0].already = true;
			MaxSlice++;
			if ( queue[0].cpu_burst == 0 ) {	
				queue.erase( queue.begin() );
				MaxSlice = 0;
			}	
		}
		else gantt_chart.push_back( -1 );
		now++;// this second Done
		while( now >= process_list[i].arrival_time && i < process_list.size() ) {
			if ( process_list[i].cpu_burst > 0 ){
				queue.push_back( process_list[i] );
				Sort_by_PP( queue , true );
			}
			i++;	
		}
		
	}
	
	
	
	
	fstream file;
	file.open( "outputRRRRR6.txt", ios::out );
	for (int i = 0; i < gantt_chart.size() ; i++ ){
		if ( gantt_chart[i] == -1 ) file << "-" ;
		else if ( gantt_chart[i] < 10 ) file << gantt_chart[i];
		else if ( gantt_chart[i] == 10 ) file << "A" ;
		else if ( gantt_chart[i] == 11 ) file << "B" ;
		else if ( gantt_chart[i] == 12 ) file << "C" ;
		else if ( gantt_chart[i] == 13 ) file << "D" ;
		else if ( gantt_chart[i] == 14 ) file << "E" ;
		else if ( gantt_chart[i] == 15 ) file << "F" ;
		else if ( gantt_chart[i] == 16 ) file << "G" ;
		else if ( gantt_chart[i] == 17 ) file << "H" ;
		else if ( gantt_chart[i] == 18 ) file << "I" ;
		else if ( gantt_chart[i] == 19 ) file << "J" ;
		else if ( gantt_chart[i] == 20 ) file << "K" ;
		else if ( gantt_chart[i] == 21 ) file << "L" ;
		else if ( gantt_chart[i] == 22 ) file << "M" ;
		else if ( gantt_chart[i] == 23 ) file << "N" ;
		else if ( gantt_chart[i] == 24 ) file << "O" ;
		else if ( gantt_chart[i] == 25 ) file << "P" ;
		else if ( gantt_chart[i] == 26 ) file << "Q" ;
		else if ( gantt_chart[i] == 27 ) file << "R" ;
		else if ( gantt_chart[i] == 28 ) file << "S" ;
		else if ( gantt_chart[i] == 29 ) file << "T" ;
		else if ( gantt_chart[i] == 30 ) file << "U" ;
		else if ( gantt_chart[i] == 31 ) file << "V" ;
		else if ( gantt_chart[i] == 32 ) file << "W" ;
		else if ( gantt_chart[i] == 33 ) file << "X" ;
		else if ( gantt_chart[i] == 34 ) file << "Y" ;
		else if ( gantt_chart[i] == 35 ) file << "Z" ;
	}	
}
void ProcessScheduling::readfile( string FileName){
	fstream file;
	file.open( FileName.c_str() , ios::in ) ;
	char a; 
	string temp;
	Process process;
	file >> command;
	file >> slice;
	file >> a;
	getline( file, temp );
	while ( file >> process.ID ) {
		file >> process.cpu_burst;
		file >> process.arrival_time;
		file >> process.priority;
		process.already = false;
		process_list.push_back( process );
	}
	
	
	
}

void ProcessScheduling::writefile(){
	fstream file;
	file.open( "output.txt" , ios::out ) ;
}

