
// Macros
#define NMOTORSMAX 1000
#define kBT .00400388
#define RAND genrand_real3()
#define INF 1e14
#define pi 3.14159265359

/* -------------------------------------------------------------------
Driving function variables
*/

int repeats;
int verboseTF;
int result;
int successes=0;
int j;

// Simulation end options
int Requirebound;
int StopOnMotor2Attach;
int StopOnAllbound;
int StopOnStep;
double StopOnTime;


/* -------------------------------------------------------------------
things that should get set by the calling script
*/

// Simulation Parameters

int prematureReturn;
int FoundNotbound;
int Foundbound;

//Motor Parameters

long N[2]; //number of motors 4

//Muller Sim
double F_s[2]; //stall force (pN) 5
double F_d[2]; //detachment force (pN) 4
double eps_0[2]; //base unbinding rate (1/sec) 1
double pi_0[2]; //base binding rate (1/sec) 5
double v_f[2]; //unloaded forward velocity (microns/s) 1
double v_b[2]; //max backward velocity (microns/s) .006

//Kunwar Sim
double a[2]; //superstall parameter 1.07
double b[2]; //superstall parameter .186
double w[2]; //force-velocity curve exponent 2

double L[2]; //motor spring rest length (microns) .1
double k_m[2]; //motor spring constant (pN/micron) 320

double step_size[2]; //length of a motor step (microns) .008

//Bovyn Sim
double D_m[2]; //diffusion constant of the anchor in the membrane (microns^2/s) 3-5

//Cargo Parameters

double center_initial[3]; //initial location of center of cargo
double R; //Cargo Radius (microns) .25
double eta; //Dynamic viscosity of surrounding fluid 10*8.9E-4

//Microtubule Parameters

double z_MT_offset; //z location of the MT R-.05
double y_MT; //y location of the MT 0
double R_MT; //radius of the MT .012
double kcMT; //steric spring to keep cargo out of MT (pN/micron) 400

//Calculated Parameters

double z_MT; //z location of MT
double mu_c; //6*pi*eta*R
double mu_m[2];
double D_c; //kBt/mu_c

double dt_max_Steric, dt_max_Motor, dt_max_Diffusion, dt_max_base;

/* -------------------------------------------------------------------
Listing of optional arguements to pass in
*/

int InitialLocations;
int MotorDiffusion;
int InitialBinding;
int Binding;
int Unbinding;
int Stepping;
int InitialNucleotideBehavior;
int NucleotideBehavior;
int MotorLoading;
int CargoBehavior;
int CargoMovement;
int ReturnDetails;
int ReturnFinalState;
int ReturnForces;

/* -------------------------------------------------------------------
Simulation dynamic variables
*/

//simulation trackers
double t_inst;
long step; //2

//Cargo dynamic properties
double center[3];

// motor dynamic properties
// vectors
double locs[2][NMOTORSMAX][3]; //anchors
double head[2][NMOTORSMAX][3]; //heads
double F_m_vec [2][NMOTORSMAX][3];

// booleans
int bound            [2][NMOTORSMAX];
int bind_possible    [2][NMOTORSMAX];
int unbind_possible  [2][NMOTORSMAX];
int step_possible    [2][NMOTORSMAX];
int exchange_possible[2][NMOTORSMAX];
int nuc_ready        [2][NMOTORSMAX];
int need_steric=0;

// scalars
double F_m_mag      [2][NMOTORSMAX];
double step_rate    [2][NMOTORSMAX];
double unbind_rate  [2][NMOTORSMAX];
double bind_rate    [2][NMOTORSMAX];
double exchange_rate[2][NMOTORSMAX];

//For gillespie time step choosing

double dt;

double gillespie_dt, dtHere, dt_max;

long hit_m, hit_n;
int hit_action;

//variables to loop over, m=motor type number, n=motor number within type
//i for dimensions, usually 3
int m,n,i;

/* -------------------------------------------------------------------
intial locations
*/

double init_locs[NMOTORSMAX][3]; //initial locations, set by initiallocations
double uu[NMOTORSMAX]; //random variables to generate elevations
double vv[NMOTORSMAX]; //random variables to generate azimuths
double az[NMOTORSMAX];
double el[NMOTORSMAX];
double x[NMOTORSMAX]; //temporary holder for cartesian locations
double y[NMOTORSMAX];
double z[NMOTORSMAX];
double rcosel[NMOTORSMAX];

int SetAtBottom;
double InitAngle;

double innerlimit;

/* -------------------------------------------------------------------
Initial Binding
*/

double MT_dist[2][NMOTORSMAX];
int done;

/* -------------------------------------------------------------------
Stepping
*/

double unloaded_step_rate[2];

/* -------------------------------------------------------------------
Binding
*/

/* -------------------------------------------------------------------
Nucleotide exchange
*/

double base_exchange_rate [2];

/* -------------------------------------------------------------------
Unbinding
*/

double neck_mag[2][NMOTORSMAX], neck_vec[2][NMOTORSMAX][3];
double unit_vec[3];

/* -------------------------------------------------------------------
Diffusion
*/

double locs_sph [2][NMOTORSMAX][2];
double rand1, rand2, randn1, randn2;
double lim;
double v_cart[3];
double u_hat[3], v_hat[3];
double du, dv;

/* -------------------------------------------------------------------
// Data collection //Recording variables
*/


/* -------------------------------------------------------------------
 // Stuff for input/output
 */

//variables
int runningInLoop;
double trash;

//strings to use for filnames and lines read in
char paramFileName[100], tmpString[100], runName[100], blah[100];
char centerlocsName[100], headName[100], summaryName[100];

// input/output files
//optional output files
FILE *fCenterLocs, *fHead;
//input parameters file
FILE *fParams;
//basic summary output file
FILE *fSummary;
