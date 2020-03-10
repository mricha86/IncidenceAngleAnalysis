#!/bin/bash

####################################################################################
################################ Script description ################################ 
# Batch download of LRO subimages from CosmoQuest database for Moon Mapper Project #
####################################################################################

#####################
# Main Script Start #
#####################
current_directory="$(pwd)/"
img_saveDir="/Users/mrichardson/Desktop/Incidence_Angle_Analysis/scripts/images"
img_type=".png"
url_reg_exp="https://s3.amazonaws.com/cosmoquest/data/mappers/moon/sub_images/"

###############################
# Verify number of arguements #
###############################
if [ ${#} -ne 1 ] 
then
    printf "USAGE: %s [Image list]\n" ${0}
    exit
fi

#######################
# Retrieve arguements #
#######################
if [ -e ${1} ]
then
    imagelist=${1}
else
    printf "File '%s' does not exist!\n" ${1}
    exit
fi

##############################
# Iterate through image list #
##############################
while read -r imagename scale maxindex 
do
    ###########################################################
    # Make a directory specifically for current set of images #
    ###########################################################
    if [ ! -d ${img_saveDir}"_"${imagename} ]
    then
       mkdir ${img_saveDir}"_"${imagename}
    fi
       
    ########################
    # Download image files #
    ########################
    for index in $(seq -f "%05g" 0 ${maxindex})
    do
	url="${url_reg_exp}${imagename}/${scale}/${index}${img_type}"
	filename="${imagename}_${scale}_${index}${img_type}"
	saveFile="${img_saveDir}_${imagename}/${filename}"
	if [ ! -f ${saveFile} ]
	then
	    status=$(curl -s --head -w %{http_code} "${url}" -o /dev/null)
	    if [[ ${status} -eq 200 ]]
	    then
		wget -nd -l1 -O ${saveFile} ${url}
	    else
		break
	    fi
	fi
    done
done < ${imagelist}

#############################
# Tarball downloaded images #
#############################
#cd ${img_saveDir}
#tar -czf ${current_directory}CosmoQuestImages.tar.gz *
#cd ${current_directory}

############################
# Remove downloaded images #
############################
#rm -rf ${img_saveDir}*

exit

###################
# Main Script End #
###################
