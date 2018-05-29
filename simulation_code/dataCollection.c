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

int open_exist(char fName[100]);
void write_all();


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
            fprintf(fInUse,"Mag_%02d_%02d     ",m,n);
            fprintf(fInUse,"Vec_%02d_%02d_x   ",m,n);
            fprintf(fInUse,"Vec_%02d_%02d_y   ",m,n);
            fprintf(fInUse,"Vec_%02d_%02d_z   ",m,n);
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
    fprintf(fInUse, "exit_cond success last_bound_center_x     last_bound_center_y     last_bound_center_z     ");
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"lb_head_type%02dmotor%02d_x ",m,n);
            fprintf(fInUse,"lb_head_type%02dmotor%02d_y ",m,n);
            fprintf(fInUse,"lb_head_type%02dmotor%02d_z ",m,n);
        }
    }
}

void writeToWHeader(){
    fprintf(fInUse, "ToW_time MT_angle ToWs F_ToW[0] F_ToW[1] F2_ToW[0] F2_ToW[1] FMT_ToW[0] FMT_ToW[1] F2MT_ToW[0] F2MT_ToW[1] FMTb_ToW[0] FMTb_ToW[1] FH_ToW[0] FH_ToW[1] F2H_ToW[0] F2H_ToW[1] Fteam_ToW[0] Fteam_ToW[1] FonMT_ToW[0][0] FonMT_ToW[0][1] FonMT_ToW[1][0] FonMT_ToW[1][1] FonOT_ToW[0] FonOT_ToW[1] n_ToW[0] n_ToW[1] off_count[0] off_count[1]");
}

void initializeDataCollection()
{
    if(verboseTF>0){
        printf("Writing details ");
        if(ReturnDetails==1){
            printf("every step\n");
        }else if(ReturnDetails==2){
            printf("every time a chemical event happens\n");
        }else if(ReturnDetails==3){
            printf("every 1000 steps\n");
        }else if(ReturnDetails==4){
            printf("every .001s\n");
        }else{
            printf("never");
        }
    }

    //create file name, open file and write header if file is new

    //summary file
    strcpy(summaryName,runName);
    strcat(summaryName,"_Summary");
    strcat(summaryName,".txt");

    newfile=open_exist(summaryName);
    fSummary=fInUse;
    if( newfile ) {
        writeBaseHeader();
        writeSummaryHeader();
        fprintf(fInUse, "\n");
    }

    if(MultiMTassay){
        strcpy(ToWName,runName);
        strcat(ToWName,"_ToW");
        strcat(ToWName,".txt");

        newfile=open_exist(ToWName);
        fToW=fInUse;
        if( newfile ) {
            writeBaseHeader();
            writeToWHeader();
            fprintf(fInUse, "\n");
        }
    }

    //if (ReturnDetails){

        //center location and locations of anchors
        if(ReturnCenterLocs){
            strcpy(centerlocsName,runName);
            strcat(centerlocsName,"_Center_and_Anchors");
            strcat(centerlocsName,".txt");

            newfile=open_exist(centerlocsName);
            fCenterLocs=fInUse;
            if( newfile ) {
                writeBaseHeader();
                writeCenterLocsHeader();
                fprintf(fInUse, "\n");
            }
        }//ReturnCenterLocs

        if(ReturnHeads){
            //file with motor head locations
            strcpy(headName,runName);
            strcat(headName,"_Heads");
            strcat(headName,".txt");

            newfile=open_exist(headName);
            fHead=fInUse;
            if( newfile ) {
                writeBaseHeader();
                writeHeadHeader();
                fprintf(fInUse, "\n");
            }
        }//ReturnHeads

        if(ReturnForces){
            //file with force values
            strcpy(forcesName,runName);
            strcat(forcesName,"_Forces");
            strcat(forcesName,".txt");

            newfile=open_exist(forcesName);
            fForces=fInUse;
            if( newfile ) {
                writeBaseHeader();
                writeForcesHeader();
                fprintf(fInUse, "\n");
            }
        }//ReturnForces

        if(ReturnOmega){
            //file with rotation quaternions
            strcpy(omegaName,runName);
            strcat(omegaName,"_Omega");
            strcat(omegaName,".txt");

            newfile=open_exist(omegaName);
            fOmega=fInUse;
            if( newfile ) {
                writeBaseHeader();
                writeOmegaHeader();
                fprintf(fInUse, "\n");
            }
        }//ReturnOmega

    //}//ReturnDetails

} //initializeDataCollection

