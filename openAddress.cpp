#include<iostream>
#include<cstdlib>
#include<time.h>


using namespace std;
typedef struct linkNode{
	int t;
	struct linkNode *next;
}Node;

int const M = 16;
long int const n = 100000;
int const w = 32;
long int const m = 65536      ;//pow(2,M)

		
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

	this->current->next = new Node;
	this->current = this->current->next;
	this->current->next = NULL;
	long int t = 0;
	if(HashTable[indexA] == 0)
	{
		HashTable[indexA] = value;
		this->current->t = t;
	}
	else
	{

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
			this->failCounter++;
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

	cout << "Total number of values added to hash :: " << totalCount << "\n Max value is :: " << max << "\n Avg value is :: " << avg << "\n mu is :: " << mu << "\n";

}

bool OpenAddress:: calcStat()
{
/*
	for(long int i = 0 ; i < m ; i++)
	{
		long int count = 0;
		Node *ptr = HashTable[i];
				
		while(ptr)
		{
			count++;
			ptr = ptr->next;
		}

		if(count > this->max)
		{
			this->max = count;
			//cout << count << "  " << max << " \n";	
		}

		this->totalCount += count;
	}


	this->avg = ( (double)this->totalCount / m );

	for(long int i = 0 ; i < m ; i++)
	{
		long int count = 0;
		Node *ptr = HashTable[i];
		
		while(ptr)
		{
			count++;
			ptr = ptr->next;
		}
		
				
		this->mu+=(double)((count - this->avg)*(count - this->avg));				

	}

	this->mu = ( this->mu / m );
*/		
}



int main(int argc , char *argv[])
{
/*
	OpenAddress chain;
	time_t timeSeed;           
	time( &timeSeed );
	srand( ( unsigned int ) timeSeed );
	Node *head;
	Node *current = new Node;
	long int random = rand();
	current->t = 0;
	current->next = NULL;
	head = current;
	for(long int i = 1 ; i < n ; i ++ )
	{
		current = current->next;
		random = rand();
		current = new Node;
		current->data = random;
		current->t = 0;
		current->next = NULL;
		chain.AddValue(random);
		//cout << "Adding " << random << " to the Table\n";
		if(!chain.CheckValue(random))
			cout << random << " was not added to the Table\n"; 
	}
	cout << "Stats for HashTable\n" << " M : " << M << "\n n : " << n << " \n w : " << w << " \n m : " << m << "\n";
	chain.calcStat();
	chain.printStat();
*/
}


