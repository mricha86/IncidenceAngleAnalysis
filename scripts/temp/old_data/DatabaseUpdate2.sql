DELIMITER $$
DROP PROCEDURE IF EXISTS correct_cosmoquest_mysql_table$$
CREATE PROCEDURE correct_cosmoquest_mysql_table()
BEGIN
/********************************************/
/* Declaration/Initialization of variables */
/********************************************/
DECLARE diff INT;
DECLARE xmax INT;
DECLARE arg INT;
DECLARE x INT;
DECLARE str1 VARCHAR(255);
DECLARE str2 VARCHAR(255);
DECLARE substr1 VARCHAR(255);
DECLARE substr2 VARCHAR(255);
DECLARE substr3 VARCHAR(255); 

/*****************************************/
/* Update 1: Remove current latitude and */
/* longitude variables from image_sets   */
/* table                                 */
/*****************************************/
ALTER TABLE image_sets DROP COLUMN minimum_latitude;
ALTER TABLE image_sets DROP COLUMN maximum_latitude;
ALTER TABLE image_sets DROP COLUMN minimum_longitude;
ALTER TABLE image_sets DROP COLUMN maximum_longitude;

/*************************************/
/* Update 2: Create new latitude and */
/* longitudes variables for          */
/* image_sets table                  */
/*************************************/
ALTER TABLE image_sets ADD COLUMN upper_left_latitude DOUBLE(8,4);
ALTER TABLE image_sets ADD COLUMN upper_left_longitude DOUBLE(8,4);
ALTER TABLE image_sets ADD COLUMN upper_right_latitude DOUBLE(8,4);
ALTER TABLE image_sets ADD COLUMN upper_right_longitude DOUBLE(8,4);
ALTER TABLE image_sets ADD COLUMN lower_right_latitude DOUBLE(8,4);
ALTER TABLE image_sets ADD COLUMN lower_right_longitude DOUBLE(8,4);
ALTER TABLE image_sets ADD COLUMN lower_left_latitude DOUBLE(8,4);
ALTER TABLE image_sets ADD COLUMN lower_left_longitude DOUBLE(8,4);

/******************************************/
/* Update 3: Update cosmoquest image_sets */
/* table for M109215691L. Each corner's   */
/* latitude and longitude (user view)     */
/******************************************/
UPDATE image_sets SET upper_left_latitude=26.09020 WHERE id=3;
UPDATE image_sets SET upper_left_longitude=3.69540 WHERE id=3;
UPDATE image_sets SET upper_right_latitude=26.08950 WHERE id=3;
UPDATE image_sets SET upper_right_longitude=3.63110 WHERE id=3;
UPDATE image_sets SET lower_right_latitude=26.21250 WHERE id=3;
UPDATE image_sets SET lower_right_longitude=3.63110 WHERE id=3;
UPDATE image_sets SET lower_left_latitude=26.21320 WHERE id=3;
UPDATE image_sets SET lower_left_longitude=3.69540 WHERE id=3;

/******************************************/
/* Update 4: Update cosmoquest image_sets */
/* table for M109215691L. Removed 993     */
/* pixels in x dimension                  */
/******************************************/
UPDATE image_sets SET details="<sun_angle>1.5708</sun_angle><width>4089</width><height>8599</height>" WHERE id=3;

/******************************************/
/* Update 5: Update cosmoquest image_sets */
/* table for M109215691R. Maximum/minimum */
/* latitude and longitude (user view)     */
/******************************************/
UPDATE image_sets SET upper_left_latitude=26.09270 WHERE id=4;
UPDATE image_sets SET upper_left_longitude=3.63620 WHERE id=4;
UPDATE image_sets SET upper_right_latitude=26.09200 WHERE id=4;
UPDATE image_sets SET upper_right_longitude=3.56570 WHERE id=4;
UPDATE image_sets SET lower_right_latitude=26.21500 WHERE id=4;
UPDATE image_sets SET lower_right_longitude=3.56570 WHERE id=4;
UPDATE image_sets SET lower_left_latitude=26.21570 WHERE id=4;
UPDATE image_sets SET lower_left_longitude=3.63620 WHERE id=4;

