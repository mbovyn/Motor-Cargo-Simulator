// prototypes
int simulate_cargo();

int simulate_cargo()
{
    // Hybrid fixed time step / gillespie with stochastic steppers

    // Setup
    if (verboseTF>4)
        printf("\nPerforming setup step\n\n");

    //set current center to center that was passed in
    for(i=0;i<3;i++)
        center[i]=center_initial[i];

    for (m=0;m<2;m++) //()()()()()()()()()()()()()()()()()()()()()()()()()()()()
    {

        // set initial locations of motors -------------------------------------
        initiallocations();
        //sets locs


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

    if(verboseTF>4){
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

    if (verboseTF>4)
        printf("\nBeginning Simulation\n\n");

    //set initial values
    step   = 1;
    t_inst = 0;

    //setup data collection
    inLoopDataCollection();

    //Have different options for end condition of the Simulation
    //initially set flag to stop the simualtion to false
    prematureReturn=0;

    //simulate until one of the end conditions triggers and sets the flag
    while (!prematureReturn)  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
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

        if(verboseTF>4){

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

        //choose dt max for the current situation
        dt_max = dt_max_base;
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
                    printf("on step, t was %g force was %g pN and rate was %g per second\n",
                        t_inst,F_m_mag[hit_m][hit_n],step_rate[hit_m][hit_n]);
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
                    printf("on binding of type%ldmotor%ld to MT %d, t was %g, MT_dist was %g microns\n",
                        hit_m,hit_n,bound[hit_m][hit_n],t_inst,MTdist);
                }
            }
            else if (hit_action == 3) // detachment
            {
                //set motor to no longer being bound
                bound[hit_m][hit_n] = 0;

                //set head position to nan
                head[hit_m][hit_n][0]=NAN;
                head[hit_m][hit_n][1]=NAN;
                head[hit_m][hit_n][2]=NAN;

                //set nucleotide status
                if(NucleotideBehavior){
                    nuc_ready[hit_m][hit_n]=0;
                }

                if(verboseTF>2){
                    printf("on unbinding, t was %g, force was %g pN and rate was %g per second\n",
                        t_inst,F_m_mag[hit_m][hit_n],unbind_rate[hit_m][hit_n]);

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
            }
        }

        //----------------------------------------------------------------------
        // Upkeep and recording
        //----------------------------------------------------------------------

        // update timestep and step number
        t_inst += dt;
        step ++;

        //record data
        if( (ReturnDetails==1 && hit_action) || ReturnDetails>1){
            inLoopDataCollection();
        }

        if (verboseTF>3)
            printf("Time t_inst = %g, timestep step = %ld\n", t_inst, step);

        //find if we've hit any of the end conditions

        if (Requirebound){ // check if there are no motors bound
            prematureReturn = 1;
            Foundbound=0;
            for(m=0;m<2 && !Foundbound;m++){
                for(n=0;n<N[m] && !Foundbound;n++){
                    if (bound[m][n]){
                        prematureReturn = 0;
                        Foundbound=1;
                    }
                }
            }
        }

        //for the experiment where we want to stop once the second motor attaches
        //check if second motor is bound
        if(StopOnMotor2Attach){
            if(bound[0][1]){
                prematureReturn=2;
            }
        }

        //for the mean first passage time test where we wait until all motors
        //attach
        if (StopOnAllbound){ // check if there are motors not bound
            prematureReturn = 3;
            FoundNotbound=0;
            for(m=0;m<2 && !FoundNotbound;m++){
                for(n=0;n<N[m] && !FoundNotbound;n++){
                    if (bound[m][n]==0){
                        prematureReturn = 0;
                        //setting this to true breaks out of the loop
                        FoundNotbound=1;
                    }
                }
            }
        }

        if(StopOnStep){
            if(step>StopOnStep){
                prematureReturn=4;
            }
        }

        if(StopOnTime){
            if(t_inst>StopOnTime){
                prematureReturn=5;
            }
        }

        if(StopOnDistance){
            if(locs[0][0][0]>StopOnDistance){
                prematureReturn=6;
            }
        }

        if(StopBelowThetaC){
            convert_loc_to_spherical();
            if(locs_sph[0][0][1]<theta_c){
                prematureReturn=7;
            }
        }

    } // of time loop=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    //--------------------------------------------------------------------------
    // End of sim
    //--------------------------------------------------------------------------

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
            default:
                printf("Missed case on reporting end of sim condition\n");
            }
        }

    //finalizeDataCollection();
    simulationEndDataCollection();

    return prematureReturn;
}
