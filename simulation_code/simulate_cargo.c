// prototypes
int simulate_cargo();

int simulate_cargo()
{
    // Hybrid fixed time step / gillespie with stochastic steppers

    // Setup
    if(verboseTF>2){
        printf("%s: Starting repeat %d\n",runName,j+1);
    }

    if (verboseTF>2)
        printf("\nPerforming setup step\n");
    //set current center to center that was passed in
    //wipe variables which don't reset otherwise
    if (verboseTF>2)
        printf("    Resetting counters and sums\n");

    clear_aggregates(); //aggregate_numbers.c

    if (verboseTF>2)
        printf("    Initial location of the cargo is (%g,%g,%g)\n",center[0],center[1],center[2]);

    // set initial locations of motors -------------------------------------
    initiallocations(); //motorHelpers_setup.c
    //sets locs

    // set initial binding status ---------------------------------------
    initialbinding(); //motorHelpers_setup.c
    //sets bound and head

    // set initial nucleotide status
    //printf("Nucleotide is %d\n",NucleotideBehavior);
    if(NucleotideBehavior){
        initialnucleotide(); //motorHelpers_setup.c
    }
    else{ //if NucleotideBehavior is 0, always be ready (removes effect)
        for (m=0;m<2;m++){
            for(n=0;n<N[m];n++){
                nuc_ready[m][n]=1;
            }
        }
    }
    //sets nuc_ready

    for (m=0;m<2;m++) //()()()()()()()()()()()()()()()()()()()()()()()()()()()()
    {
        //calculate initial forces
        motorloading(); //motorHelpers_rates.c
    } //end of looping over motor types for inital settings ()()()()()()()()()()

    calculate_forces();
    set_brownian_forces_to_0();

    if(verboseTF>2){
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
            Ftrap[0],Ftrap[1],Ftrap[2]);
        printf("    External Torque: (%g,%g,%g)\n",
            TorqeExt[0],TorqeExt[1],TorqeExt[2]);

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
    update_lasts_and_maxes(); //aggregate_numbers.c
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
                        printf("    type%dmotor%d: bind possible was %d, within_L was %d and the rate was %g\n",
                            m,n,bind_possible[m][n][k],within_L[m][n][k],bind_rate[m][n][k]);
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
        dt_max=dt_max_base;
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
                    //printf("nuc_ready of type%dmotor%d is %d\n",m,n,nuc_ready[m][n]);
                    if(bind_possible[m][n][k] && nuc_ready[m][n]){
                        //printf("binding possible for type%dmotor%d with rate %f\n",m,n,bind_rate[m][n][k]);
                        //make sure motor has a chance to diffuse away if
                        //dt_max_base is large
                        if(dt_max>dt_default && !dt_override<0){
                           dt_max=dt_default;
                        }
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
        if(dt_max_MultiMotor<dt_max){
            dt_max = dt_max_MultiMotor;
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
        calculate_forces(); //motorHelpers_sODE.c
        compute_next_locations(); //uses eqs from mathematica to find next locations of cargo and motors

        //keep track of ToW forces
        track_forces(); //aggregate_numbers.c

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
                    printf("\n\nError: Should not have gotten here on choosing action in Gillespie\n\n");
                    exit(5);
                }
            }

            //----------------------------------------------------------------------
            // Upkeep and recording
            //----------------------------------------------------------------------

            // update timestep and step number
            t_inst += dt;
            step ++;

            update_lasts_and_maxes(); //aggregate_numbers.c

            evaluate_stop_conditions(); //aggregate_numbers.c

        }//end of update section, depends on graceful exit

        if (verboseTF>3)
            printf("\n\n Step done, recording data. Time t_inst = %g, step = %ld\n\n", t_inst, step);

        if(ReturnOmega && ReturnDetails>1){
            //update quaternion
            update_quaternion(); //aggregate_numbers.c
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
        return 0;

    } else {

        if (verboseTF>2)
            printf("\nSimulation Ended\n");

        if(verboseTF>1){
            printf("\n%s: repeat %d stopped at t=%g / step %ld by ",runName,j+1,t_inst,step);
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
                case 15:
                    printf("Cargo binding\n");
                    break;
                default:
                    printf("Missed case on reporting end of sim condition\n");
            }
            printf("Cargo location was (%g,%g,%g)\n",center[0],center[1],center[2] );
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
