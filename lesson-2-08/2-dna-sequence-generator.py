import random
import argparse

parser = argparse.ArgumentParser(description='Generate "DNA.txt" file with random sequence')
parser.add_argument('-l', '--length', help='length of sequence', type=int)
args = parser.parse_args()

seq_length = args.length

if seq_length is None:
    parser.print_help()
else:
    with open('DNA.txt', 'w') as file:
        sequence = ''.join(random.choices('AGTC', k=seq_length))
        file.write(sequence)