/******************************************/
/* Update 6: Update cosmoquest image_sets */
/* table for M109215691R. Removed 342     */
/* pixels in x dimension                  */
/******************************************/
UPDATE image_sets SET details="<sun_angle>1.5708</sun_angle><width>4670</width><height>8594</height>" WHERE id=4;

/********************************************/
/* Update 7: Update cosmoquest images table */
/* for entries related to image M109215691R */
/* Shifted images by -342 pixels in x dime- */
/* nsion                                    */
/********************************************/
SET diff=342;
SET xmax=487;
SET x=234;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/******************************************/
/* Update 8: Update cosmoquest image_sets */
/* table for M111578606R. Maximum/minimum */
/* latitude and longitude (user view)     */
/******************************************/
UPDATE image_sets SET upper_left_latitude=26.08670 WHERE id=5;
UPDATE image_sets SET upper_left_longitude=3.60420 WHERE id=5;
UPDATE image_sets SET upper_right_latitude=26.08970 WHERE id=5;
UPDATE image_sets SET upper_right_longitude=3.54330 WHERE id=5;
UPDATE image_sets SET lower_right_latitude=26.21320 WHERE id=5;
UPDATE image_sets SET lower_right_longitude=3.54520 WHERE id=5;
UPDATE image_sets SET lower_left_latitude=26.21020 WHERE id=5;
UPDATE image_sets SET lower_left_longitude=3.60610 WHERE id=5;

/******************************************/
/* Update 9: Update cosmoquest image_sets */
/* table for M111578606R. Removed 392     */
/* pixels in x dimension                  */
/******************************************/
UPDATE image_sets SET details="<sun_angle>2.35619</sun_angle><width>3841</width><height>8350</height>" WHERE id=5;

/*********************************************/
/* Update 10: Update cosmoquest images table */
/* for entries related to image M111578606R  */
/* Shifted images by -392 pixels in x dime-  */
/* nsion                                     */
/*********************************************/
SET diff=392;
SET xmax=688;
SET x=488;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 11: Update cosmoquest image_sets */
/* table for M112639452L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-53.32000 WHERE id=6; 
UPDATE image_sets SET upper_left_longitude=-160.67920 WHERE id=6; 
UPDATE image_sets SET upper_right_latitude=-53.32000 WHERE id=6; 
UPDATE image_sets SET upper_right_longitude=-160.50130 WHERE id=6; 
UPDATE image_sets SET lower_right_latitude=-53.74000 WHERE id=6; 
UPDATE image_sets SET lower_right_longitude=-160.50130 WHERE id=6; 
UPDATE image_sets SET lower_left_latitude=-53.74000 WHERE id=6; 
UPDATE image_sets SET lower_left_longitude=-160.67920 WHERE id=6; 

/*******************************************/
/* Update 12: Update cosmoquest image_sets */
/* table for M112639452L. Removed 107      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.785398</sun_angle><width>9081</width><height>34083</height>" WHERE id=6;

/*********************************************/
/* Update 13: Update cosmoquest images table */
/* for entries related to image M112639452L  */
/* Shifted images by -40 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=40;
SET xmax=2504;
SET x=689;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 14: Update cosmoquest image_sets */
/* table for M112639452R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-53.32020 WHERE id=7;
UPDATE image_sets SET upper_left_longitude=-160.82860 WHERE id=7;
UPDATE image_sets SET upper_right_latitude=-53.32020 WHERE id=7;
UPDATE image_sets SET upper_right_longitude=-160.66070 WHERE id=7;
UPDATE image_sets SET lower_right_latitude=-53.74010 WHERE id=7;
UPDATE image_sets SET lower_right_longitude=-160.66070 WHERE id=7;
UPDATE image_sets SET lower_left_latitude=-53.74010 WHERE id=7;
UPDATE image_sets SET lower_left_longitude=-160.82860 WHERE id=7;

/*******************************************/
/* Update 15: Update cosmoquest image_sets */
/* table for M112639452R. Removed 67       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.698132</sun_angle><width>9155</width><height>34195</height>" WHERE id=7;

/*********************************************/
/* Update 16: Update cosmoquest images table */
/* for entries related to image M112639452R  */
/* Shifted images by -67 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=67;
SET xmax=4320;
SET x=2505;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 16: Update cosmoquest image_sets */
/* table for M113934743L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.08580 WHERE id=8;
UPDATE image_sets SET upper_left_longitude=3.69600 WHERE id=8;
UPDATE image_sets SET upper_right_latitude=26.09260 WHERE id=8;
UPDATE image_sets SET upper_right_longitude=3.62880 WHERE id=8;
UPDATE image_sets SET lower_right_latitude=26.17010 WHERE id=8;
UPDATE image_sets SET lower_right_longitude=3.62880 WHERE id=8;
UPDATE image_sets SET lower_left_latitude=26.17010 WHERE id=8;
UPDATE image_sets SET lower_left_longitude=3.69600 WHERE id=8;

/*******************************************/
/* Update 17: Update cosmoquest image_sets */
/* table for M113934743L. Removed 1336     */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>2.79253</sun_angle><width>5021</width><height>5796</height>" WHERE id=8;

