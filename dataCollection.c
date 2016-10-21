// prototypes
void initializeDataCollection();
void inLoopDataCollection();
void finalizeDataCollection();

void writeBaseHeader();
void writeCenterLocsHeader();
void writeHeadHeader();
void writeForcesHeader();
void writeSummaryHeader();

void writeBase();
void writeCenterLocs();
void writeHead();
void writeForces();
void writeSummary();


void writeBaseHeader(){
    fprintf(fInUse, "step       time                   ");
}

void writeCenterLocsHeader(){
    fprintf(fInUse, "center_x      center_y      center_z      ");
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"type%dmotor%d_x ",m,n);
            fprintf(fInUse,"type%dmotor%d_y ",m,n);
            fprintf(fInUse,"type%dmotor%d_z ",m,n);
        }
    }
}

void writeHeadHeader(){
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"type%dmotor%d_x ",m,n);
            fprintf(fInUse,"type%dmotor%d_y ",m,n);
            fprintf(fInUse,"type%dmotor%d_z ",m,n);
        }
    }
}

void writeForcesHeader(){
    fprintf(fInUse, "external_x    external_y    external_z    ");
    fprintf(fInUse, "steric_x      steric_y      steric_z      ");
    for(m = 0; m<2; m++){
        for(n=0;n<N[m];n++){
            fprintf(fInUse,"Radial_%d_%d_x  ",m,n);
            fprintf(fInUse,"Radial_%d_%d_y  ",m,n);
            fprintf(fInUse,"Radial_%d_%d_z  ",m,n);
            fprintf(fInUse,"Tangent_%d_%d_x ",m,n);
            fprintf(fInUse,"Tangent_%d_%d_y ",m,n);
            fprintf(fInUse,"Tangent_%d_%d_z ",m,n);
        }
    }
}

void writeSummaryHeader(){
    fprintf(fInUse, "exit_cond D_anchor eps_0 pi_0 ");
}

void initializeDataCollection()
{

    if (ReturnDetails){

        //create the different file names
        //name of file for center location and locations of motors

        sprintf(repeat_number,"%d",j);

        strcpy(centerlocsName,runName);
        strcat(centerlocsName,repeat_number);
        strcat(centerlocsName,"_Center_and_Anchors");
        strcat(centerlocsName,".txt");
        //file with motor head locations
        strcpy(headName,runName);
        strcat(headName,repeat_number);
        strcat(headName,"_Heads");
        strcat(headName,".txt");

        //Write center and anchor location to file
        fCenterLocs = fopen(centerlocsName, "w");
        //return header line
        fInUse=fCenterLocs;
        writeBaseHeader();
        writeCenterLocsHeader();
        fprintf(fCenterLocs, "\n");
        //write initial values
        writeBase();
        writeCenterLocs();
        fprintf(fCenterLocs, "\n");

        //write head locations to file
        fHead=fopen(headName,"w");
        fInUse=fHead;
        //write header line
        writeBaseHeader();
        writeHeadHeader();
        fprintf(fHead, "\n");
        //write the inital values
        writeBase();
        writeHead();
        fprintf(fHead, "\n");
    }//ReturnDetails

    if(ReturnForces){
        //file with force values
        strcpy(forcesName,runName);
        strcat(forcesName,repeat_number);
        strcat(forcesName,"_Forces");
        strcat(forcesName,".txt");

        //Write center and anchor location to file
        fForces = fopen(forcesName, "w");
        //return header line
        fInUse=fForces;
        writeBaseHeader();
        writeForcesHeader();
        fprintf(fForces, "\n");
        //write initial values
        writeBase();
        writeForces();
        fprintf(fForces, "\n");
    }//ReturnForces

} //initializeDataCollection

void writeBase(){
    fprintf(fInUse, "%10ld %1.16E ",step,t_inst);
}

void writeCenterLocs(){
    //write cargo center and anchor locations
    fprintf(fInUse, "%+E %+E %+E ",
            center[0],
            center[1],
            center[2]
            );
    for (m = 0; m<2; m++) {
        for(n=0;n<N[m];n++){
            fprintf(fInUse, "%+E %+E %+E ",
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
            fprintf(fInUse,"%+E %+E %+E ",
                head[m][n][0],
                head[m][n][1],
                head[m][n][2]
                );
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

void writeSummary(){
    fprintf(fInUse, "%d         %8g %g     %g    ",prematureReturn,D_m[0],eps_0[0],pi_0[0]);
}

void inLoopDataCollection()
{
    if (ReturnDetails)
    {
        fInUse=fCenterLocs;
        writeBase();
        writeCenterLocs();
        fprintf(fCenterLocs, "\n");
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
    }
}//inLoopDataCollection

void finalizeDataCollection()
{
    //close any open files
    if(ReturnDetails){
        fclose(fCenterLocs);
        fclose(fHead);
    }
    if(ReturnForces){
        fclose(fForces);
    }

    //write the information at the end of the simulation
    fInUse=fSummary;
    writeBase();
    writeSummary();
    writeCenterLocs();
    fprintf(fSummary, "\n");

}
