// prototypes
void initializeDataCollection();
void inLoopDataCollection();
void finalizeDataCollection();

void writeBaseHeader();
void writeCenterLocsHeader();
void writeHeadHeader();
void writeForcesHeader();
void writeSummaryHeader();
void writeToWHeader();

void writeBase();
void writeCenterLocs();
void writeHead();
void writeForces();
void writeSummary();
void simulationEndDataCollection();

void set_quat_to_identity();


void writeBaseHeader(){
    fprintf(fInUse, "repeat       step time                   ");
}

void writeCenterLocsHeader(){
    fprintf(fInUse, "center_x                center_y                center_z                ");
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"anchor_type%02dmotor%02d_x  ",m,n);
            fprintf(fInUse,"anchor_type%02dmotor%02d_y  ",m,n);
            fprintf(fInUse,"anchor_type%02dmotor%02d_z  ",m,n);
        }
    }
}

void writeHeadHeader(){
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"head_type%02dmotor%02d_x    ",m,n);
            fprintf(fInUse,"head_type%02dmotor%02d_y    ",m,n);
            fprintf(fInUse,"head_type%02dmotor%02d_z    ",m,n);
        }
    }
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"bound_type%02dmotor%02d ",m,n);
        }
    }
}

void writeForcesHeader(){
    fprintf(fInUse, "external_x    external_y    external_z    ");
    fprintf(fInUse, "steric_x      steric_y      steric_z      ");
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"Radial_%02d_%02d_x  ",m,n);
            fprintf(fInUse,"Radial_%02d_%02d_y  ",m,n);
            fprintf(fInUse,"Radial_%02d_%02d_z  ",m,n);
            fprintf(fInUse,"Tangent_%02d_%02d_x ",m,n);
            fprintf(fInUse,"Tangent_%02d_%02d_y ",m,n);
            fprintf(fInUse,"Tangent_%02d_%02d_z ",m,n);
        }
    }
}

void writeOmegaHeader(){
    fprintf(fInUse, "omega_x                omega_y                omega_z                ");
}

void writeSummaryHeader(){
    fprintf(fInUse, "exit_cond success D_anchor eps_0 pi_0   z_MT   R  N[0] Fexternal[2] theta_c MT_angle F_d[0]      eta k_m[0] MT2vecx   MT2vecy   MT2vecz   ToW_time               last_attached_center_x  last_attached_center_y  last_attached_center_z  ");
}

void writeToWHeader(){
    fprintf(fInUse, "ToW_time ToWs F_ToW[0] F_ToW[1] F2_ToW[0] F2_ToW[1] FMT_ToW[0] FMT_ToW[1] F2MT_ToW[0] F2MT_ToW[1] FMTb_ToW[0] FMTb_ToW[1] FH_ToW[0] FH_ToW[1] F2H_ToW[0] F2H_ToW[1] Fteam_ToW[0] Fteam_ToW[1] FonMT_ToW[0][0] FonMT_ToW[0][1] FonMT_ToW[1][0] FonMT_ToW[1][1] FonOT_ToW[0] FonOT_ToW[1] n_ToW[0] n_ToW[1] off_count[0] off_count[1]");
}