/*******************************************/
/* Update 18: Update cosmoquest image_sets */
/* table for M113934743R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.08630 WHERE id=9;
UPDATE image_sets SET upper_left_longitude=3.62960 WHERE id=9;
UPDATE image_sets SET upper_right_latitude=26.08590 WHERE id=9;
UPDATE image_sets SET upper_right_longitude=3.56380 WHERE id=9;
UPDATE image_sets SET lower_right_latitude=26.15990 WHERE id=9;
UPDATE image_sets SET lower_right_longitude=3.56390 WHERE id=9;
UPDATE image_sets SET lower_left_latitude=26.15990 WHERE id=9;
UPDATE image_sets SET lower_left_longitude=3.62960 WHERE id=9;

/*******************************************/
/* Update 19: Update cosmoquest image_sets */
/* table for M113934743R. Removed 28       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>3.14159</sun_angle><width>4380</width><height>5647</height>" WHERE id=9;

/*********************************************/
/* Update 20: Update cosmoquest images table */
/* for entries related to image M113934743R  */
/* Shifted images by -28 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=28;
SET xmax=4688;
SET x=4513;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 21: Update cosmoquest image_sets */
/* table for M115008450L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-57.13020 WHERE id=10;
UPDATE image_sets SET upper_left_longitude=-162.26910 WHERE id=10;
UPDATE image_sets SET upper_right_latitude=-57.13020 WHERE id=10;
UPDATE image_sets SET upper_right_longitude=-162.01060 WHERE id=10;
UPDATE image_sets SET lower_right_latitude=-59.20010 WHERE id=10;
UPDATE image_sets SET lower_right_longitude=-162.26910 WHERE id=10;
UPDATE image_sets SET lower_left_latitude=-59.20010 WHERE id=10;
UPDATE image_sets SET lower_left_longitude=-162.26910 WHERE id=10;

/*******************************************/
/* Update 22: Update cosmoquest image_sets */
/* table for M115008450L. Removed 80       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.314159</sun_angle><width>9209</width><height>132859</height>" WHERE id=10;

/*********************************************/
/* Update 23: Update cosmoquest images table */
/* for entries related to image M115008450L  */
/* Shifted images by -32 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=32;
SET xmax=9788;
SET x=4689;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 24: Update cosmoquest image_sets */
/* table for M115008450R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-57.13010 WHERE id=11;
UPDATE image_sets SET upper_left_longitude=-162.43850 WHERE id=11;
UPDATE image_sets SET upper_right_latitude=-57.13010 WHERE id=11;
UPDATE image_sets SET upper_right_longitude=-162.17070 WHERE id=11;
UPDATE image_sets SET lower_right_latitude=-59.20010 WHERE id=11;
UPDATE image_sets SET lower_right_longitude=-162.17070 WHERE id=11;
UPDATE image_sets SET lower_left_latitude=-59.20010 WHERE id=11;
UPDATE image_sets SET lower_left_longitude=-162.43850 WHERE id=11;

/*******************************************/
/* Update 25: Update cosmoquest image_sets */
/* table for M115008450R. Removed 82       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.296706</sun_angle><width>9588</width><height>133284</height>" WHERE id=11;

/*********************************************/
/* Update 26: Update cosmoquest images table */
/* for entries related to image M115008450R  */
/* Shifted images by -53 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=53;
SET xmax=15023;
SET x=9789;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 27: Update cosmoquest image_sets */
/* table for M117467833R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.21240 WHERE id=12;
UPDATE image_sets SET upper_left_longitude=3.58460 WHERE id=12;
UPDATE image_sets SET upper_right_latitude=26.21210 WHERE id=12;
UPDATE image_sets SET upper_right_longitude=3.65500 WHERE id=12;
UPDATE image_sets SET lower_right_latitude=26.08890 WHERE id=12;
UPDATE image_sets SET lower_right_longitude=3.65500 WHERE id=12;
UPDATE image_sets SET lower_left_latitude=26.08940 WHERE id=12;
UPDATE image_sets SET lower_left_longitude=3.58460 WHERE id=12;

/*******************************************/
/* Update 28: Update cosmoquest image_sets */
/* table for M117467833R. Removed 339      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>3.31613</sun_angle><width>6078</width><height>10342</height>" WHERE id=12;

/*********************************************/
/* Update 29: Update cosmoquest images table */
/* for entries related to image M117467833R  */
/* Shifted images by -230 pixels in x dime-  */
/* nsion                                     */
/*********************************************/
SET diff=230;
SET xmax=15419;
SET x=15024;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 30: Update cosmoquest image_sets */
/* table for M119822622L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.17990 WHERE id=13;
UPDATE image_sets SET upper_left_longitude=3.60260 WHERE id=13;
UPDATE image_sets SET upper_right_latitude=26.17990 WHERE id=13;
UPDATE image_sets SET upper_right_longitude=3.69060 WHERE id=13;
UPDATE image_sets SET lower_right_latitude=26.09110 WHERE id=13;
UPDATE image_sets SET lower_right_longitude=3.69060 WHERE id=13;
UPDATE image_sets SET lower_left_latitude=26.09210 WHERE id=13;
UPDATE image_sets SET lower_left_longitude=3.60260 WHERE id=13;

/*******************************************/
/* Update 31: Update cosmoquest image_sets */
/* table for M119822622L. Removed 3007     */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>3.31613</sun_angle><width>6554</width><height>7194</height>" WHERE id=13;

