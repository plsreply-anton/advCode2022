import sys

def part1(textFile):
    print("PART 1")
    hands = {'A': 1, 'B': 2, 'C': 3, 'X': 1, 'Y': 2, 'Z': 3}
    totalScore = 0
    with open(textFile, "r") as file:
        for line in file:
            opponent_choice, your_choice = line.strip().split()  # Split the line into two characters
            totalScore += hands[your_choice]
            if hands[your_choice] == hands[opponent_choice]:
                totalScore += 3  # Draw
            elif (hands[your_choice] == 1 and hands[opponent_choice] == 3) or \
                 (hands[your_choice] == 2 and hands[opponent_choice] == 1) or \
                 (hands[your_choice] == 3 and hands[opponent_choice] == 2):
                totalScore += 6  # You win
            else:
                totalScore += 0  # You lose

    print(f"Total Score: {totalScore}\n")
    
def part2(textFile):
    print("PART 2")
    hands = {'A': 1, 'B': 2, 'C': 3, 'X': 0, 'Y': 3, 'Z': 6}
    totalScore = 0
    with open(textFile, "r") as file:
        for line in file:
            opponent_choice, result = line.strip().split()  # Split the line into two characters
            totalScore += hands[result]
            if hands[result] == 3: #draw
                totalScore += hands[opponent_choice]
            elif (hands[result] == 6 and hands[opponent_choice] == 3):
                totalScore += hands['A']
            elif (hands[result] == 6 and hands[opponent_choice] == 2):
                totalScore += hands['C']
            elif (hands[result] == 6 and hands[opponent_choice] == 1):
                totalScore += hands['B']
            elif (hands[result] == 0 and hands[opponent_choice] == 3):
                totalScore += hands['B']
            elif (hands[result] == 0 and hands[opponent_choice] == 2):
                totalScore += hands['A']
            elif (hands[result] == 0 and hands[opponent_choice] == 1):
                totalScore += hands['C']
    print(f"Total Score: {totalScore}")
    
def main():
    if len(sys.argv) < 2:
        print("No input file specified, falling back to: day2Input.txt\n")
        textFile = "day2Input.txt"
    else:
        textFile = sys.argv[1]
        
    part1(textFile)
    part2(textFile)
        
    

if __name__ == "__main__":
    main()

