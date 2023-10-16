import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid usage.")
        return

    # TODO: Read database file into a variable

    with open(sys.argv[1]) as csvfile:
        database = csv.DictReader(csvfile)
        str_list = database.fieldnames[1:]

        # print(str_list)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dnafile:
        sequence = dnafile.read()

    # # TODO: Find longest match of each STR in DNA sequence
    sample = []
    test = []

    for i in range(len(str_list)):
        sample.append(longest_match(sequence, str_list[i]))

    # print(sample)

    # TODO: Check database for matching profiles
    with open(sys.argv[1]) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            for str in str_list:
                # print(row[str])
                test.append(int(row[str]))

            if test == sample:
                print(row["name"])
                return

            test = []

        print("No match.")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