/*********************************************/
/* Update 32: Update cosmoquest images table */
/* for entries related to image M119822622L  */
/* Shifted images by -109 pixels in x dime-  */
/* nsion                                     */
/*********************************************/
SET diff=109;
SET xmax=15711;
SET x=15420;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 33: Update cosmoquest image_sets */
/* table for M119829425L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.08990 WHERE id=14;
UPDATE image_sets SET upper_left_longitude=3.63960 WHERE id=14;
UPDATE image_sets SET upper_right_latitude=26.08990 WHERE id=14;
UPDATE image_sets SET upper_right_longitude=3.55940 WHERE id=14;
UPDATE image_sets SET lower_right_latitude=26.21290 WHERE id=14;
UPDATE image_sets SET lower_right_longitude=3.55940 WHERE id=14;
UPDATE image_sets SET lower_left_latitude=26.21280 WHERE id=14;
UPDATE image_sets SET lower_left_longitude=3.63960 WHERE id=14;

/*******************************************/
/* Update 34: Update cosmoquest image_sets */
/* table for M119829425L. Removed 899      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.349066</sun_angle><width>6035</width><height>9471</height>" WHERE id=14;

/*********************************************/
/* Update 35: Update cosmoquest images table */
/* for entries related to image M119829425L  */
/* Shifted images by -29 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=29;
SET xmax=16065;
SET x=15712;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 36: Update cosmoquest image_sets */
/* table for M120920427L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-57.10020 WHERE id=15;
UPDATE image_sets SET upper_left_longitude=-161.83850 WHERE id=15;
UPDATE image_sets SET upper_right_latitude=-57.10020 WHERE id=15;
UPDATE image_sets SET upper_right_longitude=-161.6308 WHERE id=15;
UPDATE image_sets SET lower_right_latitude=-58.15010 WHERE id=15;
UPDATE image_sets SET lower_right_longitude=-161.6308 WHERE id=15;
UPDATE image_sets SET lower_left_latitude=-58.15010 WHERE id=15;
UPDATE image_sets SET lower_left_longitude=-161.83850 WHERE id=15;

/*******************************************/
/* Update 37: Update cosmoquest image_sets */
/* table for M120920427L. Removed 117      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>2.35619</sun_angle><width>11212</width><height>97730</height>" WHERE id=15;

/*********************************************/
/* Update 38: Update cosmoquest images table */
/* for entries related to image M120920427L  */
/* Shifted images by -73 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=73;
SET xmax=21797;
SET x=16066;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 39: Update cosmoquest image_sets */
/* table for M120920427R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-57.10010 WHERE id=16;
UPDATE image_sets SET upper_left_longitude=-161.66920 WHERE id=16;
UPDATE image_sets SET upper_right_latitude=-57.09020 WHERE id=16;
UPDATE image_sets SET upper_right_longitude=-161.50140 WHERE id=16;
UPDATE image_sets SET lower_right_latitude=-58.14020 WHERE id=16;
UPDATE image_sets SET lower_right_longitude=-161.50140 WHERE id=16;
UPDATE image_sets SET lower_left_latitude=-58.15010 WHERE id=16;
UPDATE image_sets SET lower_left_longitude=-161.66920 WHERE id=16;

/*******************************************/
/* Update 40: Update cosmoquest image_sets */
/* table for M120920427R. Removed 119      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>2.35619</sun_angle><width>11450</width><height>98022</height>" WHERE id=16;

/*********************************************/
/* Update 41: Update cosmoquest images table */
/* for entries related to image M120920427R  */
/* Shifted images by -44 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=44;
SET xmax=27522;
SET x=21798;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 42: Update cosmoquest image_sets */
/* table for M122184104R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.09160 WHERE id=17;
UPDATE image_sets SET upper_left_longitude=3.66140 WHERE id=17;
UPDATE image_sets SET upper_right_latitude=26.09230 WHERE id=17;
UPDATE image_sets SET upper_right_longitude=3.58850 WHERE id=17;
UPDATE image_sets SET lower_right_latitude=26.21540 WHERE id=17;
UPDATE image_sets SET lower_right_longitude=3.58360 WHERE id=17;
UPDATE image_sets SET lower_left_latitude=26.21500 WHERE id=17;
UPDATE image_sets SET lower_left_longitude=3.66140 WHERE id=17;

/*******************************************/
/* Update 43: Update cosmoquest image_sets */
/* table for M122184104R. Removed 1595     */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.872665</sun_angle><width>5965</width><height>10311</height>" WHERE id=17;

