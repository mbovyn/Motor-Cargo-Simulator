all:
	gcc -O3 driveMotors.c -o motors.x -I /usr/local/include -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lgsl -lgslcblas -lm

mult:
	gcc -O3 driveMotors_mult.c -o motors_mult.x -lm

#dataCollection.c getInputParams.c motorHelpers_rates.c motorHelpers_setup.c motorHelpers_sODE.c motors.h simulate_cargo.c
