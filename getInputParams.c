//prototypes
void getInputParams( void );

void getInputParams( void )
{

    /************ Model and numerical parameters FROM FILE *******************/

    //open the parameter file (name specified in drive_motors.c)
    //fParams initialized in motors.h
    fParams = fopen(paramFileName, "r");

    //My approach: use fgets() to scan each line into the temporary string
    //then use sscanf() to find the values
    //learned the pattern must include the first thing on the line
    //(here stored to string called blah)
    //this lets us have comments in the file
    //(using fscanf didn't like having extra text after the numbers)

    //Go through each line and find the values of the input paramters
    //skip the first few
    for(int n_lines=1;n_lines<=13;n_lines++)
    {
      fgets(tmpString, 100, fParams);
    }



    //motor parameters

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %ld %ld", blah, &N[0], &N[1]);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    //Muller
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&F_s[0], &F_s[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&F_d[0], &F_d[1]);
    fgets(tmpString, 100, fParams);
    //Can input eps_0[0] from command line
    //only read if its still set to default nan value
    if(isnan(eps_0[0]) || eps_0[0]==0){
        sscanf(tmpString,"%s %lf %lf", blah,&eps_0[0], &eps_0[1]);
    }
    else{//if not NAN, the value was set in command line so trash it
        sscanf(tmpString,"%s %lf %lf", blah,&trash, &eps_0[1]);
    }
    fgets(tmpString, 100, fParams);
    if(isnan(pi_0[0]) || pi_0[0]==0){
        sscanf(tmpString,"%s %lf %lf", blah,&pi_0[0], &pi_0[1]);
    }
    else{//if not NAN, the value was set in command line so trash it
        sscanf(tmpString,"%s %lf %lf", blah,&trash, &pi_0[1]);
    }
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&v_f[0], &v_f[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&v_b[0], &v_b[1]);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    //Kunwar
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&a_param[0], &a_param[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&b[0], &b[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&w[0], &w[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&L[0], &L[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&k_m[0], &k_m[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&step_size[0], &step_size[1]);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    //Bovyn
    fgets(tmpString, 100, fParams);
    //Can input D_m[0] from command line
    //only read if its still set to default nan value
    if(isnan(D_m[0]) || D_m[0]==0){
        sscanf(tmpString,"%s %lf %lf", blah,&D_m[0], &D_m[1]);
    }
    else{//if not NAN, the value was set in command line so trash it
        sscanf(tmpString,"%s %lf %lf", blah,&trash, &D_m[1]);
    }
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);

    //Cargo Parameters

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf %lf", blah,
        &center_initial[0], &center_initial[1],&center_initial[2]);
    fgets(tmpString, 100, fParams);
    if(isnan(R) || R==0){
        sscanf(tmpString,"%s %lf", blah,&R);
    }
    else{//if not NAN, the value was set in command line so trash it
        sscanf(tmpString,"%s %lf", blah,&trash);
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf", blah,&eta);

    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);

    //Microtubule Parameters

    //Can input from command line
    //only read if its still set to default nan value
    fgets(tmpString, 100, fParams);
    if(isnan(z_MT_offset) || z_MT_offset==0){
        sscanf(tmpString,"%s %lf", blah,&z_MT_offset);
    }
    else{//if not NAN, the value was set in command line so trash it
        sscanf(tmpString,"%s %lf", blah,&trash);
    }
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf", blah,&y_MT);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf", blah,&R_MT);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf", blah,&kcMT);


    //make sure we have the right values
    //printf("Read in motor numbers as %ld %ld\n",N[0],N[1]);
    //printf("Read in kcMT as %lf\n",kcMT);


    // Consequent parameters

    muCargoTranslation=1/(6*pi*eta*R);    //Sphere mobility from Stokes-Einstein-Southerland
    muCargoRotation=1/(8*pi*eta*pow(R,3));
    for(m=0;m<2;m++){
      mu_m[m]=D_m[m]/kBT;
      printf("mu_m is %lf\n",mu_m[m]);
    }
    DCargoRotation=kBT*muCargoRotation;
    DCargoTranslation=kBT*muCargoTranslation;

    z_MT=-R-z_MT_offset; //z location of the MT R-.05

    //find maximum time step for attached motors
    //set to satisfy
    dt_max_Motor=0;
    if(N[0]>0){
        dt_max_Motor=.9*1/(k_m[0]*mu_m[0]);
    }
    if( N[1]>0 && (k_m[1]*mu_m[1]) > (k_m[0]*mu_m[0]) ){
        dt_max_Motor=.9*1/(k_m[1]*mu_m[1]);
    }
    if(dt_max_Motor==0){
        if(verboseTF>2){
            printf("dt_max for spring is 0 (no motors?) - setting to default.\n");
        }
        dt_max_Motor=dt_default;
    }

    //find maximum time step for steric spring that keeps cargo out of MT
    dt_max_Steric=.9*muCargoTranslation*1/(kcMT);

    //find max time step for just diffusion
    //set to satisfy sqrt(D*dt)<<R
    dt_max_Diffusion=0;
    if(N[0]>0){
        dt_max_Diffusion=.01*pow(R,2)/D_m[0];
    }
    if(N[1]>0 && D_m[1]>D_m[0]){
        dt_max_Diffusion=.01*pow(R,2)/D_m[1];
    }
    if(dt_max_Diffusion==0){
        if(verboseTF>2){
            printf("dt_max for diffusion is 0 (no motors?) - setting to default.\n");
        }
        dt_max_Diffusion=dt_default;
    }

    //the default max is the smaller of the two maximum dt's
    if(dt_max_Diffusion<dt_max_Motor){
        dt_max_base=dt_max_Diffusion;
        if(verboseTF>0){
            printf("Choosing max time step based on diffusion, dt=%g\n",dt_max_base);
        }
    }
    else{
        dt_max_base=dt_max_Motor;
        if(verboseTF>0){
            printf("Choosing max time step based on motor spring, dt=%g\n",dt_max_base);
        }
    }

    //overrule time step manually if too large
    if(dt_max_base>dt_default){
        dt_max_base=dt_default;
        if(verboseTF>0){
            printf("Time step too large, overruling. dt=%f\n",dt_max_base);
        }
    }


    //all of this may not have been necessay since dt_max_Motor is also a
    //function of D_m. May always be lower at measured k_m of 320 pN/micron

    for(m=0;m<2;m++){
      unloaded_step_rate[m]=fabs(v_f[m]/step_size[m]);
    }

    /************ Simulation Keywords FROM FILE *******************/

    for(int n_lines=1;n_lines<=5;n_lines++)
      fgets(tmpString, 100, fParams);

    //Initial Locations

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %d %lf",blah,&InitialLocations,&SetAtBottom,&InitAngle);

    for(int n_lines=1;n_lines<=16;n_lines++)
      fgets(tmpString, 100, fParams);

    //Motor Diffusion

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&MotorDiffusion);

    for(int n_lines=1;n_lines<=15;n_lines++)
      fgets(tmpString, 100, fParams);

    //InitialBinding

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&InitialBinding,&initial_head);

    for(int n_lines=1;n_lines<=13;n_lines++)
    fgets(tmpString, 100, fParams);

    //Binding

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&Binding,&innerlimit);

    for(int n_lines=1;n_lines<=13;n_lines++)
    fgets(tmpString, 100, fParams);

    //Unbinding

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&Unbinding);

    for(int n_lines=1;n_lines<=13;n_lines++)
      fgets(tmpString, 100, fParams);

    //Stepping

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&Stepping,&input_step_rate);

    for(int n_lines=1;n_lines<=13;n_lines++)
        fgets(tmpString, 100, fParams);

    //initial nucleotide Behavior

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&InitialNucleotideBehavior);

    for(int n_lines=1;n_lines<=13;n_lines++)
        fgets(tmpString, 100, fParams);

    //Nucleotide

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf %lf",blah,&NucleotideBehavior,&base_exchange_rate[0],&base_exchange_rate[1]);

    for(int n_lines=1;n_lines<=17;n_lines++)
        fgets(tmpString, 100, fParams);

    //Motor Loading

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&MotorLoading);

    for(int n_lines=1;n_lines<=7;n_lines++)
      fgets(tmpString, 100, fParams);

    //CargoBehavior

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&CargoBehavior);

    for(int n_lines=1;n_lines<=13;n_lines++)
    fgets(tmpString, 100, fParams);

    //External Force

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf %lf %lf",blah,&external_force,&Ftrap[0],&Ftrap[1],&Ftrap[2]);

    for(int n_lines=1;n_lines<=6;n_lines++)
      fgets(tmpString, 100, fParams);

    //ExternalTorque

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf %lf %lf",blah,&external_torque,&TorqeExt[0],&TorqeExt[1],&TorqeExt[2]);

    for(int n_lines=1;n_lines<=6;n_lines++)
      fgets(tmpString, 100, fParams);

    //Use Steric

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&UseSteric);

    for(int n_lines=1;n_lines<=9;n_lines++)
    fgets(tmpString, 100, fParams);

    //ReturnDetails

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %d %d",blah,&ReturnDetails,&ReturnHeads,&ReturnForces);

    for(int n_lines=1;n_lines<=12;n_lines++)
      fgets(tmpString, 100, fParams);

    //ReturnFinalState

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&ReturnFinalState);

    for(int n_lines=1;n_lines<=6;n_lines++)
      fgets(tmpString, 100, fParams);

    //End conditions

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&Requirebound);

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&StopOnMotor2Attach);

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&StopOnAllbound);

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&StopOnStep);

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf",blah,&StopOnTime);

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf",blah,&StopOnDistance);

    fgets(tmpString, 100, fParams);
    if(isnan(theta_c)){
        sscanf(tmpString,"%s %d %lf",blah,&StopBelowThetaC,&theta_c);
    }
    else{//if not NAN, the value was set in command line so trash it
        sscanf(tmpString,"%s %d %lf", blah,&StopBelowThetaC,&trash);
        //StopBelowThetaC=1;
    }

    //debugging

    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf",blah,&dt_override);

    if(dt_override){
        dt_max_base=dt_override;
        if(verboseTF>0){
            printf("Overriding dt. Now %g\n",dt_override);
        }
    }

    //close file
    fclose(fParams);

}
