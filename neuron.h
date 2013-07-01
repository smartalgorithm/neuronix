#ifndef NEURON_H
#define NEURON_H

class neuron
{
public:
    neuron(int inputs, unsigned long function);
    void print_neuron();
    int solve_neuron(unsigned long a_function);
    int write_file();//creats verilog-a and spice files for simulation
    ~neuron();
private:
    int n_inputs;//neuron inputs given by the user
    int n_synapses;//number of synapses
    unsigned long functions;//all possible functions that neuron can implement
    unsigned long a_function;//given function for generating neuron
    int theta;//treshhold
    int *omega_vector;//weights of synapses for chosen function
    int **omega;//synapses
    void print_array(int **array, int m, int n);//this can print any 2d matrix
    void print_vector(int *, int);//this can print any vector
    void build_omega();//this will all values in **omega matrix as neccessary :-)
    int next_comb(int comb[], int k, int n);//generates all unique combinations for inputs
    void push_omega(int comb[], int k, int tox, int sjun);//pushes combination
};

#endif // NEURON_H
