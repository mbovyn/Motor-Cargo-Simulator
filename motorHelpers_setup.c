// Prototypes

void initiallocations();
void initialbinding();
void initialnucleotide();
//helper helpers
void pickpointsphere();
void findMTdist();
void closestPointOnMT(double x,double y,double z,int MTnum);
void pointToMTdist(double x,double y,double z, int MTnum);


// void pickpointsphere(){
//     //find random points on sphere for each motor according to
//     //http://mathworld.wolfram.com/SpherePointPicking.html
//
//     for(n=0;n<N[m];n++){
//         uu[n]=RAND;
//         vv[n]=RAND;
//     }
//
//     //convert random u's to random azimuths
//     for(n=0;n<N[m];n++)
//         az[n]=2*pi*uu[n];
//
//     //convert random v's to random elevations
//     //need -pi/2 to convert from Wolfram's convention of 0 to pi to
//     //Matlab's of -pi/2 to pi/2
//     for(n=0;n<N[m];n++)
//         el[n]=acos(2*vv[n]-1)-pi/2;
//
//     //generate cartesian coords from spherical ones
//     for(n=0;n<N[m];n++){
//         rcosel[n] = R*cos(el[n]);
//         x[n]=rcosel[n]*cos(az[n]);
//         y[n]=rcosel[n]*sin(az[n]);
//         z[n]=R*sin(el[n]);
//     }
// }


void pickpointsphere(){
    //find random point on the unit sphere
    //http://mathworld.wolfram.com/SpherePointPicking.html
    uu=RAND;
    vv=RAND;

    //convert random u's to random azimuths
    az=2*pi*uu;

    //convert random v's to random elevations
    //need -pi/2 to convert from Wolfram's convention of 0 to pi to
    //Matlab's of -pi/2 to pi/2
    el=acos(2*vv-1)-pi/2;

    //generate cartesian coords from spherical ones
    x=cos(el)*cos(az);
    y=cos(el)*sin(az);
    z=sin(el);
}

void initiallocations(){

    //uses only parameters to generate initial locations
    //sets locs
    switch(InitialLocations){
        case 3:
            //initial locations set to the top of the sphere
            for(n=0;n<N[m];n++){
              init_locs[n][2]=R;
            }
            break;
        case 4:
            //initial locations set to the bottom of the sphere
            for(n=0;n<N[m];n++)
                init_locs[n][2]=-R;
            break;
        case 2:

            //set these to the initial locations, adjust for center of cargo
            for(n=0;n<N[m];n++){
                pickpointsphere();
                for(i=0;i<3;i++){
                    if(i==0)
                        init_locs[n][i]=x*R+center[i];
                    if(i==1)
                        init_locs[n][i]=y*R+center[i];
                    if(i==2)
                        init_locs[n][i]=z*R+center[i];
                    }
            }
            break;

        case 7: //start at a defined angle

            for(n=0;n<N[m];n++){
                init_locs[n][0]=R*cos(pi/180*InitAngle)*cos(0);
                init_locs[n][1]=R*cos(pi/180*InitAngle)*sin(0);
                init_locs[n][2]=R*sin(pi/180*InitAngle);
            }

            break;

    //     case 'LocationsOther'
    //
    //         //take input of initial locations as arguement for InitialLocations
    //         //parameter so we can set them outside the function
    //
    //         init_locs=p.Results.OtherInitialLocations{m};
    //
    //     otherwise
    //     error('Not a valid initial location type')
    // end
        default:
            printf("Not a valid initial location type\n");
    }//switch

    //if passed the setting to have one of the motors on the bottom
    if(SetAtBottom){
        //if passed 1, want to attach for m=0 (kinesin)
        //if passed 2, attach for m=1 (dynein)
        if(SetAtBottom==1 && m==0){
            init_locs[0][0]=0;
            init_locs[0][1]=0;
            init_locs[0][2]=-R;
        }
        if(SetAtBottom==2 && m==1){
            init_locs[0][0]=0;
            init_locs[0][1]=0;
            init_locs[0][2]=-R;
        }
        if(SetAtBottom==3 && m==0){
            init_locs[0][0]=0;
            init_locs[0][1]=0;
            init_locs[0][2]=R;
        }
        if(SetAtBottom==4 && m==1){
            init_locs[0][0]=0;
            init_locs[0][1]=0;
            init_locs[0][2]=R;
        }
    }//set at bottom

    //set the generated initial locations to the current location
    for(n=0;n<N[m];n++){
        //printf("%d %f %f %f\n",m,init_locs[n][0],init_locs[n][1],init_locs[n][2]);
        for(i=0;i<3;i++){
            locs[m][n][i]=init_locs[n][i];
        }
    }
} // finished initiallocations

