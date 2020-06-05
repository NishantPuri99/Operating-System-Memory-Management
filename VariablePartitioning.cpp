#include <bits/stdc++.h>
#include <queue>
#include <vector>
using namespace std;
int EF[3] = {0, 0, 0}; //Array to calculate average external fragmentation (First Fit, Best Fit, Worst Fit)
void FirstFit(int PartSize[], queue<char> AP, char proc[], int proc_size[], int NumParts, int NumProcs, int B[])
{
    cout << endl
         << "---- First Fit ----" << endl;
    int ts = 0;      //Calculate Remaining size
    int ExtFrag = 0; //External Fragmentation for First Fit
    for (int i = 0; i < NumProcs; i++)
    { //Iterate over all Processes
        for (int j = 0; j < NumParts; j++)
        {                  //Iterate over all Partitions
            if (B[j] == 0) //Check if Partitions are filled or not (array 'B' is shown and explained in main())
            {
                if (PartSize[j] >= proc_size[i]) //Checking if process can be accomodated
                {
                    ts += (PartSize[j] - proc_size[i]); //Partition size remaining after fitting the process
                    PartSize[j] -= proc_size[i];
                    AP.push(proc[i]); //Push process into queue (Means process is allocated)
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    //inQueue array is '1' for unallocated processes and '0' for allocated ones
    queue<char> temp = AP;
    int inQueue[NumProcs] = {0};
    while (!temp.empty())
    {
        for (int i = 0; i < NumProcs; i++)
        {
            if (temp.front() == proc[i])
            {
                inQueue[i] = 1;
                temp.pop();
                break;
            }
            else
            {
                continue;
            }
        }
    }

    cout << "Allocated Processes(First Fit):" << endl;
    while (!AP.empty())
    {
        cout << AP.front() << " ";
        AP.pop();
    }
    //CalcExtFrag Array to find maximum value of External Fragmentation (Yet values should be less than Internal Fragmentation)
    int CalcExtFrag[NumProcs] = {0};
    for (int i = 0; i < NumProcs; i++)
    {
        if (inQueue[i] == 0)
        {
            if (ts >= proc_size[i])
            {
                CalcExtFrag[i] = proc_size[i];
            }
        }
    }

    //Find maximum value from CalcExtFrag array (This is the final external fragmentation)
    int ME = CalcExtFrag[0];
    for (int c = 0; c < NumProcs; c++)
    {
        if (ME < CalcExtFrag[c])
        {
            ME = CalcExtFrag[c];
        }
    }
    ExtFrag = ME;
    EF[0] += ExtFrag; //External Fragmentation is added to first position of EF array
}
//BEST FIT FUNCTION
void BestFit(int PartSize[], queue<char> AP, char proc[], int proc_size[], int NumParts, int NumProcs, int B[])
{
    cout << endl
         << "---- Best Fit ----" << endl;
    int ts[NumParts] = {0};      //Array to calculate remaining size(After an allocation)
    int ExtFrag = 0; //External Fragmentation for Best Fit
    //Sort array in ascending order so that 'best fit' can be implemented (Fill Smallest memory block first)
    for (int d = 0; d < NumParts - 1; d++)
    {
        for (int f = d + 1; f < NumParts; f++)
        {
            if (PartSize[f] < PartSize[d])
            {
                swap(PartSize[f], PartSize[d]);
                swap(B[f], B[d]);
            }
        }
    }
    int CheckOne[NumParts] = {0};//Check whether a partition is being filled again or not
    for (int i = 0; i < NumProcs; i++)
    { //Iterate over all Processes
        for (int j = 0; j < NumParts; j++)
        { //Iterate over all Partitions
            if (B[j] == 0)
            { //Check if Partitions are filled or not (array 'B' is shown and explained in main())
                if (PartSize[j] >= proc_size[i]) //Checking if process can be accomodated
                {
                    if (CheckOne[j] == 0)//if not used before, then add to index value j of ts array
                    { 
                        ts[j] += (PartSize[j] - proc_size[i]);
                        CheckOne[j] = 1; 
                    }
                    else//if used before, then update the value at ts[j]
                    {
                        ts[j] = PartSize[i] - proc_size[i];
                    }
                    PartSize[j] -= proc_size[i];//Change Partition Size
                    AP.push(proc[i]); //Push process into queue (Means process is allocated)
                    //sort again in ascending order with new partition size
                    for (int d = 0; d < NumParts - 1; d++)
                    {
                        for (int f = d + 1; f < NumParts; f++)
                        {
                            if (PartSize[f] < PartSize[d])
                            {
                                swap(PartSize[f], PartSize[d]);
                                swap(B[f], B[d]);
                            }
                        }
                    }
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    //inQueue array is '1' for unallocated processes and '0' for allocated ones
    queue<char> temp = AP;
    int inQueue[NumProcs] = {0};
    while (!temp.empty())
    {
        for (int i = 0; i < NumProcs; i++)
        {
            if (temp.front() == proc[i])
            {
                inQueue[i] = 1;
                temp.pop();
                break;
            }
            else
            {
                continue;
            }
        }
    }
    cout << "Allocated Processes(Best Fit):" << endl;
    while (!AP.empty())
    {
        cout << AP.front() << " ";
        AP.pop();
    }
    int TS=0;//Total Space freely available after all processes have been allocated
    for(int a=0;a<NumParts;a++){
        TS+=ts[a];
    }
    //CalcExtFrag Array to find maximum value of External Fragmentation (Yet values should be less than Internal Fragmentation)
    int CalcExtFrag[NumProcs] = {0};
    for (int i = 0; i < NumProcs; i++)
    {
        if (inQueue[i] != 1)
        {

            if (TS >= proc_size[i])
            {
                CalcExtFrag[i] = proc_size[i];
            }
        }
    }

    //Find maximum value from CalcExtFrag array (This is the final external fragmentation)
    int ME = CalcExtFrag[0];
    for (int c = 0; c < NumProcs; c++)
    {

        if (ME < CalcExtFrag[c])
        {
            ME = CalcExtFrag[c];
        }
    }
    ExtFrag = ME;
    EF[1] += ExtFrag; //External Fragmentation is added to second position of EF array
}
//WORST FIT FUNCTION
void WorstFit(int PartSize[], queue<char> AP, char proc[], int proc_size[], int NumParts, int NumProcs, int B[])
{
    cout << endl
         << "---- Worst Fit ----" << endl;
    int ts[NumParts] = {0}; //Array to calculate remaining size(After an allocation)
    int ExtFrag = 0; //External Fragmentation for Worst Fit
    //Sort array in descending order so that 'worst fit' can be implemented(Fill largest memory block first)
    for (int d = 0; d < NumParts - 1; d++)
    {
        for (int f = d + 1; f < NumParts; f++)
        {
            if (PartSize[f] > PartSize[d])
            {
                swap(PartSize[f], PartSize[d]);
                swap(B[f], B[d]);
            }
        }
    }
    int CheckOne[NumParts] = {0};
    for (int i = 0; i < NumProcs; i++)
    { //Iterate over all Processes
        for (int j = 0; j < NumParts; j++)
        { //Iterate over all Partitions
            if (B[j] == 0)
            { //Check if Partitions are filled or not (array 'B' is shown and explained in main())
                if (PartSize[j] >= proc_size[i])
                { //Checking if process can be accomodated
                    if (CheckOne[j] == 0)//if not used before, then add to the ts variable
                    { 
                        ts[j] += (PartSize[j] - proc_size[i]);
                        CheckOne[j] = 1; 
                    }
                    else//if used before, then update the value
                    {
                        ts[j] = PartSize[i] - proc_size[i];
                    }
                    PartSize[j] -= proc_size[i];//Change partition Size
                    AP.push(proc[i]); //Push process into queue (Means process is allocated)
                    //sort again in descending order with new partition size
                    for (int d = 0; d < NumParts - 1; d++)
                    {
                        for (int f = d + 1; f < NumParts; f++)
                        {
                            if (PartSize[f] > PartSize[d])
                            {
                                swap(PartSize[f], PartSize[d]);
                                swap(B[f], B[d]);
                            }
                        }
                    }
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
    //inQueue array is '1' for unallocated processes and '0' for allocated ones
    queue<char> temp = AP;
    int inQueue[NumProcs] = {0};
    while (!temp.empty())
    {
        for (int i = 0; i < NumProcs; i++)
        {
            if (temp.front() == proc[i])
            {
                inQueue[i] = 1;
                temp.pop();
                break;
            }
            else
            {
                continue;
            }
        }
    }

    cout << "Allocated Processes(Worst Fit):" << endl;
    while (!AP.empty())
    {
        cout << AP.front() << " ";
        AP.pop();
    }
    cout << endl;
    int TS = 0; //Total Space freely available after all processes have been allocated
    for(int a=0;a<NumParts;a++){
        TS+=ts[a];
    }
    //CalcExtFrag Array to find maximum value of External Fragmentation (Yet values should be less than Internal Fragmentation)
    int CalcExtFrag[NumProcs] = {0};
    for (int i = 0; i < NumProcs; i++)
    {
        if (inQueue[i] == 0)
        {
            if (TS >= proc_size[i])
            {
                CalcExtFrag[i] = proc_size[i];
            }
        }
    }

    //Find maximum value from CalcExtFrag vector array (This is the final external fragmentation)
    int ME = CalcExtFrag[0];
    for (int c = 0; c < NumProcs; c++)
    {
        if (ME < CalcExtFrag[c])
        {
            ME = CalcExtFrag[c];
        }
    }
    ExtFrag = ME;
    EF[2] += ExtFrag; //External Fragmentation is added to third position of EF array
}
int main()
{
    srand(time(0));//Sets Custom seed for RAND()
    int NSIM; //Number of repititions required
    cout << "Enter The Number Of Times That You Wish To SIMULATE VARIABLE PARTIONING SCHEME:" << endl;
    cin >> NSIM;
    for (int l = 1; l <= NSIM; l++)
    {
        if (l == 1)
        {
            cout << endl
                 << "[====== 1st Iteration ======]" << endl;
        }
        else if (l == 2)
        {
            cout << endl
                 << "[====== 2nd Iteration ======]" << endl;
        }
        else if (l == 3)
        {
            cout << endl
                 << "[====== 3rd Iteration ======]" << endl;
        }
        else
        {
            cout << endl
                 << "[====== " << l << "th Iteraion ======]" << endl;
        }
        int NumParts = (rand() % 10) + 3; //Random Number of Memory Partitions (range, 3 to 12)
        cout << endl
             << "Number of Memory Partitions:" << endl;
        cout << NumParts;
        cout << endl
             << "Partition Size and Availability";
        int Fill[NumParts] = {0}; //Binary array (has only 1 or 0 as values), '1' means Filled, '0' means Empty Partition
        int PS[NumParts];         //Array of Partition Sizes
        //Filling the Partition and Binary 'Fill' array
        for (int i = 0; i < NumParts; i++)
        {
            int temp = rand() % 1000;//Random Partition Sizes (in 3 digit),
            PS[i] = temp + 1;
            Fill[i] = rand() % 2;//Which are randomly filled
        }
        cout << endl
             << "Memory:" << endl;
        for (int i = 0; i < NumParts; i++)
        {
            cout << PS[i] << " ";
        }
        cout << endl
             << "Filled:" << endl;
        for (int i = 0; i < NumParts; i++)
        {
            cout << Fill[i] << " ";
        }
        cout << endl;
        int NumProcs = (rand() % 10) + 3; //Random Number of processes (range, 3-12)
        cout << "Number of processes:" << endl;
        cout << NumProcs;
        int proc_size[NumProcs]; //Array of process sizes
        char proc[NumProcs];     //Array of process names ('A','B','C',etc.)
        for (int i = 0; i < NumProcs; i++)
        {
            int temp = (rand() % 1000) +10; // Random (non-zero) Process sizes
            proc_size[i] = temp;
            proc[i] = char(i + 65);
        }
        cout << endl
             << "Processes are:" << endl;
        for (int i = 0; i < NumProcs; i++)
        {
            cout << proc[i] << "\t";
        }
        cout << endl;
        for (int i = 0; i < NumProcs; i++)
        {
            cout << proc_size[i] << "\t";
        }
        queue<char> AP; //queue to check Allocated Processes

        //Temporary variables, B is for Binary 'Fill' Array, P is for the Partition Size array
        int B[NumParts];
        int P[NumParts];
        //First Fit
        for (int x = 0; x < NumParts; x++)
        {
            P[x] = PS[x];
            B[x] = Fill[x];
        }
        FirstFit(P, AP, proc, proc_size, NumParts, NumProcs, B);
        //Best Fit
        for (int x = 0; x < NumParts; x++)
        {
            P[x] = PS[x];
            B[x] = Fill[x];
        }
        BestFit(P, AP, proc, proc_size, NumParts, NumProcs, B);
        // //Worst Fit
        for (int x = 0; x < NumParts; x++)
        {
            P[x] = PS[x];
            B[x] = Fill[x];
        }
        WorstFit(P, AP, proc, proc_size, NumParts, NumProcs, B);
    }
    //Average Each external fragmentation
    for (int a = 0; a < 3; a++)
    {
        EF[a] /= NSIM;
    }
    cout << "Average External Fragmentation is:" << endl;
    cout << "FF"
         << "\t"
         << "BF"
         << "\t"
         << "WF" << endl;
    cout << EF[0] << "\t" << EF[1] << "\t" << EF[2] << endl;
    if(EF[0] == EF[1] && EF[1] == EF[2]){cout<<"All Methods have same External Fragmentation = "<<EF[0]<<endl;}
    else{
    int LEF = EF[0];
    int EFindex = 0;
    for (int z=0;z<3;z++){
        if(EF[z] < LEF){
        LEF = EF[z];
        EFindex = z;
        }
    }
    cout<<"Least External Fragmentation Exists In: ";
    if(EFindex==0){cout<<"First Fit";}
    else if(EFindex==1){cout<<"Best Fit";}
    else{cout<<"Worst Fit";}
    cout<<" and its value is "<<LEF<<endl;
    }
    return 0;
}
