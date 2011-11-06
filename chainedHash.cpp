#include<iostream>
#include<cstdlib>
#include<time.h>


using namespace std;
typedef struct linkNode{
	int data;
	struct linkNode *next;
}Node;

int const M = 16;
long int const n = 1000000;
int const w = 32;
long int const m = 65536    ;//pow(2,M)

		
class ChainedHash{
	private:
		Node* HashTable[m]; 
		long int randomSeed;
		long int max;
		long int avg;
		long int mu;
		long int totalCount;

		bool genrand()
		{
		        time_t timeSeed;
			time( &timeSeed );
			srand( ( unsigned int ) timeSeed );
			long int seed;
			if(seed%2)	
	                	this->randomSeed = seed-1;
			else
				this->randomSeed = seed;
				
		}
		
		long int hash(long int value)
		{
			return abs((value*randomSeed)>>(w-M))%m;
		}
		
									       
	public:
		bool calcStat();
		bool printStat();
		bool CheckValue(long int);
		bool AddValue(long int);

		ChainedHash() 
		{
			genrand();
			this->totalCount = 0;
			this->max = 0;
			this->avg = 0;
			this->mu = 0;
			for(long int i = 0 ; i < m ; i ++ )
				HashTable[i] = NULL;
		}
	
		~ChainedHash() 
		{

		}

};

bool ChainedHash::AddValue(long int value)
{
	long int index = hash(value);
	//cout << "index is :: " << index <<endl;
	Node *pointer = NULL;
	pointer = HashTable[index];
	if(pointer == NULL)
	{
				
		pointer = new Node;
		pointer->data = value;
		pointer->next = NULL;
		HashTable[index] = pointer;
	}
	else
	{
		//cout << "else ??\n";
		while(pointer->next!=NULL)
			pointer = pointer->next;
		//cout << "out of while loop in add value\n";
		pointer->next = new Node;
		//cout << "new node allocated in add value\n";
	       	pointer = pointer->next;
		pointer->data = value;	
		pointer->next = NULL;

	}
	
	return true;

}

bool ChainedHash::CheckValue(long int value)
{
	long int index = hash(value);
	Node *pointer = NULL;
	pointer = HashTable[index];
	if(pointer == NULL )
		return false;
	else
	{
		while(pointer)
		{
			if(pointer->data==value)
				return true;
			pointer = pointer->next;
		}
		return false;
	}	
}


bool ChainedHash:: printStat()
{

	cout << "Total number of values added to hash :: " << totalCount << "\n Max value is :: " << max << "\n Avg value is :: " << avg << "\n mu is :: " << mu ;

}

bool ChainedHash:: calcStat()
{
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
				
		}

		this->totalCount += count;
	}


	this->avg = this->totalCount / m ;

	for(long int i = 0 ; i < m ; i++)\
	{
		long int count = 0;
		Node *ptr = HashTable[i];

		while(ptr)
		{
			count++;
			ptr = ptr->next;
		}
				
		this->mu+=((count - this->avg)*(count - this->avg));				

	}

	this->mu = this->mu / m ;
		
}



int main(int argc , char *argv[])
{
	ChainedHash chain;
	time_t timeSeed;           
	time( &timeSeed );
	srand( ( unsigned int ) timeSeed );
	for(long int i = 0 ; i < n ; i ++ )
	{
		long int random = rand();
		chain.AddValue(random);
		//cout << "Adding " << random << " to the Table\n";
		if(!chain.CheckValue(random))
			cout << random << " was not added to the Table\n"; 
	}
	cout << "Stats for HashTable\n" << " M : " << M << " n : " << n << " w : " << w << " m : " << m << "\n";
	chain.calcStat();
	chain.printStat();
}


