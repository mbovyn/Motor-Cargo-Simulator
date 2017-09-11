// prototypes
int simulate_cargo();

int simulate_cargo()
{
    // Hybrid fixed time step / gillespie with stochastic steppers

    // Setup
    if (verboseTF>2)
        printf("\nPerforming setup step\n\n");

    if(verboseTF>1){
        printf("Starting repeat %d\n",j);
    }

    //set current center to center that was passed in
    //wipe variables which don't reset otherwise
    for(i=0;i<3;i++){
        center[i]=center_initial[i];
        LastBoundLocation[i]=NAN;
    }
    for(k=0;k<n_MTs;k++){
        MTviolationCounter[k]=0;
    }
    set_quat_to_identity();
    timer=0;
    ToW=0;
    ToWs=0;
    ToWtime=0;
    ToWing=0;
    for(k=0;k<n_MTs;k++){
        F_ToW[k]=0;
        F2_ToW[k]=0;
        FMT_ToW[k]=0;
        F2MT_ToW[k]=0;
        FH_ToW[k]=0;
        F2H_ToW[k]=0;
        Fteam_ToW[k]=0;
        FonMT_ToW[0][k]=0;
        FonMT_ToW[1][k]=0;
        FonOT_ToW[k]=0;
        n_ToW[k]=0;

        off_count[k]=0;
    }

    neck_length=0;
    stretch_time=0;

    for (m=0;m<2;m++){
        for(n=0;n<N[m];n++){
            for(i=0;i<3;i++){
                last_bound_head[m][n][i]=NAN;
            }
        }
    }

    if (verboseTF>2)
        printf("Initial location of the cargo is (%g,%g,%g)\n",center[0],center[1],center[2]);

    // set initial locations of motors -------------------------------------
    initiallocations();
    //sets locs

    for (m=0;m<2;m++) //()()()()()()()()()()()()()()()()()()()()()()()()()()()()
    {
        // set initial binding status ---------------------------------------
        initialbinding();
        //sets bound and head

        // set initial nucleotide status
        if(NucleotideBehavior){
            initialnucleotide();
        }
        else{ //if NucleotideBehavior is 0, always be ready (removes effect)
            for(n=0;n<N[m];n++){
                nuc_ready[m][n]=1;
            }
        }
        //sets nuc_ready

        //calculate initial forces
        motorloading();

    } //end of looping over motor types for inital settings ()()()()()()()()()()

    calculate_forces();
    set_brownian_forces_to_0();

    if(verboseTF>3){
        printf("The initial locations of the anchors are set to:\n");
        for (m=0;m<2;m++){
            for(n=0;n<N[m];n++){
                printf("    type%dmotor%d: (%g,%g,%g)\n",
                    m,n,locs[m][n][0],locs[m][n][1],locs[m][n][2]);
            }
        }

        printf("The initial binding state of the motors is:\n");
        for (m=0;m<2;m++){
            for(n=0;n<N[m];n++){
                printf("    type%dmotor%d: %d\n",
                    m,n,bound[m][n]);
            }
        }

        printf("The initial locations of the heads are set to:\n");
        for (m=0;m<2;m++){
            for(n=0;n<N[m];n++){
                printf("    type%dmotor%d: (%g,%g,%g)\n",
                    m,n,head[m][n][0],head[m][n][1],head[m][n][2]);
            }
        }

        printf("The initial forces exerted by the motors are:\n");
        for (m=0;m<2;m++){
            for(n=0;n<N[m];n++){
                printf("    type%dmotor%d: (%g,%g,%g) with magnitude %g\n",
                    m,n,
                    F_m_vec[m][n][0],F_m_vec[m][n][1],F_m_vec[m][n][2],
                    F_m_mag[m][n]);
            }
        }

        printf("The initial forces on the cargo are:\n");
        printf("    External Force: (%g,%g,%g)\n",
            Ftrap[0],Ftrap[0],Ftrap[0]);
        printf("    External Torque: (%g,%g,%g)\n",
            TorqeExt[0],TorqeExt[0],TorqeExt[0]);

    }//end of super verbose display

    // -------------------------------------------------------------------------
    // ---------------------&&&&&&&&&&&&&&&&&&&&&&&&&---------------------------
    //                             Simulate!
    // ---------------------&&&&&&&&&&&&&&&&&&&&&&&&&---------------------------
    // -------------------------------------------------------------------------

    //simulate forward in time

    if (verboseTF>2)
        printf("\nBeginning Simulation\n\n");

    //set initial values
    step   = 1;
    t_inst = 0;

    //setup data collection
    inLoopDataCollection();
    t_rec=dt_rec;

    //Have different options for end condition of the Simulation
    //initially set flag to stop the simualtion to false
    prematureReturn=0;
    graceful_exit=0;

    //simulate until one of the end conditions triggers and sets the flag
    while (!prematureReturn && !graceful_exit)  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    {
        //----------------------------------------------------------------------
        // Find rates for Stepping, Binding and Unbinding
        //----------------------------------------------------------------------

        // for each motor type, 0=kin and 1=dyn
        for (m=0;m<2;m++) //_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_
        {
            //determine forces on motors ---------------------------------------
            motorloading();
            //uses locs, head, and bound to find F_m_mag and F_m_vec

            // find stepping rates ---------------------------------------------
            stepping_rates();
            //uses F_m_mag and bound, sets step_rate and step_possible

            // find unbinding rates --------------------------------------------
            unbinding_rates();
            //uses F_m_mag and bound, sets unbind_rate, unbind_possible

            // find binding rates ----------------------------------------------
            binding_rates();
            //uses locs, sets bind_rate and bind_possible

            // nucleotide exchange ---------------------------------------------
            nucleotide();
            //uses bound, sets exchange_rate, exchange_possible

        } //end of 2nd loop over motor types _+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+

        if(verboseTF>3){

            printf("At step %ld -----------------------------------------------\n",step);
            printf("The forces exerted by the motors are:\n");
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    printf("    type%dmotor%d: (%g,%g,%g) with magnitude %g\n",
                        m,n,
                        F_m_vec[m][n][0],F_m_vec[m][n][1],F_m_vec[m][n][2],
                        F_m_mag[m][n]);
                }
            }

            printf("The stepping status was found to be:\n");
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    printf("    type%dmotor%d: step possible was %d and the rate was %g\n",
                        m,n,step_possible[m][n],step_rate[m][n]);
                }
            }

            printf("The binding status was found to be:\n");
            for (k=0;k<n_MTs;k++){
                printf("    For MT %d:\n",k+1);
                for (m=0;m<2;m++){
                    for(n=0;n<N[m];n++){
                        printf("    type%dmotor%d: bind possible was %d and the rate was %g\n",
                            m,n,bind_possible[m][n][k],bind_rate[m][n][k]);
                    }
                }
            }

            printf("The unbinding status was found to be:\n");
            for (m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    printf("    type%dmotor%d: unbind possible was %d and the rate was %g\n",
                        m,n,unbind_possible[m][n],unbind_rate[m][n]);
                }
            }


        }//end of super verbose display

        //----------------------------------------------------------------------
        //// Gillespie
        //----------------------------------------------------------------------

        //gillespie_dt saves the smallest timestep we find by gillespie
        gillespie_dt=INF;
        //loop through motors and generate time steps for each possible action
        for(m=0;m<2;m++){
            for (n=0;n<N[m];n++)
            {
                // loop through stepping rate
                if(step_possible[m][n]){
                    // generate exponential random variable
                    dtHere = -1/step_rate[m][n]*log(RAND);
                    if (dtHere < gillespie_dt)
                    {
                        gillespie_dt = dtHere;
                        hit_m      = m;
                        hit_n      = n;
                        hit_action = 1; // stepping
                    }
                }

                // loop through binding rates
                for(k=0;k<n_MTs;k++){
                    if(bind_possible[m][n][k] && nuc_ready[m][n]){
                        dtHere = -1/bind_rate[m][n][k]*log(RAND);
                        if (dtHere < gillespie_dt )
                        {
                            gillespie_dt = dtHere;
                            hit_m      = m;
                            hit_n      = n;
                            hit_k      = k;
                            hit_action = 2; // binding
                        }
                    }
                }


                // loop through detachment rates
                if(unbind_possible[m][n]){
                    dtHere = -1/unbind_rate[m][n]*log(RAND);
                    if (dtHere < gillespie_dt)
                    {
                        gillespie_dt = dtHere;
                        hit_m      = m;
                        hit_n      = n;
                        hit_action = 3; // detach
                    }
                }

                // loop through nucleotide exchange rates
                if(NucleotideBehavior && exchange_possible[m][n]){
                    dtHere = -1/exchange_rate[m][n]*log(RAND);
                    if (dtHere < gillespie_dt)
                    {
                        gillespie_dt = dtHere;
                        hit_m      = m;
                        hit_n      = n;
                        hit_action = 4; // exchange
                    }
                }
            }
        } // finished generating reaction rates and finding next event

        //to set motor time step, find number of attached motors
        nbound=0;
        for(m=0;m<2;m++){
            for (n=0;n<N[m];n++){
                if(bound[m][n]){
                    nbound++;
                }
            }
        }

        dt_max_MultiMotor=.9*1/(nbound*k_m[0]*muCargoTranslation);

        //choose dt max for the current situation
        if(dt_max_MultiMotor<dt_max_base){
            dt_max = dt_max_MultiMotor;
        }else{
            dt_max = dt_max_base;
        }
        //if have determined we need steric spring between MT and cargo
        //use the dt determined for that spring
        //need_steric initially set to 0
        if(UseSteric)
            evaluate_steric();

        if(need_steric && dt_max>dt_max_Steric){
            dt_max=dt_max_Steric;
        }

        if (gillespie_dt<dt_max) //someone beat the max time step and gets to go
        {
            dt=gillespie_dt;
        }
        else //nobody's time step was faster than the max step
        {
            // Default to max time step
            dt=dt_max;
            //no action gets taken
            hit_action=0;
        }

        // time step now determined, can do forward euler
        // to move anchors and cargo--------------------------------------------
        setup_solve(); //sets total_pulling_motors, forward equation variables
        calculate_forces(); //finds force values for trap, steric, and splits motor forces to radial and tangential
        compute_next_locations(); //uses eqs from mathematica to find next locations of cargo and motors

        //keep track of ToW forces
        if(MultiMTassay){
            if(ToWing){

                //reset vector sum of forces for this step
                for(k=0;k<n_MTs;k++){
                    for(i=0;i<3;i++){
                        F_ToW_vec[k][i]=0;
                    }
                }

                //motors bound to first MT
                for(m=0;m<2;m++){
                    for (n=0;n<N[m];n++){
                        for(k=0;k<n_MTs;k++){
                            if(bound[m][n]==k+1){
                                F_ToW[k]+=F_m_mag[m][n]*dt;
                                F2_ToW[k]+=pow(F_m_mag[m][n],2)*dt;
                                n_ToW[k]+=1*dt;

                                //vector sum of all forces of motors bound to MT k
                                //for this step
                                for(i=0;i<3;i++){
                                    F_ToW_vec[k][i]+=F_m_vec[m][n][i];
                                }

                            }
                        }
                    }
                }


                for(k=0;k<n_MTs;k++){

                    //MT forces
                    //find magnitude of the steric force
                    Fsterick_mag[k]=sqrt(Fsterick[k][0]*Fsterick[k][0]+Fsterick[k][1]*Fsterick[k][1]+Fsterick[k][2]*Fsterick[k][2]);
                    //impulse exerted by MT
                    FMT_ToW[k]+=Fsterick_mag[k]*dt;

                    //impulse on bead handle
                    //(dot product of sum of motor forces with MTvec)
                    FH_ToW[k]+=(F_ToW_vec[k][0]*MTvec[k][0] + F_ToW_vec[k][1]*MTvec[k][1] + F_ToW_vec[k][2]*MTvec[k][2])*dt;

                    //magnitude of motor team force
                    F_ToW_mag[k]=sqrt(F_ToW_vec[k][0]*F_ToW_vec[k][0] + F_ToW_vec[k][1]*F_ToW_vec[k][1] + F_ToW_vec[k][2]*F_ToW_vec[k][2]);
                    //impulse of motor team
                    Fteam_ToW[k]+=F_ToW_mag[k]*dt;

                    //force of motors trying to pull cargo into MT
                    //F_ToW_vec . Fsterick (unit vectors)
                    if(Fsterick_mag[k]>0){
                        FonMT_ToW[0][k]+=(F_ToW_vec[0][0] * Fsterick[k][0]/Fsterick_mag[k]
                            + F_ToW_vec[0][1] * Fsterick[k][1]/Fsterick_mag[k]
                            + F_ToW_vec[0][2] * Fsterick[k][2]/Fsterick_mag[k])*dt;
                        FonMT_ToW[1][k]+=(F_ToW_vec[1][0] * Fsterick[k][0]/Fsterick_mag[k]
                            + F_ToW_vec[1][1] * Fsterick[k][1]/Fsterick_mag[k]
                            + F_ToW_vec[1][2] * Fsterick[k][2]/Fsterick_mag[k])*dt;
                    } else {
                        FonMT_ToW[0][k]+=0;
                        FonMT_ToW[1][k]+=0;
                    }

                }
                //force pulling on the other motor team
                if(F_ToW_mag[1]>0){
                    FonOT_ToW[0]+=(F_ToW_vec[0][0] * F_ToW_vec[1][0]/F_ToW_mag[1]
                        + F_ToW_vec[0][1] * F_ToW_vec[1][1]/F_ToW_mag[1]
                        + F_ToW_vec[0][2] * F_ToW_vec[1][2]/F_ToW_mag[1])*dt;
                } else {
                    FonOT_ToW[0]+=0;
                }
                if(F_ToW_mag[0]>0){
                    FonOT_ToW[1]+=(F_ToW_vec[1][0] * F_ToW_vec[0][0]/F_ToW_mag[0]
                        + F_ToW_vec[1][1] * F_ToW_vec[0][1]/F_ToW_mag[0]
                        + F_ToW_vec[1][2] * F_ToW_vec[0][2]/F_ToW_mag[0])*dt;
                } else {
                    FonOT_ToW[1]+=0;
                }
                //MT Force blocking (directed against) cargo progress
                FMTb_ToW[0]+=(Fsterick[0][0]*MTvec[1][0] + Fsterick[0][1]*MTvec[1][1] + Fsterick[0][2]*MTvec[1][2])*dt;
                FMTb_ToW[1]+=(Fsterick[1][0]*MTvec[0][0] + Fsterick[1][1]*MTvec[0][1] + Fsterick[1][2]*MTvec[0][2])*dt;

            }
        }

        if(!graceful_exit){

            cargobehavior(); //updates locations

            //Once the step is complete, set the new status after any changes
            //that happened during the step
            if(hit_action){
                if (hit_action == 1) // stepping
                {
                    head[hit_m][hit_n][0] += step_size[hit_m]*MTvec[bound[hit_m][hit_n]-1][0];
                    head[hit_m][hit_n][1] += step_size[hit_m]*MTvec[bound[hit_m][hit_n]-1][1];
                    head[hit_m][hit_n][2] += step_size[hit_m]*MTvec[bound[hit_m][hit_n]-1][2];

                    if(verboseTF>2){
                        printf("Step at %g s:\n    type%ldmotor%ld, force %gpN, rate %g/s\n",
                            t_inst,hit_m,hit_n,F_m_mag[hit_m][hit_n],step_rate[hit_m][hit_n]);
                    }
                }
                else if (hit_action == 2) // binding
                {
                    //set bound status
                    bound[hit_m][hit_n]=hit_k+1;

                    //set head location
                    closestPointOnMT(locs[hit_m][hit_n][0],
                        locs[hit_m][hit_n][1],locs[hit_m][hit_n][2],hit_k);

                    head[hit_m][hit_n][0]=cPoint[0];
                    head[hit_m][hit_n][1]=cPoint[1];
                    head[hit_m][hit_n][2]=cPoint[2];

                    if(verboseTF>2){
                        printf("Binding at %g s:\n    type%ldmotor%ld to MT %d, MT_dist %g microns\n",
                            t_inst,hit_m,hit_n,bound[hit_m][hit_n],MTdist);
                    }
                }
                else if (hit_action == 3) // detachment
                {

                    if(verboseTF>2){
                        printf("Unbinding at %g s:\n    type%ldmotor%ld from MT%d, force %g pN, rate %g/s\n",
                            t_inst,hit_m,hit_n,bound[hit_m][hit_n]-1,F_m_mag[hit_m][hit_n],unbind_rate[hit_m][hit_n]);

                    }

                    off_count[bound[hit_m][hit_n]-1]+=1;

                    //set motor to no longer being bound
                    bound[hit_m][hit_n] = 0;

                    if(Stepping==5){
                        step_stopped[hit_m][hit_n]=0;
                        //printf("resetting step stop for motor %ld\n", hit_n);
                    }

                    //set head position to nan
                    head[hit_m][hit_n][0]=NAN;
                    head[hit_m][hit_n][1]=NAN;
                    head[hit_m][hit_n][2]=NAN;

                    //set nucleotide status
                    if(NucleotideBehavior){
                        nuc_ready[hit_m][hit_n]=0;
                    }


                }
                else if(hit_action==4){ //nucleotide exchange
                    nuc_ready[hit_m][hit_n]=1;

                    if(verboseTF>2){
                        printf("on nucleotide exchange, t was %g\n",t_inst);
                    }
                }
                else
                {
                    printf("Should not have gotten here on choosing action in Gillespie\n");
                    exit(5);
                }
            }

            //----------------------------------------------------------------------
            // Upkeep and recording
            //----------------------------------------------------------------------

            // update timestep and step number
            t_inst += dt;
            step ++;

            //keep track of last bound location
            Foundbound=0;
            for(m=0;m<2;m++){
                for(n=0;n<N[m];n++){
                    if (bound[m][n]){
                        Foundbound=1;
                        for(i=0;i<3;i++){
                            LastBoundLocation[i]=center[i];
                        }
                        for(i=0;i<3;i++){
                            last_bound_head[m][n][i]=head[m][n][i];
                        }
                    }
                }
            }

            //keep track of which MT the cargo is walking on
            //want to do this to know what it's state was before falling off
            if(n_MTs==2){//only if there are 2 MTs
                if(anybound(1) && !anybound(2)){
                    //cargo walking on first MT
                    activeMT=1;
                }else if(!anybound(1) && anybound(2)){
                    //cargo walking on second MT
                    activeMT=2;
                }else if(anybound(1) && anybound(2)){
                    //cargo walking on both MTs
                    activeMT=0;
                }
                //don't do anything if cargo is walking on neither MT
            }

            evaluate_stop_conditions();

        }//end of update section, depends on graceful exit

        if (verboseTF>3)
            printf("\n\n Step done, recording data. Time t_inst = %g, step = %ld\n\n", t_inst, step);

        if(ReturnOmega && ReturnDetails>1){
            //update quaternion

            //calculate new quaternion (from quaternions.nb)
            alpha = sqrt(pow(omega[0],2) + pow(omega[1],2) + pow(omega[2],2));

            if(alpha<1E-10){
                quat1[0] = (10*(384 - 48*pow(alpha,2) + pow(alpha,4))*quat[0] - (1920 - 80*pow(alpha,2) + pow(alpha,4))*(omega[0]*quat[1] + omega[1]*quat[2] + omega[2]*quat[3]))/3840.;
                quat1[1] = ((1920 - 80*pow(alpha,2) + pow(alpha,4))*omega[0]*quat[0] + 10*(384 - 48*pow(alpha,2) + pow(alpha,4))*quat[1] - (1920 - 80*pow(alpha,2) + pow(alpha,4))*(omega[2]*quat[2] - omega[1]*quat[3]))/3840.;
                quat1[2] = (omega[1]*quat[0] + omega[2]*quat[1] + 2*quat[2] - omega[0]*quat[3])/2. - (pow(alpha,2)*(omega[1]*quat[0] + omega[2]*quat[1] + 6*quat[2] - omega[0]*quat[3]))/48. + (pow(alpha,4)*(omega[1]*quat[0] + omega[2]*quat[1] + 10*quat[2] - omega[0]*quat[3]))/3840.;
                quat1[3] = (omega[2]*quat[0] - omega[1]*quat[1] + omega[0]*quat[2] + 2*quat[3])/2. - (pow(alpha,2)*(omega[2]*quat[0] - omega[1]*quat[1] + omega[0]*quat[2] + 6*quat[3]))/48. + (pow(alpha,4)*(omega[2]*quat[0] - omega[1]*quat[1] + omega[0]*quat[2] + 10*quat[3]))/3840.;
            }else{
                quat1[0] = cos(alpha/2.)*quat[0] + ((-(omega[0]*quat[1]) - omega[1]*quat[2] - omega[2]*quat[3])*sin(alpha/2.))/alpha;
                quat1[1] = cos(alpha/2.)*quat[1] + ((omega[0]*quat[0] - omega[2]*quat[2] + omega[1]*quat[3])*sin(alpha/2.))/alpha;
                quat1[2] = cos(alpha/2.)*quat[2] + ((omega[1]*quat[0] + omega[2]*quat[1] - omega[0]*quat[3])*sin(alpha/2.))/alpha;
                quat1[3] = cos(alpha/2.)*quat[3] + ((omega[2]*quat[0] - omega[1]*quat[1] + omega[0]*quat[2])*sin(alpha/2.))/alpha;
            }

            //update
            for(i=0;i<4;i++){
                quat[i]=quat1[i];
            }
            //reset on writing in inLoopDataCollection
        }

        //record data
        if( (!graceful_exit && !prematureReturn)
            &&( ReturnDetails==1
                || (ReturnDetails==2 && hit_action)
                || (ReturnDetails==3 && (step-1)%1000==0)
                || (ReturnDetails==4 && t_inst>t_rec) )){
            inLoopDataCollection();
            if(ReturnDetails==4){
                t_rec+=dt_rec;
            }
        }

        if(ReturnDetails && (prematureReturn || graceful_exit) ){
            inLoopDataCollection();
        }

    } // of time loop=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    //--------------------------------------------------------------------------
    // End of sim
    //--------------------------------------------------------------------------

    if(graceful_exit){

        write_error();
        printf("\n");
        return 6;

    } else {

        if (verboseTF>2)
            printf("Simulation Ended\n");

        if(verboseTF>1){
            printf("repeat %d stopped at t=%g / step %ld by ",j+1,t_inst,step);
            switch (prematureReturn) {
                case 1:
                    printf("detachment\n");
                    break;
                case 2:
                    printf("motor 2 attach\n");
                    break;
                case 3:
                    printf("all bound\n");
                    break;
                case 4:
                    printf("step limit\n");
                    break;
                case 5:
                    printf("time limit\n");
                    break;
                case 6:
                    printf("distance limit\n");
                    break;
                case 7:
                    printf("below theta_c\n");
                    break;
                case 8:
                    printf("pass condition for multiple MT assay\n");
                    break;
                case 9:
                    printf("switch condition for MT switching assay\n");
                    break;
                case 10:
                    printf("Absolute step limit (100 million)\n");
                    break;
                case 11:
                    printf("Cargo Dissociation (more than .5 micron from any MT)\n");
                    break;
                case 12:
                    printf("TOW condition for multiple MT assay\n");
                    break;
                case 13:
                    printf("Pass condition, but fell off before leaving ToW zone\n");
                    break;
                case 14:
                    printf("Switch condition, but fell off before leaving ToW zone\n");
                    break;
                default:
                    printf("Missed case on reporting end of sim condition\n");
            }
            printf("Cargo location was (%g,%g,%g)\n\n",center[0],center[1],center[2] );
        }

        //count up number of results we've labeled as success for this trial

        trial_success=0;
        if(success_mode==1){
            switch(success){
                case 1: //success if type0motor0bound

                    if(bound[0][0]){
                        successes++;
                        trial_success=1;
                    }

                    break;

                case 2: //success if went >10 microns (assuming you start at 0)

                    if(center[0]>10){
                        successes++;
                        trial_success=1;
                    }

                    break;

                case 3: //success if cargo underwent ToW

                    if(ToW){
                        successes++;
                        trial_success=1;
                    }

                //default:
                    //do nothing
            }
        }else{
            if(prematureReturn==success){
                successes++;
                trial_success=1;
            }
        }

        //finalizeDataCollection();
        simulationEndDataCollection();

        return prematureReturn;
    }

}