void vecToClosestPointOnMT(double x,double y,double z, int MTnum){
    //from mathematica file
    cVector[0] = (-x + MTpoint[MTnum][0] - MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]))*(1 - R_MT[MTnum]/sqrt(pow(x - MTpoint[MTnum][0] + MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(y - MTpoint[MTnum][1] + MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(z - MTpoint[MTnum][2] + MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2)));
    cVector[1] = (-y + MTpoint[MTnum][1] - MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]))*(1 - R_MT[MTnum]/sqrt(pow(x - MTpoint[MTnum][0] + MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(y - MTpoint[MTnum][1] + MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(z - MTpoint[MTnum][2] + MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2)));
    cVector[2] = (-z + MTpoint[MTnum][2] - MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]))*(1 - R_MT[MTnum]/sqrt(pow(x - MTpoint[MTnum][0] + MTvec[MTnum][0]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(y - MTpoint[MTnum][1] + MTvec[MTnum][1]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2) + pow(z - MTpoint[MTnum][2] + MTvec[MTnum][2]*((-x + MTpoint[MTnum][0])*MTvec[MTnum][0] + (-y + MTpoint[MTnum][1])*MTvec[MTnum][1] + (-z + MTpoint[MTnum][2])*MTvec[MTnum][2]),2)));

    // printf("Vec from (%g,%g,%g) to MT%d at (%g,%g,%g): (%g,%g,%g)\n",
    // x,y,z,MTnum,MTpoint[MTnum][0],MTpoint[MTnum][1],MTpoint[MTnum][2],cVector[0],cVector[1],cVector[2]);
}

void pointToMTdist(double x,double y,double z, int MTnum){
    vecToClosestPointOnMT(x,y,z,MTnum);
    MTdist = sqrt(pow(cVector[0],2) + pow(cVector[1],2) + pow(cVector[2],2));

    // printf("Distance from (%g,%g,%g) to MT%d at (%g,%g,%g): %g\n",
    // x,y,z,MTnum,MTpoint[MTnum][0],MTpoint[MTnum][1],MTpoint[MTnum][2],MTdist);
}

void findMTdist(){
    //Find out if each motor is close enough to bind to the MT
    //sets bind_possible
    for(n=0;n<N[m];n++){
        if(bound[m][n]==0){

            //for each MT, find the distance from the anchor
            for(k=0;k<n_MTs;k++){
                // printf("Calling pointtoMTdist from findMTdist\n");
                pointToMTdist(locs[m][n][0],locs[m][n][1],locs[m][n][2],k);
                if (MTdist<=L[m]) {
                    bind_possible[m][n][k]=1;
                }else{
                    bind_possible[m][n][k]=0;
                }
            }

        }else{
            for(k=0;k<n_MTs;k++){
                bind_possible[m][n][k]=0;
            }
        }
    }
}

