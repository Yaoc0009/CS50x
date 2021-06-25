from sys import argv, exit
import csv


def main():

    if len(argv) != 3:
        exit("Usage: python dna.py data.csv sequence.txt")

    persons = []
    # Open data csv file
    with open(argv[1], "r") as data:
        reader = csv.DictReader(data)
        # Iterate through file, append person to persons
        for row in reader:
            persons.append(row)

    # Open sequence txt file
    with open(argv[2], "r") as sequence:
        # Read dna seq and store as string
        dna_seq = sequence.readlines()[0]

    # Identify STRs that are relevant
    strs = findSTR(persons)

    # Count consecutive sequence of STRs in sequence
    counts = countSTRs(dna_seq, strs)

    # Find match for sequence, print name
    for person in persons:
        check = 0
        # Add 1 to check if counts don't match
        for s in strs:
            if int(person[s]) != counts[s]:
                check += 1

        # For person with any unmatched counts, check != 0
        if check == 0:
            print(person["name"])
            exit()
    print("No match")


def findSTR(persons):

    # Find STRs from persons
    strs = []
    for key in persons[0]:
        strs.append(key)
    strs = strs[1:]

    return strs


def countSTRs(seq, strs):
    # Init counts dict
    counts = {}
    # Iterate through str
    for s in strs:
        count = 0
        pattern = s
        # while pattern in seq, extend pattern by a repetition
        while pattern in seq:
            count += 1
            pattern += s
        # Assign s : count to dict
        counts[s] = count

    return counts


if __name__ == "__main__":
    main()