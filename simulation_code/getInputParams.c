//prototypes
void getInputParams( void );

void getInputParams( void )
{

    /************ Model and numerical parameters FROM FILE *******************/

    //open the parameter file (name specified in drive_motors.c)
    //fParams initialized in motors.h

    //open the MT file
    strcpy(MTparamFileName,paramFileName);
    strcat(MTparamFileName,"_MT_params");
    strcat(MTparamFileName,".txt");
    if( access( MTparamFileName, F_OK ) != -1 ) {
        //file exists
        fMTParams = fopen(MTparamFileName, "r");
    } else {
        // file doesn't exist
        printf("\n\nError! Couldn't open MT params file called:\n%s\n",MTparamFileName);
        exit(1);
    }


    //open the param file
    strcat(paramFileName,"_params");
    strcat(paramFileName,".txt");
    if( access( paramFileName, F_OK ) != -1 ) {
        //file exists
        fParams = fopen(paramFileName, "r");
    } else {
        // file doesn't exist
        printf("\n\nError! Couldn't open params file called:\n%s\n",paramFileName);
        exit(1);
    }

    //My approach: use fgets() to scan each line into the temporary string
    //then use sscanf() to find the values
    //learned the pattern must include the first thing on the line
    //(here stored to string called blah)
    //this lets us have comments in the file
    //(using fscanf didn't like having extra text after the numbers)

    //Go through each line and find the values of the input paramters
    //skip the first few
    for(n_lines=1;n_lines<=13;n_lines++)
    {
      fgets(tmpString, 100, fParams);
    }

    //motor parameters

    fgets(tmpString, 100, fParams);

    //Number of motors
    sscanf(tmpString,"%s %d %d", blah,&N[0], &N[1]);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    //Muller
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&F_s[0], &F_s[1]);
    fgets(tmpString, 100, fParams);

    sscanf(tmpString,"%s %lf %lf", blah,&F_d[0], &F_d[1]);
    fgets(tmpString, 100, fParams);
    //Base unbinding rate
    sscanf(tmpString,"%s %lf %lf", blah,&eps_0[0], &eps_0[1]);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf", blah,&pi_0[0], &pi_0[1]);
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
    sscanf(tmpString,"%s %lf %lf", blah,&D_m[0], &D_m[1]);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);

    //Cargo Parameters

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf %lf %lf", blah,
        &center_initial[0], &center_initial[1],&center_initial[2]);

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf", blah,&R);

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf", blah,&eta);

    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);

    //Microtubule Parameters

    //number of MTs
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d", blah,&n_MTs);
    //MT-cargo steric spring constant
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf", blah,&kcMT);

    //make sure we have the right values
    //printf("Read in motor numbers as %ld %ld\n",N[0],N[1]);
    //printf("Read in kcMT as %lf\n",kcMT);

    for(m=0;m<2;m++){
      unloaded_step_rate[m]=fabs(v_f[m]/step_size[m]);
    }

    /************ Simulation Keywords FROM FILE *******************/

    for(n_lines=1;n_lines<=5;n_lines++)
      fgets(tmpString, 100, fParams);

    //Initial Locations

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %d %lf",blah,&InitialLocations,&SetAtBottom,&InitAngle);

    for(n_lines=1;n_lines<=16;n_lines++)
      fgets(tmpString, 100, fParams);

    //Motor Diffusion

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&MotorDiffusion);

    if(MotorDiffusion<10){
        if(N[0]+N[1] > available_motors_free){
            printf("\n\nError! Exiting!\nAsked for unsupported number of free motors\nCompile with different keyword to include more\n\n");
            exit(2);
        }
    }else{
        if((N[0]+N[1] > available_motors_bead)
        || ((available_motors_bead==101 && (N[0]+N[1]-1)%10!=0) && !(N[0]+N[1]==0))){
            printf("\n\nError! Exiting!\nAsked for unsupported number of bead motors\nCompile with different keyword\n\n");
            exit(2);
        }
    }

    for(n_lines=1;n_lines<=20;n_lines++)
      fgets(tmpString, 100, fParams);

    //InitialBinding

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&InitialBinding,&initial_head);

    for(n_lines=1;n_lines<=13;n_lines++)
    fgets(tmpString, 100, fParams);

    //Binding

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&Binding,&innerlimit);

    for(n_lines=1;n_lines<=13;n_lines++)
    fgets(tmpString, 100, fParams);

    //Unbinding

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&Unbinding);

    for(n_lines=1;n_lines<=13;n_lines++)
      fgets(tmpString, 100, fParams);

    //Stepping

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&Stepping,&input_step_rate);

    for(n_lines=1;n_lines<=13;n_lines++)
        fgets(tmpString, 100, fParams);

    //initial nucleotide Behavior

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&InitialNucleotideBehavior);

    for(n_lines=1;n_lines<=13;n_lines++)
        fgets(tmpString, 100, fParams);

    //Nucleotide

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf %lf",blah,&NucleotideBehavior,&base_exchange_rate[0],&base_exchange_rate[1]);

    for(n_lines=1;n_lines<=17;n_lines++)
        fgets(tmpString, 100, fParams);

    //Motor Loading

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&MotorLoading);

    for(n_lines=1;n_lines<=7;n_lines++)
      fgets(tmpString, 100, fParams);

    //CargoBehavior

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&CargoBehavior);

    for(n_lines=1;n_lines<=13;n_lines++)
    fgets(tmpString, 100, fParams);

    //External Force

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf %lf %lf",blah,&external_force,&Ftrap[0],&Ftrap[1],&Ftrap[2]);
    //printf("\n\n\nFtrap[0] is %lf\n\n\n",Ftrap[0]);

    for(n_lines=1;n_lines<=6;n_lines++)
        fgets(tmpString, 100, fParams);

    //ExternalTorque

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf %lf %lf",blah,&external_torque,&TorqeExt[0],&TorqeExt[1],&TorqeExt[2]);

    for(n_lines=1;n_lines<=6;n_lines++)
        fgets(tmpString, 100, fParams);

    //Use Steric

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&UseSteric);

    for(n_lines=1;n_lines<=9;n_lines++)
        fgets(tmpString, 100, fParams);

    //ReturnDetails

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %d %d %d",blah,&ReturnDetails,&ReturnHeads,&ReturnForces,&ReturnOmega);

    for(n_lines=1;n_lines<=12;n_lines++)
        fgets(tmpString, 100, fParams);

    //ReturnFinalState

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&ReturnFinalState);

    for(n_lines=1;n_lines<=6;n_lines++)
        fgets(tmpString, 100, fParams);

    //End conditions
    if(verboseTF>1){
        printf("Stopping on:\n");
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&Requirebound);

    if(Requirebound && verboseTF>1){
        printf("     All motors unbound\n");
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&StopOnMotor2Attach);

    if(StopOnMotor2Attach && verboseTF>1){
        printf("     type0motor1 attach\n");
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&StopOnAllbound);

    if(StopOnAllbound && verboseTF>1){
        printf("     All motors bound\n");
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %ld",blah,&StopOnStep);

    if(StopOnStep && verboseTF>1){
        printf("     Step %ld\n",StopOnStep);
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf",blah,&StopOnTime);

    if(StopOnTime && verboseTF>1){
        printf("     After %g seconds\n",StopOnTime);
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %lf",blah,&StopOnDistance);

    if(StopOnDistance && verboseTF>1){
        printf("     Cargo x location > %g microns\n",StopOnDistance);
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&StopBelowThetaC,&theta_c);

    if(StopBelowThetaC && verboseTF>1){
        printf("     Motor below critical angle of %g\n",theta_c);
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %lf",blah,&MultiMTassay,&MT_angle);

    if(MultiMTassay && verboseTF>1){
        printf("     MT assay conditions\n");
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&StopOnBeadDissociation);

    if(StopOnBeadDissociation && verboseTF>1){
        printf("     Bead > .5 microns from all MTs\n");
    }

    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&StopOnCargoBinding);

    //success condition

    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d %d",blah,&success,&success_mode);

    //debugging

    for(n_lines=1;n_lines<=15;n_lines++)
        fgets(tmpString, 100, fParams);

    sscanf(tmpString,"%s %lf",blah,&dt_override);

    //check bit
    //need 2 because fgets doesn't read past the last line
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&check_bit);
    fgets(tmpString, 100, fParams);
    sscanf(tmpString,"%s %d",blah,&check_bit2);

    if(check_bit!=732 || check_bit2!=576){
        printf("\n\n\nError! Exiting!\n\n\nCheck bit incorrect, mismatch between paramers file and read in code\n");
        exit(3);
    }

    //close file
    fclose(fParams);

    if(verboseTF>2){
        printf("read in all params from params file\n");
    }

    //Read in MT params from MTparams file

    //skip the header lines
    for(n_lines=1;n_lines<=5;n_lines++)
    {
      fgets(tmpString, 100, fMTParams);
    }

    //the parameters of each MT
    for(i=0;i<n_MTs;i++){
        fgets(tmpString, 100, fMTParams);
        sscanf(tmpString,"(%lf %lf %lf) (%lf %lf %lf) %lf",
            &MTpoint[i][0],&MTpoint[i][1],&MTpoint[i][2],
            &MTvec[i][0],&MTvec[i][1],&MTvec[i][2],
            &R_MT[i]);
    }

    //set offset if one is input
    if(!isnan(z_MT_offset)){
        if(MultiMTassay){
            if(verboseTF>1){
                printf("z_MT_offset input. Moving MT2 z from %g",MTpoint[1][2]);
            }
            MTpoint[1][2]=-z_MT_offset;
            if(verboseTF>1){
                printf(" to %g\n",MTpoint[1][2]);
            }
        } else {
            MTpoint[0][2]+=z_MT_offset;
        }
    }

    //if we're doing an MT assay, find the ToW zone distance
    if(MultiMTassay){

        if(verboseTF>1){
            printf("Multi MT assay detected\n");
        }

        //enforce assumed MTvec
        MTvec[0][0]=1;
        MTvec[0][1]=0;
        MTvec[0][2]=0;

        if(verboseTF>1){
            printf("    Forcing first MTvec to (%g,%g,%g)\n",MTvec[0][0],MTvec[0][1],MTvec[0][2]);
        }

        //if MT_angle is input, override MTvec
        if(!isnan(MT_angle)){
            //assumes primary MT in (1,0,0) direction
            //angle for second MT is ccw from that (given in degrees for simplicity of input)
            MT_angle*=pi/180;
            MTvec[1][0]=cos(MT_angle);
            MTvec[1][1]=sin(MT_angle);
            MTvec[1][2]=0;

            if(verboseTF>1){
                printf("    MT_angle given,forcing second MTvec to ");
            }

        }else{//find from input MTvec
            //reduced from acos( MTvec[0] . MTvec[1] )
            // assuming MTvec[1] = (1,0,0)
            MT_angle=acos(MTvec[1][0]);

            if(verboseTF>1){
                printf("    MTvec given as ");
            }
        }

        if(verboseTF>1){
            printf("(%g,%g,%g). MT angle is %g degrees\n",MTvec[1][0],MTvec[1][1],MTvec[1][2],MT_angle*180/pi);
        }

        //set correct ToW_zone for this angle and separation distance
        //determined in ToWzone.nb
        //distance between nearest points on MT is difference in centers-(sum of MT radii)
        //s=fabs(MTpoint[0][2]-MTpoint[1][2])-R_MT[0]-R_MT[1];
        s=fabs(MTpoint[0][2]-MTpoint[1][2]);
        //expression from notebook
        //+ 20nm for safety factor for stretch in motors
        //ToW_zone=.05+sqrt((2*L[0] + 2*R - s)*(2*L[0] + 2*R + s))/sin(MT_angle);
        ToW_zone=sqrt(pow(2*(L[0]+.02) + 2*R + sqrt(2)*R_MT[0]+R_MT[1],2) - pow(s,2))/sin(MT_angle);
        // printf("L[0]= %g, R= %g, s= %g\n",L[0],R,s);
        if(verboseTF>1){
            printf("    ToW zone is %g microns\n",ToW_zone);
        }


        //set correct inital center for ToW assay
        if(verboseTF>1){
            printf("    Moving initial cargo center from (%g,%g,%g) ",center_initial[0],center_initial[1],center_initial[2]);
        }

        center_initial[0]=MTpoint[0][0]-ToW_zone;

        if(verboseTF>1){
            printf("to (%g,%g,%g)\n",center_initial[0],center_initial[1],center_initial[2]);
        }
    }

    //print out what we have
    if(verboseTF>1){
        printf("Running with %d MTs, with locations, unit vectors and radii:\n",n_MTs);
        for(i=0;i<n_MTs;i++){
            printf("     (%g,%g,%g) (%g,%g,%g) %g\n",
            MTpoint[i][0],MTpoint[i][1],MTpoint[i][2],
            MTvec[i][0],MTvec[i][1],MTvec[i][2],
            R_MT[i]);
        }
    }

    fclose(fMTParams);

    ////////////////////////////////////////////////////////////////////////////
    // Consequent parameters

    muCargoTranslation=1/(6*pi*eta*R);    //Sphere mobility from Stokes-Einstein-Southerland
    muCargoRotation=1/(8*pi*eta*pow(R,3));
    for(m=0;m<2;m++){
      mu_m[m]=D_m[m]/kBT;
    }
    DCargoRotation=kBT*muCargoRotation;
    DCargoTranslation=kBT*muCargoTranslation;

    //find maximum time step
    //There are various restrictions based on not letting the motors go too
    //far off the cargo surface
    if(verboseTF>1){
        printf("Choosing Timesteps:\n");
    }

    //Find stable timestep for motor spring
    //timestep is restricted dynamically in simulate_cargo.c during gillespie
    //timestep choosing based on number of motors attached
    dt_max_Motor=0;
    if(N[0]>0){
        dt_max_Motor=.9*1/(k_m[0]*muCargoTranslation);
    }
    if( N[1]>0 && (k_m[1]*muCargoTranslation) > (k_m[0]*muCargoTranslation) ){
        dt_max_Motor=.9*1/(k_m[1]*muCargoTranslation);
    }
    if(dt_max_Motor==0){
        dt_max_Motor=dt_default;
    }
    if(verboseTF>2){
        printf("    Max time step for single motor spring is %g\n",dt_max_Motor);
    }

    //find maximum time step for steric spring that keeps cargo out of MT
    dt_max_Steric=.9*1/(muCargoTranslation*kcMT);
    if(verboseTF>2){
        printf("    Max time step for steric spring is %g\n",dt_max_Steric);
    }

    //find max time step for diffusion of the motors
    //set to satisfy calcuation in anchor diffusion time step.nb
    //knocked down by a factor of 10 because motors were still going too far
    if(N[0]>0){
        dt_max_Diffusion=.1*(pow(R,2)/D_m[0])*pow(tan(pow(3*.005/R,1/3.)),2)/72;
    } else if(N[1]>0 && D_m[1]>D_m[0]){
        dt_max_Diffusion=.1*(pow(R,2)/D_m[1])*pow(tan(pow(3*.005/R,1/3.)),2)/72;
    } else {
        dt_max_Diffusion=dt_default;
    }
    if(verboseTF>2){
        printf("    Max time step for diffusion is %g\n",dt_max_Diffusion);
    }

    //find maximum time step for cargo rotation (6 sigma sqrt(2Ddt), again
    //knocked down by a factor of 10
    //dt_max_rotation=.1*pow((pi/30),2)*(8*pi*eta*pow(R,3)/kBT);
    //.005 instead of .01 fixes errors for large cargos
    dt_max_rotation=.1*(pow(R,2)*(8*pi*eta*pow(R,3)/kBT))*pow(tan(pow(3*.005/R,1/3.)),2)/72;
    if(verboseTF>2){
        printf("    Max time step for rotation is %g\n",dt_max_rotation);
    }
    //Manually found that even 20nm diameter cargos are ok at 5e-8
    if(dt_max_rotation<5e-8){
        dt_max_rotation=5e-8;
        if(verboseTF>1){
            printf("     Rotation dt bottomed out, setting to %g\n",dt_max_rotation);
        }
    }


    //the default max is the smallest of the restrictions, or the base time step
    if(dt_override<0){
        dt_max_base=INF;
    } else {
        dt_max_base=dt_default;
    }
    if(verboseTF>1){
        printf("    Time step set to dt=%f\n",dt_max_base);
    }

    if(dt_max_Diffusion<dt_max_base){
        dt_max_base=dt_max_Diffusion;
        if(verboseTF>1){
            printf("     Lowering base time step based on motor diffusion, dt=%g\n",dt_max_base);
        }
    }
    //don't need to include motor time step, as it's implemented automatically
    //before gillespie timestep choice
    // if(dt_max_Motor<dt_max_base){
    //     dt_max_base=dt_max_Motor;
    //     if(verboseTF>1){
    //         printf("     Lowering base time step based on motor spring, dt=%g\n",dt_max_base);
    //     }
    // }
    if(dt_max_rotation<dt_max_base){
        dt_max_base=dt_max_rotation;
        if(verboseTF>1){
            printf("     Lowering base time step based on cargo rotation, dt=%g\n",dt_max_base);
        }
    }

    if(dt_override>0){
        dt_max_base=dt_override;
        if(verboseTF>0){
            printf("Overriding dt. Now %g\n",dt_override);
        }
    }

}