/*********************************************/
/* Update 44: Update cosmoquest images table */
/* for entries related to image M122184104R  */
/* Shifted images by -1595 pixels in x dime- */
/* nsion                                     */
/*********************************************/
SET diff=1595;
SET xmax=27904;
SET x=27523;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 45: Update cosmoquest image_sets */
/* table for M126901141R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.10100 WHERE id=18;
UPDATE image_sets SET upper_left_longitude=3.69960 WHERE id=18;
UPDATE image_sets SET upper_right_latitude=26.10100 WHERE id=18;
UPDATE image_sets SET upper_right_longitude=3.61960 WHERE id=18;
UPDATE image_sets SET lower_right_latitude=26.21590 WHERE id=18;
UPDATE image_sets SET lower_right_longitude=3.61960 WHERE id=18;
UPDATE image_sets SET lower_left_latitude=26.21530 WHERE id=18;
UPDATE image_sets SET lower_left_longitude=3.69960 WHERE id=18;

/*******************************************/
/* Update 46: Update cosmoquest image_sets */
/* table for M126901141R. Removed 652      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>2.26893</sun_angle><width>6071</width><height>8298</height>" WHERE id=18;

/*********************************************/
/* Update 47: Update cosmoquest images table */
/* for entries related to image M126901141R  */
/* Shifted images by -28 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=28;
SET xmax=28225;
SET x=27905;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 48: Update cosmoquest image_sets */
/* table for M127998835L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-58.10020 WHERE id=19;
UPDATE image_sets SET upper_left_longitude=-161.82920 WHERE id=19;
UPDATE image_sets SET upper_right_latitude=-58.10020 WHERE id=19;
UPDATE image_sets SET upper_right_longitude=-161.62140 WHERE id=19;
UPDATE image_sets SET lower_right_latitude=-59.16010 WHERE id=19;
UPDATE image_sets SET lower_right_longitude=-161.62140 WHERE id=19;
UPDATE image_sets SET lower_left_latitude=-59.16010 WHERE id=19;
UPDATE image_sets SET lower_left_longitude=-161.82920 WHERE id=19;

/*******************************************/
/* Update 49: Update cosmoquest image_sets */
/* table for M127998835L. Removed 46       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.785398</sun_angle><width>11573</width><height>100523</height>" WHERE id=19;

/*********************************************/
/* Update 50: Update cosmoquest images table */
/* for entries related to image M127998835L  */
/* Shifted images by -46 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=46;
SET xmax=34309;
SET x=28226;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 51: Update cosmoquest image_sets */
/* table for M127998835R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-58.11005 WHERE id=20;
UPDATE image_sets SET upper_left_longitude=-161.99860 WHERE id=20;
UPDATE image_sets SET upper_right_latitude=-58.11005 WHERE id=20;
UPDATE image_sets SET upper_right_longitude=-161.79080 WHERE id=20;
UPDATE image_sets SET lower_right_latitude=-59.16005 WHERE id=20;
UPDATE image_sets SET lower_right_longitude=-161.79080 WHERE id=20;
UPDATE image_sets SET lower_left_latitude=-59.16005 WHERE id=20;
UPDATE image_sets SET lower_left_longitude=-161.99860 WHERE id=20;

/*******************************************/
/* Update 52: Update cosmoquest image_sets */
/* table for M127998835R. Removed 76       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.785398</sun_angle><width>11212</width><height>100818</height>" WHERE id=20;

/*********************************************/
/* Update 53: Update cosmoquest images table */
/* for entries related to image M127998835R  */
/* Shifted images by -76 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=76;
SET xmax=40422;
SET x=34310;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 54: Update cosmoquest image_sets */
/* table for M138602853L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-57.06010 WHERE id=21;
UPDATE image_sets SET upper_left_longitude=-162.05850 WHERE id=21;
UPDATE image_sets SET upper_right_latitude=-57.06010 WHERE id=21;
UPDATE image_sets SET upper_right_longitude=-161.86080 WHERE id=21;
UPDATE image_sets SET lower_right_latitude=-58.09005 WHERE id=21;
UPDATE image_sets SET lower_right_longitude=-161.86080 WHERE id=21;
UPDATE image_sets SET lower_left_latitude=-58.09005 WHERE id=21;
UPDATE image_sets SET lower_left_longitude=-162.05850 WHERE id=21;

/*******************************************/
/* Update 55: Update cosmoquest image_sets */
/* table for M138602853L. Removed 75       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>2.18166</sun_angle><width>10537</width><height>96715</height>" WHERE id=21;

/*********************************************/
/* Update 56: Update cosmoquest images table */
/* for entries related to image M138602853L  */
/* Shifted images by -75 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=75;
SET xmax=46047;
SET x=40423;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 57: Update cosmoquest image_sets */
/* table for M138602853R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-57.06005 WHERE id=22;
UPDATE image_sets SET upper_left_longitude=-161.88920 WHERE id=22;
UPDATE image_sets SET upper_right_latitude=-57.06005 WHERE id=22;
UPDATE image_sets SET upper_right_longitude=-161.70140 WHERE id=22;
UPDATE image_sets SET lower_right_latitude=-58.09005 WHERE id=22;
UPDATE image_sets SET lower_right_longitude=-161.70140 WHERE id=22;
UPDATE image_sets SET lower_left_latitude=-58.09005 WHERE id=22;
UPDATE image_sets SET lower_left_longitude=-161.88920 WHERE id=22;

/*******************************************/
/* Update 58: Update cosmoquest image_sets */
/* table for M138602853R. Removed 46       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>2.18166</sun_angle><width>10312</width><height>96970</height>" WHERE id=22;

/*********************************************/
/* Update 59: Update cosmoquest images table */
/* for entries related to image M138602853R  */
/* Shifted images by -46 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=46;
SET xmax=51712;
SET x=46048;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 60: Update cosmoquest image_sets */
/* table for M146959973L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.20100 WHERE id=23;
UPDATE image_sets SET upper_left_longitude=3.62040 WHERE id=23;
UPDATE image_sets SET upper_right_latitude=26.20100 WHERE id=23;
UPDATE image_sets SET upper_right_longitude=3.69940 WHERE id=23;
UPDATE image_sets SET lower_right_latitude=26.08680 WHERE id=23;
UPDATE image_sets SET lower_right_longitude=3.69940 WHERE id=23;
UPDATE image_sets SET lower_left_latitude=26.08690 WHERE id=23;
UPDATE image_sets SET lower_left_longitude=3.62040 WHERE id=23;

/*******************************************/
/* Update 61: Update cosmoquest image_sets */
/* table for M146959973L. Removed 69       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>5.49779</sun_angle><width>4006</width><height>6651</height>" WHERE id=23;

/*********************************************/
/* Update 62: Update cosmoquest images table */
/* for entries related to image M146959973L  */
/* Shifted images by -69 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=69;
SET xmax=51896;
SET x=51713;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 63: Update cosmoquest image_sets */
/* table for M146959973R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.20995 WHERE id=24;
UPDATE image_sets SET upper_left_longitude=3.54065 WHERE id=24;
UPDATE image_sets SET upper_right_latitude=26.20995 WHERE id=24;
UPDATE image_sets SET upper_right_longitude=3.61965 WHERE id=24;
UPDATE image_sets SET lower_right_latitude=26.08965 WHERE id=24;
UPDATE image_sets SET lower_right_longitude=3.61965 WHERE id=24;
UPDATE image_sets SET lower_left_latitude=26.08965 WHERE id=24;
UPDATE image_sets SET lower_left_longitude=3.54065 WHERE id=24;

/*******************************************/
/* Update 64: Update cosmoquest image_sets */
/* table for M146959973R. Removed 0        */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>5.75959</sun_angle><width>2666</width><height>6601</height>" WHERE id=24;

