// Prototypes

void motorloading();
void stepping_rates();
void unbinding_rates();
void binding_rates();
void nucleotide();
//helper helpers
void convert_loc_to_spherical();

void motorloading()
{
    switch(MotorLoading){

        case 1: //find forces exerted by motors

            //determine forces exerted by motors
            for(n=0;n<N[m];n++){
                if(bound[m][n]){
                    //determine vector length of motor neck
                    for(i=0;i<3;i++){
                        neck_vec[m][n][i]=head[m][n][i]-locs[m][n][i];
                    }
                    //find magnitude of neck length
                    neck_mag[m][n]=sqrt(neck_vec[m][n][0]*neck_vec[m][n][0]
                        +neck_vec[m][n][1]*neck_vec[m][n][1]
                        +neck_vec[m][n][2]*neck_vec[m][n][2]);

                    //
                    // if(neck_mag[m][n]>2*L[m]){
                    //     printf("\n\n\nError! Neck length of type%dmotor%d is more than double the rest length!\nExiting gracefully\n\n\n",m,n);
                    //     graceful_exit=1;
                    // }
                    //if this is greater than rest length, motor is stretched
                    if(neck_mag[m][n]>L[m]){
                        //find the force exerted by the spring motor
                        F_m_mag[m][n]=k_m[m]*(neck_mag[m][n]-L[m]);
                        if(F_m_mag[m][n]>50){
                            printf("\n\n\nError! type%dmotor%d force > 50pN\nExiting gracefully at step %ld\n\n\n",m,n,step);
                            graceful_exit=1;
                        }
                        //find the vector components of this force
                        for(i=0;i<3;i++){
                            unit_vec[i]=neck_vec[m][n][i]/neck_mag[m][n];
                            F_m_vec[m][n][i]=F_m_mag[m][n]*unit_vec[i];
                        }
                    }
                    else{ //if not stretched, exerts no force
                        F_m_mag[m][n]=0;
                    }
                }
                else{ //if not bound, force does not exist
                    F_m_mag[m][n]=NAN;
                }
            }

            break;

        case 2: //motors exert no forces

            for(n=0;n<N[m];n++){
                if(bound[m][n]){
                    F_m_mag[m][n]=0;
                }
                else{
                    F_m_mag[m][n]=NAN;
                }
            }

            break;

        default:
            printf("Invalid MotorLoading Type\n");
            exit(0);
    }

} // finished motorloading

int force_in_MT_direction(){
    //evaluates to 1 if force ON HEAD is in same direction as MT
    return -F_m_vec[m][n][0]*MTvec[bound[m][n]-1][0]+
        -F_m_vec[m][n][1]*MTvec[bound[m][n]-1][1]+
        -F_m_vec[m][n][2]*MTvec[bound[m][n]-1][2] > 0;
}

void stepping_rates()
{
    switch (Stepping) {
        case 1: //motors step at constant rate determined by unloaded velocity

            for(n=0;n<N[m];n++){
                if (bound[m][n]){
                    step_possible[m][n]=1;
                    step_rate[m][n]=unloaded_step_rate[m];
                }
            }

            break;

        case 2: //stepping rate according to Ambarish

            for(n=0;n<N[m];n++){
                if (bound[m][n]){
                    if(F_m_mag[m][n]==0){ //no force

                        step_possible[m][n]=1;
                        step_rate[m][n]=unloaded_step_rate[m];

                    }else if(force_in_MT_direction()){ //force is assisting

                        step_possible[m][n]=1;
                        step_rate[m][n]=unloaded_step_rate[m];

                        //printf("stepping under assisting force\n");

                    }else if(F_m_mag[m][n]/F_s[m]<1){ //force is hindering and below stall

                        step_possible[m][n]=1;
                        step_rate[m][n]=unloaded_step_rate[m]*(1-pow(F_m_mag[m][n]/F_s[m],w[m]));

                        //printf("stepping under hindering force below stall\n");

                    }else{ //force is hindering and greater than stall force
                        step_possible[m][n]=0;
                    }
                }else{ //motor isn't bound
                    step_possible[m][n]=0;
                }
            }

            break;

        case 3: //motors don't step

            for(n=0;n<N[m];n++){
                if (bound[m][n]){
                    step_possible[m][n]=0;
                }
            }
            break;

        case 4: //step at input rate

            for(n=0;n<N[m];n++){
                if (bound[m][n]){
                    step_possible[m][n]=1;
                    step_rate[m][n]=input_step_rate;
                }
            }

            break;

        default:
            printf("Invalid stepping rate type\n");
            exit(0);
    }
} // finished stepping

