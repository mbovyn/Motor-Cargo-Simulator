void evaluate_stop_conditions();
int anybound(int MTnum);

void evaluate_stop_conditions(){

    //find if we've hit any of the end conditions

    if (Requirebound || MultiMTassay){ // check if there are no motors bound
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

    if(MultiMTassay==1){

        //above, we've required at least one motor to be bound

        //pass if we make it past the point where a motor can attach to the second MT
        if(center[0]>MTpoint[1][0]+R){
            prematureReturn=8;
        }

        if(center[1]>R+L[0]){
            prematureReturn=9;
        }
    }

    if(step>100000000){
        prematureReturn=10;
    }

    if(StopOnBeadDissociation){
        prematureReturn=11;
        for(k=0;k<n_MTs;k++){
            pointToMTdist(center[0],center[1],center[2],k);
            if(MTdist<.5+R){
                prematureReturn=0;
            }
        }
    }

    if(MultiMTassay==2){//TOW fraction assay

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

        //if the cargo has walked past where it can bind the second MT, its a pass
        if(center[0]>MTpoint[1][0]+R){
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