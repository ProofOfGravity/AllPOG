#include "../src/engine.h"

int main() {



    engine eng("test", 100, 100, 800, 600);
    eng.run();
    eng.cleanUp();

    return 0;
}