void unbinding_rates()
{
  switch(Unbinding){
      case 1: //Unbinding from Kunwar and Gross

        for(n=0;n<N[m];n++){
            if(bound[m][n]){
                unbind_possible[m][n]=1;
                //motors below stall unbind exponentially
                if(F_m_mag[m][n]<F_s[m]){
                    unbind_rate[m][n]=eps_0[m]*exp(F_m_mag[m][n]/F_d[m]);
                }
                else{
                    //kinesins above stall unbind linearly
                    if(m==0){
                        unbind_rate[m][n]=a_param[m]+b[m]*F_m_mag[m][n];
                    }
                    //dyneins above stall unbind with catch bond
                    else{
                        unbind_rate[m][n]=1/(a_param[m]*(1-exp(-F_m_mag[m][n]/b[m])));
                    }
                }
            }
            else{
                unbind_possible[m][n]=0;
            }
        }

        break;

    case 2: //constant rate unbinding (no force dependance)

        for(n=0;n<N[m];n++){
            if(bound[m][n]){
                unbind_possible[m][n]=1;
                unbind_rate[m][n]=eps_0[m];
            }
            else{
                unbind_possible[m][n]=0;
            }
        }

        break;

    case 3: //no unbinding

        for(n=0;n<N[m];n++){
            unbind_possible[m][n]=0;
        }

        break;

    case 4: //different for assisting and hindering loads

        for(n=0;n<N[m];n++){
            if(bound[m][n]){
                unbind_possible[m][n]=1;

                // printf("dot product is %g\n",F_m_vec[m][n][0]*MTvec[bound[m][n]-1][0]+
                //     F_m_vec[m][n][1]*MTvec[bound[m][n]-1][1]+
                //     F_m_vec[m][n][1]*MTvec[bound[m][n]-1][1]);

                //under hindering load
                if(F_m_mag[m][n]==0){
                    unbind_rate[m][n]=eps_0[m];
                }else if(!force_in_MT_direction()){

                    //motors below stall unbind exponentially
                    if(F_m_mag[m][n]<F_s[m]){
                        unbind_rate[m][n]=eps_0[m]*exp(F_m_mag[m][n]/F_d[m]);
                    }
                    else{
                        //kinesins above stall unbind linearly
                        if(m==0){
                            unbind_rate[m][n]=a_param[m]+b[m]*F_m_mag[m][n];
                        }
                        //dyneins above stall unbind with catch bond
                        else{
                            unbind_rate[m][n]=1/(a_param[m]*(1-exp(-F_m_mag[m][n]/b[m])));
                        }
                    }

                }else if(force_in_MT_direction()){

                    unbind_rate[m][n] = eps_0[m] * exp(3*F_m_mag[m][n]/F_d[m]);

                }else{
                    printf("Error finding out if load was forward or backward\n");
                    graceful_exit=1;
                }

            }else{
                unbind_possible[m][n]=0;
            }
        }

        break;

    default:
        printf("Invalid Unbinding type\n");
        exit(0);
    }
} //finished unbinding

void convert_loc_to_spherical(){
    //locs_sph[0]=azimuthal angle
    //locs_sph[1]=elevation

    //reference:
    //http://www.mathworks.com/help/matlab/ref/cart2sph.html
    locs_sph[m][n][0]=atan2(locs[m][n][1]-center[1],locs[m][n][0]-center[0]);
    locs_sph[m][n][1]=atan2(locs[m][n][2]-center[2],hypot(locs[m][n][0]-center[0],locs[m][n][1]-center[1]));
}

void binding_rates() //sets bind_possible and bind_rate
{
    switch(Binding){
        case 1:
            //motors can bind if the anchors are closer to the MT
            //than they are long
            findMTdist();
            for(k=0;k<n_MTs;k++){
                for(n=0;n<N[m];n++){
                    if(bind_possible[m][n][k]){
                        bind_rate[m][n][k]=pi_0[m];
                    }
                }
            }

            break;

        case 2:
            //no motors can bind
            for(k=0;k<n_MTs;k++){
                for(n=0;n<N[m];n++){
                    bind_possible[m][n][k]=0;
                }
            }
            break;

        case 3: //motors always bind if possible
            findMTdist();
            for(k=0;k<n_MTs;k++){
                for(n=0;n<N[m];n++){
                    if(bind_possible[m][n][k]){
                        bind_rate[m][n][k]=INF;
                    }
                }
            }

            break;

        case 4: //motors bind if below a certain latitude (for MFP test)
        //1 MT only

            for(n=0;n<N[m];n++){
                convert_loc_to_spherical();
                if(!bound[m][n]){
                    if(locs_sph[m][n][1]<theta_c){
                        bind_possible[m][n][0]=1;
                        bind_rate[m][n][0]=INF;
                    }
                    else{
                        bind_possible[m][n][0]=0;
                    }
                }
                else{
                    bind_possible[m][n][0]=0;
                }
            }

            break;

        case 5: //motors can bind if in range, but not if they're too close

            // findMTdist();
            // for(n=0;n<N[m];n++){
            //     if(bind_possible[m][n][k] && MT_dist[m][n]>L[m]*innerlimit){
            //         bind_rate[m][n]=pi_0[m];
            //     }
            // }

            printf("Code needs to be reconfigured to exclude binding when too close\n");

            break;

        default:
            printf("Not a valid binding type\n");
            exit(0);
        }
}

void nucleotide(){
    switch (NucleotideBehavior) {

        case 0: //no nucleotide behavior (implicit)
            break;

        case 1: //no nucleotide dependance (explicit)

            for(n=0;n<N[m];n++){
                exchange_possible[m][n]=0;
            }
            break;

        case 2:

            for(n=0;n<N[m];n++){
                if(bound[m][n]==0 && nuc_ready[m][n]==0){
                    exchange_possible[m][n]=1;
                    exchange_rate[m][n]=base_exchange_rate[m];
                }
                else{
                    exchange_possible[m][n]=0;
                }
            }
            break;

        default:
            printf("Not a valid nucleotide behavior\n");
            exit(0);
    }
}
