// prototypes
void initializeDataCollection();
void inLoopDataCollection();
void finalizeDataCollection();

void initializeDataCollection()
{

    #if (ReturnDetails)

        //create the different file names
        //name of file for center location and locations of motors
        strcpy(centerlocsName,runName);
        strcat(centerlocsName,"_Center_and_Anchors");
        strcat(centerlocsName,".txt");
        //file with motor head locations
        strcpy(headName,runName);
        strcat(headName,"_Heads");
        strcat(headName,".txt");


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
        // output results to file
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
        fprintf(fHead, "%ld %E ",step,t_inst);
        //write line of head locations
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
    #endif
}

void inLoopDataCollection()
{
    #if (ReturnDetails)
        // output results to file
        // fCenterLocs = fopen(centerlocsName, "a");
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

        //write line of head locations
        // fHead=fopen(headName,"a");
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

    #endif
}

void finalizeDataCollection()
{
    #if(ReturnDetails)
        fclose(fCenterLocs);
        fclose(fHead);
    #endif

    strcpy(summaryName,runName);
    strcat(summaryName,"_Summary");
    strcat(summaryName,".txt");

    #if(runningInLoop==1)
        fSummary = fopen(summaryName, "a");
    #else
        fSummary = fopen(summaryName, "w");
        fprintf(fSummary, "step time exit_cond D exp_0 pi_0\n");
        if(runningInLoop!=0){
            printf("Bad input for running in loop, default to 0\n");
        }
    #endif

    fprintf(fSummary, "%ld %1.16E %d %g %g %g\n",step,t_inst,prematureReturn,D_m[0],eps_0[0],pi_0[0]);

    fclose(fSummary);


}
