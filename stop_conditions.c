void evaluate_stop_conditions();
int any_motor_past_ToW_zone();
int anystopped();
int anybound(int MTnum);

void evaluate_stop_conditions(){

    //find if we've hit any of the end conditions

    if ((Requirebound || MultiMTassay) && prematureReturn==0){ // check if there are no motors bound

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

        //If the cargo ToWed, then fell off, count it as a pass or switch
        if(prematureReturn == 1 && MultiMTassay==1 && ToW){
            if(activeMT==1 && center[0]>0){
                //if was walking on first MT (and had passed the cross point), pass
                prematureReturn=13;
            }else if(activeMT==2){
                //if was walking on second MT, switch
                prematureReturn=14;
            }else{

                //leave it as just a detachment

                // printf("\n\nError in pass or switch determination after ToW\n\n");
                // graceful_exit=1;
            }
        }
    }

    //for the experiment where we want to stop once the second motor attaches
    //check if second motor is bound
    if(StopOnMotor2Attach && prematureReturn==0){
        if(bound[0][1]){
            prematureReturn=2;
        }
    }

    //for the mean first passage time test where we wait until all motors
    //attach
    if (StopOnAllbound && prematureReturn==0){ // check if there are motors not bound
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

    if(StopOnStep && prematureReturn==0){
        if(step>StopOnStep){
            prematureReturn=4;
        }
    }

    if(StopOnTime && prematureReturn==0){
        if(t_inst>StopOnTime){
            prematureReturn=5;
        }
    }

    if(StopOnDistance && prematureReturn==0){
        if(locs[0][0][0]>StopOnDistance){
            prematureReturn=6;
        }
    }

    if(StopBelowThetaC && prematureReturn==0){
        convert_loc_to_spherical();
        if(locs_sph[0][0][1]<theta_c){
            prematureReturn=7;
        }
    }

    if(MultiMTassay==1 && prematureReturn==0){

        //above, we've required at least one motor to be bound

        //start the timer if we have at least one motor bound to both MTs
        if(timer==0 &&
            ((anybound(1) && anybound(2)) ||
            (Stepping==5 && anystopped())) ){

            ToWing=1;
            timer=dt;
            ToW_start=t_inst;
            ToWs+=1;

            //if we haven't yet undergone a ToW event, mark the time
            // if(!ToW){
            //     ToW_start=t_inst;
            // }else if(t_inst<ToW_end+.25){//if we have, check if it has been <.25s since the end of the last TOW
            //     //if it hasn't, don't update the start time as we count it as one ToW
            // }else{//if it has been more than .25s since the end of the last ToW, it's a new event
            //     //reset start time
            //     ToW_start=t_inst;
            // }
        }

        //increment the timer if still have both MTs bound
        if(timer>0 &&
            ((anybound(1) && anybound(2)) ||
            (Stepping==5 && anystopped())) ){
            timer+=dt;
        }

        //reset the timer if either MT becomes unbound
        if(timer>0 &&
            ( (Stepping!=5 && (!anybound(1) || !anybound(2))) ||
            (Stepping==5 && (!anybound(1) || !anybound(2)) && !anystopped()))){

            ToW_end=t_inst;
            ToWtime+=ToW_end-ToW_start;
            ToWing=0;

            //printf("stopping tow\n" );

            // if(ToW){
            //     if(ToWtime>dt_max_Steric || isnan(ToWtime)){//if there was already a ToW event
            //         if(verboseTF>1){
            //             printf("Micro ToW time: %g\n",timer);
            //             printf("    Macro ToW time: %g\n    started at %g\n    ended at %g\n",ToW_end-ToW_start,ToW_start,ToW_end);
            //         }
            //         ToWtime=ToW_end-ToW_start; //set ToW time to NAN
            //     }else{ //first ToW event
            //         ToWtime=timer; //save value of timer as ToW time
            //         if(verboseTF>1){
            //             printf("Micro ToW time: %g\n",ToWtime);
            //         }
            //     }
            // }else{//Too fast to be considered a ToW event
            //     //don't record anything
            //     if(verboseTF>1){
            //         printf("Dropping ToW event because it was too short\n");
            //     }
            // }

            timer=0;
        }

        //if both MTs are bound for more than a quarter of a second, we have a TOW
        if(timer>.25 && !ToW){
            ToW=1;
            if(verboseTF>1){
                printf("Cargo underwent tug of war!\n");
            }
        }

        //if the cargo goes outside the ToW zone, end the sim
        if(any_motor_past_ToW_zone()){

            if(verboseTF>1){
                printf("Exited ToW zone by motor %d out of ToW zone with center at (%g,%g,%g)\n",any_motor_past_ToW_zone()-1,center[0],center[1],center[2]);
            }

            //if cargo is bound to the first MT, its a pass
            if(anybound(1) && anybound(2)){
                graceful_exit=1;
                printf("Something went wrong, exited ToW zone, but motors bound to both MTs\n");
            }else if(anybound(1)){ //motors bound to 1st MT, it's a pass
                prematureReturn=8;
            }else if(anybound(2)) { //motors bound to 2nd MT, it's a switch
                //all switches are counted as ToWs
                //ToW=1;
                //(take care of this in analysis)
                prematureReturn=9;
            } else {
                graceful_exit=1;
                printf("Something went wrong, exited ToW zone, but not bound to either MT\n");
            }

        }

    }

    if(step>100000000 && prematureReturn==0){
        prematureReturn=10;
        printf("\n\nExit by step limit!\n\n");
    }

    if(StopOnBeadDissociation && prematureReturn==0){
        prematureReturn=11;
        for(k=0;k<n_MTs;k++){
            pointToMTdist(center[0],center[1],center[2],k);
            if(MTdist<.5+R){
                prematureReturn=0;
            }
        }
    }

    if(MultiMTassay==2 && prematureReturn==0){//TOW fraction assay

        //start the timer if we have at least one motor bound to both MTs
        if(anybound(1) && anybound(2) && timer==0){
            timer=dt;
        }

        //increment the timer if still have both MTs bound
        if(anybound(1) && anybound(2) && timer>0){
            timer+=dt;
        }

        //reset the timer if either MT becomes unbound
        if( (!anybound(1) || !anybound(2)) && timer>0){
            timer=0;
        }

        //if both MTs are bound for more than a quarter of a second, we have a TOW
        if(timer>.25){
            prematureReturn=12;
        }

        //if the cargo reaches the end of the ToW zone, its a pass
        if(any_motor_past_ToW_zone()){

            if(verboseTF>1){
                printf("Exited ToW zone with center at (%g,%g,%g)\n",center[0],center[1],center[2]);
            }

            //find out if it's a pass or switch
            if(anybound(1) && anybound(2)){
                graceful_exit=1;
                printf("Something went wrong, exited ToW zone, but motors bound to both MTs\n");
            }else if(anybound(1)){ //motors bound to 1st MT, it's a pass
                prematureReturn=8;
            }else if(anybound(2)){ //no ToW switch
                prematureReturn=12;
            } else {
                graceful_exit=1;
                printf("Something went wrong, exited ToW zone, but no motors bound\n");
            }

        }

    }
}

int any_motor_past_ToW_zone(){
    out_of_ToW_zone=0;
    for(m=0;m<2 && !out_of_ToW_zone;m++){
        for(n=0;n<N[m] && !out_of_ToW_zone;n++){
            if(head[m][n][0]>ToW_zone ||
                (head[m][n][0]< -ToW_zone && t_inst>1) ||
                head[m][n][1]> ToW_zone ||
                head[m][n][1]< -ToW_zone ){
                    out_of_ToW_zone=n+1;
            }
        }
    }

    return(out_of_ToW_zone);
}

int anystopped(){
    stopped=0;
    for(m=0;m<2 && !stopped;m++){
        for(n=0;n<N[m] && !stopped;n++){

            if(step_stopped[m][n]){
                stopped=1;
            }

        }
    }
    return(stopped);
}

int anybound(int MTnum){

    //finds out if any motors are bound to the MT labeled MTnum (1+ numbering)
    //if given MTnum=0, finds if any motor is bound to any MT

    if(MTnum==0){
        Foundbound=0;
        for(m=0;m<2 && !Foundbound;m++){
            for(n=0;n<N[m] && !Foundbound;n++){
                if (bound[m][n]){
                    Foundbound=1;
                }
            }
        }
    } else {
        Foundbound=0;
        for(m=0;m<2 && !Foundbound;m++){
            for(n=0;n<N[m] && !Foundbound;n++){
                if (bound[m][n]==MTnum){
                    Foundbound=1;
                }
            }
        }
    }

    return(Foundbound);
}
