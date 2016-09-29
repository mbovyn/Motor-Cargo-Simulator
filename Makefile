all:
	gcc -O3 driveMotors.c -o motors.x -I /usr/local/include -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lgsl -lgslcblas -lm

	# -I specifies the location to look for headers to include
	# -L specifies the place to look for libraries
	# -Wl,-rpath,<path> specifies the place to look for linked libraries
	# need to include the three libraries for it to work
	#
	# see
	# https://www.gnu.org/software/gsl/manual/html_node/Linking-programs-with-the-library.html#Linking-programs-with-the-library
	# http://stackoverflow.com/questions/6562403/i-dont-understand-wl-rpath-wl
	# http://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
	# http://stackoverflow.com/questions/8835108/how-to-specify-non-default-shared-library-path-in-gcc-linux-getting-error-whil
	# http://stackoverflow.com/questions/344317/where-does-gcc-look-for-c-and-c-header-files

	#gcc would ususally look these places but it doens't because its set up through
	#xcode
