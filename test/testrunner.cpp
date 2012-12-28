
#include <iostream>
#include <string>

#include <vm.hpp>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 1) return 0;

    VirtualMachine vm(16*1024);
    bool running = true;

    // void print(const char* message);
    vm.setSystemCall(0, [&](long, long, long, long, long)->long{
        return 0;
    });

    // void shutdown(long status);
    vm.setSystemCall(1, [&](long, long, long, long, long)->long{
        running = false;
        return 0;
    });

    // void test(long a, long b);
    vm.setSystemCall(2, [&](long a, long b, long, long, long)->long{
        cout << (a == b ? "." : "F");
        return 0;
    });

    vm.exec(argv[1]);
    vm.call("main");
    cout << argv[1] << ": ";
    while (running)
    {
        vm.executeNext();
    }
    cout << endl;
    return 0;
}
