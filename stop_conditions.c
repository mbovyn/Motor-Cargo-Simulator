void evaluate_stop_conditions();
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
        if(timer>.25 && !ToW){
            ToW=1;
            if(verboseTF>1){
                printf("Cargo underwent tug of war!\n");
            }
        }

        //if the cargo goes outside the ToW zone, end the sim
        if(center[0]>MTpoint[1][0]+ToW_zone ||
            (center[0]<MTpoint[1][0]-ToW_zone && t_inst>1) ||
            center[1]>MTpoint[1][1]+ToW_zone ||
            center[1]<MTpoint[1][1]-ToW_zone ){

            if(verboseTF>1){
                printf("Exited ToW zone with center at (%g,%g,%g)\n",center[0],center[1],center[2]);
            }

            //if cargo is bound to the first MT, its a pass
            if(anybound(1)){
                prematureReturn=8;
            } else if(anybound(2)) {
                prematureReturn=9;
            } else {
                graceful_exit=1;
                printf("Something went wrong, exited ToW zone, but not bound to either MT");
            }

        }

        //if the cargo reaches the end of the ToW zone, its a pass
        if(center[0]>MTpoint[1][0]+ToW_zone){
            prematureReturn=8;
        }
    }

    if(step>100000000 && prematureReturn==0){
        prematureReturn=10;
        printf("\n\nError! Exit by step limit!\n\n");
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
        if(center[0]>MTpoint[1][0]+ToW_zone){
            prematureReturn=8;
        }

    }
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
