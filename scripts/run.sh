#!/bin/bash

#################################################
# Declaration/Initialization of needed varables #
#################################################
CRATERCATALOGS="CraterCatalogList.txt"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )/"
MAKEFILE="/Users/mrichardson/Desktop/Incidence_Angle_Analysis/Makefile"
DATASET="Moon"
REDUCEDCRATERCATALOGSLIST="ReducedCraterCatalogList.txt"
EXE1_DIR="/Users/mrichardson/Desktop/Incidence_Angle_Analysis/bin/"
EXE1="IncidenceAngleAnalysis"
#EXE1_AUXILARYFILE="LROCAuxilaryData.dat"
EXE1_AUXILARYFILE="LROCAuxilaryData_Modified.dat"
EXE2_DIR="/Users/mrichardson/Desktop/DBSCAN_Clustering_Code_Matt/"
EXE2="java -cp /Users/mrichardson/Desktop/DBSCAN_Clustering_Code_Matt/classes/ dbscan/Gui"
EXE2_MIN_MARKS_PER_CLUSTER="9"
EXE2_MAP_GRID_SPACING="100000"
EXE2_SEARCH_RADIUS="10"
EXE3="MoonMapperImageBatchDownload.sh"
PLOT="FALSE"

##########################
# Recompile source codes #
##########################
arg="make -j4 -f ${MAKEFILE}"
eval ${arg}

################################################
# Go directly to plotting if data is available #
################################################
#if [[ -f ${REDUCEDCRATERCATALOGSLIST} && "${PLOT}" == "TRUE" ]]
#then
#    arg="${EXE1_DIR}${EXE1} ${REDUCEDCRATERCATALOGSLIST} 1"
#    eval ${arg}
#    exit
#fi

################################
# Produce raw marks catalog(s) #
################################
arg="${EXE1_DIR}${EXE1} ${DATASET} ${EXE1_DIR}${EXE1_AUXILARYFILE}"
# eval ${arg}

# exit

##################################
# Copy crater catalogs into list #
##################################
arg="ls Crater_* > ${CRATERCATALOGS}"
# eval ${arg}

# exit

####################################################
# Initialize array for reduced crater catalog list #
####################################################
REDUCEDCRATERCATALOGS=()

#####################################
# Produce reduced crater catalog(s) #
#####################################
while read -r CRATERCATALOG
do
    filename="Reduced_c${CRATERCATALOG:1}"
    if [[ -f ${filename} ]]
    then
	REDUCEDCRATERCATALOGS+=("${filename}")
	continue
    fi
    arg="${EXE2} ${CRATERCATALOG} ${EXE2_MIN_MARKS_PER_CLUSTER} ${EXE2_MAP_GRID_SPACING} ${EXE2_SEARCH_RADIUS}"
    # eval ${arg}
    arg="cp out_short_1.txt ${filename}"
    # eval ${arg}
    arg="rm -rf out_*.txt log.txt"
    # eval ${arg}
    if [[ -f ${filename} ]]
    then
	REDUCEDCRATERCATALOGS+=("${filename}")
    fi
done < "${CRATERCATALOGS}"

# exit

###########################################
# Create reduced crater catalog list file #
###########################################
nelements=${#REDUCEDCRATERCATALOGS[@]}
arg="echo -n >| ${REDUCEDCRATERCATALOGSLIST}"
# eval ${arg}
column=1
for(( i=0; i<${nelements}; i++ ))
do
    arg="printf ${REDUCEDCRATERCATALOGS[i]} >> ${REDUCEDCRATERCATALOGSLIST}"
    # eval ${arg}
    if [[ ${column} -eq 1 ]]
    then
	arg="printf \"\t\" >> ${REDUCEDCRATERCATALOGSLIST}"
	# eval ${arg}
	((column++))
    else
	arg="printf \"\n\" >> ${REDUCEDCRATERCATALOGSLIST}"
	# eval ${arg}
	column=1
    fi
done

# exit

##################################################
# Create cumulative size-frequency distributions #
##################################################
arg="${EXE1_DIR}${EXE1} ${DIR}${REDUCEDCRATERCATALOGSLIST}"
eval ${arg}

exit

########################
# Plot full LRO images #
########################
IMGCOMP=3

########################
# Make image list file #
########################
IMGLIST="imglist.txt"
arg="echo -n >| ${IMGLIST}"
# eval ${arg}
while read -r CRATERCATALOG
do
    run=$(echo "${CRATERCATALOG}" | awk -F'_' '{print $3}')
    if [[ "${IMGCOMP}" == "${run}" ]]
    then
	imname="${CRATERCATALOG:17:14}"
	if [[ "${imname:12:2}" == "RE" ]]
	then
	    arg="echo ${CRATERCATALOG:17:10}LE 0 10000 >> ${IMGLIST}"
	    # eval ${arg}
	    arg="echo ${CRATERCATALOG:17:10}RE 0 10000 >> ${IMGLIST}"
	    # eval ${arg}
	else
	    arg="echo ${CRATERCATALOG:17:12} 0 10000 >> ${IMGLIST}"
	    # eval ${arg}
	fi
    fi
done < "${CRATERCATALOGS}"

###################
# Retrieve images #
###################
nelements=$(cat ${CRATERCATALOGS} | wc -l)
if [[ ${nelements} -gt 0 ]]
then
    arg="./${EXE3} ${IMGLIST}"
    # eval ${arg}
else
    exit
fi

###############################
# Make image directories file #
###############################
IMGDIRLIST="imgdirlist.txt"
arg="echo -n >| ${IMGDIRLIST}"
# eval ${arg}
while read -r line
do
    imname=$(echo "${line}" | awk -F' ' '{print $1}')
    arg="echo ${DIR}/images_${imname}: >> ${IMGDIRLIST}"
    # eval ${arg}
    arg="ls ${DIR}/images_${imname} >> ${IMGDIRLIST}"
    # eval ${arg}
done < "${IMGLIST}"

#########################
# Plot image comparison #
#########################
val1=$((${IMGCOMP} * 2))
val2=$((${val1} + 1))
arg="${EXE1_DIR}${EXE1} ${EXE1_DIR}${EXE1_AUXILARYFILE} ${REDUCEDCRATERCATALOGS[${val1}]} ${REDUCEDCRATERCATALOGS[${val2}]} ${IMGDIRLIST}"
# eval ${arg}

#####################
# Plot image mosaic #
#####################
arg="${EXE1_DIR}${EXE1} ${EXE1_DIR}${EXE1_AUXILARYFILE} ${IMGDIRLIST}"
#eval ${arg}

#############################################
# Remove auxilary files from image plotting #
#############################################
arg="rm -rf img*"
#eval ${arg}

##################
# Clean up files #
##################
arg="rm -rf Reduced*"
#eval ${arg}