/*********************************************/
/* Update 65: Update cosmoquest images table */
/* for entries related to image M146959973R  */
/* Shifted images by 0 pixels in x dime-     */
/* nsion                                     */
/*********************************************/
SET diff=0;
SET xmax=52026;
SET x=51897;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 66: Update cosmoquest image_sets */
/* table for M161000252L. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-50.85005 WHERE id=25;
UPDATE image_sets SET upper_left_longitude=-159.96920 WHERE id=25;
UPDATE image_sets SET upper_right_latitude=-50.85005 WHERE id=25;
UPDATE image_sets SET upper_right_longitude=-159.80120 WHERE id=25;
UPDATE image_sets SET lower_right_latitude=-53.05010 WHERE id=25;
UPDATE image_sets SET lower_right_longitude=-159.80120 WHERE id=25;
UPDATE image_sets SET lower_left_latitude=-53.05010 WHERE id=25;
UPDATE image_sets SET lower_left_longitude=-159.96920 WHERE id=25;

/*******************************************/
/* Update 67: Update cosmoquest image_sets */
/* table for M161000252L. Removed 27       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.785398</sun_angle><width>5735</width><height>112360</height>" WHERE id=25;

/*********************************************/
/* Update 68: Update cosmoquest images table */
/* for entries related to image M161000252L  */
/* Shifted images by 27 pixels in x dime-     */
/* nsion                                     */
/*********************************************/
SET diff=27;
SET xmax=55924;
SET x=52027;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 69: Update cosmoquest image_sets */
/* table for M161000252R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=-50.85010 WHERE id=26;
UPDATE image_sets SET upper_left_longitude=-160.12870 WHERE id=26;
UPDATE image_sets SET upper_right_latitude=-50.85010 WHERE id=26;
UPDATE image_sets SET upper_right_longitude=-159.95070 WHERE id=26;
UPDATE image_sets SET lower_right_latitude=-53.05010 WHERE id=26;
UPDATE image_sets SET lower_right_longitude=-159.95070 WHERE id=26;
UPDATE image_sets SET lower_left_latitude=-53.05010 WHERE id=26;
UPDATE image_sets SET lower_left_longitude=-160.12870 WHERE id=26;

/*******************************************/
/* Update 70: Update cosmoquest image_sets */
/* table for M161000252R. Removed 44       */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.785398</sun_angle><width>5998</width><height>112700</height>" WHERE id=26;