void initialbinding(){

    //Set no motors to be bound before we start (need this for findMTdist)
    for(n=0;n<N[m];n++){
        bound[m][n]=0;
    }

    switch (InitialBinding) {
        case 1: //Bind all in range

            //call the function that find the distance from each motor to the MT
            findMTdist();

            //set bound status to mirror capture possibility
            for(n=0;n<N[m];n++){
                for(k=0;k<n_MTs;k++){
                    //set bound to MT number
                    bound[m][n]=(k+1)*bind_possible[m][n][k];
                }
            }
            //Note: this will always bind the motor to the last MT if there are multiple MTs in range

            break;

        case 2: //Bind only one kinesin to 1st MT

            //find the distance from each anchor to the MT
            findMTdist();

            //attach the one kinesin
            if(m==0){
                done=0;
                //loop through motors to assign binding status
                for(n=0;n<N[m];n++){
                    //of the motors for which capture is possible, attach only one
                    if(bind_possible[m][n][0]){
                        if(done==0){
                            bound[m][n]=1;
                            done=1;
                        }
                        //all others don't attach
                        else{
                            bound[m][n]=0;
                        }
                    }
                    else{
                        bound[m][n]=0;
                    }
                }

                //if none availiable, teleport one over
                if(done==0){
                    locs[0][0][2]=-R;
                    bound[0][0]=1;
                    if(verboseTF>2){
                        printf("Teleported kin to bottom and forced binding\n");
                    }
                }
            }

            break;

        case 3: //don't bind any motors

            //set none bound if we don't want any motors initially bound
            for(n=0;n<N[m];n++){
                bound[m][n]=0;
            }

            break;

        case 4: //Bind only one dyn

            //find the distance from each anchor to the MT
            findMTdist();

            //attach the one dyn
            if(m==1){
                done=0;
                //loop through motors to assign binding status
                for(n=0;n<N[m];n++){
                    //of the motors for which capture is possible, attach only one
                    if(bind_possible[m][n][0]){
                        if(done==0){
                            bound[m][n]=1;
                            done=1;
                        }
                        //all others don't attach
                        else{
                            bound[m][n]=0;
                        }
                    }
                    else{
                        bound[m][n]=0;
                    }
                }

                //if none availiable, teleport one over
                if(done==0){
                    locs[1][0][2]=-R;
                    bound[1][0]=1;
                    printf("Teleported dyn to attach\n");
                }
            }

            break;

        default:
            printf("Not a valid initial binding type\n");
    }

    //set head locations to reflect binding status

    //when motors attach they then have a defined head location
    //this sets the heads directly below the anchor (same x position)
    //should later change to projection from center of cargo?
    for(n=0;n<N[m];n++){
        if(bound[m][n]){
            // printf("Calling closestPoint from head setting\n");
            closestPointOnMT(locs[m][n][0],locs[m][n][1],locs[m][n][2],bound[m][n]-1);
            //printf("cVector is \n", );
            for(i=0;i<3;i++){
                head[m][n][i]=cPoint[i];
            }
        }
        else{
            head[m][n][0]=NAN;
            head[m][n][1]=NAN;
            head[m][n][2]=NAN;
        }
    }

    if (bound[0][0] && initial_head){
        closestPointOnMT(locs[0][0][0],locs[0][0][1],locs[0][0][2],bound[0][0]-1);
        head[0][0][0]=cPoint[0]+R+initial_head;
        head[0][0][1]=cPoint[1];
        head[0][0][2]=cPoint[2];
    } else if(bound[1][0] && initial_head) {
        closestPointOnMT(locs[1][0][0],locs[1][0][1],locs[1][0][2],bound[1][0]-1);
        head[1][0][0]=cPoint[0]+R+initial_head;
        head[1][0][1]=cPoint[1];
        head[1][0][2]=cPoint[2];
    }
}

void closestPointOnMT(double x,double y,double z,int MTnum){
    //find the closest point on the MT to the point given
    vecToClosestPointOnMT(x,y,z,MTnum);
    cPoint[0] = x + cVector[0];
    cPoint[1] = y + cVector[1];
    cPoint[2] = z + cVector[2];

    // printf("Point from (%g,%g,%g) closest to MT%d at (%g,%g,%g): (%g,%g,%g)\n",
    // x,y,z,MTnum,MTpoint[MTnum][0],MTpoint[MTnum][1],MTpoint[MTnum][2],cPoint[0],cPoint[1],cPoint[2]);
}

void initialnucleotide(){

    switch (InitialNucleotideBehavior) {
        case 1: //all start ready
            for(n=0;n<N[m];n++){
                nuc_ready[n][m]=1;
            }
            break;

        case 2: //all start not ready

            for(n=0;n<N[m];n++){
                nuc_ready[n][m]=0;
            }
            break;

        default:
            printf("Invalid Initial Nucleotide Behavior setting\n");
    }
}//finished initialnucleotide
