// prototypes
void initializeDataCollection();
void inLoopDataCollection();
void finalizeDataCollection();
void writeCenterLocs();
void writeHead();
void writeForces();

void initializeDataCollection()
{

    if (ReturnDetails){

        //create the different file names
        //name of file for center location and locations of motors
        strcpy(centerlocsName,runName);
        strcat(centerlocsName,"_Center_and_Anchors");
        strcat(centerlocsName,".txt");
        //file with motor head locations
        strcpy(headName,runName);
        strcat(headName,"_Heads");
        strcat(headName,".txt");
        //file with force values
        strcpy(forcesName,runName);
        strcat(forcesName,"_Forces");
        strcat(forcesName,".txt");


        //Write center and anchor location to file
        fCenterLocs = fopen(centerlocsName, "w");
        //return header line
        fprintf(fCenterLocs, "step time center_x center_y center_z ");
        for(m = 0; m<2; m++){
            for(n=0;n<N[m];n++){
                fprintf(fCenterLocs,"type%dmotor%d_x ",m,n);
                fprintf(fCenterLocs,"type%dmotor%d_y ",m,n);
                fprintf(fCenterLocs,"type%dmotor%d_z ",m,n);
            }
        }
        fprintf(fCenterLocs, "\n");
        //write initial values
        writeCenterLocs();


        //write head locations to file
        fHead=fopen(headName,"w");
        //write header line
        fprintf(fHead, "step time ");
        for(m = 0; m<2; m++){
            for(n=0;n<N[m];n++){
                fprintf(fHead,"type%dmotor%d_x ",m,n);
                fprintf(fHead,"type%dmotor%d_y ",m,n);
                fprintf(fHead,"type%dmotor%d_z ",m,n);
            }
        }
        fprintf(fHead, "\n");
        //write the inital values
        writeHead();
    }//ReturnDetails

    if(ReturnForces){
        //Write center and anchor location to file
        fForces = fopen(forcesName, "w");
        //return header line
        fprintf(fForces, "step time external_x external_y external_z ");
        fprintf(fForces, "steric_x steric_y steric_z ");
        for(m = 0; m<2; m++){
            for(n=0;n<N[m];n++){
                fprintf(fForces,"type%dmotor%d_xRadial ",m,n);
                fprintf(fForces,"type%dmotor%d_yRadial ",m,n);
                fprintf(fForces,"type%dmotor%d_zRadial ",m,n);
                fprintf(fForces,"type%dmotor%d_xTangential ",m,n);
                fprintf(fForces,"type%dmotor%d_yTangential ",m,n);
                fprintf(fForces,"type%dmotor%d_zTangential ",m,n);
            }
        }
        fprintf(fForces, "\n");
        //write initial values
        writeForces();
    }//ReturnForces

} //initializeDataCollection

void writeCenterLocs(){
    //write cargo center and anchor locations
    fprintf(fCenterLocs, "%ld %1.16E %E %E %E ",
            step,
            t_inst,
            center[0],
            center[1],
            center[2]
            );
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fCenterLocs, "%E %E %E ",
                locs[m][n][0],
                locs[m][n][1],
                locs[m][n][2]
                );
        }
    }
    fprintf(fCenterLocs, "\n");
}//writeCenterLocs

void writeHead(){
    //write line of head locations
    fprintf(fHead, "%ld %E ",step,t_inst);
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fHead,"%E %E %E ",
                head[m][n][0],
                head[m][n][1],
                head[m][n][2]
                );
        }
    }
    fprintf(fHead, "\n");
}//writeHead

void writeForces(){
    fprintf(fForces, "%ld %1.16E %E %E %E %E %E %E ",
            step,
            t_inst,
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
                fprintf(fForces, "%E %E %E %E %E %E ",
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
                fprintf(fForces, "%d %d %d %d %d %d ",
                    0,
                    0,
                    0,
                    0,
                    0,
                    0);
            }
        }
    }
    fprintf(fForces, "\n");
}//writeForces

void inLoopDataCollection()
{
    if (ReturnDetails)
    {
        writeCenterLocs();
        writeHead();
    }

    if(ReturnForces){
        writeForces();
    }
}//inLoopDataCollection

void finalizeDataCollection()
{
    if(ReturnDetails){
        fclose(fCenterLocs);
        fclose(fHead);
    }
    if(ReturnForces){
        fclose(fForces);
    }

    strcpy(summaryName,runName);
    strcat(summaryName,"_Summary");
    strcat(summaryName,".txt");

    if(runningInLoop==1){
        fSummary = fopen(summaryName, "a");
    }
    else{
        fSummary = fopen(summaryName, "w");
        fprintf(fSummary, "step time exit_cond D exp_0 pi_0\n");
        if(runningInLoop!=0){
            printf("Bad input for running in loop, default to 0\n");
        }
    }

    fprintf(fSummary, "%ld %1.16E %d %g %g %g\n",step,t_inst,prematureReturn,D_m[0],eps_0[0],pi_0[0]);

    fclose(fSummary);


}