void initializeDataCollection()
{

    //open summary file
    strcpy(summaryName,runName);
    strcat(summaryName,"_Summary");
    strcat(summaryName,".txt");

    //if summary file exists from another call, open it
    //otherwise, create it and write the header
    if( access( summaryName, F_OK ) != -1 ) {
        //file exists
        fSummary = fopen(summaryName, "a");
    } else {
        // file doesn't exist
        fSummary = fopen(summaryName, "w");
        fInUse=fSummary;
        writeBaseHeader();
        writeSummaryHeader();
        writeCenterLocsHeader();
        writeHeadHeader();
        fprintf(fSummary, "\n");
    }

    if(MultiMTassay){

        //open summary file
        strcpy(ToWName,runName);
        strcat(ToWName,"_ToW");
        strcat(ToWName,".txt");

        //if file exists from another call, open it
        //otherwise, create it and write the header
        if( access( ToWName, F_OK ) != -1 ) {
            //file exists
            fToW = fopen(ToWName, "a");
        } else {
            // file doesn't exist
            fToW = fopen(ToWName, "w");
            fInUse=fToW;
            writeBaseHeader();
            writeToWHeader();
            fprintf(fToW, "\n");
        }
    }

    if (ReturnDetails){

        //create the different file names
        //name of file for center location and locations of motors

        //sprintf(repeat_number,".%d",j);

        strcpy(centerlocsName,runName);
        //strcat(centerlocsName,repeat_number);
        strcat(centerlocsName,"_Center_and_Anchors");
        strcat(centerlocsName,".txt");

        //Write center and anchor location to file
        fCenterLocs = fopen(centerlocsName, "w");
        //return header line
        fInUse=fCenterLocs;
        writeBaseHeader();
        writeCenterLocsHeader();
        fprintf(fCenterLocs, "\n");

        if(ReturnHeads){
            //file with motor head locations
            strcpy(headName,runName);
            //strcat(headName,repeat_number);
            strcat(headName,"_Heads");
            strcat(headName,".txt");

            //write head locations to file
            fHead=fopen(headName,"w");
            fInUse=fHead;
            //write header line
            writeBaseHeader();
            writeHeadHeader();
            fprintf(fHead, "\n");
        }


        if(ReturnForces){
            //file with force values
            strcpy(forcesName,runName);
            //strcat(forcesName,repeat_number);
            strcat(forcesName,"_Forces");
            strcat(forcesName,".txt");

            //Write center and anchor location to file
            fForces = fopen(forcesName, "w");
            //return header line
            fInUse=fForces;
            writeBaseHeader();
            writeForcesHeader();
            fprintf(fForces, "\n");
        }//ReturnForces

        if(ReturnOmega){
            //file with force values
            strcpy(omegaName,runName);
            //strcat(forcesName,repeat_number);
            strcat(omegaName,"_Omega");
            strcat(omegaName,".txt");

            //Write center and anchor location to file
            fOmega = fopen(omegaName, "w");
            //return header line
            fInUse=fOmega;
            writeBaseHeader();
            writeOmegaHeader();
            fprintf(fOmega, "\n");
        }//ReturnForces

    }//ReturnDetails

} //initializeDataCollection

void writeBase(){
    fprintf(fInUse, "%4d   %10ld %.16E ",j+1,step,t_inst);
}

void writeCenterLocs(){
    //write cargo center and anchor locations
    fprintf(fInUse, "%+.16E %+.16E %+.16E ",
            center[0],
            center[1],
            center[2]
            );
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fInUse, "%+23.16E %+23.16E %+23.16E ",
                locs[m][n][0],
                locs[m][n][1],
                locs[m][n][2]
                );
        }
    }
}//writeCenterLocs

void writeHead(){
    //write line of head locations
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"%-+23.16E %-+23.16E %-+23.16E ",
                head[m][n][0],
                head[m][n][1],
                head[m][n][2]
                );
        }
    }
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"%-19d ",bound[m][n]);
        }
    }
}//writeHead

void writeForces(){
    fprintf(fInUse, "%+E %+E %+E %+E %+E %+E ",
            Ftrap[0],
            Ftrap[1],
            Ftrap[2],
            Fsteric[0],
            Fsteric[1],
            Fsteric[2]
            );

    nn=0;
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            if(bound[m][n]){
                fprintf(fInUse, "%+E %+E %+E %+E %+E %+E ",
                    FmRadial[nn][0],
                    FmRadial[nn][1],
                    FmRadial[nn][2],
                    FmTangential[nn][0],
                    FmTangential[nn][1],
                    FmTangential[nn][2]
                    );
                nn++;
            }
            else{
                fprintf(fInUse, "%d %d %d %d %d %d ",
                    0,
                    0,
                    0,
                    0,
                    0,
                    0);
            }
        }
    }
}//writeForces

void writeOmega(){
    fprintf(fInUse, "%+1.16E %+1.16E %+1.16E ",
            omega[0],
            omega[1],
            omega[2]
            );
}

void writeSummary(){
    fprintf(fInUse, "%9d %7d %8g %5g %4g %+4.3g %.2g %4d %12g %8g %8g %6g %8g %6g %-+6.6f %-+6.6f %-+6.6f %22.16E %-+23.16E %-+23.16E %-+23.16E ",
        prematureReturn,trial_success,
        D_m[0],eps_0[0],pi_0[0],MTpoint[0][2],R,N[0],Ftrap[2],theta_c,
        MT_angle,F_d[0],eta,k_m[0],
        MTvec[1][0],MTvec[1][1],MTvec[1][2],
        ToWtime,
        LastBoundLocation[0],LastBoundLocation[1],LastBoundLocation[2]);
}

