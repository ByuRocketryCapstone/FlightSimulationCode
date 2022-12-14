// Toggles which mode the simulator is in. To test the control algorithm, set the
// TEST_CONTROL_SCHEME variable to true. To generate optimal trajectories for the PID
// controller, set TEST_CONTROL_SCHEME to false.
#define TEST_CONTROL_SCHEME false
#define GENERATE_TRAJECTORIES !TEST_CONTROL_SCHEME

#include <iostream>
using namespace std;

#if TEST_CONTROL_SCHEME

#include <chrono>

#include "Simulator.h"

using namespace std;
using namespace std::chrono;

// h_0 = 762.9144;         //height at MECO, m
// V_0 = 284.57;           //velocity at MECO, m/s

void simulate(Simulator& currSim);
double controlSchemeUpdate(double h, double V, double a, double theta);


int main()
{
    Simulator currSim(762.9144, 284.57, 0);

    auto start = high_resolution_clock::now();

    simulate(currSim);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    //cout << "time: " << duration.count() << endl;

    return 0;
}


void simulate(Simulator& currSim)
{
    double currH, currV, currA;
    double alpha = 40 * (3.14159/180);
    do
    {
        currSim.calcNextStep(currH, currV, currA, alpha);
        alpha = controlSchemeUpdate(currH, currV, currA, 0);
    } while(currV > 0.1);
    
    //cout << "h: " << currH << endl;
    
}


double controlSchemeUpdate(double h, double V, double a, double theta)
{
    return 40 * (3.14159/180);
    //FIXME: add stepper motor speed limits so paddles can't instantly deploy
}


#endif //TEST_CONTROL_SCHEME



#if GENERATE_TRAJECTORIES

#include "Generator.h"

int main()
{
    Generator generator;
    generator.generateTrajectories();

    return 0;
}

#endif //GENERATE_TRAJECTORIES