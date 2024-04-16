#include "instance.h"
#include "config.h"
#include "utils.h"
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
// get-tau -i "C:\Users\admin\Downloads\cumulative-drone-main\cumulative-drone-main\0.instances\analysis\0-0-requestInfo.txt"
int main(int argc, char* argv[])
{
    try {
        Config config(argc, argv);
        Instance instance(config.input, config.param_input);
        cout << instance.num_nodes << endl;
        string tauFile = "ouput_get_tau.txt";
        ofstream outFile(tauFile);
        
        //IMPORTANT!!!!
        int numdrone = 2; //change later, not fixed

        outFile << "numNode" << "  " << instance.num_nodes - 1 << endl;
        outFile << "numDrone" << " " << numdrone << endl;
        outFile << "# DRONE FLIGHT TIME" << endl;
        outFile << setw(10) << "request_id";
        outFile << setw(9) << "tau_in";
        outFile << setw(9) << "tau_out";
        outFile << endl;

        for (int customer = 1; customer < instance.num_nodes; ++customer) {
            double flight_time_in = instance.tdrone_in(customer);
            double flight_time_out = instance.tdrone_out(customer);
            //stringstream ss;
            outFile << setw(10) << customer;
            
            string v_text;
            if (instance.tdrone(customer) < 0)
                v_text = "        -        -";
            else
            {
                outFile << setw(9);
                outFile << std::fixed << setprecision(0) << flight_time_in;
                outFile << setw(9);
       
                outFile << std::fixed << setprecision(0) << flight_time_out;
            }
            
            outFile << v_text;
            outFile << endl;
        }

        outFile << "# TRUCK TIME MATRIX" << endl;
        for (int node = 0; node < instance.num_nodes; ++node) {
            for (int node2 = 0; node2 < instance.num_nodes; ++node2) {
                outFile << setprecision(2) << instance.dist_truck[node][node2] << " ";
            }
            outFile << endl;
        }
        cout << "DONE " << instance.instanceName << endl;
    }
    catch (const string& e) { std::cerr << "EXCEPTION | " << e << "\n"; }

    return 0;
}