void writeToW(){
    fprintf(fInUse, "%-+23.16E %d %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %d %d",
        ToWtime, ToWs, F_ToW[0], F_ToW[1], F2_ToW[0], F2_ToW[1],
        FMT_ToW[0], FMT_ToW[1], F2MT_ToW[0], F2MT_ToW[1],
        FMTb_ToW[0], FMTb_ToW[1],
        FH_ToW[0], FH_ToW[1], F2H_ToW[0], F2H_ToW[1],
        Fteam_ToW[0], Fteam_ToW[1],
        FonMT_ToW[0][0], FonMT_ToW[0][1], FonMT_ToW[1][0], FonMT_ToW[1][1],
        FonOT_ToW[0], FonOT_ToW[1],
        n_ToW[0], n_ToW[1],
        off_count[0], off_count[1]);
}

void inLoopDataCollection()
{
    if (ReturnDetails)
    {
        fInUse=fCenterLocs;
        writeBase();
        writeCenterLocs();
        fprintf(fCenterLocs, "\n");

        if(ReturnHeads){
            fInUse=fHead;
            writeBase();
            writeHead();
            fprintf(fHead, "\n");
        }

        if(ReturnForces){
            fInUse=fForces;
            writeBase();
            writeForces();
            fprintf(fForces, "\n");
        }//ReturnForces

        if(ReturnOmega){

            if(ReturnDetails>1){
                //convert accumlated quaternion to euler vector and reset

                //convert to euler vector (from quaternions.nb)
                if(quat[0]>1 - 1E-10){
                    omega[0] = (2*(488 - 275*quat[0] + 144*pow(quat[0],2) - 50*pow(quat[0],3) + 8*pow(quat[0],4))*quat[1])/315.;
                    omega[1] = (2*(488 - 275*quat[0] + 144*pow(quat[0],2) - 50*pow(quat[0],3) + 8*pow(quat[0],4))*quat[2])/315.;
                    omega[2] = (2*(488 - 275*quat[0] + 144*pow(quat[0],2) - 50*pow(quat[0],3) + 8*pow(quat[0],4))*quat[3])/315.;
                }else{
                    omega[0] = (2*acos(quat[0])*quat[1])/sqrt(1 - pow(quat[0],2));
                    omega[1] = (2*acos(quat[0])*quat[2])/sqrt(1 - pow(quat[0],2));
                    omega[2] = (2*acos(quat[0])*quat[3])/sqrt(1 - pow(quat[0],2));
                }

                //reset quat by setting it to the identity quaternion
                set_quat_to_identity();
            }

            fInUse=fOmega;
            writeBase();
            writeOmega();
            fprintf(fOmega, "\n");
        }//ReturnOmega

        if(MultiMTassay){
            fInUse=fToW;
            writeBase();
            writeToW();
            fprintf(fToW, "\n");
        }
    } //ReturnDetails
}//inLoopDataCollection

void set_quat_to_identity(){
    quat[0]=1;
    quat[1]=0;
    quat[2]=0;
    quat[3]=0;
}

void finalizeDataCollection()
{
    //close any open details files
    if(ReturnDetails){
        fclose(fCenterLocs);

        if(ReturnHeads){
            fclose(fHead);
        }

        if(ReturnForces){
            fclose(fForces);
        }

        if(ReturnOmega){
            fclose(fOmega);
        }
    }//ReturnDetails

    //close summary file
    fclose(fSummary);

    if(MultiMTassay){
        fclose(fToW);
    }
}

void simulationEndDataCollection(){
    //write the information at the end of the simulation
    fInUse=fSummary;
    writeBase();
    writeSummary();
    writeCenterLocs();
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            for(i=0;i<3;i++){
                head[m][n][i]=last_bound_head[m][n][i];
            }
        }
    }
    writeHead();
    fprintf(fSummary, "\n");

    if(MultiMTassay && ReturnDetails==0){
        fInUse=fToW;
        writeBase();
        writeToW();
        fprintf(fToW, "\n");
    }
}

void write_error(){
    //write an error for the run if we exited prematurely
    fInUse=fSummary;
    writeBase();
    //write summary
    prematureReturn=-1;
    trial_success=-1;
    writeSummary();
    //write NANs in place of center locs
    fprintf(fInUse, "%+1.16E %+1.16E %+1.16E ",
            NAN,
            NAN,
            NAN
            );
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fInUse, "%+1.16E %+1.16E %+1.16E ",
                NAN,
                NAN,
                NAN
                );
        }
    }
    fprintf(fSummary, "\n");

    if(MultiMTassay && ReturnDetails==0){
        fInUse=fToW;
        writeBase();
        ToWtime=NAN;
        writeToW();
        fprintf(fToW, "\n");
    }
}
