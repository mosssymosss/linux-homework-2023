#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <inttypes.h>


void sigusr1_handler(int signum, siginfo_t* info, void* context)
{
	std::cout<<"PokemonID "<<getpid()<<std::endl;
	uint32_t ceip = 0, ceax = 0, cebx = 0 ;
	//asm volatile ("mov %%eip, %[Var]" : [Var] "=r"(ceip));
	asm volatile ("mov %%eax, %[Var]" : [Var] "=r"(ceax));
	asm volatile ("mov %%ebx, %[Var]" : [Var] "=r"(cebx));		
	
	//register int eax asm("eax");
	//register int eax asm("ebx");
	//int ceax = eax;
	//int cebx = ebx;

		
	std::cout << "Stats:\n EIP: " << ceip << "\nEAX: " << ceax << "\nEBX: " << cebx <<std::endl;
}


int main()
{
	std::cout << getpid() <<std::endl;	

	struct sigaction usr1 = {};
	usr1.sa_sigaction = sigusr1_handler;

	if(sigaction(SIGUSR1, &usr1, nullptr) == -1)
	{
		std::perror("sigaction");
		exit(errno);
	}


	while(true)
	{
		std::cout<<"I am fainted\n";
		sleep(10);
	}

	return 0;
}
