# Build instructions


## Setup and Compilation
After downloading, cd into the main source directly, then:

```bash
mkdir build  
cd build  
```

Before running the cmake and make commands, make sure that the correct compiler is selected. This can be done by entering the following command.

```bash
module swap PrgEnv-intel PrgEnv-gnu
```
Finally, run the cmake and make command to compile the programs.

```bash
cmake ../
make
```

## Running the Programs

To run the programs on CORI@NERSC, run the job bash scripts which will submit a job to be run on the current node.

```bash
# Make the job bash script an executable
chmod +x ./job-basic
chmod +x ./job-openmp
chmod +x ./job-blas

# Run the job
./job-basic
./job-openmp
./job-blas
```

## Switching from Static to Dynamic Thread Scheduling

To switch from static to dynamic thread scheduling, simply comment out line 32 in the `job.in` file and uncomment line 33 and build and run the `job-openmp` file again.

```bash
# export OMP_SCHEDULE=static     <-- Comment out this line
export OMP_SCHEDULE=dynamic    # <-- Uncomment this line

```