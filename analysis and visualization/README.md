## Matlab code for analyzing and visualizing simulation output

Main functions:
* import_params_and_results.m: imports simulation inputs and outputs into Matlab. Calls:
    * import_params.m
    * import_MT_params.m
    * import_summary.m
    * import_locs.m, which calls transform_vars.m
    * import_head.m, which calls transform_vars.m
    * import_forces.m, which calls transform_vars.m
    * import_omega.m, which calls transform_vars.m
* draw_movie.m: makes of movie of cargo and motor dynamics. Calls:
    * import_params_and_results.m
    * SpinCalc.m
    * draw_cargo.m
    * draw_motor.m
    * plotCircle3D.m
    * draw_MT.m, which calls Cylinder.m