/*********************************************/
/* Update 71: Update cosmoquest images table */
/* for entries related to image M161000252R  */
/* Shifted images by 44 pixels in x dime-    */
/* nsion                                     */
/*********************************************/
SET diff=44;
SET xmax=59843;
SET x=55925;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 72: Update cosmoquest image_sets */
/* table for M162284113R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.21030 WHERE id=27;
UPDATE image_sets SET upper_left_longitude=3.61510 WHERE id=27;
UPDATE image_sets SET upper_right_latitude=26.21060 WHERE id=27;
UPDATE image_sets SET upper_right_longitude=3.68970 WHERE id=27;
UPDATE image_sets SET lower_right_latitude=26.08760 WHERE id=27;
UPDATE image_sets SET lower_right_longitude=3.68970 WHERE id=27;
UPDATE image_sets SET lower_left_latitude=26.08720 WHERE id=27;
UPDATE image_sets SET lower_left_longitude=3.61510 WHERE id=27;

/*******************************************/
/* Update 73: Update cosmoquest image_sets */
/* table for M162284113R. Removed 866      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>5.75959</sun_angle><width>6074</width><height>10838</height>" WHERE id=27;

/*********************************************/
/* Update 74: Update cosmoquest images table */
/* for entries related to image M162284113R  */
/* Shifted images by -85 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=85;
SET xmax=60270;
SET x=59844;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x;
SET x=x+1;
END WHILE;

/*******************************************/
/* Update 75: Update cosmoquest image_sets */
/* table for M170538271R. Maximum/minimum  */
/* latitude and longitude (user view)      */
/*******************************************/
UPDATE image_sets SET upper_left_latitude=26.09130 WHERE id=28;
UPDATE image_sets SET upper_left_longitude=3.68660 WHERE id=28;
UPDATE image_sets SET upper_right_latitude=26.08520 WHERE id=28;
UPDATE image_sets SET upper_right_longitude=3.60630 WHERE id=28;
UPDATE image_sets SET lower_right_latitude=26.20870 WHERE id=28;
UPDATE image_sets SET lower_right_longitude=3.60630 WHERE id=28;
UPDATE image_sets SET lower_left_latitude=26.21340 WHERE id=28;
UPDATE image_sets SET lower_left_longitude=3.68660 WHERE id=28;

