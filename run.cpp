
#include <iostream>
#include <string>

#include <vm.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 1) return 0;

    VirtualMachine vm(10*1024);
    bool running = true;

    // void print(const char* message);
    vm.setSystemCall(0, [&](long ptr, long, long, long, long)->long{
        const char* message = (char*)vm.memory + ptr;
        cout << message << endl;
        return 0;
    });

    // void shutdown(long status);
    vm.setSystemCall(1, [&](long status, long, long, long, long)->long{
        cout << "Exit status: " << status << endl;
        running = false;
        return 0;
    });

    // void test(long a, long b);
    vm.setSystemCall(2, [&](long, long, long, long, long)->long{
        return 0;
    });

    vm.exec(argv[1]);
    vm.call("main");

    clock_t ci = clock();
    while (running)
    {
        vm.executeNext();
    }
    clock_t cf = clock();
    cout << " " << vm.clocks << " clocks in " << ((double)(cf-ci)/CLOCKS_PER_SEC) << " seconds. ";
    cout << "(" << vm.clocks / ((double)(cf-ci)/CLOCKS_PER_SEC) / 1000000 << " MHz)" << endl;
    return 0;
}
