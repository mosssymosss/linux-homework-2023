#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <inttypes.h>


void sigusr1_handler(int signum, siginfo_t* info, void* vcontext)
{
	std::cout<<"PokemonID "<<getpid()<<std::endl;
	//uint32_t ceip = 0, ceax = 0, cebx = 0 ;
	//asm volatile ("mov %%eip, %[Var]" : [Var] "=r"(ceip));
	//asm volatile ("mov %%eax, %[Var]" : [Var] "=r"(ceax));
	//asm volatile ("mov %%ebx, %[Var]" : [Var] "=r"(cebx));		
	//uint64_t rax = 0, rbx = 0;
	//__asm__("" : "=a"(rax), "=b"(rbx) ::);
	//register int eax asm("eax");
	//register int eax asm("ebx");
	//int ceax = eax;
	//int cebx = ebx;

	auto *context = static_cast<ucontext_t *>(vcontext);
	auto mcontext = context->uc_mcontext;
        std::cout << "-- RIP register : " << mcontext.gregs[REG_RIP] << std::endl;
        std::cout << "-- RAX register : " << mcontext.gregs[REG_RAX] << std::endl;
        std::cout << "-- RBX register : " << mcontext.gregs[REG_RBX] << std::endl;
		
	//std::cout << "Stats:\n EIP: " << 0 << "\nEAX: " << rax << "\nEBX: " << rbx <<std::endl;
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
