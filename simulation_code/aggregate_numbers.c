void clear_aggregates();
void update_quaternion();
void update_lasts_and_maxes();
void track_forces();

void clear_aggregates(){
    for(i=0;i<3;i++){
        center[i]=center_initial[i];
        LastBoundLocation[i]=NAN;
        max_dist[i]=center[i];
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

    omega[0]=NAN;
    omega[1]=NAN;
    omega[2]=NAN;
}

void update_quaternion(){
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

    if (verboseTF>3)
        printf("quaternion is %f %f %f %f\n",quat[0],quat[1],quat[2],quat[3] );
}

void update_lasts_and_maxes(){
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

    for(i=0;i<3;i++){
        if(center[i]>max_dist[i])
            max_dist[i]=center[i];
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
}

void track_forces(){
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
}
