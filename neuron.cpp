#include "neuron.h"
#include <math.h>
#include <iostream>
#include <bitset>
#include <fstream>

using namespace std;

neuron::neuron(int inputs, unsigned long function)
{
    //initializing neuron
    n_inputs=inputs;
    n_synapses=(long)pow(2,n_inputs)-1;
    functions=(long)pow(2,n_synapses+1)-1;
    theta=0;
    a_function=function;
    omega_vector=new int [n_synapses];
    omega=new int *[n_synapses+1];//tox sjun
    for(int i=0;i<=n_synapses;++i)//vazum e yst toxeri
        omega[i]=new int [n_synapses];//
    build_omega();
    solve_neuron(function);
}

void neuron::print_neuron()
{
    cout<<"________________Start________________\n";
    cout<<"n_inputs="<<n_inputs<<endl;
    cout<<"n_synapses="<<n_synapses<<endl;
    cout<<"functions="<<functions+1<<endl;
    cout<<"________________OMEGA________________\n";
    print_array(omega,n_synapses+1,n_synapses);
    cout<<"____________OMEGA_VECTOR_____________\n";
    print_vector(omega_vector,n_synapses);
    cout<<"Theta="<<theta<<endl;
    cout<<"for the function "<<a_function<<" (";
    bitset<512> temp(a_function);
    for(int i=0;i<=n_synapses;++i)
        cout<<temp[i];
    cout<<")\n";
    cout<<"_________________END_________________\n";

}

void neuron::print_array(int **array, int m, int n)
{
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
            cout<<array[i][j]<<" ";
        cout<<endl;
    }
}

void neuron::print_vector(int *vector, int n)
{
    for(int i=0;i<n;i++)
        cout<<vector[i]<<" ";
    cout<<endl;
}

int neuron::solve_neuron(unsigned long a_function)
{
    if(a_function>functions)
    {
        cout<<"Wrong function\n";
        return 1;
    }
    //solving code here
    theta=0;
    for(int i=0;i<n_synapses;i++)
        omega_vector[i]=0;
    bitset<512> f(a_function);

    if(f[0]==0)
        theta=1;
    else
    theta=-1;
    int temp=0;
    for(int i=1;i<=n_synapses;++i)
    {
        for(int j=0;j<n_synapses;j++)
            //find last 1(unknown)
            if(omega[i][j]==1)
                temp=j;//temp will remember the last 1 which is unknown always
      //now we will count the sum of omegas befor this unknown
    int sum=0;
    for(int e=0;e<temp;e++)
        sum+=omega[i][e]*omega_vector[e];
    //now we have omega(temp)>=theta-sum, so we will do omega(temp)=theta-sum+1 for F=1
    //and omega=theta-sum-1 for F=0(so condition will not met and f will be 0)
    if(f[i]==1)
        omega_vector[temp]=theta-sum+1;
    else
        omega_vector[temp]=theta-sum-1;

     }


    return 0;
}

void neuron::build_omega()
{

    int e=0;//counter
    bitset<256> temp(e);

    for(int i=0;i<n_synapses+1;++i)
    {
        for(int j=0;j<n_inputs;++j)
           omega[i][j]=temp[j];
        e++;
        temp=e;
    }

        int n =n_inputs; //5; /* The size of the set; for {1, 2, 3, 4} it's 4 */
        int k = 2; /* The size of the subsets; for {1, 2}, {1, 3}, ... it's 2 */
        int comb[1024]; /* comb[i] is the index of the i-th element in the
                combination */
        int sjun=n;
        for(int tox=0;tox<=n_synapses;tox++)
        {
            sjun=n;

        for (k=2;k<=n_inputs;k++)
        {
        /* Setup comb for the initial combination */
        int i;
        for (i = 0; i < k; ++i)
            comb[i] = i;

        /* Print the first combination */
        push_omega(comb,k,tox,sjun);
        sjun++;

        /* Generate and print all the other combinations */
        while (next_comb(comb, k, n))
        {
            push_omega(comb,k,tox,sjun);
            sjun++;
        }
    }
        }

}

void neuron::push_omega(int comb[], int k, int tox, int sjun)
{
    int t=1;
    for(int i=0;i<k;++i)
        t&=omega[tox][comb[i]];
    omega[tox][sjun]=t;
}

int neuron::next_comb(int comb[], int k, int n) {
       // cout<<"k="<<k<<" n="<<n<<endl;
    int i = k - 1;
    ++comb[i];
    while ((i >= 0) && (comb[i] >= n - k + 1 + i)) {
        --i;
        ++comb[i];
    }

    if (comb[0] > n - k) /* Combination (n-k, n-k+1, ..., n) reached */
        return 0; /* No more combinations can be generated */

    /* comb now looks like (..., x, n, n, n, ..., n).
    Turn it into (..., x, x + 1, x + 2, ...) */
    for (i = i + 1; i < k; ++i)
        comb[i] = comb[i - 1] + 1;

    return 1;
}

