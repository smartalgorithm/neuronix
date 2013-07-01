#include <iostream>
#include <stdlib.h>
#include "neuron.h"
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
    if(argc<3)
    {
        //program called with no parameter, ERROR
        cout<<"ERROR: No Parameter given.\nEnter neuronix -h for usage information\n";

        return 1; //error code
    }

    int inputs=atoi(argv[1]);//the number of neuron's inputs
    unsigned long function=atoi(argv[2]);//desirable function code in decimal digit

    if(inputs<2)
    {
        //ERROR, the inputs should be at least 2
        cout<<"ERROR: Wrong inputs are givet.\nThe inputs should be an integer bigger than 1\n";
        return 2; //error code
    }

    if(function>((unsigned long)pow(2,pow(2,inputs))-1))
    {
        //ERROR, the funcion does not exist
        cout<<"ERROR: Wrong function is given.\nThe function should be no bigger than 2^(2^x), where x is amount of inputs.\n";
        return 3;//error code
    }

    neuron nn(inputs, function);
    //neuron nn(3,21);
    nn.print_neuron();
    nn.write_file();

    return 0;
}

