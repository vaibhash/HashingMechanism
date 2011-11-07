#include<iostream>
#include<cstdlib>
#include<time.h>


using namespace std;
typedef struct linkNode{
	int t;
	struct linkNode *next;
}Node;

int const M = 16;
long int const n = 10000;
int const w = 32;
long int const m = 37268;     //pow(2,M)

		
class OpenAddress{
	private:
		long int HashTable[m]; 
		long int randomSeedA;
		long int randomSeedB;
		long int max;
		double avg;
		double mu;
		long int totalCount;
		long int failCounter;
		Node list;
		Node * current;
		
		bool genrandA()
		{
		        time_t timeSeed;
			time( &timeSeed );
			srand( ( unsigned int ) timeSeed );
			long int seed = rand();
			if(seed%2)	
	                	this->randomSeedA = seed-1;
			else
				this->randomSeedA = seed;
				
		}
	
		bool genrandB()
		{
		        time_t timeSeed;
			time( &timeSeed );
			srand( ( unsigned int ) timeSeed );
			long int seed = rand();
			if(seed%2)	
	                	this->randomSeedB = seed-1;
			else
				this->randomSeedB = seed;
				
		}
		
		long int hashA(long int value)
		{
			return abs((value*(this->randomSeedA))>>(w-M))%m;
		}
	
		long int hashB(long int value)
		{
			return abs((value*(this->randomSeedB))>>(w-M))%m;
		}
									       
	public:
		bool calcStat();
		bool printStat();
		bool CheckValue(long int);
		bool AddValue(long int);

		OpenAddress() 
		{
			genrandA();
			genrandB();
			this->totalCount = 0;
			this->max = 0;
			this->avg = 0;
			this->mu = 0;
			for(long int i = 0 ; i < m ; i ++ )
				HashTable[i] = 0;
			this->list.t = -1;
			this->current = &this->list;
			this->failCounter = 0;
		}
	
		~OpenAddress() 
		{

		}

};

bool OpenAddress::AddValue(long int value)
{

	long int indexA = hashA(value);
	long int indexB = hashB(value);
	long int index = (indexA + indexB)%m;
	long int t = 1;

	this->current->next = new Node;
	this->current = this->current->next;
	this->current->next = NULL;

	if(HashTable[indexA] == 0)
	{
		HashTable[indexA] = value;
		this->current->t = t;
	}
	else
	{
		t++;
		while( (HashTable[index] != 0) && (t!=m))
		{
			index = (index + indexB) %m;
			t++;
		}
		this->current->t = t;
		if(t!=m)
		{		
			HashTable[index] = value;
		}	
		else
		{
			this->failCounter+=1;
		}

	}
	
	return true;
}

bool OpenAddress::CheckValue(long int value)
{

	long int indexA = hashA(value);
	long int indexB = hashB(value);
	long int index = (indexA + indexB) % m;
	long int t;
	if(HashTable[indexA] == value )
		return true;
	else
	{
		t++;
		while( (HashTable[index] != value) && (t!=m))
		{
			index = (index + indexB) %m;
			t++;
		}
		if(t==m)
		{		
			return false;
		}	
		return true;
	}

}


bool OpenAddress:: printStat()
{

	cout << "Total number of trials :: " << totalCount << "\n Max value of trial is :: " << max << "\n Avg value of trial is :: " << avg << "\n mu is :: " << mu << "\ntotal number of failures : " << failCounter;

}

bool OpenAddress:: calcStat()
{
	Node *traverse = &this->list;
	traverse = traverse->next;
	long int count = 0;
	while(traverse)
	{
		count+=(traverse->t);
		if(traverse->t > this->max)
			this->max = traverse->t;
		traverse = traverse->next;
	}
	this->totalCount += count;
	
	this->avg = ( (double)this->totalCount / n );


 	traverse = &this->list;
	traverse = traverse->next;
        while(traverse)
        {       
                this->mu+=((traverse->t - this->avg)*(traverse->t - this->avg));
                traverse = traverse->next;
        }       

	this->mu = ( this->mu / n );	
}



int main(int argc , char *argv[])
{

	OpenAddress chain;
	time_t timeSeed;           
	time( &timeSeed );
	srand( ( unsigned int ) timeSeed );
	
	for(long int i = 1 ; i < n ; i ++ )
	{
		long int random = rand();
		chain.AddValue(random);
		cout << "Adding " << random << " to the Table\n";
		if(!chain.CheckValue(random))
			cout << random << " was not added to the Table\n"; 
	}
	cout << "Stats for HashTable\n" << " M : " << M << "\n n : " << n << " \n w : " << w << " \n m : " << m << "\n";
	chain.calcStat();
	chain.printStat();
}