//If file already exists, open in append mode
//if it doesn't, open and return 1 so we know to write the header
int open_exist(char fName[100]){
    //printf("%s\n",fName);
    if( access( fName, F_OK ) != -1 ) {
        //file exists
        fInUse = fopen(fName, "a");
        return 0;
    } else {
        // file doesn't exist
        fInUse = fopen(fName, "w");
        return 1;
    }
}

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
                fprintf(fInUse, "%+13.6E %+13.6E %+13.6E %+13.6E %+15.8E %+15.8E %+15.8E %+15.8E %+15.8E %+15.8E ",
                    F_m_mag[m][n],
                    F_m_vec[m][n][0],
                    F_m_vec[m][n][1],
                    F_m_vec[m][n][2],
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
                fprintf(fInUse, "%+-13.6E %+-13.6E %+-13.6E %+-13.6E %+-15.8E %+-15.8E %+-15.8E %+-15.8E %+-15.8E %+-15.8E ",
                    NAN,
                    NAN,
                    NAN,
                    NAN,
                    NAN,
                    NAN,
                    NAN,
                    NAN,
                    NAN,
                    NAN
                    );
            }
        }
    }

    // for(k=0;k<n_MTs;k++){
    //     fprintf(fInUse, "%+1.16E ",MTdistk[k]);
    // }
}//writeForces

void writeOmega(){
    fprintf(fInUse, "%+1.16E %+1.16E %+1.16E ",
            omega[0],
            omega[1],
            omega[2]
            );
}

void writeSummary(){
    fprintf(fInUse, "%9d %7d %-+23.16E %-+23.16E %-+23.16E ",
        prematureReturn,trial_success,
        LastBoundLocation[0],LastBoundLocation[1],LastBoundLocation[2]);
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"%-+23.16E %-+23.16E %-+23.16E ",
                last_bound_head[m][n][0],
                last_bound_head[m][n][1],
                last_bound_head[m][n][2]
                );
        }
    }
}

void writeToW(){
    fprintf(fInUse, "%-+23.16E %8g %d %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %-+23.16E %d %d %+1.16E %+1.16E ",
        ToWtime, MT_angle, ToWs, F_ToW[0], F_ToW[1], F2_ToW[0], F2_ToW[1],
        FMT_ToW[0], FMT_ToW[1], F2MT_ToW[0], F2MT_ToW[1],
        FMTb_ToW[0], FMTb_ToW[1],
        FH_ToW[0], FH_ToW[1], F2H_ToW[0], F2H_ToW[1],
        Fteam_ToW[0], Fteam_ToW[1],
        FonMT_ToW[0][0], FonMT_ToW[0][1], FonMT_ToW[1][0], FonMT_ToW[1][1],
        FonOT_ToW[0], FonOT_ToW[1],
        n_ToW[0], n_ToW[1],
        off_count[0], off_count[1], neck_length, stretch_time);
}

void inLoopDataCollection()
{
    if (ReturnDetails)
    {
        write_all();

        if(MultiMTassay){
            fInUse=fToW;
            writeBase();
            writeToW();
            fprintf(fToW, "\n");
        }
    } //ReturnDetails
}//inLoopDataCollection

void write_all(){
    if(ReturnCenterLocs){
        fInUse=fCenterLocs;
        writeBase();
        writeCenterLocs();
        fprintf(fCenterLocs, "\n");
    }

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
}

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
    fprintf(fSummary, "\n");

    if(MultiMTassay && ReturnDetails==0){
        fInUse=fToW;
        writeBase();
        writeToW();
        fprintf(fToW, "\n");
    }

    write_all();
}

void write_error(){
    //write an error for the run if we exited prematurely
    fInUse=fSummary;
    t_inst=NAN;
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
