# Purpose: Convert ASCII text table to Latex table

# Imported modules/libraries
import argparse as ap
import pandas as pd
import re
import sys


def numericString(n):
    if n >= 1:
        return "{0}".format(int(n)) if n.is_integer() else "{0}".format(round(n, 2))
    elif 0.1 <= n < 1:
        return str(round(n, 2))
    else:
        sval = "{:.2e}".format(n)
        pos = sval.find("e")
        power = int(sval[pos+1:])
        return sval[0:pos] + " \\times " + "10^{0}{1}{2}".format("{", power, "}") 


def converter(s1, s2):
    l = ""
    n = len(s1)
    if n == len(s2):
        for i in range(n):
            # Single value needed for first two entries, remaining values are composed of split data
            if i < 2:
                # Determine if number should be written in scientific notation
                l += numericString(s1[i])
            else:
                # Append first value
                l += numericString(s1[i])
                
                # Append character representing split data
                l += "/"

                # Append second value
                l += numericString(s2[i])
                
            # Append column seperator character
            if (i + 1) != n:
                l += " & "
        l += "\\\\"

    return l


def main(argv):
    # Retrieve arguments
    parser = ap.ArgumentParser()
    parser.add_argument("table1",
                        help="File containing first table")
    parser.add_argument("table2",
                        help="File containing second table")
    args = parser.parse_args()
    table1 = args.table1
    table2 = args.table2
    
    # Read each file into Pandas Dataframe
    df1 = pd.read_csv(table1, sep="\t")
    df2 = pd.read_csv(table2, sep="\t")

    # Convert to Latex format
    lines = []
    for i in range(len(df1)):
        l = converter(df1.loc[i], df2.loc[i])
        lines.append(l)

    # Print converted Latex table
    for l in lines:
        print(l)


if __name__ == "__main__":
    main(sys.argv[1:])
