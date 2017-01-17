
// Macros
#define NMOTORSMAX 101
#define NMTSMAX 10
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
double StopOnDistance;
int StopBelowThetaC;
int MultiMTassay;
int StopOnBeadDissociation;
double theta_c;
int success, success_mode, trial_success;

double timer=0;

// check
int check_bit;


/* -------------------------------------------------------------------
things that should get set by the calling script
*/

// Simulation Parameters

int prematureReturn;
int FoundNotbound;
int Foundbound;
int graceful_exit;

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
double a_param[2]; //superstall parameter 1.07
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

double z_MT_offset; //amount to change base location of MT from params file
//double y_MT; //y location of the MT 0
double R_MT[NMTSMAX]; //radius of the MT .012
double kcMT; //steric spring to keep cargo out of MT (pN/micron) 400

int n_MTs;
double MTpoint[NMTSMAX][3];
double MTvec[NMTSMAX][3];

//Calculated Parameters

//double z_MT; //z location of MT
double muCargoTranslation; //1/6*pi*eta*R
double muCargoRotation; //1/8*pi*eta*R^3
double mu_m[2];

double dt_max_Steric, dt_max_Motor, dt_max_Diffusion, dt_max_base;
double dt_default=.00001;
double dt_override;

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
int ReturnDetails;
int ReturnHeads;
int ReturnFinalState;
int ReturnForces;
int ReturnOmega;
int UseSteric;
int CargoBehavior;

/* -------------------------------------------------------------------
Simulation dynamic variables
*/

//simulation trackers
double t_inst;
long step; //2

//Cargo dynamic properties
double center[3];
double center_MT_dist;

// motor dynamic properties
// vectors
double locs[2][NMOTORSMAX][3]; //anchors
double head[2][NMOTORSMAX][3]; //heads
double last_bound_head[2][NMOTORSMAX][3];
double F_m_vec [2][NMOTORSMAX][3];

// booleans
int bound            [2][NMOTORSMAX];
int bind_possible    [2][NMOTORSMAX][NMTSMAX];
int unbind_possible  [2][NMOTORSMAX];
int step_possible    [2][NMOTORSMAX];
int exchange_possible[2][NMOTORSMAX];
int nuc_ready        [2][NMOTORSMAX];
int need_steric;

// scalars
double F_m_mag      [2][NMOTORSMAX];
double step_rate    [2][NMOTORSMAX];
double unbind_rate  [2][NMOTORSMAX];
double bind_rate    [2][NMOTORSMAX][NMTSMAX];
double exchange_rate[2][NMOTORSMAX];

//For gillespie time step choosing

double dt;

double gillespie_dt, dtHere, dt_max;

long hit_m, hit_n;
int hit_k;
int hit_action;

//variables to loop over, m=motor type number, n=motor number within type
//i for dimensions, usually 3
//k for MT number
int m,n,i,k;

/* -------------------------------------------------------------------
intial locations
*/

double initlocs[2][NMOTORSMAX][3]; //initial locations, set by initiallocations
double initlocsnew[2][NMOTORSMAX][3];
double uu; //random variables to generate elevations
double vv; //random variables to generate azimuths
double az;
double el;
double x; //temporary holder for cartesian locations
double y;
double z;

int SetAtBottom;
double InitAngle;

double innerlimit;

double rotmat[9];

/* -------------------------------------------------------------------
Initial Binding
*/

double MTdist;
int done;
double initial_head;

double cPoint[3];
double cVector[3];

/* -------------------------------------------------------------------
Stepping
*/

double unloaded_step_rate[2];
double input_step_rate;

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
double v_sph[3];
double u, v;
double u_hat[3], v_hat[3];
double du, dv, dx, dy, dz;
double brownian_displacement[3];

/* -------------------------------------------------------------------
// Data collection //Recording variables
*/

/* -------------------------------------------------------------------
Variables for forward equations
*/

//parameters (for now, should change to inputs)
double muAnchor[NMOTORSMAX];
int external_force;
int external_torque;

//next step
double c1[3];
double a1[NMOTORSMAX][3];
double omega[3];

//previous step
double c[3];
double a[NMOTORSMAX][3];
double a_sph[NMOTORSMAX][3];
double FmTangential[NMOTORSMAX][3];
double FmRadial[NMOTORSMAX][3];
double Ftrap[3];
double Fsteric[3];
double Fsterick[3];
double TorqeExt[3];

//setup
long total_motors;
long nn;

//stochastics
double Dba[NMOTORSMAX][3];
double Dbc[3];
double Rbc[3];
double DAnchor[NMOTORSMAX];
double DCargoTranslation;
double DCargoRotation;

//bead
double theta[3], theta1[3];

/* -------------------------------------------------------------------
 // Stuff for input/output
 */

double LastBoundLocation[3];

//variables
int runningInLoop;
char repeat_number[100];
double trash;

//strings to use for filnames and lines read in
char paramFileName[100], MTparamFileName[100], tmpString[100], runName[100], blah[100];
char centerlocsName[100], headName[100], summaryName[100], forcesName[100], omegaName[100];

// input/output files
//optional output files
FILE *fCenterLocs, *fHead, *fForces, *fOmega;
//input parameters file
FILE *fParams,*fMTParams;
//basic summary output file
FILE *fSummary;
//variable
FILE *fInUse;