int neuron::write_file()
{

    ///////////////////////////writing verilog-a file///////////////////////////
    ofstream veriloga("out.va");
    if(veriloga.is_open())
    {
        veriloga<<"/********************************************************\n";
        veriloga<<"Verilog-A file of a neuron\n";
        veriloga<<"Created by Neuronix v 0.0.1\n";
        veriloga<<"********************************************************/\n\n";
        veriloga<<"`include "<<'"'<<"constants.vams"<<'"'<<"\n";
        veriloga<<"`include "<<'"'<<"disciplines.vams"<<'"'<<"\n\n";
        veriloga<<"module va_neuron(Y_OUT,X_INPUT,W_WEIGHT,T_TRESHHOLD,vp,gd);\n\n";
        veriloga<<"output Y_OUT; //Y_OUT is output\n";
        veriloga<<"electrical Y_OUT;\n\n";
        veriloga<<"input ["<<n_inputs-1<<":0] X_INPUT; //X_INPUT is for inputs\n";
        veriloga<<"electrical ["<<n_inputs-1<<":0] X_INPUT;\n\n";
        veriloga<<"input ["<<n_synapses-1<<":0] W_WEIGHT; //W_WEIGHT is for weights of synapses\n";
        veriloga<<"electrical ["<<n_synapses-1<<":0] W_WEIGHT;\n\n";
        veriloga<<"input T_TRESHHOLD; //T_TRESHHOLD is the treshhold of the neuron\n";
        veriloga<<"electrical T_TRESHHOLD;\n\n";
        veriloga<<"real sum=0; //initializing sum for weights\n\n";
        veriloga<<"analog begin\n";
        veriloga<<"sum=";

        //your code is here;

        for(int i=0;i<n_inputs;++i)
        {
            veriloga<<"V(W_WEIGHT["<<i<<"])*V(X_INPUT["<<i<<"])";
            if(i!=n_inputs-1)
                veriloga<<"\n+";
            else
                veriloga<<"\n";
        }
        //veriloga<<"\n";


        int k = 2; /* The size of the subsets; for {1, 2}, {1, 3}, ... it's 2 */
        int comb[1024]; /* comb[i] is the index of the i-th element in the
                combination */
        //int n =n_inputs; //5; /* The size of the set; for {1, 2, 3, 4} it's 4 */
        int w=n_inputs-1;
        for(k=2;k<=n_inputs;++k)
        {
            veriloga<<"+V(W_WEIGHT["<<++w<<"])*(";
            for(int i=0;i<k;++i)
            {
                comb[i]=i;
                veriloga<<"V(X_INPUT["<<i<<"])";
                if(i!=k-1)
                    veriloga<<"&&";
                else
                    veriloga<<")\n";
            }
            while (next_comb(comb, k, n_inputs))
            {
                w++;
                if(w>=n_synapses-1)
                    break;
                veriloga<<'+';
                veriloga<<"V(W_WEIGHT["<<w<<"])*(";
                for(int i=0;i<k;++i)
                {
                    veriloga<<"V(X_INPUT["<<comb[i]<<"])";
                    /*if(comb[i]==4)
                    {
                        cout<<"here i am\n";
                        cout<<"k="<<k<<endl;
                        cout<<"i="<<i<<endl;
                        cout<<"w="<<w<<endl;
                    }*/
                    if(i!=k-1)
                        veriloga<<"&&";
                    else
                        veriloga<<")\n";
                }

            }


        }
        veriloga<<";";

        veriloga<<"\n\n";
        veriloga<<"if(sum>=V(T_TRESHHOLD) begin sum = V(vp); end //sign function check\n";
        veriloga<<"else begin sum = V(gd); end\n\n";
        veriloga<<"V(Y_OUT) <+ transition (sum); // making output to Y_OUT\n\n";
        veriloga<<"end\n";
        veriloga<<"endmodule\n";
        veriloga.close();
    }
    else
    {
        cout<<"cannot make verilog-a file\n";
        return 1;
    }

    ///////////////////////////writing spice file////////////////////////////////////////
    ofstream spice("out.sp");
    if(spice.is_open())
    {
        spice<<"*********************************************************\n";
        spice<<"* SPICE file for verilog-a file of a neuron\n";
        spice<<"* Created by Neuronix v 0.0.1\n";
        spice<<"*********************************************************\n\n";

        //your code is here

        spice<<"xneuron Y_OUT ";
        for(int i=0;i<n_inputs;++i)
        {
            spice<<"X_INPUT<"<<i<<"> ";
        }
        for(int i=0;i<n_synapses;++i)
        {
            spice<<"W_WEIGHT<"<<i<<"> ";
        }
        spice<<"T_TRESHHOLD vp gd va_neuron\n\n";
        for(int i=0;i<n_synapses;++i)
        {
            spice<<"v"<<(i+1)<<" W_WEIGHT<"<<i<<"> gnd! dc="<<omega_vector[i]<<"\n";
        }

        spice<<"v"<<n_synapses+1<<" T_TRESHHOLD gnd! dc="<<theta<<"\n";
        spice<<"v"<<n_synapses+2<<" gd gnd! dc=0\n";
        spice<<"v"<<n_synapses+3<<" vp gnd! dc=1\n";
        for(int i=0;i<n_inputs;++i)
        {
            spice<<"v"<<(n_synapses+4+i)<<" X_INPUT<"<<i<<"> gnd! dc=0 pulse (0 1 0 0 0 'xper' 'xper')\n";
        }

        spice<<".hdl './out.va'\n";
        spice.close();
    }
    else
    {
        cout<<"cannot make spice file\n";
        return 2;
    }

    ofstream command("command.sp");
    if(command.is_open())
    {
        command<<"*********************************************************\n";
        command<<"* SPICE COMMAND file for verilog-a file of a neuron\n";
        command<<"* Created by Neuronix v 0.0.1\n";
        command<<"*********************************************************\n\n";
        command<<".include './out.sp'\n";
        command<<".option post\n";
        command<<".option probe\n";
        command<<".param xper=400p\n";
        command<<".tran 1p '8*xper'\n";
        command<<".probe tran v(*)\n\n";
        command<<".end\n";
    }
    else
    {
        cout<<"cannot make spice command file\n";
        return 2;
    }

    return 0;
}

neuron::~neuron()
{
    delete[] omega_vector;
    for(int i=0;i<=n_synapses;++i)
        delete[] omega[i];
    delete[]omega;
}
