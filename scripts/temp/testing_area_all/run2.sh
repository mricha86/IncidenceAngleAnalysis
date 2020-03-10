#!/bin/bash

#################################################
# Declaration/Initialization of needed varables #
#################################################
CRATERCATALOGS="CraterCatalogList.txt"
MAKEFILE="/Users/mrichardson/Desktop/Incidence_Angle_Analysis/Makefile"
REDUCEDCRATERCATALOGSLIST="ReducedCraterCatalogList.txt"
EXE1_DIR="/Users/mrichardson/Desktop/Incidence_Angle_Analysis/bin/"
EXE1="IncidenceAngleAnalysis"
EXE1_AUXILARYFILE="LROCAuxilaryData.dat"
EXE2_DIR="/Users/mrichardson/Desktop/DBSCAN_Clustering_Code_Matt/"
EXE2="java -cp /Users/mrichardson/Desktop/DBSCAN_Clustering_Code_Matt/classes/ dbscan/Gui"
EXE2_MIN_MARKS_PER_CLUSTER="9"
EXE2_MAP_GRID_SPACING="100000"
EXE2_SEARCH_RADIUS="10"

##########################
# Recompile source codes #
##########################
arg="make -j4 ${MAKEFILE}"
#eval ${arg}

################################################
# Go directly to plotting if data is available #
################################################
if [[ -f ${REDUCEDCRATERCATALOGSLIST} ]]
then
    arg="${EXE1_DIR}${EXE1} ${REDUCEDCRATERCATALOGSLIST}"
    eval ${arg}
    exit
fi

####################
# Incidence angles #
####################
angles=(27.56 37.97 58.21 77.24 82.82)

##############
# Run number #
##############
run=0

####################################################
# Initialize array for reduced crater catalog list #
####################################################
REDUCEDCRATERCATALOGS=()

#####################################################
# Loop through all combinations of incidence angles #
#####################################################
nelements=${#angles[@]}
for(( i=0; i<${nelements}; i++ ))
do
    ########################################
    # Retrieve first incidence angle value #
    ########################################
    incidence_angle_1=${angles[i]}
    
    for(( j=i+1; j<${nelements}; j++ ))
    do
	#########################################
	# Retrieve second incidence angle value #
	#########################################
	incidence_angle_2=${angles[j]}
	
	#############################
	# Produce raw marks catalog #
	#############################
	arg="${EXE1_DIR}${EXE1} ${EXE1_DIR}${EXE1_AUXILARYFILE} ${incidence_angle_1} ${incidence_angle_2}"
	eval ${arg}
	
	##################################
	# Copy crater catalogs into list #
	##################################
	arg="ls Crater_* > ${CRATERCATALOGS}"
	eval ${arg}
	
	##################################
	# Produce reduced crater catalog #
	##################################
	while read -r CRATERCATALOG
	do
	    filename="Reduced_c${CRATERCATALOG:1:14}${run}${CRATERCATALOG:14}"
	    if [[ -f ${filename} ]]
	    then
		REDUCEDCRATERCATALOGS+=("${filename}")
		continue
	    fi
	    arg="$EXE2 ${CRATERCATALOG} ${EXE2_MIN_MARKS_PER_CLUSTER} ${EXE2_MAP_GRID_SPACING} ${EXE2_SEARCH_RADIUS}"
	    eval ${arg}
	    arg="cp out_short_1.txt ${filename}"
	    eval ${arg}
	    arg="rm -rf out_*.txt log.txt"
	    eval ${arg}
	    if [[ -f ${filename} ]]
	    then
		REDUCEDCRATERCATALOGS+=("${filename}")
	    fi
	done < "${CRATERCATALOGS}"

	#######################
	# Increase Run number #
	#######################
	((run++))
	
	##################################
	# Remove raw crater catalog list #
	##################################
	arg="rm -rf ${CRATERCATALOGS} Crater_*"
	eval ${arg}
    done
done

###########################################
# Create reduced crater catalog list file #
###########################################
nelements=${#REDUCEDCRATERCATALOGS[@]}
arg="echo -n >| ${REDUCEDCRATERCATALOGSLIST}"
eval ${arg}
column=1
for(( i=0; i<${nelements}; i++ ))
do
    arg="printf ${REDUCEDCRATERCATALOGS[i]} >> ${REDUCEDCRATERCATALOGSLIST}"
    eval ${arg}
    if [[ ${column} -eq 1 ]]
    then
	arg="printf \"\t\" >> ${REDUCEDCRATERCATALOGSLIST}"
	eval ${arg}
	((column++))
    else
	arg="printf \"\n\" >> ${REDUCEDCRATERCATALOGSLIST}"
	eval ${arg}
	column=1
    fi
done

#################################################
# Create cumulative size-frequency distribution #
#################################################
arg="${EXE1_DIR}${EXE1} ${REDUCEDCRATERCATALOGSLIST}"
eval ${arg}

##################
# Clean up files #
##################
arg="rm -rf Reduced*"
#eval ${arg}