/*******************************************/
/* Update 76: Update cosmoquest image_sets */
/* table for M170538271R. Removed 503      */
/* pixels in x dimension                   */
/*******************************************/
UPDATE image_sets SET details="<sun_angle>0.872665</sun_angle><width>5906</width><height>9762</height>" WHERE id=28;

/*********************************************/
/* Update 77: Update cosmoquest images table */
/* for entries related to image M170538271R  */
/* Shifted images by -104 pixels in x dime-   */
/* nsion                                     */
/*********************************************/
SET diff=104;
SET xmax=60638;
SET x=60271;
WHILE x <= xmax DO
SET str1=(SELECT details FROM images WHERE id=x);
SET substr1=SUBSTRING_INDEX(str1,"<", 4);
SET substr3=SUBSTRING_INDEX(str1,"<", -7);
SET arg=CAST(SUBSTRING_INDEX(substr1,">", -1) AS UNSIGNED);
SET substr1=CONCAT(SUBSTRING_INDEX(str1,">", 3), ">");
SET substr3=CONCAT("<", substr3);
SET arg=arg-diff;
SET substr2=CAST(arg AS CHAR);
SET str2=CONCAT(substr1,substr2,substr3);
UPDATE images SET details=str2 WHERE id=x AND application_id=1;
SET x=x+1;
END WHILE;

END$$
DELIMITER ;
