#include "includes.h"

using namespace std;

Game* game;

void cleanup()
{
    delete game;
}

int main(int argc, char **argv) //Nice and general, all implementation details abstracted out.
{
    atexit(cleanup);
    game = new Game();d
    game->Initiallise(argc, argv);
    game->Run();
    return 0;
}
